// File: test_resolvedLens_1018.cpp
// TEST_ID = 1018

#include <gtest/gtest.h>

#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>

// NOTE:
// resolvedLens(...) is declared "static" in minoltamn_int.cpp (internal linkage).
// To test it through its observable behavior without re-implementing any logic,
// we include the .cpp so the function is available in this translation unit.
//
// This is a common technique for unit-testing TU-local helpers.
#include "minoltamn_int.cpp"

namespace {

static std::string CallResolvedLensToString_1018(long lensId, long index) {
  std::ostringstream oss;
  Exiv2::Internal::resolvedLens(oss, lensId, index);
  return oss.str();
}

}  // namespace

TEST(ResolvedLensTest_1018, SingleTokenIndex1ReturnsFullLabel_1018) {
  // lensID 0 has a single label without '|'
  const std::string out = CallResolvedLensToString_1018(/*lensID=*/0, /*index=*/1);
  EXPECT_EQ(out, "Minolta AF 28-85mm F3.5-4.5 New");
}

TEST(ResolvedLensTest_1018, MultiTokenIndex1ReturnsFirstTokenTrimmed_1018) {
  // lensID 7 contains multiple alternatives separated by '|'
  const std::string out = CallResolvedLensToString_1018(/*lensID=*/7, /*index=*/1);
  EXPECT_EQ(out, "Minolta AF 100-300mm F4.5-5.6 (D) APO [New]");
}

TEST(ResolvedLensTest_1018, MultiTokenIndex2ReturnsSecondTokenTrimmed_1018) {
  const std::string out = CallResolvedLensToString_1018(/*lensID=*/7, /*index=*/2);
  EXPECT_EQ(out, "Minolta AF 100-400mm F4.5-6.7 (D)");
}

TEST(ResolvedLensTest_1018, MultiTokenIndex3ReturnsThirdTokenTrimmed_1018) {
  const std::string out = CallResolvedLensToString_1018(/*lensID=*/7, /*index=*/3);
  EXPECT_EQ(out, "Sigma AF 100-300mm F4 EX DG IF");
}

TEST(ResolvedLensTest_1018, TrailingWhitespaceInLabelIsTrimmed_1018) {
  // lensID 29 label (as shown) ends with a trailing space.
  const std::string out = CallResolvedLensToString_1018(/*lensID=*/29, /*index=*/1);
  EXPECT_EQ(out, "Minolta/Sony AF 75-300mm F4.5-5.6 (D)");
}

TEST(ResolvedLensTest_1018, IndexZeroThrowsOutOfRange_1018) {
  // tokens.at(index - 1) with index==0 should be out-of-range.
  EXPECT_THROW((void)CallResolvedLensToString_1018(/*lensID=*/0, /*index=*/0), std::out_of_range);
}

TEST(ResolvedLensTest_1018, IndexTooLargeThrowsOutOfRange_1018) {
  // lensID 0 has only one token; requesting index 2 is out-of-range.
  EXPECT_THROW((void)CallResolvedLensToString_1018(/*lensID=*/0, /*index=*/2), std::out_of_range);
}

TEST(ResolvedLensTest_1018, MultiTokenIndexTooLargeThrowsOutOfRange_1018) {
  // lensID 7 has three tokens; requesting index 4 is out-of-range.
  EXPECT_THROW((void)CallResolvedLensToString_1018(/*lensID=*/7, /*index=*/4), std::out_of_range);
}