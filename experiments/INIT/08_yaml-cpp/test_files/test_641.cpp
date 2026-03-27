// TEST_ID: 641
#include <gtest/gtest.h>

#include "yaml-cpp/mark.h"
#include "yaml-cpp/node/detail/node_data.h"

namespace {

using YAML::Mark;
using YAML::detail::node_data;

class NodeDataSetMarkTest_641 : public ::testing::Test {
 protected:
  node_data data_;
};

TEST_F(NodeDataSetMarkTest_641, DefaultMarkIsAccessible_641) {
  // Observable behavior: mark() returns a Mark reference.
  const Mark& m = data_.mark();
  (void)m;  // Just ensure it is callable and returns a reference.
}

TEST_F(NodeDataSetMarkTest_641, SetMarkCopiesProvidedMarkValues_641) {
  Mark m;
  m.pos = 123;
  m.line = 45;
  m.column = 6;

  data_.set_mark(m);

  const Mark& got = data_.mark();
  EXPECT_EQ(got.pos, 123);
  EXPECT_EQ(got.line, 45);
  EXPECT_EQ(got.column, 6);
}

TEST_F(NodeDataSetMarkTest_641, SetMarkWithNullMarkUpdatesMark_641) {
  const Mark nullM = Mark::null_mark();

  data_.set_mark(nullM);

  const Mark& got = data_.mark();
  EXPECT_EQ(got.pos, nullM.pos);
  EXPECT_EQ(got.line, nullM.line);
  EXPECT_EQ(got.column, nullM.column);
}

TEST_F(NodeDataSetMarkTest_641, SetMarkCanBeCalledMultipleTimesLastWins_641) {
  Mark first;
  first.pos = 1;
  first.line = 2;
  first.column = 3;

  Mark second;
  second.pos = 10;
  second.line = 20;
  second.column = 30;

  data_.set_mark(first);
  data_.set_mark(second);

  const Mark& got = data_.mark();
  EXPECT_EQ(got.pos, 10);
  EXPECT_EQ(got.line, 20);
  EXPECT_EQ(got.column, 30);
}

TEST_F(NodeDataSetMarkTest_641, SetMarkHandlesExtremeIntegerValues_641) {
  Mark m;
  m.pos = std::numeric_limits<int>::max();
  m.line = std::numeric_limits<int>::min();
  m.column = std::numeric_limits<int>::max();

  data_.set_mark(m);

  const Mark& got = data_.mark();
  EXPECT_EQ(got.pos, std::numeric_limits<int>::max());
  EXPECT_EQ(got.line, std::numeric_limits<int>::min());
  EXPECT_EQ(got.column, std::numeric_limits<int>::max());
}

}  // namespace