#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLCommentTest_66 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLComment* comment;



    void SetUp() override {

        comment = new XMLComment(&doc);

    }



    void TearDown() override {

        delete comment;

    }

};



TEST_F(XMLCommentTest_66, ToCommentReturnsSelfPointer_66) {

    EXPECT_EQ(comment->ToComment(), comment);

}



TEST_F(XMLCommentTest_66, ShallowCloneCreatesNewInstance_66) {

    XMLNode* cloned = comment->ShallowClone(&doc);

    EXPECT_NE(cloned, nullptr);

    EXPECT_NE(cloned, comment);

    EXPECT_TRUE(cloned->ToComment() != nullptr);

    delete cloned;

}



TEST_F(XMLCommentTest_66, ShallowEqualReturnsTrueForSameInstance_66) {

    EXPECT_TRUE(comment->ShallowEqual(comment));

}



TEST_F(XMLCommentTest_66, ShallowEqualReturnsFalseForDifferentInstances_66) {

    XMLComment other(&doc);

    EXPECT_FALSE(comment->ShallowEqual(&other));

}



// Assuming XMLVisitor is a class that can be mocked

class MockXMLVisitor : public XMLVisitor {

public:

    MOCK_METHOD(bool, VisitEnter, (const XMLElement&), (override));

    MOCK_METHOD(bool, VisitExit, (const XMLElement&), (override));

    MOCK_METHOD(bool, Visit, (const XMLText&), (override));

    MOCK_METHOD(bool, Visit, (const XMLComment&), (override));

};



TEST_F(XMLCommentTest_66, AcceptCallsVisitOnXMLVisitor_66) {

    MockXMLVisitor mockVisitor;

    EXPECT_CALL(mockVisitor, Visit(*testing::An<const XMLComment*>())).WillOnce(testing::Return(true));



    bool result = comment->Accept(&mockVisitor);

    EXPECT_TRUE(result);

}
