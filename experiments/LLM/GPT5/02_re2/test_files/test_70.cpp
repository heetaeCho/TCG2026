// File: sparse_array_size_test.cc
#include <gtest/gtest.h>

#include "re2/sparse_array.h"

namespace {

// Choose a concrete value type in case SparseArray is templated.
// If SparseArray is not templated in your build, the alias below will fail to compile;
// in that case, replace `IntSparseArray` with `re2::SparseArray`.
#if defined(__cpp_lib_is_detected) || __cplusplus >= 201703L
// Try to detect if SparseArray is templated by attempting an alias.
// If your environment doesn't support this trick, you can directly use re2::SparseArray<int>.
using IntSparseArray = re2::SparseArray<int>;
#else
using IntSparseArray = re2::SparseArray<int>;
#endif

// No fixture needed since we only validate size() via construction/assignment.

TEST(SparseArray_SizeOnly_70, DefaultConstructed_SizeIsZero_70) {
  // Verifies: size() on a default-constructed instance.
  IntSparseArray a;
  EXPECT_EQ(a.size(), 0);
}

TEST(SparseArray_SizeOnly_70, SizeCallableOnConstObject_70) {
  // Verifies: size() is const-qualified and callable on const instances.
  const IntSparseArray a;
  EXPECT_EQ(a.size(), 0);
}

TEST(SparseArray_SizeOnly_70, CopyConstruct_PreservesObservedSize_70) {
  // Verifies: copy-constructing preserves observed size via size().
  IntSparseArray a;
  // (We don't assume any mutators; we only observe size().)
  IntSparseArray b = a;
  EXPECT_EQ(a.size(), b.size());
}

TEST(SparseArray_SizeOnly_70, MoveConstruct_PreservesDestinationObservedSize_70) {
  // Verifies: move-constructing yields an object with a well-defined observed size.
  IntSparseArray a;
  IntSparseArray b = std::move(a);
  // We cannot assume what happens to 'a' after move; only check 'b' is a valid object
  // with an observable size() that is consistent with a newly constructed instance.
  EXPECT_EQ(b.size(), 0);
}

TEST(SparseArray_SizeOnly_70, CopyAssign_PreservesObservedSize_70) {
  // Verifies: copy assignment preserves observed size in destination.
  IntSparseArray a;
  IntSparseArray b;
  b = a;
  EXPECT_EQ(a.size(), b.size());
}

TEST(SparseArray_SizeOnly_70, MoveAssign_PreservesDestinationObservedSize_70) {
  // Verifies: move assignment yields a destination with a well-defined observed size.
  IntSparseArray a;
  IntSparseArray b;
  b = std::move(a);
  // As with move construction, we only assert observable behavior of 'b'.
  EXPECT_EQ(b.size(), 0);
}

}  // namespace
