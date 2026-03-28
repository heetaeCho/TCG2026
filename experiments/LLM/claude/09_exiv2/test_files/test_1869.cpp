#include <gtest/gtest.h>
#include <vector>
#include <string>

// Minimal type definitions to match the XMP_Node interface
typedef unsigned int XMP_OptionBits;
typedef const char* XMP_StringPtr;
typedef std::string XMP_VarString;

class XMP_Node;
typedef std::vector<XMP_Node*> XMP_NodeOffspring;

class XMP_Node {
public:
    XMP_OptionBits options;
    XMP_VarString name;
    XMP_VarString value;
    XMP_Node* parent;
    XMP_NodeOffspring children;
    XMP_NodeOffspring qualifiers;

    XMP_Node(XMP_Node* _parent, XMP_StringPtr _name, XMP_OptionBits _options)
        : options(_options), name(_name), parent(_parent) {}

    XMP_Node(XMP_Node* _parent, const XMP_VarString& _name, XMP_OptionBits _options)
        : options(_options), name(_name), parent(_parent) {}

    XMP_Node(XMP_Node* _parent, XMP_StringPtr _name, XMP_StringPtr _value, XMP_OptionBits _options)
        : options(_options), name(_name), value(_value), parent(_parent) {}

    XMP_Node(XMP_Node* _parent, const XMP_VarString& _name, const XMP_VarString& _value, XMP_OptionBits _options)
        : options(_options), name(_name), value(_value), parent(_parent) {}

    void RemoveQualifiers() {
        for (size_t i = 0, vLim = qualifiers.size(); i < vLim; ++i) {
            if (qualifiers[i] != 0) delete qualifiers[i];
        }
        qualifiers.clear();
    }

    virtual ~XMP_Node() {}

private:
    XMP_Node() : options(0), parent(0) {}
};

// Test fixture
class XMPNodeTest_1869 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Construction with parent, name (const char*), and options
TEST_F(XMPNodeTest_1869, ConstructWithStringPtrName_1869) {
    XMP_Node node(nullptr, "testName", 0);
    EXPECT_EQ(node.name, "testName");
    EXPECT_EQ(node.parent, nullptr);
    EXPECT_EQ(node.options, 0u);
    EXPECT_TRUE(node.value.empty());
    EXPECT_TRUE(node.children.empty());
    EXPECT_TRUE(node.qualifiers.empty());
}

// Test: Construction with parent, name (std::string), and options
TEST_F(XMPNodeTest_1869, ConstructWithVarStringName_1869) {
    XMP_VarString name = "varStringName";
    XMP_Node node(nullptr, name, 42);
    EXPECT_EQ(node.name, "varStringName");
    EXPECT_EQ(node.options, 42u);
    EXPECT_EQ(node.parent, nullptr);
}

// Test: Construction with parent, name, value (const char*), and options
TEST_F(XMPNodeTest_1869, ConstructWithStringPtrNameAndValue_1869) {
    XMP_Node node(nullptr, "name", "value", 10);
    EXPECT_EQ(node.name, "name");
    EXPECT_EQ(node.value, "value");
    EXPECT_EQ(node.options, 10u);
}

// Test: Construction with parent, name, value (std::string), and options
TEST_F(XMPNodeTest_1869, ConstructWithVarStringNameAndValue_1869) {
    XMP_VarString name = "nodeName";
    XMP_VarString value = "nodeValue";
    XMP_Node node(nullptr, name, value, 99);
    EXPECT_EQ(node.name, "nodeName");
    EXPECT_EQ(node.value, "nodeValue");
    EXPECT_EQ(node.options, 99u);
}

// Test: Parent pointer is correctly set
TEST_F(XMPNodeTest_1869, ParentPointerIsSet_1869) {
    XMP_Node parentNode(nullptr, "parent", 0);
    XMP_Node childNode(&parentNode, "child", 0);
    EXPECT_EQ(childNode.parent, &parentNode);
}

// Test: RemoveQualifiers on empty qualifiers list
TEST_F(XMPNodeTest_1869, RemoveQualifiersEmpty_1869) {
    XMP_Node node(nullptr, "test", 0);
    EXPECT_TRUE(node.qualifiers.empty());
    node.RemoveQualifiers();  // Should not crash
    EXPECT_TRUE(node.qualifiers.empty());
}

// Test: RemoveQualifiers with one qualifier
TEST_F(XMPNodeTest_1869, RemoveQualifiersSingleElement_1869) {
    XMP_Node node(nullptr, "test", 0);
    XMP_Node* qual = new XMP_Node(&node, "qualifier1", 0);
    node.qualifiers.push_back(qual);
    EXPECT_EQ(node.qualifiers.size(), 1u);

    node.RemoveQualifiers();
    EXPECT_TRUE(node.qualifiers.empty());
}

// Test: RemoveQualifiers with multiple qualifiers
TEST_F(XMPNodeTest_1869, RemoveQualifiersMultipleElements_1869) {
    XMP_Node node(nullptr, "test", 0);
    node.qualifiers.push_back(new XMP_Node(&node, "qual1", 0));
    node.qualifiers.push_back(new XMP_Node(&node, "qual2", 0));
    node.qualifiers.push_back(new XMP_Node(&node, "qual3", 0));
    EXPECT_EQ(node.qualifiers.size(), 3u);

    node.RemoveQualifiers();
    EXPECT_TRUE(node.qualifiers.empty());
}

// Test: RemoveQualifiers with null pointers in qualifiers list
TEST_F(XMPNodeTest_1869, RemoveQualifiersWithNullPointers_1869) {
    XMP_Node node(nullptr, "test", 0);
    node.qualifiers.push_back(nullptr);
    node.qualifiers.push_back(new XMP_Node(&node, "qual1", 0));
    node.qualifiers.push_back(nullptr);
    EXPECT_EQ(node.qualifiers.size(), 3u);

    node.RemoveQualifiers();  // Should handle nulls gracefully
    EXPECT_TRUE(node.qualifiers.empty());
}

// Test: RemoveQualifiers called twice is safe
TEST_F(XMPNodeTest_1869, RemoveQualifiersCalledTwice_1869) {
    XMP_Node node(nullptr, "test", 0);
    node.qualifiers.push_back(new XMP_Node(&node, "qual1", 0));

    node.RemoveQualifiers();
    EXPECT_TRUE(node.qualifiers.empty());

    node.RemoveQualifiers();  // Second call should be no-op
    EXPECT_TRUE(node.qualifiers.empty());
}

// Test: RemoveQualifiers does not affect children
TEST_F(XMPNodeTest_1869, RemoveQualifiersDoesNotAffectChildren_1869) {
    XMP_Node node(nullptr, "test", 0);
    XMP_Node* child = new XMP_Node(&node, "child1", 0);
    node.children.push_back(child);
    node.qualifiers.push_back(new XMP_Node(&node, "qual1", 0));

    node.RemoveQualifiers();
    EXPECT_TRUE(node.qualifiers.empty());
    EXPECT_EQ(node.children.size(), 1u);
    EXPECT_EQ(node.children[0]->name, "child1");

    // Clean up children manually since RemoveQualifiers doesn't touch them
    delete child;
    node.children.clear();
}

// Test: RemoveQualifiers does not affect name or value
TEST_F(XMPNodeTest_1869, RemoveQualifiersPreservesNameAndValue_1869) {
    XMP_Node node(nullptr, "myName", "myValue", 55);
    node.qualifiers.push_back(new XMP_Node(&node, "qual", 0));

    node.RemoveQualifiers();
    EXPECT_EQ(node.name, "myName");
    EXPECT_EQ(node.value, "myValue");
    EXPECT_EQ(node.options, 55u);
}

// Test: RemoveQualifiers with qualifiers that have their own qualifiers (nested)
TEST_F(XMPNodeTest_1869, RemoveQualifiersWithNestedQualifiers_1869) {
    XMP_Node node(nullptr, "root", 0);
    XMP_Node* qual = new XMP_Node(&node, "qual1", 0);
    qual->qualifiers.push_back(new XMP_Node(qual, "nestedQual", 0));
    node.qualifiers.push_back(qual);

    EXPECT_EQ(node.qualifiers.size(), 1u);
    node.RemoveQualifiers();  // Should delete qual, which should handle nested cleanup via destructor
    EXPECT_TRUE(node.qualifiers.empty());
}

// Test: Construction with empty name and value
TEST_F(XMPNodeTest_1869, ConstructWithEmptyNameAndValue_1869) {
    XMP_Node node(nullptr, "", "", 0);
    EXPECT_TRUE(node.name.empty());
    EXPECT_TRUE(node.value.empty());
    EXPECT_EQ(node.options, 0u);
}

// Test: Options field stores large value
TEST_F(XMPNodeTest_1869, OptionsStoresLargeValue_1869) {
    XMP_OptionBits maxOpts = 0xFFFFFFFF;
    XMP_Node node(nullptr, "test", maxOpts);
    EXPECT_EQ(node.options, maxOpts);
}

// Test: RemoveQualifiers with many qualifiers
TEST_F(XMPNodeTest_1869, RemoveQualifiersManyElements_1869) {
    XMP_Node node(nullptr, "test", 0);
    const size_t count = 100;
    for (size_t i = 0; i < count; ++i) {
        node.qualifiers.push_back(new XMP_Node(&node, std::string("qual") + std::to_string(i), 0));
    }
    EXPECT_EQ(node.qualifiers.size(), count);

    node.RemoveQualifiers();
    EXPECT_TRUE(node.qualifiers.empty());
}
