#include <gtest/gtest.h>
#include "PDFRectangle.h"

// Test equality of two default-constructed PDFRectangles
TEST(PDFRectangleTest_684, DefaultConstructedRectanglesAreEqual_684)
{
    PDFRectangle a;
    PDFRectangle b;
    EXPECT_TRUE(a == b);
}

// Test equality of two identical non-default rectangles
TEST(PDFRectangleTest_684, IdenticalRectanglesAreEqual_684)
{
    PDFRectangle a(1.0, 2.0, 3.0, 4.0);
    PDFRectangle b(1.0, 2.0, 3.0, 4.0);
    EXPECT_TRUE(a == b);
}

// Test inequality when x1 differs
TEST(PDFRectangleTest_684, DifferentX1NotEqual_684)
{
    PDFRectangle a(1.0, 2.0, 3.0, 4.0);
    PDFRectangle b(9.0, 2.0, 3.0, 4.0);
    EXPECT_FALSE(a == b);
}

// Test inequality when y1 differs
TEST(PDFRectangleTest_684, DifferentY1NotEqual_684)
{
    PDFRectangle a(1.0, 2.0, 3.0, 4.0);
    PDFRectangle b(1.0, 9.0, 3.0, 4.0);
    EXPECT_FALSE(a == b);
}

// Test inequality when x2 differs
TEST(PDFRectangleTest_684, DifferentX2NotEqual_684)
{
    PDFRectangle a(1.0, 2.0, 3.0, 4.0);
    PDFRectangle b(1.0, 2.0, 9.0, 4.0);
    EXPECT_FALSE(a == b);
}

// Test inequality when y2 differs
TEST(PDFRectangleTest_684, DifferentY2NotEqual_684)
{
    PDFRectangle a(1.0, 2.0, 3.0, 4.0);
    PDFRectangle b(1.0, 2.0, 3.0, 9.0);
    EXPECT_FALSE(a == b);
}

// Test equality with negative coordinates
TEST(PDFRectangleTest_684, NegativeCoordinatesEqual_684)
{
    PDFRectangle a(-1.0, -2.0, -3.0, -4.0);
    PDFRectangle b(-1.0, -2.0, -3.0, -4.0);
    EXPECT_TRUE(a == b);
}

// Test inequality when all fields differ
TEST(PDFRectangleTest_684, AllFieldsDifferNotEqual_684)
{
    PDFRectangle a(1.0, 2.0, 3.0, 4.0);
    PDFRectangle b(5.0, 6.0, 7.0, 8.0);
    EXPECT_FALSE(a == b);
}

// Test equality with very large values
TEST(PDFRectangleTest_684, LargeValuesEqual_684)
{
    PDFRectangle a(1e15, 1e15, 1e15, 1e15);
    PDFRectangle b(1e15, 1e15, 1e15, 1e15);
    EXPECT_TRUE(a == b);
}

// Test equality with very small values
TEST(PDFRectangleTest_684, SmallValuesEqual_684)
{
    PDFRectangle a(1e-15, 1e-15, 1e-15, 1e-15);
    PDFRectangle b(1e-15, 1e-15, 1e-15, 1e-15);
    EXPECT_TRUE(a == b);
}

// Test equality with zero rectangle
TEST(PDFRectangleTest_684, ZeroRectangleEqual_684)
{
    PDFRectangle a(0.0, 0.0, 0.0, 0.0);
    PDFRectangle b;
    EXPECT_TRUE(a == b);
}

// Test symmetry of equality operator
TEST(PDFRectangleTest_684, EqualityIsSymmetric_684)
{
    PDFRectangle a(1.0, 2.0, 3.0, 4.0);
    PDFRectangle b(1.0, 2.0, 3.0, 4.0);
    EXPECT_TRUE(a == b);
    EXPECT_TRUE(b == a);
}

// Test symmetry of inequality
TEST(PDFRectangleTest_684, InequalityIsSymmetric_684)
{
    PDFRectangle a(1.0, 2.0, 3.0, 4.0);
    PDFRectangle b(5.0, 6.0, 7.0, 8.0);
    EXPECT_FALSE(a == b);
    EXPECT_FALSE(b == a);
}

// Test reflexivity: a rectangle equals itself
TEST(PDFRectangleTest_684, EqualityIsReflexive_684)
{
    PDFRectangle a(1.5, 2.5, 3.5, 4.5);
    EXPECT_TRUE(a == a);
}

// Test isValid on a proper rectangle
TEST(PDFRectangleTest_684, IsValidForProperRectangle_684)
{
    PDFRectangle a(0.0, 0.0, 100.0, 200.0);
    EXPECT_TRUE(a.isValid());
}

// Test isValid on default rectangle
TEST(PDFRectangleTest_684, IsValidForDefaultRectangle_684)
{
    PDFRectangle a;
    // Default rectangle has all zeros; behavior depends on implementation
    // We just observe the result
    (void)a.isValid();
}

// Test isEmpty on a zero-area rectangle
TEST(PDFRectangleTest_684, IsEmptyForZeroAreaRectangle_684)
{
    PDFRectangle a(0.0, 0.0, 0.0, 0.0);
    EXPECT_TRUE(a.isEmpty());
}

// Test isEmpty on a non-empty rectangle
TEST(PDFRectangleTest_684, IsEmptyForNonEmptyRectangle_684)
{
    PDFRectangle a(0.0, 0.0, 10.0, 10.0);
    EXPECT_FALSE(a.isEmpty());
}

// Test contains for a point inside the rectangle
TEST(PDFRectangleTest_684, ContainsPointInside_684)
{
    PDFRectangle a(0.0, 0.0, 10.0, 10.0);
    EXPECT_TRUE(a.contains(5.0, 5.0));
}

// Test contains for a point outside the rectangle
TEST(PDFRectangleTest_684, ContainsPointOutside_684)
{
    PDFRectangle a(0.0, 0.0, 10.0, 10.0);
    EXPECT_FALSE(a.contains(15.0, 15.0));
}

// Test contains for a point on the boundary
TEST(PDFRectangleTest_684, ContainsPointOnBoundary_684)
{
    PDFRectangle a(0.0, 0.0, 10.0, 10.0);
    // Boundary behavior: at corner
    EXPECT_TRUE(a.contains(0.0, 0.0));
    EXPECT_TRUE(a.contains(10.0, 10.0));
}

// Test contains for a point on the edge
TEST(PDFRectangleTest_684, ContainsPointOnEdge_684)
{
    PDFRectangle a(0.0, 0.0, 10.0, 10.0);
    EXPECT_TRUE(a.contains(5.0, 0.0));
    EXPECT_TRUE(a.contains(0.0, 5.0));
    EXPECT_TRUE(a.contains(10.0, 5.0));
    EXPECT_TRUE(a.contains(5.0, 10.0));
}

// Test contains with negative coordinates
TEST(PDFRectangleTest_684, ContainsWithNegativeCoords_684)
{
    PDFRectangle a(-10.0, -10.0, 10.0, 10.0);
    EXPECT_TRUE(a.contains(0.0, 0.0));
    EXPECT_TRUE(a.contains(-5.0, -5.0));
    EXPECT_FALSE(a.contains(-15.0, 0.0));
}

// Test clipTo clips properly
TEST(PDFRectangleTest_684, ClipToReducesRectangle_684)
{
    PDFRectangle a(0.0, 0.0, 100.0, 100.0);
    PDFRectangle clip(10.0, 10.0, 50.0, 50.0);
    a.clipTo(clip);
    // After clipping, a should be within the clip bounds
    EXPECT_TRUE(a.contains(25.0, 25.0));
    EXPECT_FALSE(a.contains(0.0, 0.0));
    EXPECT_FALSE(a.contains(75.0, 75.0));
}

// Test clipTo when rectangles are identical
TEST(PDFRectangleTest_684, ClipToIdenticalRectangle_684)
{
    PDFRectangle a(10.0, 10.0, 50.0, 50.0);
    PDFRectangle clip(10.0, 10.0, 50.0, 50.0);
    a.clipTo(clip);
    EXPECT_TRUE(a == clip);
}

// Test clipTo when rectangle is already inside clip
TEST(PDFRectangleTest_684, ClipToWhenAlreadyInside_684)
{
    PDFRectangle a(20.0, 20.0, 30.0, 30.0);
    PDFRectangle clip(10.0, 10.0, 50.0, 50.0);
    PDFRectangle original(20.0, 20.0, 30.0, 30.0);
    a.clipTo(clip);
    EXPECT_TRUE(a == original);
}

// Test equality with mixed positive and negative zero
TEST(PDFRectangleTest_684, PositiveAndNegativeZeroEquality_684)
{
    PDFRectangle a(0.0, 0.0, 0.0, 0.0);
    PDFRectangle b(-0.0, -0.0, -0.0, -0.0);
    // In IEEE 754, 0.0 == -0.0
    EXPECT_TRUE(a == b);
}

// Test isEmpty for rectangle where x1 == x2 but y1 != y2
TEST(PDFRectangleTest_684, IsEmptyForLineRectangle_684)
{
    PDFRectangle a(5.0, 0.0, 5.0, 10.0);
    EXPECT_TRUE(a.isEmpty());
}

// Test isEmpty for rectangle where y1 == y2 but x1 != x2
TEST(PDFRectangleTest_684, IsEmptyForHorizontalLineRectangle_684)
{
    PDFRectangle a(0.0, 5.0, 10.0, 5.0);
    EXPECT_TRUE(a.isEmpty());
}

// Test contains on empty rectangle
TEST(PDFRectangleTest_684, ContainsOnEmptyRectangle_684)
{
    PDFRectangle a(0.0, 0.0, 0.0, 0.0);
    // A point at origin on an empty rectangle
    // Behavior is implementation-defined, just observe
    (void)a.contains(0.0, 0.0);
}
