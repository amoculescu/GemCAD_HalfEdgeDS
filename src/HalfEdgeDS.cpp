#include "HalfEdgeDS.h"

#include <GL/glut.h>
#include <stdio.h>		// cout
#include <iostream>		// cout

HalfEdgeDS::HalfEdgeDS()
{
	clearDS();
	createDefaultObject();
}	

HalfEdgeDS::~HalfEdgeDS()
{
	clearDS();
}

void HalfEdgeDS::createDefaultObject()
{
    /*float defObjCoord[][3] =   {{0.0f, 0.0f, 0.0f}, //array with containing arrays of coordinates for the vertices
                                {0.0f, 2.0f, 0.0f},
                                {2.0f, 2.0f, 0.0f},
                                {2.0f, 0.0f, 0.0f},
                                {2.0f, 0.0f, 2.0f}
                               };*/
    float defObjCoord[][3] =   {{0.0f, 0.0f, 0.0f}, //array with containing arrays of coordinates for the vertices
                                  {0.0f, 2.0f, 0.0f},
                                  {2.0f, 2.0f, 0.0f},
                                  {2.0f, 0.0f, 0.0f},
                                  {0.0f, 0.0f, 2.0f},
                                  {0.0f, 2.0f, 2.0f},
                                  {2.0f, 2.0f, 2.0f},
                                  {2.0f, 0.0f, 2.0f}
                                 };
 mvvels(defObjCoord);
 auto ptrToLast = vertices.begin();
 auto ptrToFirst = vertices.begin();
 std::advance(ptrToLast, (vertices.size() - 1));
 MEV(*ptrToLast, defObjCoord[2]);
 ptrToLast = vertices.begin();
 std::advance(ptrToLast, (vertices.size() - 1));
 MEV(*ptrToLast, defObjCoord[3]);
 ptrToLast = vertices.begin();
 std::advance(ptrToLast, (vertices.size() - 1));
 MEL(*ptrToFirst, *ptrToLast, true);
 ptrToLast = vertices.begin();
 MEV(*ptrToLast, defObjCoord[4]);
 ptrToLast = vertices.begin();
 std::advance(ptrToLast, 1);
 MEV(*ptrToLast, defObjCoord[5]);
 ptrToLast = vertices.begin();
 std::advance(ptrToLast, 2);
 MEV(*ptrToLast, defObjCoord[6]);
 ptrToLast = vertices.begin();
 std::advance(ptrToLast, 3);
 MEV(*ptrToLast, defObjCoord[7]);
/* ptrToFirst = vertices.begin();
 ptrToLast = vertices.begin();
 std::advance(ptrToFirst, (vertices.size() - 4));
 std::advance(ptrToLast, (vertices.size() - 3));
 MEL(*ptrToFirst, *ptrToLast);
 ptrToFirst = vertices.begin();
 ptrToLast = vertices.begin();
 std::advance(ptrToFirst, (vertices.size() - 3));
 std::advance(ptrToLast, (vertices.size() - 2));
 MEL(*ptrToFirst, *ptrToLast);
 ptrToFirst = vertices.begin();
 ptrToLast = vertices.begin();
 std::advance(ptrToFirst, (vertices.size() - 2));
 std::advance(ptrToLast, (vertices.size() - 1));
 MEL(*ptrToFirst, *ptrToLast);
 ptrToFirst = vertices.begin();
 ptrToLast = vertices.begin();
 std::advance(ptrToFirst, (vertices.size() - 4));
 std::advance(ptrToLast, (vertices.size() - 1));
 MEL(*ptrToFirst, *ptrToLast);*/


 /*auto ptrToLast = vertices.begin();
 for (int i = 2; i < 4; i++)
 {
     ptrToLast = vertices.begin();
     std::advance(ptrToLast, (vertices.size() -1 ));
     MEV(*ptrToLast, defObjCoord[i]);
 }
 auto ptrToFirst = vertices.begin();
 ptrToLast = vertices.begin();
 std::advance(ptrToLast, (vertices.size() -1 ));
 MEL(*ptrToFirst, *ptrToLast);
 for(int i = 0; i < 4; i++)
 {
     ptrToLast = vertices.begin();
     std::advance(ptrToLast, i);
     MEV(*ptrToLast, defObjCoord[i + 4]);
     if (i > 0)
     {
         ptrToFirst = vertices.begin();
         ptrToLast = vertices.begin();
         std::advance(ptrToFirst, (vertices.size() - 2));
         std::advance(ptrToLast, (vertices.size() -1 ));
         MEL(*ptrToFirst, *ptrToLast);
     }
 }
 ptrToFirst = vertices.begin();
 ptrToLast = vertices.begin();
 std::advance(ptrToFirst, (vertices.size() - 4));
 std::advance(ptrToLast, (vertices.size() -1 ));
 MEL(*ptrToFirst, *ptrToLast);*/

	// CARE: for every "new" we need a "delete". if an element is added to the according list, it is deleted automatically within clearDS().

	// TODO: Create a new VALID test object including all topological elements and linkage. The object should be volumetric and consist of at least one hole (H > 0).
}

void HalfEdgeDS::mvvels(float aon[][3] = nullptr)
{
    //create 2 Vertices 1x edge 2 halfedges 1 loop 1 solid
    Solid* s1 = new Solid;
    Face* f = new Face;
    Loop* l1 = new Loop;
    Vertex* v1 = new Vertex;
    Vertex* v2 = new Vertex;
    Edge* e1 = new Edge;
    HalfEdge* he1 = new HalfEdge;
    HalfEdge* he2 = new HalfEdge;

    //push elements into lists
    solids.push_back(s1);

    faces.push_back(f);

    loops.push_back(l1);

    vertices.push_back(v1);
    vertices.push_back(v2);

    edges.push_back(e1);

    halfEdges.push_back(he1);
    halfEdges.push_back(he2);

    //set up topology
    l1->nextLoop = l1;
    l1->prevLoop = l1;
    l1->toFace = f;
    l1->toHE = he1;

    f->outerLoop = l1;
    f->toSolid = s1;

    float x1,y1,z1,x2,y2,z2;
    if(aon == nullptr)
    {
        //ask user for point coordinates
        std::cout << "coordinates for V1 and V2 format: x1,y1,z1,x2,y2,z2" << std::endl;
        std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
    }
    else
    {
        x1 = aon[0][0];
        y1 = aon[0][1];
        z1 = aon[0][2];
        x2 = aon[1][0];
        y2 = aon[1][1];
        z2 = aon[1][2];
    }
    v1->coordinates = Vec3f(x1, y1, z1);
    v1->outgoingHE = he1;
    v2->coordinates = Vec3f(x2, y2, z2);
    v2->outgoingHE = he2;

    e1->he1 = he1;
    e1->he2 = he2;

    he1->startV = v1;
    he1->toEdge = e1;
    he1->toLoop = l1;
    he1->nextHE = he2;
    he1->prevHE = he2;

    he2->startV = v2;
    he2->toEdge = e1;
    he2->toLoop = l1;
    he2->nextHE = he1;
    he2->prevHE = he1;
}

void HalfEdgeDS::MEV(Vertex* v, float aon[] = nullptr)
{
    //create needed Elements
    Vertex* vNew = new Vertex;

    Edge* e = new Edge;

    HalfEdge* he1 = new HalfEdge;
    HalfEdge* he2 = new HalfEdge;

    //push elements into lists

    vertices.push_back(vNew);

    edges.push_back(e);

    halfEdges.push_back(he1);
    halfEdges.push_back(he2);

    float x,y,z;
    //create topology
    if(aon == nullptr)
    {
        //ask user for point coordinates
        std::cout << "coordinates for new vertex format: x,y,z" << std::endl;
        std::cin >> x >> y >> z;
    }
    else
    {
        x = aon[0];
        y = aon[1];
        z = aon[2];
    }
    vNew->coordinates = Vec3f(x, y, z);

    e->he1 = he1;
    e->he2 = he2;

    he1->toEdge = e;
    he1->toLoop = v->outgoingHE->toLoop;
    he2->toEdge = e;
    he2->toLoop = v->outgoingHE->toLoop;

    if(v->outgoingHE->nextHE->nextHE != v->outgoingHE)
    {
        vNew->outgoingHE = he1;
        he1->startV = vNew;
        he1->nextHE = getOppositeHE(v->outgoingHE)->nextHE;
        he1->prevHE = he2;
        he2->startV = v;
        he2->nextHE = he1;
        he2->prevHE = getOppositeHE(v->outgoingHE);
        getOppositeHE(v->outgoingHE)->nextHE->prevHE = he1;
        getOppositeHE(v->outgoingHE)->nextHE = he2;
        v->outgoingHE = he2;
    }
    else
    {
        vNew->outgoingHE = he1;
        he1->startV = vNew;
        he1->nextHE = v->outgoingHE;
        he1->prevHE = he2;
        he2->startV = v;
        he2->nextHE = he1;
        he2->prevHE = getOppositeHE(v->outgoingHE);
        v->outgoingHE->prevHE = he1;
        getOppositeHE(v->outgoingHE)->nextHE = he2;
        v->outgoingHE = he2;
    }
}
void HalfEdgeDS::MEL(Vertex* v1, Vertex* v2, bool front = true)
{
    //create new elements
    Loop* l = new Loop;
    Face* f = new Face;
    Edge* e = new Edge;
    HalfEdge* he1 = new HalfEdge;
    HalfEdge* he2 = new HalfEdge;

    loops.push_back(l);
    faces.push_back(f);
    edges.push_back(e);
    halfEdges.push_back(he1);
    halfEdges.push_back(he2);

    f->toSolid = v1->outgoingHE->toLoop->toFace->toSolid;
    f->outerLoop = l;
    f->innerLoop = l;

    l->nextLoop = l;
    l->prevLoop = l;
    l->toFace = f;

    HalfEdge* hea[2];
    hea[0] = he1;
    hea[1] = he2;

    int i, j;
    if (front = true)
    {
        i = 0;
        j = 1;
     }
    else
    {
        i = 1;
        j = 0;
    }

    e->he1 = hea[i];
    e->he2 = hea[j];

    l->toHE = hea[i];

    hea[i]->startV = v1;
    hea[i]->toLoop = l;
    hea[i]->toEdge = e;
    hea[i]->nextHE = v2->outgoingHE;
    hea[i]->prevHE = getOppositeHE(v1->outgoingHE);
    hea[j]->startV = v2;
    hea[j]->toLoop = v1->outgoingHE->toLoop;
    hea[j]->toEdge = e;
    hea[j]->nextHE = v1->outgoingHE;
    hea[j]->prevHE = getOppositeHE(v2->outgoingHE);

//    getOppositeHE(v1->outgoingHE)->nextHE = hea[i];
    v2->outgoingHE->prevHE = hea[i];
    getOppositeHE(v1->outgoingHE)->nextHE = hea[i];
    v1->outgoingHE->prevHE = hea[j];
    getOppositeHE(v2->outgoingHE)->nextHE = hea[j];
    v1->outgoingHE = hea[i];
    v2->outgoingHE = hea[j];


    /*Vertex* middlePoint;
    float maxX, maxY, maxZ;
    int interator = 0;;
    middlePoint = vertices.front();
    maxX = middlePoint->coordinates.x;
    maxY = middlePoint->coordinates.y;
    maxZ = middlePoint->coordinates.z;
    while (iterator <= vertices.end())
    {
        std::advance(middlePoint, iterator);
        if(middlePoint->coordinates.x > maxX)
        {
            maxX = middlePoint->coordinates.x;
        }
        if(middlePoint->coordinates.y > maxY)
        {
            maxY = middlePoint->coordinates.y;
        }
        if(middlePoint->coordinates.Z > maxZ)
        {
            maxZ = middlePoint->coordinates.z;
        }
        iterator++;
    }
    middlePoint = new Vertex;
    middlePoint->coordinates = Vec3f((maxX / 2), (maxY / 2), (maxZ) / 2);

    //create new elements
    Loop* l = new Loop;
    Face* f = new Face;
    Edge* e = new Edge;
    HalfEdge* he1 = new HalfEdge;
    HalfEdge* he2 = new HalfEdge;

    loops.push_back(l);
    faces.push_back(f);
    edges.push_back(e);
    halfEdges.push_back(he1);
    halfEdges.push_back(he2);

    //set up connections of new elements

    f->toSolid = v1->outgoingHE->toLoop->toFace->toSolid;
    f->outerLoop = l;
    f->innerLoop = l;

    l->toHE = he2;
    l->nextLoop = l;
    l->prevLoop = l;
    l->toFace = f;

    e->he1 = he1;
    e->he2 = he2;

    he1->startV = v1;
    he1->toEdge = e;
    he1->toLoop = v1->outgoingHE->toLoop;
    he2->startV = v2;
    he2->toEdge = e;
    he2->toLoop = l;

    he1->nextHE = v2->outgoingHE;
    he1->prevHE = v1->outgoingHE->toEdge->he1;
    he2->nextHE = v1->outgoingHE->toEdge->he1->nextHE;
    he2->prevHE = v2->outgoingHE->toEdge->he1;
    //update old connections
    v1->outgoingHE->toEdge->he1->nextHE->prevHE = he2;
    v1->outgoingHE->toEdge->he1->nextHE = he1;
    v2->outgoingHE->prevHE->nextHE = he2;
    v2->outgoingHE->prevHE = he1;
    v1->outgoingHE = he1;
    v2->outgoingHE = he2;
    /*else //if v1 == last Vertex
    {
        he1->startV = v2;
        he1->nextHE = v2->outgoingHE;
        he1->prevHE = v1->outgoingHE->toEdge->he1;
        he2->startV = v1;
        he2->nextHE = v2->outgoingHE->toEdge->he1->nextHE;
        he2->prevHE = v1->outgoingHE->prevHE;
        //update old connections
        v1->outgoingHE->prevHE->nextHE = he2;
        v1->outgoingHE->prevHE = he1;
        v2->outgoingHE->prevHE->nextHE = he1;
        v2->outgoingHE->prevHE = he2;
        v1->outgoingHE = he2;
        v2->outgoingHE = he1;
    }
    HalfEdge* tempHE = new HalfEdge;
    tempHE = he1->nextHE;
    while(tempHE != he1)
    {
        tempHE->toLoop = l;
        tempHE = tempHE->nextHE;
    }
    //TODO: test for mistakes in connections;*/
}

HalfEdge* HalfEdgeDS::getOppositeHE(HalfEdge* he)
{
    if(he == he->toEdge->he1)
    {
        return he->toEdge->he2;
    }
    else
    {
        return he->toEdge->he1;
    }
}

void HalfEdgeDS::clearDS()
{
	// for every "new" in this code, we need to call delete. take care, that you delete ALL elements
	for (auto *p : vertices) delete p;
	vertices.clear();
	for (auto *p : halfEdges) delete p;
	halfEdges.clear();
	for (auto *p : edges) delete p;
	edges.clear();
	for (auto *p : loops) delete p;
	loops.clear();
	for (auto *p : faces) delete p;
	faces.clear();
	for (auto *p : solids) delete p;
	solids.clear();
}



std::ostream& operator<< (std::ostream& os, HalfEdgeDS& ds)
{
	os << "Elements in the lists of the data structure:" << std::endl;
	os << "  " << ds.solids.size() << " solids, "
		<< ds.faces.size() << " faces, "
		<< ds.loops.size() << " loops, "
		<< ds.edges.size() << " edges, "
		<< ds.halfEdges.size() << " halfEdges, "
		<< ds.vertices.size() << " vertices.";
	return os;
}
