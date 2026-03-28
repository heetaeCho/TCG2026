// File: matchers_templated_or_operator_tests_170.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include <string>

// Include the header under test
#include <catch2/matchers/catch_matchers_templated.hpp>

namespace test_helpers {

// Minimal generic matchers for black-box testing.
// They derive from MatcherGenericBase and provide template match + describe(),
// which is enough for Catch2 to consider them "generic" matchers.
struct TrueGM : Catch::Matchers::MatcherGenericBase {
  template <typename T>
  bool match(const T&) const { return true; }
  std::string describe() const override { return "TrueGM"; }
};

struct FalseGM : Catch::Matchers::MatcherGenericBase {
  template <typename T>
  bool match(const T&) const { return false; }
  std::string describe() const override { return "FalseGM"; }
};

}  // namespace test_helpers

// Alias to shorten type names in tests
template <typename... Ts>
using MatchAnyOfGeneric = Catch::Matchers::Detail::MatchAnyOfGeneric<Ts...>;

using test_helpers::TrueGM;
using test_helpers::FalseGM;

//
// 1) Type: operator||(generic, generic) -> MatchAnyOfGeneric<L, R>
//
TEST(TemplatedOrMatcherTest_170, ReturnTypeIsMatchAnyOfGeneric_170) {
  TrueGM t;
  FalseGM f;
  using Expected = MatchAnyOfGeneric<TrueGM, FalseGM>;
  // Verify declared return type — no reliance on internals
  bool same = std::is_same_v<decltype(t || f), Expected>;
  EXPECT_TRUE(same);
}

//
// 2) Semantics: OR behavior is observable via match()
//    (true || false) => true, (false || false) => false, (true || true) => true
//
TEST(TemplatedOrMatcherTest_170, EvaluatesOrSemantics_170) {
  TrueGM  t1; TrueGM  t2;
  FalseGM f1; FalseGM f2;

  // Use lvalues so addresses stored inside the combined matcher remain valid
  auto tf = t1 || f1;
  auto ff = f1 || f2;
  auto tt = t1 || t2;

  EXPECT_TRUE ( tf.match(42) );      // true || false -> true
  EXPECT_FALSE( ff.match(0)  );      // false || false -> false
  EXPECT_TRUE ( tt.match("x") );     // true || true -> true
}

//
// 3) Temporaries: should be usable immediately within the same full-expression
//
TEST(TemplatedOrMatcherTest_170, AcceptsTemporariesUsedImmediately_170) {
  // Do not store the result; use it immediately (safe full-expression lifetime)
  EXPECT_TRUE( (TrueGM{} || FalseGM{}).match(123) );
  EXPECT_FALSE( (FalseGM{} || FalseGM{}).match(123) );
}

//
// 4) Chaining: (a || b) || c flattens into MatchAnyOfGeneric<A,B,C>, not nested
//
TEST(TemplatedOrMatcherTest_170, ChainedOrFlattensType_LeftAssoc_170) {
  TrueGM t; FalseGM f;
  using Expected = MatchAnyOfGeneric<TrueGM, FalseGM, TrueGM>;
  bool same = std::is_same_v<decltype( (t || f) || t ), Expected>;
  EXPECT_TRUE(same);
}

//
// 5) Chaining (other side): a || (b || c) also flattens to A,B,C
//
TEST(TemplatedOrMatcherTest_170, ChainedOrFlattensType_RightAssoc_170) {
  TrueGM t; FalseGM f;
  using Expected = MatchAnyOfGeneric<TrueGM, FalseGM, TrueGM>;
  bool same = std::is_same_v<decltype( t || (f || t) ), Expected>;
  EXPECT_TRUE(same);
}

//
// 6) Description: combined describe() should include children and " or "
//
TEST(TemplatedOrMatcherTest_170, DescribeCombinesChildDescriptions_170) {
  TrueGM t; FalseGM f;
  auto combined = t || f;
  const std::string desc = combined.describe();

  // We do not assert exact formatting — just that key parts are present.
  EXPECT_NE(desc.find("TrueGM"),  std::string::npos);
  EXPECT_NE(desc.find("FalseGM"), std::string::npos);
  EXPECT_NE(desc.find(" or "),    std::string::npos);
}
