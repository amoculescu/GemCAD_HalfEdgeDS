// ========================================================================= //
// Authors: Matthias Borner                                                  //
// mailto:matthias.borner@igd.fraunhofer.de                                  //
//                                                                           //
// GRIS - Graphisch Interaktive Systeme                                      //
// Technische Universitšt Darmstadt                                          //
// Fraunhoferstrasse 5                                                       //
// D-64283 Darmstadt, Germany                                                //
// ========================================================================= //

#ifndef HALF_EDGE_DS_H
#define HALF_EDGE_DS_H

#include <stdlib.h>		// standard library
#include <vector>		// std::vector<>
#include <list>			// std::list<>

#include "HalfEdgeDSElements.h"

// Handles creating, verifying and modifying a half edge data structure.
// Also manages memory. Since we heavily rely on raw pointers, we need to use "new" and "delete", else we get memory leaks.
class HalfEdgeDS
{

protected:

	// class members: lists of pointers to the elements. these are unsorted. the next element is not necessarily connected to the previous one.
	// so this class owns all created data structure elements and is responsible for adding new ones and deleting old ones.
	std::list<Solid*> solids;
	std::list<Face*> faces;
	std::list<Loop*> loops;
	std::list<Edge*> edges;
	std::list<HalfEdge*> halfEdges;
	std::list<Vertex*> vertices;

public:

	// empty constructor which creates an example object
	HalfEdgeDS();

	// deletes the content of the data structure
	~HalfEdgeDS();

	// creates a default example object
	void createDefaultObject();

	// clears the data structure completely
	void clearDS();

	// getters with read only access, returned as reference, so nothing gets copied
	const std::list<Solid*>& getSolids() const { return solids; }
	const std::list<Face*>& getFaces() const { return faces; }
	const std::list<Loop*>& getLoops() const { return loops; }
	const std::list<Edge*>& getEdges() const { return edges; }
	const std::list<HalfEdge*>& getHalfEdges() const { return halfEdges; }
	const std::list<Vertex*>& getVertices() const { return vertices; }

	// overloading the << operator to print our information of the class
	friend std::ostream& operator<< (std::ostream& os, HalfEdgeDS& ds);

	// TODO: Extend the interface of the this data structure by implementing at least three euler opertators
    void mvvels(float aon[][3]);
    void MEV(HalfEdge* he, float aon[]);
    void MEL(HalfEdge* he, Vertex* v1);
    void KEMH(HalfEdge* he);
    HalfEdge* getOppositeHE(HalfEdge* he);
    void checkEuler();
	// TODO: Check if the data structure is correct using the Euler-Poincar'e formula

private:

};

// ostream << operator to print some info of the data structure
std::ostream& operator<< (std::ostream& os, HalfEdgeDS& ds);

#endif
