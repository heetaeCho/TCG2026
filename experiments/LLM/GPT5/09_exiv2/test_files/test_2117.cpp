// ============================================================================
// TEST_ID 2117
// Unit tests for IsCoreSyntaxTerm (ParseRDF.cpp)
// ============================================================================

#include <gtest/gtest.h>

// NOTE:
// IsCoreSyntaxTerm is defined as `static` in ParseRDF.cpp (internal linkage).
// To test it via its observable interface, we include the implementation file
// into this test translation unit so the symbol is visible here.
//
// Ensure your test target does NOT also compile/link ParseRDF.cpp separately
// (otherwise you may get ODR / duplicate symbol issues).
#include "TestProjects/exiv2/xmpsdk/src/ParseRDF.cpp"

namespace {

TEST(IsCoreSyntaxTermTest_2117, FirstCoreReturnsTrue_2117) {
  EXPECT_TRUE(IsCoreSyntaxTerm(kRDFTerm_FirstCore));
}

TEST(IsCoreSyntaxTermTest_2117, LastCoreReturnsTrue_2117) {
  EXPECT_TRUE(IsCoreSyntaxTerm(kRDFTerm_LastCore));
}

TEST(IsCoreSyntaxTermTest_2117, ValueJustBelowFirstCoreReturnsFalse_2117) {
  // Avoid unsigned underflow by doing arithmetic in int.
  const int below = static_cast<int>(kRDFTerm_FirstCore) - 1;
  const RDFTermKind term = static_cast<RDFTermKind>(below);
  EXPECT_FALSE(IsCoreSyntaxTerm(term));
}

TEST(IsCoreSyntaxTermTest_2117, ValueJustAboveLastCoreReturnsFalse_2117) {
  const int above = static_cast<int>(kRDFTerm_LastCore) + 1;
  const RDFTermKind term = static_cast<RDFTermKind>(above);
  EXPECT_FALSE(IsCoreSyntaxTerm(term));
}

TEST(IsCoreSyntaxTermTest_2117, MidRangeValueReturnsTrueWhenRangeHasInterior_2117) {
  const int first = static_cast<int>(kRDFTerm_FirstCore);
  const int last  = static_cast<int>(kRDFTerm_LastCore);

  // If the range has no interior (first == last), this test becomes equivalent
  // to the boundary tests and still must be correct.
  const int midInt = first + (last - first) / 2;
  const RDFTermKind mid = static_cast<RDFTermKind>(midInt);

  EXPECT_TRUE(IsCoreSyntaxTerm(mid));
}

TEST(IsCoreSyntaxTermTest_2117, FarOutsideRangeReturnsFalse_2117) {
  // Pick a value far above the last core term (still via int arithmetic).
  const int farAbove = static_cast<int>(kRDFTerm_LastCore) + 100;
  const RDFTermKind term = static_cast<RDFTermKind>(farAbove);

  EXPECT_FALSE(IsCoreSyntaxTerm(term));
}

}  // namespace