// File: match_all_of_and_operator_test_158.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include <array>

// Header under test
#include "catch2/matchers/catch_matchers_templated.hpp"

using Catch::Matchers::Detail::MatchAllOfGeneric;

// Dummy matcher tag types (no behavior — we test only the container/operator)
struct A {};
struct B {};
struct C {};
struct D {};

// Distinct addresses we can stuff into the public m_matchers (observable state)
static int g_a, g_b, g_c, g_d;

class MatchAllOfAndOperatorTest_158 : public ::testing::Test {};

// Helper to build a MatchAllOfGeneric<Ts...> from raw pointer array (public ctor)
template <typename... Ts>
static MatchAllOfGeneric<Ts...> MakeWithPtrs(std::initializer_list<void const*> ptrs) {
  std::array<void const*, sizeof...(Ts)> arr{};
  std::copy(ptrs.begin(), ptrs.end(), arr.begin());
  return MatchAllOfGeneric<Ts...>(arr);
}

// --- Tests ---

// Verifies that combining two non-empty packs concatenates the pointers in-order.
TEST_F(MatchAllOfAndOperatorTest_158, Combine_NonEmptyConcatOrder_158) {
  auto lhs = MakeWithPtrs<A, B>({&g_a, &g_b});
  auto rhs = MakeWithPtrs<C>({&g_c});

  auto combined = std::move(lhs) && std::move(rhs);

  ASSERT_EQ(combined.m_matchers.size(), 3u);
  EXPECT_EQ(combined.m_matchers[0], &g_a);
  EXPECT_EQ(combined.m_matchers[1], &g_b);
  EXPECT_EQ(combined.m_matchers[2], &g_c);
}

// Verifies template type of the result is MatchAllOfGeneric<A,B,C>.
TEST_F(MatchAllOfAndOperatorTest_158, Type_CompositionMatchesTemplateParams_158) {
  auto lhs = MakeWithPtrs<A, B>({&g_a, &g_b});
  auto rhs = MakeWithPtrs<C>({&g_c});

  using ResultT = decltype(std::move(lhs) && std::move(rhs));
  static_assert(std::is_same<ResultT, MatchAllOfGeneric<A, B, C>>::value,
                "operator&& must produce a concatenated parameter pack type");
  SUCCEED();
}

// Left empty + right non-empty -> result equals right contents.
TEST_F(MatchAllOfAndOperatorTest_158, Combine_LeftEmptyRightNonEmpty_158) {
  auto lhs = MakeWithPtrs<>({});                 // zero-length std::array is valid
  auto rhs = MakeWithPtrs<C, D>({&g_c, &g_d});

  auto combined = std::move(lhs) && std::move(rhs);

  ASSERT_EQ(combined.m_matchers.size(), 2u);
  EXPECT_EQ(combined.m_matchers[0], &g_c);
  EXPECT_EQ(combined.m_matchers[1], &g_d);
}

// Left non-empty + right empty -> result equals left contents.
TEST_F(MatchAllOfAndOperatorTest_158, Combine_RightEmptyLeftNonEmpty_158) {
  auto lhs = MakeWithPtrs<A>({&g_a});
  auto rhs = MakeWithPtrs<>({});

  auto combined = std::move(lhs) && std::move(rhs);

  ASSERT_EQ(combined.m_matchers.size(), 1u);
  EXPECT_EQ(combined.m_matchers[0], &g_a);
}

// Empty + Empty -> still valid, size 0.
TEST_F(MatchAllOfAndOperatorTest_158, Combine_BothEmpty_158) {
  auto lhs = MakeWithPtrs<>({});
  auto rhs = MakeWithPtrs<>({});

  auto combined = std::move(lhs) && std::move(rhs);

  EXPECT_EQ(combined.m_matchers.size(), 0u);
}

// Chaining: (A,B) && (C) && (D) preserves order across multiple && applications.
TEST_F(MatchAllOfAndOperatorTest_158, Combine_ChainingPreservesOrder_158) {
  auto ab = MakeWithPtrs<A, B>({&g_a, &g_b});
  auto c  = MakeWithPtrs<C>({&g_c});
  auto d  = MakeWithPtrs<D>({&g_d});

  auto abc = std::move(ab) && std::move(c);
  auto abcd = std::move(abc) && std::move(d);

  ASSERT_EQ(abcd.m_matchers.size(), 4u);
  EXPECT_EQ(abcd.m_matchers[0], &g_a);
  EXPECT_EQ(abcd.m_matchers[1], &g_b);
  EXPECT_EQ(abcd.m_matchers[2], &g_c);
  EXPECT_EQ(abcd.m_matchers[3], &g_d);
}
