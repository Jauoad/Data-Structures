// ﷽
// QuadTree.cpp
// Source :  https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>
#include <vector>
#include <memory>

// Definition of a 2-DIM point
struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

// Schema: Point(x, y)
//     (x, y)
//      *
//      |
//     (x, y)

// Definition of a rectangular region
struct Rect {
    int x, y, width, height;
    Rect(int x, int y, int width, int height) 
        : x(x), y(y), width(width), height(height) {}

    // Checks if the point is inside the region
    bool contains(const Point& point) const {
        return (point.x >= x - width &&
                point.x <= x + width &&
                point.y >= y - height &&
                point.y <= y + height);
    }

    // Schema: Checking if a point is inside a region
    //     (x, y) center
    //      *---------* (x + width, y - height)
    //      |         |
    //      |    *    | (point)
    //      |         |
    //      *---------* (x - width, y + height)

    // Checks if the region intersects with another region
    bool intersects(const Rect& range) const {
        return !(range.x - range.width > x + width ||
                 range.x + range.width < x - width ||
                 range.y - range.height > y + height ||
                 range.y + range.height < y - height);
    }

    // Schema: Checking intersection of two regions
    //     (x1, y1) center      (x2, y2) center
    //      *---------*          *---------*
    //      |         |          |         |
    //      |         |          |         |
    //      *---------*          *---------*
};

// Definition of a Quad Tree
class QuadTree {
    Rect boundary; // Region covered by this node
    int capacity; // Maximum capacity of points before subdivision
    std::vector<Point> points; // Points contained in this node
    bool divided; // Indicates if the node is subdivided
    std::unique_ptr<QuadTree> C_GHRB; // Northwest sub-node
    std::unique_ptr<QuadTree> C_CHRQ; // Northeast sub-node
    std::unique_ptr<QuadTree> J_GHRB; // Southwest sub-node
    std::unique_ptr<QuadTree> J_CHRQ; // Southeast sub-node

public:
    QuadTree(Rect boundary, int capacity)
        : boundary(boundary), capacity(capacity), divided(false) {}

    // Inserts a point into the Quad Tree
    bool insert(Point point) {
        // If point is not within bounds, return false
        if (!boundary.contains(point))
            return false;

        // If capacity is not reached, add the point
        if (points.size() < capacity) {
            points.push_back(point);
            return true;
        } else {
            // If capacity is reached and not yet divided, subdivide it
            if (!divided)
                subdivide();

            // Insert the point into one of the sub-quadrants
            if (C_CHRQ->insert(point)) return true;
            if (C_GHRB->insert(point)) return true;
            if (J_CHRQ->insert(point)) return true;
            if (J_GHRB->insert(point)) return true;
        }
        return false;
    }

    // Schema: Inserting a point
    //     Before subdivision:
    //     (x, y) center
    //      *---------*
    //      |    *    | (point)
    //      |         |
    //      *---------*
    //
    //     After subdivision:
    //     (x, y) center
    //      *----*----*--------
    //      | C_GHRB | C_CHRQ |
    //      *----*----*
    //      | J_GHRB | J_CHRQ |
    //      *----*----*--------

    // Subdivides the node into four sub-nodes
    void subdivide() {
        int x = boundary.x;
        int y = boundary.y;
        int w = boundary.width / 2;
        int h = boundary.height / 2;

        // Set new boundaries for the quadrants
        Rect neRect(x + w, y - h, w, h); // Northeast
        Rect nwRect(x - w, y - h, w, h); // Northwest
        Rect seRect(x + w, y + h, w, h); // Southeast
        Rect swRect(x - w, y + h, w, h); // Southwest

        // Create new sub-nodes
        C_CHRQ = std::make_unique<QuadTree>(neRect, capacity);
        C_GHRB = std::make_unique<QuadTree>(nwRect, capacity);
        J_CHRQ = std::make_unique<QuadTree>(seRect, capacity);
        J_GHRB = std::make_unique<QuadTree>(swRect, capacity);

        divided = true;
    }

    // Schema: Subdividing a node into four sub-nodes
    //     (x, y) center
    //      *----*-------------
    //      | C_GHRB | C_CHRQ |
    //      *----*----*
    //      | J_GHRB | J_CHRQ |
    //      *----*----*--------

    // Prints the points of the Quad Tree
    void print() const {
        // Prints points of the current node
        for (const auto& point : points) {
            std::cout << "(" << point.x << ", " << point.y << ") ";
        }
        // Prints points of sub-nodes, if divided
        if (divided) {
            C_CHRQ->print();
            C_GHRB->print();
            J_CHRQ->print();
            J_GHRB->print();
        }
    }
};

int main() {
    // Define boundaries of the Quad Tree and capacity per node
    Rect boundary(0, 0, 10, 10);
    QuadTree qt(boundary, 1);

    // Schema: Initial Quad Tree
    //     (0, 0) center
    //      *---------*
    //      |         |
    //      |         |
    //      |         |
    //      *---------*

    // Insert points into the Quad Tree
    qt.insert(Point(2, 3));
    qt.insert(Point(5, 4));
    qt.insert(Point(9, 6));
    qt.insert(Point(4, 7));
    qt.insert(Point(8, 1));
    qt.insert(Point(7, 2));

    // Schema: Quad Tree after points insertion
    //     Before subdivision:
    //     (0, 0) center
    //      *---------*
    //      |    *    | (2, 3)
    //      |         |
    //      *---------*
    //
    //     After subdivision:
    //     (0, 0) center
    //      *----*----*--------
    //      | C_GHRB | C_CHRQ |
    //      *----*----*
    //      | J_GHRB | J_CHRQ |
    //      *----*----*--------

    // Print the points of the Quad Tree
    qt.print();

    return 0;
}
