#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLDocumentTest : public ::testing::Test {

protected:

    XMLDocument* doc;



    void SetUp() override {

        doc = new XMLDocument();

    }



    void TearDown() override {

        delete doc;

    }

};



TEST_F(XMLDocumentTest_273, NewComment_ReturnsNonNullPointer_273) {

    XMLComment* comment = doc->NewComment("test comment");

    EXPECT_NE(comment, nullptr);

}



TEST_F(XMLDocumentTest_273, NewComment_ValueIsSetCorrectly_273) {

    const char* expectedValue = "test comment";

    XMLComment* comment = doc->NewComment(expectedValue);

    EXPECT_STREQ(comment->Value(), expectedValue);

}



TEST_F(XMLDocumentTest_273, NewComment_EmptyString_ReturnsNonNullPointer_273) {

    XMLComment* comment = doc->NewComment("");

    EXPECT_NE(comment, nullptr);

}



TEST_F(XMLDocumentTest_273, NewComment_EmptyString_ValueIsSetCorrectly_273) {

    const char* expectedValue = "";

    XMLComment* comment = doc->NewComment(expectedValue);

    EXPECT_STREQ(comment->Value(), expectedValue);

}



TEST_F(XMLDocumentTest_273, NewComment_NullPointer_ReturnsNonNullPointer_273) {

    XMLComment* comment = doc->NewComment(nullptr);

    EXPECT_NE(comment, nullptr);

}



TEST_F(XMLDocumentTest_273, NewComment_NullPointer_ValueIsSetCorrectly_273) {

    const char* expectedValue = "";

    XMLComment* comment = doc->NewComment(nullptr);

    EXPECT_STREQ(comment->Value(), expectedValue);

}
