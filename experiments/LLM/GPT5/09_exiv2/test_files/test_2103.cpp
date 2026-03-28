// =================================================================================================
// TEST_ID: 2103
// Unit tests for internal GetNextXMPNode (XMPIterator.cpp)
// =================================================================================================

#include <gtest/gtest.h>

#include <string>

// XMP SDK headers (as present in the project tree).
#include "TestProjects/exiv2/xmpsdk/src/XMPMeta.hpp"
#include "TestProjects/exiv2/xmpsdk/include/XMP_Const.h"
#include "TestProjects/exiv2/xmpsdk/include/XMP.hpp"

// Pull the implementation into this TU so we can exercise the internal static function.
// NOTE: These tests treat GetNextXMPNode as a black box: assertions are only about observable
// return values and public fields on IterInfo/IterNode.
#include "TestProjects/exiv2/xmpsdk/src/XMPIterator.cpp"

namespace {

class GetNextXMPNodeTest_2103 : public ::testing::Test {
public:
  static void SetUpTestSuite() {
    // Many XMP SDK builds require global init before using XMPMeta.
    XMPMeta::Initialize();
  }

  static void TearDownTestSuite() { XMPMeta::Terminate(); }

protected:
  static constexpr XMP_StringPtr kXmpNS = "http://ns.adobe.com/xap/1.0/";
  static constexpr XMP_StringPtr kDcNS  = "http://purl.org/dc/elements/1.1/";

  static IterNode MakeSchemaIterNode(XMP_StringPtr schemaNS) {
    // Mark as schema node using the schema-node option bit.
    // This is part of the XMP SDK option bits and should be stable.
    return IterNode(kXMP_SchemaNode, std::string(schemaNS), /*leafOffset*/ 0);
  }

  static IterNode MakePropIterNode(const std::string& propPath) {
    // Non-schema node => options=0.
    return IterNode(/*options*/ 0, propPath, /*leafOffset*/ 0);
  }

  static void AttachIterList(IterInfo& info, IterOffspring& list) {
    // Point the iterator positions at the provided list.
    info.currPos = list.begin();
    info.endPos  = list.end();
  }
};

// -------------------------------------------------------------------------------------------------

TEST_F(GetNextXMPNodeTest_2103, ReturnsNullWhenCurrPosEqualsEndPos_2103) {
  XMPMeta xmp;
  IterInfo info(/*options*/ 0, &xmp);

  // Empty list => begin == end.
  IterOffspring empty;
  AttachIterList(info, empty);

  const XMP_Node* node = GetNextXMPNode(info);
  EXPECT_EQ(node, nullptr);
}

// -------------------------------------------------------------------------------------------------

TEST_F(GetNextXMPNodeTest_2103, MissingSchemaYieldsDummySchemaAndMarksVisitSelf_2103) {
  XMPMeta xmp;
  IterInfo info(/*options*/ 0, &xmp);

  IterOffspring seq;
  seq.emplace_back(MakeSchemaIterNode(kDcNS));
  AttachIterList(info, seq);

  ASSERT_NE(info.currPos, info.endPos);
  ASSERT_EQ(info.currPos->visitStage, kIter_BeforeVisit);

  const XMP_Node* node = GetNextXMPNode(info);

  // Observable behavior: non-null return (dummy schema) when schema isn't present.
  ASSERT_NE(node, nullptr);

  // The implementation uses a global dummy schema pointer for missing schemas.
  // We only compare against the published global variable in this TU.
  EXPECT_EQ(node, sDummySchema);

  // Observable state transition on public struct: stage should be "visit self".
  EXPECT_EQ(info.currPos->visitStage, kIter_VisitSelf);

  // And the current schema string should be set to the schema fullPath.
  EXPECT_EQ(info.currSchema, std::string(kDcNS));
}

// -------------------------------------------------------------------------------------------------

TEST_F(GetNextXMPNodeTest_2103, ExistingSchemaReturnsLiveSchemaNodeNotDummy_2103) {
  XMPMeta xmp;
  // Create a live schema by setting a property in that namespace.
  xmp.SetProperty(kXmpNS, "CreatorTool", "unit-test", 0);

  IterInfo info(/*options*/ 0, &xmp);

  IterOffspring seq;
  seq.emplace_back(MakeSchemaIterNode(kXmpNS));
  AttachIterList(info, seq);

  const XMP_Node* node = GetNextXMPNode(info);
  ASSERT_NE(node, nullptr);

  // If the schema exists, it should not fall back to the dummy schema.
  EXPECT_NE(node, sDummySchema);

  // Public state transition should still move to VisitSelf.
  EXPECT_EQ(info.currPos->visitStage, kIter_VisitSelf);
  EXPECT_EQ(info.currSchema, std::string(kXmpNS));
}

// -------------------------------------------------------------------------------------------------

TEST_F(GetNextXMPNodeTest_2103, SkipsMissingPropertyAndFindsNextLiveNode_2103) {
  XMPMeta xmp;
  xmp.SetProperty(kXmpNS, "CreatorTool", "unit-test", 0);

  IterInfo info(/*options*/ 0, &xmp);

  // Sequence: schema -> missing prop -> existing prop
  IterOffspring seq;
  seq.emplace_back(MakeSchemaIterNode(kXmpNS));
  seq.emplace_back(MakePropIterNode("DoesNotExist"));
  seq.emplace_back(MakePropIterNode("CreatorTool"));
  AttachIterList(info, seq);

  // 1) First call should return a schema node (live or dummy depending on tree; here live).
  const XMP_Node* n1 = GetNextXMPNode(info);
  ASSERT_NE(n1, nullptr);
  EXPECT_NE(n1, sDummySchema);

  // Advance externally the way iterator clients typically do: move to next position.
  // (We do not infer internal mechanics; we only manipulate public iterator positions.)
  ++info.currPos;
  ASSERT_NE(info.currPos, info.endPos);

  // 2) At missing property, GetNextXMPNode should skip it and eventually return the next live node.
  const XMP_Node* n2 = GetNextXMPNode(info);
  ASSERT_NE(n2, nullptr);

  // After skipping, currPos should be positioned at some element that is "before visit" then set.
  EXPECT_EQ(info.currPos->visitStage, kIter_VisitSelf);

  // It should not return the dummy schema here because we're looking for a property node.
  // (If returned node is schema dummy, something is wrong with our sequence/schema state.)
  EXPECT_NE(n2, sDummySchema);
}

// -------------------------------------------------------------------------------------------------

TEST_F(GetNextXMPNodeTest_2103, JustChildrenOptionDoesNotCrashAndReturnsNode_2103) {
  XMPMeta xmp;
  xmp.SetProperty(kXmpNS, "CreatorTool", "unit-test", 0);

  // Enable JustChildren option.
  IterInfo info(kXMP_IterJustChildren, &xmp);

  IterOffspring seq;
  seq.emplace_back(MakeSchemaIterNode(kXmpNS));
  AttachIterList(info, seq);

  const XMP_Node* node = GetNextXMPNode(info);
  ASSERT_NE(node, nullptr);

  // With a live schema present, this should not fall back to dummy.
  EXPECT_NE(node, sDummySchema);

  // Public stage transition.
  EXPECT_EQ(info.currPos->visitStage, kIter_VisitSelf);
}

} // namespace