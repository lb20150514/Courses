int Pass(int x){
    if (x >= 60) return 1;
    else return 0;
}

int Fail(int x){
    if (x < 60) return 1;
    else return 0;
}

int countArray(int A[], int numElements, int cntType){
    int i, cnt = 0;
    for (i = numElements - 1; i > 0; i--){
        switch (cntType){
            case '1': 
                cnt += Pass(A[i]);
                break;
            default: cnt += Fail(A[i]);
        }
    }
    return cnt;
}

int main(){
    int size = 20;
    int PassCnt, FailCnt;
    int testArray[20] = {55, 83, 30, 94, 22, 51, 54, 32, 69, 96, 
        80, 27, 61, 59, 100, 72, 66, 18, 6, 42};
    PassCnt = countArray(testArray, size, 1);
    FailCnt = countArray(testArray, size, -1);
}

