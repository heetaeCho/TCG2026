// File: sparse_array_index_value_tests_83.cc
#include <type_traits>
#include <utility>
#include <gtest/gtest.h>

// Header under test
#include "re2/sparse_array.h"

namespace {

// Helper: detect presence of a nested typedef T::iterator
template <typename T, typename = void>
struct has_nested_iterator : std::false_type {};
template <typename T>
struct has_nested_iterator<T, std::void_t<typename T::iterator>> : std::true_type {};

// Helper: detect presence of namespace-scope re2::iterator
template <typename = void>
struct has_ns_iterator : std::false_type {};
template <>
struct has_ns_iterator<std::void_t<decltype(std::declval<re2::iterator>())>> : std::true_type {};

} // namespace

// Test suite strictly targets the *public* interface contracts that can be verified by types.
class SparseArrayIndexValueTest_83 : public ::testing::Test {};

// [83] The return type of IndexValue::value() is an lvalue reference (observable by type).
TEST_F(SparseArrayIndexValueTest_83, ValueReturnsLvalueReference_83) {
  using IndexValue = typename re2::SparseArray::IndexValue;

  // value() must return an lvalue reference (modifiable reference) to its Value.
  static_assert(std::is_lvalue_reference_v<decltype(std::declval<IndexValue&>().value())>,
                "IndexValue::value() must return an lvalue reference.");
  SUCCEED(); // Runtime success to keep this as a gtest case.
}

// [83] value() is not callable on a const IndexValue (no const-qualified overload exposed).
TEST_F(SparseArrayIndexValueTest_83, ValueNotCallableOnConst_83) {
  using IndexValue = typename re2::SparseArray::IndexValue;

  // Pointer-to-member function type: Value& (IndexValue::*)()
  auto pmf = &IndexValue::value;
  (void)pmf;

  // Check invocability: should NOT be invocable on const IndexValue& because method isn't const.
  static_assert(!std::is_invocable_v<decltype(&IndexValue::value), const IndexValue&>,
                "IndexValue::value() should not be invocable on const IndexValue.");
  SUCCEED();
}

// [83] iterator typedef (if exposed) points to IndexValue.
TEST_F(SparseArrayIndexValueTest_83, IteratorTypedefPointsToIndexValue_83) {
  using SA = re2::SparseArray;
  using IndexValue = typename SA::IndexValue;

  if constexpr (has_nested_iterator<SA>::value) {
    // Prefer nested typedef if present: SA::iterator == IndexValue*
    static_assert(std::is_same_v<typename SA::iterator, IndexValue*>,
                  "SparseArray::iterator must be IndexValue*.");
  } else if constexpr (has_ns_iterator<>::value) {
    // Some headers expose iterator at namespace scope: re2::iterator == IndexValue*
    static_assert(std::is_same_v<re2::iterator, IndexValue*>,
                  "re2::iterator must be IndexValue*.");
  } else {
    // If neither typedef is present, this assertion gives a clear compile-time message.
    static_assert(sizeof(IndexValue) == 0,
                  "No iterator typedef found; expected SparseArray::iterator or re2::iterator.");
  }
  SUCCEED();
}

// [83] const_iterator typedef (if exposed) points to const IndexValue.
TEST_F(SparseArrayIndexValueTest_83, ConstIteratorTypedefPointsToConstIndexValue_83) {
  using SA = re2::SparseArray;
  using IndexValue = typename SA::IndexValue;

  // Local detectors to avoid hard failures if not present.
  struct has_nested_const_iterator {
    template <typename T>
    static auto test(int) -> decltype(std::declval<typename T::const_iterator>(), std::true_type{});
    template <typename>
    static auto test(...) -> std::false_type;
    static constexpr bool value = decltype(test<SA>(0))::value;
  };
  struct has_ns_const_iterator {
    template <typename = void>
    static auto test(int) -> decltype(std::declval<re2::const_iterator>(), std::true_type{});
    template <typename>
    static auto test(...) -> std::false_type;
    static constexpr bool value = decltype(test<>(0))::value;
  };

  if constexpr (has_nested_const_iterator::value) {
    static_assert(std::is_same_v<typename SA::const_iterator, const IndexValue*>,
                  "SparseArray::const_iterator must be const IndexValue*.");
  } else if constexpr (has_ns_const_iterator::value) {
    static_assert(std::is_same_v<re2::const_iterator, const IndexValue*>,
                  "re2::const_iterator must be const IndexValue*.");
  } else {
    static_assert(sizeof(IndexValue) == 0,
                  "No const_iterator typedef found; expected SparseArray::const_iterator or re2::const_iterator.");
  }
  SUCCEED();
}
