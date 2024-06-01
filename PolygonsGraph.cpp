// ﷽
// PolygonsGraph.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

// Structure representing a point in 2D space
struct Point {
    double x, y;
};

// Structure representing a line equation in the form y = mx + c
struct Line {
    double m, c;
};

// Function to compute the Euclidean distance between two points
double distance(const Point& p1, const Point& p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

// Function to compute the equation of a line given two points
Line lineEquation(const Point& p1, const Point& p2) {
    Line line;
    if (p1.x == p2.x) {
        line.m = std::numeric_limits<double>::infinity(); // Vertical line
        line.c = p1.x;
    } else {
        line.m = (p2.y - p1.y) / (p2.x - p1.x); // Slope calculation
        line.c = p1.y - line.m * p1.x; // Intercept calculation
    }
    return line;
}

// Function to compute the intersection point of two lines
Point lineIntersection(const Line& l1, const Line& l2) {
    Point intersection;
    if (std::isinf(l1.m) && std::isinf(l2.m)) {
        intersection.x = l1.c;
        intersection.y = std::numeric_limits<double>::infinity();
    } else if (std::isinf(l1.m)) {
        intersection.x = l1.c;
        intersection.y = l2.m * intersection.x + l2.c;
    } else if (std::isinf(l2.m)) {
        intersection.x = l2.c;
        intersection.y = l1.m * intersection.x + l1.c;
    } else {
        intersection.x = (l2.c - l1.c) / (l1.m - l2.m); // x-coordinate of intersection
        intersection.y = l1.m * intersection.x + l1.c; // y-coordinate of intersection
    }
    return intersection;
}

int main() {
    // Sample points
    std::vector<Point> points = {{1, 3}, {4, 7}, {6, 2}, {9, 5}};

    // Vector to store polygons vertices
    std::vector<Point> polygonsVertices;
    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            // Compute the midpoint of the line segment between points[i] and points[j]
            Point midPoint = {(points[i].x + points[j].x) / 2, (points[i].y + points[j].y) / 2};
            // Compute the slope of the perpendicular bisector
            double slope = -(points[j].x - points[i].x) / (points[j].y - points[i].y);
            // Compute the intercept of the perpendicular bisector
            double intercept = midPoint.y - slope * midPoint.x;
            // Store the midpoint as a polygons vertex
            polygonsVertices.push_back({midPoint.x, slope * midPoint.x + intercept});
        }
    }

    // Output Polygons vertices
    std::cout << "Polygons Vertices:" << std::endl;
    for (const auto& vertex : polygonsVertices) {
        std::cout << "(" << vertex.x << ", " << vertex.y << ")" << std::endl;
    }

    return 0;
}

/* Visual Schema:

                
                             .  [2.5, 5]
                            / \
                           /   \
                     . [1, 3]   \  . [5, 6]
                       /         \
                      /     . [3.5, 4.5]
                     /_____________\
                 . [0, 0]   . [6, 0]   . [9, 5]

            

            

                               Polygons Graph
      (4, 7) *----------------------------------------------* (9, 5)
             |  \  /                                         |
             |   \/                                          |
             |    /\                                         |
             |   /  \                                        |
             |  /    \                                       |
             | /      \                                      |
             |/        \                                     |
             *----------*----------* (6, 2)                 /|
             |          \          |                      /  |
             |           \         |                    /    |
             |            \        |                   /     |
             |             \       |                  /      |
             |              \      |                 /       |
             |               \     |                /        |
             |                \    |               /         |
             |                 \   |              /          |
             |                  \  |             /           |
             |                   \ |            /            |
             |                    \|           /             |
             *----------*----------*----------* (1, 3)      * (3, 5)
             |          |          |          |             |
             |          |          |          |             |
             |          |          |          |             |
             |          |          |          |             |
             |          |          |          |             |
             |          |          |          |             |
             |          |          |          |             |
             |          |          |          |             |
             |          |          |          |             |
             |          |          |          |             |
             |          |          |          |             |
      (4, 7) *----------*----------*----------* (9, 5)      * (6, 2)

*/
