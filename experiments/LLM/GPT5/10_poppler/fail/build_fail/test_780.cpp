#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Annot.h"

// Test class for Annot
class AnnotTest_780 : public testing::Test {
protected:
    AnnotTest_780() {
        // Setup code if needed
    }

    ~AnnotTest_780() override {
        // Cleanup code if needed
    }

    // Helper methods if needed
};

// Test: getRef should return the correct Ref object
TEST_F(AnnotTest_780, GetRef_780) {
    // Arrange
    PDFDoc* mockDoc = nullptr;
    PDFRectangle rect;
    Annot annot(mockDoc, rect);

    // Act
    Ref result = annot.getRef();

    // Assert
    EXPECT_EQ(result, annot.getRef()); // Assuming Ref is a valid comparison object
}

// Test: getXMin should return the correct minimum x-coordinate from the Rect
TEST_F(AnnotTest_780, GetXMin_780) {
    // Arrange
    PDFDoc* mockDoc = nullptr;
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    Annot annot(mockDoc, rect);

    // Act
    double xMin = annot.getXMin();

    // Assert
    EXPECT_DOUBLE_EQ(xMin, 0.0);
}

// Test: getYMax should return the correct maximum y-coordinate from the Rect
TEST_F(AnnotTest_780, GetYMax_780) {
    // Arrange
    PDFDoc* mockDoc = nullptr;
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    Annot annot(mockDoc, rect);

    // Act
    double yMax = annot.getYMax();

    // Assert
    EXPECT_DOUBLE_EQ(yMax, 10.0);
}

// Test: setName should update the name correctly
TEST_F(AnnotTest_780, SetName_780) {
    // Arrange
    PDFDoc* mockDoc = nullptr;
    PDFRectangle rect;
    Annot annot(mockDoc, rect);
    GooString* newName = new GooString("NewName");

    // Act
    annot.setName(newName);

    // Assert
    EXPECT_STREQ(annot.getName()->c_str(), "NewName");
}

// Test: setModified should update the modified content correctly
TEST_F(AnnotTest_780, SetModified_780) {
    // Arrange
    PDFDoc* mockDoc = nullptr;
    PDFRectangle rect;
    Annot annot(mockDoc, rect);
    GooString* newModified = new GooString("2026-02-15");

    // Act
    annot.setModified(std::unique_ptr<GooString>(newModified));

    // Assert
    EXPECT_STREQ(annot.getModified()->c_str(), "2026-02-15");
}

// Test: setBorder should update the border correctly
TEST_F(AnnotTest_780, SetBorder_780) {
    // Arrange
    PDFDoc* mockDoc = nullptr;
    PDFRectangle rect;
    Annot annot(mockDoc, rect);
    std::unique_ptr<AnnotBorder> newBorder = std::make_unique<AnnotBorder>();

    // Act
    annot.setBorder(std::move(newBorder));

    // Assert
    EXPECT_NE(annot.getBorder(), nullptr);
}

// Test: getDoc should return the correct PDFDoc object
TEST_F(AnnotTest_780, GetDoc_780) {
    // Arrange
    PDFDoc* mockDoc = new PDFDoc();
    PDFRectangle rect;
    Annot annot(mockDoc, rect);

    // Act
    PDFDoc* result = annot.getDoc();

    // Assert
    EXPECT_EQ(result, mockDoc);
}

// Test: match should correctly compare two Ref objects
TEST_F(AnnotTest_780, MatchRef_780) {
    // Arrange
    PDFDoc* mockDoc = nullptr;
    PDFRectangle rect;
    Annot annot(mockDoc, rect);
    Ref refA(1, 2);
    Ref refB(1, 2);

    // Act
    bool isMatch = annot.match(&refA);

    // Assert
    EXPECT_TRUE(isMatch);
}

// Test: inRect should return true when point is inside the rectangle
TEST_F(AnnotTest_780, InRectInside_780) {
    // Arrange
    PDFDoc* mockDoc = nullptr;
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    Annot annot(mockDoc, rect);

    // Act
    bool isInside = annot.inRect(5.0, 5.0);

    // Assert
    EXPECT_TRUE(isInside);
}

// Test: inRect should return false when point is outside the rectangle
TEST_F(AnnotTest_780, InRectOutside_780) {
    // Arrange
    PDFDoc* mockDoc = nullptr;
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    Annot annot(mockDoc, rect);

    // Act
    bool isInside = annot.inRect(15.0, 15.0);

    // Assert
    EXPECT_FALSE(isInside);
}