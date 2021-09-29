#include <cmath>
#include <ctime>
#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;
vector<double> solveLinearEquations(vector<vector<double>> &);
void creatAValidArrayAndSolutions(vector<vector<double>> &);
void printArray(vector<vector<double>> &);
bool confirmSolution(vector<double> &, vector<vector<double>> &);
long generateRandom(int start, int end);

unsigned N;
int main(int argc, const char **argv)
{
    srand(time(0));
    std::cout
        << "how many constants do you want to test" << std::endl;
    cin >> N;
    vector<vector<double>> arr(N, vector<double>(N + 1));

    creatAValidArrayAndSolutions(arr);
    vector<vector<double>> init_arr = arr;
    vector<double> proposedSolutions = solveLinearEquations(arr);
    if (confirmSolution(proposedSolutions, init_arr))
    {
        std::cout << "the solution is Correct" << std::endl;
    }
    else
    {
        std::cout << "the solution is Incorrect" << std::endl;
    }
    return 0;
}


void creatAValidArrayAndSolutions(vector<vector<double>> &arr)
{
    vector<double> solutions(N);

    double solution;
    for (size_t i = 0; i < N; i++)
    {

        solution = generateRandom(100, 200) * 0.25;
        solutions.at(i) = solution;
    }
    for (size_t i = 0; i < N; i++)
    {

        for (size_t j = 0; j < N; j++)
        {
            arr[i][j] = generateRandom(100, 200) * 0.125;
        }
    }
    for (size_t i = 0; i < N; i++)
    {
        double total = 0.0;
        for (size_t j = 0; j < N; j++)
        {
            total += arr[i][j] * solutions[j];
        }
        arr[i][N] = total;
    }
}

long generateRandom(int start, int end)
{
    if (start >= end)
    {
        cout << "The values are outragious";
        exit(1);
    }
    return (rand() % (end + 1 - start) + start);
}
void printArray(vector<vector<double>> &arr)
{
    for (size_t i = 0; i < N; i++)
    {
        for (size_t k = 0; k < (N + 1); k++)
        {
            cout << arr[i][k] << "\t";
        }

        cout << endl;
    }
    cout << endl
         << endl;
}
vector<double> solveLinearEquations(vector<vector<double>> &arr)
{

    vector<double> solutions(N, 0.0);
    double pivotValue;
    double rowValue;
    double multiplier;
    for (size_t pivot = 0; pivot < N; pivot++)
    {

        pivotValue = arr[pivot][pivot];
        for (size_t row = pivot + 1; row < N; row++)
        {
            rowValue = arr[row][pivot];
            multiplier = rowValue / pivotValue;
            for (size_t column = pivot; column < N + 1; column++)
            {
                arr[row][column] -= arr[pivot][column] * multiplier;
            }
        }
    }

    for (int row = N - 1; row >= 0; row--)
    {
        solutions[row] = arr[row][N];
        for (size_t column = N - 1; column > row; column--)
        {
            solutions[row] -= arr[row][column] * solutions[column];
        }
        solutions[row] /= arr[row][row];
    }

    return solutions;
}

bool confirmSolution(vector<double> &proposed_solution, vector<vector<double>> &arr)
{
    double tolerance;
    if (N > 1000)
    {
        tolerance = 0.005;
    }
    else
    {
        tolerance = 0.000005;
    }

    for (size_t row = 0; row < N; row++)
    {
        double total = 0.0;
        for (size_t column = 0; column < N; column++)
        {
            total += arr[row][column] * proposed_solution[column];
        }

        if (abs(arr[row][N] - total) >= tolerance)
        {
            std::cout << " at row " << row << " ,solution = " << arr[row][N] << "  but the value found is " << total << std::endl;
            return false;
        }
    }
    return true;
}
