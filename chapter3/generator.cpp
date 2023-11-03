#include <algorithm>
#include <bitset>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <numeric>
#include <span>
#include <vector>
#include <cstdint>

int main() {
  using namespace std;
  string message{};
  string generator{};

  cin >> message;
  cin >> generator;

  int nCrcBits = generator.size() - 1;
  message.append(nCrcBits, '0');
  uint32_t gen = stoul(generator, nullptr, 2);
  size_t pos{};

  string ss = message.substr(pos, generator.size());
  uint32_t sub{static_cast<uint32_t>(stoul(ss, nullptr, 2))};
  pos += generator.size();
  while (pos < message.size()) {
    int temp = __countl_zero(sub);
    sub = sub ^ gen;
    int temp2 = __countl_zero(sub);
    uint32_t jump = abs(temp2 - temp);
    uint32_t left = message.size() - pos;
    if (jump > left) {
      jump = left;
    }
    if (jump == 0) {
      jump = generator.size();
    }
    ss = message.substr(pos, jump);
    if (jump == generator.size()) {
      while (ss[0] == '0') {
        pos++;
        ss = message.substr(pos, jump);
      }
    }
    pos += jump;
    if (ss.empty()) {
      continue;
    }
    sub = (sub << jump) | (stoul(ss, nullptr, 2));
  }
  string strCRC{};
  for (int i{}; i < nCrcBits; i++) {
    if (sub & 0x1) {
      strCRC.push_back('1');
    } else {
      strCRC.push_back('0');
    }
    sub >>= 1;
  }
  reverse(strCRC.begin(), strCRC.end());
  message.replace(message.size() - nCrcBits, strCRC.size(), strCRC);
  cout << message;
  cout << "\n";
  cout << generator;
  return 0;
}
