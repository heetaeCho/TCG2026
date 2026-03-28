#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Annot.h" // Include the header for the Annot class

// Mock classes for any external dependencies (if needed)
class MockPDFDoc : public PDFDoc {
public:
    MOCK_METHOD(PDFDoc*, getDoc, (), (const));
};

// Unit tests for Annot class
TEST_F(AnnotTest_778, GetDoc_ReturnsPDFDoc_778) {
    // Arrange
    MockPDFDoc mockDoc;
    Annot annot(&mockDoc, nullptr);

    // Act
    PDFDoc* result = annot.getDoc();

    // Assert
    ASSERT_EQ(result, &mockDoc);
}

TEST_F(AnnotTest_778, GetRect_ValidCoordinates_778) {
    // Arrange
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    Annot annot(nullptr, nullptr);
    annot.setRect(rect);

    double x1, y1, x2, y2;

    // Act
    annot.getRect(&x1, &y1, &x2, &y2);

    // Assert
    ASSERT_EQ(x1, 0.0);
    ASSERT_EQ(y1, 0.0);
    ASSERT_EQ(x2, 10.0);
    ASSERT_EQ(y2, 10.0);
}

TEST_F(AnnotTest_778, GetDoc_NullPointer_778) {
    // Arrange
    Annot annot(nullptr, nullptr);

    // Act
    PDFDoc* result = annot.getDoc();

    // Assert
    ASSERT_EQ(result, nullptr);
}

TEST_F(AnnotTest_778, SetName_ValidName_778) {
    // Arrange
    Annot annot(nullptr, nullptr);
    GooString newName("Test Name");

    // Act
    annot.setName(&newName);

    // Assert
    ASSERT_EQ(*annot.getName(), newName);
}

TEST_F(AnnotTest_778, SetModified_ValidModified_778) {
    // Arrange
    Annot annot(nullptr, nullptr);
    GooString newModified("2023-02-15");

    // Act
    annot.setModified(std::make_unique<GooString>(newModified));

    // Assert
    ASSERT_EQ(*annot.getModified(), newModified);
}

TEST_F(AnnotTest_778, SetColor_ValidColor_778) {
    // Arrange
    Annot annot(nullptr, nullptr);
    std::unique_ptr<AnnotColor> newColor = std::make_unique<AnnotColor>();

    // Act
    annot.setColor(std::move(newColor));

    // Assert
    ASSERT_TRUE(annot.getColor() != nullptr);
}

TEST_F(AnnotTest_778, SetBorder_ValidBorder_778) {
    // Arrange
    Annot annot(nullptr, nullptr);
    std::unique_ptr<AnnotBorder> newBorder = std::make_unique<AnnotBorder>();

    // Act
    annot.setBorder(std::move(newBorder));

    // Assert
    ASSERT_TRUE(annot.getBorder() != nullptr);
}

TEST_F(AnnotTest_778, InRect_InsideRect_778) {
    // Arrange
    Annot annot(nullptr, nullptr);
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    annot.setRect(rect);

    // Act & Assert
    ASSERT_TRUE(annot.inRect(5.0, 5.0)); // Inside the rectangle
}

TEST_F(AnnotTest_778, InRect_OutsideRect_778) {
    // Arrange
    Annot annot(nullptr, nullptr);
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    annot.setRect(rect);

    // Act & Assert
    ASSERT_FALSE(annot.inRect(15.0, 15.0)); // Outside the rectangle
}

TEST_F(AnnotTest_778, GetHasRef_True_778) {
    // Arrange
    Annot annot(nullptr, nullptr);
    annot.setHasRef(true);

    // Act
    bool result = annot.getHasRef();

    // Assert
    ASSERT_TRUE(result);
}

TEST_F(AnnotTest_778, GetHasRef_False_778) {
    // Arrange
    Annot annot(nullptr, nullptr);
    annot.setHasRef(false);

    // Act
    bool result = annot.getHasRef();

    // Assert
    ASSERT_FALSE(result);
}

TEST_F(AnnotTest_778, IsOk_ValidAnnot_778) {
    // Arrange
    Annot annot(nullptr, nullptr);

    // Act
    bool result = annot.isOk();

    // Assert
    ASSERT_TRUE(result);
}

TEST_F(AnnotTest_778, GetTreeKey_ValidTreeKey_778) {
    // Arrange
    Annot annot(nullptr, nullptr);
    int expectedKey = 123;
    annot.setTreeKey(expectedKey);

    // Act
    int result = annot.getTreeKey();

    // Assert
    ASSERT_EQ(result, expectedKey);
}

TEST_F(AnnotTest_778, GetType_ValidAnnotSubtype_778) {
    // Arrange
    Annot annot(nullptr, nullptr);
    AnnotSubtype expectedType = AnnotSubtype::Text;

    // Act
    AnnotSubtype result = annot.getType();

    // Assert
    ASSERT_EQ(result, expectedType);
}

TEST_F(AnnotTest_778, GetAppearance_ValidAppearance_778) {
    // Arrange
    Annot annot(nullptr, nullptr);
    Object expectedAppearance;

    // Act
    Object result = annot.getAppearance();

    // Assert
    ASSERT_EQ(result, expectedAppearance);
}

TEST_F(AnnotTest_778, SetNewAppearance_ValidAppearance_778) {
    // Arrange
    Annot annot(nullptr, nullptr);
    Object newAppearance;

    // Act
    annot.setNewAppearance(std::move(newAppearance));

    // Assert
    ASSERT_TRUE(annot.getAppearance().isValid());
}