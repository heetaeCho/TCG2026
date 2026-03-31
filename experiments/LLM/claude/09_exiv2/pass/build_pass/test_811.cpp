#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <cstring>
#include <sstream>

using namespace Exiv2;

// Helper: StringValue is a concrete subclass of StringValueBase in exiv2
// We'll use StringValue or construct StringValueBase-derived objects for testing.

class StringValueBaseTest_811 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test toFloat returns the character value at the given position
TEST_F(StringValueBaseTest_811, ToFloatReturnsCharValueAtIndex_811) {
    StringValue sv("ABC");
    float result = sv.toFloat(0);
    EXPECT_FLOAT_EQ(result, static_cast<float>('A'));
    EXPECT_TRUE(sv.ok());
}

TEST_F(StringValueBaseTest_811, ToFloatReturnsCharValueAtSecondIndex_811) {
    StringValue sv("ABC");
    float result = sv.toFloat(1);
    EXPECT_FLOAT_EQ(result, static_cast<float>('B'));
    EXPECT_TRUE(sv.ok());
}

TEST_F(StringValueBaseTest_811, ToFloatReturnsCharValueAtLastIndex_811) {
    StringValue sv("ABC");
    float result = sv.toFloat(2);
    EXPECT_FLOAT_EQ(result, static_cast<float>('C'));
    EXPECT_TRUE(sv.ok());
}

// Test toFloat with out-of-range index throws std::out_of_range
TEST_F(StringValueBaseTest_811, ToFloatThrowsOnOutOfRange_811) {
    StringValue sv("AB");
    EXPECT_THROW(sv.toFloat(5), std::out_of_range);
}

// Test toFloat on empty string throws
TEST_F(StringValueBaseTest_811, ToFloatThrowsOnEmptyString_811) {
    StringValue sv("");
    EXPECT_THROW(sv.toFloat(0), std::out_of_range);
}

// Test toFloat with numeric characters
TEST_F(StringValueBaseTest_811, ToFloatWithNumericChar_811) {
    StringValue sv("0123456789");
    EXPECT_FLOAT_EQ(sv.toFloat(0), static_cast<float>('0'));
    EXPECT_FLOAT_EQ(sv.toFloat(9), static_cast<float>('9'));
    EXPECT_TRUE(sv.ok());
}

// Test toFloat with special characters
TEST_F(StringValueBaseTest_811, ToFloatWithSpecialChar_811) {
    StringValue sv(" \t\n");
    EXPECT_FLOAT_EQ(sv.toFloat(0), static_cast<float>(' '));
    EXPECT_FLOAT_EQ(sv.toFloat(1), static_cast<float>('\t'));
    EXPECT_FLOAT_EQ(sv.toFloat(2), static_cast<float>('\n'));
    EXPECT_TRUE(sv.ok());
}

// Test that ok() returns true after successful toFloat call
TEST_F(StringValueBaseTest_811, OkReturnsTrueAfterToFloat_811) {
    StringValue sv("test");
    sv.toFloat(0);
    EXPECT_TRUE(sv.ok());
}

// Test read and then toFloat
TEST_F(StringValueBaseTest_811, ReadThenToFloat_811) {
    StringValue sv("");
    sv.read("Hello");
    EXPECT_FLOAT_EQ(sv.toFloat(0), static_cast<float>('H'));
    EXPECT_FLOAT_EQ(sv.toFloat(4), static_cast<float>('o'));
    EXPECT_TRUE(sv.ok());
}

// Test toFloat with single character string
TEST_F(StringValueBaseTest_811, ToFloatSingleChar_811) {
    StringValue sv("X");
    EXPECT_FLOAT_EQ(sv.toFloat(0), static_cast<float>('X'));
    EXPECT_TRUE(sv.ok());
}

// Test other StringValueBase methods for completeness
TEST_F(StringValueBaseTest_811, CountReturnsOne_811) {
    StringValue sv("Hello");
    EXPECT_EQ(sv.count(), 1u);
}

TEST_F(StringValueBaseTest_811, SizeReturnsStringLength_811) {
    StringValue sv("Hello");
    EXPECT_EQ(sv.size(), 5u);
}

TEST_F(StringValueBaseTest_811, ToInt64ReturnsCharValue_811) {
    StringValue sv("ABC");
    EXPECT_EQ(sv.toInt64(0), static_cast<int64_t>('A'));
}

TEST_F(StringValueBaseTest_811, ToUint32ReturnsCharValue_811) {
    StringValue sv("ABC");
    EXPECT_EQ(sv.toUint32(0), static_cast<uint32_t>('A'));
}

TEST_F(StringValueBaseTest_811, WriteOutputsValue_811) {
    StringValue sv("test");
    std::ostringstream os;
    sv.write(os);
    EXPECT_EQ(os.str(), "test");
}

TEST_F(StringValueBaseTest_811, CopyCopiesBytesToBuffer_811) {
    StringValue sv("ABCDE");
    byte buf[10] = {};
    size_t copied = sv.copy(buf, bigEndian);
    EXPECT_EQ(copied, 5u);
    EXPECT_EQ(std::memcmp(buf, "ABCDE", 5), 0);
}

TEST_F(StringValueBaseTest_811, ReadFromByteBuffer_811) {
    StringValue sv("");
    const byte data[] = "TestData";
    sv.read(data, 8, bigEndian);
    EXPECT_EQ(sv.size(), 8u);
    EXPECT_FLOAT_EQ(sv.toFloat(0), static_cast<float>('T'));
    EXPECT_FLOAT_EQ(sv.toFloat(7), static_cast<float>('a'));
}

TEST_F(StringValueBaseTest_811, ToRationalReturnsExpectedValue_811) {
    StringValue sv("A");
    Rational r = sv.toRational(0);
    EXPECT_EQ(r.first, static_cast<int32_t>('A'));
    EXPECT_EQ(r.second, 1);
}

TEST_F(StringValueBaseTest_811, CloneProducesSameValue_811) {
    StringValue sv("clone_test");
    auto cloned = sv.clone();
    ASSERT_NE(cloned, nullptr);
    std::ostringstream os1, os2;
    sv.write(os1);
    cloned->write(os2);
    EXPECT_EQ(os1.str(), os2.str());
}

// Boundary: toFloat at the exact last valid index
TEST_F(StringValueBaseTest_811, ToFloatAtExactBoundary_811) {
    StringValue sv("XY");
    EXPECT_FLOAT_EQ(sv.toFloat(1), static_cast<float>('Y'));
    EXPECT_THROW(sv.toFloat(2), std::out_of_range);
}

// Test with null character in string
TEST_F(StringValueBaseTest_811, ToFloatWithNullChar_811) {
    std::string s("A\0B", 3);
    StringValue sv("");
    const byte* data = reinterpret_cast<const byte*>(s.data());
    sv.read(data, 3, bigEndian);
    EXPECT_FLOAT_EQ(sv.toFloat(0), static_cast<float>('A'));
    EXPECT_FLOAT_EQ(sv.toFloat(1), static_cast<float>('\0'));
    EXPECT_FLOAT_EQ(sv.toFloat(2), static_cast<float>('B'));
}
