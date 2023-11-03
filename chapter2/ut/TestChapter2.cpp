#include "../Chapter2.hpp"
#include "CppUTest/TestHarness.h"
#include <sstream>
#include <vector>

TEST_GROUP(TestChapter2){

};

TEST(TestChapter2, canReadSequence) {
  std::vector<std::string> vec = {"-1", "-1", "-1", "+1",
                                  "+1", "-1", "+1", "+1"};
  std::stringstream ss{vec};
  Sequence seq = readSequence(ss);
  EXPECT_EQUAL(8, seq.size())
};