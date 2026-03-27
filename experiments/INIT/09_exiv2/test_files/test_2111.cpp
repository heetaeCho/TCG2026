// =================================================================================================
// TEST_ID: 2111
// Unit tests for SerializePrettyRDFSchema (black-box via included .cpp TU)
// =================================================================================================

#include <gtest/gtest.h>

#include <string>
#include <map>

// Pull in core XMP SDK types / constants used by the function.
#include "TestProjects/exiv2/xmpsdk/include/XMP_Const.h"
#include "TestProjects/exiv2/xmpsdk/src/XMPCore_Impl.hpp"

// Include the implementation file so we can call the TU-local static function.
// (This is intentional: SerializePrettyRDFSchema is `static` in XMPMeta-Serialize.cpp.)
#include "TestProjects/exiv2/xmpsdk/src/XMPMeta-Serialize.cpp"

namespace {

class SerializePrettyRDFSchemaTest_2111 : public ::testing::Test {
protected:
  using StringMap = XMP_StringMap;

  void SetUp() override {
    savedMapPtr_ = ::sNamespacePrefixToURIMap;

    // Ensure the global pointer used by SerializePrettyRDFSchema is non-null and deterministic.
    // Keep it empty to minimize any output variability from namespace declarations.
    ::sNamespacePrefixToURIMap = &localMap_;
  }

  void TearDown() override {
    ::sNamespacePrefixToURIMap = savedMapPtr_;
  }

private:
  StringMap localMap_{};
  StringMap* savedMapPtr_ = nullptr;
};

TEST_F(SerializePrettyRDFSchemaTest_2111, EmptySchemaChildren_ContainsSchemaStartTreeNameAndEnd_2111) {
  // Arrange
  XMP_Node schema(/*parent*/ nullptr, /*name*/ "schema", /*options*/ kXMP_SchemaNode);
  ASSERT_TRUE(schema.qualifiers.empty());
  ASSERT_TRUE(schema.children.empty());

  const XMP_VarString treeName = "TestTree";
  XMP_VarString output;
  const XMP_OptionBits options = 0;
  const XMP_StringPtr newline = "\n";
  const XMP_StringPtr indentStr = "  ";  // 2 spaces
  const XMP_Index baseIndent = 0;

  // Act
  SerializePrettyRDFSchema(treeName, &schema, output, options, newline, indentStr, baseIndent);

  // Assert (avoid asserting full string; only observable stable fragments)
  // Leading indentation: (baseIndent + 2) repetitions of indentStr.
  const std::string expectedPrefix = std::string("  ") + std::string("  "); // 4 spaces total
  ASSERT_GE(output.size(), expectedPrefix.size());
  EXPECT_EQ(output.substr(0, expectedPrefix.size()), expectedPrefix);

  // Must contain schema start and tree name inside quotes right after rdf:about=
  EXPECT_NE(output.find(std::string(kRDF_SchemaStart) + "\"" + treeName + "\""), std::string::npos);

  // Must close the rdf:Description and end with newline appended by the function.
  EXPECT_NE(output.rfind(kRDF_SchemaEnd), std::string::npos);
  EXPECT_TRUE(!output.empty());
  EXPECT_EQ(output.back(), '\n');

  // There is always a '>' and then newline after namespace declarations.
  EXPECT_NE(output.find(std::string(">\n")), std::string::npos);
}

TEST_F(SerializePrettyRDFSchemaTest_2111, BaseIndentAffectsLeadingIndentation_2111) {
  // Arrange
  XMP_Node schema(/*parent*/ nullptr, /*name*/ "schema", /*options*/ kXMP_SchemaNode);
  ASSERT_TRUE(schema.qualifiers.empty());
  ASSERT_TRUE(schema.children.empty());

  const XMP_VarString treeName = "Tree";
  const XMP_StringPtr newline = "\n";
  const XMP_StringPtr indentStr = "\t";
  const XMP_OptionBits options = 0;

  // Act
  XMP_VarString out0;
  SerializePrettyRDFSchema(treeName, &schema, out0, options, newline, indentStr, /*baseIndent*/ 0);

  XMP_VarString out3;
  SerializePrettyRDFSchema(treeName, &schema, out3, options, newline, indentStr, /*baseIndent*/ 3);

  // Assert
  // Leading indentation is repeated (baseIndent + 2) times.
  const std::string prefix0(2, '\t');
  const std::string prefix3(5, '\t');

  ASSERT_GE(out0.size(), prefix0.size());
  ASSERT_GE(out3.size(), prefix3.size());

  EXPECT_EQ(out0.substr(0, prefix0.size()), prefix0);
  EXPECT_EQ(out3.substr(0, prefix3.size()), prefix3);

  // Both should contain schema markers.
  EXPECT_NE(out0.find(kRDF_SchemaStart), std::string::npos);
  EXPECT_NE(out3.find(kRDF_SchemaStart), std::string::npos);
  EXPECT_NE(out0.find(kRDF_SchemaEnd), std::string::npos);
  EXPECT_NE(out3.find(kRDF_SchemaEnd), std::string::npos);
}

TEST_F(SerializePrettyRDFSchemaTest_2111, EmptyTreeNameAndNoFormatting_DoesNotCrashAndHasQuotedAbout_2111) {
  // Arrange
  XMP_Node schema(/*parent*/ nullptr, /*name*/ "schema", /*options*/ kXMP_SchemaNode);
  ASSERT_TRUE(schema.qualifiers.empty());
  ASSERT_TRUE(schema.children.empty());

  const XMP_VarString treeName;  // empty
  XMP_VarString output;
  const XMP_OptionBits options = 0;
  const XMP_StringPtr newline = "";     // no newline
  const XMP_StringPtr indentStr = "";   // no indentation
  const XMP_Index baseIndent = 0;

  // Act
  SerializePrettyRDFSchema(treeName, &schema, output, options, newline, indentStr, baseIndent);

  // Assert
  // Should still have rdf:about="" (quotes are explicitly added by the function).
  EXPECT_NE(output.find(std::string(kRDF_SchemaStart) + "\"\""), std::string::npos);

  // Should contain closing tag even without newline.
  EXPECT_NE(output.find(kRDF_SchemaEnd), std::string::npos);
}

TEST_F(SerializePrettyRDFSchemaTest_2111, WriteAliasCommentsOption_DoesNotChangeOutputWithEmptySchema_2111) {
  // Arrange
  XMP_Node schema(/*parent*/ nullptr, /*name*/ "schema", /*options*/ kXMP_SchemaNode);
  ASSERT_TRUE(schema.qualifiers.empty());
  ASSERT_TRUE(schema.children.empty());

  const XMP_VarString treeName = "Tree";
  const XMP_StringPtr newline = "\n";
  const XMP_StringPtr indentStr = " ";
  const XMP_Index baseIndent = 1;

  XMP_VarString outNoOpt;
  XMP_VarString outWithOpt;

  // Act
  SerializePrettyRDFSchema(treeName, &schema, outNoOpt, /*options*/ 0, newline, indentStr, baseIndent);
  SerializePrettyRDFSchema(treeName, &schema, outWithOpt, /*options*/ kXMP_WriteAliasComments,
                           newline, indentStr, baseIndent);

  // Assert
  // The alias-comment block in the provided code is effectively disabled (#if 0),
  // so for an otherwise empty schema the serialized output should match.
  EXPECT_EQ(outNoOpt, outWithOpt);
}

}  // namespace