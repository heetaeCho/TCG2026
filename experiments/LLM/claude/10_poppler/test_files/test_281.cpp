#include <gtest/gtest.h>
#include "Link.h"
#include "Array.h"
#include "Object.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

#include <memory>

class LinkDestTest_281 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that LinkDest constructed from an empty array is not ok
TEST_F(LinkDestTest_281, EmptyArrayIsNotOk_281) {
    // Create an empty Array - LinkDest should handle this gracefully
    auto xref = (XRef *)nullptr;
    Array arr(xref);
    LinkDest dest(&arr);
    EXPECT_FALSE(dest.isOk());
}

// Test LinkDest with a /Fit destination type
TEST_F(LinkDestTest_281, FitDestination_281) {
    auto xref = (XRef *)nullptr;
    Array arr(xref);
    
    // Page number (integer)
    arr.add(Object(1));
    // /Fit name
    arr.add(Object(objName, "Fit"));
    
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFit);
        EXPECT_FALSE(dest.isPageRef());
        EXPECT_EQ(dest.getPageNum(), 1);
        EXPECT_FALSE(dest.getChangeZoom());
    }
}

// Test LinkDest with a /XYZ destination type
TEST_F(LinkDestTest_281, XYZDestination_281) {
    auto xref = (XRef *)nullptr;
    Array arr(xref);
    
    // Page number
    arr.add(Object(1));
    // /XYZ name
    arr.add(Object(objName, "XYZ"));
    // left
    arr.add(Object(100.0));
    // top
    arr.add(Object(200.0));
    // zoom
    arr.add(Object(1.5));
    
    LinkDest dest(&arr);
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

// Test LinkDest with /XYZ and null parameters (no change)
TEST_F(LinkDestTest_281, XYZDestinationWithNulls_281) {
    auto xref = (XRef *)nullptr;
    Array arr(xref);
    
    arr.add(Object(1));
    arr.add(Object(objName, "XYZ"));
    // null left
    arr.add(Object(objNull));
    // null top
    arr.add(Object(objNull));
    // null zoom (0 means no change)
    arr.add(Object(objNull));
    
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destXYZ);
        EXPECT_FALSE(dest.getChangeLeft());
        EXPECT_FALSE(dest.getChangeTop());
        EXPECT_FALSE(dest.getChangeZoom());
    }
}

// Test LinkDest with /FitH destination type
TEST_F(LinkDestTest_281, FitHDestination_281) {
    auto xref = (XRef *)nullptr;
    Array arr(xref);
    
    arr.add(Object(1));
    arr.add(Object(objName, "FitH"));
    arr.add(Object(300.0));
    
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitH);
        EXPECT_DOUBLE_EQ(dest.getTop(), 300.0);
        EXPECT_TRUE(dest.getChangeTop());
        EXPECT_FALSE(dest.getChangeZoom());
    }
}

// Test LinkDest with /FitV destination type
TEST_F(LinkDestTest_281, FitVDestination_281) {
    auto xref = (XRef *)nullptr;
    Array arr(xref);
    
    arr.add(Object(1));
    arr.add(Object(objName, "FitV"));
    arr.add(Object(150.0));
    
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitV);
        EXPECT_DOUBLE_EQ(dest.getLeft(), 150.0);
        EXPECT_TRUE(dest.getChangeLeft());
        EXPECT_FALSE(dest.getChangeZoom());
    }
}

// Test LinkDest with /FitR destination type
TEST_F(LinkDestTest_281, FitRDestination_281) {
    auto xref = (XRef *)nullptr;
    Array arr(xref);
    
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
        EXPECT_FALSE(dest.getChangeZoom());
    }
}

// Test LinkDest with /FitB destination type
TEST_F(LinkDestTest_281, FitBDestination_281) {
    auto xref = (XRef *)nullptr;
    Array arr(xref);
    
    arr.add(Object(1));
    arr.add(Object(objName, "FitB"));
    
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitB);
        EXPECT_FALSE(dest.getChangeZoom());
    }
}

// Test LinkDest with /FitBH destination type
TEST_F(LinkDestTest_281, FitBHDestination_281) {
    auto xref = (XRef *)nullptr;
    Array arr(xref);
    
    arr.add(Object(1));
    arr.add(Object(objName, "FitBH"));
    arr.add(Object(400.0));
    
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitBH);
        EXPECT_DOUBLE_EQ(dest.getTop(), 400.0);
        EXPECT_TRUE(dest.getChangeTop());
        EXPECT_FALSE(dest.getChangeZoom());
    }
}

// Test LinkDest with /FitBV destination type
TEST_F(LinkDestTest_281, FitBVDestination_281) {
    auto xref = (XRef *)nullptr;
    Array arr(xref);
    
    arr.add(Object(1));
    arr.add(Object(objName, "FitBV"));
    arr.add(Object(250.0));
    
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitBV);
        EXPECT_DOUBLE_EQ(dest.getLeft(), 250.0);
        EXPECT_TRUE(dest.getChangeLeft());
        EXPECT_FALSE(dest.getChangeZoom());
    }
}

// Test getChangeZoom returns true when zoom is specified (non-null, non-zero)
TEST_F(LinkDestTest_281, GetChangeZoomTrueWhenZoomSpecified_281) {
    auto xref = (XRef *)nullptr;
    Array arr(xref);
    
    arr.add(Object(1));
    arr.add(Object(objName, "XYZ"));
    arr.add(Object(0.0));    // left
    arr.add(Object(0.0));    // top
    arr.add(Object(2.0));    // zoom - non-null, non-zero
    
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_TRUE(dest.getChangeZoom());
        EXPECT_DOUBLE_EQ(dest.getZoom(), 2.0);
    }
}

// Test getChangeZoom returns false when zoom is 0 in XYZ
TEST_F(LinkDestTest_281, GetChangeZoomFalseWhenZoomIsZero_281) {
    auto xref = (XRef *)nullptr;
    Array arr(xref);
    
    arr.add(Object(1));
    arr.add(Object(objName, "XYZ"));
    arr.add(Object(100.0));
    arr.add(Object(200.0));
    arr.add(Object(0.0));    // zoom = 0 means no change
    
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_FALSE(dest.getChangeZoom());
    }
}

// Test with invalid destination name
TEST_F(LinkDestTest_281, InvalidDestinationName_281) {
    auto xref = (XRef *)nullptr;
    Array arr(xref);
    
    arr.add(Object(1));
    arr.add(Object(objName, "InvalidDest"));
    
    LinkDest dest(&arr);
    EXPECT_FALSE(dest.isOk());
}

// Test with only one element (missing destination type)
TEST_F(LinkDestTest_281, SingleElementArray_281) {
    auto xref = (XRef *)nullptr;
    Array arr(xref);
    
    arr.add(Object(1));
    
    LinkDest dest(&arr);
    EXPECT_FALSE(dest.isOk());
}

// Test that isPageRef returns false for integer page numbers
TEST_F(LinkDestTest_281, IsPageRefFalseForIntegerPage_281) {
    auto xref = (XRef *)nullptr;
    Array arr(xref);
    
    arr.add(Object(5));
    arr.add(Object(objName, "Fit"));
    
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_FALSE(dest.isPageRef());
        EXPECT_EQ(dest.getPageNum(), 5);
    }
}

// Test XYZ with specific zoom value - verify getChangeZoom
TEST_F(LinkDestTest_281, XYZWithSpecificZoom_281) {
    auto xref = (XRef *)nullptr;
    Array arr(xref);
    
    arr.add(Object(1));
    arr.add(Object(objName, "XYZ"));
    arr.add(Object(objNull));  // no left change
    arr.add(Object(objNull));  // no top change
    arr.add(Object(0.75));     // zoom specified
    
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destXYZ);
        EXPECT_FALSE(dest.getChangeLeft());
        EXPECT_FALSE(dest.getChangeTop());
        EXPECT_TRUE(dest.getChangeZoom());
        EXPECT_DOUBLE_EQ(dest.getZoom(), 0.75);
    }
}

// Test FitH with null top parameter
TEST_F(LinkDestTest_281, FitHWithNullTop_281) {
    auto xref = (XRef *)nullptr;
    Array arr(xref);
    
    arr.add(Object(1));
    arr.add(Object(objName, "FitH"));
    arr.add(Object(objNull));
    
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitH);
        EXPECT_FALSE(dest.getChangeTop());
    }
}

// Test boundary: page number 0
TEST_F(LinkDestTest_281, PageNumberZero_281) {
    auto xref = (XRef *)nullptr;
    Array arr(xref);
    
    arr.add(Object(0));
    arr.add(Object(objName, "Fit"));
    
    LinkDest dest(&arr);
    // Page 0 might or might not be valid depending on implementation
    // We just test the interface responds
    if (dest.isOk()) {
        EXPECT_EQ(dest.getPageNum(), 0);
    }
}

// Test boundary: negative coordinates
TEST_F(LinkDestTest_281, NegativeCoordinates_281) {
    auto xref = (XRef *)nullptr;
    Array arr(xref);
    
    arr.add(Object(1));
    arr.add(Object(objName, "XYZ"));
    arr.add(Object(-100.0));
    arr.add(Object(-200.0));
    arr.add(Object(1.0));
    
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_DOUBLE_EQ(dest.getLeft(), -100.0);
        EXPECT_DOUBLE_EQ(dest.getTop(), -200.0);
        EXPECT_TRUE(dest.getChangeLeft());
        EXPECT_TRUE(dest.getChangeTop());
        EXPECT_TRUE(dest.getChangeZoom());
    }
}
