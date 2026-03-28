#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "PDFDoc.h"
#include "Dict.h"
#include "Object.h"

using ::testing::_;
using ::testing::Return;
using ::testing::Mock;

class PDFDocMock : public PDFDoc {
public:
    PDFDocMock() : PDFDoc(nullptr, {}, {}, {}) {}
    MOCK_METHOD(XRef*, getXRef, (), (const, override));
};

class AnnotStampForPublicReleaseTest_2013 : public testing::Test {
protected:
    PDFDocMock docMock;
};

// Normal operation test case: Testing if getForPublicReleaseStampExtGStateDict correctly creates and returns the expected Dict object.
TEST_F(AnnotStampForPublicReleaseTest_2013, getForPublicReleaseStampExtGStateDict_ReturnsExpectedDict_2013) {
    // Arrange
    XRef xrefMock;
    EXPECT_CALL(docMock, getXRef()).WillOnce(Return(&xrefMock));

    // Act
    Dict* result = getForPublicReleaseStampExtGStateDict(&docMock);

    // Assert
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getLength(), 2);  // Expecting two entries in the dictionary
    EXPECT_TRUE(result->hasKey("a0"));
    EXPECT_TRUE(result->hasKey("a1"));
}

// Boundary condition: Testing the behavior when the PDFDoc's getXRef returns a null pointer.
TEST_F(AnnotStampForPublicReleaseTest_2013, getForPublicReleaseStampExtGStateDict_XRefNull_2013) {
    // Arrange
    EXPECT_CALL(docMock, getXRef()).WillOnce(Return(nullptr));

    // Act
    Dict* result = getForPublicReleaseStampExtGStateDict(&docMock);

    // Assert
    ASSERT_EQ(result, nullptr);  // Expecting null result if xref is null
}

// Exceptional/Error case: Test behavior with a null PDFDoc pointer (invalid input).
TEST_F(AnnotStampForPublicReleaseTest_2013, getForPublicReleaseStampExtGStateDict_NullDoc_2013) {
    // Act & Assert
    EXPECT_DEATH({
        Dict* result = getForPublicReleaseStampExtGStateDict(nullptr);
    }, ".*");  // Expecting the code to trigger a crash or error when passed a nullptr
}

// Verification of external interaction: Mocking interaction with getXRef.
TEST_F(AnnotStampForPublicReleaseTest_2013, getForPublicReleaseStampExtGStateDict_VerifyGetXRefCalled_2013) {
    // Arrange
    XRef xrefMock;
    EXPECT_CALL(docMock, getXRef()).WillOnce(Return(&xrefMock));

    // Act
    Dict* result = getForPublicReleaseStampExtGStateDict(&docMock);

    // Assert
    Mock::VerifyAndClearExpectations(&docMock);  // Verifying that the mock method getXRef was called
}