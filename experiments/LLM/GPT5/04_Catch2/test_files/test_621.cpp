// File: columns_iterator_postfix_increment_621_test.cpp

#include <type_traits>
#include <utility>
#include <gtest/gtest.h>

// Bring in the provided implementation snippet so the types/symbols exist.
// We do not depend on or assert any internal behavior.
#include "Catch2/src/catch2/internal/catch_textflow.cpp"

namespace {

template <typename, typename = void>
struct has_postfix_on_lvalue : std::false_type {};

template <typename T>
struct has_postfix_on_lvalue<T, std::void_t<decltype(std::declval<T&>()++)>>
    : std::true_type {};

template <typename, typename = void>
struct has_postfix_on_const_lvalue : std::false_type {};

template <typename T>
struct has_postfix_on_const_lvalue<T, std::void_t<decltype(std::declval<const T&>()++)>>
    : std::true_type {};

template <typename, typename = void>
struct has_postfix_on_rvalue : std::false_type {};

template <typename T>
struct has_postfix_on_rvalue<T, std::void_t<decltype(std::declval<T>()++)>>
    : std::true_type {};

template <typename, typename = void>
struct has_chained_postfix : std::false_type {};

template <typename T>
struct has_chained_postfix<T, std::void_t<decltype( (std::declval<T&>()++)++ )>>
    : std::true_type {};

} // namespace

using It621 = Catch::TextFlow::Columns::iterator;

// Verifies the postfix increment operator exists and returns by value of the same type.
TEST(ColumnsIteratorTraits_621, PostfixExistsAndReturnsByValue_621) {
  static_assert(has_postfix_on_lvalue<It621>::value,
                "Columns::iterator must support postfix ++ on lvalues.");
  static_assert(std::is_same<decltype(std::declval<It621&>()++), It621>::value,
                "Postfix ++ must return iterator by value (not reference).");
  SUCCEED();
}

// Ensures the operator is *not* available on const lvalues (typical iterator contract).
TEST(ColumnsIteratorTraits_621, PostfixNotCallableOnConstLvalue_621) {
  static_assert(!has_postfix_on_const_lvalue<It621>::value,
                "Postfix ++ should not be callable on const iterator.");
  SUCCEED();
}

// Confirms postfix can be applied to rvalues (the provided definition operates on *this by value).
TEST(ColumnsIteratorTraits_621, PostfixCallableOnRvalue_621) {
  static_assert(has_postfix_on_rvalue<It621>::value,
                "Postfix ++ should be callable on rvalue iterator (temporary).");
  // Also reconfirm the exact return type on rvalues is by value of the same iterator.
  static_assert(std::is_same<decltype(std::declval<It621>()++), It621>::value,
                "Postfix ++ on rvalue must return iterator by value.");
  SUCCEED();
}

// The implementation copies the iterator (iterator prev(*this)), so the type must be copy-constructible.
TEST(ColumnsIteratorTraits_621, IteratorIsCopyConstructible_621) {
  static_assert(std::is_copy_constructible<It621>::value,
                "Columns::iterator must be copy-constructible.");
  SUCCEED();
}

// Chained postfix like (it++)++ should be well-formed since the first postfix returns by value.
TEST(ColumnsIteratorTraits_621, ChainedPostfixIsWellFormed_621) {
  static_assert(has_chained_postfix<It621>::value,
                "(it++)++ should be a well-formed expression.");
  SUCCEED();
}
