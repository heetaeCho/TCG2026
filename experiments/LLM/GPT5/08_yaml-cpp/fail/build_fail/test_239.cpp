// test_node_mark_239.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/mark.h"

namespace {

using YAML::Mark;
using YAML::detail::node;

// ---- Compile-time helpers to avoid assuming Mark's exact API ----

template <typename T, typename = void>
struct has_equal_op : std::false_type {};
template <typename T>
struct has_equal_op<T, std::void_t<decltype(std::declval<const T&>() == std::declval<const T&>())>>
    : std::true_type {};

template <typename T, typename = void>
struct has_pos_member : std::false_type {};
template <typename T>
struct has_pos_member<T, std::void_t<decltype(std::declval<const T&>().pos)>> : std::true_type {};

template <typename T, typename = void>
struct has_line_member : std::false_type {};
template <typename T>
struct has_line_member<T, std::void_t<decltype(std::declval<const T&>().line)>> : std::true_type {};

template <typename T, typename = void>
struct has_column_member : std::false_type {};
template <typename T>
struct has_column_member<T, std::void_t<decltype(std::declval<const T&>().column)>> : std::true_type {};

static Mark MakeMark(int pos, int line, int column) {
  if constexpr (std::is_constructible<Mark, int, int, int>::value) {
    return Mark(pos, line, column);
  } else if constexpr (std::is_constructible<Mark, int, int>::value) {
    // Best-effort: treat as (line, column).
    return Mark(line, column);
  } else if constexpr (std::is_constructible<Mark, int>::value) {
    return Mark(pos);
  } else {
    Mark m{};
    // Best-effort assignment if public fields exist.
    if constexpr (has_pos_member<Mark>::value) m.pos = pos;
    if constexpr (has_line_member<Mark>::value) m.line = line;
    if constexpr (has_column_member<Mark>::value) m.column = column;
    return m;
  }
}

static void ExpectMarkEqual(const Mark& a, const Mark& b) {
  if constexpr (has_equal_op<Mark>::value) {
    EXPECT_TRUE(a == b);
  } else if constexpr (has_pos_member<Mark>::value || has_line_member<Mark>::value ||
                       has_column_member<Mark>::value) {
    if constexpr (has_pos_member<Mark>::value) EXPECT_EQ(a.pos, b.pos);
    if constexpr (has_line_member<Mark>::value) EXPECT_EQ(a.line, b.line);
    if constexpr (has_column_member<Mark>::value) EXPECT_EQ(a.column, b.column);
  } else {
    // If Mark provides neither operator== nor public members, we can't compare content
    // without guessing internal structure. We still validate reference forwarding elsewhere.
    SUCCEED();
  }
}

class NodeMarkTest_239 : public ::testing::Test {};

}  // namespace

TEST_F(NodeMarkTest_239, MarkReturnsSameReferenceAsRefMark_239) {
  node n;

  const Mark& m = n.mark();
  const auto* r = n.ref();

  ASSERT_NE(r, nullptr);
  EXPECT_EQ(&m, &r->mark());  // node::mark() forwards to the underlying node_ref::mark()
}

TEST_F(NodeMarkTest_239, MarkReferenceIsStableAcrossCalls_239) {
  node n;

  const Mark& m1 = n.mark();
  const Mark& m2 = n.mark();

  EXPECT_EQ(&m1, &m2);  // same referred object across repeated calls
}

TEST_F(NodeMarkTest_239, SetMarkIsObservableThroughMarkGetter_239) {
  node n;

  const Mark before = n.mark();

  const Mark desired = MakeMark(/*pos=*/11, /*line=*/22, /*column=*/33);
  EXPECT_NO_THROW(n.set_mark(desired));

  const Mark& after_ref = n.mark();

  // Still forwards to underlying ref mark storage.
  ASSERT_NE(n.ref(), nullptr);
  EXPECT_EQ(&after_ref, &n.ref()->mark());

  // Content comparison only if it's observable without guessing Mark internals.
  // If we can compare, verify it changed from "before" (unless before already matched desired),
  // and verify it matches desired.
  ExpectMarkEqual(after_ref, desired);

  if constexpr (has_equal_op<Mark>::value) {
    if (!(before == desired)) {
      EXPECT_FALSE(before == after_ref);
    }
  } else if constexpr (has_pos_member<Mark>::value || has_line_member<Mark>::value ||
                       has_column_member<Mark>::value) {
    bool same_as_desired = true;
    if constexpr (has_pos_member<Mark>::value) same_as_desired &= (before.pos == desired.pos);
    if constexpr (has_line_member<Mark>::value) same_as_desired &= (before.line == desired.line);
    if constexpr (has_column_member<Mark>::value)
      same_as_desired &= (before.column == desired.column);

    if (!same_as_desired) {
      if constexpr (has_pos_member<Mark>::value) EXPECT_NE(before.pos, after_ref.pos);
      if constexpr (has_line_member<Mark>::value) EXPECT_NE(before.line, after_ref.line);
      if constexpr (has_column_member<Mark>::value) EXPECT_NE(before.column, after_ref.column);
    }
  }
}

TEST_F(NodeMarkTest_239, MarkCallableOnConstNode_239) {
  node n;
  const node& cn = n;

  const Mark& m = cn.mark();
  ASSERT_NE(cn.ref(), nullptr);
  EXPECT_EQ(&m, &cn.ref()->mark());
}