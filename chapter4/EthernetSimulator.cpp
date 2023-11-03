#include "EthernetSimulator.hpp"
#include <cmath>
#include <iostream>
#include <random>

int EthernetStation::drawTime() {
  constexpr int maxCollision{10};
  if (collisionCounter == 10) {
    return 1023;
  }
  constexpr int minVal{0};
  int maxVal = std::pow(2, collisionCounter) - 1;

  std::random_device dev;
  std::mt19937 eng(dev());
  std::uniform_int_distribution<uint32_t> myDist(minVal, maxVal);
  return myDist(eng);
}

void EthernetStation::sendData() {
  std::cout << "Stacja nr: " << stationId << " ropoczela nadawanie/n";
}

void EthernetStation::listen() {
  while (true) {
  }
}

std::mutex Channel::channelMutex;

bool Channel::checkChannel() const { return channelFree; }

void Channel::accuire() { channelFree = false; }

void Channel::release() { channelFree = true; }
