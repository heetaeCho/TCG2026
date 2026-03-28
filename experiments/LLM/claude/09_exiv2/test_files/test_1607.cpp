#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>
#include "sonymn_int.hpp"

// Since the class is in Internal namespace, we need to access it
// We'll include the necessary headers and recreate the class interface as needed

namespace Exiv2 {
namespace Internal {

class SonyMakerNote {
public:
    std::ostream& printLensSpec(std::ostream& os, const Value& value, const ExifData*);
};

} // namespace Internal
} // namespace Exiv2

// If the above forward declaration doesn't work, we rely on the actual header.
// For testing purposes, we redefine inline based on the provided code.

// Actually, let's just include and use the code as provided. We'll create a test fixture.

using namespace Exiv2;
using namespace Exiv2::Internal;

class SonyMakerNoteTest_1607 : public ::testing::Test {
protected:
    SonyMakerNote maker;
    std::ostringstream os;

    // Helper to create a Value with 8 unsigned bytes
    std::unique_ptr<Value> makeUnsignedByteValue(const std::vector<uint8_t>& bytes) {
        auto val = Value::create(unsignedByte);
        for (auto b : bytes) {
            val->read(reinterpret_cast<const byte*>(&b), 1, invalidByteOrder);
        }
        return val;
    }

    // Helper to create a Value with wrong type (e.g., unsignedShort)
    std::unique_ptr<Value> makeUnsignedShortValue(const std::vector<uint16_t>& shorts) {
        auto val = Value::create(unsignedShort);
        for (auto s : shorts) {
            byte buf[2];
            buf[0] = static_cast<byte>(s & 0xff);
            buf[1] = static_cast<byte>((s >> 8) & 0xff);
            val->read(buf, 2, littleEndian);
        }
        return val;
    }
};

// Test: Wrong count (not 8 elements)
TEST_F(SonyMakerNoteTest_1607, WrongCount_ReturnsParenthesizedValue_1607) {
    // Only 4 bytes instead of 8
    auto val = makeUnsignedByteValue({1, 2, 3, 4});
    maker.printLensSpec(os, *val, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: Wrong type (not unsignedByte)
TEST_F(SonyMakerNoteTest_1607, WrongType_ReturnsParenthesizedValue_1607) {
    auto val = makeUnsignedShortValue({1, 2, 3, 4, 5, 6, 7, 8});
    maker.printLensSpec(os, *val, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: All zeros → "Unknown"
TEST_F(SonyMakerNoteTest_1607, AllZeros_ReturnsUnknown_1607) {
    auto val = makeUnsignedByteValue({0, 0, 0, 0, 0, 0, 0, 0});
    maker.printLensSpec(os, *val, nullptr);
    EXPECT_EQ(os.str(), "Unknown");
}

// Test: focalLenMin (index 2) is zero → "Unknown"
TEST_F(SonyMakerNoteTest_1607, FocalLenMinZero_ReturnsUnknown_1607) {
    auto val = makeUnsignedByteValue({1, 1, 0, 0x50, 0x00, 0x28, 0x00, 0});
    maker.printLensSpec(os, *val, nullptr);
    EXPECT_EQ(os.str(), "Unknown");
}

// Test: appertureMin (index 5) is zero → "Unknown"
TEST_F(SonyMakerNoteTest_1607, ApertureMinZero_ReturnsUnknown_1607) {
    auto val = makeUnsignedByteValue({0, 0, 0x18, 0x50, 0x00, 0, 0x56, 0});
    maker.printLensSpec(os, *val, nullptr);
    EXPECT_EQ(os.str(), "Unknown");
}

// Test: Normal lens spec - e.g., 18-55mm F3.5-5.6
// index: 0=flags?, 1=flags?, 2=focalLenMin(0x18), 3=focalLenMax1(0x05), 4=focalLenMax2(0x50), 5=appertureMin(0x35), 6=apertureMax(0x56), 7=flags?
TEST_F(SonyMakerNoteTest_1607, NormalLensSpec_18_55_F35_56_1607) {
    // focalLenMin=0x18 → "18", focalLenMax1=0x05, focalLenMax2=0x50 → "0550"
    // appertureMin=0x35 → "F3.5", apertureMax=0x56 → "-5.6"
    auto val = makeUnsignedByteValue({0, 0, 0x18, 0x05, 0x50, 0x35, 0x56, 0});
    maker.printLensSpec(os, *val, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("18") != std::string::npos);
    EXPECT_TRUE(result.find("mm") != std::string::npos);
    EXPECT_TRUE(result.find("F3.5") != std::string::npos);
    EXPECT_TRUE(result.find("5.6") != std::string::npos);
}

// Test: Single focal length (focalLenMax1=0, focalLenMax2=0) - prime lens
TEST_F(SonyMakerNoteTest_1607, PrimeLens_50mm_F14_1607) {
    // focalLenMin=0x50, focalLenMax1=0, focalLenMax2=0
    // appertureMin=0x14, apertureMax=0
    auto val = makeUnsignedByteValue({0, 0, 0x50, 0x00, 0x00, 0x14, 0x00, 0});
    maker.printLensSpec(os, *val, nullptr);
    std::string result = os.str();
    // Should be "50mm F1.4" (no range since max1=max2=0, no aperture range since apertureMax=0)
    EXPECT_EQ(result, "50mm F1.4");
}

// Test: focalLenMax1=0 but focalLenMax2 != 0
TEST_F(SonyMakerNoteTest_1607, FocalLenMax1Zero_Max2NonZero_1607) {
    // focalLenMin=0x18, focalLenMax1=0x00, focalLenMax2=0x55
    // appertureMin=0x35, apertureMax=0x00
    auto val = makeUnsignedByteValue({0, 0, 0x18, 0x00, 0x55, 0x35, 0x00, 0});
    maker.printLensSpec(os, *val, nullptr);
    std::string result = os.str();
    // Should have "18-55mm F3.5"
    EXPECT_TRUE(result.find("18-55mm") != std::string::npos);
    EXPECT_TRUE(result.find("F3.5") != std::string::npos);
}

// Test: Leading zero removal in focalLenMin
TEST_F(SonyMakerNoteTest_1607, FocalLenMinLeadingZero_1607) {
    // focalLenMin=0x08 → high nibble is 0, should just print "8"
    auto val = makeUnsignedByteValue({0, 0, 0x08, 0x00, 0x00, 0x28, 0x00, 0});
    maker.printLensSpec(os, *val, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result, "8mm F2.8");
}

// Test: Leading zero in focalLenMax1
TEST_F(SonyMakerNoteTest_1607, FocalLenMax1LeadingZero_1607) {
    // focalLenMax1=0x02 → high nibble=0, low nibble=2 → "2"
    // focalLenMax2=0x00 → "00"
    // So range part = "200"
    auto val = makeUnsignedByteValue({0, 0, 0x70, 0x02, 0x00, 0x28, 0x40, 0});
    maker.printLensSpec(os, *val, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("70-200mm") != std::string::npos);
    EXPECT_TRUE(result.find("F2.8-4.0") != std::string::npos);
}

// Test: focalLenMax1 has non-zero high nibble
TEST_F(SonyMakerNoteTest_1607, FocalLenMax1HighNibbleNonZero_1607) {
    // focalLenMax1=0x10 → prints "10", focalLenMax2=0x00 → "00" → total "1000"
    auto val = makeUnsignedByteValue({0, 0, 0x50, 0x10, 0x00, 0x56, 0x63, 0});
    maker.printLensSpec(os, *val, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("50-1000mm") != std::string::npos);
}

// Test: Empty value (count=0)
TEST_F(SonyMakerNoteTest_1607, EmptyValue_ReturnsParenthesized_1607) {
    auto val = Value::create(unsignedByte);
    maker.printLensSpec(os, *val, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: Exactly 8 elements but wrong type
TEST_F(SonyMakerNoteTest_1607, EightElementsWrongType_ReturnsParenthesized_1607) {
    // 8 unsigned short values
    auto val = makeUnsignedShortValue({0, 0, 0x18, 0x05, 0x50, 0x35, 0x56, 0});
    // count should be 8 but typeId is unsignedShort
    maker.printLensSpec(os, *val, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: apertureMax is zero → no aperture range printed
TEST_F(SonyMakerNoteTest_1607, ApertureMaxZero_NoApertureRange_1607) {
    auto val = makeUnsignedByteValue({0, 0, 0x50, 0x00, 0x00, 0x14, 0x00, 0});
    maker.printLensSpec(os, *val, nullptr);
    std::string result = os.str();
    // Should not contain a second aperture value
    EXPECT_EQ(result, "50mm F1.4");
    // Verify no dash after aperture
    auto fpos = result.find("F1.4");
    ASSERT_NE(fpos, std::string::npos);
    EXPECT_EQ(result.substr(fpos), "F1.4");
}

// Test: Both focalLenMax values non-zero (zoom lens with full range)
TEST_F(SonyMakerNoteTest_1607, ZoomLensFullRange_1607) {
    // 24-70mm F2.8
    // focalLenMin=0x24, focalLenMax1=0x00, focalLenMax2=0x70
    // appertureMin=0x28, apertureMax=0x00
    auto val = makeUnsignedByteValue({0, 0, 0x24, 0x00, 0x70, 0x28, 0x00, 0});
    maker.printLensSpec(os, *val, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result, "24-70mm F2.8");
}

// Test: focalLenMin with high nibble non-zero (e.g., 0x70 → "70")
TEST_F(SonyMakerNoteTest_1607, FocalLenMinHighNibbleNonZero_1607) {
    auto val = makeUnsignedByteValue({0, 0, 0x70, 0x02, 0x00, 0x28, 0x00, 0});
    maker.printLensSpec(os, *val, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("70-200mm") != std::string::npos);
}
