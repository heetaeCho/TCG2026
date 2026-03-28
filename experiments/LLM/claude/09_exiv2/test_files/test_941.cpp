#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "exiv2/exif.hpp"
#include "exiv2/value.hpp"
#include "exiv2/types.hpp"
#include "canonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNoteTest_941 : public ::testing::Test {
protected:
    std::ostringstream os;

    // Helper to create an UnsignedLong value with a specific uint32_t
    Value::UniquePtr makeULongValue(uint32_t val) {
        auto v = Value::create(unsignedLong);
        // Encode the uint32_t as little-endian bytes
        byte buf[4];
        buf[0] = static_cast<byte>(val & 0xFF);
        buf[1] = static_cast<byte>((val >> 8) & 0xFF);
        buf[2] = static_cast<byte>((val >> 16) & 0xFF);
        buf[3] = static_cast<byte>((val >> 24) & 0xFF);
        v->read(buf, 4, littleEndian);
        return v;
    }

    // Helper to create an UnsignedShort value
    Value::UniquePtr makeUShortValue(uint16_t val) {
        auto v = Value::create(unsignedShort);
        byte buf[2];
        buf[0] = static_cast<byte>(val & 0xFF);
        buf[1] = static_cast<byte>((val >> 8) & 0xFF);
        v->read(buf, 2, littleEndian);
        return v;
    }

    // Helper to set a model in ExifData
    void setModel(ExifData& exifData, const std::string& model) {
        exifData["Exif.Image.Model"] = model;
    }
};

// Test: nullptr metadata should produce fallback output "(value)"
TEST_F(CanonMakerNoteTest_941, NullMetadata_941) {
    auto val = makeULongValue(12345);
    CanonMakerNote::printFiFileNumber(os, *val, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: Wrong type (not unsignedLong) should produce fallback output
TEST_F(CanonMakerNoteTest_941, WrongTypeId_941) {
    auto val = makeUShortValue(100);
    ExifData metadata;
    setModel(metadata, "Canon EOS 20D");
    CanonMakerNote::printFiFileNumber(os, *val, &metadata);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: Empty value (count == 0) should produce fallback output
TEST_F(CanonMakerNoteTest_941, EmptyValue_941) {
    auto val = Value::create(unsignedLong);
    // Don't read any data, so count should be 0
    ExifData metadata;
    setModel(metadata, "Canon EOS 20D");
    CanonMakerNote::printFiFileNumber(os, *val, &metadata);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: No model key in metadata should produce fallback output
TEST_F(CanonMakerNoteTest_941, NoModelInMetadata_941) {
    auto val = makeULongValue(12345);
    ExifData metadata;
    // Don't add any model
    CanonMakerNote::printFiFileNumber(os, *val, &metadata);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: Unknown model should produce fallback output
TEST_F(CanonMakerNoteTest_941, UnknownModel_941) {
    auto val = makeULongValue(12345);
    ExifData metadata;
    setModel(metadata, "Canon EOS 5D Mark III");
    CanonMakerNote::printFiFileNumber(os, *val, &metadata);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: 20D model should produce formatted output (not parenthesized)
TEST_F(CanonMakerNoteTest_941, Model20D_941) {
    // Value: construct a meaningful uint32_t
    // For 20D format: "{}-{:04}" where first = (val & 0xffc0) >> 6, second = ((val >> 16) & 0xff) + ((val & 0x3f) << 8)
    // Let's use val = 0x00010040 => first = (0x40 & 0xffc0)>>6 = 1, second = ((0x01)&0xff) + ((0x40&0x3f)<<8) = 1 + 0 = 1
    uint32_t rawVal = 0x00010040;
    auto val = makeULongValue(rawVal);
    ExifData metadata;
    setModel(metadata, "Canon EOS 20D");
    CanonMakerNote::printFiFileNumber(os, *val, &metadata);
    std::string result = os.str();
    // Should not be parenthesized
    EXPECT_NE(result.front(), '(');
    // Should contain a dash
    EXPECT_NE(result.find('-'), std::string::npos);
}

// Test: 350D model should produce formatted output
TEST_F(CanonMakerNoteTest_941, Model350D_941) {
    uint32_t rawVal = 0x00020080;
    auto val = makeULongValue(rawVal);
    ExifData metadata;
    setModel(metadata, "Canon EOS 350D");
    CanonMakerNote::printFiFileNumber(os, *val, &metadata);
    std::string result = os.str();
    EXPECT_NE(result.front(), '(');
    EXPECT_NE(result.find('-'), std::string::npos);
}

// Test: REBEL XT model (ends with "REBEL XT") should match 20D branch
TEST_F(CanonMakerNoteTest_941, ModelRebelXT_941) {
    uint32_t rawVal = 0x000100C0; // (0xC0 & 0xffc0) >> 6 = 3, second part includes high bits
    auto val = makeULongValue(rawVal);
    ExifData metadata;
    setModel(metadata, "Canon EOS REBEL XT");
    CanonMakerNote::printFiFileNumber(os, *val, &metadata);
    std::string result = os.str();
    EXPECT_NE(result.front(), '(');
    EXPECT_NE(result.find('-'), std::string::npos);
}

// Test: Kiss Digital N model should match 20D branch
TEST_F(CanonMakerNoteTest_941, ModelKissDigitalN_941) {
    uint32_t rawVal = 0x00030100;
    auto val = makeULongValue(rawVal);
    ExifData metadata;
    setModel(metadata, "Canon EOS Kiss Digital N");
    CanonMakerNote::printFiFileNumber(os, *val, &metadata);
    std::string result = os.str();
    EXPECT_NE(result.front(), '(');
    EXPECT_NE(result.find('-'), std::string::npos);
}

// Test: 30D model should produce formatted output (second branch)
TEST_F(CanonMakerNoteTest_941, Model30D_941) {
    // For 30D format: dn = (val & 0xffc00) >> 10, while dn < 100: dn += 0x40
    // second = ((val & 0x3ff) << 4) + ((val >> 20) & 0x0f)
    uint32_t rawVal = 0x00100400; // dn = (0x0400 & 0xffc00) >> 10 = 1, loops until >= 100
    auto val = makeULongValue(rawVal);
    ExifData metadata;
    setModel(metadata, "Canon EOS 30D");
    CanonMakerNote::printFiFileNumber(os, *val, &metadata);
    std::string result = os.str();
    EXPECT_NE(result.front(), '(');
    EXPECT_NE(result.find('-'), std::string::npos);
}

// Test: 400D model should produce formatted output (second branch)
TEST_F(CanonMakerNoteTest_941, Model400D_941) {
    uint32_t rawVal = 0x00119C00; // dn = (0x19C00 & 0xffc00) >> 10 = 103
    auto val = makeULongValue(rawVal);
    ExifData metadata;
    setModel(metadata, "Canon EOS 400D");
    CanonMakerNote::printFiFileNumber(os, *val, &metadata);
    std::string result = os.str();
    EXPECT_NE(result.front(), '(');
    EXPECT_NE(result.find('-'), std::string::npos);
}

// Test: REBEL XTi model should match 30D branch
TEST_F(CanonMakerNoteTest_941, ModelRebelXTi_941) {
    uint32_t rawVal = 0x00119C00;
    auto val = makeULongValue(rawVal);
    ExifData metadata;
    setModel(metadata, "Canon EOS REBEL XTi");
    CanonMakerNote::printFiFileNumber(os, *val, &metadata);
    std::string result = os.str();
    EXPECT_NE(result.front(), '(');
    EXPECT_NE(result.find('-'), std::string::npos);
}

// Test: Kiss Digital X model should match 30D branch
TEST_F(CanonMakerNoteTest_941, ModelKissDigitalX_941) {
    uint32_t rawVal = 0x00119C00;
    auto val = makeULongValue(rawVal);
    ExifData metadata;
    setModel(metadata, "Canon EOS Kiss Digital X");
    CanonMakerNote::printFiFileNumber(os, *val, &metadata);
    std::string result = os.str();
    EXPECT_NE(result.front(), '(');
    EXPECT_NE(result.find('-'), std::string::npos);
}

// Test: K236 model should match 30D branch
TEST_F(CanonMakerNoteTest_941, ModelK236_941) {
    uint32_t rawVal = 0x00119C00;
    auto val = makeULongValue(rawVal);
    ExifData metadata;
    setModel(metadata, "Canon K236");
    CanonMakerNote::printFiFileNumber(os, *val, &metadata);
    std::string result = os.str();
    EXPECT_NE(result.front(), '(');
    EXPECT_NE(result.find('-'), std::string::npos);
}

// Test: 20D model with val = 0 should produce "0-0000"
TEST_F(CanonMakerNoteTest_941, Model20DZeroValue_941) {
    uint32_t rawVal = 0x00000000;
    auto val = makeULongValue(rawVal);
    ExifData metadata;
    setModel(metadata, "Canon EOS 20D");
    CanonMakerNote::printFiFileNumber(os, *val, &metadata);
    std::string result = os.str();
    EXPECT_EQ(result, "0-0000");
}

// Test: 20D specific value computation
TEST_F(CanonMakerNoteTest_941, Model20DSpecificValue_941) {
    // val = 0x00030140
    // first = (0x0140 & 0xffc0) >> 6 = (0x0100) >> 6 = 4  (0x140 & 0xFFC0 = 0x140 & 0xFFC0 = 0x0100, >> 6 = 4)
    // Actually: 0x0140 & 0xffc0 = 0x0140 & 0xFFC0 = 0x0100, >> 6 = 4
    // second = ((0x0003)&0xff) + ((0x0140 & 0x3f)<<8) = 3 + (0x00 << 8) = 3
    // Wait: 0x0140 & 0x3f = 0x00. So second = 3.
    // Output: "4-0003"
    uint32_t rawVal = 0x00030140;
    auto val = makeULongValue(rawVal);
    ExifData metadata;
    setModel(metadata, "Canon EOS 20D");
    CanonMakerNote::printFiFileNumber(os, *val, &metadata);
    std::string result = os.str();
    EXPECT_EQ(result, "4-0003");
}

// Test: 30D with dn that needs looping (dn < 100 initially)
TEST_F(CanonMakerNoteTest_941, Model30DDnLooping_941) {
    // dn starts at (val & 0xffc00) >> 10
    // If we set val such that dn = 0, it should loop adding 0x40 = 64 each time
    // 0 + 64 = 64 < 100, 64 + 64 = 128 >= 100, so dn = 128
    // second = ((val & 0x3ff) << 4) + ((val >> 20) & 0x0f)
    // val = 0x00000000 => dn=0, loops to 128, second = 0
    // Output: "128-0000"
    uint32_t rawVal = 0x00000000;
    auto val = makeULongValue(rawVal);
    ExifData metadata;
    setModel(metadata, "Canon EOS 30D");
    CanonMakerNote::printFiFileNumber(os, *val, &metadata);
    std::string result = os.str();
    EXPECT_EQ(result, "128-0000");
}

// Test: 30D with dn already >= 100 (no looping needed)
TEST_F(CanonMakerNoteTest_941, Model30DNoDnLooping_941) {
    // We want dn = 100, so (val & 0xffc00) >> 10 = 100
    // val & 0xffc00 = 100 << 10 = 102400 = 0x19000
    // second = 0
    // val = 0x00019000
    uint32_t rawVal = 0x00019000;
    auto val = makeULongValue(rawVal);
    ExifData metadata;
    setModel(metadata, "Canon EOS 30D");
    CanonMakerNote::printFiFileNumber(os, *val, &metadata);
    std::string result = os.str();
    EXPECT_EQ(result, "100-0000");
}

// Test: Return value is the same ostream reference
TEST_F(CanonMakerNoteTest_941, ReturnsSameStream_941) {
    auto val = makeULongValue(0);
    ExifData metadata;
    setModel(metadata, "Canon EOS 20D");
    std::ostream& ret = CanonMakerNote::printFiFileNumber(os, *val, &metadata);
    EXPECT_EQ(&ret, &os);
}

// Test: Return value is the same ostream reference for fallback case
TEST_F(CanonMakerNoteTest_941, ReturnsSameStreamFallback_941) {
    auto val = makeULongValue(0);
    std::ostream& ret = CanonMakerNote::printFiFileNumber(os, *val, nullptr);
    EXPECT_EQ(&ret, &os);
}

// Test: Model string that contains "REBEL XT" but not at the end (should not match REBEL XT suffix check if model also doesn't contain 20D/350D/Kiss Digital N)
// "REBEL XT something" - check that it doesn't match the suffix check, but may match REBEL XTi if it contains that
TEST_F(CanonMakerNoteTest_941, ModelRebelXTNotAtEnd_941) {
    uint32_t rawVal = 0x00010040;
    auto val = makeULongValue(rawVal);
    ExifData metadata;
    // This model doesn't contain 20D, 350D, Kiss Digital N, and doesn't end with "REBEL XT"
    // It also doesn't contain 30D, 400D, REBEL XTi, Kiss Digital X, K236
    setModel(metadata, "Canon REBEL XT Model Z");
    CanonMakerNote::printFiFileNumber(os, *val, &metadata);
    std::string result = os.str();
    // Should be fallback since none of the conditions match
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: Model that exactly ends with "REBEL XT" (8 chars at end)
TEST_F(CanonMakerNoteTest_941, ModelExactRebelXTSuffix_941) {
    uint32_t rawVal = 0x00010040;
    auto val = makeULongValue(rawVal);
    ExifData metadata;
    setModel(metadata, "SomeModelREBEL XT");
    CanonMakerNote::printFiFileNumber(os, *val, &metadata);
    std::string result = os.str();
    // Should match the 20D branch since it ends with "REBEL XT"
    EXPECT_NE(result.front(), '(');
    EXPECT_NE(result.find('-'), std::string::npos);
}

// Test: 20D model with large value to verify bit masking
TEST_F(CanonMakerNoteTest_941, Model20DLargeValue_941) {
    // val = 0xFFFFFFFF
    // first = (0xFFFFFFFF & 0xffc0) >> 6 = (0xFFC0) >> 6 = 0x3FF = 1023 (but val is 32 bit, 0xFFFF & 0xFFC0 = 0xFFC0, >> 6 = 0x3FF = 1023)
    // Wait: 0xFFFFFFFF & 0xFFC0 = 0xFFFFFFC0, >> 6 = 0x03FFFFFF = 67108863
    // second = ((0xFFFFFFFF >> 16) & 0xFF) + ((0xFFFFFFFF & 0x3F) << 8) = 0xFF + (0x3F << 8) = 255 + 16128 = 16383
    uint32_t rawVal = 0xFFFFFFFF;
    auto val = makeULongValue(rawVal);
    ExifData metadata;
    setModel(metadata, "Canon EOS 20D");
    CanonMakerNote::printFiFileNumber(os, *val, &metadata);
    std::string result = os.str();
    EXPECT_NE(result.front(), '(');
    EXPECT_NE(result.find('-'), std::string::npos);
}
