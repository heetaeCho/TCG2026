// File: yaml-cpp/test/ostream_wrapper_pos_test_29.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <cstring>
#include <sstream>
#include <string>

#include "yaml-cpp/ostream_wrapper.h"

namespace {

class OstreamWrapperPosTest_29 : public ::testing::Test {};

TEST_F(OstreamWrapperPosTest_29, DefaultConstructor_PosStartsAtZero_29) {
  YAML::ostream_wrapper ow;
  EXPECT_EQ(ow.pos(), static_cast<std::size_t>(0));
}

TEST_F(OstreamWrapperPosTest_29, StreamConstructor_PosStartsAtZero_29) {
  std::ostringstream oss;
  YAML::ostream_wrapper ow(oss);
  EXPECT_EQ(ow.pos(), static_cast<std::size_t>(0));
}

TEST_F(OstreamWrapperPosTest_29, WriteString_IncreasesPosByStringSize_29) {
  YAML::ostream_wrapper ow;

  const std::size_t before = ow.pos();
  const std::string s = "abc";
  ow.write(s);

  EXPECT_EQ(ow.pos(), before + s.size());
}

TEST_F(OstreamWrapperPosTest_29, WriteCharBuffer_IncreasesPosByGivenSize_29) {
  YAML::ostream_wrapper ow;

  const char buf[] = {'x', 'y', 'z', 'w'};
  const std::size_t n = sizeof(buf) / sizeof(buf[0]);

  const std::size_t before = ow.pos();
  ow.write(buf, n);

  EXPECT_EQ(ow.pos(), before + n);
}

TEST_F(OstreamWrapperPosTest_29, WriteEmptyString_DoesNotChangePos_29) {
  YAML::ostream_wrapper ow;

  const std::size_t before = ow.pos();
  ow.write(std::string());
  EXPECT_EQ(ow.pos(), before);

  ow.write("");
  EXPECT_EQ(ow.pos(), before);
}

TEST_F(OstreamWrapperPosTest_29, WriteBufferSizeZero_DoesNotChangePos_29) {
  YAML::ostream_wrapper ow;

  const std::size_t before = ow.pos();
  const char* ptr = "data";
  ow.write(ptr, 0);
  EXPECT_EQ(ow.pos(), before);

  // Also verify it's safe with an arbitrary pointer when size is zero.
  const char* arbitrary = nullptr;
  ow.write(arbitrary, 0);
  EXPECT_EQ(ow.pos(), before);
}

TEST_F(OstreamWrapperPosTest_29, MultipleWrites_PosIsMonotonicAndAccumulates_29) {
  YAML::ostream_wrapper ow;

  EXPECT_EQ(ow.pos(), static_cast<std::size_t>(0));

  ow.write("hi");
  const std::size_t after1 = ow.pos();
  EXPECT_GE(after1, static_cast<std::size_t>(0));
  EXPECT_EQ(after1, static_cast<std::size_t>(2));

  ow.write(std::string(" there"));
  const std::size_t after2 = ow.pos();
  EXPECT_GE(after2, after1);
  EXPECT_EQ(after2, after1 + std::strlen(" there"));

  const char tail[] = "!";
  ow.write(tail, 1);
  const std::size_t after3 = ow.pos();
  EXPECT_GE(after3, after2);
  EXPECT_EQ(after3, after2 + 1);
}

}  // namespace
