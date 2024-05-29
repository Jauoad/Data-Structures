// ﷽
// GardenStructures.cpp
// Source :  https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

// Declaration of a global vector to hold the flowers data
static int N = 9;
vector<tuple<char, int, bool, vector<int>>> flowers(N);

int main() {
    // Diagonal matrix Garden approach 1
    generate(flowers.begin(), flowers.end(), [] {
        char c = 'A';
        int i = 1;
        vector<int> petals(N);
        generate(petals.begin(), petals.end(), [] {
            static int j = 1;
            return (j < N) ? j++ : j = 0;
        });
        return make_tuple(c++, i++, false, petals);
    });

    //print the generated garden vector
    for (const auto& f : flowers) {
        cout << " " << get<0>(f) << " " << get<1>(f) << " " << get<2>(f) << " ";
        for (const auto& val : get<3>(f)) {
            cout << val;
        }
        cout << endl;
    }

    // *********************************************************************

    //Incremented Garden approach 2

    generate(flowers.begin(), flowers.end(), [] {
        static char c = 'A';
        static int i = 1;
        static bool b = false;
        b = !b;
        static vector<int> petals(N);
        generate(petals.begin(), petals.end(), [] {
            static int j = 1;
            return j++;
        });
        return make_tuple(c++, i++, b, petals);
    });

    //print the generated vector
    for (const auto& f : flowers) {
        cout << " " << get<0>(f) << " " << get<1>(f) << "  " << (get<2>(f) ? "T" : "F") << "   ";
        for (const auto& val : get<3>(f)) {
            printf("%2d", val);
            cout << " ";
        }
        cout << endl;
    }

    return 0;

    /*

    // Garden Structure 'Approch 1'

    CHAR    INT        BOOL          VECTOR<INT>

    A      1          0        1 2 3 4 5 6 7 8 9 0 
    A      1          0        0 1 2 3 4 5 6 7 8 9
    A      1          0        0 0 1 2 3 4 5 6 7 8
    A      1          0        9 0 0 1 2 3 4 5 6 7
    A      1          0        8 9 0 0 1 2 3 4 5 6
    A      1          0        7 8 9 0 0 1 2 3 4 5
    A      1          0        6 7 8 9 0 0 1 2 3 4
    A      1          0        5 6 7 8 9 0 0 1 2 3
    A      1          0        4 5 6 7 8 9 0 0 1 2
    A      1          0        3 4 5 6 7 8 9 0 0 1

    // Garden Structure 'Approach 2'

    CHAR    INT        BOOL             VECTOR<INT>

    A       1          T         1  2  3  4  5  6  7  8  9 
    B       2          F        10 11 12 13 14 15 16 17 18 
    C       3          T        19 20 21 22 23 24 25 26 27 
    D       4          F        28 29 30 31 32 33 34 35 36 
    E       5          T        37 38 39 40 41 42 43 44 45 
    F       6          F        46 47 48 49 50 51 52 53 54 
    G       7          T        55 56 57 58 59 60 61 62 63 
    H       8          F        64 65 66 67 68 69 70 71 72 
    I       9          T        73 74 75 76 77 78 79 80 81
    */
}
