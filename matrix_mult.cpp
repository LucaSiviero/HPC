#include <iostream>
#include <chrono>
using namespace std;
#define SIZE 4096

int a[SIZE][SIZE], b[SIZE][SIZE], mult[SIZE][SIZE];

int main() {

    int r1, c1, r2, c2, i, j, k;

    cout << "Enter rows and columns for first matrix ( max 768 ): ";
    cin >> r1 >> c1;
    cout << "Enter rows and columns for second matrix: ";
    cin >> r2 >> c2;

    // If column of first matrix in not equal to row of second matrix,
    // ask the user to enter the size of matrix again.
    while (c1!=r2)
    {
        cout << "Error! column of first matrix not equal to row of second.";

        cout << "Enter rows and columns for first matrix: ";
        cin >> r1 >> c1;

        cout << "Enter rows and columns for second matrix: ";
        cin >> r2 >> c2;
    }

    // Storing elements of first matrix.
    for(i = 0; i < r1; ++i)
        for(j = 0; j < c1; ++j)
        {
            //cout << "Enter element a" << i + 1 << j + 1 << " : ";
            //cin >> a[i][j];
            a[i][j] = i + 4 / 2;
        }

    // Storing elements of second matrix.
    for(i = 0; i < r2; ++i)
        for(j = 0; j < c2; ++j)
        {
            //cout << "Enter element b" << i + 1 << j + 1 << " : ";
            //cin >> b[i][j];
            b[i][j] = j+1;
        }

    // Initializing elements of matrix mult to 0.
    for(i = 0; i < r1; ++i)
        for(j = 0; j < c2; ++j)
        {
            mult[i][j]=0;
        }

    cout << "Starting execution" << endl;

    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    // Multiplying matrix a and b and storing in array mult.
    for(i = 0; i < r1; ++i)
        for(j = 0; j < c2; ++j)
            for(k = 0; k < c1; ++k)
            {
                mult[i][j] += a[i][k] * b[k][j];
            }

    // Displaying the multiplication of two matrix.
    cout << endl << "Output Matrix: " << endl;
    for(i = 0; i < r1; ++i)
    for(j = 0; j < c2; ++j)
    {
        cout << " " << mult[i][j];
        if(j == c2-1)
            cout << endl;
    }
    
    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    cout << "Time difference = " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]" << endl;
    cout << "Time difference = " << chrono::duration_cast<chrono::nanoseconds> (end - begin).count() << "[ns]" << endl;
    cout << "Time difference = " << chrono::duration_cast<chrono::milliseconds> (end - begin).count() << "[ms]" << endl;
    cout << "Time difference = " << chrono::duration_cast<chrono::seconds> (end - begin).count() << "[s]" << endl;        

    return 0;
}