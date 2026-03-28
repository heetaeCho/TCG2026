#include <gtest/gtest.h>
#include <vector>
#include <string>

// Include necessary headers
#include "XMPCore_Impl.hpp"
#include "XMP_Const.h"

// We need to access the static inline function. Since it's defined as static inline
// in a .cpp file, we need to either include that file or redefine the helper.
// For testing purposes, we'll replicate the minimal needed definitions and
// include the function under test.

// GetStepKind is typically defined as:
// static inline XMP_OptionBits GetStepKind(XMP_OptionBits options) { return options & kXMP_StepKindMask; }
// We need this helper to be available. It should be in XMPCore_Impl.hpp or similar.

// Since CheckImplicitStruct is static inline in the .cpp file, we need to either
// include that .cpp or define a test wrapper. For unit testing, we'll include the
// implementation file directly to get access to the static function.
#include "XMPCore_Impl.cpp"

// Type aliases for clarity
using XMP_ExpandedXPath = std::vector<XPathStepInfo>;

class CheckImplicitStructTest_1889 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: When stepNum < stepLim, node has no composite flags, and step kind is kXMP_StructFieldStep,
// node should get kXMP_PropValueIsStruct flag set.
TEST_F(CheckImplicitStructTest_1889, SetsStructFlagWhenConditionsMet_1889) {
    XMP_Node node(nullptr, "testNode", 0);  // options = 0, no composite mask bits set
    
    XMP_ExpandedXPath expandedXPath;
    expandedXPath.push_back(XPathStepInfo("schema", 0));
    expandedXPath.push_back(XPathStepInfo("field", kXMP_StructFieldStep));  // stepNum=1, kind=kXMP_StructFieldStep
    
    size_t stepNum = 1;
    size_t stepLim = 2;
    
    CheckImplicitStruct(&node, expandedXPath, stepNum, stepLim);
    
    EXPECT_TRUE((node.options & kXMP_PropValueIsStruct) != 0);
}

// Test: When stepNum >= stepLim, the function should NOT modify the node options.
TEST_F(CheckImplicitStructTest_1889, DoesNotSetFlagWhenStepNumEqualsStepLim_1889) {
    XMP_Node node(nullptr, "testNode", 0);
    
    XMP_ExpandedXPath expandedXPath;
    expandedXPath.push_back(XPathStepInfo("schema", 0));
    expandedXPath.push_back(XPathStepInfo("field", kXMP_StructFieldStep));
    
    size_t stepNum = 2;
    size_t stepLim = 2;
    
    CheckImplicitStruct(&node, expandedXPath, stepNum, stepLim);
    
    EXPECT_EQ(node.options, 0u);
}

// Test: When stepNum > stepLim, the function should NOT modify the node options.
TEST_F(CheckImplicitStructTest_1889, DoesNotSetFlagWhenStepNumGreaterThanStepLim_1889) {
    XMP_Node node(nullptr, "testNode", 0);
    
    XMP_ExpandedXPath expandedXPath;
    expandedXPath.push_back(XPathStepInfo("schema", 0));
    expandedXPath.push_back(XPathStepInfo("field", kXMP_StructFieldStep));
    expandedXPath.push_back(XPathStepInfo("field2", kXMP_StructFieldStep));
    
    size_t stepNum = 3;
    size_t stepLim = 2;
    
    CheckImplicitStruct(&node, expandedXPath, stepNum, stepLim);
    
    EXPECT_EQ(node.options, 0u);
}

// Test: When node already has kXMP_PropValueIsStruct set (composite mask != 0),
// the function should NOT change the options (condition fails).
TEST_F(CheckImplicitStructTest_1889, DoesNotSetFlagWhenNodeAlreadyIsStruct_1889) {
    XMP_Node node(nullptr, "testNode", kXMP_PropValueIsStruct);
    
    XMP_ExpandedXPath expandedXPath;
    expandedXPath.push_back(XPathStepInfo("schema", 0));
    expandedXPath.push_back(XPathStepInfo("field", kXMP_StructFieldStep));
    
    size_t stepNum = 1;
    size_t stepLim = 2;
    
    XMP_OptionBits originalOptions = node.options;
    CheckImplicitStruct(&node, expandedXPath, stepNum, stepLim);
    
    // Options should remain unchanged since composite mask was already set
    EXPECT_EQ(node.options, originalOptions);
}

// Test: When node has kXMP_PropValueIsArray set (part of composite mask),
// the function should NOT set the struct flag.
TEST_F(CheckImplicitStructTest_1889, DoesNotSetFlagWhenNodeIsArray_1889) {
    XMP_Node node(nullptr, "testNode", kXMP_PropValueIsArray);
    
    XMP_ExpandedXPath expandedXPath;
    expandedXPath.push_back(XPathStepInfo("schema", 0));
    expandedXPath.push_back(XPathStepInfo("field", kXMP_StructFieldStep));
    
    size_t stepNum = 1;
    size_t stepLim = 2;
    
    CheckImplicitStruct(&node, expandedXPath, stepNum, stepLim);
    
    // kXMP_PropValueIsStruct should NOT be added
    EXPECT_EQ(node.options, (XMP_OptionBits)kXMP_PropValueIsArray);
}

// Test: When step kind is NOT kXMP_StructFieldStep (e.g., kXMP_ArrayIndexStep),
// the function should NOT set the struct flag.
TEST_F(CheckImplicitStructTest_1889, DoesNotSetFlagWhenStepKindIsArrayIndex_1889) {
    XMP_Node node(nullptr, "testNode", 0);
    
    XMP_ExpandedXPath expandedXPath;
    expandedXPath.push_back(XPathStepInfo("schema", 0));
    expandedXPath.push_back(XPathStepInfo("index", kXMP_ArrayIndexStep));
    
    size_t stepNum = 1;
    size_t stepLim = 2;
    
    CheckImplicitStruct(&node, expandedXPath, stepNum, stepLim);
    
    EXPECT_EQ(node.options, 0u);
}

// Test: When step kind is kXMP_QualifierStep, should NOT set struct flag.
TEST_F(CheckImplicitStructTest_1889, DoesNotSetFlagWhenStepKindIsQualifier_1889) {
    XMP_Node node(nullptr, "testNode", 0);
    
    XMP_ExpandedXPath expandedXPath;
    expandedXPath.push_back(XPathStepInfo("schema", 0));
    expandedXPath.push_back(XPathStepInfo("qualifier", kXMP_QualifierStep));
    
    size_t stepNum = 1;
    size_t stepLim = 2;
    
    CheckImplicitStruct(&node, expandedXPath, stepNum, stepLim);
    
    EXPECT_EQ(node.options, 0u);
}

// Test: When step kind is kXMP_ArrayLastStep, should NOT set struct flag.
TEST_F(CheckImplicitStructTest_1889, DoesNotSetFlagWhenStepKindIsArrayLast_1889) {
    XMP_Node node(nullptr, "testNode", 0);
    
    XMP_ExpandedXPath expandedXPath;
    expandedXPath.push_back(XPathStepInfo("schema", 0));
    expandedXPath.push_back(XPathStepInfo("last", kXMP_ArrayLastStep));
    
    size_t stepNum = 1;
    size_t stepLim = 2;
    
    CheckImplicitStruct(&node, expandedXPath, stepNum, stepLim);
    
    EXPECT_EQ(node.options, 0u);
}

// Test: When step kind is kXMP_QualSelectorStep, should NOT set struct flag.
TEST_F(CheckImplicitStructTest_1889, DoesNotSetFlagWhenStepKindIsQualSelector_1889) {
    XMP_Node node(nullptr, "testNode", 0);
    
    XMP_ExpandedXPath expandedXPath;
    expandedXPath.push_back(XPathStepInfo("schema", 0));
    expandedXPath.push_back(XPathStepInfo("qualsel", kXMP_QualSelectorStep));
    
    size_t stepNum = 1;
    size_t stepLim = 2;
    
    CheckImplicitStruct(&node, expandedXPath, stepNum, stepLim);
    
    EXPECT_EQ(node.options, 0u);
}

// Test: When step kind is kXMP_FieldSelectorStep, should NOT set struct flag.
TEST_F(CheckImplicitStructTest_1889, DoesNotSetFlagWhenStepKindIsFieldSelector_1889) {
    XMP_Node node(nullptr, "testNode", 0);
    
    XMP_ExpandedXPath expandedXPath;
    expandedXPath.push_back(XPathStepInfo("schema", 0));
    expandedXPath.push_back(XPathStepInfo("fieldsel", kXMP_FieldSelectorStep));
    
    size_t stepNum = 1;
    size_t stepLim = 2;
    
    CheckImplicitStruct(&node, expandedXPath, stepNum, stepLim);
    
    EXPECT_EQ(node.options, 0u);
}

// Test: Node has non-composite options (e.g., kXMP_PropValueIsURI) and step kind is struct field.
// Should set struct flag since kXMP_PropValueIsURI is not in kXMP_PropCompositeMask.
TEST_F(CheckImplicitStructTest_1889, SetsStructFlagWhenNodeHasNonCompositeOptions_1889) {
    XMP_Node node(nullptr, "testNode", kXMP_PropValueIsURI);
    
    XMP_ExpandedXPath expandedXPath;
    expandedXPath.push_back(XPathStepInfo("schema", 0));
    expandedXPath.push_back(XPathStepInfo("field", kXMP_StructFieldStep));
    
    size_t stepNum = 1;
    size_t stepLim = 2;
    
    CheckImplicitStruct(&node, expandedXPath, stepNum, stepLim);
    
    EXPECT_TRUE((node.options & kXMP_PropValueIsStruct) != 0);
    // Original flag should be preserved
    EXPECT_TRUE((node.options & kXMP_PropValueIsURI) != 0);
}

// Test: stepNum is 0, stepLim is 1, and conditions are met.
TEST_F(CheckImplicitStructTest_1889, SetsStructFlagAtStepZero_1889) {
    XMP_Node node(nullptr, "testNode", 0);
    
    XMP_ExpandedXPath expandedXPath;
    expandedXPath.push_back(XPathStepInfo("field", kXMP_StructFieldStep));
    
    size_t stepNum = 0;
    size_t stepLim = 1;
    
    CheckImplicitStruct(&node, expandedXPath, stepNum, stepLim);
    
    EXPECT_TRUE((node.options & kXMP_PropValueIsStruct) != 0);
}

// Test: Node has kXMP_PropArrayIsOrdered (part of composite mask via array form).
// kXMP_PropArrayIsOrdered = 1024, which is within kXMP_PropCompositeMask = 7936.
// So composite mask check should fail and struct flag should NOT be set.
TEST_F(CheckImplicitStructTest_1889, DoesNotSetFlagWhenNodeHasOrderedArray_1889) {
    XMP_Node node(nullptr, "testNode", kXMP_PropArrayIsOrdered);
    
    XMP_ExpandedXPath expandedXPath;
    expandedXPath.push_back(XPathStepInfo("schema", 0));
    expandedXPath.push_back(XPathStepInfo("field", kXMP_StructFieldStep));
    
    size_t stepNum = 1;
    size_t stepLim = 2;
    
    CheckImplicitStruct(&node, expandedXPath, stepNum, stepLim);
    
    EXPECT_FALSE((node.options & kXMP_PropValueIsStruct) != 0);
    EXPECT_EQ(node.options, (XMP_OptionBits)kXMP_PropArrayIsOrdered);
}

// Test: Node has kXMP_PropArrayIsAlternate set.
TEST_F(CheckImplicitStructTest_1889, DoesNotSetFlagWhenNodeHasAlternateArray_1889) {
    XMP_Node node(nullptr, "testNode", kXMP_PropArrayIsAlternate);
    
    XMP_ExpandedXPath expandedXPath;
    expandedXPath.push_back(XPathStepInfo("schema", 0));
    expandedXPath.push_back(XPathStepInfo("field", kXMP_StructFieldStep));
    
    size_t stepNum = 1;
    size_t stepLim = 2;
    
    CheckImplicitStruct(&node, expandedXPath, stepNum, stepLim);
    
    EXPECT_FALSE((node.options & kXMP_PropValueIsStruct) != 0);
}

// Test: Node has kXMP_PropArrayIsAltText set.
TEST_F(CheckImplicitStructTest_1889, DoesNotSetFlagWhenNodeHasAltText_1889) {
    XMP_Node node(nullptr, "testNode", kXMP_PropArrayIsAltText);
    
    XMP_ExpandedXPath expandedXPath;
    expandedXPath.push_back(XPathStepInfo("schema", 0));
    expandedXPath.push_back(XPathStepInfo("field", kXMP_StructFieldStep));
    
    size_t stepNum = 1;
    size_t stepLim = 2;
    
    CheckImplicitStruct(&node, expandedXPath, stepNum, stepLim);
    
    EXPECT_FALSE((node.options & kXMP_PropValueIsStruct) != 0);
}

// Test: Step options has kXMP_StructFieldStep combined with kXMP_StepIsAlias.
// GetStepKind masks with kXMP_StepKindMask (0x0F), so kXMP_StepIsAlias (16) is masked out.
// The step kind should still be kXMP_StructFieldStep.
TEST_F(CheckImplicitStructTest_1889, SetsStructFlagWhenStepHasAliasFlag_1889) {
    XMP_Node node(nullptr, "testNode", 0);
    
    XMP_ExpandedXPath expandedXPath;
    expandedXPath.push_back(XPathStepInfo("schema", 0));
    expandedXPath.push_back(XPathStepInfo("field", kXMP_StructFieldStep | kXMP_StepIsAlias));
    
    size_t stepNum = 1;
    size_t stepLim = 2;
    
    CheckImplicitStruct(&node, expandedXPath, stepNum, stepLim);
    
    EXPECT_TRUE((node.options & kXMP_PropValueIsStruct) != 0);
}

// Test: Step options is 0 (kind = 0, which is not kXMP_StructFieldStep).
// Should NOT set struct flag.
TEST_F(CheckImplicitStructTest_1889, DoesNotSetFlagWhenStepKindIsZero_1889) {
    XMP_Node node(nullptr, "testNode", 0);
    
    XMP_ExpandedXPath expandedXPath;
    expandedXPath.push_back(XPathStepInfo("schema", 0));
    expandedXPath.push_back(XPathStepInfo("unknown", 0));
    
    size_t stepNum = 1;
    size_t stepLim = 2;
    
    CheckImplicitStruct(&node, expandedXPath, stepNum, stepLim);
    
    EXPECT_EQ(node.options, 0u);
}

// Test: Multiple calls - calling twice should be idempotent (struct flag already set on second call
// means composite mask is non-zero, so second call is a no-op effectively but flag stays).
TEST_F(CheckImplicitStructTest_1889, IdempotentWhenCalledTwice_1889) {
    XMP_Node node(nullptr, "testNode", 0);
    
    XMP_ExpandedXPath expandedXPath;
    expandedXPath.push_back(XPathStepInfo("schema", 0));
    expandedXPath.push_back(XPathStepInfo("field", kXMP_StructFieldStep));
    
    size_t stepNum = 1;
    size_t stepLim = 2;
    
    CheckImplicitStruct(&node, expandedXPath, stepNum, stepLim);
    EXPECT_TRUE((node.options & kXMP_PropValueIsStruct) != 0);
    
    // Second call - node now has kXMP_PropValueIsStruct which is in composite mask,
    // so the condition (node->options & kXMP_PropCompositeMask) == 0 fails.
    // The flag should remain set but no additional modification.
    XMP_OptionBits afterFirst = node.options;
    CheckImplicitStruct(&node, expandedXPath, stepNum, stepLim);
    EXPECT_EQ(node.options, afterFirst);
}

// Test: Verify with a longer expanded XPath, using a middle step.
TEST_F(CheckImplicitStructTest_1889, SetsStructFlagForMiddleStep_1889) {
    XMP_Node node(nullptr, "testNode", 0);
    
    XMP_ExpandedXPath expandedXPath;
    expandedXPath.push_back(XPathStepInfo("schema", 0));
    expandedXPath.push_back(XPathStepInfo("step1", kXMP_ArrayIndexStep));
    expandedXPath.push_back(XPathStepInfo("step2", kXMP_StructFieldStep));
    expandedXPath.push_back(XPathStepInfo("step3", kXMP_QualifierStep));
    
    size_t stepNum = 2;  // step2 which is kXMP_StructFieldStep
    size_t stepLim = 4;
    
    CheckImplicitStruct(&node, expandedXPath, stepNum, stepLim);
    
    EXPECT_TRUE((node.options & kXMP_PropValueIsStruct) != 0);
}

// Test: stepLim is 0 and stepNum is 0 - condition stepNum < stepLim fails.
TEST_F(CheckImplicitStructTest_1889, DoesNotSetFlagWhenBothZero_1889) {
    XMP_Node node(nullptr, "testNode", 0);
    
    XMP_ExpandedXPath expandedXPath;
    
    size_t stepNum = 0;
    size_t stepLim = 0;
    
    CheckImplicitStruct(&node, expandedXPath, stepNum, stepLim);
    
    EXPECT_EQ(node.options, 0u);
}

// Test: Node has kXMP_PropHasQualifiers flag (not in composite mask).
// Should still set struct flag.
TEST_F(CheckImplicitStructTest_1889, SetsStructFlagWhenNodeHasQualifiers_1889) {
    XMP_Node node(nullptr, "testNode", kXMP_PropHasQualifiers);
    
    XMP_ExpandedXPath expandedXPath;
    expandedXPath.push_back(XPathStepInfo("schema", 0));
    expandedXPath.push_back(XPathStepInfo("field", kXMP_StructFieldStep));
    
    size_t stepNum = 1;
    size_t stepLim = 2;
    
    CheckImplicitStruct(&node, expandedXPath, stepNum, stepLim);
    
    EXPECT_TRUE((node.options & kXMP_PropValueIsStruct) != 0);
    EXPECT_TRUE((node.options & kXMP_PropHasQualifiers) != 0);
}
