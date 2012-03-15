/* closestpair.c
 *
 * An algorithm that finds the closest pair of a set of points in
 * euclidean space.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define NUMBER_OF_POINTS 64
#define SPACE_DIMENSION 102

void print_points(char *label, int number_of_points, double (*points)[2])
{
    int i = 0;

    printf("%s\n", label);
    for(i = 0; i < number_of_points; i++) {
        printf("(%lf,%lf)\n", points[i][0], points[i][1]);
    }
}

void populate_points(int number_of_points, double (*points)[2])
{
    int i = 0;

    for(i = 0; i < number_of_points; i++) {
        points[i][0] = (rand() % SPACE_DIMENSION) + 1;
        points[i][1] = (rand() % SPACE_DIMENSION) + 1;
    }
}

double euclidean_distance(double *point_a, double *point_b)
{
    double delta_x = point_b[0] - point_a[0];
    double delta_y = point_b[1] - point_a[1];
    return (sqrt(pow(delta_x, 2) + pow(delta_y, 2)));
}

double naive_closest_pair(int number_of_points, double (*points)[2])
{
    int i = 0;
    int j = 0;

    double min_distance = DBL_MAX;
    double distance = 0;
    double pair[2][2];

    for(i = 0; i < number_of_points; i++) {
        for(j = 0; j < number_of_points; j++) {
            distance = euclidean_distance(points[i], points[j]);
            if(distance > 0 && distance < min_distance) {
                min_distance = distance;
                pair[0][0] = points[i][0];
                pair[0][1] = points[i][1];
                pair[1][0] = points[j][0];
                pair[1][1] = points[j][1];
            }
        }
    }

    print_points("Closest Pair", 2, pair);

    return min_distance;
}

int main(int argc, char *argv[])
{
    int number_of_points = NUMBER_OF_POINTS;
    double points[number_of_points][2];

    populate_points(number_of_points, points);
    print_points("Points", number_of_points, points);

    double min_distance = naive_closest_pair(number_of_points, points);

    printf("Minimum Distance: %lf\n", min_distance);

    return 0;
}
