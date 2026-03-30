#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/PDFDoc.h"
#include "./TestProjects/poppler/poppler/XRef.h"

// Mock class for testing the interaction with XRef
class MockXRef : public XRef {
public:
    MOCK_METHOD(bool, okToAssemble, (bool ignoreOwnerPW), (const, override));
};

// Test fixture class for PDFDoc tests
class PDFDocTest : public ::testing::Test {
protected:
    std::unique_ptr<PDFDoc> pdfDoc;
    std::unique_ptr<MockXRef> mockXRef;

    void SetUp() override {
        // Mocking XRef object used in PDFDoc constructor
        mockXRef = std::make_unique<MockXRef>();
        pdfDoc = std::make_unique<PDFDoc>(std::move(mockXRef));
    }
};

// Test the okToAssemble method with default behavior
TEST_F(PDFDocTest, OkToAssembleNormal_971) {
    // Arrange
    bool ignoreOwnerPW = false;
    EXPECT_CALL(*mockXRef, okToAssemble(ignoreOwnerPW)).WillOnce(testing::Return(true));

    // Act
    bool result = pdfDoc->okToAssemble(ignoreOwnerPW);

    // Assert
    EXPECT_TRUE(result);
}

// Test the okToAssemble method with the ignoreOwnerPW flag
TEST_F(PDFDocTest, OkToAssembleWithIgnoreOwnerPW_972) {
    // Arrange
    bool ignoreOwnerPW = true;
    EXPECT_CALL(*mockXRef, okToAssemble(ignoreOwnerPW)).WillOnce(testing::Return(false));

    // Act
    bool result = pdfDoc->okToAssemble(ignoreOwnerPW);

    // Assert
    EXPECT_FALSE(result);
}

// Test error case when okToAssemble fails
TEST_F(PDFDocTest, OkToAssembleError_973) {
    // Arrange
    bool ignoreOwnerPW = false;
    EXPECT_CALL(*mockXRef, okToAssemble(ignoreOwnerPW)).WillOnce(testing::Return(false));

    // Act
    bool result = pdfDoc->okToAssemble(ignoreOwnerPW);

    // Assert
    EXPECT_FALSE(result);
}