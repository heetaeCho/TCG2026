#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tinyxml2.h"



using namespace tinyxml2;

using ::testing::Return;

using ::testing::_;



class MockXMLVisitor : public XMLVisitor {

public:

    MOCK_METHOD(bool, Visit, (const XMLText&), (override));

};



class XMLTextTest_196 : public ::testing::Test {

protected:

    void SetUp() override {

        xmlDocument = new XMLDocument();

        xmlText = new XMLText(xmlDocument);

        mockVisitor = new MockXMLVisitor();

    }



    void TearDown() override {

        delete mockVisitor;

        delete xmlText;

        delete xmlDocument;

    }



    XMLDocument* xmlDocument;

    XMLText* xmlText;

    MockXMLVisitor* mockVisitor;

};



TEST_F(XMLTextTest_196, AcceptCallsVisitOnVisitor_196) {

    EXPECT_CALL(*mockVisitor, Visit(_)).Times(1).WillOnce(Return(true));

    bool result = xmlText->Accept(mockVisitor);

    EXPECT_TRUE(result);

}



TEST_F(XMLTextTest_196, AcceptReturnsFalseIfVisitFails_196) {

    EXPECT_CALL(*mockVisitor, Visit(_)).Times(1).WillOnce(Return(false));

    bool result = xmlText->Accept(mockVisitor);

    EXPECT_FALSE(result);

}



TEST_F(XMLTextTest_196, CDataIsInitiallyFalse_196) {

    EXPECT_FALSE(xmlText->CData());

}



TEST_F(XMLTextTest_196, SetCDataSetValueCorrectly_196) {

    xmlText->SetCData(true);

    EXPECT_TRUE(xmlText->CData());



    xmlText->SetCData(false);

    EXPECT_FALSE(xmlText->CData());

}
