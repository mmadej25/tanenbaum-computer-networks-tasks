#include <array>
#include <fstream>
#include <iostream>
#include <numeric>
#include <span>
#include <thread>
#include <valarray>
#include <vector>

constexpr int sequenceLength{8};
constexpr int numOfStations{4};

using Sequence = std::valarray<int>;
using SequenceContainer = std::array<Sequence, numOfStations>;
using BitContainer = std::array<int, numOfStations>;

Sequence readSequence(std::istream &in) {
  std::array<int, sequenceLength> seq;
  for (auto &val : seq) {
    in >> val;
  }
  Sequence out{seq.begin(), seq.size()};
  return out;
}

SequenceContainer readAllStationsSequences(std::istream &in) {
  std::cout << "We will read sequences for 4 stations\n";
  SequenceContainer container;
  for (auto &sequence : container) {
    sequence = readSequence(in);
  }
  return container;
}

BitContainer readBits(std::istream &in) {
  std::cout << "Give 4 bits to transmmit, one bit per one station\n";
  BitContainer bits;
  for (auto &bit : bits) {
    in >> bit;
  }
  return bits;
}

void printSequence(std::span<int> sequence) {
  for (auto &val : sequence) {
    std::cout << val << "\t";
  }
  std::cout << std::endl;
}

void printContainer(SequenceContainer container) {
  for (auto &sequence : container) {
    printSequence(sequence);
    std::cout << std::endl;
  }
}

void transmiter(Sequence sequence, int bitToSend, Sequence &outSequence) {
  int mult{1};
  if (bitToSend == 0) {
    mult = -1;
  }
  outSequence = sequence;
  std::valarray<int> multi(mult, sequenceLength);
  outSequence *= multi;
}

void receiver(Sequence &sequence, Sequence &receivedSignal, int &bit) {
  std::valarray<int> temp = sequence * receivedSignal;
  bit = temp.sum() / sequenceLength;
  if (bit == -1)
    bit = 0;
}

Sequence makeCombinedSignal(SequenceContainer &container) {
  Sequence signal(0, sequenceLength);
  for (auto sequence : container) {
    signal += sequence;
  }
  return signal;
}

auto main() -> int {
  std::ifstream file{"sequences.txt"};
  if (not file)
    return 1;

  SequenceContainer inputSequences = readAllStationsSequences(file);
  std::cout << "Input sequences from file:\n";
  printContainer(inputSequences);

  BitContainer inputBits = readBits(std::cin);
  SequenceContainer outSequences{};

  for (std::size_t i{0}; i < inputSequences.size(); ++i) {
    outSequences[i] = std::valarray<int>(0, sequenceLength);
    transmiter(inputSequences[i], inputBits[i], outSequences[i]);
  }

  std::cout << "Sequences from TX:\n";
  printContainer(outSequences);

  std::cout << "Combining signal\n";
  Sequence signal = makeCombinedSignal(outSequences);

  std::cout << "Combined signal to send\n";
  printSequence(signal);

  BitContainer outputBits{};
  for (std::size_t i{0}; i < outSequences.size(); ++i) {
    receiver(inputSequences[i], signal, outputBits[i]);
  }

  std::cout << "Output bits:\n";
  printSequence(outputBits);

  if (std::equal(std::begin(inputBits), std::end(inputBits),
                 std::begin(outputBits))) {
    std::cout << "Test OK Bits are equal" << std::endl;
  } else {
    std::cout << "OPSS FAILURE Bits are not equal" << std::endl;
  }
  return 0;
}