#include <iostream>
#include <fstream>

using namespace std;
// int a,b;
// Top Down function
int Mfill(int i, int j, int* chord, int** M, char**D)
{
    if (M[i][j] != -1) return M[i][j]; 
    else{
        int k = chord[j];
        if (k >= j || k < i) {
            M[i][j] = Mfill(i, j-1, chord, M, D);
            D[i][j] = 'L';
        }
        else if (k>i && k<j) {
            int a = (Mfill(i,k-1, chord, M, D) + Mfill(k+1, j-1, chord, M, D) + 1);
            int b = Mfill(i,j-1, chord, M, D);
            if (a >= b){
                M[i][j] = a;
                D[i][j] = 'M';
            }
            else{
                M[i][j] = b;
                D[i][j] = 'L';
            }
            // M[i][j] = max( (Mfill(i,k-1, chord, M, D) + Mfill(k+1, j-1, chord, M, D) + 1),  Mfill(i,j-1, chord, M, D)  );
            
        }
        else {
            M[i][j] = Mfill(i+1, j-1,chord,M, D)+1;
            D[i][j] = 'B';
            // if (Mfill(i+1,j-1, chord, M) == -1) M[i][j] = 1;
            // else M[i][j] = Mfill(i+1,j-1, chord, M)+1;
        }
    }
    return M[i][j];
    
    
}

void trace(int i, int j, char**D, int* chord, int* Doc)
{
    if (D[i][j] == 'L') trace(i, j-1, D, chord, Doc);
    else if (D[i][j] == 'M'){
        int k = chord[j];
        Doc[k] = j;
        trace(i,k-1, D, chord, Doc);
        trace(k+1, j-1, D, chord, Doc);
    }
    else if (D[i][j] == 'B'){
        Doc[i] = j;
        trace(i+1, j-1, D, chord, Doc);
    }
}

int main(int argc, char*argv[])
{
    if (argc < 3){
        cout << "Wrong command format!";
        return 1;
    }
    // Input
    fstream ifile;
    ifile.open(argv[1],ios::in);
    if (!ifile){
        cout << "Input file cannot be opened!";
        return 1;
    }
    // Output
    fstream ofile;
    ofile.open(argv[2],ios::out);
    if (!ofile){
        cout << "Output file cannot be opened!";
        return 1;
    }

    // Create 1D array for recording chords
    int dotNum = 0;
    int *chord = NULL;
    ifile >> dotNum; // Input
    chord = new int[dotNum];



    // Record the endpoints of chords
    for (int i=0; i<(dotNum/2); i++){
        int p1,p2;
        ifile >> p1;
        ifile >> p2;
        chord[p1] = p2;
        chord[p2] = p1;
    }

    // // debug
    // for (int i=0; i<(dotNum); i++){
    //     cout << chord[i] << " " << endl;
    // }

    // Create a 2n*2n array M
    int **M = NULL;
    char **D = NULL;
    M = new int*[dotNum];
    D = new char *[dotNum];
    for (int i=0; i<dotNum; i++){
        M[i] = new int[dotNum];
        D[i] = new char[dotNum];
    }
    
    // Create a array of length 2n to record chosen chords
    int *Doc = NULL;
    Doc = new int[dotNum];

    // Initializing M
    for (int i=0; i<dotNum; i++){
        for (int j=0; j<dotNum; j++) {
            if ( i >= j ) M[i][j] = 0;
            else M[i][j] = -1;
        }
    }

    // int k=0;
    // int i=0;
    // int j=0;

    // // Bottum Up
    // for (int f = 1; f<dotNum; f++){
    //     for (int s = 0; s<dotNum; s++){
    //         i = s;
    //         j = s + f;
    //         if (j < dotNum && i < dotNum){
    //             if (M[i][j] != -1) {}
    //             else{
    //                 k = chord[j];
    //                 if (k >= j || k < i) {
    //                     M[i][j] = M[i][j-1];
    //                 }
    //                 else if ( k>i && k<j) {
    //                     int a = M[i][k-1] + ((M[k+1][j-1] == -1)? 0:M[k+1][j-1]) + 1;
    //                     int b = M[i][j-1];
    //                     M[i][j] = (a>b)? a:b;
    //                 }
    //                 else {
    //                     if (M[i+1][j-1] == -1) M[i][j] = 1;
    //                     else M[i][j] = M[i+1][j-1]+1;
    //                 }
    //             }
    //         }
    //     }
    // }
    
    ofile << Mfill(0,dotNum-1, chord, M, D) << endl;
    trace(0,dotNum-1, D, chord, Doc);
    for (int i=0; i<dotNum; i++){
        if (Doc[i] != 0){
            ofile << i << " " << Doc[i] << endl;
        }
    }

    // // Debug
    // for (int i=0; i<dotNum; i++){
    //     for (int j=0; j<dotNum; j++){
    //         ofile << M[i][j] << " ";
    //     }
    //     ofile << endl;
    // }
    return 0;


}

