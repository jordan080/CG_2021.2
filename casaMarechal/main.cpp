#include <GL/glut.h>
#include <math.h>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "utils.h"

// Variaveis para controle da porta
#define ANGLE_DOOR_MAX 60
#define ANGLE_WINDOW_MAX 90
#define X_LIM_DOOR 10
#define Z_LIM_DOOR -10
#define XY_ONE_ANGLE 5
GLfloat x_trans_angle = 0, z_trans_angle = 0, angle_door = 0;
GLfloat x_window_angle = 0, z_window_angle = 0, angle_window = 0;

OBJnotex *paredes, *mesa, *cadeira, *cama, *porta, *telhado, *janela, *lampada, *lampada_parede;

// Luminosidade base de uma lampada
#define LOW	0.3

// Define parametros de iluminacao
// Luz 1
GLfloat luzAmb1[4] = {0.01, 0.01, 0.01, 1.0};	// luz ambiente
GLfloat luzDif1[4] = {LOW, LOW, LOW, 1.0};		// luz difusa
GLfloat luzEsp1[4] = {0.01, 0.01, 0.01, 1.0};	// luz especular
GLfloat posLuz1[4] = {6.8, 153.3, -402, 1.0};	// posicao da fonte de luz

// Luz 2
GLfloat luzDif2[4] = {LOW, LOW, LOW, 1.0};	// luz difusa
GLfloat posLuz2[4] = {6.8, 153.3, -405, 1};	// posicao da fonte de luz

// Luz 3
GLfloat luzDif3[4] = {LOW, LOW, LOW, 1.0};	// luz difusa
GLfloat posLuz3[4] = {6.8, 153.3, -408, 1};	// posicao da fonte de luz

// Luz 4
GLfloat luzDif4[4] = {LOW, LOW, LOW, 1.0};	// luz difusa
GLfloat posLuz4[4] = {-4, 153.3, -408, 1};	// direcao da fonte de luz

// Luz 5
GLfloat luzDif5[4] = {LOW, LOW, LOW, 1.0};	// luz difusa
GLfloat posLuz5[4] = {-4, 153.3, -405, 1};	// direcao da fonte de luz

// Luz 6
GLfloat luzDif6[4] = {LOW, LOW, LOW, 1.0};	// luz difusa
GLfloat posLuz6[4] = {-4, 153.3, -402, 1};	// direcao da fonte de luz

bool luzes[6] = {true, true, true, true, true, true};

GLfloat rotX=1, rotY=-90, rotX_ini, rotY_ini;
GLfloat obsX=21.3, obsY=151.5, obsZ=-405.5, obsY_ini;
int x_ini,y_ini,bot;

// Variaveis para controle da projecao
GLfloat fAspect;
GLfloat ang_cam = 60;

void CriaObjetos(void)
{	
	// Paredes
	glPushMatrix();
	glColor3ub(211,211,211);
	glTranslatef(0,150,-400);
	DesenhaObjeto(paredes);
	glPopMatrix();

	//Lampada 1
	glPushMatrix();
	glTranslatef(11.8,153.42,-402);
	glScalef(0.01,0.01,0.01);
	glRotated(90,1,0,0);
	glRotated(-5,0,1,0);
	DesenhaObjeto(lampada);
	glPopMatrix();

	//Lampada 2
	glPushMatrix();
	glTranslatef(11.8,153.42,-405);
	glScalef(0.01,0.01,0.01);
	glRotated(90,1,0,0);
	glRotated(-5,0,1,0);
	DesenhaObjeto(lampada);
	glPopMatrix();

	//Lampada 3
	glPushMatrix();
	glTranslatef(11.8,153.42,-408);
	glScalef(0.01,0.01,0.01);
	glRotated(90,1,0,0);
	glRotated(-5,0,1,0);
	DesenhaObjeto(lampada);
	glPopMatrix();

	//Lampada 4
	glPushMatrix();
	glTranslatef(-5.8,153.65,-408);
	glScalef(0.01,0.01,0.01);
	glRotated(90,1,0,0);
	glRotated(5,0,1,0);
	DesenhaObjeto(lampada);
	glPopMatrix();

	//Lampada 5
	glPushMatrix();
	glTranslatef(-5.8,153.65,-405);
	glScalef(0.01,0.01,0.01);
	glRotated(90,1,0,0);
	glRotated(5,0,1,0);
	DesenhaObjeto(lampada);
	glPopMatrix();

	//Lampada 6
	glPushMatrix();
	glTranslatef(-5.8,153.65,-402);
	glScalef(0.01,0.01,0.01);
	glRotated(90,1,0,0);
	glRotated(5,0,1,0);
	DesenhaObjeto(lampada);
	glPopMatrix();

	// Porta
	glPushMatrix();
	glColor3ub(0,0,255);
	glTranslatef(14.05,150,-405.6);
	glRotated(angle_door,0,1,0);
	glTranslatef(x_trans_angle,0,z_trans_angle);
	DesenhaObjeto(porta);
	glPopMatrix();

	// Janela 1
	glPushMatrix();
	glColor3ub(0,0,255);
	glTranslatef(13.8,150.95,-403.45);
	glScalef(0.65,0.58,0.65);
	glRotated(-angle_window,0,1,0);
	glTranslatef(x_window_angle,0,z_window_angle);
	DesenhaObjeto(janela);
	glPopMatrix();

	// Janela 2
	glPushMatrix();
	glColor3ub(0,0,255);
	glTranslatef(13.8,150.95,-401.65);
	glScalef(0.65,0.58,0.65);
	glRotated(-angle_window,0,1,0);
	glTranslatef(x_window_angle,0,z_window_angle);
	DesenhaObjeto(janela);
	glPopMatrix();

	// Janela 3
	glPushMatrix();
	glColor3ub(0,0,255);
	glTranslatef(13.8,150.95,-407.55);
	glScalef(0.65,0.58,0.69);
	glRotated(-angle_window,0,1,0);
	glTranslatef(x_window_angle,0,z_window_angle);
	DesenhaObjeto(janela);
	glPopMatrix();

	// Janela 4
	glPushMatrix();
	glColor3ub(0,0,255);
	glTranslatef(13.85,150.95,-409.50);
	glScalef(0.65,0.58,0.69);
	glRotated(-angle_window,0,1,0);
	glTranslatef(x_window_angle,0,z_window_angle);
	DesenhaObjeto(janela);
	glPopMatrix();

	// Mesa
	glPushMatrix();
	glColor3ub(150,75,0);
	glTranslatef(5,150.1,-409.5);
	glScalef(0.098,0.098,0.098);
	DesenhaObjeto(mesa);
	glPopMatrix();

	// Cadeira 1
	glPushMatrix();
	glTranslatef(5.1,149.7,-410.2);
	glRotatef(180,0,1,0);
	DesenhaObjeto(cadeira);
	glPopMatrix();

	// Cadeira 2
	glPushMatrix();
	glTranslatef(5.8,149.7,-409.5);
	glRotatef(90,0,1,0);
	DesenhaObjeto(cadeira);
	glPopMatrix();

	// Cadeira 3
	glPushMatrix();
	glTranslatef(4.3,149.7,-409.5);
	glRotatef(270,0,1,0);
	DesenhaObjeto(cadeira);
	glPopMatrix();

	// Cadeira 4
	glPushMatrix();
	glTranslatef(5.1,149.7,-409);
	DesenhaObjeto(cadeira);
	glPopMatrix();

	// Cama
	glPushMatrix();
	glTranslatef(-3,149.7,-401.5);
	glRotatef(180,0,1,0);
	glScalef(0.015,0.015,0.015);
	DesenhaObjeto(cama);
	glPopMatrix();

	// Cama 2
	glPushMatrix();
	glTranslatef(0.3,149.7,-401.5);
	glRotatef(180,0,1,0);
	glScalef(0.015,0.015,0.015);
	DesenhaObjeto(cama);
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

	// Agora posiciona a fonte de luz do meio da sala
	// Agora posiciona demais fontes de luz
	glLightfv(GL_LIGHT0, GL_POSITION, posLuz1);
	glLightfv(GL_LIGHT1, GL_POSITION, posLuz2);
	glLightfv(GL_LIGHT2, GL_POSITION, posLuz3);
	glLightfv(GL_LIGHT3, GL_POSITION, posLuz4);
	glLightfv(GL_LIGHT4, GL_POSITION, posLuz5);
	glLightfv(GL_LIGHT5, GL_POSITION, posLuz6);

	// Desenha todos os elementos da cena
	CriaObjetos();

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

void SetaLuzes()
{
	for(int luz=0;luz<6;++luz)
	{
		if(luzes[luz]) glEnable(GL_LIGHT0+luz);
		else glDisable(GL_LIGHT0+luz);
	}
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
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
					luzes[key-'1'] = !luzes[key-'1'];
					SetaLuzes();
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
	cosa = 0.20*cos((rotY+90)*M_PI/180.0);

	// Pre-calcula o seno e cosseno do angulo
	// sem os 90 graus
	sina_01 = 0.20*sin(rotY*M_PI/180.0);
	cosa_01 = 0.20*cos(rotY*M_PI/180.0);

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
	// Botao esquerdo 
	if(bot==GLUT_LEFT_BUTTON)
	{
		// Calcula diferencas
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		// E modifica angulos
		rotY = rotY_ini - deltax/SENS_ROT;
		rotX = rotX_ini - deltay/SENS_ROT;
	}
	// Botao direito 
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

	// Ajusta iluminacao
	glLightfv( GL_LIGHT0, GL_AMBIENT,  luzAmb1 );
	glLightfv( GL_LIGHT0, GL_DIFFUSE,  luzDif1 );
	glLightfv( GL_LIGHT0, GL_SPECULAR, luzEsp1 );

	glLightfv( GL_LIGHT1, GL_AMBIENT,  luzAmb1 );
	glLightfv( GL_LIGHT1, GL_DIFFUSE,  luzDif2 );

	glLightfv( GL_LIGHT2, GL_AMBIENT,  luzAmb1 );
	glLightfv( GL_LIGHT2, GL_DIFFUSE,  luzDif3 );

	glLightfv( GL_LIGHT3, GL_AMBIENT,  luzAmb1 );
	glLightfv( GL_LIGHT3, GL_DIFFUSE,  luzDif4 );

	glLightfv( GL_LIGHT4, GL_AMBIENT,  luzAmb1 );
	glLightfv( GL_LIGHT4, GL_DIFFUSE,  luzDif5 );

	glLightfv( GL_LIGHT5, GL_AMBIENT,  luzAmb1 );
	glLightfv( GL_LIGHT5, GL_DIFFUSE,  luzDif6 );
	
	// Habilita todas as fontes de luz
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT4);
	glEnable(GL_LIGHT5);
	glEnable(GL_LIGHTING);

	// Define coeficientes ambiente e difuso
	// do material
	GLfloat matAmb[4] = { 0.15,0.15,0.15,1 };
	GLfloat matDif[4] = { 0.5,0.5,0.5,0.5 };

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
	paredes = CarregaObjeto("obj/paredes3.obj", false);
	mesa = CarregaObjeto("obj/mesa.obj", false);
	cadeira = CarregaObjeto("obj/cadeira.obj", false);
	cama = CarregaObjeto("obj/cama.obj", false);
	porta = CarregaObjeto("obj/porta.obj", false);
	janela = CarregaObjeto("obj/porta.obj", false);
	lampada = CarregaObjeto("obj/lampada.obj", false);
	//lampada_parede = CarregaObjeto("obj/lampada_parede.obj", false);
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