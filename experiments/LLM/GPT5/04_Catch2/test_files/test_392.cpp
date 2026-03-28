// File: tests/Clara_Opt_Subscript_392.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include <utility>

#include "catch2/internal/catch_clara.hpp"
#include "catch2/internal/catch_stringref.hpp"

namespace {
  using Catch::Clara::Opt;
  using Catch::StringRef;

  // Detection idiom: is the expression T_expr well-formed?
  template <typename, typename = void>
  struct is_valid : std::false_type {};

  template <typename T>
  struct is_valid<T, std::void_t<T>> : std::true_type {};

  // Try forming: std::declval<Opt&>()[std::declval<StringRef>()]
  using LValueCallExpr =
      decltype(std::declval<Opt&>()[std::declval<StringRef>()]);

  // Try forming: std::declval<Opt&&>()[std::declval<StringRef>()]  (rvalue)
  using RValueCallExpr =
      decltype(std::declval<Opt&&>()[std::declval<StringRef>()]);

  // Try forming: std::declval<Opt&>()["-v"]  (argument convertible to StringRef)
  using LiteralArgExpr =
      decltype(std::declval<Opt&>()["-v"]);
}

// 1) Returns Opt& on lvalues (enables chaining) --------------------------------
TEST(ClaraOptTest_392, LvalueSubscriptReturnsLvalueRef_392) {
  static_assert(std::is_same<LValueCallExpr, Opt&>::value,
                "operator[] on lvalue must return Opt&");
  SUCCEED();
}

// 2) Chaining preserves Opt& (Opt& after two subscripts) -----------------------
TEST(ClaraOptTest_392, ChainingReturnsLvalueRef_392) {
  using ChainExpr =
      decltype(std::declval<Opt&>()[std::declval<StringRef>()][std::declval<StringRef>()]);
  static_assert(std::is_same<ChainExpr, Opt&>::value,
                "Chained operator[] must still return Opt&");
  SUCCEED();
}

// 3) operator[] is NOT callable on rvalues (it is lvalue-qualified) ------------
TEST(ClaraOptTest_392, NotInvocableOnRvalue_392) {
  static_assert(!is_valid<RValueCallExpr>::value,
                "operator[] must be lvalue-qualified and not accept rvalues");
  SUCCEED();
}

// 4) Accepts arguments convertible to StringRef (e.g., string literals) --------
TEST(ClaraOptTest_392, AcceptsStringLiteralConvertibleToStringRef_392) {
  static_assert(std::is_same<LiteralArgExpr, Opt&>::value,
                "operator[] should accept types convertible to StringRef");
  SUCCEED();
}
