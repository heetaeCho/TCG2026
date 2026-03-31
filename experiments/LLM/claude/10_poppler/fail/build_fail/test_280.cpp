#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Link.h"
#include "Array.h"
#include "Object.h"
#include "PDFDoc.h"

// Since LinkDest requires an Array for construction, we need to create proper
// Array objects to test the class. The behavior is treated as a black box.

class LinkDestTest_280 : public ::testing::Test {
protected:
    void SetUp() override {
        // We need an XRef for Array construction in some Poppler versions
        doc = nullptr;
    }

    void TearDown() override {
    }

    PDFDoc *doc;
};

// Test that LinkDest constructed with a /Fit destination is ok
TEST_F(LinkDestTest_280, FitDestinationIsOk_280) {
    // Create a /Fit destination: [pageNum /Fit]
    // Array: [page_number, /Fit]
    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(1)); // page number
    arrObj.arrayAdd(Object(objName, "Fit"));

    LinkDest dest(*arrObj.getArray());

    EXPECT_TRUE(dest.isOk());
    EXPECT_EQ(dest.getKind(), destFit);
    EXPECT_FALSE(dest.isPageRef());
    EXPECT_EQ(dest.getPageNum(), 1);
}

// Test that LinkDest constructed with /XYZ destination preserves coordinates
TEST_F(LinkDestTest_280, XYZDestinationWithCoordinates_280) {
    // Create a /XYZ destination: [pageNum /XYZ left top zoom]
    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(1)); // page number
    arrObj.arrayAdd(Object(objName, "XYZ"));
    arrObj.arrayAdd(Object(100.0)); // left
    arrObj.arrayAdd(Object(200.0)); // top
    arrObj.arrayAdd(Object(1.5));   // zoom

    LinkDest dest(*arrObj.getArray());

    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destXYZ);
        EXPECT_FALSE(dest.isPageRef());
        EXPECT_EQ(dest.getPageNum(), 1);
        EXPECT_DOUBLE_EQ(dest.getLeft(), 100.0);
        EXPECT_DOUBLE_EQ(dest.getTop(), 200.0);
        EXPECT_DOUBLE_EQ(dest.getZoom(), 1.5);
        EXPECT_TRUE(dest.getChangeLeft());
        EXPECT_TRUE(dest.getChangeTop());
        EXPECT_TRUE(dest.getChangeZoom());
    }
}

// Test that LinkDest constructed with /XYZ and null values
TEST_F(LinkDestTest_280, XYZDestinationWithNullValues_280) {
    // Create a /XYZ destination with null left, top, zoom
    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(1)); // page number
    arrObj.arrayAdd(Object(objName, "XYZ"));
    arrObj.arrayAdd(Object(objNull)); // left is null
    arrObj.arrayAdd(Object(objNull)); // top is null
    arrObj.arrayAdd(Object(objNull)); // zoom is null

    LinkDest dest(*arrObj.getArray());

    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destXYZ);
        EXPECT_FALSE(dest.getChangeLeft());
        EXPECT_FALSE(dest.getChangeTop());
        EXPECT_FALSE(dest.getChangeZoom());
    }
}

// Test getChangeTop returns true when top is specified
TEST_F(LinkDestTest_280, GetChangeTopTrueWhenTopSpecified_280) {
    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(1));
    arrObj.arrayAdd(Object(objName, "XYZ"));
    arrObj.arrayAdd(Object(50.0));  // left
    arrObj.arrayAdd(Object(300.0)); // top
    arrObj.arrayAdd(Object(0.0));   // zoom (0 means no change)

    LinkDest dest(*arrObj.getArray());

    if (dest.isOk()) {
        EXPECT_TRUE(dest.getChangeTop());
    }
}

// Test getChangeTop returns false when top is null
TEST_F(LinkDestTest_280, GetChangeTopFalseWhenTopNull_280) {
    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(1));
    arrObj.arrayAdd(Object(objName, "XYZ"));
    arrObj.arrayAdd(Object(50.0));    // left
    arrObj.arrayAdd(Object(objNull)); // top is null
    arrObj.arrayAdd(Object(1.0));     // zoom

    LinkDest dest(*arrObj.getArray());

    if (dest.isOk()) {
        EXPECT_FALSE(dest.getChangeTop());
    }
}

// Test /FitH destination
TEST_F(LinkDestTest_280, FitHDestination_280) {
    // [page /FitH top]
    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(2));
    arrObj.arrayAdd(Object(objName, "FitH"));
    arrObj.arrayAdd(Object(500.0)); // top

    LinkDest dest(*arrObj.getArray());

    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitH);
        EXPECT_EQ(dest.getPageNum(), 2);
        EXPECT_DOUBLE_EQ(dest.getTop(), 500.0);
        EXPECT_TRUE(dest.getChangeTop());
    }
}

// Test /FitV destination
TEST_F(LinkDestTest_280, FitVDestination_280) {
    // [page /FitV left]
    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(3));
    arrObj.arrayAdd(Object(objName, "FitV"));
    arrObj.arrayAdd(Object(100.0)); // left

    LinkDest dest(*arrObj.getArray());

    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitV);
        EXPECT_EQ(dest.getPageNum(), 3);
        EXPECT_DOUBLE_EQ(dest.getLeft(), 100.0);
        EXPECT_TRUE(dest.getChangeLeft());
    }
}

// Test /FitR destination
TEST_F(LinkDestTest_280, FitRDestination_280) {
    // [page /FitR left bottom right top]
    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(1));
    arrObj.arrayAdd(Object(objName, "FitR"));
    arrObj.arrayAdd(Object(10.0));  // left
    arrObj.arrayAdd(Object(20.0));  // bottom
    arrObj.arrayAdd(Object(300.0)); // right
    arrObj.arrayAdd(Object(400.0)); // top

    LinkDest dest(*arrObj.getArray());

    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitR);
        EXPECT_DOUBLE_EQ(dest.getLeft(), 10.0);
        EXPECT_DOUBLE_EQ(dest.getBottom(), 20.0);
        EXPECT_DOUBLE_EQ(dest.getRight(), 300.0);
        EXPECT_DOUBLE_EQ(dest.getTop(), 400.0);
    }
}

// Test /FitB destination
TEST_F(LinkDestTest_280, FitBDestination_280) {
    // [page /FitB]
    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(1));
    arrObj.arrayAdd(Object(objName, "FitB"));

    LinkDest dest(*arrObj.getArray());

    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitB);
    }
}

// Test /FitBH destination
TEST_F(LinkDestTest_280, FitBHDestination_280) {
    // [page /FitBH top]
    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(1));
    arrObj.arrayAdd(Object(objName, "FitBH"));
    arrObj.arrayAdd(Object(250.0));

    LinkDest dest(*arrObj.getArray());

    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitBH);
        EXPECT_DOUBLE_EQ(dest.getTop(), 250.0);
    }
}

// Test /FitBV destination
TEST_F(LinkDestTest_280, FitBVDestination_280) {
    // [page /FitBV left]
    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(1));
    arrObj.arrayAdd(Object(objName, "FitBV"));
    arrObj.arrayAdd(Object(75.0));

    LinkDest dest(*arrObj.getArray());

    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitBV);
        EXPECT_DOUBLE_EQ(dest.getLeft(), 75.0);
    }
}

// Test empty array results in invalid destination
TEST_F(LinkDestTest_280, EmptyArrayIsNotOk_280) {
    Object arrObj = Object(new Array(nullptr));

    LinkDest dest(*arrObj.getArray());

    EXPECT_FALSE(dest.isOk());
}

// Test array with only one element (missing destination type)
TEST_F(LinkDestTest_280, SingleElementArrayIsNotOk_280) {
    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(1));

    LinkDest dest(*arrObj.getArray());

    EXPECT_FALSE(dest.isOk());
}

// Test invalid destination name
TEST_F(LinkDestTest_280, InvalidDestinationNameIsNotOk_280) {
    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(1));
    arrObj.arrayAdd(Object(objName, "InvalidName"));

    LinkDest dest(*arrObj.getArray());

    EXPECT_FALSE(dest.isOk());
}

// Test getChangeLeft and getChangeZoom with XYZ
TEST_F(LinkDestTest_280, XYZChangeLeftAndChangeZoom_280) {
    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(1));
    arrObj.arrayAdd(Object(objName, "XYZ"));
    arrObj.arrayAdd(Object(42.0));    // left specified
    arrObj.arrayAdd(Object(objNull)); // top null
    arrObj.arrayAdd(Object(2.0));     // zoom specified

    LinkDest dest(*arrObj.getArray());

    if (dest.isOk()) {
        EXPECT_TRUE(dest.getChangeLeft());
        EXPECT_FALSE(dest.getChangeTop());
        EXPECT_TRUE(dest.getChangeZoom());
        EXPECT_DOUBLE_EQ(dest.getLeft(), 42.0);
        EXPECT_DOUBLE_EQ(dest.getZoom(), 2.0);
    }
}

// Test that page number is correctly returned for different pages
TEST_F(LinkDestTest_280, DifferentPageNumbers_280) {
    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(99));
    arrObj.arrayAdd(Object(objName, "Fit"));

    LinkDest dest(*arrObj.getArray());

    if (dest.isOk()) {
        EXPECT_EQ(dest.getPageNum(), 99);
    }
}

// Test boundary: zero coordinates in XYZ
TEST_F(LinkDestTest_280, XYZWithZeroCoordinates_280) {
    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(1));
    arrObj.arrayAdd(Object(objName, "XYZ"));
    arrObj.arrayAdd(Object(0.0)); // left = 0
    arrObj.arrayAdd(Object(0.0)); // top = 0
    arrObj.arrayAdd(Object(0.0)); // zoom = 0

    LinkDest dest(*arrObj.getArray());

    if (dest.isOk()) {
        EXPECT_DOUBLE_EQ(dest.getLeft(), 0.0);
        EXPECT_DOUBLE_EQ(dest.getTop(), 0.0);
        EXPECT_DOUBLE_EQ(dest.getZoom(), 0.0);
    }
}

// Test boundary: negative coordinates
TEST_F(LinkDestTest_280, XYZWithNegativeCoordinates_280) {
    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(1));
    arrObj.arrayAdd(Object(objName, "XYZ"));
    arrObj.arrayAdd(Object(-50.0));
    arrObj.arrayAdd(Object(-100.0));
    arrObj.arrayAdd(Object(1.0));

    LinkDest dest(*arrObj.getArray());

    if (dest.isOk()) {
        EXPECT_DOUBLE_EQ(dest.getLeft(), -50.0);
        EXPECT_DOUBLE_EQ(dest.getTop(), -100.0);
    }
}

// Test FitH with null top
TEST_F(LinkDestTest_280, FitHWithNullTop_280) {
    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(1));
    arrObj.arrayAdd(Object(objName, "FitH"));
    arrObj.arrayAdd(Object(objNull)); // top is null

    LinkDest dest(*arrObj.getArray());

    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitH);
        EXPECT_FALSE(dest.getChangeTop());
    }
}
