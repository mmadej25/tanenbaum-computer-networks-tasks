#include <array>
#include <mutex>

class Channel {
public:
  bool checkChannel() const;
  void accuire();
  void release();

private:
  bool channelFree{true};
  static std::mutex channelMutex;
};

/*
Algorithm CSMA/CD
1) Listen channel condition
2) If free send frame
3) If not wait until free
4) If collision wait some time
How can I model collisions i don't know how to do it?
*/
class EthernetStation {
public:
  EthernetStation(Channel *ptr, int id) : channel{ptr}, stationId{id} {}
  void listen();
  void checkChannel();
  void sendData();

private:
  int drawTime();
  Channel *channel{nullptr};
  int stationId{};
  int collisionCounter{0};
};

class Simulator {
private:
  static constexpr int numOfStations{10000};
  std::array<EthernetStation, numOfStations> allStations;
};