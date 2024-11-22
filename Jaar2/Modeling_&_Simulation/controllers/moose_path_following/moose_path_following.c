#include <math.h>
#include <stdio.h>
#include <time.h>
#include <webots/compass.h>
#include <webots/gps.h>
#include <webots/keyboard.h>
#include <webots/motor.h>
#include <webots/robot.h>
#include <webots/camera.h>
#include <webots/distance_sensor.h>


#define TIME_STEP 16
#define TARGET_POINTS_SIZE 8
#define DISTANCE_TOLERANCE 1.5
#define MAX_SPEED 7.0
#define TURN_COEFFICIENT 4.0
#define RED_THRESHOLD 100

enum XYZAComponents { X = 0, Y, Z, ALPHA };
enum Sides { LEFT, RIGHT };

typedef struct _Vector {
  double u;
  double v;
} Vector;

static WbDeviceTag motors[8];
static WbDeviceTag gps;
static WbDeviceTag compass;
static WbDeviceTag camera;
static WbDeviceTag distance_sensor;
static const char *camera_name = {"camera"};

Vector targets[TARGET_POINTS_SIZE] = {
  {21.21, 3.3}, {6.43, 4.50}, {-20.08, 4.50},   {-20.4, 0},  {-21.4, -1.6},
  {-14.22, -4.46}, {19.5, -4.46}, {20.3061, -1.42275}
};
static int current_target_index = 0;
static bool autopilot = true;

static double modulus_double(double a, double m) {
  const int div = (int)(a / m);
  double r = a - div * m;
  if (r < 0.0)
    r += m;
  return r;
}

// set left and right motor speed [rad/s]
static void robot_set_speed(double left, double right) {
  int i;
  for (i = 0; i < 4; i++) {
    wb_motor_set_velocity(motors[i + 0], left);
    wb_motor_set_velocity(motors[i + 4], right);
  }
}



// ||v||
static double norm(const Vector *v) {
  return sqrt(v->u * v->u + v->v * v->v);
}

// v = v/||v||
static void normalize(Vector *v) {
  double n = norm(v);
  v->u /= n;
  v->v /= n;
}

// v = v1-v2
static void minus(Vector *v, const Vector *const v1, const Vector *const v2) {
  v->u = v1->u - v2->u;
  v->v = v1->v - v2->v;
}

// autopilot
// pass trough the predefined target positions
static void run_autopilot(bool red,double sensorvalue) {
  double speeds[2] = {0.0, 0.0};
  if(red&&sensorvalue<0.5){
    speeds[LEFT] = 0;
    speeds[RIGHT] = 0;
    robot_set_speed(speeds[LEFT], speeds[RIGHT]);
    return;
  }
  
  // read gps position and compass values
  const double *position_3d = wb_gps_get_values(gps);
  const double *north_3d = wb_compass_get_values(compass);

  // compute the 2D position of the robot and its orientation
  const Vector position = {position_3d[X], position_3d[Y]};

  // compute the direction and the distance to the target
  Vector direction;
  minus(&direction, &(targets[current_target_index]), &position);
  const double distance = norm(&direction);
  normalize(&direction);

  // compute the error angle
  const double robot_angle = atan2(north_3d[0], north_3d[1]);
  const double target_angle = atan2(direction.v, direction.u);
  double beta = modulus_double(target_angle - robot_angle, 2.0 * M_PI) - M_PI;

  // move singularity
  if (beta > 0)
    beta = M_PI - beta;
  else
    beta = -beta - M_PI;

  // a target position has been reached
  if (distance < DISTANCE_TOLERANCE) {
    char index_char[3] = "th";
    if (current_target_index == 0)
      sprintf(index_char, "st");
    else if (current_target_index == 1)
      sprintf(index_char, "nd");
    else if (current_target_index == 2)
      sprintf(index_char, "rd");
    printf("%d%s target reached\n", current_target_index + 1, index_char);
    current_target_index++;
    current_target_index %= TARGET_POINTS_SIZE;
  }
  // move the robot to the next target
  else {
    speeds[LEFT] = MAX_SPEED - M_PI + TURN_COEFFICIENT * beta;
    speeds[RIGHT] = MAX_SPEED - M_PI - TURN_COEFFICIENT * beta;
  }

  // set the motor speeds
  robot_set_speed(speeds[LEFT], speeds[RIGHT]);
}

int main(int argc, char *argv[]) {
  // initialize webots communication
  wb_robot_init();
  srand(time(NULL));
  int r = rand()%2;
  // int r = 1;
  if(r==1){
    Vector targets2 [TARGET_POINTS_SIZE] = {
    {21.21, 3.3}, {6.43, 4.50}, {-9.08, 4.50},   {-9.08, -20.9},  {0.6, -20},
    {5.87, -4.46}, {19.5, -4.46}, {20.3061, -1.42275}
    };
    for(int i = 0; i< TARGET_POINTS_SIZE;i++){
      targets[i] = targets2[i];
    }
  }
  gps = wb_robot_get_device("gps");
  wb_gps_enable(gps, TIME_STEP);
  // print user instructionss

  wb_robot_step(1000);

  const char *names[8] = {"left motor 1",  "left motor 2",  "left motor 3",  "left motor 4",
                          "right motor 1", "right motor 2", "right motor 3", "right motor 4"};

  // get motor tags
  int i;
  for (i = 0; i < 8; i++) {
    motors[i] = wb_robot_get_device(names[i]);
    wb_motor_set_position(motors[i], INFINITY);
  }

  // get gps tag and enable
  gps = wb_robot_get_device("gps");
  wb_gps_enable(gps, TIME_STEP);

  // get compass tag and enable
  compass = wb_robot_get_device("compass");
  wb_compass_enable(compass, TIME_STEP);

  // enable keyboard
  wb_keyboard_enable(TIME_STEP);
  distance_sensor = wb_robot_get_device("dist");
  wb_distance_sensor_enable(distance_sensor, TIME_STEP);
  
  // start forward motion
  robot_set_speed(MAX_SPEED, MAX_SPEED);
  camera = wb_robot_get_device(camera_name);
  if (camera > 0)
    wb_camera_enable(camera, TIME_STEP);
  // main loop
  
  while (wb_robot_step(TIME_STEP) != -1) {
    const unsigned char *image = wb_camera_get_image(camera);
    bool red_detected = false;
    int red = wb_camera_image_get_red(image, 1, 0, 0);
    int green = wb_camera_image_get_green(image, 1, 0, 0);
    int blue = wb_camera_image_get_blue(image, 1, 0, 0);
    if (red > RED_THRESHOLD && green < RED_THRESHOLD && blue < RED_THRESHOLD) {
        red_detected = true;
    }
    double sensorvalue = wb_distance_sensor_get_value(distance_sensor);
    // check_keyboard();
    if (autopilot)
      run_autopilot(red_detected,sensorvalue);
  }

  wb_robot_cleanup();

  return 0;
}
