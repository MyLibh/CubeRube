#include "CubeRube.h"

#define CUBE_SZ 14
#define TIMER 30

struct Settings
    {
    unsigned int color[9] ;

    int xrot,
         yrot,
         zrot;

    double scale;

    bool timer, xd, yd, zd;

    float light_pos[4] ;
    } s = {{0xFFFFFF, 0xFFFF00, 0x0000FF, 0x00FF00, 0xFF0000, 0xCD853F}, 25, 45, 0, -45.0, false, false, false, false, {0, 100, 200, 0}};

CubeRube3x3 Cube;

void display();
void mouse(int key, int state, int, int);
void timer(int time);
void reshape(int width, int height);
void keys(unsigned char key, int, int);
void ypr(int key, int, int);
void Init();

//Написать текст для вращение(кнопки)

int main(int argc, char* argv[])
    {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("CubeRube");
    //glutFullScreen();

    Init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keys);
    glutMouseFunc(mouse);
    glutSpecialFunc(ypr);
    glutTimerFunc(TIMER, timer, 0);

    glutMainLoop();

    return 0;
    }

void display()
    {
    glPushMatrix();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

    glLightfv(GL_LIGHT0, GL_POSITION, s.light_pos);
    glTranslatef(0, 0, s.scale);
    glRotatef(s.xrot, 1, 0, 0);
    glRotatef(s.yrot, 0, 1, 0);
    glRotatef(s.zrot, 0, 0, 1);
    glTranslatef(CUBE_SZ/-2, CUBE_SZ/-2, CUBE_SZ/-2);
    Cube.Draw();

    if((s.xrot - 25)%90 != 0) (s.xd)? s.xrot++ : s.xrot--;
    if((s.yrot - 45)%90  != 0) (s.yd)? s.yrot++ : s.yrot--;
    if((s.zrot -   0)%90  != 0) (s.zd)? s.zrot++ : s.zrot--;

    glPopMatrix();
    glutSwapBuffers();
    }

void Init()
    {
    glClearColor(1.0, 1.0, 0.5, 0.0);
    srand(time(NULL));

    float specular[] = {0.3, 0.3, 0.3, 0};
    float diffuse[]  = {0.2, 0.2, 0.2, 1};
    float ambient[]  = {0.9, 0.9, 0.9, 1};

    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMateriali(GL_FRONT, GL_SHININESS, 128);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    switch(Cube.type)
        {
        case 2: s.scale = -25.0; break;
        case 3: s.scale = -35.0; break;
        case 4: s.scale = -45.0; break;
        case 5: s.scale = -55.0; break;

        default :                      break;
        }

    Cube.Clear(CUBE_SZ, s.color);
    }

void mouse(int key, int state, int, int)
    {
    if(key == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) s.timer = !s.timer;
    }

void timer(int)
    {
    glutTimerFunc(TIMER, timer, 0);

    if(s.timer)
        {
		if(Cube.act_face == -1) keys(rand()%6 + '0', 0, 0);
		else Cube.Rotate(Cube.act_face, 3);
        }
	else if(Cube.act_face != -1) Cube.Rotate(Cube.act_face, 3);

	display();
    }

void keys(unsigned char key, int, int)
    {
    if(Cube.act_face == -1)
        {
        if(Cube.type == 2)                           if(key >= '0' && key <   '6') Cube.Rotate(key - '0', 3);
        if(Cube.type == 3)                           if(key >= '0' && key <   '9') Cube.Rotate(key - '0', 3);
        if(Cube.type != 2 && Cube.type != 3) if(key >= '0' && key <= '9') Cube.Rotate(key - '0', 3);

        display();
        }
    }

void reshape(int width, int height)
    {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)width/(float)height, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    }

void ypr(int key, int, int)
    {
    switch(key)
        {
        case GLUT_KEY_DOWN:
        s.xrot += 4;
        s.xd = true;
        if(s.xrot >= 360) s.xrot -= 360;
        glutPostRedisplay();
        break;

        case GLUT_KEY_UP:
        s.xrot -= 4;
        s.xd = false;
        if(s.xrot < 0) s.xrot += 360;
        glutPostRedisplay();
        break;

        case GLUT_KEY_LEFT:
        s.yrot -= 4;
        s.yd = false;
        if(s.yrot < 0) s.yrot += 360;
        glutPostRedisplay();
        break;

        case GLUT_KEY_RIGHT:
        s.yrot += 4;
        s.yd = true;
        if(s.yrot >= 360) s.yrot -= 360, s.yd = false;
        glutPostRedisplay();
        break;

        case GLUT_KEY_END:
        s.zrot += 4;
        s.zd = true;
        if(s.zrot >= 360) s.zrot -= 360;
        glutPostRedisplay();
        break;

        case GLUT_KEY_HOME:
        s.zrot -= 4;
        s.zd = false;
        if(s.zrot < 0) s.zrot += 360;
        glutPostRedisplay();
        break;

        case GLUT_KEY_F2:
        s.scale += 5;
        break;

        case GLUT_KEY_F3:
        s.scale -= 5;
        break;

        case GLUT_KEY_F1:
        s.xrot = 25;
        s.yrot = 45;
        s.zrot =  0;
        Cube.Clear(CUBE_SZ, s.color);
        glutPostRedisplay();
        break;

        case 65: printf("%d %d %d\n", s.xrot, s.yrot, s.zrot); break;
        case 27: abort(); break;

        default: break;
        }
    }

