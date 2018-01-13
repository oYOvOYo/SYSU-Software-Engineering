#include <array>
#include <cctype>
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

struct {
  int number;
  string str[10];
} keywords = {3, "int", "main", "return"};  //关键词

struct {
  int number;
  string str[10];
} operators = {5, "+", "*", "=", "+=", "*="};  //运算符

struct {
  int number;
  string str[10];
} boundaries = {6, "(", ")", "{", "}", ",", ";"};  //分界符

struct {
  int number;
  string str[100];
} identifieres = {0};  //标识符

struct {
  int number;
  string str[100];
} Unsigned_integer = {0};  //无符号整数

bool isKeyChar(char ch) {
  if (isspace(ch)) return true;

  for (int i = 0; i < operators.number; i++) {
    if (operators.str[i].find(ch) != string::npos) return true;
  }

  for (int i = 0; i < boundaries.number; i++) {
    if (boundaries.str[i].find(ch) != string::npos) return true;
  }

  return false;
}

bool is_identifieres(const string& str) {
  if (str.empty()) return false;
  if (!isalpha(str[0])) return false;
  for (auto ch : str) {
    if (!isalnum(ch)) return false;
  }
  return true;
}

bool is_Unsigned_integer(const string& str) {
  if (str.empty()) return false;
  for (auto ch : str) {
    if (!isdigit(ch)) return false;
  }
  return true;
}
// check can be process
bool can_process(const string& str) {
  for (int i = 0; i < keywords.number; i++) {
    if (keywords.str[i] == str) {
      return true;
    }
  }

  for (int i = 0; i < operators.number; i++) {
    if (operators.str[i] == str) {
      return true;
    }
  }

  for (int i = 0; i < boundaries.number; i++) {
    if (boundaries.str[i] == str) {
      return true;
    }
  }

  for (int i = 0; i < identifieres.number; i++) {
    if (identifieres.str[i] == str) {
      return true;
    }
  }

  for (int i = 0; i < Unsigned_integer.number; i++) {
    if (Unsigned_integer.str[i] == str) {
      return true;
    }
  }

  if (is_identifieres(str)) {
    return true;
  }

  if (is_Unsigned_integer(str)) {
    return true;
  }

  return false;
}
// find properol str type
void process_str(string& str) {
  // cout << str << endl;
  for (int i = 0; i < keywords.number; i++) {
    if (keywords.str[i] == str) {
      cout << "<1," << i << ">";
      str = "";
    }
  }

  for (int i = 0; i < operators.number; i++) {
    if (operators.str[i] == str) {
      cout << "<2," << i << ">";
      str = "";
    }
  }

  for (int i = 0; i < boundaries.number; i++) {
    if (boundaries.str[i] == str) {
      cout << "<3," << i << ">";
      str = "";
    }
  }

  for (int i = 0; i < identifieres.number; i++) {
    if (identifieres.str[i] == str) {
      cout << "<4," << i << ">";
      str = "";
    }
  }

  for (int i = 0; i < Unsigned_integer.number; i++) {
    if (Unsigned_integer.str[i] == str) {
      cout << "<5," << i << ">";
      str = "";
    }
  }

  if (is_identifieres(str)) {
    cout << "<4," << identifieres.number << ">";
    identifieres.str[identifieres.number] = str;
    identifieres.number++;
    str = "";
  }

  if (is_Unsigned_integer(str)) {
    cout << "<5," << Unsigned_integer.number << ">";
    Unsigned_integer.str[Unsigned_integer.number] = str;
    Unsigned_integer.number++;
    str = "";
  }
}

int main() {
  char ch;
  string before = "";

  while (scanf("%c", &ch), ch != '#') {
      if (isspace(ch)) {
        process_str(before);
      } else {
      if (can_process(before + ch)) {
        before += ch;
      } else {
        // use longest principle
        process_str(before);
        before += ch;
      }
    }
  }
  // process last when # enter
  process_str(before);

  cout << endl;
  cout << "identifieres:";
  for (int i = 0; i < identifieres.number; i++) {
    cout << (i == 0 ? "" : " ") << identifieres.str[i];
  }
  cout << endl;
  cout << "Unsigned_integer:";
  for (int i = 0; i < Unsigned_integer.number; i++) {
    cout << (i == 0 ? "" : " ") << Unsigned_integer.str[i];
  }
}
