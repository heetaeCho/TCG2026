#include <gtest/gtest.h>

#include "tinyxml2.h"

#include <gmock/gmock.h>



using namespace tinyxml2;

using ::testing::Return;



class MockXMLDocument : public XMLDocument {

public:

    MOCK_METHOD(XMLNode*, ShallowClone, (XMLDocument* document), const);

};



class MockXMLNode : public XMLNode {

public:

    using XMLNode::XMLNode;

    MOCK_CONST_METHOD0(FirstChild, XMLNode*());

    MOCK_CONST_METHOD0(NextSibling, XMLNode*());

    MOCK_METHOD1(InsertEndChild, XMLNode*(XMLNode* addThis));

};



TEST_F(MockXMLDocumentTest_186, DeepClone_ReturnsNullIfShallowCloneFails_186) {

    MockXMLDocument mockDoc;

    EXPECT_CALL(mockDoc, ShallowClone(&mockDoc)).WillOnce(Return(nullptr));



    XMLNode* result = mockDoc.DeepClone(&mockDoc);

    ASSERT_EQ(result, nullptr);

}



TEST_F(MockXMLDocumentTest_186, DeepClone_ClonesChildrenSuccessfully_186) {

    MockXMLDocument mockDoc;

    MockXMLNode mockNode(&mockDoc);



    EXPECT_CALL(mockDoc, ShallowClone(&mockDoc)).WillOnce(Return(&mockNode));



    MockXMLNode child1(&mockDoc);

    MockXMLNode child2(&mockDoc);

    MockXMLNode clonedChild1(&mockDoc);

    MockXMLNode clonedChild2(&mockDoc);



    EXPECT_CALL(mockNode, FirstChild()).WillOnce(Return(&child1)).WillRepeatedly(Return(nullptr));

    EXPECT_CALL(child1, NextSibling()).WillOnce(Return(&child2)).WillRepeatedly(Return(nullptr));



    EXPECT_CALL(child1, DeepClone(&mockDoc)).WillOnce(Return(&clonedChild1));

    EXPECT_CALL(child2, DeepClone(&mockDoc)).WillOnce(Return(&clonedChild2));



    EXPECT_CALL(mockNode, InsertEndChild(&clonedChild1)).WillOnce(Return(&clonedChild1));

    EXPECT_CALL(mockNode, InsertEndChild(&clonedChild2)).WillOnce(Return(&clonedChild2));



    XMLNode* result = mockNode.DeepClone(&mockDoc);

    ASSERT_NE(result, nullptr);

}



TEST_F(MockXMLDocumentTest_186, DeepClone_NoChildren_ClonesOnlyRoot_186) {

    MockXMLDocument mockDoc;

    MockXMLNode mockNode(&mockDoc);



    EXPECT_CALL(mockDoc, ShallowClone(&mockDoc)).WillOnce(Return(&mockNode));

    EXPECT_CALL(mockNode, FirstChild()).WillRepeatedly(Return(nullptr));



    XMLNode* result = mockNode.DeepClone(&mockDoc);

    ASSERT_NE(result, nullptr);

}
