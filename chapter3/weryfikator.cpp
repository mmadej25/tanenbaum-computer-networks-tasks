
#include <array>
#include <fstream>
#include <iostream>
#include <numeric>
#include <span>
#include <thread>
#include <valarray>
#include <vector>

int main() {
  using namespace std;
  string m{};
  string g{};

  cin >> m;
  cin >> g;

  int nCrcBits = g.size() - 1;
  uint32_t gen = stoul(g, nullptr, 2);
  size_t pos{};
  int count{nCrcBits};
  string ss = m.substr(pos, g.size());
  uint32_t sub{stoul(ss, nullptr, 2)};
  pos += g.size();
  while (pos < m.size()) {
    int temp = __countl_zero(sub);
    sub = sub ^ gen;
    int temp2 = __countl_zero(sub);
    int jump = abs(temp2 - temp);
    int left = m.size() - pos;
    if (jump > left) {
      jump = left;
    }
    if (jump != 0) {
      count = jump;
    } else {
      count = g.size();
    }
    ss = m.substr(pos, count);
    if (count == g.size()) {
      while (ss[0] == '0') {
        pos++;
        ss = m.substr(pos, count);
      }
    }
    pos += count;
    if (ss.empty()) {
      continue;
    }
    sub = (sub << count) | (stoul(ss, nullptr, 2));
  }

  if (sub == 0) {
    cout << "Dane przesłane poprawne\n";
  } else {
    cout << "Dane z błędem \n";
    cout << sub << "\n";
  }
  return 0;
}
