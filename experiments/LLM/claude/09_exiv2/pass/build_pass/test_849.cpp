#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <stdexcept>

using namespace Exiv2;

class XmpArrayValueTest_849 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test that toUint32 returns correct value for a simple positive integer
TEST_F(XmpArrayValueTest_849, ToUint32_SimplePositiveInteger_849) {
    XmpArrayValue val(xmpSeq);
    val.read("42");
    EXPECT_EQ(42u, val.toUint32(0));
}

// Test that toUint32 returns correct value for zero
TEST_F(XmpArrayValueTest_849, ToUint32_Zero_849) {
    XmpArrayValue val(xmpSeq);
    val.read("0");
    EXPECT_EQ(0u, val.toUint32(0));
}

// Test that toUint32 returns correct value for a large number
TEST_F(XmpArrayValueTest_849, ToUint32_LargeNumber_849) {
    XmpArrayValue val(xmpSeq);
    val.read("4294967295");
    uint32_t result = val.toUint32(0);
    EXPECT_EQ(4294967295u, result);
}

// Test that toUint32 works with multiple values and correct index
TEST_F(XmpArrayValueTest_849, ToUint32_MultipleValues_849) {
    XmpArrayValue val(xmpSeq);
    val.read("10");
    val.read("20");
    val.read("30");
    EXPECT_EQ(10u, val.toUint32(0));
    EXPECT_EQ(20u, val.toUint32(1));
    EXPECT_EQ(30u, val.toUint32(2));
}

// Test that toUint32 throws when index is out of range
TEST_F(XmpArrayValueTest_849, ToUint32_OutOfRangeIndex_849) {
    XmpArrayValue val(xmpSeq);
    val.read("42");
    EXPECT_THROW(val.toUint32(1), std::out_of_range);
}

// Test that toUint32 throws on empty value
TEST_F(XmpArrayValueTest_849, ToUint32_EmptyValue_ThrowsOutOfRange_849) {
    XmpArrayValue val(xmpSeq);
    EXPECT_THROW(val.toUint32(0), std::out_of_range);
}

// Test count after reading values
TEST_F(XmpArrayValueTest_849, Count_AfterReads_849) {
    XmpArrayValue val(xmpSeq);
    EXPECT_EQ(0u, val.count());
    val.read("10");
    EXPECT_EQ(1u, val.count());
    val.read("20");
    EXPECT_EQ(2u, val.count());
}

// Test toString for a given index
TEST_F(XmpArrayValueTest_849, ToString_ValidIndex_849) {
    XmpArrayValue val(xmpSeq);
    val.read("hello");
    val.read("world");
    EXPECT_EQ("hello", val.toString(0));
    EXPECT_EQ("world", val.toString(1));
}

// Test toInt64 returns correct value
TEST_F(XmpArrayValueTest_849, ToInt64_SimpleValue_849) {
    XmpArrayValue val(xmpSeq);
    val.read("12345");
    EXPECT_EQ(12345, val.toInt64(0));
}

// Test toFloat returns correct value
TEST_F(XmpArrayValueTest_849, ToFloat_SimpleValue_849) {
    XmpArrayValue val(xmpSeq);
    val.read("3.14");
    EXPECT_NEAR(3.14f, val.toFloat(0), 0.01f);
}

// Test toRational returns correct value
TEST_F(XmpArrayValueTest_849, ToRational_SimpleValue_849) {
    XmpArrayValue val(xmpSeq);
    val.read("5");
    Rational r = val.toRational(0);
    // Expecting the rational representation of 5
    EXPECT_EQ(5, r.first);
    EXPECT_EQ(1, r.second);
}

// Test toUint32 with non-numeric string (behavior depends on parseUint32)
TEST_F(XmpArrayValueTest_849, ToUint32_NonNumericString_849) {
    XmpArrayValue val(xmpSeq);
    val.read("abc");
    // Should return some value (likely 0) and ok_ should be false
    uint32_t result = val.toUint32(0);
    EXPECT_EQ(0u, result);
    EXPECT_FALSE(val.ok());
}

// Test ok() is true after successful numeric conversion
TEST_F(XmpArrayValueTest_849, OkTrue_AfterValidConversion_849) {
    XmpArrayValue val(xmpSeq);
    val.read("100");
    val.toUint32(0);
    EXPECT_TRUE(val.ok());
}

// Test clone produces equivalent value
TEST_F(XmpArrayValueTest_849, Clone_ProducesEquivalentValue_849) {
    XmpArrayValue val(xmpSeq);
    val.read("42");
    val.read("99");
    auto cloned = val.clone();
    ASSERT_NE(nullptr, cloned);
    EXPECT_EQ(2u, cloned->count());
    EXPECT_EQ("42", cloned->toString(0));
    EXPECT_EQ("99", cloned->toString(1));
}

// Test typeId returns the type passed in constructor
TEST_F(XmpArrayValueTest_849, TypeId_ReturnsConstructorType_849) {
    XmpArrayValue val(xmpSeq);
    EXPECT_EQ(xmpSeq, val.typeId());
}

// Test with xmpBag type
TEST_F(XmpArrayValueTest_849, ToUint32_XmpBagType_849) {
    XmpArrayValue val(xmpBag);
    val.read("7");
    EXPECT_EQ(7u, val.toUint32(0));
}

// Test with xmpAlt type
TEST_F(XmpArrayValueTest_849, ToUint32_XmpAltType_849) {
    XmpArrayValue val(xmpAlt);
    val.read("255");
    EXPECT_EQ(255u, val.toUint32(0));
}

// Test write output
TEST_F(XmpArrayValueTest_849, Write_OutputsValues_849) {
    XmpArrayValue val(xmpSeq);
    val.read("alpha");
    val.read("beta");
    std::ostringstream os;
    val.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(std::string::npos, output.find("alpha"));
    EXPECT_NE(std::string::npos, output.find("beta"));
}

// Test toUint32 with value "1"
TEST_F(XmpArrayValueTest_849, ToUint32_One_849) {
    XmpArrayValue val(xmpSeq);
    val.read("1");
    EXPECT_EQ(1u, val.toUint32(0));
}

// Test read returns success
TEST_F(XmpArrayValueTest_849, Read_ReturnsZeroOnSuccess_849) {
    XmpArrayValue val(xmpSeq);
    int result = val.read("test");
    EXPECT_EQ(0, result);
}

// Test multiple conversions maintain ok state
TEST_F(XmpArrayValueTest_849, ToUint32_MultipleConversions_OkState_849) {
    XmpArrayValue val(xmpSeq);
    val.read("10");
    val.read("20");
    val.toUint32(0);
    EXPECT_TRUE(val.ok());
    val.toUint32(1);
    EXPECT_TRUE(val.ok());
}

// Test negative number handling for toUint32
TEST_F(XmpArrayValueTest_849, ToUint32_NegativeNumber_849) {
    XmpArrayValue val(xmpSeq);
    val.read("-1");
    // Behavior with negative is implementation-defined, but should not crash
    val.toUint32(0);
    // Just verify it doesn't crash; ok() may be false
}

// Test with whitespace in value
TEST_F(XmpArrayValueTest_849, ToUint32_WithWhitespace_849) {
    XmpArrayValue val(xmpSeq);
    val.read(" 42 ");
    // Depending on implementation, may parse as 42 or fail
    uint32_t result = val.toUint32(0);
    // At least should not crash
    (void)result;
}
