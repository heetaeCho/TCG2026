// TEST_ID: 215
#include <gtest/gtest.h>

#include <string>

#include "yaml-cpp/node/detail/node_ref.h"

namespace {

using YAML::detail::node_ref;

class NodeRefTagTest_215 : public ::testing::Test {};

TEST_F(NodeRefTagTest_215, DefaultConstructedTagIsAccessible_215) {
  node_ref n;

  // Black-box expectation: tag() is callable and returns a usable reference.
  const std::string& t = n.tag();
  (void)t;

  // Basic sanity: the reference should be stable for repeated calls while the object lives.
  const std::string& t2 = n.tag();
  EXPECT_EQ(&t, &t2);
}

TEST_F(NodeRefTagTest_215, SetTagThenTagReturnsSameValue_215) {
  node_ref n;

  n.set_tag("!myTag");
  EXPECT_EQ(n.tag(), "!myTag");
}

TEST_F(NodeRefTagTest_215, SetTagAcceptsEmptyString_215) {
  node_ref n;

  n.set_tag("");
  EXPECT_EQ(n.tag(), "");
}

TEST_F(NodeRefTagTest_215, SetTagAcceptsLongString_215) {
  node_ref n;

  const std::string long_tag(4096, 'x');
  n.set_tag(long_tag);
  EXPECT_EQ(n.tag(), long_tag);
}

TEST_F(NodeRefTagTest_215, SetTagAcceptsSpecialCharacters_215) {
  node_ref n;

  const std::string tag = "tag:with spaces/utf8?\t\n!@#$%^&*()";
  n.set_tag(tag);
  EXPECT_EQ(n.tag(), tag);
}

TEST_F(NodeRefTagTest_215, TagReferenceReflectsUpdatesAfterSetTag_215) {
  node_ref n;

  const std::string& before_ref = n.tag();
  n.set_tag("updated");
  // Observable behavior: after mutation, tag() reports the new value.
  EXPECT_EQ(n.tag(), "updated");
  // The previously obtained reference should still be usable while `n` lives.
  EXPECT_EQ(before_ref, "updated");
}

TEST_F(NodeRefTagTest_215, TagWorksOnConstNodeRef_215) {
  node_ref n;
  n.set_tag("const-ok");

  const node_ref& cn = n;
  EXPECT_EQ(cn.tag(), "const-ok");
}

TEST_F(NodeRefTagTest_215, SetDataCopiesOrSharesTagValueAtTimeOfCall_215) {
  node_ref a;
  a.set_tag("from-a");

  node_ref b;
  b.set_tag("from-b");

  b.set_data(a);
  EXPECT_EQ(b.tag(), "from-a");
}

}  // namespace