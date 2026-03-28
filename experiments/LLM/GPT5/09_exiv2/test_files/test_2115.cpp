// =================================================================================================
// TEST_ID 2115
// Unit tests for SerializeAsRDF (./TestProjects/exiv2/xmpsdk/src/XMPMeta-Serialize.cpp)
// =================================================================================================

#include <gtest/gtest.h>

#include <cstring>
#include <string>

// Pull in core SDK types.
#include "TestProjects/exiv2/xmpsdk/src/XMPCore_Impl.hpp"
#include "TestProjects/exiv2/xmpsdk/src/XMPMeta.hpp"
#include "TestProjects/exiv2/xmpsdk/include/XMP_Const.h"

// IMPORTANT:
// SerializeAsRDF is a file-scope static function in XMPMeta-Serialize.cpp.
// Including the .cpp brings the function into this test translation unit so it can be called.
#include "TestProjects/exiv2/xmpsdk/src/XMPMeta-Serialize.cpp"

namespace {

// A tiny helper to reduce repetition.
static void CallSerializeAsRDF(const XMPMeta& xmp,
                              std::string& head,
                              std::string& tail,
                              XMP_OptionBits options,
                              const char* newline,
                              const char* indent,
                              XMP_Index baseIndent) {
  SerializeAsRDF(xmp, head, tail, options, newline, indent, baseIndent);
}

static bool Contains(const std::string& s, const char* needle) {
  return s.find(needle) != std::string::npos;
}

}  // namespace

class SerializeAsRDFTest_2115 : public ::testing::Test {};

TEST_F(SerializeAsRDFTest_2115, DefaultIncludesPacketWrapperAndXMPMetaAndRDFMarkers_2115) {
  XMPMeta xmp;
  xmp.SetObjectName("testObject");

  std::string head = "PREHEAD";
  std::string tail = "PRETAIL";

  CallSerializeAsRDF(xmp, head, tail, /*options*/ 0, "\n", "  ", /*baseIndent*/ 0);

  // Head: should contain packet header and RDF wrapper markers.
  EXPECT_TRUE(Contains(head, kPacketHeader));
  EXPECT_TRUE(Contains(head, kRDF_XMPMetaStart));
  EXPECT_TRUE(Contains(head, kRDF_RDFStart));
  EXPECT_TRUE(Contains(head, kRDF_RDFEnd));
  EXPECT_TRUE(Contains(head, kRDF_XMPMetaEnd));

  // Tail: should contain packet trailer (default end="w").
  EXPECT_TRUE(Contains(tail, kPacketTrailer));
  EXPECT_TRUE(Contains(tail, "end=\"w\""));

  // The function should erase and rebuild, not append to previous content.
  EXPECT_NE(head.find("PREHEAD"), 0u);
  EXPECT_EQ(head.find("PREHEAD"), std::string::npos);
  EXPECT_EQ(tail.find("PRETAIL"), std::string::npos);
}

TEST_F(SerializeAsRDFTest_2115, OmitPacketWrapperProducesNoHeaderAndEmptyTail_2115) {
  XMPMeta xmp;
  xmp.SetObjectName("obj");

  std::string head;
  std::string tail;

  CallSerializeAsRDF(xmp, head, tail, kXMP_OmitPacketWrapper, "\n", "  ", /*baseIndent*/ 0);

  EXPECT_FALSE(Contains(head, kPacketHeader));
  EXPECT_TRUE(Contains(head, kRDF_RDFStart));
  EXPECT_TRUE(Contains(head, kRDF_RDFEnd));

  // Tail should be cleared and remain empty when packet wrapper is omitted.
  EXPECT_TRUE(tail.empty());
}

TEST_F(SerializeAsRDFTest_2115, ReadOnlyPacketChangesTrailerToEndR_2115) {
  XMPMeta xmp;
  xmp.SetObjectName("obj");

  std::string head;
  std::string tail;

  CallSerializeAsRDF(xmp, head, tail, kXMP_ReadOnlyPacket, "\n", "  ", /*baseIndent*/ 0);

  EXPECT_TRUE(Contains(tail, kPacketTrailer));
  EXPECT_TRUE(Contains(tail, "end=\"r\""));
  EXPECT_FALSE(Contains(tail, "end=\"w\""));
}

TEST_F(SerializeAsRDFTest_2115, OmitXMPMetaElementRemovesXmpmetaStartAndEndButKeepsRDF_2115) {
  XMPMeta xmp;
  xmp.SetObjectName("obj");

  std::string head;
  std::string tail;

  CallSerializeAsRDF(xmp, head, tail, kXMP_OmitXMPMetaElement, "\n", "  ", /*baseIndent*/ 0);

  EXPECT_FALSE(Contains(head, kRDF_XMPMetaStart));
  EXPECT_FALSE(Contains(head, kRDF_XMPMetaEnd));
  EXPECT_TRUE(Contains(head, kRDF_RDFStart));
  EXPECT_TRUE(Contains(head, kRDF_RDFEnd));

  // Packet wrapper still present by default.
  EXPECT_TRUE(Contains(head, kPacketHeader));
  EXPECT_TRUE(Contains(tail, kPacketTrailer));
}

TEST_F(SerializeAsRDFTest_2115, EmptyObjectPrettyModeEmitsSelfClosingDescriptionWithObjectName_2115) {
  XMPMeta xmp;
  xmp.SetObjectName("emptyName");

  std::string head;
  std::string tail;

  // Ensure pretty mode (no kXMP_UseCompactFormat) and no schemas (fresh object).
  CallSerializeAsRDF(xmp, head, tail, /*options*/ 0, "\n", "  ", /*baseIndent*/ 0);

  // Special-case should serialize an empty XMP object as a self-closing Description.
  EXPECT_TRUE(Contains(head, kRDF_SchemaStart));
  EXPECT_TRUE(Contains(head, "rdf:about=\"emptyName\"/>"));
}

TEST_F(SerializeAsRDFTest_2115, NonEmptyObjectPrettyModeIncludesDescriptionEndTag_2115) {
  XMPMeta xmp;
  xmp.SetObjectName("objWithProp");

  // Add at least one property to create schema content.
  xmp.SetProperty("http://ns.adobe.com/xap/1.0/", "CreatorTool", "UnitTest", /*options*/ 0);

  std::string head;
  std::string tail;

  CallSerializeAsRDF(xmp, head, tail, /*options*/ 0, "\n", "  ", /*baseIndent*/ 0);

  // In non-empty case, pretty schema serialization should (at minimum) include a Description end tag.
  EXPECT_TRUE(Contains(head, kRDF_RDFStart));
  EXPECT_TRUE(Contains(head, kRDF_RDFEnd));
  EXPECT_TRUE(Contains(head, kRDF_SchemaEnd));
}

TEST_F(SerializeAsRDFTest_2115, CompactFormatStillProducesRDFWrapperMarkers_2115) {
  XMPMeta xmp;
  xmp.SetObjectName("obj");
  xmp.SetProperty("http://ns.adobe.com/xap/1.0/", "CreatorTool", "UnitTest", /*options*/ 0);

  std::string head;
  std::string tail;

  CallSerializeAsRDF(xmp, head, tail, kXMP_UseCompactFormat, "\n", "  ", /*baseIndent*/ 0);

  // Compact vs pretty affects internal formatting, but wrapper markers should remain.
  EXPECT_TRUE(Contains(head, kRDF_RDFStart));
  EXPECT_TRUE(Contains(head, kRDF_RDFEnd));
}

TEST_F(SerializeAsRDFTest_2115, BaseIndentAppliesToPacketHeaderIndentation_2115) {
  XMPMeta xmp;
  xmp.SetObjectName("obj");

  std::string head;
  std::string tail;

  CallSerializeAsRDF(xmp, head, tail, /*options*/ 0, "\n", " ", /*baseIndent*/ 3);

  // Packet header should be preceded by baseIndent copies of indentStr (" ").
  // We verify by checking for "\n" then three spaces then header, OR beginning with spaces then header.
  // (If baseIndent>0, SerializeAsRDF emits indentation then header then newline).
  const std::string expectedPrefix = std::string(3, ' ') + std::string(kPacketHeader);
  EXPECT_NE(head.find(expectedPrefix), std::string::npos);
}

TEST_F(SerializeAsRDFTest_2115, EmptyIndentAndEmptyNewlineAreHandled_2115) {
  XMPMeta xmp;
  xmp.SetObjectName("obj");

  std::string head;
  std::string tail;

  CallSerializeAsRDF(xmp, head, tail, /*options*/ 0, /*newline*/ "", /*indent*/ "", /*baseIndent*/ 2);

  // With empty indent/newline, output should still contain core markers.
  EXPECT_TRUE(Contains(head, kPacketHeader));
  EXPECT_TRUE(Contains(head, kRDF_RDFStart));
  EXPECT_TRUE(Contains(head, kRDF_RDFEnd));
  EXPECT_TRUE(Contains(tail, kPacketTrailer));
}