// TEST_ID: 514
#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "yaml-cpp/emitter.h"

namespace {

class EmitterSizeTest_514 : public ::testing::Test {};

TEST_F(EmitterSizeTest_514, DefaultConstructor_SizeInitiallyZero_514) {
  YAML::Emitter out;
  EXPECT_EQ(out.size(), 0u);
}

TEST_F(EmitterSizeTest_514, WriteEmptyString_DoesNotDecreaseSize_514) {
  YAML::Emitter out;

  const std::size_t before = out.size();
  out.Write(std::string());
  const std::size_t after = out.size();

  // We don't assume whether empty writes produce output, but size must not go backwards.
  EXPECT_GE(after, before);
}

TEST_F(EmitterSizeTest_514, WriteNonEmptyString_IncreasesSize_514) {
  YAML::Emitter out;

  const std::size_t before = out.size();
  out.Write(std::string("abc"));
  const std::size_t after = out.size();

  EXPECT_GT(after, before);
}

TEST_F(EmitterSizeTest_514, WriteChar_IncreasesSize_514) {
  YAML::Emitter out;

  const std::size_t before = out.size();
  out.Write('x');
  const std::size_t after = out.size();

  EXPECT_GT(after, before);
}

TEST_F(EmitterSizeTest_514, WriteCStringWithExplicitSize_IncreasesSize_514) {
  YAML::Emitter out;

  const std::size_t before = out.size();
  out.Write("hello", 5);
  const std::size_t after = out.size();

  EXPECT_GT(after, before);
}

TEST_F(EmitterSizeTest_514, NullptrWithZeroSize_DoesNotThrowAndDoesNotDecrease_514) {
  YAML::Emitter out;

  const std::size_t before = out.size();
  EXPECT_NO_THROW(out.Write(static_cast<const char*>(nullptr), 0));
  const std::size_t after = out.size();

  EXPECT_GE(after, before);
}

TEST_F(EmitterSizeTest_514, ExternalStream_SizeMatchesStreamLengthAfterWrites_514) {
  std::stringstream ss;
  YAML::Emitter out(ss);

  EXPECT_EQ(out.size(), ss.str().size());

  out.Write(std::string("abc"));
  EXPECT_EQ(out.size(), ss.str().size());

  out.Write(' ');
  EXPECT_EQ(out.size(), ss.str().size());

  out.Write("xyz", 3);
  EXPECT_EQ(out.size(), ss.str().size());
}

TEST_F(EmitterSizeTest_514, MultipleWrites_SizeIsMonotonicNonDecreasing_514) {
  YAML::Emitter out;

  const std::size_t s0 = out.size();
  out.Write(std::string("first"));
  const std::size_t s1 = out.size();

  out.Write(std::string("second"));
  const std::size_t s2 = out.size();

  out.Write('!');
  const std::size_t s3 = out.size();

  EXPECT_LE(s0, s1);
  EXPECT_LE(s1, s2);
  EXPECT_LE(s2, s3);
}

}  // namespace