#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <sstream>
#include <cstring>

class ExifdatumTest_731 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test construction with a valid ExifKey
TEST_F(ExifdatumTest_731, ConstructWithValidKey_731) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
    EXPECT_EQ(datum.familyName(), std::string("Exif"));
    EXPECT_EQ(datum.groupName(), "Image");
    EXPECT_EQ(datum.tagName(), "Make");
}

// Test construction with key and a value
TEST_F(ExifdatumTest_731, ConstructWithKeyAndValue_731) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::AsciiValue val("Canon");
    Exiv2::Exifdatum datum(key, &val);
    
    EXPECT_EQ(datum.toString(), "Canon");
    EXPECT_EQ(datum.count(), 6u); // "Canon" + null
}

// Test copy constructor
TEST_F(ExifdatumTest_731, CopyConstructor_731) {
    Exiv2::ExifKey key("Exif.Image.Model");
    Exiv2::AsciiValue val("EOS 5D");
    Exiv2::Exifdatum original(key, &val);
    
    Exiv2::Exifdatum copy(original);
    
    EXPECT_EQ(copy.key(), original.key());
    EXPECT_EQ(copy.toString(), original.toString());
    EXPECT_EQ(copy.tag(), original.tag());
}

// Test copy assignment operator
TEST_F(ExifdatumTest_731, CopyAssignmentOperator_731) {
    Exiv2::ExifKey key1("Exif.Image.Make");
    Exiv2::AsciiValue val1("Canon");
    Exiv2::Exifdatum datum1(key1, &val1);
    
    Exiv2::ExifKey key2("Exif.Image.Model");
    Exiv2::AsciiValue val2("EOS R");
    Exiv2::Exifdatum datum2(key2, &val2);
    
    datum2 = datum1;
    
    EXPECT_EQ(datum2.key(), "Exif.Image.Make");
    EXPECT_EQ(datum2.toString(), "Canon");
}

// Test operator= with string
TEST_F(ExifdatumTest_731, AssignStringOperator_731) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    
    datum = std::string("Nikon");
    
    EXPECT_EQ(datum.toString(), "Nikon");
}

// Test operator= with uint16_t
TEST_F(ExifdatumTest_731, AssignUint16Operator_731) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    
    uint16_t val = 1;
    datum = val;
    
    EXPECT_EQ(datum.toInt64(0), 1);
}

// Test operator= with uint32_t
TEST_F(ExifdatumTest_731, AssignUint32Operator_731) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    Exiv2::Exifdatum datum(key, nullptr);
    
    uint32_t val = 4000;
    datum = val;
    
    EXPECT_EQ(datum.toInt64(0), 4000);
}

// Test operator= with int16_t
TEST_F(ExifdatumTest_731, AssignInt16Operator_731) {
    Exiv2::ExifKey key("Exif.Photo.ExposureCompensation");
    Exiv2::Exifdatum datum(key, nullptr);
    
    int16_t val = -3;
    datum = val;
    
    EXPECT_EQ(datum.toInt64(0), -3);
}

// Test operator= with int32_t
TEST_F(ExifdatumTest_731, AssignInt32Operator_731) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    Exiv2::Exifdatum datum(key, nullptr);
    
    int32_t val = 1920;
    datum = val;
    
    EXPECT_EQ(datum.toInt64(0), 1920);
}

// Test operator= with URational
TEST_F(ExifdatumTest_731, AssignURationalOperator_731) {
    Exiv2::ExifKey key("Exif.Photo.ExposureTime");
    Exiv2::Exifdatum datum(key, nullptr);
    
    Exiv2::URational val(1, 250);
    datum = val;
    
    Exiv2::Rational result = datum.toRational(0);
    EXPECT_EQ(result.first, 1);
    EXPECT_EQ(result.second, 250);
}

// Test operator= with Rational
TEST_F(ExifdatumTest_731, AssignRationalOperator_731) {
    Exiv2::ExifKey key("Exif.Photo.ExposureBiasValue");
    Exiv2::Exifdatum datum(key, nullptr);
    
    Exiv2::Rational val(-1, 3);
    datum = val;
    
    Exiv2::Rational result = datum.toRational(0);
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, 3);
}

// Test operator= with Value
TEST_F(ExifdatumTest_731, AssignValueOperator_731) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    
    Exiv2::AsciiValue val("Sony");
    datum = static_cast<const Exiv2::Value&>(val);
    
    EXPECT_EQ(datum.toString(), "Sony");
}

// Test setValue with string
TEST_F(ExifdatumTest_731, SetValueString_731) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::AsciiValue initial("Canon");
    Exiv2::Exifdatum datum(key, &initial);
    
    int result = datum.setValue("Fujifilm");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "Fujifilm");
}

// Test setValue with Value pointer
TEST_F(ExifdatumTest_731, SetValuePointer_731) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    
    Exiv2::AsciiValue val("Pentax");
    datum.setValue(&val);
    
    EXPECT_EQ(datum.toString(), "Pentax");
}

// Test setValue with nullptr
TEST_F(ExifdatumTest_731, SetValueNullPointer_731) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::AsciiValue val("Canon");
    Exiv2::Exifdatum datum(key, &val);
    
    datum.setValue(nullptr);
    
    // After setting nullptr, count/size should be 0
    EXPECT_EQ(datum.count(), 0u);
}

// Test key-related methods
TEST_F(ExifdatumTest_731, KeyRelatedMethods_731) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    Exiv2::Exifdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.key(), "Exif.Photo.DateTimeOriginal");
    EXPECT_EQ(datum.familyName(), std::string("Exif"));
    EXPECT_EQ(datum.groupName(), "Photo");
    EXPECT_EQ(datum.tagName(), "DateTimeOriginal");
}

// Test tag() method
TEST_F(ExifdatumTest_731, TagMethod_731) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    
    // Orientation tag is 0x0112 = 274
    EXPECT_EQ(datum.tag(), 0x0112);
}

// Test typeId when no value is set
TEST_F(ExifdatumTest_731, TypeIdNoValue_731) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    
    // Without a value, typeId should return invalidTypeId or similar
    EXPECT_EQ(datum.typeId(), Exiv2::invalidTypeId);
}

// Test typeId with a value
TEST_F(ExifdatumTest_731, TypeIdWithValue_731) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::AsciiValue val("Canon");
    Exiv2::Exifdatum datum(key, &val);
    
    EXPECT_EQ(datum.typeId(), Exiv2::asciiString);
}

// Test count and size with value
TEST_F(ExifdatumTest_731, CountAndSizeWithValue_731) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::AsciiValue val("Canon");
    Exiv2::Exifdatum datum(key, &val);
    
    EXPECT_GT(datum.count(), 0u);
    EXPECT_GT(datum.size(), 0u);
}

// Test count and size without value
TEST_F(ExifdatumTest_731, CountAndSizeWithoutValue_731) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.count(), 0u);
    EXPECT_EQ(datum.size(), 0u);
}

// Test toString with index
TEST_F(ExifdatumTest_731, ToStringWithIndex_731) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::AsciiValue val("Canon");
    Exiv2::Exifdatum datum(key, &val);
    
    EXPECT_EQ(datum.toString(0), "Canon");
}

// Test toFloat
TEST_F(ExifdatumTest_731, ToFloat_731) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    
    uint16_t orientation = 1;
    datum = orientation;
    
    EXPECT_FLOAT_EQ(datum.toFloat(0), 1.0f);
}

// Test toInt64
TEST_F(ExifdatumTest_731, ToInt64_731) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    
    uint16_t orientation = 6;
    datum = orientation;
    
    EXPECT_EQ(datum.toInt64(0), 6);
}

// Test toRational
TEST_F(ExifdatumTest_731, ToRational_731) {
    Exiv2::ExifKey key("Exif.Photo.ExposureTime");
    Exiv2::Exifdatum datum(key, nullptr);
    
    Exiv2::URational expTime(1, 1000);
    datum = expTime;
    
    Exiv2::Rational result = datum.toRational(0);
    EXPECT_EQ(result.first, 1);
    EXPECT_EQ(result.second, 1000);
}

// Test getValue
TEST_F(ExifdatumTest_731, GetValue_731) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::AsciiValue val("Canon");
    Exiv2::Exifdatum datum(key, &val);
    
    auto value = datum.getValue();
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->toString(), "Canon");
}

// Test getValue when no value set
TEST_F(ExifdatumTest_731, GetValueNull_731) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    
    auto value = datum.getValue();
    EXPECT_EQ(value, nullptr);
}

// Test write to stream
TEST_F(ExifdatumTest_731, WriteToStream_731) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::AsciiValue val("Canon");
    Exiv2::Exifdatum datum(key, &val);
    
    std::ostringstream os;
    datum.write(os, nullptr);
    
    EXPECT_FALSE(os.str().empty());
}

// Test sizeDataArea when no data area
TEST_F(ExifdatumTest_731, SizeDataAreaEmpty_731) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::AsciiValue val("Canon");
    Exiv2::Exifdatum datum(key, &val);
    
    EXPECT_EQ(datum.sizeDataArea(), 0u);
}

// Test tagLabel returns a non-empty string for known tags
TEST_F(ExifdatumTest_731, TagLabel_731) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test tagDesc
TEST_F(ExifdatumTest_731, TagDesc_731) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    
    // tagDesc may or may not be empty depending on tag, but should not throw
    std::string desc = datum.tagDesc();
    // Just verify it doesn't crash
}

// Test typeName with value
TEST_F(ExifdatumTest_731, TypeName_731) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::AsciiValue val("Canon");
    Exiv2::Exifdatum datum(key, &val);
    
    const char* tn = datum.typeName();
    ASSERT_NE(tn, nullptr);
    EXPECT_EQ(std::string(tn), "Ascii");
}

// Test typeSize with value
TEST_F(ExifdatumTest_731, TypeSize_731) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::AsciiValue val("Canon");
    Exiv2::Exifdatum datum(key, &val);
    
    // ASCII type size should be 1
    EXPECT_EQ(datum.typeSize(), 1u);
}

// Test ExifData integration: add and find
TEST_F(ExifdatumTest_731, ExifDataAddAndFind_731) {
    Exiv2::ExifData exifData;
    
    Exiv2::ExifKey key("Exif.Image.Make");
    exifData[key.key()] = "Canon";
    
    auto it = exifData.findKey(key);
    ASSERT_NE(it, exifData.end());
    EXPECT_EQ(it->toString(), "Canon");
}

// Test ExifData: multiple entries
TEST_F(ExifdatumTest_731, ExifDataMultipleEntries_731) {
    Exiv2::ExifData exifData;
    
    exifData["Exif.Image.Make"] = "Canon";
    exifData["Exif.Image.Model"] = "EOS 5D Mark IV";
    
    Exiv2::ExifKey makeKey("Exif.Image.Make");
    Exiv2::ExifKey modelKey("Exif.Image.Model");
    
    auto itMake = exifData.findKey(makeKey);
    auto itModel = exifData.findKey(modelKey);
    
    ASSERT_NE(itMake, exifData.end());
    ASSERT_NE(itModel, exifData.end());
    
    EXPECT_EQ(itMake->toString(), "Canon");
    EXPECT_EQ(itModel->toString(), "EOS 5D Mark IV");
}

// Test ExifData empty
TEST_F(ExifdatumTest_731, ExifDataEmpty_731) {
    Exiv2::ExifData exifData;
    
    EXPECT_TRUE(exifData.empty());
    EXPECT_EQ(exifData.count(), 0u);
}

// Test ExifData erase
TEST_F(ExifdatumTest_731, ExifDataErase_731) {
    Exiv2::ExifData exifData;
    
    exifData["Exif.Image.Make"] = "Canon";
    EXPECT_EQ(exifData.count(), 1u);
    
    Exiv2::ExifKey key("Exif.Image.Make");
    auto it = exifData.findKey(key);
    ASSERT_NE(it, exifData.end());
    
    exifData.erase(it);
    EXPECT_EQ(exifData.count(), 0u);
    EXPECT_TRUE(exifData.empty());
}

// Test copy to buffer
TEST_F(ExifdatumTest_731, CopyToBuffer_731) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    
    uint16_t orientation = 1;
    datum = orientation;
    
    Exiv2::byte buf[16] = {};
    size_t copied = datum.copy(buf, Exiv2::littleEndian);
    
    EXPECT_GT(copied, 0u);
}

// Test self assignment
TEST_F(ExifdatumTest_731, SelfAssignment_731) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::AsciiValue val("Canon");
    Exiv2::Exifdatum datum(key, &val);
    
    datum = datum;
    
    EXPECT_EQ(datum.toString(), "Canon");
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
}

// Test idx method
TEST_F(ExifdatumTest_731, IdxMethod_731) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    
    // idx should return 0 by default
    EXPECT_EQ(datum.idx(), 0);
}

// Test empty string assignment
TEST_F(ExifdatumTest_731, EmptyStringAssignment_731) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::AsciiValue val("Canon");
    Exiv2::Exifdatum datum(key, &val);
    
    datum = std::string("");
    
    EXPECT_EQ(datum.toString(), "");
}

// Test overwrite value
TEST_F(ExifdatumTest_731, OverwriteValue_731) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::AsciiValue val("Canon");
    Exiv2::Exifdatum datum(key, &val);
    
    EXPECT_EQ(datum.toString(), "Canon");
    
    datum = std::string("Nikon");
    EXPECT_EQ(datum.toString(), "Nikon");
    
    datum = std::string("Sony");
    EXPECT_EQ(datum.toString(), "Sony");
}

// Test value() throws when no value is set
TEST_F(ExifdatumTest_731, ValueThrowsWhenEmpty_731) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    
    EXPECT_THROW(datum.value(), Exiv2::Error);
}

// Test ifdId
TEST_F(ExifdatumTest_731, IfdId_731) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    
    Exiv2::IfdId id = datum.ifdId();
    EXPECT_EQ(id, Exiv2::IfdId::ifd0Id);
}

// Test ifdName
TEST_F(ExifdatumTest_731, IfdName_731) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    
    const char* name = datum.ifdName();
    ASSERT_NE(name, nullptr);
}
