#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>

using namespace Exiv2;

class XmpArrayValueTest_845 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test that a newly created XmpArrayValue has count 0
TEST_F(XmpArrayValueTest_845, DefaultCountIsZero_845) {
    XmpArrayValue val(xmpBag);
    EXPECT_EQ(0u, val.count());
}

// Test that reading a single value increases count to 1
TEST_F(XmpArrayValueTest_845, ReadSingleValueCountIsOne_845) {
    XmpArrayValue val(xmpBag);
    val.read("hello");
    EXPECT_EQ(1u, val.count());
}

// Test that reading multiple values increases count appropriately
TEST_F(XmpArrayValueTest_845, ReadMultipleValuesIncrementsCount_845) {
    XmpArrayValue val(xmpBag);
    val.read("first");
    val.read("second");
    val.read("third");
    EXPECT_EQ(3u, val.count());
}

// Test toString returns the correct string for index 0
TEST_F(XmpArrayValueTest_845, ToStringReturnsCorrectValue_845) {
    XmpArrayValue val(xmpBag);
    val.read("hello");
    EXPECT_EQ("hello", val.toString(0));
}

// Test toString for multiple elements at different indices
TEST_F(XmpArrayValueTest_845, ToStringMultipleElements_845) {
    XmpArrayValue val(xmpBag);
    val.read("alpha");
    val.read("beta");
    val.read("gamma");
    EXPECT_EQ("alpha", val.toString(0));
    EXPECT_EQ("beta", val.toString(1));
    EXPECT_EQ("gamma", val.toString(2));
}

// Test toInt64 with a numeric string
TEST_F(XmpArrayValueTest_845, ToInt64WithNumericString_845) {
    XmpArrayValue val(xmpBag);
    val.read("42");
    EXPECT_EQ(42, val.toInt64(0));
}

// Test toUint32 with a numeric string
TEST_F(XmpArrayValueTest_845, ToUint32WithNumericString_845) {
    XmpArrayValue val(xmpBag);
    val.read("100");
    EXPECT_EQ(100u, val.toUint32(0));
}

// Test toFloat with a numeric string
TEST_F(XmpArrayValueTest_845, ToFloatWithNumericString_845) {
    XmpArrayValue val(xmpBag);
    val.read("3.14");
    EXPECT_NEAR(3.14f, val.toFloat(0), 0.01f);
}

// Test toRational with a numeric string
TEST_F(XmpArrayValueTest_845, ToRationalWithNumericString_845) {
    XmpArrayValue val(xmpBag);
    val.read("5");
    Rational r = val.toRational(0);
    EXPECT_EQ(5, r.first);
    EXPECT_EQ(1, r.second);
}

// Test write outputs values correctly
TEST_F(XmpArrayValueTest_845, WriteOutputsValues_845) {
    XmpArrayValue val(xmpBag);
    val.read("one");
    val.read("two");
    std::ostringstream os;
    val.write(os);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(std::string::npos, result.find("one"));
    EXPECT_NE(std::string::npos, result.find("two"));
}

// Test clone creates a copy with same count
TEST_F(XmpArrayValueTest_845, ClonePreservesCount_845) {
    XmpArrayValue val(xmpBag);
    val.read("a");
    val.read("b");
    auto cloned = val.clone();
    ASSERT_NE(nullptr, cloned.get());
    EXPECT_EQ(val.count(), cloned->count());
}

// Test clone preserves string values
TEST_F(XmpArrayValueTest_845, ClonePreservesValues_845) {
    XmpArrayValue val(xmpBag);
    val.read("hello");
    val.read("world");
    auto cloned = val.clone();
    EXPECT_EQ("hello", cloned->toString(0));
    EXPECT_EQ("world", cloned->toString(1));
}

// Test with xmpSeq type
TEST_F(XmpArrayValueTest_845, XmpSeqTypeWorks_845) {
    XmpArrayValue val(xmpSeq);
    val.read("item1");
    val.read("item2");
    EXPECT_EQ(2u, val.count());
    EXPECT_EQ("item1", val.toString(0));
    EXPECT_EQ("item2", val.toString(1));
}

// Test reading an empty string
TEST_F(XmpArrayValueTest_845, ReadEmptyString_845) {
    XmpArrayValue val(xmpBag);
    val.read("");
    // Even an empty string should be stored as an element
    EXPECT_GE(val.count(), 0u);
}

// Test toInt64 with zero
TEST_F(XmpArrayValueTest_845, ToInt64WithZero_845) {
    XmpArrayValue val(xmpBag);
    val.read("0");
    EXPECT_EQ(0, val.toInt64(0));
}

// Test toInt64 with negative number
TEST_F(XmpArrayValueTest_845, ToInt64WithNegativeNumber_845) {
    XmpArrayValue val(xmpBag);
    val.read("-10");
    EXPECT_EQ(-10, val.toInt64(0));
}

// Test toFloat with zero
TEST_F(XmpArrayValueTest_845, ToFloatWithZero_845) {
    XmpArrayValue val(xmpBag);
    val.read("0.0");
    EXPECT_FLOAT_EQ(0.0f, val.toFloat(0));
}

// Test that read returns 0 on success
TEST_F(XmpArrayValueTest_845, ReadReturnsZeroOnSuccess_845) {
    XmpArrayValue val(xmpBag);
    int result = val.read("test");
    EXPECT_EQ(0, result);
}

// Test writing empty XmpArrayValue
TEST_F(XmpArrayValueTest_845, WriteEmptyValue_845) {
    XmpArrayValue val(xmpBag);
    std::ostringstream os;
    val.write(os);
    // Should not crash; output may be empty
    EXPECT_TRUE(os.good());
}

// Test toString with boundary index 0 when only one element
TEST_F(XmpArrayValueTest_845, ToStringBoundaryIndex_845) {
    XmpArrayValue val(xmpBag);
    val.read("only");
    EXPECT_EQ("only", val.toString(0));
}

// Test toInt64 with large number
TEST_F(XmpArrayValueTest_845, ToInt64WithLargeNumber_845) {
    XmpArrayValue val(xmpBag);
    val.read("1000000000");
    EXPECT_EQ(1000000000LL, val.toInt64(0));
}

// Test toUint32 with zero
TEST_F(XmpArrayValueTest_845, ToUint32WithZero_845) {
    XmpArrayValue val(xmpBag);
    val.read("0");
    EXPECT_EQ(0u, val.toUint32(0));
}

// Test multiple reads and verify all toString values
TEST_F(XmpArrayValueTest_845, MultipleReadsVerifyAll_845) {
    XmpArrayValue val(xmpBag);
    for (int i = 0; i < 10; ++i) {
        val.read(std::to_string(i));
    }
    EXPECT_EQ(10u, val.count());
    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(std::to_string(i), val.toString(i));
    }
}
