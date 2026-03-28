// TEST_ID: 559
#include <gtest/gtest.h>

#include <string>

#include <yaml-cpp/yaml.h>

namespace {

class NodeSetTagTest_559 : public ::testing::Test {};

TEST_F(NodeSetTagTest_559, SetTagOnDefaultConstructedNode_559) {
  YAML::Node n;
  const std::string tag = "!mytag";

  EXPECT_NO_THROW(n.SetTag(tag));
  EXPECT_EQ(n.Tag(), tag);
}

TEST_F(NodeSetTagTest_559, SetTagToEmptyString_559) {
  YAML::Node n;

  EXPECT_NO_THROW(n.SetTag(std::string{}));
  EXPECT_EQ(n.Tag(), std::string{});
}

TEST_F(NodeSetTagTest_559, SetTagToLongString_559) {
  YAML::Node n;
  const std::string long_tag(4096, 'a');

  EXPECT_NO_THROW(n.SetTag(long_tag));
  EXPECT_EQ(n.Tag(), long_tag);
}

TEST_F(NodeSetTagTest_559, SetTagWithNonAlnumCharacters_559) {
  YAML::Node n;
  const std::string tag = "!tag-with:punctuation/and spaces\t\u2603";

  EXPECT_NO_THROW(n.SetTag(tag));
  EXPECT_EQ(n.Tag(), tag);
}

TEST_F(NodeSetTagTest_559, SetTagTwiceLastValueWins_559) {
  YAML::Node n;

  EXPECT_NO_THROW(n.SetTag("!first"));
  EXPECT_EQ(n.Tag(), "!first");

  EXPECT_NO_THROW(n.SetTag("!second"));
  EXPECT_EQ(n.Tag(), "!second");
}

TEST_F(NodeSetTagTest_559, CopyConstructorPreservesTag_559) {
  YAML::Node original;
  original.SetTag("!copied");

  const YAML::Node copied(original);
  EXPECT_EQ(copied.Tag(), "!copied");
}

TEST_F(NodeSetTagTest_559, CopyAssignmentPreservesTag_559) {
  YAML::Node src;
  src.SetTag("!assigned");

  YAML::Node dst;
  EXPECT_NO_THROW(dst = src);
  EXPECT_EQ(dst.Tag(), "!assigned");
}

}  // namespace