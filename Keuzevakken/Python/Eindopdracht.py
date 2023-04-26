import turtle as tu
import time as ti

class RaceTrack:
    def __init__(self):
        self.screen = tu.Screen ()
        self.screenWidth = 1500
        self.screenHeight = 500
        self.offset = 50
        self.screen.setup (self.screenWidth, self.screenHeight)
        self.screen.bgpic('AsphaltBG.png')
        self.screen.listen ()
        self.screen.onkey (self.printA, 'a')
        self.screen.onkey (self.printZ, 'z')
        self.screen.onkey (self.printK, 'k')
        self.screen.onkey (self.printM, 'm')
        self.time = ti.time ()
        self.car1 = Car1()
        self.car2 = Car2()
        self.button = tu.Pen()
        self.safetyCar = tu.Pen()
        self.car1.setShape(self.screen)
        self.car2.setShape(self.screen)
        self.finishedCar = False
        self.speedScaler = 10
        self.stop = False

    def buttonSetup(self):
        self.button.shape("circle")
        self.button.pu()
        self.button.goto(0, self.screenHeight/2-30)
        self.button.pd()
        self.button.color("white")
        FONT_SIZE = 12
        FONT = ('Arial', FONT_SIZE, 'bold')
        self.button.write("Click me to stop!", align='center', font=FONT)
        self.button.color("red")

    def end(self,x,y):
        self.screen.clear()
        self.stop = True

    def printA (self):
        if self.car1.car1.pos()[0]> (self.screenWidth/2)-self.offset*2+self.safetyCar.pensize()/2 and self.car1.car1.pos()[0]<self.screenWidth/2-self.safetyCar.pensize() and self.car1.speed == 0:
            self.car1.speed = 0
        else:
            self.car1.accel(self.deltaTime)
        
    def printZ (self):
        self.car1.slowdown(self.deltaTime)
    
    def printK(self):
        if self.car2.car2.pos()[0]> (self.screenWidth/2)-self.offset*2+self.safetyCar.pensize()/2 and self.car2.car2.pos()[0]<self.screenWidth/2-self.safetyCar.pensize() and self.car2.speed == 0:
            self.car2.speed = 0
        else:
            self.car2.accel(self.deltaTime)

    def printM(self):
        self.car2.slowdown(self.deltaTime)

    def createTrack(self):
        self.safetyCar.speed(5)
        self.safetyCar.pensize(5)
        self.safetyCar.color('white')
        self.safetyCar.pu()
        self.safetyCar.goto(-self.screenWidth/2,-self.screenHeight/2+self.offset)
        self.safetyCar.pd()
        self.safetyCar.fd(self.screenWidth)
        self.safetyCar.pu()
        self.safetyCar.goto(-self.screenWidth/2,self.screenHeight/2-self.offset)
        self.safetyCar.pd()
        self.safetyCar.fd(self.screenWidth)
        self.safetyCar.pu()
        self.safetyCar.goto(-self.screenWidth/2,0)
        self.safetyCar.pd()
        while(self.safetyCar.pos()[0]<self.screenWidth/2):
            self.safetyCar.fd(self.screenWidth/10)
            self.safetyCar.pu()
            self.safetyCar.fd(self.screenWidth/10)
            self.safetyCar.pd()
        self.safetyCar.pu()
        self.safetyCar.pensize(20)
        self.safetyCar.color('yellow')
        self.safetyCar.goto(self.screenWidth/2-self.offset*2,self.screenHeight/2-self.offset-self.safetyCar.pensize()/2)
        self.safetyCar.pd()
        self.safetyCar.goto(self.screenWidth/2-self.offset*2,-self.screenHeight/2+self.offset+self.safetyCar.pensize()/2)
        self.safetyCar.pu()
        self.safetyCar.color('red')
        self.safetyCar.goto(self.screenWidth/2-self.safetyCar.pensize(),self.screenHeight/2-self.offset-self.safetyCar.pensize()/2)
        self.safetyCar.pd()
        self.safetyCar.goto(self.screenWidth/2-self.safetyCar.pensize(),-self.screenHeight/2+self.offset+self.safetyCar.pensize()/2)
        self.safetyCar.pu()
        self.safetyCar.hideturtle()
        self.createLights()

    def createLights(self):
        self.safetyCar.pencolor('black')
        self.safetyCar.goto(-self.screenWidth/2+self.offset*2, 0)
        self.safetyCar.pd()
        self.safetyCar.goto(-self.screenWidth/2+self.offset*4, 0)
        self.safetyCar.pu()
        self.safetyCar.speed(2)
        self.safetyCar.color('red')
        self.safetyCar.goto(-self.screenWidth/2+self.offset*3.8,0)
        self.safetyCar.pd()
        self.safetyCar.goto(self.safetyCar.pos()[0]+1,self.safetyCar.pos()[1])
        self.safetyCar.pu()
        self.safetyCar.goto(0,0)
        self.safetyCar.color('orange')
        self.safetyCar.goto(-self.screenWidth/2+self.offset*3,0)
        self.safetyCar.pd()
        self.safetyCar.goto(self.safetyCar.pos()[0]+1,self.safetyCar.pos()[1])
        self.safetyCar.pu()
        self.safetyCar.goto(0,0)
        self.safetyCar.color('green')
        self.safetyCar.goto(-self.screenWidth/2+self.offset*2.2,0)
        self.safetyCar.pd()
        self.safetyCar.goto(self.safetyCar.pos()[0]+1,self.safetyCar.pos()[1])
        self.safetyCar.pencolor('red')
        self.safetyCar.speed(5)
        self.safetyCar.pu()

    def run (self):
        self.button.onclick(self.end)
        self.buttonSetup()
        self.createTrack()
        while self.stop!=True:
            self.oldTime = self.time
            self.time = ti.time ()
            self.deltaTime = self.time - self.oldTime
            if self.car1.car1.pos()[0]> (self.screenWidth/2)-self.offset*2+self.safetyCar.pensize()/2 and self.car1.car1.pos()[0]<self.screenWidth/2-self.safetyCar.pensize() and self.car1.speed == 0:
                self.safetyCar.goto((self.screenWidth/2)-self.offset*3,self.screenHeight/4)
                self.safetyCar.pd()
                if self.finishedCar == False:
                    if self.car1.finished == False:
                        self.safetyCar.write('WINNER')
                        self.car1.finished = True
                    self.finishedCar = True
                else:
                    if self.car1.finished == False:
                        self.safetyCar.write('LOST')
                        self.car1.finished = True
                self.safetyCar.pu()
            elif self.car1.car1.pos()[0]+self.car1.speed/self.speedScaler <= (self.screenWidth/2)-self.safetyCar.pensize():
                self.car1.car1.fd(self.car1.speed/self.speedScaler)
            else:
                self.safetyCar.goto((self.screenWidth/2)-self.offset*2+self.safetyCar.pensize()/2,self.screenHeight/4)
                self.safetyCar.pd()
                if self.car1.finished == False:
                    self.car1.finished = True
                    self.safetyCar.write('DEFEAT')
                self.safetyCar.pu()
            
            if self.car2.car2.pos()[0]> (self.screenWidth/2)-self.offset*2+self.safetyCar.pensize()/2 and self.car2.car2.pos()[0]<self.screenWidth/2-self.safetyCar.pensize() and self.car2.speed == 0:
                self.safetyCar.goto((self.screenWidth/2)-self.offset*3,-self.screenHeight/4)
                self.safetyCar.pd()
                if self.finishedCar == False:
                    if self.car2.finished == False:
                        self.car2.finished = True
                        self.safetyCar.write('WINNER')
                    self.finishedCar = True
                else:
                    if self.car2.finished == False:
                        self.car2.finished = True
                        self.safetyCar.write('LOST')
                self.safetyCar.pu()
            elif self.car2.car2.pos()[0]+self.car2.speed/self.speedScaler <= (self.screenWidth/2)-self.safetyCar.pensize():
                self.car2.car2.fd(self.car2.speed/self.speedScaler)
            else:
                self.safetyCar.goto((self.screenWidth/2)-self.offset*2+self.safetyCar.pensize()/2,-self.screenHeight/4)
                self.safetyCar.pd()
                if self.car2.finished == False:
                    self.car2.finished = True
                    self.safetyCar.write('DEFEAT')
                self.safetyCar.pu()

            self.screen.update ()
            ti.sleep (0.02)
        tu.done()

class Car1:
    def __init__(self):
        self.screenWidth = 1500
        self.screenHeight = 500
        self.offset = 50
        self.car1 = tu.Pen()
        self.car1.pu()
        self.car1.goto(-self.screenWidth/2+50, self.screenHeight/4)
        self.acceleration = 10
        self.speed = 0
        self.maxSpeed = 300
        self.finished = False

    def setShape(self,screen):
        box = ((-10, -20), (-10, 20), (10, 20), (10, -20))
        window = ((-8, 5), (-8, 10), (8, 10), (8, 5))
        backplate = ((-5, -10), (-7, 0), (7, 0), (5, -10))
        spoilerStand1 = ((-6,-16),(-6,-14),(-5,-14),(-5,-16))
        spoilerStand2 = ((6,-16),(6,-14),(5,-14),(5,-16))
        spoiler = ((-11,-17),(-11,-19),(11,-19),(11,-17))
        carShape = tu.Shape ('compound')
        carShape.addcomponent (box, 'red')
        carShape.addcomponent (window, 'cyan')
        carShape.addcomponent (backplate, 'dark red')
        carShape.addcomponent (spoilerStand1, 'black')
        carShape.addcomponent (spoilerStand2, 'black')
        carShape.addcomponent (spoiler, 'black')
        screen.register_shape ('car',carShape)
        self.car1.shape('car')

    def accel(self, deltaTime):
        if self.speed + self.acceleration*deltaTime<=self.maxSpeed:
            self.speed += self.acceleration*deltaTime
        else:
            self.speed=self.maxSpeed

    def slowdown(self, deltaTime):
        if self.speed - self.acceleration*deltaTime >= 0:
            self.speed -= self.acceleration*deltaTime
        else:
            self.speed = 0
        

class Car2:
    def __init__(self):
        self.screenWidth = 1500
        self.screenHeight = 500
        self.offset = 50
        self.car2 = tu.Pen()
        self.car2.pu()
        self.car2.goto(-self.screenWidth/2+50, -self.screenHeight/4)
        self.acceleration = 10
        self.speed = 0
        self.maxSpeed = 300
        self.finished = False

    def setShape(self,screen):
        box = ((-10, -20), (-10, 20), (10, 20), (10, -20))
        window = ((-8, 5), (-8, 10), (8, 10), (8, 5))
        backplate = ((-5, -10), (-7, 0), (7, 0), (5, -10))
        spoilerStand1 = ((-6,-16),(-6,-14),(-5,-14),(-5,-16))
        spoilerStand2 = ((6,-16),(6,-14),(5,-14),(5,-16))
        spoiler = ((-11,-17),(-11,-19),(11,-19),(11,-17))
        carShape2 = tu.Shape ('compound')
        carShape2.addcomponent (box, 'blue')
        carShape2.addcomponent (window, 'cyan')
        carShape2.addcomponent (backplate, 'dark blue')
        carShape2.addcomponent (spoilerStand1, 'black')
        carShape2.addcomponent (spoilerStand2, 'black')
        carShape2.addcomponent (spoiler, 'black')
        screen.register_shape ('car2',carShape2)
        self.car2.shape('car2')

    def accel(self, deltaTime):
        if self.speed + self.acceleration*deltaTime<=self.maxSpeed:
            self.speed += self.acceleration*deltaTime
        else:
            self.speed=self.maxSpeed

    def slowdown(self, deltaTime):
        if self.speed - self.acceleration*deltaTime >= 0:
            self.speed -= self.acceleration*deltaTime
        else:
            self.speed = 0


track1 = RaceTrack ()
track1.run ()