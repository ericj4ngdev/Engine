#ifndef COLOR_H_
#define COLOR_H_
class Color4f {
public:
	float r;
	float g;
	float b;
	float a;
public:
	Color4f() {}
	~Color4f() {}
	Color4f(float tr, float tg, float tb, float ta) : r(tr), g(tg), b(tb), a(ta) {}
	Color4f(const Color4f& c)
	{
		r = c.r;
		g = c.g;
		b = c.b;
		a = c.a;
	}

	void operator=(const Color4f& c)
	{
		r = c.r;
		g = c.g;
		b = c.b;
		a = c.a;
	}

};
#endif