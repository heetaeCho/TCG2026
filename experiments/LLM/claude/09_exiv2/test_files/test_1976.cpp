#include <gtest/gtest.h>
#include <string>
#include <map>
#include <vector>

// Include necessary headers
#include "XMLParserAdapter.hpp"

// We need to declare the function under test since it's static in the source file.
// Since CollectNamespaceDecls is a static function in XML_Node.cpp, we need to
// either include it or replicate its signature for testing. Since it's static,
// we'll need to include the source file to get access to it.
// This is a common pattern for testing static functions.

typedef std::map<std::string, std::string> NamespaceMap;

// Include the implementation to access the static function
// We need to make the static function accessible for testing
#include "XML_Node.cpp"

class CollectNamespaceDeclsTest_1976 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Element node with namespace and prefix collects the namespace
TEST_F(CollectNamespaceDeclsTest_1976, ElementWithNamespaceCollectsPrefix_1976) {
    XML_Node root(nullptr, "root", kElemNode);
    XML_Node child(nullptr, "xmp:Description", kElemNode);
    child.ns = "http://ns.adobe.com/xap/1.0/";
    root.content.push_back(&child);

    NamespaceMap nsMap;
    CollectNamespaceDecls(&nsMap, root);

    // root has no namespace, but child does
    // However, CollectNamespaceDecls recurses into content for kElemNode
    // child has ns set and name "xmp:Description", so prefix "xmp" should map
    EXPECT_EQ(nsMap.size(), 1u);
    EXPECT_EQ(nsMap["xmp"], "http://ns.adobe.com/xap/1.0/");
}

// Test: Node with empty namespace does not add to map
TEST_F(CollectNamespaceDeclsTest_1976, NodeWithEmptyNamespaceSkipped_1976) {
    XML_Node node(nullptr, "element", kElemNode);
    node.ns = "";

    NamespaceMap nsMap;
    CollectNamespaceDecls(&nsMap, node);

    EXPECT_TRUE(nsMap.empty());
}

// Test: Node with namespace extracts correct prefix before colon
TEST_F(CollectNamespaceDeclsTest_1976, PrefixExtractedCorrectly_1976) {
    XML_Node node(nullptr, "dc:title", kElemNode);
    node.ns = "http://purl.org/dc/elements/1.1/";

    NamespaceMap nsMap;
    CollectNamespaceDecls(&nsMap, node);

    EXPECT_EQ(nsMap.size(), 1u);
    EXPECT_EQ(nsMap["dc"], "http://purl.org/dc/elements/1.1/");
}

// Test: Attributes with namespaces are collected
TEST_F(CollectNamespaceDeclsTest_1976, AttributeNamespacesCollected_1976) {
    XML_Node node(nullptr, "root", kElemNode);
    
    XML_Node* attr = new XML_Node(&node, "xml:lang", kAttrNode);
    attr->ns = "http://www.w3.org/XML/1998/namespace";
    node.attrs.push_back(attr);

    NamespaceMap nsMap;
    CollectNamespaceDecls(&nsMap, node);

    EXPECT_EQ(nsMap.size(), 1u);
    EXPECT_EQ(nsMap["xml"], "http://www.w3.org/XML/1998/namespace");

    delete attr;
}

// Test: Recursive collection from nested elements
TEST_F(CollectNamespaceDeclsTest_1976, NestedElementsCollected_1976) {
    XML_Node root(nullptr, "rdf:RDF", kElemNode);
    root.ns = "http://www.w3.org/1999/02/22-rdf-syntax-ns#";

    XML_Node* child = new XML_Node(&root, "dc:title", kElemNode);
    child->ns = "http://purl.org/dc/elements/1.1/";
    root.content.push_back(child);

    XML_Node* grandchild = new XML_Node(child, "xmp:Rating", kElemNode);
    grandchild->ns = "http://ns.adobe.com/xap/1.0/";
    child->content.push_back(grandchild);

    NamespaceMap nsMap;
    CollectNamespaceDecls(&nsMap, root);

    EXPECT_EQ(nsMap.size(), 3u);
    EXPECT_EQ(nsMap["rdf"], "http://www.w3.org/1999/02/22-rdf-syntax-ns#");
    EXPECT_EQ(nsMap["dc"], "http://purl.org/dc/elements/1.1/");
    EXPECT_EQ(nsMap["xmp"], "http://ns.adobe.com/xap/1.0/");

    delete grandchild;
    delete child;
}

// Test: Non-element content nodes are not recursed into
TEST_F(CollectNamespaceDeclsTest_1976, NonElementContentNotRecursed_1976) {
    XML_Node root(nullptr, "rdf:RDF", kElemNode);
    root.ns = "http://www.w3.org/1999/02/22-rdf-syntax-ns#";

    XML_Node* cdataChild = new XML_Node(&root, "some:cdata", kCDataNode);
    cdataChild->ns = "http://example.com/cdata";
    root.content.push_back(cdataChild);

    NamespaceMap nsMap;
    CollectNamespaceDecls(&nsMap, root);

    // Only root's namespace should be collected; cdata node is not kElemNode
    // so it won't be recursed into for its content/attrs, but its own ns IS checked
    // Wait - looking at the code more carefully:
    // The code checks: if content.kind == kElemNode then recurse
    // So cdataChild won't be recursed. But cdataChild's own ns won't be checked
    // because CollectNamespaceDecls is only called on kElemNode content children
    EXPECT_EQ(nsMap.size(), 1u);
    EXPECT_EQ(nsMap["rdf"], "http://www.w3.org/1999/02/22-rdf-syntax-ns#");

    delete cdataChild;
}

// Test: Multiple attributes with different namespaces
TEST_F(CollectNamespaceDeclsTest_1976, MultipleAttributeNamespaces_1976) {
    XML_Node node(nullptr, "elem:node", kElemNode);
    node.ns = "http://example.com/elem";

    XML_Node* attr1 = new XML_Node(&node, "ns1:attr1", kAttrNode);
    attr1->ns = "http://example.com/ns1";
    node.attrs.push_back(attr1);

    XML_Node* attr2 = new XML_Node(&node, "ns2:attr2", kAttrNode);
    attr2->ns = "http://example.com/ns2";
    node.attrs.push_back(attr2);

    NamespaceMap nsMap;
    CollectNamespaceDecls(&nsMap, node);

    EXPECT_EQ(nsMap.size(), 3u);
    EXPECT_EQ(nsMap["elem"], "http://example.com/elem");
    EXPECT_EQ(nsMap["ns1"], "http://example.com/ns1");
    EXPECT_EQ(nsMap["ns2"], "http://example.com/ns2");

    delete attr1;
    delete attr2;
}

// Test: Same prefix with different namespaces - last one wins (map behavior)
TEST_F(CollectNamespaceDeclsTest_1976, DuplicatePrefixLastWins_1976) {
    XML_Node root(nullptr, "ns:Root", kElemNode);
    root.ns = "http://example.com/first";

    XML_Node* child = new XML_Node(&root, "ns:Child", kElemNode);
    child->ns = "http://example.com/second";
    root.content.push_back(child);

    NamespaceMap nsMap;
    CollectNamespaceDecls(&nsMap, root);

    // The root is processed first, then the child. The child overwrites.
    EXPECT_EQ(nsMap.size(), 1u);
    EXPECT_EQ(nsMap["ns"], "http://example.com/second");

    delete child;
}

// Test: Empty content and attrs on element node
TEST_F(CollectNamespaceDeclsTest_1976, EmptyElementNode_1976) {
    XML_Node node(nullptr, "test:empty", kElemNode);
    node.ns = "http://example.com/test";

    NamespaceMap nsMap;
    CollectNamespaceDecls(&nsMap, node);

    EXPECT_EQ(nsMap.size(), 1u);
    EXPECT_EQ(nsMap["test"], "http://example.com/test");
}

// Test: Non-element node kind with namespace but no content recursion
TEST_F(CollectNamespaceDeclsTest_1976, AttrNodeKindNoRecursion_1976) {
    XML_Node node(nullptr, "attr:name", kAttrNode);
    node.ns = "http://example.com/attr";

    // Even though kAttrNode, the ns check is done, but no recursion into attrs/content
    NamespaceMap nsMap;
    CollectNamespaceDecls(&nsMap, node);

    EXPECT_EQ(nsMap.size(), 1u);
    EXPECT_EQ(nsMap["attr"], "http://example.com/attr");
}

// Test: Attribute with empty namespace is not added
TEST_F(CollectNamespaceDeclsTest_1976, AttributeWithEmptyNamespace_1976) {
    XML_Node node(nullptr, "elem", kElemNode);

    XML_Node* attr = new XML_Node(&node, "localattr", kAttrNode);
    attr->ns = "";
    node.attrs.push_back(attr);

    NamespaceMap nsMap;
    CollectNamespaceDecls(&nsMap, node);

    EXPECT_TRUE(nsMap.empty());

    delete attr;
}

// Test: Deep nesting collects all namespaces
TEST_F(CollectNamespaceDeclsTest_1976, DeepNestingCollectsAll_1976) {
    XML_Node root(nullptr, "a:Root", kElemNode);
    root.ns = "http://example.com/a";

    XML_Node* level1 = new XML_Node(&root, "b:Level1", kElemNode);
    level1->ns = "http://example.com/b";
    root.content.push_back(level1);

    XML_Node* level2 = new XML_Node(level1, "c:Level2", kElemNode);
    level2->ns = "http://example.com/c";
    level1->content.push_back(level2);

    XML_Node* level3 = new XML_Node(level2, "d:Level3", kElemNode);
    level3->ns = "http://example.com/d";
    level2->content.push_back(level3);

    NamespaceMap nsMap;
    CollectNamespaceDecls(&nsMap, root);

    EXPECT_EQ(nsMap.size(), 4u);
    EXPECT_EQ(nsMap["a"], "http://example.com/a");
    EXPECT_EQ(nsMap["b"], "http://example.com/b");
    EXPECT_EQ(nsMap["c"], "http://example.com/c");
    EXPECT_EQ(nsMap["d"], "http://example.com/d");

    delete level3;
    delete level2;
    delete level1;
}

// Test: PI node kind with namespace
TEST_F(CollectNamespaceDeclsTest_1976, PINodeWithNamespace_1976) {
    XML_Node node(nullptr, "pi:instruction", kPINode);
    node.ns = "http://example.com/pi";

    NamespaceMap nsMap;
    CollectNamespaceDecls(&nsMap, node);

    // ns is not empty, so prefix should be extracted
    EXPECT_EQ(nsMap.size(), 1u);
    EXPECT_EQ(nsMap["pi"], "http://example.com/pi");
}

// Test: Mixed content with element and non-element children
TEST_F(CollectNamespaceDeclsTest_1976, MixedContentChildren_1976) {
    XML_Node root(nullptr, "root", kElemNode);

    XML_Node* elemChild = new XML_Node(&root, "ns1:elem", kElemNode);
    elemChild->ns = "http://example.com/ns1";
    root.content.push_back(elemChild);

    XML_Node* textChild = new XML_Node(&root, "ns2:text", kCDataNode);
    textChild->ns = "http://example.com/ns2";
    root.content.push_back(textChild);

    XML_Node* elemChild2 = new XML_Node(&root, "ns3:elem2", kElemNode);
    elemChild2->ns = "http://example.com/ns3";
    root.content.push_back(elemChild2);

    NamespaceMap nsMap;
    CollectNamespaceDecls(&nsMap, root);

    // Only element children are recursed, so ns2 from CData should not appear
    EXPECT_EQ(nsMap.size(), 2u);
    EXPECT_EQ(nsMap["ns1"], "http://example.com/ns1");
    EXPECT_EQ(nsMap["ns3"], "http://example.com/ns3");

    delete elemChild;
    delete textChild;
    delete elemChild2;
}

// Test: Empty map passed in remains empty when no namespaces
TEST_F(CollectNamespaceDeclsTest_1976, EmptyMapRemainsEmpty_1976) {
    XML_Node node(nullptr, "simple", kElemNode);

    NamespaceMap nsMap;
    CollectNamespaceDecls(&nsMap, node);

    EXPECT_TRUE(nsMap.empty());
}

// Test: Existing entries in map are preserved
TEST_F(CollectNamespaceDeclsTest_1976, ExistingEntriesPreserved_1976) {
    XML_Node node(nullptr, "ns:elem", kElemNode);
    node.ns = "http://example.com/ns";

    NamespaceMap nsMap;
    nsMap["existing"] = "http://example.com/existing";

    CollectNamespaceDecls(&nsMap, node);

    EXPECT_EQ(nsMap.size(), 2u);
    EXPECT_EQ(nsMap["existing"], "http://example.com/existing");
    EXPECT_EQ(nsMap["ns"], "http://example.com/ns");
}
