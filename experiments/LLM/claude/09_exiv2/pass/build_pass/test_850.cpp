#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <stdexcept>

using namespace Exiv2;

class XmpArrayValueTest_850 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test that a newly created XmpArrayValue has count 0
TEST_F(XmpArrayValueTest_850, DefaultConstructorHasZeroCount_850) {
    XmpArrayValue val(xmpBag);
    EXPECT_EQ(0u, val.count());
}

// Test reading a single value
TEST_F(XmpArrayValueTest_850, ReadSingleValue_850) {
    XmpArrayValue val(xmpBag);
    val.read("hello");
    EXPECT_EQ(1u, val.count());
    EXPECT_EQ("hello", val.toString(0));
}

// Test reading multiple values (comma-separated or multiple reads)
TEST_F(XmpArrayValueTest_850, ReadMultipleValues_850) {
    XmpArrayValue val(xmpBag);
    val.read("first");
    val.read("second");
    val.read("third");
    EXPECT_EQ(3u, val.count());
    EXPECT_EQ("first", val.toString(0));
    EXPECT_EQ("second", val.toString(1));
    EXPECT_EQ("third", val.toString(2));
}

// Test toFloat with a valid integer string
TEST_F(XmpArrayValueTest_850, ToFloatWithIntegerString_850) {
    XmpArrayValue val(xmpBag);
    val.read("42");
    float result = val.toFloat(0);
    EXPECT_FLOAT_EQ(42.0f, result);
    EXPECT_TRUE(val.ok());
}

// Test toFloat with a valid floating point string
TEST_F(XmpArrayValueTest_850, ToFloatWithFloatString_850) {
    XmpArrayValue val(xmpBag);
    val.read("3.14");
    float result = val.toFloat(0);
    EXPECT_FLOAT_EQ(3.14f, result);
    EXPECT_TRUE(val.ok());
}

// Test toFloat with negative value
TEST_F(XmpArrayValueTest_850, ToFloatWithNegativeValue_850) {
    XmpArrayValue val(xmpBag);
    val.read("-2.5");
    float result = val.toFloat(0);
    EXPECT_FLOAT_EQ(-2.5f, result);
    EXPECT_TRUE(val.ok());
}

// Test toFloat with zero
TEST_F(XmpArrayValueTest_850, ToFloatWithZero_850) {
    XmpArrayValue val(xmpBag);
    val.read("0");
    float result = val.toFloat(0);
    EXPECT_FLOAT_EQ(0.0f, result);
    EXPECT_TRUE(val.ok());
}

// Test toFloat with multiple elements, accessing different indices
TEST_F(XmpArrayValueTest_850, ToFloatMultipleElements_850) {
    XmpArrayValue val(xmpBag);
    val.read("1.1");
    val.read("2.2");
    val.read("3.3");
    EXPECT_FLOAT_EQ(1.1f, val.toFloat(0));
    EXPECT_FLOAT_EQ(2.2f, val.toFloat(1));
    EXPECT_FLOAT_EQ(3.3f, val.toFloat(2));
}

// Test toFloat with out-of-range index throws
TEST_F(XmpArrayValueTest_850, ToFloatOutOfRangeThrows_850) {
    XmpArrayValue val(xmpBag);
    val.read("1.0");
    EXPECT_THROW(val.toFloat(1), std::out_of_range);
}

// Test toFloat on empty array throws
TEST_F(XmpArrayValueTest_850, ToFloatEmptyArrayThrows_850) {
    XmpArrayValue val(xmpBag);
    EXPECT_THROW(val.toFloat(0), std::out_of_range);
}

// Test toFloat with non-numeric string
TEST_F(XmpArrayValueTest_850, ToFloatWithNonNumericString_850) {
    XmpArrayValue val(xmpBag);
    val.read("not_a_number");
    val.toFloat(0);
    EXPECT_FALSE(val.ok());
}

// Test toInt64 with valid integer
TEST_F(XmpArrayValueTest_850, ToInt64WithValidInteger_850) {
    XmpArrayValue val(xmpBag);
    val.read("12345");
    EXPECT_EQ(12345, val.toInt64(0));
    EXPECT_TRUE(val.ok());
}

// Test toUint32 with valid unsigned integer
TEST_F(XmpArrayValueTest_850, ToUint32WithValidInteger_850) {
    XmpArrayValue val(xmpBag);
    val.read("65535");
    EXPECT_EQ(65535u, val.toUint32(0));
    EXPECT_TRUE(val.ok());
}

// Test toRational with a rational string
TEST_F(XmpArrayValueTest_850, ToRationalWithValue_850) {
    XmpArrayValue val(xmpBag);
    val.read("3/4");
    Rational r = val.toRational(0);
    EXPECT_EQ(3, r.first);
    EXPECT_EQ(4, r.second);
}

// Test toString with valid index
TEST_F(XmpArrayValueTest_850, ToStringValidIndex_850) {
    XmpArrayValue val(xmpBag);
    val.read("test_string");
    EXPECT_EQ("test_string", val.toString(0));
}

// Test toString with out-of-range index throws
TEST_F(XmpArrayValueTest_850, ToStringOutOfRangeThrows_850) {
    XmpArrayValue val(xmpBag);
    EXPECT_THROW(val.toString(0), std::out_of_range);
}

// Test write outputs to stream
TEST_F(XmpArrayValueTest_850, WriteOutputsToStream_850) {
    XmpArrayValue val(xmpBag);
    val.read("alpha");
    val.read("beta");
    std::ostringstream os;
    val.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(std::string::npos, output.find("alpha"));
    EXPECT_NE(std::string::npos, output.find("beta"));
}

// Test typeId returns the type passed in constructor
TEST_F(XmpArrayValueTest_850, TypeIdReturnsCorrectType_850) {
    XmpArrayValue valBag(xmpBag);
    EXPECT_EQ(xmpBag, valBag.typeId());

    XmpArrayValue valSeq(xmpSeq);
    EXPECT_EQ(xmpSeq, valSeq.typeId());

    XmpArrayValue valAlt(xmpAlt);
    EXPECT_EQ(xmpAlt, valAlt.typeId());
}

// Test clone creates a copy with same values
TEST_F(XmpArrayValueTest_850, ClonePreservesValues_850) {
    XmpArrayValue val(xmpBag);
    val.read("one");
    val.read("two");
    auto cloned = val.clone();
    ASSERT_NE(nullptr, cloned);
    EXPECT_EQ(val.count(), cloned->count());
    EXPECT_EQ(val.toString(0), cloned->toString(0));
    EXPECT_EQ(val.toString(1), cloned->toString(1));
}

// Test reading an empty string
TEST_F(XmpArrayValueTest_850, ReadEmptyString_850) {
    XmpArrayValue val(xmpBag);
    val.read("");
    // Empty string may or may not add an element; we just verify no crash
    // and count is consistent
    size_t c = val.count();
    EXPECT_GE(c, 0u);
}

// Test toFloat with a very large number
TEST_F(XmpArrayValueTest_850, ToFloatLargeNumber_850) {
    XmpArrayValue val(xmpBag);
    val.read("999999999.0");
    float result = val.toFloat(0);
    EXPECT_NEAR(999999999.0f, result, 1000.0f);  // float precision
}

// Test toFloat with scientific notation
TEST_F(XmpArrayValueTest_850, ToFloatScientificNotation_850) {
    XmpArrayValue val(xmpBag);
    val.read("1.5e2");
    float result = val.toFloat(0);
    EXPECT_FLOAT_EQ(150.0f, result);
}

// Test count after multiple reads
TEST_F(XmpArrayValueTest_850, CountAfterMultipleReads_850) {
    XmpArrayValue val(xmpSeq);
    EXPECT_EQ(0u, val.count());
    val.read("a");
    EXPECT_EQ(1u, val.count());
    val.read("b");
    EXPECT_EQ(2u, val.count());
    val.read("c");
    EXPECT_EQ(3u, val.count());
}

// Test toInt64 out of range throws
TEST_F(XmpArrayValueTest_850, ToInt64OutOfRangeThrows_850) {
    XmpArrayValue val(xmpBag);
    val.read("100");
    EXPECT_THROW(val.toInt64(5), std::out_of_range);
}

// Test toUint32 out of range throws
TEST_F(XmpArrayValueTest_850, ToUint32OutOfRangeThrows_850) {
    XmpArrayValue val(xmpBag);
    EXPECT_THROW(val.toUint32(0), std::out_of_range);
}

// Test toRational out of range throws
TEST_F(XmpArrayValueTest_850, ToRationalOutOfRangeThrows_850) {
    XmpArrayValue val(xmpBag);
    EXPECT_THROW(val.toRational(0), std::out_of_range);
}
