#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/annot_stamp_top_secret.h"
#include "./TestProjects/poppler/poppler/Dict.h"
#include "./TestProjects/poppler/poppler/PDFDoc.h"

// Mocks for external dependencies
class MockPDFDoc : public PDFDoc {
public:
    MockPDFDoc() : PDFDoc(nullptr, nullptr, nullptr) {}
    MOCK_METHOD(XRef*, getXRef, (), (const, override));
};

// Test case for getTopSecretStampExtGStateDict
TEST_F(TopSecretStampTest_2012, getTopSecretStampExtGStateDict_CreatesExpectedDict_2012) {
    // Arrange
    MockPDFDoc mockDoc;
    XRef* mockXRef = new XRef();
    EXPECT_CALL(mockDoc, getXRef()).WillOnce(testing::Return(mockXRef));

    // Act
    Dict* extGStateDict = getTopSecretStampExtGStateDict(&mockDoc);

    // Assert
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Dict = extGStateDict->lookup("a0", 0);
    ASSERT_TRUE(a0Dict.isDict());

    Object a1Dict = extGStateDict->lookup("a1", 0);
    ASSERT_TRUE(a1Dict.isDict());

    // Additional checks for values in a0 and a1 dictionaries
    Dict* dictA0 = a0Dict.getDict();
    ASSERT_EQ(dictA0->lookup("CA", 0).getFloat(), 0.588235);
    ASSERT_EQ(dictA0->lookup("ca", 0).getFloat(), 0.588235);

    Dict* dictA1 = a1Dict.getDict();
    ASSERT_EQ(dictA1->lookup("CA", 0).getFloat(), 1);
    ASSERT_EQ(dictA1->lookup("ca", 0).getFloat(), 1);

    // Cleanup
    delete extGStateDict;
}

TEST_F(TopSecretStampTest_2012, getTopSecretStampExtGStateDict_MockXRefInteraction_2012) {
    // Arrange
    MockPDFDoc mockDoc;
    XRef* mockXRef = new XRef();
    EXPECT_CALL(mockDoc, getXRef()).WillOnce(testing::Return(mockXRef));

    // Act
    Dict* extGStateDict = getTopSecretStampExtGStateDict(&mockDoc);

    // Assert
    ASSERT_NE(extGStateDict, nullptr);

    // Ensure the mock XRef was interacted with
    testing::Mock::VerifyAndClearExpectations(&mockDoc);
}

// Test for boundary conditions (e.g., empty PDFDoc)
TEST_F(TopSecretStampTest_2012, getTopSecretStampExtGStateDict_EmptyDoc_2012) {
    // Arrange
    MockPDFDoc mockDoc;
    XRef* mockXRef = new XRef();
    EXPECT_CALL(mockDoc, getXRef()).WillOnce(testing::Return(mockXRef));

    // Act
    Dict* extGStateDict = getTopSecretStampExtGStateDict(&mockDoc);

    // Assert
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Dict = extGStateDict->lookup("a0", 0);
    ASSERT_TRUE(a0Dict.isDict());
    Object a1Dict = extGStateDict->lookup("a1", 0);
    ASSERT_TRUE(a1Dict.isDict());
}

TEST_F(TopSecretStampTest_2012, getTopSecretStampExtGStateDict_NullXRef_2012) {
    // Arrange
    MockPDFDoc mockDoc;
    EXPECT_CALL(mockDoc, getXRef()).WillOnce(testing::Return(nullptr));

    // Act
    Dict* extGStateDict = getTopSecretStampExtGStateDict(&mockDoc);

    // Assert
    ASSERT_EQ(extGStateDict, nullptr);
}