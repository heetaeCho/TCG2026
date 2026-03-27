// =================================================================================================
// TEST_ID: 2121
// Unit tests for AddQualifierNode (./TestProjects/exiv2/xmpsdk/src/ParseRDF.cpp)
// =================================================================================================

#include <gtest/gtest.h>

#include <string>

// Pull in the real SDK types.
#include "XMP_Const.h"
#include "XMPCore_Impl.hpp"

// NOTE: AddQualifierNode is a static function in ParseRDF.cpp (internal linkage).
// To test it without changing production code, we include the .cpp into this test TU.
#include "ParseRDF.cpp"

namespace {

class AddQualifierNodeTest_2121 : public ::testing::Test {
protected:
  XMP_Node MakeParent(const char* name = "parent") {
    // Pick a safe constructor that exists in XMPCore_Impl.hpp as provided.
    // Options start at 0 for a plain node.
    return XMP_Node(nullptr, name, static_cast<XMP_OptionBits>(0));
  }

  static bool HasBit(XMP_OptionBits bits, XMP_OptionBits flag) { return (bits & flag) != 0; }
};

TEST_F(AddQualifierNodeTest_2121, AddsNonSpecialQualifier_AppendsAndSetsFlags_2121) {
  XMP_Node parent = MakeParent("p");

  ASSERT_TRUE(parent.qualifiers.empty());

  XMP_Node* q = AddQualifierNode(&parent, XMP_VarString("ns:qual"), XMP_VarString("v"));

  ASSERT_NE(q, nullptr);
  EXPECT_EQ(q->parent, &parent);
  EXPECT_EQ(q->name, "ns:qual");
  EXPECT_EQ(q->value, "v");

  ASSERT_EQ(parent.qualifiers.size(), 1u);
  EXPECT_EQ(parent.qualifiers[0], q);

  // Parent should indicate it has qualifiers.
  EXPECT_TRUE(HasBit(parent.options, kXMP_PropHasQualifiers));
  // Non-special qualifier should not set these special bits.
  EXPECT_FALSE(HasBit(parent.options, kXMP_PropHasLang));
  EXPECT_FALSE(HasBit(parent.options, kXMP_PropHasType));

  // Qualifier node should be marked as qualifier.
  EXPECT_TRUE(HasBit(q->options, kXMP_PropIsQualifier));
}

TEST_F(AddQualifierNodeTest_2121, AddsXmlLangQualifier_GoesFirstAndSetsLangFlags_2121) {
  XMP_Node parent = MakeParent("p");

  // Seed with a non-special qualifier first.
  XMP_Node* first = AddQualifierNode(&parent, XMP_VarString("ns:qual"), XMP_VarString("v1"));
  ASSERT_NE(first, nullptr);
  ASSERT_EQ(parent.qualifiers.size(), 1u);
  ASSERT_EQ(parent.qualifiers[0], first);

  XMP_Node* lang = AddQualifierNode(&parent, XMP_VarString("xml:lang"), XMP_VarString("en-US"));

  ASSERT_NE(lang, nullptr);
  ASSERT_EQ(parent.qualifiers.size(), 2u);

  // xml:lang should be at the beginning.
  EXPECT_EQ(parent.qualifiers[0], lang);
  EXPECT_EQ(parent.qualifiers[1], first);

  EXPECT_TRUE(HasBit(parent.options, kXMP_PropHasQualifiers));
  EXPECT_TRUE(HasBit(parent.options, kXMP_PropHasLang));
  EXPECT_FALSE(HasBit(parent.options, kXMP_PropHasType));

  EXPECT_TRUE(HasBit(lang->options, kXMP_PropIsQualifier));
  EXPECT_EQ(lang->name, "xml:lang");
  EXPECT_EQ(lang->value, "en-US");
}

TEST_F(AddQualifierNodeTest_2121, AddsRdfTypeQualifier_WhenNoLang_GoesFirstAndSetsTypeFlags_2121) {
  XMP_Node parent = MakeParent("p");

  // Seed with a non-special qualifier first.
  XMP_Node* first = AddQualifierNode(&parent, XMP_VarString("ns:qual"), XMP_VarString("v1"));
  ASSERT_NE(first, nullptr);
  ASSERT_EQ(parent.qualifiers.size(), 1u);
  ASSERT_EQ(parent.qualifiers[0], first);

  XMP_Node* type = AddQualifierNode(&parent, XMP_VarString("rdf:type"), XMP_VarString("SomeType"));

  ASSERT_NE(type, nullptr);
  ASSERT_EQ(parent.qualifiers.size(), 2u);

  // rdf:type should be inserted at the beginning when there is no xml:lang.
  EXPECT_EQ(parent.qualifiers[0], type);
  EXPECT_EQ(parent.qualifiers[1], first);

  EXPECT_TRUE(HasBit(parent.options, kXMP_PropHasQualifiers));
  EXPECT_FALSE(HasBit(parent.options, kXMP_PropHasLang));
  EXPECT_TRUE(HasBit(parent.options, kXMP_PropHasType));

  EXPECT_TRUE(HasBit(type->options, kXMP_PropIsQualifier));
  EXPECT_EQ(type->name, "rdf:type");
  EXPECT_EQ(type->value, "SomeType");
}

TEST_F(AddQualifierNodeTest_2121, AddsRdfTypeQualifier_WhenLangExists_GoesAfterLang_2121) {
  XMP_Node parent = MakeParent("p");

  XMP_Node* lang = AddQualifierNode(&parent, XMP_VarString("xml:lang"), XMP_VarString("fr-FR"));
  ASSERT_NE(lang, nullptr);
  ASSERT_EQ(parent.qualifiers.size(), 1u);
  ASSERT_EQ(parent.qualifiers[0], lang);
  ASSERT_TRUE(HasBit(parent.options, kXMP_PropHasLang));

  // Add another ordinary qualifier after lang.
  XMP_Node* other = AddQualifierNode(&parent, XMP_VarString("ns:qual"), XMP_VarString("v"));
  ASSERT_NE(other, nullptr);
  ASSERT_EQ(parent.qualifiers.size(), 2u);

  // Now add rdf:type; it should come after xml:lang (and before non-special ones).
  XMP_Node* type = AddQualifierNode(&parent, XMP_VarString("rdf:type"), XMP_VarString("T"));
  ASSERT_NE(type, nullptr);
  ASSERT_EQ(parent.qualifiers.size(), 3u);

  EXPECT_EQ(parent.qualifiers[0], lang);
  EXPECT_EQ(parent.qualifiers[1], type);
  EXPECT_EQ(parent.qualifiers[2], other);

  EXPECT_TRUE(HasBit(parent.options, kXMP_PropHasQualifiers));
  EXPECT_TRUE(HasBit(parent.options, kXMP_PropHasLang));
  EXPECT_TRUE(HasBit(parent.options, kXMP_PropHasType));
}

TEST_F(AddQualifierNodeTest_2121, AddsMultipleNonSpecialQualifiers_PreservesAppendOrder_2121) {
  XMP_Node parent = MakeParent("p");

  XMP_Node* q1 = AddQualifierNode(&parent, XMP_VarString("ns:q1"), XMP_VarString("v1"));
  XMP_Node* q2 = AddQualifierNode(&parent, XMP_VarString("ns:q2"), XMP_VarString("v2"));
  XMP_Node* q3 = AddQualifierNode(&parent, XMP_VarString("ns:q3"), XMP_VarString("v3"));

  ASSERT_NE(q1, nullptr);
  ASSERT_NE(q2, nullptr);
  ASSERT_NE(q3, nullptr);

  ASSERT_EQ(parent.qualifiers.size(), 3u);
  EXPECT_EQ(parent.qualifiers[0], q1);
  EXPECT_EQ(parent.qualifiers[1], q2);
  EXPECT_EQ(parent.qualifiers[2], q3);

  EXPECT_TRUE(HasBit(parent.options, kXMP_PropHasQualifiers));
  EXPECT_FALSE(HasBit(parent.options, kXMP_PropHasLang));
  EXPECT_FALSE(HasBit(parent.options, kXMP_PropHasType));
}

} // namespace