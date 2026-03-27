// TEST_ID: 58
// File: Object_ref_operator_ne_test.cpp
//
// Unit tests for:
//   inline bool operator!=(const Ref lhs, const Ref rhs) noexcept;
//
// Constraints honored:
// - Treat implementation as a black box (only observable behavior: return value)
// - No private/internal access (Ref is a simple struct in the provided interface)
// - Boundary + normal cases covered

#include <gtest/gtest.h>

// Re-declare the minimal interface provided by the prompt.
// In your real codebase, you should prefer including the actual header:
//   #include "poppler/Object.h"
struct Ref {
  int num;
  int gen;
  static constexpr Ref INVALID();
};

// The operator under test (as provided).
inline bool operator!=(const Ref lhs, const Ref rhs) noexcept {
  return lhs.num != rhs.num || lhs.gen != rhs.gen;
}

// Helper: define INVALID() if needed by the project; not used by these tests.
// Keep it constexpr and simple to avoid implying internal logic.
// If your real header already defines it, remove this definition and include the header above.
constexpr Ref Ref::INVALID() { return Ref{-1, -1}; }

class RefOperatorNotEqualTest_58 : public ::testing::Test {};

TEST_F(RefOperatorNotEqualTest_58, SameNumSameGen_ReturnsFalse_58) {
  Ref a{10, 0};
  Ref b{10, 0};

  EXPECT_FALSE(a != b);
}

TEST_F(RefOperatorNotEqualTest_58, DifferentNumSameGen_ReturnsTrue_58) {
  Ref a{10, 0};
  Ref b{11, 0};

  EXPECT_TRUE(a != b);
}

TEST_F(RefOperatorNotEqualTest_58, SameNumDifferentGen_ReturnsTrue_58) {
  Ref a{10, 0};
  Ref b{10, 1};

  EXPECT_TRUE(a != b);
}

TEST_F(RefOperatorNotEqualTest_58, DifferentNumDifferentGen_ReturnsTrue_58) {
  Ref a{10, 0};
  Ref b{11, 1};

  EXPECT_TRUE(a != b);
}

TEST_F(RefOperatorNotEqualTest_58, BoundaryValues_IntMinAndMax_NumOrGenDifferencesObserved_58) {
  Ref base{0, 0};

  Ref numMin{std::numeric_limits<int>::min(), 0};
  Ref numMax{std::numeric_limits<int>::max(), 0};
  Ref genMin{0, std::numeric_limits<int>::min()};
  Ref genMax{0, std::numeric_limits<int>::max()};

  EXPECT_TRUE(base != numMin);
  EXPECT_TRUE(base != numMax);
  EXPECT_TRUE(base != genMin);
  EXPECT_TRUE(base != genMax);

  // Also check that identical boundary refs compare as equal (i.e., != is false).
  EXPECT_FALSE(numMin != Ref{std::numeric_limits<int>::min(), 0});
  EXPECT_FALSE(genMax != Ref{0, std::numeric_limits<int>::max()});
}

TEST_F(RefOperatorNotEqualTest_58, Symmetry_HoldsForVariousPairs_58) {
  Ref a{1, 2};
  Ref b{1, 3};
  Ref c{2, 2};

  // Symmetry expectation: (a != b) == (b != a)
  EXPECT_EQ(a != b, b != a);
  EXPECT_EQ(a != c, c != a);
  EXPECT_EQ(b != c, c != b);

  // Also for equal pair
  Ref d{5, 6};
  Ref e{5, 6};
  EXPECT_EQ(d != e, e != d);
}

TEST_F(RefOperatorNotEqualTest_58, NoThrow_IsNoexcept_58) {
  Ref a{1, 1};
  Ref b{2, 2};

  // Compile-time check of the noexcept contract.
  static_assert(noexcept(a != b), "operator!= for Ref must be noexcept");

  // Runtime sanity: calling it should not throw.
  EXPECT_NO_THROW({
    (void)(a != b);
    (void)(a != a);
  });
}