#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <climits>
#include <ctime>
#include <cassert>

using namespace std;

void swap(int vec[], const int i, const int j){
    int temp = vec[j];
    vec[j] = vec[i];
    vec[i] = temp;
}

int partition(int vec[], const int len){
    int min_index = 0;
    for (int temp = 0; temp < len; temp ++)
    {
        if (vec[temp] < vec[min_index]) min_index = temp;
    }
    swap(vec, 0, min_index);
    return min_index;
}

void selection_sort(int vec[], const int left, const int right){
    for (int i = 0; i < right - left - 1; i ++){
        int min_index = i;
        for (int j = i; j < right - left - 1; j++){
            if (vec[j] < vec[min_index]) min_index = j;
        }
        swap(vec, i, min_index);
    }
}

int Rselect(int vec[], const int len, const int i){
    if (len == 1) return vec[0];
    char debug;
    int index = len / 2;
    swap(vec, index, 0);
    int min_index = partition(vec, len);
    cin >> debug;
    if (min_index == i) return vec[min_index];
    if (min_index > i)
    {
        int new_vec[min_index];
        for (int temp = 0; temp < min_index; temp ++) new_vec[temp] = vec[temp];
        cout << 1;
        return Rselect(new_vec, min_index, i);
    }
    int new_len = len - min_index - 1,  new_vec[new_len];
    for (int temp = 0; temp < new_len; temp ++) new_vec[temp] = vec[temp + index + 1];
    cout << 2;
    return Rselect(new_vec, new_len, i - min_index);
}

int choosepivot(int vec[], const int len){
    return 0;
}

int Dselect(int vec[], int len, int i){
    if (len == 1) return vec[0];
    int index = choosepivot(vec, len), min_index = partition(vec, len);
    if (min_index == i) return vec[min_index];
    if (min_index > i)
    {
        int new_vec[min_index];
        for (int temp = 0; temp < min_index; temp ++) new_vec[temp] = vec[temp];
        return Dselect(new_vec, min_index, i);
    }
    int new_len = len - min_index - 1,  new_vec[new_len];
    for (int temp = 0; temp < new_len; temp ++) new_vec[temp] = vec[temp + index + 1];
    return Dselect(new_vec, new_len, i - min_index);
}

int main(){
    bool method;
    int len, i, ismall;
    cin >> method;
    cin >> len;
    cin >> i;
    int vec[len];
    for (int temp = 0; temp < len; temp ++) cin >> vec[temp];
    if (method) ismall = Dselect(vec, len, i);
    else ismall = Rselect(vec, len, i);
    cout << "The order-" << i << " item is " << ismall << endl;
}
