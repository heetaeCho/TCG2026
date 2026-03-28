#include "tinyxml2.h"

#include <gtest/gtest.h>



using namespace tinyxml2;



// Test fixture for XMLElement tests

class XMLElementTest_266 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* element1;

    XMLElement* element2;



    void SetUp() override {

        element1 = new XMLElement(&doc);

        element2 = new XMLElement(&doc);

    }



    void TearDown() override {

        delete element1;

        delete element2;

    }

};



// Test normal operation of ShallowEqual with identical elements

TEST_F(XMLElementTest_266, ShallowEqual_IdenticalElements_266) {

    element1->SetName("test");

    element2->SetName("test");



    XMLAttribute* attr1 = new XMLAttribute();

    attr1->SetName("attr");

    attr1->SetValue("value");

    element1->SetAttribute(attr1);



    XMLAttribute* attr2 = new XMLAttribute();

    attr2->SetName("attr");

    attr2->SetValue("value");

    element2->SetAttribute(attr2);



    EXPECT_TRUE(element1->ShallowEqual(element2));

}



// Test normal operation of ShallowEqual with different names

TEST_F(XMLElementTest_266, ShallowEqual_DifferentNames_266) {

    element1->SetName("test1");

    element2->SetName("test2");



    EXPECT_FALSE(element1->ShallowEqual(element2));

}



// Test normal operation of ShallowEqual with different attributes

TEST_F(XMLElementTest_266, ShallowEqual_DifferentAttributes_266) {

    element1->SetName("test");

    element2->SetName("test");



    XMLAttribute* attr1 = new XMLAttribute();

    attr1->SetName("attr");

    attr1->SetValue("value");

    element1->SetAttribute(attr1);



    XMLAttribute* attr2 = new XMLAttribute();

    attr2->SetName("attr");

    attr2->SetValue("different_value");

    element2->SetAttribute(attr2);



    EXPECT_FALSE(element1->ShallowEqual(element2));

}



// Test boundary condition of ShallowEqual with one attribute missing

TEST_F(XMLElementTest_266, ShallowEqual_OneAttributeMissing_266) {

    element1->SetName("test");

    element2->SetName("test");



    XMLAttribute* attr = new XMLAttribute();

    attr->SetName("attr");

    attr->SetValue("value");

    element1->SetAttribute(attr);



    EXPECT_FALSE(element1->ShallowEqual(element2));

}



// Test boundary condition of ShallowEqual with no attributes

TEST_F(XMLElementTest_266, ShallowEqual_NoAttributes_266) {

    element1->SetName("test");

    element2->SetName("test");



    EXPECT_TRUE(element1->ShallowEqual(element2));

}



// Test exceptional case of ShallowEqual with null comparison

TEST_F(XMLElementTest_266, ShallowEqual_NullComparison_266) {

    EXPECT_FALSE(element1->ShallowEqual(nullptr));

}
