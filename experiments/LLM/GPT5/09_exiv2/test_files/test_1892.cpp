#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "XMPCore_Impl.hpp"
#include "XMP_Const.h"
#include "XMP_Const.h"

using ::testing::_;
using ::testing::Eq;

class ComposeXPathTest_1892 : public ::testing::Test {
protected:
    void SetUp() override {
        // Any setup needed for each test case
    }

    void TearDown() override {
        // Clean up if necessary
    }
};

TEST_F(ComposeXPathTest_1892, ComposeXPath_NormalOperation_1892) {
    // Test for normal operation
    XMP_ExpandedXPath expandedXPath = {
        XPathStepInfo("rootStep", kXMP_StructFieldStep),
        XPathStepInfo("field1", kXMP_QualifierStep),
        XPathStepInfo("field2", kXMP_ArrayIndexStep)
    };

    XMP_VarString stringXPath;
    ComposeXPath(expandedXPath, &stringXPath);
    
    EXPECT_EQ(stringXPath, "rootStep/field1/field2");
}

TEST_F(ComposeXPathTest_1892, ComposeXPath_EmptyXPath_1893) {
    // Test for boundary condition: Empty XPath
    XMP_ExpandedXPath expandedXPath;

    XMP_VarString stringXPath;
    ComposeXPath(expandedXPath, &stringXPath);

    EXPECT_EQ(stringXPath, "");
}

TEST_F(ComposeXPathTest_1892, ComposeXPath_UnexpectedStepKind_1894) {
    // Test for exceptional case: Unexpected Step Kind
    XMP_ExpandedXPath expandedXPath = {
        XPathStepInfo("rootStep", kXMP_StructFieldStep),
        XPathStepInfo("field1", 999)  // Invalid step kind, should trigger an exception
    };

    XMP_VarString stringXPath;

    EXPECT_THROW(ComposeXPath(expandedXPath, &stringXPath), std::runtime_error);
}

TEST_F(ComposeXPathTest_1892, ComposeXPath_SingleStep_1895) {
    // Test for a single step
    XMP_ExpandedXPath expandedXPath = {
        XPathStepInfo("rootStep", kXMP_StructFieldStep)
    };

    XMP_VarString stringXPath;
    ComposeXPath(expandedXPath, &stringXPath);

    EXPECT_EQ(stringXPath, "rootStep");
}

TEST_F(ComposeXPathTest_1892, ComposeXPath_MixedStepKinds_1896) {
    // Test for a mixture of step kinds
    XMP_ExpandedXPath expandedXPath = {
        XPathStepInfo("rootStep", kXMP_StructFieldStep),
        XPathStepInfo("field1", kXMP_QualifierStep),
        XPathStepInfo("index1", kXMP_ArrayIndexStep),
        XPathStepInfo("field2", kXMP_ArrayLastStep)
    };

    XMP_VarString stringXPath;
    ComposeXPath(expandedXPath, &stringXPath);

    EXPECT_EQ(stringXPath, "rootStep/field1/index1/field2");
}