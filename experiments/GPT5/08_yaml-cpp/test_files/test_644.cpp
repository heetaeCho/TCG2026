// TEST_ID: 644
#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_data.h"
#include "yaml-cpp/emitterstyle.h"

namespace {

class NodeDataSetStyleTest_644 : public ::testing::Test {
protected:
  YAML::detail::node_data data_;
};

TEST_F(NodeDataSetStyleTest_644, SetStyleBlockIsObservableViaGetter_644) {
  data_.set_style(YAML::EmitterStyle::Block);
  EXPECT_EQ(data_.style(), YAML::EmitterStyle::Block);
}

TEST_F(NodeDataSetStyleTest_644, SetStyleFlowIsObservableViaGetter_644) {
  data_.set_style(YAML::EmitterStyle::Flow);
  EXPECT_EQ(data_.style(), YAML::EmitterStyle::Flow);
}

TEST_F(NodeDataSetStyleTest_644, SetStyleDefaultIsObservableViaGetter_644) {
  data_.set_style(YAML::EmitterStyle::Default);
  EXPECT_EQ(data_.style(), YAML::EmitterStyle::Default);
}

TEST_F(NodeDataSetStyleTest_644, RepeatedCallsLastCallWins_644) {
  data_.set_style(YAML::EmitterStyle::Block);
  EXPECT_EQ(data_.style(), YAML::EmitterStyle::Block);

  data_.set_style(YAML::EmitterStyle::Flow);
  EXPECT_EQ(data_.style(), YAML::EmitterStyle::Flow);

  data_.set_style(YAML::EmitterStyle::Default);
  EXPECT_EQ(data_.style(), YAML::EmitterStyle::Default);
}

TEST_F(NodeDataSetStyleTest_644, DoesNotThrowForValidStyles_644) {
  EXPECT_NO_THROW(data_.set_style(YAML::EmitterStyle::Block));
  EXPECT_NO_THROW(data_.set_style(YAML::EmitterStyle::Flow));
  EXPECT_NO_THROW(data_.set_style(YAML::EmitterStyle::Default));
}

}  // namespace