/*

Data structures for learnply

Eugene Zhang 2005

*/

#ifndef __LEARNPLY_H__
#define __LEARNPLY_H__


#include "ply.h"
#include "icVector.H"
#include <vector>


const double EPS = 1.0e-6;
const double PI=3.1415926535898;

/* forward declarations */
class Triangle;
class Corner;

class Vertex {
public:
  double x,y,z;
  int index;

  int ntris;
  Triangle **tris;
  std::vector<Corner*> corners;
  int max_tris;

	icVector3 normal;
  void *other_props;

  //holds vertex color settings
  double r = .60, g = .60, b = .6;

public:
  Vertex(double xx, double yy, double zz) { x = xx; y = yy; z = zz; }
  Vertex(icVector3 pos) { x = pos.x; y =  pos.y; z = pos.z; }
  icVector3 pos() {
	  return icVector3(x, y, z);
  }
};

class Edge {
public:
  int index;
  Vertex *verts[2];
  int ntris;
  Triangle **tris;
	double length;
	bool broken = false;
};

class Triangle {
public:
  int index;
  int nverts;
  Vertex *verts[3];
  //for irregular
  Vertex* new_verts[3] = { NULL, NULL, NULL };
  Edge *edges[3];
  std::vector<Edge*> brokenEdges;
  //for regualr
  std::vector<Vertex*> newVerts;
  std::vector<Corner*> corners;
	double angle[3];
	float area;

	icVector3 normal;
  void *other_props;
};

class Corner
{
public:
	int index;
	//holds index in cur triangle
	int t_index;
	//Points to previous corner
	Corner* p;
	//Points to next corner
	Corner* n;
	//Points to opposite corner in another triangle
	Corner* o;

	//Points to triangle containing corner
	Triangle* t;
	//points to vertex at corner
	Vertex* v;
	//points to edge opposite corner
	Edge* e;

	//Stores the angle of the corner (must be updated during subdivision)
	double theta;

	void findAngle();
};



class Polyhedron {
public:

int index;
 std::vector<Corner*> clist; /* vector holding corners*/

  Triangle **tlist;  /* list of triangles */
  int ntris;
  int max_tris;

  Vertex **vlist;    /* list of vertices */
  int nverts;
  int max_verts;

  Edge **elist;      /* list of edges */
  int nedges;
  int max_edges;

icVector3 center;
double radius;
double area;

int seed;

  PlyOtherProp *vert_other,*face_other;

	void average_normals();
	void subdivideRegular();
	void subdivideIrregular();
	void create_corners();
	void clear_corner_vectors();
	void create_edge(Vertex *, Vertex *);
	void create_edges();
	int face_to_vertex_ref(Triangle *, Vertex *);
	void order_vertex_to_tri_ptrs(Vertex *);
	void vertex_to_tri_ptrs();
	Triangle *find_common_edge(Triangle *, Vertex *, Vertex *);
	Triangle *other_triangle(Edge *, Triangle *);
	void calc_bounding_sphere();
	void calc_face_normals_and_area();
	void calc_edge_length();

	Polyhedron();
  Polyhedron(FILE *);
  void write_file(FILE *);

  void create_pointers();

	// initialization and finalization
	void initialize();
	void finalize();
};

#endif /* __LEARNPLY_H__ */

