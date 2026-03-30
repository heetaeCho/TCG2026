// File: test/ostream_wrapper_test_25.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "yaml-cpp/ostream_wrapper.h"

namespace {

class OstreamWrapperTest_25 : public ::testing::Test {};

TEST_F(OstreamWrapperTest_25, DefaultConstructor_CommentStartsFalse_25) {
  YAML::ostream_wrapper w;
  EXPECT_FALSE(w.comment());
}

TEST_F(OstreamWrapperTest_25, SetComment_SetsCommentTrue_25) {
  YAML::ostream_wrapper w;

  w.set_comment();

  EXPECT_TRUE(w.comment());
}

TEST_F(OstreamWrapperTest_25, SetComment_CanBeCalledMultipleTimes_RemainsTrue_25) {
  YAML::ostream_wrapper w;

  w.set_comment();
  w.set_comment();
  w.set_comment();

  EXPECT_TRUE(w.comment());
}

TEST_F(OstreamWrapperTest_25, StreamConstructor_CommentStartsFalse_25) {
  std::ostringstream oss;
  YAML::ostream_wrapper w(oss);

  EXPECT_FALSE(w.comment());
}

TEST_F(OstreamWrapperTest_25, StreamConstructor_SetComment_SetsCommentTrue_25) {
  std::ostringstream oss;
  YAML::ostream_wrapper w(oss);

  w.set_comment();

  EXPECT_TRUE(w.comment());
}

TEST_F(OstreamWrapperTest_25, SetComment_DoesNotThrow_25) {
  YAML::ostream_wrapper w;
  EXPECT_NO_THROW(w.set_comment());
}

TEST_F(OstreamWrapperTest_25, SetComment_AfterWrites_CommentStillTrue_25) {
  // This test only checks the observable "comment" flag behavior and does not
  // assume anything about how write() formats/outputs data.
  YAML::ostream_wrapper w;

  // Exercise other public APIs, if available.
  w.write(std::string("abc"));
  w.write("def", 3);

  w.set_comment();

  EXPECT_TRUE(w.comment());
}

}  // namespace
