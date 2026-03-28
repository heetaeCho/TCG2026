#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Declaration of the function under test
namespace Exiv2 {
namespace Internal {
std::ostream& printCsLensFFFF(std::ostream& os, const Value& value, const ExifData* metadata);
}
}

class PrintCsLensFFFFTest_947 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to set a string value on an ExifData key
    void setExifString(Exiv2::ExifData& exifData, const std::string& keyStr, const std::string& val) {
        Exiv2::ExifKey key(keyStr);
        auto value = Exiv2::Value::create(Exiv2::asciiString);
        value->read(val);
        exifData.add(key, value.get());
    }

    // Helper to set a short value
    void setExifShort(Exiv2::ExifData& exifData, const std::string& keyStr, uint16_t val) {
        Exiv2::ExifKey key(keyStr);
        auto value = Exiv2::Value::create(Exiv2::unsignedShort);
        value->read(std::to_string(val));
        exifData.add(key, value.get());
    }

    // Helper to set multiple short values (e.g., for Lens "24 24 1")
    void setExifShortArray(Exiv2::ExifData& exifData, const std::string& keyStr, const std::string& vals) {
        Exiv2::ExifKey key(keyStr);
        auto value = Exiv2::Value::create(Exiv2::unsignedShort);
        value->read(vals);
        exifData.add(key, value.get());
    }
};

// Test: Canon EOS 30D with matching lens and aperture should return specific lens name
TEST_F(PrintCsLensFFFFTest_947, CanonEOS30D_MatchingLensAndAperture_947) {
    Exiv2::ExifData exifData;

    setExifString(exifData, "Exif.Image.Model", "Canon EOS 30D");
    setExifShortArray(exifData, "Exif.CanonCs.Lens", "24 24 1");
    setExifShort(exifData, "Exif.CanonCs.MaxAperture", 95);

    // The value parameter for the lens type - use 65535 (0xFFFF) which is "n/a"
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("65535");

    std::ostringstream os;
    Exiv2::Internal::printCsLensFFFF(os, *value, &exifData);

    EXPECT_EQ(os.str(), "Canon EF-S 24mm f/2.8 STM");
}

// Test: Different model should NOT trigger special case, should fall through to tag lookup
TEST_F(PrintCsLensFFFFTest_947, DifferentModel_FallsThrough_947) {
    Exiv2::ExifData exifData;

    setExifString(exifData, "Exif.Image.Model", "Canon EOS 5D");
    setExifShortArray(exifData, "Exif.CanonCs.Lens", "24 24 1");
    setExifShort(exifData, "Exif.CanonCs.MaxAperture", 95);

    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("65535");

    std::ostringstream os;
    Exiv2::Internal::printCsLensFFFF(os, *value, &exifData);

    // Should NOT be the special lens name
    EXPECT_NE(os.str(), "Canon EF-S 24mm f/2.8 STM");
}

// Test: Correct model but different lens values should fall through
TEST_F(PrintCsLensFFFFTest_947, CorrectModelDifferentLens_FallsThrough_947) {
    Exiv2::ExifData exifData;

    setExifString(exifData, "Exif.Image.Model", "Canon EOS 30D");
    setExifShortArray(exifData, "Exif.CanonCs.Lens", "50 50 1");
    setExifShort(exifData, "Exif.CanonCs.MaxAperture", 95);

    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("65535");

    std::ostringstream os;
    Exiv2::Internal::printCsLensFFFF(os, *value, &exifData);

    EXPECT_NE(os.str(), "Canon EF-S 24mm f/2.8 STM");
}

// Test: Correct model and lens but different aperture should fall through
TEST_F(PrintCsLensFFFFTest_947, CorrectModelAndLensDifferentAperture_FallsThrough_947) {
    Exiv2::ExifData exifData;

    setExifString(exifData, "Exif.Image.Model", "Canon EOS 30D");
    setExifShortArray(exifData, "Exif.CanonCs.Lens", "24 24 1");
    setExifShort(exifData, "Exif.CanonCs.MaxAperture", 100);

    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("65535");

    std::ostringstream os;
    Exiv2::Internal::printCsLensFFFF(os, *value, &exifData);

    EXPECT_NE(os.str(), "Canon EF-S 24mm f/2.8 STM");
}

// Test: Missing Model key should fall through
TEST_F(PrintCsLensFFFFTest_947, MissingModelKey_FallsThrough_947) {
    Exiv2::ExifData exifData;

    // No Model key set
    setExifShortArray(exifData, "Exif.CanonCs.Lens", "24 24 1");
    setExifShort(exifData, "Exif.CanonCs.MaxAperture", 95);

    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("65535");

    std::ostringstream os;
    Exiv2::Internal::printCsLensFFFF(os, *value, &exifData);

    EXPECT_NE(os.str(), "Canon EF-S 24mm f/2.8 STM");
}

// Test: Missing Lens key should fall through
TEST_F(PrintCsLensFFFFTest_947, MissingLensKey_FallsThrough_947) {
    Exiv2::ExifData exifData;

    setExifString(exifData, "Exif.Image.Model", "Canon EOS 30D");
    // No Lens key set
    setExifShort(exifData, "Exif.CanonCs.MaxAperture", 95);

    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("65535");

    std::ostringstream os;
    Exiv2::Internal::printCsLensFFFF(os, *value, &exifData);

    EXPECT_NE(os.str(), "Canon EF-S 24mm f/2.8 STM");
}

// Test: Missing MaxAperture key should fall through
TEST_F(PrintCsLensFFFFTest_947, MissingApertureKey_FallsThrough_947) {
    Exiv2::ExifData exifData;

    setExifString(exifData, "Exif.Image.Model", "Canon EOS 30D");
    setExifShortArray(exifData, "Exif.CanonCs.Lens", "24 24 1");
    // No MaxAperture key set

    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("65535");

    std::ostringstream os;
    Exiv2::Internal::printCsLensFFFF(os, *value, &exifData);

    EXPECT_NE(os.str(), "Canon EF-S 24mm f/2.8 STM");
}

// Test: Empty metadata should fall through to tag lookup
TEST_F(PrintCsLensFFFFTest_947, EmptyMetadata_FallsThrough_947) {
    Exiv2::ExifData exifData;

    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("65535");

    std::ostringstream os;
    Exiv2::Internal::printCsLensFFFF(os, *value, &exifData);

    // Should produce some output (the tag lookup result for 65535 which is "n/a")
    EXPECT_FALSE(os.str().empty());
}

// Test: Known lens type value should return correct lens via tag lookup
TEST_F(PrintCsLensFFFFTest_947, KnownLensTypeValue_ReturnsTagLookup_947) {
    Exiv2::ExifData exifData;

    // Use lens type 1 which should map to "Canon EF 50mm f/1.8"
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("1");

    std::ostringstream os;
    Exiv2::Internal::printCsLensFFFF(os, *value, &exifData);

    EXPECT_EQ(os.str(), "Canon EF 50mm f/1.8");
}

// Test: Value 65535 with no special match should return "n/a" from tag lookup
TEST_F(PrintCsLensFFFFTest_947, Value65535NoMatch_ReturnsNA_947) {
    Exiv2::ExifData exifData;

    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("65535");

    std::ostringstream os;
    Exiv2::Internal::printCsLensFFFF(os, *value, &exifData);

    EXPECT_EQ(os.str(), "n/a");
}

// Test: Known lens type 29 should return "Canon EF 50mm f/1.8 II"
TEST_F(PrintCsLensFFFFTest_947, LensType29_CanonEF50_947) {
    Exiv2::ExifData exifData;

    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("29");

    std::ostringstream os;
    Exiv2::Internal::printCsLensFFFF(os, *value, &exifData);

    EXPECT_EQ(os.str(), "Canon EF 50mm f/1.8 II");
}

// Test: Output stream is correctly chained (return value is same stream)
TEST_F(PrintCsLensFFFFTest_947, OutputStreamReturnsSameStream_947) {
    Exiv2::ExifData exifData;

    setExifString(exifData, "Exif.Image.Model", "Canon EOS 30D");
    setExifShortArray(exifData, "Exif.CanonCs.Lens", "24 24 1");
    setExifShort(exifData, "Exif.CanonCs.MaxAperture", 95);

    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("65535");

    std::ostringstream os;
    std::ostream& result = Exiv2::Internal::printCsLensFFFF(os, *value, &exifData);

    EXPECT_EQ(&result, &os);
}

// Test: Lens type 2 should return one of the known mappings
TEST_F(PrintCsLensFFFFTest_947, LensType2_ReturnsCanonEF28_947) {
    Exiv2::ExifData exifData;

    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("2");

    std::ostringstream os;
    Exiv2::Internal::printCsLensFFFF(os, *value, &exifData);

    // Type 2 maps to "Canon EF 28mm f/2.8" or "Sigma 24mm f/2.8 Super Wide II"
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test: All three metadata fields present but none match the special case
TEST_F(PrintCsLensFFFFTest_947, AllFieldsPresentNoSpecialMatch_947) {
    Exiv2::ExifData exifData;

    setExifString(exifData, "Exif.Image.Model", "Canon EOS 30D");
    setExifShortArray(exifData, "Exif.CanonCs.Lens", "50 50 1");
    setExifShort(exifData, "Exif.CanonCs.MaxAperture", 95);

    // Use a known lens value = 10
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("10");

    std::ostringstream os;
    Exiv2::Internal::printCsLensFFFF(os, *value, &exifData);

    // Should be one of the type 10 lenses
    std::string result = os.str();
    EXPECT_NE(result, "Canon EF-S 24mm f/2.8 STM");
    EXPECT_FALSE(result.empty());
}
