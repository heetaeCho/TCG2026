#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_262 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* element;



    void SetUp() override {

        element = doc.NewElement("Root");

        doc.InsertFirstChild(element);

    }



    void TearDown() override {

        doc.Clear();

    }

};



TEST_F(XMLElementTest_262, InsertNewDeclaration_ReturnsValidPointer_262) {

    XMLDeclaration* decl = element->InsertNewDeclaration("version=\"1.0\" encoding=\"UTF-8\"");

    EXPECT_NE(decl, nullptr);

}



TEST_F(XMLElementTest_262, InsertNewDeclaration_IncreasesChildCount_262) {

    int initialCount = element->ChildElementCount();

    element->InsertNewDeclaration("version=\"1.0\" encoding=\"UTF-8\"");

    EXPECT_EQ(element->ChildElementCount(), initialCount + 1);

}



TEST_F(XMLElementTest_262, InsertNewDeclaration_ValueIsSetCorrectly_262) {

    XMLDeclaration* decl = element->InsertNewDeclaration("version=\"1.0\" encoding=\"UTF-8\"");

    EXPECT_STREQ(decl->Value(), "xml");

    EXPECT_STREQ(decl->GetText(), "version=\"1.0\" encoding=\"UTF-8\"");

}



TEST_F(XMLElementTest_262, InsertNewDeclaration_EmptyString_ReturnsNull_262) {

    XMLDeclaration* decl = element->InsertNewDeclaration("");

    EXPECT_EQ(decl, nullptr);

}



TEST_F(XMLElementTest_262, InsertNewDeclaration_NullPointer_ReturnsNull_262) {

    XMLDeclaration* decl = element->InsertNewDeclaration(nullptr);

    EXPECT_EQ(decl, nullptr);

}
