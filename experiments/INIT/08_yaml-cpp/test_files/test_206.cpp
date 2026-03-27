// TEST_ID: 206
#include <gtest/gtest.h>

#include "yaml-cpp/mark.h"
#include "yaml-cpp/node/detail/node_data.h"

namespace {

using YAML::Mark;
using YAML::detail::node_data;

class NodeDataMarkTest_206 : public ::testing::Test {};

TEST_F(NodeDataMarkTest_206, DefaultMarkIsNullMark_206) {
  node_data nd;

  const Mark& m = nd.mark();
  const Mark nullm = Mark::null_mark();

  // Compare observable fields (avoid relying on internal storage details).
  EXPECT_EQ(m.pos, nullm.pos);
  EXPECT_EQ(m.line, nullm.line);
  EXPECT_EQ(m.column, nullm.column);
}

TEST_F(NodeDataMarkTest_206, MarkReturnsStableReferenceAcrossCalls_206) {
  node_data nd;

  const Mark* p1 = &nd.mark();
  const Mark* p2 = &nd.mark();

  EXPECT_EQ(p1, p2);
}

TEST_F(NodeDataMarkTest_206, MarkCallableOnConstNodeData_206) {
  const node_data nd;

  const Mark& m = nd.mark();
  const Mark nullm = Mark::null_mark();

  EXPECT_EQ(m.pos, nullm.pos);
  EXPECT_EQ(m.line, nullm.line);
  EXPECT_EQ(m.column, nullm.column);
}

}  // namespace