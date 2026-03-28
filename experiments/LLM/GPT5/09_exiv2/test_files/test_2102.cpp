// =================================================================================================
// TEST_ID: 2102
// Unit tests for static AdvanceIterPos (XMPIterator.cpp)
// =================================================================================================

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstddef>
#include <string>
#include <utility>
#include <vector>

// ---- Minimal type system stubs (only what's needed to compile and observe behavior) ----

using XMP_Uns8 = unsigned char;
using XMP_OptionBits = unsigned int;
using XMP_VarString = std::string;

struct XMPMeta {};  // opaque dependency

// Visit stages (values don't matter; only equality comparisons do).
static constexpr XMP_Uns8 kIter_BeforeVisit     = 0;
static constexpr XMP_Uns8 kIter_VisitSelf       = 1;
static constexpr XMP_Uns8 kIter_VisitQualifiers = 2;
static constexpr XMP_Uns8 kIter_VisitChildren   = 3;

// Option bit used in the function.
static constexpr XMP_OptionBits kXMP_SchemaNode = 0x00000001u;

struct IterNode;
using IterOffspring = std::vector<IterNode>;
using IterPos = IterOffspring::iterator;
using IterPosPair = std::pair<IterPos, IterPos>;
using IterPosStack = std::vector<IterPosPair>;

struct IterNode {
public:
  XMP_OptionBits options;
  XMP_VarString fullPath;
  size_t leafOffset;
  IterOffspring children;
  IterOffspring qualifiers;
  XMP_Uns8 visitStage;

  IterNode() : options(0), leafOffset(0), visitStage(kIter_BeforeVisit) {}
  IterNode(XMP_OptionBits _options, const XMP_VarString& _fullPath, size_t _leafOffset)
      : options(_options), fullPath(_fullPath), leafOffset(_leafOffset), visitStage(kIter_BeforeVisit) {}
};

struct IterInfo {
public:
  XMP_OptionBits options;
  const XMPMeta* xmpObj;
  XMP_VarString currSchema;
  IterPos currPos;
  IterPos endPos;
  IterPosStack ancestors;
  IterNode tree;

  IterInfo() : options(0), xmpObj(nullptr) {}
  IterInfo(XMP_OptionBits _options, const XMPMeta* _xmpObj) : options(_options), xmpObj(_xmpObj) {}
};

// ---- External collaborator we want to observe (spy via gmock) ----

struct SetCurrSchemaSpy {
  MOCK_METHOD(void, Call, (IterInfo&, const XMP_VarString&), ());
};

static SetCurrSchemaSpy* g_setCurrSchemaSpy = nullptr;

// The function under test calls SetCurrSchema(info, fullPath).
// Provide a test-defined hook to observe interactions.
static void SetCurrSchema(IterInfo& info, const XMP_VarString& schema) {
  if (g_setCurrSchemaSpy) g_setCurrSchemaSpy->Call(info, schema);
  // Observable side-effect we can also check without "inferring logic":
  // setting currSchema is reasonable public behavior for a "SetCurrSchema" collaborator.
  info.currSchema = schema;
}

// XMP_Assert used at end of function. Keep it test-friendly.
#define XMP_Assert(cond) ASSERT_TRUE(cond)

// ---- The function under test (as provided) ----

static void AdvanceIterPos(IterInfo& info) {
  while (true) {
    if (info.currPos == info.endPos) {
      if (info.ancestors.empty()) break;  // We're at the end of the schema list.

      IterPosPair& parent = info.ancestors.back();
      info.currPos = parent.first;
      info.endPos = parent.second;
      info.ancestors.pop_back();
    } else {
      if (info.currPos->visitStage == kIter_BeforeVisit) {
        // Visit this node now.
        if (info.currPos->options & kXMP_SchemaNode) SetCurrSchema(info, info.currPos->fullPath);
        break;
      }

      if (info.currPos->visitStage == kIter_VisitSelf) {
        // Just finished visiting the value portion.
        info.currPos->visitStage = kIter_VisitQualifiers;  // Start visiting the qualifiers.
        if (!info.currPos->qualifiers.empty()) {
          info.ancestors.push_back(IterPosPair(info.currPos, info.endPos));
          info.endPos = info.currPos->qualifiers.end();  // ! Set the parent's endPos before changing currPos!
          info.currPos = info.currPos->qualifiers.begin();
          break;
        }
      }

      if (info.currPos->visitStage == kIter_VisitQualifiers) {
        // Just finished visiting the qualifiers.
        info.currPos->qualifiers.clear();
        info.currPos->visitStage = kIter_VisitChildren;  // Start visiting the children.
        if (!info.currPos->children.empty()) {
          info.ancestors.push_back(IterPosPair(info.currPos, info.endPos));
          info.endPos = info.currPos->children.end();  // ! Set the parent's endPos before changing currPos!
          info.currPos = info.currPos->children.begin();
          break;
        }
      }

      if (info.currPos->visitStage == kIter_VisitChildren) {
        // Just finished visiting the children.
        info.currPos->children.clear();
        ++info.currPos;  // Move to the next sibling.
        continue;
      }
    }
  }

  // Loop to find the next node.
  XMP_Assert((info.currPos == info.endPos) || (info.currPos->visitStage == kIter_BeforeVisit));
}

// =================================================================================================
// Tests
// =================================================================================================

class AdvanceIterPosTest_2102 : public ::testing::Test {
protected:
  void SetUp() override { g_setCurrSchemaSpy = &spy_; }
  void TearDown() override { g_setCurrSchemaSpy = nullptr; }

  SetCurrSchemaSpy spy_;
};

TEST_F(AdvanceIterPosTest_2102, WhenAtEndAndNoAncestors_DoesNotMove_2102) {
  IterInfo info;
  info.tree.children.clear();
  info.currPos = info.tree.children.begin();
  info.endPos = info.tree.children.end();
  ASSERT_EQ(info.currPos, info.endPos);
  ASSERT_TRUE(info.ancestors.empty());

  EXPECT_CALL(spy_, Call(::testing::_, ::testing::_)).Times(0);

  AdvanceIterPos(info);

  EXPECT_EQ(info.currPos, info.endPos);
  EXPECT_TRUE(info.ancestors.empty());
}

TEST_F(AdvanceIterPosTest_2102, BeforeVisitSchemaNode_CallsSetCurrSchemaAndStops_2102) {
  IterInfo info;
  info.tree.children = {
      IterNode(kXMP_SchemaNode, "ns:SchemaA", 0),
      IterNode(0, "ns:Other", 0),
  };

  info.currPos = info.tree.children.begin();
  info.endPos = info.tree.children.end();
  info.currPos->visitStage = kIter_BeforeVisit;

  EXPECT_CALL(spy_, Call(::testing::Ref(info), "ns:SchemaA")).Times(1);

  AdvanceIterPos(info);

  // Should still be at same node (function "stops" on BeforeVisit node).
  EXPECT_EQ(info.currPos, info.tree.children.begin());
  EXPECT_EQ(info.currSchema, "ns:SchemaA");
}

TEST_F(AdvanceIterPosTest_2102, BeforeVisitNonSchemaNode_DoesNotCallSetCurrSchema_2102) {
  IterInfo info;
  info.tree.children = {IterNode(0, "ns:NotSchema", 0)};
  info.currPos = info.tree.children.begin();
  info.endPos = info.tree.children.end();
  info.currPos->visitStage = kIter_BeforeVisit;

  EXPECT_CALL(spy_, Call(::testing::_, ::testing::_)).Times(0);

  AdvanceIterPos(info);

  EXPECT_EQ(info.currPos, info.tree.children.begin());
  EXPECT_TRUE(info.currSchema.empty());
}

TEST_F(AdvanceIterPosTest_2102, VisitSelfWithQualifiers_DescendsIntoQualifiersAndPushesAncestor_2102) {
  IterInfo info;
  info.tree.children = {IterNode(0, "p", 0)};
  info.tree.children[0].visitStage = kIter_VisitSelf;
  info.tree.children[0].qualifiers = {IterNode(0, "p?q1", 0), IterNode(0, "p?q2", 0)};

  info.currPos = info.tree.children.begin();
  info.endPos = info.tree.children.end();

  EXPECT_CALL(spy_, Call(::testing::_, ::testing::_)).Times(0);

  AdvanceIterPos(info);

  ASSERT_EQ(info.ancestors.size(), 1u);
  EXPECT_EQ(info.currPos, info.tree.children[0].qualifiers.begin());
  EXPECT_EQ(info.endPos, info.tree.children[0].qualifiers.end());
  EXPECT_EQ(info.currPos->fullPath, "p?q1");
  EXPECT_EQ(info.currPos->visitStage, kIter_BeforeVisit);  // default for created nodes
}

TEST_F(AdvanceIterPosTest_2102, VisitQualifiersWithChildren_ClearsQualifiersAndDescendsIntoChildren_2102) {
  IterInfo info;
  info.tree.children = {IterNode(0, "p", 0)};
  IterNode& parent = info.tree.children[0];

  parent.visitStage = kIter_VisitQualifiers;
  parent.qualifiers = {IterNode(0, "p?q", 0)};  // will be cleared by AdvanceIterPos
  parent.children = {IterNode(0, "p/c1", 0), IterNode(0, "p/c2", 0)};

  info.currPos = info.tree.children.begin();
  info.endPos = info.tree.children.end();

  EXPECT_CALL(spy_, Call(::testing::_, ::testing::_)).Times(0);

  AdvanceIterPos(info);

  EXPECT_TRUE(parent.qualifiers.empty());
  EXPECT_EQ(parent.visitStage, kIter_VisitChildren);

  ASSERT_EQ(info.ancestors.size(), 1u);
  EXPECT_EQ(info.currPos, parent.children.begin());
  EXPECT_EQ(info.endPos, parent.children.end());
  EXPECT_EQ(info.currPos->fullPath, "p/c1");
}

TEST_F(AdvanceIterPosTest_2102, VisitChildren_AdvancesToNextSiblingAndClearsChildren_2102) {
  IterInfo info;
  info.tree.children = {IterNode(0, "s1", 0), IterNode(0, "s2", 0)};
  IterNode& s1 = info.tree.children[0];
  s1.visitStage = kIter_VisitChildren;
  s1.children = {IterNode(0, "s1/c", 0)};  // should be cleared

  info.currPos = info.tree.children.begin();
  info.endPos = info.tree.children.end();

  EXPECT_CALL(spy_, Call(::testing::_, ::testing::_)).Times(0);

  AdvanceIterPos(info);

  EXPECT_TRUE(s1.children.empty());
  EXPECT_EQ(info.currPos->fullPath, "s2");
  EXPECT_EQ(info.currPos->visitStage, kIter_BeforeVisit);
}

TEST_F(AdvanceIterPosTest_2102, WhenAtEndWithAncestor_PopsAncestorAndFindsNextBeforeVisitSibling_2102) {
  IterInfo info;
  info.tree.children = {IterNode(0, "parent", 0), IterNode(0, "next", 0)};
  IterNode& parent = info.tree.children[0];
  parent.visitStage = kIter_VisitChildren;  // so after moving up it advances to next sibling

  // Simulate that we were iterating inside parent's children and reached end.
  parent.children = {IterNode(0, "parent/c1", 0)};
  info.currPos = parent.children.end();
  info.endPos = parent.children.end();

  // Ancestor should restore iteration over the sibling list containing "parent" and "next".
  info.ancestors.push_back(IterPosPair(info.tree.children.begin(), info.tree.children.end()));

  EXPECT_CALL(spy_, Call(::testing::_, ::testing::_)).Times(0);

  AdvanceIterPos(info);

  EXPECT_TRUE(info.ancestors.empty());
  ASSERT_NE(info.currPos, info.endPos);
  EXPECT_EQ(info.currPos->fullPath, "next");
  EXPECT_EQ(info.currPos->visitStage, kIter_BeforeVisit);
}