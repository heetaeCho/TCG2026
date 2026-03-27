#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_260 : public ::testing::Test {

protected:

    void SetUp() override {

        xmlDocument = new XMLDocument();

        xmlElement = new XMLElement(xmlDocument);

    }



    void TearDown() override {

        delete xmlElement;

        delete xmlDocument;

    }



    XMLDocument* xmlDocument;

    XMLElement* xmlElement;

};



TEST_F(XMLElementTest_260, InsertNewComment_NormalOperation_260) {

    const char* commentText = "This is a comment";

    XMLComment* commentNode = xmlElement->InsertNewComment(commentText);

    

    ASSERT_NE(commentNode, nullptr);

    EXPECT_STREQ(commentNode->Value(), commentText);

}



TEST_F(XMLElementTest_260, InsertNewComment_EmptyString_260) {

    const char* emptyCommentText = "";

    XMLComment* commentNode = xmlElement->InsertNewComment(emptyCommentText);



    ASSERT_NE(commentNode, nullptr);

    EXPECT_STREQ(commentNode->Value(), "");

}



TEST_F(XMLElementTest_260, InsertNewComment_NullString_260) {

    const char* nullCommentText = nullptr;

    XMLComment* commentNode = xmlElement->InsertNewComment(nullCommentText);



    ASSERT_EQ(commentNode, nullptr);

}
