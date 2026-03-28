#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <cstring>

// Include necessary headers for XMP SDK
#define TXMP_STRING_TYPE std::string
#include "XMP.hpp"
#include "XMPMeta.hpp"
#include "XMPCore_Impl.hpp"

class XMPMetaTest_1985 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize XMP SDK if needed
        try {
            SXMPMeta::Initialize();
        } catch (...) {
            // May already be initialized
        }
    }

    void TearDown() override {
        try {
            SXMPMeta::Terminate();
        } catch (...) {
        }
    }
};

// Test: XMPMeta default construction creates empty tree
TEST_F(XMPMetaTest_1985, DefaultConstructionCreatesEmptyTree_1985) {
    XMPMeta meta;
    EXPECT_TRUE(meta.tree.children.empty());
    EXPECT_EQ(meta.tree.name, "");
}

// Test: XMP_Node construction with parent and name
TEST_F(XMPMetaTest_1985, XMPNodeConstructionWithParentAndName_1985) {
    XMP_Node parent(nullptr, "root", 0);
    XMP_Node child(&parent, "child", 0);
    
    EXPECT_EQ(child.name, "child");
    EXPECT_EQ(child.parent, &parent);
}

// Test: XMP_Node construction with name and value
TEST_F(XMPMetaTest_1985, XMPNodeConstructionWithNameAndValue_1985) {
    XMP_Node node(nullptr, "testName", "testValue", 0);
    
    EXPECT_EQ(node.name, "testName");
    EXPECT_EQ(node.value, "testValue");
    EXPECT_EQ(node.parent, nullptr);
}

// Test: XMP_Node construction with string references
TEST_F(XMPMetaTest_1985, XMPNodeConstructionWithStringReferences_1985) {
    XMP_VarString name = "schemaName";
    XMP_VarString value = "schemaValue";
    XMP_Node node(nullptr, name, value, 0);
    
    EXPECT_EQ(node.name, name);
    EXPECT_EQ(node.value, value);
}

// Test: XMP_Node children can be added and removed
TEST_F(XMPMetaTest_1985, NodeChildrenAddAndRemove_1985) {
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

// Test: XMP_Node RemoveChildren on empty node
TEST_F(XMPMetaTest_1985, RemoveChildrenOnEmptyNode_1985) {
    XMP_Node node(nullptr, "empty", 0);
    EXPECT_TRUE(node.children.empty());
    node.RemoveChildren();
    EXPECT_TRUE(node.children.empty());
}

// Test: XMP_Node RemoveQualifiers
TEST_F(XMPMetaTest_1985, RemoveQualifiers_1985) {
    XMP_Node node(nullptr, "test", 0);
    XMP_Node* qual = new XMP_Node(&node, "qualifier", 0);
    node.qualifiers.push_back(qual);
    
    EXPECT_EQ(node.qualifiers.size(), 1u);
    node.RemoveQualifiers();
    EXPECT_TRUE(node.qualifiers.empty());
}

// Test: XMP_Node ClearNode clears everything
TEST_F(XMPMetaTest_1985, ClearNodeClearsEverything_1985) {
    XMP_Node node(nullptr, "testNode", "testValue", 0);
    XMP_Node* child = new XMP_Node(&node, "child", 0);
    node.children.push_back(child);
    XMP_Node* qual = new XMP_Node(&node, "qual", 0);
    node.qualifiers.push_back(qual);
    
    node.ClearNode();
    
    EXPECT_TRUE(node.children.empty());
    EXPECT_TRUE(node.qualifiers.empty());
}

// Test: Tree structure with schemas and properties (mirrors what CreateEstimatedSizeMap traverses)
TEST_F(XMPMetaTest_1985, TreeWithSchemasAndProperties_1985) {
    XMPMeta meta;
    
    // Create schema node
    XMP_Node* schema = new XMP_Node(&meta.tree, "http://ns.adobe.com/xap/1.0/", 0);
    meta.tree.children.push_back(schema);
    
    // Create property nodes under schema
    XMP_Node* prop1 = new XMP_Node(schema, "xmp:CreateDate", "2023-01-01", 0);
    XMP_Node* prop2 = new XMP_Node(schema, "xmp:ModifyDate", "2023-06-15", 0);
    schema->children.push_back(prop1);
    schema->children.push_back(prop2);
    
    EXPECT_EQ(meta.tree.children.size(), 1u);
    EXPECT_EQ(meta.tree.children[0]->children.size(), 2u);
    EXPECT_EQ(meta.tree.children[0]->children[0]->name, "xmp:CreateDate");
    EXPECT_EQ(meta.tree.children[0]->children[1]->name, "xmp:ModifyDate");
}

// Test: Multiple schemas in tree
TEST_F(XMPMetaTest_1985, MultipleSchemas_1985) {
    XMPMeta meta;
    
    XMP_Node* schema1 = new XMP_Node(&meta.tree, "http://ns.adobe.com/xap/1.0/", 0);
    XMP_Node* schema2 = new XMP_Node(&meta.tree, "http://purl.org/dc/elements/1.1/", 0);
    meta.tree.children.push_back(schema1);
    meta.tree.children.push_back(schema2);
    
    XMP_Node* prop1 = new XMP_Node(schema1, "xmp:CreateDate", "2023-01-01", 0);
    schema1->children.push_back(prop1);
    
    XMP_Node* prop2 = new XMP_Node(schema2, "dc:title", "Test Title", 0);
    schema2->children.push_back(prop2);
    
    EXPECT_EQ(meta.tree.children.size(), 2u);
    EXPECT_EQ(schema1->children.size(), 1u);
    EXPECT_EQ(schema2->children.size(), 1u);
}

// Test: Schema with xmpNote:HasExtendedXMP property (should be skipped by CreateEstimatedSizeMap)
TEST_F(XMPMetaTest_1985, XmpNoteHasExtendedXMPProperty_1985) {
    XMPMeta meta;
    
    // The kXMP_NS_XMP_Note namespace with HasExtendedXMP is special
    XMP_Node* noteSchema = new XMP_Node(&meta.tree, "http://ns.adobe.com/xmp/note/", 0);
    meta.tree.children.push_back(noteSchema);
    
    XMP_Node* extProp = new XMP_Node(noteSchema, "xmpNote:HasExtendedXMP", "some_guid", 0);
    noteSchema->children.push_back(extProp);
    
    EXPECT_EQ(noteSchema->children.size(), 1u);
    EXPECT_EQ(noteSchema->children[0]->name, "xmpNote:HasExtendedXMP");
}

// Test: Empty schema (no properties)
TEST_F(XMPMetaTest_1985, EmptySchema_1985) {
    XMPMeta meta;
    
    XMP_Node* schema = new XMP_Node(&meta.tree, "http://ns.adobe.com/xap/1.0/", 0);
    meta.tree.children.push_back(schema);
    
    EXPECT_EQ(meta.tree.children.size(), 1u);
    EXPECT_TRUE(schema->children.empty());
}

// Test: XMPMeta Erase clears tree
TEST_F(XMPMetaTest_1985, EraseClears_1985) {
    XMPMeta meta;
    
    XMP_Node* schema = new XMP_Node(&meta.tree, "http://ns.adobe.com/xap/1.0/", 0);
    meta.tree.children.push_back(schema);
    XMP_Node* prop = new XMP_Node(schema, "xmp:CreateDate", "2023", 0);
    schema->children.push_back(prop);
    
    meta.Erase();
    EXPECT_TRUE(meta.tree.children.empty());
}

// Test: XMP_Node destructor cleans up properly (no crash)
TEST_F(XMPMetaTest_1985, NodeDestructorNoLeak_1985) {
    XMP_Node* node = new XMP_Node(nullptr, "test", 0);
    XMP_Node* child = new XMP_Node(node, "child", "value", 0);
    node->children.push_back(child);
    
    // Should not crash or leak
    delete node;
    SUCCEED();
}

// Test: XMP_Node with options
TEST_F(XMPMetaTest_1985, NodeWithOptions_1985) {
    XMP_Node node(nullptr, "test", 0x1234);
    EXPECT_EQ(node.options, static_cast<XMP_OptionBits>(0x1234));
}

// Test: Deeply nested property structure
TEST_F(XMPMetaTest_1985, DeeplyNestedStructure_1985) {
    XMPMeta meta;
    
    XMP_Node* schema = new XMP_Node(&meta.tree, "http://ns.adobe.com/xap/1.0/", 0);
    meta.tree.children.push_back(schema);
    
    XMP_Node* prop = new XMP_Node(schema, "xmp:Struct", 0);
    schema->children.push_back(prop);
    
    XMP_Node* subProp = new XMP_Node(prop, "xmp:SubField", "value", 0);
    prop->children.push_back(subProp);
    
    XMP_Node* subSubProp = new XMP_Node(subProp, "xmp:DeepField", "deep", 0);
    subProp->children.push_back(subSubProp);
    
    EXPECT_EQ(meta.tree.children[0]->children[0]->children[0]->children[0]->value, "deep");
}

// Test: Large number of properties in a schema
TEST_F(XMPMetaTest_1985, ManyPropertiesInSchema_1985) {
    XMPMeta meta;
    
    XMP_Node* schema = new XMP_Node(&meta.tree, "http://ns.adobe.com/xap/1.0/", 0);
    meta.tree.children.push_back(schema);
    
    const int numProps = 100;
    for (int i = 0; i < numProps; ++i) {
        std::string propName = "xmp:Prop" + std::to_string(i);
        std::string propValue = "Value" + std::to_string(i);
        XMP_Node* prop = new XMP_Node(schema, propName.c_str(), propValue.c_str(), 0);
        schema->children.push_back(prop);
    }
    
    EXPECT_EQ(schema->children.size(), static_cast<size_t>(numProps));
    EXPECT_EQ(schema->children[0]->name, "xmp:Prop0");
    EXPECT_EQ(schema->children[99]->name, "xmp:Prop99");
}

// Test: Property with empty name and value
TEST_F(XMPMetaTest_1985, PropertyWithEmptyNameAndValue_1985) {
    XMP_Node node(nullptr, "", "", 0);
    EXPECT_EQ(node.name, "");
    EXPECT_EQ(node.value, "");
}

// Test: XMPMeta clientRefs and prevTkVer initialization
TEST_F(XMPMetaTest_1985, MetaDefaultInitialization_1985) {
    XMPMeta meta;
    EXPECT_EQ(meta.clientRefs, 0);
    EXPECT_EQ(meta.prevTkVer, 0);
    EXPECT_EQ(meta.xmlParser, nullptr);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
