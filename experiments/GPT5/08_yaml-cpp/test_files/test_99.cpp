// File: ./TestProjects/yaml-cpp/test/streamcharsource_test_99.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "stream.h"
#include "streamcharsource.h"

namespace {

class StreamCharSourceTest_99 : public ::testing::Test {};

TEST_F(StreamCharSourceTest_99, OperatorNotMatchesNegatedBoolConversionOnEmptyStream_99) {
  std::stringstream ss;
  ss.str(std::string{});  // empty

  YAML::Stream stream(ss);
  YAML::StreamCharSource src(stream);

  // Contract-style check: operator! should reflect logical negation of truthiness.
  EXPECT_EQ(!src, !static_cast<bool>(src));

  // Idempotent: repeated calls should be consistent (no observable mutation).
  const bool first = !src;
  const bool second = !src;
  EXPECT_EQ(first, second);
}

TEST_F(StreamCharSourceTest_99, OperatorNotMatchesNegatedBoolConversionOnNonEmptyStream_99) {
  std::stringstream ss;
  ss.str("x");

  YAML::Stream stream(ss);
  YAML::StreamCharSource src(stream);

  EXPECT_EQ(!src, !static_cast<bool>(src));

  const bool first = !src;
  const bool second = !src;
  EXPECT_EQ(first, second);
}

TEST_F(StreamCharSourceTest_99, OperatorNotIsCallableOnConstInstance_99) {
  std::stringstream ss;
  ss.str("data");

  YAML::Stream stream(ss);
  const YAML::StreamCharSource src(stream);

  // Compile-time / const-correctness check (runtime expectation is consistency).
  EXPECT_EQ(!src, !static_cast<bool>(src));
}

TEST_F(StreamCharSourceTest_99, OperatorNotReflectsErrorStateStream_99) {
  std::stringstream ss;
  ss.str("x");
  ss.setstate(std::ios::failbit);  // put the underlying stream in an error state

  YAML::Stream stream(ss);
  YAML::StreamCharSource src(stream);

  // We don't assume how YAML::StreamCharSource interprets stream errors;
  // we only assert operator! is consistent with bool conversion.
  EXPECT_EQ(!src, !static_cast<bool>(src));
}

}  // namespace
