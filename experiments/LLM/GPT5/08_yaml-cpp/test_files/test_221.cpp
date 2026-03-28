// TEST_ID: 221
#include <gtest/gtest.h>

#include <string>

#include "yaml-cpp/node/detail/node_ref.h"

namespace {

using YAML::detail::node_ref;

class NodeRefSetTagTest_221 : public ::testing::Test {
 protected:
  node_ref ref_;
};

TEST_F(NodeRefSetTagTest_221, SetTagStoresExactValue_221) {
  const std::string tag = "!mytag";
  ref_.set_tag(tag);
  EXPECT_EQ(ref_.tag(), tag);
}

TEST_F(NodeRefSetTagTest_221, SetTagOverwritesPreviousValue_221) {
  ref_.set_tag("!first");
  EXPECT_EQ(ref_.tag(), "!first");

  ref_.set_tag("!second");
  EXPECT_EQ(ref_.tag(), "!second");
}

TEST_F(NodeRefSetTagTest_221, SetTagAllowsEmptyString_221) {
  ref_.set_tag("!nonempty");
  ASSERT_EQ(ref_.tag(), "!nonempty");

  ref_.set_tag(std::string{});
  EXPECT_EQ(ref_.tag(), "");
}

TEST_F(NodeRefSetTagTest_221, SetTagPreservesSpecialCharacters_221) {
  const std::string tag = "!tag-with spaces\tand\nnewlines\u2603";
  ref_.set_tag(tag);
  EXPECT_EQ(ref_.tag(), tag);
}

TEST_F(NodeRefSetTagTest_221, SetTagHandlesLargeInput_221) {
  const std::string large_tag = "!" + std::string(32 * 1024, 'x');  // 32KiB-ish
  ASSERT_NO_THROW(ref_.set_tag(large_tag));
  EXPECT_EQ(ref_.tag(), large_tag);
}

TEST_F(NodeRefSetTagTest_221, SetTagDoesNotThrowForTypicalTags_221) {
  EXPECT_NO_THROW(ref_.set_tag("!"));
  EXPECT_NO_THROW(ref_.set_tag("!!str"));
  EXPECT_NO_THROW(ref_.set_tag("!<tag:example.com,2026:test>"));
}

}  // namespace