// AnnotPath_getCoordsLength_736_test.cpp
// Unit tests for AnnotPath::getCoordsLength()
// The TEST_ID is 736

#include <gtest/gtest.h>

#include "./TestProjects/poppler/poppler/Annot.h"

#include <vector>
#include <limits>

namespace {

class AnnotPathTest_736 : public ::testing::Test {};

TEST_F(AnnotPathTest_736, DefaultConstructedHasZeroLength_736) {
  AnnotPath path;
  EXPECT_EQ(path.getCoordsLength(), 0);
}

TEST_F(AnnotPathTest_736, ConstObjectMethodCallReturnsLength_736) {
  const AnnotPath path;
  EXPECT_EQ(path.getCoordsLength(), 0);
}

TEST_F(AnnotPathTest_736, MoveVectorConstructorReflectsVectorSize_736) {
  // Boundary-ish: small non-zero size
  std::vector<AnnotCoord> coords(3);
  const int expected = static_cast<int>(coords.size());

  AnnotPath path(std::move(coords));
  EXPECT_EQ(path.getCoordsLength(), expected);
}

TEST_F(AnnotPathTest_736, MoveEmptyVectorConstructorReturnsZero_736) {
  std::vector<AnnotCoord> coords;
  AnnotPath path(std::move(coords));
  EXPECT_EQ(path.getCoordsLength(), 0);
}

TEST_F(AnnotPathTest_736, LargerVectorSizeIsReportedCorrectly_736) {
  // Boundary: a larger count (still safe for typical unit tests)
  constexpr int kN = 1000;
  std::vector<AnnotCoord> coords(static_cast<size_t>(kN));

  AnnotPath path(std::move(coords));
  EXPECT_EQ(path.getCoordsLength(), kN);
}

}  // namespace