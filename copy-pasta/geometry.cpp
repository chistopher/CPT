#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>


using namespace std;

template<typename T>
int sign(T a)
{
    if (a > 0)
        return 1;
    else if (a < 0)
        return -1;
    else
        return 0;
}


struct Vector
{
    double x;
    double y;

    double dotProduct(const Vector& other) const
    {
        return x*other.x + y*other.y;
    }

    double crossProduct(const Vector& other) const
    {
        return x*other.y - other.x*y;
    }

    double length() const
    {
        return sqrt(dotProduct(*this));
    }

    Vector operator+(const Vector& other) const
    {
        return { x + other.x, y + other.y };
    }

    Vector operator-(const Vector& other) const
    {
        return { x - other.x, y - other.y };
    }

    Vector operator-() const
    {
        return { -x,-y };
    }

    Vector operator*(double scalar) const
    {
        return { x*scalar,y*scalar };
    }

    Vector operator/(double scalar) const
    {
        return { x / scalar,y / scalar };
    }

    bool operator==(const Vector& other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator<(const Vector& other) const
    {
        if (x == other.x)
            return y < other.y;
        return x < other.x;
    }

    Vector normalized() const {
        return *this / this->length();
    }
};


struct Line
{
    Vector normal; //stores point if degenerated
    double offset;
    bool degenerated = false;

    Line() = default;

    Line(const Vector& start, const Vector& end)
    {
        degenerated = start == end;
        if (degenerated)
        {
            normal = start;
            return;
        }
            
        auto direction = end - start;
        normal = { -direction.y, direction.x };
        //normal = normal.normalized();
        offset = -normal.dotProduct(start);
    }

    double a() const
    {
        return normal.x;
    }

    double b() const
    {
        return normal.y;
    }

    double c() const
    {
        return offset;
    }

    //always normalized
    Vector direction() const
    {
        return { b(), -a() };
    }

    bool parallel(const Line& other) const
    {
        return normal.crossProduct(other.normal) == 0;
    }

    bool operator==(const Line& other) const
    {
        return normal == other.normal && offset == other.offset; //not sure
    }

    Vector anyPoint() const
    {
        if (a() != 0)
            return { -offset / a(), 0 };

        if (b() != 0)
            return { 0, -offset / b() };

        return { 0, 0 };
    }

    bool colinear(const Line& other) const
    {
        return direction().crossProduct(other.direction()) == 0;
    }
};


struct Ray
{
    Line line;
    Vector start;

    Ray(const Vector& start1, const Vector& end1)
    {
        line = Line(start1, end1);
        start = start1;
    }
};

struct Segment
{
    Line line;
    Vector start;
    Vector end;

    Segment(const Vector& start1, const Vector& end1)
    {
        line = Line(start1, end1);
        start = start1;
        end = end1;
    }

    bool crosses(const Line& aLine) const
    {
        auto sign1 = sign(aLine.direction().crossProduct(start - aLine.anyPoint()));
        auto sign2 = sign(aLine.direction().crossProduct(end - aLine.anyPoint()));
        return sign1 != sign2; //start and end lie on differen sides of the line
    }
};


//Distance functions
double dist(const Vector& a, const Vector& b)
{
    return (a - b).length();
}

double dist(const Line& line, const Vector& point)
{
    if (line.degenerated) return dist(line.normal, point);
    return abs(line.direction().normalized().crossProduct(point - line.anyPoint()));
}

double dist(const Vector& point, const Line& line)
{
    return dist(line, point);
}

double dist(const Segment& seg, const Vector& point)
{
    if (seg.line.degenerated) return dist(seg.start, point);

    auto direction = seg.line.direction();

    if ((point - seg.start).dotProduct(direction) >= 0 && (point - seg.end).dotProduct(-direction) >= 0) //not sure about this one
        return dist(seg.line, point);

    return min(dist(seg.start, point), dist(seg.end, point));
}

double dist(const Vector& point, const Segment& seg)
{
    return dist(seg, point);
}

double dist(const Segment& seg1, const Segment& seg2)
{
    if (seg1.line.degenerated) return dist(seg2, seg1.start);
    if (seg2.line.degenerated) return dist(seg1, seg2.start);

    if (seg1.line.colinear(seg2.line) || !seg1.crosses(seg2.line) || !seg2.crosses(seg1.line))
    {
        //1. colinear 2. not both intersect each other (eiter one does not intersect two or other way round
        auto minEndpointDist1 = min(dist(seg1, seg2.start), dist(seg1, seg2.end));
        auto minEndpointDist2 = min(dist(seg2, seg1.start), dist(seg2, seg1.end));
        return min(minEndpointDist1, minEndpointDist2);
    }

    return 0.0;
}

double dist(const Line& line1, const Line& line2)
{
    if (line1.degenerated) return dist(line2, line1.normal);
    if (line2.degenerated) return dist(line1, line2.normal);

    if (line1.colinear(line2))
        return dist(line1, line2.anyPoint());

    return 0.0;
}

double dist(const Line& line, const Segment& seg)
{
    if (line.degenerated) return dist(seg, line.normal);
    if (seg.line.degenerated) return dist(line, seg.start);

    if (line.colinear(seg.line))
        return dist(line, seg.start); //colinear

    if (seg.crosses(line))
        return 0.0; //intersecting

    return min(dist(line, seg.start), dist(line, seg.end));
}

double dist(const Segment& seg, const Line& line)
{
    return dist(line, seg);
}

double dist(const Ray& ray, const Vector& point)
{
    if (ray.line.degenerated) return dist(ray.start, point);

    if ((point - ray.start).dotProduct(ray.line.direction()) >= 0)
        return dist(ray.line, point); //point is in front of start (in ray direction)

    return dist(ray.start, point); //point is behind start (in ray direction)
}

double dist(const Vector& point, const Ray& ray)
{
    return dist(ray, point);
}

double dist(const Ray& ray, const Segment& seg)
{
    if (ray.line.degenerated) return dist(seg, ray.start);
    if (seg.line.degenerated) return dist(ray, seg.start);

    auto scalar1 = (seg.start - ray.start).dotProduct(ray.line.direction()) >= 0;
    auto scalar2 = (seg.end - ray.start).dotProduct(ray.line.direction()) >= 0;

    if (scalar1 && scalar2)
        return dist(ray.line, seg);

    return dist(seg, ray.start);
}

double dist(const Segment& seg, const Ray& ray)
{
    return dist(ray, seg);
}

//only call when not colinear
Vector intersection(const Line& first, const Line& second)
{
    auto x = ((-first.c()) * second.b() - ((-second.c()) * first.b()));
    x = x / (first.a() * second.b() - second.a()*first.b());

    auto y = first.a() * (-second.c()) - (second.a()*(-first.c()));
    y = y / (first.a() * second.b() - second.a()*first.b());

    return { x,y };
}

double dist(const Ray& ray1, const Ray& ray2)
{
    if (ray1.line.degenerated) return dist(ray2, ray1.start);
    if (ray2.line.degenerated) return dist(ray1, ray2.start);

    if (ray1.line.parallel(ray2.line))
        return min(dist(ray1, ray2.start), dist(ray2, ray1.start));

    auto inter = intersection(ray1.line, ray2.line);
    if (dist(ray1, inter) < 0.0000001 && dist(ray2, inter) < 0.0000001)
        return 0.0; //intersection lies on both rays

    return min(dist(ray1, ray2.start), dist(ray2, ray1.start));
}

double dist(const Ray& ray, const Line& line)
{
    if (ray.line.degenerated) return dist(line, ray.start);
    if (line.degenerated) return dist(ray, line.normal);

    if (line.parallel(ray.line))
        return dist(line, ray.start);

    if (dist(ray, intersection(ray.line, line)) < 0.0000001)
        return 0.0;

    return dist(line, ray.start);
}

double dist(const Line& line, const Ray& ray)
{
    return dist(ray, line);
}