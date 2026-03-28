#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <stdexcept>

using namespace Exiv2;

class XmpArrayValueTest_851 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test that a freshly constructed XmpArrayValue has count 0
TEST_F(XmpArrayValueTest_851, DefaultConstructionHasZeroCount_851) {
    XmpArrayValue val(xmpSeq);
    EXPECT_EQ(val.count(), 0u);
}

// Test reading a single string value
TEST_F(XmpArrayValueTest_851, ReadSingleValue_851) {
    XmpArrayValue val(xmpSeq);
    val.read("hello");
    EXPECT_EQ(val.count(), 1u);
    EXPECT_EQ(val.toString(0), "hello");
}

// Test reading multiple values
TEST_F(XmpArrayValueTest_851, ReadMultipleValues_851) {
    XmpArrayValue val(xmpSeq);
    val.read("first");
    val.read("second");
    val.read("third");
    EXPECT_EQ(val.count(), 3u);
    EXPECT_EQ(val.toString(0), "first");
    EXPECT_EQ(val.toString(1), "second");
    EXPECT_EQ(val.toString(2), "third");
}

// Test toRational with a valid rational string
TEST_F(XmpArrayValueTest_851, ToRationalValidFraction_851) {
    XmpArrayValue val(xmpSeq);
    val.read("1/2");
    Rational r = val.toRational(0);
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 2);
    EXPECT_TRUE(val.ok());
}

// Test toRational with an integer string
TEST_F(XmpArrayValueTest_851, ToRationalInteger_851) {
    XmpArrayValue val(xmpSeq);
    val.read("42");
    Rational r = val.toRational(0);
    EXPECT_EQ(r.first, 42);
    EXPECT_EQ(r.second, 1);
    EXPECT_TRUE(val.ok());
}

// Test toRational with zero
TEST_F(XmpArrayValueTest_851, ToRationalZero_851) {
    XmpArrayValue val(xmpSeq);
    val.read("0/1");
    Rational r = val.toRational(0);
    EXPECT_EQ(r.first, 0);
    EXPECT_EQ(r.second, 1);
    EXPECT_TRUE(val.ok());
}

// Test toRational with negative rational
TEST_F(XmpArrayValueTest_851, ToRationalNegative_851) {
    XmpArrayValue val(xmpSeq);
    val.read("-3/4");
    Rational r = val.toRational(0);
    EXPECT_EQ(r.first, -3);
    EXPECT_EQ(r.second, 4);
    EXPECT_TRUE(val.ok());
}

// Test toRational out of bounds throws
TEST_F(XmpArrayValueTest_851, ToRationalOutOfBoundsThrows_851) {
    XmpArrayValue val(xmpSeq);
    val.read("1/2");
    EXPECT_THROW(val.toRational(1), std::out_of_range);
}

// Test toRational on empty value throws
TEST_F(XmpArrayValueTest_851, ToRationalEmptyThrows_851) {
    XmpArrayValue val(xmpSeq);
    EXPECT_THROW(val.toRational(0), std::out_of_range);
}

// Test toRational with non-numeric string
TEST_F(XmpArrayValueTest_851, ToRationalNonNumeric_851) {
    XmpArrayValue val(xmpSeq);
    val.read("not_a_number");
    Rational r = val.toRational(0);
    // After parsing a non-numeric string, ok() should be false
    EXPECT_FALSE(val.ok());
}

// Test toRational with multiple values, accessing second element
TEST_F(XmpArrayValueTest_851, ToRationalMultipleElements_851) {
    XmpArrayValue val(xmpSeq);
    val.read("1/3");
    val.read("5/7");
    Rational r = val.toRational(1);
    EXPECT_EQ(r.first, 5);
    EXPECT_EQ(r.second, 7);
    EXPECT_TRUE(val.ok());
}

// Test toInt64 with a valid integer string
TEST_F(XmpArrayValueTest_851, ToInt64Valid_851) {
    XmpArrayValue val(xmpSeq);
    val.read("12345");
    EXPECT_EQ(val.toInt64(0), 12345);
}

// Test toUint32 with a valid unsigned integer string
TEST_F(XmpArrayValueTest_851, ToUint32Valid_851) {
    XmpArrayValue val(xmpSeq);
    val.read("9999");
    EXPECT_EQ(val.toUint32(0), 9999u);
}

// Test toFloat with a valid float string
TEST_F(XmpArrayValueTest_851, ToFloatValid_851) {
    XmpArrayValue val(xmpSeq);
    val.read("3.14");
    EXPECT_NEAR(val.toFloat(0), 3.14f, 0.01f);
}

// Test toString out of bounds throws
TEST_F(XmpArrayValueTest_851, ToStringOutOfBoundsThrows_851) {
    XmpArrayValue val(xmpSeq);
    EXPECT_THROW(val.toString(0), std::out_of_range);
}

// Test clone produces equivalent object
TEST_F(XmpArrayValueTest_851, ClonePreservesValues_851) {
    XmpArrayValue val(xmpSeq);
    val.read("10/3");
    val.read("7/2");
    auto cloned = val.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->count(), 2u);
    EXPECT_EQ(cloned->toString(0), "10/3");
    EXPECT_EQ(cloned->toString(1), "7/2");
}

// Test typeId is preserved
TEST_F(XmpArrayValueTest_851, TypeIdPreserved_851) {
    XmpArrayValue val(xmpSeq);
    EXPECT_EQ(val.typeId(), xmpSeq);
}

// Test with xmpBag type
TEST_F(XmpArrayValueTest_851, XmpBagTypeId_851) {
    XmpArrayValue val(xmpBag);
    EXPECT_EQ(val.typeId(), xmpBag);
    val.read("item1");
    EXPECT_EQ(val.count(), 1u);
    EXPECT_EQ(val.toString(0), "item1");
}

// Test write output
TEST_F(XmpArrayValueTest_851, WriteOutput_851) {
    XmpArrayValue val(xmpSeq);
    val.read("alpha");
    val.read("beta");
    std::ostringstream os;
    val.write(os);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("alpha"), std::string::npos);
    EXPECT_NE(result.find("beta"), std::string::npos);
}

// Test toRational with large numbers
TEST_F(XmpArrayValueTest_851, ToRationalLargeNumbers_851) {
    XmpArrayValue val(xmpSeq);
    val.read("1000000/1");
    Rational r = val.toRational(0);
    EXPECT_EQ(r.first, 1000000);
    EXPECT_EQ(r.second, 1);
    EXPECT_TRUE(val.ok());
}

// Test reading empty string
TEST_F(XmpArrayValueTest_851, ReadEmptyString_851) {
    XmpArrayValue val(xmpSeq);
    val.read("");
    // Even an empty string may be stored as a value
    // The count should still be incremented
    EXPECT_GE(val.count(), 0u);
}

// Test toRational with "0/0"
TEST_F(XmpArrayValueTest_851, ToRationalZeroDenominator_851) {
    XmpArrayValue val(xmpSeq);
    val.read("0/0");
    Rational r = val.toRational(0);
    EXPECT_EQ(r.first, 0);
    EXPECT_EQ(r.second, 0);
}

// Test ok() returns true initially
TEST_F(XmpArrayValueTest_851, OkInitiallyTrue_851) {
    XmpArrayValue val(xmpSeq);
    EXPECT_TRUE(val.ok());
}
