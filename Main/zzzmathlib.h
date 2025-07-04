#ifndef __MATHLIB__
#define __MATHLIB__

#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef DOUBLEVEC_T
typedef double vec_t;
#else
typedef float vec_t;
#endif
typedef vec_t vec3_t[3];
typedef vec_t vec4_t[4];
typedef vec_t vec34_t[3][4];

typedef struct
{
	vec3_t StartPos;
	vec3_t XAxis;
	vec3_t YAxis;
	vec3_t ZAxis;
} OBB_t;

#define	SIDE_FRONT		0
#define	SIDE_ON			2
#define	SIDE_BACK		1
#define	SIDE_CROSS		-2

#define	Q_PI		 	3.14159265358979323846f
#define	ON_EPSILON		0.01
#define	EQUAL_EPSILON	0.001

int VectorCompare (vec3_t v1, vec3_t v2);

float GetSquare(float value);

#define Vector(a,b,c,d) {(d)[0]=a;(d)[1]=b;(d)[2]=c;}
#define Vector4(a,b,c,d,e) {(e)[0]=a;(e)[1]=b;(e)[2]=c;(e)[3]=d;}
#define VectorAvg(a) ( ( (a)[0] + (a)[1] + (a)[2] ) / 3 )
#define VectorSubtract(a,b,c) {(c)[0]=(a)[0]-(b)[0];(c)[1]=(a)[1]-(b)[1];(c)[2]=(a)[2]-(b)[2];}
#define VectorAdd(a,b,c) {(c)[0]=(a)[0]+(b)[0];(c)[1]=(a)[1]+(b)[1];(c)[2]=(a)[2]+(b)[2];}
#define VectorCopy(a,b) {(b)[0]=(a)[0];(b)[1]=(a)[1];(b)[2]=(a)[2];}
#define VectorCopy123(a,b) {(b)[0]=(a)[0];(b)[1]=(a)[1];(b)[2]=(a)[2];}

#define VectorScale(a,b,c) {(c)[0]=(b)*(a)[0];(c)[1]=(b)*(a)[1];(c)[2]=(b)*(a)[2];}
#define DotProduct(x,y) ((x)[0]*(y)[0]+(x)[1]*(y)[1]+(x)[2]*(y)[2])
#define VectorFill(a,b) { (a)[0]=(b); (a)[1]=(b); (a)[2]=(b);}

vec_t Q_rint (vec_t in);
vec_t _DotProduct (vec3_t v1, vec3_t v2);
void _VectorSubtract (vec3_t va, vec3_t vb, vec3_t out);
void _VectorAdd (vec3_t va, vec3_t vb, vec3_t out);
void _VectorCopy (vec3_t in, vec3_t out);
void _VectorScale (vec3_t v, vec_t scale, vec3_t out);

float VectorLength(vec3_t v);

void VectorMA (vec3_t va, float scale, vec3_t vb, vec3_t vc);

void CrossProduct (vec3_t v1, vec3_t v2, vec3_t cross);
vec_t VectorNormalize (vec3_t v);
void VectorInverse (vec3_t v);

void ClearBounds (vec3_t mins, vec3_t maxs);
void AddPointToBounds (vec3_t v, vec3_t mins, vec3_t maxs);

void AngleMatrix (const vec3_t angles, float matrix[3][4] );
void AngleIMatrix (const vec3_t angles, float matrix[3][4] );
void R_ConcatTransforms (const float in1[3][4], const float in2[3][4], float out[3][4]);

void VectorIRotate (const vec3_t in1, const float in2[3][4], vec3_t out);
void VectorRotate (const vec3_t in1, const float in2[3][4], vec3_t out);
void VectorTranslate (const vec3_t in1, const float in2[3][4], vec3_t out);
void VectorTransform (const vec3_t in1, const float in2[3][4], vec3_t out);

void AngleQuaternion( const vec3_t angles, vec4_t quaternion );
void QuaternionMatrix( const vec4_t quaternion, float (*matrix)[4] );
void QuaternionSlerp( const vec4_t p, vec4_t q, float t, vec4_t qt );

void FaceNormalize(vec3_t v1,vec3_t v2,vec3_t v3,vec3_t Normal);

#ifdef __cplusplus
}
#endif

#endif
