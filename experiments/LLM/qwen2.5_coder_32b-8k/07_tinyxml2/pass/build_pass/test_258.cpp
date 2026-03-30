#include "gtest/gtest.h"

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_258 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* element;



    void SetUp() override {

        element = doc.NewElement("Root");

        doc.InsertEndChild(element);

    }



    void TearDown() override {

        doc.Clear();

    }

};



TEST_F(XMLElementTest_258, DeleteNonExistentAttribute_258) {

    element->DeleteAttribute("nonexistent");

    // No attributes should be removed if the attribute does not exist

}



TEST_F(XMLElementTest_258, DeleteSingleAttribute_258) {

    element->SetAttribute("test", "value");

    element->DeleteAttribute("test");

    EXPECT_EQ(element->FindAttribute("test"), nullptr);

}



TEST_F(XMLElementTest_258, DeleteMultipleAttributes_258) {

    element->SetAttribute("attr1", "value1");

    element->SetAttribute("attr2", "value2");

    element->DeleteAttribute("attr1");

    EXPECT_EQ(element->FindAttribute("attr1"), nullptr);

    EXPECT_NE(element->FindAttribute("attr2"), nullptr);



    element->DeleteAttribute("attr2");

    EXPECT_EQ(element->FindAttribute("attr2"), nullptr);

}



TEST_F(XMLElementTest_258, DeleteFirstAttribute_258) {

    element->SetAttribute("first", "value1");

    element->SetAttribute("second", "value2");

    element->DeleteAttribute("first");

    EXPECT_EQ(element->FindAttribute("first"), nullptr);

    EXPECT_NE(element->FindAttribute("second"), nullptr);

}



TEST_F(XMLElementTest_258, DeleteLastAttribute_258) {

    element->SetAttribute("first", "value1");

    element->SetAttribute("last", "value2");

    element->DeleteAttribute("last");

    EXPECT_EQ(element->FindAttribute("last"), nullptr);

    EXPECT_NE(element->FindAttribute("first"), nullptr);

}



TEST_F(XMLElementTest_258, DeleteMiddleAttribute_258) {

    element->SetAttribute("first", "value1");

    element->SetAttribute("middle", "value2");

    element->SetAttribute("last", "value3");

    element->DeleteAttribute("middle");

    EXPECT_EQ(element->FindAttribute("middle"), nullptr);

    EXPECT_NE(element->FindAttribute("first"), nullptr);

    EXPECT_NE(element->FindAttribute("last"), nullptr);

}



TEST_F(XMLElementTest_258, DeleteAllAttributes_258) {

    element->SetAttribute("attr1", "value1");

    element->SetAttribute("attr2", "value2");

    element->DeleteAttribute("attr1");

    element->DeleteAttribute("attr2");

    EXPECT_EQ(element->FindAttribute("attr1"), nullptr);

    EXPECT_EQ(element->FindAttribute("attr2"), nullptr);

}
