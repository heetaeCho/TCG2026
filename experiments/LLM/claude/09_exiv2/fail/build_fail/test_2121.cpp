#include <gtest/gtest.h>
#include <string>
#include <vector>

// Include necessary headers
#include "XMP_Const.h"
#include "XMPCore_Impl.hpp"

// We need to declare the function under test since it's static in ParseRDF.cpp
// We'll include it or re-declare it. Since it's a static function in a .cpp file,
// we need to include the source to test it, or use a workaround.

// For testing purposes, we include the relevant definitions and re-create the function
// signature. Since the function is static in ParseRDF.cpp, we need to include that file
// or extract the function. We'll define a test-accessible version.

// Include the source file to get access to the static function
// This is a common technique for testing static/file-scope functions
#include "ParseRDF.cpp"

class AddQualifierNodeTest_2121 : public ::testing::Test {
protected:
    void SetUp() override {
        parent = new XMP_Node(nullptr, "testParent", 0);
    }

    void TearDown() override {
        // Clean up qualifiers
        for (size_t i = 0; i < parent->qualifiers.size(); ++i) {
            delete parent->qualifiers[i];
        }
        parent->qualifiers.clear();
        delete parent;
    }

    XMP_Node* parent;
};

// Test: Adding a regular qualifier (not xml:lang, not rdf:type) appends to the end
TEST_F(AddQualifierNodeTest_2121, RegularQualifierAppendsToEnd_2121) {
    XMP_Node* result = AddQualifierNode(parent, "custom:qualifier", "value1");

    ASSERT_NE(result, nullptr);
    ASSERT_EQ(parent->qualifiers.size(), 1u);
    EXPECT_EQ(parent->qualifiers[0], result);
    EXPECT_EQ(result->name, "custom:qualifier");
    EXPECT_EQ(result->value, "value1");
    EXPECT_TRUE(result->options & kXMP_PropIsQualifier);
    EXPECT_TRUE(parent->options & kXMP_PropHasQualifiers);
}

// Test: Adding xml:lang qualifier to empty qualifiers list
TEST_F(AddQualifierNodeTest_2121, LangQualifierToEmptyList_2121) {
    XMP_Node* result = AddQualifierNode(parent, "xml:lang", "en");

    ASSERT_NE(result, nullptr);
    ASSERT_EQ(parent->qualifiers.size(), 1u);
    EXPECT_EQ(parent->qualifiers[0], result);
    EXPECT_EQ(result->name, "xml:lang");
    EXPECT_EQ(result->value, "en");
    EXPECT_TRUE(parent->options & kXMP_PropHasLang);
    EXPECT_TRUE(parent->options & kXMP_PropHasQualifiers);
}

// Test: Adding xml:lang qualifier inserts at beginning when list is non-empty
TEST_F(AddQualifierNodeTest_2121, LangQualifierInsertsAtBeginning_2121) {
    // First add a regular qualifier
    XMP_Node* regular = AddQualifierNode(parent, "custom:qual", "val");
    // Now add xml:lang
    XMP_Node* lang = AddQualifierNode(parent, "xml:lang", "fr");

    ASSERT_EQ(parent->qualifiers.size(), 2u);
    EXPECT_EQ(parent->qualifiers[0], lang);
    EXPECT_EQ(parent->qualifiers[1], regular);
    EXPECT_TRUE(parent->options & kXMP_PropHasLang);
}

// Test: Adding rdf:type qualifier to empty list
TEST_F(AddQualifierNodeTest_2121, TypeQualifierToEmptyList_2121) {
    XMP_Node* result = AddQualifierNode(parent, "rdf:type", "SomeType");

    ASSERT_NE(result, nullptr);
    ASSERT_EQ(parent->qualifiers.size(), 1u);
    EXPECT_EQ(parent->qualifiers[0], result);
    EXPECT_EQ(result->name, "rdf:type");
    EXPECT_EQ(result->value, "SomeType");
    EXPECT_TRUE(parent->options & kXMP_PropHasType);
    EXPECT_TRUE(parent->options & kXMP_PropHasQualifiers);
}

// Test: Adding rdf:type when xml:lang already exists - type goes after lang
TEST_F(AddQualifierNodeTest_2121, TypeQualifierAfterLang_2121) {
    XMP_Node* lang = AddQualifierNode(parent, "xml:lang", "en");
    XMP_Node* regular = AddQualifierNode(parent, "custom:qual", "val");
    XMP_Node* type = AddQualifierNode(parent, "rdf:type", "SomeType");

    ASSERT_EQ(parent->qualifiers.size(), 3u);
    EXPECT_EQ(parent->qualifiers[0], lang);
    EXPECT_EQ(parent->qualifiers[1], type);
    EXPECT_EQ(parent->qualifiers[2], regular);
}

// Test: Adding rdf:type when no xml:lang exists - type goes at beginning
TEST_F(AddQualifierNodeTest_2121, TypeQualifierAtBeginningWhenNoLang_2121) {
    XMP_Node* regular = AddQualifierNode(parent, "custom:qual", "val");
    XMP_Node* type = AddQualifierNode(parent, "rdf:type", "SomeType");

    ASSERT_EQ(parent->qualifiers.size(), 2u);
    EXPECT_EQ(parent->qualifiers[0], type);
    EXPECT_EQ(parent->qualifiers[1], regular);
}

// Test: Multiple regular qualifiers are appended in order
TEST_F(AddQualifierNodeTest_2121, MultipleRegularQualifiersAppendInOrder_2121) {
    XMP_Node* q1 = AddQualifierNode(parent, "ns:q1", "v1");
    XMP_Node* q2 = AddQualifierNode(parent, "ns:q2", "v2");
    XMP_Node* q3 = AddQualifierNode(parent, "ns:q3", "v3");

    ASSERT_EQ(parent->qualifiers.size(), 3u);
    EXPECT_EQ(parent->qualifiers[0], q1);
    EXPECT_EQ(parent->qualifiers[1], q2);
    EXPECT_EQ(parent->qualifiers[2], q3);
}

// Test: Verify kXMP_PropHasQualifiers is set on parent options
TEST_F(AddQualifierNodeTest_2121, HasQualifiersFlagIsSet_2121) {
    EXPECT_FALSE(parent->options & kXMP_PropHasQualifiers);
    AddQualifierNode(parent, "ns:q1", "v1");
    EXPECT_TRUE(parent->options & kXMP_PropHasQualifiers);
}

// Test: Verify kXMP_PropIsQualifier is set on the new node
TEST_F(AddQualifierNodeTest_2121, IsQualifierFlagOnNewNode_2121) {
    XMP_Node* result = AddQualifierNode(parent, "ns:q1", "v1");
    EXPECT_TRUE(result->options & kXMP_PropIsQualifier);
}

// Test: kXMP_PropHasLang flag is set when adding xml:lang
TEST_F(AddQualifierNodeTest_2121, HasLangFlagSet_2121) {
    EXPECT_FALSE(parent->options & kXMP_PropHasLang);
    AddQualifierNode(parent, "xml:lang", "en");
    EXPECT_TRUE(parent->options & kXMP_PropHasLang);
}

// Test: kXMP_PropHasType flag is set when adding rdf:type
TEST_F(AddQualifierNodeTest_2121, HasTypeFlagSet_2121) {
    EXPECT_FALSE(parent->options & kXMP_PropHasType);
    AddQualifierNode(parent, "rdf:type", "SomeType");
    EXPECT_TRUE(parent->options & kXMP_PropHasType);
}

// Test: Regular qualifier does NOT set kXMP_PropHasLang or kXMP_PropHasType
TEST_F(AddQualifierNodeTest_2121, RegularQualifierDoesNotSetLangOrTypeFlags_2121) {
    AddQualifierNode(parent, "custom:qual", "val");
    EXPECT_FALSE(parent->options & kXMP_PropHasLang);
    EXPECT_FALSE(parent->options & kXMP_PropHasType);
}

// Test: New qualifier node has correct parent
TEST_F(AddQualifierNodeTest_2121, NewNodeHasCorrectParent_2121) {
    XMP_Node* result = AddQualifierNode(parent, "ns:q1", "v1");
    EXPECT_EQ(result->parent, parent);
}

// Test: Adding qualifier with empty value
TEST_F(AddQualifierNodeTest_2121, EmptyValueQualifier_2121) {
    XMP_Node* result = AddQualifierNode(parent, "ns:q1", "");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->value, "");
    EXPECT_EQ(result->name, "ns:q1");
}

// Test: Full ordering: xml:lang first, rdf:type second, then regulars
TEST_F(AddQualifierNodeTest_2121, FullOrderingLangTypeRegular_2121) {
    XMP_Node* r1 = AddQualifierNode(parent, "ns:r1", "v1");
    XMP_Node* r2 = AddQualifierNode(parent, "ns:r2", "v2");
    XMP_Node* type = AddQualifierNode(parent, "rdf:type", "T");
    XMP_Node* lang = AddQualifierNode(parent, "xml:lang", "en");

    ASSERT_EQ(parent->qualifiers.size(), 4u);
    EXPECT_EQ(parent->qualifiers[0], lang);
    EXPECT_EQ(parent->qualifiers[1], type);
    EXPECT_EQ(parent->qualifiers[2], r1);
    EXPECT_EQ(parent->qualifiers[3], r2);
}

// Test: Adding rdf:type when there are qualifiers but no lang - offset should be 0
TEST_F(AddQualifierNodeTest_2121, TypeQualifierNoLangOffset_2121) {
    XMP_Node* r1 = AddQualifierNode(parent, "ns:r1", "v1");
    XMP_Node* r2 = AddQualifierNode(parent, "ns:r2", "v2");

    // No lang flag set, so offset should be 0 and type goes to front
    XMP_Node* type = AddQualifierNode(parent, "rdf:type", "T");

    ASSERT_EQ(parent->qualifiers.size(), 3u);
    EXPECT_EQ(parent->qualifiers[0], type);
    EXPECT_EQ(parent->qualifiers[1], r1);
    EXPECT_EQ(parent->qualifiers[2], r2);
}

// Test: Return value is the newly created node
TEST_F(AddQualifierNodeTest_2121, ReturnValueIsNewNode_2121) {
    XMP_Node* result = AddQualifierNode(parent, "ns:test", "testval");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->name, "ns:test");
    EXPECT_EQ(result->value, "testval");
}

// Test: Parent with pre-existing options retains them
TEST_F(AddQualifierNodeTest_2121, PreExistingOptionsRetained_2121) {
    parent->options = kXMP_PropValueIsStruct;
    AddQualifierNode(parent, "ns:q1", "v1");
    EXPECT_TRUE(parent->options & kXMP_PropValueIsStruct);
    EXPECT_TRUE(parent->options & kXMP_PropHasQualifiers);
}

// Test: Adding lang then type then regular gives correct ordering
TEST_F(AddQualifierNodeTest_2121, LangThenTypeThenRegularOrdering_2121) {
    XMP_Node* lang = AddQualifierNode(parent, "xml:lang", "en");
    XMP_Node* type = AddQualifierNode(parent, "rdf:type", "T");
    XMP_Node* reg = AddQualifierNode(parent, "ns:reg", "v");

    ASSERT_EQ(parent->qualifiers.size(), 3u);
    EXPECT_EQ(parent->qualifiers[0], lang);
    EXPECT_EQ(parent->qualifiers[1], type);
    EXPECT_EQ(parent->qualifiers[2], reg);
}
