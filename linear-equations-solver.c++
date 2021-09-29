#include <cmath>
#include <ctime>
#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;


void creatAValidArrayAndSolutions(vector<vector<double>> &);
long generateRandom(int start, int end);
void printArray(vector<vector<double>> &);

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
