#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <sstream>
#include <cstring>

class ExifdatumTest_734 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test construction with a valid ExifKey
TEST_F(ExifdatumTest_734, ConstructWithValidKey_734) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
    EXPECT_EQ(datum.familyName(), std::string("Exif"));
    EXPECT_EQ(datum.groupName(), "Image");
    EXPECT_EQ(datum.tagName(), "Make");
}

// Test construction with key and value
TEST_F(ExifdatumTest_734, ConstructWithKeyAndValue_734) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::AsciiValue value("Canon");
    Exiv2::Exifdatum datum(key, &value);
    EXPECT_EQ(datum.toString(), "Canon");
    EXPECT_EQ(datum.count(), 6u); // "Canon" + null terminator
}

// Test copy constructor
TEST_F(ExifdatumTest_734, CopyConstructor_734) {
    Exiv2::ExifKey key("Exif.Image.Model");
    Exiv2::AsciiValue value("EOS 5D");
    Exiv2::Exifdatum original(key, &value);
    Exiv2::Exifdatum copy(original);
    EXPECT_EQ(copy.key(), original.key());
    EXPECT_EQ(copy.toString(), original.toString());
    EXPECT_EQ(copy.tagName(), original.tagName());
}

// Test copy assignment operator
TEST_F(ExifdatumTest_734, CopyAssignment_734) {
    Exiv2::ExifKey key1("Exif.Image.Make");
    Exiv2::AsciiValue value1("Nikon");
    Exiv2::Exifdatum datum1(key1, &value1);

    Exiv2::ExifKey key2("Exif.Image.Model");
    Exiv2::Exifdatum datum2(key2, nullptr);
    datum2 = datum1;
    EXPECT_EQ(datum2.key(), datum1.key());
    EXPECT_EQ(datum2.toString(), datum1.toString());
}

// Test operator= with string
TEST_F(ExifdatumTest_734, AssignString_734) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("Sony");
    EXPECT_EQ(datum.toString(), "Sony");
}

// Test operator= with uint16_t
TEST_F(ExifdatumTest_734, AssignUint16_734) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    uint16_t val = 1;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 1);
}

// Test operator= with uint32_t
TEST_F(ExifdatumTest_734, AssignUint32_734) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    Exiv2::Exifdatum datum(key, nullptr);
    uint32_t val = 4000;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 4000);
}

// Test operator= with URational
TEST_F(ExifdatumTest_734, AssignURational_734) {
    Exiv2::ExifKey key("Exif.Image.XResolution");
    Exiv2::Exifdatum datum(key, nullptr);
    Exiv2::URational val(72, 1);
    datum = val;
    EXPECT_EQ(datum.toRational(0).first, 72);
    EXPECT_EQ(datum.toRational(0).second, 1);
}

// Test operator= with int16_t
TEST_F(ExifdatumTest_734, AssignInt16_734) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    int16_t val = -5;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), -5);
}

// Test operator= with int32_t
TEST_F(ExifdatumTest_734, AssignInt32_734) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    Exiv2::Exifdatum datum(key, nullptr);
    int32_t val = -1000;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), -1000);
}

// Test operator= with Rational
TEST_F(ExifdatumTest_734, AssignRational_734) {
    Exiv2::ExifKey key("Exif.Image.XResolution");
    Exiv2::Exifdatum datum(key, nullptr);
    Exiv2::Rational val(-1, 3);
    datum = val;
    Exiv2::Rational result = datum.toRational(0);
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, 3);
}

// Test operator= with Value
TEST_F(ExifdatumTest_734, AssignValue_734) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    Exiv2::AsciiValue value("Pentax");
    datum = static_cast<const Exiv2::Value&>(value);
    EXPECT_EQ(datum.toString(), "Pentax");
}

// Test setValue with string
TEST_F(ExifdatumTest_734, SetValueString_734) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    int result = datum.setValue("Olympus");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "Olympus");
}

// Test setValue with Value pointer
TEST_F(ExifdatumTest_734, SetValuePointer_734) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::AsciiValue value("Fujifilm");
    Exiv2::Exifdatum datum(key, nullptr);
    datum.setValue(&value);
    EXPECT_EQ(datum.toString(), "Fujifilm");
}

// Test setValue with nullptr
TEST_F(ExifdatumTest_734, SetValueNullPointer_734) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::AsciiValue value("Test");
    Exiv2::Exifdatum datum(key, &value);
    datum.setValue(nullptr);
    // After setting null, getValue should return nullptr or count should be 0
    EXPECT_EQ(datum.count(), 0u);
}

// Test key properties
TEST_F(ExifdatumTest_734, KeyProperties_734) {
    Exiv2::ExifKey key("Exif.Photo.ExposureTime");
    Exiv2::Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Exif.Photo.ExposureTime");
    EXPECT_EQ(std::string(datum.familyName()), "Exif");
    EXPECT_EQ(datum.groupName(), "Photo");
    EXPECT_EQ(datum.tagName(), "ExposureTime");
    EXPECT_EQ(datum.tag(), 0x829a);
}

// Test tag() returns correct tag number
TEST_F(ExifdatumTest_734, TagNumber_734) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.tag(), 0x0112);
}

// Test typeId when no value is set
TEST_F(ExifdatumTest_734, TypeIdNoValue_734) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    // When no value is set, typeId should return invalidTypeId or similar
    EXPECT_EQ(datum.typeId(), Exiv2::invalidTypeId);
}

// Test typeId after setting a value
TEST_F(ExifdatumTest_734, TypeIdWithValue_734) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::AsciiValue value("TestMake");
    Exiv2::Exifdatum datum(key, &value);
    EXPECT_EQ(datum.typeId(), Exiv2::asciiString);
}

// Test count when no value
TEST_F(ExifdatumTest_734, CountNoValue_734) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.count(), 0u);
}

// Test size when no value
TEST_F(ExifdatumTest_734, SizeNoValue_734) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.size(), 0u);
}

// Test size with value
TEST_F(ExifdatumTest_734, SizeWithValue_734) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::AsciiValue value("Canon");
    Exiv2::Exifdatum datum(key, &value);
    EXPECT_GT(datum.size(), 0u);
}

// Test toString with no value
TEST_F(ExifdatumTest_734, ToStringNoValue_734) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.toString(), "");
}

// Test toFloat
TEST_F(ExifdatumTest_734, ToFloat_734) {
    Exiv2::ExifKey key("Exif.Image.XResolution");
    Exiv2::Exifdatum datum(key, nullptr);
    Exiv2::URational val(72, 1);
    datum = val;
    EXPECT_FLOAT_EQ(datum.toFloat(0), 72.0f);
}

// Test toFloat with rational
TEST_F(ExifdatumTest_734, ToFloatRational_734) {
    Exiv2::ExifKey key("Exif.Image.XResolution");
    Exiv2::Exifdatum datum(key, nullptr);
    Exiv2::URational val(1, 3);
    datum = val;
    EXPECT_NEAR(datum.toFloat(0), 1.0f / 3.0f, 0.001f);
}

// Test getValue returns a valid unique_ptr
TEST_F(ExifdatumTest_734, GetValue_734) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::AsciiValue value("TestValue");
    Exiv2::Exifdatum datum(key, &value);
    auto val = datum.getValue();
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->toString(), "TestValue");
}

// Test getValue when no value is set
TEST_F(ExifdatumTest_734, GetValueNoValue_734) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    auto val = datum.getValue();
    EXPECT_EQ(val, nullptr);
}

// Test write to ostream
TEST_F(ExifdatumTest_734, WriteToStream_734) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::AsciiValue value("StreamTest");
    Exiv2::Exifdatum datum(key, &value);
    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test idx returns an integer
TEST_F(ExifdatumTest_734, IdxDefault_734) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    // idx should be 0 by default
    EXPECT_EQ(datum.idx(), 0);
}

// Test typeName when no value
TEST_F(ExifdatumTest_734, TypeNameNoValue_734) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    // When no value, typeName might return empty or null
    const char* tn = datum.typeName();
    // Just verify it doesn't crash; could be nullptr or ""
    if (tn) {
        SUCCEED();
    } else {
        SUCCEED();
    }
}

// Test typeName with value
TEST_F(ExifdatumTest_734, TypeNameWithValue_734) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::AsciiValue value("Test");
    Exiv2::Exifdatum datum(key, &value);
    const char* tn = datum.typeName();
    ASSERT_NE(tn, nullptr);
    EXPECT_EQ(std::string(tn), "Ascii");
}

// Test assigning URational with zero denominator
TEST_F(ExifdatumTest_734, AssignURationalZeroDenominator_734) {
    Exiv2::ExifKey key("Exif.Image.XResolution");
    Exiv2::Exifdatum datum(key, nullptr);
    Exiv2::URational val(0, 0);
    datum = val;
    Exiv2::Rational result = datum.toRational(0);
    EXPECT_EQ(result.first, 0);
    EXPECT_EQ(result.second, 0);
}

// Test assigning URational with large values
TEST_F(ExifdatumTest_734, AssignURationalLargeValues_734) {
    Exiv2::ExifKey key("Exif.Image.XResolution");
    Exiv2::Exifdatum datum(key, nullptr);
    Exiv2::URational val(UINT32_MAX, 1);
    datum = val;
    EXPECT_EQ(datum.toRational(0).first, static_cast<int32_t>(UINT32_MAX));
}

// Test sizeDataArea when no data area
TEST_F(ExifdatumTest_734, SizeDataAreaEmpty_734) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::AsciiValue value("Test");
    Exiv2::Exifdatum datum(key, &value);
    EXPECT_EQ(datum.sizeDataArea(), 0u);
}

// Test tagLabel returns non-empty for known tags
TEST_F(ExifdatumTest_734, TagLabel_734) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test using ExifData container with Exifdatum
TEST_F(ExifdatumTest_734, ExifDataContainerUsage_734) {
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "Canon";
    exifData["Exif.Image.Model"] = "EOS R5";

    auto it = exifData.findKey(Exiv2::ExifKey("Exif.Image.Make"));
    ASSERT_NE(it, exifData.end());
    EXPECT_EQ(it->toString(), "Canon");

    it = exifData.findKey(Exiv2::ExifKey("Exif.Image.Model"));
    ASSERT_NE(it, exifData.end());
    EXPECT_EQ(it->toString(), "EOS R5");
}

// Test multiple assignments overwrite properly
TEST_F(ExifdatumTest_734, MultipleAssignments_734) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("First");
    EXPECT_EQ(datum.toString(), "First");
    datum = std::string("Second");
    EXPECT_EQ(datum.toString(), "Second");
}

// Test typeSize with value
TEST_F(ExifdatumTest_734, TypeSizeWithValue_734) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    uint16_t val = 1;
    datum = val;
    EXPECT_EQ(datum.typeSize(), 2u); // uint16 is 2 bytes
}

// Test toInt64 for uint16
TEST_F(ExifdatumTest_734, ToInt64Uint16_734) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    uint16_t val = 42;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 42);
}

// Test copy to buffer
TEST_F(ExifdatumTest_734, CopyToBuffer_734) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    uint16_t val = 1;
    datum = val;

    Exiv2::byte buf[64] = {0};
    size_t copied = datum.copy(buf, Exiv2::bigEndian);
    EXPECT_GT(copied, 0u);
}

// Test ifdId
TEST_F(ExifdatumTest_734, IfdId_734) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    Exiv2::IfdId id = datum.ifdId();
    EXPECT_EQ(id, Exiv2::IfdId::ifd0Id);
}

// Test self-assignment
TEST_F(ExifdatumTest_734, SelfAssignment_734) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::AsciiValue value("SelfTest");
    Exiv2::Exifdatum datum(key, &value);
    datum = datum;
    EXPECT_EQ(datum.toString(), "SelfTest");
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
}
