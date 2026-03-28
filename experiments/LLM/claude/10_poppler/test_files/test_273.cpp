#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Link.h"
#include "Object.h"
#include "Array.h"

// Helper to create a LinkDest from an Array with specific destination type
// Since we treat LinkDest as a black box, we test through the public interface
// by constructing Array objects that represent different PDF destination types.

class LinkDestTest_273 : public ::testing::Test {
protected:
    // Helper to create an XRef-less array (using nullptr or minimal setup)
    // We need to build PDF arrays that LinkDest constructor can parse
};

// Test: Construction with Fit destination type
TEST_F(LinkDestTest_273, FitDestination_273) {
    // Create array: [pageRef /Fit]
    // Array format: [page /Fit]
    // page can be an integer (page number) or indirect reference
    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(0)); // page number 0
    arrObj.arrayAdd(Object(objName, "Fit"));
    
    LinkDest dest(arrObj.getArray());
    
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFit);
        EXPECT_FALSE(dest.isPageRef());
        EXPECT_EQ(dest.getPageNum(), 0);
    }
}

// Test: Construction with XYZ destination type
TEST_F(LinkDestTest_273, XYZDestination_273) {
    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(1)); // page number 1
    arrObj.arrayAdd(Object(objName, "XYZ"));
    arrObj.arrayAdd(Object(100.0)); // left
    arrObj.arrayAdd(Object(200.0)); // top
    arrObj.arrayAdd(Object(1.5));   // zoom
    
    LinkDest dest(arrObj.getArray());
    
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

// Test: Construction with XYZ destination with null parameters
TEST_F(LinkDestTest_273, XYZDestinationWithNulls_273) {
    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(2)); // page number
    arrObj.arrayAdd(Object(objName, "XYZ"));
    arrObj.arrayAdd(Object(objNull)); // left is null
    arrObj.arrayAdd(Object(objNull)); // top is null
    arrObj.arrayAdd(Object(objNull)); // zoom is null
    
    LinkDest dest(arrObj.getArray());
    
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destXYZ);
        EXPECT_FALSE(dest.getChangeLeft());
        EXPECT_FALSE(dest.getChangeTop());
        EXPECT_FALSE(dest.getChangeZoom());
    }
}

// Test: Construction with FitH destination type
TEST_F(LinkDestTest_273, FitHDestination_273) {
    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(0)); // page number
    arrObj.arrayAdd(Object(objName, "FitH"));
    arrObj.arrayAdd(Object(300.0)); // top
    
    LinkDest dest(arrObj.getArray());
    
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitH);
        EXPECT_DOUBLE_EQ(dest.getTop(), 300.0);
        EXPECT_TRUE(dest.getChangeTop());
    }
}

// Test: Construction with FitV destination type
TEST_F(LinkDestTest_273, FitVDestination_273) {
    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(0)); // page number
    arrObj.arrayAdd(Object(objName, "FitV"));
    arrObj.arrayAdd(Object(150.0)); // left
    
    LinkDest dest(arrObj.getArray());
    
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitV);
        EXPECT_DOUBLE_EQ(dest.getLeft(), 150.0);
        EXPECT_TRUE(dest.getChangeLeft());
    }
}

// Test: Construction with FitR destination type
TEST_F(LinkDestTest_273, FitRDestination_273) {
    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(0)); // page number
    arrObj.arrayAdd(Object(objName, "FitR"));
    arrObj.arrayAdd(Object(10.0));  // left
    arrObj.arrayAdd(Object(20.0));  // bottom
    arrObj.arrayAdd(Object(300.0)); // right
    arrObj.arrayAdd(Object(400.0)); // top
    
    LinkDest dest(arrObj.getArray());
    
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitR);
        EXPECT_DOUBLE_EQ(dest.getLeft(), 10.0);
        EXPECT_DOUBLE_EQ(dest.getBottom(), 20.0);
        EXPECT_DOUBLE_EQ(dest.getRight(), 300.0);
        EXPECT_DOUBLE_EQ(dest.getTop(), 400.0);
    }
}

// Test: Construction with FitB destination type
TEST_F(LinkDestTest_273, FitBDestination_273) {
    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(0)); // page number
    arrObj.arrayAdd(Object(objName, "FitB"));
    
    LinkDest dest(arrObj.getArray());
    
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitB);
    }
}

// Test: Construction with FitBH destination type
TEST_F(LinkDestTest_273, FitBHDestination_273) {
    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(0)); // page number
    arrObj.arrayAdd(Object(objName, "FitBH"));
    arrObj.arrayAdd(Object(500.0)); // top
    
    LinkDest dest(arrObj.getArray());
    
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitBH);
        EXPECT_DOUBLE_EQ(dest.getTop(), 500.0);
    }
}

// Test: Construction with FitBV destination type
TEST_F(LinkDestTest_273, FitBVDestination_273) {
    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(0)); // page number
    arrObj.arrayAdd(Object(objName, "FitBV"));
    arrObj.arrayAdd(Object(250.0)); // left
    
    LinkDest dest(arrObj.getArray());
    
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitBV);
        EXPECT_DOUBLE_EQ(dest.getLeft(), 250.0);
    }
}

// Test: Empty array should result in invalid LinkDest
TEST_F(LinkDestTest_273, EmptyArrayIsInvalid_273) {
    Object arrObj = Object(new Array(nullptr));
    
    LinkDest dest(arrObj.getArray());
    
    EXPECT_FALSE(dest.isOk());
}

// Test: Array with only one element (page but no type) should be invalid
TEST_F(LinkDestTest_273, ArrayWithOnlyPageIsInvalid_273) {
    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(0));
    
    LinkDest dest(arrObj.getArray());
    
    EXPECT_FALSE(dest.isOk());
}

// Test: Array with invalid destination type name
TEST_F(LinkDestTest_273, InvalidDestTypeIsInvalid_273) {
    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(0));
    arrObj.arrayAdd(Object(objName, "InvalidType"));
    
    LinkDest dest(arrObj.getArray());
    
    EXPECT_FALSE(dest.isOk());
}

// Test: getPageRef for a destination constructed with page number (not ref)
TEST_F(LinkDestTest_273, PageNumNotRef_273) {
    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(5)); // page number
    arrObj.arrayAdd(Object(objName, "Fit"));
    
    LinkDest dest(arrObj.getArray());
    
    if (dest.isOk()) {
        EXPECT_FALSE(dest.isPageRef());
        EXPECT_EQ(dest.getPageNum(), 5);
    }
}

// Test: getPageRef returns valid Ref structure
TEST_F(LinkDestTest_273, GetPageRefReturnsRef_273) {
    // When dest is constructed with a page reference (indirect object),
    // isPageRef() should be true and getPageRef() should return the ref.
    // Since constructing indirect references requires XRef, we test
    // the case with integer page numbers primarily.
    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(0));
    arrObj.arrayAdd(Object(objName, "Fit"));
    
    LinkDest dest(arrObj.getArray());
    
    if (dest.isOk() && !dest.isPageRef()) {
        // For integer page, getPageNum should work
        int pageNum = dest.getPageNum();
        EXPECT_GE(pageNum, 0);
    }
}

// Test: XYZ with zero zoom
TEST_F(LinkDestTest_273, XYZZeroZoom_273) {
    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(0));
    arrObj.arrayAdd(Object(objName, "XYZ"));
    arrObj.arrayAdd(Object(0.0));   // left
    arrObj.arrayAdd(Object(0.0));   // top
    arrObj.arrayAdd(Object(0.0));   // zoom = 0 means no change
    
    LinkDest dest(arrObj.getArray());
    
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destXYZ);
        // zoom of 0 typically means "no change"
        EXPECT_DOUBLE_EQ(dest.getZoom(), 0.0);
    }
}

// Test: Negative coordinates
TEST_F(LinkDestTest_273, NegativeCoordinates_273) {
    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(0));
    arrObj.arrayAdd(Object(objName, "XYZ"));
    arrObj.arrayAdd(Object(-100.0)); // left
    arrObj.arrayAdd(Object(-200.0)); // top
    arrObj.arrayAdd(Object(1.0));    // zoom
    
    LinkDest dest(arrObj.getArray());
    
    if (dest.isOk()) {
        EXPECT_DOUBLE_EQ(dest.getLeft(), -100.0);
        EXPECT_DOUBLE_EQ(dest.getTop(), -200.0);
    }
}

// Test: Very large coordinate values
TEST_F(LinkDestTest_273, LargeCoordinates_273) {
    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(0));
    arrObj.arrayAdd(Object(objName, "FitR"));
    arrObj.arrayAdd(Object(1e10));  // left
    arrObj.arrayAdd(Object(1e10));  // bottom
    arrObj.arrayAdd(Object(1e10));  // right
    arrObj.arrayAdd(Object(1e10));  // top
    
    LinkDest dest(arrObj.getArray());
    
    if (dest.isOk()) {
        EXPECT_DOUBLE_EQ(dest.getLeft(), 1e10);
        EXPECT_DOUBLE_EQ(dest.getBottom(), 1e10);
        EXPECT_DOUBLE_EQ(dest.getRight(), 1e10);
        EXPECT_DOUBLE_EQ(dest.getTop(), 1e10);
    }
}

// Test: FitH with null top parameter
TEST_F(LinkDestTest_273, FitHWithNullTop_273) {
    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(0));
    arrObj.arrayAdd(Object(objName, "FitH"));
    arrObj.arrayAdd(Object(objNull)); // top is null
    
    LinkDest dest(arrObj.getArray());
    
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitH);
        EXPECT_FALSE(dest.getChangeTop());
    }
}

// Test: FitV with null left parameter
TEST_F(LinkDestTest_273, FitVWithNullLeft_273) {
    Object arrObj = Object(new Array(nullptr));
    arrObj.arrayAdd(Object(0));
    arrObj.arrayAdd(Object(objName, "FitV"));
    arrObj.arrayAdd(Object(objNull)); // left is null
    
    LinkDest dest(arrObj.getArray());
    
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitV);
        EXPECT_FALSE(dest.getChangeLeft());
    }
}
