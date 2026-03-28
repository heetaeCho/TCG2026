// TEST_ID: 33
#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <cstring>

#include "yaml-cpp/ostream_wrapper.h"

namespace {

class OstreamWrapperCharOpTest_33 : public ::testing::Test {
protected:
  std::ostringstream oss;
};

TEST_F(OstreamWrapperCharOpTest_33, WritesSingleCharToBoundStream_33) {
  YAML::ostream_wrapper w(oss);

  const std::size_t pos_before = w.pos();
  ASSERT_NO_THROW((w << 'A'));

  EXPECT_EQ(w.pos(), pos_before + 1u);
  EXPECT_EQ(oss.str(), std::string("A"));

  // If wrapper also buffers internally, ensure it's at least consistent with what was written.
  const char* s = w.str();
  ASSERT_NE(s, nullptr);
  EXPECT_GE(std::strlen(s), 1u);
  EXPECT_EQ(s[0], 'A');
}

TEST_F(OstreamWrapperCharOpTest_33, ReturnsSameWrapperReferenceForChaining_33) {
  YAML::ostream_wrapper w(oss);

  YAML::ostream_wrapper* ret = nullptr;
  ASSERT_NO_THROW(ret = &((w << 'x') << 'y'));

  EXPECT_EQ(ret, &w);
  EXPECT_EQ(oss.str(), std::string("xy"));
}

TEST_F(OstreamWrapperCharOpTest_33, WorksWhenDefaultConstructedWithoutStream_33) {
  YAML::ostream_wrapper w;

  const std::size_t pos_before = w.pos();
  EXPECT_NO_THROW((w << 'Z'));
  EXPECT_EQ(w.pos(), pos_before + 1u);

  const char* s = w.str();
  ASSERT_NE(s, nullptr);
  EXPECT_GE(std::strlen(s), 1u);
  EXPECT_EQ(s[0], 'Z');
}

TEST_F(OstreamWrapperCharOpTest_33, WritesNullByteToBoundStream_33) {
  YAML::ostream_wrapper w(oss);

  const std::size_t pos_before = w.pos();

  ASSERT_NO_THROW((w << 'x' << '\0' << 'y'));
  EXPECT_EQ(w.pos(), pos_before + 3u);

  const std::string out = oss.str();
  ASSERT_EQ(out.size(), 3u);
  EXPECT_EQ(out[0], 'x');
  EXPECT_EQ(out[1], '\0');
  EXPECT_EQ(out[2], 'y');
}

TEST_F(OstreamWrapperCharOpTest_33, WritesMultipleCharsAndPosMatchesCount_33) {
  YAML::ostream_wrapper w(oss);

  const std::size_t pos_before = w.pos();
  ASSERT_NO_THROW((w << '1' << '2' << '3' << '4' << '5'));

  EXPECT_EQ(w.pos(), pos_before + 5u);
  EXPECT_EQ(oss.str(), std::string("12345"));
}

}  // namespace
