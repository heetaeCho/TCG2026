#include <gtest/gtest.h>

#include "XMPCore_Impl.hpp"

#include "XMP_Const.h"



class CheckImplicitStructTest_1889 : public ::testing::Test {

protected:

    XMP_Node node;

    XMP_ExpandedXPath expandedXPath;



    void SetUp() override {

        node = XMP_Node(nullptr, "testNode", 0);

        expandedXPath.clear();

    }

};



TEST_F(CheckImplicitStructTest_1889, NormalOperation_1889) {

    XPathStepInfo step("field", kXMP_StructFieldStep);

    expandedXPath.push_back(step);



    CheckImplicitStruct(&node, expandedXPath, 0, 1);

    EXPECT_EQ(node.options & kXMP_PropValueIsStruct, kXMP_PropValueIsStruct);

}



TEST_F(CheckImplicitStructTest_1889, StepNumEqualsStepLim_1889) {

    XPathStepInfo step("field", kXMP_StructFieldStep);

    expandedXPath.push_back(step);



    CheckImplicitStruct(&node, expandedXPath, 1, 1);

    EXPECT_EQ(node.options & kXMP_PropValueIsStruct, 0);

}



TEST_F(CheckImplicitStructTest_1889, NodeAlreadyComposite_1889) {

    XPathStepInfo step("field", kXMP_StructFieldStep);

    expandedXPath.push_back(step);



    node.options |= kXMP_PropCompositeMask;

    CheckImplicitStruct(&node, expandedXPath, 0, 1);

    EXPECT_EQ(node.options & kXMP_PropValueIsStruct, 0);

}



TEST_F(CheckImplicitStructTest_1889, StepKindNotStructFieldStep_1889) {

    XPathStepInfo step("field", kXMP_QualifierStep);

    expandedXPath.push_back(step);



    CheckImplicitStruct(&node, expandedXPath, 0, 1);

    EXPECT_EQ(node.options & kXMP_PropValueIsStruct, 0);

}



TEST_F(CheckImplicitStructTest_1889, MultipleSteps_1889) {

    XPathStepInfo step1("field", kXMP_StructFieldStep);

    XPathStepInfo step2("qualifier", kXMP_QualifierStep);

    expandedXPath.push_back(step1);

    expandedXPath.push_back(step2);



    CheckImplicitStruct(&node, expandedXPath, 0, 2);

    EXPECT_EQ(node.options & kXMP_PropValueIsStruct, kXMP_PropValueIsStruct);

}



TEST_F(CheckImplicitStructTest_1889, StepNumExceedsStepLim_1889) {

    XPathStepInfo step("field", kXMP_StructFieldStep);

    expandedXPath.push_back(step);



    CheckImplicitStruct(&node, expandedXPath, 2, 1);

    EXPECT_EQ(node.options & kXMP_PropValueIsStruct, 0);

}
