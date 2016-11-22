#include "HalfEdgeDS.h"

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
    MVVELS();

    for (int i = 0; i < 2; i++)
    {
        auto vi = vertices.begin();
        std::advance(vi, i);
        MEV(*vi);
    }
	// CARE: for every "new" we need a "delete". if an element is added to the according list, it is deleted automatically within clearDS().

	// create example elements. 	

	// TODO: Create a new VALID test object including all topological elements and linkage. The object should be volumetric and consist of at least one hole (H > 0).
}

void HalfEdgeDS::MVVELS()
{
    //create 2 Vertices 1x edge 2 halfedges 1 loop 1 solid
    Solid* s1 = new Solid;
    Loop* l1 = new Loop;
    Vertex* v1 = new Vertex;
    Vertex* v2 = new Vertex;
    Edge* e1 = new Edge;
    HalfEdge* he1 = new HalfEdge;
    HalfEdge* he2 = new HalfEdge;

    //push elements into lists
    solids.push_back(s1);

    loops.push_back(l1);

    vertices.push_back(v1);
    vertices.push_back(v2);

    edges.push_back(e1);

    halfEdges.push_back(he1);
    halfEdges.push_back(he2);

    //set up topology
    l1->nextLoop = l1;
    l1->prevLoop = l1;
    l1->toHE = he1;

    float x1,y1,z1,x2,y2,z2;
    std::cout << "coordinates for V1 and V2 format: x1,y1,z1,x2,y2,z2" << std::endl;
    std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
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

void HalfEdgeDS::MEV(Vertex* v)
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

    //create topology
    float x,y,z;
    std::cout << "coordinates for new vertex format: x,y,z" << std::endl;
    std::cin >> x >> y >> z;
    vNew->coordinates = Vec3f(x, y, z);
    vNew->outgoingHE = he2;

    e->he1 = he1;
    e->he2 = he2;

    he1->startV = v;
    he1->toEdge = e;
    he1->toLoop = v->outgoingHE->toLoop;
    he1->nextHE = he2;
    he1->prevHE = v->outgoingHE->prevHE;

    he2->startV = vNew;
    he2->toEdge = e;
    he2->toLoop = v->outgoingHE->toLoop;
    he2->nextHE = v->outgoingHE;
    he2->prevHE = he1;

    //make previous half-edges point to new ones
    v->outgoingHE->prevHE->nextHE = he2;
    v->outgoingHE->prevHE = he1;
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
