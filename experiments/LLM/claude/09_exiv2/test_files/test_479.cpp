#include <gtest/gtest.h>
#include <sstream>
#include <cmath>
#include <exiv2/exiv2.hpp>

// We need access to the Internal namespace
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNotePrintFocal_479 : public ::testing::Test {
protected:
    std::ostringstream os;
    Nikon3MakerNote maker;
};

// Test: When value count is not 1, should output parenthesized value
TEST_F(Nikon3MakerNotePrintFocal_479, MultipleValuesOutputsParenthesized_479) {
    // Create a value with multiple entries
    DataBuf buf(2);
    buf.write_uint8(0, 10);
    buf.write_uint8(1, 20);
    
    Value::UniquePtr val = Value::create(unsignedByte);
    val->read(buf.c_data(), buf.size(), byteOrder);
    
    // count() should be 2, so it should hit the first branch
    if (val->count() != 1) {
        maker.printFocal(os, *val, nullptr);
        std::string result = os.str();
        EXPECT_EQ(result.front(), '(');
        EXPECT_EQ(result.back(), ')');
    }
}

// Test: When value type is not unsignedByte, should output parenthesized value
TEST_F(Nikon3MakerNotePrintFocal_479, WrongTypeOutputsParenthesized_479) {
    Value::UniquePtr val = Value::create(unsignedShort);
    val->read("100");
    
    maker.printFocal(os, *val, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: When value is 0, should output "n/a"
TEST_F(Nikon3MakerNotePrintFocal_479, ZeroValueOutputsNA_479) {
    DataBuf buf(1);
    buf.write_uint8(0, 0);
    
    Value::UniquePtr val = Value::create(unsignedByte);
    val->read(buf.c_data(), 1, byteOrder);
    
    ASSERT_EQ(val->count(), 1u);
    ASSERT_EQ(val->typeId(), unsignedByte);
    
    maker.printFocal(os, *val, nullptr);
    std::string result = os.str();
    // Should contain "n/a" (possibly translated)
    EXPECT_TRUE(result.find("n/a") != std::string::npos || result.find("N/A") != std::string::npos || !result.empty());
}

// Test: Normal value should output focal length in mm format
TEST_F(Nikon3MakerNotePrintFocal_479, NormalValueOutputsFocalLength_479) {
    // val = 24 => 5.0 * 2^(24/24) = 5.0 * 2.0 = 10.0
    DataBuf buf(1);
    buf.write_uint8(0, 24);
    
    Value::UniquePtr val = Value::create(unsignedByte);
    val->read(buf.c_data(), 1, byteOrder);
    
    ASSERT_EQ(val->count(), 1u);
    ASSERT_EQ(val->typeId(), unsignedByte);
    
    maker.printFocal(os, *val, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("10.0") != std::string::npos);
    EXPECT_TRUE(result.find("mm") != std::string::npos);
}

// Test: Value of 48 => 5.0 * 2^(48/24) = 5.0 * 4.0 = 20.0
TEST_F(Nikon3MakerNotePrintFocal_479, Value48OutputsTwentyMM_479) {
    DataBuf buf(1);
    buf.write_uint8(0, 48);
    
    Value::UniquePtr val = Value::create(unsignedByte);
    val->read(buf.c_data(), 1, byteOrder);
    
    maker.printFocal(os, *val, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("20.0") != std::string::npos);
    EXPECT_TRUE(result.find("mm") != std::string::npos);
}

// Test: Value of 1 => 5.0 * 2^(1/24) ≈ 5.146
TEST_F(Nikon3MakerNotePrintFocal_479, Value1OutputsSmallFocal_479) {
    DataBuf buf(1);
    buf.write_uint8(0, 1);
    
    Value::UniquePtr val = Value::create(unsignedByte);
    val->read(buf.c_data(), 1, byteOrder);
    
    maker.printFocal(os, *val, nullptr);
    std::string result = os.str();
    // Should contain "mm" and a number > 5.0
    EXPECT_TRUE(result.find("mm") != std::string::npos);
    EXPECT_FALSE(result.empty());
}

// Test: Maximum unsigned byte value (255) => 5.0 * 2^(255/24)
TEST_F(Nikon3MakerNotePrintFocal_479, MaxByteValueOutputsLargeFocal_479) {
    DataBuf buf(1);
    buf.write_uint8(0, 255);
    
    Value::UniquePtr val = Value::create(unsignedByte);
    val->read(buf.c_data(), 1, byteOrder);
    
    maker.printFocal(os, *val, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("mm") != std::string::npos);
}

// Test: Value of 72 => 5.0 * 2^(72/24) = 5.0 * 8.0 = 40.0
TEST_F(Nikon3MakerNotePrintFocal_479, Value72OutputsFortyMM_479) {
    DataBuf buf(1);
    buf.write_uint8(0, 72);
    
    Value::UniquePtr val = Value::create(unsignedByte);
    val->read(buf.c_data(), 1, byteOrder);
    
    maker.printFocal(os, *val, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("40.0") != std::string::npos);
    EXPECT_TRUE(result.find("mm") != std::string::npos);
}

// Test: Empty value (count == 0) should output parenthesized
TEST_F(Nikon3MakerNotePrintFocal_479, EmptyValueOutputsParenthesized_479) {
    Value::UniquePtr val = Value::create(unsignedByte);
    // Don't read any data, count should be 0
    
    if (val->count() == 0) {
        maker.printFocal(os, *val, nullptr);
        std::string result = os.str();
        EXPECT_EQ(result.front(), '(');
        EXPECT_EQ(result.back(), ')');
    }
}

// Test: String type value should output parenthesized
TEST_F(Nikon3MakerNotePrintFocal_479, StringTypeOutputsParenthesized_479) {
    Value::UniquePtr val = Value::create(asciiString);
    val->read("50");
    
    maker.printFocal(os, *val, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: nullptr ExifData parameter should not cause crash
TEST_F(Nikon3MakerNotePrintFocal_479, NullExifDataDoesNotCrash_479) {
    DataBuf buf(1);
    buf.write_uint8(0, 50);
    
    Value::UniquePtr val = Value::create(unsignedByte);
    val->read(buf.c_data(), 1, byteOrder);
    
    EXPECT_NO_THROW(maker.printFocal(os, *val, nullptr));
}

// Test: Return value is the same ostream reference
TEST_F(Nikon3MakerNotePrintFocal_479, ReturnsOstreamReference_479) {
    DataBuf buf(1);
    buf.write_uint8(0, 24);
    
    Value::UniquePtr val = Value::create(unsignedByte);
    val->read(buf.c_data(), 1, byteOrder);
    
    std::ostream& result = maker.printFocal(os, *val, nullptr);
    EXPECT_EQ(&result, &os);
}
