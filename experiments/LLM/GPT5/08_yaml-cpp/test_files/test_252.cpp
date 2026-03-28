// File: yaml-cpp/test/node/detail/node_set_tag_test_252.cpp

#include <gtest/gtest.h>

#include <string>

#include "yaml-cpp/node/detail/node.h"

namespace {

class NodeSetTagTest_252 : public ::testing::Test {
protected:
  YAML::detail::node n;
};

TEST_F(NodeSetTagTest_252, SetTagUpdatesTagValue_252) {
  const std::string newTag = "!mytag";
  n.set_tag(newTag);
  EXPECT_EQ(n.tag(), newTag);
}

TEST_F(NodeSetTagTest_252, SetTagMarksNodeDefined_252) {
  // We only assert the observable post-condition implied by the interface:
  // calling set_tag() should leave the node in a defined state.
  n.set_tag("!t");
  EXPECT_TRUE(n.is_defined());
}

TEST_F(NodeSetTagTest_252, SetTagAllowsEmptyString_252) {
  const std::string emptyTag;
  n.set_tag(emptyTag);
  EXPECT_EQ(n.tag(), emptyTag);
  EXPECT_TRUE(n.is_defined());
}

TEST_F(NodeSetTagTest_252, SetTagCanBeCalledMultipleTimes_LastCallWins_252) {
  n.set_tag("!first");
  EXPECT_EQ(n.tag(), "!first");

  n.set_tag("!second");
  EXPECT_EQ(n.tag(), "!second");

  n.set_tag("!third");
  EXPECT_EQ(n.tag(), "!third");
}

TEST_F(NodeSetTagTest_252, SetTagAcceptsSpecialCharacters_252) {
  const std::string tagWithSpecials = "!tag:with spaces/#[]{}@";
  n.set_tag(tagWithSpecials);
  EXPECT_EQ(n.tag(), tagWithSpecials);
  EXPECT_TRUE(n.is_defined());
}

TEST_F(NodeSetTagTest_252, SetTagAcceptsLongTag_252) {
  const std::string longTag(4096, 'a');  // long but reasonable
  const std::string newTag = "!" + longTag;

  n.set_tag(newTag);
  EXPECT_EQ(n.tag(), newTag);
  EXPECT_TRUE(n.is_defined());
}

}  // namespace