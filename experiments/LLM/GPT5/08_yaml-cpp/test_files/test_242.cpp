// File: test/node/detail/node_tag_test_242.cpp

#include <gtest/gtest.h>

#include <string>

#include "yaml-cpp/node/detail/node.h"

namespace YAML {
namespace detail {

class NodeTagTest_242 : public ::testing::Test {};

TEST_F(NodeTagTest_242, SetTagThenTagReturnsSameValue_242) {
  node n;
  n.set_tag("!mytag");
  EXPECT_EQ(n.tag(), "!mytag");
}

TEST_F(NodeTagTest_242, TagReflectsLatestSetTagValue_242) {
  node n;
  n.set_tag("!first");
  ASSERT_EQ(n.tag(), "!first");

  n.set_tag("!second");
  EXPECT_EQ(n.tag(), "!second");
}

TEST_F(NodeTagTest_242, SetTagToEmptyStringIsObservable_242) {
  node n;
  n.set_tag("!nonempty");
  ASSERT_EQ(n.tag(), "!nonempty");

  n.set_tag(std::string{});
  EXPECT_EQ(n.tag(), "");
}

TEST_F(NodeTagTest_242, TagReturnsReferenceStableAcrossCalls_242) {
  node n;
  n.set_tag("!stable");

  const std::string& ref1 = n.tag();
  const std::string& ref2 = n.tag();

  EXPECT_EQ(ref1, "!stable");
  EXPECT_EQ(ref2, "!stable");
  EXPECT_EQ(&ref1, &ref2);  // same referenced string object (observable via address)
}

TEST_F(NodeTagTest_242, SetTagWithLongStringRoundTrips_242) {
  node n;

  const std::string long_tag(4096, 'a');
  n.set_tag(long_tag);

  EXPECT_EQ(n.tag(), long_tag);
}

}  // namespace detail
}  // namespace YAML