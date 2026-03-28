// test_node_style_243.cpp
#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node.h"

namespace {

using YAML::detail::node;

class NodeStyleTest_243 : public ::testing::Test {};

TEST_F(NodeStyleTest_243, DefaultConstructedStyleDoesNotThrow_243) {
  node n;
  EXPECT_NO_THROW({
    (void)n.style();
  });
}

TEST_F(NodeStyleTest_243, SetStyleThenStyleReturnsSameValue_243) {
  node n;

  n.set_style(YAML::EmitterStyle::Block);
  EXPECT_EQ(n.style(), YAML::EmitterStyle::Block);

  n.set_style(YAML::EmitterStyle::Flow);
  EXPECT_EQ(n.style(), YAML::EmitterStyle::Flow);

  n.set_style(YAML::EmitterStyle::Default);
  EXPECT_EQ(n.style(), YAML::EmitterStyle::Default);
}

TEST_F(NodeStyleTest_243, TwoNodesMaintainIndependentStyles_243) {
  node a;
  node b;

  a.set_style(YAML::EmitterStyle::Block);
  b.set_style(YAML::EmitterStyle::Flow);

  EXPECT_EQ(a.style(), YAML::EmitterStyle::Block);
  EXPECT_EQ(b.style(), YAML::EmitterStyle::Flow);

  // Changing one should not affect the other (unless explicitly linked via set_ref/set_data).
  a.set_style(YAML::EmitterStyle::Default);
  EXPECT_EQ(a.style(), YAML::EmitterStyle::Default);
  EXPECT_EQ(b.style(), YAML::EmitterStyle::Flow);
}

TEST_F(NodeStyleTest_243, SetRefMakesStyleFollowReferencedNode_243) {
  node a;
  node b;

  a.set_style(YAML::EmitterStyle::Block);
  b.set_style(YAML::EmitterStyle::Flow);
  ASSERT_EQ(a.style(), YAML::EmitterStyle::Block);
  ASSERT_EQ(b.style(), YAML::EmitterStyle::Flow);

  // After set_ref, b should reflect a's observable properties such as style.
  b.set_ref(a);
  EXPECT_EQ(b.style(), a.style());

  // If the reference is shared, updating a's style should be observable through b.
  a.set_style(YAML::EmitterStyle::Default);
  EXPECT_EQ(b.style(), YAML::EmitterStyle::Default);
}

}  // namespace