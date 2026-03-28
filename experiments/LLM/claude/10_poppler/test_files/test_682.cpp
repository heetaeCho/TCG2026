#include <gtest/gtest.h>
#include "PDFRectangle.h"

// Test isEmpty for default-constructed rectangle (all zeros)
TEST(PDFRectangleTest_682, DefaultConstructedIsEmpty_682) {
    PDFRectangle rect;
    EXPECT_TRUE(rect.isEmpty());
}

// Test isEmpty when x1==x2 and y1==y2 but non-zero
TEST(PDFRectangleTest_682, SamePointNonZeroIsEmpty_682) {
    PDFRectangle rect(5.0, 10.0, 5.0, 10.0);
    EXPECT_TRUE(rect.isEmpty());
}

// Test isEmpty for a normal rectangle with area
TEST(PDFRectangleTest_682, NormalRectangleIsNotEmpty_682) {
    PDFRectangle rect(0.0, 0.0, 100.0, 200.0);
    EXPECT_FALSE(rect.isEmpty());
}

// Test isEmpty when only x differs
TEST(PDFRectangleTest_682, DifferentXNotEmpty_682) {
    PDFRectangle rect(0.0, 5.0, 10.0, 5.0);
    EXPECT_FALSE(rect.isEmpty());
}

// Test isEmpty when only y differs
TEST(PDFRectangleTest_682, DifferentYNotEmpty_682) {
    PDFRectangle rect(5.0, 0.0, 5.0, 10.0);
    EXPECT_FALSE(rect.isEmpty());
}

// Test isEmpty with negative coordinates forming a point
TEST(PDFRectangleTest_682, NegativePointIsEmpty_682) {
    PDFRectangle rect(-3.0, -7.0, -3.0, -7.0);
    EXPECT_TRUE(rect.isEmpty());
}

// Test isEmpty with negative coordinates forming a rectangle
TEST(PDFRectangleTest_682, NegativeRectangleIsNotEmpty_682) {
    PDFRectangle rect(-10.0, -20.0, -5.0, -10.0);
    EXPECT_FALSE(rect.isEmpty());
}

// Test isValid
TEST(PDFRectangleTest_682, DefaultConstructedIsValid_682) {
    PDFRectangle rect;
    EXPECT_TRUE(rect.isValid());
}

TEST(PDFRectangleTest_682, NormalRectangleIsValid_682) {
    PDFRectangle rect(0.0, 0.0, 100.0, 200.0);
    EXPECT_TRUE(rect.isValid());
}

// Test contains for a point inside the rectangle
TEST(PDFRectangleTest_682, ContainsPointInside_682) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    EXPECT_TRUE(rect.contains(5.0, 5.0));
}

// Test contains for a point outside the rectangle
TEST(PDFRectangleTest_682, DoesNotContainPointOutside_682) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    EXPECT_FALSE(rect.contains(15.0, 15.0));
}

// Test contains for a point on the boundary
TEST(PDFRectangleTest_682, ContainsPointOnBoundary_682) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    EXPECT_TRUE(rect.contains(0.0, 0.0));
    EXPECT_TRUE(rect.contains(10.0, 10.0));
    EXPECT_TRUE(rect.contains(0.0, 10.0));
    EXPECT_TRUE(rect.contains(10.0, 0.0));
}

// Test contains for point just outside
TEST(PDFRectangleTest_682, DoesNotContainPointJustOutside_682) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    EXPECT_FALSE(rect.contains(-0.001, 5.0));
    EXPECT_FALSE(rect.contains(5.0, 10.001));
}

// Test equality operator with identical rectangles
TEST(PDFRectangleTest_682, EqualityIdenticalRectangles_682) {
    PDFRectangle rect1(1.0, 2.0, 3.0, 4.0);
    PDFRectangle rect2(1.0, 2.0, 3.0, 4.0);
    EXPECT_TRUE(rect1 == rect2);
}

// Test equality operator with different rectangles
TEST(PDFRectangleTest_682, EqualityDifferentRectangles_682) {
    PDFRectangle rect1(1.0, 2.0, 3.0, 4.0);
    PDFRectangle rect2(1.0, 2.0, 3.0, 5.0);
    EXPECT_FALSE(rect1 == rect2);
}

// Test equality with default constructed
TEST(PDFRectangleTest_682, EqualityDefaultConstructed_682) {
    PDFRectangle rect1;
    PDFRectangle rect2;
    EXPECT_TRUE(rect1 == rect2);
}

// Test clipTo - clipping a rectangle to a smaller one
TEST(PDFRectangleTest_682, ClipToSmallerRectangle_682) {
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    PDFRectangle clipRect(10.0, 10.0, 50.0, 50.0);
    rect.clipTo(clipRect);
    PDFRectangle expected(10.0, 10.0, 50.0, 50.0);
    EXPECT_TRUE(rect == expected);
}

// Test clipTo - clipping when partially overlapping
TEST(PDFRectangleTest_682, ClipToPartiallyOverlapping_682) {
    PDFRectangle rect(0.0, 0.0, 50.0, 50.0);
    PDFRectangle clipRect(25.0, 25.0, 100.0, 100.0);
    rect.clipTo(clipRect);
    PDFRectangle expected(25.0, 25.0, 50.0, 50.0);
    EXPECT_TRUE(rect == expected);
}

// Test clipTo with identical rectangles
TEST(PDFRectangleTest_682, ClipToIdenticalRectangle_682) {
    PDFRectangle rect(10.0, 10.0, 50.0, 50.0);
    PDFRectangle clipRect(10.0, 10.0, 50.0, 50.0);
    rect.clipTo(clipRect);
    PDFRectangle expected(10.0, 10.0, 50.0, 50.0);
    EXPECT_TRUE(rect == expected);
}

// Test isEmpty with very small difference
TEST(PDFRectangleTest_682, VerySmallDifferenceNotEmpty_682) {
    PDFRectangle rect(0.0, 0.0, 1e-15, 1e-15);
    EXPECT_FALSE(rect.isEmpty());
}

// Test contains with inverted rectangle (x1 > x2)
TEST(PDFRectangleTest_682, ContainsWithInvertedCoordinates_682) {
    PDFRectangle rect(10.0, 10.0, 0.0, 0.0);
    // Point inside the "inverted" rectangle range
    // Behavior depends on implementation, but we test observable behavior
    bool result = rect.contains(5.0, 5.0);
    // Just verify it doesn't crash; the result depends on implementation
    (void)result;
}

// Test constructor sets coordinates correctly via equality
TEST(PDFRectangleTest_682, ConstructorSetsCoordinates_682) {
    PDFRectangle rect(1.5, 2.5, 3.5, 4.5);
    PDFRectangle expected(1.5, 2.5, 3.5, 4.5);
    EXPECT_TRUE(rect == expected);
}

// Test that default constructor produces empty rectangle
TEST(PDFRectangleTest_682, DefaultIsEmptyAndEqualToZeroRect_682) {
    PDFRectangle rect;
    PDFRectangle zeroRect(0.0, 0.0, 0.0, 0.0);
    EXPECT_TRUE(rect == zeroRect);
    EXPECT_TRUE(rect.isEmpty());
}
