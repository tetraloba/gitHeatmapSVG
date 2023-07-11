#include <fstream>
#include <string>
using namespace std;

typedef unsigned int uint;
struct Pos{
    double x;
    double y;
};
struct RGB{
    uint r;
    uint g;
    uint b;
};

void start(Pos, Pos, string, ofstream&); //SVGのヘッダを出力 指定座標でキャンバスサイズとビューポイント
void finish(ofstream&); //SVGタグを閉じる
void line(Pos, Pos, RGB, ofstream&); //直線を出力
void rect(Pos, Pos, RGB, ofstream&); //矩形(長方形)を出力
void circle(Pos, Pos, RGB, ofstream&); //円を出力
void text(Pos, string, RGB, uint, ofstream&); //文字を出力