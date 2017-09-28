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
	float d;
	float radian = radianOf(m_camera.FOV);
	d = 1 / (tan(radian / 2));

	// setup Xsp (scales NDC to screen)
	Xsp[0][0] = xres / 2;
	Xsp[0][1] = 0;
	Xsp[0][2] = 0;
	Xsp[0][3] = xres / 2;

	Xsp[1][0] = 0;
	Xsp[1][1] = -yres / 2;
	Xsp[1][2] = 0;
	Xsp[1][3] = yres / 2;

	Xsp[2][0] = 0;
	Xsp[2][1] = 0;
	Xsp[2][2] = MAXINT; // scale screen space "z" range
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
	GzCoord cl, cameraU, cameraX, cameraY, cameraZ;
	cl[X] = m_camera.lookat[X] - m_camera.position[X];
	cl[Y] = m_camera.lookat[Y] - m_camera.position[Y];
	cl[Z] = m_camera.lookat[Z] - m_camera.position[Z];
	normalize(cl);
	cameraZ[X] = cl[X];
	cameraZ[Y] = cl[Y];
	cameraZ[Z] = cl[Z];
	normalize(cameraZ);

	float upDotZ = m_camera.worldup[X] * cameraZ[X] + m_camera.worldup[Y] * cameraZ[Y] + m_camera.worldup[Z] * cameraZ[Z];
	cameraU[X] = m_camera.worldup[X] - upDotZ*cameraZ[X];
	cameraU[Y] = m_camera.worldup[Y] - upDotZ*cameraZ[Y];
	cameraU[Z] = m_camera.worldup[Z] - upDotZ*cameraZ[Z];
	normalize(cameraU);
	cameraY[X] = cameraU[X];
	cameraY[Y] = cameraU[Y];
	cameraY[Z] = cameraU[Z];
	normalize(cameraY);

	cameraX[X] = cameraY[Y] * cameraZ[Z] - cameraY[Z] * cameraZ[Y];
	cameraX[Y] = cameraY[Z] * cameraZ[X] - cameraY[X] * cameraZ[Z];
	cameraX[Z] = cameraY[X] * cameraZ[Y] - cameraY[Y] * cameraZ[X];
	normalize(cameraX);

	m_camera.Xiw[0][0] = cameraX[X];
	m_camera.Xiw[0][1] = cameraX[Y];
	m_camera.Xiw[0][2] = cameraX[Z];
	m_camera.Xiw[0][3] = -(cameraX[X] * m_camera.position[X] + cameraX[Y] * m_camera.position[Y] + cameraX[Z] * m_camera.position[Z]);

	m_camera.Xiw[1][0] = cameraY[X];
	m_camera.Xiw[1][1] = cameraY[Y];
	m_camera.Xiw[1][2] = cameraY[Z];
	m_camera.Xiw[1][3] = -(cameraY[X] * m_camera.position[X] + cameraY[Y] * m_camera.position[Y] + cameraY[Z] * m_camera.position[Z]);

	m_camera.Xiw[2][0] = cameraZ[X];
	m_camera.Xiw[2][1] = cameraZ[Y];
	m_camera.Xiw[2][2] = cameraZ[Z];
	m_camera.Xiw[2][3] = -(cameraZ[X] * m_camera.position[X] + cameraZ[Y] * m_camera.position[Y] + cameraZ[Z] * m_camera.position[Z]);

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
	GzCoord* model_vert;
	GzCoord* screen_vert;
	bool showInScreen = FALSE;

	screen_vert = (GzCoord*) malloc(sizeof(GzCoord) * 3);
	for (int i = 0; i < numParts; i++) {
		if (nameList[i] == GZ_NULL_TOKEN) {
			continue;
		}
		if (nameList[i] == GZ_POSITION) {
			model_vert = (GzCoord*) valueList[i];
			toScreen(model_vert, Ximage[matlevel - 1], screen_vert);
		}
	}
	
	for (int i = 0; i < 3; i++) {
		if (screen_vert[i][X] >= 0 && screen_vert[i][X] < xres &&
			screen_vert[i][Y] >= 0 && screen_vert[i][Y] < yres) {
			showInScreen = TRUE;
			break;
		}
	}

	if (screen_vert[0][Z] > 0 && screen_vert[1][Z] > 0 && screen_vert[2][Z] > 0 && showInScreen) {
		setupTriangle(screen_vert);
		LEE(screen_vert);
	}
	return GZ_SUCCESS;
}

void GzRender::LEE(GzCoord* vertices) {
	GzIntensity red, green, blue, alpha;
	GzDepth fb_z;
	float A, B, C, D;
	int u, d, l, r;
	bool e01_r, e12_r, e20_r;

	u = floor(vertices[0][Y]);
	d = ceil(vertices[1][Y] > vertices[2][Y] ? vertices[1][Y] : vertices[2][Y]);
	l = floor(min(min(vertices[0][X], vertices[1][X]), vertices[2][X]));
	r = ceil(max(max(vertices[0][X], vertices[1][X]), vertices[2][X]));

	if (vertices[0][Y] == vertices[1][Y] || vertices[1][Y] < vertices[2][Y]) {
		e01_r = true;
		e12_r = true;
		e20_r = false;
	} else {
		e01_r = true;
		e12_r = false;
		e20_r = false;
	}
	
	getZplane(vertices, &A, &B, &C, &D);
	for (int j = u; j < d; j++) {
		if (j < 0 || j > xres) {
			continue;
		}
		for (int i = l; i < r; i++) {
			if (i < 0 || i > yres) {
				continue;
			}
			float e01 = getEdge(vertices[0], vertices[1], i, j, e01_r);
			float e12 = getEdge(vertices[1], vertices[2], i, j, e12_r);
			float e20 = getEdge(vertices[2], vertices[0], i, j, e20_r);
			if (e01 > 0 && e12 > 0 && e20 > 0 || e01 < 0 && e12 < 0 && e20 < 0) {
				float coord_z = (-A * i - B * j - D) / C;
				GzGet(i, j, &red, &green, &blue, &alpha, &fb_z);
				if (coord_z > 0 && coord_z < fb_z) {
					red = ctoi(flatcolor[0]);
					green = ctoi(flatcolor[1]);
					blue = ctoi(flatcolor[2]);
					fb_z = coord_z;
					GzPut(i, j, red, green, blue, alpha, fb_z);
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
	float tempX = v1[X];
	float tempY = v1[Y];
	float tempZ = v1[Z];
	v1[X] = v2[X];
	v1[Y] = v2[Y];
	v1[Z] = v2[Z];
	v2[X] = tempX;
	v2[Y] = tempY;
	v2[Z] = tempZ;
}

void getZplane(const GzCoord* vertices, float* A, float* B, float* C, float* D) {
	GzCoord e01, e12;
	e01[X] = vertices[1][X] - vertices[0][X];
	e01[Y] = vertices[1][Y] - vertices[0][Y];
	e01[Z] = vertices[1][Z] - vertices[0][Z];

	e12[X] = vertices[2][X] - vertices[1][X];
	e12[Y] = vertices[2][Y] - vertices[1][Y];
	e12[Z] = vertices[2][Z] - vertices[1][Z];

	*A = e01[Y] * e12[Z] - e01[Z] * e12[Y];
	*B = e01[Z] * e12[X] - e01[X] * e12[Z];
	*C = e01[X] * e12[Y] - e01[Y] * e12[X];
	*D = -*A * (vertices[0][X]) - *B * (vertices[0][Y]) - *C * (vertices[0][Z]);
}

float getEdge(const float* start, const float* end, int x, int y, bool right) {
	return (end[Y] - start[Y]) * (x - start[X]) - (end[X] - start[X]) * (y - start[Y]);
}

void toScreen(const GzCoord* model_vert, GzMatrix Xsw, GzCoord* screen_vert) {
	float world_tri[4][3];
	float screen_tri[4][3];

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
			screen_tri[i][j] = 0;

	for (int i = 0; i < 3; i++) {
		world_tri[X][i] = model_vert[i][X];
		world_tri[Y][i] = model_vert[i][Y];
		world_tri[Z][i] = model_vert[i][Z];
		world_tri[3][i] = 1;
	}

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
			for (int m = 0; m < 4; m++)
				screen_tri[i][j] += Xsw[i][m] * world_tri[m][j];

	for (int i = 0; i < 3; i++) {
		screen_vert[i][X] = screen_tri[X][i] / screen_tri[3][i];
		screen_vert[i][Y] = screen_tri[Y][i] / screen_tri[3][i];
		screen_vert[i][Z] = screen_tri[Z][i] / screen_tri[3][i];
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
		if (v[i].z < 0) {
			d_f = 1;
			break;
		}
		if ((v[i].x < 0 || v[i].x > xres) || (v[i].y < 0 || v[i].y > yres)) {
			v_n++;
		}
	}
	if (v_n == 3) {
		d_f = 1;
	}
	return d_f;
}