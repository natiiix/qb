#pragma once

class ObjectGL
{
protected:
	float pos[3];
	float posOffset[3];
	float anchor[3];
	float rot[3];
	float scale[3];

	bool calculateOffset;
	bool calculateSize;
	bool calculateVertices;

	void CalculateOffset();

public:
	void SetRotation(float _x, float _y, float _z);
	void Rotate(float _x, float _y, float _z);

	float GetX() { return pos[0]; };
	float GetY() { return pos[1]; };
	float GetZ() { return pos[2]; };

	virtual void SetPosition(float _x, float _y, float _z, bool _setAnchor = true) = 0;
	virtual void Move(float _x, float _y, float _z, bool _moveAnchor = true) = 0;
	virtual void SetAnchor(float _x, float _y, float _z) = 0;
	virtual void MoveAnchor(float _x, float _y, float _z) = 0;
	virtual void SetColor(int _vertex, float _r, float _g, float _b) = 0;
	virtual void SetColor(float _r, float _g, float _b) = 0;
	virtual void SetSize(float _w, float _h, float _d) = 0;
	virtual void SetScale(float _x, float _y, float _z) = 0;
	virtual void SetScale(float _scale) = 0;
	virtual void Scale(float _scale) = 0;
	virtual void Draw() = 0;
};

class CubeGL : public ObjectGL
{
private:
	float sizeBase[3];
	float sizeHalf[3];
	float col[8][3];
	float vert[8][3];

#define NORMLEN 0.57735026919f
	const float norm[8][3] =
	{
		{ -NORMLEN, -NORMLEN, -NORMLEN },
		{ -NORMLEN, -NORMLEN,  NORMLEN },
		{ -NORMLEN,  NORMLEN, -NORMLEN },
		{ -NORMLEN,  NORMLEN,  NORMLEN },
		{ NORMLEN, -NORMLEN, -NORMLEN },
		{ NORMLEN, -NORMLEN,  NORMLEN },
		{ NORMLEN,  NORMLEN, -NORMLEN },
		{ NORMLEN,  NORMLEN,  NORMLEN }
	};

	void CalculateSize();
	void CalculateVertices();

	void DrawFace(int _face);
	void DrawVertex(int _vertex);

public:
	CubeGL(float _x, float _y, float _z, float _w, float _h, float _d);
	void SetPosition(float _x, float _y, float _z, bool _setAnchor = true);
	void Move(float _x, float _y, float _z, bool _moveAnchor = true);
	void SetAnchor(float _x, float _y, float _z);
	void MoveAnchor(float _x, float _y, float _z);
	void SetColor(int _vertex, float _r, float _g, float _b);
	void SetColor(float _r, float _g, float _b);
	void SetSize(float _w, float _h, float _d);
	void SetScale(float _x, float _y, float _z);
	void SetScale(float _scale);
	void Scale(float _scale);
	void Draw();
};

#define FACE_LEFT 0
#define FACE_RIGHT 1
#define FACE_BOTTOM 2
#define FACE_TOP 3
#define FACE_BACK 4
#define FACE_FRONT 5

#define VERTEX_LEFT_BOTTOM_BACK 0
#define VERTEX_LEFT_BOTTOM_FRONT 1
#define VERTEX_LEFT_TOP_BACK 2
#define VERTEX_LEFT_TOP_FRONT 3
#define VERTEX_RIGHT_BOTTOM_BACK 4
#define VERTEX_RIGHT_BOTTOM_FRONT 5
#define VERTEX_RIGHT_TOP_BACK 6
#define VERTEX_RIGHT_TOP_FRONT 7
