#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <stdexcept>

using namespace Exiv2;

class XmpArrayValueTest_847 : public ::testing::Test {
protected:
    void SetUp() override {
        value_ = std::make_unique<XmpArrayValue>(xmpBag);
    }

    std::unique_ptr<XmpArrayValue> value_;
};

// Test that a newly constructed XmpArrayValue has count 0
TEST_F(XmpArrayValueTest_847, DefaultConstructionHasZeroCount_847) {
    EXPECT_EQ(0u, value_->count());
}

// Test that typeId returns the type passed in constructor
TEST_F(XmpArrayValueTest_847, TypeIdReturnsConstructedType_847) {
    EXPECT_EQ(xmpBag, value_->typeId());

    XmpArrayValue seqValue(xmpSeq);
    EXPECT_EQ(xmpSeq, seqValue.typeId());

    XmpArrayValue altValue(xmpAlt);
    EXPECT_EQ(xmpAlt, altValue.typeId());
}

// Test reading a single value
TEST_F(XmpArrayValueTest_847, ReadSingleValue_847) {
    int result = value_->read("hello");
    EXPECT_EQ(0, result);
    EXPECT_EQ(1u, value_->count());
    EXPECT_EQ("hello", value_->toString(0));
}

// Test reading multiple values
TEST_F(XmpArrayValueTest_847, ReadMultipleValues_847) {
    value_->read("first");
    value_->read("second");
    value_->read("third");
    EXPECT_EQ(3u, value_->count());
    EXPECT_EQ("first", value_->toString(0));
    EXPECT_EQ("second", value_->toString(1));
    EXPECT_EQ("third", value_->toString(2));
}

// Test toString with valid index
TEST_F(XmpArrayValueTest_847, ToStringValidIndex_847) {
    value_->read("test_value");
    std::string result = value_->toString(0);
    EXPECT_EQ("test_value", result);
    EXPECT_TRUE(value_->ok());
}

// Test toString with out-of-range index throws
TEST_F(XmpArrayValueTest_847, ToStringOutOfRangeThrows_847) {
    value_->read("only_one");
    EXPECT_THROW(value_->toString(1), std::out_of_range);
}

// Test toString on empty value throws
TEST_F(XmpArrayValueTest_847, ToStringOnEmptyThrows_847) {
    EXPECT_THROW(value_->toString(0), std::out_of_range);
}

// Test ok() returns true after successful toString
TEST_F(XmpArrayValueTest_847, OkReturnsTrueAfterValidToString_847) {
    value_->read("value");
    value_->toString(0);
    EXPECT_TRUE(value_->ok());
}

// Test toInt64 with numeric string
TEST_F(XmpArrayValueTest_847, ToInt64WithNumericString_847) {
    value_->read("42");
    int64_t result = value_->toInt64(0);
    EXPECT_EQ(42, result);
}

// Test toInt64 with negative number
TEST_F(XmpArrayValueTest_847, ToInt64WithNegativeNumber_847) {
    value_->read("-100");
    int64_t result = value_->toInt64(0);
    EXPECT_EQ(-100, result);
}

// Test toUint32 with numeric string
TEST_F(XmpArrayValueTest_847, ToUint32WithNumericString_847) {
    value_->read("123");
    uint32_t result = value_->toUint32(0);
    EXPECT_EQ(123u, result);
}

// Test toFloat with numeric string
TEST_F(XmpArrayValueTest_847, ToFloatWithNumericString_847) {
    value_->read("3.14");
    float result = value_->toFloat(0);
    EXPECT_NEAR(3.14f, result, 0.001f);
}

// Test toRational with numeric string
TEST_F(XmpArrayValueTest_847, ToRationalWithNumericString_847) {
    value_->read("5");
    Rational result = value_->toRational(0);
    // The rational should represent the value 5
    EXPECT_NE(0, result.second);
    EXPECT_FLOAT_EQ(5.0f, static_cast<float>(result.first) / static_cast<float>(result.second));
}

// Test write outputs values properly
TEST_F(XmpArrayValueTest_847, WriteOutputsValues_847) {
    value_->read("alpha");
    value_->read("beta");
    std::ostringstream os;
    value_->write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(std::string::npos, output.find("alpha"));
    EXPECT_NE(std::string::npos, output.find("beta"));
}

// Test write on empty value
TEST_F(XmpArrayValueTest_847, WriteOnEmptyValue_847) {
    std::ostringstream os;
    value_->write(os);
    // Should not crash; output may be empty
    SUCCEED();
}

// Test clone produces equivalent copy
TEST_F(XmpArrayValueTest_847, CloneProducesCopy_847) {
    value_->read("cloned_value");
    auto cloned = value_->clone();
    ASSERT_NE(nullptr, cloned);
    EXPECT_EQ(value_->typeId(), cloned->typeId());
    EXPECT_EQ(value_->count(), cloned->count());
    EXPECT_EQ(value_->toString(0), cloned->toString(0));
}

// Test reading empty string
TEST_F(XmpArrayValueTest_847, ReadEmptyString_847) {
    int result = value_->read("");
    // After reading empty string, behavior depends on implementation
    // Just verify no crash and count is deterministic
    EXPECT_GE(value_->count(), 0u);
    SUCCEED();
}

// Test reading string with spaces
TEST_F(XmpArrayValueTest_847, ReadStringWithSpaces_847) {
    value_->read("hello world");
    EXPECT_GE(value_->count(), 1u);
    // The first element should contain at least part of the input
    std::string first = value_->toString(0);
    EXPECT_FALSE(first.empty());
}

// Test count increments with each read
TEST_F(XmpArrayValueTest_847, CountIncrementsWithReads_847) {
    EXPECT_EQ(0u, value_->count());
    value_->read("a");
    EXPECT_EQ(1u, value_->count());
    value_->read("b");
    EXPECT_EQ(2u, value_->count());
    value_->read("c");
    EXPECT_EQ(3u, value_->count());
}

// Test toInt64 with non-numeric string
TEST_F(XmpArrayValueTest_847, ToInt64WithNonNumericString_847) {
    value_->read("not_a_number");
    // Should not crash; ok() may become false
    value_->toInt64(0);
    // We just verify it doesn't crash
    SUCCEED();
}

// Test toFloat with non-numeric string
TEST_F(XmpArrayValueTest_847, ToFloatWithNonNumericString_847) {
    value_->read("not_a_float");
    value_->toFloat(0);
    SUCCEED();
}

// Test with xmpSeq type
TEST_F(XmpArrayValueTest_847, XmpSeqTypeWorks_847) {
    XmpArrayValue seqValue(xmpSeq);
    seqValue.read("item1");
    seqValue.read("item2");
    EXPECT_EQ(2u, seqValue.count());
    EXPECT_EQ("item1", seqValue.toString(0));
    EXPECT_EQ("item2", seqValue.toString(1));
}

// Test with xmpAlt type
TEST_F(XmpArrayValueTest_847, XmpAltTypeWorks_847) {
    XmpArrayValue altValue(xmpAlt);
    altValue.read("alternative");
    EXPECT_EQ(1u, altValue.count());
    EXPECT_EQ("alternative", altValue.toString(0));
}

// Test toInt64 with zero
TEST_F(XmpArrayValueTest_847, ToInt64WithZero_847) {
    value_->read("0");
    EXPECT_EQ(0, value_->toInt64(0));
}

// Test toUint32 with zero
TEST_F(XmpArrayValueTest_847, ToUint32WithZero_847) {
    value_->read("0");
    EXPECT_EQ(0u, value_->toUint32(0));
}

// Test toFloat with zero
TEST_F(XmpArrayValueTest_847, ToFloatWithZero_847) {
    value_->read("0.0");
    EXPECT_FLOAT_EQ(0.0f, value_->toFloat(0));
}

// Test reading special characters
TEST_F(XmpArrayValueTest_847, ReadSpecialCharacters_847) {
    value_->read("hello@world#2024!");
    EXPECT_EQ(1u, value_->count());
    EXPECT_EQ("hello@world#2024!", value_->toString(0));
}

// Test large number of elements
TEST_F(XmpArrayValueTest_847, ManyElements_847) {
    for (int i = 0; i < 100; ++i) {
        value_->read("item" + std::to_string(i));
    }
    EXPECT_EQ(100u, value_->count());
    EXPECT_EQ("item0", value_->toString(0));
    EXPECT_EQ("item99", value_->toString(99));
}

// Test toString boundary - last valid index
TEST_F(XmpArrayValueTest_847, ToStringLastValidIndex_847) {
    value_->read("a");
    value_->read("b");
    value_->read("c");
    EXPECT_EQ("c", value_->toString(2));
    EXPECT_THROW(value_->toString(3), std::out_of_range);
}
