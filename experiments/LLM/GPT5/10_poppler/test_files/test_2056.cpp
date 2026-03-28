#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-annot.h"
#include "poppler-private.h"
#include "PDFRectangle.h"

class PopplerAnnotTest_2056 : public ::testing::Test {
protected:
    PopplerDocument* mockDoc;
    PopplerRectangle* mockRect;

    void SetUp() override {
        // Mock the PopplerDocument and PopplerRectangle objects
        mockDoc = new PopplerDocument();
        mockRect = new PopplerRectangle();
    }

    void TearDown() override {
        // Clean up after each test
        delete mockDoc;
        delete mockRect;
    }
};

// Test case for normal operation of poppler_annot_circle_new
TEST_F(PopplerAnnotTest_2056, poppler_annot_circle_new_NormalOperation_2056) {
    // Arrange: Create a mock rectangle
    mockRect->x2 = 10;
    mockRect->y2 = 20;
    mockRect->x1 = 5;
    mockRect->y1 = 5;

    // Act: Call the function under test
    auto annot = poppler_annot_circle_new(mockDoc, mockRect);

    // Assert: Verify that the returned annotation is of type Circle
    ASSERT_NE(annot, nullptr);
    ASSERT_EQ(annot->getType(), Annot::typeCircle);
}

// Test case for boundary condition where the rectangle has zero area
TEST_F(PopplerAnnotTest_2056, poppler_annot_circle_new_ZeroAreaRectangle_2056) {
    // Arrange: Create a rectangle with zero area
    mockRect->x1 = 5;
    mockRect->y1 = 5;
    mockRect->x2 = 5;
    mockRect->y2 = 5;

    // Act: Call the function under test
    auto annot = poppler_annot_circle_new(mockDoc, mockRect);

    // Assert: The annotation should still be created, but we can check that it's valid
    ASSERT_NE(annot, nullptr);
    ASSERT_EQ(annot->getType(), Annot::typeCircle);
}

// Test case for invalid document input
TEST_F(PopplerAnnotTest_2056, poppler_annot_circle_new_InvalidDocument_2056) {
    // Arrange: Create a null document and rectangle
    mockDoc = nullptr;
    mockRect->x1 = 5;
    mockRect->y1 = 5;
    mockRect->x2 = 10;
    mockRect->y2 = 20;

    // Act & Assert: Expect a nullptr returned since the document is invalid
    auto annot = poppler_annot_circle_new(mockDoc, mockRect);
    ASSERT_EQ(annot, nullptr);
}

// Test case for an empty rectangle (where x1 == x2 and y1 == y2)
TEST_F(PopplerAnnotTest_2056, poppler_annot_circle_new_EmptyRectangle_2056) {
    // Arrange: Create an empty rectangle
    mockRect->x1 = 0;
    mockRect->y1 = 0;
    mockRect->x2 = 0;
    mockRect->y2 = 0;

    // Act: Call the function under test
    auto annot = poppler_annot_circle_new(mockDoc, mockRect);

    // Assert: The annotation should still be created with an empty rectangle
    ASSERT_NE(annot, nullptr);
    ASSERT_EQ(annot->getType(), Annot::typeCircle);
}

// Test case to verify external interaction with the rectangle clipping logic
TEST_F(PopplerAnnotTest_2056, poppler_annot_circle_new_VerifyRectangleClipping_2056) {
    // Arrange: Mock a document and rectangle that should clip to a specific range
    mockRect->x1 = 5;
    mockRect->y1 = 5;
    mockRect->x2 = 15;
    mockRect->y2 = 15;

    // Mock the clipTo functionality of PDFRectangle
    PDFRectangle rect(mockRect->x1, mockRect->y1, mockRect->x2, mockRect->y2);
    EXPECT_CALL(rect, clipTo(testing::_)).Times(1);

    // Act: Call the function under test
    auto annot = poppler_annot_circle_new(mockDoc, mockRect);

    // Assert: Check the interaction with the clipping method (as per our mock)
    ASSERT_NE(annot, nullptr);
    ASSERT_EQ(annot->getType(), Annot::typeCircle);
}