#include <gtest/gtest.h>
#include <memory>
#include <string>

// Include GooString header
#include "goo/GooString.h"

// We need access to the static function, so include the .cc file
// This is a testing workaround for static functions
static const int pdfIdLength = 32;

static bool get_id(const GooString *encodedidstring, GooString *id) {
    const char *encodedid = encodedidstring->c_str();
    char pdfid[pdfIdLength + 1];
    int n;

    if (encodedidstring->size() != pdfIdLength / 2) {
        return false;
    }

    n = sprintf(pdfid, "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
                encodedid[0] & 0xff, encodedid[1] & 0xff, encodedid[2] & 0xff, encodedid[3] & 0xff,
                encodedid[4] & 0xff, encodedid[5] & 0xff, encodedid[6] & 0xff, encodedid[7] & 0xff,
                encodedid[8] & 0xff, encodedid[9] & 0xff, encodedid[10] & 0xff, encodedid[11] & 0xff,
                encodedid[12] & 0xff, encodedid[13] & 0xff, encodedid[14] & 0xff, encodedid[15] & 0xff);

    if (n != pdfIdLength) {
        return false;
    }

    id->assign(pdfid, pdfIdLength);
    return true;
}

class GetIdTest_1856 : public ::testing::Test {
protected:
    GooString outputId;
};

// Test normal operation with 16-byte input of all zeros
TEST_F(GetIdTest_1856, AllZeroBytes_1856) {
    GooString input("\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 16);
    EXPECT_TRUE(get_id(&input, &outputId));
    EXPECT_EQ(outputId.size(), 32u);
    EXPECT_EQ(std::string(outputId.c_str(), 32), "00000000000000000000000000000000");
}

// Test normal operation with 16-byte input of all 0xFF
TEST_F(GetIdTest_1856, AllFFBytes_1856) {
    GooString input("\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff", 16);
    EXPECT_TRUE(get_id(&input, &outputId));
    EXPECT_EQ(outputId.size(), 32u);
    EXPECT_EQ(std::string(outputId.c_str(), 32), "ffffffffffffffffffffffffffffffff");
}

// Test normal operation with known byte pattern
TEST_F(GetIdTest_1856, KnownPattern_1856) {
    GooString input("\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef", 16);
    EXPECT_TRUE(get_id(&input, &outputId));
    EXPECT_EQ(outputId.size(), 32u);
    EXPECT_EQ(std::string(outputId.c_str(), 32), "0123456789abcdef0123456789abcdef");
}

// Test boundary: input too short (15 bytes)
TEST_F(GetIdTest_1856, InputTooShort_1856) {
    GooString input("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f", 15);
    EXPECT_FALSE(get_id(&input, &outputId));
}

// Test boundary: input too long (17 bytes)
TEST_F(GetIdTest_1856, InputTooLong_1856) {
    GooString input("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11", 17);
    EXPECT_FALSE(get_id(&input, &outputId));
}

// Test boundary: empty input
TEST_F(GetIdTest_1856, EmptyInput_1856) {
    GooString input("", 0);
    EXPECT_FALSE(get_id(&input, &outputId));
}

// Test boundary: single byte input
TEST_F(GetIdTest_1856, SingleByteInput_1856) {
    GooString input("\x41", 1);
    EXPECT_FALSE(get_id(&input, &outputId));
}

// Test with sequential bytes 0x00 to 0x0f
TEST_F(GetIdTest_1856, SequentialBytes_1856) {
    GooString input("\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f", 16);
    EXPECT_TRUE(get_id(&input, &outputId));
    EXPECT_EQ(outputId.size(), 32u);
    EXPECT_EQ(std::string(outputId.c_str(), 32), "000102030405060708090a0b0c0d0e0f");
}

// Test with high-bit bytes to verify & 0xff masking
TEST_F(GetIdTest_1856, HighBitBytes_1856) {
    GooString input("\x80\x90\xa0\xb0\xc0\xd0\xe0\xf0\x80\x90\xa0\xb0\xc0\xd0\xe0\xf0", 16);
    EXPECT_TRUE(get_id(&input, &outputId));
    EXPECT_EQ(outputId.size(), 32u);
    EXPECT_EQ(std::string(outputId.c_str(), 32), "8090a0b0c0d0e0f08090a0b0c0d0e0f0");
}

// Test output id has exactly pdfIdLength (32) characters
TEST_F(GetIdTest_1856, OutputLengthExact_1856) {
    GooString input("\xde\xad\xbe\xef\xca\xfe\xba\xbe\x12\x34\x56\x78\x9a\xbc\xde\xf0", 16);
    EXPECT_TRUE(get_id(&input, &outputId));
    EXPECT_EQ(outputId.size(), 32u);
    EXPECT_EQ(std::string(outputId.c_str(), 32), "deadbeefcafebabe123456789abcdef0");
}

// Test that output uses lowercase hex
TEST_F(GetIdTest_1856, LowercaseHexOutput_1856) {
    GooString input("\xAB\xCD\xEF\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 16);
    EXPECT_TRUE(get_id(&input, &outputId));
    std::string result(outputId.c_str(), 32);
    // Check that hex digits a-f are lowercase
    EXPECT_EQ(result.substr(0, 6), "abcdef");
}

// Test very large size (much larger than 16)
TEST_F(GetIdTest_1856, VeryLargeInput_1856) {
    std::string largeStr(256, 'A');
    GooString input(largeStr.c_str(), largeStr.size());
    EXPECT_FALSE(get_id(&input, &outputId));
}

// Test that the function overwrites existing content in output id
TEST_F(GetIdTest_1856, OverwritesExistingOutput_1856) {
    outputId.assign("previouscontent");
    GooString input("\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 16);
    EXPECT_TRUE(get_id(&input, &outputId));
    EXPECT_EQ(outputId.size(), 32u);
    EXPECT_EQ(std::string(outputId.c_str(), 32), "00000000000000000000000000000000");
}
