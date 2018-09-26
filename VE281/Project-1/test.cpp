int partition_inplace(int vec[], int left, int right){
  swap(vec, (int)(left + right) / 2, left);
  int pivotat = left, i = left + 1; j = right;
  while (i < j){
    while (vec[i] < pivot && i < right) i++;
    while (vec[j] >= pivot && j > left + 1) j--;
    if (i < j) swap(vec, i, j);
  }
  swap(vec, left, j);
  return j;
}

void quicksort_inplace(int vec[], int left, int right){
  if (left >= right) return;
  int pivotat = partition_inplace(vec, left, right);
  quicksort_inplace(vec, left, pivotat - 1);
  quicksort_inplace(vec, pivotat +1, right);
}
