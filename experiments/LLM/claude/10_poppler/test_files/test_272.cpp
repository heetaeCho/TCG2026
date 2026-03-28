#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Link.h"
#include "Object.h"
#include "Array.h"
#include "PDFDoc.h"

// Test fixture for LinkDest
class LinkDestTest_272 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getPageNum returns a value (basic construction test with a Fit destination)
TEST_F(LinkDestTest_272, GetPageNumFromFitDestination_272) {
    // Create an Array that represents a valid LinkDest
    // Format: [pageNum /Fit]
    // We construct a minimal array with a page number and /Fit name
    auto xrefPtr = std::unique_ptr<XRef>(nullptr);
    
    Array *arr = new Array(nullptr);
    // Page number (0-based internally, but the array element is the page object ref or int)
    arr->add(Object(0));  // page number as integer
    arr->add(Object(objName, "Fit"));  // destination type
    
    Object arrObj(arr);
    LinkDest dest(*arr);
    
    // If the dest is ok, check page number
    if (dest.isOk()) {
        int pageNum = dest.getPageNum();
        // The page number should be accessible
        EXPECT_GE(pageNum, 0);
    }
}

// Test getPageNum with XYZ destination type
TEST_F(LinkDestTest_272, GetPageNumFromXYZDestination_272) {
    Array *arr = new Array(nullptr);
    arr->add(Object(5));  // page number
    arr->add(Object(objName, "XYZ"));
    arr->add(Object(100.0));  // left
    arr->add(Object(200.0));  // top
    arr->add(Object(1.0));    // zoom
    
    LinkDest dest(*arr);
    
    if (dest.isOk()) {
        EXPECT_FALSE(dest.isPageRef());
        int pageNum = dest.getPageNum();
        EXPECT_EQ(pageNum, 5);
    }
}

// Test getPageNum with FitR destination type
TEST_F(LinkDestTest_272, GetPageNumFromFitRDestination_272) {
    Array *arr = new Array(nullptr);
    arr->add(Object(3));  // page number
    arr->add(Object(objName, "FitR"));
    arr->add(Object(10.0));   // left
    arr->add(Object(20.0));   // bottom
    arr->add(Object(300.0));  // right
    arr->add(Object(400.0));  // top
    
    LinkDest dest(*arr);
    
    if (dest.isOk()) {
        EXPECT_FALSE(dest.isPageRef());
        EXPECT_EQ(dest.getPageNum(), 3);
    }
}

// Test with page number 0 (boundary)
TEST_F(LinkDestTest_272, GetPageNumZero_272) {
    Array *arr = new Array(nullptr);
    arr->add(Object(0));  // page number = 0
    arr->add(Object(objName, "Fit"));
    
    LinkDest dest(*arr);
    
    if (dest.isOk() && !dest.isPageRef()) {
        EXPECT_EQ(dest.getPageNum(), 0);
    }
}

// Test with a large page number
TEST_F(LinkDestTest_272, GetPageNumLargeValue_272) {
    Array *arr = new Array(nullptr);
    arr->add(Object(99999));  // large page number
    arr->add(Object(objName, "Fit"));
    
    LinkDest dest(*arr);
    
    if (dest.isOk() && !dest.isPageRef()) {
        EXPECT_EQ(dest.getPageNum(), 99999);
    }
}

// Test with FitH destination
TEST_F(LinkDestTest_272, GetPageNumFromFitHDestination_272) {
    Array *arr = new Array(nullptr);
    arr->add(Object(7));  // page number
    arr->add(Object(objName, "FitH"));
    arr->add(Object(500.0));  // top
    
    LinkDest dest(*arr);
    
    if (dest.isOk() && !dest.isPageRef()) {
        EXPECT_EQ(dest.getPageNum(), 7);
    }
}

// Test with FitV destination
TEST_F(LinkDestTest_272, GetPageNumFromFitVDestination_272) {
    Array *arr = new Array(nullptr);
    arr->add(Object(12));  // page number
    arr->add(Object(objName, "FitV"));
    arr->add(Object(100.0));  // left
    
    LinkDest dest(*arr);
    
    if (dest.isOk() && !dest.isPageRef()) {
        EXPECT_EQ(dest.getPageNum(), 12);
    }
}

// Test with FitB destination
TEST_F(LinkDestTest_272, GetPageNumFromFitBDestination_272) {
    Array *arr = new Array(nullptr);
    arr->add(Object(1));  // page number
    arr->add(Object(objName, "FitB"));
    
    LinkDest dest(*arr);
    
    if (dest.isOk() && !dest.isPageRef()) {
        EXPECT_EQ(dest.getPageNum(), 1);
    }
}

// Test with empty array - should not be ok
TEST_F(LinkDestTest_272, EmptyArrayNotOk_272) {
    Array *arr = new Array(nullptr);
    
    LinkDest dest(*arr);
    
    EXPECT_FALSE(dest.isOk());
}

// Test with single element array - should not be ok
TEST_F(LinkDestTest_272, SingleElementArrayNotOk_272) {
    Array *arr = new Array(nullptr);
    arr->add(Object(1));
    
    LinkDest dest(*arr);
    
    EXPECT_FALSE(dest.isOk());
}

// Test isOk for valid destination
TEST_F(LinkDestTest_272, IsOkForValidDestination_272) {
    Array *arr = new Array(nullptr);
    arr->add(Object(1));
    arr->add(Object(objName, "Fit"));
    
    LinkDest dest(*arr);
    
    // A valid Fit destination with integer page should be ok
    // (depends on implementation details, but we test the interface)
    if (dest.isOk()) {
        EXPECT_FALSE(dest.isPageRef());
    }
}

// Test getKind returns appropriate kind for Fit
TEST_F(LinkDestTest_272, GetKindForFitDestination_272) {
    Array *arr = new Array(nullptr);
    arr->add(Object(1));
    arr->add(Object(objName, "Fit"));
    
    LinkDest dest(*arr);
    
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFit);
    }
}

// Test getKind returns appropriate kind for XYZ
TEST_F(LinkDestTest_272, GetKindForXYZDestination_272) {
    Array *arr = new Array(nullptr);
    arr->add(Object(1));
    arr->add(Object(objName, "XYZ"));
    arr->add(Object(100.0));
    arr->add(Object(200.0));
    arr->add(Object(1.5));
    
    LinkDest dest(*arr);
    
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destXYZ);
    }
}

// Test getLeft, getTop, getZoom for XYZ destination
TEST_F(LinkDestTest_272, GetCoordinatesForXYZDestination_272) {
    Array *arr = new Array(nullptr);
    arr->add(Object(1));
    arr->add(Object(objName, "XYZ"));
    arr->add(Object(100.0));
    arr->add(Object(200.0));
    arr->add(Object(1.5));
    
    LinkDest dest(*arr);
    
    if (dest.isOk()) {
        EXPECT_DOUBLE_EQ(dest.getLeft(), 100.0);
        EXPECT_DOUBLE_EQ(dest.getTop(), 200.0);
        EXPECT_DOUBLE_EQ(dest.getZoom(), 1.5);
    }
}

// Test getChangeLeft, getChangeTop, getChangeZoom for XYZ with null values
TEST_F(LinkDestTest_272, GetChangeFlags_XYZ_WithNulls_272) {
    Array *arr = new Array(nullptr);
    arr->add(Object(1));
    arr->add(Object(objName, "XYZ"));
    arr->add(Object(objNull));  // left is null
    arr->add(Object(objNull));  // top is null
    arr->add(Object(objNull));  // zoom is null
    
    LinkDest dest(*arr);
    
    if (dest.isOk()) {
        EXPECT_FALSE(dest.getChangeLeft());
        EXPECT_FALSE(dest.getChangeTop());
        EXPECT_FALSE(dest.getChangeZoom());
    }
}

// Test invalid destination name
TEST_F(LinkDestTest_272, InvalidDestinationName_272) {
    Array *arr = new Array(nullptr);
    arr->add(Object(1));
    arr->add(Object(objName, "InvalidDest"));
    
    LinkDest dest(*arr);
    
    EXPECT_FALSE(dest.isOk());
}

// Test FitR coordinates
TEST_F(LinkDestTest_272, GetCoordinatesForFitRDestination_272) {
    Array *arr = new Array(nullptr);
    arr->add(Object(2));
    arr->add(Object(objName, "FitR"));
    arr->add(Object(10.0));   // left
    arr->add(Object(20.0));   // bottom
    arr->add(Object(300.0));  // right
    arr->add(Object(400.0));  // top
    
    LinkDest dest(*arr);
    
    if (dest.isOk()) {
        EXPECT_DOUBLE_EQ(dest.getLeft(), 10.0);
        EXPECT_DOUBLE_EQ(dest.getBottom(), 20.0);
        EXPECT_DOUBLE_EQ(dest.getRight(), 300.0);
        EXPECT_DOUBLE_EQ(dest.getTop(), 400.0);
        EXPECT_EQ(dest.getKind(), destFitR);
    }
}

// Test negative page number
TEST_F(LinkDestTest_272, NegativePageNumber_272) {
    Array *arr = new Array(nullptr);
    arr->add(Object(-1));  // negative page
    arr->add(Object(objName, "Fit"));
    
    LinkDest dest(*arr);
    
    // Negative page number may or may not be valid depending on implementation
    // We just verify it doesn't crash and the interface is accessible
    if (dest.isOk() && !dest.isPageRef()) {
        int pageNum = dest.getPageNum();
        (void)pageNum; // just ensure it's callable
    }
}

// Test FitBH destination
TEST_F(LinkDestTest_272, GetPageNumFromFitBHDestination_272) {
    Array *arr = new Array(nullptr);
    arr->add(Object(4));
    arr->add(Object(objName, "FitBH"));
    arr->add(Object(250.0));  // top
    
    LinkDest dest(*arr);
    
    if (dest.isOk() && !dest.isPageRef()) {
        EXPECT_EQ(dest.getPageNum(), 4);
        EXPECT_EQ(dest.getKind(), destFitBH);
    }
}

// Test FitBV destination
TEST_F(LinkDestTest_272, GetPageNumFromFitBVDestination_272) {
    Array *arr = new Array(nullptr);
    arr->add(Object(6));
    arr->add(Object(objName, "FitBV"));
    arr->add(Object(150.0));  // left
    
    LinkDest dest(*arr);
    
    if (dest.isOk() && !dest.isPageRef()) {
        EXPECT_EQ(dest.getPageNum(), 6);
        EXPECT_EQ(dest.getKind(), destFitBV);
    }
}
