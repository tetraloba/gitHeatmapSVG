#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
string MONTHS[13] = {"Dmy", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
struct DailyCommit{
    int c;
    int y;
    int m;
    int d;
};

int monthToInt(string);

int main(int argc, char *argv[]){
    if (argc < 3) {
        cerr << "too few arguments" << endl;
    }
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    vector<DailyCommit> v;
    while (fin) {
        DailyCommit tmp;
        string tmp_m;
        fin >> tmp.c >> tmp.y >> tmp_m >> tmp.d;
        tmp.m = monthToInt(tmp_m);
        v.push_back(tmp);
    }
    fin.close();

    for (DailyCommit dc : v) {
        fout << dc.y << ' ' << dc.m << ' ' << dc.d << ' ' << dc.c << endl;
    }
    fout.close();

    return 0;
}

int monthToInt(string m){
    for (int i = 1; i <= 12; i++) {
        if (MONTHS[i] == m) {
            return i;
        }
    }
    return 0;
}