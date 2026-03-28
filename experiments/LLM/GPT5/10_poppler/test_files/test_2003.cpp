#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "PDFDoc.h"
#include "Dict.h"

class PDFDocMock : public PDFDoc {
public:
    PDFDocMock() : PDFDoc(nullptr, std::nullopt, std::nullopt, [](){}) {}
    MOCK_METHOD(XRef*, getXRef, (), (const, override));
};

class DictMock : public Dict {
public:
    DictMock(XRef* xref) : Dict(xref) {}
    MOCK_METHOD(void, add, (std::string_view key, Object&& val), (override));
};

TEST_F(PDFDocTest_2003, getConfidentialStampExtGStateDict_CreatesCorrectDictStructure_2003) {
    // Arrange
    PDFDocMock docMock;
    XRef* xrefMock = new XRef();
    EXPECT_CALL(docMock, getXRef()).WillOnce(testing::Return(xrefMock));
    
    DictMock* dictMock1 = new DictMock(xrefMock);
    DictMock* dictMock2 = new DictMock(xrefMock);
    DictMock* extGStateDictMock = new DictMock(xrefMock);

    // Expectations on the add method of DictMock
    EXPECT_CALL(*dictMock1, add("CA", Object(0.588235))).Times(1);
    EXPECT_CALL(*dictMock1, add("ca", Object(0.588235))).Times(1);
    
    EXPECT_CALL(*dictMock2, add("CA", Object(1))).Times(1);
    EXPECT_CALL(*dictMock2, add("ca", Object(1))).Times(1);
    
    EXPECT_CALL(*extGStateDictMock, add("a0", Object(dictMock1))).Times(1);
    EXPECT_CALL(*extGStateDictMock, add("a1", Object(dictMock2))).Times(1);

    // Act
    Dict* result = getConfidentialStampExtGStateDict(&docMock);

    // Assert
    ASSERT_NE(result, nullptr);  // Ensure that result is not null.
    // Further assertions can be added to check the contents of the resulting Dict.
}

TEST_F(PDFDocTest_2003, getConfidentialStampExtGStateDict_HandlesNullXRef_2003) {
    // Arrange
    PDFDocMock docMock;
    XRef* xrefMock = nullptr;
    EXPECT_CALL(docMock, getXRef()).WillOnce(testing::Return(xrefMock));
    
    // Act and Assert
    EXPECT_THROW(getConfidentialStampExtGStateDict(&docMock), std::runtime_error);
}

TEST_F(PDFDocTest_2003, getConfidentialStampExtGStateDict_VerifiesDictAddCalls_2003) {
    // Arrange
    PDFDocMock docMock;
    XRef* xrefMock = new XRef();
    EXPECT_CALL(docMock, getXRef()).WillOnce(testing::Return(xrefMock));

    // Mocking Dict and adding expectations
    DictMock* dictMock1 = new DictMock(xrefMock);
    DictMock* dictMock2 = new DictMock(xrefMock);
    DictMock* extGStateDictMock = new DictMock(xrefMock);

    EXPECT_CALL(*dictMock1, add("CA", Object(0.588235))).Times(1);
    EXPECT_CALL(*dictMock1, add("ca", Object(0.588235))).Times(1);
    
    EXPECT_CALL(*dictMock2, add("CA", Object(1))).Times(1);
    EXPECT_CALL(*dictMock2, add("ca", Object(1))).Times(1);
    
    EXPECT_CALL(*extGStateDictMock, add("a0", Object(dictMock1))).Times(1);
    EXPECT_CALL(*extGStateDictMock, add("a1", Object(dictMock2))).Times(1);

    // Act
    Dict* result = getConfidentialStampExtGStateDict(&docMock);

    // Assert
    ASSERT_NE(result, nullptr);  // Ensure that the returned result is not null.
}