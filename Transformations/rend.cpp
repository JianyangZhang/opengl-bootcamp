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
	if (mat == NULL) { return GZ_FAILURE; }
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
	if (mat == NULL) { return GZ_FAILURE; }
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
	if (mat == NULL) { return GZ_FAILURE; }
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
	if (mat == NULL) { return GZ_FAILURE; }
	mat[0][0] = 1; mat[0][1] = 0; mat[0][2] = 0; mat[0][3] = translate[X];

	mat[1][0] = 0; mat[1][1] = 1; mat[1][2] = 0; mat[1][3] = translate[Y];

	mat[2][0] = 0; mat[2][1] = 0; mat[2][2] = 1; mat[2][3] = translate[Z];

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
	if (mat == NULL) { return GZ_FAILURE; }
	mat[0][0] = scale[X];      mat[0][1] = 0;           mat[0][2] = 0;          mat[0][3] = 0;

	mat[1][0] = 0;             mat[1][1] = scale[Y];    mat[1][2] = 0;          mat[1][3] = 0;

	mat[2][0] = 0;             mat[2][1] = 0;           mat[2][2] = scale[Z];   mat[2][3] = 0;

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
	matlevel = 0;

	// setup Xsp
	float d;
	float radian = radianOf(m_camera.FOV);
	d = 1 / (tan(radian / 2));
	Xsp[0][0] = xres / 2.0;
	Xsp[0][1] = 0;
	Xsp[0][2] = 0;
	Xsp[0][3] = xres / 2.0;

	Xsp[1][0] = 0;
	Xsp[1][1] = -yres / 2.0;
	Xsp[1][2] = 0;
	Xsp[1][3] = yres / 2.0;

	Xsp[2][0] = 0;
	Xsp[2][1] = 0;
	Xsp[2][2] = MAXINT;
	Xsp[2][3] = 0;

	Xsp[3][0] = 0;
	Xsp[3][1] = 0;
	Xsp[3][2] = 0;
	Xsp[3][3] = 1;

	// setup camera
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
	float rad = radianOf(m_camera.FOV / 2);

	// ---------------- Xpi ----------------
	m_camera.Xpi[0][0] = 1;
	m_camera.Xpi[0][1] = 0;
	m_camera.Xpi[0][2] = 0;
	m_camera.Xpi[0][3] = 0;
	
	m_camera.Xpi[1][0] = 0;
	m_camera.Xpi[1][1] = 1;
	m_camera.Xpi[1][2] = 0;
	m_camera.Xpi[1][3] = 0;
	
	m_camera.Xpi[2][0] = 0;
	m_camera.Xpi[2][1] = 0;
	m_camera.Xpi[2][2] = tan(rad);
	m_camera.Xpi[2][3] = 0;

	m_camera.Xpi[3][0] = 0;
	m_camera.Xpi[3][1] = 0;
	m_camera.Xpi[3][2] = tan(rad);
	m_camera.Xpi[3][3] = 1;
	
	// ---------------- Xiw ----------------
	GzCoord cl, camZ;
	cl[X] = m_camera.lookat[X] - m_camera.position[X];
	cl[Y] = m_camera.lookat[Y] - m_camera.position[Y];
	cl[Z] = m_camera.lookat[Z] - m_camera.position[Z];
	normalize(cl);
	camZ[X] = cl[X];
	camZ[Y] = cl[Y];
	camZ[Z] = cl[Z];
	normalize(camZ);

	GzCoord camUp, camY;
	float upDotZ = m_camera.worldup[X] * camZ[X] + m_camera.worldup[Y] * camZ[Y] + m_camera.worldup[Z] * camZ[Z];
	camUp[X] = m_camera.worldup[X] - upDotZ*camZ[X];
	camUp[Y] = m_camera.worldup[Y] - upDotZ*camZ[Y];
	camUp[Z] = m_camera.worldup[Z] - upDotZ*camZ[Z];
	normalize(camUp);
	camY[X] = camUp[X];
	camY[Y] = camUp[Y];
	camY[Z] = camUp[Z];
	normalize(camY);

	GzCoord camX;
	camX[X] = camY[Y] * camZ[Z] - camY[Z] * camZ[Y];
	camX[Y] = camY[Z] * camZ[X] - camY[X] * camZ[Z];
	camX[Z] = camY[X] * camZ[Y] - camY[Y] * camZ[X];
	normalize(camX);

	m_camera.Xiw[0][0] = camX[X];
	m_camera.Xiw[0][1] = camX[Y];
	m_camera.Xiw[0][2] = camX[Z];
	m_camera.Xiw[0][3] = -(camX[X] * m_camera.position[X] + camX[Y] * m_camera.position[Y] + camX[Z] * m_camera.position[Z]);

	m_camera.Xiw[1][0] = camY[X];
	m_camera.Xiw[1][1] = camY[Y];
	m_camera.Xiw[1][2] = camY[Z];
	m_camera.Xiw[1][3] = -(camY[X] * m_camera.position[X] + camY[Y] * m_camera.position[Y] + camY[Z] * m_camera.position[Z]);

	m_camera.Xiw[2][0] = camZ[X];
	m_camera.Xiw[2][1] = camZ[Y];
	m_camera.Xiw[2][2] = camZ[Z];
	m_camera.Xiw[2][3] = -(camZ[X] * m_camera.position[X] + camZ[Y] * m_camera.position[Y] + camZ[Z] * m_camera.position[Z]);

	m_camera.Xiw[3][0] = 0;
	m_camera.Xiw[3][1] = 0;
	m_camera.Xiw[3][2] = 0;
	m_camera.Xiw[3][3] = 1;

	GzPushMatrix(Xsp);
	GzPushMatrix(m_camera.Xpi);
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

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			Ximage[matlevel][i][j] = 0;
		}
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
				for (int m = 0; m < 4; m++) {
					Ximage[matlevel][i][j] += Ximage[matlevel - 1][i][m] * matrix[m][j];
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

/* ------------------------------- HW2 ------------------------------- */

int GzRender::GzPutAttribute(int numAttributes, GzToken* nameList, GzPointer* valueList) {
	for (int i = 0; i < numAttributes; i++) {
		if (*nameList == GZ_RGB_COLOR) {
			GzColor* a = (GzColor*) valueList[0];
			flatcolor[0] = (*a)[0];
			flatcolor[1] = (*a)[1];
			flatcolor[2] = (*a)[2];
		}
	}
	return GZ_SUCCESS;
}

int GzRender::GzPutTriangle(int	numParts, GzToken *nameList, GzPointer *valueList) {
	GzCoord* vertices_model;
	GzCoord* vertices_screen;
	vertices_screen = (GzCoord*) malloc(sizeof(GzCoord) * 3);
	for (int i = 0; i < numParts; i++) {
		if (nameList[i] == GZ_NULL_TOKEN) {
			continue;
		}
		if (nameList[i] == GZ_POSITION) {
			vertices_model = (GzCoord*) valueList[i];
			toScreen(vertices_model, Ximage[matlevel - 1], vertices_screen);
		}
	}

	bool inScreen = FALSE;
	for (int i = 0; i < 3; i++) {
		if (vertices_screen[i][X] >= 0 && vertices_screen[i][X] < xres &&
			vertices_screen[i][Y] >= 0 && vertices_screen[i][Y] < yres) {
			inScreen = TRUE;
			break;
		}
	}

	if (vertices_screen[0][Z] > 0 && vertices_screen[1][Z] > 0 && vertices_screen[2][Z] > 0 && inScreen) {
		setupTriangle(vertices_screen);
		LEE(vertices_screen);
	}
	return GZ_SUCCESS;
}

void GzRender::LEE(GzCoord* vertices) {
	int Up = floor(vertices[0][Y]);
	int Down = ceil(vertices[1][Y] > vertices[2][Y] ? vertices[1][Y] : vertices[2][Y]);
	int Left = floor(min(min(vertices[0][X], vertices[1][X]), vertices[2][X]));
	int Right = ceil(max(max(vertices[0][X], vertices[1][X]), vertices[2][X]));
	bool E01Right;
	bool E12Right;
	bool E20Right;
	GzIntensity red, green, blue, alpha;
	GzDepth fbZ;
	if (vertices[0][Y] == vertices[1][Y] || vertices[1][Y] < vertices[2][Y]) {
		E01Right = true;
		E12Right = true;
		E20Right = false;
	} else {
		E01Right = true;
		E12Right = false;
		E20Right = false;
	}
	float A, B, C, D;
	getZplane(vertices, &A, &B, &C, &D);
	for (int j = Up; j < Down; j++) {
		if (j < 0 || j > xres) {
			continue;
		}
		for (int i = Left; i < Right; i++) {
			if (i < 0 || i > yres) {
				continue;
			}
			float E01 = getEdge(vertices[0], vertices[1], i, j, E01Right);
			float E12 = getEdge(vertices[1], vertices[2], i, j, E12Right);
			float E20 = getEdge(vertices[2], vertices[0], i, j, E20Right);
			if (E01 > 0 && E12 > 0 && E20 > 0 || E01 < 0 && E12 < 0 && E20 < 0) {
				float pointZ = (-A * i - B * j - D) / C;
				GzGet(i, j, &red, &green, &blue, &alpha, &fbZ);
				if (pointZ > 0 && pointZ < fbZ) {
					red = ctoi(flatcolor[0]);
					green = ctoi(flatcolor[1]);
					blue = ctoi(flatcolor[2]);
					fbZ = pointZ;
					GzPut(i, j, red, green, blue, alpha, fbZ);
				}
			}
		}
	}
}

void setupTriangle(GzCoord* vertices) {
	for (int i = 2; i > 0; i--) {
		if (vertices[i][Y] < vertices[i - 1][Y]) {
			swap(vertices[i], vertices[i - 1]);
		}
	}
	if (vertices[2][Y] < vertices[1][Y]) {
		swap(vertices[2], vertices[1]);
	}
	if (vertices[0][Y] == vertices[1][Y]) {
		if (vertices[0][X] > vertices[1][X]) {
			swap(vertices[0], vertices[1]);
		}
	} else if (vertices[1][Y] == vertices[2][Y]) {
		if (vertices[1][X] < vertices[2][X]) {
			swap(vertices[1], vertices[2]);
		}
	} else if ((vertices[0][X] - vertices[2][X])*(vertices[1][Y] - vertices[2][Y]) / (vertices[0][Y] - vertices[2][Y]) + vertices[2][X] > vertices[1][X]) {
		swap(vertices[1], vertices[2]);
	}
}

void swap(float* v1, float* v2) {
	float tempx = v1[X];
	float tempy = v1[Y];
	float tempz = v1[Z];
	v1[X] = v2[X];
	v1[Y] = v2[Y];
	v1[Z] = v2[Z];
	v2[X] = tempx;
	v2[Y] = tempy;
	v2[Z] = tempz;
}

void getZplane(const GzCoord* vertices, float* A, float* B, float* C, float* D) {
	GzCoord E01;
	E01[X] = vertices[1][X] - vertices[0][X];
	E01[Y] = vertices[1][Y] - vertices[0][Y];
	E01[Z] = vertices[1][Z] - vertices[0][Z];
	GzCoord E12;
	E12[X] = vertices[2][X] - vertices[1][X];
	E12[Y] = vertices[2][Y] - vertices[1][Y];
	E12[Z] = vertices[2][Z] - vertices[1][Z];

	*A = E01[Y] * E12[Z] - E01[Z] * E12[Y];
	*B = E01[Z] * E12[X] - E01[X] * E12[Z];
	*C = E01[X] * E12[Y] - E01[Y] * E12[X];

	*D = -*A * (vertices[0][X]) - *B * (vertices[0][Y]) - *C * (vertices[0][Z]);
}

float getEdge(const float* start, const float* end, int x, int y, bool right) {
	return (end[Y] - start[Y]) * (x - start[X]) - (end[X] - start[X]) * (y - start[Y]);
}

void toScreen(const GzCoord* vert_world, GzMatrix Xsw, GzCoord* vert_screen) {
	float tri_world[4][3];
	float tri_screen[4][3];

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
			tri_screen[i][j] = 0;

	for (int i = 0; i < 3; i++) {
		tri_world[X][i] = vert_world[i][X];
		tri_world[Y][i] = vert_world[i][Y];
		tri_world[Z][i] = vert_world[i][Z];
		tri_world[3][i] = 1;
	}

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
			for (int m = 0; m < 4; m++)
				tri_screen[i][j] += Xsw[i][m] * tri_world[m][j];

	for (int i = 0; i < 3; i++) {
		vert_screen[i][X] = tri_screen[X][i] / tri_screen[3][i];
		vert_screen[i][Y] = tri_screen[Y][i] / tri_screen[3][i];
		vert_screen[i][Z] = tri_screen[Z][i] / tri_screen[3][i];
	}
}

int normalize(GzCoord vector) {
	float length = sqrt(vector[X] * vector[X] + vector[Y] * vector[Y] + vector[Z] * vector[Z]);
	vector[X] /= length;
	vector[Y] /= length;
	vector[Z] /= length;
	return GZ_SUCCESS;
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
		if (v[i].z < 0)
		{
			d_f = 1;
			break;
		}
		if ((v[i].x < 0 || v[i].x > xres) || (v[i].y < 0 || v[i].y > yres))
		{
			v_n++;
		}
	}
	if (v_n == 3)
	{
		d_f = 1;
	}
	return d_f;
}