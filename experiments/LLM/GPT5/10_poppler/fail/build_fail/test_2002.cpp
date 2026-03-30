#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "PDFDoc.h"
#include "Dict.h"

class MockPDFDoc : public PDFDoc {
public:
    MockPDFDoc(std::unique_ptr<GooString> fileNameA, const std::optional<GooString>& ownerPassword, 
               const std::optional<GooString>& userPassword, const std::function<void(void)>& xrefReconstructedCallback)
        : PDFDoc(std::move(fileNameA), ownerPassword, userPassword, xrefReconstructedCallback) {}

    MOCK_METHOD(XRef*, getXRef, (), (const, override));
};

TEST_F(PDFDocTest_2002, GetAsIsStampExtGStateDict_NormalOperation_2002) {
    // Arrange
    auto doc = std::make_unique<MockPDFDoc>(std::make_unique<GooString>("test.pdf"), {}, {}, [](){});
    XRef* mockXRef = new XRef();  // Mock or stub this as needed
    EXPECT_CALL(*doc, getXRef()).WillOnce(testing::Return(mockXRef));

    // Act
    Dict* result = getAsIsStampExtGStateDict(doc.get());

    // Assert
    ASSERT_NE(result, nullptr);
    ASSERT_TRUE(result->hasKey("a0"));
    ASSERT_TRUE(result->hasKey("a1"));
    // Further assertions can be added to check the content of the "CA" and "ca" keys.
}

TEST_F(PDFDocTest_2002, GetAsIsStampExtGStateDict_NullDoc_2002) {
    // Act & Assert
    EXPECT_THROW({
        Dict* result = getAsIsStampExtGStateDict(nullptr);
    }, std::invalid_argument);  // Assuming nullptr throws an exception in the actual implementation
}

TEST_F(PDFDocTest_2002, GetAsIsStampExtGStateDict_MissingXRef_2002) {
    // Arrange
    auto doc = std::make_unique<MockPDFDoc>(std::make_unique<GooString>("test.pdf"), {}, {}, [](){});
    EXPECT_CALL(*doc, getXRef()).WillOnce(testing::Return(nullptr));

    // Act & Assert
    EXPECT_THROW({
        Dict* result = getAsIsStampExtGStateDict(doc.get());
    }, std::runtime_error);  // Assuming an error is thrown when XRef is nullptr
}

TEST_F(PDFDocTest_2002, GetAsIsStampExtGStateDict_EmptyXRef_2002) {
    // Arrange
    auto doc = std::make_unique<MockPDFDoc>(std::make_unique<GooString>("test.pdf"), {}, {}, [](){});
    XRef* mockXRef = new XRef();  // Assuming XRef is still valid but empty
    EXPECT_CALL(*doc, getXRef()).WillOnce(testing::Return(mockXRef));

    // Act
    Dict* result = getAsIsStampExtGStateDict(doc.get());

    // Assert
    ASSERT_NE(result, nullptr);
    ASSERT_TRUE(result->hasKey("a0"));
    ASSERT_TRUE(result->hasKey("a1"));
}