/* CS580 Homework 3 */

#include	"stdafx.h"
#include	"stdio.h"
#include	"math.h"
#include	"Gz.h"
#include	"rend.h"

#define PI (float) 3.14159265358979323846

int GzRender::GzRotXMat(float degree, GzMatrix mat)
{
/* HW 3.1
// Create rotate matrix : rotate along x axis
// Pass back the matrix using mat value
*/

	return GZ_SUCCESS;
}

int GzRender::GzRotYMat(float degree, GzMatrix mat)
{
/* HW 3.2
// Create rotate matrix : rotate along y axis
// Pass back the matrix using mat value
*/

	return GZ_SUCCESS;
}

int GzRender::GzRotZMat(float degree, GzMatrix mat)
{
/* HW 3.3
// Create rotate matrix : rotate along z axis
// Pass back the matrix using mat value
*/

	return GZ_SUCCESS;
}

int GzRender::GzTrxMat(GzCoord translate, GzMatrix mat)
{
/* HW 3.4
// Create translation matrix
// Pass back the matrix using mat value
*/

	return GZ_SUCCESS;
}


int GzRender::GzScaleMat(GzCoord scale, GzMatrix mat)
{
/* HW 3.5
// Create scaling matrix
// Pass back the matrix using mat value
*/

	return GZ_SUCCESS;
}


GzRender::GzRender(int xRes, int yRes)
{
/* HW1.1 create a framebuffer for MS Windows display:
 -- set display resolution
 -- allocate memory for framebuffer : 3 bytes(b, g, r) x width x height
 -- allocate memory for pixel buffer
 */
	framebuffer = (char*) malloc (3 * sizeof(char) * xRes * yRes);

/* HW 3.6
- setup Xsp and anything only done once 
- init default camera 
*/ 
}

GzRender::~GzRender()
{
/* HW1.2 clean up, free buffer memory */

}

int GzRender::GzDefault()
{
/* HW1.3 set pixel buffer to some default values - start a new frame */

	return GZ_SUCCESS;
}

int GzRender::GzBeginRender()
{
/* HW 3.7 
- setup for start of each frame - init frame buffer color,alpha,z
- compute Xiw and projection xform Xpi from camera definition 
- init Ximage - put Xsp at base of stack, push on Xpi and Xiw 
- now stack contains Xsw and app can push model Xforms when needed 
*/ 

	return GZ_SUCCESS;
}

int GzRender::GzPutCamera(GzCamera camera)
{
/* HW 3.8 
/*- overwrite renderer camera structure with new camera definition
*/

	return GZ_SUCCESS;	
}

int GzRender::GzPushMatrix(GzMatrix	matrix)
{
/* HW 3.9 
- push a matrix onto the Ximage stack
- check for stack overflow
*/
	
	return GZ_SUCCESS;
}

int GzRender::GzPopMatrix()
{
/* HW 3.10
- pop a matrix off the Ximage stack
- check for stack underflow
*/

	return GZ_SUCCESS;
}

int GzRender::GzPut(int i, int j, GzIntensity r, GzIntensity g, GzIntensity b, GzIntensity a, GzDepth z)
{
/* HW1.4 write pixel values into the buffer */

	return GZ_SUCCESS;
}


int GzRender::GzGet(int i, int j, GzIntensity *r, GzIntensity *g, GzIntensity *b, GzIntensity *a, GzDepth *z)
{
/* HW1.5 retrieve a pixel information from the pixel buffer */

	return GZ_SUCCESS;
}


int GzRender::GzFlushDisplay2File(FILE* outfile)
{
/* HW1.6 write image to ppm file -- "P6 %d %d 255\r" */
	
	return GZ_SUCCESS;
}

int GzRender::GzFlushDisplay2FrameBuffer()
{
/* HW1.7 write pixels to framebuffer: 
	- put the pixels into the frame buffer
	- CAUTION: when storing the pixels into the frame buffer, the order is blue, green, and red 
	- NOT red, green, and blue !!!
*/

	return GZ_SUCCESS;
}


/***********************************************/
/* HW2 methods: implement from here */

int GzRender::GzPutAttribute(int numAttributes, GzToken* nameList, GzPointer* valueList) {
	/* HW 2.1
	-- Set renderer attribute states (e.g.: GZ_RGB_COLOR default color)
	-- In later homeworks set shaders, interpolaters, texture maps, and lights
	*/

	if (pixelbuffer == NULL) {
		return GZ_FAILURE;
	}

	for (int i = 0; i < numAttributes; i++) {
		if (nameList[i] == GZ_RGB_COLOR) {
			GzColor* color = (GzColor*) valueList[i];
			flatcolor[RED] = *color[0];
			flatcolor[GREEN] = *color[1];
			flatcolor[BLUE] = *color[2];
		}

	}
	return GZ_SUCCESS;
}

int GzRender::GzPutTriangle(int	numParts, GzToken *nameList, GzPointer *valueList)
/* numParts - how many names and values */
{
	/* HW 2.2
	-- Pass in a triangle description with tokens and values corresponding to
	GZ_NULL_TOKEN:		do nothing - no values
	GZ_POSITION:		3 vert positions in model space
	-- Invoke the rastrizer/scanline framework
	-- Return error code
	*/
	
	if (pixelbuffer == NULL) {
		return GZ_FAILURE;
	}

	for (int i = 0; i < numParts; i++) {
		if (nameList[i] == GZ_NULL_TOKEN) {
			continue;
		}
		if (nameList[i] == GZ_POSITION) {
			std::vector<Vertex> vertices;
			std::vector<Edge> edges;
			bool flag;
			getVertices(vertices, valueList, i); // get three vertices of a triangle
			sortByY(vertices); // sort vertices by y
			setupEdges(edges, vertices, flag); // set up edges
			scanLine(edges, vertices, flag);
		}
	}
	return GZ_SUCCESS;
}

/* implementation of helper functions */

void getVertices(std::vector<Vertex>& vertices, GzPointer* valueList, int i) {
	Vertex v1, v2, v3;
	v1.x = ((GzCoord*) (valueList[i]))[0][0];
	v1.y = ((GzCoord*) (valueList[i]))[0][1];
	v1.z = ((GzCoord*) (valueList[i]))[0][2];

	v2.x = ((GzCoord*) (valueList[i]))[1][0];
	v2.y = ((GzCoord*) (valueList[i]))[1][1];
	v2.z = ((GzCoord*) (valueList[i]))[1][2];

	v3.x = ((GzCoord*) (valueList[i]))[2][0];
	v3.y = ((GzCoord*) (valueList[i]))[2][1];
	v3.z = ((GzCoord*) (valueList[i]))[2][2];

	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
}

void sortByY(std::vector<Vertex>& vertices) {
	for (int i = 0; i < 3; i++) {
		for (int j = (i + 1); j < 3; j++) {
			if (vertices[j].y < vertices[i].y) { // ascending
				Vertex temp = vertices[i];
				vertices[i] = vertices[j];
				vertices[j] = temp;
			}
		}
	}
}

void setupEdges(std::vector<Edge>& edges, std::vector<Vertex>& vertices, bool& flag) {
	Edge e01 = Edge(vertices[0], vertices[1]);
	Edge e10 = Edge(vertices[1], vertices[0]);
	Edge e02 = Edge(vertices[0], vertices[2]);
	Edge e20 = Edge(vertices[2], vertices[0]);
	Edge e12 = Edge(vertices[1], vertices[2]);
	Edge e21 = Edge(vertices[2], vertices[1]);

	flag = true;
	// inverted triangle
	if (vertices[0].y == vertices[1].y) {
		if (e02.slope_x > e12.slope_x) {
			edges.push_back(e10);
			edges.push_back(e02);
			edges.push_back(e12);
		} else {
			edges.push_back(e01);
			edges.push_back(e12);
			edges.push_back(e02);
		}
		return;
	}
	// regular triangle
	if (vertices[1].y == vertices[2].y) {
		if (e01.slope_x < e02.slope_x) {
			edges.push_back(e01);
			edges.push_back(e12);
			edges.push_back(e02);
		} else {
			edges.push_back(e02);
			edges.push_back(e21);
			edges.push_back(e01);
		}
		return;
	}
	// L or R triangle
	if (e01.slope_x < e02.slope_x) {
		edges.push_back(e01);
		edges.push_back(e12);
		edges.push_back(e02);
	} else {
		flag = false;
		edges.push_back(e01);
		edges.push_back(e12);
		edges.push_back(e02);
	}
}

void GzRender::scanLine(std::vector<Edge>& edges, std::vector<Vertex>& vertices, const bool& flag) {
	float dy;
	float dx;
	SpanLine spanLine;
	GzIntensity* r = (GzIntensity*) malloc(sizeof(GzIntensity));
	GzIntensity* g = (GzIntensity*) malloc(sizeof(GzIntensity));
	GzIntensity* b = (GzIntensity*) malloc(sizeof(GzIntensity));
	GzIntensity* a = (GzIntensity*) malloc(sizeof(GzIntensity));
	GzDepth* z = (GzDepth*) malloc(sizeof(GzDepth));

	/******************** ABOVE MID-VERT ********************/
	dy = ceil(vertices[0].y) - vertices[0].y;

	edges[0].current.x = edges[0].start.x + edges[0].slope_x * dy;
	edges[0].current.y = edges[0].start.y + dy;
	edges[0].current.z = edges[0].start.z + edges[0].slope_z * dy;

	edges[2].current.x = edges[2].start.x + edges[2].slope_x * dy;
	edges[2].current.y = edges[2].start.y + dy;
	edges[2].current.z = edges[2].start.z + edges[2].slope_z * dy;

	while (edges[0].current.y < edges[0].end.y) {
		// get a span line
		if (flag) {
			spanLine.set(edges[0].current, edges[2].current);
			dx = ceil(edges[0].current.x) - edges[0].current.x;
		} else {
			spanLine.set(edges[2].current, edges[0].current);
			dx = ceil(edges[2].current.x) - edges[2].current.x;
		}

		spanLine.current.x = spanLine.start.x + dx;
		spanLine.current.y = spanLine.start.y;
		spanLine.current.z = spanLine.start.z + spanLine.slope_z * dx;
		// color this span line
		while (spanLine.current.x < spanLine.end.x) {
			if (spanLine.current.z < 0) { // behind the camera
				spanLine.current.x = spanLine.current.x++;
				spanLine.current.z = spanLine.current.z + spanLine.slope_z;
				continue;
			}
			GzGet((int) spanLine.current.x, (int) spanLine.current.y, r, g, b, a, z);
			if (spanLine.current.z <= *z) { // check shading
				GzPut((int) spanLine.current.x, (int) spanLine.current.y, ctoi(flatcolor[RED]), ctoi(flatcolor[GREEN]), ctoi(flatcolor[BLUE]), 0, (GzDepth) spanLine.current.z);
			}
			spanLine.current.x = spanLine.current.x++;
			spanLine.current.z = spanLine.current.z + spanLine.slope_z;
		}

		edges[0].current.x = edges[0].current.x + edges[0].slope_x;
		edges[0].current.y = edges[0].current.y++;
		edges[0].current.z = edges[0].current.z + edges[0].slope_z;

		edges[2].current.x = edges[2].current.x + edges[2].slope_x;
		edges[2].current.y = edges[2].current.y++;
		edges[2].current.z = edges[2].current.z + edges[2].slope_z;
	}

	/******************** BELOW MID-VERT ********************/
	dy = ceil(vertices[1].y) - vertices[1].y;

	edges[1].current.x = edges[1].start.x + edges[1].slope_x * dy;
	edges[1].current.y = edges[1].start.y + dy;
	edges[1].current.z = edges[1].start.z + edges[1].slope_z * dy;

	edges[2].current.x = edges[2].current.x + edges[2].slope_x * dy;
	edges[2].current.y = edges[2].current.y + dy;
	edges[2].current.z = edges[2].current.z + edges[2].slope_z * dy;

	while (edges[1].current.y < edges[1].end.y) {
		// get a span line
		if (flag) {
			spanLine.set(edges[1].current, edges[2].current);
			dx = ceil(edges[1].current.x) - edges[1].current.x;
		} else {
			spanLine.set(edges[2].current, edges[1].current);
			dx = ceil(edges[2].current.x) - edges[2].current.x;
		}
		spanLine.current.x = spanLine.start.x + dx;
		spanLine.current.y = spanLine.start.y;
		spanLine.current.z = spanLine.start.z + spanLine.slope_z * dx;
		// color this span line
		while (spanLine.current.x < spanLine.end.x) {
			if (spanLine.current.z < 0) { // behind the camera
				spanLine.current.x = spanLine.current.x++;
				spanLine.current.z = spanLine.current.z + spanLine.slope_z;
				continue;
			}
			GzGet((int) spanLine.current.x, (int) spanLine.current.y, r, g, b, a, z);
			if (spanLine.current.z <= *z) { // check shading
				GzPut((int) spanLine.current.x, (int) spanLine.current.y, ctoi(flatcolor[RED]), ctoi(flatcolor[GREEN]), ctoi(flatcolor[BLUE]), 0, (GzDepth) spanLine.current.z);
			}
			spanLine.current.x = spanLine.current.x++;
			spanLine.current.z = spanLine.current.z + spanLine.slope_z;
		}

		edges[1].current.x = edges[1].current.x + edges[1].slope_x;
		edges[1].current.y = edges[1].current.y++;
		edges[1].current.z = edges[1].current.z + edges[1].slope_z;

		edges[2].current.x = edges[2].current.x + edges[2].slope_x;
		edges[2].current.y = edges[2].current.y++;
		edges[2].current.z = edges[2].current.z + edges[2].slope_z;
	}
	free(r);
	free(g);
	free(b);
	free(a);
	free(z);
};


