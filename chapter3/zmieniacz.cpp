
#include <cassert>
#include <iostream>
#include <sstream>
#include <cstdint>

int main(int argc, char *argv[]) {
  using namespace std;
  string message{};
  string generator{};
  cin >> message;
  cin >> generator;
  uint32_t pos{};

  if (argc == 2) {
    istringstream iss{argv[1]};
    iss >> pos;
    assert(pos < message.size());
  } else {
    cout << message << "\n";
    cout << generator;
    exit(0);
  }

  if (message[pos] == '0') {
    message[pos] = '1';
  } else {
    message[pos] = '0';
  }
  cout << message << "\n";
  cout << generator;

  return 0;
}
