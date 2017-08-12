#include "ObjectGL.hpp"
#include <GL/glut.h>

// ======================== 
// ======  ObjectGL  ======
// ========================

void ObjectGL::SetRotation(float _x, float _y, float _z)
{
	rot[0] = _x;
	while (rot[0] >= 360.0f) { rot[0] -= 360.0f; }
	while (rot[0] < 360.0f) { rot[0] += 360.0f; }

	rot[1] = _y;
	while (rot[1] >= 360.0f) { rot[1] -= 360.0f; }
	while (rot[1] < 360.0f) { rot[1] += 360.0f; }

	rot[2] = _z;
	while (rot[2] >= 360.0f) { rot[2] -= 360.0f; }
	while (rot[2] < 360.0f) { rot[2] += 360.0f; }
}

void ObjectGL::Rotate(float _x, float _y, float _z)
{
	SetRotation(rot[0] + _x, rot[1] + _y, rot[2] + _z);
}

void ObjectGL::CalculateOffset()
{
	posOffset[0] = pos[0] - anchor[0];
	posOffset[1] = pos[1] - anchor[1];
	posOffset[2] = pos[2] - anchor[2];

	calculateOffset = false;
	calculateVertices = true;
}

// ======================== 
// =======  CubeGL  =======
// ========================

CubeGL::CubeGL(float _x, float _y, float _z, float _w, float _h, float _d)
{
	SetPosition(_x, _y, _z);
	SetAnchor(_x, _y, _z);
	SetRotation(0.0f, 0.0f, 0.0f);
	SetScale(1.0f, 1.0f, 1.0f);
	SetColor(1.0f, 1.0f, 1.0f);
	SetSize(_w, _h, _d);
}

void CubeGL::SetPosition(float _x, float _y, float _z, bool _setAnchor/* = true*/)
{
	if (_setAnchor)
		SetAnchor(_x, _y, _z);

	pos[0] = _x;
	pos[1] = _y;
	pos[2] = _z;

	calculateOffset = true;
}

void CubeGL::Move(float _x, float _y, float _z, bool _moveAnchor/* = true*/)
{
	if (_moveAnchor)
	{
		MoveAnchor(_x, _y, _z);
		SetPosition(pos[0] + _x, pos[1] + _y, pos[2] + _z, false);
	}
	else
		SetPosition(pos[0] + _x, pos[1] + _y, pos[2] + _z, _moveAnchor);
}

void CubeGL::SetAnchor(float _x, float _y, float _z)
{
	anchor[0] = _x;
	anchor[1] = _y;
	anchor[2] = _z;

	calculateOffset = true;
}

void CubeGL::MoveAnchor(float _x, float _y, float _z)
{
	SetPosition(anchor[0] + _x, anchor[1] + _y, anchor[2] + _z);
}

void CubeGL::SetColor(int _vertex, float _r, float _g, float _b)
{
	if (_r < 0.0f)
		col[_vertex][0] = 0.0f;
	else if (_r > 1.0f)
		col[_vertex][0] = 1.0f;
	else
		col[_vertex][0] = _r;

	if (_g < 0.0f)
		col[_vertex][1] = 0.0f;
	else if (_g > 1.0f)
		col[_vertex][1] = 1.0f;
	else
		col[_vertex][1] = _g;

	if (_b < 0.0f)
		col[_vertex][2] = 0.0f;
	else if (_b > 1.0f)
		col[_vertex][2] = 1.0f;
	else
		col[_vertex][2] = _b;
}

void CubeGL::SetColor(float _r, float _g, float _b)
{
	for (int i = 0; i < 8; i++)
	{
		SetColor(i, _r, _g, _b);
	}
}

void CubeGL::SetSize(float _w, float _h, float _d)
{
	sizeBase[0] = (_w > 0.0f ? _w : 0.0f);
	sizeBase[1] = (_h > 0.0f ? _h : 0.0f);
	sizeBase[2] = (_d > 0.0f ? _d : 0.0f);

	calculateSize = true;
}

void CubeGL::SetScale(float _x, float _y, float _z)
{
	scale[0] = _x;
	scale[1] = _y;
	scale[2] = _z;

	calculateSize = true;
}

void CubeGL::SetScale(float _scale)
{
	scale[0] = scale[1] = scale[2] = _scale;

	calculateSize = true;
}

void CubeGL::Scale(float _scale)
{
	scale[0] *= _scale;
	scale[1] *= _scale;
	scale[2] *= _scale;

	calculateSize = true;
}

void CubeGL::CalculateSize()
{
	sizeHalf[0] = sizeBase[0] * scale[0] / 2.0f;
	sizeHalf[1] = sizeBase[1] * scale[1] / 2.0f;
	sizeHalf[2] = sizeBase[2] * scale[2] / 2.0f;

	calculateSize = false;
	calculateVertices = true;
}

void CubeGL::CalculateVertices()
{
	// Left Bottom Back
	vert[0][0] = posOffset[0] - sizeHalf[0];
	vert[0][1] = posOffset[1] - sizeHalf[1];
	vert[0][2] = posOffset[2] - sizeHalf[2];

	// Left Bottom Front
	vert[1][0] = posOffset[0] - sizeHalf[0];
	vert[1][1] = posOffset[1] - sizeHalf[1];
	vert[1][2] = posOffset[2] + sizeHalf[2];

	// Left Top Back
	vert[2][0] = posOffset[0] - sizeHalf[0];
	vert[2][1] = posOffset[1] + sizeHalf[1];
	vert[2][2] = posOffset[2] - sizeHalf[2];

	// Left Top Front
	vert[3][0] = posOffset[0] - sizeHalf[0];
	vert[3][1] = posOffset[1] + sizeHalf[1];
	vert[3][2] = posOffset[2] + sizeHalf[2];

	// Right Bottom Back
	vert[4][0] = posOffset[0] + sizeHalf[0];
	vert[4][1] = posOffset[1] - sizeHalf[1];
	vert[4][2] = posOffset[2] - sizeHalf[2];

	// Right Bottom Front
	vert[5][0] = posOffset[0] + sizeHalf[0];
	vert[5][1] = posOffset[1] - sizeHalf[1];
	vert[5][2] = posOffset[2] + sizeHalf[2];

	// Right Top Back
	vert[6][0] = posOffset[0] + sizeHalf[0];
	vert[6][1] = posOffset[1] + sizeHalf[1];
	vert[6][2] = posOffset[2] - sizeHalf[2];

	// Right Top Front
	vert[7][0] = posOffset[0] + sizeHalf[0];
	vert[7][1] = posOffset[1] + sizeHalf[1];
	vert[7][2] = posOffset[2] + sizeHalf[2];
}

void CubeGL::Draw()
{
	if (calculateSize) CalculateSize();
	if (calculateOffset) CalculateOffset();
	if (calculateVertices) CalculateVertices();

	glPushMatrix();

	glTranslatef(anchor[0], anchor[1], anchor[2]);

	if (rot[0] > 0.0f) glRotatef(rot[0], 1.0f, 0.0f, 0.0f);
	if (rot[1] > 0.0f) glRotatef(rot[1], 0.0f, 1.0f, 0.0f);
	if (rot[2] > 0.0f) glRotatef(rot[2], 0.0f, 0.0f, 1.0f);

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 6; i++)
	{
		DrawFace(i);
	}
	glEnd();

	glPopMatrix();
}

void CubeGL::DrawFace(int _face)
{
	switch (_face)
	{
	case FACE_LEFT:
		DrawVertex(VERTEX_LEFT_BOTTOM_BACK);
		DrawVertex(VERTEX_LEFT_BOTTOM_FRONT);
		DrawVertex(VERTEX_LEFT_TOP_BACK);

		DrawVertex(VERTEX_LEFT_BOTTOM_FRONT);
		DrawVertex(VERTEX_LEFT_TOP_FRONT);
		DrawVertex(VERTEX_LEFT_TOP_BACK);
		break;

	case FACE_RIGHT:
		DrawVertex(VERTEX_RIGHT_BOTTOM_BACK);
		DrawVertex(VERTEX_RIGHT_BOTTOM_FRONT);
		DrawVertex(VERTEX_RIGHT_TOP_BACK);

		DrawVertex(VERTEX_RIGHT_BOTTOM_FRONT);
		DrawVertex(VERTEX_RIGHT_TOP_FRONT);
		DrawVertex(VERTEX_RIGHT_TOP_BACK);
		break;

	case FACE_BOTTOM:
		DrawVertex(VERTEX_LEFT_BOTTOM_BACK);
		DrawVertex(VERTEX_LEFT_BOTTOM_FRONT);
		DrawVertex(VERTEX_RIGHT_BOTTOM_BACK);

		DrawVertex(VERTEX_LEFT_BOTTOM_FRONT);
		DrawVertex(VERTEX_RIGHT_BOTTOM_BACK);
		DrawVertex(VERTEX_RIGHT_BOTTOM_FRONT);
		break;

	case FACE_TOP:
		DrawVertex(VERTEX_LEFT_TOP_BACK);
		DrawVertex(VERTEX_LEFT_TOP_FRONT);
		DrawVertex(VERTEX_RIGHT_TOP_BACK);

		DrawVertex(VERTEX_LEFT_TOP_FRONT);
		DrawVertex(VERTEX_RIGHT_TOP_BACK);
		DrawVertex(VERTEX_RIGHT_TOP_FRONT);
		break;

	case FACE_BACK:
		DrawVertex(VERTEX_LEFT_BOTTOM_BACK);
		DrawVertex(VERTEX_LEFT_TOP_BACK);
		DrawVertex(VERTEX_RIGHT_BOTTOM_BACK);

		DrawVertex(VERTEX_LEFT_TOP_BACK);
		DrawVertex(VERTEX_RIGHT_BOTTOM_BACK);
		DrawVertex(VERTEX_RIGHT_TOP_BACK);
		break;

	case FACE_FRONT:
		DrawVertex(VERTEX_LEFT_BOTTOM_FRONT);
		DrawVertex(VERTEX_LEFT_TOP_FRONT);
		DrawVertex(VERTEX_RIGHT_BOTTOM_FRONT);

		DrawVertex(VERTEX_LEFT_TOP_FRONT);
		DrawVertex(VERTEX_RIGHT_BOTTOM_FRONT);
		DrawVertex(VERTEX_RIGHT_TOP_FRONT);
		break;

	default:
		break;
	}
}

void CubeGL::DrawVertex(int _vertex)
{
	glColor3f(col[_vertex][0], col[_vertex][1], col[_vertex][2]);
	glNormal3f(norm[_vertex][0], norm[_vertex][1], norm[_vertex][2]);
	glVertex3f(vert[_vertex][0], vert[_vertex][1], vert[_vertex][2]);
}
