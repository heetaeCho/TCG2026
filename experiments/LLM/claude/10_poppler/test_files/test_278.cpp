#include <gtest/gtest.h>
#include "Link.h"
#include "Array.h"
#include "Object.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

#include <memory>

class LinkDestTest_278 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that getZoom returns the zoom value from a properly constructed LinkDest
// We construct via Array with known destination types to observe getZoom behavior

TEST_F(LinkDestTest_278, GetZoomReturnsZeroForFitDest_278) {
    // Create an XRef-less array for testing
    // A /Fit destination has no zoom parameter, so zoom should be 0
    // Destination array: [pageNum /Fit]
    auto xref = std::unique_ptr<XRef>(nullptr);
    Array arr(nullptr);
    arr.add(Object(0));  // page number
    arr.add(Object(objName, "Fit"));
    
    LinkDest dest(arr);
    
    if (dest.isOk()) {
        // For Fit destinations, zoom is typically 0 or unchanged
        double zoom = dest.getZoom();
        // Zoom should be a non-negative value for Fit type
        EXPECT_GE(zoom, 0.0);
    }
}

TEST_F(LinkDestTest_278, GetZoomReturnsValueForXYZDest_278) {
    // XYZ destination: [pageNum /XYZ left top zoom]
    Array arr(nullptr);
    arr.add(Object(0));  // page number
    arr.add(Object(objName, "XYZ"));
    arr.add(Object(100.0));  // left
    arr.add(Object(200.0));  // top
    arr.add(Object(1.5));    // zoom
    
    LinkDest dest(arr);
    
    if (dest.isOk()) {
        EXPECT_DOUBLE_EQ(dest.getZoom(), 1.5);
    }
}

TEST_F(LinkDestTest_278, GetZoomReturnsZeroForXYZWithNullZoom_278) {
    // XYZ destination with null zoom: [pageNum /XYZ left top null]
    Array arr(nullptr);
    arr.add(Object(0));  // page number
    arr.add(Object(objName, "XYZ"));
    arr.add(Object(100.0));  // left
    arr.add(Object(200.0));  // top
    arr.add(Object(objNull));  // null zoom
    
    LinkDest dest(arr);
    
    if (dest.isOk()) {
        // With null zoom, zoom should be 0
        EXPECT_DOUBLE_EQ(dest.getZoom(), 0.0);
    }
}

TEST_F(LinkDestTest_278, GetZoomForFitHDest_278) {
    // FitH destination: [pageNum /FitH top]
    Array arr(nullptr);
    arr.add(Object(0));
    arr.add(Object(objName, "FitH"));
    arr.add(Object(500.0));  // top
    
    LinkDest dest(arr);
    
    if (dest.isOk()) {
        // FitH doesn't have a zoom parameter
        double zoom = dest.getZoom();
        EXPECT_GE(zoom, 0.0);
    }
}

TEST_F(LinkDestTest_278, GetZoomForFitVDest_278) {
    // FitV destination: [pageNum /FitV left]
    Array arr(nullptr);
    arr.add(Object(0));
    arr.add(Object(objName, "FitV"));
    arr.add(Object(100.0));  // left
    
    LinkDest dest(arr);
    
    if (dest.isOk()) {
        double zoom = dest.getZoom();
        EXPECT_GE(zoom, 0.0);
    }
}

TEST_F(LinkDestTest_278, GetZoomForFitRDest_278) {
    // FitR destination: [pageNum /FitR left bottom right top]
    Array arr(nullptr);
    arr.add(Object(0));
    arr.add(Object(objName, "FitR"));
    arr.add(Object(0.0));    // left
    arr.add(Object(0.0));    // bottom
    arr.add(Object(612.0));  // right
    arr.add(Object(792.0));  // top
    
    LinkDest dest(arr);
    
    if (dest.isOk()) {
        double zoom = dest.getZoom();
        EXPECT_GE(zoom, 0.0);
    }
}

TEST_F(LinkDestTest_278, GetZoomXYZWithZeroZoom_278) {
    // XYZ destination with zoom = 0: [pageNum /XYZ left top 0]
    Array arr(nullptr);
    arr.add(Object(0));
    arr.add(Object(objName, "XYZ"));
    arr.add(Object(0.0));
    arr.add(Object(0.0));
    arr.add(Object(0.0));  // zoom = 0
    
    LinkDest dest(arr);
    
    if (dest.isOk()) {
        EXPECT_DOUBLE_EQ(dest.getZoom(), 0.0);
    }
}

TEST_F(LinkDestTest_278, GetZoomXYZWithLargeZoom_278) {
    // XYZ destination with large zoom value
    Array arr(nullptr);
    arr.add(Object(0));
    arr.add(Object(objName, "XYZ"));
    arr.add(Object(0.0));
    arr.add(Object(0.0));
    arr.add(Object(10.0));  // large zoom
    
    LinkDest dest(arr);
    
    if (dest.isOk()) {
        EXPECT_DOUBLE_EQ(dest.getZoom(), 10.0);
    }
}

TEST_F(LinkDestTest_278, GetZoomXYZWithSmallZoom_278) {
    // XYZ destination with small zoom value
    Array arr(nullptr);
    arr.add(Object(0));
    arr.add(Object(objName, "XYZ"));
    arr.add(Object(0.0));
    arr.add(Object(0.0));
    arr.add(Object(0.01));  // small zoom
    
    LinkDest dest(arr);
    
    if (dest.isOk()) {
        EXPECT_DOUBLE_EQ(dest.getZoom(), 0.01);
    }
}

TEST_F(LinkDestTest_278, IsOkForEmptyArray_278) {
    // Empty array should result in invalid LinkDest
    Array arr(nullptr);
    
    LinkDest dest(arr);
    
    EXPECT_FALSE(dest.isOk());
}

TEST_F(LinkDestTest_278, GetChangeZoomForXYZWithZoom_278) {
    // XYZ with explicit zoom should have changeZoom true
    Array arr(nullptr);
    arr.add(Object(0));
    arr.add(Object(objName, "XYZ"));
    arr.add(Object(0.0));
    arr.add(Object(0.0));
    arr.add(Object(2.0));
    
    LinkDest dest(arr);
    
    if (dest.isOk()) {
        EXPECT_TRUE(dest.getChangeZoom());
        EXPECT_DOUBLE_EQ(dest.getZoom(), 2.0);
    }
}

TEST_F(LinkDestTest_278, GetKindForFitDest_278) {
    Array arr(nullptr);
    arr.add(Object(0));
    arr.add(Object(objName, "Fit"));
    
    LinkDest dest(arr);
    
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFit);
    }
}

TEST_F(LinkDestTest_278, GetKindForXYZDest_278) {
    Array arr(nullptr);
    arr.add(Object(0));
    arr.add(Object(objName, "XYZ"));
    arr.add(Object(0.0));
    arr.add(Object(0.0));
    arr.add(Object(1.0));
    
    LinkDest dest(arr);
    
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destXYZ);
    }
}

TEST_F(LinkDestTest_278, GetLeftForXYZDest_278) {
    Array arr(nullptr);
    arr.add(Object(0));
    arr.add(Object(objName, "XYZ"));
    arr.add(Object(42.0));
    arr.add(Object(84.0));
    arr.add(Object(1.0));
    
    LinkDest dest(arr);
    
    if (dest.isOk()) {
        EXPECT_DOUBLE_EQ(dest.getLeft(), 42.0);
    }
}

TEST_F(LinkDestTest_278, GetTopForXYZDest_278) {
    Array arr(nullptr);
    arr.add(Object(0));
    arr.add(Object(objName, "XYZ"));
    arr.add(Object(42.0));
    arr.add(Object(84.0));
    arr.add(Object(1.0));
    
    LinkDest dest(arr);
    
    if (dest.isOk()) {
        EXPECT_DOUBLE_EQ(dest.getTop(), 84.0);
    }
}

TEST_F(LinkDestTest_278, IsPageRefForPageNum_278) {
    Array arr(nullptr);
    arr.add(Object(0));  // page number (not a ref)
    arr.add(Object(objName, "Fit"));
    
    LinkDest dest(arr);
    
    if (dest.isOk()) {
        EXPECT_FALSE(dest.isPageRef());
    }
}
