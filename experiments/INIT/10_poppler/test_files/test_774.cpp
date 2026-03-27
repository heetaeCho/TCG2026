#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Annot.h"  // Include the necessary header

// Test fixture for AnnotAppearanceBBox tests
class AnnotAppearanceBBoxTest_774 : public ::testing::Test {
protected:
    AnnotAppearanceBBoxTest_774() : bbox(nullptr) {}

    // Create an instance of AnnotAppearanceBBox before each test
    void SetUp() override {
        PDFRectangle* rect = new PDFRectangle(0.0, 0.0, 10.0, 10.0);
        bbox = new AnnotAppearanceBBox(rect);
    }

    // Clean up after each test
    void TearDown() override {
        delete bbox;
    }

    AnnotAppearanceBBox* bbox;
};

// Test: Normal operation of setBorderWidth
TEST_F(AnnotAppearanceBBoxTest_774, SetBorderWidth_NormalOperation_774) {
    bbox->setBorderWidth(5.0);
    // As borderWidth is private, we assume it's effectively set, but you can add
    // a getter or interaction check if the interface allows. Here we can assert no crash.
    EXPECT_NO_THROW(bbox->setBorderWidth(5.0));
}

// Test: Boundary case for borderWidth setting to 0
TEST_F(AnnotAppearanceBBoxTest_774, SetBorderWidth_Zero_774) {
    bbox->setBorderWidth(0.0);
    EXPECT_NO_THROW(bbox->setBorderWidth(0.0));
}

// Test: Boundary case for borderWidth setting to a very large value
TEST_F(AnnotAppearanceBBoxTest_774, SetBorderWidth_LargeValue_774) {
    bbox->setBorderWidth(1000000.0);
    EXPECT_NO_THROW(bbox->setBorderWidth(1000000.0));
}

// Test: Check boundary values for getBBoxRect method
TEST_F(AnnotAppearanceBBoxTest_774, GetBBoxRect_Boundary_774) {
    const auto bboxRect = bbox->getBBoxRect();
    // Assert that the bounding box values are correctly within the expected limits
    EXPECT_EQ(bboxRect[0], 0.0);  // minX
    EXPECT_EQ(bboxRect[1], 0.0);  // minY
    EXPECT_EQ(bboxRect[2], 10.0); // maxX
    EXPECT_EQ(bboxRect[3], 10.0); // maxY
}

// Test: Extend to a new point and check if bounding box adjusts accordingly
TEST_F(AnnotAppearanceBBoxTest_774, ExtendTo_NewPoint_774) {
    bbox->extendTo(15.0, 20.0);
    const auto bboxRect = bbox->getBBoxRect();
    EXPECT_EQ(bboxRect[2], 15.0); // maxX should now be 15
    EXPECT_EQ(bboxRect[3], 20.0); // maxY should now be 20
}

// Test: Check exceptional case for extending beyond boundary
TEST_F(AnnotAppearanceBBoxTest_774, ExtendTo_InvalidPoint_774) {
    // If the class has specific validation, test for exceptions here
    EXPECT_THROW(bbox->extendTo(-1.0, -1.0), std::out_of_range); // Example of boundary check
}

// Test: Verify no crash when getting page min/max values
TEST_F(AnnotAppearanceBBoxTest_774, GetPageMinMax_774) {
    EXPECT_NO_THROW(bbox->getPageXMin());
    EXPECT_NO_THROW(bbox->getPageYMin());
    EXPECT_NO_THROW(bbox->getPageXMax());
    EXPECT_NO_THROW(bbox->getPageYMax());
}

// Test: Mock external interaction (example with Google Mock)
class MockPDFRectangle : public PDFRectangle {
public:
    MOCK_METHOD(void, someExternalFunction, (), (override));
};

TEST_F(AnnotAppearanceBBoxTest_774, MockExternalInteraction_774) {
    MockPDFRectangle mockRect;
    EXPECT_CALL(mockRect, someExternalFunction()).Times(1);
    
    AnnotAppearanceBBox bbox(&mockRect);
    bbox.setBorderWidth(5.0); // If this triggers some interaction, mock should be called
}