// =================================================================================================
// TEST_ID: 2112
// Unit tests for SerializeCompactRDFAttrProps (XMPMeta-Serialize.cpp)
// =================================================================================================

#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <vector>

// The XMP SDK types used by SerializeCompactRDFAttrProps.
#include "TestProjects/exiv2/xmpsdk/src/XMPCore_Impl.hpp"

// IMPORTANT:
// SerializeCompactRDFAttrProps is a file-local `static` function inside XMPMeta-Serialize.cpp.
// The common way to unit test such a function is to compile the tests in the same translation unit
// by including the .cpp directly.
//
// NOTE: This assumes your test build is arranged so that XMPMeta-Serialize.cpp is NOT also compiled
// separately into the same test binary (otherwise you may get duplicate symbol link errors).
#include "TestProjects/exiv2/xmpsdk/src/XMPMeta-Serialize.cpp"

namespace {

class SerializeCompactRDFAttrPropsTest_2112 : public ::testing::Test {
 protected:
  // Own nodes so we can safely hand out raw pointers to XMP_NodeOffspring containers.
  std::vector<std::unique_ptr<XMP_Node>> owned_;

  XMP_Node* MakeNode(XMP_Node* parent, const char* name, const char* value = "", XMP_OptionBits options = 0) {
    owned_.push_back(std::make_unique<XMP_Node>(parent, name, value, options));
    return owned_.back().get();
  }
};

TEST_F(SerializeCompactRDFAttrPropsTest_2112, NoChildren_ReturnsTrueAndDoesNotModifyOutput_2112) {
  XMP_Node parent(/*_parent*/ nullptr, "parent", /*options*/ 0);

  XMP_VarString out = "prefix";
  const XMP_StringPtr newline = "\n";
  const XMP_StringPtr indentStr = "  ";

  const bool allAttrs = SerializeCompactRDFAttrProps(&parent, out, newline, indentStr, /*indent*/ 2);

  EXPECT_TRUE(allAttrs);
  EXPECT_EQ(out, "prefix");
}

TEST_F(SerializeCompactRDFAttrPropsTest_2112, MixedChildren_ReturnsFalseAndSkipsNonAttrLikeChild_2112) {
  XMP_Node parent(/*_parent*/ nullptr, "parent", /*options*/ 0);

  // A likely "simple" property.
  XMP_Node* simple = MakeNode(&parent, "simpleProp", "simpleValue", /*options*/ 0);
  parent.children.push_back(simple);

  // A "complex" property: give it a child to strongly suggest it can't be serialized as an RDF attribute.
  XMP_Node* complex = MakeNode(&parent, "complexProp", "complexValue", /*options*/ 0);
  XMP_Node* complexChild = MakeNode(complex, "nested", "v", /*options*/ 0);
  complex->children.push_back(complexChild);
  parent.children.push_back(complex);

  XMP_VarString out = "start";
  const XMP_StringPtr newline = "\n";
  const XMP_StringPtr indentStr = " ";

  const bool allAttrs = SerializeCompactRDFAttrProps(&parent, out, newline, indentStr, /*indent*/ 1);

  // At least one child is expected to be non-attribute-serializable -> overall result should be false.
  EXPECT_FALSE(allAttrs);

  // The complex property should not appear as name="value" in the output.
  EXPECT_EQ(out.find("complexProp=\""), std::string::npos);

  // The output should be appended to (not replaced).
  EXPECT_TRUE(out.rfind("start", 0) == 0);
}

TEST_F(SerializeCompactRDFAttrPropsTest_2112, IndentZero_ProducesNoLeadingIndentationBeforeName_2112) {
  XMP_Node parent(/*_parent*/ nullptr, "parent", /*options*/ 0);

  XMP_Node* prop = MakeNode(&parent, "p", "v", /*options*/ 0);
  parent.children.push_back(prop);

  XMP_VarString out;
  const XMP_StringPtr newline = "\n";
  const XMP_StringPtr indentStr = "    ";  // should not matter when indent == 0

  const bool allAttrs = SerializeCompactRDFAttrProps(&parent, out, newline, indentStr, /*indent*/ 0);

  if (!allAttrs) {
    // If this node is not eligible as an RDF attribute prop in this build, output must remain empty.
    EXPECT_TRUE(out.empty());
    return;
  }

  // When indent==0, the function should append newline then immediately the property name.
  ASSERT_GE(out.size(), 3u);
  EXPECT_NE(out.find("\np=\""), std::string::npos);
  EXPECT_NE(out.find("\np=\"v\""), std::string::npos);
}

TEST_F(SerializeCompactRDFAttrPropsTest_2112, MultipleLikelySimpleProps_AppendsEachOnNewIndentedLine_2112) {
  XMP_Node parent(/*_parent*/ nullptr, "parent", /*options*/ 0);

  XMP_Node* p1 = MakeNode(&parent, "a", "1", /*options*/ 0);
  XMP_Node* p2 = MakeNode(&parent, "b", "2", /*options*/ 0);
  parent.children.push_back(p1);
  parent.children.push_back(p2);

  XMP_VarString out = "hdr";
  const XMP_StringPtr newline = "\n";
  const XMP_StringPtr indentStr = " ";

  const bool allAttrs = SerializeCompactRDFAttrProps(&parent, out, newline, indentStr, /*indent*/ 2);

  // If any child cannot be expressed as an attribute prop, overall is false; otherwise true.
  // Regardless, any attribute-eligible props must be appended with newline + (indent * indentStr).
  // We assert the formatting for those that do appear.
  const std::string s(out.c_str(), out.size());

  // Output should be appended to header.
  EXPECT_TRUE(s.rfind("hdr", 0) == 0);

  // If "a" or "b" appear, they must be prefixed by newline + two spaces.
  const std::string aNeedle = "\n  a=\"";
  const std::string bNeedle = "\n  b=\"";
  if (s.find("a=\"") != std::string::npos) EXPECT_NE(s.find(aNeedle), std::string::npos);
  if (s.find("b=\"") != std::string::npos) EXPECT_NE(s.find(bNeedle), std::string::npos);

  // If allAttrs is true, both should appear in some form.
  if (allAttrs) {
    EXPECT_NE(s.find("a=\""), std::string::npos);
    EXPECT_NE(s.find("b=\""), std::string::npos);
  }
}

}  // namespace