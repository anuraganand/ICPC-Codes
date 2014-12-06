// type of coordinates
typedef double pType; 
 
struct Point {
    pType x,y;
    Point() {}
    Point(pType x,pType y):x(x),y(y) {}

    // use brackets with all operators e.g use (a ^ b) instead of just a ^ b
    // vector addition
    Point operator +(const Point &rhs) const { return Point(this->x + rhs.x, this->y + rhs.y); } 
    // vector subtraction
    Point operator -(const Point &rhs) const { return Point(this->x - rhs.x, this->y - rhs.y); }   
    
    bool operator ==(const Point &rhs) const { return (this->x == rhs.x && this->y == rhs.y);}
    bool operator <(const Point &rhs) const { if(this->x != rhs.x) return this->x < rhs.x; return this->y < rhs.y;}
    // cross product
    pType operator ^(const Point &rhs) const { return this->x * rhs.y - this->y * rhs.x; } 
    // dot product
    pType operator *(const Point &rhs) const { return this->x * rhs.x + this->y * rhs.y; }

    void print() {
        cout << "[" << x << " , " << y << "]";
    }
};

// scalar multiplication
Point operator *(pType c, const Point &p)       { return Point(c * p.x, c * p.y); }    
// square of length
pType len2(const Point & p) { return p * p; }
// square of distance between two vectors
pType dis2(const Point & p, const Point & q) { return len2(p - q); }

// convex hull (monotone chain) O(nlogn)
// pass a vector of unique points
vector <Point> convexHull(vector <Point> pts) {
    vector <Point> hull;
    sort(pts.begin(), pts.end());
    int n = (int)pts.size();

    hull.push_back(pts[0]);
    int nh = 1, start = 0;
    for(int i = 0; i < n; ++i) {
        Point p = pts[i];
        while(nh - start >= 2 and ((p - hull[nh - 1]) ^ (hull[nh - 1] - hull[nh - 2])) >= 0) {
            hull.pop_back(); --nh;
        }
        hull.push_back(p); ++nh;
    }

    start = nh - 1;
    for(int i = n - 2; i >= 0; --i) {
        Point p = pts[i];
        while(nh - start >= 2 and ((p - hull[nh - 1]) ^ (hull[nh - 1] - hull[nh - 2])) >= 0) {
            hull.pop_back(); --nh;
        }
        hull.push_back(p); ++nh;
    }
    hull.pop_back();
    return hull;
}

// area of a convex hull of a vector of points
double area(vector <Point> & pts) {
    sort(all(pts));
    pts.erase(unique(all(pts)), pts.end());
    if(sz(pts) <= 2) return 0.0;
    double ar = 0.0;
    vector <Point> hull = convexHull(pts);
    rep(i, sz(hull)) {
        ar += hull[i] ^ hull[(i + 1) % sz(hull)];
    }
    return 0.5 * ar;
}