#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLTextTest_63 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLText* xmlText;



    void SetUp() override {

        xmlText = new XMLText(&doc);

    }



    void TearDown() override {

        delete xmlText;

    }

};



TEST_F(XMLTextTest_63, ToTextReturnsSelfPointer_63) {

    EXPECT_EQ(xmlText->ToText(), xmlText);

}



TEST_F(XMLTextTest_63, SetCDataAndGetCData_63) {

    xmlText->SetCData(true);

    EXPECT_TRUE(xmlText->CData());



    xmlText->SetCData(false);

    EXPECT_FALSE(xmlText->CData());

}



TEST_F(XMLTextTest_63, ShallowCloneCreatesNewInstance_63) {

    XMLNode* clonedNode = xmlText->ShallowClone(&doc);

    ASSERT_NE(clonedNode, nullptr);



    XMLText* clonedXmlText = clonedNode->ToText();

    EXPECT_TRUE(clonedXmlText != nullptr && clonedXmlText != xmlText);

    delete clonedNode;

}



TEST_F(XMLTextTest_63, ShallowEqualWithSameContent_63) {

    XMLDocument anotherDoc;

    XMLText otherText(&anotherDoc);



    xmlText->SetCData(true);

    otherText.SetCData(true);



    EXPECT_TRUE(xmlText->ShallowEqual(&otherText));



    xmlText->SetCData(false);

    EXPECT_FALSE(xmlText->ShallowEqual(&otherText));

}



TEST_F(XMLTextTest_63, ShallowEqualWithDifferentContent_63) {

    XMLDocument anotherDoc;

    XMLText otherText(&anotherDoc);



    EXPECT_FALSE(xmlText->ShallowEqual(&otherText));



    xmlText->SetCData(true);

    EXPECT_FALSE(xmlText->ShallowEqual(&otherText));

}



TEST_F(XMLTextTest_63, AcceptCallsVisitor_63) {

    class MockXMLVisitor : public XMLVisitor {

    public:

        MOCK_METHOD(bool, VisitEnter, (const XMLElement&), (override));

        MOCK_METHOD(bool, VisitExit, (const XMLElement&), (override));

        MOCK_METHOD(void, Visit, (const XMLText&), (override));

    };



    MockXMLVisitor mockVisitor;

    EXPECT_CALL(mockVisitor, Visit(*xmlText));



    xmlText->Accept(&mockVisitor);

}
