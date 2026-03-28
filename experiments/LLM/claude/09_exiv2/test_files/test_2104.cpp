#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <cstring>

// We need to set up the XMP environment to include the static function
// Include necessary XMP SDK headers

#define TXMP_STRING_TYPE std::string

// Minimal includes to get XMP_Node and related types
#include "XMP_Const.h"
#include "XMP_Environment.h"

// Pull in the implementation headers
#include "XMPCore_Impl.hpp"

// Since EstimateRDFSize is static in the .cpp file, we need to include it
// We wrap it to get access
namespace {
    // Forward declare the constants that the function uses
    // These are defined in the source file
}

// Include the source file to access the static function
// We need to be careful about multiple definition issues
#include "XMPMeta-Serialize.cpp"

class EstimateRDFSizeTest_2104 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test a simple leaf node with no children, no qualifiers, no special options
TEST_F(EstimateRDFSizeTest_2104, SimpleLeafNode_2104) {
    XMP_Node root(nullptr, "prop", "value123", 0);
    
    size_t indent = 0;
    size_t indentLen = 2;
    size_t result = EstimateRDFSize(&root, indent, indentLen);
    
    // For a leaf node: 2*(indent*indentLen + name.size() + 4) + value.size()
    // = 2*(0*2 + 4 + 4) + 8 = 2*8 + 8 = 24
    size_t expected = 2 * (0 * 2 + std::string("prop").size() + 4) + std::string("value123").size();
    EXPECT_EQ(result, expected);
}

// Test a leaf node with indent > 0
TEST_F(EstimateRDFSizeTest_2104, LeafNodeWithIndent_2104) {
    XMP_Node root(nullptr, "element", "data", 0);
    
    size_t indent = 3;
    size_t indentLen = 4;
    size_t result = EstimateRDFSize(&root, indent, indentLen);
    
    // 2*(3*4 + 7 + 4) + 4 = 2*(12+7+4) + 4 = 2*23 + 4 = 50
    size_t expected = 2 * (3 * 4 + std::string("element").size() + 4) + std::string("data").size();
    EXPECT_EQ(result, expected);
}

// Test a struct node with no children
TEST_F(EstimateRDFSizeTest_2104, StructNodeNoChildren_2104) {
    XMP_Node root(nullptr, "myStruct", kXMP_PropValueIsStruct);
    
    size_t indent = 1;
    size_t indentLen = 2;
    size_t result = EstimateRDFSize(&root, indent, indentLen);
    
    // Property element tags: 2*(1*2 + 8 + 4) = 2*14 = 28
    // Struct: indent becomes 2, rdf:Description tags: 2*(2*2 + strlen(kRDF_StructStart) + 2) = 2*(4+17+2) = 2*23 = 46
    size_t expectedPropTags = 2 * (1 * 2 + std::string("myStruct").size() + 4);
    size_t expectedStructTags = 2 * (2 * 2 + strlen(kRDF_StructStart) + 2);
    size_t expected = expectedPropTags + expectedStructTags;
    EXPECT_EQ(result, expected);
}

// Test an array node with no children
TEST_F(EstimateRDFSizeTest_2104, ArrayNodeNoChildren_2104) {
    XMP_Node root(nullptr, "myArray", kXMP_PropValueIsArray);
    
    size_t indent = 0;
    size_t indentLen = 2;
    size_t result = EstimateRDFSize(&root, indent, indentLen);
    
    // Property tags: 2*(0*2 + 7 + 4) = 2*11 = 22
    // Array: indent becomes 2
    // Bag tags: 2*((2-1)*2 + strlen(kRDF_BagStart) + 2) = 2*(2 + 9 + 2) = 2*13 = 26
    // li tags: 2*0*(strlen(kRDF_ItemStart)+2) = 0
    size_t expectedPropTags = 2 * (0 * 2 + std::string("myArray").size() + 4);
    size_t expectedBagTags = 2 * (1 * 2 + strlen(kRDF_BagStart) + 2);
    size_t expectedLiTags = 0; // no children
    size_t expected = expectedPropTags + expectedBagTags + expectedLiTags;
    EXPECT_EQ(result, expected);
}

// Test an array node with children (leaf children)
TEST_F(EstimateRDFSizeTest_2104, ArrayNodeWithChildren_2104) {
    XMP_Node root(nullptr, "myArray", kXMP_PropValueIsArray);
    XMP_Node child1(&root, "item1", "val1", 0);
    XMP_Node child2(&root, "item2", "val2", 0);
    root.children.push_back(&child1);
    root.children.push_back(&child2);
    
    size_t indent = 0;
    size_t indentLen = 2;
    size_t result = EstimateRDFSize(&root, indent, indentLen);
    
    // Property tags: 2*(0 + 7 + 4) = 22
    // Array: indent becomes 2
    // Bag tags: 2*(1*2 + 9 + 2) = 2*13 = 26
    // li tags: 2*2*(8+2) = 4*10 = 40
    // child1 at indent 3: 2*(3*2 + 5 + 4) + 4 = 2*15 + 4 = 34
    // child2 at indent 3: 2*(3*2 + 5 + 4) + 4 = 34
    size_t expectedPropTags = 2 * (0 * 2 + std::string("myArray").size() + 4);
    size_t expectedBagTags = 2 * (1 * 2 + strlen(kRDF_BagStart) + 2);
    size_t expectedLiTags = 2 * 2 * (strlen(kRDF_ItemStart) + 2);
    
    // Children are estimated at indent+1 where indent=2 after array processing, so indent=3
    size_t childIndent = 3;
    size_t child1Est = 2 * (childIndent * indentLen + std::string("item1").size() + 4) + std::string("val1").size();
    size_t child2Est = 2 * (childIndent * indentLen + std::string("item2").size() + 4) + std::string("val2").size();
    
    size_t expected = expectedPropTags + expectedBagTags + expectedLiTags + child1Est + child2Est;
    EXPECT_EQ(result, expected);
    
    // Clean up: remove children from vector so destructor doesn't double-free
    root.children.clear();
}

// Test a node with qualifiers
TEST_F(EstimateRDFSizeTest_2104, NodeWithQualifiers_2104) {
    XMP_Node root(nullptr, "prop", "val", 0);
    XMP_Node qual(&root, "qualifier", "qval", 0);
    root.qualifiers.push_back(&qual);
    
    size_t indent = 1;
    size_t indentLen = 2;
    size_t result = EstimateRDFSize(&root, indent, indentLen);
    
    // Property element tags: 2*(1*2 + 4 + 4) = 2*10 = 20
    // Has qualifiers, so indent becomes 3 inside:
    // rdf:Description tags: 2*((3-1)*2 + strlen(kRDF_StructStart) + 2) = 2*(4 + 17 + 2) = 2*23 = 46
    // rdf:value tags: 2*(3*2 + strlen(kRDF_ValueStart) + 2) = 2*(6 + 11 + 2) = 2*19 = 38
    // qualifier estimate at indent=3: 2*(3*2 + 9 + 4) + 4 = 2*19 + 4 = 42
    // value.size() = 3 (leaf node, no struct/array/schema flag)
    size_t expectedPropTags = 2 * (1 * 2 + std::string("prop").size() + 4);
    XMP_Index qualIndent = 3;
    size_t expectedDescTags = 2 * ((qualIndent - 1) * indentLen + strlen(kRDF_StructStart) + 2);
    size_t expectedValueTags = 2 * (qualIndent * indentLen + strlen(kRDF_ValueStart) + 2);
    size_t qualEst = 2 * (qualIndent * indentLen + std::string("qualifier").size() + 4) + std::string("qval").size();
    size_t expectedLeafValue = std::string("val").size();
    
    size_t expected = expectedPropTags + expectedDescTags + expectedValueTags + qualEst + expectedLeafValue;
    EXPECT_EQ(result, expected);
    
    root.qualifiers.clear();
}

// Test a schema node (no value contribution for schema nodes)
TEST_F(EstimateRDFSizeTest_2104, SchemaNode_2104) {
    XMP_Node root(nullptr, "schema", "schemaValue", kXMP_SchemaNode);
    
    size_t indent = 0;
    size_t indentLen = 2;
    size_t result = EstimateRDFSize(&root, indent, indentLen);
    
    // Property tags: 2*(0 + 6 + 4) = 2*10 = 20
    // Schema node: not struct, not array, but is schema -> no value added
    size_t expected = 2 * (0 * 2 + std::string("schema").size() + 4);
    EXPECT_EQ(result, expected);
}

// Test empty name and value
TEST_F(EstimateRDFSizeTest_2104, EmptyNameAndValue_2104) {
    XMP_Node root(nullptr, "", "", 0);
    
    size_t indent = 0;
    size_t indentLen = 0;
    size_t result = EstimateRDFSize(&root, indent, indentLen);
    
    // Property tags: 2*(0 + 0 + 4) = 8
    // Leaf value: 0
    size_t expected = 2 * 4 + 0;
    EXPECT_EQ(result, expected);
}

// Test struct node with children
TEST_F(EstimateRDFSizeTest_2104, StructNodeWithChildren_2104) {
    XMP_Node root(nullptr, "myStruct", kXMP_PropValueIsStruct);
    XMP_Node child(&root, "field", "fieldVal", 0);
    root.children.push_back(&child);
    
    size_t indent = 0;
    size_t indentLen = 2;
    size_t result = EstimateRDFSize(&root, indent, indentLen);
    
    // Property tags: 2*(0 + 8 + 4) = 2*12 = 24
    // Struct: indent becomes 1
    // rdf:Description tags: 2*(1*2 + 17 + 2) = 2*21 = 42
    // child at indent 2: 2*(2*2 + 5 + 4) + 8 = 2*13 + 8 = 34
    size_t expectedPropTags = 2 * (0 * 2 + std::string("myStruct").size() + 4);
    size_t structIndent = 1;
    size_t expectedStructTags = 2 * (structIndent * indentLen + strlen(kRDF_StructStart) + 2);
    size_t childEst = 2 * (2 * indentLen + std::string("field").size() + 4) + std::string("fieldVal").size();
    
    size_t expected = expectedPropTags + expectedStructTags + childEst;
    EXPECT_EQ(result, expected);
    
    root.children.clear();
}

// Test deep nesting: struct within struct
TEST_F(EstimateRDFSizeTest_2104, DeepNestedStructs_2104) {
    XMP_Node root(nullptr, "outer", kXMP_PropValueIsStruct);
    XMP_Node inner(&root, "inner", kXMP_PropValueIsStruct);
    XMP_Node leaf(&inner, "leaf", "leafValue", 0);
    root.children.push_back(&inner);
    inner.children.push_back(&leaf);
    
    size_t indent = 0;
    size_t indentLen = 2;
    size_t result = EstimateRDFSize(&root, indent, indentLen);
    
    // This should be a deterministic computation; just verify it returns > 0
    EXPECT_GT(result, 0u);
    
    // Compute expected:
    // root prop tags: 2*(0 + 5 + 4) = 18
    // root struct: indent 1, desc tags: 2*(1*2 + 17 + 2) = 42
    // inner at indent 2: prop tags: 2*(2*2 + 5 + 4) = 2*13 = 26
    // inner struct: indent 3, desc tags: 2*(3*2 + 17 + 2) = 2*25 = 50
    // leaf at indent 4: prop tags: 2*(4*2 + 4 + 4) = 2*16 = 32, value: 9
    size_t rootPropTags = 2 * (0 + 5 + 4);
    size_t rootStructTags = 2 * (1 * 2 + strlen(kRDF_StructStart) + 2);
    size_t innerPropTags = 2 * (2 * 2 + 5 + 4);
    size_t innerStructTags = 2 * (3 * 2 + strlen(kRDF_StructStart) + 2);
    size_t leafEst = 2 * (4 * 2 + 4 + 4) + 9;
    size_t expected = rootPropTags + rootStructTags + innerPropTags + innerStructTags + leafEst;
    EXPECT_EQ(result, expected);
    
    inner.children.clear();
    root.children.clear();
}

// Test with indentLen = 0
TEST_F(EstimateRDFSizeTest_2104, ZeroIndentLen_2104) {
    XMP_Node root(nullptr, "prop", "val", 0);
    
    size_t indent = 5;
    size_t indentLen = 0;
    size_t result = EstimateRDFSize(&root, indent, indentLen);
    
    // Property tags: 2*(5*0 + 4 + 4) = 2*8 = 16
    // Leaf value: 3
    size_t expected = 2 * (0 + std::string("prop").size() + 4) + std::string("val").size();
    EXPECT_EQ(result, expected);
}

// Test node with multiple qualifiers
TEST_F(EstimateRDFSizeTest_2104, MultipleQualifiers_2104) {
    XMP_Node root(nullptr, "prop", "v", 0);
    XMP_Node qual1(&root, "q1", "a", 0);
    XMP_Node qual2(&root, "q2", "bb", 0);
    root.qualifiers.push_back(&qual1);
    root.qualifiers.push_back(&qual2);
    
    size_t indent = 0;
    size_t indentLen = 1;
    size_t result = EstimateRDFSize(&root, indent, indentLen);
    
    // Property tags: 2*(0 + 4 + 4) = 16
    // Has qualifiers: indent becomes 2
    // rdf:Description tags: 2*((2-1)*1 + 17 + 2) = 2*20 = 40
    // rdf:value tags: 2*(2*1 + 11 + 2) = 2*15 = 30
    // qual1 at indent 2: 2*(2*1 + 2 + 4) + 1 = 2*8 + 1 = 17
    // qual2 at indent 2: 2*(2*1 + 2 + 4) + 2 = 2*8 + 2 = 18
    // Leaf value: 1
    size_t expectedPropTags = 2 * (0 + 4 + 4);
    XMP_Index qualIndent = 2;
    size_t expectedDescTags = 2 * ((qualIndent - 1) * 1 + strlen(kRDF_StructStart) + 2);
    size_t expectedValueTags = 2 * (qualIndent * 1 + strlen(kRDF_ValueStart) + 2);
    size_t qual1Est = 2 * (qualIndent * 1 + std::string("q1").size() + 4) + std::string("a").size();
    size_t qual2Est = 2 * (qualIndent * 1 + std::string("q2").size() + 4) + std::string("bb").size();
    size_t leafVal = std::string("v").size();
    
    size_t expected = expectedPropTags + expectedDescTags + expectedValueTags + qual1Est + qual2Est + leafVal;
    EXPECT_EQ(result, expected);
    
    root.qualifiers.clear();
}

// Test node with both children and qualifiers and struct type
TEST_F(EstimateRDFSizeTest_2104, StructWithQualifiersAndChildren_2104) {
    XMP_Node root(nullptr, "s", kXMP_PropValueIsStruct);
    XMP_Node qual(&root, "q", "qv", 0);
    XMP_Node child(&root, "c", "cv", 0);
    root.qualifiers.push_back(&qual);
    root.children.push_back(&child);
    
    size_t indent = 0;
    size_t indentLen = 1;
    size_t result = EstimateRDFSize(&root, indent, indentLen);
    
    // Property tags: 2*(0 + 1 + 4) = 10
    // Has qualifiers: indent += 2 -> indent=2
    // rdf:Description tags: 2*((2-1)*1 + 17 + 2) = 2*20 = 40
    // rdf:value tags: 2*(2*1 + 11 + 2) = 2*15 = 30
    // qual at indent 2: 2*(2 + 1 + 4) + 2 = 14+2 = 16
    // Is struct: indent += 1 -> indent=3
    // struct desc tags: 2*(3*1 + 17 + 2) = 2*22 = 44
    // child at indent 4: 2*(4 + 1 + 4) + 2 = 18 + 2 = 20
    size_t expectedPropTags = 2 * (0 + 1 + 4);
    size_t qualIndent = 2;
    size_t expectedDescTags = 2 * ((qualIndent - 1) * 1 + strlen(kRDF_StructStart) + 2);
    size_t expectedValueTags = 2 * (qualIndent * 1 + strlen(kRDF_ValueStart) + 2);
    size_t qualEst = 2 * (qualIndent * 1 + 1 + 4) + 2;
    size_t structIndent = 3;
    size_t expectedStructTags = 2 * (structIndent * 1 + strlen(kRDF_StructStart) + 2);
    size_t childEst = 2 * (4 * 1 + 1 + 4) + 2;
    
    size_t expected = expectedPropTags + expectedDescTags + expectedValueTags + qualEst + expectedStructTags + childEst;
    EXPECT_EQ(result, expected);
    
    root.qualifiers.clear();
    root.children.clear();
}

// Test large indent value
TEST_F(EstimateRDFSizeTest_2104, LargeIndent_2104) {
    XMP_Node root(nullptr, "x", "y", 0);
    
    size_t indent = 100;
    size_t indentLen = 4;
    size_t result = EstimateRDFSize(&root, indent, indentLen);
    
    size_t expected = 2 * (100 * 4 + 1 + 4) + 1;
    EXPECT_EQ(result, expected);
}

// Test schema node with children (like a real namespace node)
TEST_F(EstimateRDFSizeTest_2104, SchemaNodeWithChildren_2104) {
    XMP_Node schema(nullptr, "ns:schema", kXMP_SchemaNode);
    XMP_Node child(&schema, "ns:prop", "value", 0);
    schema.children.push_back(&child);
    
    size_t indent = 0;
    size_t indentLen = 2;
    size_t result = EstimateRDFSize(&schema, indent, indentLen);
    
    // Schema prop tags: 2*(0 + 9 + 4) = 26
    // Schema: no value added (schema node)
    // child at indent 1: 2*(1*2 + 7 + 4) = 2*13 = 26, value: 5
    size_t expectedPropTags = 2 * (0 + std::string("ns:schema").size() + 4);
    size_t childEst = 2 * (1 * 2 + std::string("ns:prop").size() + 4) + std::string("value").size();
    
    size_t expected = expectedPropTags + childEst;
    EXPECT_EQ(result, expected);
    
    schema.children.clear();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
