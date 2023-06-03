#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include "SVG.h"
#define WEEK_NUM 53 // 53週分描画する
using namespace std;
string MONTHS[13] = {"Dmy", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
struct DailyCommit{
    int c;
    tm date;
};

bool sameDay(tm, tm);

int monthToInt(string);

int main(int argc, char *argv[]){
    if (argc < 3) {
        cerr << "too few arguments" << endl;
    }
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    vector<DailyCommit> v(7 * WEEK_NUM);
    string sl;
    time_t timer = time(nullptr);
    const tm *now = localtime(&timer);
    tm thisWeekend = {0, 0, 0, now->tm_mday + (6 - now->tm_wday), now->tm_mon, now->tm_year};
    mktime(&thisWeekend);

    DailyCommit tmp;
    int tmp_c, tmp_y, tmp_d;
    string tmp_m;
    if (getline(fin, sl)) {
        istringstream iss(sl);
        iss >> tmp_c >> tmp_y >> tmp_m >> tmp_d;
        tmp.date = {0, 0, 0, tmp_d, monthToInt(tmp_m) - 1, tmp_y - 1900};
    }
    for (int i = 0; i < 7 * WEEK_NUM; i++) {
        v[i].date = {0, 0, 0, thisWeekend.tm_mday - i, thisWeekend.tm_mon, thisWeekend.tm_year};
        mktime(&v[i].date);
        if (sameDay(tmp.date, v[i].date)) {
            v[i].c = tmp_c;
            if (getline(fin, sl)) {
                istringstream iss(sl);
                iss >> tmp_c >> tmp_y >> tmp_m >> tmp_d;
                tmp.date = {0, 0, 0, tmp_d, monthToInt(tmp_m) - 1, tmp_y - 1900};
            }
        } else {
            v[i].c = 0;
        }
    }
    fin.close();

    start(Pos{-40, -20}, Pos{1100, 160}, "px", fout);
    for (DailyCommit dc : v) {
        time_t dc_timer = mktime(&dc.date);
        fout << dc.c << " commits  " << ctime(&dc_timer) << endl;
    }
    for (int i = 0; i < WEEK_NUM; i++) {
        for (int j = 0; j < 7; j++) {
            ;
        }
    }
    finish(fout);
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

bool sameDay(tm a, tm b){
    // cout << a.tm_year << ':' << b.tm_year << ' ' << a.tm_mon << ':' << b.tm_mon << ' ' << a.tm_mday << ':' << b.tm_mday << endl; // debug
    if (a.tm_year == b.tm_year && a.tm_mon == b.tm_mon && a.tm_mday == b.tm_mday) {
        return true;
    }
    return false;
}