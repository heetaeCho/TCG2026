#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <cstring>

// We need the XMP types and node definitions
// Minimal type definitions to make the code compile
#ifndef XMP_Const_h
#define XMP_Const_h

typedef unsigned int XMP_OptionBits;
typedef const char* XMP_StringPtr;
typedef std::string XMP_VarString;

enum {
    kXMP_PropValueIsURI = 2,
    kXMP_PropHasQualifiers = 16,
    kXMP_PropIsQualifier = 32,
    kXMP_PropHasLang = 64,
    kXMP_PropHasType = 128,
    kXMP_PropValueIsStruct = 256,
    kXMP_PropValueIsArray = 512,
    kXMP_PropArrayIsUnordered = 512,
    kXMP_PropArrayIsOrdered = 1024,
    kXMP_PropArrayIsAlternate = 2048,
    kXMP_PropArrayIsAltText = 4096,
    kXMP_PropIsAlias = 65536,
    kXMP_PropHasAliases = 131072,
    kXMP_PropIsInternal = 262144,
    kXMP_PropIsStable = 1048576,
    kXMP_PropIsDerived = 2097152,
    kXMP_PropArrayFormMask = 7680,
    kXMP_PropCompositeMask = 7936,
    kXMP_ImplReservedMask = 1879048192
};

#endif

// Minimal XMP_Node class
typedef std::vector<void*> XMP_NodeOffspring_Base;

class XMP_Node {
public:
    XMP_OptionBits options;
    XMP_VarString name;
    XMP_VarString value;
    XMP_Node* parent;
    std::vector<XMP_Node*> children;
    std::vector<XMP_Node*> qualifiers;

    XMP_Node(XMP_Node* _parent, XMP_StringPtr _name, XMP_OptionBits _options)
        : options(_options), name(_name), parent(_parent) {}

    XMP_Node(XMP_Node* _parent, const XMP_VarString& _name, XMP_OptionBits _options)
        : options(_options), name(_name), parent(_parent) {}

    XMP_Node(XMP_Node* _parent, XMP_StringPtr _name, XMP_StringPtr _value, XMP_OptionBits _options)
        : options(_options), name(_name), value(_value), parent(_parent) {}

    XMP_Node(XMP_Node* _parent, const XMP_VarString& _name, const XMP_VarString& _value, XMP_OptionBits _options)
        : options(_options), name(_name), value(_value), parent(_parent) {}

    void RemoveChildren() { children.clear(); }
    void RemoveQualifiers() { qualifiers.clear(); }
    void ClearNode() { children.clear(); qualifiers.clear(); }
    virtual ~XMP_Node() {}
};

// FindConstChild is used by ItemValuesMatch - provide implementation
static const XMP_Node* FindConstChild(const XMP_Node* parent, XMP_StringPtr childName) {
    for (size_t i = 0; i < parent->children.size(); ++i) {
        if (parent->children[i]->name == childName) {
            return parent->children[i];
        }
    }
    return nullptr;
}

#ifndef XMP_Assert
#define XMP_Assert(c) ((void)0)
#endif

// Now define ItemValuesMatch as it appears in the source
static bool ItemValuesMatch(const XMP_Node* leftNode, const XMP_Node* rightNode) {
    const XMP_OptionBits leftForm = leftNode->options & kXMP_PropCompositeMask;
    const XMP_OptionBits rightForm = rightNode->options & kXMP_PropCompositeMask;

    if (leftForm != rightForm) return false;

    if (leftForm == 0) {
        // Simple property
        if (leftNode->value != rightNode->value) return false;
        if ((leftNode->options & kXMP_PropHasLang) != (rightNode->options & kXMP_PropHasLang)) return false;
        if (leftNode->options & kXMP_PropHasLang) {
            if (leftNode->qualifiers[0]->value != rightNode->qualifiers[0]->value) return false;
        }
    } else if (leftForm == kXMP_PropValueIsStruct) {
        // Struct
        if (leftNode->children.size() != rightNode->children.size()) return false;
        for (size_t leftNum = 0, leftLim = leftNode->children.size(); leftNum != leftLim; ++leftNum) {
            const XMP_Node* leftField = leftNode->children[leftNum];
            const XMP_Node* rightField = FindConstChild(rightNode, leftField->name.c_str());
            if ((rightField == 0) || (!ItemValuesMatch(leftField, rightField))) return false;
        }
    } else {
        // Array
        XMP_Assert(leftForm & kXMP_PropValueIsArray);
        for (size_t leftNum = 0, leftLim = leftNode->children.size(); leftNum != leftLim; ++leftNum) {
            const XMP_Node* leftItem = leftNode->children[leftNum];
            size_t rightNum, rightLim;
            for (rightNum = 0, rightLim = rightNode->children.size(); rightNum != rightLim; ++rightNum) {
                const XMP_Node* rightItem = rightNode->children[rightNum];
                if (ItemValuesMatch(leftItem, rightItem)) break;
            }
            if (rightNum == rightLim) return false;
        }
    }

    return true;
}

// Helper to create simple nodes quickly
class ItemValuesMatchTest_1922 : public ::testing::Test {
protected:
    std::vector<XMP_Node*> allocatedNodes;

    XMP_Node* makeNode(const std::string& name, const std::string& value, XMP_OptionBits options) {
        XMP_Node* node = new XMP_Node(nullptr, name.c_str(), value.c_str(), options);
        allocatedNodes.push_back(node);
        return node;
    }

    void TearDown() override {
        for (auto* n : allocatedNodes) {
            delete n;
        }
        allocatedNodes.clear();
    }
};

// --- Simple Value Tests ---

TEST_F(ItemValuesMatchTest_1922, SimpleValuesMatch_1922) {
    XMP_Node* left = makeNode("prop", "hello", 0);
    XMP_Node* right = makeNode("prop", "hello", 0);
    EXPECT_TRUE(ItemValuesMatch(left, right));
}

TEST_F(ItemValuesMatchTest_1922, SimpleValuesDiffer_1922) {
    XMP_Node* left = makeNode("prop", "hello", 0);
    XMP_Node* right = makeNode("prop", "world", 0);
    EXPECT_FALSE(ItemValuesMatch(left, right));
}

TEST_F(ItemValuesMatchTest_1922, SimpleValuesEmptyStrings_1922) {
    XMP_Node* left = makeNode("prop", "", 0);
    XMP_Node* right = makeNode("prop", "", 0);
    EXPECT_TRUE(ItemValuesMatch(left, right));
}

TEST_F(ItemValuesMatchTest_1922, SimpleValueOneEmptyOneFilled_1922) {
    XMP_Node* left = makeNode("prop", "", 0);
    XMP_Node* right = makeNode("prop", "value", 0);
    EXPECT_FALSE(ItemValuesMatch(left, right));
}

// --- Form Mismatch Tests ---

TEST_F(ItemValuesMatchTest_1922, DifferentFormsMismatch_1922) {
    XMP_Node* left = makeNode("prop", "hello", 0);
    XMP_Node* right = makeNode("prop", "hello", kXMP_PropValueIsStruct);
    EXPECT_FALSE(ItemValuesMatch(left, right));
}

TEST_F(ItemValuesMatchTest_1922, SimpleVsArrayMismatch_1922) {
    XMP_Node* left = makeNode("prop", "hello", 0);
    XMP_Node* right = makeNode("prop", "hello", kXMP_PropValueIsArray);
    EXPECT_FALSE(ItemValuesMatch(left, right));
}

TEST_F(ItemValuesMatchTest_1922, StructVsArrayMismatch_1922) {
    XMP_Node* left = makeNode("prop", "", kXMP_PropValueIsStruct);
    XMP_Node* right = makeNode("prop", "", kXMP_PropValueIsArray);
    EXPECT_FALSE(ItemValuesMatch(left, right));
}

// --- Language Qualifier Tests ---

TEST_F(ItemValuesMatchTest_1922, SimpleWithMatchingLang_1922) {
    XMP_Node* left = makeNode("prop", "hello", kXMP_PropHasLang);
    XMP_Node* right = makeNode("prop", "hello", kXMP_PropHasLang);

    XMP_Node* leftLang = makeNode("xml:lang", "en-US", 0);
    XMP_Node* rightLang = makeNode("xml:lang", "en-US", 0);

    left->qualifiers.push_back(leftLang);
    right->qualifiers.push_back(rightLang);

    EXPECT_TRUE(ItemValuesMatch(left, right));
}

TEST_F(ItemValuesMatchTest_1922, SimpleWithDifferentLang_1922) {
    XMP_Node* left = makeNode("prop", "hello", kXMP_PropHasLang);
    XMP_Node* right = makeNode("prop", "hello", kXMP_PropHasLang);

    XMP_Node* leftLang = makeNode("xml:lang", "en-US", 0);
    XMP_Node* rightLang = makeNode("xml:lang", "fr-FR", 0);

    left->qualifiers.push_back(leftLang);
    right->qualifiers.push_back(rightLang);

    EXPECT_FALSE(ItemValuesMatch(left, right));
}

TEST_F(ItemValuesMatchTest_1922, SimpleOnlyOneHasLang_1922) {
    XMP_Node* left = makeNode("prop", "hello", kXMP_PropHasLang);
    XMP_Node* right = makeNode("prop", "hello", 0);

    XMP_Node* leftLang = makeNode("xml:lang", "en-US", 0);
    left->qualifiers.push_back(leftLang);

    EXPECT_FALSE(ItemValuesMatch(left, right));
}

TEST_F(ItemValuesMatchTest_1922, SimpleNoLangOnEither_1922) {
    XMP_Node* left = makeNode("prop", "value", 0);
    XMP_Node* right = makeNode("prop", "value", 0);
    EXPECT_TRUE(ItemValuesMatch(left, right));
}

// --- Struct Tests ---

TEST_F(ItemValuesMatchTest_1922, StructsWithMatchingChildren_1922) {
    XMP_Node* left = makeNode("struct", "", kXMP_PropValueIsStruct);
    XMP_Node* right = makeNode("struct", "", kXMP_PropValueIsStruct);

    XMP_Node* leftChild1 = makeNode("field1", "val1", 0);
    XMP_Node* leftChild2 = makeNode("field2", "val2", 0);
    XMP_Node* rightChild1 = makeNode("field1", "val1", 0);
    XMP_Node* rightChild2 = makeNode("field2", "val2", 0);

    left->children.push_back(leftChild1);
    left->children.push_back(leftChild2);
    right->children.push_back(rightChild1);
    right->children.push_back(rightChild2);

    EXPECT_TRUE(ItemValuesMatch(left, right));
}

TEST_F(ItemValuesMatchTest_1922, StructsDifferentChildCount_1922) {
    XMP_Node* left = makeNode("struct", "", kXMP_PropValueIsStruct);
    XMP_Node* right = makeNode("struct", "", kXMP_PropValueIsStruct);

    XMP_Node* leftChild1 = makeNode("field1", "val1", 0);
    XMP_Node* leftChild2 = makeNode("field2", "val2", 0);
    XMP_Node* rightChild1 = makeNode("field1", "val1", 0);

    left->children.push_back(leftChild1);
    left->children.push_back(leftChild2);
    right->children.push_back(rightChild1);

    EXPECT_FALSE(ItemValuesMatch(left, right));
}

TEST_F(ItemValuesMatchTest_1922, StructsChildNotFoundInRight_1922) {
    XMP_Node* left = makeNode("struct", "", kXMP_PropValueIsStruct);
    XMP_Node* right = makeNode("struct", "", kXMP_PropValueIsStruct);

    XMP_Node* leftChild = makeNode("field1", "val1", 0);
    XMP_Node* rightChild = makeNode("field2", "val1", 0);

    left->children.push_back(leftChild);
    right->children.push_back(rightChild);

    EXPECT_FALSE(ItemValuesMatch(left, right));
}

TEST_F(ItemValuesMatchTest_1922, StructsChildValueMismatch_1922) {
    XMP_Node* left = makeNode("struct", "", kXMP_PropValueIsStruct);
    XMP_Node* right = makeNode("struct", "", kXMP_PropValueIsStruct);

    XMP_Node* leftChild = makeNode("field1", "val1", 0);
    XMP_Node* rightChild = makeNode("field1", "val2", 0);

    left->children.push_back(leftChild);
    right->children.push_back(rightChild);

    EXPECT_FALSE(ItemValuesMatch(left, right));
}

TEST_F(ItemValuesMatchTest_1922, EmptyStructsMatch_1922) {
    XMP_Node* left = makeNode("struct", "", kXMP_PropValueIsStruct);
    XMP_Node* right = makeNode("struct", "", kXMP_PropValueIsStruct);

    EXPECT_TRUE(ItemValuesMatch(left, right));
}

TEST_F(ItemValuesMatchTest_1922, StructsChildrenDifferentOrder_1922) {
    XMP_Node* left = makeNode("struct", "", kXMP_PropValueIsStruct);
    XMP_Node* right = makeNode("struct", "", kXMP_PropValueIsStruct);

    XMP_Node* leftChild1 = makeNode("field1", "val1", 0);
    XMP_Node* leftChild2 = makeNode("field2", "val2", 0);
    XMP_Node* rightChild1 = makeNode("field2", "val2", 0);
    XMP_Node* rightChild2 = makeNode("field1", "val1", 0);

    left->children.push_back(leftChild1);
    left->children.push_back(leftChild2);
    right->children.push_back(rightChild1);
    right->children.push_back(rightChild2);

    // Struct lookup is by name, so order shouldn't matter
    EXPECT_TRUE(ItemValuesMatch(left, right));
}

// --- Array Tests ---

TEST_F(ItemValuesMatchTest_1922, ArraysWithMatchingItems_1922) {
    XMP_Node* left = makeNode("arr", "", kXMP_PropValueIsArray);
    XMP_Node* right = makeNode("arr", "", kXMP_PropValueIsArray);

    XMP_Node* leftItem1 = makeNode("[1]", "a", 0);
    XMP_Node* leftItem2 = makeNode("[2]", "b", 0);
    XMP_Node* rightItem1 = makeNode("[1]", "a", 0);
    XMP_Node* rightItem2 = makeNode("[2]", "b", 0);

    left->children.push_back(leftItem1);
    left->children.push_back(leftItem2);
    right->children.push_back(rightItem1);
    right->children.push_back(rightItem2);

    EXPECT_TRUE(ItemValuesMatch(left, right));
}

TEST_F(ItemValuesMatchTest_1922, ArraysWithDifferentOrder_1922) {
    XMP_Node* left = makeNode("arr", "", kXMP_PropValueIsArray);
    XMP_Node* right = makeNode("arr", "", kXMP_PropValueIsArray);

    XMP_Node* leftItem1 = makeNode("[1]", "a", 0);
    XMP_Node* leftItem2 = makeNode("[2]", "b", 0);
    XMP_Node* rightItem1 = makeNode("[1]", "b", 0);
    XMP_Node* rightItem2 = makeNode("[2]", "a", 0);

    left->children.push_back(leftItem1);
    left->children.push_back(leftItem2);
    right->children.push_back(rightItem1);
    right->children.push_back(rightItem2);

    // Array matching is by value, not position — each left item must find a match in right
    EXPECT_TRUE(ItemValuesMatch(left, right));
}

TEST_F(ItemValuesMatchTest_1922, ArraysLeftItemNotInRight_1922) {
    XMP_Node* left = makeNode("arr", "", kXMP_PropValueIsArray);
    XMP_Node* right = makeNode("arr", "", kXMP_PropValueIsArray);

    XMP_Node* leftItem1 = makeNode("[1]", "a", 0);
    XMP_Node* leftItem2 = makeNode("[2]", "c", 0);
    XMP_Node* rightItem1 = makeNode("[1]", "a", 0);
    XMP_Node* rightItem2 = makeNode("[2]", "b", 0);

    left->children.push_back(leftItem1);
    left->children.push_back(leftItem2);
    right->children.push_back(rightItem1);
    right->children.push_back(rightItem2);

    EXPECT_FALSE(ItemValuesMatch(left, right));
}

TEST_F(ItemValuesMatchTest_1922, EmptyArraysMatch_1922) {
    XMP_Node* left = makeNode("arr", "", kXMP_PropValueIsArray);
    XMP_Node* right = makeNode("arr", "", kXMP_PropValueIsArray);

    EXPECT_TRUE(ItemValuesMatch(left, right));
}

TEST_F(ItemValuesMatchTest_1922, ArrayLeftEmptyRightNot_1922) {
    XMP_Node* left = makeNode("arr", "", kXMP_PropValueIsArray);
    XMP_Node* right = makeNode("arr", "", kXMP_PropValueIsArray);

    XMP_Node* rightItem = makeNode("[1]", "a", 0);
    right->children.push_back(rightItem);

    // Left has no items, so all (zero) items match. Should return true.
    EXPECT_TRUE(ItemValuesMatch(left, right));
}

TEST_F(ItemValuesMatchTest_1922, ArrayLeftHasItemsRightEmpty_1922) {
    XMP_Node* left = makeNode("arr", "", kXMP_PropValueIsArray);
    XMP_Node* right = makeNode("arr", "", kXMP_PropValueIsArray);

    XMP_Node* leftItem = makeNode("[1]", "a", 0);
    left->children.push_back(leftItem);

    // Left has item but right is empty - no match possible
    EXPECT_FALSE(ItemValuesMatch(left, right));
}

// --- Nested Struct Tests ---

TEST_F(ItemValuesMatchTest_1922, NestedStructsMatch_1922) {
    XMP_Node* left = makeNode("struct", "", kXMP_PropValueIsStruct);
    XMP_Node* right = makeNode("struct", "", kXMP_PropValueIsStruct);

    XMP_Node* leftInner = makeNode("inner", "", kXMP_PropValueIsStruct);
    XMP_Node* rightInner = makeNode("inner", "", kXMP_PropValueIsStruct);

    XMP_Node* leftLeaf = makeNode("leaf", "data", 0);
    XMP_Node* rightLeaf = makeNode("leaf", "data", 0);

    leftInner->children.push_back(leftLeaf);
    rightInner->children.push_back(rightLeaf);

    left->children.push_back(leftInner);
    right->children.push_back(rightInner);

    EXPECT_TRUE(ItemValuesMatch(left, right));
}

TEST_F(ItemValuesMatchTest_1922, NestedStructsMismatchAtLeaf_1922) {
    XMP_Node* left = makeNode("struct", "", kXMP_PropValueIsStruct);
    XMP_Node* right = makeNode("struct", "", kXMP_PropValueIsStruct);

    XMP_Node* leftInner = makeNode("inner", "", kXMP_PropValueIsStruct);
    XMP_Node* rightInner = makeNode("inner", "", kXMP_PropValueIsStruct);

    XMP_Node* leftLeaf = makeNode("leaf", "data1", 0);
    XMP_Node* rightLeaf = makeNode("leaf", "data2", 0);

    leftInner->children.push_back(leftLeaf);
    rightInner->children.push_back(rightLeaf);

    left->children.push_back(leftInner);
    right->children.push_back(rightInner);

    EXPECT_FALSE(ItemValuesMatch(left, right));
}

// --- Ordered Array Tests ---

TEST_F(ItemValuesMatchTest_1922, OrderedArraysMatch_1922) {
    XMP_Node* left = makeNode("arr", "", kXMP_PropArrayIsOrdered);
    XMP_Node* right = makeNode("arr", "", kXMP_PropArrayIsOrdered);

    XMP_Node* leftItem1 = makeNode("[1]", "x", 0);
    XMP_Node* rightItem1 = makeNode("[1]", "x", 0);

    left->children.push_back(leftItem1);
    right->children.push_back(rightItem1);

    EXPECT_TRUE(ItemValuesMatch(left, right));
}

// --- Array of structs ---

TEST_F(ItemValuesMatchTest_1922, ArrayOfStructsMatch_1922) {
    XMP_Node* left = makeNode("arr", "", kXMP_PropValueIsArray);
    XMP_Node* right = makeNode("arr", "", kXMP_PropValueIsArray);

    XMP_Node* leftStruct = makeNode("[1]", "", kXMP_PropValueIsStruct);
    XMP_Node* rightStruct = makeNode("[1]", "", kXMP_PropValueIsStruct);

    XMP_Node* leftField = makeNode("name", "John", 0);
    XMP_Node* rightField = makeNode("name", "John", 0);

    leftStruct->children.push_back(leftField);
    rightStruct->children.push_back(rightField);

    left->children.push_back(leftStruct);
    right->children.push_back(rightStruct);

    EXPECT_TRUE(ItemValuesMatch(left, right));
}

TEST_F(ItemValuesMatchTest_1922, ArrayOfStructsMismatch_1922) {
    XMP_Node* left = makeNode("arr", "", kXMP_PropValueIsArray);
    XMP_Node* right = makeNode("arr", "", kXMP_PropValueIsArray);

    XMP_Node* leftStruct = makeNode("[1]", "", kXMP_PropValueIsStruct);
    XMP_Node* rightStruct = makeNode("[1]", "", kXMP_PropValueIsStruct);

    XMP_Node* leftField = makeNode("name", "John", 0);
    XMP_Node* rightField = makeNode("name", "Jane", 0);

    leftStruct->children.push_back(leftField);
    rightStruct->children.push_back(rightField);

    left->children.push_back(leftStruct);
    right->children.push_back(rightStruct);

    EXPECT_FALSE(ItemValuesMatch(left, right));
}

// --- Composite mask filtering ---

TEST_F(ItemValuesMatchTest_1922, NonCompositeOptionBitsIgnored_1922) {
    // Options that don't affect composite mask should not cause form mismatch
    XMP_Node* left = makeNode("prop", "hello", kXMP_PropValueIsURI);
    XMP_Node* right = makeNode("prop", "hello", 0);

    // kXMP_PropValueIsURI (2) is not in kXMP_PropCompositeMask (7936)
    // So both have form == 0 and values match
    EXPECT_TRUE(ItemValuesMatch(left, right));
}

TEST_F(ItemValuesMatchTest_1922, NonCompositeOptionsDifferButValuesMatch_1922) {
    XMP_Node* left = makeNode("prop", "test", kXMP_PropIsInternal);
    XMP_Node* right = makeNode("prop", "test", kXMP_PropIsStable);

    // Neither kXMP_PropIsInternal nor kXMP_PropIsStable is in composite mask
    EXPECT_TRUE(ItemValuesMatch(left, right));
}

// --- Same names different values in struct ---

TEST_F(ItemValuesMatchTest_1922, StructSameNamesDifferentValues_1922) {
    XMP_Node* left = makeNode("struct", "", kXMP_PropValueIsStruct);
    XMP_Node* right = makeNode("struct", "", kXMP_PropValueIsStruct);

    XMP_Node* leftChild = makeNode("field", "alpha", 0);
    XMP_Node* rightChild = makeNode("field", "beta", 0);

    left->children.push_back(leftChild);
    right->children.push_back(rightChild);

    EXPECT_FALSE(ItemValuesMatch(left, right));
}

// --- Single item array ---

TEST_F(ItemValuesMatchTest_1922, SingleItemArrayMatch_1922) {
    XMP_Node* left = makeNode("arr", "", kXMP_PropValueIsArray);
    XMP_Node* right = makeNode("arr", "", kXMP_PropValueIsArray);

    XMP_Node* leftItem = makeNode("[1]", "only", 0);
    XMP_Node* rightItem = makeNode("[1]", "only", 0);

    left->children.push_back(leftItem);
    right->children.push_back(rightItem);

    EXPECT_TRUE(ItemValuesMatch(left, right));
}

TEST_F(ItemValuesMatchTest_1922, SingleItemArrayMismatch_1922) {
    XMP_Node* left = makeNode("arr", "", kXMP_PropValueIsArray);
    XMP_Node* right = makeNode("arr", "", kXMP_PropValueIsArray);

    XMP_Node* leftItem = makeNode("[1]", "one", 0);
    XMP_Node* rightItem = makeNode("[1]", "two", 0);

    left->children.push_back(leftItem);
    right->children.push_back(rightItem);

    EXPECT_FALSE(ItemValuesMatch(left, right));
}

// --- Alternate array ---

TEST_F(ItemValuesMatchTest_1922, AlternateArrayMatch_1922) {
    XMP_OptionBits altOpts = kXMP_PropArrayIsAlternate;
    XMP_Node* left = makeNode("arr", "", altOpts);
    XMP_Node* right = makeNode("arr", "", altOpts);

    XMP_Node* leftItem = makeNode("[1]", "alt", 0);
    XMP_Node* rightItem = makeNode("[1]", "alt", 0);

    left->children.push_back(leftItem);
    right->children.push_back(rightItem);

    EXPECT_TRUE(ItemValuesMatch(left, right));
}

// --- Multiple items in array with duplicates ---

TEST_F(ItemValuesMatchTest_1922, ArrayDuplicateItemsMatch_1922) {
    XMP_Node* left = makeNode("arr", "", kXMP_PropValueIsArray);
    XMP_Node* right = makeNode("arr", "", kXMP_PropValueIsArray);

    XMP_Node* leftItem1 = makeNode("[1]", "a", 0);
    XMP_Node* leftItem2 = makeNode("[2]", "a", 0);
    XMP_Node* rightItem1 = makeNode("[1]", "a", 0);

    left->children.push_back(leftItem1);
    left->children.push_back(leftItem2);
    right->children.push_back(rightItem1);

    // Both left items match rightItem1, so this should succeed
    EXPECT_TRUE(ItemValuesMatch(left, right));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
