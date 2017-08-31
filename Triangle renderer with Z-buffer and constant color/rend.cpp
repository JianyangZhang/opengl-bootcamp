#include "Gz.h"
#include "stdafx.h"
#include "stdio.h"
#include "math.h"
#include "rend.h"
#include <vector>
#include <math.h>

/* helper structs & functions */
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
		slope_z = (v2.z - v1.z) / (v2.y - v1.y);
	}
};

void getVertices(std::vector<Vertex>& vertices, GzPointer *valueList, int i);
void sortByY(std::vector<Vertex>&);
void setupEdges(std::vector<Edge>&, std::vector<Vertex>&, int&);
void scan(std::vector<Edge>&, std::vector<Vertex>&, int&);

/***********************************************/
/* HW1 methods: copy here the methods from HW1 */

GzRender::GzRender(int xRes, int yRes) {
	/* HW1.1 create a framebuffer for MS Windows display:
	-- set display resolution
	-- allocate memory for framebuffer : 3 bytes(b, g, r) x width x height
	-- allocate memory for pixel buffer
	*/
	xres = xRes;
	yres = yRes;
	framebuffer = (char*) malloc(sizeof(GzPixel) * xRes * yRes);
	pixelbuffer = (GzPixel*) malloc(sizeof(GzPixel) * xRes * yRes);
}

GzRender::~GzRender() {
	/* HW1.2 clean up, free buffer memory */
	free(pixelbuffer);
	free(framebuffer);
}

int GzRender::GzDefault() {
	/* HW1.3 set pixel buffer to some default values - start a new frame */
	if (pixelbuffer == NULL) {
		return GZ_FAILURE;
	}
	for (int i = 0; i < xres; i++) {
		for (int j = 0; j < yres; j++) {
			pixelbuffer[ARRAY(i, j)].blue = 1000;
			pixelbuffer[ARRAY(i, j)].green = 1000;
			pixelbuffer[ARRAY(i, j)].red = 1000;
			pixelbuffer[ARRAY(i, j)].alpha = 1;
			pixelbuffer[ARRAY(i, j)].z = 0;
		}
	}
	return GZ_SUCCESS;
}


int GzRender::GzPut(int i, int j, GzIntensity r, GzIntensity g, GzIntensity b, GzIntensity a, GzDepth z) {
	/* HW1.4 write pixel values into the buffer */
	if (pixelbuffer == NULL || i < 0 || j < 0 || i >= xres || j >= yres) {
		return GZ_FAILURE;
	}

	b = (b > 0) ? b : 0;
	g = (g > 0) ? g : 0;
	r = (r > 0) ? r : 0;
	b = (b < 4095) ? b : 4095;
	g = (g < 4095) ? g : 4095;
	r = (r < 4095) ? r : 4095;

	pixelbuffer[ARRAY(i, j)].blue = b;
	pixelbuffer[ARRAY(i, j)].green = g;
	pixelbuffer[ARRAY(i, j)].red = r;
	pixelbuffer[ARRAY(i, j)].alpha = a;
	pixelbuffer[ARRAY(i, j)].z = z;

	return GZ_SUCCESS;
}


int GzRender::GzGet(int i, int j, GzIntensity* r, GzIntensity* g, GzIntensity* b, GzIntensity* a, GzDepth* z) {
	/* HW1.5 retrieve a pixel information from the pixel buffer */
	if (pixelbuffer == NULL || i < 0 || j < 0 || i >= xres || j >= yres) {
		return GZ_FAILURE;
	}

	*b = pixelbuffer[ARRAY(i, j)].blue;
	*g = pixelbuffer[ARRAY(i, j)].green;
	*r = pixelbuffer[ARRAY(i, j)].red;
	*a = pixelbuffer[ARRAY(i, j)].alpha;
	*z = pixelbuffer[ARRAY(i, j)].z;

	return GZ_SUCCESS;
}


int GzRender::GzFlushDisplay2File(FILE* outfile) {
	/* HW1.6 write image to ppm file -- "P6 %d %d 255\r" */
	if (pixelbuffer == NULL || outfile == NULL) {
		return GZ_FAILURE;
	}

	fprintf(outfile, "P6 %d %d 255\r", xres, yres);
	char r, g, b;
	for (int i = 0; i < xres; i++) {
		for (int j = 0; j < yres; j++) {
			r = pixelbuffer[ARRAY(j, i)].red >> 4;
			g = pixelbuffer[ARRAY(j, i)].green >> 4;
			b = pixelbuffer[ARRAY(j, i)].blue >> 4;
			fprintf(outfile, "%c%c%c", r, g, b);
		}
	}
	return GZ_SUCCESS;
}

int GzRender::GzFlushDisplay2FrameBuffer() {
	/* HW1.7 write pixels to framebuffer:
	- put the pixels into the frame buffer
	- CAUTION: when storing the pixels into the frame buffer, the order is blue, green, and red
	- NOT red, green, and blue !!!
	*/
	if (pixelbuffer == NULL || framebuffer == NULL) {
		return GZ_FAILURE;
	}

	char b, g, r;
	for (int i = 0; i < xres; i++) {
		for (int j = 0; j < yres; j++) {
			b = pixelbuffer[ARRAY(i, j)].blue >> 4;
			g = pixelbuffer[ARRAY(i, j)].green >> 4;
			r = pixelbuffer[ARRAY(i, j)].red >> 4;
			framebuffer[ARRAY(i, j) * 3] = b;
			framebuffer[ARRAY(i, j) * 3 + 1] = g;
			framebuffer[ARRAY(i, j) * 3 + 2] = r;
		}
	}

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
			GzColor* c = (GzColor*) valueList[i];
			*c[0] = *c[0] > 0 ? *c[0] : 0;
			*c[1] = *c[1] > 0 ? *c[1] : 0;
			*c[2] = *c[2] > 0 ? *c[2] : 0;
			*c[0] = *c[0] < 4095 ? *c[0] : 4095;
			*c[1] = *c[1] < 4095 ? *c[1] : 4095;
			*c[2] = *c[2] < 4095 ? *c[2] : 4095;

			flatcolor[RED] = *c[0];
			flatcolor[GREEN] = *c[1];
			flatcolor[BLUE] = *c[2];
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
			int flag;
			getVertices(vertices, valueList, i); // get three vertices of a triangle
			sortByY(vertices); // sort vertices by y
			setupEdges(edges, vertices, flag); // set up edges

			// scan line to fill up the triangle
			float dy = ceil(vertices[0].y) - vertices[0].y;
			SpanLine spanLine;
			GzIntensity* r;
			GzIntensity* g;
			GzIntensity* b;
			GzIntensity* a;
			GzDepth* z;

			if (flag == 2) {
				/******************** ABOVE MID-VERT ********************/
				// first left point of span line
				edges[0].current.x = edges[0].start.x + edges[0].slope_x * dy;
				edges[0].current.y = edges[0].start.y + dy;
				edges[0].current.z = edges[0].start.z + edges[0].slope_z * dy;
				// first right point of span line
				edges[2].current.x = edges[2].start.x + edges[2].slope_x * dy;
				edges[2].current.y = edges[2].start.y + dy;
				edges[2].current.z = edges[2].start.z + edges[2].slope_z * dy;
				
				while (edges[0].current.y < edges[0].end.y) {
					// get a span line
					spanLine.set(edges[0].current, edges[2].current);
					float dx = ceil(edges[0].current.x) - edges[0].current.x;
					spanLine.current.x = edges[0].current.x + dx;
					spanLine.current.y = edges[0].current.y;
					spanLine.current.z = edges[0].current.z + edges[0].slope_z * dx;
					// color this span line
					while (spanLine.current.x < edges[2].current.x) {
						if (spanLine.current.z < 0) { // behind camera
							continue;
						}
						GzGet((int) spanLine.current.x, (int) spanLine.current.y, r, g, b, a, z);
						if (spanLine.current.z <= *z) {
							GzPut((int) spanLine.current.x, (int) spanLine.current.y, *r, *g, *b, *a, *z);
						}
						spanLine.current.x = spanLine.current.x + dx;
						spanLine.current.z = edges[0].current.z + edges[0].slope_z * dx;
					}
					// next left point of the span line
					edges[0].current.x = edges[0].start.x + edges[0].slope_x * dy;
					edges[0].current.y = edges[0].start.y + dy;
					edges[0].current.z = edges[0].start.z + edges[0].slope_z * dy;
					// next right point of the span line
					edges[2].current.x = edges[2].start.x + edges[2].slope_x * dy;
					edges[2].current.y = edges[2].start.y + dy;
					edges[2].current.z = edges[2].start.z + edges[2].slope_z * dy;
				}
				/******************** BELOW MID-VERT ********************/


			}
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

void setupEdges(std::vector<Edge>& edges, std::vector<Vertex>& vertices, int& flag) {
	Edge e01 = Edge(vertices[0], vertices[1]);
	Edge e10 = Edge(vertices[1], vertices[0]);
	Edge e02 = Edge(vertices[0], vertices[2]);
	Edge e20 = Edge(vertices[2], vertices[0]);
	Edge e12 = Edge(vertices[1], vertices[2]);
	Edge e21 = Edge(vertices[2], vertices[1]);

	// inverted triangle
	if (vertices[0].y == vertices[1].y) {
		flag = 0;
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
		flag = 1;
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
		flag = 2;
		edges.push_back(e01);
		edges.push_back(e12);
		edges.push_back(e02);
	} else {
		flag = 3;
		edges.push_back(e02);
		edges.push_back(e01);
		edges.push_back(e12);
	}
}
