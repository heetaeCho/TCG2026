#include <gtest/gtest.h>

#include "XMPIterator.hpp"



class XMPIteratorTest : public ::testing::Test {

protected:

    IterInfo info;



    void SetUp() override {

        // Initialize the IterInfo object with default values

        info = IterInfo();

    }

};



TEST_F(XMPIteratorTest_2102, AdvanceIterPos_MoveToNextSibling_2102) {

    // Setup: Create a simple node structure with siblings

    IterNode node1(XMP_OptionBits(), "node1", 0);

    IterNode node2(XMP_OptionBits(), "node2", 0);

    node1.children.push_back(&node2);



    info.currPos = &node1;

    info.endPos = node1.children.end();

    node1.visitStage = kIter_VisitChildren;



    // Act: Advance the iterator position

    AdvanceIterPos(info);



    // Assert: Expect currPos to move to the next sibling (node2)

    EXPECT_EQ(info.currPos, &node2);

}



TEST_F(XMPIteratorTest_2102, AdvanceIterPos_MoveToQualifiers_2102) {

    // Setup: Create a node with qualifiers

    IterNode node(XMP_OptionBits(), "node", 0);

    node.qualifiers.push_back(&node);



    info.currPos = &node;

    info.endPos = &node + 1;

    node.visitStage = kIter_VisitSelf;



    // Act: Advance the iterator position

    AdvanceIterPos(info);



    // Assert: Expect currPos to move to the qualifiers of the current node

    EXPECT_EQ(info.currPos, node.qualifiers.begin());

}



TEST_F(XMPIteratorTest_2102, AdvanceIterPos_MoveToChildren_2102) {

    // Setup: Create a node with children

    IterNode node(XMP_OptionBits(), "node", 0);

    IterNode child(XMP_OptionBits(), "child", 0);

    node.children.push_back(&child);



    info.currPos = &node;

    info.endPos = &node + 1;

    node.visitStage = kIter_VisitQualifiers;



    // Act: Advance the iterator position

    AdvanceIterPos(info);



    // Assert: Expect currPos to move to the children of the current node

    EXPECT_EQ(info.currPos, node.children.begin());

}



TEST_F(XMPIteratorTest_2102, AdvanceIterPos_MoveUpToParent_2102) {

    // Setup: Create a parent-child relationship with ancestors stack

    IterNode parent(XMP_OptionBits(), "parent", 0);

    IterNode child(XMP_OptionBits(), "child", 0);

    parent.children.push_back(&child);



    info.currPos = &child;

    info.endPos = &child + 1;

    info.ancestors.emplace(&parent, &parent + 1);

    child.visitStage = kIter_VisitChildren;



    // Act: Advance the iterator position

    AdvanceIterPos(info);



    // Assert: Expect currPos to move up to the parent node

    EXPECT_EQ(info.currPos, &parent);

}



TEST_F(XMPIteratorTest_2102, AdvanceIterPos_EndOfIteration_2102) {

    // Setup: Create a simple node with no children, qualifiers or siblings

    IterNode node(XMP_OptionBits(), "node", 0);



    info.currPos = &node;

    info.endPos = &node + 1;

    node.visitStage = kIter_VisitChildren;



    // Act: Advance the iterator position

    AdvanceIterPos(info);



    // Assert: Expect currPos to reach the end of iteration (endPos)

    EXPECT_EQ(info.currPos, info.endPos);

}
