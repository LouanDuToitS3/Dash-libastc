#include <stdio.h>
#include <stdlib.h>

#include "astc.h"

// Template methods from mathlib.cpp which are defined out for MSVC builds when C++ < 11.
// Which is legacy and false, but will be fixed in VS2017 15.7 Preview 3 
#if (_MSC_VER) && (__cplusplus < 201103L)
float fmax(float p, float q)
{
	if (p != p)
		return q;
	if (q != q)
		return p;
	if (p > q)
		return p;
	return q;
}

float fmin(float p, float q)
{
	if (p != p)
		return q;
	if (q != q)
		return p;
	if (p < q)
		return p;
	return q;
}
#endif

void myExit(int exitCode) throw ()
{
    printf("ASTC encoder error: %d\n", exitCode);
}
