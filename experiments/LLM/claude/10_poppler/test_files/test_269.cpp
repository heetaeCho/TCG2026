#include <gtest/gtest.h>
#include "Link.h"
#include "Array.h"
#include "Object.h"
#include "Dict.h"
#include "PDFDoc.h"

#include <memory>

// Helper to create a minimal XRef/PDF context for Array construction
class LinkDestTest_269 : public ::testing::Test {
protected:
    void SetUp() override {
        // We need an XRef for Array construction. We'll create a minimal one.
        // In poppler, Array requires an XRef pointer.
    }

    void TearDown() override {
    }
};

// Test that a LinkDest constructed from an empty array is not ok
TEST_F(LinkDestTest_269, EmptyArrayIsNotOk_269) {
    // An empty array should not produce a valid LinkDest
    Array arr(nullptr);
    LinkDest dest(&arr);
    EXPECT_FALSE(dest.isOk());
}

// Test that a LinkDest constructed from an array with only one element (page ref but no type) is not ok
TEST_F(LinkDestTest_269, SingleElementArrayIsNotOk_269) {
    Array arr(nullptr);
    Object obj(1); // just a page number
    arr.add(std::move(obj));
    LinkDest dest(&arr);
    EXPECT_FALSE(dest.isOk());
}

// Test that a LinkDest with /Fit destination type is ok
TEST_F(LinkDestTest_269, FitDestinationIsOk_269) {
    Array arr(nullptr);
    // Page number
    Object pageObj(0);
    arr.add(std::move(pageObj));
    // /Fit name
    Object fitObj(objName, "Fit");
    arr.add(std::move(fitObj));

    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFit);
        EXPECT_FALSE(dest.isPageRef());
        EXPECT_EQ(dest.getPageNum(), 0);
    }
}

// Test that a LinkDest with /FitH destination type works
TEST_F(LinkDestTest_269, FitHDestinationIsOk_269) {
    Array arr(nullptr);
    // Page number
    Object pageObj(1);
    arr.add(std::move(pageObj));
    // /FitH name
    Object fitHObj(objName, "FitH");
    arr.add(std::move(fitHObj));
    // top parameter
    Object topObj(100.0);
    arr.add(std::move(topObj));

    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitH);
        EXPECT_FALSE(dest.isPageRef());
        EXPECT_DOUBLE_EQ(dest.getTop(), 100.0);
        EXPECT_TRUE(dest.getChangeTop());
    }
}

// Test that a LinkDest with /FitV destination type works
TEST_F(LinkDestTest_269, FitVDestinationIsOk_269) {
    Array arr(nullptr);
    // Page number
    Object pageObj(2);
    arr.add(std::move(pageObj));
    // /FitV name
    Object fitVObj(objName, "FitV");
    arr.add(std::move(fitVObj));
    // left parameter
    Object leftObj(50.0);
    arr.add(std::move(leftObj));

    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitV);
        EXPECT_FALSE(dest.isPageRef());
        EXPECT_DOUBLE_EQ(dest.getLeft(), 50.0);
        EXPECT_TRUE(dest.getChangeLeft());
    }
}

// Test that a LinkDest with /XYZ destination type works
TEST_F(LinkDestTest_269, XYZDestinationIsOk_269) {
    Array arr(nullptr);
    // Page number
    Object pageObj(3);
    arr.add(std::move(pageObj));
    // /XYZ name
    Object xyzObj(objName, "XYZ");
    arr.add(std::move(xyzObj));
    // left
    Object leftObj(10.0);
    arr.add(std::move(leftObj));
    // top
    Object topObj(20.0);
    arr.add(std::move(topObj));
    // zoom
    Object zoomObj(1.5);
    arr.add(std::move(zoomObj));

    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destXYZ);
        EXPECT_FALSE(dest.isPageRef());
        EXPECT_EQ(dest.getPageNum(), 3);
        EXPECT_DOUBLE_EQ(dest.getLeft(), 10.0);
        EXPECT_DOUBLE_EQ(dest.getTop(), 20.0);
        EXPECT_DOUBLE_EQ(dest.getZoom(), 1.5);
        EXPECT_TRUE(dest.getChangeLeft());
        EXPECT_TRUE(dest.getChangeTop());
        EXPECT_TRUE(dest.getChangeZoom());
    }
}

// Test XYZ with null parameters (nulls mean "unchanged")
TEST_F(LinkDestTest_269, XYZWithNullParamsIsOk_269) {
    Array arr(nullptr);
    // Page number
    Object pageObj(0);
    arr.add(std::move(pageObj));
    // /XYZ name
    Object xyzObj(objName, "XYZ");
    arr.add(std::move(xyzObj));
    // null left
    Object leftObj(objNull);
    arr.add(std::move(leftObj));
    // null top
    Object topObj(objNull);
    arr.add(std::move(topObj));
    // null zoom
    Object zoomObj(objNull);
    arr.add(std::move(zoomObj));

    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destXYZ);
        EXPECT_FALSE(dest.getChangeLeft());
        EXPECT_FALSE(dest.getChangeTop());
        EXPECT_FALSE(dest.getChangeZoom());
    }
}

// Test /FitR destination type
TEST_F(LinkDestTest_269, FitRDestinationIsOk_269) {
    Array arr(nullptr);
    Object pageObj(1);
    arr.add(std::move(pageObj));
    Object fitRObj(objName, "FitR");
    arr.add(std::move(fitRObj));
    // left, bottom, right, top
    Object leftObj(10.0);
    arr.add(std::move(leftObj));
    Object bottomObj(20.0);
    arr.add(std::move(bottomObj));
    Object rightObj(300.0);
    arr.add(std::move(rightObj));
    Object topObj(400.0);
    arr.add(std::move(topObj));

    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitR);
        EXPECT_DOUBLE_EQ(dest.getLeft(), 10.0);
        EXPECT_DOUBLE_EQ(dest.getBottom(), 20.0);
        EXPECT_DOUBLE_EQ(dest.getRight(), 300.0);
        EXPECT_DOUBLE_EQ(dest.getTop(), 400.0);
    }
}

// Test /FitB destination type
TEST_F(LinkDestTest_269, FitBDestinationIsOk_269) {
    Array arr(nullptr);
    Object pageObj(0);
    arr.add(std::move(pageObj));
    Object fitBObj(objName, "FitB");
    arr.add(std::move(fitBObj));

    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitB);
    }
}

// Test /FitBH destination type
TEST_F(LinkDestTest_269, FitBHDestinationIsOk_269) {
    Array arr(nullptr);
    Object pageObj(0);
    arr.add(std::move(pageObj));
    Object fitBHObj(objName, "FitBH");
    arr.add(std::move(fitBHObj));
    Object topObj(150.0);
    arr.add(std::move(topObj));

    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitBH);
        EXPECT_DOUBLE_EQ(dest.getTop(), 150.0);
    }
}

// Test /FitBV destination type
TEST_F(LinkDestTest_269, FitBVDestinationIsOk_269) {
    Array arr(nullptr);
    Object pageObj(0);
    arr.add(std::move(pageObj));
    Object fitBVObj(objName, "FitBV");
    arr.add(std::move(fitBVObj));
    Object leftObj(75.0);
    arr.add(std::move(leftObj));

    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitBV);
        EXPECT_DOUBLE_EQ(dest.getLeft(), 75.0);
    }
}

// Test with an invalid destination name
TEST_F(LinkDestTest_269, InvalidDestNameIsNotOk_269) {
    Array arr(nullptr);
    Object pageObj(0);
    arr.add(std::move(pageObj));
    Object invalidObj(objName, "InvalidDest");
    arr.add(std::move(invalidObj));

    LinkDest dest(&arr);
    EXPECT_FALSE(dest.isOk());
}

// Test that getPageNum returns the correct page number for non-ref pages
TEST_F(LinkDestTest_269, GetPageNumReturnsCorrectValue_269) {
    Array arr(nullptr);
    Object pageObj(42);
    arr.add(std::move(pageObj));
    Object fitObj(objName, "Fit");
    arr.add(std::move(fitObj));

    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_FALSE(dest.isPageRef());
        EXPECT_EQ(dest.getPageNum(), 42);
    }
}

// Test with XYZ and zero zoom (zoom = 0 means no change)
TEST_F(LinkDestTest_269, XYZZeroZoom_269) {
    Array arr(nullptr);
    Object pageObj(0);
    arr.add(std::move(pageObj));
    Object xyzObj(objName, "XYZ");
    arr.add(std::move(xyzObj));
    Object leftObj(0.0);
    arr.add(std::move(leftObj));
    Object topObj(0.0);
    arr.add(std::move(topObj));
    Object zoomObj(0.0);
    arr.add(std::move(zoomObj));

    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destXYZ);
        EXPECT_DOUBLE_EQ(dest.getZoom(), 0.0);
    }
}

// Test with negative coordinates
TEST_F(LinkDestTest_269, NegativeCoordinates_269) {
    Array arr(nullptr);
    Object pageObj(0);
    arr.add(std::move(pageObj));
    Object xyzObj(objName, "XYZ");
    arr.add(std::move(xyzObj));
    Object leftObj(-100.0);
    arr.add(std::move(leftObj));
    Object topObj(-200.0);
    arr.add(std::move(topObj));
    Object zoomObj(1.0);
    arr.add(std::move(zoomObj));

    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_DOUBLE_EQ(dest.getLeft(), -100.0);
        EXPECT_DOUBLE_EQ(dest.getTop(), -200.0);
    }
}

// Test FitH with null top parameter
TEST_F(LinkDestTest_269, FitHWithNullTop_269) {
    Array arr(nullptr);
    Object pageObj(0);
    arr.add(std::move(pageObj));
    Object fitHObj(objName, "FitH");
    arr.add(std::move(fitHObj));
    Object topObj(objNull);
    arr.add(std::move(topObj));

    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitH);
        EXPECT_FALSE(dest.getChangeTop());
    }
}
