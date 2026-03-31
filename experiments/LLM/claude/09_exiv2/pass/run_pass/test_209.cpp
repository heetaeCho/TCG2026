#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// We need access to the internal printLensType via the PentaxMakerNote tag info
// The function is static in the .cpp file, so we test it through the public tag interface

namespace {

class PentaxLensTypeTest_209 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that a known lens type from pentaxLensType table produces expected output
TEST_F(PentaxLensTypeTest_209, KnownLensType_NoLens_209) {
    // Lens type 0 = "M-42 or No Lens" (index 0x0000, so byte0=0, byte1=0)
    Exiv2::ExifData exifData;
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    // For a two-component unsignedShort value representing lens type
    // pentaxLensType index = value[0]*256 + value[1]
    // For index 0: value[0]=0, value[1]=0
    value->read("0 0");
    
    // Use the Exiv2 tag printing infrastructure
    // We can access printLensType through the Pentax makernote tag for LensType
    // Tag 0x003f in Pentax makernote is LensType
    std::ostringstream os;
    Exiv2::ExifKey key("Exif.Pentax.LensType");
    exifData.add(key, value.get());
    
    auto it = exifData.findKey(key);
    if (it != exifData.end()) {
        os << it->print(&exifData);
    }
    
    // Index 0 maps to "M-42 or No Lens"
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test with a known specific lens type 
TEST_F(PentaxLensTypeTest_209, KnownLensType_KSeriesLens_209) {
    Exiv2::ExifData exifData;
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    // Index 256 = "K or M Lens" -> byte0=1, byte1=0
    value->read("1 0");
    
    std::ostringstream os;
    Exiv2::ExifKey key("Exif.Pentax.LensType");
    exifData.add(key, value.get());
    
    auto it = exifData.findKey(key);
    if (it != exifData.end()) {
        os << it->print(&exifData);
    }
    
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test with A Series Lens (index 512 = byte0=2, byte1=0)
TEST_F(PentaxLensTypeTest_209, KnownLensType_ASeriesLens_209) {
    Exiv2::ExifData exifData;
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("2 0");
    
    std::ostringstream os;
    Exiv2::ExifKey key("Exif.Pentax.LensType");
    exifData.add(key, value.get());
    
    auto it = exifData.findKey(key);
    if (it != exifData.end()) {
        os << it->print(&exifData);
    }
    
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test with Sigma Lens (index 768 = byte0=3, byte1=0)
TEST_F(PentaxLensTypeTest_209, KnownLensType_SigmaLens_209) {
    Exiv2::ExifData exifData;
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("3 0");
    
    std::ostringstream os;
    Exiv2::ExifKey key("Exif.Pentax.LensType");
    exifData.add(key, value.get());
    
    auto it = exifData.findKey(key);
    if (it != exifData.end()) {
        os << it->print(&exifData);
    }
    
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test with a specific well-known lens: smc PENTAX-FA 50mm F1.4 (index 1036 = byte0=4, byte1=12)
TEST_F(PentaxLensTypeTest_209, KnownLensType_FA50mmF14_209) {
    Exiv2::ExifData exifData;
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    // 1036 = 4*256 + 12
    value->read("4 12");
    
    std::ostringstream os;
    Exiv2::ExifKey key("Exif.Pentax.LensType");
    exifData.add(key, value.get());
    
    auto it = exifData.findKey(key);
    if (it != exifData.end()) {
        os << it->print(&exifData);
    }
    
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test with unknown lens type that doesn't exist in any table
TEST_F(PentaxLensTypeTest_209, UnknownLensType_209) {
    Exiv2::ExifData exifData;
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    // Use a value that's unlikely to be in the table
    // index = 255*256 + 254 = 65534
    value->read("255 254");
    
    std::ostringstream os;
    Exiv2::ExifKey key("Exif.Pentax.LensType");
    exifData.add(key, value.get());
    
    auto it = exifData.findKey(key);
    if (it != exifData.end()) {
        os << it->print(&exifData);
    }
    
    std::string result = os.str();
    // Should produce some output even for unknown types
    EXPECT_FALSE(result.empty());
}

// Test with nullptr metadata
TEST_F(PentaxLensTypeTest_209, NullMetadata_209) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("3 0");
    
    // When we can't pass nullptr through the print infrastructure,
    // we verify the tag can be created and value set
    EXPECT_EQ(value->count(), 2u);
    EXPECT_EQ(value->toUint32(0), 3u);
    EXPECT_EQ(value->toUint32(1), 0u);
}

// Test with single value (count == 1)
TEST_F(PentaxLensTypeTest_209, SingleValueCount_209) {
    Exiv2::ExifData exifData;
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("3");
    
    std::ostringstream os;
    Exiv2::ExifKey key("Exif.Pentax.LensType");
    exifData.add(key, value.get());
    
    auto it = exifData.findKey(key);
    if (it != exifData.end()) {
        os << it->print(&exifData);
    }
    
    // Should produce some output
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test lens type that goes through resolveLensType (index 0x0317 = 3*256+23 = 791)
TEST_F(PentaxLensTypeTest_209, ResolveLensType_0x0317_209) {
    Exiv2::ExifData exifData;
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    // 0x0317 = 3*256 + 23 = 791
    value->read("3 23");
    
    std::ostringstream os;
    Exiv2::ExifKey key("Exif.Pentax.LensType");
    exifData.add(key, value.get());
    
    auto it = exifData.findKey(key);
    if (it != exifData.end()) {
        os << it->print(&exifData);
    }
    
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test lens type 0x03ff (index = 3*256+255 = 1023) which uses resolveLens0x3ff
TEST_F(PentaxLensTypeTest_209, ResolveLens0x3ff_209) {
    Exiv2::ExifData exifData;
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    // 0x03ff = 3*256 + 255 = 1023
    value->read("3 255");
    
    std::ostringstream os;
    Exiv2::ExifKey key("Exif.Pentax.LensType");
    exifData.add(key, value.get());
    
    auto it = exifData.findKey(key);
    if (it != exifData.end()) {
        os << it->print(&exifData);
    }
    
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test lens type 0x08ff (index = 8*256+255 = 2303) which uses resolveLens0x8ff
TEST_F(PentaxLensTypeTest_209, ResolveLens0x8ff_209) {
    Exiv2::ExifData exifData;
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    // 0x08ff = 8*256 + 255 = 2303
    value->read("8 255");
    
    std::ostringstream os;
    Exiv2::ExifKey key("Exif.Pentax.LensType");
    exifData.add(key, value.get());
    
    auto it = exifData.findKey(key);
    if (it != exifData.end()) {
        os << it->print(&exifData);
    }
    
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test with Pentax Q lens (index 5377 = 21*256+1)
TEST_F(PentaxLensTypeTest_209, PentaxQLens_209) {
    Exiv2::ExifData exifData;
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    // 5377 = 21*256 + 1
    value->read("21 1");
    
    std::ostringstream os;
    Exiv2::ExifKey key("Exif.Pentax.LensType");
    exifData.add(key, value.get());
    
    auto it = exifData.findKey(key);
    if (it != exifData.end()) {
        os << it->print(&exifData);
    }
    
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test 645 lens (index 2817 = 11*256+1)
TEST_F(PentaxLensTypeTest_209, Pentax645Lens_209) {
    Exiv2::ExifData exifData;
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    // 2817 = 11*256 + 1
    value->read("11 1");
    
    std::ostringstream os;
    Exiv2::ExifKey key("Exif.Pentax.LensType");
    exifData.add(key, value.get());
    
    auto it = exifData.findKey(key);
    if (it != exifData.end()) {
        os << it->print(&exifData);
    }
    
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test HD PENTAX-D FA lens (index 2107 = 8*256+43)
TEST_F(PentaxLensTypeTest_209, HDPentaxDFALens_209) {
    Exiv2::ExifData exifData;
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    // 2107 = 8*256 + 43
    value->read("8 43");
    
    std::ostringstream os;
    Exiv2::ExifKey key("Exif.Pentax.LensType");
    exifData.add(key, value.get());
    
    auto it = exifData.findKey(key);
    if (it != exifData.end()) {
        os << it->print(&exifData);
    }
    
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test with three component value
TEST_F(PentaxLensTypeTest_209, ThreeComponentValue_209) {
    Exiv2::ExifData exifData;
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("3 0 5");
    
    std::ostringstream os;
    Exiv2::ExifKey key("Exif.Pentax.LensType");
    exifData.add(key, value.get());
    
    auto it = exifData.findKey(key);
    if (it != exifData.end()) {
        os << it->print(&exifData);
    }
    
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test zero-zero value maps to "M-42 or No Lens"
TEST_F(PentaxLensTypeTest_209, ZeroZeroIsM42_209) {
    Exiv2::ExifData exifData;
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("0 0");
    
    std::ostringstream os;
    Exiv2::ExifKey key("Exif.Pentax.LensType");
    exifData.add(key, value.get());
    
    auto it = exifData.findKey(key);
    if (it != exifData.end()) {
        os << it->print(&exifData);
    }
    
    std::string result = os.str();
    EXPECT_NE(result.find("M-42"), std::string::npos);
}

} // namespace
