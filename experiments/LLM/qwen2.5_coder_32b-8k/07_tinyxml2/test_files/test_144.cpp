#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLConstHandleTest_144 : public ::testing::Test {

protected:

    XMLNode node;

    XMLConstHandle handle;



    void SetUp() override {

        handle = XMLConstHandle(&node);

    }

};



TEST_F(XMLConstHandleTest_144, ToText_ReturnsNullPointerWhenNotText_144) {

    EXPECT_EQ(handle.ToText(), nullptr);

}



TEST_F(XMLConstHandleTest_144, ToNode_ReturnsValidNodePointer_144) {

    EXPECT_EQ(handle.ToNode(), &node);

}



TEST_F(XMLConstHandleTest_144, FirstChild_ReturnsEmptyHandleWhenNoChildren_144) {

    XMLConstHandle childHandle = handle.FirstChild();

    EXPECT_EQ(childHandle.ToNode(), nullptr);

}



TEST_F(XMLConstHandleTest_144, LastChild_ReturnsEmptyHandleWhenNoChildren_144) {

    XMLConstHandle childHandle = handle.LastChild();

    EXPECT_EQ(childHandle.ToNode(), nullptr);

}



TEST_F(XMLConstHandleTest_144, PreviousSibling_ReturnsEmptyHandleWhenNoPreviousSibling_144) {

    XMLConstHandle siblingHandle = handle.PreviousSibling();

    EXPECT_EQ(siblingHandle.ToNode(), nullptr);

}



TEST_F(XMLConstHandleTest_144, NextSibling_ReturnsEmptyHandleWhenNoNextSibling_144) {

    XMLConstHandle siblingHandle = handle.NextSibling();

    EXPECT_EQ(siblingHandle.ToNode(), nullptr);

}
