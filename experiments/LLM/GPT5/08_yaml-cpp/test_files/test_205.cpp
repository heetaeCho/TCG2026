// TEST_ID: 205
//
// Unit tests for YAML::detail::node_data::is_defined()
//
// Constraints respected:
// - Treat implementation as black box (only observe public API).
// - No access to private state.
// - No re-implementation of logic.

#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_data.h"

namespace {

using YAML::detail::node_data;

TEST(NodeDataTest_205, DefaultConstructedIsNotDefined_205) {
  node_data nd;
  EXPECT_FALSE(nd.is_defined());
}

TEST(NodeDataTest_205, IsDefinedIsConstCallable_205) {
  const node_data nd;
  EXPECT_FALSE(nd.is_defined());
}

TEST(NodeDataTest_205, MarkDefinedMakesIsDefinedTrue_205) {
  node_data nd;

  nd.mark_defined();

  EXPECT_TRUE(nd.is_defined());
}

TEST(NodeDataTest_205, MarkDefinedIsIdempotent_205) {
  node_data nd;

  nd.mark_defined();
  EXPECT_TRUE(nd.is_defined());

  nd.mark_defined();
  EXPECT_TRUE(nd.is_defined());
}

TEST(NodeDataTest_205, IsDefinedCanBeCalledRepeatedly_205) {
  node_data nd;

  EXPECT_NO_THROW({
    (void)nd.is_defined();
    (void)nd.is_defined();
    (void)nd.is_defined();
  });
}

TEST(NodeDataTest_205, IsDefinedDoesNotThrowAfterMarkDefined_205) {
  node_data nd;
  nd.mark_defined();

  EXPECT_NO_THROW({
    (void)nd.is_defined();
    (void)nd.is_defined();
  });
}

}  // namespace