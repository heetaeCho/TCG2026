#include <gtest/gtest.h>
#include <string>
#include <vector>

// Include necessary headers
#include "XMPCore_Impl.hpp"

// We need to know the option bits for AltText arrays
// Typically: kXMP_PropArrayIsOrdered | kXMP_PropArrayIsAlternate | kXMP_PropArrayIsAltText
// From XMP SDK, these are usually:
// kXMP_PropValueIsArray = 0x00000200
// kXMP_PropArrayIsOrdered = 0x00000400
// kXMP_PropArrayIsAlternate = 0x00000800
// kXMP_PropArrayIsAltText = 0x00001000
// XMP_ArrayIsAltText checks for kXMP_PropArrayIsAltText bit

#ifndef kXMP_PropArrayIsAltText
#define kXMP_PropArrayIsAltText 0x00001000UL
#endif
#ifndef kXMP_PropArrayIsAlternate
#define kXMP_PropArrayIsAlternate 0x00000800UL
#endif
#ifndef kXMP_PropArrayIsOrdered
#define kXMP_PropArrayIsOrdered 0x00000400UL
#endif
#ifndef kXMP_PropValueIsArray
#define kXMP_PropValueIsArray 0x00000200UL
#endif

static const XMP_OptionBits kAltTextOptions =
    kXMP_PropValueIsArray | kXMP_PropArrayIsOrdered |
    kXMP_PropArrayIsAlternate | kXMP_PropArrayIsAltText;

// Forward declaration of the function under test
extern void NormalizeLangArray(XMP_Node* array);

// Helper to create a child node with xml:lang qualifier
static XMP_Node* MakeChildWithLang(XMP_Node* parent, const std::string& value, const std::string& lang) {
    XMP_Node* child = new XMP_Node(parent, "rdf:li", value.c_str(), 0);
    XMP_Node* qual = new XMP_Node(child, "xml:lang", lang.c_str(), 0);
    child->qualifiers.push_back(qual);
    parent->children.push_back(child);
    return child;
}

// Helper to create a child node without qualifiers
static XMP_Node* MakeChildWithoutQualifiers(XMP_Node* parent, const std::string& value) {
    XMP_Node* child = new XMP_Node(parent, "rdf:li", value.c_str(), 0);
    parent->children.push_back(child);
    return child;
}

// Helper to create a child with a wrong first qualifier name
static XMP_Node* MakeChildWithWrongQualifier(XMP_Node* parent, const std::string& value) {
    XMP_Node* child = new XMP_Node(parent, "rdf:li", value.c_str(), 0);
    XMP_Node* qual = new XMP_Node(child, "not-xml-lang", "en", 0);
    child->qualifiers.push_back(qual);
    parent->children.push_back(child);
    return child;
}

// Cleanup helper
static void CleanupArray(XMP_Node* array) {
    for (size_t i = 0; i < array->children.size(); ++i) {
        XMP_Node* child = array->children[i];
        for (size_t j = 0; j < child->qualifiers.size(); ++j) {
            delete child->qualifiers[j];
        }
        child->qualifiers.clear();
        delete child;
    }
    array->children.clear();
    delete array;
}

class NormalizeLangArrayTest_1904 : public ::testing::Test {
protected:
    void TearDown() override {
        // Cleanup handled per test
    }
};

// Test: Empty array - no children, should not throw
TEST_F(NormalizeLangArrayTest_1904, EmptyArray_1904) {
    XMP_Node* array = new XMP_Node(nullptr, "test:array", kAltTextOptions);
    EXPECT_NO_THROW(NormalizeLangArray(array));
    CleanupArray(array);
}

// Test: Single child with x-default lang - already at position 0
TEST_F(NormalizeLangArrayTest_1904, SingleChildXDefault_1904) {
    XMP_Node* array = new XMP_Node(nullptr, "test:array", kAltTextOptions);
    MakeChildWithLang(array, "default value", "x-default");

    EXPECT_NO_THROW(NormalizeLangArray(array));
    EXPECT_EQ(array->children[0]->qualifiers[0]->value, "x-default");
    EXPECT_EQ(array->children[0]->value, "default value");
    CleanupArray(array);
}

// Test: Single child with non-default lang - no swap needed
TEST_F(NormalizeLangArrayTest_1904, SingleChildNonDefault_1904) {
    XMP_Node* array = new XMP_Node(nullptr, "test:array", kAltTextOptions);
    MakeChildWithLang(array, "english value", "en");

    EXPECT_NO_THROW(NormalizeLangArray(array));
    EXPECT_EQ(array->children[0]->qualifiers[0]->value, "en");
    EXPECT_EQ(array->children[0]->value, "english value");
    CleanupArray(array);
}

// Test: x-default is at position 0, multiple children - no swap needed
TEST_F(NormalizeLangArrayTest_1904, XDefaultAlreadyFirst_1904) {
    XMP_Node* array = new XMP_Node(nullptr, "test:array", kAltTextOptions);
    MakeChildWithLang(array, "default value", "x-default");
    MakeChildWithLang(array, "english value", "en");
    MakeChildWithLang(array, "french value", "fr");

    EXPECT_NO_THROW(NormalizeLangArray(array));
    EXPECT_EQ(array->children[0]->qualifiers[0]->value, "x-default");
    EXPECT_EQ(array->children[0]->value, "default value");
    EXPECT_EQ(array->children[1]->qualifiers[0]->value, "en");
    EXPECT_EQ(array->children[2]->qualifiers[0]->value, "fr");
    CleanupArray(array);
}

// Test: x-default is at position 1 (second) - should be swapped to position 0
TEST_F(NormalizeLangArrayTest_1904, XDefaultAtSecondPosition_1904) {
    XMP_Node* array = new XMP_Node(nullptr, "test:array", kAltTextOptions);
    MakeChildWithLang(array, "english value", "en");
    MakeChildWithLang(array, "default value", "x-default");
    MakeChildWithLang(array, "french value", "fr");

    EXPECT_NO_THROW(NormalizeLangArray(array));
    EXPECT_EQ(array->children[0]->qualifiers[0]->value, "x-default");
    EXPECT_EQ(array->children[0]->value, "default value");
    EXPECT_EQ(array->children[1]->qualifiers[0]->value, "en");
    EXPECT_EQ(array->children[1]->value, "english value");
    EXPECT_EQ(array->children[2]->qualifiers[0]->value, "fr");
    CleanupArray(array);
}

// Test: x-default is at the last position - should be swapped to position 0
TEST_F(NormalizeLangArrayTest_1904, XDefaultAtLastPosition_1904) {
    XMP_Node* array = new XMP_Node(nullptr, "test:array", kAltTextOptions);
    MakeChildWithLang(array, "english value", "en");
    MakeChildWithLang(array, "french value", "fr");
    MakeChildWithLang(array, "german value", "de");
    MakeChildWithLang(array, "default value", "x-default");

    EXPECT_NO_THROW(NormalizeLangArray(array));
    EXPECT_EQ(array->children[0]->qualifiers[0]->value, "x-default");
    EXPECT_EQ(array->children[0]->value, "default value");
    // The previously first child should now be at the x-default's old position
    EXPECT_EQ(array->children[3]->qualifiers[0]->value, "en");
    EXPECT_EQ(array->children[3]->value, "english value");
    CleanupArray(array);
}

// Test: No x-default in the array - no swap should occur, order preserved
TEST_F(NormalizeLangArrayTest_1904, NoXDefault_1904) {
    XMP_Node* array = new XMP_Node(nullptr, "test:array", kAltTextOptions);
    MakeChildWithLang(array, "english value", "en");
    MakeChildWithLang(array, "french value", "fr");
    MakeChildWithLang(array, "german value", "de");

    EXPECT_NO_THROW(NormalizeLangArray(array));
    EXPECT_EQ(array->children[0]->qualifiers[0]->value, "en");
    EXPECT_EQ(array->children[1]->qualifiers[0]->value, "fr");
    EXPECT_EQ(array->children[2]->qualifiers[0]->value, "de");
    CleanupArray(array);
}

// Test: Child with empty qualifiers - should throw kXMPErr_BadXMP
TEST_F(NormalizeLangArrayTest_1904, ChildWithEmptyQualifiersThrows_1904) {
    XMP_Node* array = new XMP_Node(nullptr, "test:array", kAltTextOptions);
    MakeChildWithoutQualifiers(array, "bad value");

    try {
        NormalizeLangArray(array);
        FAIL() << "Expected XMP_Error to be thrown";
    } catch (const XMP_Error& e) {
        EXPECT_EQ(e.GetID(), kXMPErr_BadXMP);
    } catch (...) {
        FAIL() << "Expected XMP_Error but got different exception";
    }
    CleanupArray(array);
}

// Test: Child with wrong first qualifier name - should throw kXMPErr_BadXMP
TEST_F(NormalizeLangArrayTest_1904, ChildWithWrongQualifierNameThrows_1904) {
    XMP_Node* array = new XMP_Node(nullptr, "test:array", kAltTextOptions);
    MakeChildWithWrongQualifier(array, "bad value");

    try {
        NormalizeLangArray(array);
        FAIL() << "Expected XMP_Error to be thrown";
    } catch (const XMP_Error& e) {
        EXPECT_EQ(e.GetID(), kXMPErr_BadXMP);
    } catch (...) {
        FAIL() << "Expected XMP_Error but got different exception";
    }
    CleanupArray(array);
}

// Test: First child valid, second child missing qualifiers - should throw
TEST_F(NormalizeLangArrayTest_1904, SecondChildMissingQualifiersThrows_1904) {
    XMP_Node* array = new XMP_Node(nullptr, "test:array", kAltTextOptions);
    MakeChildWithLang(array, "good value", "en");
    MakeChildWithoutQualifiers(array, "bad value");

    try {
        NormalizeLangArray(array);
        FAIL() << "Expected XMP_Error to be thrown";
    } catch (const XMP_Error& e) {
        EXPECT_EQ(e.GetID(), kXMPErr_BadXMP);
    } catch (...) {
        FAIL() << "Expected XMP_Error but got different exception";
    }
    CleanupArray(array);
}

// Test: Two children, both with valid lang but no x-default - order preserved
TEST_F(NormalizeLangArrayTest_1904, TwoChildrenNoDefaultOrderPreserved_1904) {
    XMP_Node* array = new XMP_Node(nullptr, "test:array", kAltTextOptions);
    MakeChildWithLang(array, "english", "en");
    MakeChildWithLang(array, "french", "fr");

    EXPECT_NO_THROW(NormalizeLangArray(array));
    EXPECT_EQ(array->children.size(), 2u);
    EXPECT_EQ(array->children[0]->value, "english");
    EXPECT_EQ(array->children[1]->value, "french");
    CleanupArray(array);
}

// Test: x-default in the middle of many items - only default and first are swapped
TEST_F(NormalizeLangArrayTest_1904, XDefaultInMiddleSwapsCorrectly_1904) {
    XMP_Node* array = new XMP_Node(nullptr, "test:array", kAltTextOptions);
    MakeChildWithLang(array, "v0", "en");
    MakeChildWithLang(array, "v1", "fr");
    MakeChildWithLang(array, "v2", "x-default");
    MakeChildWithLang(array, "v3", "de");
    MakeChildWithLang(array, "v4", "ja");

    EXPECT_NO_THROW(NormalizeLangArray(array));
    // After normalization: x-default should be at 0, en should be at 2
    EXPECT_EQ(array->children[0]->qualifiers[0]->value, "x-default");
    EXPECT_EQ(array->children[0]->value, "v2");
    EXPECT_EQ(array->children[1]->qualifiers[0]->value, "fr");
    EXPECT_EQ(array->children[2]->qualifiers[0]->value, "en");
    EXPECT_EQ(array->children[2]->value, "v0");
    EXPECT_EQ(array->children[3]->qualifiers[0]->value, "de");
    EXPECT_EQ(array->children[4]->qualifiers[0]->value, "ja");
    EXPECT_EQ(array->children.size(), 5u);
    CleanupArray(array);
}

// Test: Bad child occurs before x-default - should throw before reaching default
TEST_F(NormalizeLangArrayTest_1904, BadChildBeforeDefaultThrows_1904) {
    XMP_Node* array = new XMP_Node(nullptr, "test:array", kAltTextOptions);
    MakeChildWithoutQualifiers(array, "bad");
    MakeChildWithLang(array, "default", "x-default");

    try {
        NormalizeLangArray(array);
        FAIL() << "Expected XMP_Error";
    } catch (const XMP_Error& e) {
        EXPECT_EQ(e.GetID(), kXMPErr_BadXMP);
    }
    CleanupArray(array);
}

// Test: Child with multiple qualifiers but first one is xml:lang - should be valid
TEST_F(NormalizeLangArrayTest_1904, MultipleQualifiersFirstIsLang_1904) {
    XMP_Node* array = new XMP_Node(nullptr, "test:array", kAltTextOptions);
    XMP_Node* child = new XMP_Node(array, "rdf:li", "value", 0);
    XMP_Node* qual1 = new XMP_Node(child, "xml:lang", "en", 0);
    XMP_Node* qual2 = new XMP_Node(child, "other:qual", "something", 0);
    child->qualifiers.push_back(qual1);
    child->qualifiers.push_back(qual2);
    array->children.push_back(child);

    EXPECT_NO_THROW(NormalizeLangArray(array));
    // Cleanup
    for (auto* q : child->qualifiers) delete q;
    child->qualifiers.clear();
    delete child;
    array->children.clear();
    delete array;
}

// Test: Child with multiple qualifiers but first one is NOT xml:lang - should throw
TEST_F(NormalizeLangArrayTest_1904, MultipleQualifiersFirstNotLang_1904) {
    XMP_Node* array = new XMP_Node(nullptr, "test:array", kAltTextOptions);
    XMP_Node* child = new XMP_Node(array, "rdf:li", "value", 0);
    XMP_Node* qual1 = new XMP_Node(child, "other:qual", "something", 0);
    XMP_Node* qual2 = new XMP_Node(child, "xml:lang", "en", 0);
    child->qualifiers.push_back(qual1);
    child->qualifiers.push_back(qual2);
    array->children.push_back(child);

    try {
        NormalizeLangArray(array);
        FAIL() << "Expected XMP_Error";
    } catch (const XMP_Error& e) {
        EXPECT_EQ(e.GetID(), kXMPErr_BadXMP);
    }
    // Cleanup
    for (auto* q : child->qualifiers) delete q;
    child->qualifiers.clear();
    delete child;
    array->children.clear();
    delete array;
}
