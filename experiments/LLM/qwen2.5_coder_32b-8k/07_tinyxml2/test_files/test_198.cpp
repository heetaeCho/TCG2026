#include <gtest/gtest.h>

#include "tinyxml2.h"

using namespace tinyxml2;



class XMLCommentTest_198 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLComment* comment;



    XMLCommentTest_198() : doc(true, Whitespace::preserve) {

        comment = new XMLComment(&doc);

        comment->SetValue("Sample Comment", false);

    }



    virtual ~XMLCommentTest_198() {

        delete comment;

    }

};



TEST_F(XMLCommentTest_198, ShallowCloneWithNullDoc_198) {

    XMLComment* clonedComment = comment->ShallowClone(nullptr);

    ASSERT_NE(clonedComment, nullptr);

    EXPECT_EQ(strcmp(clonedComment->Value(), "Sample Comment"), 0);

    EXPECT_EQ(clonedComment->_document, &doc);

    delete clonedComment;

}



TEST_F(XMLCommentTest_198, ShallowCloneWithProvidedDoc_198) {

    XMLDocument newDoc(true, Whitespace::preserve);

    XMLComment* clonedComment = comment->ShallowClone(&newDoc);

    ASSERT_NE(clonedComment, nullptr);

    EXPECT_EQ(strcmp(clonedComment->Value(), "Sample Comment"), 0);

    EXPECT_EQ(clonedComment->_document, &newDoc);

    delete clonedComment;

}



TEST_F(XMLCommentTest_198, ShallowCloneSameAsOriginal_198) {

    XMLComment* clonedComment = comment->ShallowClone(&doc);

    ASSERT_NE(clonedComment, nullptr);

    EXPECT_EQ(strcmp(clonedComment->Value(), comment->Value()), 0);

    delete clonedComment;

}



TEST_F(XMLCommentTest_198, ShallowCloneDifferentDocument_198) {

    XMLDocument newDoc(true, Whitespace::preserve);

    XMLComment* clonedComment = comment->ShallowClone(&newDoc);

    ASSERT_NE(clonedComment, nullptr);

    EXPECT_EQ(strcmp(clonedComment->Value(), "Sample Comment"), 0);

    EXPECT_NE(clonedComment->_document, comment->_document);

    delete clonedComment;

}
