// TEST_ID: 253
#include <gtest/gtest.h>

#include <yaml-cpp/emitterstyle.h>
#include <yaml-cpp/node/detail/node.h>

namespace {

class NodeSetStyleTest_253 : public ::testing::Test {
protected:
  YAML::detail::node n_;
};

TEST_F(NodeSetStyleTest_253, SetStyleMakesNodeDefined_253) {
  // Precondition: newly-constructed node may be undefined in this API.
  const bool was_defined = n_.is_defined();

  EXPECT_NO_THROW(n_.set_style(YAML::EmitterStyle::Block));

  // Observable effects through public interface:
  EXPECT_TRUE(n_.is_defined());
  EXPECT_EQ(n_.style(), YAML::EmitterStyle::Block);

  // If it was already defined, it should remain defined.
  if (was_defined) {
    EXPECT_TRUE(n_.is_defined());
  }
}

TEST_F(NodeSetStyleTest_253, SetStyleUpdatesStyleValue_253) {
  EXPECT_NO_THROW(n_.set_style(YAML::EmitterStyle::Flow));
  EXPECT_TRUE(n_.is_defined());
  EXPECT_EQ(n_.style(), YAML::EmitterStyle::Flow);

  EXPECT_NO_THROW(n_.set_style(YAML::EmitterStyle::Block));
  EXPECT_TRUE(n_.is_defined());
  EXPECT_EQ(n_.style(), YAML::EmitterStyle::Block);
}

TEST_F(NodeSetStyleTest_253, SetStyleAcceptsDifferentEnumValues_253) {
  // Boundary-ish coverage across multiple valid enum values.
  EXPECT_NO_THROW(n_.set_style(YAML::EmitterStyle::Default));
  EXPECT_TRUE(n_.is_defined());
  EXPECT_EQ(n_.style(), YAML::EmitterStyle::Default);

  EXPECT_NO_THROW(n_.set_style(YAML::EmitterStyle::Flow));
  EXPECT_TRUE(n_.is_defined());
  EXPECT_EQ(n_.style(), YAML::EmitterStyle::Flow);
}

}  // namespace