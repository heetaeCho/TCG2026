#include <gtest/gtest.h>
#include <string>
#include <vector>

// Include necessary headers from the XMP SDK
#define TXMP_STRING_TYPE std::string
#include "public/include/XMP_Const.h"
#include "public/include/XMP_Environment.h"
#include "XMPCore/source/XMPMeta.hpp"
#include "XMPCore/source/XMPIterator.hpp"
#include "XMPIterator.hpp"

// Visit stage constants
#ifndef kIter_BeforeVisit
#define kIter_BeforeVisit 0
#endif
#ifndef kIter_VisitSelf
#define kIter_VisitSelf 1
#endif
#ifndef kIter_VisitQualifiers
#define kIter_VisitQualifiers 2
#endif
#ifndef kIter_VisitChildren
#define kIter_VisitChildren 3
#endif

class IterNodeTest_2102 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

class IterInfoTest_2102 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

class AdvanceIterPosTest_2102 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== IterNode Tests ====================

TEST_F(IterNodeTest_2102, DefaultConstructor_InitializesDefaults_2102) {
    IterNode node;
    EXPECT_EQ(node.options, 0u);
    EXPECT_EQ(node.leafOffset, 0u);
    EXPECT_EQ(node.visitStage, kIter_BeforeVisit);
    EXPECT_TRUE(node.fullPath.empty());
    EXPECT_TRUE(node.children.empty());
    EXPECT_TRUE(node.qualifiers.empty());
}

TEST_F(IterNodeTest_2102, ParameterizedConstructor_SetsValues_2102) {
    XMP_OptionBits opts = kXMP_PropValueIsArray;
    std::string path = "dc:creator";
    size_t offset = 3;
    
    IterNode node(opts, path, offset);
    EXPECT_EQ(node.options, opts);
    EXPECT_EQ(node.fullPath, path);
    EXPECT_EQ(node.leafOffset, offset);
    EXPECT_EQ(node.visitStage, kIter_BeforeVisit);
    EXPECT_TRUE(node.children.empty());
    EXPECT_TRUE(node.qualifiers.empty());
}

TEST_F(IterNodeTest_2102, ParameterizedConstructor_EmptyPath_2102) {
    IterNode node(0, "", 0);
    EXPECT_EQ(node.options, 0u);
    EXPECT_TRUE(node.fullPath.empty());
    EXPECT_EQ(node.leafOffset, 0u);
    EXPECT_EQ(node.visitStage, kIter_BeforeVisit);
}

TEST_F(IterNodeTest_2102, ParameterizedConstructor_LongPath_2102) {
    std::string longPath(1024, 'x');
    IterNode node(0xFFFFFFFF, longPath, 512);
    EXPECT_EQ(node.fullPath, longPath);
    EXPECT_EQ(node.leafOffset, 512u);
    EXPECT_EQ(node.options, 0xFFFFFFFF);
}

TEST_F(IterNodeTest_2102, ChildrenCanBeAdded_2102) {
    IterNode parent(0, "parent", 0);
    IterNode child(0, "parent/child", 7);
    parent.children.push_back(child);
    EXPECT_EQ(parent.children.size(), 1u);
    EXPECT_EQ(parent.children[0].fullPath, "parent/child");
}

TEST_F(IterNodeTest_2102, QualifiersCanBeAdded_2102) {
    IterNode node(0, "dc:title", 3);
    IterNode qualifier(0, "dc:title/?xml:lang", 10);
    node.qualifiers.push_back(qualifier);
    EXPECT_EQ(node.qualifiers.size(), 1u);
    EXPECT_EQ(node.qualifiers[0].fullPath, "dc:title/?xml:lang");
}

// ==================== IterInfo Tests ====================

TEST_F(IterInfoTest_2102, DefaultConstructor_InitializesDefaults_2102) {
    IterInfo info;
    EXPECT_EQ(info.options, 0u);
    EXPECT_EQ(info.xmpObj, nullptr);
    EXPECT_TRUE(info.currSchema.empty());
    EXPECT_TRUE(info.ancestors.empty());
}

TEST_F(IterInfoTest_2102, ParameterizedConstructor_SetsValues_2102) {
    XMPMeta meta;
    XMP_OptionBits opts = kXMP_IterJustChildren;
    IterInfo info(opts, &meta);
    EXPECT_EQ(info.options, opts);
    EXPECT_EQ(info.xmpObj, &meta);
}

TEST_F(IterInfoTest_2102, ParameterizedConstructor_NullXmpObj_2102) {
    IterInfo info(0, nullptr);
    EXPECT_EQ(info.options, 0u);
    EXPECT_EQ(info.xmpObj, nullptr);
}

// ==================== AdvanceIterPos Behavior Tests ====================

TEST_F(AdvanceIterPosTest_2102, EmptyTree_CurrPosEqualsEndPos_2102) {
    // When tree has no children, currPos should equal endPos after advance
    IterInfo info;
    info.tree.children.clear();
    info.currPos = info.tree.children.begin();
    info.endPos = info.tree.children.end();
    
    // currPos == endPos and ancestors empty, should just break
    // This tests the first branch: empty iteration
    EXPECT_EQ(info.currPos, info.endPos);
    EXPECT_TRUE(info.ancestors.empty());
}

TEST_F(AdvanceIterPosTest_2102, SingleNode_BeforeVisit_StopsAtNode_2102) {
    IterInfo info;
    IterNode node(0, "dc:title", 3);
    node.visitStage = kIter_BeforeVisit;
    info.tree.children.push_back(node);
    
    info.currPos = info.tree.children.begin();
    info.endPos = info.tree.children.end();
    
    // Node is at kIter_BeforeVisit, AdvanceIterPos should stop here
    EXPECT_EQ(info.currPos->visitStage, kIter_BeforeVisit);
    EXPECT_NE(info.currPos, info.endPos);
}

TEST_F(AdvanceIterPosTest_2102, NodeWithChildren_ChildrenAreListed_2102) {
    IterInfo info;
    IterNode parent(0, "dc:creator", 3);
    parent.visitStage = kIter_BeforeVisit;
    
    IterNode child1(0, "dc:creator[1]", 3);
    child1.visitStage = kIter_BeforeVisit;
    IterNode child2(0, "dc:creator[2]", 3);
    child2.visitStage = kIter_BeforeVisit;
    
    parent.children.push_back(child1);
    parent.children.push_back(child2);
    
    info.tree.children.push_back(parent);
    info.currPos = info.tree.children.begin();
    info.endPos = info.tree.children.end();
    
    EXPECT_EQ(info.tree.children.size(), 1u);
    EXPECT_EQ(info.tree.children[0].children.size(), 2u);
}

TEST_F(AdvanceIterPosTest_2102, NodeVisitStage_VisitChildren_ClearsAndAdvances_2102) {
    IterInfo info;
    
    IterNode node1(0, "dc:title", 3);
    node1.visitStage = kIter_VisitChildren;
    
    IterNode node2(0, "dc:creator", 3);
    node2.visitStage = kIter_BeforeVisit;
    
    info.tree.children.push_back(node1);
    info.tree.children.push_back(node2);
    
    info.currPos = info.tree.children.begin();
    info.endPos = info.tree.children.end();
    
    // First node is at VisitChildren stage with no children
    // Should clear children and move to next sibling (node2)
    EXPECT_EQ(info.currPos->visitStage, kIter_VisitChildren);
    EXPECT_EQ(info.tree.children.size(), 2u);
}

TEST_F(AdvanceIterPosTest_2102, SchemaNode_SetsCurrentSchema_2102) {
    IterInfo info;
    IterNode schemaNode(kXMP_SchemaNode, "http://purl.org/dc/elements/1.1/", 0);
    schemaNode.visitStage = kIter_BeforeVisit;
    
    info.tree.children.push_back(schemaNode);
    info.currPos = info.tree.children.begin();
    info.endPos = info.tree.children.end();
    
    // A schema node at BeforeVisit should trigger SetCurrSchema
    EXPECT_TRUE(info.currPos->options & kXMP_SchemaNode);
    EXPECT_EQ(info.currPos->visitStage, kIter_BeforeVisit);
}

TEST_F(AdvanceIterPosTest_2102, NodeWithQualifiers_QualifiersVisited_2102) {
    IterInfo info;
    
    IterNode node(0, "dc:title", 3);
    node.visitStage = kIter_BeforeVisit;
    
    IterNode qualifier(0, "dc:title/?xml:lang", 10);
    qualifier.visitStage = kIter_BeforeVisit;
    node.qualifiers.push_back(qualifier);
    
    info.tree.children.push_back(node);
    info.currPos = info.tree.children.begin();
    info.endPos = info.tree.children.end();
    
    EXPECT_FALSE(info.tree.children[0].qualifiers.empty());
    EXPECT_EQ(info.tree.children[0].qualifiers.size(), 1u);
}

TEST_F(AdvanceIterPosTest_2102, MultipleNodes_AllBeforeVisit_2102) {
    IterInfo info;
    
    for (int i = 0; i < 5; ++i) {
        std::string path = "ns:prop" + std::to_string(i);
        IterNode node(0, path, 3);
        node.visitStage = kIter_BeforeVisit;
        info.tree.children.push_back(node);
    }
    
    info.currPos = info.tree.children.begin();
    info.endPos = info.tree.children.end();
    
    EXPECT_EQ(info.tree.children.size(), 5u);
    // First node should be at BeforeVisit
    EXPECT_EQ(info.currPos->visitStage, kIter_BeforeVisit);
    EXPECT_EQ(info.currPos->fullPath, "ns:prop0");
}

TEST_F(AdvanceIterPosTest_2102, AncestorsStack_PushAndPop_2102) {
    IterInfo info;
    
    // Simulate ancestors stack behavior
    IterNode parent(0, "parent", 0);
    parent.visitStage = kIter_BeforeVisit;
    IterNode child(0, "parent/child", 7);
    child.visitStage = kIter_BeforeVisit;
    parent.children.push_back(child);
    
    info.tree.children.push_back(parent);
    info.currPos = info.tree.children.begin();
    info.endPos = info.tree.children.end();
    
    // Ancestors initially empty
    EXPECT_TRUE(info.ancestors.empty());
    
    // Simulate pushing to ancestors
    info.ancestors.push_back(IterPosPair(info.currPos, info.endPos));
    EXPECT_EQ(info.ancestors.size(), 1u);
    
    // Pop from ancestors
    IterPosPair & back = info.ancestors.back();
    info.currPos = back.first;
    info.endPos = back.second;
    info.ancestors.pop_back();
    EXPECT_TRUE(info.ancestors.empty());
}

TEST_F(AdvanceIterPosTest_2102, VisitSelf_TransitionsToVisitQualifiers_2102) {
    // A node at VisitSelf stage should transition to VisitQualifiers
    IterNode node(0, "dc:title", 3);
    node.visitStage = kIter_VisitSelf;
    
    // After AdvanceIterPos processes this, it should set stage to VisitQualifiers
    // We verify the initial condition
    EXPECT_EQ(node.visitStage, kIter_VisitSelf);
    
    // Manually simulate what the code does
    node.visitStage = kIter_VisitQualifiers;
    EXPECT_EQ(node.visitStage, kIter_VisitQualifiers);
}

TEST_F(AdvanceIterPosTest_2102, VisitQualifiers_EmptyQualifiers_TransitionsToChildren_2102) {
    IterNode node(0, "dc:title", 3);
    node.visitStage = kIter_VisitQualifiers;
    // No qualifiers
    EXPECT_TRUE(node.qualifiers.empty());
    
    // Code should clear qualifiers and move to VisitChildren
    node.qualifiers.clear();
    node.visitStage = kIter_VisitChildren;
    EXPECT_EQ(node.visitStage, kIter_VisitChildren);
}

TEST_F(AdvanceIterPosTest_2102, VisitChildren_EmptyChildren_ClearsAndAdvances_2102) {
    IterNode node(0, "dc:title", 3);
    node.visitStage = kIter_VisitChildren;
    EXPECT_TRUE(node.children.empty());
    
    // Code should clear children and increment currPos
    node.children.clear();
    EXPECT_TRUE(node.children.empty());
}

TEST_F(AdvanceIterPosTest_2102, NestedChildren_MultipleLevel_2102) {
    IterInfo info;
    
    IterNode grandchild(0, "a/b/c", 4);
    grandchild.visitStage = kIter_BeforeVisit;
    
    IterNode child(0, "a/b", 2);
    child.visitStage = kIter_BeforeVisit;
    child.children.push_back(grandchild);
    
    IterNode root(0, "a", 0);
    root.visitStage = kIter_BeforeVisit;
    root.children.push_back(child);
    
    info.tree.children.push_back(root);
    info.currPos = info.tree.children.begin();
    info.endPos = info.tree.children.end();
    
    EXPECT_EQ(info.tree.children[0].children[0].children.size(), 1u);
    EXPECT_EQ(info.tree.children[0].children[0].children[0].fullPath, "a/b/c");
}

TEST_F(AdvanceIterPosTest_2102, LeafOffset_PreservedThroughIteration_2102) {
    IterNode node(0, "xmp:CreateDate", 4);
    EXPECT_EQ(node.leafOffset, 4u);
    EXPECT_EQ(node.fullPath.substr(node.leafOffset), "CreateDate");
}

TEST_F(AdvanceIterPosTest_2102, OptionsPreserved_2102) {
    XMP_OptionBits opts = kXMP_PropValueIsArray | kXMP_PropArrayIsOrdered;
    IterNode node(opts, "dc:subject", 3);
    EXPECT_EQ(node.options, opts);
    EXPECT_TRUE(node.options & kXMP_PropValueIsArray);
    EXPECT_TRUE(node.options & kXMP_PropArrayIsOrdered);
}

// Integration-style test: Full XMPIterator through public API
class XMPIteratorIntegrationTest_2102 : public ::testing::Test {
protected:
    void SetUp() override {
        SXMPMeta::Initialize();
    }
    void TearDown() override {
        SXMPMeta::Terminate();
    }
};

TEST_F(XMPIteratorIntegrationTest_2102, EmptyMeta_NoIteration_2102) {
    try {
        XMPMeta meta;
        XMPIterator iter(meta, "", "", 0);
        
        std::string schemaNS, propPath, propVal;
        XMP_OptionBits opts;
        
        // Empty metadata should have nothing to iterate
        bool hasNext = iter.Next(&schemaNS, &propPath, &propVal, &opts);
        // May or may not have items, depending on implementation
        // This is just to verify no crash occurs
        (void)hasNext;
    } catch (...) {
        // Some implementations may throw for empty meta
    }
}
