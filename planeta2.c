#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

float fov_y;
float cam_x, cam_y, cam_z;
float center_x, center_y, center_z;
float anguloP = 0, anguloP2 = 10, anguloL = 0, anguloL2 = 10;
int t_refresh = 80;

float x=0, y=0, z=1;

static GLfloat angle = 2, fAspect;

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Define a posição da camera
    gluLookAt(cam_x, cam_y, cam_z, center_x, center_y, center_z, 0.0f, 1.0f, 0.0f);

 
    //Sol
    glTranslatef(0.0f, 0.0f, -100.0f);
    glColor3f(255, 255, 0);
    glutSolidSphere(30.0f, 15, 15);

    //planeta vermelho
    glPushMatrix();
        glRotatef(anguloP, 0.0f, 1.0f, 0.0f);
        glTranslatef(-50.0f, 0.0f, 0.0f);
        glColor3f(1, 0, 0);
        glutSolidSphere(3.0f, 15, 15);
    glPopMatrix();

    // planeta verde
    glRotatef(anguloP2, 0.0f, 1.0f, 0.0f);
    glTranslatef(85.0f, 0.0f, 0.0f);
    glColor3f(0, 1, 0);
    glutSolidSphere(6.0f, 15, 15);

    // lua azul claro
    glPushMatrix();
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        glRotatef(anguloL, 1.0f, 0.0f, 0.0f);
        glTranslatef(0.0f, 20.0f, 0.0f);
        glColor3f(1, 1, 1);
        glutSolidSphere(2.8f, 15, 15);
    glPopMatrix();

    //lua branca
    glPushMatrix();
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        glRotatef(anguloL2, 0.0f, 1.0f, 0.0f);
        glTranslatef(-20.0f, 0.0f, 0.0f);
        glColor3f(0, 1, 1);
        glutSolidSphere(2.8f, 15, 15);
    glPopMatrix();

    anguloP += 2.0f;
    if(anguloP > 360.0f)
        anguloP = 0.0f;

    anguloL += 10.0f;
    if(anguloL > 360.0f)
        anguloL = 0.0f;

    glutSwapBuffers();
}

void timer(int value)
{
    glutPostRedisplay();

    anguloP += 2.0f;
    if(anguloP > 360.0f)
        anguloP = 0.0f;

    anguloP2 += 1.0f;
    if(anguloP2 > 360.0f)
        anguloP2 = 0.0f;

    anguloL += 9.0f;
    if(anguloL > 360.0f)
        anguloL = 0.0f;

    anguloL2 += 5.0f;
    if(anguloL2 > 360.0f)
        anguloL2 = 0.0f;

    glutTimerFunc(t_refresh, timer, 0);
}

void GerenciaTeclado(unsigned char key, int x, int y)
{
    if (key == 'y')
    {
        glutTimerFunc(0, timer, 0);
    }
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    // Inicializacao
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(250,50);
    glutCreateWindow("OpenGL");
    
    // Registra o callback de renderizacao (por enquanto nao faz nada)
    glutDisplayFunc(display);

    fov_y = 100.0f;
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov_y, 1.0f * WINDOW_WIDTH / WINDOW_HEIGHT, 0.001f, 1000.0f);
	
    //Gerencia a tecla
	glutKeyboardFunc(GerenciaTeclado);
	glEnable(GL_DEPTH_TEST);
    
    //Variaveis de posição da camera
    cam_y = 30.0f;
	cam_z = 30.0f; 
    center_y = 30.0f;
    center_z = -5.0f; 
		
    // Inicia o loop de eventos da GLUT
    glutMainLoop();
    
    return 0;
}