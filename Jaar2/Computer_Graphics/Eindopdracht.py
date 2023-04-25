'''
Eindopdracht Computer Graphics
Rowan van der Zanden (1027332)

Controls: A,S,K,L,C,V,B
'''
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
from PIL import Image
import numpy
import freetype
from array import *
#freeType = overlay with letters

#translations for every cube
trans = ((0.5,0.5,0.5,0),(-0.5,0.5,0.5,0),(-0.5,-0.5,0.5,0),(0.5,-0.5,0.5,0),(0.5,0.5,-0.5,0),(-0.5,0.5,-0.5,0),(-0.5,-0.5,-0.5,0),(0.5,-0.5,-0.5,0))
#colours for every cube
color = ((0,0,1),(1,0,0),(1,1,1),\
        (0,0,1),(1,0.5,0),(1,1,1),\
        (0,1,0),(1,0.5,0),(1,1,1),\
        (0,1,0),(1,0,0),(1,1,1),\
        (0,0,1),(1,0,0),(1,1,0),\
        (0,0,1),(1,0.5,0),(1,1,0),\
        (0,1,0),(1,0.5,0),(1,1,0),\
        (0,1,0),(1,0,0),(1,1,0))
STEPSIZE = 1
ROTATION = 0 # direction of rotation
STEPS = 0    # number of rotations
class Cube:
    def __init__(self,pos):
        self.pos = pos
        self.angleX = 0 # current angle on X axle
        self.angleZ = 0 # current angle on Z axle
        self.headingX = 0 # heading angle on X axle
        self.headingZ = 0 # heading angle on Z axle
        self.currentPos = pos
        self.angleY = 0 # current angle on Y axle
    def setAngle(self,angleX,angleZ):
        if angleX < 0:
            if self.angleX >= 0-angleX:
                self.angleX += angleX
            else:
                self.angleX = self.angleX+angleX+360
        elif angleX > 0:
            if self.angleX <= 360+angleX:
                self.angleX += angleX
            else:
                self.angleX = self.angleX+angleX-360
        if angleZ < 0:
            if self.angleZ >= 0-angleZ:
                self.angleZ += angleZ
            else:
                self.angleZ = self.angleZ+angleZ+360
        elif angleZ > 0:
            if self.angleZ <= 360+angleZ:
                self.angleZ += angleZ
            else:
                self.angleZ = self.angleZ+angleZ-360
    def setPos(self,pos):
        self.currentPos = pos
    def drawCube(self):
        self.angleY += ROTATION/5
        if self.angleX < self.headingX and self.headingX-self.angleX<=180:
            self.setAngle(STEPSIZE,0)
        elif self.angleX < self.headingX and self.headingX-self.angleX>180:
            self.setAngle(-STEPSIZE,0)
        elif self.angleX > self.headingX and self.angleX-self.headingX<=180:
            self.setAngle(-STEPSIZE,0)
        elif self.angleX > self.headingX and self.angleX-self.headingX>180:
            self.setAngle(STEPSIZE,0)
        else:
            self.setAngle(0,0)
        if self.angleZ < self.headingZ and self.headingZ-self.angleZ<=180:
            self.setAngle(0,STEPSIZE)
        elif self.angleZ < self.headingZ and self.headingZ-self.angleZ>180:
            self.setAngle(0,-STEPSIZE)
        elif self.angleZ > self.headingZ and self.angleZ-self.headingZ<=180:
            self.setAngle(0,-STEPSIZE)
        elif self.angleZ > self.headingZ and self.angleZ-self.headingZ>180:
            self.setAngle(0,STEPSIZE)
        else:
            self.setAngle(0,0)

        glRotate(self.angleY,0,1,0)
        if self.currentPos == 1 or self.currentPos == 2:
            glRotate(self.angleZ,0,0,1)
            glRotate(self.angleX,1,0,0)
        elif self.currentPos == 4 or self.currentPos == 7:
            glRotate(self.angleX,1,0,0)
            glRotate(self.angleZ,0,0,1)
        else:
            if self.currentPos == 0:
                if self.headingX != 0:
                    glRotate(self.angleX,1,0,0)
                    glRotate(self.angleZ,0,0,1)
                else:
                    glRotate(self.angleZ,0,0,1)
                    glRotate(self.angleX,1,0,0)
            elif self.currentPos == 3:
                if self.headingX != 0:
                    glRotate(self.angleX,1,0,0)
                    glRotate(self.angleZ,0,0,1)
                else:
                    glRotate(self.angleZ,0,0,1)
                    glRotate(self.angleX,1,0,0)
        glTranslate(trans[self.pos][0],\
                    trans[self.pos][1],\
                    trans[self.pos][2])
        glMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, [0.5, 0.5, 0.5, 1])
        glEnable(GL_TEXTURE_2D)
        glutSolidCube(1)
        glDisable(GL_TEXTURE_2D)
        glMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, [color[self.pos*3][0], color[self.pos*3][1], color[self.pos*3][2], 1])
        glTranslate(0,0.1,0)
        glutSolidCube(0.9)
        glTranslate(0,-0.2,0)
        glutSolidCube(0.9)
        glMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, [color[self.pos*3+1][0], color[self.pos*3+1][1], color[self.pos*3+1][2], 1])
        glTranslate(0.1,0.1,0)
        glutSolidCube(0.9)
        glTranslate(-0.2,0,0)
        glutSolidCube(0.9)
        glMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, [color[self.pos*3+2][0], color[self.pos*3+2][1], color[self.pos*3+2][2], 1])
        glTranslate(0.1,0,0.1)
        glutSolidCube(0.9)
        glTranslate(0,0,-0.2)
        glutSolidCube(0.9)
        glTranslate(0,0,0.1)
        glTranslate(-trans[self.pos][0],\
                    -trans[self.pos][1],\
                    -trans[self.pos][2])
        if self.currentPos == 1 or self.currentPos == 2:
            glRotate(-self.angleX,1,0,0)
            glRotate(-self.angleZ,0,0,1)
        elif self.currentPos == 4 or self.currentPos == 7:
            glRotate(-self.angleZ,0,0,1)
            glRotate(-self.angleX,1,0,0)
        else:
            if self.currentPos == 0:
                if self.headingX != 0:
                    glRotate(-self.angleZ,0,0,1)
                    glRotate(-self.angleX,1,0,0)
                else:
                    glRotate(-self.angleX,1,0,0)
                    glRotate(-self.angleZ,0,0,1)
            elif self.currentPos == 3:
                if self.headingX != 0:
                    glRotate(-self.angleZ,0,0,1)
                    glRotate(-self.angleX,1,0,0)
                else:
                    glRotate(-self.angleX,1,0,0)
                    glRotate(-self.angleZ,0,0,1)
        glRotate(-self.angleY,0,1,0)

cubeArray = [Cube(0)]*len(trans)
for i in range(len(trans)):
    cubeArray[i] = Cube(i)

def buttons(key,x,y):
    global ROTATION
    global STEPS
    if key == b'b':
        ROTATION = 1
    if key == b'v':
        ROTATION = 0
    if key == b'c':
        ROTATION = -1
    if key == b'a':
        STEPS+=1
        for i in range(len(cubeArray)):
            if cubeArray[i].currentPos < 3:
                if cubeArray[i].headingZ < 270:
                    cubeArray[i].headingZ += 90
                else:
                    cubeArray[i].headingZ = 0
                cubeArray[i].setPos(cubeArray[i].currentPos+1)
            elif cubeArray[i].currentPos == 3:
                if cubeArray[i].headingZ < 270:
                    cubeArray[i].headingZ += 90
                else:
                    cubeArray[i].headingZ = 0
                cubeArray[i].setPos(0)
    if key == b's':
        STEPS+=1
        for i in range(len(cubeArray)):
            if cubeArray[i].currentPos == 0:
                if cubeArray[i].headingZ > 0:
                    cubeArray[i].headingZ -= 90
                else:
                    cubeArray[i].headingZ = 270
                cubeArray[i].setPos(3)
            elif cubeArray[i].currentPos < 4:
                if cubeArray[i].headingZ > 0:
                    cubeArray[i].headingZ -= 90
                else:
                    cubeArray[i].headingZ = 270
                cubeArray[i].setPos(cubeArray[i].currentPos-1)
    if key == b'k':
        STEPS+=1
        for i in range(len(cubeArray)):
            match cubeArray[i].currentPos:
                case 0:
                    if cubeArray[i].headingX < 270:
                        cubeArray[i].headingX += 90
                    else:
                        cubeArray[i].headingX = 0
                    cubeArray[i].setPos(3)
                case 3:
                    if cubeArray[i].headingX < 270:
                        cubeArray[i].headingX += 90
                    else:
                        cubeArray[i].headingX = 0
                    cubeArray[i].setPos(7)
                case 4:
                    if cubeArray[i].headingX < 270:
                        cubeArray[i].headingX += 90
                    else:
                        cubeArray[i].headingX = 0
                    cubeArray[i].setPos(0)
                case 7:
                    if cubeArray[i].headingX < 270:
                        cubeArray[i].headingX += 90
                    else:
                        cubeArray[i].headingX = 0
                    cubeArray[i].setPos(4)
    if key == b'l':
        STEPS+=1
        for i in range(len(cubeArray)):
            match cubeArray[i].currentPos:
                case 0:
                    if cubeArray[i].headingX > 0:
                        cubeArray[i].headingX -= 90
                    else:
                        cubeArray[i].headingX = 270
                    cubeArray[i].setPos(4)
                case 3:
                    if cubeArray[i].headingX > 0:
                        cubeArray[i].headingX -= 90
                    else:
                        cubeArray[i].headingX = 270
                    cubeArray[i].setPos(0)
                case 4:
                    if cubeArray[i].headingX > 0:
                        cubeArray[i].headingX -= 90
                    else:
                        cubeArray[i].headingX = 270
                    cubeArray[i].setPos(7)
                case 7:
                    if cubeArray[i].headingX > 0:
                        cubeArray[i].headingX -= 90
                    else:
                        cubeArray[i].headingX = 270
                    cubeArray[i].setPos(3)


def display():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glPushMatrix()
    solved = 0
    for i in range(len(cubeArray)):
        if cubeArray[i].currentPos==cubeArray[i].pos:
            solved +=1
        cubeArray[i].drawCube()    
    glPopMatrix()
    glutSwapBuffers()
    if solved == 8 and STEPS != 0:
        print('SOLVED IN ', STEPS, 'MOVES')

glutInit()
glutInitDisplayMode(GLUT_MULTISAMPLE | GLUT_DOUBLE | GLUT_DEPTH)
glutInitWindowSize(1080, 720)
glutCreateWindow("rubik's cube".encode("ascii"))
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)
glEnable(GL_BLEND)
glEnable(GL_LINE_SMOOTH)
glEnable(GL_DEPTH_TEST)
glMatrixMode(GL_PROJECTION)
glFrustum(-1.333, 1.333, -1, 1, 5, 20) # perspective
glMatrixMode(GL_MODELVIEW)
gluLookAt(3, 4, 5, 0, 0, 0, 0, 1, 0)

#lighting
glEnable(GL_LIGHTING)
glEnable(GL_LIGHT0)
glLight(GL_LIGHT0, GL_POSITION, [-3, 4, 5])
glLight(GL_LIGHT0, GL_DIFFUSE, [0.5, 0.5, 0.5])
glLight(GL_LIGHT0, GL_AMBIENT, [0.5, 0.5, 0.5])
glLight(GL_LIGHT0, GL_SPECULAR, [1, 1, 1])
glMaterial(GL_FRONT_AND_BACK, GL_SPECULAR, [1, 1, 1])
glMaterial(GL_FRONT_AND_BACK, GL_SHININESS, 50)

#texture
img = Image.open('plastic.png') # open image
img_data = numpy.array(list(img.getdata()), numpy.int8) # convert image to array
SIZE = img.size[0]
texture = glGenTextures(1) #ID 1 for this texture
glBindTexture(GL_TEXTURE_2D, texture)
glTexParameter(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)
glTexParameter(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SIZE, SIZE, 0, GL_RGB, GL_UNSIGNED_BYTE, img_data) # uses the image (plastic)
glEnable(GL_TEXTURE_2D)
glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR)
glTexGenfv(GL_S, GL_OBJECT_PLANE, [1, 0, 0, 0])
glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR)
glTexGenfv(GL_T, GL_OBJECT_PLANE, [0, 1, 0, 0])
glEnable(GL_TEXTURE_GEN_S)
glEnable(GL_TEXTURE_GEN_T)

glutDisplayFunc(display)
glutKeyboardFunc(buttons)
glutIdleFunc(glutPostRedisplay)
glutMainLoop()