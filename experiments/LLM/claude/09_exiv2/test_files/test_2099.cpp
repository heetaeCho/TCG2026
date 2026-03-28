#include <gtest/gtest.h>
#include <string>
#include <vector>

// Include necessary XMP headers
#include "XMP_Environment.h"
#include "XMP_Const.h"
#include "XMPCore_Impl.hpp"
#include "XMPIterator.hpp"

// Include the cpp file to access the static function
#include "XMPIterator.cpp"

class AddNodeOffspringTest_2099 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test: No qualifiers and no children - iterParent should remain unchanged
TEST_F(AddNodeOffspringTest_2099, EmptyNode_NoQualifiersNoChildren_2099) {
    IterInfo info;
    info.options = 0;

    IterNode iterParent(0, "TestPath", 0);

    XMP_Node xmpParent(nullptr, "Parent", 0);
    // No qualifiers, no children

    AddNodeOffspring(info, iterParent, &xmpParent);

    EXPECT_TRUE(iterParent.children.empty());
    EXPECT_TRUE(iterParent.qualifiers.empty());
}

// Test: Node with qualifiers, qualifiers NOT omitted
TEST_F(AddNodeOffspringTest_2099, QualifiersAdded_WhenNotOmitted_2099) {
    IterInfo info;
    info.options = 0; // kXMP_IterOmitQualifiers is NOT set

    IterNode iterParent(0, "Prop", 0);

    XMP_Node xmpParent(nullptr, "Parent", 0);
    XMP_Node qual1(&xmpParent, "Qual1", kXMP_PropIsQualifier);
    XMP_Node qual2(&xmpParent, "Qual2", kXMP_PropIsQualifier);
    xmpParent.qualifiers.push_back(&qual1);
    xmpParent.qualifiers.push_back(&qual2);

    AddNodeOffspring(info, iterParent, &xmpParent);

    EXPECT_EQ(iterParent.qualifiers.size(), 2u);
    EXPECT_EQ(iterParent.qualifiers[0].fullPath, "Prop/?Qual1");
    EXPECT_EQ(iterParent.qualifiers[1].fullPath, "Prop/?Qual2");
    // leafOffset should be Prop.size() + 2 = 4 + 2 = 6
    EXPECT_EQ(iterParent.qualifiers[0].leafOffset, 6u);
    EXPECT_EQ(iterParent.qualifiers[1].leafOffset, 6u);
}

// Test: Node with qualifiers, qualifiers omitted via kXMP_IterOmitQualifiers
TEST_F(AddNodeOffspringTest_2099, QualifiersOmitted_WhenFlagSet_2099) {
    IterInfo info;
    info.options = kXMP_IterOmitQualifiers;

    IterNode iterParent(0, "Prop", 0);

    XMP_Node xmpParent(nullptr, "Parent", 0);
    XMP_Node qual1(&xmpParent, "Qual1", kXMP_PropIsQualifier);
    xmpParent.qualifiers.push_back(&qual1);

    AddNodeOffspring(info, iterParent, &xmpParent);

    EXPECT_TRUE(iterParent.qualifiers.empty());
}

// Test: Node with struct children
TEST_F(AddNodeOffspringTest_2099, StructChildren_AddedWithSlashSeparator_2099) {
    IterInfo info;
    info.options = 0;

    IterNode iterParent(0, "Struct", 0);

    XMP_Node xmpParent(nullptr, "Parent", kXMP_PropValueIsStruct | kXMP_PropCompositeMask);
    XMP_Node child1(&xmpParent, "Child1", 0);
    XMP_Node child2(&xmpParent, "Child2", 0);
    xmpParent.children.push_back(&child1);
    xmpParent.children.push_back(&child2);

    AddNodeOffspring(info, iterParent, &xmpParent);

    EXPECT_EQ(iterParent.children.size(), 2u);
    EXPECT_EQ(iterParent.children[0].fullPath, "Struct/Child1");
    EXPECT_EQ(iterParent.children[1].fullPath, "Struct/Child2");
    // leafOffset = "Struct".size() + 1 = 7
    EXPECT_EQ(iterParent.children[0].leafOffset, 7u);
    EXPECT_EQ(iterParent.children[1].leafOffset, 7u);
}

// Test: Node with array children - uses [index] notation
TEST_F(AddNodeOffspringTest_2099, ArrayChildren_AddedWithIndexNotation_2099) {
    IterInfo info;
    info.options = 0;

    IterNode iterParent(0, "Array", 0);

    XMP_Node xmpParent(nullptr, "Parent", kXMP_PropValueIsArray);
    XMP_Node child1(&xmpParent, "Item1", 0);
    XMP_Node child2(&xmpParent, "Item2", 0);
    XMP_Node child3(&xmpParent, "Item3", 0);
    xmpParent.children.push_back(&child1);
    xmpParent.children.push_back(&child2);
    xmpParent.children.push_back(&child3);

    AddNodeOffspring(info, iterParent, &xmpParent);

    EXPECT_EQ(iterParent.children.size(), 3u);
    EXPECT_EQ(iterParent.children[0].fullPath, "Array[1]");
    EXPECT_EQ(iterParent.children[1].fullPath, "Array[2]");
    EXPECT_EQ(iterParent.children[2].fullPath, "Array[3]");
    // leafOffset = "Array".size() = 5
    EXPECT_EQ(iterParent.children[0].leafOffset, 5u);
}

// Test: Node with both qualifiers and struct children
TEST_F(AddNodeOffspringTest_2099, BothQualifiersAndStructChildren_2099) {
    IterInfo info;
    info.options = 0;

    IterNode iterParent(0, "Node", 0);

    XMP_Node xmpParent(nullptr, "Parent", kXMP_PropValueIsStruct | kXMP_PropCompositeMask);
    XMP_Node qual1(&xmpParent, "QualA", kXMP_PropIsQualifier);
    xmpParent.qualifiers.push_back(&qual1);

    XMP_Node child1(&xmpParent, "ChildX", 0);
    xmpParent.children.push_back(&child1);

    AddNodeOffspring(info, iterParent, &xmpParent);

    EXPECT_EQ(iterParent.qualifiers.size(), 1u);
    EXPECT_EQ(iterParent.qualifiers[0].fullPath, "Node/?QualA");

    EXPECT_EQ(iterParent.children.size(), 1u);
    EXPECT_EQ(iterParent.children[0].fullPath, "Node/ChildX");
}

// Test: Node with both qualifiers and array children
TEST_F(AddNodeOffspringTest_2099, BothQualifiersAndArrayChildren_2099) {
    IterInfo info;
    info.options = 0;

    IterNode iterParent(0, "Arr", 0);

    XMP_Node xmpParent(nullptr, "Parent", kXMP_PropValueIsArray);
    XMP_Node qual1(&xmpParent, "Q1", kXMP_PropIsQualifier);
    xmpParent.qualifiers.push_back(&qual1);

    XMP_Node child1(&xmpParent, "Item", 0);
    XMP_Node child2(&xmpParent, "Item", 0);
    xmpParent.children.push_back(&child1);
    xmpParent.children.push_back(&child2);

    AddNodeOffspring(info, iterParent, &xmpParent);

    EXPECT_EQ(iterParent.qualifiers.size(), 1u);
    EXPECT_EQ(iterParent.qualifiers[0].fullPath, "Arr/?Q1");
    // leafOffset for qualifier: "Arr".size() + 2 = 5
    EXPECT_EQ(iterParent.qualifiers[0].leafOffset, 5u);

    EXPECT_EQ(iterParent.children.size(), 2u);
    EXPECT_EQ(iterParent.children[0].fullPath, "Arr[1]");
    EXPECT_EQ(iterParent.children[1].fullPath, "Arr[2]");
    // leafOffset for array children: "Arr".size() = 3
    EXPECT_EQ(iterParent.children[0].leafOffset, 3u);
}

// Test: Options are correctly propagated to IterNode children
TEST_F(AddNodeOffspringTest_2099, ChildOptions_PropagatedCorrectly_2099) {
    IterInfo info;
    info.options = 0;

    IterNode iterParent(0, "Root", 0);

    XMP_Node xmpParent(nullptr, "Parent", kXMP_PropValueIsStruct | kXMP_PropCompositeMask);
    XMP_Node child1(&xmpParent, "C1", kXMP_PropValueIsArray);
    XMP_Node child2(&xmpParent, "C2", kXMP_PropValueIsURI);
    xmpParent.children.push_back(&child1);
    xmpParent.children.push_back(&child2);

    AddNodeOffspring(info, iterParent, &xmpParent);

    EXPECT_EQ(iterParent.children.size(), 2u);
    EXPECT_EQ(iterParent.children[0].options, static_cast<XMP_OptionBits>(kXMP_PropValueIsArray));
    EXPECT_EQ(iterParent.children[1].options, static_cast<XMP_OptionBits>(kXMP_PropValueIsURI));
}

// Test: Qualifier options are correctly propagated
TEST_F(AddNodeOffspringTest_2099, QualifierOptions_PropagatedCorrectly_2099) {
    IterInfo info;
    info.options = 0;

    IterNode iterParent(0, "P", 0);

    XMP_Node xmpParent(nullptr, "Parent", 0);
    XMP_Node qual1(&xmpParent, "Q1", kXMP_PropIsQualifier | kXMP_PropValueIsURI);
    xmpParent.qualifiers.push_back(&qual1);

    AddNodeOffspring(info, iterParent, &xmpParent);

    EXPECT_EQ(iterParent.qualifiers.size(), 1u);
    EXPECT_EQ(iterParent.qualifiers[0].options,
              static_cast<XMP_OptionBits>(kXMP_PropIsQualifier | kXMP_PropValueIsURI));
}

// Test: Empty fullPath on iterParent
TEST_F(AddNodeOffspringTest_2099, EmptyFullPath_StructChildren_2099) {
    IterInfo info;
    info.options = 0;

    IterNode iterParent(0, "", 0);

    XMP_Node xmpParent(nullptr, "Parent", kXMP_PropValueIsStruct | kXMP_PropCompositeMask);
    XMP_Node child1(&xmpParent, "Child1", 0);
    xmpParent.children.push_back(&child1);

    AddNodeOffspring(info, iterParent, &xmpParent);

    EXPECT_EQ(iterParent.children.size(), 1u);
    EXPECT_EQ(iterParent.children[0].fullPath, "/Child1");
    EXPECT_EQ(iterParent.children[0].leafOffset, 1u);
}

// Test: Empty fullPath on iterParent with array children
TEST_F(AddNodeOffspringTest_2099, EmptyFullPath_ArrayChildren_2099) {
    IterInfo info;
    info.options = 0;

    IterNode iterParent(0, "", 0);

    XMP_Node xmpParent(nullptr, "Parent", kXMP_PropValueIsArray);
    XMP_Node child1(&xmpParent, "Item", 0);
    xmpParent.children.push_back(&child1);

    AddNodeOffspring(info, iterParent, &xmpParent);

    EXPECT_EQ(iterParent.children.size(), 1u);
    EXPECT_EQ(iterParent.children[0].fullPath, "[1]");
    EXPECT_EQ(iterParent.children[0].leafOffset, 0u);
}

// Test: Multiple qualifiers ensure correct path construction for each
TEST_F(AddNodeOffspringTest_2099, MultipleQualifiers_CorrectPaths_2099) {
    IterInfo info;
    info.options = 0;

    IterNode iterParent(0, "MyProp", 0);

    XMP_Node xmpParent(nullptr, "Parent", 0);
    XMP_Node q1(&xmpParent, "Alpha", kXMP_PropIsQualifier);
    XMP_Node q2(&xmpParent, "Beta", kXMP_PropIsQualifier);
    XMP_Node q3(&xmpParent, "Gamma", kXMP_PropIsQualifier);
    xmpParent.qualifiers.push_back(&q1);
    xmpParent.qualifiers.push_back(&q2);
    xmpParent.qualifiers.push_back(&q3);

    AddNodeOffspring(info, iterParent, &xmpParent);

    ASSERT_EQ(iterParent.qualifiers.size(), 3u);
    EXPECT_EQ(iterParent.qualifiers[0].fullPath, "MyProp/?Alpha");
    EXPECT_EQ(iterParent.qualifiers[1].fullPath, "MyProp/?Beta");
    EXPECT_EQ(iterParent.qualifiers[2].fullPath, "MyProp/?Gamma");
}

// Test: Array with many children - indices are one-based
TEST_F(AddNodeOffspringTest_2099, ArrayManyChildren_OneBasedIndices_2099) {
    IterInfo info;
    info.options = 0;

    IterNode iterParent(0, "Arr", 0);

    XMP_Node xmpParent(nullptr, "Parent", kXMP_PropValueIsArray);
    
    std::vector<XMP_Node*> children;
    for (int i = 0; i < 10; i++) {
        children.push_back(new XMP_Node(&xmpParent, "Item", 0));
        xmpParent.children.push_back(children.back());
    }

    AddNodeOffspring(info, iterParent, &xmpParent);

    ASSERT_EQ(iterParent.children.size(), 10u);
    for (int i = 0; i < 10; i++) {
        char expected[64];
        snprintf(expected, sizeof(expected), "Arr[%d]", i + 1);
        EXPECT_EQ(iterParent.children[i].fullPath, std::string(expected));
    }

    // Clean up - don't let xmpParent destructor try to delete children
    xmpParent.children.clear();
    for (auto* c : children) delete c;
}

// Test: visitStage of created IterNodes defaults to kIter_BeforeVisit
TEST_F(AddNodeOffspringTest_2099, IterNodes_DefaultVisitStage_2099) {
    IterInfo info;
    info.options = 0;

    IterNode iterParent(0, "X", 0);

    XMP_Node xmpParent(nullptr, "Parent", kXMP_PropValueIsStruct | kXMP_PropCompositeMask);
    XMP_Node child1(&xmpParent, "C1", 0);
    xmpParent.children.push_back(&child1);

    XMP_Node qual1(&xmpParent, "Q1", 0);
    xmpParent.qualifiers.push_back(&qual1);

    AddNodeOffspring(info, iterParent, &xmpParent);

    ASSERT_EQ(iterParent.children.size(), 1u);
    ASSERT_EQ(iterParent.qualifiers.size(), 1u);
    EXPECT_EQ(iterParent.children[0].visitStage, kIter_BeforeVisit);
    EXPECT_EQ(iterParent.qualifiers[0].visitStage, kIter_BeforeVisit);
}

// Test: Ordered array children use bracket notation
TEST_F(AddNodeOffspringTest_2099, OrderedArray_BracketNotation_2099) {
    IterInfo info;
    info.options = 0;

    IterNode iterParent(0, "OrdArr", 0);

    XMP_Node xmpParent(nullptr, "Parent", kXMP_PropArrayIsOrdered);
    // kXMP_PropArrayIsOrdered includes kXMP_PropValueIsArray bit
    XMP_Node child1(&xmpParent, "Item", 0);
    XMP_Node child2(&xmpParent, "Item", 0);
    xmpParent.children.push_back(&child1);
    xmpParent.children.push_back(&child2);

    AddNodeOffspring(info, iterParent, &xmpParent);

    ASSERT_EQ(iterParent.children.size(), 2u);
    EXPECT_EQ(iterParent.children[0].fullPath, "OrdArr[1]");
    EXPECT_EQ(iterParent.children[1].fullPath, "OrdArr[2]");
}

// Test: Only qualifiers, no children on the node
TEST_F(AddNodeOffspringTest_2099, OnlyQualifiers_NoChildren_2099) {
    IterInfo info;
    info.options = 0;

    IterNode iterParent(0, "SimpleProp", 0);

    XMP_Node xmpParent(nullptr, "Parent", 0); // simple prop, no composite mask
    XMP_Node qual1(&xmpParent, "lang", kXMP_PropIsQualifier);
    xmpParent.qualifiers.push_back(&qual1);

    AddNodeOffspring(info, iterParent, &xmpParent);

    EXPECT_EQ(iterParent.qualifiers.size(), 1u);
    EXPECT_EQ(iterParent.qualifiers[0].fullPath, "SimpleProp/?lang");
    EXPECT_TRUE(iterParent.children.empty());
}

// Test: Only children, no qualifiers
TEST_F(AddNodeOffspringTest_2099, OnlyChildren_NoQualifiers_2099) {
    IterInfo info;
    info.options = 0;

    IterNode iterParent(0, "Struct", 0);

    XMP_Node xmpParent(nullptr, "Parent", kXMP_PropValueIsStruct | kXMP_PropCompositeMask);
    // No qualifiers
    XMP_Node child1(&xmpParent, "Field1", 0);
    xmpParent.children.push_back(&child1);

    AddNodeOffspring(info, iterParent, &xmpParent);

    EXPECT_TRUE(iterParent.qualifiers.empty());
    EXPECT_EQ(iterParent.children.size(), 1u);
    EXPECT_EQ(iterParent.children[0].fullPath, "Struct/Field1");
}
