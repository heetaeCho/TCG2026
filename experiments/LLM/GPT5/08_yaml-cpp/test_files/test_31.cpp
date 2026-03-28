// TEST_ID: 31
#include <gtest/gtest.h>

#include <cstring>
#include <string>

#include "yaml-cpp/ostream_wrapper.h"

namespace {

class OstreamWrapperCharArrayInsertionTest_31 : public ::testing::Test {
 protected:
  YAML::ostream_wrapper w_;
};

TEST_F(OstreamWrapperCharArrayInsertionTest_31, ReturnsSameObjectReference_31) {
  YAML::ostream_wrapper* returned = &(w_ << "a");
  EXPECT_EQ(returned, &w_);
}

TEST_F(OstreamWrapperCharArrayInsertionTest_31, WritesEmptyStringLiteral_NoChange_31) {
  const std::size_t pos_before = w_.pos();
  const std::size_t row_before = w_.row();
  const std::size_t col_before = w_.col();

  w_ << "";

  EXPECT_EQ(w_.pos(), pos_before);
  EXPECT_EQ(w_.row(), row_before);
  EXPECT_EQ(w_.col(), col_before);
  EXPECT_STREQ(w_.str(), "");
}

TEST_F(OstreamWrapperCharArrayInsertionTest_31, WritesNonEmptyStringLiteral_31) {
  w_ << "abc";

  EXPECT_EQ(w_.pos(), 3u);
  EXPECT_STREQ(w_.str(), "abc");
}

TEST_F(OstreamWrapperCharArrayInsertionTest_31, SupportsChainingMultipleInsertions_31) {
  w_ << "a" << "bc" << "def";

  EXPECT_EQ(w_.pos(), 6u);
  EXPECT_STREQ(w_.str(), "abcdef");
}

TEST_F(OstreamWrapperCharArrayInsertionTest_31, DoesNotAppendNullTerminatorFromLiteral_31) {
  w_ << "abc";

  // If a '\0' from the array were written, strlen(str()) would be < pos() or
  // pos() would be 4. We only assert what is observable via the public API.
  EXPECT_EQ(std::strlen(w_.str()), 3u);
  EXPECT_EQ(w_.pos(), 3u);
}

TEST_F(OstreamWrapperCharArrayInsertionTest_31, LargeStringLiteralUpdatesPositionAndContent_31) {
  // 512 'x' characters using literal concatenation (compile-time char array).
  constexpr const char kBig[] =
      "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"  // 64
      "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"  // 128
      "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"  // 192
      "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"  // 256
      "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"  // 320
      "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"  // 384
      "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"  // 448
      "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"; // 512

  w_ << kBig;

  EXPECT_EQ(w_.pos(), 512u);
  EXPECT_EQ(std::strlen(w_.str()), 512u);
  EXPECT_EQ(std::string(w_.str()), std::string(kBig));
}

TEST_F(OstreamWrapperCharArrayInsertionTest_31, PreservesCommentFlagState_31) {
  // Observable expectation: insertion should not implicitly toggle comment state.
  const bool before = w_.comment();

  w_ << "abc";

  EXPECT_EQ(w_.comment(), before);

  w_.set_comment();
  const bool after_set = w_.comment();

  w_ << "def";

  EXPECT_EQ(w_.comment(), after_set);
}

}  // namespace
