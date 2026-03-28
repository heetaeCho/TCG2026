// File: test_ParseRDF_IsOldTerm_2118.cpp
#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

// Include the .cpp directly so the TU can see the file-scope `static` function.
// This is a common unit-test technique for testing internal-linkage helpers.
#include "TestProjects/exiv2/xmpsdk/src/ParseRDF.cpp"

namespace {

class ParseRDF_IsOldTermTest_2118 : public ::testing::Test {};

TEST_F(ParseRDF_IsOldTermTest_2118, ReturnsTrueAtFirstOld_2118) {
  const RDFTermKind term = static_cast<RDFTermKind>(kRDFTerm_FirstOld);
  EXPECT_TRUE(IsOldTerm(term));
}

TEST_F(ParseRDF_IsOldTermTest_2118, ReturnsTrueAtLastOld_2118) {
  const RDFTermKind term = static_cast<RDFTermKind>(kRDFTerm_LastOld);
  EXPECT_TRUE(IsOldTerm(term));
}

TEST_F(ParseRDF_IsOldTermTest_2118, ReturnsTrueForValueBetweenBounds_2118) {
  // Pick a stable "between" value when possible; otherwise fall back to the lower bound.
  RDFTermKind term = static_cast<RDFTermKind>(kRDFTerm_FirstOld);
  if (kRDFTerm_FirstOld < kRDFTerm_LastOld) {
    term = static_cast<RDFTermKind>(static_cast<int>(kRDFTerm_FirstOld) +
                                    (static_cast<int>(kRDFTerm_LastOld) -
                                     static_cast<int>(kRDFTerm_FirstOld)) /
                                        2);
  }
  EXPECT_TRUE(IsOldTerm(term));
}

TEST_F(ParseRDF_IsOldTermTest_2118, ReturnsFalseForValueJustBelowFirstOld_2118) {
  // Only perform this check when "just below" is representable without underflow.
  const int first = static_cast<int>(kRDFTerm_FirstOld);
  if (first > std::numeric_limits<RDFTermKind>::min()) {
    const RDFTermKind term = static_cast<RDFTermKind>(first - 1);
    EXPECT_FALSE(IsOldTerm(term));
  } else {
    // If the lower bound is already the minimum representable, a "below" value can't exist.
    SUCCEED();
  }
}

TEST_F(ParseRDF_IsOldTermTest_2118, ReturnsFalseForValueJustAboveLastOld_2118) {
  // Only perform this check when "just above" is representable without overflow.
  const int last = static_cast<int>(kRDFTerm_LastOld);
  if (last < std::numeric_limits<RDFTermKind>::max()) {
    const RDFTermKind term = static_cast<RDFTermKind>(last + 1);
    EXPECT_FALSE(IsOldTerm(term));
  } else {
    // If the upper bound is already the maximum representable, an "above" value can't exist.
    SUCCEED();
  }
}

TEST_F(ParseRDF_IsOldTermTest_2118, ReturnsFalseForMinimumRepresentableWhenOutOfRange_2118) {
  const RDFTermKind minVal = std::numeric_limits<RDFTermKind>::min();
  const bool expected = (static_cast<int>(kRDFTerm_FirstOld) <= static_cast<int>(minVal)) &&
                        (static_cast<int>(minVal) <= static_cast<int>(kRDFTerm_LastOld));
  EXPECT_EQ(IsOldTerm(minVal), expected);
}

TEST_F(ParseRDF_IsOldTermTest_2118, ReturnsFalseForMaximumRepresentableWhenOutOfRange_2118) {
  const RDFTermKind maxVal = std::numeric_limits<RDFTermKind>::max();
  const bool expected = (static_cast<int>(kRDFTerm_FirstOld) <= static_cast<int>(maxVal)) &&
                        (static_cast<int>(maxVal) <= static_cast<int>(kRDFTerm_LastOld));
  EXPECT_EQ(IsOldTerm(maxVal), expected);
}

}  // namespace