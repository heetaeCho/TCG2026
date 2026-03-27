#include <gtest/gtest.h>

#include "XMPCore_Impl.hpp"

#include "XMP_Const.h"



using namespace AdobeXMPCommon;



TEST(ComposeXPathTest_1892, NormalOperation_SingleStep_1892) {

    XMP_ExpandedXPath expandedXPath = { XPathStepInfo("root", kXMP_StructFieldStep) };

    XMP_VarString stringXPath;

    ComposeXPath(expandedXPath, &stringXPath);

    EXPECT_EQ(stringXPath, "root");

}



TEST(ComposeXPathTest_1892, NormalOperation_MultipleSteps_1892) {

    XMP_ExpandedXPath expandedXPath = { 

        XPathStepInfo("root", kXMP_StructFieldStep),

        XPathStepInfo("child1", kXMP_QualifierStep),

        XPathStepInfo("child2", kXMP_ArrayIndexStep)

    };

    XMP_VarString stringXPath;

    ComposeXPath(expandedXPath, &stringXPath);

    EXPECT_EQ(stringXPath, "root/child1child2");

}



TEST(ComposeXPathTest_1892, BoundaryCondition_EmptyPath_1892) {

    XMP_ExpandedXPath expandedXPath = {};

    XMP_VarString stringXPath;

    ComposeXPath(expandedXPath, &stringXPath);

    EXPECT_EQ(stringXPath, "");

}



TEST(ComposeXPathTest_1892, ExceptionalCase_UnexpectedStepKind_1892) {

    XMP_ExpandedXPath expandedXPath = { 

        XPathStepInfo("root", kXMP_StructFieldStep),

        XPathStepInfo("child1", 0)

    };

    XMP_VarString stringXPath;

    EXPECT_THROW(ComposeXPath(expandedXPath, &stringXPath), std::exception);

}



TEST(ComposeXPathTest_1892, BoundaryCondition_SingleRootStep_1892) {

    XMP_ExpandedXPath expandedXPath = { XPathStepInfo("root", kXMP_StructFieldStep) };

    XMP_VarString stringXPath;

    ComposeXPath(expandedXPath, &stringXPath);

    EXPECT_EQ(stringXPath, "root");

}



TEST(ComposeXPathTest_1892, NormalOperation_MixedSteps_1892) {

    XMP_ExpandedXPath expandedXPath = { 

        XPathStepInfo("root", kXMP_StructFieldStep),

        XPathStepInfo("child1", kXMP_QualifierStep),

        XPathStepInfo("index1", kXMP_ArrayIndexStep),

        XPathStepInfo("selector", kXMP_FieldSelectorStep)

    };

    XMP_VarString stringXPath;

    ComposeXPath(expandedXPath, &stringXPath);

    EXPECT_EQ(stringXPath, "root/child1index1selector");

}
