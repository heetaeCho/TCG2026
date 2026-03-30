// File: node_ref_style_test_216.cpp
#include <gtest/gtest.h>

#include <yaml-cpp/emitterstyle.h>
#include <yaml-cpp/node/detail/node_ref.h>

namespace {

using YAML::EmitterStyle;
using YAML::detail::node_ref;

class NodeRefStyleTest_216 : public ::testing::Test {};

TEST_F(NodeRefStyleTest_216, DefaultConstructedStyleIsAValidEmitterStyleValue_216) {
  const node_ref ref;
  const auto s = ref.style();

  // Avoid assuming a specific default; just ensure it is one of the known valid values.
  EXPECT_TRUE(s == EmitterStyle::Default || s == EmitterStyle::Block || s == EmitterStyle::Flow);
}

TEST_F(NodeRefStyleTest_216, SetStyleRoundTripsBlock_216) {
  node_ref ref;

  ref.set_style(EmitterStyle::Block);
  EXPECT_EQ(ref.style(), EmitterStyle::Block);
}

TEST_F(NodeRefStyleTest_216, SetStyleRoundTripsFlow_216) {
  node_ref ref;

  ref.set_style(EmitterStyle::Flow);
  EXPECT_EQ(ref.style(), EmitterStyle::Flow);
}

TEST_F(NodeRefStyleTest_216, SetStyleCanBeChangedMultipleTimes_216) {
  node_ref ref;

  ref.set_style(EmitterStyle::Block);
  EXPECT_EQ(ref.style(), EmitterStyle::Block);

  ref.set_style(EmitterStyle::Flow);
  EXPECT_EQ(ref.style(), EmitterStyle::Flow);

  ref.set_style(EmitterStyle::Default);
  EXPECT_EQ(ref.style(), EmitterStyle::Default);
}

TEST_F(NodeRefStyleTest_216, SetStyleIsIdempotentForSameValue_216) {
  node_ref ref;

  ref.set_style(EmitterStyle::Block);
  const auto first = ref.style();

  ref.set_style(EmitterStyle::Block);
  const auto second = ref.style();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, EmitterStyle::Block);
}

TEST_F(NodeRefStyleTest_216, StyleIsTransferredViaSetDataAtTimeOfCall_216) {
  node_ref a;
  node_ref b;

  a.set_style(EmitterStyle::Flow);
  b.set_data(a);

  // Only assert the observable postcondition of set_data: b reflects a at the moment of transfer.
  EXPECT_EQ(b.style(), EmitterStyle::Flow);

  // Changing 'a' after set_data may or may not affect 'b' (sharing vs. copy is an internal detail).
  // We only verify both remain callable and consistent with their own setters.
  a.set_style(EmitterStyle::Block);
  EXPECT_EQ(a.style(), EmitterStyle::Block);

  b.set_style(EmitterStyle::Default);
  EXPECT_EQ(b.style(), EmitterStyle::Default);
}

}  // namespace