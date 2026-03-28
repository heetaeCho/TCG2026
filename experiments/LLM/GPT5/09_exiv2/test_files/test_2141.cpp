// ============================================================================
// TEST_ID: 2141
// Unit tests for static DumpPropertyTree (black-box via observable output)
// File: test_DumpPropertyTree_2141.cpp
// ============================================================================

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>
#include <memory>
#include <vector>

// The XMP SDK headers are expected to be available in the build.
// These provide XMP_Status, XMP_OptionBits, XMP_TextOutputProc, etc.
#include "XMP_Const.h"

// IMPORTANT:
// DumpPropertyTree is a static function inside XMPMeta.cpp (internal linkage).
// To test it using only its observable behavior (output + return status),
// we compile it into this test translation unit by including the .cpp.
//
// This is a common pattern for unit-testing TU-local helpers while still
// treating the implementation as a black box (we assert only on outputs).
#include "./TestProjects/exiv2/xmpsdk/src/XMPMeta.cpp"

namespace {

struct OutputSink {
  std::string out;
};

// XMP_TextOutputProc is typically: XMP_Status (*)(void* refCon, XMP_StringPtr buffer, XMP_StringLen count)
// We'll implement a compatible callback as used by the SDK output helpers.
// If the signature differs in your SDK version, adjust parameters accordingly.
static XMP_Status CollectingOutProc(void* refCon, XMP_StringPtr buffer, XMP_StringLen count) {
  auto* sink = static_cast<OutputSink*>(refCon);
  if (buffer != nullptr && count > 0) sink->out.append(buffer, static_cast<size_t>(count));
  return 0;
}

struct FailingOutputSink {
  std::string out;
  int calls = 0;
  int fail_on_call = 1;  // 1-based
  XMP_Status fail_status = 1;
};

static XMP_Status FailingOutProc(void* refCon, XMP_StringPtr buffer, XMP_StringLen count) {
  auto* sink = static_cast<FailingOutputSink*>(refCon);
  sink->calls++;
  if (buffer != nullptr && count > 0) sink->out.append(buffer, static_cast<size_t>(count));
  if (sink->calls >= sink->fail_on_call) return sink->fail_status;
  return 0;
}

// Helper to own nodes while wiring raw pointers into children/qualifiers vectors.
struct NodeArena {
  std::vector<std::unique_ptr<XMP_Node>> nodes;

  XMP_Node* MakeNode(XMP_Node* parent, XMP_StringPtr name, XMP_StringPtr value, XMP_OptionBits options) {
    nodes.emplace_back(std::make_unique<XMP_Node>(parent, name, value, options));
    return nodes.back().get();
  }

  XMP_Node* MakeNode(XMP_Node* parent, XMP_StringPtr name, XMP_OptionBits options) {
    nodes.emplace_back(std::make_unique<XMP_Node>(parent, name, options));
    return nodes.back().get();
  }
};

class DumpPropertyTreeTest_2141 : public ::testing::Test {
protected:
  NodeArena arena;
};

}  // namespace

TEST_F(DumpPropertyTreeTest_2141, LeafNode_EmitsNameAndValue_2141) {
  OutputSink sink;

  XMP_Node* leaf = arena.MakeNode(/*parent*/ nullptr, "dc:title", "Hello", /*options*/ 0);

  const XMP_Status st = DumpPropertyTree(leaf, /*indent*/ 0, /*itemIndex*/ 0, &CollectingOutProc, &sink);
  EXPECT_EQ(st, 0);

  // Observable behavior: name and value are printed in a predictable format.
  EXPECT_THAT(sink.out, ::testing::HasSubstr("dc:title"));
  EXPECT_THAT(sink.out, ::testing::HasSubstr(" = \"Hello\""));
  EXPECT_THAT(sink.out, ::testing::HasSubstr("\n"));
}

TEST_F(DumpPropertyTreeTest_2141, QualifierNode_PrefixedWithQuestionMark_2141) {
  OutputSink sink;

  // Parent with a qualifier.
  XMP_Node* parent = arena.MakeNode(nullptr, "xmp:CreatorTool", "ToolX", /*options*/ kXMP_PropHasQualifiers);

  // Qualifier: must have kXMP_PropIsQualifier to avoid "** bad qual flag => "
  XMP_Node* qual = arena.MakeNode(parent, "xmp:qual", "qv", /*options*/ kXMP_PropIsQualifier);
  parent->qualifiers.push_back(qual);

  const XMP_Status st = DumpPropertyTree(parent, /*indent*/ 0, /*itemIndex*/ 0, &CollectingOutProc, &sink);
  EXPECT_EQ(st, 0);

  // Observable behavior: qualifiers are dumped with "? " prefix (when itemIndex==0).
  EXPECT_THAT(sink.out, ::testing::HasSubstr("? xmp:qual"));
  EXPECT_THAT(sink.out, ::testing::HasSubstr(" = \"qv\""));
}

TEST_F(DumpPropertyTreeTest_2141, HasLangFlagWithoutXmlLangQualifier_EmitsBadLangFlagMarker_2141) {
  OutputSink sink;

  // kXMP_PropHasLang set, but qualifiers are empty => " ** bad lang flag **"
  XMP_Node* node = arena.MakeNode(nullptr, "dc:title", "Hello", /*options*/ kXMP_PropHasLang);

  const XMP_Status st = DumpPropertyTree(node, /*indent*/ 0, /*itemIndex*/ 0, &CollectingOutProc, &sink);
  EXPECT_EQ(st, 0);

  EXPECT_THAT(sink.out, ::testing::HasSubstr("** bad lang flag **"));
}

TEST_F(DumpPropertyTreeTest_2141, ArrayChildren_RenderBracketedIndices_2141) {
  OutputSink sink;

  XMP_Node* arr = arena.MakeNode(nullptr, "dc:subject", "", /*options*/ kXMP_PropValueIsArray);

  // Array items should be named kXMP_ArrayItemName to avoid "** bad item name => "
  XMP_Node* item1 = arena.MakeNode(arr, kXMP_ArrayItemName, "one", /*options*/ 0);
  XMP_Node* item2 = arena.MakeNode(arr, kXMP_ArrayItemName, "two", /*options*/ 0);
  arr->children.push_back(item1);
  arr->children.push_back(item2);

  const XMP_Status st = DumpPropertyTree(arr, /*indent*/ 0, /*itemIndex*/ 0, &CollectingOutProc, &sink);
  EXPECT_EQ(st, 0);

  // Observable behavior: array items are printed as [1], [2], ...
  EXPECT_THAT(sink.out, ::testing::HasSubstr("[1]"));
  EXPECT_THAT(sink.out, ::testing::HasSubstr(" = \"one\""));
  EXPECT_THAT(sink.out, ::testing::HasSubstr("[2]"));
  EXPECT_THAT(sink.out, ::testing::HasSubstr(" = \"two\""));
}

TEST_F(DumpPropertyTreeTest_2141, ArrayChildWithWrongItemName_EmitsBadItemNameMarker_2141) {
  OutputSink sink;

  XMP_Node* arr = arena.MakeNode(nullptr, "dc:subject", "", /*options*/ kXMP_PropValueIsArray);

  // Wrong name for an array item triggers "** bad item name => "
  XMP_Node* badItem = arena.MakeNode(arr, "not-an-item", "oops", /*options*/ 0);
  arr->children.push_back(badItem);

  const XMP_Status st = DumpPropertyTree(arr, /*indent*/ 0, /*itemIndex*/ 0, &CollectingOutProc, &sink);
  EXPECT_EQ(st, 0);

  EXPECT_THAT(sink.out, ::testing::HasSubstr("** bad item name => "));
}

TEST_F(DumpPropertyTreeTest_2141, ChildWithWrongParentPointer_EmitsBadParentLinkMarker_2141) {
  OutputSink sink;

  XMP_Node* parent = arena.MakeNode(nullptr, "rdf:Description", "", /*options*/ kXMP_PropValueIsStruct);

  // Create a child but intentionally do not set its parent pointer to `parent`.
  XMP_Node* childWrongParent = arena.MakeNode(/*parent*/ nullptr, "dc:title", "Hello", /*options*/ 0);
  parent->children.push_back(childWrongParent);

  const XMP_Status st = DumpPropertyTree(parent, /*indent*/ 0, /*itemIndex*/ 0, &CollectingOutProc, &sink);
  EXPECT_EQ(st, 0);

  EXPECT_THAT(sink.out, ::testing::HasSubstr("** bad parent link => "));
}

TEST_F(DumpPropertyTreeTest_2141, NonCompositeNodeWithChildren_EmitsBadChildrenMarker_2141) {
  OutputSink sink;

  // No composite flags => treated as leaf; having children should emit " ** bad children **"
  XMP_Node* node = arena.MakeNode(nullptr, "dc:title", "Hello", /*options*/ 0);
  XMP_Node* child = arena.MakeNode(node, "dc:child", "X", /*options*/ 0);
  node->children.push_back(child);

  const XMP_Status st = DumpPropertyTree(node, /*indent*/ 0, /*itemIndex*/ 0, &CollectingOutProc, &sink);
  EXPECT_EQ(st, 0);

  EXPECT_THAT(sink.out, ::testing::HasSubstr("** bad children **"));
}

TEST_F(DumpPropertyTreeTest_2141, OutputProcFailure_IsPropagatedAsStatus_2141) {
  FailingOutputSink sink;
  sink.fail_on_call = 1;
  sink.fail_status = 7;

  XMP_Node* leaf = arena.MakeNode(nullptr, "dc:title", "Hello", /*options*/ 0);

  const XMP_Status st = DumpPropertyTree(leaf, /*indent*/ 0, /*itemIndex*/ 0, &FailingOutProc, &sink);
  EXPECT_EQ(st, 7);
}