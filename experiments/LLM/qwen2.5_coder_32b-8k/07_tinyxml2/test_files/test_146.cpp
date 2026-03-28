#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLConstHandleTest_146 : public ::testing::Test {

protected:

    XMLNode* node;

    XMLConstHandle handle;



    void SetUp() override {

        node = new XMLNode(nullptr);

        handle = XMLConstHandle(node);

    }



    void TearDown() override {

        delete node;

    }

};



TEST_F(XMLConstHandleTest_146, ToDeclaration_ReturnsNull_WhenNodeIsNotADeclaration_146) {

    EXPECT_EQ(handle.ToDeclaration(), nullptr);

}



TEST_F(XMLConstHandleTest_146, FirstChild_ReturnsEmptyHandle_WhenNoChildren_146) {

    XMLConstHandle childHandle = handle.FirstChild();

    EXPECT_EQ(childHandle.ToNode(), nullptr);

}



TEST_F(XMLConstHandleTest_146, LastChild_ReturnsEmptyHandle_WhenNoChildren_146) {

    XMLConstHandle childHandle = handle.LastChild();

    EXPECT_EQ(childHandle.ToNode(), nullptr);

}



TEST_F(XMLConstHandleTest_146, PreviousSibling_ReturnsEmptyHandle_WhenNoSiblings_146) {

    XMLConstHandle siblingHandle = handle.PreviousSibling();

    EXPECT_EQ(siblingHandle.ToNode(), nullptr);

}



TEST_F(XMLConstHandleTest_146, NextSibling_ReturnsEmptyHandle_WhenNoSiblings_146) {

    XMLConstHandle siblingHandle = handle.NextSibling();

    EXPECT_EQ(siblingHandle.ToNode(), nullptr);

}
