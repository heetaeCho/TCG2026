// File: yaml-cpp/test/ostream_wrapper_comment_test_30.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <type_traits>

#include "yaml-cpp/ostream_wrapper.h"

namespace {

using YAML::ostream_wrapper;

// Compile-time interface checks (observable via the public interface)
static_assert(!std::is_copy_constructible_v<ostream_wrapper>,
              "ostream_wrapper must not be copy-constructible");
static_assert(!std::is_move_constructible_v<ostream_wrapper>,
              "ostream_wrapper must not be move-constructible");
static_assert(!std::is_copy_assignable_v<ostream_wrapper>,
              "ostream_wrapper must not be copy-assignable");
static_assert(!std::is_move_assignable_v<ostream_wrapper>,
              "ostream_wrapper must not be move-assignable");

class OstreamWrapperCommentTest_30 : public ::testing::Test {};

TEST_F(OstreamWrapperCommentTest_30, DefaultConstructorCommentIsFalse_30) {
  ostream_wrapper w;
  EXPECT_FALSE(w.comment());
}

TEST_F(OstreamWrapperCommentTest_30, SetCommentMakesCommentTrue_30) {
  ostream_wrapper w;

  w.set_comment();

  EXPECT_TRUE(w.comment());
}

TEST_F(OstreamWrapperCommentTest_30, SetCommentIsIdempotent_30) {
  ostream_wrapper w;

  w.set_comment();
  const bool after_first = w.comment();

  w.set_comment();
  const bool after_second = w.comment();

  // Only assert observable behavior: calling set_comment again does not flip it back.
  EXPECT_TRUE(after_first);
  EXPECT_EQ(after_first, after_second);
}

TEST_F(OstreamWrapperCommentTest_30, StreamConstructorCommentInitiallyFalse_30) {
  std::ostringstream oss;
  ostream_wrapper w(oss);

  EXPECT_FALSE(w.comment());
}

TEST_F(OstreamWrapperCommentTest_30, StreamConstructorSetCommentMakesCommentTrue_30) {
  std::ostringstream oss;
  ostream_wrapper w(oss);

  w.set_comment();

  EXPECT_TRUE(w.comment());
}

}  // namespace
