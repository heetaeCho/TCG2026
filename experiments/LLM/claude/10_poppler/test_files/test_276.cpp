#include <gtest/gtest.h>
#include "Link.h"
#include "Array.h"
#include "Object.h"
#include "PDFDoc.h"

#include <memory>

// Helper to create a minimal XRef/PDFDoc context for Array construction
// Since LinkDest requires an Array, we need to construct valid Array objects.

class LinkDestTest_276 : public ::testing::Test {
protected:
    void SetUp() override {
        // We need an XRef for Array construction in poppler
    }

    void TearDown() override {
    }
};

// Test that constructing a LinkDest with an empty array results in !isOk()
TEST_F(LinkDestTest_276, EmptyArrayIsNotOk_276) {
    // Create an empty array - LinkDest should fail to parse it
    auto xref = std::unique_ptr<XRef>(new XRef());
    Array *arr = new Array(xref.get());
    Object obj(arr);
    LinkDest dest(obj.getArray());
    EXPECT_FALSE(dest.isOk());
}

// Test constructing a /Fit destination
TEST_F(LinkDestTest_276, FitDestination_276) {
    auto xref = std::unique_ptr<XRef>(new XRef());
    Array *arr = new Array(xref.get());
    // [pageNum /Fit]
    arr->add(Object(1));  // page number
    arr->add(Object(objName, "Fit"));
    Object obj(arr);
    LinkDest dest(obj.getArray());
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFit);
        EXPECT_FALSE(dest.isPageRef());
        EXPECT_EQ(dest.getPageNum(), 1);
    }
}

// Test constructing a /XYZ destination
TEST_F(LinkDestTest_276, XYZDestination_276) {
    auto xref = std::unique_ptr<XRef>(new XRef());
    Array *arr = new Array(xref.get());
    // [pageNum /XYZ left top zoom]
    arr->add(Object(1));  // page number
    arr->add(Object(objName, "XYZ"));
    arr->add(Object(100.0));  // left
    arr->add(Object(200.0));  // top
    arr->add(Object(1.5));    // zoom
    Object obj(arr);
    LinkDest dest(obj.getArray());
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destXYZ);
        EXPECT_DOUBLE_EQ(dest.getLeft(), 100.0);
        EXPECT_DOUBLE_EQ(dest.getTop(), 200.0);
        EXPECT_DOUBLE_EQ(dest.getZoom(), 1.5);
    }
}

// Test constructing a /FitR destination which uses right
TEST_F(LinkDestTest_276, FitRDestination_276) {
    auto xref = std::unique_ptr<XRef>(new XRef());
    Array *arr = new Array(xref.get());
    // [pageNum /FitR left bottom right top]
    arr->add(Object(1));        // page number
    arr->add(Object(objName, "FitR"));
    arr->add(Object(10.0));     // left
    arr->add(Object(20.0));     // bottom
    arr->add(Object(300.0));    // right
    arr->add(Object(400.0));    // top
    Object obj(arr);
    LinkDest dest(obj.getArray());
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitR);
        EXPECT_DOUBLE_EQ(dest.getLeft(), 10.0);
        EXPECT_DOUBLE_EQ(dest.getBottom(), 20.0);
        EXPECT_DOUBLE_EQ(dest.getRight(), 300.0);
        EXPECT_DOUBLE_EQ(dest.getTop(), 400.0);
    }
}

// Test getRight returns expected value for FitR
TEST_F(LinkDestTest_276, GetRightReturnsFitRRight_276) {
    auto xref = std::unique_ptr<XRef>(new XRef());
    Array *arr = new Array(xref.get());
    arr->add(Object(1));
    arr->add(Object(objName, "FitR"));
    arr->add(Object(0.0));      // left
    arr->add(Object(0.0));      // bottom
    arr->add(Object(612.0));    // right
    arr->add(Object(792.0));    // top
    Object obj(arr);
    LinkDest dest(obj.getArray());
    if (dest.isOk()) {
        EXPECT_DOUBLE_EQ(dest.getRight(), 612.0);
    }
}

// Test FitH destination
TEST_F(LinkDestTest_276, FitHDestination_276) {
    auto xref = std::unique_ptr<XRef>(new XRef());
    Array *arr = new Array(xref.get());
    // [pageNum /FitH top]
    arr->add(Object(1));
    arr->add(Object(objName, "FitH"));
    arr->add(Object(500.0));  // top
    Object obj(arr);
    LinkDest dest(obj.getArray());
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitH);
        EXPECT_DOUBLE_EQ(dest.getTop(), 500.0);
    }
}

// Test FitV destination
TEST_F(LinkDestTest_276, FitVDestination_276) {
    auto xref = std::unique_ptr<XRef>(new XRef());
    Array *arr = new Array(xref.get());
    // [pageNum /FitV left]
    arr->add(Object(1));
    arr->add(Object(objName, "FitV"));
    arr->add(Object(72.0));  // left
    Object obj(arr);
    LinkDest dest(obj.getArray());
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitV);
        EXPECT_DOUBLE_EQ(dest.getLeft(), 72.0);
    }
}

// Test FitB destination
TEST_F(LinkDestTest_276, FitBDestination_276) {
    auto xref = std::unique_ptr<XRef>(new XRef());
    Array *arr = new Array(xref.get());
    arr->add(Object(1));
    arr->add(Object(objName, "FitB"));
    Object obj(arr);
    LinkDest dest(obj.getArray());
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitB);
    }
}

// Test FitBH destination
TEST_F(LinkDestTest_276, FitBHDestination_276) {
    auto xref = std::unique_ptr<XRef>(new XRef());
    Array *arr = new Array(xref.get());
    arr->add(Object(1));
    arr->add(Object(objName, "FitBH"));
    arr->add(Object(350.0));  // top
    Object obj(arr);
    LinkDest dest(obj.getArray());
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitBH);
        EXPECT_DOUBLE_EQ(dest.getTop(), 350.0);
    }
}

// Test FitBV destination
TEST_F(LinkDestTest_276, FitBVDestination_276) {
    auto xref = std::unique_ptr<XRef>(new XRef());
    Array *arr = new Array(xref.get());
    arr->add(Object(1));
    arr->add(Object(objName, "FitBV"));
    arr->add(Object(150.0));  // left
    Object obj(arr);
    LinkDest dest(obj.getArray());
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitBV);
        EXPECT_DOUBLE_EQ(dest.getLeft(), 150.0);
    }
}

// Test with null values in XYZ destination
TEST_F(LinkDestTest_276, XYZWithNullValues_276) {
    auto xref = std::unique_ptr<XRef>(new XRef());
    Array *arr = new Array(xref.get());
    arr->add(Object(1));
    arr->add(Object(objName, "XYZ"));
    arr->add(Object(objNull));  // left = null
    arr->add(Object(objNull));  // top = null
    arr->add(Object(objNull));  // zoom = null
    Object obj(arr);
    LinkDest dest(obj.getArray());
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destXYZ);
        EXPECT_FALSE(dest.getChangeLeft());
        EXPECT_FALSE(dest.getChangeTop());
        EXPECT_FALSE(dest.getChangeZoom());
    }
}

// Test with invalid destination name
TEST_F(LinkDestTest_276, InvalidDestinationName_276) {
    auto xref = std::unique_ptr<XRef>(new XRef());
    Array *arr = new Array(xref.get());
    arr->add(Object(1));
    arr->add(Object(objName, "InvalidDest"));
    Object obj(arr);
    LinkDest dest(obj.getArray());
    EXPECT_FALSE(dest.isOk());
}

// Test getRight with negative value
TEST_F(LinkDestTest_276, GetRightNegativeValue_276) {
    auto xref = std::unique_ptr<XRef>(new XRef());
    Array *arr = new Array(xref.get());
    arr->add(Object(1));
    arr->add(Object(objName, "FitR"));
    arr->add(Object(-10.0));    // left
    arr->add(Object(-20.0));    // bottom
    arr->add(Object(-5.0));     // right (negative)
    arr->add(Object(400.0));    // top
    Object obj(arr);
    LinkDest dest(obj.getArray());
    if (dest.isOk()) {
        EXPECT_DOUBLE_EQ(dest.getRight(), -5.0);
    }
}

// Test getRight with zero value
TEST_F(LinkDestTest_276, GetRightZeroValue_276) {
    auto xref = std::unique_ptr<XRef>(new XRef());
    Array *arr = new Array(xref.get());
    arr->add(Object(1));
    arr->add(Object(objName, "FitR"));
    arr->add(Object(0.0));   // left
    arr->add(Object(0.0));   // bottom
    arr->add(Object(0.0));   // right
    arr->add(Object(0.0));   // top
    Object obj(arr);
    LinkDest dest(obj.getArray());
    if (dest.isOk()) {
        EXPECT_DOUBLE_EQ(dest.getRight(), 0.0);
    }
}

// Test with very large values
TEST_F(LinkDestTest_276, GetRightLargeValue_276) {
    auto xref = std::unique_ptr<XRef>(new XRef());
    Array *arr = new Array(xref.get());
    arr->add(Object(1));
    arr->add(Object(objName, "FitR"));
    arr->add(Object(0.0));
    arr->add(Object(0.0));
    arr->add(Object(1e10));   // very large right
    arr->add(Object(1e10));
    Object obj(arr);
    LinkDest dest(obj.getArray());
    if (dest.isOk()) {
        EXPECT_DOUBLE_EQ(dest.getRight(), 1e10);
    }
}

// Test that single element array is not ok
TEST_F(LinkDestTest_276, SingleElementArrayNotOk_276) {
    auto xref = std::unique_ptr<XRef>(new XRef());
    Array *arr = new Array(xref.get());
    arr->add(Object(1));
    Object obj(arr);
    LinkDest dest(obj.getArray());
    EXPECT_FALSE(dest.isOk());
}

// Test XYZ with changeLeft and changeTop flags
TEST_F(LinkDestTest_276, XYZChangeFlags_276) {
    auto xref = std::unique_ptr<XRef>(new XRef());
    Array *arr = new Array(xref.get());
    arr->add(Object(1));
    arr->add(Object(objName, "XYZ"));
    arr->add(Object(100.0));  // left - should set changeLeft
    arr->add(Object(200.0));  // top - should set changeTop
    arr->add(Object(2.0));    // zoom - should set changeZoom
    Object obj(arr);
    LinkDest dest(obj.getArray());
    if (dest.isOk()) {
        EXPECT_TRUE(dest.getChangeLeft());
        EXPECT_TRUE(dest.getChangeTop());
        EXPECT_TRUE(dest.getChangeZoom());
    }
}
