#include <gtest/gtest.h>

#include "tinyxml2.h"



namespace tinyxml2 {



class XMLConstHandleTest_138 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup initial state if needed

    }



    XMLNode* createNode(const char* value) {

        XMLDocument doc;

        return new XMLNode(&doc);

    }

};



TEST_F(XMLConstHandleTest_138, PreviousSibling_NoPreviousSibling_138) {

    XMLNode* node = createNode("test");

    XMLConstHandle handle(node);



    XMLConstHandle previousSibling = handle.PreviousSibling();

    EXPECT_EQ(previousSibling.ToNode(), nullptr);

}



TEST_F(XMLConstHandleTest_138, PreviousSibling_WithPreviousSibling_138) {

    XMLDocument doc;

    XMLNode* parent = new XMLNode(&doc);

    XMLNode* firstChild = new XMLNode(&doc);

    XMLNode* secondChild = new XMLNode(&doc);



    parent->InsertFirstChild(firstChild);

    parent->InsertEndChild(secondChild);



    XMLConstHandle handle(secondChild);

    XMLConstHandle previousSibling = handle.PreviousSibling();

    EXPECT_EQ(previousSibling.ToNode(), firstChild);

}



TEST_F(XMLConstHandleTest_138, PreviousSibling_RootNode_138) {

    XMLDocument doc;

    XMLNode* rootNode = new XMLNode(&doc);



    XMLConstHandle handle(rootNode);

    XMLConstHandle previousSibling = handle.PreviousSibling();

    EXPECT_EQ(previousSibling.ToNode(), nullptr);

}



TEST_F(XMLConstHandleTest_138, PreviousSibling_MultipleSiblings_138) {

    XMLDocument doc;

    XMLNode* parent = new XMLNode(&doc);

    XMLNode* firstChild = new XMLNode(&doc);

    XMLNode* secondChild = new XMLNode(&doc);

    XMLNode* thirdChild = new XMLNode(&doc);



    parent->InsertFirstChild(firstChild);

    parent->InsertEndChild(secondChild);

    parent->InsertEndChild(thirdChild);



    XMLConstHandle handle(thirdChild);

    XMLConstHandle previousSibling = handle.PreviousSibling();

    EXPECT_EQ(previousSibling.ToNode(), secondChild);

}



TEST_F(XMLConstHandleTest_138, PreviousSibling_FirstSiblingInChain_138) {

    XMLDocument doc;

    XMLNode* parent = new XMLNode(&doc);

    XMLNode* firstChild = new XMLNode(&doc);

    XMLNode* secondChild = new XMLNode(&doc);



    parent->InsertFirstChild(firstChild);

    parent->InsertEndChild(secondChild);



    XMLConstHandle handle(firstChild);

    XMLConstHandle previousSibling = handle.PreviousSibling();

    EXPECT_EQ(previousSibling.ToNode(), nullptr);

}



} // namespace tinyxml2
