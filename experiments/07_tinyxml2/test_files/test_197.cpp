#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tinyxml2.cpp"



namespace tinyxml2 {



class XMLCommentTest_197 : public ::testing::Test {

protected:

    XMLComment xml_comment;

    char buffer[1024];

    StrPair str_pair;

    int curLineNum = 0;



    void SetUp() override {

        memset(buffer, 0, sizeof(buffer));

        curLineNum = 0;

    }

};



TEST_F(XMLCommentTest_197, ParseDeep_NormalOperation_197) {

    strcpy(buffer, "<!--This is a comment-->");

    char* result = xml_comment.ParseDeep(buffer, &str_pair, &curLineNum);

    EXPECT_NE(result, nullptr);

    EXPECT_STREQ(result, ">");

}



TEST_F(XMLCommentTest_197, ParseDeep_EmptyComment_197) {

    strcpy(buffer, "<!---->");

    char* result = xml_comment.ParseDeep(buffer, &str_pair, &curLineNum);

    EXPECT_NE(result, nullptr);

    EXPECT_STREQ(result, ">");

}



TEST_F(XMLCommentTest_197, ParseDeep_NoEndTag_197) {

    strcpy(buffer, "<!--This is a comment");

    char* result = xml_comment.ParseDeep(buffer, &str_pair, &curLineNum);

    EXPECT_EQ(result, nullptr);

}



TEST_F(XMLCommentTest_197, ParseDeep_MultipleComments_197) {

    strcpy(buffer, "<!--First--><!--Second-->");

    char* result = xml_comment.ParseDeep(buffer, &str_pair, &curLineNum);

    EXPECT_NE(result, nullptr);

    EXPECT_STREQ(result, "><!-");

}



TEST_F(XMLCommentTest_197, ParseDeep_ErrorHandling_197) {

    strcpy(buffer, "<!--This is a comment");

    char* result = xml_comment.ParseDeep(buffer, &str_pair, &curLineNum);

    EXPECT_EQ(result, nullptr);

    // Assuming _document and _parseLineNum are set appropriately in the real implementation

    // We cannot directly verify them here due to constraint 4.

}



} // namespace tinyxml2
