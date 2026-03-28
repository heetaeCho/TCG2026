// File: ./TestProjects/yaml-cpp/test/stream_test_73.cpp

#include <gtest/gtest.h>

#include <type_traits>

#include "stream.h"  // ./TestProjects/yaml-cpp/src/stream.h

namespace {

TEST(StreamTest_73, EofReturnsExpectedControlChar_73) {
  // Observable behavior: Stream::eof() returns a specific sentinel character.
  const char c = YAML::Stream::eof();
  EXPECT_EQ(static_cast<unsigned char>(c), static_cast<unsigned char>(0x04));
}

TEST(StreamTest_73, EofIsStableAcrossCalls_73) {
  // Boundary/consistency: repeated calls return the same value.
  const char a = YAML::Stream::eof();
  const char b = YAML::Stream::eof();
  const char c = YAML::Stream::eof();
  EXPECT_EQ(a, b);
  EXPECT_EQ(b, c);
}

TEST(StreamTest_73, EofIsNotNullChar_73) {
  // Defensive check: EOF sentinel should not be '\0' in this implementation.
  EXPECT_NE(YAML::Stream::eof(), '\0');
}

TEST(StreamTest_73, EofHasCharReturnType_73) {
  // Interface contract: return type is char (compile-time observable).
  static_assert(std::is_same_v<decltype(YAML::Stream::eof()), char>,
                "YAML::Stream::eof() must return char");
  SUCCEED();
}

}  // namespace
