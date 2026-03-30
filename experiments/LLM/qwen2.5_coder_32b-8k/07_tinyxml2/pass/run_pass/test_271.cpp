#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLDocumentTest_271 : public ::testing::Test {

protected:

    void SetUp() override {

        doc = new XMLDocument();

        targetDoc = new XMLDocument();

    }



    void TearDown() override {

        delete targetDoc;

        delete doc;

    }



    XMLDocument* doc;

    XMLDocument* targetDoc;

};



TEST_F(XMLDocumentTest_271, DeepCopy_NoChildren_NormalOperation_271) {

    // Arrange

    EXPECT_EQ(0, doc->ChildElementCount());



    // Act

    doc->DeepCopy(targetDoc);



    // Assert

    EXPECT_EQ(0, targetDoc->ChildElementCount());

}



TEST_F(XMLDocumentTest_271, DeepCopy_WithChildren_NormalOperation_271) {

    // Arrange

    XMLElement* elem = doc->NewElement("test");

    doc->InsertEndChild(elem);

    EXPECT_EQ(1, doc->ChildElementCount());



    // Act

    doc->DeepCopy(targetDoc);



    // Assert

    EXPECT_EQ(1, targetDoc->ChildElementCount());

}



TEST_F(XMLDocumentTest_271, DeepCopy_SameObject_NoOp_271) {

    // Arrange & Act

    doc->DeepCopy(doc);



    // Assert: No change expected in child count or any other observable behavior.

    EXPECT_EQ(0, doc->ChildElementCount());

}



TEST_F(XMLDocumentTest_271, DeepCopy_TargetInitiallyNotEmpty_ClearsBeforeCopy_271) {

    // Arrange

    XMLElement* elem = targetDoc->NewElement("preexisting");

    targetDoc->InsertEndChild(elem);

    EXPECT_EQ(1, targetDoc->ChildElementCount());



    XMLElement* newElem = doc->NewElement("new");

    doc->InsertEndChild(newElem);



    // Act

    doc->DeepCopy(targetDoc);



    // Assert: Target document should be cleared before copying.

    EXPECT_EQ(1, targetDoc->ChildElementCount());

    EXPECT_STREQ("new", targetDoc->FirstChild()->Value());

}



TEST_F(XMLDocumentTest_271, DeepCopy_DeepClonesChildren_StructurePreserved_271) {

    // Arrange

    XMLElement* root = doc->NewElement("root");

    XMLElement* child = doc->NewElement("child");

    root->InsertEndChild(child);

    doc->InsertEndChild(root);



    // Act

    doc->DeepCopy(targetDoc);



    // Assert: Structure of the children should be preserved in the target document.

    EXPECT_EQ(1, targetDoc->ChildElementCount());

    const XMLNode* rootNode = targetDoc->FirstChild();

    EXPECT_STREQ("root", rootNode->Value());



    const XMLNode* childNode = rootNode->FirstChild();

    EXPECT_STREQ("child", childNode->Value());

}
