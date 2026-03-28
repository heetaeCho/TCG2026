#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLCommentTest : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLComment* comment1;

    XMLComment* comment2;



    void SetUp() override {

        comment1 = new XMLComment(&doc);

        comment1->SetValue("This is a test comment", false);



        comment2 = new XMLComment(&doc);

        comment2->SetValue("Another test comment", false);

    }



    void TearDown() override {

        delete comment1;

        delete comment2;

    }

};



TEST_F(XMLCommentTest_199, ShallowEqual_SameContent_ReturnsTrue_199) {

    EXPECT_TRUE(comment1->ShallowEqual(comment1));

}



TEST_F(XMLCommentTest_199, ShallowEqual_DifferentContent_ReturnsFalse_199) {

    EXPECT_FALSE(comment1->ShallowEqual(comment2));

}



TEST_F(XMLCommentTest_199, ShallowEqual_NullPointer_ReturnsFalse_199) {

    EXPECT_FALSE(comment1->ShallowEqual(nullptr));

}



TEST_F(XMLCommentTest_199, ShallowEqual_DifferentType_ReturnsFalse_199) {

    XMLElement* element = new XMLElement(&doc);

    EXPECT_FALSE(comment1->ShallowEqual(element));

    delete element;

}
