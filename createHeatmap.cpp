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
    uint c;
    tm date;
};

bool sameDay(tm, tm);
int monthToInt(string);
RGB commitRGB(uint);

int main(int argc, char *argv[]){
    if (argc < 3) {
        cerr << "too few arguments" << endl;
    }
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    fout.fill('0');

    vector<DailyCommit> v(7 * WEEK_NUM);
    string sl;
    time_t timer = time(nullptr);
    const tm *now = localtime(&timer);
    tm thisWeekend = {0, 0, 0, now->tm_mday + (6 - now->tm_wday), now->tm_mon, now->tm_year};
    mktime(&thisWeekend);

    DailyCommit tmp;
    uint tmp_c;
    int tmp_y, tmp_d;
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
    rect({-40, -20}, {1100, 160}, {10, 14, 18}, fout);
    // for (DailyCommit dc : v) {
    //     time_t dc_timer = mktime(&dc.date);
    //     fout << dc.c << " commits  " << ctime(&dc_timer) << endl; // debug
    // }
    double first[12];
    for (int i = 0; i < WEEK_NUM; i++) {
        for (int j = 0; j < 7; j++) {
            rect({1041.0 - 20 * i, 121.0 - 20 * j}, {1059.0 - 20 * i, 139.0 - 20 * j}, commitRGB(v[i * 7 + j].c), fout);
            if (v[i * 7 + j].date.tm_mday == 1) {
                first[v[i * 7 + j].date.tm_mon] = 1041.0 - 20 * i;
            }
        }
    }
    RGB rgb_text = {180, 180, 180};
    uint size_text = 18;
    text({-35, 40}, "Mon", rgb_text, size_text, fout);
    text({-35, 80}, "Wed", rgb_text, size_text, fout);
    text({-35, 120}, "Fri", rgb_text, size_text, fout);
    for (int i = 0; i < 12; i++) {
        text({first[i], -2}, MONTHS[i + 1], rgb_text, size_text, fout);
    }
    finish(fout);
    fout.close();

    return 0;
}

/* commit数に対応したRGBを返す */
RGB commitRGB(uint commit){
    if (commit) {
        return RGB{0, 70 + min(20 * (commit / 3), (uint)155), 0};
    } else {
        return RGB{25, 25, 25};
    }
}
/* 月を表す文字列をint値に変換する。(1月 = Jan = 0) */
int monthToInt(string m){
    for (int i = 1; i <= 12; i++) {
        if (MONTHS[i] == m) {
            return i;
        }
    }
    return 0;
}
/* a と b が同じ日ならtrue。(tm_year, tm_mon, tm_mdayを比較) */
bool sameDay(tm a, tm b){
    // cout << a.tm_year << ':' << b.tm_year << ' ' << a.tm_mon << ':' << b.tm_mon << ' ' << a.tm_mday << ':' << b.tm_mday << endl; // debug
    if (a.tm_year == b.tm_year && a.tm_mon == b.tm_mon && a.tm_mday == b.tm_mday) {
        return true;
    }
    return false;
}