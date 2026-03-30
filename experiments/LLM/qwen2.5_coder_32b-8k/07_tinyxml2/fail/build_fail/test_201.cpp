#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tinyxml2.cpp"



using namespace tinyxml2;

using ::testing::_;

using ::testing::Return;

using ::testing::SetArgReferee;



class XMLDeclarationTest_201 : public ::testing::Test {

protected:

    XMLDocument mockDocument;

    XMLDeclaration declaration;

    StrPair strPair;

    int curLineNum = 1;



    void SetUp() override {

        // Setup any necessary state before each test.

        declaration._document = &mockDocument;

        declaration._parseLineNum = curLineNum;

    }

};



TEST_F(XMLDeclarationTest_201, ParseDeep_NormalOperation_201) {

    char input[] = "version=\"1.0\" encoding=\"UTF-8\"?>";

    char* result = declaration.ParseDeep(input, &strPair, &curLineNum);

    EXPECT_STREQ(result, input + 35); // Move past the entire declaration string

}



TEST_F(XMLDeclarationTest_201, ParseDeep_BoundaryCondition_EmptyString_201) {

    char input[] = "";

    char* result = declaration.ParseDeep(input, &strPair, &curLineNum);

    EXPECT_EQ(result, static_cast<char*>(nullptr));

}



TEST_F(XMLDeclarationTest_201, ParseDeep_BoundaryCondition_IncompleteDeclaration_201) {

    char input[] = "version=\"1.0\"";

    char* result = declaration.ParseDeep(input, &strPair, &curLineNum);

    EXPECT_EQ(result, static_cast<char*>(nullptr));

}



TEST_F(XMLDeclarationTest_201, ParseDeep_ErrorHandling_MissingClosingTag_201) {

    char input[] = "version=\"1.0\" encoding=\"UTF-8\"";

    EXPECT_CALL(mockDocument, SetError(XML_ERROR_PARSING_DECLARATION, curLineNum, 0)).Times(1);

    char* result = declaration.ParseDeep(input, &strPair, &curLineNum);

    EXPECT_EQ(result, static_cast<char*>(nullptr));

}



TEST_F(XMLDeclarationTest_201, ParseDeep_VerifyCurLineNumIncremented_201) {

    int initialCurLineNum = curLineNum;

    char input[] = "version=\"1.0\" encoding=\"UTF-8\"?>\n";

    char* result = declaration.ParseDeep(input, &strPair, &curLineNum);

    EXPECT_STREQ(result, input + 36); // Move past the entire declaration string including newline

    EXPECT_EQ(curLineNum, initialCurLineNum + 1);

}
