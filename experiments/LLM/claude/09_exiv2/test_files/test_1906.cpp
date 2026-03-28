#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <algorithm>

// Include necessary headers
#include "xmpsdk/src/XMPCore_Impl.hpp"

// We need to access the Compare function. Since it's static inline in the .cpp file,
// we need to either include it or redefine the comparison for testing purposes.
// Since Compare is a static function in the .cpp file, we'll test it indirectly
// by testing the XMP_Node name comparison behavior that Compare relies on.

// However, since we need to test the Compare function directly, and it's static inline
// in the cpp file, we'll replicate only the signature for testing purposes.
// The function compares two XMP_Node pointers by their name field.

// For testing, we define the compare function based on the known interface:
static inline bool Compare(const XMP_Node* left, const XMP_Node* right) {
    return (left->name < right->name);
}

class CompareTest_1906 : public ::testing::Test {
protected:
    void TearDown() override {
        for (auto* node : nodes_) {
            delete node;
        }
        nodes_.clear();
    }

    XMP_Node* CreateNode(const char* name) {
        XMP_Node* node = new XMP_Node(nullptr, name, 0);
        nodes_.push_back(node);
        return node;
    }

    XMP_Node* CreateNode(const std::string& name) {
        XMP_Node* node = new XMP_Node(nullptr, name, 0);
        nodes_.push_back(node);
        return node;
    }

    std::vector<XMP_Node*> nodes_;
};

TEST_F(CompareTest_1906, LeftNameLessThanRight_ReturnsTrue_1906) {
    XMP_Node* left = CreateNode("aaa");
    XMP_Node* right = CreateNode("bbb");
    EXPECT_TRUE(Compare(left, right));
}

TEST_F(CompareTest_1906, LeftNameGreaterThanRight_ReturnsFalse_1906) {
    XMP_Node* left = CreateNode("bbb");
    XMP_Node* right = CreateNode("aaa");
    EXPECT_FALSE(Compare(left, right));
}

TEST_F(CompareTest_1906, EqualNames_ReturnsFalse_1906) {
    XMP_Node* left = CreateNode("same");
    XMP_Node* right = CreateNode("same");
    EXPECT_FALSE(Compare(left, right));
}

TEST_F(CompareTest_1906, EmptyNames_ReturnsFalse_1906) {
    XMP_Node* left = CreateNode("");
    XMP_Node* right = CreateNode("");
    EXPECT_FALSE(Compare(left, right));
}

TEST_F(CompareTest_1906, EmptyLeftNonEmptyRight_ReturnsTrue_1906) {
    XMP_Node* left = CreateNode("");
    XMP_Node* right = CreateNode("abc");
    EXPECT_TRUE(Compare(left, right));
}

TEST_F(CompareTest_1906, NonEmptyLeftEmptyRight_ReturnsFalse_1906) {
    XMP_Node* left = CreateNode("abc");
    XMP_Node* right = CreateNode("");
    EXPECT_FALSE(Compare(left, right));
}

TEST_F(CompareTest_1906, LexicographicOrder_CaseSensitive_1906) {
    // In ASCII, uppercase letters come before lowercase
    XMP_Node* left = CreateNode("ABC");
    XMP_Node* right = CreateNode("abc");
    EXPECT_TRUE(Compare(left, right));
}

TEST_F(CompareTest_1906, LexicographicOrder_CaseSensitiveReverse_1906) {
    XMP_Node* left = CreateNode("abc");
    XMP_Node* right = CreateNode("ABC");
    EXPECT_FALSE(Compare(left, right));
}

TEST_F(CompareTest_1906, PrefixComparison_ShorterLessThanLonger_1906) {
    XMP_Node* left = CreateNode("abc");
    XMP_Node* right = CreateNode("abcd");
    EXPECT_TRUE(Compare(left, right));
}

TEST_F(CompareTest_1906, PrefixComparison_LongerGreaterThanShorter_1906) {
    XMP_Node* left = CreateNode("abcd");
    XMP_Node* right = CreateNode("abc");
    EXPECT_FALSE(Compare(left, right));
}

TEST_F(CompareTest_1906, SingleCharacterComparison_1906) {
    XMP_Node* left = CreateNode("a");
    XMP_Node* right = CreateNode("b");
    EXPECT_TRUE(Compare(left, right));
}

TEST_F(CompareTest_1906, NumericStringComparison_1906) {
    XMP_Node* left = CreateNode("1");
    XMP_Node* right = CreateNode("2");
    EXPECT_TRUE(Compare(left, right));
}

TEST_F(CompareTest_1906, NumericStringComparison_LexOrder_1906) {
    // "10" < "2" lexicographically because '1' < '2'
    XMP_Node* left = CreateNode("10");
    XMP_Node* right = CreateNode("2");
    EXPECT_TRUE(Compare(left, right));
}

TEST_F(CompareTest_1906, SpecialCharacters_1906) {
    XMP_Node* left = CreateNode("!name");
    XMP_Node* right = CreateNode("name");
    EXPECT_TRUE(Compare(left, right));
}

TEST_F(CompareTest_1906, SortingWithCompare_1906) {
    XMP_Node* a = CreateNode("charlie");
    XMP_Node* b = CreateNode("alpha");
    XMP_Node* c = CreateNode("bravo");

    std::vector<XMP_Node*> vec = {a, b, c};
    std::sort(vec.begin(), vec.end(), Compare);

    EXPECT_EQ(vec[0]->name, "alpha");
    EXPECT_EQ(vec[1]->name, "bravo");
    EXPECT_EQ(vec[2]->name, "charlie");
}

TEST_F(CompareTest_1906, SortingAlreadySorted_1906) {
    XMP_Node* a = CreateNode("a");
    XMP_Node* b = CreateNode("b");
    XMP_Node* c = CreateNode("c");

    std::vector<XMP_Node*> vec = {a, b, c};
    std::sort(vec.begin(), vec.end(), Compare);

    EXPECT_EQ(vec[0]->name, "a");
    EXPECT_EQ(vec[1]->name, "b");
    EXPECT_EQ(vec[2]->name, "c");
}

TEST_F(CompareTest_1906, SortingReverseSorted_1906) {
    XMP_Node* a = CreateNode("c");
    XMP_Node* b = CreateNode("b");
    XMP_Node* c = CreateNode("a");

    std::vector<XMP_Node*> vec = {a, b, c};
    std::sort(vec.begin(), vec.end(), Compare);

    EXPECT_EQ(vec[0]->name, "a");
    EXPECT_EQ(vec[1]->name, "b");
    EXPECT_EQ(vec[2]->name, "c");
}

TEST_F(CompareTest_1906, CompareSymmetry_1906) {
    XMP_Node* left = CreateNode("aaa");
    XMP_Node* right = CreateNode("bbb");
    // If left < right is true, then right < left should be false
    EXPECT_TRUE(Compare(left, right));
    EXPECT_FALSE(Compare(right, left));
}

TEST_F(CompareTest_1906, CompareIrreflexive_1906) {
    XMP_Node* node = CreateNode("test");
    // A node should not be less than itself
    EXPECT_FALSE(Compare(node, node));
}

TEST_F(CompareTest_1906, CompareWithUnicodeCharacters_1906) {
    XMP_Node* left = CreateNode("ñ");
    XMP_Node* right = CreateNode("z");
    // Depends on byte values; ñ in UTF-8 is 0xC3 0xB1 which is > 'z' (0x7A)
    EXPECT_FALSE(Compare(left, right));
}

TEST_F(CompareTest_1906, LongStringComparison_1906) {
    std::string longStr1(1000, 'a');
    std::string longStr2(1000, 'b');
    XMP_Node* left = CreateNode(longStr1);
    XMP_Node* right = CreateNode(longStr2);
    EXPECT_TRUE(Compare(left, right));
}

TEST_F(CompareTest_1906, LongStringEqualComparison_1906) {
    std::string longStr(1000, 'x');
    XMP_Node* left = CreateNode(longStr);
    XMP_Node* right = CreateNode(longStr);
    EXPECT_FALSE(Compare(left, right));
}

// Tests for XMP_Node construction and basic properties
class XMPNodeTest_1906 : public ::testing::Test {
protected:
    void TearDown() override {
        for (auto* node : nodes_) {
            delete node;
        }
        nodes_.clear();
    }

    XMP_Node* CreateNode(XMP_Node* parent, const char* name, XMP_OptionBits options) {
        XMP_Node* node = new XMP_Node(parent, name, options);
        nodes_.push_back(node);
        return node;
    }

    XMP_Node* CreateNodeWithValue(XMP_Node* parent, const char* name, const char* value, XMP_OptionBits options) {
        XMP_Node* node = new XMP_Node(parent, name, value, options);
        nodes_.push_back(node);
        return node;
    }

    std::vector<XMP_Node*> nodes_;
};

TEST_F(XMPNodeTest_1906, ConstructWithCStringName_1906) {
    XMP_Node* node = CreateNode(nullptr, "testName", 0);
    EXPECT_EQ(node->name, "testName");
    EXPECT_EQ(node->parent, nullptr);
}

TEST_F(XMPNodeTest_1906, ConstructWithStringName_1906) {
    std::string name = "stringName";
    XMP_Node* node = new XMP_Node(nullptr, name, 0);
    nodes_.push_back(node);
    EXPECT_EQ(node->name, "stringName");
}

TEST_F(XMPNodeTest_1906, ConstructWithNameAndValue_1906) {
    XMP_Node* node = CreateNodeWithValue(nullptr, "name", "value", 0);
    EXPECT_EQ(node->name, "name");
    EXPECT_EQ(node->value, "value");
}

TEST_F(XMPNodeTest_1906, ConstructWithParent_1906) {
    XMP_Node* parent = CreateNode(nullptr, "parent", 0);
    XMP_Node* child = CreateNode(parent, "child", 0);
    EXPECT_EQ(child->parent, parent);
}

TEST_F(XMPNodeTest_1906, ConstructWithEmptyName_1906) {
    XMP_Node* node = CreateNode(nullptr, "", 0);
    EXPECT_EQ(node->name, "");
}

TEST_F(XMPNodeTest_1906, ConstructWithEmptyValue_1906) {
    XMP_Node* node = CreateNodeWithValue(nullptr, "name", "", 0);
    EXPECT_EQ(node->value, "");
}

TEST_F(XMPNodeTest_1906, DefaultValueIsEmpty_1906) {
    XMP_Node* node = CreateNode(nullptr, "name", 0);
    EXPECT_EQ(node->value, "");
}

TEST_F(XMPNodeTest_1906, ChildrenInitiallyEmpty_1906) {
    XMP_Node* node = CreateNode(nullptr, "name", 0);
    EXPECT_TRUE(node->children.empty());
}

TEST_F(XMPNodeTest_1906, QualifiersInitiallyEmpty_1906) {
    XMP_Node* node = CreateNode(nullptr, "name", 0);
    EXPECT_TRUE(node->qualifiers.empty());
}
