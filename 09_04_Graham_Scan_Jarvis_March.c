/*
  Graham Scan - Convex Hull (generalized)
  Input:
    First line: integer N (number of points)
    Next N lines: two numbers xi yi (can be integers or floats)
  Output:
    First line: H (number of hull vertices)
    Next H lines: hull vertices in CCW order (x y)
  Notes:
    - Uses double for coordinates.
    - Removes duplicates before processing.
    - Keeps extreme points when collinear on hull edges.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x, y;
} Point;

static Point pivot; // used by comparator

// Utility: orientation of ordered triplet (a,b,c)
// returns >0 if counter-clockwise, <0 if clockwise, 0 if collinear
double cross(const Point a, const Point b, const Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

double dist2(const Point a, const Point b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    return dx*dx + dy*dy;
}

// Comparator for qsort: sort by polar angle w.r.t pivot (increasing)
// If same angle (collinear), put the closer point first
int cmpAngle(const void *p1, const void *p2) {
    Point *a = (Point*)p1;
    Point *b = (Point*)p2;
    double c = cross(pivot, *a, *b);
    if (fabs(c) < 1e-12) {
        double da = dist2(pivot, *a);
        double db = dist2(pivot, *b);
        if (da < db) return -1;
        if (da > db) return 1;
        return 0;
    }
    return (c > 0) ? -1 : 1; // counter-clockwise first
}

// Remove duplicates (exact matches) from array of points in-place.
// Returns new size.
int remove_duplicates(Point pts[], int n) {
    if (n <= 1) return n;
    // sort by x then y to group duplicates
    int cmpXY(const void *pa, const void *pb) {
        Point *a = (Point*)pa;
        Point *b = (Point*)pb;
        if (a->x < b->x) return -1;
        if (a->x > b->x) return 1;
        if (a->y < b->y) return -1;
        if (a->y > b->y) return 1;
        return 0;
    }
    qsort(pts, n, sizeof(Point), cmpXY);
    int m = 1;
    for (int i = 1; i < n; ++i) {
        if (fabs(pts[i].x - pts[m-1].x) > 1e-12 || fabs(pts[i].y - pts[m-1].y) > 1e-12) {
            pts[m++] = pts[i];
        }
    }
    return m;
}

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) {
        fprintf(stderr, "Invalid input: expected integer N\n");
        return 1;
    }
    if (N <= 0) {
        printf("0\n");
        return 0;
    }

    Point *pts = malloc(sizeof(Point) * N);
    if (!pts) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < N; ++i) {
        if (scanf("%lf %lf", &pts[i].x, &pts[i].y) != 2) {
            fprintf(stderr, "Invalid input: expected coordinates\n");
            free(pts);
            return 1;
        }
    }

    // Remove duplicates
    N = remove_duplicates(pts, N);
    if (N == 1) {
        printf("1\n%.10g %.10g\n", pts[0].x, pts[0].y);
        free(pts);
        return 0;
    }

    // 1) Find pivot: lowest y, tie -> lowest x
    int pivot_idx = 0;
    for (int i = 1; i < N; ++i) {
        if (pts[i].y < pts[pivot_idx].y || (fabs(pts[i].y - pts[pivot_idx].y) < 1e-12 && pts[i].x < pts[pivot_idx].x)) {
            pivot_idx = i;
        }
    }

    // Swap pivot to position 0
    Point tmp = pts[0];
    pts[0] = pts[pivot_idx];
    pts[pivot_idx] = tmp;
    pivot = pts[0];

    // 2) Sort remaining points by polar angle around pivot
    qsort(pts + 1, N - 1, sizeof(Point), cmpAngle);

    // 3) If there are points with same angle at the end, we want the farthest one last.
    // Our comparator placed closer first, so during scan we'll pop the closer ones.
    // Special case: after sorting, if multiple points have same angle as pivot and are collinear,
    // we must ensure that the farthest remains (this will be handled in the scan by popping).

    // 4) Graham scan using stack (array)
    Point *stack = malloc(sizeof(Point) * N);
    if (!stack) { free(pts); fprintf(stderr, "Memory allocation failed\n"); return 1; }
    int top = 0;
    stack[top++] = pts[0];
    stack[top++] = pts[1];

    for (int i = 2; i < N; ++i) {
        // while the turn formed by second-top, top, pts[i] is not counter-clockwise, pop top
        while (top >= 2 && cross(stack[top-2], stack[top-1], pts[i]) <= 0) {
            // <= 0: removes collinear interior points so only extreme points remain
            top--;
        }
        stack[top++] = pts[i];
    }

    // If all points are collinear, stack could end up containing only two endpoints.
    // Output hull
    printf("%d\n", top);
    for (int i = 0; i < top; ++i) {
        // Print with compact formatting (preserve integer-like inputs nicely)
        printf("%.10g %.10g\n", stack[i].x, stack[i].y);
    }

    free(pts);
    free(stack);
    return 0;
}
