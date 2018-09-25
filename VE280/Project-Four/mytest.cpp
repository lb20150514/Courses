#include <fstream>

using namespace std;

int main(){
    ofstream fout("mytest.txt");
    fout << "39 22 33 37 38 37 38";
    fout.close();
}
