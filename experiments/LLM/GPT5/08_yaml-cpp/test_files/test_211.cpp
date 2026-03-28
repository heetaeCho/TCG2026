// TEST_ID: 211
// File: test/node/detail/node_ref_is_defined_test_211.cpp

#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_ref.h"

namespace {

using YAML::detail::node_ref;

class NodeRefIsDefinedTest_211 : public ::testing::Test {};

TEST_F(NodeRefIsDefinedTest_211, DefaultConstructedIsNotDefined_211) {
  node_ref ref;
  EXPECT_FALSE(ref.is_defined());
}

TEST_F(NodeRefIsDefinedTest_211, MarkDefinedMakesDefined_211) {
  node_ref ref;

  ref.mark_defined();

  EXPECT_TRUE(ref.is_defined());
}

TEST_F(NodeRefIsDefinedTest_211, MarkDefinedIsIdempotent_211) {
  node_ref ref;

  ref.mark_defined();
  EXPECT_TRUE(ref.is_defined());

  // Calling again should remain defined (no observable error / regression).
  ref.mark_defined();
  EXPECT_TRUE(ref.is_defined());
}

TEST_F(NodeRefIsDefinedTest_211, SetDataCopiesDefinedStateFromRhs_211) {
  node_ref rhs;
  rhs.mark_defined();
  ASSERT_TRUE(rhs.is_defined());

  node_ref lhs;
  ASSERT_FALSE(lhs.is_defined());

  lhs.set_data(rhs);

  EXPECT_TRUE(lhs.is_defined());
  EXPECT_TRUE(rhs.is_defined());
}

}  // namespace