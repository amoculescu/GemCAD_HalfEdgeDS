#define RADPERDEG 0.0174533

#include "HalfEdgeDSRendering.h"

#include <GL/glut.h>

Vec3f colorRed(1.0f, 0.0f, 0.0f);
Vec3f colorGreen(0.0f, 1.0f, 0.0f);
Vec3f colorBlue(0.0f, 0.0f, 1.0f);
Vec3f colorWhite(1.0f, 1.0f, 1.0f);
Vec3f colorTeal(0.0f, 1.0f, 0.92f);

void renderDS(const HalfEdgeDS& heDS)
{
    for (auto const *v : heDS.getVertices()) renderV(v, colorRed); // render all vertices as points
    for (auto const *e : heDS.getEdges()) renderE(e, colorTeal); // render all edges as lines
    //for (auto const *he : heDS.getHalfEdges()) renderHE(he, colorGreen);
    //for (auto const *l : heDS.getLoops()) renderHE(l, colorGreen); // render all halfedges as lines
}

void renderE(const Edge* e, const Vec3f& color)
{
    glBegin(GL_LINES);
    glColor3fv(&color.x);
    glVertex3fv(&e->he1->startV->coordinates.x);
    glVertex3fv(&e->he2->startV->coordinates.x);
    glEnd();
}

void renderHE(const HalfEdge* he, const Vec3f& color)
{
    /*glColor3fv(&color.x);
    Vertex* pa[4];
    HalfEdge* temp = new HalfEdge;
    temp = l->toHE->nextHE;
    for(int i = 0; i < 4; i++)
    {
        pa[i] = temp->startV;
        temp = temp->nextHE;
    }
    glPushMatrix();
    //glTranslatef(-(pa[0]->coordinates.x), -(pa[0]->coordinates.y), -(pa[0]->coordinates.z));
    glScalef(0.5, 0.5, 0.5);
    for(int i = 0; i < 4; i++)
    {
        if(i != 3)
        {
            renderArrow(pa[i]->coordinates, pa[i + 1]->coordinates, 0.02);
        }
        else
        {
            renderArrow(pa[i]->coordinates, pa[0]->coordinates, 0.02);
        }
    }
    //glTranslatef((pa[0]->coordinates.x * 1,5), (pa[0]->coordinates.y * 1.5), (pa[0]->coordinates.z* 1.5));
    glPopMatrix();
    Vec3f p2;
    if(he == he->toEdge->he1)
    {
        p2 = he->toEdge->he2->startV->coordinates;
    }
    else
    {
        p2 = he->toEdge->he1->startV->coordinates;
    }*/

    renderArrow(he->startV->coordinates, he->nextHE->startV->coordinates, 0.06);
}

void renderV(const Vertex* v, const Vec3f& color)
{
    glBegin(GL_POINTS);
    glColor3fv(&color.x);
    glVertex3fv(&v->coordinates.x);
    glEnd();
}


void renderHEActive(const HalfEdge* he)
{
    glColor3fv(&colorWhite.x);
    renderArrow(he->startV->coordinates, he->nextHE->startV->coordinates, 0.04);
	// TODO: render the currently selected half-edge.
	// use renderArrow method to visualize the direction of the half-edge
}

void renderArrow(const Vec3f& p1, const Vec3f& p2, float diameter)
{
	Vec3f dir = p2 - p1;
	float length = dir.length();
	if (length < 0.00001f) return;

	GLUquadricObj *quadObj;

	glPushMatrix ();

	glTranslated(p1.x, p1.y, p1.z);

	if((dir.x!=0.)||(dir.y!=0.)) {
		glRotated(atan2(dir.y,dir.x)/RADPERDEG,0.,0.,1.);
		glRotated(atan2(sqrt(dir.x*dir.x+dir.y*dir.y),dir.z)/RADPERDEG,0.,1.,0.);
	} else if (dir.z<0){
		glRotated(180,1.,0.,0.);
	}

	glTranslatef(0,0,length-4*diameter);

	quadObj = gluNewQuadric ();
	gluQuadricDrawStyle (quadObj, GLU_FILL);
	gluQuadricNormals (quadObj, GLU_SMOOTH);
	gluCylinder(quadObj, 2*diameter, 0.0, 4*diameter, 32, 1);
	gluDeleteQuadric(quadObj);

	quadObj = gluNewQuadric ();
	gluQuadricDrawStyle (quadObj, GLU_FILL);
	gluQuadricNormals (quadObj, GLU_SMOOTH);
	gluDisk(quadObj, 0.0, 2*diameter, 32, 1);
	gluDeleteQuadric(quadObj);

	glTranslatef(0,0,-length+4*diameter);

	quadObj = gluNewQuadric ();
	gluQuadricDrawStyle (quadObj, GLU_FILL);
	gluQuadricNormals (quadObj, GLU_SMOOTH);
	gluCylinder(quadObj, diameter, diameter, length-4*diameter, 32, 1);
	gluDeleteQuadric(quadObj);

	quadObj = gluNewQuadric ();
	gluQuadricDrawStyle (quadObj, GLU_FILL);
	gluQuadricNormals (quadObj, GLU_SMOOTH);
	gluDisk(quadObj, 0.0, diameter, 32, 1);
	gluDeleteQuadric(quadObj);

	glPopMatrix ();
}
