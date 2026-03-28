// TEST_ID: 224
#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_ref.h"

namespace {

class NodeRefSetStyleTest_224 : public ::testing::Test {
protected:
  YAML::detail::node_ref ref_;
};

TEST_F(NodeRefSetStyleTest_224, SetStyleUpdatesStyleGetter_224) {
  ref_.set_style(YAML::EmitterStyle::Block);
  EXPECT_EQ(ref_.style(), YAML::EmitterStyle::Block);

  ref_.set_style(YAML::EmitterStyle::Flow);
  EXPECT_EQ(ref_.style(), YAML::EmitterStyle::Flow);

  ref_.set_style(YAML::EmitterStyle::Default);
  EXPECT_EQ(ref_.style(), YAML::EmitterStyle::Default);
}

TEST_F(NodeRefSetStyleTest_224, SetStyleCanBeCalledMultipleTimesAndLastWins_224) {
  ref_.set_style(YAML::EmitterStyle::Default);
  EXPECT_EQ(ref_.style(), YAML::EmitterStyle::Default);

  ref_.set_style(YAML::EmitterStyle::Block);
  EXPECT_EQ(ref_.style(), YAML::EmitterStyle::Block);

  ref_.set_style(YAML::EmitterStyle::Flow);
  EXPECT_EQ(ref_.style(), YAML::EmitterStyle::Flow);
}

TEST_F(NodeRefSetStyleTest_224, SetStyleDoesNotThrowForValidEnumValues_224) {
  EXPECT_NO_THROW(ref_.set_style(YAML::EmitterStyle::Default));
  EXPECT_NO_THROW(ref_.set_style(YAML::EmitterStyle::Block));
  EXPECT_NO_THROW(ref_.set_style(YAML::EmitterStyle::Flow));
}

}  // namespace