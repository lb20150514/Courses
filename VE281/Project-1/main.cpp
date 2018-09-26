#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <climits>
#include <ctime>
#include <cassert>

using namespace std;

void swap(int vec[], const int i,  const int j){
    int temp = vec[j];
    vec[j] = vec[i];  
    vec[i] = temp;
}

void bubble_sort(int vec[], const int len){
    for (int i = 0; i < len - 1; i++){
        for (int j = 0; j < len - i - 1; j++){
            if (vec[j] > vec[j + 1])
                swap(vec, j, j + 1); 
        }
    }
}

void insertion_sort(int vec[], const int len){
    for (int i = 1; i < len; i++){
        int temp = vec[i], j = i - 1;
        while (j >= 0){
            if (vec[j] > temp){
                vec[j + 1] = vec[j];
                j--;
            }
            else break;
        }
        if (j >= 0) vec[j + 1] = temp;
        else vec[0] = temp;
    }
}

void selection_sort(int vec[], const int len){
    for (int i = 0; i < len - 1; i++){
        int minimum = vec[i], min_loc = i;
        for (int j = i; j < len; j++){
            if (vec[j] < minimum){
                minimum = vec[j];
                min_loc = j;
            }
        }
        swap(vec, i, min_loc);
    }
} 

void merge(int vec[], const int left, const int mid, const int right){
    int temp[right - left + 1];
    int p1 = left, p2 = mid + 1;
    for (int i = 0; i <= right - left; i++){
       if (p1 <= mid && p2 <= right){
           if (vec[p1] <= vec[p2]) temp[i] = vec[p1++];
           else temp[i] = vec[p2++];
       }
       else if (p1 > mid) temp[i] = vec[p2++];
       else temp[i] = vec[p1++];
    }
    for (int i = left; i <= right; i++)
        vec[i] = temp[i - left];
}

void merge_sort(int vec[], const int left, const int right){
    if (left >= right) return;
    int mid = (left + right) / 2;
    merge_sort(vec, left, mid);
    merge_sort(vec, mid + 1, right);
    merge(vec, left, mid, right);
}

int partition_extra(int vec[], const int left, const int right){
    int temp[right - left + 1];
    int pivotat = left, i = left + 1, ileft = 0, iright = right - left;
    while (ileft < iright && i <= right){
        if (vec[i] <= vec[pivotat]) temp[ileft++] = vec[i++];
        else temp[iright--] = vec[i++];
    }
    temp[ileft] = vec[pivotat];
    for (int j = left; j <= right; j++) vec[j] = temp[j - left];
    return (left + ileft);
}

void quick_extra(int vec[], const int left, const int right){
    if (left >= right) return;
    int pivotat = partition_extra(vec, left, right);
    quick_extra(vec, left, pivotat - 1);
    quick_extra(vec, pivotat + 1, right);
}

int partition_inplace(int vec[], const int left, const int right){
  swap(vec, (int)(left + right) / 2, left);
  int pivotat = left, i = left + 1, j = right;
  while (i <= j){
    while (vec[i] < vec[pivotat] && i < right) i++;
    while (vec[j] >= vec[pivotat] && j > left) j--;
    if (i < j) swap(vec, i, j);
    else break;
  }
  swap(vec, left, j);
  return j;
}

void quick_inplace(int vec[], const int left, const int right){
  if (left >= right) return;
  int pivotat = partition_inplace(vec, left, right);
  quick_inplace(vec, left, pivotat - 1);
  quick_inplace(vec, pivotat + 1, right);
}

int main(){
    //data input
    int sort_type, len;
    cin >> sort_type;
    cin >> len;
    int vec[len];
    for (int i = 0; i < len; i++)
        cin >> vec[i];

    //choose the method to sort
    switch(sort_type){
        case 0: 
            bubble_sort(vec, len);
            break;
        case 1: 
            insertion_sort(vec, len);
            break;
        case 2: 
            selection_sort(vec, len);
            break;
        case 3: 
            merge_sort(vec, 0, len - 1);
            break;
        case 4: 
            quick_extra(vec, 0, len - 1);
            break;
        case 5: 
            quick_in_place(vec, 0, len - 1);
            break;
        default: break;
    }
    for (int i = 0; i < len; i++)
        cout << vec[i] << endl;
}
