// TEST_ID: 209
// File: test/node/detail/node_data_tag_test_209.cpp

#include <gtest/gtest.h>

#include <string>

#include "yaml-cpp/node/detail/node_data.h"

namespace {

using YAML::detail::node_data;

TEST(NodeDataTagTest_209, TagReturnsConstReference_209) {
  node_data nd;

  // Compile-time check that tag() returns a const std::string&.
  static_assert(std::is_same_v<decltype(nd.tag()), const std::string&>,
                "node_data::tag() must return const std::string&");
}

TEST(NodeDataTagTest_209, TagReferenceIsStableAcrossCalls_209) {
  node_data nd;

  const std::string& t1 = nd.tag();
  const std::string& t2 = nd.tag();

  // Same object should yield the same referenced string across calls.
  EXPECT_EQ(&t1, &t2);
  EXPECT_EQ(t1, t2);
}

TEST(NodeDataTagTest_209, TagDoesNotThrowAndIsUsable_209) {
  node_data nd;

  EXPECT_NO_THROW({
    const std::string& t = nd.tag();
    // Basic usability checks (do not assume specific default contents).
    (void)t.size();
    (void)t.empty();
  });
}

TEST(NodeDataTagTest_209, DifferentInstancesReturnDifferentReferenceAddresses_209) {
  node_data nd1;
  node_data nd2;

  // Even if contents are the same by default, they should not alias the same string object.
  EXPECT_NE(&nd1.tag(), &nd2.tag());
}

}  // namespace