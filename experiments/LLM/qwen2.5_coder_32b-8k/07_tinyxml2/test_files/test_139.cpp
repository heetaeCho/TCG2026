#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLConstHandleTest_139 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* rootElement;

    XMLElement* childElement1;

    XMLElement* childElement2;



    void SetUp() override {

        rootElement = doc.NewElement("Root");

        childElement1 = doc.NewElement("Child1");

        childElement2 = doc.NewElement("Child2");



        rootElement->InsertEndChild(childElement1);

        rootElement->InsertEndChild(childElement2);

        doc.InsertFirstChild(rootElement);

    }

};



TEST_F(XMLConstHandleTest_139, PreviousSiblingElement_NormalOperation_139) {

    XMLConstHandle handle(childElement2);

    XMLConstHandle sibling = handle.PreviousSiblingElement();

    EXPECT_EQ(sibling.ToNode(), childElement1);

}



TEST_F(XMLConstHandleTest_139, PreviousSiblingElement_SameName_139) {

    XMLElement* childElement3 = doc.NewElement("Child1");

    rootElement->InsertEndChild(childElement3);



    XMLConstHandle handle(childElement3);

    XMLConstHandle sibling = handle.PreviousSiblingElement("Child1");

    EXPECT_EQ(sibling.ToNode(), childElement1);

}



TEST_F(XMLConstHandleTest_139, PreviousSiblingElement_NoPreviousSibling_139) {

    XMLConstHandle handle(childElement1);

    XMLConstHandle sibling = handle.PreviousSiblingElement();

    EXPECT_TRUE(sibling.ToNode() == nullptr);

}



TEST_F(XMLConstHandleTest_139, PreviousSiblingElement_NameNotFound_139) {

    XMLConstHandle handle(childElement2);

    XMLConstHandle sibling = handle.PreviousSiblingElement("NonExistent");

    EXPECT_TRUE(sibling.ToNode() == nullptr);

}



TEST_F(XMLConstHandleTest_139, PreviousSiblingElement_NullNode_139) {

    XMLConstHandle nullHandle;

    XMLConstHandle sibling = nullHandle.PreviousSiblingElement();

    EXPECT_TRUE(sibling.ToNode() == nullptr);

}
