#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler/annot_stamp_departmental.h"
#include "poppler/Dict.h"
#include "poppler/PDFDoc.h"

// Mock PDFDoc class
class MockPDFDoc : public PDFDoc {
public:
    MockPDFDoc() : PDFDoc(nullptr, std::nullopt, std::nullopt, nullptr) {}

    MOCK_METHOD(XRef*, getXRef, (), (const, override));
};

// Test suite for getDepartmentalStampExtGStateDict function
TEST_F(AnnotStampDepartmentalTest_2004, GetDepartmentalStampExtGStateDict_NormalOperation_2004) {
    // Arrange
    MockPDFDoc mockDoc;
    XRef* mockXRef = new XRef();
    EXPECT_CALL(mockDoc, getXRef()).WillOnce(testing::Return(mockXRef));

    // Act
    Dict* extGStateDict = getDepartmentalStampExtGStateDict(&mockDoc);

    // Assert
    ASSERT_NE(extGStateDict, nullptr);
    EXPECT_TRUE(extGStateDict->hasKey("a0"));
    EXPECT_TRUE(extGStateDict->hasKey("a1"));
    delete extGStateDict; // Clean up
}

TEST_F(AnnotStampDepartmentalTest_2004, GetDepartmentalStampExtGStateDict_EmptyXRef_2004) {
    // Arrange
    MockPDFDoc mockDoc;
    XRef* mockXRef = nullptr;  // Simulate null XRef
    EXPECT_CALL(mockDoc, getXRef()).WillOnce(testing::Return(mockXRef));

    // Act
    Dict* extGStateDict = getDepartmentalStampExtGStateDict(&mockDoc);

    // Assert
    ASSERT_NE(extGStateDict, nullptr);
    EXPECT_FALSE(extGStateDict->hasKey("a0"));
    EXPECT_FALSE(extGStateDict->hasKey("a1"));
    delete extGStateDict; // Clean up
}

TEST_F(AnnotStampDepartmentalTest_2004, GetDepartmentalStampExtGStateDict_ValidXRef_2004) {
    // Arrange
    MockPDFDoc mockDoc;
    XRef* mockXRef = new XRef();
    EXPECT_CALL(mockDoc, getXRef()).WillOnce(testing::Return(mockXRef));

    // Act
    Dict* extGStateDict = getDepartmentalStampExtGStateDict(&mockDoc);

    // Assert
    ASSERT_NE(extGStateDict, nullptr);
    EXPECT_TRUE(extGStateDict->hasKey("a0"));
    EXPECT_TRUE(extGStateDict->hasKey("a1"));
    delete extGStateDict; // Clean up
}

TEST_F(AnnotStampDepartmentalTest_2004, GetDepartmentalStampExtGStateDict_ExceptionHandling_2004) {
    // Arrange
    MockPDFDoc mockDoc;
    EXPECT_CALL(mockDoc, getXRef()).WillOnce(testing::Throw(std::runtime_error("XRef not available")));

    // Act & Assert
    try {
        Dict* extGStateDict = getDepartmentalStampExtGStateDict(&mockDoc);
        FAIL() << "Expected exception not thrown.";
    } catch (const std::runtime_error& e) {
        EXPECT_STREQ(e.what(), "XRef not available");
    }
}

TEST_F(AnnotStampDepartmentalTest_2004, GetDepartmentalStampExtGStateDict_VerifyExternalInteractions_2004) {
    // Arrange
    MockPDFDoc mockDoc;
    XRef* mockXRef = new XRef();
    EXPECT_CALL(mockDoc, getXRef()).WillOnce(testing::Return(mockXRef));

    // Act
    Dict* extGStateDict = getDepartmentalStampExtGStateDict(&mockDoc);

    // Assert
    ASSERT_NE(extGStateDict, nullptr);
    delete extGStateDict; // Clean up
}