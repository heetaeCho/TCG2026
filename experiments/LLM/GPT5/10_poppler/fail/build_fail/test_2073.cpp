#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/glib/poppler-annot.cc"
#include "./TestProjects/poppler/poppler/PDFRectangle.h"
#include "./TestProjects/poppler/glib/poppler-page.h"
#include "./TestProjects/poppler/glib/poppler-private.h"

// Mocks for external dependencies
class MockAnnot {
public:
    MOCK_METHOD(PDFRectangle, getRect, (), (const));
};

class MockPopplerAnnot {
public:
    std::shared_ptr<MockAnnot> annot;

    MockPopplerAnnot() {
        annot = std::make_shared<MockAnnot>();
    }
};

// Test fixture for poppler_annot_get_rectangle
class PopplerAnnotTest_2073 : public ::testing::Test {
protected:
    MockPopplerAnnot mock_annot;
    PopplerRectangle poppler_rect;

    // This helper method can be called for each test to ensure proper setup
    void callPopplerAnnotGetRectangle(PopplerAnnot *poppler_annot) {
        poppler_annot_get_rectangle(poppler_annot, &poppler_rect);
    }
};

// Normal operation test
TEST_F(PopplerAnnotTest_2073, NormalOperation_2073) {
    PopplerAnnot poppler_annot;
    MockPopplerAnnot mock_annot;
    PDFRectangle expected_rect(1.0, 2.0, 3.0, 4.0);

    // Mock behavior: annot's getRect() returns a rectangle
    EXPECT_CALL(*mock_annot.annot, getRect())
        .WillOnce(testing::Return(expected_rect));

    // Call the function and check the result
    callPopplerAnnotGetRectangle(&poppler_annot);
    
    EXPECT_DOUBLE_EQ(poppler_rect.x1, expected_rect.x1);
    EXPECT_DOUBLE_EQ(poppler_rect.y1, expected_rect.y1);
    EXPECT_DOUBLE_EQ(poppler_rect.x2, expected_rect.x2);
    EXPECT_DOUBLE_EQ(poppler_rect.y2, expected_rect.y2);
}

// Boundary condition: empty rectangle
TEST_F(PopplerAnnotTest_2073, EmptyRectangle_2073) {
    PopplerAnnot poppler_annot;
    MockPopplerAnnot mock_annot;
    PDFRectangle empty_rect(0.0, 0.0, 0.0, 0.0);

    // Mock behavior: annot's getRect() returns an empty rectangle
    EXPECT_CALL(*mock_annot.annot, getRect())
        .WillOnce(testing::Return(empty_rect));

    // Call the function and check the result
    callPopplerAnnotGetRectangle(&poppler_annot);

    EXPECT_DOUBLE_EQ(poppler_rect.x1, empty_rect.x1);
    EXPECT_DOUBLE_EQ(poppler_rect.y1, empty_rect.y1);
    EXPECT_DOUBLE_EQ(poppler_rect.x2, empty_rect.x2);
    EXPECT_DOUBLE_EQ(poppler_rect.y2, empty_rect.y2);
}

// Exceptional case: poppler_annot is null
TEST_F(PopplerAnnotTest_2073, NullPopplerAnnot_2073) {
    PopplerAnnot *poppler_annot = nullptr;

    // Call the function with a null pointer and ensure it does not crash
    EXPECT_NO_THROW(callPopplerAnnotGetRectangle(poppler_annot));
}

// Boundary condition: poppler_rect has negative values after crop box subtraction
TEST_F(PopplerAnnotTest_2073, NegativeValues_2073) {
    PopplerAnnot poppler_annot;
    MockPopplerAnnot mock_annot;
    PDFRectangle rect(5.0, 5.0, 3.0, 3.0);  // After crop box subtraction, x2 < x1, y2 < y1

    // Mock behavior: annot's getRect() returns a rectangle that causes negative values
    EXPECT_CALL(*mock_annot.annot, getRect())
        .WillOnce(testing::Return(rect));

    // Call the function and check the result
    callPopplerAnnotGetRectangle(&poppler_annot);

    // Check the outcome, ensuring no crash or undefined behavior
    EXPECT_DOUBLE_EQ(poppler_rect.x1, -2.0);
    EXPECT_DOUBLE_EQ(poppler_rect.y1, -2.0);
    EXPECT_DOUBLE_EQ(poppler_rect.x2, -2.0);
    EXPECT_DOUBLE_EQ(poppler_rect.y2, -2.0);
}

// Boundary condition: crop box is zeroed
TEST_F(PopplerAnnotTest_2073, ZeroCropBox_2073) {
    PopplerAnnot poppler_annot;
    MockPopplerAnnot mock_annot;
    PDFRectangle rect(10.0, 10.0, 20.0, 20.0);
    PDFRectangle zerobox(0.0, 0.0, 0.0, 0.0);

    // Mock behavior: annot's getRect() returns a normal rectangle
    EXPECT_CALL(*mock_annot.annot, getRect())
        .WillOnce(testing::Return(rect));

    // Mock behavior for crop box: return a zeroed crop box
    EXPECT_CALL(*mock_annot.annot, getCropBox())
        .WillOnce(testing::Return(zerobox));

    // Call the function and check the result
    callPopplerAnnotGetRectangle(&poppler_annot);

    EXPECT_DOUBLE_EQ(poppler_rect.x1, rect.x1);
    EXPECT_DOUBLE_EQ(poppler_rect.y1, rect.y1);
    EXPECT_DOUBLE_EQ(poppler_rect.x2, rect.x2);
    EXPECT_DOUBLE_EQ(poppler_rect.y2, rect.y2);
}

// Boundary condition: crop box is the same as annot's rectangle
TEST_F(PopplerAnnotTest_2073, IdenticalCropBox_2073) {
    PopplerAnnot poppler_annot;
    MockPopplerAnnot mock_annot;
    PDFRectangle rect(5.0, 5.0, 10.0, 10.0);
    PDFRectangle crop_box(5.0, 5.0, 10.0, 10.0);

    // Mock behavior: annot's getRect() returns the rectangle
    EXPECT_CALL(*mock_annot.annot, getRect())
        .WillOnce(testing::Return(rect));

    // Mock behavior for crop box: return a rectangle identical to annot's
    EXPECT_CALL(*mock_annot.annot, getCropBox())
        .WillOnce(testing::Return(crop_box));

    // Call the function and check the result
    callPopplerAnnotGetRectangle(&poppler_annot);

    // Expect a zeroed poppler_rect, as crop box and annot's rectangle are identical
    EXPECT_DOUBLE_EQ(poppler_rect.x1, 0.0);
    EXPECT_DOUBLE_EQ(poppler_rect.y1, 0.0);
    EXPECT_DOUBLE_EQ(poppler_rect.x2, 0.0);
    EXPECT_DOUBLE_EQ(poppler_rect.y2, 0.0);
}