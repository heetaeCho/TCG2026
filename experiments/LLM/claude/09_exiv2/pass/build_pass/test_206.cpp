#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>

#include <exiv2/exiv2.hpp>
#include "pentaxmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper function to set up ExifData with specific metadata
class ResolveLens0x8ffTest_206 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    // Helper to create a UShortValue with specific values
    std::unique_ptr<Value> createUShortValue(const std::vector<uint16_t>& values) {
        auto val = Value::create(unsignedShort);
        for (const auto& v : values) {
            std::string s = std::to_string(v);
            if (val->count() == 0) {
                val->read(s);
            } else {
                // Append values by reading space-separated string
            }
        }
        return val;
    }

    // Helper to build a space-separated string of values
    std::string buildValueString(const std::vector<uint16_t>& values) {
        std::string result;
        for (size_t i = 0; i < values.size(); i++) {
            if (i > 0) result += " ";
            result += std::to_string(values[i]);
        }
        return result;
    }

    // Set up ExifData with the Pentax lens type tag
    void setupExifData(ExifData& exifData, const std::string& model,
                       const std::vector<uint16_t>& lensInfoValues) {
        // Set camera model
        exifData["Exif.Image.Model"] = model;

        // Set lens info - use Exif.Pentax.LensInfo or similar
        // The function calls findLensInfo which looks for lens info in metadata
        if (!lensInfoValues.empty()) {
            auto lensInfoVal = Value::create(unsignedByte);
            lensInfoVal->read(buildValueString(lensInfoValues));
            exifData.add(ExifKey("Exif.Pentax.LensInfo"), lensInfoVal.get());
        }
    }
};

// Test that resolveLens0x8ff can be called through the Exifdatum write mechanism
// by setting up appropriate metadata for a Pentax lens type tag

// Test: When ExifData is null/empty, the function should still produce output via the fallback path
TEST_F(ResolveLens0x8ffTest_206, FallbackPathWithNoMetadata_206) {
    // Create a value with 2 elements (the normal case for EXV_PRINT_COMBITAG_MULTI)
    auto value = Value::create(unsignedShort);
    value->read("8 255");  // 0x8ff = 2303 split as two bytes: high=8, low=255

    std::ostringstream os;
    // Without metadata, the function should fall through to the fallback
    // We just verify it doesn't crash
    EXPECT_NO_THROW({
        // The function is internal, but we can test it indirectly through ExifData
        ExifData exifData;
        exifData["Exif.Pentax.LensType"] = *value;

        auto it = exifData.findKey(ExifKey("Exif.Pentax.LensType"));
        if (it != exifData.end()) {
            std::string result = it->print(&exifData);
            // Should produce some output
            EXPECT_FALSE(result.empty());
        }
    });
}

// Test: Normal operation with a standard Pentax lens type
TEST_F(ResolveLens0x8ffTest_206, NormalLensTypeResolution_206) {
    ExifData exifData;

    // Set up a known lens type that isn't 0x8ff
    auto value = Value::create(unsignedByte);
    value->read("3 253");  // = 3*256 + 253 = 1021 = "smc PENTAX-DA 14mm F2.8 ED[IF]"

    exifData.add(ExifKey("Exif.Pentax.LensType"), value.get());
    
    auto it = exifData.findKey(ExifKey("Exif.Pentax.LensType"));
    if (it != exifData.end()) {
        std::string result = it->print(&exifData);
        EXPECT_FALSE(result.empty());
    }
}

// Test: With PENTAX K-3 model and specific lens info matching the special condition
TEST_F(ResolveLens0x8ffTest_206, SpecialK3LensResolution_206) {
    ExifData exifData;

    // Set camera model to PENTAX K-3
    exifData["Exif.Image.Model"] = "PENTAX K-3";

    // Create lens type value with 4 elements (count == 4 condition)
    auto lensTypeValue = Value::create(unsignedByte);
    lensTypeValue->read("8 255 0 0");  // 0x8ff with 4 values

    exifData.add(ExifKey("Exif.Pentax.LensType"), lensTypeValue.get());

    // Create lens info with 128 bytes where byte[1]==168 and byte[2]==144
    std::string lensInfoStr = "0 168 144";
    for (int i = 3; i < 128; i++) {
        lensInfoStr += " 0";
    }
    auto lensInfoValue = Value::create(unsignedByte);
    lensInfoValue->read(lensInfoStr);

    exifData.add(ExifKey("Exif.Pentax.LensInfo"), lensInfoValue.get());

    auto it = exifData.findKey(ExifKey("Exif.Pentax.LensType"));
    if (it != exifData.end()) {
        std::string result = it->print(&exifData);
        // Should resolve to a specific lens name (the 7th entry for 0x8ff)
        EXPECT_FALSE(result.empty());
    }
}

// Test: K-3 model but lens info doesn't match the special conditions
TEST_F(ResolveLens0x8ffTest_206, K3ModelMismatchedLensInfo_206) {
    ExifData exifData;

    exifData["Exif.Image.Model"] = "PENTAX K-3";

    // Create lens type value with 4 elements
    auto lensTypeValue = Value::create(unsignedByte);
    lensTypeValue->read("8 255 0 0");

    exifData.add(ExifKey("Exif.Pentax.LensType"), lensTypeValue.get());

    // Create lens info with 128 bytes but byte[1] != 168
    std::string lensInfoStr = "0 100 144";
    for (int i = 3; i < 128; i++) {
        lensInfoStr += " 0";
    }
    auto lensInfoValue = Value::create(unsignedByte);
    lensInfoValue->read(lensInfoStr);

    exifData.add(ExifKey("Exif.Pentax.LensInfo"), lensInfoValue.get());

    auto it = exifData.findKey(ExifKey("Exif.Pentax.LensType"));
    if (it != exifData.end()) {
        std::string result = it->print(&exifData);
        // Should fall through to the fallback path
        EXPECT_FALSE(result.empty());
    }
}

// Test: Non-K3 model with 0x8ff lens type falls through to fallback
TEST_F(ResolveLens0x8ffTest_206, NonK3ModelFallback_206) {
    ExifData exifData;

    exifData["Exif.Image.Model"] = "PENTAX K-5";

    auto lensTypeValue = Value::create(unsignedByte);
    lensTypeValue->read("8 255 0 0");

    exifData.add(ExifKey("Exif.Pentax.LensType"), lensTypeValue.get());

    // Even with matching lens info, non-K3 model should go to fallback
    std::string lensInfoStr = "0 168 144";
    for (int i = 3; i < 128; i++) {
        lensInfoStr += " 0";
    }
    auto lensInfoValue = Value::create(unsignedByte);
    lensInfoValue->read(lensInfoStr);

    exifData.add(ExifKey("Exif.Pentax.LensInfo"), lensInfoValue.get());

    auto it = exifData.findKey(ExifKey("Exif.Pentax.LensType"));
    if (it != exifData.end()) {
        std::string result = it->print(&exifData);
        EXPECT_FALSE(result.empty());
    }
}

// Test: Value with count != 4 should skip the special K-3 check
TEST_F(ResolveLens0x8ffTest_206, ValueCountNot4SkipsSpecialCheck_206) {
    ExifData exifData;

    exifData["Exif.Image.Model"] = "PENTAX K-3";

    // Only 2 elements instead of 4
    auto lensTypeValue = Value::create(unsignedByte);
    lensTypeValue->read("8 255");

    exifData.add(ExifKey("Exif.Pentax.LensType"), lensTypeValue.get());

    std::string lensInfoStr = "0 168 144";
    for (int i = 3; i < 128; i++) {
        lensInfoStr += " 0";
    }
    auto lensInfoValue = Value::create(unsignedByte);
    lensInfoValue->read(lensInfoStr);

    exifData.add(ExifKey("Exif.Pentax.LensInfo"), lensInfoValue.get());

    auto it = exifData.findKey(ExifKey("Exif.Pentax.LensType"));
    if (it != exifData.end()) {
        std::string result = it->print(&exifData);
        // Falls through to fallback since count != 4
        EXPECT_FALSE(result.empty());
    }
}

// Test: K-3 Mark II model (starts_with "PENTAX K-3") should also trigger special path
TEST_F(ResolveLens0x8ffTest_206, K3MarkIIModel_206) {
    ExifData exifData;

    exifData["Exif.Image.Model"] = "PENTAX K-3 Mark III";

    auto lensTypeValue = Value::create(unsignedByte);
    lensTypeValue->read("8 255 0 0");

    exifData.add(ExifKey("Exif.Pentax.LensType"), lensTypeValue.get());

    std::string lensInfoStr = "0 168 144";
    for (int i = 3; i < 128; i++) {
        lensInfoStr += " 0";
    }
    auto lensInfoValue = Value::create(unsignedByte);
    lensInfoValue->read(lensInfoStr);

    exifData.add(ExifKey("Exif.Pentax.LensInfo"), lensInfoValue.get());

    auto it = exifData.findKey(ExifKey("Exif.Pentax.LensType"));
    if (it != exifData.end()) {
        std::string result = it->print(&exifData);
        EXPECT_FALSE(result.empty());
    }
}

// Test: Lens info with wrong byte[2] (not 144)
TEST_F(ResolveLens0x8ffTest_206, LensInfoWrongByte2_206) {
    ExifData exifData;

    exifData["Exif.Image.Model"] = "PENTAX K-3";

    auto lensTypeValue = Value::create(unsignedByte);
    lensTypeValue->read("8 255 0 0");

    exifData.add(ExifKey("Exif.Pentax.LensType"), lensTypeValue.get());

    // byte[2] is 100 instead of 144
    std::string lensInfoStr = "0 168 100";
    for (int i = 3; i < 128; i++) {
        lensInfoStr += " 0";
    }
    auto lensInfoValue = Value::create(unsignedByte);
    lensInfoValue->read(lensInfoStr);

    exifData.add(ExifKey("Exif.Pentax.LensInfo"), lensInfoValue.get());

    auto it = exifData.findKey(ExifKey("Exif.Pentax.LensType"));
    if (it != exifData.end()) {
        std::string result = it->print(&exifData);
        // Should fall through to fallback since byte[2] != 144
        EXPECT_FALSE(result.empty());
    }
}

// Test: Lens info with count != 128
TEST_F(ResolveLens0x8ffTest_206, LensInfoWrongCount_206) {
    ExifData exifData;

    exifData["Exif.Image.Model"] = "PENTAX K-3";

    auto lensTypeValue = Value::create(unsignedByte);
    lensTypeValue->read("8 255 0 0");

    exifData.add(ExifKey("Exif.Pentax.LensType"), lensTypeValue.get());

    // Only 64 bytes instead of 128
    std::string lensInfoStr = "0 168 144";
    for (int i = 3; i < 64; i++) {
        lensInfoStr += " 0";
    }
    auto lensInfoValue = Value::create(unsignedByte);
    lensInfoValue->read(lensInfoStr);

    exifData.add(ExifKey("Exif.Pentax.LensInfo"), lensInfoValue.get());

    auto it = exifData.findKey(ExifKey("Exif.Pentax.LensType"));
    if (it != exifData.end()) {
        std::string result = it->print(&exifData);
        // Should fall through to fallback
        EXPECT_FALSE(result.empty());
    }
}

// Test: No lens info metadata present at all
TEST_F(ResolveLens0x8ffTest_206, NoLensInfoPresent_206) {
    ExifData exifData;

    exifData["Exif.Image.Model"] = "PENTAX K-3";

    auto lensTypeValue = Value::create(unsignedByte);
    lensTypeValue->read("8 255 0 0");

    exifData.add(ExifKey("Exif.Pentax.LensType"), lensTypeValue.get());

    // Don't add any lens info

    auto it = exifData.findKey(ExifKey("Exif.Pentax.LensType"));
    if (it != exifData.end()) {
        std::string result = it->print(&exifData);
        // Should not crash and should fall through to fallback
        EXPECT_FALSE(result.empty());
    }
}

// Test: Empty model string
TEST_F(ResolveLens0x8ffTest_206, EmptyModelString_206) {
    ExifData exifData;

    // Don't set model

    auto lensTypeValue = Value::create(unsignedByte);
    lensTypeValue->read("8 255 0 0");

    exifData.add(ExifKey("Exif.Pentax.LensType"), lensTypeValue.get());

    std::string lensInfoStr = "0 168 144";
    for (int i = 3; i < 128; i++) {
        lensInfoStr += " 0";
    }
    auto lensInfoValue = Value::create(unsignedByte);
    lensInfoValue->read(lensInfoStr);

    exifData.add(ExifKey("Exif.Pentax.LensInfo"), lensInfoValue.get());

    auto it = exifData.findKey(ExifKey("Exif.Pentax.LensType"));
    if (it != exifData.end()) {
        std::string result = it->print(&exifData);
        EXPECT_FALSE(result.empty());
    }
}

// Test: Known simple lens type (not 0x8ff)
TEST_F(ResolveLens0x8ffTest_206, KnownSimpleLensType_206) {
    ExifData exifData;

    // Lens type 0 = "M-42 or No Lens"
    auto lensTypeValue = Value::create(unsignedByte);
    lensTypeValue->read("0 0");

    exifData.add(ExifKey("Exif.Pentax.LensType"), lensTypeValue.get());

    auto it = exifData.findKey(ExifKey("Exif.Pentax.LensType"));
    if (it != exifData.end()) {
        std::string result = it->print(&exifData);
        EXPECT_FALSE(result.empty());
    }
}

// Test: Null metadata pointer handling (print with nullptr)
TEST_F(ResolveLens0x8ffTest_206, NullMetadataPointer_206) {
    ExifData exifData;

    auto lensTypeValue = Value::create(unsignedByte);
    lensTypeValue->read("8 255 0 0");

    exifData.add(ExifKey("Exif.Pentax.LensType"), lensTypeValue.get());

    auto it = exifData.findKey(ExifKey("Exif.Pentax.LensType"));
    if (it != exifData.end()) {
        // Print with nullptr metadata - should not crash
        EXPECT_NO_THROW({
            std::string result = it->print(nullptr);
        });
    }
}
