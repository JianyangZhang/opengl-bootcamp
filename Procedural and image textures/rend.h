#include	"gz.h"
#ifndef GZRENDER_
#define GZRENDER_


/* Camera defaults */
#define	DEFAULT_FOV		35.0
#define	DEFAULT_IM_Z	(-10.0)  /* world coords for image plane origin */
#define	DEFAULT_IM_Y	(5.0)    /* default look-at point = 0,0,0 */
#define	DEFAULT_IM_X	(-10.0)

#define	DEFAULT_AMBIENT	{0.1, 0.1, 0.1}
#define	DEFAULT_DIFFUSE	{0.7, 0.6, 0.5}
#define	DEFAULT_SPECULAR	{0.2, 0.3, 0.4}
#define	DEFAULT_SPEC		32

#define	MATLEVELS	100		/* how many matrix pushes allowed */
#define	MAX_LIGHTS	10		/* how many lights allowed */
#define PI (float) 3.14159265358979323846
#include <vector>
#include <limits.h>

struct Vertex {
	float x;
	float y;
	float z;
};

struct Edge {
	Vertex start;
	Vertex end;
	Vertex current;
	float slope_x;
	float slope_z;
	Edge(Vertex v1, Vertex v2) {
		start = v1;
		end = v2;
		slope_x = (v2.x - v1.x) / (v2.y - v1.y);
		slope_z = (v2.z - v1.z) / (v2.y - v1.y);
	}
};

struct SpanLine {
	Vertex start;
	Vertex end;
	Vertex current;
	float slope_z;
	void set(Vertex v1, Vertex v2) {
		start = v1;
		end = v2;
		slope_z = (v2.z - v1.z) / (v2.x - v1.x);
	}
};

// helper functions used in rend.cpp
void setupTriangle(GzCoord*, GzColor*, GzTextureIndex*);
void swap(float*, float*);
void swapUV(float*, float*);
void getZplane(const GzCoord*, float*, float*, float*, float*);
float getEdge(const float*, const float*, int, int, bool);
void vertToScreen(const GzCoord*, GzMatrix, GzCoord*);
void normalToScreen(const GzCoord*, GzMatrix, GzCoord*);
int normalize(GzCoord);
float getArea(GzCoord, GzCoord, GzCoord);
float dotProduct(GzCoord, GzCoord);

class GzRender{			/* define a renderer */

public:
	unsigned short	xres;
	unsigned short	yres;
	GzPixel		*pixelbuffer;		/* frame buffer array */
	char* framebuffer;

	GzCamera		m_camera;
	short		    matlevel;	        /* top of stack - current xform */
	GzMatrix		Ximage[MATLEVELS];	/* stack of xforms (Xsm) */
	GzMatrix		Xnorm[MATLEVELS];	/* xforms for norms (Xim) */
	GzMatrix		Xsp;		        /* NDC to screen (pers-to-screen) */
	GzColor		flatcolor;          /* color state for flat shaded triangles */
	int			interp_mode;
	int			numlights;
	GzLight		lights[MAX_LIGHTS];
	GzLight		ambientlight;
	GzColor		Ka, Kd, Ks;
	float		    spec;		/* specular power */
	GzTexture		tex_fun;    /* tex_fun(float u, float v, GzColor color) */

  	// Constructors
	GzRender(int xRes, int yRes);
	~GzRender();

	// Function declaration

	// HW1: Display methods
	int GzDefault();
	int GzBeginRender();
	int GzPut(int i, int j, GzIntensity r, GzIntensity g, GzIntensity b, GzIntensity a, GzDepth z);
	int GzGet(int i, int j, GzIntensity *r, GzIntensity *g, GzIntensity *b, GzIntensity *a, GzDepth	*z);

	int GzFlushDisplay2File(FILE* outfile);
	int GzFlushDisplay2FrameBuffer();

	// HW2: Render methods
	int GzPutAttribute(int numAttributes, GzToken *nameList, GzPointer *valueList);
	int GzPutTriangle(int numParts, GzToken *nameList, GzPointer *valueList);
	void LEE(GzCoord* vertices, GzCoord* normals, GzTextureIndex*);
	int getColor(GzColor color, GzCoord norm);
	int getTexture(GzColor color, GzCoord norm);

	// HW3
	int GzPutCamera(GzCamera camera);
	int GzPushMatrix(GzMatrix	matrix);
	int GzPopMatrix();

	// Extra methods: NOT part of API - just for general assistance */
	inline int ARRAY(int x, int y){return (x+y*xres);}	/* simplify fbuf indexing */
	inline short	ctoi(float color) {return(short)((int)(color * ((1 << 12) - 1)));}		/* convert float color to GzIntensity short */
	inline float radianOf(float degree) { return (float) (degree / 180) * PI; }

	// Object Translation
	int GzRotXMat(float degree, GzMatrix mat);
	int GzRotYMat(float degree, GzMatrix mat);
	int GzRotZMat(float degree, GzMatrix mat);
	int GzTrxMat(GzCoord translate, GzMatrix mat);
	int GzScaleMat(GzCoord scale, GzMatrix mat);

};
#endif