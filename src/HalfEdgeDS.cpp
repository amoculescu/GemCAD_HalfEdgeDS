#include "HalfEdgeDS.h"
#include "HalfEdgeDSRendering.h"
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
    float defObjCoord[][3] =   {{1.0f, 1.0f, 0.0f}, //array with containing arrays of coordinates for the vertices
                                  {1.0f, 6.0f, 0.0f},
                                  {6.0f, 1.0f, 0.0f},
                                  {6.0f, 6.0f, 0.0f},
                                  {1.0f, 1.0f, -5.0f},
                                  {1.0f, 6.0f, -5.0f},
                                  {6.0f, 6.0f, -5.0f},
                                  {6.0f, 1.0f, -5.0f}
                                 };
    mvvels(defObjCoord);
    auto ptrToHalfEdge = halfEdges.begin();
    auto ptrToVertex = vertices.begin();
    MEV(*ptrToHalfEdge, defObjCoord[2]);
    std::advance(ptrToHalfEdge, 1);
    MEV(*ptrToHalfEdge, defObjCoord[3]);
    ptrToHalfEdge = halfEdges.begin();
    std::advance(ptrToHalfEdge, 5);
    std::advance(ptrToVertex, 2);
    MEL(*ptrToHalfEdge, *ptrToVertex, true);
    ptrToHalfEdge = halfEdges.begin();
    MEV(*ptrToHalfEdge, defObjCoord[4]);
    std::advance(ptrToHalfEdge, 4);
    MEV(*ptrToHalfEdge, defObjCoord[5]);
    ptrToHalfEdge = halfEdges.begin();
    std::advance(ptrToHalfEdge, 7);
    MEV(*ptrToHalfEdge, defObjCoord[6]);
    ptrToHalfEdge = halfEdges.begin();
    std::advance(ptrToHalfEdge, 3);
    MEV(*ptrToHalfEdge, defObjCoord[7]);
    ptrToHalfEdge = halfEdges.begin();
    ptrToVertex = vertices.begin();
    std::advance(ptrToHalfEdge, 15);
    std::advance(ptrToVertex, 4);
    MEL(*ptrToHalfEdge, *ptrToVertex, true);
    ptrToHalfEdge = halfEdges.begin();
    std::advance(ptrToHalfEdge, 11);
    MEL(*ptrToHalfEdge, *ptrToVertex, true);
    ptrToHalfEdge = halfEdges.begin();
    ptrToVertex = vertices.begin();
    std::advance(ptrToHalfEdge, 17);
    std::advance(ptrToVertex, 6);
    MEL(*ptrToHalfEdge, *ptrToVertex, true);
    ptrToHalfEdge = halfEdges.begin();
    ptrToVertex = vertices.begin();
    std::advance(ptrToHalfEdge, 11);
    std::advance(ptrToVertex, 6);
    MEL(*ptrToHalfEdge, *ptrToVertex, true);


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


void HalfEdgeDS::MEV(HalfEdge* he, float aon[] = nullptr)
{
    Vertex* vNew = new Vertex;
    Vertex* vOld = he->startV;
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

    he1->startV = vOld;
    he1->toEdge = e;
    he1->toLoop = he->toLoop;
    he1->nextHE = he2;
    he1->prevHE = he->prevHE;

    he2->startV = vNew;
    he2->nextHE = he;
    he2->prevHE = he1;
    he2->toEdge = e;
    he2->toLoop = he->toLoop;

    he->prevHE->nextHE = he1;
    he->prevHE = he2;

    vOld->outgoingHE = he1;
    vNew->outgoingHE = he2;

}

void HalfEdgeDS::MEL(HalfEdge* he, Vertex* v2, bool front = true)
{
    //create new elements
    Vertex* v1 = he->startV;
    Loop* l = new Loop;
    Face* f = new Face;
    Edge* e = new Edge;
    HalfEdge* he1 = new HalfEdge;
    HalfEdge* he2 = new HalfEdge;
    HalfEdge* temp = he;

    loops.push_back(l);
    faces.push_back(f);
    edges.push_back(e);
    halfEdges.push_back(he1);
    halfEdges.push_back(he2);

    f->toSolid = v1->outgoingHE->toLoop->toFace->toSolid;
    f->outerLoop = l;

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

    while(temp->startV != v2)
    {
        temp = temp->nextHE;
    }

    hea[i]->startV = v2;
    hea[i]->nextHE = he;
    hea[i]->prevHE = temp->prevHE;
    hea[i]->toEdge = e;
    hea[i]->toLoop = he->toLoop;

    hea[j]->startV = v1;
    hea[j]->nextHE = temp;
    hea[j]->prevHE = he->prevHE;
    hea[j]->toEdge = e;
    hea[j]->toLoop = l;

    he->prevHE->nextHE = hea[j];
    he->prevHE = hea[i];
    temp->prevHE->nextHE = hea[i];
    temp->prevHE = hea[j];
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

void HalfEdgeDS::KEMH(HalfEdge* he)
{
    //create new elements
    Loop* l = new Loop;
    loops.push_back(l);
    //Set tmp Pointer
    HalfEdge* hea = he->prevHE;
    HalfEdge* heb = getOppositeHE(he)->nextHE;
    HalfEdge* tmp = he->nextHE;
    Loop* oldLoop = he->toLoop;
    Face* face = oldLoop->toFace;

    // Set Pointers
    oldLoop->nextLoop = l;
    l->prevLoop = oldLoop;
    l->nextLoop = oldLoop->nextLoop;
    oldLoop->toHE = hea;
    l->toFace = oldLoop->toFace;
    l->toHE = he->nextHE;
    face->innerLoop = l;
    hea->nextHE = heb;
    heb->prevHE = hea;
    while (tmp->startV != he->nextHE->startV)
    {
        tmp->toLoop = l;
        tmp = tmp->nextHE;
    }
    tmp->nextHE = he->nextHE;
    he->nextHE->prevHE = tmp;
    // remove from lists and heap
    edges.remove(he->toEdge);
    halfEdges.remove(getOppositeHE(he));
    halfEdges.remove(he);
    /*delete getOppositeHE(he);
    delete he->toEdge;
    delete he;*/
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

void HalfEdgeDS::checkEuler()
{
                // Amount of holes (inner loops)
        int h = 0;
        std::list<Face*> hfaces;
        hfaces = faces;
        while (hfaces.size() != 0)
        {
                if (hfaces.front()->innerLoop != nullptr)
                {
                        h++;
                        hfaces.pop_front();
                }
                else
                {
                        hfaces.pop_front();
                }
        }
                int a;
                a = 1 - (vertices.size() - edges.size() + faces.size() - h) / 2;
                std::cout << "According to the Euler-Pointcare formula, there should be " << a << " rings" << std::endl;

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
