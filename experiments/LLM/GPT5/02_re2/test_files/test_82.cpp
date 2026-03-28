// File: sparse_array_index_value_test_82.cc
#include <gtest/gtest.h>
#include <type_traits>
#include <utility>

// Header under test
#include "re2/sparse_array.h"

namespace {

using re2::SparseArray;

// Test suite name must include TEST_ID per requirements.
class SparseArrayIndexValueTest_82 : public ::testing::Test {};

}  // namespace

// Verifies: IndexValue::index() exists and returns int.
// This relies solely on the function signature; no instances are created.
TEST_F(SparseArrayIndexValueTest_82, IndexReturnTypeIsInt_82) {
  using IV = SparseArray::IndexValue;
  // Unevaluated context: checks the declared return type without constructing IV.
  const bool is_int = std::is_same<decltype(std::declval<const IV>().index()), int>::value;
  EXPECT_TRUE(is_int);
}

// Verifies: IndexValue::index() is callable on a const object (i.e., method is const-qualified).
// Uses sizeof in an unevaluated context to avoid any runtime access.
TEST_F(SparseArrayIndexValueTest_82, IndexCallableOnConst_82) {
  using IV = SparseArray::IndexValue;
  const IV* p = nullptr;
  // If index() is not const-qualified, this line fails to compile.
  (void)sizeof(p->index());
  SUCCEED();
}

// Verifies: iterator typedef matches the documented interface (pointer to IndexValue).
TEST_F(SparseArrayIndexValueTest_82, IteratorTypedefMatchesInterface_82) {
  using Iter = SparseArray::iterator;
  using Expected = SparseArray::IndexValue*;
  EXPECT_TRUE((std::is_same<Iter, Expected>::value));
}

// Verifies: const_iterator typedef matches the documented interface (pointer to const IndexValue).
TEST_F(SparseArrayIndexValueTest_82, ConstIteratorTypedefMatchesInterface_82) {
  using CIter = SparseArray::const_iterator;
  using Expected = const SparseArray::IndexValue*;
  EXPECT_TRUE((std::is_same<CIter, Expected>::value));
}
