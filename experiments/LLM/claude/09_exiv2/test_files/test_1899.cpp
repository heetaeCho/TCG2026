XMP_Node * FindNode(XMP_Node * xmpTree, const XMP_ExpandedXPath & expandedXPath, 
                     bool createNodes, XMP_OptionBits leafOptions = 0, 
                     XMP_NodePtrPos * ptrPos = 0);
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>

// Include necessary headers
#include "XMPCore_Impl.hpp"

// We need the XMP types and constants
#include "XMP_Const.h"

// Forward declarations for functions used
extern XMP_Node * FindNode(XMP_Node * xmpTree, const XMP_ExpandedXPath & expandedXPath,
                            bool createNodes, XMP_OptionBits leafOptions = 0,
                            XMP_NodePtrPos * ptrPos = 0);
extern XMP_Node * FindSchemaNode(XMP_Node * xmpTree, XMP_StringPtr schemaURI,
                                  bool createNodes, XMP_NodePtrPos * ptrPos = 0);
extern XMP_AliasMap * sRegisteredAliasMap;

class FindNodeTest_1899 : public ::testing::Test {
protected:
    void SetUp() override {
        xmpTree = new XMP_Node(nullptr, "xmpTree", 0);
        // Ensure the alias map exists
        if (sRegisteredAliasMap == nullptr) {
            sRegisteredAliasMap = new XMP_AliasMap();
        }
    }

    void TearDown() override {
        delete xmpTree;
        xmpTree = nullptr;
    }

    XMP_Node* xmpTree;
};

// Test 1: Empty XPath should throw kXMPErr_BadXPath
TEST_F(FindNodeTest_1899, EmptyXPathThrows_1899) {
    XMP_ExpandedXPath emptyPath;
    EXPECT_THROW(
        FindNode(xmpTree, emptyPath, false),
        XMP_Error
    );
}

// Test 2: Empty XPath throws with createNodes = true
TEST_F(FindNodeTest_1899, EmptyXPathThrowsWithCreateNodes_1899) {
    XMP_ExpandedXPath emptyPath;
    EXPECT_THROW(
        FindNode(xmpTree, emptyPath, true),
        XMP_Error
    );
}

// Test 3: Empty XPath throws the correct error code
TEST_F(FindNodeTest_1899, EmptyXPathThrowsCorrectErrorCode_1899) {
    XMP_ExpandedXPath emptyPath;
    try {
        FindNode(xmpTree, emptyPath, false);
        FAIL() << "Expected XMP_Error to be thrown";
    } catch (const XMP_Error& e) {
        EXPECT_EQ(e.GetID(), kXMPErr_BadXPath);
    }
}

// Test 4: Non-existent schema with createNodes=false returns null
TEST_F(FindNodeTest_1899, NonExistentSchemaNoCreateReturnsNull_1899) {
    XMP_ExpandedXPath path;
    path.push_back(XPathStepInfo("http://ns.example.com/", 0));  // schema step
    path.push_back(XPathStepInfo("http://ns.example.com/:prop", 0));  // root prop step (no alias)

    XMP_Node* result = FindNode(xmpTree, path, false);
    EXPECT_EQ(result, nullptr);
}

// Test 5: Schema node creation with createNodes=true for simple two-step path
TEST_F(FindNodeTest_1899, CreateSchemaAndPropertyNode_1899) {
    XMP_ExpandedXPath path;
    path.push_back(XPathStepInfo("http://ns.example.com/", 0));  // schema step
    path.push_back(XPathStepInfo("http://ns.example.com/:TestProp", kXMP_StructFieldStep));  // root prop step

    XMP_Node* result = FindNode(xmpTree, path, true);
    // With createNodes=true, we expect a non-null result
    EXPECT_NE(result, nullptr);
}

// Test 6: FindNode with createNodes=true and leafOptions set
TEST_F(FindNodeTest_1899, CreateNodeWithLeafOptions_1899) {
    XMP_ExpandedXPath path;
    path.push_back(XPathStepInfo("http://ns.test.com/", 0));  // schema step
    path.push_back(XPathStepInfo("http://ns.test.com/:Prop", kXMP_StructFieldStep));  // root prop step

    XMP_Node* result = FindNode(xmpTree, path, true, kXMP_PropValueIsArray);
    EXPECT_NE(result, nullptr);
    if (result) {
        EXPECT_TRUE((result->options & kXMP_PropValueIsArray) != 0);
    }
}

// Test 7: FindNode returns correct ptrPos
TEST_F(FindNodeTest_1899, PtrPosIsSetOnSuccess_1899) {
    XMP_ExpandedXPath path;
    path.push_back(XPathStepInfo("http://ns.ptrtest.com/", 0));
    path.push_back(XPathStepInfo("http://ns.ptrtest.com/:Item", kXMP_StructFieldStep));

    XMP_NodePtrPos ptrPos;
    XMP_Node* result = FindNode(xmpTree, path, true, 0, &ptrPos);
    EXPECT_NE(result, nullptr);
    if (result) {
        EXPECT_EQ(*ptrPos, result);
    }
}

// Test 8: FindNode with null tree and createNodes=false for non-existent path
TEST_F(FindNodeTest_1899, NonExistentPathNoCreateReturnsNull_1899) {
    // Add a schema node first but don't add the property
    XMP_Node* schema = new XMP_Node(xmpTree, "http://ns.exists.com/", kXMP_SchemaNode);
    xmpTree->children.push_back(schema);

    XMP_ExpandedXPath path;
    path.push_back(XPathStepInfo("http://ns.exists.com/", 0));
    path.push_back(XPathStepInfo("http://ns.exists.com/:NonExistent", kXMP_StructFieldStep));

    XMP_Node* result = FindNode(xmpTree, path, false);
    EXPECT_EQ(result, nullptr);
}

// Test 9: Repeated calls should find the same node
TEST_F(FindNodeTest_1899, RepeatedCallsFindSameNode_1899) {
    XMP_ExpandedXPath path;
    path.push_back(XPathStepInfo("http://ns.repeat.com/", 0));
    path.push_back(XPathStepInfo("http://ns.repeat.com/:RepeatProp", kXMP_StructFieldStep));

    XMP_Node* result1 = FindNode(xmpTree, path, true);
    EXPECT_NE(result1, nullptr);

    XMP_Node* result2 = FindNode(xmpTree, path, false);
    EXPECT_EQ(result1, result2);
}

// Test 10: Creating node then finding without create returns same node
TEST_F(FindNodeTest_1899, FindAfterCreateReturnsSameNode_1899) {
    XMP_ExpandedXPath path;
    path.push_back(XPathStepInfo("http://ns.findafter.com/", 0));
    path.push_back(XPathStepInfo("http://ns.findafter.com/:Prop", kXMP_StructFieldStep));

    XMP_Node* created = FindNode(xmpTree, path, true);
    ASSERT_NE(created, nullptr);

    XMP_Node* found = FindNode(xmpTree, path, false);
    EXPECT_EQ(created, found);
}

// Test 11: Null ptrPos does not crash
TEST_F(FindNodeTest_1899, NullPtrPosDoesNotCrash_1899) {
    XMP_ExpandedXPath path;
    path.push_back(XPathStepInfo("http://ns.nullptr.com/", 0));
    path.push_back(XPathStepInfo("http://ns.nullptr.com/:Prop", kXMP_StructFieldStep));

    EXPECT_NO_THROW(FindNode(xmpTree, path, true, 0, nullptr));
}

// Test 12: LeafOptions zero doesn't modify existing node options
TEST_F(FindNodeTest_1899, ZeroLeafOptionsOnExistingNode_1899) {
    XMP_ExpandedXPath path;
    path.push_back(XPathStepInfo("http://ns.zeroleaf.com/", 0));
    path.push_back(XPathStepInfo("http://ns.zeroleaf.com/:Prop", kXMP_StructFieldStep));

    // Create the node first
    XMP_Node* created = FindNode(xmpTree, path, true, kXMP_PropValueIsArray);
    ASSERT_NE(created, nullptr);

    // Find it again without creating
    XMP_Node* found = FindNode(xmpTree, path, false, 0);
    EXPECT_NE(found, nullptr);
}

// Test 13: Multiple different properties under same schema
TEST_F(FindNodeTest_1899, MultipleDifferentPropertiesSameSchema_1899) {
    XMP_ExpandedXPath path1;
    path1.push_back(XPathStepInfo("http://ns.multi.com/", 0));
    path1.push_back(XPathStepInfo("http://ns.multi.com/:Prop1", kXMP_StructFieldStep));

    XMP_ExpandedXPath path2;
    path2.push_back(XPathStepInfo("http://ns.multi.com/", 0));
    path2.push_back(XPathStepInfo("http://ns.multi.com/:Prop2", kXMP_StructFieldStep));

    XMP_Node* node1 = FindNode(xmpTree, path1, true);
    XMP_Node* node2 = FindNode(xmpTree, path2, true);

    EXPECT_NE(node1, nullptr);
    EXPECT_NE(node2, nullptr);
    EXPECT_NE(node1, node2);
}

// Test 14: Different schemas create different schema nodes
TEST_F(FindNodeTest_1899, DifferentSchemasCreateDifferentNodes_1899) {
    XMP_ExpandedXPath pathA;
    pathA.push_back(XPathStepInfo("http://ns.schemaA.com/", 0));
    pathA.push_back(XPathStepInfo("http://ns.schemaA.com/:Prop", kXMP_StructFieldStep));

    XMP_ExpandedXPath pathB;
    pathB.push_back(XPathStepInfo("http://ns.schemaB.com/", 0));
    pathB.push_back(XPathStepInfo("http://ns.schemaB.com/:Prop", kXMP_StructFieldStep));

    XMP_Node* nodeA = FindNode(xmpTree, pathA, true);
    XMP_Node* nodeB = FindNode(xmpTree, pathB, true);

    EXPECT_NE(nodeA, nullptr);
    EXPECT_NE(nodeB, nullptr);
    EXPECT_NE(nodeA, nodeB);
}
