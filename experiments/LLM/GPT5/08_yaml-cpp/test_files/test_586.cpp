// File: ./TestProjects/yaml-cpp/test/ostream_wrapper_test_586.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "yaml-cpp/ostream_wrapper.h"

namespace {

using YAML::ostream_wrapper;

class OstreamWrapperTest_586 : public ::testing::Test {};

TEST_F(OstreamWrapperTest_586, DefaultConstructedStartsEmpty_586) {
  ostream_wrapper w;

  const char* s = w.str();
  ASSERT_NE(s, nullptr);
  EXPECT_STREQ(s, "");

  EXPECT_EQ(w.pos(), 0u);
  EXPECT_EQ(w.row(), 0u);
  EXPECT_EQ(w.col(), 0u);
  EXPECT_FALSE(w.comment());
}

TEST_F(OstreamWrapperTest_586, WriteEmptyStringDoesNotChangeState_586) {
  ostream_wrapper w;

  const std::string before_str = w.str() ? std::string(w.str()) : std::string();
  const std::size_t before_pos = w.pos();
  const std::size_t before_row = w.row();
  const std::size_t before_col = w.col();
  const bool before_comment = w.comment();

  w.write(std::string(""));

  const char* after = w.str();
  ASSERT_NE(after, nullptr);
  EXPECT_EQ(std::string(after), before_str);

  EXPECT_EQ(w.pos(), before_pos);
  EXPECT_EQ(w.row(), before_row);
  EXPECT_EQ(w.col(), before_col);
  EXPECT_EQ(w.comment(), before_comment);
}

TEST_F(OstreamWrapperTest_586, WriteAppendsToInternalBuffer_586) {
  ostream_wrapper w;

  w.write(std::string("abc"));

  const char* s = w.str();
  ASSERT_NE(s, nullptr);
  EXPECT_STREQ(s, "abc");

  // For content with no newlines, pos/col should advance by the number of chars written.
  EXPECT_EQ(w.pos(), 3u);
  EXPECT_EQ(w.col(), 3u);
  EXPECT_EQ(w.row(), 0u);
}

TEST_F(OstreamWrapperTest_586, MultipleWritesAccumulateInBuffer_586) {
  ostream_wrapper w;

  w.write(std::string("ab"));
  w.write(std::string("cd"));

  const char* s = w.str();
  ASSERT_NE(s, nullptr);
  EXPECT_STREQ(s, "abcd");

  EXPECT_EQ(w.pos(), 4u);
  EXPECT_EQ(w.col(), 4u);
  EXPECT_EQ(w.row(), 0u);
}

TEST_F(OstreamWrapperTest_586, StreamConstructedWritesToProvidedStream_586) {
  std::ostringstream oss;
  ostream_wrapper w(oss);

  w.write(std::string("hello"));

  EXPECT_EQ(oss.str(), "hello");

  // Observable position should advance by the number of characters written for no-newline input.
  EXPECT_EQ(w.pos(), 5u);
  EXPECT_EQ(w.col(), 5u);
}

TEST_F(OstreamWrapperTest_586, StreamConstructedMultipleWritesAppendToStream_586) {
  std::ostringstream oss;
  ostream_wrapper w(oss);

  w.write(std::string("hi"));
  w.write(std::string(" there"));

  EXPECT_EQ(oss.str(), "hi there");
  EXPECT_EQ(w.pos(), 8u);
  EXPECT_EQ(w.col(), 8u);
}

TEST_F(OstreamWrapperTest_586, SetCommentIsObservableAndPersistsAcrossWrite_586) {
  ostream_wrapper w;

  EXPECT_FALSE(w.comment());
  w.set_comment();
  EXPECT_TRUE(w.comment());

  w.write(std::string("abc"));
  EXPECT_TRUE(w.comment());  // observable behavior: comment flag remains set
}

}  // namespace