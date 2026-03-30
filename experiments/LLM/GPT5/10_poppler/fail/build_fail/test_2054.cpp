#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/glib/poppler-annot.cc"
#include "./TestProjects/poppler/poppler/PDFRectangle.h"
#include "./TestProjects/poppler/glib/poppler-page.h"
#include "./TestProjects/poppler/glib/poppler-private.h"

// Mock classes for the dependencies
class MockPopplerDocument {
public:
    MOCK_METHOD(int, get_document_id, (), (const));
};

class MockPopplerRectangle {
public:
    MOCK_METHOD(double, get_x1, (), (const));
    MOCK_METHOD(double, get_y1, (), (const));
    MOCK_METHOD(double, get_x2, (), (const));
    MOCK_METHOD(double, get_y2, (), (const));
};

class MockPopplerPoint {
public:
    MOCK_METHOD(double, get_x, (), (const));
    MOCK_METHOD(double, get_y, (), (const));
};

// Test fixture class for setting up common test objects
class PopplerAnnotLineTest : public ::testing::Test {
protected:
    MockPopplerDocument mock_doc;
    MockPopplerRectangle mock_rect;
    MockPopplerPoint mock_start;
    MockPopplerPoint mock_end;

    // Create a shared pointer to a PopplerAnnotLine object
    PopplerAnnot* create_poppler_annot_line() {
        return poppler_annot_line_new(&mock_doc, &mock_rect, &mock_start, &mock_end);
    }
};

// TEST_ID 2054 - Normal operation: PopplerAnnotLine creation
TEST_F(PopplerAnnotLineTest, NormalOperation_2054) {
    // Set up mock behaviors
    EXPECT_CALL(mock_doc, get_document_id()).WillOnce(testing::Return(1));
    EXPECT_CALL(mock_rect, get_x1()).WillOnce(testing::Return(0.0));
    EXPECT_CALL(mock_rect, get_y1()).WillOnce(testing::Return(0.0));
    EXPECT_CALL(mock_rect, get_x2()).WillOnce(testing::Return(10.0));
    EXPECT_CALL(mock_rect, get_y2()).WillOnce(testing::Return(10.0));
    EXPECT_CALL(mock_start, get_x()).WillOnce(testing::Return(0.0));
    EXPECT_CALL(mock_start, get_y()).WillOnce(testing::Return(0.0));
    EXPECT_CALL(mock_end, get_x()).WillOnce(testing::Return(10.0));
    EXPECT_CALL(mock_end, get_y()).WillOnce(testing::Return(10.0));

    // Call the function
    PopplerAnnot* annot = create_poppler_annot_line();

    // Check if the PopplerAnnot object is not null
    ASSERT_NE(annot, nullptr);
}

// TEST_ID 2055 - Boundary condition: Empty rectangle
TEST_F(PopplerAnnotLineTest, EmptyRectangle_2055) {
    // Set up mock behaviors for empty rectangle
    EXPECT_CALL(mock_doc, get_document_id()).WillOnce(testing::Return(1));
    EXPECT_CALL(mock_rect, get_x1()).WillOnce(testing::Return(0.0));
    EXPECT_CALL(mock_rect, get_y1()).WillOnce(testing::Return(0.0));
    EXPECT_CALL(mock_rect, get_x2()).WillOnce(testing::Return(0.0));
    EXPECT_CALL(mock_rect, get_y2()).WillOnce(testing::Return(0.0));
    EXPECT_CALL(mock_start, get_x()).WillOnce(testing::Return(0.0));
    EXPECT_CALL(mock_start, get_y()).WillOnce(testing::Return(0.0));
    EXPECT_CALL(mock_end, get_x()).WillOnce(testing::Return(0.0));
    EXPECT_CALL(mock_end, get_y()).WillOnce(testing::Return(0.0));

    // Call the function
    PopplerAnnot* annot = create_poppler_annot_line();

    // Check if the PopplerAnnot object is still created, even with an empty rectangle
    ASSERT_NE(annot, nullptr);
}

// TEST_ID 2056 - Boundary condition: Large rectangle
TEST_F(PopplerAnnotLineTest, LargeRectangle_2056) {
    // Set up mock behaviors for large rectangle
    EXPECT_CALL(mock_doc, get_document_id()).WillOnce(testing::Return(1));
    EXPECT_CALL(mock_rect, get_x1()).WillOnce(testing::Return(0.0));
    EXPECT_CALL(mock_rect, get_y1()).WillOnce(testing::Return(0.0));
    EXPECT_CALL(mock_rect, get_x2()).WillOnce(testing::Return(10000.0));
    EXPECT_CALL(mock_rect, get_y2()).WillOnce(testing::Return(10000.0));
    EXPECT_CALL(mock_start, get_x()).WillOnce(testing::Return(0.0));
    EXPECT_CALL(mock_start, get_y()).WillOnce(testing::Return(0.0));
    EXPECT_CALL(mock_end, get_x()).WillOnce(testing::Return(10000.0));
    EXPECT_CALL(mock_end, get_y()).WillOnce(testing::Return(10000.0));

    // Call the function
    PopplerAnnot* annot = create_poppler_annot_line();

    // Check if the PopplerAnnot object is created
    ASSERT_NE(annot, nullptr);
}

// TEST_ID 2057 - Exceptional case: Null document
TEST_F(PopplerAnnotLineTest, NullDocument_2057) {
    // Set up mock behaviors with null document
    EXPECT_CALL(mock_rect, get_x1()).WillOnce(testing::Return(0.0));
    EXPECT_CALL(mock_rect, get_y1()).WillOnce(testing::Return(0.0));
    EXPECT_CALL(mock_rect, get_x2()).WillOnce(testing::Return(10.0));
    EXPECT_CALL(mock_rect, get_y2()).WillOnce(testing::Return(10.0));
    EXPECT_CALL(mock_start, get_x()).WillOnce(testing::Return(0.0));
    EXPECT_CALL(mock_start, get_y()).WillOnce(testing::Return(0.0));
    EXPECT_CALL(mock_end, get_x()).WillOnce(testing::Return(10.0));
    EXPECT_CALL(mock_end, get_y()).WillOnce(testing::Return(10.0));

    // Call the function with a null document
    PopplerAnnot* annot = poppler_annot_line_new(nullptr, &mock_rect, &mock_start, &mock_end);

    // Ensure the returned annot is null, as document is null
    ASSERT_EQ(annot, nullptr);
}