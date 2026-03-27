// ============================================================================
// File: CompareNodeNamesTest_2142.cpp
// Description: Unit tests for static CompareNodeNames in XMPMeta.cpp
// TEST_ID: 2142
// ============================================================================

#include <gtest/gtest.h>

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

// Include the class definition used by CompareNodeNames.
#include "TestProjects/exiv2/xmpsdk/src/XMPCore_Impl.hpp"

// IMPORTANT:
// CompareNodeNames is declared `static` inside XMPMeta.cpp, so it has internal linkage.
// To test it as a black box without re-implementing logic, we include the .cpp so the
// tests are compiled in the same translation unit and can call the function directly.
#include "TestProjects/exiv2/xmpsdk/src/XMPMeta.cpp"

namespace {

class CompareNodeNamesTest_2142 : public ::testing::Test {
protected:
  static std::unique_ptr<XMP_Node> MakeNode(const char* name) {
    // Parent pointer and options are not relevant for name comparison.
    return std::make_unique<XMP_Node>(nullptr, name, (XMP_OptionBits)0);
  }
};

TEST_F(CompareNodeNamesTest_2142, LeftXmlLangAlwaysTrue_2142) {
  auto left = MakeNode("xml:lang");
  auto right = MakeNode("anything");
  EXPECT_TRUE(CompareNodeNames(left.get(), right.get()));

  auto right2 = MakeNode("xml:lang");
  EXPECT_TRUE(CompareNodeNames(left.get(), right2.get()));  // even when both are xml:lang
}

TEST_F(CompareNodeNamesTest_2142, RightXmlLangAlwaysFalseWhenLeftNotXmlLang_2142) {
  auto left = MakeNode("aaa");
  auto right = MakeNode("xml:lang");
  EXPECT_FALSE(CompareNodeNames(left.get(), right.get()));
}

TEST_F(CompareNodeNamesTest_2142, LeftRdfTypePreferredOverOtherNonXmlLang_2142) {
  auto left = MakeNode("rdf:type");
  auto right = MakeNode("zzz");
  EXPECT_TRUE(CompareNodeNames(left.get(), right.get()));

  auto right2 = MakeNode("rdf:type");
  EXPECT_TRUE(CompareNodeNames(left.get(), right2.get()));  // even when both are rdf:type
}

TEST_F(CompareNodeNamesTest_2142, RightRdfTypeBeatsNormalNamesWhenLeftNotSpecial_2142) {
  auto left = MakeNode("aaa");
  auto right = MakeNode("rdf:type");
  EXPECT_FALSE(CompareNodeNames(left.get(), right.get()));
}

TEST_F(CompareNodeNamesTest_2142, XmlLangHasPriorityOverRdfType_2142) {
  auto xmlLang = MakeNode("xml:lang");
  auto rdfType = MakeNode("rdf:type");

  // xml:lang should come before rdf:type.
  EXPECT_TRUE(CompareNodeNames(xmlLang.get(), rdfType.get()));
  EXPECT_FALSE(CompareNodeNames(rdfType.get(), xmlLang.get()));
}

TEST_F(CompareNodeNamesTest_2142, FallsBackToLexicographicComparisonForNormalNames_2142) {
  auto a = MakeNode("aaa");
  auto b = MakeNode("bbb");
  auto z = MakeNode("zzz");

  EXPECT_TRUE(CompareNodeNames(a.get(), b.get()));
  EXPECT_FALSE(CompareNodeNames(b.get(), a.get()));

  EXPECT_TRUE(CompareNodeNames(b.get(), z.get()));
  EXPECT_FALSE(CompareNodeNames(z.get(), b.get()));
}

TEST_F(CompareNodeNamesTest_2142, SortingPlacesSpecialNamesFirstAndOrdersOthers_2142) {
  auto n1 = MakeNode("bbb");
  auto n2 = MakeNode("xml:lang");
  auto n3 = MakeNode("aaa");
  auto n4 = MakeNode("rdf:type");
  auto n5 = MakeNode("ccc");

  std::vector<XMP_Node*> nodes{n1.get(), n2.get(), n3.get(), n4.get(), n5.get()};

  std::sort(nodes.begin(), nodes.end(),
            [](XMP_Node* l, XMP_Node* r) { return CompareNodeNames(l, r); });

  ASSERT_EQ(nodes.size(), 5u);
  EXPECT_EQ(nodes[0]->name, "xml:lang");
  EXPECT_EQ(nodes[1]->name, "rdf:type");
  EXPECT_EQ(nodes[2]->name, "aaa");
  EXPECT_EQ(nodes[3]->name, "bbb");
  EXPECT_EQ(nodes[4]->name, "ccc");
}

TEST_F(CompareNodeNamesTest_2142, SortingWithOnlyNormalNamesMatchesStringOrder_2142) {
  auto n1 = MakeNode("delta");
  auto n2 = MakeNode("alpha");
  auto n3 = MakeNode("charlie");
  auto n4 = MakeNode("bravo");

  std::vector<XMP_Node*> nodes{n1.get(), n2.get(), n3.get(), n4.get()};
  std::sort(nodes.begin(), nodes.end(),
            [](XMP_Node* l, XMP_Node* r) { return CompareNodeNames(l, r); });

  ASSERT_EQ(nodes.size(), 4u);
  EXPECT_EQ(nodes[0]->name, "alpha");
  EXPECT_EQ(nodes[1]->name, "bravo");
  EXPECT_EQ(nodes[2]->name, "charlie");
  EXPECT_EQ(nodes[3]->name, "delta");
}

}  // namespace