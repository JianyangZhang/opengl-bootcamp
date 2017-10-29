/* CS580 Homework 3 */
#include	"stdafx.h"
#include	"stdio.h"
#include	"math.h"
#include	"rend.h"

#define PI (float) 3.14159265358979323846

int GzRender::GzRotXMat(float degree, GzMatrix mat)
{
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
	if (mat == NULL) { return GZ_FAILURE; }
	mat[0][0] = 1; mat[0][1] = 0; mat[0][2] = 0; mat[0][3] = translate[X];

	mat[1][0] = 0; mat[1][1] = 1; mat[1][2] = 0; mat[1][3] = translate[Y];

	mat[2][0] = 0; mat[2][1] = 0; mat[2][2] = 1; mat[2][3] = translate[Z];

	mat[3][0] = 0; mat[3][1] = 0; mat[3][2] = 0; mat[3][3] = 1;
	return GZ_SUCCESS;
}


int GzRender::GzScaleMat(GzCoord scale, GzMatrix mat)
{
	if (mat == NULL) { return GZ_FAILURE; }
	mat[0][0] = scale[X];      mat[0][1] = 0;           mat[0][2] = 0;          mat[0][3] = 0;

	mat[1][0] = 0;             mat[1][1] = scale[Y];    mat[1][2] = 0;          mat[1][3] = 0;

	mat[2][0] = 0;             mat[2][1] = 0;           mat[2][2] = scale[Z];   mat[2][3] = 0;

	mat[3][0] = 0;             mat[3][1] = 0;           mat[3][2] = 0;          mat[3][3] = 1;

	return GZ_SUCCESS;
}


GzRender::GzRender(int xRes, int yRes)
{
	xres = xRes;
	yres = yRes;
	framebuffer = (char*) malloc(3 * sizeof(char) * xRes * yRes);
	pixelbuffer = (GzPixel*) malloc(sizeof(GzPixel) * xRes * yRes);

	matlevel = 0;
	float d;
	float radian = radianOf(m_camera.FOV);
	d = 1 / (tan(radian / 2));

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
	Xsp[2][2] = MAXINT;
	Xsp[2][3] = 0;

	Xsp[3][0] = 0;
	Xsp[3][1] = 0;
	Xsp[3][2] = 0;
	Xsp[3][3] = 1;

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

	interp_mode = GZ_RGB_COLOR;
	numlights = 0;
	GzColor dKa = DEFAULT_AMBIENT;
	GzColor dKd = DEFAULT_DIFFUSE;
	GzColor dKs = DEFAULT_SPECULAR;
	Ka[0] = dKa[0];
	Ka[1] = dKa[1];
	Ka[2] = dKa[2];
	Kd[0] = dKd[0];
	Kd[1] = dKd[1];
	Kd[2] = dKd[2];
	Ks[0] = dKs[0];
	Ks[1] = dKs[1];
	Ks[2] = dKs[2];
	tex_fun = NULL;
}

GzRender::~GzRender()
{
	free(pixelbuffer);
	free(framebuffer);
}

int GzRender::GzDefault()
{
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
	float rad = radianOf(m_camera.FOV / 2);

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
	if (matlevel >= MATLEVELS) {
		return GZ_FAILURE;
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			Ximage[matlevel][i][j] = 0;
			Xnorm[matlevel][i][j] = 0;
		}
	}

	if (matlevel == 0) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				Ximage[matlevel][i][j] = matrix[i][j];
				Xnorm[matlevel][i][j] = 0;
			}
		}
		Xnorm[matlevel][0][0] = 1;
		Xnorm[matlevel][1][1] = 1;
		Xnorm[matlevel][2][2] = 1;
		Xnorm[matlevel][3][3] = 1;
	} else {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				for (int m = 0; m < 4; m++) {
					Ximage[matlevel][i][j] += Ximage[matlevel - 1][i][m] * matrix[m][j];
				}
			}
		}

		if (matlevel == 1) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					Xnorm[matlevel][i][j] = 0;
				}
			}
			Xnorm[matlevel][0][0] = 1;
			Xnorm[matlevel][1][1] = 1;
			Xnorm[matlevel][2][2] = 1;
			Xnorm[matlevel][3][3] = 1;
		} else {
			float k;
			GzMatrix R;
			k = 1 / sqrt(matrix[0][0] * matrix[0][0] + matrix[1][0] * matrix[1][0] + matrix[2][0] * matrix[2][0]);
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					R[i][j] = matrix[i][j] * k;
				}
				R[i][3] = 0;
				R[3][i] = 0;
			}
			R[3][3] = 1;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					for (int m = 0; m < 4; m++) {
						Xnorm[matlevel][i][j] += Xnorm[matlevel - 1][i][m] * R[m][j];
					}
				}
			}
		}
	}
	matlevel++;
	return GZ_SUCCESS;
}

int GzRender::GzPopMatrix()
{
	if (matlevel <= 0) {
		return GZ_FAILURE;
	}
	matlevel--;
	return GZ_SUCCESS;
}

int GzRender::GzPut(int i, int j, GzIntensity r, GzIntensity g, GzIntensity b, GzIntensity a, GzDepth z)
{
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


int GzRender::GzGet(int i, int j, GzIntensity *r, GzIntensity *g, GzIntensity *b, GzIntensity *a, GzDepth *z)
{
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


int GzRender::GzFlushDisplay2File(FILE* outfile)
{
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

int GzRender::GzFlushDisplay2FrameBuffer()
{
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
			GzColor* c = (GzColor*) valueList[0];
			flatcolor[0] = (*c)[0];
			flatcolor[1] = (*c)[1];
			flatcolor[2] = (*c)[2];
		}
		if (nameList[i] == GZ_DIRECTIONAL_LIGHT) {
			if (numlights >= MAX_LIGHTS) { return GZ_FAILURE; }
			lights[numlights] = *(GzLight*) valueList[i];
			numlights++;
		}
		if (nameList[i] == GZ_AMBIENT_LIGHT) {
			ambientlight = *(GzLight*) valueList[i];
		}
		if (nameList[i] == GZ_DIFFUSE_COEFFICIENT) {
			GzColor* diffuseColor = (GzColor*) valueList[i];
			float diffuseR = diffuseColor[0][0];
			float diffuseG = diffuseColor[0][1];
			float diffuseB = diffuseColor[0][2];
			Kd[0] = diffuseR;
			Kd[1] = diffuseG;
			Kd[2] = diffuseB;
		}
		if (nameList[i] == GZ_INTERPOLATE) {
			interp_mode = *(int*) valueList[i];
		}
		if (nameList[i] == GZ_AMBIENT_COEFFICIENT) {
			GzColor* ambientColor = (GzColor*) valueList[i];
			float ambientR = ambientColor[0][0];
			float ambientG = ambientColor[0][1];
			float ambientB = ambientColor[0][2];
			Ka[0] = ambientR;
			Ka[1] = ambientG;
			Ka[2] = ambientB;
		}
		if (nameList[i] == GZ_SPECULAR_COEFFICIENT) {
			GzColor* specularColor = (GzColor*) valueList[i];
			float specularR = specularColor[0][0];
			float specularG = specularColor[0][1];
			float specularB = specularColor[0][2];
			Ks[0] = specularR;
			Ks[1] = specularG;
			Ks[2] = specularB;
		}
		if (nameList[i] == GZ_DISTRIBUTION_COEFFICIENT) {
			spec = *(float*) valueList[i];
		}
		if (nameList[i] == GZ_TEXTURE_MAP) {
			tex_fun = (GzTexture) (valueList[i]);
		}
	}
	return GZ_SUCCESS;
}

int GzRender::GzPutTriangle(int	numParts, GzToken *nameList, GzPointer *valueList) {
	GzCoord* model_vert;
	GzCoord* model_normal;
	GzCoord* screen_vert;
	GzCoord* screen_normal;
	GzTextureIndex* uv;
	GzTextureIndex* uvCoord;
	float vz;
	bool showInScreen = FALSE;

	screen_vert = (GzCoord*) malloc(sizeof(GzCoord) * 3);
	screen_normal = (GzCoord*) malloc(sizeof(GzCoord) * 3);
	uvCoord = (GzTextureIndex*) malloc(sizeof(GzTextureIndex) * 2);
	for (int i = 0; i < numParts; i++) {
		if (nameList[i] == GZ_NULL_TOKEN) { continue; }
		if (nameList[i] == GZ_POSITION) {
			model_vert = (GzCoord*) valueList[i];
			vertToScreen(model_vert, Ximage[matlevel - 1], screen_vert);
		}
		if (nameList[i] == GZ_NORMAL) {
			model_normal = (GzCoord*) valueList[i];
			normalize(model_normal[0]);
			normalize(model_normal[1]);
			normalize(model_normal[2]);
			normalToScreen(model_normal, Xnorm[matlevel - 1], screen_normal);
		}
		if (nameList[i] == GZ_TEXTURE_INDEX) {
			uv = (GzTextureIndex*) valueList[i];
			for (int i = 0; i < 3; i++) {
				vz = screen_vert[i][Z] / (INT_MAX - screen_vert[i][Z]);
				uvCoord[i][0] = uv[i][0] / (vz + 1);
				uvCoord[i][1] = uv[i][1] / (vz + 1);
			}
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
		setupTriangle(screen_vert, screen_normal, uvCoord);
		LEE(screen_vert, screen_normal, uvCoord);
	}
	return GZ_SUCCESS;
}

void GzRender::LEE(GzCoord* vertices, GzCoord* normals, GzTextureIndex* uvCoord) {
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
			GzCoord flag = { i, j, 1 };
			float e01 = getEdge(vertices[0], vertices[1], i, j, e01_r);
			float e12 = getEdge(vertices[1], vertices[2], i, j, e12_r);
			float e20 = getEdge(vertices[2], vertices[0], i, j, e20_r);
			float area = getArea(vertices[0], vertices[1], vertices[2]);
			if (e01 > 0 && e12 > 0 && e20 > 0 || e01 < 0 && e12 < 0 && e20 < 0) {
				float coord_z = (-A * i - B * j - D) / C;
				float A0 = getArea(vertices[1], flag, vertices[2]);
				float A1 = getArea(vertices[0], flag, vertices[2]);
				float A2 = getArea(vertices[0], flag, vertices[1]);
				GzGet(i, j, &red, &green, &blue, &alpha, &fb_z);

				if (coord_z > 0 && coord_z < fb_z) {
					if (interp_mode == GZ_FLAT) {
						red = ctoi(flatcolor[0]);
						green = ctoi(flatcolor[1]);
						blue = ctoi(flatcolor[2]);
						fb_z = coord_z;
					}
					if (interp_mode == GZ_COLOR) {
						GzColor cv0, cv1, cv2;

						getTexture(cv0, normals[0]);
						getTexture(cv1, normals[1]);
						getTexture(cv2, normals[2]);

						GzTextureIndex UV;
						UV[0] = (A0 * uvCoord[0][0] + A1 * uvCoord[1][0] + A2 * uvCoord[2][0]) / area;
						UV[1] = (A0 * uvCoord[0][1] + A1 * uvCoord[1][1] + A2 * uvCoord[2][1]) / area;

						GzTextureIndex uv;
						float vz = coord_z / (INT_MAX - coord_z);
						uv[0] = UV[0] * (vz + 1);
						uv[1] = UV[1] * (vz + 1);


						float interp_r = (A0 * cv0[0] + A1 * cv1[0] + A2 * cv2[0]) / area;
						float interp_g = (A0 * cv0[1] + A1 * cv1[1] + A2 * cv2[1]) / area;
						float interp_b = (A0 * cv0[2] + A1 * cv1[2] + A2 * cv2[2]) / area;
						interp_r = interp_r > 1.0 ? 1 : interp_r;
						interp_g = interp_g > 1.0 ? 1 : interp_g;
						interp_b = interp_b > 1.0 ? 1 : interp_b;
						red = (GzIntensity) ctoi(interp_r);
						green = (GzIntensity) ctoi(interp_g);
						blue = (GzIntensity) ctoi(interp_b);
						fb_z = coord_z;
					}
					if (interp_mode == GZ_NORMALS) {
						GzCoord interp_normal;
						GzColor color;

						float area0 = getArea(vertices[1], flag, vertices[2]);
						float area1 = getArea(vertices[0], flag, vertices[2]);
						float area2 = getArea(vertices[0], flag, vertices[1]);
						interp_normal[X] = (area0 * normals[0][X] + area1 * normals[1][X] + area2 * normals[2][X]) / area;
						interp_normal[Y] = (area0 * normals[0][Y] + area1 * normals[1][Y] + area2 * normals[2][Y]) / area;
						interp_normal[Z] = (area0 * normals[0][Z] + area1 * normals[1][Z] + area2 * normals[2][Z]) / area;
						normalize(interp_normal);

						GzTextureIndex UV;
						UV[0] = (A0 * uvCoord[0][0] + A1 * uvCoord[1][0] + A2 * uvCoord[2][0]) / area;
						UV[1] = (A0 * uvCoord[0][1] + A1 * uvCoord[1][1] + A2 * uvCoord[2][1]) / area;

						GzTextureIndex uv;
						float uv_z = coord_z / (INT_MAX - coord_z);
						uv[0] = UV[0] * (uv_z + 1);
						uv[1] = UV[1] * (uv_z + 1);

						GzColor textureColor;
						if (tex_fun != NULL) {
							tex_fun(uv[0], uv[1], textureColor);
						}

						if (tex_fun != NULL) {
							Ka[RED] = Kd[RED] = textureColor[RED];
							Ka[GREEN] = Kd[GREEN] = textureColor[GREEN];
							Ka[BLUE] = Kd[BLUE] = textureColor[BLUE];
						}

						getColor(color, interp_normal);
						if (color[0] > 1.0) color[0] = 1.0;
						if (color[1] > 1.0) color[1] = 1.0;
						if (color[2] > 1.0) color[2] = 1.0;
						red = (GzIntensity) ctoi(color[0]);
						green = (GzIntensity) ctoi(color[1]);
						blue = (GzIntensity) ctoi(color[2]);
						fb_z = coord_z;
					}
					GzPut(i, j, red, green, blue, alpha, fb_z);
				}
			}
		}
	}
}

void setupTriangle(GzCoord* screen_vert, GzCoord* screen_normal, GzTextureIndex* uvCoord) {
	for (int i = 2; i > 0; i--) {
		if (screen_vert[i][Y] < screen_vert[i - 1][Y]) {
			swap(screen_vert[i], screen_vert[i - 1]);
			swap(screen_normal[i], screen_normal[i - 1]);
			swapUV(uvCoord[i], uvCoord[i - 1]);
		}
	}
	if (screen_vert[2][Y] < screen_vert[1][Y]) {
		swap(screen_vert[2], screen_vert[1]);
		swap(screen_normal[2], screen_normal[1]);
		swapUV(uvCoord[2], uvCoord[1]);
	}
	if (screen_vert[0][Y] == screen_vert[1][Y]) {
		if (screen_vert[0][X] > screen_vert[1][X]) {
			swap(screen_vert[0], screen_vert[1]);
			swap(screen_normal[0], screen_normal[1]);
			swapUV(uvCoord[0], uvCoord[1]);
		}
	} else if (screen_vert[1][Y] == screen_vert[2][Y]) {
		if (screen_vert[1][X] < screen_vert[2][X]) {
			swap(screen_vert[1], screen_vert[2]);
			swap(screen_normal[1], screen_normal[2]);
			swapUV(uvCoord[1], uvCoord[2]);
		}
	} else if ((screen_vert[0][X] - screen_vert[2][X])*(screen_vert[1][Y] - screen_vert[2][Y]) / (screen_vert[0][Y] - screen_vert[2][Y]) + screen_vert[2][X] > screen_vert[1][X]) {
		swap(screen_vert[1], screen_vert[2]);
		swap(screen_normal[1], screen_normal[2]);
		swapUV(uvCoord[1], uvCoord[2]);
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

void swapUV(float* v1, float* v2) {
	float tempU = v1[0];
	float tempV = v1[1];
	v1[0] = v2[0];
	v1[1] = v2[1];
	v2[0] = tempU;
	v2[1] = tempV;
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

void vertToScreen(const GzCoord* model_vert, GzMatrix Xsw, GzCoord* screen_vert) {
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

void normalToScreen(const GzCoord* model_normal, GzMatrix Xsw, GzCoord* screen_normal) {
	float temp_normal[4][3];
	float trans_normal[4][3];
	for (int i = 0; i < 3; i++) {
		trans_normal[0][i] = model_normal[i][0];
		trans_normal[1][i] = model_normal[i][1];
		trans_normal[2][i] = model_normal[i][2];
		trans_normal[3][i] = 1;
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			temp_normal[i][j] = 0;
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 4; k++) {
				temp_normal[i][j] += Xsw[i][k] * trans_normal[k][j];
			}
		}
	}
	for (int i = 0; i < 3; i++) {
		screen_normal[i][0] = temp_normal[0][i] / temp_normal[3][i];
		screen_normal[i][1] = temp_normal[1][i] / temp_normal[3][i];
		screen_normal[i][2] = temp_normal[2][i] / temp_normal[3][i];
	}
	for (int i = 0; i < 3; i++) {
		normalize(screen_normal[i]);
	}
}

int normalize(GzCoord vector) {
	float length = sqrt(vector[X] * vector[X] + vector[Y] * vector[Y] + vector[Z] * vector[Z]);
	vector[X] /= length;
	vector[Y] /= length;
	vector[Z] /= length;
	return GZ_SUCCESS;
}

float dotProduct(GzCoord v1, GzCoord v2) {
	return v1[X] * v2[X] + v1[Y] * v2[Y] + v1[Z] * v2[Z];
}

Vertex crossProduct(const Vertex& a, const Vertex& b) {
	Vertex result;
	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return result;
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

float getArea(GzCoord v0, GzCoord v1, GzCoord v2) {
	float area = (v0[X] * v1[Y] + v0[Y] * v2[X] + v1[X] * v2[Y] - v1[Y] * v2[X] - v0[Y] * v1[X] - v0[X] * v2[Y]) / 2;
	if (area < 0) {
		return -area;
	} else {
		return area;
	}
}

int GzRender::getColor(GzColor color, GzCoord norm) {
	GzColor ambientIntensity, diffuseIntensity, specularIntensity, diffuseSum = { 0, 0, 0 }, specularSum = { 0, 0, 0 };
	GzCoord eye, negativeN = { -norm[X], -norm[Y], -norm[Z] };
	GzCoord* reflect = (GzCoord*) malloc(sizeof(GzCoord) * numlights);
	int* checker = (int*) malloc(sizeof(int) * numlights);
	float NL, NE, RE;

	eye[X] = 0;
	eye[Y] = 0;
	eye[Z] = -1;
	normalize(eye);
	normalize(norm);
	NE = dotProduct(norm, eye);

	for (int i = 0; i < numlights; i++) {
		NL = dotProduct(norm, lights[i].direction);
		if (NL >= 0 && NE >= 0) {
			checker[i] = 1;
			reflect[i][X] = 2 * NL * norm[X] - lights[i].direction[X];
			reflect[i][Y] = 2 * NL * norm[Y] - lights[i].direction[Y];
			reflect[i][Z] = 2 * NL * norm[Z] - lights[i].direction[Z];
			normalize(reflect[i]);
		} else if (NL < 0 && NE < 0) {
			checker[i] = -1;
			reflect[i][X] = 2 * NL * (-norm[X]) - lights[i].direction[X];
			reflect[i][Y] = 2 * NL * (-norm[Y]) - lights[i].direction[Y];
			reflect[i][Z] = 2 * NL * (-norm[Z]) - lights[i].direction[Z];
			normalize(reflect[i]);
		} else {
			checker[i] = 0;
			continue;
		}
	}
	ambientIntensity[0] = Ka[0] * ambientlight.color[0];
	ambientIntensity[1] = Ka[1] * ambientlight.color[1];
	ambientIntensity[2] = Ka[2] * ambientlight.color[2];

	for (int i = 0; i < numlights; i++) {
		if (checker[i] == 0) continue;
		if (checker[i] == 1) {
			diffuseSum[0] += lights[i].color[0] * dotProduct(norm, lights[i].direction);
			diffuseSum[1] += lights[i].color[1] * dotProduct(norm, lights[i].direction);
			diffuseSum[2] += lights[i].color[2] * dotProduct(norm, lights[i].direction);
		} else if (checker[i] == -1) {
			diffuseSum[0] += lights[i].color[0] * dotProduct(negativeN, lights[i].direction);
			diffuseSum[1] += lights[i].color[1] * dotProduct(negativeN, lights[i].direction);
			diffuseSum[2] += lights[i].color[2] * dotProduct(negativeN, lights[i].direction);
		}
	}
	diffuseIntensity[0] = Kd[0] * diffuseSum[0];
	diffuseIntensity[1] = Kd[1] * diffuseSum[1];
	diffuseIntensity[2] = Kd[2] * diffuseSum[2];


	for (int i = 0; i < numlights; i++) {
		if (checker[i] == 0) { continue; }
		RE = dotProduct(reflect[i], eye);
		RE = RE < 0 ? 0 : RE;
		specularSum[0] += lights[i].color[0] * pow(RE, spec);
		specularSum[1] += lights[i].color[1] * pow(RE, spec);
		specularSum[2] += lights[i].color[2] * pow(RE, spec);
	}
	specularIntensity[0] = Ks[0] * specularSum[0];
	specularIntensity[1] = Ks[1] * specularSum[1];
	specularIntensity[2] = Ks[2] * specularSum[2];

	color[0] = specularIntensity[0] + diffuseIntensity[0] + ambientIntensity[0];
	color[1] = specularIntensity[1] + diffuseIntensity[1] + ambientIntensity[1];
	color[2] = specularIntensity[2] + diffuseIntensity[2] + ambientIntensity[2];
	return GZ_SUCCESS;
}

int GzRender::getTexture(GzColor color, GzCoord norm) {
	GzCoord* reflect = (GzCoord*) malloc(sizeof(GzCoord) *numlights);
	int* checker = (int*) malloc(sizeof(int) *numlights);
	GzCoord eye, negativeN = { -norm[X], -norm[Y], -norm[Z] };
	float NL, NE, RE;
	
	eye[X] = 0;
	eye[Y] = 0;
	eye[Z] = -1;
	normalize(eye);
	normalize(norm);
	NE = dotProduct(norm, eye);

	for (int i = 0; i < numlights; i++) {
		NL = dotProduct(norm, lights[i].direction);
		if (NL >= 0 && NE >= 0) {
			checker[i] = 1;
			reflect[i][X] = 2 * NL*norm[X] - lights[i].direction[X];
			reflect[i][Y] = 2 * NL*norm[Y] - lights[i].direction[Y];
			reflect[i][Z] = 2 * NL*norm[Z] - lights[i].direction[Z];
			normalize(reflect[i]);
		} else if (NL < 0 && NE < 0) {
			checker[i] = -1;
			reflect[i][X] = 2 * NL*(-norm[X]) - lights[i].direction[X];
			reflect[i][Y] = 2 * NL*(-norm[Y]) - lights[i].direction[Y];
			reflect[i][Z] = 2 * NL*(-norm[Z]) - lights[i].direction[Z];
			normalize(reflect[i]);
		} else {
			checker[i] = 0;
			continue;
		}
	}

	GzColor diffuseSum = { 0, 0, 0 };
	for (int i = 0; i < numlights; ++i) {
		if (checker[i] == 0) continue;
		if (checker[i] == 1) {
			diffuseSum[0] += lights[i].color[0] * dotProduct(norm, lights[i].direction);
			diffuseSum[1] += lights[i].color[1] * dotProduct(norm, lights[i].direction);
			diffuseSum[2] += lights[i].color[2] * dotProduct(norm, lights[i].direction);
		} else if (checker[i] == -1) {
			diffuseSum[0] += lights[i].color[0] * dotProduct(negativeN, lights[i].direction);
			diffuseSum[1] += lights[i].color[1] * dotProduct(negativeN, lights[i].direction);
			diffuseSum[2] += lights[i].color[2] * dotProduct(negativeN, lights[i].direction);
		}
	}

	GzColor specularSum = { 0, 0, 0 };
	for (int i = 0; i < numlights; ++i) {
		if (checker[i] == 0) continue;
		RE = dotProduct(reflect[i], eye);
		if (RE < 0) { RE = 0; }
		if (RE > 1) { RE = 1; }
		specularSum[0] += lights[i].color[0] * pow(RE, spec);
		specularSum[2] += lights[i].color[2] * pow(RE, spec);
	}

	color[0] = specularSum[0] + diffuseSum[0];
	color[1] = specularSum[1] + diffuseSum[1];
	color[2] = specularSum[2] + diffuseSum[2];

	return GZ_SUCCESS;
}