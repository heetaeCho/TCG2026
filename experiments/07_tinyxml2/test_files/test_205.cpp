#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tinyxml2.cpp"



using namespace tinyxml2;

using ::testing::_;

using ::testing::Return;



class MockStrPair : public StrPair {

public:

    MOCK_METHOD(char*, ParseText, (char* p, const char* endTag, int flags, int* curLineNumPtr), (override));

};



class MockXMLDocument : public XMLDocument {

public:

    MOCK_METHOD(void, SetError, (XMLError error, int lineNum, int col), (override));

};



class XMLUnknownTest_205 : public ::testing::Test {

protected:

    void SetUp() override {

        mockStrPair = new MockStrPair();

        mockXMLDocument = new MockXMLDocument();

        xmlUnknown._value = *mockStrPair;

        xmlUnknown._document = mockXMLDocument;

        xmlUnknown._parseLineNum = 10;

    }



    void TearDown() override {

        delete mockStrPair;

        delete mockXMLDocument;

    }



    XMLUnknown xmlUnknown;

    MockStrPair* mockStrPair;

    MockXMLDocument* mockXMLDocument;

};



TEST_F(XMLUnknownTest_205, ParseDeep_NormalOperation_ReturnsNextPointer_205) {

    char input[] = "<unknown>data></unknown>";

    char* expectedOutput = input + 19; // After "</unknown>"

    int curLineNum = 1;



    EXPECT_CALL(*mockStrPair, ParseText(input + 8, ">", StrPair::NEEDS_NEWLINE_NORMALIZATION, &curLineNum))

        .WillOnce(Return(expectedOutput));



    char* result = xmlUnknown.ParseDeep(input, mockStrPair, &curLineNum);



    EXPECT_EQ(result, expectedOutput);

}



TEST_F(XMLUnknownTest_205, ParseDeep_ParseTextReturnsNull_SetsError_205) {

    char input[] = "<unknown>data></unknown>";

    int curLineNum = 1;



    EXPECT_CALL(*mockStrPair, ParseText(input + 8, ">", StrPair::NEEDS_NEWLINE_NORMALIZATION, &curLineNum))

        .WillOnce(Return(nullptr));



    EXPECT_CALL(*mockXMLDocument, SetError(XML_ERROR_PARSING_UNKNOWN, 10, 0));



    char* result = xmlUnknown.ParseDeep(input, mockStrPair, &curLineNum);



    EXPECT_EQ(result, nullptr);

}



TEST_F(XMLUnknownTest_205, ParseDeep_EmptyInput_ReturnsNull_SetsError_205) {

    char input[] = "";

    int curLineNum = 1;



    EXPECT_CALL(*mockStrPair, ParseText(input + 8, ">", StrPair::NEEDS_NEWLINE_NORMALIZATION, &curLineNum))

        .WillOnce(Return(nullptr));



    EXPECT_CALL(*mockXMLDocument, SetError(XML_ERROR_PARSING_UNKNOWN, 10, 0));



    char* result = xmlUnknown.ParseDeep(input, mockStrPair, &curLineNum);



    EXPECT_EQ(result, nullptr);

}



TEST_F(XMLUnknownTest_205, ParseDeep_ParseTextModifiesCurLineNum_ReturnsNextPointer_205) {

    char input[] = "<unknown>data></unknown>";

    char* expectedOutput = input + 19; // After "</unknown>"

    int curLineNum = 1;

    int modifiedCurLineNum = 3;



    EXPECT_CALL(*mockStrPair, ParseText(input + 8, ">", StrPair::NEEDS_NEWLINE_NORMALIZATION, &curLineNum))

        .WillOnce(testing::DoAll(testing::SetArgReferee<3>(modifiedCurLineNum), Return(expectedOutput)));



    char* result = xmlUnknown.ParseDeep(input, mockStrPair, &curLineNum);



    EXPECT_EQ(result, expectedOutput);

    EXPECT_EQ(curLineNum, modifiedCurLineNum);

}
