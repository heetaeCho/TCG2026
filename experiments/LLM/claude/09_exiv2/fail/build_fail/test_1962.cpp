#include <gtest/gtest.h>
#include <vector>
#include <string>

// Include necessary headers
#include "XMPCore_Impl.hpp"
#include "XMP_Const.h"

// We need to access the static function CompareAliasedSubtrees.
// Since it's defined as static in XMPMeta-Parse.cpp, we need to include it or
// re-declare access. For testing purposes, we include the source file directly.
// This is a common technique for testing static functions.

// Forward declaration approach won't work for static functions, so we include the cpp
// We may need to define some prerequisites that the cpp file expects.

// The function is static, so we need to expose it for testing.
// We'll include the implementation file to get access to the static function.
#include "XMPMeta-Parse.cpp"

class CompareAliasedSubtreesTest_1962 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a simple XMP_Node
    XMP_Node* makeNode(XMP_Node* parent, const char* name, const char* value, XMP_OptionBits options = 0) {
        return new XMP_Node(parent, name, value, options);
    }

    // Helper to clean up a tree of nodes
    void deleteTree(XMP_Node* node) {
        if (!node) return;
        for (auto* child : node->children) {
            deleteTree(child);
        }
        for (auto* qual : node->qualifiers) {
            deleteTree(qual);
        }
        node->children.clear();
        node->qualifiers.clear();
        delete node;
    }
};

// Test: Identical leaf nodes with same value should not throw
TEST_F(CompareAliasedSubtreesTest_1962, IdenticalLeafNodes_NoThrow_1962) {
    XMP_Node* alias = makeNode(nullptr, "alias", "value1");
    XMP_Node* base = makeNode(nullptr, "base", "value1");

    EXPECT_NO_THROW(CompareAliasedSubtrees(alias, base));

    deleteTree(alias);
    deleteTree(base);
}

// Test: Different values should throw kXMPErr_BadXMP
TEST_F(CompareAliasedSubtreesTest_1962, DifferentValues_Throws_1962) {
    XMP_Node* alias = makeNode(nullptr, "alias", "value1");
    XMP_Node* base = makeNode(nullptr, "base", "value2");

    EXPECT_THROW(CompareAliasedSubtrees(alias, base), XMP_Error);

    deleteTree(alias);
    deleteTree(base);
}

// Test: Different number of children should throw
TEST_F(CompareAliasedSubtreesTest_1962, DifferentChildCount_Throws_1962) {
    XMP_Node* alias = makeNode(nullptr, "alias", "value");
    XMP_Node* base = makeNode(nullptr, "base", "value");

    XMP_Node* child1 = makeNode(alias, "child1", "cv");
    alias->children.push_back(child1);

    EXPECT_THROW(CompareAliasedSubtrees(alias, base), XMP_Error);

    deleteTree(alias);
    deleteTree(base);
}

// Test: Same structure with one child each, matching values
TEST_F(CompareAliasedSubtreesTest_1962, MatchingOneChild_NoThrow_1962) {
    XMP_Node* alias = makeNode(nullptr, "alias", "value");
    XMP_Node* base = makeNode(nullptr, "base", "value");

    XMP_Node* aliasChild = makeNode(alias, "child", "childval", 0);
    alias->children.push_back(aliasChild);

    XMP_Node* baseChild = makeNode(base, "child", "childval", 0);
    base->children.push_back(baseChild);

    EXPECT_NO_THROW(CompareAliasedSubtrees(alias, base));

    deleteTree(alias);
    deleteTree(base);
}

// Test: Children with different names should throw (non-outer call checks name)
TEST_F(CompareAliasedSubtreesTest_1962, ChildrenDifferentNames_Throws_1962) {
    XMP_Node* alias = makeNode(nullptr, "alias", "value");
    XMP_Node* base = makeNode(nullptr, "base", "value");

    XMP_Node* aliasChild = makeNode(alias, "child_a", "childval", 0);
    alias->children.push_back(aliasChild);

    XMP_Node* baseChild = makeNode(base, "child_b", "childval", 0);
    base->children.push_back(baseChild);

    EXPECT_THROW(CompareAliasedSubtrees(alias, base), XMP_Error);

    deleteTree(alias);
    deleteTree(base);
}

// Test: Children with different options should throw
TEST_F(CompareAliasedSubtreesTest_1962, ChildrenDifferentOptions_Throws_1962) {
    XMP_Node* alias = makeNode(nullptr, "alias", "value");
    XMP_Node* base = makeNode(nullptr, "base", "value");

    XMP_Node* aliasChild = makeNode(alias, "child", "childval", 1);
    alias->children.push_back(aliasChild);

    XMP_Node* baseChild = makeNode(base, "child", "childval", 2);
    base->children.push_back(baseChild);

    EXPECT_THROW(CompareAliasedSubtrees(alias, base), XMP_Error);

    deleteTree(alias);
    deleteTree(base);
}

// Test: Children with different qualifier counts should throw
TEST_F(CompareAliasedSubtreesTest_1962, ChildrenDifferentQualifierCount_Throws_1962) {
    XMP_Node* alias = makeNode(nullptr, "alias", "value");
    XMP_Node* base = makeNode(nullptr, "base", "value");

    XMP_Node* aliasChild = makeNode(alias, "child", "childval", 0);
    XMP_Node* aliasQual = makeNode(aliasChild, "qual1", "qv", 0);
    aliasChild->qualifiers.push_back(aliasQual);
    alias->children.push_back(aliasChild);

    XMP_Node* baseChild = makeNode(base, "child", "childval", 0);
    base->children.push_back(baseChild);

    EXPECT_THROW(CompareAliasedSubtrees(alias, base), XMP_Error);

    deleteTree(alias);
    deleteTree(base);
}

// Test: Outer call does NOT check name or options mismatch (outerCall=true by default)
TEST_F(CompareAliasedSubtreesTest_1962, OuterCallDifferentNames_NoThrow_1962) {
    XMP_Node* alias = makeNode(nullptr, "different_name_a", "value", 1);
    XMP_Node* base = makeNode(nullptr, "different_name_b", "value", 2);

    // outerCall=true means name, options, qualifier size are NOT checked at top level
    EXPECT_NO_THROW(CompareAliasedSubtrees(alias, base, true));

    deleteTree(alias);
    deleteTree(base);
}

// Test: Outer call with different options at top level should not throw
TEST_F(CompareAliasedSubtreesTest_1962, OuterCallDifferentOptions_NoThrow_1962) {
    XMP_Node* alias = makeNode(nullptr, "name", "value", 10);
    XMP_Node* base = makeNode(nullptr, "name", "value", 20);

    EXPECT_NO_THROW(CompareAliasedSubtrees(alias, base, true));

    deleteTree(alias);
    deleteTree(base);
}

// Test: When outerCall is false, name mismatch throws
TEST_F(CompareAliasedSubtreesTest_1962, NonOuterCallNameMismatch_Throws_1962) {
    XMP_Node* alias = makeNode(nullptr, "name_a", "value", 0);
    XMP_Node* base = makeNode(nullptr, "name_b", "value", 0);

    EXPECT_THROW(CompareAliasedSubtrees(alias, base, false), XMP_Error);

    deleteTree(alias);
    deleteTree(base);
}

// Test: Empty nodes with same empty values should not throw
TEST_F(CompareAliasedSubtreesTest_1962, EmptyValueNodes_NoThrow_1962) {
    XMP_Node* alias = makeNode(nullptr, "a", "");
    XMP_Node* base = makeNode(nullptr, "b", "");

    EXPECT_NO_THROW(CompareAliasedSubtrees(alias, base));

    deleteTree(alias);
    deleteTree(base);
}

// Test: Deep nested matching tree should not throw
TEST_F(CompareAliasedSubtreesTest_1962, DeepNestedMatching_NoThrow_1962) {
    XMP_Node* alias = makeNode(nullptr, "root", "rv");
    XMP_Node* base = makeNode(nullptr, "root", "rv");

    XMP_Node* ac1 = makeNode(alias, "c1", "v1", 0);
    alias->children.push_back(ac1);
    XMP_Node* ac1c1 = makeNode(ac1, "c1c1", "v2", 0);
    ac1->children.push_back(ac1c1);

    XMP_Node* bc1 = makeNode(base, "c1", "v1", 0);
    base->children.push_back(bc1);
    XMP_Node* bc1c1 = makeNode(bc1, "c1c1", "v2", 0);
    bc1->children.push_back(bc1c1);

    EXPECT_NO_THROW(CompareAliasedSubtrees(alias, base));

    deleteTree(alias);
    deleteTree(base);
}

// Test: Deep nested mismatch in value at leaf should throw
TEST_F(CompareAliasedSubtreesTest_1962, DeepNestedValueMismatch_Throws_1962) {
    XMP_Node* alias = makeNode(nullptr, "root", "rv");
    XMP_Node* base = makeNode(nullptr, "root", "rv");

    XMP_Node* ac1 = makeNode(alias, "c1", "v1", 0);
    alias->children.push_back(ac1);
    XMP_Node* ac1c1 = makeNode(ac1, "c1c1", "MISMATCH", 0);
    ac1->children.push_back(ac1c1);

    XMP_Node* bc1 = makeNode(base, "c1", "v1", 0);
    base->children.push_back(bc1);
    XMP_Node* bc1c1 = makeNode(bc1, "c1c1", "v2", 0);
    bc1->children.push_back(bc1c1);

    EXPECT_THROW(CompareAliasedSubtrees(alias, base), XMP_Error);

    deleteTree(alias);
    deleteTree(base);
}

// Test: Matching qualifiers should not throw
TEST_F(CompareAliasedSubtreesTest_1962, MatchingQualifiers_NoThrow_1962) {
    XMP_Node* alias = makeNode(nullptr, "root", "rv");
    XMP_Node* base = makeNode(nullptr, "root", "rv");

    XMP_Node* aq = makeNode(alias, "qual", "qv", 0);
    alias->qualifiers.push_back(aq);

    XMP_Node* bq = makeNode(base, "qual", "qv", 0);
    base->qualifiers.push_back(bq);

    // Top-level qualifiers are iterated but not size-checked at outerCall=true
    // The qualifiers themselves are compared with outerCall=false
    EXPECT_NO_THROW(CompareAliasedSubtrees(alias, base));

    deleteTree(alias);
    deleteTree(base);
}

// Test: Qualifiers with value mismatch should throw
TEST_F(CompareAliasedSubtreesTest_1962, QualifierValueMismatch_Throws_1962) {
    XMP_Node* alias = makeNode(nullptr, "root", "rv");
    XMP_Node* base = makeNode(nullptr, "root", "rv");

    XMP_Node* aq = makeNode(alias, "qual", "qv1", 0);
    alias->qualifiers.push_back(aq);

    XMP_Node* bq = makeNode(base, "qual", "qv2", 0);
    base->qualifiers.push_back(bq);

    EXPECT_THROW(CompareAliasedSubtrees(alias, base), XMP_Error);

    deleteTree(alias);
    deleteTree(base);
}

// Test: Qualifiers with name mismatch should throw (non-outer call for quals)
TEST_F(CompareAliasedSubtreesTest_1962, QualifierNameMismatch_Throws_1962) {
    XMP_Node* alias = makeNode(nullptr, "root", "rv");
    XMP_Node* base = makeNode(nullptr, "root", "rv");

    XMP_Node* aq = makeNode(alias, "qual_a", "qv", 0);
    alias->qualifiers.push_back(aq);

    XMP_Node* bq = makeNode(base, "qual_b", "qv", 0);
    base->qualifiers.push_back(bq);

    EXPECT_THROW(CompareAliasedSubtrees(alias, base), XMP_Error);

    deleteTree(alias);
    deleteTree(base);
}

// Test: Multiple children all matching
TEST_F(CompareAliasedSubtreesTest_1962, MultipleChildrenMatching_NoThrow_1962) {
    XMP_Node* alias = makeNode(nullptr, "root", "rv");
    XMP_Node* base = makeNode(nullptr, "root", "rv");

    for (int i = 0; i < 5; ++i) {
        std::string cname = "child" + std::to_string(i);
        std::string cval = "val" + std::to_string(i);
        XMP_Node* ac = makeNode(alias, cname.c_str(), cval.c_str(), 0);
        alias->children.push_back(ac);
        XMP_Node* bc = makeNode(base, cname.c_str(), cval.c_str(), 0);
        base->children.push_back(bc);
    }

    EXPECT_NO_THROW(CompareAliasedSubtrees(alias, base));

    deleteTree(alias);
    deleteTree(base);
}

// Test: Verify the exception type contains correct error code
TEST_F(CompareAliasedSubtreesTest_1962, ExceptionContainsCorrectErrorCode_1962) {
    XMP_Node* alias = makeNode(nullptr, "alias", "val1");
    XMP_Node* base = makeNode(nullptr, "base", "val2");

    try {
        CompareAliasedSubtrees(alias, base);
        FAIL() << "Expected XMP_Error to be thrown";
    } catch (const XMP_Error& e) {
        EXPECT_EQ(e.GetID(), kXMPErr_BadXMP);
    }

    deleteTree(alias);
    deleteTree(base);
}

// Test: No children, no qualifiers, same value - simplest passing case
TEST_F(CompareAliasedSubtreesTest_1962, SimplestPassingCase_1962) {
    XMP_Node* alias = makeNode(nullptr, "a", "x");
    XMP_Node* base = makeNode(nullptr, "b", "x");

    EXPECT_NO_THROW(CompareAliasedSubtrees(alias, base));

    deleteTree(alias);
    deleteTree(base);
}

// Test: outerCall=false with matching everything should pass
TEST_F(CompareAliasedSubtreesTest_1962, NonOuterCallFullyMatching_NoThrow_1962) {
    XMP_Node* alias = makeNode(nullptr, "same", "value", 42);
    XMP_Node* base = makeNode(nullptr, "same", "value", 42);

    EXPECT_NO_THROW(CompareAliasedSubtrees(alias, base, false));

    deleteTree(alias);
    deleteTree(base);
}

// Test: outerCall=false with different qualifier count at top level should throw
TEST_F(CompareAliasedSubtreesTest_1962, NonOuterCallDiffQualCount_Throws_1962) {
    XMP_Node* alias = makeNode(nullptr, "same", "value", 0);
    XMP_Node* base = makeNode(nullptr, "same", "value", 0);

    XMP_Node* aq = makeNode(alias, "q", "qv", 0);
    alias->qualifiers.push_back(aq);

    EXPECT_THROW(CompareAliasedSubtrees(alias, base, false), XMP_Error);

    deleteTree(alias);
    deleteTree(base);
}
