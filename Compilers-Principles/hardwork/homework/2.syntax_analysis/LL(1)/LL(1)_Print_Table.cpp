// reference
// http://blog.csdn.net/lichen_yun/article/details/78740265

#include <string.h>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

#define MAXSIZE 1000

string result[MAXSIZE][MAXSIZE];
string expr[MAXSIZE];
vector<char> vt;
vector<char> vn;

int findrow(char ch) {
  int n = vn.size();
  for (int i = 0; i < n; ++i) {
    if (vn[i] == ch) return i;
  }
}
int findcol(char ch) {
  int n = vt.size();
  for (int i = 0; i < n; ++i) {
    if (vt[i] == ch) return i;
  }
}
int main() {
  char start;
  char ch;
  // initialize
  for (int i = 0; i < MAXSIZE; ++i) expr[i] = "";
  for (int i = 0; i < MAXSIZE; ++i) {
    for (int j = 0; j < MAXSIZE; ++j) {
      result[i][j] = "";
    }
  }
  //  vt and vn
  int vnnum, vtnum, exprnum, pronum;
  cin >> start;
  cin >> vnnum;
  for (int i = 0; i < vnnum; ++i) {
    cin >> ch;
    vn.push_back(ch);
  }
  cin >> vtnum;
  for (int i = 0; i < vtnum; ++i) {
    cin >> ch;
    vt.push_back(ch);
  }
  vt.push_back('#');
  vtnum++;
  //  expression
  cin >> exprnum;
  int seq;
  string str;
  for (int i = 0; i < exprnum; ++i) {
    cin >> seq >> ch >> str;
    expr[seq] = str;
  }
  //  production expression
  char vnchar, vtchar;
  int relseq;
  cin >> pronum;
  for (int i = 0; i < pronum; ++i) {
    cin >> seq >> vnchar >> vtchar >> relseq;
    result[findrow(vnchar)][findcol(vtchar)] = expr[relseq];
  }
  //  print the result
  int widthOccupy = 5;
  cout << setw(widthOccupy) << ' ';
  for (int i = 0; i < vtnum; ++i) cout << setw(widthOccupy) << vt[i];
  cout << endl;
  for (int i = 0; i < vnnum; ++i) {
    cout << setw(widthOccupy) << vn[i];
    for (int j = 0; j < vtnum; ++j) {
      cout << setw(widthOccupy) << result[findrow(vn[i])][findcol(vt[j])];
    }
    cout << endl;
  }
  return 0;
}