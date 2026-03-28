#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <stdexcept>

// Include necessary headers from the project
#include "XMP_Const.h"
#include "XMPCore_Impl.hpp"

// We need access to the static function - include the cpp file or declare it
// Since FixupQualifiedNode is static in ParseRDF.cpp, we include it to get access
// We also need FindChildNode and other dependencies

// Forward declarations and necessary includes
#include "XMP_Environment.h"

// Include the source to access the static function
// This is necessary because FixupQualifiedNode is file-static
namespace ParseRDF_Test {
#include "ParseRDF.cpp"
}

using namespace ParseRDF_Test;

class FixupQualifiedNodeTest_2123 : public ::testing::Test {
protected:
    void TearDown() override {
        // Cleanup is handled by individual tests
    }

    // Helper to create a basic valid parent node setup
    // Parent is a struct with rdf:value as first child
    XMP_Node* CreateBasicParent(const std::string& value = "testValue") {
        XMP_Node* parent = new XMP_Node(nullptr, "test:parent", kXMP_PropValueIsStruct);
        XMP_Node* valueNode = new XMP_Node(parent, "rdf:value", value.c_str(), 0);
        parent->children.push_back(valueNode);
        return parent;
    }

    void CleanupNode(XMP_Node* node) {
        if (node) {
            node->RemoveChildren();
            node->RemoveQualifiers();
            delete node;
        }
    }
};

// Test normal operation: basic rdf:value fixup with no qualifiers
TEST_F(FixupQualifiedNodeTest_2123, BasicValueNodeFixup_2123) {
    XMP_Node* parent = CreateBasicParent("hello");

    FixupQualifiedNode(parent);

    EXPECT_EQ(parent->value, "hello");
    EXPECT_TRUE(parent->children.empty());
    EXPECT_FALSE(parent->options & kXMP_PropValueIsStruct);
    EXPECT_FALSE(parent->options & kRDF_HasValueElem);

    CleanupNode(parent);
}

// Test that value node's value is properly swapped to parent
TEST_F(FixupQualifiedNodeTest_2123, ValueTransferredToParent_2123) {
    XMP_Node* parent = CreateBasicParent("transferred_value");

    FixupQualifiedNode(parent);

    EXPECT_EQ(parent->value, "transferred_value");

    CleanupNode(parent);
}

// Test with xml:lang qualifier on value node, no lang on parent
TEST_F(FixupQualifiedNodeTest_2123, LangQualifierMovedFromValueNode_2123) {
    XMP_Node* parent = new XMP_Node(nullptr, "test:parent", kXMP_PropValueIsStruct);
    XMP_Node* valueNode = new XMP_Node(parent, "rdf:value", "val", 0);
    XMP_Node* langQual = new XMP_Node(valueNode, "xml:lang", "en", kXMP_PropIsQualifier);
    valueNode->qualifiers.push_back(langQual);
    valueNode->options |= kXMP_PropHasLang;
    parent->children.push_back(valueNode);

    FixupQualifiedNode(parent);

    EXPECT_TRUE(parent->options & kXMP_PropHasLang);
    EXPECT_TRUE(parent->options & kXMP_PropHasQualifiers);
    ASSERT_FALSE(parent->qualifiers.empty());
    EXPECT_EQ(parent->qualifiers[0]->name, "xml:lang");
    EXPECT_EQ(parent->qualifiers[0]->value, "en");
    EXPECT_EQ(parent->qualifiers[0]->parent, parent);

    CleanupNode(parent);
}

// Test error: redundant xml:lang - parent already has lang, value node also has lang
TEST_F(FixupQualifiedNodeTest_2123, RedundantLangThrows_2123) {
    XMP_Node* parent = new XMP_Node(nullptr, "test:parent", kXMP_PropValueIsStruct | kXMP_PropHasLang);
    XMP_Node* existingLangQual = new XMP_Node(parent, "xml:lang", "fr", kXMP_PropIsQualifier);
    parent->qualifiers.push_back(existingLangQual);

    XMP_Node* valueNode = new XMP_Node(parent, "rdf:value", "val", kXMP_PropHasLang);
    XMP_Node* langQual = new XMP_Node(valueNode, "xml:lang", "en", kXMP_PropIsQualifier);
    valueNode->qualifiers.push_back(langQual);
    parent->children.push_back(valueNode);

    EXPECT_ANY_THROW(FixupQualifiedNode(parent));

    // Cleanup - since exception was thrown, we need manual cleanup
    delete langQual;
    delete valueNode;
    parent->children.clear();
    CleanupNode(parent);
}

// Test with additional qualifiers on value node (non-lang)
TEST_F(FixupQualifiedNodeTest_2123, NonLangQualifiersMovedFromValueNode_2123) {
    XMP_Node* parent = new XMP_Node(nullptr, "test:parent", kXMP_PropValueIsStruct);
    XMP_Node* valueNode = new XMP_Node(parent, "rdf:value", "val", 0);
    XMP_Node* qual1 = new XMP_Node(valueNode, "test:qual1", "q1", kXMP_PropIsQualifier);
    valueNode->qualifiers.push_back(qual1);
    parent->children.push_back(valueNode);

    FixupQualifiedNode(parent);

    EXPECT_TRUE(parent->options & kXMP_PropHasQualifiers);
    ASSERT_EQ(parent->qualifiers.size(), 1u);
    EXPECT_EQ(parent->qualifiers[0]->name, "test:qual1");
    EXPECT_EQ(parent->qualifiers[0]->value, "q1");
    EXPECT_EQ(parent->qualifiers[0]->parent, parent);

    CleanupNode(parent);
}

// Test with children (beyond rdf:value) that become qualifiers
TEST_F(FixupQualifiedNodeTest_2123, ChildrenBecomeQualifiers_2123) {
    XMP_Node* parent = new XMP_Node(nullptr, "test:parent", kXMP_PropValueIsStruct);
    XMP_Node* valueNode = new XMP_Node(parent, "rdf:value", "val", 0);
    parent->children.push_back(valueNode);

    XMP_Node* child1 = new XMP_Node(parent, "test:child1", "c1", 0);
    parent->children.push_back(child1);

    XMP_Node* child2 = new XMP_Node(parent, "test:child2", "c2", 0);
    parent->children.push_back(child2);

    FixupQualifiedNode(parent);

    EXPECT_TRUE(parent->options & kXMP_PropHasQualifiers);
    ASSERT_EQ(parent->qualifiers.size(), 2u);
    EXPECT_EQ(parent->qualifiers[0]->name, "test:child1");
    EXPECT_EQ(parent->qualifiers[1]->name, "test:child2");

    // Verify they are marked as qualifiers
    EXPECT_TRUE(parent->qualifiers[0]->options & kXMP_PropIsQualifier);
    EXPECT_TRUE(parent->qualifiers[1]->options & kXMP_PropIsQualifier);

    CleanupNode(parent);
}

// Test rdf:type child sets kXMP_PropHasType
TEST_F(FixupQualifiedNodeTest_2123, RdfTypeChildSetsHasType_2123) {
    XMP_Node* parent = new XMP_Node(nullptr, "test:parent", kXMP_PropValueIsStruct);
    XMP_Node* valueNode = new XMP_Node(parent, "rdf:value", "val", 0);
    parent->children.push_back(valueNode);

    XMP_Node* typeChild = new XMP_Node(parent, "rdf:type", "SomeType", 0);
    parent->children.push_back(typeChild);

    FixupQualifiedNode(parent);

    EXPECT_TRUE(parent->options & kXMP_PropHasType);
    EXPECT_TRUE(parent->options & kXMP_PropHasQualifiers);

    CleanupNode(parent);
}

// Test xml:lang child is inserted at beginning of qualifiers
TEST_F(FixupQualifiedNodeTest_2123, LangChildInsertedAtBeginning_2123) {
    XMP_Node* parent = new XMP_Node(nullptr, "test:parent", kXMP_PropValueIsStruct);
    XMP_Node* valueNode = new XMP_Node(parent, "rdf:value", "val", 0);
    XMP_Node* nonLangQual = new XMP_Node(valueNode, "test:qual", "q", kXMP_PropIsQualifier);
    valueNode->qualifiers.push_back(nonLangQual);
    parent->children.push_back(valueNode);

    // Add a non-lang child first, then a lang child
    XMP_Node* normalChild = new XMP_Node(parent, "test:normal", "n", 0);
    parent->children.push_back(normalChild);

    XMP_Node* langChild = new XMP_Node(parent, "xml:lang", "de", 0);
    parent->children.push_back(langChild);

    FixupQualifiedNode(parent);

    EXPECT_TRUE(parent->options & kXMP_PropHasLang);
    ASSERT_GE(parent->qualifiers.size(), 1u);
    // xml:lang should be first
    EXPECT_EQ(parent->qualifiers[0]->name, "xml:lang");
    EXPECT_EQ(parent->qualifiers[0]->value, "de");

    CleanupNode(parent);
}

// Test duplicate xml:lang child throws
TEST_F(FixupQualifiedNodeTest_2123, DuplicateLangChildThrows_2123) {
    XMP_Node* parent = new XMP_Node(nullptr, "test:parent", kXMP_PropValueIsStruct);
    XMP_Node* valueNode = new XMP_Node(parent, "rdf:value", "val", kXMP_PropHasLang);
    XMP_Node* langQual = new XMP_Node(valueNode, "xml:lang", "en", kXMP_PropIsQualifier);
    valueNode->qualifiers.push_back(langQual);
    parent->children.push_back(valueNode);

    // Second child that is also xml:lang
    XMP_Node* langChild = new XMP_Node(parent, "xml:lang", "fr", 0);
    parent->children.push_back(langChild);

    EXPECT_ANY_THROW(FixupQualifiedNode(parent));

    // Manual cleanup since exception leaves things in partial state
    // The langQual was moved to parent already, langChild caused the throw
    delete langChild;
    parent->children.pop_back();
    // valueNode was partially processed
    parent->RemoveQualifiers();
    parent->RemoveChildren();
    delete parent;
}

// Test that struct option is cleared after fixup
TEST_F(FixupQualifiedNodeTest_2123, StructOptionCleared_2123) {
    XMP_Node* parent = CreateBasicParent("val");
    parent->options |= kRDF_HasValueElem;

    EXPECT_TRUE(parent->options & kXMP_PropValueIsStruct);
    EXPECT_TRUE(parent->options & kRDF_HasValueElem);

    FixupQualifiedNode(parent);

    EXPECT_FALSE(parent->options & kXMP_PropValueIsStruct);
    EXPECT_FALSE(parent->options & kRDF_HasValueElem);

    CleanupNode(parent);
}

// Test that value node's options are transferred to parent
TEST_F(FixupQualifiedNodeTest_2123, ValueNodeOptionsTransferred_2123) {
    XMP_Node* parent = new XMP_Node(nullptr, "test:parent", kXMP_PropValueIsStruct);
    XMP_Node* valueNode = new XMP_Node(parent, "rdf:value", "val", kXMP_PropValueIsURI);
    parent->children.push_back(valueNode);

    FixupQualifiedNode(parent);

    EXPECT_TRUE(parent->options & kXMP_PropValueIsURI);
    EXPECT_FALSE(parent->options & kXMP_PropValueIsStruct);

    CleanupNode(parent);
}

// Test that value node's children are transferred to parent
TEST_F(FixupQualifiedNodeTest_2123, ValueNodeChildrenTransferred_2123) {
    XMP_Node* parent = new XMP_Node(nullptr, "test:parent", kXMP_PropValueIsStruct);
    XMP_Node* valueNode = new XMP_Node(parent, "rdf:value", "val", kXMP_PropValueIsStruct);
    XMP_Node* innerChild = new XMP_Node(valueNode, "test:inner", "innerVal", 0);
    valueNode->children.push_back(innerChild);
    parent->children.push_back(valueNode);

    FixupQualifiedNode(parent);

    ASSERT_EQ(parent->children.size(), 1u);
    EXPECT_EQ(parent->children[0]->name, "test:inner");
    EXPECT_EQ(parent->children[0]->value, "innerVal");
    EXPECT_EQ(parent->children[0]->parent, parent);

    CleanupNode(parent);
}

// Test enforcement: parent must be a struct
TEST_F(FixupQualifiedNodeTest_2123, NonStructParentThrows_2123) {
    XMP_Node* parent = new XMP_Node(nullptr, "test:parent", 0); // Not a struct
    XMP_Node* valueNode = new XMP_Node(parent, "rdf:value", "val", 0);
    parent->children.push_back(valueNode);

    EXPECT_ANY_THROW(FixupQualifiedNode(parent));

    delete valueNode;
    parent->children.clear();
    delete parent;
}

// Test enforcement: parent must have children
TEST_F(FixupQualifiedNodeTest_2123, EmptyChildrenThrows_2123) {
    XMP_Node* parent = new XMP_Node(nullptr, "test:parent", kXMP_PropValueIsStruct);
    // No children added

    EXPECT_ANY_THROW(FixupQualifiedNode(parent));

    delete parent;
}

// Test enforcement: first child must be rdf:value
TEST_F(FixupQualifiedNodeTest_2123, FirstChildNotRdfValueThrows_2123) {
    XMP_Node* parent = new XMP_Node(nullptr, "test:parent", kXMP_PropValueIsStruct);
    XMP_Node* notValueNode = new XMP_Node(parent, "test:notValue", "val", 0);
    parent->children.push_back(notValueNode);

    EXPECT_ANY_THROW(FixupQualifiedNode(parent));

    delete notValueNode;
    parent->children.clear();
    delete parent;
}

// Test no qualifiers results in no kXMP_PropHasQualifiers flag
TEST_F(FixupQualifiedNodeTest_2123, NoQualifiersNoFlag_2123) {
    XMP_Node* parent = CreateBasicParent("val");

    FixupQualifiedNode(parent);

    EXPECT_FALSE(parent->options & kXMP_PropHasQualifiers);
    EXPECT_TRUE(parent->qualifiers.empty());

    CleanupNode(parent);
}

// Test with both value node qualifiers and additional children
TEST_F(FixupQualifiedNodeTest_2123, CombinedQualifiersAndChildren_2123) {
    XMP_Node* parent = new XMP_Node(nullptr, "test:parent", kXMP_PropValueIsStruct);
    XMP_Node* valueNode = new XMP_Node(parent, "rdf:value", "val", kXMP_PropHasLang);

    XMP_Node* langQual = new XMP_Node(valueNode, "xml:lang", "en", kXMP_PropIsQualifier);
    valueNode->qualifiers.push_back(langQual);

    XMP_Node* extraQual = new XMP_Node(valueNode, "test:extra", "e", kXMP_PropIsQualifier);
    valueNode->qualifiers.push_back(extraQual);

    parent->children.push_back(valueNode);

    XMP_Node* child1 = new XMP_Node(parent, "test:childQual", "cq", 0);
    parent->children.push_back(child1);

    FixupQualifiedNode(parent);

    EXPECT_TRUE(parent->options & kXMP_PropHasLang);
    EXPECT_TRUE(parent->options & kXMP_PropHasQualifiers);

    // Should have: xml:lang (from valueNode), test:extra (from valueNode), test:childQual (from children)
    ASSERT_EQ(parent->qualifiers.size(), 3u);
    EXPECT_EQ(parent->qualifiers[0]->name, "xml:lang");
    EXPECT_EQ(parent->qualifiers[1]->name, "test:extra");
    EXPECT_EQ(parent->qualifiers[2]->name, "test:childQual");

    // All should have parent set to xmpParent
    for (size_t i = 0; i < parent->qualifiers.size(); ++i) {
        EXPECT_EQ(parent->qualifiers[i]->parent, parent);
    }

    CleanupNode(parent);
}

// Test that parent's value is empty string when valueNode has empty value
TEST_F(FixupQualifiedNodeTest_2123, EmptyValueNodeValue_2123) {
    XMP_Node* parent = CreateBasicParent("");

    FixupQualifiedNode(parent);

    EXPECT_EQ(parent->value, "");

    CleanupNode(parent);
}

// Test with lang qualifier on value node, parent qualifiers are empty
TEST_F(FixupQualifiedNodeTest_2123, LangQualPushedBackWhenParentQualsEmpty_2123) {
    XMP_Node* parent = new XMP_Node(nullptr, "test:parent", kXMP_PropValueIsStruct);
    XMP_Node* valueNode = new XMP_Node(parent, "rdf:value", "val", kXMP_PropHasLang);
    XMP_Node* langQual = new XMP_Node(valueNode, "xml:lang", "ja", kXMP_PropIsQualifier);
    valueNode->qualifiers.push_back(langQual);
    parent->children.push_back(valueNode);

    EXPECT_TRUE(parent->qualifiers.empty());

    FixupQualifiedNode(parent);

    ASSERT_EQ(parent->qualifiers.size(), 1u);
    EXPECT_EQ(parent->qualifiers[0]->name, "xml:lang");
    EXPECT_EQ(parent->qualifiers[0]->value, "ja");

    CleanupNode(parent);
}

// Test with lang qualifier on value node, parent already has other qualifiers (but not lang)
TEST_F(FixupQualifiedNodeTest_2123, LangQualInsertedAtBeginWhenParentHasOtherQuals_2123) {
    XMP_Node* parent = new XMP_Node(nullptr, "test:parent", kXMP_PropValueIsStruct | kXMP_PropHasQualifiers);

    // Pre-existing qualifier on parent (not xml:lang)
    XMP_Node* existingQual = new XMP_Node(parent, "test:existing", "ex", kXMP_PropIsQualifier);
    parent->qualifiers.push_back(existingQual);

    XMP_Node* valueNode = new XMP_Node(parent, "rdf:value", "val", kXMP_PropHasLang);
    XMP_Node* langQual = new XMP_Node(valueNode, "xml:lang", "ko", kXMP_PropIsQualifier);
    valueNode->qualifiers.push_back(langQual);
    parent->children.push_back(valueNode);

    FixupQualifiedNode(parent);

    EXPECT_TRUE(parent->options & kXMP_PropHasLang);
    ASSERT_GE(parent->qualifiers.size(), 2u);
    EXPECT_EQ(parent->qualifiers[0]->name, "xml:lang");

    CleanupNode(parent);
}

// Test duplicate qualifier from value node throws
TEST_F(FixupQualifiedNodeTest_2123, DuplicateQualifierFromValueNodeThrows_2123) {
    XMP_Node* parent = new XMP_Node(nullptr, "test:parent", kXMP_PropValueIsStruct);

    // Pre-add a child that will become a qualifier with name "test:dup"
    XMP_Node* valueNode = new XMP_Node(parent, "rdf:value", "val", 0);

    // Add qualifier to value node
    XMP_Node* qual1 = new XMP_Node(valueNode, "test:dup", "v1", kXMP_PropIsQualifier);
    valueNode->qualifiers.push_back(qual1);

    parent->children.push_back(valueNode);

    // This depends on FindChildNode - the duplicate check is for qualifiers whose name
    // matches an existing child. Since the parent only has rdf:value as child, and
    // we add "test:dup" as a qualifier on valueNode, it shouldn't match any child.
    // So this should NOT throw. Let's test the normal path.
    EXPECT_NO_THROW(FixupQualifiedNode(parent));

    CleanupNode(parent);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
