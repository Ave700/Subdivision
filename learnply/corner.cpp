#include "learnply.h"

void Corner::findAngle() {
	//find vectors from self to other points
	//printf("x: %lf\n", n->v->x);
	icVector3 v1 = icVector3(n->v->x, n->v->y, n->v->z) - icVector3(v->x,v->y,v->z);
	icVector3 v2 = icVector3(p->v->x, p->v->y, p->v->z) - icVector3(v->x, v->y, v->z);
	double magv1 = length(v1);
	double magv2 = length(v2);

	double dotres = dot(v1, v2);

	theta = acos( dotres / (magv1 * magv2));

}
