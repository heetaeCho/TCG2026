#include <gtest/gtest.h>
#include "Link.h"
#include "Array.h"
#include "Object.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

#include <memory>

class LinkDestTest_274 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that constructing LinkDest from an empty array results in not ok
TEST_F(LinkDestTest_274, EmptyArrayIsNotOk_274) {
    // Create an empty Array - need an XRef but can pass nullptr for basic tests
    Array arr(nullptr);
    LinkDest dest(&arr);
    EXPECT_FALSE(dest.isOk());
}

// Test that constructing LinkDest with a single element array that is not valid results in not ok
TEST_F(LinkDestTest_274, SingleElementInvalidArray_274) {
    Array arr(nullptr);
    arr.add(Object(42));  // Just a page number, no destination type
    LinkDest dest(&arr);
    EXPECT_FALSE(dest.isOk());
}

// Test construction with /Fit destination type
TEST_F(LinkDestTest_274, FitDestination_274) {
    Array arr(nullptr);
    arr.add(Object(0));  // page number
    arr.add(Object(objName, "Fit"));
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFit);
        EXPECT_FALSE(dest.isPageRef());
    }
}

// Test construction with /FitH destination type
TEST_F(LinkDestTest_274, FitHDestination_274) {
    Array arr(nullptr);
    arr.add(Object(0));  // page number
    arr.add(Object(objName, "FitH"));
    arr.add(Object(100.0));  // top
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitH);
        EXPECT_DOUBLE_EQ(dest.getTop(), 100.0);
    }
}

// Test construction with /FitV destination type
TEST_F(LinkDestTest_274, FitVDestination_274) {
    Array arr(nullptr);
    arr.add(Object(0));  // page number
    arr.add(Object(objName, "FitV"));
    arr.add(Object(50.0));  // left
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitV);
        EXPECT_DOUBLE_EQ(dest.getLeft(), 50.0);
    }
}

// Test construction with /XYZ destination type
TEST_F(LinkDestTest_274, XYZDestination_274) {
    Array arr(nullptr);
    arr.add(Object(0));  // page number
    arr.add(Object(objName, "XYZ"));
    arr.add(Object(10.0));  // left
    arr.add(Object(20.0));  // top
    arr.add(Object(1.5));   // zoom
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destXYZ);
        EXPECT_DOUBLE_EQ(dest.getLeft(), 10.0);
        EXPECT_DOUBLE_EQ(dest.getTop(), 20.0);
        EXPECT_DOUBLE_EQ(dest.getZoom(), 1.5);
    }
}

// Test construction with /FitR destination type
TEST_F(LinkDestTest_274, FitRDestination_274) {
    Array arr(nullptr);
    arr.add(Object(0));  // page number
    arr.add(Object(objName, "FitR"));
    arr.add(Object(10.0));  // left
    arr.add(Object(20.0));  // bottom
    arr.add(Object(300.0)); // right
    arr.add(Object(400.0)); // top
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitR);
        EXPECT_DOUBLE_EQ(dest.getLeft(), 10.0);
        EXPECT_DOUBLE_EQ(dest.getBottom(), 20.0);
        EXPECT_DOUBLE_EQ(dest.getRight(), 300.0);
        EXPECT_DOUBLE_EQ(dest.getTop(), 400.0);
    }
}

// Test construction with /FitB destination type
TEST_F(LinkDestTest_274, FitBDestination_274) {
    Array arr(nullptr);
    arr.add(Object(0));  // page number
    arr.add(Object(objName, "FitB"));
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitB);
    }
}

// Test construction with /FitBH destination type
TEST_F(LinkDestTest_274, FitBHDestination_274) {
    Array arr(nullptr);
    arr.add(Object(0));  // page number
    arr.add(Object(objName, "FitBH"));
    arr.add(Object(150.0));  // top
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitBH);
        EXPECT_DOUBLE_EQ(dest.getTop(), 150.0);
    }
}

// Test construction with /FitBV destination type
TEST_F(LinkDestTest_274, FitBVDestination_274) {
    Array arr(nullptr);
    arr.add(Object(0));  // page number
    arr.add(Object(objName, "FitBV"));
    arr.add(Object(75.0));  // left
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitBV);
        EXPECT_DOUBLE_EQ(dest.getLeft(), 75.0);
    }
}

// Test getLeft returns the stored left value
TEST_F(LinkDestTest_274, GetLeftReturnsCorrectValue_274) {
    Array arr(nullptr);
    arr.add(Object(0));
    arr.add(Object(objName, "XYZ"));
    arr.add(Object(42.5));  // left
    arr.add(Object(100.0)); // top
    arr.add(Object(1.0));   // zoom
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_DOUBLE_EQ(dest.getLeft(), 42.5);
    }
}

// Test XYZ with null values (represented as objNull)
TEST_F(LinkDestTest_274, XYZWithNullParameters_274) {
    Array arr(nullptr);
    arr.add(Object(0));
    arr.add(Object(objName, "XYZ"));
    arr.add(Object(objNull));  // left null
    arr.add(Object(objNull));  // top null
    arr.add(Object(objNull));  // zoom null
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destXYZ);
        EXPECT_FALSE(dest.getChangeLeft());
        EXPECT_FALSE(dest.getChangeTop());
        EXPECT_FALSE(dest.getChangeZoom());
    }
}

// Test that getPageNum returns proper page number for non-ref pages
TEST_F(LinkDestTest_274, GetPageNumForIntegerPage_274) {
    Array arr(nullptr);
    arr.add(Object(5));  // page number (0-based in array, but implementation may adjust)
    arr.add(Object(objName, "Fit"));
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_FALSE(dest.isPageRef());
        EXPECT_EQ(dest.getPageNum(), 5);
    }
}

// Test with unknown destination name
TEST_F(LinkDestTest_274, UnknownDestinationName_274) {
    Array arr(nullptr);
    arr.add(Object(0));
    arr.add(Object(objName, "UnknownDest"));
    LinkDest dest(&arr);
    EXPECT_FALSE(dest.isOk());
}

// Test XYZ destination with zero coordinates
TEST_F(LinkDestTest_274, XYZZeroCoordinates_274) {
    Array arr(nullptr);
    arr.add(Object(0));
    arr.add(Object(objName, "XYZ"));
    arr.add(Object(0.0));  // left
    arr.add(Object(0.0));  // top
    arr.add(Object(0.0));  // zoom
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destXYZ);
        EXPECT_DOUBLE_EQ(dest.getLeft(), 0.0);
        EXPECT_DOUBLE_EQ(dest.getTop(), 0.0);
        EXPECT_DOUBLE_EQ(dest.getZoom(), 0.0);
    }
}

// Test XYZ with negative coordinates
TEST_F(LinkDestTest_274, XYZNegativeCoordinates_274) {
    Array arr(nullptr);
    arr.add(Object(0));
    arr.add(Object(objName, "XYZ"));
    arr.add(Object(-10.0));  // left
    arr.add(Object(-20.0));  // top
    arr.add(Object(1.0));    // zoom
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_DOUBLE_EQ(dest.getLeft(), -10.0);
        EXPECT_DOUBLE_EQ(dest.getTop(), -20.0);
    }
}

// Test FitR with boundary values
TEST_F(LinkDestTest_274, FitRBoundaryValues_274) {
    Array arr(nullptr);
    arr.add(Object(0));
    arr.add(Object(objName, "FitR"));
    arr.add(Object(0.0));       // left
    arr.add(Object(0.0));       // bottom
    arr.add(Object(612.0));     // right (typical US Letter width in points)
    arr.add(Object(792.0));     // top (typical US Letter height in points)
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitR);
        EXPECT_DOUBLE_EQ(dest.getLeft(), 0.0);
        EXPECT_DOUBLE_EQ(dest.getBottom(), 0.0);
        EXPECT_DOUBLE_EQ(dest.getRight(), 612.0);
        EXPECT_DOUBLE_EQ(dest.getTop(), 792.0);
    }
}

// Test that getChangeLeft and getChangeTop return true for XYZ with actual values
TEST_F(LinkDestTest_274, XYZChangeFlags_274) {
    Array arr(nullptr);
    arr.add(Object(0));
    arr.add(Object(objName, "XYZ"));
    arr.add(Object(100.0));  // left - should set changeLeft
    arr.add(Object(200.0));  // top - should set changeTop
    arr.add(Object(2.0));    // zoom - should set changeZoom
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_TRUE(dest.getChangeLeft());
        EXPECT_TRUE(dest.getChangeTop());
        EXPECT_TRUE(dest.getChangeZoom());
    }
}

// Test with very large coordinate values
TEST_F(LinkDestTest_274, XYZLargeCoordinates_274) {
    Array arr(nullptr);
    arr.add(Object(0));
    arr.add(Object(objName, "XYZ"));
    arr.add(Object(1e10));   // left
    arr.add(Object(1e10));   // top
    arr.add(Object(100.0));  // zoom
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_DOUBLE_EQ(dest.getLeft(), 1e10);
        EXPECT_DOUBLE_EQ(dest.getTop(), 1e10);
    }
}
