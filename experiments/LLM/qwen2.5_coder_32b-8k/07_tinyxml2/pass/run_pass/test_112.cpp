#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLDocumentTest_112 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* rootElement;



    void SetUp() override {

        doc.Parse("<root></root>");

        rootElement = doc.RootElement();

    }

};



TEST_F(XMLDocumentTest_112, RootElementReturnsRoot_112) {

    ASSERT_NE(rootElement, nullptr);

    EXPECT_STREQ("root", rootElement->Value());

}



TEST_F(XMLDocumentTest_112, RootElementWithNoChildren_ReturnsNull_112) {

    EXPECT_EQ(rootElement->FirstChild(), nullptr);

    EXPECT_EQ(rootElement->LastChild(), nullptr);

    EXPECT_EQ(rootElement->PreviousSibling(), nullptr);

    EXPECT_EQ(rootElement->NextSibling(), nullptr);

}



TEST_F(XMLDocumentTest_112, ChildElementCountNoChildren_ReturnsZero_112) {

    EXPECT_EQ(rootElement->ChildElementCount(), 0);

}



TEST_F(XMLDocumentTest_112, InsertEndChild_AddsChildToEnd_112) {

    XMLElement* child = doc.NewElement("child");

    rootElement->InsertEndChild(child);

    EXPECT_STREQ("child", rootElement->FirstChild()->Value());

    EXPECT_EQ(rootElement->ChildElementCount(), 1);

}



TEST_F(XMLDocumentTest_112, InsertEndChild_MultipleChildren_AddsToEnd_112) {

    XMLElement* child1 = doc.NewElement("child1");

    XMLElement* child2 = doc.NewElement("child2");

    rootElement->InsertEndChild(child1);

    rootElement->InsertEndChild(child2);

    EXPECT_STREQ("child1", rootElement->FirstChild()->Value());

    EXPECT_STREQ("child2", rootElement->LastChild()->Value());

}



TEST_F(XMLDocumentTest_112, InsertFirstChild_AddsChildToBeginning_112) {

    XMLElement* child = doc.NewElement("child");

    rootElement->InsertFirstChild(child);

    EXPECT_STREQ("child", rootElement->FirstChild()->Value());

    EXPECT_EQ(rootElement->ChildElementCount(), 1);

}



TEST_F(XMLDocumentTest_112, InsertAfterChild_InsertsInCorrectPosition_112) {

    XMLElement* child1 = doc.NewElement("child1");

    XMLElement* child2 = doc.NewElement("child2");

    rootElement->InsertEndChild(child1);

    rootElement->InsertAfterChild(child1, child2);

    EXPECT_STREQ("child1", rootElement->FirstChild()->Value());

    EXPECT_STREQ("child2", rootElement->LastChild()->Value());

}



TEST_F(XMLDocumentTest_112, DeleteChildren_RemovesAllChildren_112) {

    XMLElement* child1 = doc.NewElement("child1");

    XMLElement* child2 = doc.NewElement("child2");

    rootElement->InsertEndChild(child1);

    rootElement->InsertEndChild(child2);

    rootElement->DeleteChildren();

    EXPECT_EQ(rootElement->FirstChild(), nullptr);

}



TEST_F(XMLDocumentTest_112, DeleteChild_RemovesSpecificChild_112) {

    XMLElement* child1 = doc.NewElement("child1");

    XMLElement* child2 = doc.NewElement("child2");

    rootElement->InsertEndChild(child1);

    rootElement->InsertEndChild(child2);

    rootElement->DeleteChild(child1);

    EXPECT_STREQ("child2", rootElement->FirstChild()->Value());

}



TEST_F(XMLDocumentTest_112, ParseValidXML_Succeeds_112) {

    const char* xml = "<root><child></child></root>";

    XMLError result = doc.Parse(xml);

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_STREQ("root", doc.RootElement()->Value());

}



TEST_F(XMLDocumentTest_112, ParseInvalidXML_Fails_112) {

    const char* xml = "<root><child></child>";

    XMLError result = doc.Parse(xml);

    EXPECT_NE(result, XML_SUCCESS);

}



TEST_F(XMLDocumentTest_112, SetValue_ChangesElementValue_112) {

    rootElement->SetValue("newRoot");

    EXPECT_STREQ("newRoot", rootElement->Value());

}
