// test_node_set_mark_248.cpp

#include <gtest/gtest.h>

#include "yaml-cpp/mark.h"
#include "yaml-cpp/node/detail/node.h"

namespace {

class NodeSetMarkTest_248 : public ::testing::Test {};

TEST_F(NodeSetMarkTest_248, SetMarkWithDefaultConstructedMark_248) {
  YAML::detail::node n;

  YAML::Mark m;  // default-constructed (pos/line/column are publicly readable)
  n.set_mark(m);

  const YAML::Mark& got = n.mark();
  EXPECT_EQ(got.pos, m.pos);
  EXPECT_EQ(got.line, m.line);
  EXPECT_EQ(got.column, m.column);
}

TEST_F(NodeSetMarkTest_248, SetMarkWithNullMark_248) {
  YAML::detail::node n;

  const YAML::Mark nm = YAML::Mark::null_mark();
  n.set_mark(nm);

  const YAML::Mark& got = n.mark();
  // Verify observable "null-ness" via the public API.
  EXPECT_EQ(got.is_null(), nm.is_null());

  // If fields are meaningful for null marks, they should still be observable and comparable.
  EXPECT_EQ(got.pos, nm.pos);
  EXPECT_EQ(got.line, nm.line);
  EXPECT_EQ(got.column, nm.column);
}

TEST_F(NodeSetMarkTest_248, SetMarkIsRepeatable_248) {
  YAML::detail::node n;

  YAML::Mark m;
  n.set_mark(m);
  n.set_mark(m);

  const YAML::Mark& got = n.mark();
  EXPECT_EQ(got.pos, m.pos);
  EXPECT_EQ(got.line, m.line);
  EXPECT_EQ(got.column, m.column);
}

}  // namespace