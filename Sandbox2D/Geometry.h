#pragma once

#define SQUARE(X) X*X
#define DELTA(A, B) (A < B ? B - A : A - B)
#define MIN(A, B) (A < B ? A : B)
#define MAX(A, B) (A > B ? A : B)

// Tuple
template <typename P>
struct Tuple
{
	P x;
	P y;
};

typedef Tuple<int> Pixel;
typedef Tuple<double> Vector2;
template <typename P> using Line = Tuple<Tuple<P>>;
template <typename P> using Rect = Line<P>;

template <typename P>
struct Circle
{
	double radius;
	Tuple<P> position;
};

// Basic conversions

inline Pixel ToPixel(Vector2 v)
{
	return Pixel{ static_cast<int>(floor(v.x + .5)), static_cast<int>(floor(v.y + .5)) };
}

inline Vector2 ToVector2(Pixel p)
{
	return Vector2{ static_cast<double>(p.x), static_cast<double>(p.y) };
}

// SDL conversions

inline SDL_Rect ToSDL(Rect<int> orig)
{
	return SDL_Rect{
		MIN(orig.x.x, orig.y.x),
		MIN(orig.x.y, orig.y.y),
		MAX(orig.x.x, orig.y.x) - MIN(orig.x.x, orig.y.x),
		MAX(orig.x.y, orig.y.y) - MIN(orig.x.y, orig.y.y)
	};
}

inline SDL_Point ToSDL(Pixel orig)
{
	return{ orig.x, orig.y };
}

template <typename P>
Tuple<P> MakeTuple(P x, P y)
{
	return{ x, y };
}

// Origin point
template <typename N = double,
	typename std::enable_if<std::is_floating_point<N>::value, int>::type = 0>
	Tuple<N> MakeTuple()
{
	return{ static_cast<N>(0), static_cast<N>(0) };
}

// Simple maths

template <typename P>
Tuple<P> Add(Tuple<P> a, Tuple<P> b)
{
	return{ a.x + b.x, a.y + b.y };
}

template <typename P>
Tuple<P> operator+(Tuple<P> a, Tuple<P> b)
{
	return{ a.x + b.x, a.y + b.y };
}

template <typename P>
Tuple<P> Dot(Tuple<P> a, Tuple<P> b)
{
	return{ a.x * b.x, a.y * b.y };
}

template <typename P>
Tuple<P> operator*(Tuple<P> a, Tuple<P> b)
{
	return{ a.x * b.x, a.y * b.y };
}

template <typename P>
Tuple<P> operator*(Tuple<P> a, P b)
{
	return{ a.x * b, a.y * b };
}

template <typename P>
Tuple<P> operator-(Tuple<P> tup) {
	return{ -tup.x, -tup.y };
}

template <typename P>
Tuple<P> operator-(Tuple<P> a, Tuple<P> b) {
	return{ a.x - b.x, a.y - b.y };
}

// Advanced maths

template <typename P>
Tuple<P> Normalize(Tuple<P> tup) {
	const double dist = Distance(MakeTuple<>(), tup);

	return{ tup.x / dist, tup.y / dist };
}

template <typename N,
	typename std::enable_if<std::is_floating_point<N>::value, int>::type = 0>
	N Floor(N n)
{
	return floor(n);
}

template <typename N>
Tuple<N> Floor(Tuple<N> t)
{
	return{ Floor(t.x), Floor(t.y) };
}

template <typename N,
	typename std::enable_if<std::is_floating_point<N>::value, int>::type = 0>
	N Round(N n)
{
	return Floor(n + 0.5);
}

template <typename N>
Tuple<N> Round(Tuple<N> t)
{
	return{ Round(t.x), Round(t.y) };
}

template <typename P>
std::ostream& operator<<(std::ostream& os, Tuple<P> p)
{
	return os << "Tuple<" << typeid(P).name() << "> { " << p.x << ", " << p.y << " }";
}

// Checks if point is inside of rect
template <typename P>
bool Contains(Rect<P> rect, Tuple<P> point)
{
	return rect.x.x < point.x && rect.y.x > point.x
		&& rect.x.y < point.y && rect.y.y > point.y;
}

// Checks if a overlaps b
template <typename P>
bool Contains(Rect<P> a, Rect<P> b)
{
	// Not intersecting if found seperated along axis
	if (a.y.x < b.x.x || a.x.x > b.y.x) return false;
	if (a.y.y < b.x.y || a.x.y > b.y.y) return false;

	// There is at least one overlapping axis
	return true;
}

// Checks if a overlaps b
template <typename P>
bool Contains(Circle<P> a, Circle<P> b)
{
	P r = a.radius + b.radius;
	r *= r;
	return r < pow(a.position.x + b.position.x, 2) + pow(a.position.y + b.position.y, 2);
}

template <typename P>
Line<P> MakeLine(Tuple<P> a, Tuple<P> b)
{
	return{ a, b };
}

template <typename P>
Line<P> MakeLine(P x, P y, P xx, P yy)
{
	return{ { x, y },{ xx, yy } };
}

template <typename P>
std::ostream& operator<<(std::ostream& os, Line<P> line)
{
	return os << "Line<" << typeid(P).name() << "> { " << line.x << ", " << line.y << " }";
}

template <typename P>
double Distance(Tuple<P> a, Tuple<P> b)
{
	return sqrt(SQUARE(DELTA(a.x, b.x)) + SQUARE(DELTA(a.y, b.y)));
}

template <typename P>
double Distance(Line<P> line)
{
	return Distance(line.a, line.b);
}

template <typename P> using Poly = std::vector<P>;

template <typename P>
Poly<P> MakePoly(std::initializer_list<P> args)
{
	return static_cast<Poly<P>>(args);
}


template <typename P>
Poly<Tuple<P>> Translate(Poly<Tuple<P>> poly, Tuple<P> mod)
{
	Poly<Tuple<P>> p;

	for (Tuple<P> elem : poly)
		p.push_back(elem + mod);

	return p;
}