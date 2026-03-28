#include <gtest/gtest.h>
#include <string>
#include <vector>

// Include necessary headers
#include "XMLParserAdapter.hpp"

// We need to declare the function under test since it's static in the source file.
// To test a static function, we include the source file directly or use a workaround.
// Here we redefine the function signature to match and include the cpp file.

// Forward declare the options constant
#ifndef kXMP_RequireXMPMeta
#define kXMP_RequireXMPMeta 1
#endif

// Since PickBestRoot is a static function in the .cpp file, we need to include
// the source to access it. We'll use a trick to make it accessible.
// We wrap the include so we can access the static function.

// Alternatively, we can copy the function declaration and test it.
// But per constraints, we must not re-implement. So we include the source.

// We'll define a test-accessible wrapper by including the source file
// which makes the static function available in this translation unit.

// First, let's provide minimal stubs for dependencies that the .cpp file needs
// but that aren't part of our test focus.

// We need to handle the includes that XMPMeta-Parse.cpp expects
// For testing purposes, we'll directly define the function to match the implementation

// Since the function is static, we include the cpp to get access
// But we need to be careful about other definitions in that file.
// Instead, let's extract just the function for testing.

// Actually, let's just declare and define a test-accessible version
// by including source. If that's not possible, we replicate the declaration.

// For practical test purposes, we declare the function as it appears:
static const XML_Node * PickBestRoot ( const XML_Node & xmlParent, XMP_OptionBits options );

// Include the implementation file to get the static function
// This is a common technique for testing static/file-scoped functions
#include "XMPMeta-Parse.cpp"

class PickBestRootTest_1959 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
    
    // Helper to create a node
    XML_Node* createNode(XML_Node* parent, const std::string& name, XMP_Uns8 kind) {
        XML_Node* node = new XML_Node(parent, name, kind);
        return node;
    }
    
    // Helper to clean up nodes - we manage memory manually
    void addChildNode(XML_Node* parent, XML_Node* child) {
        parent->content.push_back(child);
    }
};

// Test: Empty parent node returns nullptr
TEST_F(PickBestRootTest_1959, EmptyParentReturnsNull_1959) {
    XML_Node root(nullptr, "root", kRootNode);
    const XML_Node* result = PickBestRoot(root, 0);
    EXPECT_EQ(result, nullptr);
}

// Test: Direct rdf:RDF child is found when no kXMP_RequireXMPMeta
TEST_F(PickBestRootTest_1959, DirectRdfRDFChildFound_1959) {
    XML_Node root(nullptr, "root", kRootNode);
    XML_Node* rdfNode = createNode(&root, "rdf:RDF", kElemNode);
    addChildNode(&root, rdfNode);
    
    const XML_Node* result = PickBestRoot(root, 0);
    EXPECT_EQ(result, rdfNode);
    
    delete rdfNode;
}

// Test: x:xmpmeta child causes recursive search
TEST_F(PickBestRootTest_1959, XmpmmetaChildRecursesInto_1959) {
    XML_Node root(nullptr, "root", kRootNode);
    XML_Node* xmpmetaNode = createNode(&root, "x:xmpmeta", kElemNode);
    addChildNode(&root, xmpmetaNode);
    
    XML_Node* rdfNode = createNode(xmpmetaNode, "rdf:RDF", kElemNode);
    addChildNode(xmpmetaNode, rdfNode);
    
    const XML_Node* result = PickBestRoot(root, 0);
    EXPECT_EQ(result, rdfNode);
    
    delete rdfNode;
    delete xmpmetaNode;
}

// Test: x:xapmeta child causes recursive search
TEST_F(PickBestRootTest_1959, XapmetaChildRecursesInto_1959) {
    XML_Node root(nullptr, "root", kRootNode);
    XML_Node* xapmetaNode = createNode(&root, "x:xapmeta", kElemNode);
    addChildNode(&root, xapmetaNode);
    
    XML_Node* rdfNode = createNode(xapmetaNode, "rdf:RDF", kElemNode);
    addChildNode(xapmetaNode, rdfNode);
    
    const XML_Node* result = PickBestRoot(root, 0);
    EXPECT_EQ(result, rdfNode);
    
    delete rdfNode;
    delete xapmetaNode;
}

// Test: kXMP_RequireXMPMeta option prevents finding bare rdf:RDF
TEST_F(PickBestRootTest_1959, RequireXMPMetaPreventsDirectRdfRDF_1959) {
    XML_Node root(nullptr, "root", kRootNode);
    XML_Node* rdfNode = createNode(&root, "rdf:RDF", kElemNode);
    addChildNode(&root, rdfNode);
    
    const XML_Node* result = PickBestRoot(root, kXMP_RequireXMPMeta);
    // With RequireXMPMeta, the second loop (direct rdf:RDF) is skipped.
    // The third loop recurses into children but rdf:RDF itself doesn't contain
    // x:xmpmeta or rdf:RDF children, so returns null.
    EXPECT_EQ(result, nullptr);
    
    delete rdfNode;
}

// Test: Non-element nodes are skipped
TEST_F(PickBestRootTest_1959, NonElementNodesSkipped_1959) {
    XML_Node root(nullptr, "root", kRootNode);
    XML_Node* cdataNode = createNode(&root, "x:xmpmeta", kCDataNode);
    addChildNode(&root, cdataNode);
    
    const XML_Node* result = PickBestRoot(root, 0);
    EXPECT_EQ(result, nullptr);
    
    delete cdataNode;
}

// Test: Non-element rdf:RDF node is skipped
TEST_F(PickBestRootTest_1959, NonElementRdfNodeSkipped_1959) {
    XML_Node root(nullptr, "root", kRootNode);
    XML_Node* rdfAttr = createNode(&root, "rdf:RDF", kAttrNode);
    addChildNode(&root, rdfAttr);
    
    const XML_Node* result = PickBestRoot(root, 0);
    EXPECT_EQ(result, nullptr);
    
    delete rdfAttr;
}

// Test: x:xmpmeta is preferred over rdf:RDF at same level
TEST_F(PickBestRootTest_1959, XmpmetaPreferredOverRdfRDFAtSameLevel_1959) {
    XML_Node root(nullptr, "root", kRootNode);
    XML_Node* xmpmetaNode = createNode(&root, "x:xmpmeta", kElemNode);
    addChildNode(&root, xmpmetaNode);
    
    XML_Node* rdfInsideMeta = createNode(xmpmetaNode, "rdf:RDF", kElemNode);
    addChildNode(xmpmetaNode, rdfInsideMeta);
    
    XML_Node* rdfDirect = createNode(&root, "rdf:RDF", kElemNode);
    addChildNode(&root, rdfDirect);
    
    const XML_Node* result = PickBestRoot(root, 0);
    // The first loop finds x:xmpmeta and recurses, finding rdf:RDF inside it
    EXPECT_EQ(result, rdfInsideMeta);
    
    delete rdfInsideMeta;
    delete xmpmetaNode;
    delete rdfDirect;
}

// Test: Deep nested rdf:RDF is found through recursive third loop
TEST_F(PickBestRootTest_1959, DeepNestedRdfRDFFound_1959) {
    XML_Node root(nullptr, "root", kRootNode);
    XML_Node* wrapper = createNode(&root, "wrapper", kElemNode);
    addChildNode(&root, wrapper);
    
    XML_Node* rdfNode = createNode(wrapper, "rdf:RDF", kElemNode);
    addChildNode(wrapper, rdfNode);
    
    const XML_Node* result = PickBestRoot(root, 0);
    EXPECT_EQ(result, rdfNode);
    
    delete rdfNode;
    delete wrapper;
}

// Test: Deep nested x:xmpmeta with rdf:RDF inside
TEST_F(PickBestRootTest_1959, DeepNestedXmpmetaWithRdfRDF_1959) {
    XML_Node root(nullptr, "root", kRootNode);
    XML_Node* wrapper = createNode(&root, "wrapper", kElemNode);
    addChildNode(&root, wrapper);
    
    XML_Node* xmpmetaNode = createNode(wrapper, "x:xmpmeta", kElemNode);
    addChildNode(wrapper, xmpmetaNode);
    
    XML_Node* rdfNode = createNode(xmpmetaNode, "rdf:RDF", kElemNode);
    addChildNode(xmpmetaNode, rdfNode);
    
    const XML_Node* result = PickBestRoot(root, 0);
    EXPECT_EQ(result, rdfNode);
    
    delete rdfNode;
    delete xmpmetaNode;
    delete wrapper;
}

// Test: kXMP_RequireXMPMeta with x:xmpmeta containing rdf:RDF - should succeed
TEST_F(PickBestRootTest_1959, RequireXMPMetaWithXmpmetaSucceeds_1959) {
    XML_Node root(nullptr, "root", kRootNode);
    XML_Node* xmpmetaNode = createNode(&root, "x:xmpmeta", kElemNode);
    addChildNode(&root, xmpmetaNode);
    
    XML_Node* rdfNode = createNode(xmpmetaNode, "rdf:RDF", kElemNode);
    addChildNode(xmpmetaNode, rdfNode);
    
    const XML_Node* result = PickBestRoot(root, kXMP_RequireXMPMeta);
    // x:xmpmeta found in first loop, recurse with options=0, finds rdf:RDF
    EXPECT_EQ(result, rdfNode);
    
    delete rdfNode;
    delete xmpmetaNode;
}

// Test: Multiple children, first non-element, second is x:xmpmeta
TEST_F(PickBestRootTest_1959, SkipsNonElementFindsXmpmeta_1959) {
    XML_Node root(nullptr, "root", kRootNode);
    XML_Node* piNode = createNode(&root, "x:xmpmeta", kPINode);
    addChildNode(&root, piNode);
    
    XML_Node* xmpmetaNode = createNode(&root, "x:xmpmeta", kElemNode);
    addChildNode(&root, xmpmetaNode);
    
    XML_Node* rdfNode = createNode(xmpmetaNode, "rdf:RDF", kElemNode);
    addChildNode(xmpmetaNode, rdfNode);
    
    const XML_Node* result = PickBestRoot(root, 0);
    EXPECT_EQ(result, rdfNode);
    
    delete rdfNode;
    delete xmpmetaNode;
    delete piNode;
}

// Test: Empty x:xmpmeta (no rdf:RDF inside) returns null
TEST_F(PickBestRootTest_1959, EmptyXmpmetaReturnsNull_1959) {
    XML_Node root(nullptr, "root", kRootNode);
    XML_Node* xmpmetaNode = createNode(&root, "x:xmpmeta", kElemNode);
    addChildNode(&root, xmpmetaNode);
    
    const XML_Node* result = PickBestRoot(root, 0);
    EXPECT_EQ(result, nullptr);
    
    delete xmpmetaNode;
}

// Test: Unrelated element nodes only, no xmpmeta or rdf:RDF
TEST_F(PickBestRootTest_1959, UnrelatedElementNodesReturnNull_1959) {
    XML_Node root(nullptr, "root", kRootNode);
    XML_Node* elem1 = createNode(&root, "foo:bar", kElemNode);
    addChildNode(&root, elem1);
    XML_Node* elem2 = createNode(&root, "baz:qux", kElemNode);
    addChildNode(&root, elem2);
    
    const XML_Node* result = PickBestRoot(root, 0);
    EXPECT_EQ(result, nullptr);
    
    delete elem1;
    delete elem2;
}

// Test: Multiple rdf:RDF nodes - first one is returned
TEST_F(PickBestRootTest_1959, FirstRdfRDFNodeReturned_1959) {
    XML_Node root(nullptr, "root", kRootNode);
    XML_Node* rdf1 = createNode(&root, "rdf:RDF", kElemNode);
    addChildNode(&root, rdf1);
    XML_Node* rdf2 = createNode(&root, "rdf:RDF", kElemNode);
    addChildNode(&root, rdf2);
    
    const XML_Node* result = PickBestRoot(root, 0);
    EXPECT_EQ(result, rdf1);
    
    delete rdf1;
    delete rdf2;
}

// Test: x:xmpmeta found first even if rdf:RDF appears before in different position
TEST_F(PickBestRootTest_1959, XmpmetaFoundBeforeRdfRDF_1959) {
    XML_Node root(nullptr, "root", kRootNode);
    // First child is an element but not xmpmeta/xapmeta
    XML_Node* other = createNode(&root, "other", kElemNode);
    addChildNode(&root, other);
    
    // rdf:RDF comes after in the first loop scan but xmpmeta check is done first
    XML_Node* rdfDirect = createNode(&root, "rdf:RDF", kElemNode);
    addChildNode(&root, rdfDirect);
    
    // The first loop doesn't find x:xmpmeta, second loop finds rdf:RDF
    const XML_Node* result = PickBestRoot(root, 0);
    EXPECT_EQ(result, rdfDirect);
    
    delete other;
    delete rdfDirect;
}

// Test: kXMP_RequireXMPMeta with nested rdf:RDF in non-xmpmeta wrapper - goes through third loop
TEST_F(PickBestRootTest_1959, RequireXMPMetaDeepNestedSearchSkipsDirectRdf_1959) {
    XML_Node root(nullptr, "root", kRootNode);
    XML_Node* wrapper = createNode(&root, "wrapper", kElemNode);
    addChildNode(&root, wrapper);
    
    // rdf:RDF nested in wrapper but no x:xmpmeta
    XML_Node* rdfNode = createNode(wrapper, "rdf:RDF", kElemNode);
    addChildNode(wrapper, rdfNode);
    
    // With kXMP_RequireXMPMeta: first loop finds no x:xmpmeta at root level,
    // second loop is skipped, third loop recurses into "wrapper",
    // which again: first loop no xmpmeta, second loop skipped (still kXMP_RequireXMPMeta),
    // third loop recurses into rdf:RDF (empty), returns null.
    const XML_Node* result = PickBestRoot(root, kXMP_RequireXMPMeta);
    EXPECT_EQ(result, nullptr);
    
    delete rdfNode;
    delete wrapper;
}

// Test: Nested x:xmpmeta under wrapper with RequireXMPMeta - should find it
TEST_F(PickBestRootTest_1959, RequireXMPMetaNestedXmpmetaFound_1959) {
    XML_Node root(nullptr, "root", kRootNode);
    XML_Node* wrapper = createNode(&root, "wrapper", kElemNode);
    addChildNode(&root, wrapper);
    
    XML_Node* xmpmetaNode = createNode(wrapper, "x:xmpmeta", kElemNode);
    addChildNode(wrapper, xmpmetaNode);
    
    XML_Node* rdfNode = createNode(xmpmetaNode, "rdf:RDF", kElemNode);
    addChildNode(xmpmetaNode, rdfNode);
    
    // Third loop recurses into wrapper, first loop finds x:xmpmeta, recurses with options=0
    const XML_Node* result = PickBestRoot(root, kXMP_RequireXMPMeta);
    EXPECT_EQ(result, rdfNode);
    
    delete rdfNode;
    delete xmpmetaNode;
    delete wrapper;
}

// Test: Single child that is PI node (not element) - returns null
TEST_F(PickBestRootTest_1959, SinglePINodeReturnsNull_1959) {
    XML_Node root(nullptr, "root", kRootNode);
    XML_Node* piNode = createNode(&root, "processing-instruction", kPINode);
    addChildNode(&root, piNode);
    
    const XML_Node* result = PickBestRoot(root, 0);
    EXPECT_EQ(result, nullptr);
    
    delete piNode;
}

// Test: x:xmpmeta recursion resets options to 0
TEST_F(PickBestRootTest_1959, XmpmetaRecursionResetsOptions_1959) {
    // When x:xmpmeta is found, it recurses with options=0
    // So even if original options had kXMP_RequireXMPMeta,
    // rdf:RDF can be found directly inside x:xmpmeta
    XML_Node root(nullptr, "root", kRootNode);
    XML_Node* xmpmetaNode = createNode(&root, "x:xmpmeta", kElemNode);
    addChildNode(&root, xmpmetaNode);
    
    XML_Node* rdfNode = createNode(xmpmetaNode, "rdf:RDF", kElemNode);
    addChildNode(xmpmetaNode, rdfNode);
    
    // Even with kXMP_RequireXMPMeta, since we find x:xmpmeta first,
    // recursion uses options=0, so rdf:RDF is found
    const XML_Node* result = PickBestRoot(root, kXMP_RequireXMPMeta);
    EXPECT_EQ(result, rdfNode);
    
    delete rdfNode;
    delete xmpmetaNode;
}
