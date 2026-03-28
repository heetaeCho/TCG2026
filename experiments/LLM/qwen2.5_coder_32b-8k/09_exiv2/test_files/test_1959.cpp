#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming XML_Node and related constants are included from their respective headers



class PickBestRootTest_1959 : public ::testing::Test {

protected:

    std::vector<XML_Node*> content;

    XML_Node xmlParent;



    void SetUp() override {

        xmlParent.content = content;

    }



    void TearDown() override {

        for (auto node : content) {

            delete node;

        }

        content.clear();

    }

};



TEST_F(PickBestRootTest_1959, NormalOperation_XMPMetaFound_1959) {

    XML_Node* xmpmetaNode = new XML_Node(nullptr, "x:xmpmeta", kElemNode);

    content.push_back(xmpmetaNode);



    const XML_Node* result = PickBestRoot(xmlParent, 0);

    EXPECT_EQ(result, xmpmetaNode);

}



TEST_F(PickBestRootTest_1959, NormalOperation_XAPMetaFound_1959) {

    XML_Node* xapmetaNode = new XML_Node(nullptr, "x:xapmeta", kElemNode);

    content.push_back(xapmetaNode);



    const XML_Node* result = PickBestRoot(xmlParent, 0);

    EXPECT_EQ(result, xapmetaNode);

}



TEST_F(PickBestRootTest_1959, NormalOperation_RDFRDFFoundWithoutXMPMeta_1959) {

    XML_Node* rdfRdfNode = new XML_Node(nullptr, "rdf:RDF", kElemNode);

    content.push_back(rdfRdfNode);



    const XML_Node* result = PickBestRoot(xmlParent, 0);

    EXPECT_EQ(result, rdfRdfNode);

}



TEST_F(PickBestRootTest_1959, NormalOperation_NoXMPMetaOrRDFRDF_1959) {

    XML_Node* otherNode = new XML_Node(nullptr, "other", kElemNode);

    content.push_back(otherNode);



    const XML_Node* result = PickBestRoot(xmlParent, 0);

    EXPECT_EQ(result, nullptr);

}



TEST_F(PickBestRootTest_1959, Boundary_NoChildren_1959) {

    const XML_Node* result = PickBestRoot(xmlParent, 0);

    EXPECT_EQ(result, nullptr);

}



TEST_F(PickBestRootTest_1959, Exceptional_RequireXMPMetaWithoutXMPMetaOrRDFRDF_1959) {

    XML_Node* otherNode = new XML_Node(nullptr, "other", kElemNode);

    content.push_back(otherNode);



    const XML_Node* result = PickBestRoot(xmlParent, kXMP_RequireXMPMeta);

    EXPECT_EQ(result, nullptr);

}



TEST_F(PickBestRootTest_1959, RecursiveCall_ReturnsValidRoot_1959) {

    XML_Node* childNode = new XML_Node(&xmlParent, "child", kElemNode);

    XML_Node* xmpmetaNode = new XML_Node(childNode, "x:xmpmeta", kElemNode);



    content.push_back(childNode);

    childNode->content.push_back(xmpmetaNode);



    const XML_Node* result = PickBestRoot(xmlParent, 0);

    EXPECT_EQ(result, xmpmetaNode);

}



TEST_F(PickBestRootTest_1959, RecursiveCall_ReturnsNullIfNoValidRoot_1959) {

    XML_Node* childNode = new XML_Node(&xmlParent, "child", kElemNode);



    content.push_back(childNode);



    const XML_Node* result = PickBestRoot(xmlParent, 0);

    EXPECT_EQ(result, nullptr);

}



TEST_F(PickBestRootTest_1959, NonElementNodesIgnored_1959) {

    XML_Node* textNode = new XML_Node(nullptr, "", kCDataNode);

    content.push_back(textNode);



    const XML_Node* result = PickBestRoot(xmlParent, 0);

    EXPECT_EQ(result, nullptr);

}
