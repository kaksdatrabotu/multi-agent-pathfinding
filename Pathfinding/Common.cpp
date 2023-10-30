#include "Common.h"


void normalizeVectorManhattan(Vec2d& v)
{
	if (v.x > 0)
		v.x = 1;
	else if (v.x < 0)
		v.x = -1;

	if (v.y > 0)
		v.y = 1;
	else if (v.y < 0)
		v.y = -1;
}