// TEST_ID: 587
#include <gtest/gtest.h>

#include <sstream>
#include <stdexcept>
#include <string>

#include "yaml-cpp/ostream_wrapper.h"

namespace {

class OstreamWrapperTest_587 : public ::testing::Test {};

TEST_F(OstreamWrapperTest_587, DefaultCtor_BufferStartsEmpty_587) {
  YAML::ostream_wrapper w;
  ASSERT_NE(w.str(), nullptr);
  EXPECT_STREQ(w.str(), "");
}

TEST_F(OstreamWrapperTest_587, WriteCharPtr_AppendsToInternalBuffer_587) {
  YAML::ostream_wrapper w;

  const char first[] = {'a', 'b', 'c'};
  w.write(first, 3);
  EXPECT_STREQ(w.str(), "abc");

  const char second[] = {'d', 'e', 'f'};
  w.write(second, 3);
  EXPECT_STREQ(w.str(), "abcdef");
}

TEST_F(OstreamWrapperTest_587, WriteCharPtr_ZeroSizeDoesNotChangeBuffer_587) {
  YAML::ostream_wrapper w;

  w.write("abc", 0);
  EXPECT_STREQ(w.str(), "");

  w.write("xyz", 3);
  EXPECT_STREQ(w.str(), "xyz");

  w.write("ignored", 0);
  EXPECT_STREQ(w.str(), "xyz");
}

TEST_F(OstreamWrapperTest_587, WriteCharPtr_ForwardsToProvidedOstream_587) {
  std::ostringstream oss;
  YAML::ostream_wrapper w(oss);

  const char data[] = {'h', 'e', 'l', 'l', 'o'};
  EXPECT_NO_THROW(w.write(data, 5));
  EXPECT_EQ(oss.str(), "hello");

  EXPECT_NO_THROW(w.write("!", 1));
  EXPECT_EQ(oss.str(), "hello!");
}

TEST_F(OstreamWrapperTest_587, WriteCharPtr_ThrowsIfUnderlyingOstreamThrows_587) {
  std::ostringstream oss;

  // Configure the stream to throw on badbit/failbit.
  oss.exceptions(std::ios::badbit | std::ios::failbit);
  // Put the stream into a bad state so a subsequent write triggers an exception.
  oss.setstate(std::ios::badbit);

  YAML::ostream_wrapper w(oss);

  EXPECT_THROW(w.write("abc", 3), std::ios_base::failure);
}

}  // namespace