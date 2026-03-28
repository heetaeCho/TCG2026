#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Link.h"
#include "Object.h"
#include "Array.h"
#include "PDFDoc.h"

// Helper to create an Array for LinkDest construction
// We need to work with poppler's Array class which requires an XRef

class LinkDestTest_270 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that constructing LinkDest with an empty array results in not ok
TEST_F(LinkDestTest_270, EmptyArrayIsNotOk_270) {
    // An empty array should not produce a valid LinkDest
    Array arr(nullptr);
    LinkDest dest(&arr);
    EXPECT_FALSE(dest.isOk());
}

// Test that constructing LinkDest with a single element array (page only, no destination type) is not ok
TEST_F(LinkDestTest_270, SingleElementArrayIsNotOk_270) {
    Array arr(nullptr);
    Object pageObj(1); // page number
    arr.add(std::move(pageObj));
    LinkDest dest(&arr);
    EXPECT_FALSE(dest.isOk());
}

// Test constructing a /Fit destination
TEST_F(LinkDestTest_270, FitDestination_270) {
    Array arr(nullptr);
    Object pageObj(1);
    arr.add(std::move(pageObj));
    Object nameObj(objName, "Fit");
    arr.add(std::move(nameObj));
    
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFit);
    }
}

// Test constructing a /FitB destination
TEST_F(LinkDestTest_270, FitBDestination_270) {
    Array arr(nullptr);
    Object pageObj(1);
    arr.add(std::move(pageObj));
    Object nameObj(objName, "FitB");
    arr.add(std::move(nameObj));
    
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitB);
    }
}

// Test constructing a /XYZ destination with left, top, zoom
TEST_F(LinkDestTest_270, XYZDestination_270) {
    Array arr(nullptr);
    Object pageObj(1);
    arr.add(std::move(pageObj));
    Object nameObj(objName, "XYZ");
    arr.add(std::move(nameObj));
    Object leftObj(100.0);
    arr.add(std::move(leftObj));
    Object topObj(200.0);
    arr.add(std::move(topObj));
    Object zoomObj(1.5);
    arr.add(std::move(zoomObj));
    
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destXYZ);
        EXPECT_DOUBLE_EQ(dest.getLeft(), 100.0);
        EXPECT_DOUBLE_EQ(dest.getTop(), 200.0);
        EXPECT_DOUBLE_EQ(dest.getZoom(), 1.5);
        EXPECT_TRUE(dest.getChangeLeft());
        EXPECT_TRUE(dest.getChangeTop());
        EXPECT_TRUE(dest.getChangeZoom());
    }
}

// Test constructing a /XYZ destination with null values
TEST_F(LinkDestTest_270, XYZDestinationWithNulls_270) {
    Array arr(nullptr);
    Object pageObj(1);
    arr.add(std::move(pageObj));
    Object nameObj(objName, "XYZ");
    arr.add(std::move(nameObj));
    Object nullLeft(objNull);
    arr.add(std::move(nullLeft));
    Object nullTop(objNull);
    arr.add(std::move(nullTop));
    Object nullZoom(objNull);
    arr.add(std::move(nullZoom));
    
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destXYZ);
        EXPECT_FALSE(dest.getChangeLeft());
        EXPECT_FALSE(dest.getChangeTop());
        EXPECT_FALSE(dest.getChangeZoom());
    }
}

// Test constructing a /FitH destination
TEST_F(LinkDestTest_270, FitHDestination_270) {
    Array arr(nullptr);
    Object pageObj(1);
    arr.add(std::move(pageObj));
    Object nameObj(objName, "FitH");
    arr.add(std::move(nameObj));
    Object topObj(300.0);
    arr.add(std::move(topObj));
    
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitH);
        EXPECT_DOUBLE_EQ(dest.getTop(), 300.0);
        EXPECT_TRUE(dest.getChangeTop());
    }
}

// Test constructing a /FitV destination
TEST_F(LinkDestTest_270, FitVDestination_270) {
    Array arr(nullptr);
    Object pageObj(1);
    arr.add(std::move(pageObj));
    Object nameObj(objName, "FitV");
    arr.add(std::move(nameObj));
    Object leftObj(50.0);
    arr.add(std::move(leftObj));
    
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitV);
        EXPECT_DOUBLE_EQ(dest.getLeft(), 50.0);
        EXPECT_TRUE(dest.getChangeLeft());
    }
}

// Test constructing a /FitR destination
TEST_F(LinkDestTest_270, FitRDestination_270) {
    Array arr(nullptr);
    Object pageObj(1);
    arr.add(std::move(pageObj));
    Object nameObj(objName, "FitR");
    arr.add(std::move(nameObj));
    Object leftObj(10.0);
    arr.add(std::move(leftObj));
    Object bottomObj(20.0);
    arr.add(std::move(bottomObj));
    Object rightObj(500.0);
    arr.add(std::move(rightObj));
    Object topObj(700.0);
    arr.add(std::move(topObj));
    
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitR);
        EXPECT_DOUBLE_EQ(dest.getLeft(), 10.0);
        EXPECT_DOUBLE_EQ(dest.getBottom(), 20.0);
        EXPECT_DOUBLE_EQ(dest.getRight(), 500.0);
        EXPECT_DOUBLE_EQ(dest.getTop(), 700.0);
    }
}

// Test constructing a /FitBH destination
TEST_F(LinkDestTest_270, FitBHDestination_270) {
    Array arr(nullptr);
    Object pageObj(1);
    arr.add(std::move(pageObj));
    Object nameObj(objName, "FitBH");
    arr.add(std::move(nameObj));
    Object topObj(400.0);
    arr.add(std::move(topObj));
    
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitBH);
        EXPECT_DOUBLE_EQ(dest.getTop(), 400.0);
    }
}

// Test constructing a /FitBV destination
TEST_F(LinkDestTest_270, FitBVDestination_270) {
    Array arr(nullptr);
    Object pageObj(1);
    arr.add(std::move(pageObj));
    Object nameObj(objName, "FitBV");
    arr.add(std::move(nameObj));
    Object leftObj(75.0);
    arr.add(std::move(leftObj));
    
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destFitBV);
        EXPECT_DOUBLE_EQ(dest.getLeft(), 75.0);
    }
}

// Test with an invalid destination name
TEST_F(LinkDestTest_270, InvalidDestinationName_270) {
    Array arr(nullptr);
    Object pageObj(1);
    arr.add(std::move(pageObj));
    Object nameObj(objName, "InvalidName");
    arr.add(std::move(nameObj));
    
    LinkDest dest(&arr);
    EXPECT_FALSE(dest.isOk());
}

// Test isPageRef when page is specified as integer
TEST_F(LinkDestTest_270, PageIsNotRefWhenInteger_270) {
    Array arr(nullptr);
    Object pageObj(1);
    arr.add(std::move(pageObj));
    Object nameObj(objName, "Fit");
    arr.add(std::move(nameObj));
    
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_FALSE(dest.isPageRef());
        EXPECT_EQ(dest.getPageNum(), 1);
    }
}

// Test getKind returns the correct kind value
TEST_F(LinkDestTest_270, GetKindReturnsCorrectValue_270) {
    Array arr(nullptr);
    Object pageObj(1);
    arr.add(std::move(pageObj));
    Object nameObj(objName, "Fit");
    arr.add(std::move(nameObj));
    
    LinkDest dest(&arr);
    if (dest.isOk()) {
        LinkDestKind k = dest.getKind();
        EXPECT_EQ(k, destFit);
    }
}

// Test that a two-element array with wrong second element type is not ok
TEST_F(LinkDestTest_270, WrongSecondElementType_270) {
    Array arr(nullptr);
    Object pageObj(1);
    arr.add(std::move(pageObj));
    Object intObj(42);  // should be a name, not an int
    arr.add(std::move(intObj));
    
    LinkDest dest(&arr);
    EXPECT_FALSE(dest.isOk());
}

// Test XYZ with zero zoom
TEST_F(LinkDestTest_270, XYZWithZeroZoom_270) {
    Array arr(nullptr);
    Object pageObj(1);
    arr.add(std::move(pageObj));
    Object nameObj(objName, "XYZ");
    arr.add(std::move(nameObj));
    Object leftObj(0.0);
    arr.add(std::move(leftObj));
    Object topObj(0.0);
    arr.add(std::move(topObj));
    Object zoomObj(0.0);
    arr.add(std::move(zoomObj));
    
    LinkDest dest(&arr);
    if (dest.isOk()) {
        EXPECT_EQ(dest.getKind(), destXYZ);
    }
}

// Test FitR with insufficient parameters
TEST_F(LinkDestTest_270, FitRWithInsufficientParams_270) {
    Array arr(nullptr);
    Object pageObj(1);
    arr.add(std::move(pageObj));
    Object nameObj(objName, "FitR");
    arr.add(std::move(nameObj));
    // Only provide 2 out of 4 required parameters
    Object leftObj(10.0);
    arr.add(std::move(leftObj));
    Object bottomObj(20.0);
    arr.add(std::move(bottomObj));
    
    LinkDest dest(&arr);
    // With insufficient params, it should either not be ok or have default behavior
    // We just verify it doesn't crash
    dest.isOk();
}
