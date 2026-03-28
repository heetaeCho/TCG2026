#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <cstring>
#include <exiv2/value.hpp>

using namespace Exiv2;

// StringValue is a concrete subclass of StringValueBase that we can instantiate
// We'll use StringValue for testing since StringValueBase is typically abstract or
// at least has concrete derived classes.

class StringValueBaseTest_808 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test construction with empty string
TEST_F(StringValueBaseTest_808, ConstructWithEmptyString_808) {
    StringValue sv("");
    EXPECT_EQ(sv.size(), 0u);
    EXPECT_EQ(sv.count(), 0u);
}

// Test construction with non-empty string
TEST_F(StringValueBaseTest_808, ConstructWithNonEmptyString_808) {
    StringValue sv("Hello World");
    EXPECT_EQ(sv.size(), 11u);
}

// Test read from string
TEST_F(StringValueBaseTest_808, ReadFromString_808) {
    StringValue sv("");
    int result = sv.read("Test String");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(sv.size(), 11u);
}

// Test read from empty string
TEST_F(StringValueBaseTest_808, ReadFromEmptyString_808) {
    StringValue sv("initial");
    int result = sv.read("");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(sv.size(), 0u);
}

// Test read from byte buffer
TEST_F(StringValueBaseTest_808, ReadFromByteBuffer_808) {
    StringValue sv("");
    const std::string data = "ByteData";
    int result = sv.read(reinterpret_cast<const byte*>(data.c_str()), data.size(), littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(sv.size(), data.size());
}

// Test read from byte buffer with zero length
TEST_F(StringValueBaseTest_808, ReadFromByteBufferZeroLength_808) {
    StringValue sv("initial");
    const byte buf[] = {0};
    int result = sv.read(buf, 0, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(sv.size(), 0u);
}

// Test write to ostream
TEST_F(StringValueBaseTest_808, WriteToOstream_808) {
    StringValue sv("Hello");
    std::ostringstream os;
    sv.write(os);
    EXPECT_EQ(os.str(), "Hello");
}

// Test write empty value to ostream
TEST_F(StringValueBaseTest_808, WriteEmptyToOstream_808) {
    StringValue sv("");
    std::ostringstream os;
    sv.write(os);
    EXPECT_EQ(os.str(), "");
}

// Test copy to byte buffer
TEST_F(StringValueBaseTest_808, CopyToByteBuffer_808) {
    StringValue sv("Copy");
    byte buf[10] = {0};
    size_t copied = sv.copy(buf, littleEndian);
    EXPECT_EQ(copied, 4u);
    EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), copied), "Copy");
}

// Test copy empty value
TEST_F(StringValueBaseTest_808, CopyEmptyToByteBuffer_808) {
    StringValue sv("");
    byte buf[10] = {0};
    size_t copied = sv.copy(buf, littleEndian);
    EXPECT_EQ(copied, 0u);
}

// Test count
TEST_F(StringValueBaseTest_808, CountNonEmpty_808) {
    StringValue sv("Hello");
    EXPECT_EQ(sv.count(), 5u);
}

// Test count empty
TEST_F(StringValueBaseTest_808, CountEmpty_808) {
    StringValue sv("");
    EXPECT_EQ(sv.count(), 0u);
}

// Test size
TEST_F(StringValueBaseTest_808, SizeMatchesStringLength_808) {
    StringValue sv("12345");
    EXPECT_EQ(sv.size(), 5u);
}

// Test toInt64 with numeric string
TEST_F(StringValueBaseTest_808, ToInt64WithNumericString_808) {
    StringValue sv("12345");
    int64_t val = sv.toInt64(0);
    EXPECT_EQ(val, 12345);
}

// Test toInt64 with non-numeric string
TEST_F(StringValueBaseTest_808, ToInt64WithNonNumericString_808) {
    StringValue sv("abc");
    int64_t val = sv.toInt64(0);
    EXPECT_EQ(val, 0);
}

// Test toUint32 with numeric string
TEST_F(StringValueBaseTest_808, ToUint32WithNumericString_808) {
    StringValue sv("42");
    uint32_t val = sv.toUint32(0);
    EXPECT_EQ(val, 42u);
}

// Test toFloat with numeric string
TEST_F(StringValueBaseTest_808, ToFloatWithNumericString_808) {
    StringValue sv("3.14");
    float val = sv.toFloat(0);
    EXPECT_NEAR(val, 3.14f, 0.01f);
}

// Test toFloat with non-numeric string
TEST_F(StringValueBaseTest_808, ToFloatWithNonNumericString_808) {
    StringValue sv("notanumber");
    float val = sv.toFloat(0);
    EXPECT_FLOAT_EQ(val, 0.0f);
}

// Test toRational with numeric string
TEST_F(StringValueBaseTest_808, ToRationalWithNumericString_808) {
    StringValue sv("5");
    Rational r = sv.toRational(0);
    // Expect rational representation of 5
    EXPECT_EQ(r.first, 5);
    EXPECT_EQ(r.second, 1);
}

// Test clone
TEST_F(StringValueBaseTest_808, Clone_808) {
    StringValue sv("CloneMe");
    auto cloned = sv.clone();
    ASSERT_NE(cloned, nullptr);
    std::ostringstream os1, os2;
    sv.write(os1);
    cloned->write(os2);
    EXPECT_EQ(os1.str(), os2.str());
}

// Test value_ is publicly accessible
TEST_F(StringValueBaseTest_808, ValueMemberAccessible_808) {
    StringValue sv("direct");
    EXPECT_EQ(sv.value_, "direct");
}

// Test read replaces existing value
TEST_F(StringValueBaseTest_808, ReadReplacesExistingValue_808) {
    StringValue sv("original");
    EXPECT_EQ(sv.value_, "original");
    sv.read("replaced");
    EXPECT_EQ(sv.value_, "replaced");
}

// Test with special characters
TEST_F(StringValueBaseTest_808, SpecialCharacters_808) {
    StringValue sv("Hello\nWorld\t!");
    EXPECT_EQ(sv.size(), 13u);
    std::ostringstream os;
    sv.write(os);
    EXPECT_EQ(os.str(), "Hello\nWorld\t!");
}

// Test with string containing null-like characters via byte buffer
TEST_F(StringValueBaseTest_808, ByteBufferWithEmbeddedNulls_808) {
    const byte data[] = {'A', 0, 'B', 'C'};
    StringValue sv("");
    sv.read(data, 4, littleEndian);
    // Behavior depends on implementation - size should be 4 or could stop at null
    // We just test it doesn't crash
    EXPECT_GE(sv.size(), 0u);
}

// Test write returns reference to same stream
TEST_F(StringValueBaseTest_808, WriteReturnsSameStream_808) {
    StringValue sv("stream");
    std::ostringstream os;
    std::ostream& returned = sv.write(os);
    EXPECT_EQ(&returned, &os);
}

// Test with large string
TEST_F(StringValueBaseTest_808, LargeString_808) {
    std::string large(10000, 'x');
    StringValue sv(large);
    EXPECT_EQ(sv.size(), 10000u);
    EXPECT_EQ(sv.value_, large);
}

// Test byte order independence for copy
TEST_F(StringValueBaseTest_808, CopyByteOrderIndependence_808) {
    StringValue sv("test");
    byte buf1[10] = {0};
    byte buf2[10] = {0};
    size_t copied1 = sv.copy(buf1, littleEndian);
    size_t copied2 = sv.copy(buf2, bigEndian);
    EXPECT_EQ(copied1, copied2);
    EXPECT_EQ(std::memcmp(buf1, buf2, copied1), 0);
}

// Test byte order independence for read
TEST_F(StringValueBaseTest_808, ReadByteOrderIndependence_808) {
    const byte data[] = {'H', 'i'};
    StringValue sv1("");
    StringValue sv2("");
    sv1.read(data, 2, littleEndian);
    sv2.read(data, 2, bigEndian);
    EXPECT_EQ(sv1.value_, sv2.value_);
}

// Test negative number string
TEST_F(StringValueBaseTest_808, ToInt64WithNegativeNumber_808) {
    StringValue sv("-42");
    int64_t val = sv.toInt64(0);
    EXPECT_EQ(val, -42);
}

// Test toInt64 with n parameter
TEST_F(StringValueBaseTest_808, ToInt64WithNParameterZero_808) {
    StringValue sv("100");
    int64_t val = sv.toInt64(0);
    EXPECT_EQ(val, 100);
}
