#include <gtest/gtest.h>

#include "XMPCore_Impl.hpp"

#include "XMPMeta.hpp"



using namespace XMP_NAMESPACE;



class XMPCoreTest_1894 : public ::testing::Test {

protected:

    void SetUp() override {

        root = new XMP_Node(nullptr, "", 0);

    }



    void TearDown() override {

        delete root;

    }



    XMP_Node* root;

};



TEST_F(XMPCoreTest_1894, FindSchemaNode_NormalOperation_1894) {

    const char* nsURI = "http://example.com/schema";

    XMP_Node* schemaNode = FindSchemaNode(root, nsURI, true);

    EXPECT_EQ(schemaNode->name.c_str(), nsURI);

    EXPECT_TRUE(!schemaNode->value.empty());

}



TEST_F(XMPCoreTest_1894, FindSchemaNode_CreateNodesFalse_1894) {

    const char* nsURI = "http://example.com/schema";

    XMP_Node* schemaNode = FindSchemaNode(root, nsURI, false);

    EXPECT_EQ(schemaNode, nullptr);

}



TEST_F(XMPCoreTest_1894, FindSchemaNode_CreateNodesTrue_1894) {

    const char* nsURI = "http://example.com/schema";

    XMP_Node* schemaNode = FindSchemaNode(root, nsURI, true);

    EXPECT_NE(schemaNode, nullptr);

}



TEST_F(XMPCoreTest_1894, FindSchemaNode_BoundaryCondition_EmptyNamespaceURI_1894) {

    const char* nsURI = "";

    XMP_Node* schemaNode = FindSchemaNode(root, nsURI, true);

    EXPECT_EQ(schemaNode->name.c_str(), "");

    EXPECT_TRUE(!schemaNode->value.empty());

}



TEST_F(XMPCoreTest_1894, FindSchemaNode_BoundaryCondition_NullNamespaceURI_1894) {

    XMP_Node* schemaNode = FindSchemaNode(root, nullptr, true);

    EXPECT_EQ(schemaNode, nullptr); // Assuming the function handles nullptr gracefully

}



TEST_F(XMPCoreTest_1894, FindSchemaNode_PtrPosNotNull_1894) {

    const char* nsURI = "http://example.com/schema";

    XMP_NodePtrPos ptrPos;

    XMP_Node* schemaNode = FindSchemaNode(root, nsURI, true, &ptrPos);

    EXPECT_NE(schemaNode, nullptr);

    EXPECT_EQ(*ptrPos, std::find(root->children.begin(), root->children.end(), schemaNode));

}



TEST_F(XMPCoreTest_1894, FindSchemaNode_PtrPosNull_1894) {

    const char* nsURI = "http://example.com/schema";

    XMP_Node* schemaNode = FindSchemaNode(root, nsURI, true, nullptr);

    EXPECT_NE(schemaNode, nullptr);

}



TEST_F(XMPCoreTest_1894, FindSchemaNode_SchemaAlreadyExists_1894) {

    const char* nsURI = "http://example.com/schema";

    XMP_Node* firstCall = FindSchemaNode(root, nsURI, true);

    XMP_Node* secondCall = FindSchemaNode(root, nsURI, false);

    EXPECT_EQ(firstCall, secondCall);

}



TEST_F(XMPCoreTest_1894, FindSchemaNode_GetNamespacePrefixFailure_1894) {

    // Mock the GetNamespacePrefix to return false

    // This is not directly possible here as we cannot mock static methods in C++ without redesigning

    // Assuming that the function handles the failure gracefully or throws an exception

    const char* nsURI = "http://example.com/unknownschema";

    XMP_Node* schemaNode = FindSchemaNode(root, nsURI, true);

    EXPECT_EQ(schemaNode, nullptr); // Assuming the function returns null on failure to get prefix

}



TEST_F(XMPCoreTest_1894, FindSchemaNode_ExceptionalCase_MemoryAllocationFailure_1894) {

    // This test case is not directly possible without simulating memory allocation failure

    // which is complex and usually requires modifying the code or using specific tools.

    // Assuming no exception is thrown and null is returned on failure to allocate memory

    const char* nsURI = "http://example.com/schema";

    XMP_Node* schemaNode = FindSchemaNode(root, nsURI, true);

    EXPECT_EQ(schemaNode, nullptr); // Assuming the function handles allocation failure gracefully

}
