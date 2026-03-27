#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_264 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* element;



    void SetUp() override {

        element = new XMLElement(&doc);

    }



    void TearDown() override {

        delete element;

    }

};



TEST_F(XMLElementTest_264, ParseDeep_NormalOperation_264) {

    const char xml[] = "<tag>value</tag>";

    int curLineNum = 0;

    StrPair parentEndTag;



    char* result = element->ParseDeep(const_cast<char*>(xml), &parentEndTag, &curLineNum);



    EXPECT_EQ(result[0], '>');

}



TEST_F(XMLElementTest_264, ParseDeep_EmptyName_264) {

    const char xml[] = "<>";

    int curLineNum = 0;

    StrPair parentEndTag;



    char* result = element->ParseDeep(const_cast<char*>(xml), &parentEndTag, &curLineNum);



    EXPECT_EQ(result, nullptr);

}



TEST_F(XMLElementTest_264, ParseDeep_ClosingTag_264) {

    const char xml[] = "</tag>";

    int curLineNum = 0;

    StrPair parentEndTag;



    char* result = element->ParseDeep(const_cast<char*>(xml), &parentEndTag, &curLineNum);



    EXPECT_EQ(result[0], '>');

}



TEST_F(XMLElementTest_264, ParseDeep_BoundaryCondition_EmptyString_264) {

    const char xml[] = "";

    int curLineNum = 0;

    StrPair parentEndTag;



    char* result = element->ParseDeep(const_cast<char*>(xml), &parentEndTag, &curLineNum);



    EXPECT_EQ(result, nullptr);

}



TEST_F(XMLElementTest_264, ParseDeep_ErrorCase_MissingClosingBracket_264) {

    const char xml[] = "<tag";

    int curLineNum = 0;

    StrPair parentEndTag;



    char* result = element->ParseDeep(const_cast<char*>(xml), &parentEndTag, &curLineNum);



    EXPECT_EQ(result, nullptr);

}
