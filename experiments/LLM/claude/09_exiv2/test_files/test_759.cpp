#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>
#include <exiv2/exiv2.hpp>
#include <string>
#include <cstdint>

namespace {

class ExifdatumTest_759 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that a default-constructed Exifdatum (with a known ExifKey) has expected key properties
TEST_F(ExifdatumTest_759, ConstructWithExifKey_759) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
    EXPECT_STREQ(datum.familyName(), "Exif");
    EXPECT_EQ(datum.groupName(), "Image");
    EXPECT_EQ(datum.tagName(), "Make");
}

// Test toString with no value set returns empty string
TEST_F(ExifdatumTest_759, ToStringWithNoValue_759) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.toString(), "");
    EXPECT_EQ(datum.toString(0), "");
}

// Test setting and getting a string value
TEST_F(ExifdatumTest_759, SetValueString_759) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    
    datum = std::string("Canon");
    EXPECT_EQ(datum.toString(), "Canon");
    EXPECT_EQ(datum.count(), 1u);
}

// Test setValue with string
TEST_F(ExifdatumTest_759, SetValueWithStringMethod_759) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    
    int result = datum.setValue("Nikon");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "Nikon");
}

// Test assigning uint16_t value
TEST_F(ExifdatumTest_759, AssignUint16Value_759) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    
    datum = static_cast<uint16_t>(1);
    EXPECT_EQ(datum.toInt64(0), 1);
    EXPECT_EQ(datum.count(), 1u);
}

// Test assigning uint32_t value
TEST_F(ExifdatumTest_759, AssignUint32Value_759) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    Exiv2::Exifdatum datum(key, nullptr);
    
    datum = static_cast<uint32_t>(1920);
    EXPECT_EQ(datum.toInt64(0), 1920);
}

// Test assigning int16_t value
TEST_F(ExifdatumTest_759, AssignInt16Value_759) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    
    datum = static_cast<int16_t>(-5);
    EXPECT_EQ(datum.toInt64(0), -5);
}

// Test assigning int32_t value
TEST_F(ExifdatumTest_759, AssignInt32Value_759) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    Exiv2::Exifdatum datum(key, nullptr);
    
    datum = static_cast<int32_t>(-100);
    EXPECT_EQ(datum.toInt64(0), -100);
}

// Test assigning URational value
TEST_F(ExifdatumTest_759, AssignURationalValue_759) {
    Exiv2::ExifKey key("Exif.Photo.ExposureTime");
    Exiv2::Exifdatum datum(key, nullptr);
    
    Exiv2::URational ur = {1, 100};
    datum = ur;
    Exiv2::Rational r = datum.toRational(0);
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 100);
}

// Test assigning Rational value
TEST_F(ExifdatumTest_759, AssignRationalValue_759) {
    Exiv2::ExifKey key("Exif.Photo.ExposureBiasValue");
    Exiv2::Exifdatum datum(key, nullptr);
    
    Exiv2::Rational r = {-1, 3};
    datum = r;
    Exiv2::Rational result = datum.toRational(0);
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, 3);
}

// Test copy constructor
TEST_F(ExifdatumTest_759, CopyConstructor_759) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("Sony");
    
    Exiv2::Exifdatum copy(datum);
    EXPECT_EQ(copy.key(), "Exif.Image.Make");
    EXPECT_EQ(copy.toString(), "Sony");
}

// Test copy assignment operator
TEST_F(ExifdatumTest_759, CopyAssignment_759) {
    Exiv2::ExifKey key1("Exif.Image.Make");
    Exiv2::Exifdatum datum1(key1, nullptr);
    datum1 = std::string("Sony");
    
    Exiv2::ExifKey key2("Exif.Image.Model");
    Exiv2::Exifdatum datum2(key2, nullptr);
    datum2 = datum1;
    
    EXPECT_EQ(datum2.key(), "Exif.Image.Make");
    EXPECT_EQ(datum2.toString(), "Sony");
}

// Test tag() returns a valid tag number
TEST_F(ExifdatumTest_759, TagReturnsValidNumber_759) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    
    // Make tag is 0x010f
    EXPECT_EQ(datum.tag(), 0x010f);
}

// Test typeId when no value is set
TEST_F(ExifdatumTest_759, TypeIdWithNoValue_759) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    
    // Without value, typeId should be undefined or default
    Exiv2::TypeId tid = datum.typeId();
    EXPECT_EQ(tid, Exiv2::undefined);
}

// Test size when no value is set
TEST_F(ExifdatumTest_759, SizeWithNoValue_759) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.size(), 0u);
}

// Test count when no value is set
TEST_F(ExifdatumTest_759, CountWithNoValue_759) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.count(), 0u);
}

// Test setValue with a Value pointer
TEST_F(ExifdatumTest_759, SetValueWithValuePointer_759) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    
    auto value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("TestCamera");
    datum.setValue(value.get());
    
    EXPECT_EQ(datum.toString(), "TestCamera");
    EXPECT_EQ(datum.typeId(), Exiv2::asciiString);
}

// Test getValue returns a clone of the value
TEST_F(ExifdatumTest_759, GetValueReturnsClone_759) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("Panasonic");
    
    auto val = datum.getValue();
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->toString(), "Panasonic");
}

// Test getValue when no value is set
TEST_F(ExifdatumTest_759, GetValueWithNoValue_759) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    
    auto val = datum.getValue();
    // When no value is set, getValue should return nullptr
    EXPECT_EQ(val, nullptr);
}

// Test toFloat conversion
TEST_F(ExifdatumTest_759, ToFloatConversion_759) {
    Exiv2::ExifKey key("Exif.Photo.ExposureTime");
    Exiv2::Exifdatum datum(key, nullptr);
    
    Exiv2::URational ur = {1, 4};
    datum = ur;
    
    float result = datum.toFloat(0);
    EXPECT_FLOAT_EQ(result, 0.25f);
}

// Test toInt64 conversion
TEST_F(ExifdatumTest_759, ToInt64Conversion_759) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    
    datum = static_cast<uint16_t>(6);
    EXPECT_EQ(datum.toInt64(0), 6);
}

// Test toString with index n
TEST_F(ExifdatumTest_759, ToStringWithIndex_759) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("Olympus");
    
    EXPECT_EQ(datum.toString(0), "Olympus");
}

// Test sizeDataArea when no data area is set
TEST_F(ExifdatumTest_759, SizeDataAreaNoData_759) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.sizeDataArea(), 0u);
}

// Test tagLabel returns a non-empty description for known tags
TEST_F(ExifdatumTest_759, TagLabelForKnownTag_759) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test familyName is "Exif"
TEST_F(ExifdatumTest_759, FamilyNameIsExif_759) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    Exiv2::Exifdatum datum(key, nullptr);
    
    EXPECT_STREQ(datum.familyName(), "Exif");
}

// Test write to ostream
TEST_F(ExifdatumTest_759, WriteToOstream_759) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("Fujifilm");
    
    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test assigning a Value object directly
TEST_F(ExifdatumTest_759, AssignValueObject_759) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    
    auto value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("Leica");
    datum = *value;
    
    EXPECT_EQ(datum.toString(), "Leica");
}

// Test constructing with a value pointer
TEST_F(ExifdatumTest_759, ConstructWithValuePointer_759) {
    Exiv2::ExifKey key("Exif.Image.Make");
    auto value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("Hasselblad");
    
    Exiv2::Exifdatum datum(key, value.get());
    EXPECT_EQ(datum.toString(), "Hasselblad");
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
}

// Test idx returns a value (default should be 0)
TEST_F(ExifdatumTest_759, IdxDefaultValue_759) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    
    int idx = datum.idx();
    EXPECT_EQ(idx, 0);
}

// Test typeName when no value is set
TEST_F(ExifdatumTest_759, TypeNameWithNoValue_759) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    
    // With no value, typeName might return a representation for undefined
    const char* tn = datum.typeName();
    // Should not crash; may be nullptr or a valid string
    // Just check it doesn't crash
    (void)tn;
}

// Test setting value then overwriting with another string
TEST_F(ExifdatumTest_759, OverwriteStringValue_759) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    
    datum = std::string("First");
    EXPECT_EQ(datum.toString(), "First");
    
    datum = std::string("Second");
    EXPECT_EQ(datum.toString(), "Second");
}

// Test that ifdName returns something meaningful
TEST_F(ExifdatumTest_759, IfdNameReturnsValue_759) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    
    const char* ifdName = datum.ifdName();
    ASSERT_NE(ifdName, nullptr);
    // IFD0 or similar
    EXPECT_TRUE(std::string(ifdName).size() > 0);
}

} // namespace
