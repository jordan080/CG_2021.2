#include <GL/glut.h>
#include <math.h>
#include "bibutilNoTex.h"
#include "bibutil.h"
#include <vector>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Filtros de textura
GLint filtros[] = {
       GL_NEAREST, GL_LINEAR,
       GL_NEAREST_MIPMAP_NEAREST,GL_LINEAR_MIPMAP_NEAREST,
       GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR
};

// Define filtro inicial como GL_NEAREST_MIPMAP_LINEAR
int filtro = 4;

// Define modo inicial de aplicacao da textura
GLint modo = GL_MODULATE;

// Define modo de desenho inicial: textura
char modo_des = 't';

// Variaveis para controle da porta
#define ANGLE_DOOR_MAX 60
#define ANGLE_WINDOW_MAX 90
#define X_LIM_DOOR 10
#define Z_LIM_DOOR -10
#define XY_ONE_ANGLE 5
GLfloat x_trans_angle = 0, z_trans_angle = 0, angle_door = 0;
GLfloat x_window_angle = 0, z_window_angle = 0, angle_window = 0;

OBJnotex *paredes, *mesa, *cadeira, *cama, *porta, *telhado, *janela;

GLfloat rotX=1, rotY=-90, rotX_ini, rotY_ini;
GLfloat obsX=21.3, obsY=151.5, obsZ=-405.5, obsY_ini;
int x_ini,y_ini,bot;

// Variaveis para controle da projecao
GLfloat fAspect;
GLfloat ang_cam = 60;

void DesenhaParedes(void)
{	

	if(modo_des=='t')
		glColor3f(1,1,1);
	else
		glColor3ub(196,210,184);
	//glColor3ub(196,210,184);

	// Paredes
	glPushMatrix();
	glColor3ub(211,211,211);
	glTranslatef(0,150,-400);
	//glScalef(6,3,1);
	DesenhaObjetoNoTex(paredes);
	glPopMatrix();

	// Porta
	glPushMatrix();
	glColor3ub(0,0,255);
	glTranslatef(14.05,150,-405.6);
	//glScalef(0.098,0.098,0.098);
	glRotated(angle_door,0,1,0);
	glTranslatef(x_trans_angle,0,z_trans_angle);
	DesenhaObjetoNoTex(porta);
	glPopMatrix();

	// Janela 1
	glPushMatrix();
	glColor3ub(0,0,255);
	glTranslatef(13.8,150.95,-403.45);
	glScalef(0.65,0.58,0.65);
	glRotated(-angle_window,0,1,0);
	glTranslatef(x_window_angle,0,z_window_angle);
	DesenhaObjetoNoTex(janela);
	glPopMatrix();

	// Janela 2
	glPushMatrix();
	glColor3ub(0,0,255);
	glTranslatef(13.8,150.95,-401.65);
	glScalef(0.65,0.58,0.65);
	glRotated(-angle_window,0,1,0);
	glTranslatef(x_window_angle,0,z_window_angle);
	DesenhaObjetoNoTex(janela);
	glPopMatrix();

	// Janela 3
	glPushMatrix();
	glColor3ub(0,0,255);
	glTranslatef(13.8,150.95,-407.55);
	glScalef(0.65,0.58,0.69);
	glRotated(-angle_window,0,1,0);
	glTranslatef(x_window_angle,0,z_window_angle);
	DesenhaObjetoNoTex(janela);
	glPopMatrix();

	// Janela 4
	glPushMatrix();
	glColor3ub(0,0,255);
	glTranslatef(13.85,150.95,-409.50);
	glScalef(0.65,0.58,0.69);
	glRotated(-angle_window,0,1,0);
	glTranslatef(x_window_angle,0,z_window_angle);
	DesenhaObjetoNoTex(janela);
	glPopMatrix();

	// Mesa
	glPushMatrix();
	glColor3ub(150,75,0);
	glTranslatef(5,150.1,-409.5);
	glScalef(0.098,0.098,0.098);
	DesenhaObjetoNoTex(mesa);
	glPopMatrix();

	// Cadeira 1
	glPushMatrix();
	glTranslatef(5.1,149.7,-410.2);
	glRotatef(180,0,1,0);
	DesenhaObjetoNoTex(cadeira);
	glPopMatrix();

	// Cadeira 2
	glPushMatrix();
	glTranslatef(5.8,149.7,-409.5);
	glRotatef(90,0,1,0);
	DesenhaObjetoNoTex(cadeira);
	glPopMatrix();

	// Cadeira 3
	glPushMatrix();
	glTranslatef(4.3,149.7,-409.5);
	glRotatef(270,0,1,0);
	DesenhaObjetoNoTex(cadeira);
	glPopMatrix();

	// Cadeira 4
	glPushMatrix();
	glTranslatef(5.1,149.7,-409);
	DesenhaObjetoNoTex(cadeira);
	glPopMatrix();

	// Cama
	glPushMatrix();
	glTranslatef(-3,149.7,-401.5);
	glRotatef(180,0,1,0);
	glScalef(0.015,0.015,0.015);
	DesenhaObjetoNoTex(cama);
	glPopMatrix();

	// Cama 2
	glPushMatrix();
	glTranslatef(0.3,149.7,-401.5);
	glRotatef(180,0,1,0);
	glScalef(0.015,0.015,0.015);
	DesenhaObjetoNoTex(cama);
	glPopMatrix();
}

// Desenha toda a cena
void Desenha(void)
{
	// Limpa a janela de visualizacao com a cor
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Inicializa sistema de coordenadas do modelo
	// antes da execucao de qualquer operacao de manipulacao de matrizes
	glLoadIdentity();
	
	// Posiciona e orienta observador
	glRotatef(rotX,1,0,0);
	glRotatef(rotY,0,1,0);
	glTranslatef(-obsX,-obsY,-obsZ);

	glEnable(GL_TEXTURE_2D);

	// Desenha todos os elementos da cena
	DesenhaParedes();

	// Faz a troca dos buffers
	glutSwapBuffers();
}

// Funcao usada para especificar o volume de visualizacao
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de projecao
	glMatrixMode(GL_PROJECTION);
	
	// Inicializa sistema de coordenadas de projecao
	glLoadIdentity();

	// Especifica a projecao perspectiva
	// (angulo, aspecto, zMin, zMax)
	gluPerspective(ang_cam,fAspect,0.1,1000);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
}

// Funcao callback chamada quando o tamanho da janela e alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divisao por zero
	if ( h == 0 ) h = 1;

	// Especifica as dimensoes da viewport
	glViewport(0, 0, w, h);

	// Calcula a correcao de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}

// Funcao callback para eventos de teclado
void Teclado(unsigned char key, int x, int y)
{

	// Trata as diversas teclas
	switch(key)
	{
		case 'n':	
					if(angle_door < ANGLE_DOOR_MAX){
						angle_door = angle_door + 3.8;
						x_trans_angle = x_trans_angle + 0.045;
						z_trans_angle = z_trans_angle - 0.035;
					}
					break;
		case 'm':	
					if(angle_door > 0){
						angle_door = angle_door - 3.8;
						x_trans_angle = x_trans_angle - 0.045;
						z_trans_angle = z_trans_angle + 0.035;
					}
					break;
		case 'y':	
					if(angle_window < ANGLE_WINDOW_MAX){
						angle_window = angle_window + 3.5;
						x_window_angle = x_window_angle + 0.018;
						z_window_angle = z_window_angle + 0.035;
					}
					break;
		case 'u':	
					if(angle_window > 0){
						angle_window = angle_window - 3.5;
						x_window_angle = x_window_angle - 0.018;
						z_window_angle = z_window_angle - 0.035;
					}
					break;
	}
	// Na próxima iteração por meio de glutMainLoop essa janela será exibida novamente
	glutPostRedisplay();
}

void TecladoEspecial(int key, int x, int y)
{
	float sina, cosa, sina_01, cosa_01;

	// Pre-calcula o seno e cosseno do angulo
	// de direcao atual + 90 graus, ou seja,
	// a direcao para deslocamento lateral
	sina = 0.5*sin((rotY+90)*M_PI/180.0);
	cosa = 0.25*cos((rotY+90)*M_PI/180.0);

	// Pre-calcula o seno e cosseno do angulo
	// sem os 90 graus
	sina_01 = 0.25*sin(rotY*M_PI/180.0);
	cosa_01 = 0.25*cos(rotY*M_PI/180.0);

	// Trata as teclas especiais
	switch(key)
	{
		// Controles de deslocamento lateral
		case GLUT_KEY_LEFT:		
							obsX = obsX - sina;
							obsZ = obsZ + cosa;
							break;
		case GLUT_KEY_RIGHT:	
							obsX = obsX + sina;
							obsZ = obsZ - cosa;
							break;
		case GLUT_KEY_UP:		
							obsX = obsX + sina_01;
							obsZ = obsZ - cosa_01;
							break;

		case GLUT_KEY_DOWN:		
							obsX = obsX - sina_01;
							obsZ = obsZ + cosa_01;
							break;
	}
	glutPostRedisplay();
}

// Funcao callback para eventos de botoes do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	if(state==GLUT_DOWN)
	{
		// Atualiza as variaveis de navegação com os valores atuais
		x_ini = x;
		y_ini = y;
		obsY_ini = obsY;
		rotX_ini = rotX;
		rotY_ini = rotY;
		bot = button;
	}
	else bot = -1;
}

// Funcao callback para eventos de movimento do mouse
#define SENS_ROT	5.0
#define SENS_OBS	10.0

void GerenciaMovim(int x, int y)
{
	// Botao esquerdo ?
	if(bot==GLUT_LEFT_BUTTON)
	{
		// Calcula diferencas
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		// E modifica angulos
		rotY = rotY_ini - deltax/SENS_ROT;
		rotX = rotX_ini - deltay/SENS_ROT;
	}
	// Botao direito ?
	else if(bot==GLUT_RIGHT_BUTTON)
	{
		// Calcula diferenca
		int deltay = y_ini - y;
		// E modifica altura do observador
		obsY = obsY_ini + deltay/SENS_OBS;
	}
	glutPostRedisplay();
}

// Funcao responsavel por inicializar parametros e variaveis
void Inicializa(void)
{
	// Define a cor de fundo da janela de visualizacao como preto
	glClearColor(0,0,0,1);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, modo);

	// Define coeficientes ambiente e difuso
	// do material
	GLfloat matAmb[4] = { 0.2,0.2,0.2,1 };
	GLfloat matDif[4] = { 1,1,1,1 };

	// Material
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,matAmb);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,matDif);

	// Seleciona o modo de GL_COLOR_MATERIAL
	// faz com que uma cor de material acompanhe a cor atual
	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	
	// Habilita normalizacao automatica
	// Vetores normais sao normalizados para valores unitarios
	// apos transformacao e antes da iluminacao
	glEnable(GL_NORMALIZE);

	// Habilita Z-Buffer
	// Realiza comparacoes de profundidade
	// e atualiza o buffer de profundidade
	glEnable(GL_DEPTH_TEST);

	// Carrega objetos
	paredes = CarregaObjetoNoTex("obj/paredes.obj", false);
	mesa = CarregaObjetoNoTex("obj/mesa.obj", false);
	cadeira = CarregaObjetoNoTex("obj/cadeira.obj", false);
	cama = CarregaObjetoNoTex("obj/cama.obj", false);
	porta = CarregaObjetoNoTex("obj/porta.obj", false);
	janela = CarregaObjetoNoTex("obj/porta.obj", false);
}

// Programa Principal
int main(int argc, char** argv)
{
	// Inicilizar a Glut
	glutInit(&argc, argv);

	// Define o modo de operacao da GLUT
	// GLUT_DOUBLE : dois buffers de cor
	// GLUT_RGB : define que as cores do programa serão especificadas por componentes GLUT_RGB
	// GLUT_DEPTH : buffer de profundidade
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

	// Especifica a posicao e o tamanho inicial em pixels da janela GLUT
	glutInitWindowPosition(150,50);
	glutInitWindowSize(800,600);

	// Cria a janela passando como argumento o titulo da mesma
	glutCreateWindow("Casa");

	// Registra a funcao callback de redesenho da janela de visualizacao
	glutDisplayFunc(Desenha);

	// Registra a funcao callback de teclado
	glutKeyboardFunc(Teclado);

	// Registra a funcao callback de teclas especiais
	glutSpecialFunc(TecladoEspecial);

	// Registra a funcao callback para eventos de botoes do mouse
	glutMouseFunc(GerenciaMouse);

	// Registra a funcao callback para eventos de movimento do mouse
	glutMotionFunc(GerenciaMovim);

	// Registra a funcao callback de redimensionamento da janela de visualizacao
	glutReshapeFunc(AlteraTamanhoJanela);

	// Chama a funcao responsavel por fazer as inicializacoes
	Inicializa();

    glutMainLoop();
}