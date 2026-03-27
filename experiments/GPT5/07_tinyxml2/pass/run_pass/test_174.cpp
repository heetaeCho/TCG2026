#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLUtilToBoolTest_174 : public ::testing::Test {
protected:
    XMLUtil util;
};

/**
 * Normal operation: numeric zero should map to false.
 */
TEST_F(XMLUtilToBoolTest_174, NumericZeroReturnsFalse_174) {
    bool value = true; // preset to opposite
    bool result = util.ToBool("0", &value);

    EXPECT_TRUE(result);
    EXPECT_FALSE(value);
}

/**
 * Normal operation: numeric non-zero should map to true.
 */
TEST_F(XMLUtilToBoolTest_174, NumericNonZeroReturnsTrue_174) {
    bool value = false;
    bool result = util.ToBool("1", &value);

    EXPECT_TRUE(result);
    EXPECT_TRUE(value);
}

/**
 * Normal operation: positive numeric string should map to true.
 */
TEST_F(XMLUtilToBoolTest_174, PositiveNumberReturnsTrue_174) {
    bool value = false;
    bool result = util.ToBool("42", &value);

    EXPECT_TRUE(result);
    EXPECT_TRUE(value);
}

/**
 * Boundary condition: negative numeric string should still be treated as non-zero.
 */
TEST_F(XMLUtilToBoolTest_174, NegativeNumberReturnsTrue_174) {
    bool value = false;
    bool result = util.ToBool("-1", &value);

    EXPECT_TRUE(result);
    EXPECT_TRUE(value);
}

/**
 * Normal operation: lowercase textual true.
 */
TEST_F(XMLUtilToBoolTest_174, LowercaseTrueStringReturnsTrue_174) {
    bool value = false;
    bool result = util.ToBool("true", &value);

    EXPECT_TRUE(result);
    EXPECT_TRUE(value);
}

/**
 * Normal operation: mixed case textual true.
 */
TEST_F(XMLUtilToBoolTest_174, MixedCaseTrueStringReturnsTrue_174) {
    bool value = false;
    bool result = util.ToBool("True", &value);

    EXPECT_TRUE(result);
    EXPECT_TRUE(value);
}

/**
 * Normal operation: uppercase textual true.
 */
TEST_F(XMLUtilToBoolTest_174, UppercaseTrueStringReturnsTrue_174) {
    bool value = false;
    bool result = util.ToBool("TRUE", &value);

    EXPECT_TRUE(result);
    EXPECT_TRUE(value);
}

/**
 * Normal operation: lowercase textual false.
 */
TEST_F(XMLUtilToBoolTest_174, LowercaseFalseStringReturnsFalse_174) {
    bool value = true;
    bool result = util.ToBool("false", &value);

    EXPECT_TRUE(result);
    EXPECT_FALSE(value);
}

/**
 * Normal operation: mixed case textual false.
 */
TEST_F(XMLUtilToBoolTest_174, MixedCaseFalseStringReturnsFalse_174) {
    bool value = true;
    bool result = util.ToBool("False", &value);

    EXPECT_TRUE(result);
    EXPECT_FALSE(value);
}

/**
 * Normal operation: uppercase textual false.
 */
TEST_F(XMLUtilToBoolTest_174, UppercaseFalseStringReturnsFalse_174) {
    bool value = true;
    bool result = util.ToBool("FALSE", &value);

    EXPECT_TRUE(result);
    EXPECT_FALSE(value);
}

/**
 * Exceptional case: unrecognized string should fail and not modify output.
 */
TEST_F(XMLUtilToBoolTest_174, InvalidStringReturnsFalse_174) {
    bool value = true;
    bool result = util.ToBool("notabool", &value);

    EXPECT_FALSE(result);
    EXPECT_TRUE(value); // unchanged
}

/**
 * Boundary condition: empty string should fail.
 */
TEST_F(XMLUtilToBoolTest_174, EmptyStringReturnsFalse_174) {
    bool value = false;
    bool result = util.ToBool("", &value);

    EXPECT_FALSE(result);
    EXPECT_FALSE(value); // unchanged
}

/**
 * Boundary condition: whitespace-only string should fail.
 */
TEST_F(XMLUtilToBoolTest_174, WhitespaceStringReturnsFalse_174) {
    bool value = true;
    bool result = util.ToBool("   ", &value);

    EXPECT_FALSE(result);
    EXPECT_TRUE(value); // unchanged
}
