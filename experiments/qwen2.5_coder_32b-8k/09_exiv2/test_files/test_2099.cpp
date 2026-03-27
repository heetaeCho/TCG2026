#include <gtest/gtest.h>

#include "XMPIterator.hpp"

#include "XMPNode.hpp"



class AddNodeOffspringTest_2099 : public ::testing::Test {

protected:

    IterInfo info;

    IterNode iterParent;

    XMP_Node xmpParent;



    void SetUp() override {

        info.options = 0; // Default options

        iterParent.fullPath = "Root";

        xmpParent.name = "Root";

        xmpParent.options = kXMP_PropValueIsStruct;

    }

};



TEST_F(AddNodeOffspringTest_2099, NoChildrenOrQualifiers_2099) {

    AddNodeOffspring(info, iterParent, &xmpParent);

    EXPECT_TRUE(iterParent.children.empty());

    EXPECT_TRUE(iterParent.qualifiers.empty());

}



TEST_F(AddNodeOffspringTest_2099, WithQualifiers_2099) {

    XMP_Node qualifier1(&xmpParent, "qualifier1", kXMP_PropIsQualifier);

    XMP_Node qualifier2(&xmpParent, "qualifier2", kXMP_PropIsQualifier);

    xmpParent.qualifiers.push_back(&qualifier1);

    xmpParent.qualifiers.push_back(&qualifier2);



    AddNodeOffspring(info, iterParent, &xmpParent);

    EXPECT_EQ(iterParent.qualifiers.size(), 2);

    EXPECT_EQ(iterParent.qualifiers[0].fullPath, "Root/?qualifier1");

    EXPECT_EQ(iterParent.qualifiers[1].fullPath, "Root/?qualifier2");

}



TEST_F(AddNodeOffspringTest_2099, WithQualifiersAndOptionsOmitQualifiers_2099) {

    info.options = kXMP_IterOmitQualifiers;

    XMP_Node qualifier(&xmpParent, "qualifier", kXMP_PropIsQualifier);

    xmpParent.qualifiers.push_back(&qualifier);



    AddNodeOffspring(info, iterParent, &xmpParent);

    EXPECT_TRUE(iterParent.qualifiers.empty());

}



TEST_F(AddNodeOffspringTest_2099, WithChildren_2099) {

    XMP_Node child1(&xmpParent, "child1", kXMP_PropValueIsStruct);

    XMP_Node child2(&xmpParent, "child2", kXMP_PropValueIsStruct);

    xmpParent.children.push_back(&child1);

    xmpParent.children.push_back(&child2);



    AddNodeOffspring(info, iterParent, &xmpParent);

    EXPECT_EQ(iterParent.children.size(), 2);

    EXPECT_EQ(iterParent.children[0].fullPath, "Root/child1");

    EXPECT_EQ(iterParent.children[1].fullPath, "Root/child2");

}



TEST_F(AddNodeOffspringTest_2099, WithChildrenAndArray_2099) {

    xmpParent.options |= kXMP_PropValueIsArray;

    XMP_Node child1(&xmpParent, "value", kXMP_PropValueIsStruct);

    XMP_Node child2(&xmpParent, "value", kXMP_PropValueIsStruct);

    xmpParent.children.push_back(&child1);

    xmpParent.children.push_back(&child2);



    AddNodeOffspring(info, iterParent, &xmpParent);

    EXPECT_EQ(iterParent.children.size(), 2);

    EXPECT_EQ(iterParent.children[0].fullPath, "Root/[1]");

    EXPECT_EQ(iterParent.children[1].fullPath, "Root/[2]");

}



TEST_F(AddNodeOffspringTest_2099, MixedChildrenAndQualifiers_2099) {

    XMP_Node qualifier(&xmpParent, "qualifier", kXMP_PropIsQualifier);

    XMP_Node child(&xmpParent, "child", kXMP_PropValueIsStruct);

    xmpParent.qualifiers.push_back(&qualifier);

    xmpParent.children.push_back(&child);



    AddNodeOffspring(info, iterParent, &xmpParent);

    EXPECT_EQ(iterParent.qualifiers.size(), 1);

    EXPECT_EQ(iterParent.children.size(), 1);

    EXPECT_EQ(iterParent.qualifiers[0].fullPath, "Root/?qualifier");

    EXPECT_EQ(iterParent.children[0].fullPath, "Root/child");

}
