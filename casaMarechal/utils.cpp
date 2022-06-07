#include <math.h>
#include <string.h>
#include <vector>
#include "utils.h"

#define DEBUG

using namespace std;

vector<OBJnotex*> _objetos(0);
vector<MATnotex*> _materiais(0);

char _modoNoTex = 't';

int leNumNoTex(char **face, char *sep)
{
	char temp[10];
	int pos = 0;
	while(**face)
	{
		if(**face == '/' || **face==' ') 
		{
			*sep = **face;
			(*face)++;
			break;
		}
		temp[pos++] = **face;
		(*face)++;
	}
	temp[pos]=0;
	if(!pos) 
		return -1;
	return atoi(temp);
}

OBJnotex *CarregaObjeto(char *nomeArquivo, bool mipmap)
{	
	
	int i;
	int vcont,ncont,fcont,tcont;
	int material;
	char aux[256];
	TEXnotex *ptr;
	FILE *fp;
	OBJnotex *obj;

	fp = fopen(nomeArquivo, "r");  

	if(fp == NULL){
          return NULL;
	}

	if ( ( obj = (OBJnotex *) malloc(sizeof(OBJnotex)) ) == NULL){
		return NULL;
	}

	obj->numVertices  = 0;
	obj->numFaces     = 0;
	obj->numNormais   = 0;
	obj->numTexcoords = 0;
	obj->normais_por_vertice = false;
	obj->tem_materiais = false;
	obj->dlist = -1;	

	obj->vertices = NULL;
	obj->faces = NULL;
	obj->normais = NULL;
	obj->texcoords = NULL;

	while(!feof(fp))
	{
		fgets(aux,255,fp);
		if(!strncmp(aux,"v ",2)) 
			obj->numVertices++;
		if(!strncmp(aux,"f ",2))
			obj->numFaces++;
		if(!strncmp(aux,"vn ",3)) 
			obj->numNormais++;
		if(!strncmp(aux,"vt ",3)) 
			obj->numTexcoords++;
	}

	rewind(fp);

	
	if ( ( obj->vertices = (VERTnotex *) malloc((sizeof(VERTnotex)) * obj->numVertices) ) == NULL ){
		return NULL;
	}


	if ( ( obj->faces = (FACEnotex *) malloc((sizeof(FACEnotex)) * obj->numFaces) ) == NULL ){
		return NULL;
	}


	if(obj->numNormais){
		if ( ( obj->normais = (VERTnotex *) malloc((sizeof(VERTnotex)) * obj->numNormais) ) == NULL )
			return NULL;
	}

	if(obj->numTexcoords){
		if ( ( obj->texcoords = (TEXCOORDnotex *) malloc((sizeof(TEXCOORDnotex)) * obj->numTexcoords) ) == NULL )
			return NULL;
	}


	vcont = 0;
	ncont = 0;
	tcont = 0;
	fcont = 0;
	material = -1;

	
	float minx,miny,minz;
	float maxx,maxy,maxz;


	while(!feof(fp))
	{
		fgets(aux,255,fp);
		aux[strlen(aux)-1]=0;	

		if(aux[0]=='#') continue;

		if(!strncmp(aux,"v ",2))
		{
			sscanf(aux,"v %f %f %f",&obj->vertices[vcont].x,
					&obj->vertices[vcont].y,
					&obj->vertices[vcont].z);
			if(!vcont)
			{
				minx = maxx = obj->vertices[vcont].x;
				miny = maxy = obj->vertices[vcont].y;
				minz = maxz = obj->vertices[vcont].z;
			}
			else
			{
				if(obj->vertices[vcont].x < minx) minx = obj->vertices[vcont].x;
				if(obj->vertices[vcont].y < miny) miny = obj->vertices[vcont].y;
				if(obj->vertices[vcont].z < minz) minz = obj->vertices[vcont].z;
				if(obj->vertices[vcont].x > maxx) maxx = obj->vertices[vcont].x;
				if(obj->vertices[vcont].y > maxy) maxy = obj->vertices[vcont].y;
				if(obj->vertices[vcont].z > maxz) maxz = obj->vertices[vcont].z;
			}
			vcont++;
		}
		if(!strncmp(aux,"vn ",3))
		{
			sscanf(aux,"vn %f %f %f",&obj->normais[ncont].x,
					&obj->normais[ncont].y,
					&obj->normais[ncont].z);
			ncont++;

			obj->normais_por_vertice = true;
		}

		if(!strncmp(aux,"vt ",3))
		{
			sscanf(aux,"vt %f %f %f",&obj->texcoords[tcont].s,
					&obj->texcoords[tcont].t,
					&obj->texcoords[tcont].r);
			tcont++;
		}
		if(!strncmp(aux,"f ",2))
		{
			char *ptr = aux+2;

			obj->faces[fcont].mat = material;

			int vi[10],ti[10],ni[10];
			char sep;
			obj->faces[fcont].nv = 0;
			int nv = 0;
			bool tem_t = false;
			bool tem_n = false;
			while(*ptr)
			{
				vi[nv] = leNumNoTex(&ptr,&sep);
				if(sep==' ')
				{
					nv++;
					continue;
				}
				int aux = leNumNoTex(&ptr,&sep);
				if(aux!=-1)
				{
					ti[nv] = aux;
					tem_t = true;
				}
				if(sep==' ')
				{
					nv++;
					continue;
				}
				aux = leNumNoTex(&ptr,&sep);
				if(aux!=-1)
				{
					ni[nv] = aux;
					tem_n = true;
				}
				nv++;
			}

			obj->faces[fcont].nv = nv;
			obj->faces[fcont].vert = (int *) malloc(sizeof(int)*nv);
			if(tem_n) obj->faces[fcont].norm = (int *) malloc(sizeof(int)*nv);
				else obj->faces[fcont].norm = NULL;
			for(i=0;i<nv;++i)
			{

				obj->faces[fcont].vert[i] = vi[i]-1;
				if(tem_n) obj->faces[fcont].norm[i] = ni[i]-1;
			}
			fcont++;
		}
	}

	fclose(fp);
	_objetos.push_back(obj);
	return obj;
}

void DesenhaObjeto(OBJnotex *obj)
{	
	
	int i;	
	GLenum prim = GL_POLYGON;	

	GLfloat branco[4] = { 1.0, 1.0, 1.0, 1.0 };	
	
	
	if(obj->dlist >= 1000){
		
		glNewList(obj->dlist-1000,GL_COMPILE_AND_EXECUTE);
	}	
	else if(obj->dlist > -1)
	{
		glCallList(obj->dlist);
		return;
	}

	
	
	if(_modoNoTex=='w') prim = GL_LINE_LOOP;

	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_TEXTURE_2D);

	if(obj->tem_materiais)
		glDisable(GL_COLOR_MATERIAL);

	
	
	for(i=0; i<obj->numFaces; i++)
	{
		
		if(!obj->normais_por_vertice)
			glNormal3f(obj->normais[i].x,obj->normais[i].y,obj->normais[i].z);

		
		if(obj->faces[i].mat != -1)
		{
			
			int mat = obj->faces[i].mat;
			glMaterialfv(GL_FRONT,GL_AMBIENT,_materiais[mat]->ka);
			

				glMaterialfv(GL_FRONT,GL_DIFFUSE,_materiais[mat]->kd);
			glMaterialfv(GL_FRONT,GL_SPECULAR,_materiais[mat]->ks);
			glMaterialfv(GL_FRONT,GL_EMISSION,_materiais[mat]->ke);
			glMaterialf(GL_FRONT,GL_SHININESS,_materiais[mat]->spec);
		}
		

		glBegin(prim);

		for(int vf=0; vf<obj->faces[i].nv;++vf)
		{

			if(obj->normais_por_vertice)
				glNormal3f(obj->normais[obj->faces[i].norm[vf]].x,
				obj->normais[obj->faces[i].norm[vf]].y,
				obj->normais[obj->faces[i].norm[vf]].z);


			glVertex3f(obj->vertices[obj->faces[i].vert[vf]].x,
		    	obj->vertices[obj->faces[i].vert[vf]].y,
			obj->vertices[obj->faces[i].vert[vf]].z);
		}

		glEnd();

	} 
	
	glDisable(GL_TEXTURE_2D);

	glPopAttrib();

	if(obj->dlist >= 1000)
	{
		glEndList();

		obj->dlist-=1000;
	}
}