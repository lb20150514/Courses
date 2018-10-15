#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <climits>
#include <ctime>
#include <cassert>

using namespace std;

void swap(int vec[], const int i, const int j);
int partition(int vec[], const int len, const int p);
int choosePivot(int vec[], const int len);
int median(int temp[5]);
int Rselect(int vec[], const int len, const int i);
int Dselect(int vec[], const int len, const int i);

void swap(int vec[], const int i, const int j){
    int temp = vec[j];
    vec[j] = vec[i];
    vec[i] = temp;
}

int partition(int vec[], const int len, const int p){
    swap(vec, p, 0);
    int i = 1, j = len - 1;
    while (i <= j){
        while (vec[i] < vec[0] && i < len - 1) i++;
        while (vec[j] >= vec[0] && j > 0) j--;
        if (i < j) swap(vec, i, j);
        else break;
    }
    swap(vec, 0, j);
    return j;
}

int Rselect(int vec[], const int len, const int i){
    if (len == 1) return vec[0];
    int j = partition(vec, len, len / 2);
    if (j == i) return vec[j];
    if (j > i){
        int new_vec[j];
        for (int temp = 0; temp < j; temp ++) new_vec[temp] = vec[temp];
        return Rselect(new_vec, j, i);
    }
    int new_len = len - j - 1,  new_vec[new_len];
    for (int temp = 0; temp < new_len; temp ++) new_vec[temp] = vec[j + temp + 1];
    return Rselect(new_vec, new_len, i - j - 1);
}

int median(int temp[5]){
	for (int i = 0; i < 4; i++){
        int minimum = temp[i], min_loc = i;
        for (int j = i; j < 5; j++){
            if (temp[j] < minimum){
                minimum = temp[j];
                min_loc = j;
            }
        }
        swap(temp, i, min_loc);
    }
    return temp[2];
}

int choosePivot(int vec[], const int len){
    int C[len / 5], temp[5] = {0}, p = 0;
    if (len < 5) return len / 2;
    for (int i = 0; i * 5 < len; i ++){
        for (int j = 0; j < 5; j++) temp[j] = vec[i * 5 + j];
        C[i] = median(temp);
    }
    int pivot = Dselect(C, len / 5, len / 10);
    while (p < len){
        if (vec[p] == pivot) break;
        p++;
    }
    return p;
}

int Dselect(int vec[], const int len, const int i){
    if (len == 1) return vec[0];
    int p = choosePivot(vec, len);
    int j = partition(vec, len, p);
    if (j == i) return vec[j];
    if (j > i){
        int new_vec[j];
        for (int temp = 0; temp < j; temp ++) new_vec[temp] = vec[temp];
        return Dselect(new_vec, j, i);
    }
    int new_len = len - j - 1,  new_vec[new_len];
    for (int temp = 0; temp < new_len; temp ++)
        new_vec[temp] = vec[j + temp + 1];
    return Dselect(new_vec, new_len, i - j - 1);
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
	ofstream out_file;
    out_file.open("sdata.csv");
	for (int it = 1; it <= 1000; it++){
		int time[3] = {0}, len = it * 100;
		int vec1[len], vec2[len], vec3[len];
		srand48(it);
		for (int generate = 0; generate < len; generate++) 
			vec1[generate] = vec2[generate] = vec3[len] = generate;//mrand48();
		for (int test = 0; test < 10; test ++){
			int start = 0, finish = 0;
			start = clock();
			Rselect(vec1, len, test);
			finish = clock();
        	time[0] += finish - start;
			start = clock();
			Dselect(vec2, len, test);
			finish = clock();
			time[1] += finish - start;
			start = clock();
			quick_inplace(vec3, 0, len - 1);
			finish = clock();
			time[2] += finish - start;
		}
		time[0] = time[0]; /// 10;
		time[1] = time[1]; /// 10;
		time[2] = time[2]; /// 10;
		out_file << time[0] << ',' << time[1] << "," << time[2] <<endl;
	}
	out_file.close();
}
