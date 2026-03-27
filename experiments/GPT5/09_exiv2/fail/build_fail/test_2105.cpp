// =================================================================================================
// TEST_ID: 2105
// Unit tests for static DeclareElemNamespace in XMPMeta-Serialize.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <string>

// We include the implementation file directly so the `static` function is visible to this TU.
// This is a common approach for testing file-local helpers.
#include "TestProjects/exiv2/xmpsdk/src/XMPMeta-Serialize.cpp"

namespace {

class DeclareElemNamespaceTest_2105 : public ::testing::Test {
protected:
  XMP_StringMap* savedMap_ = nullptr;

  void SetUp() override {
    savedMap_ = ::sNamespacePrefixToURIMap;

    // Use an isolated map for these tests to avoid coupling to any global initialization order.
    ::sNamespacePrefixToURIMap = new XMP_StringMap();

    // Add a well-known mapping we can assert against.
    // NOTE: DeclareElemNamespace uses prefix including trailing ':' (e.g., "dc:").
    (*::sNamespacePrefixToURIMap)[XMP_VarString("dc:")] =
        XMP_VarString("http://purl.org/dc/elements/1.1/");
    (*::sNamespacePrefixToURIMap)[XMP_VarString("xmp:")] =
        XMP_VarString("http://ns.adobe.com/xap/1.0/");
  }

  void TearDown() override {
    delete ::sNamespacePrefixToURIMap;
    ::sNamespacePrefixToURIMap = savedMap_;
  }
};

TEST_F(DeclareElemNamespaceTest_2105, NoColonDoesNothing_2105) {
  XMP_VarString usedNS("USED");
  XMP_VarString outputStr("OUT");

  const XMP_StringPtr newline = "\n";
  const XMP_StringPtr indentStr = "  ";
  const XMP_Index indent = 2;

  EXPECT_NO_THROW(DeclareElemNamespace(XMP_VarString("NoPrefixElement"), usedNS, outputStr,
                                       newline, indentStr, indent));

  EXPECT_EQ(usedNS, "USED");
  EXPECT_EQ(outputStr, "OUT");
}

TEST_F(DeclareElemNamespaceTest_2105, KnownPrefixAppendsDeclaration_2105) {
  XMP_VarString usedNS;
  XMP_VarString outputStr;

  const XMP_StringPtr newline = "\n";
  const XMP_StringPtr indentStr = " ";
  const XMP_Index indent = 0;

  EXPECT_NO_THROW(DeclareElemNamespace(XMP_VarString("dc:title"), usedNS, outputStr,
                                       newline, indentStr, indent));

  // Black-box observable behavior: something should be emitted when a known prefix is used.
  EXPECT_FALSE(outputStr.empty());

  // Keep assertions intentionally loose to avoid relying on exact formatting.
  EXPECT_NE(outputStr.find("dc"), XMP_VarString::npos);
  EXPECT_NE(outputStr.find("http://purl.org/dc/elements/1.1/"), XMP_VarString::npos);
}

TEST_F(DeclareElemNamespaceTest_2105, ColonAtEndIsTreatedAsPrefix_2105) {
  XMP_VarString usedNS;
  XMP_VarString outputStr;

  const XMP_StringPtr newline = "\n";
  const XMP_StringPtr indentStr = "  ";
  const XMP_Index indent = 1;

  // elemName "xmp:" still has a prefix "xmp:" (including ':') and should resolve.
  EXPECT_NO_THROW(DeclareElemNamespace(XMP_VarString("xmp:"), usedNS, outputStr,
                                       newline, indentStr, indent));

  EXPECT_FALSE(outputStr.empty());
  EXPECT_NE(outputStr.find("xmp"), XMP_VarString::npos);
  EXPECT_NE(outputStr.find("http://ns.adobe.com/xap/1.0/"), XMP_VarString::npos);
}

TEST_F(DeclareElemNamespaceTest_2105, UnknownPrefixThrows_2105) {
  XMP_VarString usedNS("before");
  XMP_VarString outputStr("before");

  const XMP_StringPtr newline = "\n";
  const XMP_StringPtr indentStr = "  ";
  const XMP_Index indent = 0;

  // The implementation enforces that the prefix exists in sNamespacePrefixToURIMap.
  EXPECT_ANY_THROW(DeclareElemNamespace(XMP_VarString("unknown:elem"), usedNS, outputStr,
                                       newline, indentStr, indent));
}

TEST_F(DeclareElemNamespaceTest_2105, PrefixExtractionUsesSubstringUpToAndIncludingColon_2105) {
  // Boundary-ish case: ensure it looks up exactly "<prefix>:" not just "<prefix>".
  // We only register "dc:"; if the function looked up "dc" (without ':'), it would fail.
  XMP_VarString usedNS;
  XMP_VarString outputStr;

  const XMP_StringPtr newline = "\n";
  const XMP_StringPtr indentStr = " ";
  const XMP_Index indent = 0;

  EXPECT_NO_THROW(DeclareElemNamespace(XMP_VarString("dc:creator"), usedNS, outputStr,
                                       newline, indentStr, indent));
  EXPECT_FALSE(outputStr.empty());
  EXPECT_NE(outputStr.find("http://purl.org/dc/elements/1.1/"), XMP_VarString::npos);
}

}  // namespace