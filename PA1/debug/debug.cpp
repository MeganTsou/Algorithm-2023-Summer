#include <iostream>
#include <ctime>
#include <vector>
using namespace std;

void MergeSortSubVector(vector<int> &data, int low, int high)
{
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if (low<high){
        int p = (low+high)/2;
        MergeSortSubVector(data, low, p);
        MergeSortSubVector(data, p+1, high);
        //Merge(data, low, p, p+1, high);
        int middle1 = p;
        int middle2 = p+1;
        vector<int> sub1;
        vector<int> sub2;
        for (int i=low; i<=middle1; i++){
            sub1.push_back(data[i]);
        }
        for (int i=middle2; i<=high; i++){
            sub2.push_back(data[i]);
        }

        int a = 0;
        int b = 0;
        for (int i=low; i<=high; i++){
            if ( (a<sub1.size()) && (b<sub2.size()) && (sub1[a] <= sub2[b]) ){
                data[i] = sub1[a];
                a++;
            }
            else if ((a<sub1.size()) && (b<sub2.size()) && (sub1[a] > sub2[b])){
                data[i] = sub2[b];
                b++;
            }
            else if ( (a >= sub1.size()) && (b<sub2.size()) ){
                data[i] = sub2[b];
                b++;
            }
            else if ( (a<sub1.size()) && (b >= sub2.size()) ){
                data[i] = sub1[a];
                a++;
            }
        }

        
    }
    
}

int main(){
    vector<int> data;
    data.push_back(4);
    data.push_back(18);
    data.push_back(2);
    data.push_back(1);
    data.push_back(7);
    for (int i=0; i<data.size(); i++){
        cout << data[i] << " ";
    }
    cout << endl;
    MergeSortSubVector(data, 0,  data.size()-1);

    for (int i=0; i<data.size(); i++){
        cout << data[i] << " ";
    }
}