struct Point {
    float x,y;

    Point operator-(Point& other) {
        return {x-other.x, y-other.y};
    }

    auto crossProduct(Point& other) {
        return x*other.y - y*other.x;
    }

    auto dotProduct(Point& other) {
        return x*other.x + y*other.y;
    }

    auto length() {
        return sqrt(dotProduct(*this));
    }

    auto distanceToLine(Point& start, Point& end) {
        auto v1 = end - start;
        auto v2 = *this - start;
        auto area = v1.crossProduct(v2); // area of parallelogram v1,v2
        return abs(area / v1.length()); // height of parallelogram
    }
};


Point lineLineIntersection(Point& start1, Point& end1, Point& start2, Point& end2) {
    // Line AB represented as a1x + b1y = c1
    auto a1 = end1.y - start1.y;
    auto b1 = start1.x - end1.x;
    auto c1 = a1*(start1.x) + b1*(start1.y);

    // Line CD represented as a2x + b2y = c2
    auto a2 = end2.y - start2.y;
    auto b2 = start2.x - end2.x;
    auto c2 = a2*(start2.x)+ b2*(start2.y);

    auto determinant = a1*b2 - a2*b1;

    if (determinant == 0) { // The lines are parallel.
        return {FLT_MAX, FLT_MAX};
    } else {
        auto x = (b2*c1 - b1*c2)/determinant;
        auto y = (a1*c2 - a2*c1)/determinant;
        return {x, y};
    }
}
