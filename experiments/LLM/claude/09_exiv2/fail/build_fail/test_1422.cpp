#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

using namespace Exiv2;

class PrintExifVersionTest_1422 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test normal operation with a valid 4-byte undefined value representing "0230"
TEST_F(PrintExifVersionTest_1422, ValidExifVersion0230_1422) {
    DataBuf buf(4);
    buf.data()[0] = '0';
    buf.data()[1] = '2';
    buf.data()[2] = '3';
    buf.data()[3] = '0';
    
    Value::UniquePtr value = Value::create(undefined);
    value->read(buf.data(), 4, invalidByteOrder);
    
    Internal::printExifVersion(os, *value, nullptr);
    std::string result = os.str();
    // Should print a formatted version string like "2.30"
    EXPECT_FALSE(result.empty());
    // Should NOT be wrapped in parentheses (which indicates error path)
    EXPECT_NE(result.front(), '(');
}

// Test normal operation with "0210"
TEST_F(PrintExifVersionTest_1422, ValidExifVersion0210_1422) {
    DataBuf buf(4);
    buf.data()[0] = '0';
    buf.data()[1] = '2';
    buf.data()[2] = '1';
    buf.data()[3] = '0';
    
    Value::UniquePtr value = Value::create(undefined);
    value->read(buf.data(), 4, invalidByteOrder);
    
    Internal::printExifVersion(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.front(), '(');
}

// Test normal operation with "0220"
TEST_F(PrintExifVersionTest_1422, ValidExifVersion0220_1422) {
    DataBuf buf(4);
    buf.data()[0] = '0';
    buf.data()[1] = '2';
    buf.data()[2] = '2';
    buf.data()[3] = '0';
    
    Value::UniquePtr value = Value::create(undefined);
    value->read(buf.data(), 4, invalidByteOrder);
    
    Internal::printExifVersion(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.front(), '(');
}

// Test boundary: wrong size (3 bytes) should trigger parenthesized output
TEST_F(PrintExifVersionTest_1422, WrongSize3Bytes_1422) {
    DataBuf buf(3);
    buf.data()[0] = '0';
    buf.data()[1] = '2';
    buf.data()[2] = '3';
    
    Value::UniquePtr value = Value::create(undefined);
    value->read(buf.data(), 3, invalidByteOrder);
    
    Internal::printExifVersion(os, *value, nullptr);
    std::string result = os.str();
    // Should be parenthesized because size != 4
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test boundary: wrong size (5 bytes) should trigger parenthesized output
TEST_F(PrintExifVersionTest_1422, WrongSize5Bytes_1422) {
    DataBuf buf(5);
    buf.data()[0] = '0';
    buf.data()[1] = '2';
    buf.data()[2] = '3';
    buf.data()[3] = '0';
    buf.data()[4] = '0';
    
    Value::UniquePtr value = Value::create(undefined);
    value->read(buf.data(), 5, invalidByteOrder);
    
    Internal::printExifVersion(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test boundary: empty value (0 bytes) should trigger parenthesized output
TEST_F(PrintExifVersionTest_1422, EmptyValue_1422) {
    Value::UniquePtr value = Value::create(undefined);
    // Read with 0 bytes
    value->read(nullptr, 0, invalidByteOrder);
    
    Internal::printExifVersion(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test error case: wrong type (asciiString instead of undefined) with 4 bytes
TEST_F(PrintExifVersionTest_1422, WrongTypeAscii_1422) {
    Value::UniquePtr value = Value::create(asciiString);
    value->read("0230");
    
    Internal::printExifVersion(os, *value, nullptr);
    std::string result = os.str();
    // typeId is not undefined, so parenthesized output
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test error case: wrong type (unsignedShort) 
TEST_F(PrintExifVersionTest_1422, WrongTypeUnsignedShort_1422) {
    Value::UniquePtr value = Value::create(unsignedShort);
    value->read("48 50 51 48");
    
    Internal::printExifVersion(os, *value, nullptr);
    std::string result = os.str();
    // typeId is not undefined, so parenthesized output
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test normal operation with "0100" version
TEST_F(PrintExifVersionTest_1422, ValidExifVersion0100_1422) {
    DataBuf buf(4);
    buf.data()[0] = '0';
    buf.data()[1] = '1';
    buf.data()[2] = '0';
    buf.data()[3] = '0';
    
    Value::UniquePtr value = Value::create(undefined);
    value->read(buf.data(), 4, invalidByteOrder);
    
    Internal::printExifVersion(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.front(), '(');
}

// Test with nullptr ExifData (should still work - it's unused)
TEST_F(PrintExifVersionTest_1422, NullExifData_1422) {
    DataBuf buf(4);
    buf.data()[0] = '0';
    buf.data()[1] = '2';
    buf.data()[2] = '3';
    buf.data()[3] = '0';
    
    Value::UniquePtr value = Value::create(undefined);
    value->read(buf.data(), 4, invalidByteOrder);
    
    Internal::printExifVersion(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.front(), '(');
}

// Test boundary: 1 byte undefined value
TEST_F(PrintExifVersionTest_1422, SingleByte_1422) {
    DataBuf buf(1);
    buf.data()[0] = '0';
    
    Value::UniquePtr value = Value::create(undefined);
    value->read(buf.data(), 1, invalidByteOrder);
    
    Internal::printExifVersion(os, *value, nullptr);
    std::string result = os.str();
    // size != 4, should be parenthesized
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test with all zero bytes
TEST_F(PrintExifVersionTest_1422, AllZeroBytes_1422) {
    DataBuf buf(4);
    buf.data()[0] = 0;
    buf.data()[1] = 0;
    buf.data()[2] = 0;
    buf.data()[3] = 0;
    
    Value::UniquePtr value = Value::create(undefined);
    value->read(buf.data(), 4, invalidByteOrder);
    
    Internal::printExifVersion(os, *value, nullptr);
    std::string result = os.str();
    // Valid size and type, so it should not be parenthesized
    EXPECT_NE(result.front(), '(');
}

// Test with "0300" version
TEST_F(PrintExifVersionTest_1422, ValidExifVersion0300_1422) {
    DataBuf buf(4);
    buf.data()[0] = '0';
    buf.data()[1] = '3';
    buf.data()[2] = '0';
    buf.data()[3] = '0';
    
    Value::UniquePtr value = Value::create(undefined);
    value->read(buf.data(), 4, invalidByteOrder);
    
    Internal::printExifVersion(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.front(), '(');
}
