#ifndef __BIBUTILNOTEX_H
#define __BIBUTILNOTEX_H
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#ifndef M_PI
#define M_PI 3.1415926
#endif

typedef struct
{
	char nome[50];			
	int ncomp;				
	GLint dimx;				
	GLint dimy;				
	GLuint texid;			
	unsigned char *data;	
} TEXnotex;

typedef struct {
	GLfloat x,y,z;
} VERTnotex;

typedef struct {
	GLint nv;		
	GLint *vert;	
	GLint *norm;	
	GLint *tex;		
	GLint mat;		
	GLint texid;	
} FACEnotex;

typedef struct {
	GLfloat s,t,r;
} TEXCOORDnotex;

typedef struct {
	GLint numVertices;
	GLint numFaces;
	GLint numNormais;
	GLint numTexcoords;
	bool normais_por_vertice;	
	bool tem_materiais;			
	GLint textura;				
	GLint dlist;				
	VERTnotex *vertices;
	VERTnotex *normais;
	FACEnotex *faces;
	TEXCOORDnotex *texcoords;
} OBJnotex;

// Define um material
typedef struct {
	char nome[20];	
	GLfloat ka[4];	
	GLfloat kd[4];	
	GLfloat ks[4];	
	GLfloat ke[4];	
	GLfloat spec;	
} MATnotex;

OBJnotex *CarregaObjetoNoTex(char *nomeArquivo, bool mipmap);
void DesenhaObjetoNoTex(OBJnotex *obj);

#ifndef GL_ARB_texture_cube_map
# define GL_NORMAL_MAP					0x8511
# define GL_REFLECTION_MAP				0x8512
# define GL_TEXTURE_CUBE_MAP			0x8513
# define GL_TEXTURE_BINDING_CUBE_MAP	0x8514
# define GL_TEXTURE_CUBE_MAP_POSITIVE_X	0x8515
# define GL_TEXTURE_CUBE_MAP_NEGATIVE_X	0x8516
# define GL_TEXTURE_CUBE_MAP_POSITIVE_Y	0x8517
# define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y	0x8518
# define GL_TEXTURE_CUBE_MAP_POSITIVE_Z	0x8519
# define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z	0x851A
# define GL_PROXY_TEXTURE_CUBE_MAP		0x851B
# define GL_MAX_CUBE_MAP_TEXTURE_SIZE	0x851C
#endif

#endif
