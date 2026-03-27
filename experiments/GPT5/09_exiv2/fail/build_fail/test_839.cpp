// ============================================================================
// TestProjects/exiv2/tests/value_xmptextvalue_toInt64_test.cpp
// TEST_ID: 839
// ============================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <limits>
#include <type_traits>

// Prefer the public Exiv2 header if available; fall back to local include paths.
#if __has_include(<exiv2/value.hpp>)
#include <exiv2/value.hpp>
#elif __has_include("value.hpp")
#include "value.hpp"
#elif __has_include("value.h")
#include "value.h"
#else
// If your build system provides Exiv2 headers via another path, adjust includes here.
#include "exiv2/value.hpp"
#endif

namespace {

// Black-box tests for Exiv2::XmpTextValue::toInt64(size_t).
// We deliberately do NOT assume how parsing works or how the internal value is stored.
// We only test observable properties implied by the signature and shown implementation:
// - The parameter is unused (/*n*/).
// - Return type is int64_t.
// - The call should be stable for the same object across calls and across n values.

class XmpTextValueTest_839 : public ::testing::Test {};

TEST_F(XmpTextValueTest_839, ReturnTypeIsInt64_839) {
  // Compile-time check: the function returns int64_t.
  const Exiv2::XmpTextValue v;
  static_assert(std::is_same_v<decltype(v.toInt64(0)), int64_t>,
                "XmpTextValue::toInt64 must return int64_t");
}

TEST_F(XmpTextValueTest_839, SameObjectDifferentIndicesReturnSameValue_839) {
  const Exiv2::XmpTextValue v;

  // The signature (and provided code) indicates the index is ignored.
  const int64_t r0 = v.toInt64(0);
  const int64_t r1 = v.toInt64(1);
  const int64_t rMax = v.toInt64(std::numeric_limits<size_t>::max());

  EXPECT_EQ(r0, r1);
  EXPECT_EQ(r0, rMax);
}

TEST_F(XmpTextValueTest_839, RepeatedCallsAreStableForSameIndex_839) {
  const Exiv2::XmpTextValue v;

  const int64_t r1 = v.toInt64(0);
  const int64_t r2 = v.toInt64(0);
  const int64_t r3 = v.toInt64(0);

  EXPECT_EQ(r1, r2);
  EXPECT_EQ(r2, r3);
}

TEST_F(XmpTextValueTest_839, RepeatedCallsAreStableAcrossDifferentIndices_839) {
  const Exiv2::XmpTextValue v;

  const int64_t a = v.toInt64(0);
  const int64_t b = v.toInt64(123);
  const int64_t c = v.toInt64(std::numeric_limits<size_t>::max());
  const int64_t d = v.toInt64(0);

  EXPECT_EQ(a, b);
  EXPECT_EQ(a, c);
  EXPECT_EQ(a, d);
}

TEST_F(XmpTextValueTest_839, CopyConstructedObjectMatchesOriginal_839) {
  const Exiv2::XmpTextValue original;
  const Exiv2::XmpTextValue copy = original;

  // Without assuming internal state, we can still assert that the observable conversion
  // matches for a copied object.
  EXPECT_EQ(original.toInt64(0), copy.toInt64(0));
  EXPECT_EQ(original.toInt64(1), copy.toInt64(999));
  EXPECT_EQ(original.toInt64(std::numeric_limits<size_t>::max()),
            copy.toInt64(std::numeric_limits<size_t>::max()));
}

TEST_F(XmpTextValueTest_839, BoundaryIndicesDoNotCrash_839) {
  const Exiv2::XmpTextValue v;

  // Boundary coverage for size_t argument. We do not assert a particular numeric value,
  // only that calling is well-defined enough to return a value.
  (void)v.toInt64(0);
  (void)v.toInt64(1);
  (void)v.toInt64(std::numeric_limits<size_t>::max());

  SUCCEED();
}

}  // namespace