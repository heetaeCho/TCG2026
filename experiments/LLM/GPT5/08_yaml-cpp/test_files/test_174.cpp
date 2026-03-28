#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "stream.h"

namespace {

class StreamBoolTest_174 : public ::testing::Test {};

TEST_F(StreamBoolTest_174, InitiallyTrueEvenForEmptyInputStream_174) {
  std::istringstream input("");
  YAML::Stream stream(input);

  EXPECT_TRUE(static_cast<bool>(stream));
}

TEST_F(StreamBoolTest_174, BecomesFalseAfterExhaustingInput_174) {
  std::istringstream input("x");
  YAML::Stream stream(input);

  EXPECT_TRUE(static_cast<bool>(stream));

  // Consume at most a small bounded number of reads to avoid any risk of a hang.
  // Expect that once input is exhausted, the stream eventually becomes false.
  bool became_false = false;
  for (int i = 0; i < 16; ++i) {
    if (!static_cast<bool>(stream)) {
      became_false = true;
      break;
    }
    (void)stream.get();
  }

  EXPECT_TRUE(became_false);
  EXPECT_FALSE(static_cast<bool>(stream));
}

TEST_F(StreamBoolTest_174, RemainsTrueWhenBufferedCharExistsEvenIfUnderlyingStreamIsBad_174) {
  std::istringstream input("hi");
  YAML::Stream stream(input);

  // Trigger read-ahead/buffering (without assuming details beyond "peek is observable").
  (void)stream.peek();

  // Corrupt underlying stream state after buffering.
  input.setstate(std::ios::badbit);

  // Even if the underlying stream is not "good", a buffered non-EOF character should
  // keep operator bool() true (observable via the interface).
  EXPECT_TRUE(static_cast<bool>(stream));

  // Consume until it eventually becomes false (bounded).
  bool became_false = false;
  for (int i = 0; i < 32; ++i) {
    if (!static_cast<bool>(stream)) {
      became_false = true;
      break;
    }
    (void)stream.get();
  }

  EXPECT_TRUE(became_false);
  EXPECT_FALSE(static_cast<bool>(stream));
}

TEST_F(StreamBoolTest_174, FalseWhenExhaustedAndPeekBuffersEOF_174) {
  std::istringstream input("a");
  YAML::Stream stream(input);

  ASSERT_TRUE(static_cast<bool>(stream));
  (void)stream.get();   // consume the only character
  (void)stream.peek();  // encourage EOF to be observed/buffered, if applicable

  // After exhaustion, operator bool should eventually be false.
  bool became_false = false;
  for (int i = 0; i < 16; ++i) {
    if (!static_cast<bool>(stream)) {
      became_false = true;
      break;
    }
    (void)stream.peek();
    (void)stream.get();
  }

  EXPECT_TRUE(became_false);
  EXPECT_FALSE(static_cast<bool>(stream));
}

}  // namespace