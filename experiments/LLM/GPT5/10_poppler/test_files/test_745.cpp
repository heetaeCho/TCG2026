// File: test_annot_quadrilaterals_745.cpp
// Unit tests for AnnotQuadrilaterals (Poppler)
// TEST_ID: 745

#include <gtest/gtest.h>

#include <memory>

#include "poppler/Annot.h"

class AnnotQuadrilateralsTest_745 : public ::testing::Test {
protected:
  // Helper to create a quadrilateral array of a given size, without assuming any
  // internal fields/initialization requirements beyond being default-constructible.
  static std::unique_ptr<AnnotQuadrilateral[]> MakeQuads(int n) {
    if (n <= 0) {
      return std::unique_ptr<AnnotQuadrilateral[]>();
    }
    return std::unique_ptr<AnnotQuadrilateral[]>(new AnnotQuadrilateral[n]);
  }
};

TEST_F(AnnotQuadrilateralsTest_745, ReturnsProvidedLengthForZero_745) {
  // Boundary: length == 0
  auto quads = MakeQuads(0);
  AnnotQuadrilaterals a(std::move(quads), 0);

  EXPECT_EQ(a.getQuadrilateralsLength(), 0);
}

TEST_F(AnnotQuadrilateralsTest_745, ReturnsProvidedLengthForOne_745) {
  // Normal: length == 1
  auto quads = MakeQuads(1);
  AnnotQuadrilaterals a(std::move(quads), 1);

  EXPECT_EQ(a.getQuadrilateralsLength(), 1);
}

TEST_F(AnnotQuadrilateralsTest_745, ReturnsProvidedLengthForMultiple_745) {
  // Normal: length > 1
  constexpr int kLen = 5;
  auto quads = MakeQuads(kLen);
  AnnotQuadrilaterals a(std::move(quads), kLen);

  EXPECT_EQ(a.getQuadrilateralsLength(), kLen);
}

TEST_F(AnnotQuadrilateralsTest_745, LengthStableAcrossRepeatedCalls_745) {
  // Observable behavior: repeated calls return consistent value
  constexpr int kLen = 3;
  auto quads = MakeQuads(kLen);
  AnnotQuadrilaterals a(std::move(quads), kLen);

  const int first = a.getQuadrilateralsLength();
  const int second = a.getQuadrilateralsLength();
  const int third = a.getQuadrilateralsLength();

  EXPECT_EQ(first, kLen);
  EXPECT_EQ(second, kLen);
  EXPECT_EQ(third, kLen);
}

TEST_F(AnnotQuadrilateralsTest_745, UsesConstructorLengthEvenIfArrayMoved_745) {
  // Boundary/robustness: ensure the length is determined by the public ctor input.
  // We don't inspect moved-from state (black-box), only that the created object reports
  // the expected length.
  constexpr int kLen = 2;
  auto quads = MakeQuads(kLen);

  AnnotQuadrilaterals a(std::move(quads), kLen);
  EXPECT_EQ(a.getQuadrilateralsLength(), kLen);
}

TEST_F(AnnotQuadrilateralsTest_745, LargeLengthReportsSameValue_745) {
  // Boundary: "large-ish" value while still reasonable for unit tests.
  // (Avoids huge allocations/time while still testing non-trivial input.)
  constexpr int kLen = 128;
  auto quads = MakeQuads(kLen);
  AnnotQuadrilaterals a(std::move(quads), kLen);

  EXPECT_EQ(a.getQuadrilateralsLength(), kLen);
}