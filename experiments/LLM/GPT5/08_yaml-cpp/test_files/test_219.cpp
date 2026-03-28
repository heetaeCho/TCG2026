// TEST_ID: 219
#include <gtest/gtest.h>

#include <climits>
#include <limits>

#include "yaml-cpp/mark.h"
#include "yaml-cpp/node/detail/node_ref.h"

namespace {

using YAML::Mark;
using YAML::detail::node_ref;

Mark MakeMark(int pos, int line, int column) {
  Mark m;
  m.pos = pos;
  m.line = line;
  m.column = column;
  return m;
}

void ExpectMarkEq(const Mark& actual, const Mark& expected) {
  EXPECT_EQ(actual.pos, expected.pos);
  EXPECT_EQ(actual.line, expected.line);
  EXPECT_EQ(actual.column, expected.column);
}

}  // namespace

// Normal operation: set_mark updates the observable mark() value.
TEST(NodeRefSetMarkTest_219, SetMarkUpdatesMark_219) {
  node_ref ref;

  const Mark m = MakeMark(7, 8, 9);
  EXPECT_NO_THROW(ref.set_mark(m));

  const Mark& got = ref.mark();
  ExpectMarkEq(got, m);
}

// Boundary conditions: extreme / negative values are stored and observable.
TEST(NodeRefSetMarkTest_219, SetMarkAcceptsExtremeValues_219) {
  node_ref ref;

  const Mark m1 = MakeMark(0, 0, 0);
  EXPECT_NO_THROW(ref.set_mark(m1));
  ExpectMarkEq(ref.mark(), m1);

  const Mark m2 = MakeMark(-1, -1, -1);
  EXPECT_NO_THROW(ref.set_mark(m2));
  ExpectMarkEq(ref.mark(), m2);

  const Mark m3 = MakeMark(std::numeric_limits<int>::max(),
                           std::numeric_limits<int>::max(),
                           std::numeric_limits<int>::max());
  EXPECT_NO_THROW(ref.set_mark(m3));
  ExpectMarkEq(ref.mark(), m3);

  const Mark m4 = MakeMark(std::numeric_limits<int>::min(),
                           std::numeric_limits<int>::min(),
                           std::numeric_limits<int>::min());
  EXPECT_NO_THROW(ref.set_mark(m4));
  ExpectMarkEq(ref.mark(), m4);
}

// Error/exceptional (observable): calling set_mark repeatedly should not throw and
// the most recent mark should be observable.
TEST(NodeRefSetMarkTest_219, SetMarkMultipleTimesLastWriteWins_219) {
  node_ref ref;

  const Mark m1 = MakeMark(1, 2, 3);
  const Mark m2 = MakeMark(10, 20, 30);

  EXPECT_NO_THROW(ref.set_mark(m1));
  ExpectMarkEq(ref.mark(), m1);

  EXPECT_NO_THROW(ref.set_mark(m2));
  ExpectMarkEq(ref.mark(), m2);
}

// External interaction (via public API): if set_data makes two node_ref instances
// refer to the same underlying data, mark changes should be visible across them.
// This test verifies the observable behavior of set_data + set_mark together.
TEST(NodeRefSetMarkTest_219, SetDataSharesOrCopiesMarkObservableBehavior_219) {
  node_ref a;
  node_ref b;

  // Connect b's data to a via the public API.
  EXPECT_NO_THROW(b.set_data(a));

  const Mark m1 = MakeMark(3, 4, 5);
  EXPECT_NO_THROW(a.set_mark(m1));
  // If set_data shares, b should observe m1. If it copies-at-call-time, it may
  // or may not (depending on implementation). We assert what must be true for
  // the connected state to be meaningful: b observes a's current mark after set_data.
  ExpectMarkEq(b.mark(), a.mark());

  const Mark m2 = MakeMark(30, 40, 50);
  EXPECT_NO_THROW(b.set_mark(m2));
  // Symmetric observable check: after updating b, both should match if they share.
  // If implementation is copy-on-write, it may diverge; the interface-observable
  // expectation we can assert safely is that b reflects what it set.
  ExpectMarkEq(b.mark(), m2);
}