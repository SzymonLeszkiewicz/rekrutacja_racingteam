// Szymon Leszkiewicz
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stack>
#include <cmath>
#include <iomanip>
#include <string>

// Structure representing a 2D point.
struct Point {
    double x, y;
    Point(double x, double y) : x(x), y(y) {}
};

// Finds the starting point (with the lowest y-coordinate, and in case of a tie, lowest x-coordinate).
Point findStartPoint(const std::vector<Point>& points) {
    Point start = points[0];
    for (size_t i = 1; i < points.size(); i++) {
        if (points[i].y < start.y || (points[i].y == start.y && points[i].x < start.x)) {
            start = points[i];
        }
    }
    return start;
}

// Returns orientation of ordered triplet (a, b, c).
// 0 --> collinear, 1 --> clockwise, 2 --> counterclockwise.
int getOrientation(const Point &a, const Point &b, const Point &c) {
    double val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
    if (fabs(val) < 1e-9) return 0;
    return (val > 0) ? 1 : 2;
}

// Comparator for sorting points relative to a given starting point based on polar angle.
struct PointComparator {
    Point start;
    PointComparator(const Point &s) : start(s) {}

    bool operator()(const Point &a, const Point &b) const {
        double dx1 = a.x - start.x, dy1 = a.y - start.y;
        double dx2 = b.x - start.x, dy2 = b.y - start.y;
        double cross = dx1 * dy2 - dy1 * dx2;
        if (fabs(cross) < 1e-9) {
            // If collinear, sort by distance from the starting point.
            return (dx1 * dx1 + dy1 * dy1) < (dx2 * dx2 + dy2 * dy2);
        }
        return cross > 0;
    }
};

// Sorts the points based on the polar angle with respect to the start point.
void sortPoints(std::vector<Point>& points, const Point &start) {
    PointComparator comp(start);
    std::sort(points.begin(), points.end(), comp);
}

// Computes the convex hull using the Graham Scan algorithm.
std::vector<Point> convexHull(const std::vector<Point>& points) {
    if (points.size() < 3) return points;

    std::stack<Point> hull;
    hull.push(points[0]);
    hull.push(points[1]);

    for (size_t i = 2; i < points.size(); ++i) {
        Point top = hull.top();
        hull.pop();
        while (!hull.empty() && getOrientation(hull.top(), top, points[i]) != 2) {
            top = hull.top();
            hull.pop();
        }
        hull.push(top);
        hull.push(points[i]);
    }

    std::vector<Point> result;
    while (!hull.empty()) {
        result.push_back(hull.top());
        hull.pop();
    }
    std::reverse(result.begin(), result.end());
    return result;
}

int main() {
    // Read input file name from the user.
    std::string filename;
    std::cin >> filename;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: could not open file '" << filename << "'." << std::endl;
        return 1;
    }

    // Read the number of points.
    int numPoints;
    if (!(file >> numPoints)) {
        std::cerr << "Error: invalid number of points." << std::endl;
        return 1;
    }

    // Read the points from the file.
    std::vector<Point> points;
    double x, y;
    for (int i = 0; i < numPoints; ++i) {
        if (!(file >> x >> y)) {
            std::cerr << "Error: invalid format for point #" << (i + 1) << "." << std::endl;
            return 1;
        }
        points.emplace_back(x, y);
    }
    file.close();

    if (points.empty()) {
        std::cerr << "Error: no points provided." << std::endl;
        return 1;
    }

    // Find the starting point and sort the points based on the polar angle.
    Point start = findStartPoint(points);
    sortPoints(points, start);

    // Compute the convex hull.
    std::vector<Point> hull = convexHull(points);

    // Output
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "[";
    for (size_t i = 0; i < hull.size(); ++i) {
        std::cout << "(" << hull[i].x << ", " << hull[i].y << ")";
        if (i != hull.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;

    return 0;
}