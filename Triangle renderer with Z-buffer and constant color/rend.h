#include "gz.h"
#include <vector>
#include <limits.h>

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

#define	MATLEVELS	10		/* how many matrix pushes allowed */
#define	MAX_LIGHTS	10		/* how many lights allowed */

/* Dummy definition : change it later */
#ifndef GzCamera
#define GzCamera	    	GzPointer
#endif

#ifndef GzLight
#define GzLight		GzPointer
#endif

#ifndef GzTexture
#define GzTexture	GzPointer
#endif

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

void getVertices(std::vector<Vertex>& vertices, GzPointer *valueList, int i);
void sortByY(std::vector<Vertex>&);
void setupEdges(std::vector<Edge>&, std::vector<Vertex>&, bool&);

class GzRender{			/* define a renderer */
  

public:
	unsigned short xres;
	unsigned short yres;
	GzPixel *pixelbuffer;		/* frame buffer array */
	char* framebuffer;

	GzCamera camera;
	short matlevel;	/* top of stack - current xform */
	GzMatrix Ximage[MATLEVELS];	/* stack of xforms (Xsm) */
	GzMatrix Xnorm[MATLEVELS];	/* xform for norms (Xim) */
	GzMatrix Xsp;		/* NDC to screen (pers-to-screen) */
	GzColor flatcolor;    /* color state for flat shaded triangles */
	int interp_mode;
	int numlights;
	GzLight	lights[MAX_LIGHTS];
	GzLight	ambientlight;
	GzColor	Ka, Kd, Ks;
	float spec;		/* specular power */
	GzTexture tex_fun;  /* tex_fun(float u, float v, GzColor color) */


	// Constructors
	GzRender(int xRes, int yRes);
	~GzRender();

	// HW1: Display methods
	int GzDefault();
	int GzPut(int i, int j, GzIntensity r, GzIntensity g, GzIntensity b, GzIntensity a, GzDepth z);
	int GzGet(int i, int j, GzIntensity *r, GzIntensity *g, GzIntensity *b, GzIntensity *a, GzDepth	*z);

	int GzFlushDisplay2File(FILE* outfile);
	int GzFlushDisplay2FrameBuffer();

	// HW2: Render methods
	int GzPutAttribute(int numAttributes, GzToken *nameList, GzPointer *valueList);
	int GzPutTriangle(int numParts, GzToken *nameList, GzPointer *valueList);
	void scanLine(std::vector<Edge>& edges, std::vector<Vertex>& vertices, const bool& flag); /* fill up the triangle with color by Scan-Line */
	
	// Extra methods: NOT part of API - just for general assistance */
	inline int ARRAY(int x, int y){return x+(y*xres);}	/* simplify fbuf indexing */
	inline short ctoi(float color) {return(short)((int)(color * ((1 << 12) - 1)));}		/* convert float color to GzIntensity short */
};

#endif

