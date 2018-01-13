// reference:
// http://blog.csdn.net/mohuak/article/details/78845675

#include <string.h>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

struct v {
  char vn;
  string vt;
  // v(string vn1, string vt1) {vn = vn1, vt = vt1;}
};

struct sel {
  char v, t;
  int ch;
};

vector<char> s1, s2;  // s1非终结符， s2终结符
vector<v> s3;
vector<sel> s4;
string result;
stack<char> room;

string find(char v, char t) {
  for (auto i : s4) {
    if (i.v == v && i.t == t) return s3[i.ch - 1].vt;
  }
  return "";
}
bool in_v(char v) {
  for (auto i : s1) {
    if (i == v) return true;
  }
  return false;
}

bool in_t(char t) {
  for (auto i : s2) {
    if (i == t) return true;
  }
  return false;
}

int main() {
  char start;
  cin >> start;
  int s1num, s2num, s3num, s4num;
  cin >> s1num;
  for (int i = 0; i < s1num; i++) {
    char tmp;
    cin >> tmp;
    s1.push_back(tmp);
  }
  cin >> s2num;
  for (int i = 1; i <= s2num; i++) {
    char tmp;
    cin >> tmp;
    s2.push_back(tmp);
  }
  s2num++;
  s2.push_back('#');
  cin >> s3num;
  for (int i = 1; i <= s3num; i++) {
    char vn;
    string vt;
    int n;
    cin >> n;
    cin >> vn;
    cin >> vt;
    v tmp;
    tmp.vn = vn, tmp.vt = vt;
    s3.push_back(tmp);
  }
  cin >> s4num;
  for (int i = 1; i <= s4num; i++) {
    char v, t;
    int num, n;
    cin >> n, cin >> v >> t, cin >> num;
    sel tmp;
    tmp.v = v, tmp.t = t, tmp.ch = num;
    s4.push_back(tmp);
  }
  cin >> result;
  room.push('#');
  room.push(start);
  int tag = 0;
  while (1) {
    stack<char> tmp = room;
    cout << "#";
    for (int i = 0; i < tag; ++i) {
      cout << result[i];
    }
    cout << " & ";
    while (!tmp.empty()) {
      cout << tmp.top();
      tmp.pop();
    }
    cout << endl;
    if (in_v(room.top())) {
      string k = find(room.top(), result[tag]);
      room.pop();
      for (int i = k.size() - 1; i >= 0; i--) {
        if (k[i] == 'k') continue;
        room.push(k[i]);
      }
    } else if (room.top() == '#')
      break;
    else {
      tag++;
      room.pop();
    }
  }

  return 0;
}