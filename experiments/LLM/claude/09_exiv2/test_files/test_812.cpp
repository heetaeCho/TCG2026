#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <stdexcept>

using namespace Exiv2;

// Helper to create a StringValueBase-derived object. Since StringValueBase
// might be abstract or we need a concrete type, we use StringValue or
// create via Value::create. We'll use StringValue which derives from StringValueBase.

class StringValueBaseTest_812 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test toRational with a simple single-character string
TEST_F(StringValueBaseTest_812, ToRationalSingleChar_812) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("A");
    Rational r = val->toRational(0);
    // 'A' == 65, so we expect {65, 1}
    EXPECT_EQ(r.first, 65);
    EXPECT_EQ(r.second, 1);
    EXPECT_TRUE(val->ok());
}

// Test toRational with index accessing different characters
TEST_F(StringValueBaseTest_812, ToRationalMultipleChars_812) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("Hello");
    
    // Index 0 -> 'H' = 72
    Rational r0 = val->toRational(0);
    EXPECT_EQ(r0.first, 72);
    EXPECT_EQ(r0.second, 1);
    
    // Index 1 -> 'e' = 101
    Rational r1 = val->toRational(1);
    EXPECT_EQ(r1.first, 101);
    EXPECT_EQ(r1.second, 1);
    
    // Index 4 -> 'o' = 111
    Rational r4 = val->toRational(4);
    EXPECT_EQ(r4.first, 111);
    EXPECT_EQ(r4.second, 1);
}

// Test toRational denominator is always 1
TEST_F(StringValueBaseTest_812, ToRationalDenominatorIsOne_812) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("Z");
    Rational r = val->toRational(0);
    EXPECT_EQ(r.second, 1);
}

// Test toRational with out-of-range index throws
TEST_F(StringValueBaseTest_812, ToRationalOutOfRange_812) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("AB");
    // Index 2 is out of range for a 2-character string
    EXPECT_THROW(val->toRational(2), std::out_of_range);
}

// Test toRational with empty string throws on any index
TEST_F(StringValueBaseTest_812, ToRationalEmptyString_812) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("");
    EXPECT_THROW(val->toRational(0), std::out_of_range);
}

// Test that ok() returns true after successful toRational call
TEST_F(StringValueBaseTest_812, ToRationalSetsOkTrue_812) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("X");
    val->toRational(0);
    EXPECT_TRUE(val->ok());
}

// Test toRational with null character in string
TEST_F(StringValueBaseTest_812, ToRationalNullChar_812) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    std::string s(1, '\0');
    val->read(s);
    // Depending on how the string is stored, index 0 should be char 0
    Rational r = val->toRational(0);
    EXPECT_EQ(r.first, 0);
    EXPECT_EQ(r.second, 1);
}

// Test toRational with numeric digit characters
TEST_F(StringValueBaseTest_812, ToRationalDigitChars_812) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("0123456789");
    
    // '0' = 48
    Rational r0 = val->toRational(0);
    EXPECT_EQ(r0.first, 48);
    EXPECT_EQ(r0.second, 1);
    
    // '9' = 57
    Rational r9 = val->toRational(9);
    EXPECT_EQ(r9.first, 57);
    EXPECT_EQ(r9.second, 1);
}

// Test toRational last valid index (boundary)
TEST_F(StringValueBaseTest_812, ToRationalLastValidIndex_812) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("abc");
    // Last valid index is 2 -> 'c' = 99
    Rational r = val->toRational(2);
    EXPECT_EQ(r.first, 99);
    EXPECT_EQ(r.second, 1);
}

// Test basic read and count
TEST_F(StringValueBaseTest_812, ReadAndCount_812) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("test");
    EXPECT_EQ(val->count(), 1u);
}

// Test size returns string length
TEST_F(StringValueBaseTest_812, SizeReturnsLength_812) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("Hello");
    EXPECT_EQ(val->size(), 5u);
}

// Test toInt64
TEST_F(StringValueBaseTest_812, ToInt64_812) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("A");
    int64_t v = val->toInt64(0);
    EXPECT_EQ(v, 65);
}

// Test toUint32
TEST_F(StringValueBaseTest_812, ToUint32_812) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("B");
    uint32_t v = val->toUint32(0);
    EXPECT_EQ(v, 66u);
}

// Test toFloat
TEST_F(StringValueBaseTest_812, ToFloat_812) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("C");
    float v = val->toFloat(0);
    EXPECT_FLOAT_EQ(v, 67.0f);
}

// Test write to ostream
TEST_F(StringValueBaseTest_812, WriteToStream_812) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("test output");
    std::ostringstream oss;
    val->write(oss);
    EXPECT_EQ(oss.str(), "test output");
}

// Test copy to buffer
TEST_F(StringValueBaseTest_812, CopyToBuffer_812) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("copy");
    byte buf[10] = {};
    size_t copied = val->copy(buf, littleEndian);
    EXPECT_EQ(copied, 4u);
    EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), 4), "copy");
}

// Test read from byte buffer
TEST_F(StringValueBaseTest_812, ReadFromByteBuffer_812) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    const byte data[] = {'h', 'i'};
    val->read(data, 2, littleEndian);
    std::ostringstream oss;
    val->write(oss);
    EXPECT_EQ(oss.str(), "hi");
}

// Test typeId
TEST_F(StringValueBaseTest_812, TypeId_812) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), string);
}

// Test clone
TEST_F(StringValueBaseTest_812, Clone_812) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("cloned");
    auto cloned = val->clone();
    ASSERT_NE(cloned, nullptr);
    std::ostringstream oss;
    cloned->write(oss);
    EXPECT_EQ(oss.str(), "cloned");
}

// Test toRational with space character
TEST_F(StringValueBaseTest_812, ToRationalSpaceChar_812) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read(" ");
    Rational r = val->toRational(0);
    EXPECT_EQ(r.first, 32);  // space = 32
    EXPECT_EQ(r.second, 1);
}

// Test re-read overwrites previous value
TEST_F(StringValueBaseTest_812, ReReadOverwrites_812) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("first");
    val->read("second");
    EXPECT_EQ(val->size(), 6u);
    Rational r = val->toRational(0);
    EXPECT_EQ(r.first, 's');  // 's' = 115
    EXPECT_EQ(r.second, 1);
}
