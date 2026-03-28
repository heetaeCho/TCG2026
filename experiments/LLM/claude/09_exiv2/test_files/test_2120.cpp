#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <map>

// Include necessary headers
#include "XMP_Const.h"
#include "XMPCore_Impl.hpp"
#include "XMLParserAdapter.hpp"

// We need access to internal functions and types from ParseRDF.cpp
// Since AddChildNode is static, we need to include the source or use a workaround

// Forward declarations and constants needed
static const XMP_OptionBits kRDF_HasValueElem = 0x10000000UL;
static const XMP_OptionBits kXMP_NewImplicitNode = 0x80000000UL;
static const char* kXMP_ArrayItemName = "[]";

// External dependencies we need
extern XMP_AliasMap* sRegisteredAliasMap;

// Helper to find/create schema nodes and child nodes
extern XMP_Node* FindSchemaNode(XMP_Node* xmpTree, XMP_StringPtr nsURI, bool createNodes);
extern XMP_Node* FindChildNode(XMP_Node* xmpParent, XMP_StringPtr childName, bool createNode);

// Include the function under test
// Since AddChildNode is static in ParseRDF.cpp, we include it for testing
// In practice, this would need a test-friendly build configuration
#include "ParseRDF.cpp"

class AddChildNodeTest_2120 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure sRegisteredAliasMap exists
        if (sRegisteredAliasMap == nullptr) {
            sRegisteredAliasMap = new XMP_AliasMap();
        }
    }

    void TearDown() override {
        // Cleanup
    }

    // Helper to create a basic XML_Node with namespace set
    XML_Node* createXMLNode(XML_NodePtr parent, const std::string& name, const std::string& ns) {
        XML_Node* node = new XML_Node(parent, name.c_str(), 0);
        node->ns = ns;
        return node;
    }
};

// Test: Empty namespace should throw kXMPErr_BadRDF
TEST_F(AddChildNodeTest_2120, EmptyNamespaceThrows_2120) {
    XMP_Node treeRoot(nullptr, "root", 0);
    XMP_Node parentNode(&treeRoot, "parent", kXMP_PropValueIsStruct);

    XML_Node xmlNode(nullptr, "testProp", 0);
    xmlNode.ns = "";  // Empty namespace

    EXPECT_THROW(
        AddChildNode(&parentNode, xmlNode, "value", false),
        XMP_Error
    );
}

// Test: Normal child addition (not top level, not array item, not value node)
TEST_F(AddChildNodeTest_2120, NormalChildAddition_2120) {
    XMP_Node treeRoot(nullptr, "", 0);
    XMP_Node parentNode(&treeRoot, "parent", kXMP_PropValueIsStruct);

    XML_Node xmlNode(nullptr, "dc:title", 0);
    xmlNode.ns = "http://purl.org/dc/elements/1.1/";

    XMP_Node* result = AddChildNode(&parentNode, xmlNode, "test value", false);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->name, "dc:title");
    EXPECT_EQ(result->value, "test value");
    EXPECT_EQ(result->parent, &parentNode);
    EXPECT_EQ(parentNode.children.size(), 1u);
    EXPECT_EQ(parentNode.children[0], result);
}

// Test: Duplicate property should throw kXMPErr_BadXMP
TEST_F(AddChildNodeTest_2120, DuplicatePropertyThrows_2120) {
    XMP_Node treeRoot(nullptr, "", 0);
    XMP_Node parentNode(&treeRoot, "parent", kXMP_PropValueIsStruct);

    XML_Node xmlNode(nullptr, "dc:title", 0);
    xmlNode.ns = "http://purl.org/dc/elements/1.1/";

    // Add first child
    AddChildNode(&parentNode, xmlNode, "value1", false);

    // Adding duplicate should throw
    EXPECT_THROW(
        AddChildNode(&parentNode, xmlNode, "value2", false),
        XMP_Error
    );
}

// Test: rdf:li element added to array parent
TEST_F(AddChildNodeTest_2120, ArrayItemAddition_2120) {
    XMP_Node treeRoot(nullptr, "", 0);
    XMP_Node parentNode(&treeRoot, "parent", kXMP_PropValueIsArray);

    XML_Node xmlNode(nullptr, "rdf:li", 0);
    xmlNode.ns = "http://www.w3.org/1999/02/22-rdf-syntax-ns#";

    XMP_Node* result = AddChildNode(&parentNode, xmlNode, "item value", false);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->name, kXMP_ArrayItemName);
    EXPECT_EQ(result->value, "item value");
    EXPECT_EQ(parentNode.children.size(), 1u);
}

// Test: rdf:li on non-array parent should throw
TEST_F(AddChildNodeTest_2120, ArrayItemOnNonArrayThrows_2120) {
    XMP_Node treeRoot(nullptr, "", 0);
    XMP_Node parentNode(&treeRoot, "parent", kXMP_PropValueIsStruct);

    XML_Node xmlNode(nullptr, "rdf:li", 0);
    xmlNode.ns = "http://www.w3.org/1999/02/22-rdf-syntax-ns#";

    EXPECT_THROW(
        AddChildNode(&parentNode, xmlNode, "item value", false),
        XMP_Error
    );
}

// Test: rdf:value on struct parent (not top level)
TEST_F(AddChildNodeTest_2120, ValueNodeOnStruct_2120) {
    XMP_Node treeRoot(nullptr, "", 0);
    XMP_Node parentNode(&treeRoot, "parent", kXMP_PropValueIsStruct);

    XML_Node xmlNode(nullptr, "rdf:value", 0);
    xmlNode.ns = "http://www.w3.org/1999/02/22-rdf-syntax-ns#";

    XMP_Node* result = AddChildNode(&parentNode, xmlNode, "val", false);

    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(parentNode.options & kRDF_HasValueElem);
}

// Test: rdf:value at top level should throw
TEST_F(AddChildNodeTest_2120, ValueNodeAtTopLevelThrows_2120) {
    XMP_Node treeRoot(nullptr, "", 0);
    treeRoot.parent = nullptr;

    XML_Node xmlNode(nullptr, "rdf:value", 0);
    xmlNode.ns = "http://purl.org/dc/elements/1.1/";

    EXPECT_THROW(
        AddChildNode(&treeRoot, xmlNode, "val", true),
        XMP_Error
    );
}

// Test: rdf:value on non-struct parent should throw
TEST_F(AddChildNodeTest_2120, ValueNodeOnNonStructThrows_2120) {
    XMP_Node treeRoot(nullptr, "", 0);
    XMP_Node parentNode(&treeRoot, "parent", 0);  // Not a struct

    XML_Node xmlNode(nullptr, "rdf:value", 0);
    xmlNode.ns = "http://www.w3.org/1999/02/22-rdf-syntax-ns#";

    EXPECT_THROW(
        AddChildNode(&parentNode, xmlNode, "val", false),
        XMP_Error
    );
}

// Test: rdf:value inserted at beginning when children already exist
TEST_F(AddChildNodeTest_2120, ValueNodeInsertedAtBeginning_2120) {
    XMP_Node treeRoot(nullptr, "", 0);
    XMP_Node parentNode(&treeRoot, "parent", kXMP_PropValueIsStruct);

    // Add an existing child first
    XML_Node xmlNode1(nullptr, "dc:creator", 0);
    xmlNode1.ns = "http://purl.org/dc/elements/1.1/";
    XMP_Node* first = AddChildNode(&parentNode, xmlNode1, "existing", false);

    // Now add rdf:value - should be inserted at beginning
    XML_Node xmlNodeValue(nullptr, "rdf:value", 0);
    xmlNodeValue.ns = "http://www.w3.org/1999/02/22-rdf-syntax-ns#";
    XMP_Node* valueNode = AddChildNode(&parentNode, xmlNodeValue, "the value", false);

    ASSERT_EQ(parentNode.children.size(), 2u);
    EXPECT_EQ(parentNode.children[0], valueNode);
    EXPECT_EQ(parentNode.children[1], first);
}

// Test: Multiple rdf:li items can be added to the same array parent
TEST_F(AddChildNodeTest_2120, MultipleArrayItems_2120) {
    XMP_Node treeRoot(nullptr, "", 0);
    XMP_Node parentNode(&treeRoot, "parent", kXMP_PropValueIsArray);

    XML_Node xmlNode(nullptr, "rdf:li", 0);
    xmlNode.ns = "http://www.w3.org/1999/02/22-rdf-syntax-ns#";

    XMP_Node* item1 = AddChildNode(&parentNode, xmlNode, "item1", false);
    XMP_Node* item2 = AddChildNode(&parentNode, xmlNode, "item2", false);
    XMP_Node* item3 = AddChildNode(&parentNode, xmlNode, "item3", false);

    ASSERT_EQ(parentNode.children.size(), 3u);
    EXPECT_EQ(item1->name, kXMP_ArrayItemName);
    EXPECT_EQ(item2->name, kXMP_ArrayItemName);
    EXPECT_EQ(item3->name, kXMP_ArrayItemName);
    EXPECT_EQ(item1->value, "item1");
    EXPECT_EQ(item2->value, "item2");
    EXPECT_EQ(item3->value, "item3");
}

// Test: Top level addition creates/uses schema node
TEST_F(AddChildNodeTest_2120, TopLevelAddition_2120) {
    XMP_Node treeRoot(nullptr, "", 0);
    treeRoot.parent = nullptr;  // Tree root has no parent

    XML_Node xmlNode(nullptr, "dc:title", 0);
    xmlNode.ns = "http://purl.org/dc/elements/1.1/";

    XMP_Node* result = AddChildNode(&treeRoot, xmlNode, "top level value", true);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->name, "dc:title");
    EXPECT_EQ(result->value, "top level value");
}

// Test: Empty value for child node
TEST_F(AddChildNodeTest_2120, EmptyValueChild_2120) {
    XMP_Node treeRoot(nullptr, "", 0);
    XMP_Node parentNode(&treeRoot, "parent", kXMP_PropValueIsStruct);

    XML_Node xmlNode(nullptr, "dc:description", 0);
    xmlNode.ns = "http://purl.org/dc/elements/1.1/";

    XMP_Node* result = AddChildNode(&parentNode, xmlNode, "", false);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->value, "");
    EXPECT_EQ(result->name, "dc:description");
}

// Test: rdf:value on empty parent children list gets appended (not inserted)
TEST_F(AddChildNodeTest_2120, ValueNodeOnEmptyChildrenAppended_2120) {
    XMP_Node treeRoot(nullptr, "", 0);
    XMP_Node parentNode(&treeRoot, "parent", kXMP_PropValueIsStruct);

    ASSERT_TRUE(parentNode.children.empty());

    XML_Node xmlNodeValue(nullptr, "rdf:value", 0);
    xmlNodeValue.ns = "http://www.w3.org/1999/02/22-rdf-syntax-ns#";
    XMP_Node* valueNode = AddChildNode(&parentNode, xmlNodeValue, "the value", false);

    ASSERT_EQ(parentNode.children.size(), 1u);
    EXPECT_EQ(parentNode.children[0], valueNode);
}
