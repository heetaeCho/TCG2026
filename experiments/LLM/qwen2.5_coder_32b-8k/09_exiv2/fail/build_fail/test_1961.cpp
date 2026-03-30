#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming XMP_Node and related classes/functions are already included in the build system



class XMPMeta_ParseTest_1961 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary objects or state here

        xmpTree = new XMP_Node(nullptr, "root", 0);

    }



    void TearDown() override {

        // Clean up any allocated resources here

        delete xmpTree;

    }



    XMP_Node* xmpTree;

};



TEST_F(XMPMeta_ParseTest_1961, NormalizeDCArrays_NoDcSchema_1961) {

    NormalizeDCArrays(xmpTree);

    EXPECT_EQ(xmpTree->children.size(), 0);

}



TEST_F(XMPMeta_ParseTest_1961, NormalizeDCArrays_DcSchemaNoChildren_1961) {

    XMP_Node* dcSchema = new XMP_Node(xmpTree, kXMP_NS_DC, 0);

    xmpTree->children.push_back(dcSchema);



    NormalizeDCArrays(xmpTree);

    EXPECT_EQ(dcSchema->children.size(), 0);



    delete dcSchema;

}



TEST_F(XMPMeta_ParseTest_1961, NormalizeDCArrays_DcCreatorSimple_1961) {

    XMP_Node* dcSchema = new XMP_Node(xmpTree, kXMP_NS_DC, 0);

    xmpTree->children.push_back(dcSchema);



    XMP_Node* creatorNode = new XMP_Node(dcSchema, "dc:creator", "John Doe", 0);

    dcSchema->children.push_back(creatorNode);



    NormalizeDCArrays(xmpTree);

    EXPECT_EQ(dcSchema->children.size(), 1);

    XMP_Node* newArray = dcSchema->children[0];

    EXPECT_EQ(newArray->name, "dc:creator");

    EXPECT_TRUE((newArray->options & kXMP_PropArrayIsOrdered) != 0);

    EXPECT_EQ(newArray->children.size(), 1);

    EXPECT_EQ(newArray->children[0]->name, kXMP_ArrayItemName);

    EXPECT_EQ(newArray->children[0]->value, "John Doe");



    delete creatorNode;

    delete newArray;

    delete dcSchema;

}



TEST_F(XMPMeta_ParseTest_1961, NormalizeDCArrays_DcDescriptionSimple_1961) {

    XMP_Node* dcSchema = new XMP_Node(xmpTree, kXMP_NS_DC, 0);

    xmpTree->children.push_back(dcSchema);



    XMP_Node* descriptionNode = new XMP_Node(dcSchema, "dc:description", "Sample Description", 0);

    dcSchema->children.push_back(descriptionNode);



    NormalizeDCArrays(xmpTree);

    EXPECT_EQ(dcSchema->children.size(), 1);

    XMP_Node* newArray = dcSchema->children[0];

    EXPECT_EQ(newArray->name, "dc:description");

    EXPECT_TRUE((newArray->options & kXMP_PropArrayIsAltText) != 0);

    EXPECT_EQ(newArray->children.size(), 1);

    EXPECT_EQ(newArray->children[0]->name, kXMP_ArrayItemName);

    EXPECT_EQ(newArray->children[0]->value, "Sample Description");

    EXPECT_TRUE((newArray->children[0]->options & kXMP_PropHasQualifiers) != 0);

    EXPECT_TRUE((newArray->children[0]->options & kXMP_PropHasLang) != 0);

    EXPECT_EQ(newArray->children[0]->qualifiers.size(), 1);

    EXPECT_EQ(newArray->children[0]->qualifiers[0]->name, "xml:lang");

    EXPECT_EQ(newArray->children[0]->qualifiers[0]->value, "x-default");



    delete descriptionNode;

    delete newArray;

    delete dcSchema;

}



TEST_F(XMPMeta_ParseTest_1961, NormalizeDCArrays_DcContributorComplex_1961) {

    XMP_Node* dcSchema = new XMP_Node(xmpTree, kXMP_NS_DC, 0);

    xmpTree->children.push_back(dcSchema);



    XMP_Node* contributorNode = new XMP_Node(dcSchema, "dc:contributor", "Jane Doe", kXMP_PropArrayIsOrdered);

    dcSchema->children.push_back(contributorNode);



    NormalizeDCArrays(xmpTree);

    EXPECT_EQ(dcSchema->children.size(), 1);

    XMP_Node* newArray = dcSchema->children[0];

    EXPECT_EQ(newArray->name, "dc:contributor");

    EXPECT_TRUE((newArray->options & kXMP_PropValueIsArray) != 0);

    EXPECT_EQ(newArray->children.size(), 1);

    EXPECT_EQ(newArray->children[0]->name, kXMP_ArrayItemName);

    EXPECT_EQ(newArray->children[0]->value, "Jane Doe");



    delete contributorNode;

    delete newArray;

    delete dcSchema;

}
