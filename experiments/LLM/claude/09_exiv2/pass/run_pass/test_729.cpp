#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/error.hpp>
#include <exiv2/value.hpp>
#include <exiv2/tags.hpp>

namespace {

class ExifdatumTest_729 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that constructing an Exifdatum with a valid ExifKey works
TEST_F(ExifdatumTest_729, ConstructWithValidKey_729) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
}

// Test that value() throws when no value is set
TEST_F(ExifdatumTest_729, ValueThrowsWhenNotSet_729) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    EXPECT_THROW(datum.value(), Exiv2::Error);
}

// Test that familyName returns "Exif"
TEST_F(ExifdatumTest_729, FamilyNameReturnsExif_729) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    EXPECT_STREQ(datum.familyName(), "Exif");
}

// Test that groupName returns the correct group
TEST_F(ExifdatumTest_729, GroupNameReturnsImage_729) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "Image");
}

// Test that tagName returns the correct tag name
TEST_F(ExifdatumTest_729, TagNameReturnsMake_729) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.tagName(), "Make");
}

// Test tag() returns the correct tag number
TEST_F(ExifdatumTest_729, TagReturnsCorrectValue_729) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.tag(), 0x010f);
}

// Test setValue with a string value
TEST_F(ExifdatumTest_729, SetValueWithString_729) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    // First set the type by assigning a Value
    Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::asciiString);
    datum.setValue(val.get());
    int result = datum.setValue("TestCamera");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "TestCamera");
}

// Test operator= with string
TEST_F(ExifdatumTest_729, AssignString_729) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("Nikon");
    EXPECT_EQ(datum.toString(), "Nikon");
}

// Test operator= with uint16_t
TEST_F(ExifdatumTest_729, AssignUint16_729) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = static_cast<uint16_t>(1);
    EXPECT_EQ(datum.toInt64(0), 1);
}

// Test operator= with uint32_t
TEST_F(ExifdatumTest_729, AssignUint32_729) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = static_cast<uint32_t>(1920);
    EXPECT_EQ(datum.toInt64(0), 1920);
}

// Test operator= with int16_t
TEST_F(ExifdatumTest_729, AssignInt16_729) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = static_cast<int16_t>(-5);
    EXPECT_EQ(datum.toInt64(0), -5);
}

// Test operator= with int32_t
TEST_F(ExifdatumTest_729, AssignInt32_729) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = static_cast<int32_t>(-100);
    EXPECT_EQ(datum.toInt64(0), -100);
}

// Test operator= with URational
TEST_F(ExifdatumTest_729, AssignURational_729) {
    Exiv2::ExifKey key("Exif.Image.XResolution");
    Exiv2::Exifdatum datum(key, nullptr);
    Exiv2::URational ur(72, 1);
    datum = ur;
    EXPECT_EQ(datum.toInt64(0), 72);
}

// Test operator= with Rational
TEST_F(ExifdatumTest_729, AssignRational_729) {
    Exiv2::ExifKey key("Exif.Photo.ExposureBiasValue");
    Exiv2::Exifdatum datum(key, nullptr);
    Exiv2::Rational r(-1, 3);
    datum = r;
    Exiv2::Rational result = datum.toRational(0);
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, 3);
}

// Test copy constructor
TEST_F(ExifdatumTest_729, CopyConstructor_729) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("Canon");

    Exiv2::Exifdatum copy(datum);
    EXPECT_EQ(copy.key(), "Exif.Image.Make");
    EXPECT_EQ(copy.toString(), "Canon");
}

// Test copy assignment operator
TEST_F(ExifdatumTest_729, CopyAssignment_729) {
    Exiv2::ExifKey key1("Exif.Image.Make");
    Exiv2::Exifdatum datum1(key1, nullptr);
    datum1 = std::string("Canon");

    Exiv2::ExifKey key2("Exif.Image.Model");
    Exiv2::Exifdatum datum2(key2, nullptr);
    datum2 = datum1;
    EXPECT_EQ(datum2.key(), "Exif.Image.Make");
    EXPECT_EQ(datum2.toString(), "Canon");
}

// Test getValue returns a valid unique_ptr when value is set
TEST_F(ExifdatumTest_729, GetValueReturnsValidPtr_729) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("Sony");
    auto val = datum.getValue();
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->toString(), "Sony");
}

// Test getValue returns nullptr when value is not set
TEST_F(ExifdatumTest_729, GetValueReturnsNullptrWhenNotSet_729) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    auto val = datum.getValue();
    EXPECT_EQ(val, nullptr);
}

// Test count returns 0 when no value set
TEST_F(ExifdatumTest_729, CountZeroWhenNoValue_729) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.count(), 0u);
}

// Test count returns correct count after setting a value
TEST_F(ExifdatumTest_729, CountAfterSettingValue_729) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("Test");
    EXPECT_GT(datum.count(), 0u);
}

// Test size returns 0 when no value set
TEST_F(ExifdatumTest_729, SizeZeroWhenNoValue_729) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.size(), 0u);
}

// Test size returns correct size after setting a value
TEST_F(ExifdatumTest_729, SizeAfterSettingValue_729) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("TestMaker");
    EXPECT_GT(datum.size(), 0u);
}

// Test typeId when no value is set
TEST_F(ExifdatumTest_729, TypeIdWhenNoValue_729) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    // When no value set, typeId should return invalidTypeId or similar
    Exiv2::TypeId tid = datum.typeId();
    EXPECT_EQ(tid, Exiv2::invalidTypeId);
}

// Test typeId after setting a string value
TEST_F(ExifdatumTest_729, TypeIdAfterStringAssignment_729) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("Canon");
    EXPECT_EQ(datum.typeId(), Exiv2::asciiString);
}

// Test typeId after setting uint16_t value
TEST_F(ExifdatumTest_729, TypeIdAfterUint16Assignment_729) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = static_cast<uint16_t>(1);
    EXPECT_EQ(datum.typeId(), Exiv2::unsignedShort);
}

// Test operator= with Value object
TEST_F(ExifdatumTest_729, AssignValueObject_729) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::asciiString);
    val->read("Pentax");
    datum = *val;
    EXPECT_EQ(datum.toString(), "Pentax");
}

// Test setValue with Value pointer
TEST_F(ExifdatumTest_729, SetValueWithPointer_729) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::asciiString);
    val->read("Olympus");
    datum.setValue(val.get());
    EXPECT_EQ(datum.toString(), "Olympus");
}

// Test setValue with nullptr clears the value
TEST_F(ExifdatumTest_729, SetValueWithNullptr_729) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("Canon");
    EXPECT_NO_THROW(datum.value());
    datum.setValue(nullptr);
    EXPECT_THROW(datum.value(), Exiv2::Error);
}

// Test toFloat
TEST_F(ExifdatumTest_729, ToFloat_729) {
    Exiv2::ExifKey key("Exif.Image.XResolution");
    Exiv2::Exifdatum datum(key, nullptr);
    Exiv2::URational ur(72, 1);
    datum = ur;
    EXPECT_FLOAT_EQ(datum.toFloat(0), 72.0f);
}

// Test toString with index
TEST_F(ExifdatumTest_729, ToStringWithIndex_729) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("Fujifilm");
    std::string result = datum.toString(0);
    EXPECT_EQ(result, "Fujifilm");
}

// Test sizeDataArea when no data area
TEST_F(ExifdatumTest_729, SizeDataAreaZero_729) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("Test");
    EXPECT_EQ(datum.sizeDataArea(), 0u);
}

// Test constructing with a Value pointer
TEST_F(ExifdatumTest_729, ConstructWithValue_729) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::asciiString);
    val->read("Leica");
    Exiv2::Exifdatum datum(key, val.get());
    EXPECT_EQ(datum.toString(), "Leica");
    EXPECT_NO_THROW(datum.value());
}

// Test tagLabel returns a non-empty string for known tags
TEST_F(ExifdatumTest_729, TagLabelNonEmpty_729) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test that the error thrown by value() has the correct error code
TEST_F(ExifdatumTest_729, ValueThrowsCorrectErrorCode_729) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    try {
        datum.value();
        FAIL() << "Expected Exiv2::Error to be thrown";
    } catch (const Exiv2::Error& e) {
        EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerValueNotSet);
    }
}

// Test using ExifData container with Exifdatum
TEST_F(ExifdatumTest_729, ExifDataAddAndFind_729) {
    Exiv2::ExifData exifData;
    Exiv2::ExifKey key("Exif.Image.Make");
    exifData[key.key()] = "Canon";
    
    auto it = exifData.findKey(key);
    ASSERT_NE(it, exifData.end());
    EXPECT_EQ(it->toString(), "Canon");
}

// Test ExifData empty
TEST_F(ExifdatumTest_729, ExifDataEmpty_729) {
    Exiv2::ExifData exifData;
    EXPECT_TRUE(exifData.empty());
}

// Test ExifData count after adding entries
TEST_F(ExifdatumTest_729, ExifDataCount_729) {
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "Canon";
    exifData["Exif.Image.Model"] = "EOS R5";
    EXPECT_EQ(exifData.count(), 2u);
}

// Test idx() returns default value
TEST_F(ExifdatumTest_729, IdxReturnsDefault_729) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    // idx should return 0 by default
    EXPECT_EQ(datum.idx(), 0);
}

// Test typeName when no value is set
TEST_F(ExifdatumTest_729, TypeNameWhenNoValue_729) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    // When no value is set, typeName should return something meaningful or empty
    const char* tn = datum.typeName();
    // Just ensure it doesn't crash; might be nullptr or a valid string
    (void)tn;
}

// Test typeSize when value is set
TEST_F(ExifdatumTest_729, TypeSizeForUint16_729) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = static_cast<uint16_t>(1);
    EXPECT_EQ(datum.typeSize(), 2u);
}

}  // namespace
