// node_ref_scalar_test_214.cpp
#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "yaml-cpp/node/detail/node_ref.h"

namespace {

class NodeRefScalarTest_214 : public ::testing::Test {
 protected:
  YAML::detail::node_ref ref_;
};

TEST_F(NodeRefScalarTest_214, DefaultScalarIsEmpty_214) {
  const std::string& s = ref_.scalar();
  EXPECT_TRUE(s.empty());
}

TEST_F(NodeRefScalarTest_214, SetScalarThenScalarReturnsSameValue_214) {
  ref_.set_scalar("hello");
  EXPECT_EQ(ref_.scalar(), "hello");

  ref_.set_scalar("world");
  EXPECT_EQ(ref_.scalar(), "world");
}

TEST_F(NodeRefScalarTest_214, SetScalarEmptyStringBoundary_214) {
  ref_.set_scalar("");
  EXPECT_TRUE(ref_.scalar().empty());
  EXPECT_EQ(ref_.scalar(), std::string{});
}

TEST_F(NodeRefScalarTest_214, SetScalarLargeStringBoundary_214) {
  std::string big(1 << 20, 'x');  // 1 MiB
  ref_.set_scalar(big);
  EXPECT_EQ(ref_.scalar().size(), big.size());
  EXPECT_EQ(ref_.scalar(), big);
}

TEST_F(NodeRefScalarTest_214, SetScalarWithEmbeddedNullByte_214) {
  std::string with_null;
  with_null.push_back('a');
  with_null.push_back('\0');
  with_null.push_back('b');

  ref_.set_scalar(with_null);

  const std::string& out = ref_.scalar();
  EXPECT_EQ(out.size(), 3u);
  EXPECT_EQ(out[0], 'a');
  EXPECT_EQ(out[1], '\0');
  EXPECT_EQ(out[2], 'b');
  EXPECT_EQ(out, with_null);
}

TEST_F(NodeRefScalarTest_214, SetNullThenScalarIsEmpty_214) {
  ref_.set_scalar("not-empty");
  ASSERT_EQ(ref_.scalar(), "not-empty");

  ref_.set_null();
  EXPECT_TRUE(ref_.scalar().empty());
}

TEST_F(NodeRefScalarTest_214, SetDataSharesOrCopiesAtLeastInitialScalar_214) {
  YAML::detail::node_ref a;
  a.set_scalar("shared");
  YAML::detail::node_ref b;

  b.set_data(a);

  // Observable minimum: after set_data, b sees the same scalar value as a.
  EXPECT_EQ(b.scalar(), a.scalar());
  EXPECT_EQ(b.scalar(), "shared");
}

TEST_F(NodeRefScalarTest_214, SetDataThenMutationsAreObservedAcrossRefs_214) {
  YAML::detail::node_ref a;
  a.set_scalar("one");

  YAML::detail::node_ref b;
  b.set_data(a);

  // If node_ref is sharing underlying data (as suggested by set_data + shared_node_data),
  // updates through one ref should be observable through the other.
  a.set_scalar("two");
  EXPECT_EQ(b.scalar(), "two");

  b.set_scalar("three");
  EXPECT_EQ(a.scalar(), "three");
}

}  // namespace