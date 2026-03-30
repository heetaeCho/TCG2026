// TEST_ID: 210
// File: node_data_style_test_210.cpp

#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_data.h"

namespace {

using YAML::EmitterStyle;
using YAML::detail::node_data;

TEST(NodeDataStyleTest_210, DefaultConstructedStyleIsStableAcrossCalls_210) {
  node_data nd;

  const auto s1 = nd.style();
  const auto s2 = nd.style();

  // We don't assume any particular default enum value; we only require stability/consistency.
  EXPECT_EQ(s1, s2);
}

TEST(NodeDataStyleTest_210, StyleCanBeReadFromConstObject_210) {
  node_data nd;

  // Set via non-const, then observe via const.
  nd.set_style(EmitterStyle::Default);
  const node_data& cnd = nd;

  EXPECT_EQ(cnd.style(), EmitterStyle::Default);
}

TEST(NodeDataStyleTest_210, SetStyleThenStyleReturnsSameValue_210) {
  node_data nd;

  nd.set_style(EmitterStyle::Flow);
  EXPECT_EQ(nd.style(), EmitterStyle::Flow);

  nd.set_style(EmitterStyle::Block);
  EXPECT_EQ(nd.style(), EmitterStyle::Block);
}

TEST(NodeDataStyleTest_210, SettingSameStyleMultipleTimesKeepsThatStyle_210) {
  node_data nd;

  nd.set_style(EmitterStyle::Flow);
  nd.set_style(EmitterStyle::Flow);

  EXPECT_EQ(nd.style(), EmitterStyle::Flow);
}

TEST(NodeDataStyleTest_210, LastSetStyleWinsWhenChangedMultipleTimes_210) {
  node_data nd;

  nd.set_style(EmitterStyle::Default);
  EXPECT_EQ(nd.style(), EmitterStyle::Default);

  nd.set_style(EmitterStyle::Flow);
  EXPECT_EQ(nd.style(), EmitterStyle::Flow);

  nd.set_style(EmitterStyle::Default);
  EXPECT_EQ(nd.style(), EmitterStyle::Default);
}

}  // namespace