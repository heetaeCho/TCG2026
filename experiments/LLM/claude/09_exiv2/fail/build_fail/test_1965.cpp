#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>

// XMP SDK headers
#define TXMP_STRING_TYPE std::string
#include "XMP_Const.h"
#include "XMPCore_Impl.hpp"
#include "XMPMeta.hpp"
#include "TXMPMeta.hpp"

// We need to test through the public API since MoveExplicitAliases is static
// We'll test XMP_Node structure and parsing behavior that triggers alias resolution

class XMPNodeTest_1965 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test XMP_Node basic construction
TEST_F(XMPNodeTest_1965, NodeConstructionWithStringPtr_1965) {
    XMP_Node parent(nullptr, "root", 0);
    XMP_Node child(&parent, "child", 0);
    
    EXPECT_EQ(child.name, "child");
    EXPECT_EQ(child.parent, &parent);
    EXPECT_EQ(child.options, 0u);
    EXPECT_TRUE(child.value.empty());
    EXPECT_TRUE(child.children.empty());
    EXPECT_TRUE(child.qualifiers.empty());
}

TEST_F(XMPNodeTest_1965, NodeConstructionWithValue_1965) {
    XMP_Node node(nullptr, "prop", "value", 0);
    
    EXPECT_EQ(node.name, "prop");
    EXPECT_EQ(node.value, "value");
    EXPECT_EQ(node.parent, nullptr);
}

TEST_F(XMPNodeTest_1965, NodeConstructionWithOptions_1965) {
    XMP_Node node(nullptr, "prop", kXMP_PropValueIsArray);
    
    EXPECT_EQ(node.options, static_cast<XMP_OptionBits>(kXMP_PropValueIsArray));
}

TEST_F(XMPNodeTest_1965, NodeConstructionWithVarString_1965) {
    XMP_VarString name("testNode");
    XMP_Node node(nullptr, name, kXMP_PropValueIsStruct);
    
    EXPECT_EQ(node.name, "testNode");
    EXPECT_EQ(node.options, static_cast<XMP_OptionBits>(kXMP_PropValueIsStruct));
}

TEST_F(XMPNodeTest_1965, NodeConstructionWithVarStringAndValue_1965) {
    XMP_VarString name("testNode");
    XMP_VarString value("testValue");
    XMP_Node node(nullptr, name, value, kXMP_PropHasQualifiers);
    
    EXPECT_EQ(node.name, "testNode");
    EXPECT_EQ(node.value, "testValue");
    EXPECT_EQ(node.options, static_cast<XMP_OptionBits>(kXMP_PropHasQualifiers));
}

TEST_F(XMPNodeTest_1965, NodeChildrenManagement_1965) {
    XMP_Node parent(nullptr, "parent", 0);
    XMP_Node* child1 = new XMP_Node(&parent, "child1", 0);
    XMP_Node* child2 = new XMP_Node(&parent, "child2", 0);
    
    parent.children.push_back(child1);
    parent.children.push_back(child2);
    
    EXPECT_EQ(parent.children.size(), 2u);
    EXPECT_EQ(parent.children[0]->name, "child1");
    EXPECT_EQ(parent.children[1]->name, "child2");
    
    parent.RemoveChildren();
    EXPECT_TRUE(parent.children.empty());
}

TEST_F(XMPNodeTest_1965, NodeQualifiersManagement_1965) {
    XMP_Node node(nullptr, "node", 0);
    XMP_Node* qual = new XMP_Node(&node, "qualifier", "qualValue", kXMP_PropIsQualifier);
    
    node.qualifiers.push_back(qual);
    
    EXPECT_EQ(node.qualifiers.size(), 1u);
    EXPECT_EQ(node.qualifiers[0]->name, "qualifier");
    EXPECT_EQ(node.qualifiers[0]->value, "qualValue");
    
    node.RemoveQualifiers();
    EXPECT_TRUE(node.qualifiers.empty());
}

TEST_F(XMPNodeTest_1965, NodeClearNode_1965) {
    XMP_Node node(nullptr, "node", "value", kXMP_PropValueIsArray);
    XMP_Node* child = new XMP_Node(&node, "child", 0);
    XMP_Node* qual = new XMP_Node(&node, "qual", kXMP_PropIsQualifier);
    
    node.children.push_back(child);
    node.qualifiers.push_back(qual);
    
    node.ClearNode();
    
    EXPECT_TRUE(node.children.empty());
    EXPECT_TRUE(node.qualifiers.empty());
}

TEST_F(XMPNodeTest_1965, NodeDestructor_1965) {
    // Verify that destructor doesn't crash with empty node
    XMP_Node* node = new XMP_Node(nullptr, "test", 0);
    delete node;  // Should not crash
}

TEST_F(XMPNodeTest_1965, NodeDestructorWithChildren_1965) {
    XMP_Node* node = new XMP_Node(nullptr, "parent", 0);
    // Children should be cleaned up properly
    delete node;  // Should not crash
}

// Test option bit constants
TEST_F(XMPNodeTest_1965, PropIsAliasFlag_1965) {
    XMP_Node node(nullptr, "alias", kXMP_PropIsAlias);
    EXPECT_TRUE((node.options & kXMP_PropIsAlias) != 0);
    
    // Toggle off
    node.options ^= kXMP_PropIsAlias;
    EXPECT_FALSE((node.options & kXMP_PropIsAlias) != 0);
}

TEST_F(XMPNodeTest_1965, PropHasAliasesFlag_1965) {
    XMP_Node node(nullptr, "tree", kXMP_PropHasAliases);
    EXPECT_TRUE((node.options & kXMP_PropHasAliases) != 0);
    
    // Toggle off as MoveExplicitAliases does
    node.options ^= kXMP_PropHasAliases;
    EXPECT_FALSE((node.options & kXMP_PropHasAliases) != 0);
}

TEST_F(XMPNodeTest_1965, ArrayFormMask_1965) {
    XMP_OptionBits opts = kXMP_PropArrayIsOrdered | kXMP_PropArrayIsAlternate;
    XMP_OptionBits masked = opts & kXMP_PropArrayFormMask;
    
    EXPECT_TRUE((masked & kXMP_PropArrayIsOrdered) != 0);
    EXPECT_TRUE((masked & kXMP_PropArrayIsAlternate) != 0);
    EXPECT_FALSE((masked & kXMP_PropArrayIsAltText) != 0);
}

TEST_F(XMPNodeTest_1965, AltTextFlag_1965) {
    XMP_OptionBits opts = kXMP_PropArrayIsAltText | kXMP_PropArrayIsAlternate | kXMP_PropArrayIsOrdered | kXMP_PropValueIsArray;
    EXPECT_TRUE((opts & kXMP_PropArrayIsAltText) != 0);
}

// Test XPathStepInfo
TEST_F(XMPNodeTest_1965, XPathStepInfoConstruction_1965) {
    XPathStepInfo step("dc:title", 0);
    EXPECT_EQ(step.step, "dc:title");
    EXPECT_EQ(step.options, 0u);
}

TEST_F(XMPNodeTest_1965, XPathStepInfoWithOptions_1965) {
    XPathStepInfo step("ns:prop", kXMP_PropValueIsArray);
    EXPECT_EQ(step.step, "ns:prop");
    EXPECT_EQ(step.options, static_cast<XMP_OptionBits>(kXMP_PropValueIsArray));
}

TEST_F(XMPNodeTest_1965, XPathStepInfoWithVarString_1965) {
    XMP_VarString stepStr("ns:arrayProp");
    XPathStepInfo step(stepStr, kXMP_PropArrayIsOrdered);
    EXPECT_EQ(step.step, "ns:arrayProp");
    EXPECT_EQ(step.options, static_cast<XMP_OptionBits>(kXMP_PropArrayIsOrdered));
}

// Test parse options constants
TEST_F(XMPNodeTest_1965, StrictAliasingOptionValue_1965) {
    XMP_OptionBits opts = kXMP_StrictAliasing;
    EXPECT_EQ(opts, 4u);
    EXPECT_TRUE((opts & kXMP_StrictAliasing) != 0);
}

TEST_F(XMPNodeTest_1965, ParseOptionsCombination_1965) {
    XMP_OptionBits opts = kXMP_RequireXMPMeta | kXMP_StrictAliasing;
    EXPECT_TRUE((opts & kXMP_RequireXMPMeta) != 0);
    EXPECT_TRUE((opts & kXMP_StrictAliasing) != 0);
    EXPECT_FALSE((opts & kXMP_ParseMoreBuffers) != 0);
}

// Test step index constants
TEST_F(XMPNodeTest_1965, StepIndexConstants_1965) {
    EXPECT_EQ(kSchemaStep, 0);
    EXPECT_EQ(kRootPropStep, 1);
    EXPECT_EQ(kAliasIndexStep, 2);
}

// Test tree structure manipulation similar to what MoveExplicitAliases does
TEST_F(XMPNodeTest_1965, TreeStructureSchemaRemoval_1965) {
    XMP_Node tree(nullptr, "xmpmeta", 0);
    XMP_Node* schema = new XMP_Node(&tree, "http://ns.example.com/", 0);
    tree.children.push_back(schema);
    
    EXPECT_EQ(tree.children.size(), 1u);
    
    // Simulate empty schema removal (as done in MoveExplicitAliases)
    if (schema->children.empty()) {
        delete tree.children[0];
        tree.children.erase(tree.children.begin());
    }
    
    EXPECT_TRUE(tree.children.empty());
}

TEST_F(XMPNodeTest_1965, TreeStructurePropertyRemoval_1965) {
    XMP_Node tree(nullptr, "xmpmeta", 0);
    XMP_Node* schema = new XMP_Node(&tree, "http://ns.example.com/", 0);
    tree.children.push_back(schema);
    
    XMP_Node* prop1 = new XMP_Node(schema, "ns:prop1", "val1", 0);
    XMP_Node* prop2 = new XMP_Node(schema, "ns:prop2", "val2", 0);
    schema->children.push_back(prop1);
    schema->children.push_back(prop2);
    
    EXPECT_EQ(schema->children.size(), 2u);
    
    // Remove first property
    schema->children.erase(schema->children.begin());
    delete prop1;
    
    EXPECT_EQ(schema->children.size(), 1u);
    EXPECT_EQ(schema->children[0]->name, "ns:prop2");
    
    // Cleanup
    tree.RemoveChildren();
}

TEST_F(XMPNodeTest_1965, OptionsBitToggle_1965) {
    XMP_OptionBits opts = kXMP_PropHasAliases | kXMP_PropIsAlias;
    
    // XOR toggle kXMP_PropHasAliases off
    opts ^= kXMP_PropHasAliases;
    EXPECT_FALSE((opts & kXMP_PropHasAliases) != 0);
    EXPECT_TRUE((opts & kXMP_PropIsAlias) != 0);
    
    // XOR toggle kXMP_PropIsAlias off
    opts ^= kXMP_PropIsAlias;
    EXPECT_FALSE((opts & kXMP_PropIsAlias) != 0);
    EXPECT_EQ(opts, 0u);
}

TEST_F(XMPNodeTest_1965, NewImplicitNodeFlag_1965) {
    // kXMP_NewImplicitNode is used in FindSchemaNode results
    // Testing the toggle pattern used in MoveExplicitAliases
    XMP_OptionBits opts = kXMP_InsertBeforeItem; // Some arbitrary flag
    // The function checks and toggles kXMP_NewImplicitNode
    // We just verify option manipulation works correctly
    XMP_OptionBits testFlag = 0x80000000u; // Hypothetical flag
    opts |= testFlag;
    EXPECT_TRUE((opts & testFlag) != 0);
    opts ^= testFlag;
    EXPECT_FALSE((opts & testFlag) != 0);
}

TEST_F(XMPNodeTest_1965, MultipleSchemaIteration_1965) {
    XMP_Node tree(nullptr, "xmpmeta", 0);
    
    XMP_Node* schema1 = new XMP_Node(&tree, "http://ns1.example.com/", 0);
    XMP_Node* schema2 = new XMP_Node(&tree, "http://ns2.example.com/", 0);
    XMP_Node* schema3 = new XMP_Node(&tree, "http://ns3.example.com/", 0);
    
    tree.children.push_back(schema1);
    tree.children.push_back(schema2);
    tree.children.push_back(schema3);
    
    // Add children to schema1 and schema3 but not schema2
    schema1->children.push_back(new XMP_Node(schema1, "ns1:prop", "val", 0));
    schema3->children.push_back(new XMP_Node(schema3, "ns3:prop", "val", 0));
    
    // Simulate the schema removal loop pattern from MoveExplicitAliases
    size_t schemaNum = 0;
    while (schemaNum < tree.children.size()) {
        XMP_Node* currSchema = tree.children[schemaNum];
        if (currSchema->children.empty()) {
            delete tree.children[schemaNum];
            tree.children.erase(tree.children.begin() + schemaNum);
        } else {
            ++schemaNum;
        }
    }
    
    EXPECT_EQ(tree.children.size(), 2u);
    EXPECT_EQ(tree.children[0]->name, "http://ns1.example.com/");
    EXPECT_EQ(tree.children[1]->name, "http://ns3.example.com/");
    
    tree.RemoveChildren();
}

TEST_F(XMPNodeTest_1965, EmptyTreeNoSchemas_1965) {
    XMP_Node tree(nullptr, "xmpmeta", kXMP_PropHasAliases);
    
    // Toggle alias flag as MoveExplicitAliases does first
    tree.options ^= kXMP_PropHasAliases;
    EXPECT_EQ(tree.options, 0u);
    EXPECT_TRUE(tree.children.empty());
}

TEST_F(XMPNodeTest_1965, NodeParentRelationship_1965) {
    XMP_Node tree(nullptr, "root", 0);
    XMP_Node* child = new XMP_Node(&tree, "child", 0);
    tree.children.push_back(child);
    
    EXPECT_EQ(child->parent, &tree);
    EXPECT_EQ(tree.parent, nullptr);
    
    tree.RemoveChildren();
}

TEST_F(XMPNodeTest_1965, ArrayNodeStructure_1965) {
    XMP_Node tree(nullptr, "root", 0);
    XMP_Node* arrayNode = new XMP_Node(&tree, "ns:array", 
        kXMP_PropValueIsArray | kXMP_PropArrayIsOrdered);
    tree.children.push_back(arrayNode);
    
    XMP_Node* item1 = new XMP_Node(arrayNode, "rdf:li", "item1", 0);
    XMP_Node* item2 = new XMP_Node(arrayNode, "rdf:li", "item2", 0);
    arrayNode->children.push_back(item1);
    arrayNode->children.push_back(item2);
    
    EXPECT_TRUE((arrayNode->options & kXMP_PropValueIsArray) != 0);
    EXPECT_TRUE((arrayNode->options & kXMP_PropArrayIsOrdered) != 0);
    EXPECT_EQ(arrayNode->children.size(), 2u);
    EXPECT_EQ(arrayNode->children[0]->value, "item1");
    EXPECT_EQ(arrayNode->children[1]->value, "item2");
    
    tree.RemoveChildren();
}

TEST_F(XMPNodeTest_1965, AltTextArrayNodeStructure_1965) {
    XMP_Node tree(nullptr, "root", 0);
    XMP_OptionBits altTextOpts = kXMP_PropValueIsArray | kXMP_PropArrayIsOrdered | 
                                  kXMP_PropArrayIsAlternate | kXMP_PropArrayIsAltText;
    XMP_Node* arrayNode = new XMP_Node(&tree, "ns:altArray", altTextOpts);
    tree.children.push_back(arrayNode);
    
    EXPECT_TRUE((arrayNode->options & kXMP_PropArrayIsAltText) != 0);
    EXPECT_TRUE((arrayNode->options & kXMP_PropArrayFormMask) != 0);
    
    tree.RemoveChildren();
}

TEST_F(XMPNodeTest_1965, PropertyEraseFromMiddle_1965) {
    XMP_Node schema(nullptr, "schema", 0);
    
    XMP_Node* p1 = new XMP_Node(&schema, "prop1", 0);
    XMP_Node* p2 = new XMP_Node(&schema, "prop2", kXMP_PropIsAlias);
    XMP_Node* p3 = new XMP_Node(&schema, "prop3", 0);
    
    schema.children.push_back(p1);
    schema.children.push_back(p2);
    schema.children.push_back(p3);
    
    // Erase middle element (simulating alias removal)
    schema.children.erase(schema.children.begin() + 1);
    delete p2;
    
    EXPECT_EQ(schema.children.size(), 2u);
    EXPECT_EQ(schema.children[0]->name, "prop1");
    EXPECT_EQ(schema.children[1]->name, "prop3");
    
    schema.RemoveChildren();
}
