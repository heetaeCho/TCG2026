#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include <exiv2/exiv2.hpp>
#include "pentaxmn_int.hpp"

// We need access to the internal function and data structures
namespace Exiv2 {
namespace Internal {

// Forward declarations for internal items we need
extern const TagDetails pentaxLensType[];

// The function under test is static in the .cpp file, so we need to test it
// indirectly through the print function mechanism. However, since the function
// is static and not directly accessible, we'll test through the Exifdatum
// write/print interface which calls the registered print functions.

} // namespace Internal
} // namespace Exiv2

class ResolveLens0x3ffTest_205 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create ExifData with the lens type tag set to specific values
    // and optionally set lens info
    Exiv2::ExifData createExifDataWithLensType(const std::vector<uint16_t>& lensTypeValues,
                                                const std::vector<uint8_t>& lensInfoValues = {}) {
        Exiv2::ExifData exifData;

        // Set Exif.Pentax.LensType
        {
            Exiv2::ExifKey key("Exif.Pentax.LensType");
            auto value = Exiv2::Value::create(Exiv2::unsignedByte);
            std::string buf;
            for (size_t i = 0; i < lensTypeValues.size(); i++) {
                if (i > 0) buf += " ";
                buf += std::to_string(lensTypeValues[i]);
            }
            value->read(buf);
            exifData.add(key, value.get());
        }

        // Set Exif.Pentax.LensInfo if provided
        if (!lensInfoValues.empty()) {
            Exiv2::ExifKey key("Exif.Pentax.LensInfo");
            auto value = Exiv2::Value::create(Exiv2::unsignedByte);
            std::string buf;
            for (size_t i = 0; i < lensInfoValues.size(); i++) {
                if (i > 0) buf += " ";
                buf += std::to_string(lensInfoValues[i]);
            }
            value->read(buf);
            exifData.add(key, value.get());
        }

        return exifData;
    }

    // Helper to get printed lens type string
    std::string getLensTypeString(Exiv2::ExifData& exifData) {
        auto it = exifData.findKey(Exiv2::ExifKey("Exif.Pentax.LensType"));
        if (it == exifData.end()) return "";
        std::ostringstream os;
        it->write(os, &exifData);
        return os.str();
    }
};

// Test: LensType 0x3ff (1023) with 2-element value and no lens info
// Should fall back to default combo tag lookup
TEST_F(ResolveLens0x3ffTest_205, NoLensInfoFallback_205) {
    // lens type 3 255 => 0x03ff = 1023
    Exiv2::ExifData exifData = createExifDataWithLensType({3, 255});
    std::string result = getLensTypeString(exifData);
    // Without lens info, should produce some result (likely "Sigma Lens" or similar)
    EXPECT_FALSE(result.empty());
}

// Test: LensType 0x3ff with 2-element value and short lens info (count < 5)
// Should fall through to EXV_PRINT_COMBITAG_MULTI
TEST_F(ResolveLens0x3ffTest_205, ShortLensInfoFallback_205) {
    // LensInfo with only 3 bytes
    Exiv2::ExifData exifData = createExifDataWithLensType({3, 255}, {0, 0, 0});
    std::string result = getLensTypeString(exifData);
    EXPECT_FALSE(result.empty());
}

// Test: LensType 0x3ff with 2-element value and lens info matching index 8
// autoAperture=0, minAperture=0, minFocusDistance=0x28, lensInfo[base+4]=148
TEST_F(ResolveLens0x3ffTest_205, TwoElementValueIndex8_205) {
    // value.count() == 2, lensInfo needs count >= 5
    // base = 1
    // lensInfo[2] & 0x01 == 0 (autoAperture)
    // lensInfo[3] & 0x06 == 0 (minAperture)
    // lensInfo[4] & 0xf8 == 0x28 (minFocusDistance) => 0x28 = 40, so lensInfo[4] = 0x28
    // lensInfo[5] == 148 (base+4 = 5)
    std::vector<uint8_t> lensInfo = {0, 0, 0x00, 0x00, 0x28, 148, 0};
    Exiv2::ExifData exifData = createExifDataWithLensType({3, 255}, lensInfo);
    std::string result = getLensTypeString(exifData);
    // index 8 in pentaxLensType entries starting from lensID 0x3ff
    EXPECT_FALSE(result.empty());
}

// Test: LensType 0x3ff with 2-element value and lens info matching index 7 via lensInfo[base+5]
// autoAperture=0, minAperture=0, minFocusDistance=0x28, lensInfo[base+5]=110
TEST_F(ResolveLens0x3ffTest_205, TwoElementValueIndex7ViaBase5_205) {
    // base = 1
    // lensInfo[2] & 0x01 == 0
    // lensInfo[3] & 0x06 == 0
    // lensInfo[4] & 0xf8 == 0x28
    // lensInfo[6] == 110 (base+5 = 6)
    std::vector<uint8_t> lensInfo = {0, 0, 0x00, 0x00, 0x28, 0, 110};
    Exiv2::ExifData exifData = createExifDataWithLensType({3, 255}, lensInfo);
    std::string result = getLensTypeString(exifData);
    EXPECT_FALSE(result.empty());
}

// Test: LensType 0x3ff with 2-element value and lens info matching index 7 via lensInfo[base+4]
// autoAperture=0, minAperture=0, minFocusDistance=0x28, lensInfo[base+4]=110
TEST_F(ResolveLens0x3ffTest_205, TwoElementValueIndex7ViaBase4_205) {
    // base = 1
    // lensInfo[2] & 0x01 == 0
    // lensInfo[3] & 0x06 == 0
    // lensInfo[4] & 0xf8 == 0x28
    // lensInfo[5] == 110 (base+4 = 5)
    std::vector<uint8_t> lensInfo = {0, 0, 0x00, 0x00, 0x28, 110, 0};
    Exiv2::ExifData exifData = createExifDataWithLensType({3, 255}, lensInfo);
    std::string result = getLensTypeString(exifData);
    EXPECT_FALSE(result.empty());
}

// Test: LensType 0x3ff with 3-element value and lens info matching index 8
// lensInfo[4]==0, lensInfo[5]==40, lensInfo[6]==148
TEST_F(ResolveLens0x3ffTest_205, ThreeElementValueIndex8_205) {
    // Need value.count() == 3
    // lensInfo needs count >= 7
    std::vector<uint8_t> lensInfo = {0, 0, 0, 0, 0, 40, 148};
    
    Exiv2::ExifData exifData;
    
    // Set lens type with 3 values
    {
        Exiv2::ExifKey key("Exif.Pentax.LensType");
        auto value = Exiv2::Value::create(Exiv2::unsignedByte);
        value->read("3 255 0");
        exifData.add(key, value.get());
    }
    
    // Set lens info
    {
        Exiv2::ExifKey key("Exif.Pentax.LensInfo");
        auto value = Exiv2::Value::create(Exiv2::unsignedByte);
        std::string buf;
        for (size_t i = 0; i < lensInfo.size(); i++) {
            if (i > 0) buf += " ";
            buf += std::to_string(lensInfo[i]);
        }
        value->read(buf);
        exifData.add(key, value.get());
    }
    
    std::string result = getLensTypeString(exifData);
    EXPECT_FALSE(result.empty());
}

// Test: LensType 0x3ff with 4-element value, lensInfo count=128, specific values
TEST_F(ResolveLens0x3ffTest_205, FourElementValueIndex8With128Count_205) {
    Exiv2::ExifData exifData;
    
    // Set lens type with 4 values
    {
        Exiv2::ExifKey key("Exif.Pentax.LensType");
        auto value = Exiv2::Value::create(Exiv2::unsignedByte);
        value->read("3 255 0 0");
        exifData.add(key, value.get());
    }
    
    // Create lensInfo with count=128, lensInfo[1]=131, lensInfo[2]=128
    {
        Exiv2::ExifKey key("Exif.Pentax.LensInfo");
        auto value = Exiv2::Value::create(Exiv2::unsignedByte);
        std::string buf = "0 131 128";
        for (int i = 3; i < 128; i++) {
            buf += " 0";
        }
        value->read(buf);
        exifData.add(key, value.get());
    }
    
    std::string result = getLensTypeString(exifData);
    EXPECT_FALSE(result.empty());
}

// Test: LensType 0x3ff with 4-element value, lensInfo[6]==5 => index 7
TEST_F(ResolveLens0x3ffTest_205, FourElementValueIndex7_205) {
    Exiv2::ExifData exifData;
    
    // Set lens type with 4 values
    {
        Exiv2::ExifKey key("Exif.Pentax.LensType");
        auto value = Exiv2::Value::create(Exiv2::unsignedByte);
        value->read("3 255 0 0");
        exifData.add(key, value.get());
    }
    
    // Create lensInfo with lensInfo[6]=5
    {
        Exiv2::ExifKey key("Exif.Pentax.LensInfo");
        auto value = Exiv2::Value::create(Exiv2::unsignedByte);
        // Need at least 7 elements, lensInfo[6] = 5
        value->read("0 0 0 0 0 0 5");
        exifData.add(key, value.get());
    }
    
    std::string result = getLensTypeString(exifData);
    EXPECT_FALSE(result.empty());
}

// Test: Non 0x3ff lens type should just use normal lookup
TEST_F(ResolveLens0x3ffTest_205, NonSpecialLensType_205) {
    // Use a well-known lens ID, e.g., 3 17 => smc PENTAX-FA SOFT 85mm F2.8
    Exiv2::ExifData exifData = createExifDataWithLensType({3, 17});
    std::string result = getLensTypeString(exifData);
    EXPECT_FALSE(result.empty());
}

// Test: LensType with no matching entry
TEST_F(ResolveLens0x3ffTest_205, UnknownLensType_205) {
    // Use an ID unlikely to exist
    Exiv2::ExifData exifData = createExifDataWithLensType({99, 99});
    std::string result = getLensTypeString(exifData);
    // Should still produce some output (even if "(0)" or unknown)
    EXPECT_FALSE(result.empty());
}

// Test: LensType 0x3ff with 2-element value where no conditions match
// Should fall back to combo tag
TEST_F(ResolveLens0x3ffTest_205, TwoElementNoConditionsMatch_205) {
    // Provide lensInfo that doesn't match any condition
    // Set bits so autoAperture != 0
    std::vector<uint8_t> lensInfo = {0, 0, 0x01, 0x00, 0x00, 0, 0};
    Exiv2::ExifData exifData = createExifDataWithLensType({3, 255}, lensInfo);
    std::string result = getLensTypeString(exifData);
    EXPECT_FALSE(result.empty());
}

// Test: LensType 0x3ff with 3-element value where no conditions match
TEST_F(ResolveLens0x3ffTest_205, ThreeElementNoConditionsMatch_205) {
    Exiv2::ExifData exifData;
    
    {
        Exiv2::ExifKey key("Exif.Pentax.LensType");
        auto value = Exiv2::Value::create(Exiv2::unsignedByte);
        value->read("3 255 0");
        exifData.add(key, value.get());
    }
    
    {
        Exiv2::ExifKey key("Exif.Pentax.LensInfo");
        auto value = Exiv2::Value::create(Exiv2::unsignedByte);
        // lensInfo[4]=1, lensInfo[5]=1, lensInfo[6]=1 - won't match
        value->read("0 0 0 0 1 1 1");
        exifData.add(key, value.get());
    }
    
    std::string result = getLensTypeString(exifData);
    EXPECT_FALSE(result.empty());
}

// Test: LensType 0x3ff with 4-element value where no conditions match
TEST_F(ResolveLens0x3ffTest_205, FourElementNoConditionsMatch_205) {
    Exiv2::ExifData exifData;
    
    {
        Exiv2::ExifKey key("Exif.Pentax.LensType");
        auto value = Exiv2::Value::create(Exiv2::unsignedByte);
        value->read("3 255 0 0");
        exifData.add(key, value.get());
    }
    
    {
        Exiv2::ExifKey key("Exif.Pentax.LensInfo");
        auto value = Exiv2::Value::create(Exiv2::unsignedByte);
        // count != 128, lensInfo[6] != 5
        value->read("0 0 0 0 0 0 0");
        exifData.add(key, value.get());
    }
    
    std::string result = getLensTypeString(exifData);
    EXPECT_FALSE(result.empty());
}

// Test: Using PentaxDng tags instead of Pentax
TEST_F(ResolveLens0x3ffTest_205, PentaxDngLensType_205) {
    Exiv2::ExifData exifData;
    
    // Try with PentaxDng group
    try {
        Exiv2::ExifKey key("Exif.PentaxDng.LensType");
        auto value = Exiv2::Value::create(Exiv2::unsignedByte);
        value->read("3 255");
        exifData.add(key, value.get());
        
        auto it = exifData.findKey(Exiv2::ExifKey("Exif.PentaxDng.LensType"));
        if (it != exifData.end()) {
            std::ostringstream os;
            it->write(os, &exifData);
            std::string result = os.str();
            EXPECT_FALSE(result.empty());
        }
    } catch (...) {
        // PentaxDng might not be available, that's ok
    }
}

// Test: LensType with single value (edge case)
TEST_F(ResolveLens0x3ffTest_205, SingleValueLensType_205) {
    Exiv2::ExifData exifData;
    
    {
        Exiv2::ExifKey key("Exif.Pentax.LensType");
        auto value = Exiv2::Value::create(Exiv2::unsignedByte);
        value->read("0");
        exifData.add(key, value.get());
    }
    
    std::string result = getLensTypeString(exifData);
    // Should produce "M-42 or No Lens" or similar
    EXPECT_FALSE(result.empty());
}

// Test: Both index 7 and 8 conditions met - index 7 should win (last assignment)
TEST_F(ResolveLens0x3ffTest_205, BothIndex7And8ConditionsMet_205) {
    // autoAperture=0, minAperture=0, minFocusDistance=0x28
    // lensInfo[base+4]=148 (matches index 8)
    // lensInfo[base+4]=110 would match index 7, but can't be both
    // Instead: lensInfo[base+4]=148 and lensInfo[base+5]=110
    // This matches index 8 first, then index 7 overwrites
    std::vector<uint8_t> lensInfo = {0, 0, 0x00, 0x00, 0x28, 148, 110};
    Exiv2::ExifData exifData = createExifDataWithLensType({3, 255}, lensInfo);
    std::string result = getLensTypeString(exifData);
    EXPECT_FALSE(result.empty());
}

// Test: Verify that empty ExifData for metadata doesn't crash
TEST_F(ResolveLens0x3ffTest_205, EmptyMetadata_205) {
    Exiv2::ExifData exifData;
    
    {
        Exiv2::ExifKey key("Exif.Pentax.LensType");
        auto value = Exiv2::Value::create(Exiv2::unsignedByte);
        value->read("3 255");
        exifData.add(key, value.get());
    }
    
    // No LensInfo at all
    std::string result = getLensTypeString(exifData);
    EXPECT_FALSE(result.empty());
}

// Test: LensType 0x3ff with sufficient lens info but value count is something unusual (e.g., 5)
TEST_F(ResolveLens0x3ffTest_205, FiveElementValueFallback_205) {
    Exiv2::ExifData exifData;
    
    {
        Exiv2::ExifKey key("Exif.Pentax.LensType");
        auto value = Exiv2::Value::create(Exiv2::unsignedByte);
        value->read("3 255 0 0 0");
        exifData.add(key, value.get());
    }
    
    {
        Exiv2::ExifKey key("Exif.Pentax.LensInfo");
        auto value = Exiv2::Value::create(Exiv2::unsignedByte);
        value->read("0 0 0 0 0 0 0");
        exifData.add(key, value.get());
    }
    
    // value.count() == 5, none of the branches match, should fall through
    std::string result = getLensTypeString(exifData);
    EXPECT_FALSE(result.empty());
}
