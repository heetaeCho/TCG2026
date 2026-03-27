// ============================================================================
// File: ExpatAdapterTest_2090.cpp
// Unit tests for XMP_NewExpatAdapter factory function (ExpatAdapter.cpp)
// TEST_ID: 2090
// ============================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <type_traits>

// Try to include the real declaration if it exists in the build.
// (Keeps the test robust across different xmpsdk header layouts.)
#if __has_include("ExpatAdapter.hpp")
  #include "ExpatAdapter.hpp"
#elif __has_include("ExpatAdapter.h")
  #include "ExpatAdapter.h"
#elif __has_include("ExpatAdapter.hpp")
  #include <ExpatAdapter.hpp>
#elif __has_include("ExpatAdapter.h")
  #include <ExpatAdapter.h>
#endif

// If headers were not available or don't declare the symbols (some build layouts do this),
// fall back to forward declarations. This does NOT infer or re-implement logic; it only
// provides the minimal interface needed to compile the tests.
#ifndef XMP_NEW_EXPAT_ADAPTER_DECLARED_FOR_TEST_2090
// If the class is already declared by headers, this forward-decl is harmless.
class ExpatAdapter;

// Factory under test (implemented in ExpatAdapter.cpp).
ExpatAdapter* XMP_NewExpatAdapter();
#endif

namespace {

TEST(ExpatAdapterFactoryTest_2090, ReturnsNonNull_2090) {
  ExpatAdapter* adapter = nullptr;
  ASSERT_NO_THROW(adapter = XMP_NewExpatAdapter());
  ASSERT_NE(adapter, nullptr);

  // Clean up to avoid leaks in the test suite.
  delete adapter;
}

TEST(ExpatAdapterFactoryTest_2090, ReturnsDistinctInstancesOnMultipleCalls_2090) {
  ExpatAdapter* a = XMP_NewExpatAdapter();
  ExpatAdapter* b = XMP_NewExpatAdapter();

  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);

  // Observable behavior: factory uses dynamic allocation and should produce distinct objects.
  EXPECT_NE(a, b);

  delete a;
  delete b;
}

TEST(ExpatAdapterFactoryTest_2090, ReturnedPointerIsDeletable_2090) {
  ExpatAdapter* adapter = XMP_NewExpatAdapter();
  ASSERT_NE(adapter, nullptr);

  // Boundary-ish: ensure the pointer can be deleted safely.
  // (No reliance on internal state; only verifies valid lifetime management via interface.)
  EXPECT_NO_THROW(delete adapter);
}

TEST(ExpatAdapterFactoryTest_2090, CanCreateAndDestroyManyTimes_2090) {
  // Boundary condition: repeated use (helps catch gross lifetime/allocation issues).
  for (int i = 0; i < 100; ++i) {
    ExpatAdapter* adapter = XMP_NewExpatAdapter();
    ASSERT_NE(adapter, nullptr) << "Iteration " << i;
    delete adapter;
  }
}

}  // namespace