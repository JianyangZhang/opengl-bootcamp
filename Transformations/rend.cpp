/* CS580 Homework 3 */
#include	"stdafx.h"
#include	"stdio.h"
#include	"math.h"
#include	"rend.h"

#define PI (float) 3.14159265358979323846

int GzRender::GzRotXMat(float degree, GzMatrix mat)
{
/* HW 3.1
// Create rotate matrix : rotate along x axis
// Pass back the matrix using mat value
*/
	/*
		1    0    0    0
		0   cos -sin   0
		0   sin  cos   0
		0    0    0    1
	*/
	float radian = radianOf(degree);
	mat[0][0] = 1;              mat[0][1] = 0;              mat[0][2] = 0;              mat[0][3] = 0;

	mat[1][0] = 0;				mat[1][1] = cos(radian);    mat[1][2] = -sin(radian);   mat[1][3] = 0;

	mat[2][0] = 0;              mat[2][1] = sin(radian);    mat[2][2] = cos(radian);    mat[2][3] = 0;

	mat[3][0] = 0;              mat[3][1] = 0;              mat[3][2] = 0;              mat[3][3] = 1;
	return GZ_SUCCESS;
}

int GzRender::GzRotYMat(float degree, GzMatrix mat)
{
/* HW 3.2
// Create rotate matrix : rotate along y axis
// Pass back the matrix using mat value
*/
	/*
	cos  0   sin  0
	0    1    0   0
   -sin  0   cos  0
	0    0    0   1
	*/
	float radian = radianOf(degree);
	mat[0][0] = cos(radian);    mat[0][1] = 0;              mat[0][2] = sin(radian);    mat[0][3] = 0;

	mat[1][0] = 0;              mat[1][1] = 1;              mat[1][2] = 0;              mat[1][3] = 0;

	mat[2][0] = -sin(radian);   mat[2][1] = 0;              mat[2][2] = cos(radian);    mat[2][3] = 0;

	mat[3][0] = 0;              mat[3][1] = 0;              mat[3][2] = 0;              mat[3][3] = 1;

	return GZ_SUCCESS;
}

int GzRender::GzRotZMat(float degree, GzMatrix mat)
{
/* HW 3.3
// Create rotate matrix : rotate along z axis
// Pass back the matrix using mat value
*/	
   /*
	cos -sin  0   0
	sin  cos  0   0
    0    0    1   0
	0    0    0   1
	*/
	float radian = radianOf(degree);
	mat[0][0] = cos(radian);    mat[0][1] = -sin(radian);   mat[0][2] = 0;              mat[0][3] = 0;

	mat[1][0] = sin(radian);    mat[1][1] = cos(radian);    mat[1][2] = 0;              mat[1][3] = 0;

	mat[2][0] = 0;              mat[2][1] = 0;              mat[2][2] = 1;              mat[2][3] = 0;

	mat[3][0] = 0;              mat[3][1] = 0;              mat[3][2] = 0;              mat[3][3] = 1;

	return GZ_SUCCESS;
}

int GzRender::GzTrxMat(GzCoord translate, GzMatrix mat)
{
/* HW 3.4
// Create translation matrix
// Pass back the matrix using mat value
*/
	/*
     1,  0,  0,  tx
     0,  1,  0,  ty
     0,  0,  1,  tz
     0,  0,  0,  1
	*/
	mat[0][0] = 1; mat[0][1] = 0; mat[0][2] = 0; mat[0][3] = translate[0];

	mat[1][0] = 0; mat[1][1] = 1; mat[1][2] = 0; mat[1][3] = translate[1];

	mat[2][0] = 0; mat[2][1] = 0; mat[2][2] = 1; mat[2][3] = translate[2];

	mat[3][0] = 0; mat[3][1] = 0; mat[3][2] = 0; mat[3][3] = 1;
	return GZ_SUCCESS;
}


int GzRender::GzScaleMat(GzCoord scale, GzMatrix mat)
{
/* HW 3.5
// Create scaling matrix
// Pass back the matrix using mat value
*/
	/*
	sx,  0,   0,   0
	0,   sy,  0,   0
	0,   0,   sz,  0
	0,   0,   0,   1
	*/
	mat[0][0] = scale[0];      mat[0][1] = 0;           mat[0][2] = 0;          mat[0][3] = 0;

	mat[1][0] = 0;             mat[1][1] = scale[1];    mat[1][2] = 0;          mat[1][3] = 0;

	mat[2][0] = 0;             mat[2][1] = 0;           mat[2][2] = scale[2];   mat[2][3] = 0;

	mat[3][0] = 0;             mat[3][1] = 0;           mat[3][2] = 0;          mat[3][3] = 1;

	return GZ_SUCCESS;
}


GzRender::GzRender(int xRes, int yRes)
{
/* HW1.1 create a framebuffer for MS Windows display:
 -- set display resolution
 -- allocate memory for framebuffer : 3 bytes(b, g, r) x width x height
 -- allocate memory for pixel buffer
 */
	xres = xRes;
	yres = yRes;
	framebuffer = (char*) malloc(3 * sizeof(char) * xRes * yRes);
	pixelbuffer = (GzPixel*) malloc(sizeof(GzPixel) * xRes * yRes);

/* HW 3.6
- setup Xsp and anything only done once 
- init default camera 
*/ 
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			Xsp[i][j] = 0;
			m_camera.Xiw[i][j] = 0;
			m_camera.Xpi[i][j] = 0;
		}
	}
	matlevel = 0;
	m_camera.lookat[0] = 0;
	m_camera.lookat[1] = 0;
	m_camera.lookat[2] = 0;
	m_camera.position[0] = DEFAULT_IM_X;
	m_camera.position[1] = DEFAULT_IM_Y;
	m_camera.position[2] = DEFAULT_IM_Z;
	m_camera.worldup[0] = 0;
	m_camera.worldup[1] = 1;
	m_camera.worldup[2] = 0;
	m_camera.FOV = DEFAULT_FOV;
}

GzRender::~GzRender()
{
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
			pixelbuffer[ARRAY(i, j)].blue = 3000;
			pixelbuffer[ARRAY(i, j)].green = 3000;
			pixelbuffer[ARRAY(i, j)].red = 3000;
			pixelbuffer[ARRAY(i, j)].alpha = 1;
			pixelbuffer[ARRAY(i, j)].z = INT_MAX;
		}
	}
	return GZ_SUCCESS;
}

int GzRender::GzBeginRender()
{
/* HW 3.7 
- setup for start of each frame - init frame buffer color, alpha, z
- compute Xiw and projection xform Xpi from camera definition 
- init Ximage - put Xsp at base of stack, push on Xpi and Xiw 
- now stack contains Xsw and app can push model Xforms when needed 
*/	

	float d;
	float radian;
	// ---------------- Xsp ----------------
	radian = radianOf(m_camera.FOV);
	d = 1 / (tan(radian / 2));
	Xsp[0][0] = xres / 2.0; 
	Xsp[0][1] = 0;
	Xsp[0][2] = 0;
	Xsp[0][3] = xres / 2.0;

	Xsp[1][0] = 0;
	Xsp[1][1] = yres / 2.0;
	Xsp[1][2] = 0;
	Xsp[1][3] = yres / 2.0;

	Xsp[2][0] = 0;
	Xsp[2][1] = 0;
	Xsp[2][2] = INT_MAX / d;
	Xsp[2][3] = 0;

	Xsp[3][0] = 0;
	Xsp[3][1] = 0;
	Xsp[3][2] = 0;
	Xsp[3][3] = 1;
	GzPushMatrix(Xsp);

	// ---------------- Xpi ----------------
	m_camera.Xpi[0][0] = 1;
	m_camera.Xpi[1][1] = 1;
	m_camera.Xpi[2][2] = 1;
	m_camera.Xpi[3][3] = 1;
	m_camera.Xpi[3][2] = 1 / d;
	GzPushMatrix(m_camera.Xpi);

	// ---------------- Xiw ----------------
	Vertex cl;
	Vertex cz;
	float dp;
	Vertex up;
	Vertex cUp;
	Vertex cy;
	Vertex cx;
	Vertex camera;
	
	//camera Z-axis
	cl.x = m_camera.lookat[0] - m_camera.position[0];
	cl.y = m_camera.lookat[1] - m_camera.position[1];
	cl.z = m_camera.lookat[2] - m_camera.position[2];
	cz = normalize(cl);
	//up vector 
	up.x = m_camera.worldup[0];
	up.y = m_camera.worldup[1];
	up.z = m_camera.worldup[2];
	dp = dotProduct(up, cz);
	//camera Y-axis
	cUp.x = up.x - dp * cz.x;
	cUp.y = up.y - dp * cz.y;
	cUp.z = up.z - dp * cz.z;
	cy = normalize(cUp);
	//camera X-axis
	cx = crossProduct(cy, cz);
	//camera location
	camera.x = m_camera.position[0];
	camera.y = m_camera.position[1];
	camera.z = m_camera.position[2];

	m_camera.Xiw[0][0] = cx.x;
	m_camera.Xiw[0][1] = cx.y;
	m_camera.Xiw[0][2] = cx.z;
	m_camera.Xiw[0][3] = -dotProduct(cx, camera);

	m_camera.Xiw[1][0] = cy.x;
	m_camera.Xiw[1][1] = cy.y;
	m_camera.Xiw[1][2] = cy.z;
	m_camera.Xiw[1][3] = -dotProduct(cy, camera);

	m_camera.Xiw[2][0] = cz.x;
	m_camera.Xiw[2][1] = cz.y;
	m_camera.Xiw[2][2] = cz.z;
	m_camera.Xiw[2][3] = -dotProduct(cz, camera);

	m_camera.Xiw[3][0] = 0;
	m_camera.Xiw[3][1] = 0;
	m_camera.Xiw[3][2] = 0;
	m_camera.Xiw[3][3] = 1;
	GzPushMatrix(m_camera.Xiw);

	return GZ_SUCCESS;
}

int GzRender::GzPutCamera(GzCamera camera)
{
/* HW 3.8 
/*- overwrite renderer camera structure with new camera definition
*/
	m_camera.position[0] = camera.position[0];
	m_camera.position[1] = camera.position[1];
	m_camera.position[2] = camera.position[2];

	m_camera.lookat[0] = camera.lookat[0];
	m_camera.lookat[1] = camera.lookat[1];
	m_camera.lookat[2] = camera.lookat[2];

	m_camera.worldup[0] = camera.worldup[0];
	m_camera.worldup[1] = camera.worldup[1];
	m_camera.worldup[2] = camera.worldup[2];

	m_camera.FOV = camera.FOV;
	return GZ_SUCCESS;	
}

int GzRender::GzPushMatrix(GzMatrix	matrix)
{
/* HW 3.9 
- push a matrix onto the Ximage stack
- check for stack overflow
*/
	if (matlevel >= MATLEVELS) {
		return GZ_FAILURE;
	}
	if (matlevel == 0) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				Ximage[matlevel][i][j] = matrix[i][j];
			}
		}
	} else {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				Ximage[matlevel][i][j] = 0;
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 4; k++) {
					Ximage[matlevel][i][j] += Ximage[matlevel - 1][i][k] * matrix[k][j];
				}
			}
		}
	}
	matlevel++;
	return GZ_SUCCESS;
}

int GzRender::GzPopMatrix()
{
/* HW 3.10
- pop a matrix off the Ximage stack
- check for stack underflow
*/
	if (matlevel <= 0) {
		return GZ_FAILURE;
	}
	matlevel--;
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
			std::vector<Vertex> v(3);
			std::vector<Vertex> vertices;
			std::vector<Edge> edges;
			bool flag;
			getVertices(vertices, valueList, i); // get three vertices of a triangle
			worldSpaceToScreenSpace(vertices, Ximage[matlevel - 1], v);
			if ((checkTri(v, xres, yres)) == 1) { continue; }
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

Vertex normalize(const Vertex& v) {
	Vertex result;
	float sum = v.x * v.x + v.y * v.y + v.z * v.z;
	result.x = v.x / sqrt(sum);
	result.y = v.y / sqrt(sum);
	result.z = v.z / sqrt(sum);
	return result;
}

float dotProduct(const Vertex& a, const Vertex& b) {
	float result = a.x * b.x + a.y * b.y + a.z * b.z;
	return result;
}

Vertex crossProduct(const Vertex& a, const Vertex& b) {
	Vertex result;
	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return result;
}

void worldSpaceToScreenSpace(std::vector<Vertex>& vertW, GzMatrix matrix, std::vector<Vertex>& vertS) {
	float outVect[4][3];
	float transVect[4][3];

	for (int i = 0; i < 3; i++) {
		transVect[0][i] = vertW[i].x;
		transVect[1][i] = vertW[i].y;
		transVect[2][i] = vertW[i].z;
		transVect[3][i] = 1;
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			outVect[i][j] = 0;
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 4; k++) {
				outVect[i][j] = outVect[i][j] + matrix[i][k] * transVect[k][j];
			}
		}
	}

	for (int i = 0; i < 3; i++) {
		vertS[i].x = outVect[0][i] / outVect[3][i];
		vertS[i].y = outVect[1][i] / outVect[3][i];
		vertS[i].z = outVect[2][i] / outVect[3][i];
	}
}

int checkTri(std::vector<Vertex>& v, unsigned short	xres, unsigned short yres) {
	int d_f = 0;
	int v_n = 0;
	for (int i = 0; i < 3; i++) {
		if (v[i].z < 0) //check if this triangle has vertex behind the camera
		{
			d_f = 1;
			break;
		}
		if ((v[i].x < 0 || v[i].x > xres) || (v[i].y < 0 || v[i].y > yres)) //check if this triangle is out of the screen
		{
			v_n++;
		}
	}
	if (v_n == 3) //all three verts are out of the screen
	{
		d_f = 1;
	}
	return d_f;
}