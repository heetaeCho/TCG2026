#include <gtest/gtest.h>

#include "XMPCore_Impl.hpp"

#include "XMPMeta-Serialize.cpp"



class EstimateRDFSizeTest_2104 : public ::testing::Test {

protected:

    XMP_Node* root;



    void SetUp() override {

        root = new XMP_Node(nullptr, "root", 0);

    }



    void TearDown() override {

        delete root;

    }

};



TEST_F(EstimateRDFSizeTest_2104, BasicLeafNode_2104) {

    size_t result = EstimateRDFSize(root, 0, 2);

    EXPECT_EQ(result, 8); // 2 * (0*2 + "root".size() + 4)

}



TEST_F(EstimateRDFSizeTest_2104, LeafNodeWithIndent_2104) {

    size_t result = EstimateRDFSize(root, 1, 2);

    EXPECT_EQ(result, 16); // 2 * (1*2 + "root".size() + 4)

}



TEST_F(EstimateRDFSizeTest_2104, NodeWithQualifiers_2104) {

    XMP_Node* qualifier = new XMP_Node(root, "qualifier", kXMP_PropHasQualifiers);

    root->qualifiers.push_back(qualifier);

    size_t result = EstimateRDFSize(root, 0, 2);

    delete qualifier;

    EXPECT_EQ(result, 56); 

    // 8 for root + 32 for rdf:Description and rdf:value tags + 16 for qualifier

}



TEST_F(EstimateRDFSizeTest_2104, NodeWithStructValue_2104) {

    root->options = kXMP_PropValueIsStruct;

    size_t result = EstimateRDFSize(root, 0, 2);

    EXPECT_EQ(result, 28); 

    // 8 for root + 20 for rdf:Description tags

}



TEST_F(EstimateRDFSizeTest_2104, NodeWithArrayValue_2104) {

    root->options = kXMP_PropValueIsArray;

    XMP_Node* child1 = new XMP_Node(root, "item1", 0);

    XMP_Node* child2 = new XMP_Node(root, "item2", 0);

    root->children.push_back(child1);

    root->children.push_back(child2);



    size_t result = EstimateRDFSize(root, 0, 2);

    delete child1;

    delete child2;



    EXPECT_EQ(result, 56); 

    // 8 for root + 24 for rdf:Bag tags + 24 for two rdf:li tags

}



TEST_F(EstimateRDFSizeTest_2104, NodeWithChildren_2104) {

    XMP_Node* child = new XMP_Node(root, "child", 0);

    root->children.push_back(child);



    size_t result = EstimateRDFSize(root, 0, 2);

    delete child;



    EXPECT_EQ(result, 16); 

    // 8 for root + 8 for child

}



TEST_F(EstimateRDFSizeTest_2104, ComplexStructureWithIndent_2104) {

    XMP_Node* structChild = new XMP_Node(root, "structChild", kXMP_PropValueIsStruct);

    XMP_Node* arrayChild = new XMP_Node(structChild, "arrayChild", kXMP_PropValueIsArray);

    XMP_Node* item1 = new XMP_Node(arrayChild, "item1", 0);

    XMP_Node* item2 = new XMP_Node(arrayChild, "item2", 0);



    root->children.push_back(structChild);

    arrayChild->children.push_back(item1);

    arrayChild->children.push_back(item2);



    size_t result = EstimateRDFSize(root, 1, 2);

    

    delete item1;

    delete item2;

    delete arrayChild;

    delete structChild;



    EXPECT_EQ(result, 136); 

    // 8 for root + 40 for structChild (including rdf:Description) 

    // + 56 for arrayChild (including rdf:Bag and two rdf:li)

}



TEST_F(EstimateRDFSizeTest_2104, ZeroIndentLength_2104) {

    size_t result = EstimateRDFSize(root, 1, 0);

    EXPECT_EQ(result, 8); 

    // 8 for root (no indentation length)

}
