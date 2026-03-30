// File: prog_start_test_112.cc
#include <climits>
#include "gtest/gtest.h"
#include "re2/prog.h"

namespace {

using re2::Prog;

class ProgStartTest_112 : public ::testing::Test {};

// Verifies the observable default state via the public accessor.
TEST_F(ProgStartTest_112, DefaultStartIsZero_112) {
  Prog p;
  EXPECT_EQ(p.start(), 0) << "Freshly constructed Prog should report start() == 0";
}

// Setting a start value should be observable via start().
TEST_F(ProgStartTest_112, SetStartUpdatesValue_112) {
  Prog p;
  p.set_start(5);
  EXPECT_EQ(p.start(), 5);
}

// Setting the start value multiple times should always reflect the latest set value.
TEST_F(ProgStartTest_112, MultipleSetStartOverwrites_112) {
  Prog p;
  p.set_start(3);
  EXPECT_EQ(p.start(), 3);
  p.set_start(42);
  EXPECT_EQ(p.start(), 42);
  p.set_start(-7);
  EXPECT_EQ(p.start(), -7);
}

// Boundary: large positive value round‑trips through the public API.
TEST_F(ProgStartTest_112, StartAcceptsIntMax_112) {
  Prog p;
  p.set_start(INT_MAX);
  EXPECT_EQ(p.start(), INT_MAX);
}

// Boundary: large negative value round‑trips through the public API.
TEST_F(ProgStartTest_112, StartAcceptsIntMin_112) {
  Prog p;
  p.set_start(INT_MIN);
  EXPECT_EQ(p.start(), INT_MIN);
}

}  // namespace
