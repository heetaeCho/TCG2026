#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <exiv2/value.hpp>

namespace {

class XmpArrayValueTest_846 : public ::testing::Test {
protected:
    void SetUp() override {
        // xmpSeq is a common TypeId for XmpArrayValue
        value_ = std::make_unique<Exiv2::XmpArrayValue>(Exiv2::xmpSeq);
    }

    std::unique_ptr<Exiv2::XmpArrayValue> value_;
};

// Test that a newly constructed XmpArrayValue has count 0
TEST_F(XmpArrayValueTest_846, DefaultConstructionHasZeroCount_846) {
    EXPECT_EQ(0u, value_->count());
}

// Test writing an empty value produces no output
TEST_F(XmpArrayValueTest_846, WriteEmptyProducesNoOutput_846) {
    std::ostringstream os;
    value_->write(os);
    EXPECT_EQ("", os.str());
}

// Test reading a single value
TEST_F(XmpArrayValueTest_846, ReadSingleValue_846) {
    int result = value_->read("hello");
    EXPECT_EQ(0, result);
    EXPECT_EQ(1u, value_->count());
}

// Test toString for a single value
TEST_F(XmpArrayValueTest_846, ToStringSingleValue_846) {
    value_->read("hello");
    EXPECT_EQ("hello", value_->toString(0));
}

// Test writing a single value
TEST_F(XmpArrayValueTest_846, WriteSingleValue_846) {
    value_->read("hello");
    std::ostringstream os;
    value_->write(os);
    EXPECT_EQ("hello", os.str());
}

// Test reading multiple values
TEST_F(XmpArrayValueTest_846, ReadMultipleValues_846) {
    value_->read("first");
    value_->read("second");
    value_->read("third");
    EXPECT_EQ(3u, value_->count());
}

// Test writing multiple values produces comma-separated output
TEST_F(XmpArrayValueTest_846, WriteMultipleValuesCommaseparated_846) {
    value_->read("first");
    value_->read("second");
    value_->read("third");
    std::ostringstream os;
    value_->write(os);
    EXPECT_EQ("first, second, third", os.str());
}

// Test toString with index for multiple values
TEST_F(XmpArrayValueTest_846, ToStringWithIndex_846) {
    value_->read("alpha");
    value_->read("beta");
    value_->read("gamma");
    EXPECT_EQ("alpha", value_->toString(0));
    EXPECT_EQ("beta", value_->toString(1));
    EXPECT_EQ("gamma", value_->toString(2));
}

// Test writing two values
TEST_F(XmpArrayValueTest_846, WriteTwoValues_846) {
    value_->read("one");
    value_->read("two");
    std::ostringstream os;
    value_->write(os);
    EXPECT_EQ("one, two", os.str());
}

// Test toInt64 for numeric string
TEST_F(XmpArrayValueTest_846, ToInt64NumericString_846) {
    value_->read("42");
    EXPECT_EQ(42, value_->toInt64(0));
}

// Test toUint32 for numeric string
TEST_F(XmpArrayValueTest_846, ToUint32NumericString_846) {
    value_->read("100");
    EXPECT_EQ(100u, value_->toUint32(0));
}

// Test toFloat for numeric string
TEST_F(XmpArrayValueTest_846, ToFloatNumericString_846) {
    value_->read("3.14");
    EXPECT_NEAR(3.14f, value_->toFloat(0), 0.01f);
}

// Test toRational for numeric string
TEST_F(XmpArrayValueTest_846, ToRationalNumericString_846) {
    value_->read("5");
    Exiv2::Rational r = value_->toRational(0);
    // The rational should represent 5 in some form
    if (r.second != 0) {
        EXPECT_NEAR(5.0, static_cast<double>(r.first) / r.second, 0.01);
    }
}

// Test clone produces equivalent object
TEST_F(XmpArrayValueTest_846, CloneProducesEquivalent_846) {
    value_->read("a");
    value_->read("b");
    auto cloned = value_->clone();
    ASSERT_NE(nullptr, cloned.get());
    std::ostringstream os1, os2;
    value_->write(os1);
    cloned->write(os2);
    EXPECT_EQ(os1.str(), os2.str());
}

// Test reading an empty string
TEST_F(XmpArrayValueTest_846, ReadEmptyString_846) {
    value_->read("");
    // After reading empty string, there should be at least one entry (the empty string itself)
    // or zero entries depending on implementation. We just check it doesn't crash.
    std::ostringstream os;
    value_->write(os);
    // The output is whatever the implementation produces
}

// Test toString out of range throws or returns empty
TEST_F(XmpArrayValueTest_846, ToStringOutOfRange_846) {
    value_->read("only");
    // Accessing index beyond count - behavior may throw
    try {
        std::string s = value_->toString(5);
        // If it doesn't throw, that's also acceptable behavior
    } catch (const std::exception&) {
        // Expected for out-of-range access
    }
}

// Test with xmpBag type
TEST(XmpArrayValueBagTest_846, ConstructWithXmpBag_846) {
    Exiv2::XmpArrayValue val(Exiv2::xmpBag);
    val.read("item1");
    val.read("item2");
    EXPECT_EQ(2u, val.count());
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ("item1, item2", os.str());
}

// Test with xmpAlt type
TEST(XmpArrayValueAltTest_846, ConstructWithXmpAlt_846) {
    Exiv2::XmpArrayValue val(Exiv2::xmpAlt);
    val.read("alt1");
    val.read("alt2");
    EXPECT_EQ(2u, val.count());
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ("alt1, alt2", os.str());
}

// Test that reading values with whitespace works
TEST_F(XmpArrayValueTest_846, ReadValueWithSpaces_846) {
    value_->read("hello world");
    EXPECT_EQ(1u, value_->count());
    EXPECT_EQ("hello world", value_->toString(0));
}

// Test multiple writes to same stream
TEST_F(XmpArrayValueTest_846, WriteReturnsStream_846) {
    value_->read("x");
    value_->read("y");
    std::ostringstream os;
    os << "[";
    value_->write(os);
    os << "]";
    EXPECT_EQ("[x, y]", os.str());
}

// Test large number of elements
TEST_F(XmpArrayValueTest_846, ManyElements_846) {
    for (int i = 0; i < 100; ++i) {
        value_->read(std::to_string(i));
    }
    EXPECT_EQ(100u, value_->count());
    
    std::ostringstream os;
    value_->write(os);
    std::string result = os.str();
    // Should contain commas separating elements
    // First element should be "0" and last should be "99"
    EXPECT_EQ('0', result[0]);
    EXPECT_NE(std::string::npos, result.find("99"));
}

// Test toInt64 with multiple numeric values
TEST_F(XmpArrayValueTest_846, ToInt64MultipleValues_846) {
    value_->read("10");
    value_->read("20");
    value_->read("30");
    EXPECT_EQ(10, value_->toInt64(0));
    EXPECT_EQ(20, value_->toInt64(1));
    EXPECT_EQ(30, value_->toInt64(2));
}

}  // namespace
