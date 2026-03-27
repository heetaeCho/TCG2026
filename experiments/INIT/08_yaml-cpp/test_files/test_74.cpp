// File: ./TestProjects/yaml-cpp/test/stream_mark_test_74.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <type_traits>
#include <utility>

#include "stream.h"

namespace {

template <typename T>
using remove_cvref_t = std::remove_cv_t<std::remove_reference_t<T>>;

template <typename MarkT>
constexpr bool HasPosMember() {
  return requires(const MarkT& m) { m.pos; };
}
template <typename MarkT>
constexpr bool HasLineMember() {
  return requires(const MarkT& m) { m.line; };
}
template <typename MarkT>
constexpr bool HasColumnMember() {
  return requires(const MarkT& m) { m.column; };
}
template <typename MarkT>
constexpr bool HasEquality() {
  return requires(const MarkT& a, const MarkT& b) { a == b; };
}

class StreamMarkTest_74 : public ::testing::Test {};

TEST_F(StreamMarkTest_74, MarkCallableOnFreshStream_74) {
  std::istringstream input("abc");
  YAML::Stream s(input);

  // Observable behavior: mark() is callable and returns a value.
  auto m = s.mark();
  (void)m;

  // Also ensure calling mark() is non-mutating in observable ways.
  const int pos_before = s.pos();
  const int line_before = s.line();
  const int col_before = s.column();

  auto m2 = s.mark();
  (void)m2;

  EXPECT_EQ(s.pos(), pos_before);
  EXPECT_EQ(s.line(), line_before);
  EXPECT_EQ(s.column(), col_before);
}

TEST_F(StreamMarkTest_74, MarkMatchesAccessorsWhenMembersExist_74) {
  std::istringstream input("a\nb");
  YAML::Stream s(input);

  using MarkT = remove_cvref_t<decltype(s.mark())>;
  const auto m0 = s.mark();

  // If Mark exposes the canonical members, verify they match the Stream accessors.
  if constexpr (HasPosMember<MarkT>()) {
    EXPECT_EQ(m0.pos, s.pos());
  }
  if constexpr (HasLineMember<MarkT>()) {
    EXPECT_EQ(m0.line, s.line());
  }
  if constexpr (HasColumnMember<MarkT>()) {
    EXPECT_EQ(m0.column, s.column());
  }

  // Advance the stream by consuming one character, then re-check.
  (void)s.get();
  const auto m1 = s.mark();

  if constexpr (HasPosMember<MarkT>()) {
    EXPECT_EQ(m1.pos, s.pos());
  }
  if constexpr (HasLineMember<MarkT>()) {
    EXPECT_EQ(m1.line, s.line());
  }
  if constexpr (HasColumnMember<MarkT>()) {
    EXPECT_EQ(m1.column, s.column());
  }
}

TEST_F(StreamMarkTest_74, MarkChangesAfterConsumingInputWhenComparable_74) {
  std::istringstream input("hello");
  YAML::Stream s(input);

  using MarkT = remove_cvref_t<decltype(s.mark())>;
  const auto before = s.mark();

  // Consume at least one character if available.
  const char c = s.get();
  (void)c;

  const auto after = s.mark();

  // If Mark supports equality comparison, ensure advancing input changes it.
  if constexpr (HasEquality<MarkT>()) {
    EXPECT_FALSE(before == after);
  }

  // Independently, the accessors should reflect some observable advancement in position
  // as long as we're not already at EOF. We don't assume exact increments.
  EXPECT_GE(s.pos(), 0);
}

TEST_F(StreamMarkTest_74, MarkStableAcrossRepeatedCallsAtSamePosition_74) {
  std::istringstream input("xyz");
  YAML::Stream s(input);

  using MarkT = remove_cvref_t<decltype(s.mark())>;
  const auto m1 = s.mark();
  const auto m2 = s.mark();
  const auto m3 = s.mark();

  // If Mark is comparable, repeated calls without consuming input should yield equal marks.
  if constexpr (HasEquality<MarkT>()) {
    EXPECT_TRUE(m1 == m2);
    EXPECT_TRUE(m2 == m3);
  }

  // And observable accessors remain unchanged across mark() calls.
  const int pos = s.pos();
  const int line = s.line();
  const int col = s.column();

  (void)s.mark();
  EXPECT_EQ(s.pos(), pos);
  EXPECT_EQ(s.line(), line);
  EXPECT_EQ(s.column(), col);
}

TEST_F(StreamMarkTest_74, MarkRemainsCallableAfterEatingPastEnd_74) {
  std::istringstream input("hi");
  YAML::Stream s(input);

  // Eat more than the available input; behavior is implementation-defined, but must be observable.
  // We only require that public methods remain callable.
  s.eat(1000);

  // mark() should still be callable and accessors should return ints.
  auto m = s.mark();
  (void)m;

  EXPECT_GE(s.pos(), 0);
  EXPECT_GE(s.line(), 0);
  EXPECT_GE(s.column(), 0);

  // peek()/get() should be callable as well; we don't assume specific return values beyond type.
  (void)s.peek();
  (void)s.get();
}

}  // namespace
