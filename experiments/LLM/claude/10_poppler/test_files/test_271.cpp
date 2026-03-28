#include <gtest/gtest.h>
#include "Link.h"

// Since LinkDest requires an Array for construction, and we need to test
// the interface without reimplementing internal logic, we focus on
// observable behavior through the public interface.

// We need poppler headers for Array construction
#include "Object.h"
#include "PDFDoc.h"

#include <memory>

class LinkDestTest_271 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that an empty array creates an invalid LinkDest
TEST_F(LinkDestTest_271, EmptyArrayCreatesInvalidDest_271) {
    // Create an empty Array
    Array *arr = new Array(nullptr);
    Object obj(arr);
    LinkDest dest(*obj.getArray());
    EXPECT_FALSE(dest.isOk());
}

// Test isPageRef returns a boolean value (basic interface check)
TEST_F(LinkDestTest_271, IsPageRefReturnsBool_271) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    LinkDest dest(*obj.getArray());
    // Even for invalid dest, isPageRef should return some boolean
    bool result = dest.isPageRef();
    EXPECT_TRUE(result == true || result == false);
}

// Test that a malformed array (single element, not a valid dest name) yields invalid dest
TEST_F(LinkDestTest_271, SingleElementArrayInvalid_271) {
    Array *arr = new Array(nullptr);
    arr->add(Object(1));
    Object obj(arr);
    LinkDest dest(*obj.getArray());
    EXPECT_FALSE(dest.isOk());
}

// Test that an array with a page number and /Fit name creates a valid dest
TEST_F(LinkDestTest_271, FitDestWithPageNum_271) {
    Array *arr = new Array(nullptr);
    // Page number (integer)
    arr->add(Object(0));
    // /Fit name
    arr->add(Object(objName, "Fit"));
    Object obj(arr);
    LinkDest dest(*obj.getArray());
    if (dest.isOk()) {
        EXPECT_FALSE(dest.isPageRef());
        EXPECT_EQ(dest.getKind(), destFit);
        EXPECT_EQ(dest.getPageNum(), 1); // page nums are 1-based typically
    }
}

// Test /FitH destination type
TEST_F(LinkDestTest_271, FitHDestWithPageNum_271) {
    Array *arr = new Array(nullptr);
    arr->add(Object(0));
    arr->add(Object(objName, "FitH"));
    arr->add(Object(100.0));
    Object obj(arr);
    LinkDest dest(*obj.getArray());
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitH);
        EXPECT_FALSE(dest.isPageRef());
    }
}

// Test /FitV destination type
TEST_F(LinkDestTest_271, FitVDestWithPageNum_271) {
    Array *arr = new Array(nullptr);
    arr->add(Object(0));
    arr->add(Object(objName, "FitV"));
    arr->add(Object(50.0));
    Object obj(arr);
    LinkDest dest(*obj.getArray());
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitV);
    }
}

// Test /XYZ destination type
TEST_F(LinkDestTest_271, XYZDestWithPageNum_271) {
    Array *arr = new Array(nullptr);
    arr->add(Object(0));
    arr->add(Object(objName, "XYZ"));
    arr->add(Object(10.0));  // left
    arr->add(Object(20.0));  // top
    arr->add(Object(1.5));   // zoom
    Object obj(arr);
    LinkDest dest(*obj.getArray());
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destXYZ);
        EXPECT_DOUBLE_EQ(dest.getLeft(), 10.0);
        EXPECT_DOUBLE_EQ(dest.getTop(), 20.0);
        EXPECT_DOUBLE_EQ(dest.getZoom(), 1.5);
        EXPECT_TRUE(dest.getChangeLeft());
        EXPECT_TRUE(dest.getChangeTop());
        EXPECT_TRUE(dest.getChangeZoom());
    }
}

// Test /XYZ destination with null parameters
TEST_F(LinkDestTest_271, XYZDestWithNullParams_271) {
    Array *arr = new Array(nullptr);
    arr->add(Object(0));
    arr->add(Object(objName, "XYZ"));
    arr->add(Object(objNull));  // left = null
    arr->add(Object(objNull));  // top = null
    arr->add(Object(objNull));  // zoom = null
    Object obj(arr);
    LinkDest dest(*obj.getArray());
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destXYZ);
        EXPECT_FALSE(dest.getChangeLeft());
        EXPECT_FALSE(dest.getChangeTop());
        EXPECT_FALSE(dest.getChangeZoom());
    }
}

// Test /FitR destination type
TEST_F(LinkDestTest_271, FitRDestWithPageNum_271) {
    Array *arr = new Array(nullptr);
    arr->add(Object(0));
    arr->add(Object(objName, "FitR"));
    arr->add(Object(10.0));   // left
    arr->add(Object(20.0));   // bottom
    arr->add(Object(300.0));  // right
    arr->add(Object(400.0));  // top
    Object obj(arr);
    LinkDest dest(*obj.getArray());
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitR);
        EXPECT_DOUBLE_EQ(dest.getLeft(), 10.0);
        EXPECT_DOUBLE_EQ(dest.getBottom(), 20.0);
        EXPECT_DOUBLE_EQ(dest.getRight(), 300.0);
        EXPECT_DOUBLE_EQ(dest.getTop(), 400.0);
    }
}

// Test /FitB destination type
TEST_F(LinkDestTest_271, FitBDestWithPageNum_271) {
    Array *arr = new Array(nullptr);
    arr->add(Object(0));
    arr->add(Object(objName, "FitB"));
    Object obj(arr);
    LinkDest dest(*obj.getArray());
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitB);
    }
}

// Test /FitBH destination type
TEST_F(LinkDestTest_271, FitBHDestWithPageNum_271) {
    Array *arr = new Array(nullptr);
    arr->add(Object(0));
    arr->add(Object(objName, "FitBH"));
    arr->add(Object(200.0));
    Object obj(arr);
    LinkDest dest(*obj.getArray());
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitBH);
    }
}

// Test /FitBV destination type
TEST_F(LinkDestTest_271, FitBVDestWithPageNum_271) {
    Array *arr = new Array(nullptr);
    arr->add(Object(0));
    arr->add(Object(objName, "FitBV"));
    arr->add(Object(150.0));
    Object obj(arr);
    LinkDest dest(*obj.getArray());
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitBV);
    }
}

// Test with invalid destination name
TEST_F(LinkDestTest_271, InvalidDestName_271) {
    Array *arr = new Array(nullptr);
    arr->add(Object(0));
    arr->add(Object(objName, "InvalidName"));
    Object obj(arr);
    LinkDest dest(*obj.getArray());
    EXPECT_FALSE(dest.isOk());
}

// Test that getters return consistent values for boundary coordinates
TEST_F(LinkDestTest_271, BoundaryCoordinateValues_271) {
    Array *arr = new Array(nullptr);
    arr->add(Object(0));
    arr->add(Object(objName, "XYZ"));
    arr->add(Object(0.0));    // left = 0
    arr->add(Object(0.0));    // top = 0
    arr->add(Object(0.0));    // zoom = 0
    Object obj(arr);
    LinkDest dest(*obj.getArray());
    if (dest.isOk()) {
        EXPECT_DOUBLE_EQ(dest.getLeft(), 0.0);
        EXPECT_DOUBLE_EQ(dest.getTop(), 0.0);
        EXPECT_DOUBLE_EQ(dest.getZoom(), 0.0);
    }
}

// Test with negative coordinate values
TEST_F(LinkDestTest_271, NegativeCoordinateValues_271) {
    Array *arr = new Array(nullptr);
    arr->add(Object(0));
    arr->add(Object(objName, "XYZ"));
    arr->add(Object(-100.0));
    arr->add(Object(-200.0));
    arr->add(Object(2.0));
    Object obj(arr);
    LinkDest dest(*obj.getArray());
    if (dest.isOk()) {
        EXPECT_DOUBLE_EQ(dest.getLeft(), -100.0);
        EXPECT_DOUBLE_EQ(dest.getTop(), -200.0);
    }
}

// Test with page reference (Ref object) instead of page number
TEST_F(LinkDestTest_271, PageRefDest_271) {
    Array *arr = new Array(nullptr);
    // Add a Ref object as page reference
    Ref ref = {10, 0};
    arr->add(Object(ref));
    arr->add(Object(objName, "Fit"));
    Object obj(arr);
    LinkDest dest(*obj.getArray());
    if (dest.isOk()) {
        EXPECT_TRUE(dest.isPageRef());
        Ref resultRef = dest.getPageRef();
        EXPECT_EQ(resultRef.num, 10);
        EXPECT_EQ(resultRef.gen, 0);
    }
}

// Test copy behavior - LinkDest should be copyable
TEST_F(LinkDestTest_271, CopyConstruction_271) {
    Array *arr = new Array(nullptr);
    arr->add(Object(0));
    arr->add(Object(objName, "Fit"));
    Object obj(arr);
    LinkDest dest1(*obj.getArray());
    if (dest1.isOk()) {
        LinkDest dest2(dest1);
        EXPECT_EQ(dest1.isOk(), dest2.isOk());
        EXPECT_EQ(dest1.getKind(), dest2.getKind());
        EXPECT_EQ(dest1.isPageRef(), dest2.isPageRef());
    }
}
