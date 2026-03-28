// =================================================================================================
// TEST_ID 2113
// Unit tests for SerializeCompactRDFElemProps (black-box, interface/observable behavior only)
// =================================================================================================

#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <vector>

// Pull in the real XMP_Node definition used by the code under test.
#include "TestProjects/exiv2/xmpsdk/src/XMPCore_Impl.hpp"
#include "TestProjects/exiv2/xmpsdk/include/XMP_Const.h"

// IMPORTANT: SerializeCompactRDFElemProps is a static function in a .cpp file.
// To test it without changing production code, include the implementation file so the
// function is in the same translation unit as these tests.
#include "TestProjects/exiv2/xmpsdk/src/XMPMeta-Serialize.cpp"

namespace {

// Simple owning arena for nodes allocated with new (the XMP SDK uses raw pointers in offspring lists).
class NodeArena {
 public:
  XMP_Node* MakeNode(XMP_Node* parent, const char* name, XMP_OptionBits options = 0) {
    nodes_.emplace_back(std::unique_ptr<XMP_Node>(new XMP_Node(parent, name, options)));
    return nodes_.back().get();
  }

  XMP_Node* MakeNode(XMP_Node* parent, const char* name, const char* value, XMP_OptionBits options = 0) {
    nodes_.emplace_back(std::unique_ptr<XMP_Node>(new XMP_Node(parent, name, value, options)));
    return nodes_.back().get();
  }

 private:
  std::vector<std::unique_ptr<XMP_Node>> nodes_;
};

class SerializeCompactRDFElemPropsTest_2113 : public ::testing::Test {
 protected:
  static constexpr XMP_StringPtr kNL = "\n";
  static constexpr XMP_StringPtr kIndent = "  ";

  NodeArena arena_;

  std::string SerializeChildrenOf(XMP_Node* parent, XMP_Index indent = 0) {
    XMP_VarString out;
    SerializeCompactRDFElemProps(parent, out, kNL, kIndent, indent);
    return out;
  }
};

TEST_F(SerializeCompactRDFElemPropsTest_2113, EmitsRdfLiWhenNameStartsWithBracket_2113) {
  XMP_Node* root = arena_.MakeNode(nullptr, "root", 0);

  // Name beginning with '[' should be emitted as rdf:li.
  XMP_Node* item = arena_.MakeNode(root, "[1]", "value", 0);
  root->children.push_back(item);

  const std::string out = SerializeChildrenOf(root, /*indent=*/0);

  EXPECT_NE(out.find("<rdf:li"), std::string::npos);
  EXPECT_NE(out.find(">value</rdf:li>"), std::string::npos);
}

TEST_F(SerializeCompactRDFElemPropsTest_2113, EmitsEmptyPropertyAsSelfClosingTag_2113) {
  XMP_Node* root = arena_.MakeNode(nullptr, "root", 0);

  // Empty value, simple (non-composite) -> "/>" + newline.
  XMP_Node* p = arena_.MakeNode(root, "ns:Empty", "", 0);
  root->children.push_back(p);

  const std::string out = SerializeChildrenOf(root, /*indent=*/0);

  EXPECT_NE(out.find("<ns:Empty/>"), std::string::npos);
  EXPECT_NE(out.find("<ns:Empty/>" + std::string(kNL)), std::string::npos);
}

TEST_F(SerializeCompactRDFElemPropsTest_2113, EmitsUriValueAsRdfResourceAttributeAndSelfCloses_2113) {
  XMP_Node* root = arena_.MakeNode(nullptr, "root", 0);

  // If kXMP_PropValueIsURI is set on a simple property, it should serialize as rdf:resource="..."/> .
  XMP_Node* p = arena_.MakeNode(root, "ns:Link", "http://example.com", kXMP_PropValueIsURI);
  root->children.push_back(p);

  const std::string out = SerializeChildrenOf(root, /*indent=*/0);

  EXPECT_NE(out.find("<ns:Link"), std::string::npos);
  EXPECT_NE(out.find("rdf:resource=\"http://example.com\""), std::string::npos);
  EXPECT_NE(out.find("\"/>" + std::string(kNL)), std::string::npos);
}

TEST_F(SerializeCompactRDFElemPropsTest_2113, EmitsNonEmptySimpleValueWithStartAndEndTags_2113) {
  XMP_Node* root = arena_.MakeNode(nullptr, "root", 0);

  XMP_Node* p = arena_.MakeNode(root, "ns:Title", "Hello", 0);
  root->children.push_back(p);

  const std::string out = SerializeChildrenOf(root, /*indent=*/0);

  EXPECT_NE(out.find("<ns:Title"), std::string::npos);
  EXPECT_NE(out.find(">Hello</ns:Title>" + std::string(kNL)), std::string::npos);
}

TEST_F(SerializeCompactRDFElemPropsTest_2113, EmitsArrayChildrenIncludingRdfLiFromBracketNames_2113) {
  XMP_Node* root = arena_.MakeNode(nullptr, "root", 0);

  // Mark as array (composite). Exact container tag (Bag/Seq/Alt) is delegated to EmitRDFArrayTag,
  // so we only validate observable recursion: the children are serialized as rdf:li when bracketed.
  XMP_Node* arr = arena_.MakeNode(root, "ns:Array", kXMP_PropValueIsArray);
  root->children.push_back(arr);

  XMP_Node* li1 = arena_.MakeNode(arr, "[1]", "A", 0);
  XMP_Node* li2 = arena_.MakeNode(arr, "[2]", "B", 0);
  arr->children.push_back(li1);
  arr->children.push_back(li2);

  const std::string out = SerializeChildrenOf(root, /*indent=*/0);

  EXPECT_NE(out.find("<ns:Array"), std::string::npos);
  EXPECT_NE(out.find("<rdf:li"), std::string::npos);
  EXPECT_NE(out.find(">A</rdf:li>"), std::string::npos);
  EXPECT_NE(out.find(">B</rdf:li>"), std::string::npos);
}

TEST_F(SerializeCompactRDFElemPropsTest_2113, StructWithMixedFieldStylesUsesRdfDescriptionWrapper_2113) {
  XMP_Node* root = arena_.MakeNode(nullptr, "root", 0);

  // Make a struct property. The serializer decides whether fields can be attributes vs elements
  // using CanBeRDFAttrProp. To encourage a mix:
  // - "ns:AttrCandidate" is a simple leaf (likely attribute-serializable)
  // - "ns:ElemForced" is an array (likely element field)
  XMP_Node* st = arena_.MakeNode(root, "ns:Struct", kXMP_PropValueIsStruct);
  root->children.push_back(st);

  XMP_Node* attrCandidate = arena_.MakeNode(st, "ns:AttrCandidate", "v", 0);
  st->children.push_back(attrCandidate);

  XMP_Node* elemForced = arena_.MakeNode(st, "ns:ElemForced", kXMP_PropValueIsArray);
  st->children.push_back(elemForced);

  XMP_Node* li = arena_.MakeNode(elemForced, "[1]", "x", 0);
  elemForced->children.push_back(li);

  const std::string out = SerializeChildrenOf(root, /*indent=*/0);

  // Observable behavior of the "mixed fields" path includes emitting an rdf:Description wrapper.
  EXPECT_NE(out.find("<rdf:Description"), std::string::npos);
  EXPECT_NE(out.find(kRDF_StructEnd), std::string::npos);
}

TEST_F(SerializeCompactRDFElemPropsTest_2113, StructWithRdfResourceQualifierAndElementFieldsThrows_2113) {
  XMP_Node* root = arena_.MakeNode(nullptr, "root", 0);

  XMP_Node* st = arena_.MakeNode(root, "ns:Struct", kXMP_PropValueIsStruct);
  root->children.push_back(st);

  // Add rdf:resource qualifier.
  XMP_Node* q = arena_.MakeNode(st, "rdf:resource", "http://example.com/res", kXMP_PropIsQualifier);
  st->qualifiers.push_back(q);

  // Add an element-style field to ensure "hasElemFields" becomes true (array is a strong signal).
  XMP_Node* elemField = arena_.MakeNode(st, "ns:ElemForced", kXMP_PropValueIsArray);
  st->children.push_back(elemField);
  XMP_Node* li = arena_.MakeNode(elemField, "[1]", "x", 0);
  elemField->children.push_back(li);

  XMP_VarString out;
  EXPECT_ANY_THROW({
    SerializeCompactRDFElemProps(root, out, kNL, kIndent, /*indent=*/0);
  });
}

TEST_F(SerializeCompactRDFElemPropsTest_2113, GeneralQualifierForcesParseTypeResourceAndPrettyProperties_2113) {
  XMP_Node* root = arena_.MakeNode(nullptr, "root", 0);

  XMP_Node* p = arena_.MakeNode(root, "ns:Prop", "V", 0);
  root->children.push_back(p);

  // Use a non-rdf:* qualifier name to be treated as a "general qualifier" (not an RDF attribute qualifier).
  XMP_Node* genQ = arena_.MakeNode(p, "ns:qual", "QV", kXMP_PropIsQualifier);
  p->qualifiers.push_back(genQ);

  const std::string out = SerializeChildrenOf(root, /*indent=*/0);

  // Observable outcome for general qualifiers path includes rdf:parseType="Resource".
  EXPECT_NE(out.find("rdf:parseType=\"Resource\""), std::string::npos);

  // It should still emit the property element start/end for ns:Prop somewhere.
  EXPECT_NE(out.find("<ns:Prop"), std::string::npos);
  EXPECT_NE(out.find("</ns:Prop>" + std::string(kNL)), std::string::npos);
}

TEST_F(SerializeCompactRDFElemPropsTest_2113, IndentationAppliedForNonZeroIndent_2113) {
  XMP_Node* root = arena_.MakeNode(nullptr, "root", 0);

  XMP_Node* p = arena_.MakeNode(root, "ns:Title", "Hello", 0);
  root->children.push_back(p);

  const std::string out = SerializeChildrenOf(root, /*indent=*/2);

  // With indent=2 and indentStr="  ", the element line should start with 4 spaces.
  EXPECT_TRUE(out.rfind("    <ns:Title", 0) == 0);
}

}  // namespace