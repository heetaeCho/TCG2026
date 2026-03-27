// File: tests/AnsiSkippingStringConstIterator_postfix_38_test.cpp

#include <type_traits>
#include <utility>
#include <gtest/gtest.h>

// Include the provided header (path from the prompt)
#include "Catch2/src/catch2/internal/catch_textflow.hpp"

namespace {

template <typename T, typename = void>
struct has_postfix_inc : std::false_type {};

template <typename T>
struct has_postfix_inc<T, std::void_t<decltype(std::declval<T&>()++)>> : std::true_type {};

template <typename T, typename = void>
struct has_postfix_inc_const : std::false_type {};

template <typename T>
struct has_postfix_inc_const<
    T,
    std::void_t<decltype(std::declval<const T&>()++)>> : std::true_type {};

} // namespace

using Iter = Catch::TextFlow::AnsiSkippingString::const_iterator;

//
// NOTE:
// These tests only assert interface & type semantics that are observable at
// compile time, which is all we can check from the given interface without
// constructing concrete iterators or relying on hidden state/behaviour.
//

// 1) The postfix operator++ exists for a non-const lvalue and returns *a value*
//    (i.e., a non-reference), which is copy-constructible.
TEST(AnsiSkippingStringIteratorTest_38, PostfixExistsAndReturnsByValue_38) {
  static_assert(has_postfix_inc<Iter>::value,
                "const_iterator must support postfix operator++(int) on lvalues");

  using PostRet = decltype(std::declval<Iter&>()++);

  // It should return by value (not a reference).
  static_assert(!std::is_reference<PostRet>::value,
                "Postfix operator++(int) should return by value");

  // The returned type must be copy-constructible (so the old value can be used).
  static_assert(std::is_copy_constructible<PostRet>::value,
                "Result of postfix operator++(int) must be copy-constructible");

  SUCCEED(); // Runtime part succeeds if the compile-time interface checks pass.
}

// 2) The postfix operator++ should NOT be invocable on a const lvalue
//    (since the signature is non-const in the provided interface).
TEST(AnsiSkippingStringIteratorTest_38, PostfixNotCallableOnConstLvalue_38) {
  static_assert(!has_postfix_inc_const<Iter>::value,
                "Postfix operator++(int) should not be callable on const lvalues");
  SUCCEED();
}

// 3) Chained postfix expressions are well-formed at the type level
//    (i.e., the temporary produced by i++ also supports i++), which is a
//    common iterator requirement. We only check well-formedness via decltype.
TEST(AnsiSkippingStringIteratorTest_38, ChainedPostfixIsWellFormed_38) {
  // Form the type of (it++)++ in an unevaluated context.
  using ChainedType = decltype( std::declval<Iter&>()++ ++ );
  // And ensure it is a value type (not a reference).
  static_assert(!std::is_reference<ChainedType>::value,
                "Chained postfix result should be a value (non-reference)");
  SUCCEED();
}

// 4) The postfix operator accepts an int dummy parameter (as per standard form).
//    We validate that calling with literal 0 is well-formed in decltype context.
TEST(AnsiSkippingStringIteratorTest_38, PostfixAcceptsIntDummy_38) {
  using ExplicitCallType = decltype(std::declval<Iter&>().operator++(0));
  static_assert(!std::is_reference<ExplicitCallType>::value,
                "Explicit postfix operator++(int) should return by value");
  SUCCEED();
}
