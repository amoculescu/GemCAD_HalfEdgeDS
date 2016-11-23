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
    glPushMatrix();
    glTranslatef(-1, -1, 0);
    glPushMatrix();
    glScalef(0.8, 0.8, 0.8);
    //glTranslatef(1.25, 1.25, 0);
    for (auto const *he : heDS.getHalfEdges()) renderHE(he, colorGreen); // render all halfedges as lines
    glPopMatrix();
    glPopMatrix();
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
    Vec3f p2;
    glColor3fv(&color.x);
    if(he == he->toEdge->he1)
    {
        p2 = he->toEdge->he2->startV->coordinates;
    }
    else
    {
        p2 = he->toEdge->he1->startV->coordinates;
    }
    renderArrow(he->startV->coordinates, p2, 0.02);
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
