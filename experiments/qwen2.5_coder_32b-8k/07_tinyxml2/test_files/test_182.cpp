#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLNodeTest_182 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* root;

    XMLElement* child1;

    XMLElement* child2;

    XMLElement* child3;



    void SetUp() override {

        root = doc.NewElement("Root");

        child1 = doc.NewElement("Child");

        child2 = doc.NewElement("Child");

        child3 = doc.NewElement("AnotherChild");



        root->InsertEndChild(child1);

        root->InsertEndChild(child2);

        root->InsertEndChild(child3);



        doc.InsertFirstChild(root);

    }

};



TEST_F(XMLNodeTest_182, ChildElementCount_NoChildren_182) {

    XMLNode emptyNode(&doc);

    EXPECT_EQ(emptyNode.ChildElementCount("Child"), 0);

}



TEST_F(XMLNodeTest_182, ChildElementCount_SpecificNameMatching_182) {

    EXPECT_EQ(root->ChildElementCount("Child"), 2);

}



TEST_F(XMLNodeTest_182, ChildElementCount_SpecificNameNonMatching_182) {

    EXPECT_EQ(root->ChildElementCount("AnotherChild"), 1);

}



TEST_F(XMLNodeTest_182, ChildElementCount_AllChildren_182) {

    EXPECT_EQ(root->ChildElementCount(), 3);

}



TEST_F(XMLNodeTest_182, ChildElementCount_EmptyStringName_182) {

    EXPECT_EQ(root->ChildElementCount(""), 0);

}
