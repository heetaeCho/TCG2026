#include <gtest/gtest.h>
#include "Link.h"
#include "Array.h"
#include "Object.h"
#include "PDFDoc.h"

#include <memory>

// Since LinkDest requires an Array for construction, and we need to test
// the getBottom() method, we need to create valid Array objects that
// represent link destinations.

class LinkDestTest_275 : public ::testing::Test {
protected:
    void SetUp() override {
        // We need an XRef for Array construction in some versions
        // Create a minimal setup
    }

    void TearDown() override {
    }
};

// Test that getBottom returns a value from a properly constructed LinkDest
// with a /FitR destination (which sets bottom)
TEST_F(LinkDestTest_275, GetBottomFromFitRDestination_275) {
    // Create an array representing a /FitR destination: [page /FitR left bottom right top]
    // /FitR requires left, bottom, right, top parameters
    
    Object arrObj = Object(new Array(nullptr));
    Array *arr = arrObj.getArray();
    
    // Page number (0-based internally, but destinations use 1-based or ref)
    arr->add(Object(0));           // page number
    arr->add(Object(objName, "FitR")); // destination type
    arr->add(Object(10.0));        // left
    arr->add(Object(20.5));        // bottom
    arr->add(Object(300.0));       // right
    arr->add(Object(400.0));       // top
    
    LinkDest dest(*arr);
    
    if (dest.isOk()) {
        EXPECT_DOUBLE_EQ(dest.getBottom(), 20.5);
    }
}

// Test getBottom with zero value
TEST_F(LinkDestTest_275, GetBottomZeroValue_275) {
    Object arrObj = Object(new Array(nullptr));
    Array *arr = arrObj.getArray();
    
    arr->add(Object(0));
    arr->add(Object(objName, "FitR"));
    arr->add(Object(0.0));   // left
    arr->add(Object(0.0));   // bottom = 0
    arr->add(Object(100.0)); // right
    arr->add(Object(100.0)); // top
    
    LinkDest dest(*arr);
    
    if (dest.isOk()) {
        EXPECT_DOUBLE_EQ(dest.getBottom(), 0.0);
    }
}

// Test getBottom with negative value
TEST_F(LinkDestTest_275, GetBottomNegativeValue_275) {
    Object arrObj = Object(new Array(nullptr));
    Array *arr = arrObj.getArray();
    
    arr->add(Object(0));
    arr->add(Object(objName, "FitR"));
    arr->add(Object(-50.0));  // left
    arr->add(Object(-100.5)); // bottom (negative)
    arr->add(Object(300.0));  // right
    arr->add(Object(400.0));  // top
    
    LinkDest dest(*arr);
    
    if (dest.isOk()) {
        EXPECT_DOUBLE_EQ(dest.getBottom(), -100.5);
    }
}

// Test getBottom with large value
TEST_F(LinkDestTest_275, GetBottomLargeValue_275) {
    Object arrObj = Object(new Array(nullptr));
    Array *arr = arrObj.getArray();
    
    arr->add(Object(0));
    arr->add(Object(objName, "FitR"));
    arr->add(Object(0.0));
    arr->add(Object(999999.999)); // large bottom value
    arr->add(Object(1000000.0));
    arr->add(Object(1000000.0));
    
    LinkDest dest(*arr);
    
    if (dest.isOk()) {
        EXPECT_DOUBLE_EQ(dest.getBottom(), 999999.999);
    }
}

// Test that getBottom is consistent with other coordinate getters
TEST_F(LinkDestTest_275, GetBottomConsistentWithOtherCoordinates_275) {
    Object arrObj = Object(new Array(nullptr));
    Array *arr = arrObj.getArray();
    
    arr->add(Object(0));
    arr->add(Object(objName, "FitR"));
    arr->add(Object(10.0));  // left
    arr->add(Object(20.0));  // bottom
    arr->add(Object(30.0));  // right
    arr->add(Object(40.0));  // top
    
    LinkDest dest(*arr);
    
    if (dest.isOk()) {
        EXPECT_DOUBLE_EQ(dest.getLeft(), 10.0);
        EXPECT_DOUBLE_EQ(dest.getBottom(), 20.0);
        EXPECT_DOUBLE_EQ(dest.getRight(), 30.0);
        EXPECT_DOUBLE_EQ(dest.getTop(), 40.0);
    }
}

// Test getBottom returns const
TEST_F(LinkDestTest_275, GetBottomReturnsDouble_275) {
    Object arrObj = Object(new Array(nullptr));
    Array *arr = arrObj.getArray();
    
    arr->add(Object(0));
    arr->add(Object(objName, "FitR"));
    arr->add(Object(1.0));
    arr->add(Object(2.0));
    arr->add(Object(3.0));
    arr->add(Object(4.0));
    
    LinkDest dest(*arr);
    
    if (dest.isOk()) {
        double bottom = dest.getBottom();
        EXPECT_DOUBLE_EQ(bottom, 2.0);
        // Call again to ensure consistency
        EXPECT_DOUBLE_EQ(dest.getBottom(), bottom);
    }
}

// Test with /XYZ destination type (which may not set bottom explicitly)
TEST_F(LinkDestTest_275, GetBottomFromXYZDestination_275) {
    Object arrObj = Object(new Array(nullptr));
    Array *arr = arrObj.getArray();
    
    // /XYZ destination: [page /XYZ left top zoom]
    arr->add(Object(0));
    arr->add(Object(objName, "XYZ"));
    arr->add(Object(100.0)); // left
    arr->add(Object(200.0)); // top
    arr->add(Object(1.0));   // zoom
    
    LinkDest dest(*arr);
    
    if (dest.isOk()) {
        // For XYZ, bottom may not be explicitly set, but getBottom should still return a double
        double bottom = dest.getBottom();
        // We just verify it returns without error
        (void)bottom;
    }
}

// Test with very small fractional bottom value
TEST_F(LinkDestTest_275, GetBottomSmallFractionalValue_275) {
    Object arrObj = Object(new Array(nullptr));
    Array *arr = arrObj.getArray();
    
    arr->add(Object(0));
    arr->add(Object(objName, "FitR"));
    arr->add(Object(0.0));
    arr->add(Object(0.001)); // very small bottom
    arr->add(Object(100.0));
    arr->add(Object(100.0));
    
    LinkDest dest(*arr);
    
    if (dest.isOk()) {
        EXPECT_DOUBLE_EQ(dest.getBottom(), 0.001);
    }
}
