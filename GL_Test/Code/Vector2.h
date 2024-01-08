#ifndef VECTOR2_H_
#define VECTOR2_H_


class Vector2
{
public:
	// ������� �밡���� ǥ����� m_x, m_y�� ������ ���ǻ� x, y�� ���ڴ�.
	float x;
	float y;
public:
	Vector2();
	Vector2(float tx, float ty) : x(tx), y(ty) {}
	~Vector2();
	Vector2 operator +(const Vector2& v) const;
	Vector2 operator -(const Vector2& v) const;
	Vector2 operator *(float v) const;
	Vector2 operator /(float v) const;
	float Dot(const Vector2& v) const;
	void operator +=(const Vector2& v);
	void operator -=(const Vector2& v);
	void operator *=(float v);
	void operator /=(float v);
	bool operator ==(const Vector2& v)const;
	Vector2 Cross(const Vector2& v) const;
	Vector2 Normalize();
	float Length();
};

// typedef Vector2<int> ivec2;
// typedef Vector2<float> fvec2;

#endif