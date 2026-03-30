#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "PDFDoc.h"
#include "XRef.h"

// Mocking the XRef class as it is a dependency of PDFDoc.
class MockXRef : public XRef {
public:
    MOCK_METHOD(bool, okToPrint, (bool ignoreOwnerPW), (const, override));
    MOCK_METHOD(bool, okToPrintHighRes, (bool ignoreOwnerPW), (const, override));
    MOCK_METHOD(bool, okToChange, (bool ignoreOwnerPW), (const, override));
    MOCK_METHOD(bool, okToCopy, (bool ignoreOwnerPW), (const, override));
    MOCK_METHOD(bool, okToAddNotes, (bool ignoreOwnerPW), (const, override));
    MOCK_METHOD(bool, okToFillForm, (bool ignoreOwnerPW), (const, override));
    MOCK_METHOD(bool, okToAccessibility, (bool ignoreOwnerPW), (const, override));
    MOCK_METHOD(bool, okToAssemble, (bool ignoreOwnerPW), (const, override));
};

// Test Fixture for PDFDoc tests
class PDFDocTest : public ::testing::Test {
protected:
    // Mocking the XRef for the PDFDoc class.
    std::unique_ptr<MockXRef> mockXRef;
    std::unique_ptr<PDFDoc> pdfDoc;

    void SetUp() override {
        mockXRef = std::make_unique<MockXRef>();
        pdfDoc = std::make_unique<PDFDoc>(); // Assuming PDFDoc constructor doesn't require parameters for this mock
    }

    void TearDown() override {
        pdfDoc.reset();
        mockXRef.reset();
    }
};

// TEST_ID: 964

TEST_F(PDFDocTest, okToPrint_Valid) {
    EXPECT_CALL(*mockXRef, okToPrint(false)).WillOnce(testing::Return(true));

    bool result = pdfDoc->okToPrint(false);
    EXPECT_TRUE(result);
}

TEST_F(PDFDocTest, okToPrintHighRes_Valid) {
    EXPECT_CALL(*mockXRef, okToPrintHighRes(false)).WillOnce(testing::Return(true));

    bool result = pdfDoc->okToPrintHighRes(false);
    EXPECT_TRUE(result);
}

TEST_F(PDFDocTest, okToPrint_InvalidOwnerPW) {
    EXPECT_CALL(*mockXRef, okToPrint(true)).WillOnce(testing::Return(false));

    bool result = pdfDoc->okToPrint(true);
    EXPECT_FALSE(result);
}

TEST_F(PDFDocTest, okToChange_Valid) {
    EXPECT_CALL(*mockXRef, okToChange(false)).WillOnce(testing::Return(true));

    bool result = pdfDoc->okToChange(false);
    EXPECT_TRUE(result);
}

TEST_F(PDFDocTest, okToCopy_Valid) {
    EXPECT_CALL(*mockXRef, okToCopy(false)).WillOnce(testing::Return(true));

    bool result = pdfDoc->okToCopy(false);
    EXPECT_TRUE(result);
}

TEST_F(PDFDocTest, okToAddNotes_Valid) {
    EXPECT_CALL(*mockXRef, okToAddNotes(false)).WillOnce(testing::Return(true));

    bool result = pdfDoc->okToAddNotes(false);
    EXPECT_TRUE(result);
}

TEST_F(PDFDocTest, okToFillForm_Valid) {
    EXPECT_CALL(*mockXRef, okToFillForm(false)).WillOnce(testing::Return(true));

    bool result = pdfDoc->okToFillForm(false);
    EXPECT_TRUE(result);
}

TEST_F(PDFDocTest, okToAccessibility_Valid) {
    EXPECT_CALL(*mockXRef, okToAccessibility(false)).WillOnce(testing::Return(true));

    bool result = pdfDoc->okToAccessibility(false);
    EXPECT_TRUE(result);
}

TEST_F(PDFDocTest, okToAssemble_Valid) {
    EXPECT_CALL(*mockXRef, okToAssemble(false)).WillOnce(testing::Return(true));

    bool result = pdfDoc->okToAssemble(false);
    EXPECT_TRUE(result);
}

TEST_F(PDFDocTest, okToPrint_ExceptionalCase) {
    EXPECT_CALL(*mockXRef, okToPrint(false)).WillOnce(testing::Return(false));

    bool result = pdfDoc->okToPrint(false);
    EXPECT_FALSE(result);
}