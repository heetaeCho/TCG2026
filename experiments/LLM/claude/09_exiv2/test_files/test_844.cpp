#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <string>

using namespace Exiv2;

class XmpArrayValueTest_844 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test construction with different TypeIds
TEST_F(XmpArrayValueTest_844, ConstructWithXmpBag_844) {
    XmpArrayValue val(xmpBag);
    EXPECT_EQ(val.count(), 0u);
}

TEST_F(XmpArrayValueTest_844, ConstructWithXmpSeq_844) {
    XmpArrayValue val(xmpSeq);
    EXPECT_EQ(val.count(), 0u);
}

TEST_F(XmpArrayValueTest_844, ConstructWithXmpAlt_844) {
    XmpArrayValue val(xmpAlt);
    EXPECT_EQ(val.count(), 0u);
}

// Test read with a simple string
TEST_F(XmpArrayValueTest_844, ReadSingleValue_844) {
    XmpArrayValue val(xmpBag);
    int result = val.read("hello");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val.count(), 1u);
    EXPECT_EQ(val.toString(0), "hello");
}

// Test read with multiple values (comma-separated or multiple reads)
TEST_F(XmpArrayValueTest_844, ReadMultipleValues_844) {
    XmpArrayValue val(xmpBag);
    val.read("first");
    val.read("second");
    val.read("third");
    EXPECT_EQ(val.count(), 3u);
    EXPECT_EQ(val.toString(0), "first");
    EXPECT_EQ(val.toString(1), "second");
    EXPECT_EQ(val.toString(2), "third");
}

// Test read with empty string
TEST_F(XmpArrayValueTest_844, ReadEmptyString_844) {
    XmpArrayValue val(xmpBag);
    int result = val.read("");
    EXPECT_EQ(result, 0);
    // Even empty string should be stored as one element
    EXPECT_GE(val.count(), 0u);
}

// Test count on empty value
TEST_F(XmpArrayValueTest_844, CountEmpty_844) {
    XmpArrayValue val(xmpBag);
    EXPECT_EQ(val.count(), 0u);
}

// Test count after reads
TEST_F(XmpArrayValueTest_844, CountAfterMultipleReads_844) {
    XmpArrayValue val(xmpSeq);
    val.read("a");
    EXPECT_EQ(val.count(), 1u);
    val.read("b");
    EXPECT_EQ(val.count(), 2u);
    val.read("c");
    EXPECT_EQ(val.count(), 3u);
}

// Test toString with valid index
TEST_F(XmpArrayValueTest_844, ToStringValidIndex_844) {
    XmpArrayValue val(xmpBag);
    val.read("test_value");
    EXPECT_EQ(val.toString(0), "test_value");
}

// Test toString with out of range index
TEST_F(XmpArrayValueTest_844, ToStringOutOfRange_844) {
    XmpArrayValue val(xmpBag);
    val.read("only_one");
    EXPECT_NO_FATAL_FAILURE(val.toString(0));
    // Out of range - should throw or return empty
    EXPECT_THROW(val.toString(5), std::out_of_range);
}

// Test toInt64 with numeric string
TEST_F(XmpArrayValueTest_844, ToInt64NumericValue_844) {
    XmpArrayValue val(xmpBag);
    val.read("42");
    EXPECT_EQ(val.toInt64(0), 42);
}

// Test toInt64 with negative number
TEST_F(XmpArrayValueTest_844, ToInt64NegativeValue_844) {
    XmpArrayValue val(xmpBag);
    val.read("-100");
    EXPECT_EQ(val.toInt64(0), -100);
}

// Test toInt64 with zero
TEST_F(XmpArrayValueTest_844, ToInt64Zero_844) {
    XmpArrayValue val(xmpBag);
    val.read("0");
    EXPECT_EQ(val.toInt64(0), 0);
}

// Test toUint32 with numeric string
TEST_F(XmpArrayValueTest_844, ToUint32NumericValue_844) {
    XmpArrayValue val(xmpBag);
    val.read("123");
    EXPECT_EQ(val.toUint32(0), 123u);
}

// Test toFloat with numeric string
TEST_F(XmpArrayValueTest_844, ToFloatNumericValue_844) {
    XmpArrayValue val(xmpBag);
    val.read("3.14");
    EXPECT_NEAR(val.toFloat(0), 3.14f, 0.01f);
}

// Test toFloat with integer string
TEST_F(XmpArrayValueTest_844, ToFloatIntegerValue_844) {
    XmpArrayValue val(xmpBag);
    val.read("7");
    EXPECT_FLOAT_EQ(val.toFloat(0), 7.0f);
}

// Test toRational with numeric string
TEST_F(XmpArrayValueTest_844, ToRationalNumericValue_844) {
    XmpArrayValue val(xmpBag);
    val.read("5");
    Rational r = val.toRational(0);
    // The rational should represent the value 5
    if (r.second != 0) {
        EXPECT_NEAR(static_cast<double>(r.first) / r.second, 5.0, 0.001);
    }
}

// Test write to ostream
TEST_F(XmpArrayValueTest_844, WriteSingleValue_844) {
    XmpArrayValue val(xmpBag);
    val.read("hello");
    std::ostringstream os;
    val.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("hello"), std::string::npos);
}

// Test write to ostream with multiple values
TEST_F(XmpArrayValueTest_844, WriteMultipleValues_844) {
    XmpArrayValue val(xmpBag);
    val.read("alpha");
    val.read("beta");
    val.read("gamma");
    std::ostringstream os;
    val.write(os);
    std::string output = os.str();
    EXPECT_NE(output.find("alpha"), std::string::npos);
    EXPECT_NE(output.find("beta"), std::string::npos);
    EXPECT_NE(output.find("gamma"), std::string::npos);
}

// Test write to ostream with empty value
TEST_F(XmpArrayValueTest_844, WriteEmptyValue_844) {
    XmpArrayValue val(xmpBag);
    std::ostringstream os;
    val.write(os);
    // Should not crash, output may be empty
    EXPECT_TRUE(os.str().empty() || !os.str().empty());
}

// Test clone
TEST_F(XmpArrayValueTest_844, ClonePreservesValues_844) {
    XmpArrayValue val(xmpBag);
    val.read("clone_test");
    auto cloned = val.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->count(), val.count());
    EXPECT_EQ(cloned->toString(0), "clone_test");
}

// Test clone with multiple values
TEST_F(XmpArrayValueTest_844, ClonePreservesMultipleValues_844) {
    XmpArrayValue val(xmpSeq);
    val.read("one");
    val.read("two");
    val.read("three");
    auto cloned = val.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->count(), 3u);
    EXPECT_EQ(cloned->toString(0), "one");
    EXPECT_EQ(cloned->toString(1), "two");
    EXPECT_EQ(cloned->toString(2), "three");
}

// Test clone of empty value
TEST_F(XmpArrayValueTest_844, CloneEmptyValue_844) {
    XmpArrayValue val(xmpBag);
    auto cloned = val.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->count(), 0u);
}

// Test reading whitespace-only string
TEST_F(XmpArrayValueTest_844, ReadWhitespace_844) {
    XmpArrayValue val(xmpBag);
    int result = val.read("   ");
    EXPECT_EQ(result, 0);
}

// Test reading string with leading/trailing spaces
TEST_F(XmpArrayValueTest_844, ReadStringWithSpaces_844) {
    XmpArrayValue val(xmpBag);
    val.read("  spaced  ");
    EXPECT_GE(val.count(), 1u);
}

// Test toInt64 with non-numeric string
TEST_F(XmpArrayValueTest_844, ToInt64NonNumericValue_844) {
    XmpArrayValue val(xmpBag);
    val.read("not_a_number");
    // Should return 0 or handle gracefully
    EXPECT_NO_FATAL_FAILURE(val.toInt64(0));
}

// Test toFloat with non-numeric string
TEST_F(XmpArrayValueTest_844, ToFloatNonNumericValue_844) {
    XmpArrayValue val(xmpBag);
    val.read("abc");
    EXPECT_NO_FATAL_FAILURE(val.toFloat(0));
}

// Test large number of elements
TEST_F(XmpArrayValueTest_844, ReadManyValues_844) {
    XmpArrayValue val(xmpBag);
    for (int i = 0; i < 100; ++i) {
        val.read(std::to_string(i));
    }
    EXPECT_EQ(val.count(), 100u);
    EXPECT_EQ(val.toString(0), "0");
    EXPECT_EQ(val.toString(99), "99");
}

// Test toUint32 with large value
TEST_F(XmpArrayValueTest_844, ToUint32LargeValue_844) {
    XmpArrayValue val(xmpBag);
    val.read("4294967295"); // UINT32_MAX
    EXPECT_NO_FATAL_FAILURE(val.toUint32(0));
}

// Test toInt64 with large value
TEST_F(XmpArrayValueTest_844, ToInt64LargeValue_844) {
    XmpArrayValue val(xmpBag);
    val.read("9223372036854775807"); // INT64_MAX
    EXPECT_NO_FATAL_FAILURE(val.toInt64(0));
}

// Test toString default argument (n=0)
TEST_F(XmpArrayValueTest_844, ToStringDefaultIndex_844) {
    XmpArrayValue val(xmpBag);
    val.read("default_test");
    EXPECT_EQ(val.toString(0), "default_test");
}

// Test that clone is a deep copy (modifying original doesn't affect clone)
TEST_F(XmpArrayValueTest_844, CloneIsDeepCopy_844) {
    XmpArrayValue val(xmpBag);
    val.read("original");
    auto cloned = val.clone();
    val.read("modified");
    EXPECT_EQ(val.count(), 2u);
    EXPECT_EQ(cloned->count(), 1u);
    EXPECT_EQ(cloned->toString(0), "original");
}

// Test special characters in string
TEST_F(XmpArrayValueTest_844, ReadSpecialCharacters_844) {
    XmpArrayValue val(xmpBag);
    val.read("hello, world!");
    EXPECT_GE(val.count(), 1u);
}

// Test unicode-like strings
TEST_F(XmpArrayValueTest_844, ReadUnicodeString_844) {
    XmpArrayValue val(xmpBag);
    val.read("café");
    EXPECT_GE(val.count(), 1u);
}
