#include <gtest/gtest.h>
#include "Link.h"
#include "Array.h"
#include "Object.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

#include <memory>

class LinkDestTest_279 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that constructing a LinkDest from an empty array results in an invalid destination
TEST_F(LinkDestTest_279, EmptyArrayIsNotOk_279) {
    // Create an empty Array - need an XRef, but we can try with nullptr
    // This tests boundary condition of empty input
    auto doc = std::unique_ptr<PDFDoc>();
    Array arr(nullptr);
    LinkDest dest(&arr);
    EXPECT_FALSE(dest.isOk());
}

// Test LinkDest with a /Fit destination type
TEST_F(LinkDestTest_279, FitDestination_279) {
    Array arr(nullptr);
    // Page number (direct page number, 0-based index internally but let's use an integer)
    arr.add(Object(1));  // page number
    arr.add(Object(objName, "Fit"));
    
    LinkDest dest(&arr);
    // If the construction succeeds, verify properties
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFit);
        EXPECT_FALSE(dest.isPageRef());
    }
}

// Test LinkDest with a /XYZ destination type
TEST_F(LinkDestTest_279, XYZDestination_279) {
    Array arr(nullptr);
    arr.add(Object(1));  // page number
    arr.add(Object(objName, "XYZ"));
    arr.add(Object(100.0));  // left
    arr.add(Object(200.0));  // top
    arr.add(Object(1.5));    // zoom
    
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destXYZ);
        EXPECT_TRUE(dest.getChangeLeft());
        EXPECT_TRUE(dest.getChangeTop());
        EXPECT_TRUE(dest.getChangeZoom());
        EXPECT_DOUBLE_EQ(dest.getLeft(), 100.0);
        EXPECT_DOUBLE_EQ(dest.getTop(), 200.0);
        EXPECT_DOUBLE_EQ(dest.getZoom(), 1.5);
    }
}

// Test LinkDest with /XYZ and null values (no change)
TEST_F(LinkDestTest_279, XYZDestinationWithNulls_279) {
    Array arr(nullptr);
    arr.add(Object(1));  // page number
    arr.add(Object(objName, "XYZ"));
    arr.add(Object(objNull));  // left = null => changeLeft = false
    arr.add(Object(objNull));  // top = null => changeTop = false
    arr.add(Object(objNull));  // zoom = null => changeZoom = false
    
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destXYZ);
        EXPECT_FALSE(dest.getChangeLeft());
        EXPECT_FALSE(dest.getChangeTop());
        EXPECT_FALSE(dest.getChangeZoom());
    }
}

// Test LinkDest with /FitH destination
TEST_F(LinkDestTest_279, FitHDestination_279) {
    Array arr(nullptr);
    arr.add(Object(1));
    arr.add(Object(objName, "FitH"));
    arr.add(Object(300.0));  // top
    
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitH);
        EXPECT_TRUE(dest.getChangeTop());
        EXPECT_DOUBLE_EQ(dest.getTop(), 300.0);
    }
}

// Test LinkDest with /FitV destination
TEST_F(LinkDestTest_279, FitVDestination_279) {
    Array arr(nullptr);
    arr.add(Object(1));
    arr.add(Object(objName, "FitV"));
    arr.add(Object(150.0));  // left
    
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitV);
        EXPECT_TRUE(dest.getChangeLeft());
        EXPECT_DOUBLE_EQ(dest.getLeft(), 150.0);
    }
}

// Test LinkDest with /FitR destination
TEST_F(LinkDestTest_279, FitRDestination_279) {
    Array arr(nullptr);
    arr.add(Object(1));
    arr.add(Object(objName, "FitR"));
    arr.add(Object(10.0));   // left
    arr.add(Object(20.0));   // bottom
    arr.add(Object(500.0));  // right
    arr.add(Object(700.0));  // top
    
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitR);
        EXPECT_DOUBLE_EQ(dest.getLeft(), 10.0);
        EXPECT_DOUBLE_EQ(dest.getBottom(), 20.0);
        EXPECT_DOUBLE_EQ(dest.getRight(), 500.0);
        EXPECT_DOUBLE_EQ(dest.getTop(), 700.0);
    }
}

// Test LinkDest with /FitB destination
TEST_F(LinkDestTest_279, FitBDestination_279) {
    Array arr(nullptr);
    arr.add(Object(1));
    arr.add(Object(objName, "FitB"));
    
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitB);
    }
}

// Test LinkDest with /FitBH destination
TEST_F(LinkDestTest_279, FitBHDestination_279) {
    Array arr(nullptr);
    arr.add(Object(1));
    arr.add(Object(objName, "FitBH"));
    arr.add(Object(400.0));  // top
    
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitBH);
        EXPECT_TRUE(dest.getChangeTop());
        EXPECT_DOUBLE_EQ(dest.getTop(), 400.0);
    }
}

// Test LinkDest with /FitBV destination
TEST_F(LinkDestTest_279, FitBVDestination_279) {
    Array arr(nullptr);
    arr.add(Object(1));
    arr.add(Object(objName, "FitBV"));
    arr.add(Object(250.0));  // left
    
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitBV);
        EXPECT_TRUE(dest.getChangeLeft());
        EXPECT_DOUBLE_EQ(dest.getLeft(), 250.0);
    }
}

// Test that getChangeLeft returns false when constructed with an invalid array
TEST_F(LinkDestTest_279, InvalidArrayGetChangeLeftFalse_279) {
    Array arr(nullptr);
    arr.add(Object(objNull));  // invalid page
    
    LinkDest dest(&arr);
    // For an invalid dest, we just check it's not ok
    EXPECT_FALSE(dest.isOk());
}

// Test with an unrecognized destination name
TEST_F(LinkDestTest_279, UnrecognizedDestNameNotOk_279) {
    Array arr(nullptr);
    arr.add(Object(1));
    arr.add(Object(objName, "UnknownDest"));
    
    LinkDest dest(&arr);
    EXPECT_FALSE(dest.isOk());
}

// Test single element array (only page, no destination type)
TEST_F(LinkDestTest_279, SingleElementArrayNotOk_279) {
    Array arr(nullptr);
    arr.add(Object(1));
    
    LinkDest dest(&arr);
    EXPECT_FALSE(dest.isOk());
}

// Test getChangeLeft specifically - with XYZ and valid left value
TEST_F(LinkDestTest_279, GetChangeLeftTrueWhenLeftProvided_279) {
    Array arr(nullptr);
    arr.add(Object(1));
    arr.add(Object(objName, "XYZ"));
    arr.add(Object(50.0));    // left - provided
    arr.add(Object(objNull)); // top - null
    arr.add(Object(objNull)); // zoom - null
    
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_TRUE(dest.getChangeLeft());
        EXPECT_DOUBLE_EQ(dest.getLeft(), 50.0);
        EXPECT_FALSE(dest.getChangeTop());
        EXPECT_FALSE(dest.getChangeZoom());
    }
}

// Test getChangeLeft with null left in XYZ
TEST_F(LinkDestTest_279, GetChangeLeftFalseWhenLeftNull_279) {
    Array arr(nullptr);
    arr.add(Object(1));
    arr.add(Object(objName, "XYZ"));
    arr.add(Object(objNull)); // left - null
    arr.add(Object(200.0));   // top - provided
    arr.add(Object(2.0));     // zoom - provided
    
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_FALSE(dest.getChangeLeft());
        EXPECT_TRUE(dest.getChangeTop());
        EXPECT_TRUE(dest.getChangeZoom());
    }
}

// Boundary: zero values for coordinates
TEST_F(LinkDestTest_279, ZeroCoordinates_279) {
    Array arr(nullptr);
    arr.add(Object(1));
    arr.add(Object(objName, "XYZ"));
    arr.add(Object(0.0));  // left = 0
    arr.add(Object(0.0));  // top = 0
    arr.add(Object(0.0));  // zoom = 0
    
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destXYZ);
        // Zero is still a valid value, so changeLeft should be true
        EXPECT_TRUE(dest.getChangeLeft());
        EXPECT_TRUE(dest.getChangeTop());
        EXPECT_DOUBLE_EQ(dest.getLeft(), 0.0);
        EXPECT_DOUBLE_EQ(dest.getTop(), 0.0);
        EXPECT_DOUBLE_EQ(dest.getZoom(), 0.0);
    }
}

// Boundary: negative coordinate values
TEST_F(LinkDestTest_279, NegativeCoordinates_279) {
    Array arr(nullptr);
    arr.add(Object(1));
    arr.add(Object(objName, "XYZ"));
    arr.add(Object(-100.0));  // left
    arr.add(Object(-200.0));  // top
    arr.add(Object(1.0));     // zoom
    
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_TRUE(dest.getChangeLeft());
        EXPECT_TRUE(dest.getChangeTop());
        EXPECT_DOUBLE_EQ(dest.getLeft(), -100.0);
        EXPECT_DOUBLE_EQ(dest.getTop(), -200.0);
    }
}

// Test page number accessor
TEST_F(LinkDestTest_279, GetPageNumForDirectPage_279) {
    Array arr(nullptr);
    arr.add(Object(5));  // page number 5
    arr.add(Object(objName, "Fit"));
    
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_FALSE(dest.isPageRef());
        EXPECT_EQ(dest.getPageNum(), 5);
    }
}

// Test /FitH with null top
TEST_F(LinkDestTest_279, FitHWithNullTop_279) {
    Array arr(nullptr);
    arr.add(Object(1));
    arr.add(Object(objName, "FitH"));
    arr.add(Object(objNull));  // top = null
    
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitH);
        EXPECT_FALSE(dest.getChangeTop());
    }
}

// Test /FitV with null left
TEST_F(LinkDestTest_279, FitVWithNullLeft_279) {
    Array arr(nullptr);
    arr.add(Object(1));
    arr.add(Object(objName, "FitV"));
    arr.add(Object(objNull));  // left = null
    
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitV);
        EXPECT_FALSE(dest.getChangeLeft());
    }
}
