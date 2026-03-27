#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "PDFDoc.h"

// Mock class for dependencies
class MockXRef : public XRef {
public:
    MOCK_METHOD(Object, getDocInfoNF, (), (const, override));
};

// Test fixture for PDFDoc
class PDFDocTest_973 : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup mock XRef and PDFDoc
        xrefMock = std::make_unique<MockXRef>();
        pdfDoc = std::make_unique<PDFDoc>();
    }

    std::unique_ptr<PDFDoc> pdfDoc;
    std::unique_ptr<MockXRef> xrefMock;
};

// Test case for the getDocInfoNF function
TEST_F(PDFDocTest_973, GetDocInfoNF_ReturnsCorrectObject_973) {
    // Arrange: Setup expected behavior for the mock
    Object expectedObject;
    EXPECT_CALL(*xrefMock, getDocInfoNF())
        .WillOnce(testing::Return(expectedObject));
    
    // Act: Call the method
    Object result = pdfDoc->getDocInfoNF();
    
    // Assert: Check that the correct object is returned
    EXPECT_EQ(result, expectedObject);
}

// Boundary test case: Call getDocInfoNF with an empty or uninitialized state
TEST_F(PDFDocTest_973, GetDocInfoNF_UninitializedState_973) {
    // No setup for mock as it is uninitialized
    EXPECT_NO_THROW({
        Object result = pdfDoc->getDocInfoNF();
    });
}

// Test case for exception handling, if getDocInfoNF throws an error (e.g., null pointer dereference)
TEST_F(PDFDocTest_973, GetDocInfoNF_ThrowsOnError_973) {
    // Arrange: Simulate an error in the mock
    EXPECT_CALL(*xrefMock, getDocInfoNF())
        .WillOnce(testing::Throw(std::runtime_error("Error fetching doc info")));
    
    // Act & Assert: Expect exception to be thrown
    EXPECT_THROW({
        Object result = pdfDoc->getDocInfoNF();
    }, std::runtime_error);
}

// Verification of external interactions: Ensuring the correct interaction with XRef when calling getDocInfoNF
TEST_F(PDFDocTest_973, GetDocInfoNF_VerifyMockInteraction_973) {
    // Arrange
    Object expectedObject;
    EXPECT_CALL(*xrefMock, getDocInfoNF())
        .WillOnce(testing::Return(expectedObject));

    // Act
    pdfDoc->getDocInfoNF();

    // Assert: Verify that the mock function was called
    testing::Mock::VerifyAndClearExpectations(xrefMock.get());
}