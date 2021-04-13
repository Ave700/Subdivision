#include "learnply.h"
class myPoly
{
	std::vector<Vertex*> verts;
	std::vector<Edge*> edges;
	std::vector<Triangle*> tris;
	std::vector<Corner*> corners;

	myPoly(Triangle** tlist, int ntris, Vertex** vlist, int nverts);
};

