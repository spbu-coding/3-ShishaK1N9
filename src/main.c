/*
 * Gags with precision
 *
 * Roman Shishkin
 * Last update: 02.11.2020
 */
#include <stdio.h>
#include <math.h>

const float FLOAT_EPSILON = 1e-6f, FLOAT_SECOND_POINT_COEFFICIENT = 1e-4f, FLOAT_MAX_DELTA = 1e-4f;
const float FLOAT_TRUE_FIRST_POINT = 1.0f, FLOAT_TRUE_SECOND_POINT = 1.0f;
const float FLOAT_FIRST_SUM = 2.0f, FLOAT_SECOND_SUM = 2.0001f;
const double DOUBLE_EPSILON = 1e-6, DOUBLE_SECOND_POINT_COEFFICIENT = 1e-4, DOUBLE_MAX_DELTA = 1e-4;
const double DOUBLE_TRUE_FIRST_POINT = 1.0, DOUBLE_TRUE_SECOND_POINT = 1.0;
const double DOUBLE_FIRST_SUM = 2.0, DOUBLE_SECOND_SUM = 2.0001;

struct double_points
{
    double first_point;
    double second_point;
};

struct float_points
{
    float first_point;
    float second_point;
};

float calc_distance_in_float(struct float_points float_pair)
{
    return sqrtf(powf(float_pair.first_point - FLOAT_TRUE_FIRST_POINT, 2) +
                 powf(float_pair.second_point - FLOAT_TRUE_SECOND_POINT, 2));
}

double calc_distance_in_double(struct double_points double_pair)
{
    return sqrt(pow(double_pair.first_point - DOUBLE_TRUE_FIRST_POINT, 2) +
                 pow(double_pair.second_point - DOUBLE_TRUE_SECOND_POINT, 2));
}

struct float_points calc_answer_in_float(float float_delta)
{
    struct float_points float_answer;
    float_answer.second_point = (FLOAT_SECOND_SUM - FLOAT_FIRST_SUM + float_delta) / FLOAT_SECOND_POINT_COEFFICIENT;
    float_answer.first_point = FLOAT_FIRST_SUM - float_answer.second_point;
    return float_answer;
}

struct double_points calc_answer_in_double(double double_delta)
{
    struct double_points double_answer;
    double_answer.second_point = (DOUBLE_SECOND_SUM - DOUBLE_FIRST_SUM + double_delta) / DOUBLE_SECOND_POINT_COEFFICIENT;
    double_answer.first_point = DOUBLE_FIRST_SUM - double_answer.second_point;
    return double_answer;
}

void float_output_results(float float_delta)
{
    printf("Experiment in floats\n");
    int index = 1;
    float float_last_distance;
    while(calc_distance_in_float(calc_answer_in_float(float_delta)) > FLOAT_EPSILON)
    {
        printf("    Calculation #%d:\n", index);
        struct float_points answer = calc_answer_in_float(float_delta);
        printf("        x = %.7f, y = %.7f\n", answer.first_point, answer.second_point);
        float float_new_distance = calc_distance_in_float(answer);
        printf("        Distance = %.7f\n", float_new_distance);
        printf("        Delta = %.7f\n", float_delta);
        float_delta /= 2;
        index++;
        if(index != 1)
            if(fabsf(float_last_distance - float_new_distance) < FLOAT_EPSILON)
            {
                printf("    Something went wrong:\n");
                printf("    Distance doesn't change\n");
                break;
            }
        float_last_distance = float_new_distance;
    }
    printf("End of experiment in floats.\n");
}

void double_output_results(double double_delta)
{
    printf("Experiment in doubles\n");
    int index = 1;
    double double_last_distance;
    while(calc_distance_in_double(calc_answer_in_double(double_delta)) > DOUBLE_EPSILON)
    {
        printf("    Calculation #%d:\n", index);
        struct double_points answer = calc_answer_in_double(double_delta);
        printf("        x = %.15f, y = %.15f\n", answer.first_point, answer.second_point);
        double double_new_distance = calc_distance_in_double(answer);
        printf("        Distance = %.15f\n", double_new_distance);
        printf("        Delta = %.15f\n", double_delta);
        double_delta /= 2;
        index++;
        if(index != 1)
            if(fabs(double_last_distance - double_new_distance) < DOUBLE_EPSILON)
            {
                printf("    Something went wrong:\n");
                printf("    Distance doesn't change\n");
                break;
            }
        double_last_distance = double_new_distance;
    }
    printf("End of experiment in doubles.\n");
}

void float_output_data()
{
    printf("Float data:\n");
    printf("    x + y = %.7f\n", FLOAT_FIRST_SUM);
    printf("    x + %.7f * y = %.7f\n", 1.0f + FLOAT_SECOND_POINT_COEFFICIENT, FLOAT_SECOND_SUM);
    printf("    Epsilon = %.7f\n", FLOAT_EPSILON);
}

void double_output_data()
{
    printf("Double data:\n");
    printf("    x + y = %.15lf\n", DOUBLE_FIRST_SUM);
    printf("    x + %.15lf * y = %.15lf\n", 1.0f + DOUBLE_SECOND_POINT_COEFFICIENT, DOUBLE_SECOND_SUM);
    printf("    Epsilon = %.15lf\n", DOUBLE_EPSILON);
}

int main()
{
    float_output_data();
    float_output_results(FLOAT_MAX_DELTA);
    double_output_data();
    double_output_results(DOUBLE_MAX_DELTA);
    return 0;
}
