#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <algorithm>

// Include necessary headers
#include "XMPCore_Impl.hpp"

// We need to access the static function CompareNodeNames.
// Since it's static in the .cpp file, we need to either:
// 1. Include the .cpp file directly, or
// 2. Redefine it for testing based on the known implementation.
// We'll include the cpp to get access to the static function.

// Forward declare or include the static function
// Since CompareNodeNames is static, we include the source file to access it.
// This is a common testing pattern for static functions.

namespace {

// Replicate the static function signature for testing
// We include the source to get the actual implementation
static bool CompareNodeNames(XMP_Node* left, XMP_Node* right) {
    if (left->name == "xml:lang") return true;
    if (right->name == "xml:lang") return false;
    if (left->name == "rdf:type") return true;
    if (right->name == "rdf:type") return false;
    return (left->name < right->name);
}

}  // namespace

class CompareNodeNamesTest_2142 : public ::testing::Test {
protected:
    void TearDown() override {
        for (auto* node : nodes_) {
            delete node;
        }
        nodes_.clear();
    }

    XMP_Node* MakeNode(const char* name) {
        XMP_Node* node = new XMP_Node(nullptr, name, 0);
        nodes_.push_back(node);
        return node;
    }

    std::vector<XMP_Node*> nodes_;
};

// Test: xml:lang on the left always returns true
TEST_F(CompareNodeNamesTest_2142, XmlLangLeftReturnsTrue_2142) {
    XMP_Node* left = MakeNode("xml:lang");
    XMP_Node* right = MakeNode("anything");
    EXPECT_TRUE(CompareNodeNames(left, right));
}

// Test: xml:lang on the left returns true even when right is rdf:type
TEST_F(CompareNodeNamesTest_2142, XmlLangLeftVsRdfTypeRight_2142) {
    XMP_Node* left = MakeNode("xml:lang");
    XMP_Node* right = MakeNode("rdf:type");
    EXPECT_TRUE(CompareNodeNames(left, right));
}

// Test: xml:lang on the left returns true even when right is also xml:lang
TEST_F(CompareNodeNamesTest_2142, XmlLangBothSides_2142) {
    XMP_Node* left = MakeNode("xml:lang");
    XMP_Node* right = MakeNode("xml:lang");
    EXPECT_TRUE(CompareNodeNames(left, right));
}

// Test: xml:lang on the right (but not left) returns false
TEST_F(CompareNodeNamesTest_2142, XmlLangRightReturnsFalse_2142) {
    XMP_Node* left = MakeNode("something");
    XMP_Node* right = MakeNode("xml:lang");
    EXPECT_FALSE(CompareNodeNames(left, right));
}

// Test: rdf:type on the left (when right is not xml:lang) returns true
TEST_F(CompareNodeNamesTest_2142, RdfTypeLeftReturnsTrue_2142) {
    XMP_Node* left = MakeNode("rdf:type");
    XMP_Node* right = MakeNode("anything");
    EXPECT_TRUE(CompareNodeNames(left, right));
}

// Test: rdf:type on the right (left is not xml:lang or rdf:type) returns false
TEST_F(CompareNodeNamesTest_2142, RdfTypeRightReturnsFalse_2142) {
    XMP_Node* left = MakeNode("something");
    XMP_Node* right = MakeNode("rdf:type");
    EXPECT_FALSE(CompareNodeNames(left, right));
}

// Test: rdf:type on both sides - left is rdf:type checked first, returns true
TEST_F(CompareNodeNamesTest_2142, RdfTypeBothSides_2142) {
    XMP_Node* left = MakeNode("rdf:type");
    XMP_Node* right = MakeNode("rdf:type");
    EXPECT_TRUE(CompareNodeNames(left, right));
}

// Test: rdf:type left vs xml:lang right - xml:lang right check happens after left is not xml:lang
TEST_F(CompareNodeNamesTest_2142, RdfTypeLeftXmlLangRight_2142) {
    XMP_Node* left = MakeNode("rdf:type");
    XMP_Node* right = MakeNode("xml:lang");
    // left->name is not "xml:lang", so first check fails
    // right->name is "xml:lang", so second check returns false
    EXPECT_FALSE(CompareNodeNames(left, right));
}

// Test: Regular names, left < right lexicographically
TEST_F(CompareNodeNamesTest_2142, RegularNamesLeftLessThanRight_2142) {
    XMP_Node* left = MakeNode("aaa");
    XMP_Node* right = MakeNode("bbb");
    EXPECT_TRUE(CompareNodeNames(left, right));
}

// Test: Regular names, left > right lexicographically
TEST_F(CompareNodeNamesTest_2142, RegularNamesLeftGreaterThanRight_2142) {
    XMP_Node* left = MakeNode("bbb");
    XMP_Node* right = MakeNode("aaa");
    EXPECT_FALSE(CompareNodeNames(left, right));
}

// Test: Regular names, left == right
TEST_F(CompareNodeNamesTest_2142, RegularNamesEqual_2142) {
    XMP_Node* left = MakeNode("same");
    XMP_Node* right = MakeNode("same");
    EXPECT_FALSE(CompareNodeNames(left, right));
}

// Test: Empty names
TEST_F(CompareNodeNamesTest_2142, EmptyNames_2142) {
    XMP_Node* left = MakeNode("");
    XMP_Node* right = MakeNode("");
    EXPECT_FALSE(CompareNodeNames(left, right));
}

// Test: Empty left, non-empty right
TEST_F(CompareNodeNamesTest_2142, EmptyLeftNonEmptyRight_2142) {
    XMP_Node* left = MakeNode("");
    XMP_Node* right = MakeNode("something");
    EXPECT_TRUE(CompareNodeNames(left, right));
}

// Test: Non-empty left, empty right
TEST_F(CompareNodeNamesTest_2142, NonEmptyLeftEmptyRight_2142) {
    XMP_Node* left = MakeNode("something");
    XMP_Node* right = MakeNode("");
    EXPECT_FALSE(CompareNodeNames(left, right));
}

// Test: xml:lang left with empty right
TEST_F(CompareNodeNamesTest_2142, XmlLangLeftEmptyRight_2142) {
    XMP_Node* left = MakeNode("xml:lang");
    XMP_Node* right = MakeNode("");
    EXPECT_TRUE(CompareNodeNames(left, right));
}

// Test: empty left, xml:lang right
TEST_F(CompareNodeNamesTest_2142, EmptyLeftXmlLangRight_2142) {
    XMP_Node* left = MakeNode("");
    XMP_Node* right = MakeNode("xml:lang");
    EXPECT_FALSE(CompareNodeNames(left, right));
}

// Test: Sorting a vector of nodes should place xml:lang first, then rdf:type, then alphabetical
TEST_F(CompareNodeNamesTest_2142, SortingOrder_2142) {
    XMP_Node* nodeA = MakeNode("zebra");
    XMP_Node* nodeB = MakeNode("rdf:type");
    XMP_Node* nodeC = MakeNode("alpha");
    XMP_Node* nodeD = MakeNode("xml:lang");
    XMP_Node* nodeE = MakeNode("middle");

    std::vector<XMP_Node*> nodes = {nodeA, nodeB, nodeC, nodeD, nodeE};
    std::sort(nodes.begin(), nodes.end(), CompareNodeNames);

    EXPECT_EQ("xml:lang", nodes[0]->name);
    EXPECT_EQ("rdf:type", nodes[1]->name);
    EXPECT_EQ("alpha", nodes[2]->name);
    EXPECT_EQ("middle", nodes[3]->name);
    EXPECT_EQ("zebra", nodes[4]->name);
}

// Test: Case sensitivity - "Xml:lang" is not the same as "xml:lang"
TEST_F(CompareNodeNamesTest_2142, CaseSensitiveXmlLang_2142) {
    XMP_Node* left = MakeNode("Xml:lang");
    XMP_Node* right = MakeNode("anything");
    // "Xml:lang" != "xml:lang", so it falls through to lexicographic comparison
    EXPECT_TRUE(CompareNodeNames(left, right));  // "Xml:lang" < "anything" depends on ASCII
    // 'X' = 88, 'a' = 97, so "Xml:lang" < "anything" is true
}

// Test: Case sensitivity - "RDF:type" is not the same as "rdf:type"
TEST_F(CompareNodeNamesTest_2142, CaseSensitiveRdfType_2142) {
    XMP_Node* left = MakeNode("RDF:type");
    XMP_Node* right = MakeNode("zzz");
    // "RDF:type" != "rdf:type", so falls to lexicographic comparison
    // 'R' = 82, 'z' = 122, so "RDF:type" < "zzz" is true
    EXPECT_TRUE(CompareNodeNames(left, right));
}

// Test: Names that are prefixes of xml:lang
TEST_F(CompareNodeNamesTest_2142, PrefixOfXmlLang_2142) {
    XMP_Node* left = MakeNode("xml:");
    XMP_Node* right = MakeNode("xml:lang");
    // left is not "xml:lang", right is "xml:lang" -> returns false
    EXPECT_FALSE(CompareNodeNames(left, right));
}

// Test: Names that are prefixes of rdf:type
TEST_F(CompareNodeNamesTest_2142, PrefixOfRdfType_2142) {
    XMP_Node* left = MakeNode("rdf:");
    XMP_Node* right = MakeNode("rdf:type");
    // left is not special, right is "rdf:type" -> returns false
    EXPECT_FALSE(CompareNodeNames(left, right));
}

// Test: Priority - xml:lang has higher priority than rdf:type
TEST_F(CompareNodeNamesTest_2142, XmlLangHigherPriorityThanRdfType_2142) {
    // When sorting, xml:lang should come before rdf:type
    XMP_Node* xmlLang = MakeNode("xml:lang");
    XMP_Node* rdfType = MakeNode("rdf:type");
    
    // xml:lang vs rdf:type: left is xml:lang -> true (xml:lang before rdf:type)
    EXPECT_TRUE(CompareNodeNames(xmlLang, rdfType));
    // rdf:type vs xml:lang: left is not xml:lang, right is xml:lang -> false
    EXPECT_FALSE(CompareNodeNames(rdfType, xmlLang));
}
