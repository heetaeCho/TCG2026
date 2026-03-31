#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"

class ConvertBoolTest_623 : public ::testing::Test {
protected:
    YAML::Node node;
    bool result;
};

// ==================== Normal operation tests ====================

TEST_F(ConvertBoolTest_623, DecodeTrue_Lowercase_623) {
    node = YAML::Node("true");
    EXPECT_TRUE(YAML::convert<bool>::decode(node, result));
    EXPECT_TRUE(result);
}

TEST_F(ConvertBoolTest_623, DecodeFalse_Lowercase_623) {
    node = YAML::Node("false");
    EXPECT_TRUE(YAML::convert<bool>::decode(node, result));
    EXPECT_FALSE(result);
}

TEST_F(ConvertBoolTest_623, DecodeYes_Lowercase_623) {
    node = YAML::Node("yes");
    EXPECT_TRUE(YAML::convert<bool>::decode(node, result));
    EXPECT_TRUE(result);
}

TEST_F(ConvertBoolTest_623, DecodeNo_Lowercase_623) {
    node = YAML::Node("no");
    EXPECT_TRUE(YAML::convert<bool>::decode(node, result));
    EXPECT_FALSE(result);
}

TEST_F(ConvertBoolTest_623, DecodeY_Lowercase_623) {
    node = YAML::Node("y");
    EXPECT_TRUE(YAML::convert<bool>::decode(node, result));
    EXPECT_TRUE(result);
}

TEST_F(ConvertBoolTest_623, DecodeN_Lowercase_623) {
    node = YAML::Node("n");
    EXPECT_TRUE(YAML::convert<bool>::decode(node, result));
    EXPECT_FALSE(result);
}

TEST_F(ConvertBoolTest_623, DecodeOn_Lowercase_623) {
    node = YAML::Node("on");
    EXPECT_TRUE(YAML::convert<bool>::decode(node, result));
    EXPECT_TRUE(result);
}

TEST_F(ConvertBoolTest_623, DecodeOff_Lowercase_623) {
    node = YAML::Node("off");
    EXPECT_TRUE(YAML::convert<bool>::decode(node, result));
    EXPECT_FALSE(result);
}

// ==================== Case insensitivity tests ====================

TEST_F(ConvertBoolTest_623, DecodeTrue_Uppercase_623) {
    node = YAML::Node("TRUE");
    EXPECT_TRUE(YAML::convert<bool>::decode(node, result));
    EXPECT_TRUE(result);
}

TEST_F(ConvertBoolTest_623, DecodeFalse_Uppercase_623) {
    node = YAML::Node("FALSE");
    EXPECT_TRUE(YAML::convert<bool>::decode(node, result));
    EXPECT_FALSE(result);
}

TEST_F(ConvertBoolTest_623, DecodeTrue_MixedCase_623) {
    node = YAML::Node("True");
    EXPECT_TRUE(YAML::convert<bool>::decode(node, result));
    EXPECT_TRUE(result);
}

TEST_F(ConvertBoolTest_623, DecodeFalse_MixedCase_623) {
    node = YAML::Node("False");
    EXPECT_TRUE(YAML::convert<bool>::decode(node, result));
    EXPECT_FALSE(result);
}

TEST_F(ConvertBoolTest_623, DecodeYes_Uppercase_623) {
    node = YAML::Node("YES");
    EXPECT_TRUE(YAML::convert<bool>::decode(node, result));
    EXPECT_TRUE(result);
}

TEST_F(ConvertBoolTest_623, DecodeNo_Uppercase_623) {
    node = YAML::Node("NO");
    EXPECT_TRUE(YAML::convert<bool>::decode(node, result));
    EXPECT_FALSE(result);
}

TEST_F(ConvertBoolTest_623, DecodeY_Uppercase_623) {
    node = YAML::Node("Y");
    EXPECT_TRUE(YAML::convert<bool>::decode(node, result));
    EXPECT_TRUE(result);
}

TEST_F(ConvertBoolTest_623, DecodeN_Uppercase_623) {
    node = YAML::Node("N");
    EXPECT_TRUE(YAML::convert<bool>::decode(node, result));
    EXPECT_FALSE(result);
}

TEST_F(ConvertBoolTest_623, DecodeOn_Uppercase_623) {
    node = YAML::Node("ON");
    EXPECT_TRUE(YAML::convert<bool>::decode(node, result));
    EXPECT_TRUE(result);
}

TEST_F(ConvertBoolTest_623, DecodeOff_Uppercase_623) {
    node = YAML::Node("OFF");
    EXPECT_TRUE(YAML::convert<bool>::decode(node, result));
    EXPECT_FALSE(result);
}

TEST_F(ConvertBoolTest_623, DecodeOn_MixedCase_623) {
    node = YAML::Node("On");
    EXPECT_TRUE(YAML::convert<bool>::decode(node, result));
    EXPECT_TRUE(result);
}

TEST_F(ConvertBoolTest_623, DecodeOff_MixedCase_623) {
    node = YAML::Node("Off");
    EXPECT_TRUE(YAML::convert<bool>::decode(node, result));
    EXPECT_FALSE(result);
}

TEST_F(ConvertBoolTest_623, DecodeYes_MixedCase_623) {
    node = YAML::Node("Yes");
    EXPECT_TRUE(YAML::convert<bool>::decode(node, result));
    EXPECT_TRUE(result);
}

TEST_F(ConvertBoolTest_623, DecodeNo_MixedCase_623) {
    node = YAML::Node("No");
    EXPECT_TRUE(YAML::convert<bool>::decode(node, result));
    EXPECT_FALSE(result);
}

// ==================== Error / invalid input tests ====================

TEST_F(ConvertBoolTest_623, DecodeInvalidString_623) {
    node = YAML::Node("invalid");
    EXPECT_FALSE(YAML::convert<bool>::decode(node, result));
}

TEST_F(ConvertBoolTest_623, DecodeEmptyString_623) {
    node = YAML::Node("");
    EXPECT_FALSE(YAML::convert<bool>::decode(node, result));
}

TEST_F(ConvertBoolTest_623, DecodeNumericOne_623) {
    node = YAML::Node("1");
    // "1" is not one of the recognized true/false names
    EXPECT_FALSE(YAML::convert<bool>::decode(node, result));
}

TEST_F(ConvertBoolTest_623, DecodeNumericZero_623) {
    node = YAML::Node("0");
    EXPECT_FALSE(YAML::convert<bool>::decode(node, result));
}

TEST_F(ConvertBoolTest_623, DecodeSequenceNode_623) {
    node = YAML::Node(YAML::NodeType::Sequence);
    node.push_back("true");
    EXPECT_FALSE(YAML::convert<bool>::decode(node, result));
}

TEST_F(ConvertBoolTest_623, DecodeMapNode_623) {
    node = YAML::Node(YAML::NodeType::Map);
    node["key"] = "value";
    EXPECT_FALSE(YAML::convert<bool>::decode(node, result));
}

TEST_F(ConvertBoolTest_623, DecodeNullNode_623) {
    node = YAML::Node(YAML::NodeType::Null);
    EXPECT_FALSE(YAML::convert<bool>::decode(node, result));
}

TEST_F(ConvertBoolTest_623, DecodeRandomText_623) {
    node = YAML::Node("maybe");
    EXPECT_FALSE(YAML::convert<bool>::decode(node, result));
}

TEST_F(ConvertBoolTest_623, DecodeTrueWithTrailingSpace_623) {
    node = YAML::Node("true ");
    // Has trailing space, not a flexible match
    EXPECT_FALSE(YAML::convert<bool>::decode(node, result));
}

TEST_F(ConvertBoolTest_623, DecodeTrueWithLeadingSpace_623) {
    node = YAML::Node(" true");
    EXPECT_FALSE(YAML::convert<bool>::decode(node, result));
}

TEST_F(ConvertBoolTest_623, DecodeTruePartialMatch_623) {
    node = YAML::Node("tru");
    EXPECT_FALSE(YAML::convert<bool>::decode(node, result));
}

TEST_F(ConvertBoolTest_623, DecodeFalsePartialMatch_623) {
    node = YAML::Node("fals");
    EXPECT_FALSE(YAML::convert<bool>::decode(node, result));
}

// ==================== Using Node::as<bool>() interface ====================

TEST_F(ConvertBoolTest_623, AsBoolean_True_623) {
    node = YAML::Node("true");
    EXPECT_TRUE(node.as<bool>());
}

TEST_F(ConvertBoolTest_623, AsBoolean_False_623) {
    node = YAML::Node("false");
    EXPECT_FALSE(node.as<bool>());
}

TEST_F(ConvertBoolTest_623, AsBoolean_WithFallback_InvalidInput_623) {
    node = YAML::Node("notabool");
    EXPECT_TRUE(node.as<bool>(true));
    EXPECT_FALSE(node.as<bool>(false));
}

TEST_F(ConvertBoolTest_623, AsBoolean_WithFallback_ValidInput_623) {
    node = YAML::Node("yes");
    EXPECT_TRUE(node.as<bool>(false));
}

TEST_F(ConvertBoolTest_623, DecodeYeS_AllCapsVariation_623) {
    node = YAML::Node("YeS");
    EXPECT_TRUE(YAML::convert<bool>::decode(node, result));
    EXPECT_TRUE(result);
}

TEST_F(ConvertBoolTest_623, DecodeTRUE_AllCaps_623) {
    node = YAML::Node("tRuE");
    EXPECT_TRUE(YAML::convert<bool>::decode(node, result));
    EXPECT_TRUE(result);
}

TEST_F(ConvertBoolTest_623, DecodeFALSE_AllCapsVariation_623) {
    node = YAML::Node("fAlSe");
    EXPECT_TRUE(YAML::convert<bool>::decode(node, result));
    EXPECT_FALSE(result);
}

// ==================== Boundary: single character tests ====================

TEST_F(ConvertBoolTest_623, DecodeSingleCharY_Lower_623) {
    node = YAML::Node("y");
    EXPECT_TRUE(YAML::convert<bool>::decode(node, result));
    EXPECT_TRUE(result);
}

TEST_F(ConvertBoolTest_623, DecodeSingleCharN_Lower_623) {
    node = YAML::Node("n");
    EXPECT_TRUE(YAML::convert<bool>::decode(node, result));
    EXPECT_FALSE(result);
}

TEST_F(ConvertBoolTest_623, DecodeSingleCharA_623) {
    node = YAML::Node("a");
    EXPECT_FALSE(YAML::convert<bool>::decode(node, result));
}

TEST_F(ConvertBoolTest_623, DecodeSingleCharT_623) {
    node = YAML::Node("t");
    EXPECT_FALSE(YAML::convert<bool>::decode(node, result));
}

TEST_F(ConvertBoolTest_623, DecodeSingleCharF_623) {
    node = YAML::Node("f");
    EXPECT_FALSE(YAML::convert<bool>::decode(node, result));
}

// ==================== Previous result not modified on failure ====================

TEST_F(ConvertBoolTest_623, ResultUnchangedOnFailure_623) {
    result = true;
    node = YAML::Node("notvalid");
    EXPECT_FALSE(YAML::convert<bool>::decode(node, result));
    // result should remain unchanged since decode failed
    EXPECT_TRUE(result);
}

TEST_F(ConvertBoolTest_623, ResultUnchangedOnFailure_FalseInitial_623) {
    result = false;
    node = YAML::Node("notvalid");
    EXPECT_FALSE(YAML::convert<bool>::decode(node, result));
    EXPECT_FALSE(result);
}
