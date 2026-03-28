#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <sstream>

// Include internal headers for access to the function
#include "fujimn_int.hpp"

using namespace Exiv2;

class PrintFujiDriveSettingTest_625 : public ::testing::Test {
protected:
    std::ostringstream os;
    ExifData exifData;

    // Helper to create a ULongValue with a specific uint32 value
    std::unique_ptr<Value> makeULongValue(uint32_t val) {
        auto v = std::make_unique<ValueType<uint32_t>>(TypeId::unsignedLong);
        v->value_.push_back(val);
        return v;
    }

    std::string printTag(uint32_t val) {
        os.str("");
        os.clear();
        auto v = makeULongValue(val);
        // Use the ExifKey for FujiMn DriveSetting tag and print through exiv2's print mechanism
        ExifKey key("Exif.Fujifilm.DriveSetting");
        auto tag = ExifTags::tagList("Fujifilm");
        // Print via the tag's print method
        key.tagInfo().print_(os, *v, &exifData);
        return os.str();
    }
};

// Test with all zeros: byte1=0, fps=0
// byte1=0 should match a known entry in fujiDriveSettingByte1 (likely "Single" or similar)
// fps=0 means no fps printed, byte1=0 means no byte2/byte3 printed
TEST_F(PrintFujiDriveSettingTest_625, AllZeros_625) {
    std::string result = printTag(0x00000000);
    // Should not contain fps or parenthesized unknown bytes
    EXPECT_TRUE(result.find("fps") == std::string::npos);
    // byte1 is 0, so no extra bytes printed
    EXPECT_FALSE(result.empty());
}

// Test with byte1=0 and non-zero fps
// fps should be printed, but byte2/byte3 should not (since byte1==0)
TEST_F(PrintFujiDriveSettingTest_625, ZeroByte1WithFps_625) {
    uint32_t val = (10u << 24); // fps=10, byte1=0
    std::string result = printTag(val);
    EXPECT_NE(result.find("10 fps"), std::string::npos);
}

// Test with unknown byte1 value
// Should print byte1 in parentheses like "(253)"
TEST_F(PrintFujiDriveSettingTest_625, UnknownByte1_625) {
    uint32_t val = 0x00000FD; // byte1=253, unlikely to be in the table
    std::string result = printTag(val);
    // If not in table, prints "(253)"
    // byte1 != 0, so byte2 and byte3 will also be printed
    EXPECT_NE(result.find("("), std::string::npos);
}

// Test with non-zero byte1 to ensure byte2 and byte3 are printed
TEST_F(PrintFujiDriveSettingTest_625, NonZeroByte1PrintsExtraBytes_625) {
    // byte1=1, byte2=5, byte3=10, fps=0
    uint32_t val = (0u << 24) | (10u << 16) | (5u << 8) | 1u;
    std::string result = printTag(val);
    // byte1 != 0, so should print byte2 and byte3
    EXPECT_NE(result.find("5"), std::string::npos);
    EXPECT_NE(result.find("10"), std::string::npos);
}

// Test with all components non-zero
TEST_F(PrintFujiDriveSettingTest_625, AllComponentsNonZero_625) {
    // byte1=1, byte2=2, byte3=3, fps=30
    uint32_t val = (30u << 24) | (3u << 16) | (2u << 8) | 1u;
    std::string result = printTag(val);
    EXPECT_NE(result.find("30 fps"), std::string::npos);
    // byte1 != 0 so byte2 and byte3 should appear
    EXPECT_NE(result.find("2"), std::string::npos);
    EXPECT_NE(result.find("3"), std::string::npos);
}

// Test with byte1=0, fps=0 produces output without fps or extra bytes
TEST_F(PrintFujiDriveSettingTest_625, Byte1ZeroNoFpsNoExtraBytes_625) {
    std::string result = printTag(0x00000000);
    EXPECT_TRUE(result.find("fps") == std::string::npos);
    // No comma should appear if no fps and byte1==0
    // The only output should be the label for byte1=0
}

// Test with byte1=0, byte2 and byte3 non-zero but they should NOT be printed since byte1==0
TEST_F(PrintFujiDriveSettingTest_625, Byte1ZeroSuppressesExtraBytes_625) {
    uint32_t val = (0u << 24) | (99u << 16) | (88u << 8) | 0u;
    std::string result = printTag(val);
    // byte1==0 so byte2/byte3 should not appear
    EXPECT_TRUE(result.find("99") == std::string::npos);
    EXPECT_TRUE(result.find("88") == std::string::npos);
}

// Test with fps=255 (max single byte fps)
TEST_F(PrintFujiDriveSettingTest_625, MaxFps_625) {
    uint32_t val = (255u << 24) | 0u;
    std::string result = printTag(val);
    EXPECT_NE(result.find("255 fps"), std::string::npos);
}

// Test with fps=1 (minimum non-zero fps)
TEST_F(PrintFujiDriveSettingTest_625, MinNonZeroFps_625) {
    uint32_t val = (1u << 24) | 0u;
    std::string result = printTag(val);
    EXPECT_NE(result.find("1 fps"), std::string::npos);
}
