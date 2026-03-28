// =================================================================================================
// UNIT TESTS: SerializePrettyRDFProperty (TEST_ID = 2110)
// File under test: ./TestProjects/exiv2/xmpsdk/src/XMPMeta-Serialize.cpp
// =================================================================================================

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>
#include <string>
#include <vector>

// Pull in XMP SDK core types/options/errors.
#include "XMP_Const.h"
#include "XMPCore_Impl.hpp"

// IMPORTANT:
// SerializePrettyRDFProperty is a `static` function inside XMPMeta-Serialize.cpp.
// To test it as a black box while still calling it, we include the .cpp into this test TU.
#include "XMPMeta-Serialize.cpp"

namespace {

using ::testing::HasSubstr;
using ::testing::Not;

class SerializePrettyRDFPropertyTest_2110 : public ::testing::Test {
protected:
  // Owning storage for nodes created in a test, to avoid leaks regardless of XMP_Node internals.
  std::vector<std::unique_ptr<XMP_Node>> owned_;

  XMP_Node* NewNode(XMP_Node* parent, const char* name, const char* value, XMP_OptionBits options) {
    owned_.push_back(std::make_unique<XMP_Node>(parent, name, value, options));
    return owned_.back().get();
  }
  XMP_Node* NewNode(XMP_Node* parent, const char* name, XMP_OptionBits options) {
    owned_.push_back(std::make_unique<XMP_Node>(parent, name, options));
    return owned_.back().get();
  }

  static std::string RunSerialize(const XMP_Node* node,
                                  const char* newline = "\n",
                                  const char* indentStr = "  ",
                                  XMP_Index indent = 0,
                                  bool emitAsRDFValue = false) {
    XMP_VarString out;
    SerializePrettyRDFProperty(node, out, newline, indentStr, indent, emitAsRDFValue);
    return out;
  }
};

TEST_F(SerializePrettyRDFPropertyTest_2110, SerializesSimpleLiteralElement_2110) {
  XMP_Node* prop = NewNode(nullptr, "dc:title", "Hello", 0);

  const std::string out = RunSerialize(prop);

  // Observable behavior: emits an element with content and end tag, followed by newline.
  EXPECT_THAT(out, HasSubstr("<dc:title>"));
  EXPECT_THAT(out, HasSubstr("Hello"));
  EXPECT_THAT(out, HasSubstr("</dc:title>\n"));
}

TEST_F(SerializePrettyRDFPropertyTest_2110, SerializesEmptyValueAsSelfClosing_2110) {
  XMP_Node* prop = NewNode(nullptr, "dc:creator", "", 0);

  const std::string out = RunSerialize(prop);

  // Empty value -> self closing element.
  EXPECT_THAT(out, HasSubstr("<dc:creator/>"));
  EXPECT_THAT(out, HasSubstr("\n"));
  EXPECT_THAT(out, Not(HasSubstr("</dc:creator>")));
}

TEST_F(SerializePrettyRDFPropertyTest_2110, SerializesURIValueAsRdfResourceAttribute_2110) {
  XMP_Node* prop = NewNode(nullptr, "xmp:Identifier", "http://example.com/id", kXMP_PropValueIsURI);

  const std::string out = RunSerialize(prop);

  // URI -> rdf:resource="..."/> and no end tag.
  EXPECT_THAT(out, HasSubstr("<xmp:Identifier"));
  EXPECT_THAT(out, HasSubstr("rdf:resource=\""));
  EXPECT_THAT(out, HasSubstr("http://example.com/id"));
  EXPECT_THAT(out, HasSubstr("\"/>"));
  EXPECT_THAT(out, Not(HasSubstr("</xmp:Identifier>")));
}

TEST_F(SerializePrettyRDFPropertyTest_2110, UsesRdfLiForBracketChildNames_2110) {
  // Parent is an unordered array with one child named "[1]" (serialized as rdf:li).
  XMP_Node* arrayProp = NewNode(nullptr, "dc:subject", kXMP_PropValueIsArray | kXMP_PropArrayIsUnordered);
  XMP_Node* child = NewNode(arrayProp, "[1]", "TagA", 0);
  arrayProp->children.push_back(child);

  const std::string out = RunSerialize(arrayProp);

  // We don't assert the exact array container tags (implementation detail),
  // but we DO assert the observable behavior for bracket child name -> <rdf:li>.
  EXPECT_THAT(out, HasSubstr("<rdf:li>"));
  EXPECT_THAT(out, HasSubstr("TagA"));
  EXPECT_THAT(out, HasSubstr("</rdf:li>\n"));
}

TEST_F(SerializePrettyRDFPropertyTest_2110, SerializesStructWithoutChildrenAsParseTypeResourceSelfClosing_2110) {
  XMP_Node* st = NewNode(nullptr, "ex:Struct", "", kXMP_PropValueIsStruct);

  const std::string out = RunSerialize(st);

  EXPECT_THAT(out, HasSubstr("<ex:Struct"));
  EXPECT_THAT(out, HasSubstr("rdf:parseType=\"Resource\"/>"));
  EXPECT_THAT(out, HasSubstr("\n"));
  EXPECT_THAT(out, Not(HasSubstr("</ex:Struct>")));
}

TEST_F(SerializePrettyRDFPropertyTest_2110, ThrowsWhenMixingRdfResourceAndGeneralQualifiers_2110) {
  // General qualifier: not an RDF attribute qualifier.
  XMP_Node* prop = NewNode(nullptr, "ex:Prop", "V", kXMP_PropHasQualifiers);

  XMP_Node* rdfRes = NewNode(prop, "rdf:resource", "http://example.com/res", kXMP_PropIsQualifier);
  XMP_Node* genQual = NewNode(prop, "ex:qual", "QV", kXMP_PropIsQualifier);

  prop->qualifiers.push_back(rdfRes);
  prop->qualifiers.push_back(genQual);

  // Observable behavior: throws (error code detail/type is SDK-specific, so we keep it generic).
  EXPECT_ANY_THROW((void)RunSerialize(prop));
}

TEST_F(SerializePrettyRDFPropertyTest_2110, ThrowsWhenRdfResourceAndComplexChildFieldMixed_2110) {
  // Struct with rdf:resource qualifier and a complex (array) child should throw.
  XMP_Node* prop = NewNode(nullptr, "ex:StructWithRes", "", kXMP_PropValueIsStruct | kXMP_PropHasQualifiers);

  XMP_Node* rdfRes = NewNode(prop, "rdf:resource", "http://example.com/res", kXMP_PropIsQualifier);
  prop->qualifiers.push_back(rdfRes);

  // Complex child: array child (not an attribute property).
  XMP_Node* complexChild = NewNode(prop, "ex:childArray", "", kXMP_PropValueIsArray | kXMP_PropArrayIsOrdered);
  prop->children.push_back(complexChild);

  EXPECT_ANY_THROW((void)RunSerialize(prop));
}

TEST_F(SerializePrettyRDFPropertyTest_2110, EmitsIndentationAtRequestedLevel_2110) {
  XMP_Node* prop = NewNode(nullptr, "dc:description", "Text", 0);

  const std::string out = RunSerialize(prop, "\n", " ", /*indent=*/3);

  // Should start with 3 indentStr copies (3 spaces) then '<'.
  ASSERT_GE(out.size(), size_t(4));
  EXPECT_EQ(out[0], ' ');
  EXPECT_EQ(out[1], ' ');
  EXPECT_EQ(out[2], ' ');
  EXPECT_EQ(out[3], '<');
}

}  // namespace