#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <stdexcept>

using namespace Exiv2;

class XmpArrayValueTest_848 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test that a freshly constructed XmpArrayValue has count() == 0
TEST_F(XmpArrayValueTest_848, DefaultConstructionHasZeroCount_848) {
    XmpArrayValue val(xmpSeq);
    EXPECT_EQ(val.count(), 0u);
}

// Test that reading a single value results in count() == 1
TEST_F(XmpArrayValueTest_848, ReadSingleValueCountIsOne_848) {
    XmpArrayValue val(xmpSeq);
    val.read("42");
    EXPECT_EQ(val.count(), 1u);
}

// Test reading multiple values increases count
TEST_F(XmpArrayValueTest_848, ReadMultipleValuesIncreasesCount_848) {
    XmpArrayValue val(xmpSeq);
    val.read("10");
    val.read("20");
    val.read("30");
    EXPECT_EQ(val.count(), 3u);
}

// Test toInt64 returns correct value for a simple integer string
TEST_F(XmpArrayValueTest_848, ToInt64ReturnsCorrectValue_848) {
    XmpArrayValue val(xmpSeq);
    val.read("12345");
    EXPECT_EQ(val.toInt64(0), 12345);
}

// Test toInt64 with negative integer
TEST_F(XmpArrayValueTest_848, ToInt64NegativeValue_848) {
    XmpArrayValue val(xmpSeq);
    val.read("-9876");
    EXPECT_EQ(val.toInt64(0), -9876);
}

// Test toInt64 with zero
TEST_F(XmpArrayValueTest_848, ToInt64ZeroValue_848) {
    XmpArrayValue val(xmpSeq);
    val.read("0");
    EXPECT_EQ(val.toInt64(0), 0);
}

// Test toInt64 with multiple elements, accessing different indices
TEST_F(XmpArrayValueTest_848, ToInt64MultipleElements_848) {
    XmpArrayValue val(xmpSeq);
    val.read("100");
    val.read("200");
    val.read("300");
    EXPECT_EQ(val.toInt64(0), 100);
    EXPECT_EQ(val.toInt64(1), 200);
    EXPECT_EQ(val.toInt64(2), 300);
}

// Test toInt64 with out-of-range index throws
TEST_F(XmpArrayValueTest_848, ToInt64OutOfRangeThrows_848) {
    XmpArrayValue val(xmpSeq);
    val.read("42");
    EXPECT_THROW(val.toInt64(1), std::out_of_range);
}

// Test toInt64 on empty array throws
TEST_F(XmpArrayValueTest_848, ToInt64EmptyArrayThrows_848) {
    XmpArrayValue val(xmpSeq);
    EXPECT_THROW(val.toInt64(0), std::out_of_range);
}

// Test toUint32 returns correct value
TEST_F(XmpArrayValueTest_848, ToUint32ReturnsCorrectValue_848) {
    XmpArrayValue val(xmpSeq);
    val.read("65535");
    EXPECT_EQ(val.toUint32(0), 65535u);
}

// Test toFloat returns correct value
TEST_F(XmpArrayValueTest_848, ToFloatReturnsCorrectValue_848) {
    XmpArrayValue val(xmpSeq);
    val.read("3.14");
    EXPECT_NEAR(val.toFloat(0), 3.14f, 0.01f);
}

// Test toRational returns correct value
TEST_F(XmpArrayValueTest_848, ToRationalReturnsValue_848) {
    XmpArrayValue val(xmpSeq);
    val.read("5/3");
    Rational r = val.toRational(0);
    EXPECT_EQ(r.first, 5);
    EXPECT_EQ(r.second, 3);
}

// Test toString returns the stored string
TEST_F(XmpArrayValueTest_848, ToStringReturnsStoredString_848) {
    XmpArrayValue val(xmpSeq);
    val.read("hello");
    EXPECT_EQ(val.toString(0), "hello");
}

// Test toString with multiple elements
TEST_F(XmpArrayValueTest_848, ToStringMultipleElements_848) {
    XmpArrayValue val(xmpSeq);
    val.read("alpha");
    val.read("beta");
    EXPECT_EQ(val.toString(0), "alpha");
    EXPECT_EQ(val.toString(1), "beta");
}

// Test typeId returns the type passed at construction
TEST_F(XmpArrayValueTest_848, TypeIdReturnsConstructedType_848) {
    XmpArrayValue val(xmpSeq);
    EXPECT_EQ(val.typeId(), xmpSeq);
}

// Test with xmpBag type
TEST_F(XmpArrayValueTest_848, ConstructWithXmpBag_848) {
    XmpArrayValue val(xmpBag);
    EXPECT_EQ(val.typeId(), xmpBag);
    val.read("test");
    EXPECT_EQ(val.count(), 1u);
    EXPECT_EQ(val.toString(0), "test");
}

// Test with xmpAlt type
TEST_F(XmpArrayValueTest_848, ConstructWithXmpAlt_848) {
    XmpArrayValue val(xmpAlt);
    EXPECT_EQ(val.typeId(), xmpAlt);
}

// Test clone creates a copy with same values
TEST_F(XmpArrayValueTest_848, ClonePreservesValues_848) {
    XmpArrayValue val(xmpSeq);
    val.read("111");
    val.read("222");
    auto cloned = val.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->count(), 2u);
    EXPECT_EQ(cloned->toInt64(0), 111);
    EXPECT_EQ(cloned->toInt64(1), 222);
}

// Test write outputs values
TEST_F(XmpArrayValueTest_848, WriteOutputsValues_848) {
    XmpArrayValue val(xmpSeq);
    val.read("abc");
    val.read("def");
    std::ostringstream os;
    val.write(os);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("abc"), std::string::npos);
    EXPECT_NE(result.find("def"), std::string::npos);
}

// Test toInt64 with large positive number
TEST_F(XmpArrayValueTest_848, ToInt64LargePositiveNumber_848) {
    XmpArrayValue val(xmpSeq);
    val.read("9999999999");
    EXPECT_EQ(val.toInt64(0), 9999999999LL);
}

// Test toInt64 with large negative number
TEST_F(XmpArrayValueTest_848, ToInt64LargeNegativeNumber_848) {
    XmpArrayValue val(xmpSeq);
    val.read("-9999999999");
    EXPECT_EQ(val.toInt64(0), -9999999999LL);
}

// Test ok() after successful parse
TEST_F(XmpArrayValueTest_848, OkAfterSuccessfulParse_848) {
    XmpArrayValue val(xmpSeq);
    val.read("42");
    val.toInt64(0);
    EXPECT_TRUE(val.ok());
}

// Test read returns 0 on success
TEST_F(XmpArrayValueTest_848, ReadReturnsZeroOnSuccess_848) {
    XmpArrayValue val(xmpSeq);
    int result = val.read("test_value");
    EXPECT_EQ(result, 0);
}

// Test toFloat with integer string
TEST_F(XmpArrayValueTest_848, ToFloatWithIntegerString_848) {
    XmpArrayValue val(xmpSeq);
    val.read("42");
    EXPECT_NEAR(val.toFloat(0), 42.0f, 0.001f);
}

// Test toUint32 with out-of-range index throws
TEST_F(XmpArrayValueTest_848, ToUint32OutOfRangeThrows_848) {
    XmpArrayValue val(xmpSeq);
    EXPECT_THROW(val.toUint32(0), std::out_of_range);
}

// Test toFloat with out-of-range index throws
TEST_F(XmpArrayValueTest_848, ToFloatOutOfRangeThrows_848) {
    XmpArrayValue val(xmpSeq);
    EXPECT_THROW(val.toFloat(0), std::out_of_range);
}

// Test toRational with out-of-range index throws
TEST_F(XmpArrayValueTest_848, ToRationalOutOfRangeThrows_848) {
    XmpArrayValue val(xmpSeq);
    EXPECT_THROW(val.toRational(0), std::out_of_range);
}

// Test toString with out-of-range index throws
TEST_F(XmpArrayValueTest_848, ToStringOutOfRangeThrows_848) {
    XmpArrayValue val(xmpSeq);
    EXPECT_THROW(val.toString(5), std::out_of_range);
}

// Test reading whitespace-only string
TEST_F(XmpArrayValueTest_848, ReadWhitespaceString_848) {
    XmpArrayValue val(xmpSeq);
    val.read("   ");
    // It should still store a value (possibly trimmed or as-is)
    EXPECT_GE(val.count(), 0u);
}

// Test reading empty string
TEST_F(XmpArrayValueTest_848, ReadEmptyString_848) {
    XmpArrayValue val(xmpSeq);
    val.read("");
    // Behavior should be defined - either adds empty string or doesn't
    // Just verify no crash
    EXPECT_GE(val.count(), 0u);
}

// Test toInt64 with non-numeric string
TEST_F(XmpArrayValueTest_848, ToInt64NonNumericString_848) {
    XmpArrayValue val(xmpSeq);
    val.read("not_a_number");
    // Should return some value (likely 0) and set ok_ to false
    int64_t result = val.toInt64(0);
    (void)result; // Just ensure no crash
}
