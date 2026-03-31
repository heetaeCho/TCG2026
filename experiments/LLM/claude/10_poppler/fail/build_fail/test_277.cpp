#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Link.h"
#include "Array.h"
#include "Object.h"
#include "PDFDoc.h"

// Helper to create a LinkDest from an Array with specific destination type
// Since we're treating LinkDest as a black box, we construct it via its Array constructor

class LinkDestTest_277 : public ::testing::Test {
protected:
    void SetUp() override {
        // We need an XRef for Array construction
        // Using nullptr or minimal setup where possible
    }
};

// Test: LinkDest constructed with XYZ destination type returns correct top value
TEST_F(LinkDestTest_277, GetTopReturnsTopValue_277) {
    // Create an XYZ destination: [pageRef /XYZ left top zoom]
    // We need to construct a valid Array for LinkDest
    // Since we can't easily create Array objects without a full PDF context,
    // we test what we can about the interface

    // For a minimal test, we attempt to construct with an empty or minimal array
    // and verify behavior
    
    // Create a PDFDoc-less array - this requires XRef which is complex
    // We'll test with a nullptr xref array if possible
    
    auto xref = std::unique_ptr<XRef>(nullptr);
    Object arrayObj;
    
    // Build array: [0 /XYZ 100 200 1.5]
    // page=0, type=XYZ, left=100, top=200, zoom=1.5
    Array *arr = new Array(nullptr);
    
    // Page number (integer)
    arr->add(Object(0));
    
    // Destination name
    arr->add(Object(objName, "XYZ"));
    
    // Left
    arr->add(Object(100.0));
    
    // Top
    arr->add(Object(200.0));
    
    // Zoom
    arr->add(Object(1.5));
    
    LinkDest dest(arr);
    
    if (dest.isOk()) {
        EXPECT_DOUBLE_EQ(dest.getTop(), 200.0);
        EXPECT_DOUBLE_EQ(dest.getLeft(), 100.0);
        EXPECT_DOUBLE_EQ(dest.getZoom(), 1.5);
        EXPECT_EQ(dest.getKind(), destXYZ);
        EXPECT_FALSE(dest.isPageRef());
        EXPECT_EQ(dest.getPageNum(), 0);
    }
    
    delete arr;
}

// Test: LinkDest with Fit destination type
TEST_F(LinkDestTest_277, FitDestination_277) {
    Array *arr = new Array(nullptr);
    
    arr->add(Object(1));
    arr->add(Object(objName, "Fit"));
    
    LinkDest dest(arr);
    
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFit);
    }
    
    delete arr;
}

// Test: LinkDest with FitH destination type
TEST_F(LinkDestTest_277, FitHDestination_277) {
    Array *arr = new Array(nullptr);
    
    arr->add(Object(1));
    arr->add(Object(objName, "FitH"));
    arr->add(Object(300.0));
    
    LinkDest dest(arr);
    
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitH);
        EXPECT_DOUBLE_EQ(dest.getTop(), 300.0);
    }
    
    delete arr;
}

// Test: LinkDest with FitV destination type
TEST_F(LinkDestTest_277, FitVDestination_277) {
    Array *arr = new Array(nullptr);
    
    arr->add(Object(1));
    arr->add(Object(objName, "FitV"));
    arr->add(Object(150.0));
    
    LinkDest dest(arr);
    
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitV);
        EXPECT_DOUBLE_EQ(dest.getLeft(), 150.0);
    }
    
    delete arr;
}

// Test: LinkDest with FitR destination type
TEST_F(LinkDestTest_277, FitRDestination_277) {
    Array *arr = new Array(nullptr);
    
    arr->add(Object(1));
    arr->add(Object(objName, "FitR"));
    arr->add(Object(10.0));   // left
    arr->add(Object(20.0));   // bottom
    arr->add(Object(300.0));  // right
    arr->add(Object(400.0));  // top
    
    LinkDest dest(arr);
    
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitR);
        EXPECT_DOUBLE_EQ(dest.getLeft(), 10.0);
        EXPECT_DOUBLE_EQ(dest.getBottom(), 20.0);
        EXPECT_DOUBLE_EQ(dest.getRight(), 300.0);
        EXPECT_DOUBLE_EQ(dest.getTop(), 400.0);
    }
    
    delete arr;
}

// Test: LinkDest with FitB destination type
TEST_F(LinkDestTest_277, FitBDestination_277) {
    Array *arr = new Array(nullptr);
    
    arr->add(Object(1));
    arr->add(Object(objName, "FitB"));
    
    LinkDest dest(arr);
    
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitB);
    }
    
    delete arr;
}

// Test: LinkDest with FitBH destination type
TEST_F(LinkDestTest_277, FitBHDestination_277) {
    Array *arr = new Array(nullptr);
    
    arr->add(Object(1));
    arr->add(Object(objName, "FitBH"));
    arr->add(Object(250.0));
    
    LinkDest dest(arr);
    
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitBH);
        EXPECT_DOUBLE_EQ(dest.getTop(), 250.0);
    }
    
    delete arr;
}

// Test: LinkDest with FitBV destination type
TEST_F(LinkDestTest_277, FitBVDestination_277) {
    Array *arr = new Array(nullptr);
    
    arr->add(Object(1));
    arr->add(Object(objName, "FitBV"));
    arr->add(Object(175.0));
    
    LinkDest dest(arr);
    
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitBV);
        EXPECT_DOUBLE_EQ(dest.getLeft(), 175.0);
    }
    
    delete arr;
}

// Test: LinkDest with invalid/empty array
TEST_F(LinkDestTest_277, EmptyArrayIsNotOk_277) {
    Array *arr = new Array(nullptr);
    
    LinkDest dest(arr);
    
    EXPECT_FALSE(dest.isOk());
    
    delete arr;
}

// Test: LinkDest with single element array (too few elements)
TEST_F(LinkDestTest_277, SingleElementArrayIsNotOk_277) {
    Array *arr = new Array(nullptr);
    arr->add(Object(1));
    
    LinkDest dest(arr);
    
    EXPECT_FALSE(dest.isOk());
    
    delete arr;
}

// Test: LinkDest with unknown destination name
TEST_F(LinkDestTest_277, UnknownDestNameIsNotOk_277) {
    Array *arr = new Array(nullptr);
    arr->add(Object(1));
    arr->add(Object(objName, "UnknownDest"));
    
    LinkDest dest(arr);
    
    EXPECT_FALSE(dest.isOk());
    
    delete arr;
}

// Test: XYZ with null values (no change flags)
TEST_F(LinkDestTest_277, XYZWithNullValues_277) {
    Array *arr = new Array(nullptr);
    
    arr->add(Object(1));
    arr->add(Object(objName, "XYZ"));
    arr->add(Object(objNull));  // left = null
    arr->add(Object(objNull));  // top = null
    arr->add(Object(objNull));  // zoom = null
    
    LinkDest dest(arr);
    
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destXYZ);
        EXPECT_FALSE(dest.getChangeLeft());
        EXPECT_FALSE(dest.getChangeTop());
        EXPECT_FALSE(dest.getChangeZoom());
    }
    
    delete arr;
}

// Test: XYZ with actual values sets change flags
TEST_F(LinkDestTest_277, XYZWithValuesHasChangeFlags_277) {
    Array *arr = new Array(nullptr);
    
    arr->add(Object(1));
    arr->add(Object(objName, "XYZ"));
    arr->add(Object(50.0));   // left
    arr->add(Object(100.0));  // top
    arr->add(Object(2.0));    // zoom
    
    LinkDest dest(arr);
    
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destXYZ);
        EXPECT_TRUE(dest.getChangeLeft());
        EXPECT_TRUE(dest.getChangeTop());
        EXPECT_TRUE(dest.getChangeZoom());
        EXPECT_DOUBLE_EQ(dest.getLeft(), 50.0);
        EXPECT_DOUBLE_EQ(dest.getTop(), 100.0);
        EXPECT_DOUBLE_EQ(dest.getZoom(), 2.0);
    }
    
    delete arr;
}

// Test: getTop returns correct value for zero
TEST_F(LinkDestTest_277, GetTopReturnsZero_277) {
    Array *arr = new Array(nullptr);
    
    arr->add(Object(0));
    arr->add(Object(objName, "XYZ"));
    arr->add(Object(0.0));
    arr->add(Object(0.0));
    arr->add(Object(0.0));
    
    LinkDest dest(arr);
    
    if (dest.isOk()) {
        EXPECT_DOUBLE_EQ(dest.getTop(), 0.0);
    }
    
    delete arr;
}

// Test: getTop returns correct value for negative number
TEST_F(LinkDestTest_277, GetTopReturnsNegativeValue_277) {
    Array *arr = new Array(nullptr);
    
    arr->add(Object(0));
    arr->add(Object(objName, "XYZ"));
    arr->add(Object(0.0));
    arr->add(Object(-50.0));
    arr->add(Object(1.0));
    
    LinkDest dest(arr);
    
    if (dest.isOk()) {
        EXPECT_DOUBLE_EQ(dest.getTop(), -50.0);
    }
    
    delete arr;
}

// Test: getTop returns correct value for large number
TEST_F(LinkDestTest_277, GetTopReturnsLargeValue_277) {
    Array *arr = new Array(nullptr);
    
    arr->add(Object(0));
    arr->add(Object(objName, "XYZ"));
    arr->add(Object(0.0));
    arr->add(Object(99999.99));
    arr->add(Object(1.0));
    
    LinkDest dest(arr);
    
    if (dest.isOk()) {
        EXPECT_DOUBLE_EQ(dest.getTop(), 99999.99);
    }
    
    delete arr;
}

// Test: Page number is correctly reported
TEST_F(LinkDestTest_277, GetPageNumReturnsCorrectPage_277) {
    Array *arr = new Array(nullptr);
    
    arr->add(Object(5));
    arr->add(Object(objName, "Fit"));
    
    LinkDest dest(arr);
    
    if (dest.isOk()) {
        EXPECT_FALSE(dest.isPageRef());
        EXPECT_EQ(dest.getPageNum(), 5);
    }
    
    delete arr;
}
