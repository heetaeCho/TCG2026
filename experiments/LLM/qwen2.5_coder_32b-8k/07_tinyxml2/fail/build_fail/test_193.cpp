#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tinyxml2.h"



using namespace tinyxml2;

using ::testing::_;

using ::testing::Return;



class MockXMLDocument : public XMLDocument {

public:

    MOCK_METHOD(bool, CData, (), (const));

    MOCK_METHOD(int, ProcessEntities, (), (const));

    MOCK_METHOD(WhitespaceMode, WhitespaceMode, (), (const));

    MOCK_METHOD(void, SetError, (XMLError, int, const char*), ());

};



class XMLTextTest : public ::testing::Test {

protected:

    MockXMLDocument mockDoc;

    XMLText xmlText;



    void SetUp() override {

        xmlText._document = &mockDoc;

    }

};



TEST_F(XMLTextTest_193, ParseDeep_CData_Success_193) {

    char input[] = "]]>";

    StrPair strPair;

    int curLineNum = 0;

    EXPECT_CALL(mockDoc, CData()).WillOnce(Return(true));

    EXPECT_CALL(mockDoc, SetError(_, _, _)).Times(0);



    char* result = xmlText.ParseDeep(input, &strPair, &curLineNum);



    ASSERT_EQ(result, input + 3);

}



TEST_F(XMLTextTest_193, ParseDeep_CData_Error_193) {

    char input[] = "]]";

    StrPair strPair;

    int curLineNum = 0;

    EXPECT_CALL(mockDoc, CData()).WillOnce(Return(true));

    EXPECT_CALL(mockDoc, SetError(XML_ERROR_PARSING_CDATA, _, _));



    char* result = xmlText.ParseDeep(input, &strPair, &curLineNum);



    ASSERT_EQ(result, nullptr);

}



TEST_F(XMLTextTest_193, ParseDeep_Text_ProcessEntities_Success_193) {

    char input[] = "<";

    StrPair strPair;

    int curLineNum = 0;

    EXPECT_CALL(mockDoc, CData()).WillOnce(Return(false));

    EXPECT_CALL(mockDoc, ProcessEntities()).WillOnce(Return(true));

    EXPECT_CALL(mockDoc, WhitespaceMode()).WillOnce(Return(COLLAPSE_WHITESPACE));

    EXPECT_CALL(mockDoc, SetError(_, _, _)).Times(0);



    char* result = xmlText.ParseDeep(input, &strPair, &curLineNum);



    ASSERT_EQ(result, input - 1);

}



TEST_F(XMLTextTest_193, ParseDeep_Text_NoProcessEntities_Success_193) {

    char input[] = "<";

    StrPair strPair;

    int curLineNum = 0;

    EXPECT_CALL(mockDoc, CData()).WillOnce(Return(false));

    EXPECT_CALL(mockDoc, ProcessEntities()).WillOnce(Return(false));

    EXPECT_CALL(mockDoc, WhitespaceMode()).WillOnce(Return(COLLAPSE_WHITESPACE));

    EXPECT_CALL(mockDoc, SetError(_, _, _)).Times(0);



    char* result = xmlText.ParseDeep(input, &strPair, &curLineNum);



    ASSERT_EQ(result, input - 1);

}



TEST_F(XMLTextTest_193, ParseDeep_Text_Error_193) {

    char input[] = "";

    StrPair strPair;

    int curLineNum = 0;

    EXPECT_CALL(mockDoc, CData()).WillOnce(Return(false));

    EXPECT_CALL(mockDoc, ProcessEntities()).WillOnce(Return(true));

    EXPECT_CALL(mockDoc, WhitespaceMode()).WillOnce(Return(COLLAPSE_WHITESPACE));

    EXPECT_CALL(mockDoc, SetError(XML_ERROR_PARSING_TEXT, _, _));



    char* result = xmlText.ParseDeep(input, &strPair, &curLineNum);



    ASSERT_EQ(result, nullptr);

}
