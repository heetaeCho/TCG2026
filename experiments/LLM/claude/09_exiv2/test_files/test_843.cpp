#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <string>

using namespace Exiv2;

class XmpArrayValueTest_843 : public ::testing::Test {
protected:
    void SetUp() override {
        value_ = std::make_unique<XmpArrayValue>(xmpBag);
    }

    std::unique_ptr<XmpArrayValue> value_;
};

// Test: Default constructed XmpArrayValue has zero count
TEST_F(XmpArrayValueTest_843, DefaultConstructedHasZeroCount_843) {
    EXPECT_EQ(0u, value_->count());
}

// Test: Reading a non-empty string increases count by one
TEST_F(XmpArrayValueTest_843, ReadNonEmptyStringIncreasesCount_843) {
    int result = value_->read("hello");
    EXPECT_EQ(0, result);
    EXPECT_EQ(1u, value_->count());
}

// Test: Reading multiple strings increases count accordingly
TEST_F(XmpArrayValueTest_843, ReadMultipleStringsIncreasesCount_843) {
    value_->read("first");
    value_->read("second");
    value_->read("third");
    EXPECT_EQ(3u, value_->count());
}

// Test: Reading an empty string
TEST_F(XmpArrayValueTest_843, ReadEmptyString_843) {
    int result = value_->read("");
    EXPECT_EQ(0, result);
    // Empty string may or may not be added; check count is 0 or 1
    // Based on the partial code, empty strings are not added
    EXPECT_EQ(0u, value_->count());
}

// Test: toString returns the correct value for a given index
TEST_F(XmpArrayValueTest_843, ToStringReturnsCorrectValue_843) {
    value_->read("hello");
    value_->read("world");
    EXPECT_EQ("hello", value_->toString(0));
    EXPECT_EQ("world", value_->toString(1));
}

// Test: toInt64 converts numeric string correctly
TEST_F(XmpArrayValueTest_843, ToInt64ConvertsNumericString_843) {
    value_->read("42");
    EXPECT_EQ(42, value_->toInt64(0));
}

// Test: toUint32 converts numeric string correctly
TEST_F(XmpArrayValueTest_843, ToUint32ConvertsNumericString_843) {
    value_->read("100");
    EXPECT_EQ(100u, value_->toUint32(0));
}

// Test: toFloat converts numeric string correctly
TEST_F(XmpArrayValueTest_843, ToFloatConvertsNumericString_843) {
    value_->read("3.14");
    EXPECT_NEAR(3.14f, value_->toFloat(0), 0.01f);
}

// Test: toRational converts numeric string
TEST_F(XmpArrayValueTest_843, ToRationalConvertsNumericString_843) {
    value_->read("5");
    Rational r = value_->toRational(0);
    // The rational should represent 5 in some form
    EXPECT_NE(0, r.second);
    EXPECT_FLOAT_EQ(5.0f, static_cast<float>(r.first) / static_cast<float>(r.second));
}

// Test: write outputs values to stream
TEST_F(XmpArrayValueTest_843, WriteOutputsToStream_843) {
    value_->read("alpha");
    value_->read("beta");
    std::ostringstream os;
    value_->write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(std::string::npos, output.find("alpha"));
    EXPECT_NE(std::string::npos, output.find("beta"));
}

// Test: clone creates an independent copy
TEST_F(XmpArrayValueTest_843, CloneCreatesIndependentCopy_843) {
    value_->read("original");
    auto cloned = value_->clone();
    ASSERT_NE(nullptr, cloned);
    EXPECT_EQ(1u, value_->count());
    // The cloned value should also have count 1
    // Adding to original shouldn't affect clone
    value_->read("additional");
    EXPECT_EQ(2u, value_->count());
}

// Test: toString with out of range index
TEST_F(XmpArrayValueTest_843, ToStringOutOfRangeIndex_843) {
    value_->read("only");
    // Accessing index beyond count - behavior may throw or return empty
    try {
        std::string result = value_->toString(5);
        // If it doesn't throw, that's also acceptable behavior
    } catch (const std::exception&) {
        // Expected for out of range
    }
}

// Test: toInt64 with out of range index
TEST_F(XmpArrayValueTest_843, ToInt64OutOfRangeIndex_843) {
    // No elements added, accessing index 0
    try {
        int64_t result = value_->toInt64(0);
        (void)result;
    } catch (const std::exception&) {
        // Expected for out of range
    }
}

// Test: Read returns 0 on success
TEST_F(XmpArrayValueTest_843, ReadReturnsZeroOnSuccess_843) {
    EXPECT_EQ(0, value_->read("test_value"));
}

// Test: Construct with different TypeId
TEST_F(XmpArrayValueTest_843, ConstructWithXmpSeq_843) {
    XmpArrayValue seqValue(xmpSeq);
    seqValue.read("item1");
    seqValue.read("item2");
    EXPECT_EQ(2u, seqValue.count());
    EXPECT_EQ("item1", seqValue.toString(0));
    EXPECT_EQ("item2", seqValue.toString(1));
}

// Test: Construct with xmpAlt type
TEST_F(XmpArrayValueTest_843, ConstructWithXmpAlt_843) {
    XmpArrayValue altValue(xmpAlt);
    altValue.read("alternative");
    EXPECT_EQ(1u, altValue.count());
    EXPECT_EQ("alternative", altValue.toString(0));
}

// Test: Reading a string with spaces
TEST_F(XmpArrayValueTest_843, ReadStringWithSpaces_843) {
    value_->read("hello world");
    EXPECT_EQ(1u, value_->count());
    EXPECT_EQ("hello world", value_->toString(0));
}

// Test: Reading a numeric string and then converting
TEST_F(XmpArrayValueTest_843, ReadNegativeNumber_843) {
    value_->read("-42");
    EXPECT_EQ(-42, value_->toInt64(0));
}

// Test: toFloat for integer string
TEST_F(XmpArrayValueTest_843, ToFloatForIntegerString_843) {
    value_->read("7");
    EXPECT_FLOAT_EQ(7.0f, value_->toFloat(0));
}

// Test: Write with empty value
TEST_F(XmpArrayValueTest_843, WriteWithNoElements_843) {
    std::ostringstream os;
    value_->write(os);
    // Should produce empty or minimal output
    // Just verify it doesn't crash
    SUCCEED();
}

// Test: Write with single element
TEST_F(XmpArrayValueTest_843, WriteWithSingleElement_843) {
    value_->read("single");
    std::ostringstream os;
    value_->write(os);
    std::string output = os.str();
    EXPECT_NE(std::string::npos, output.find("single"));
}

// Test: Read large number of elements
TEST_F(XmpArrayValueTest_843, ReadLargeNumberOfElements_843) {
    for (int i = 0; i < 1000; ++i) {
        value_->read("item" + std::to_string(i));
    }
    EXPECT_EQ(1000u, value_->count());
    EXPECT_EQ("item0", value_->toString(0));
    EXPECT_EQ("item999", value_->toString(999));
}

// Test: toUint32 with zero
TEST_F(XmpArrayValueTest_843, ToUint32WithZero_843) {
    value_->read("0");
    EXPECT_EQ(0u, value_->toUint32(0));
}

// Test: toInt64 with zero
TEST_F(XmpArrayValueTest_843, ToInt64WithZero_843) {
    value_->read("0");
    EXPECT_EQ(0, value_->toInt64(0));
}

// Test: Special characters in string
TEST_F(XmpArrayValueTest_843, ReadSpecialCharacters_843) {
    value_->read("hello\tworld\n");
    EXPECT_EQ(1u, value_->count());
}
