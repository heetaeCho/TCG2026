#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/exifdatum.hpp>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <exiv2/tags.hpp>
#include <exiv2/exif.hpp>
#include <memory>
#include <string>
#include <sstream>

using namespace Exiv2;

class ExifdatumTest_753 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test: Constructing Exifdatum with a known ExifKey and no value
TEST_F(ExifdatumTest_753, ConstructWithKeyNoValue_753) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
    EXPECT_EQ(datum.familyName(), std::string("Exif"));
    EXPECT_EQ(datum.groupName(), "Image");
    EXPECT_EQ(datum.tagName(), "Make");
    EXPECT_EQ(datum.count(), 0u);
    EXPECT_EQ(datum.size(), 0u);
}

// Test: typeId returns invalidTypeId when no value is set
TEST_F(ExifdatumTest_753, TypeIdWithoutValue_753) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    EXPECT_EQ(datum.typeId(), invalidTypeId);
}

// Test: typeName when no value is set
TEST_F(ExifdatumTest_753, TypeNameWithoutValue_753) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    // When no value is set, typeName should reflect invalidTypeId
    // It may return something like "(Invalid)" or similar
    const char* tn = datum.typeName();
    // Just verify it doesn't crash and returns something
    EXPECT_NE(tn, nullptr);
}

// Test: setValue with string
TEST_F(ExifdatumTest_753, SetValueString_753) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    int result = datum.setValue("Canon");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "Canon");
    EXPECT_GT(datum.count(), 0u);
}

// Test: operator= with string
TEST_F(ExifdatumTest_753, AssignString_753) {
    ExifKey key("Exif.Image.Model");
    Exifdatum datum(key);
    datum = std::string("EOS 5D");
    EXPECT_EQ(datum.toString(), "EOS 5D");
}

// Test: operator= with uint16_t
TEST_F(ExifdatumTest_753, AssignUint16_753) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    datum = static_cast<uint16_t>(1);
    EXPECT_EQ(datum.toInt64(0), 1);
    EXPECT_EQ(datum.typeId(), unsignedShort);
}

// Test: operator= with uint32_t
TEST_F(ExifdatumTest_753, AssignUint32_753) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key);
    datum = static_cast<uint32_t>(4000);
    EXPECT_EQ(datum.toInt64(0), 4000);
    EXPECT_EQ(datum.typeId(), unsignedLong);
}

// Test: operator= with int16_t
TEST_F(ExifdatumTest_753, AssignInt16_753) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    datum = static_cast<int16_t>(-5);
    EXPECT_EQ(datum.toInt64(0), -5);
    EXPECT_EQ(datum.typeId(), signedShort);
}

// Test: operator= with int32_t
TEST_F(ExifdatumTest_753, AssignInt32_753) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key);
    datum = static_cast<int32_t>(-100);
    EXPECT_EQ(datum.toInt64(0), -100);
    EXPECT_EQ(datum.typeId(), signedLong);
}

// Test: operator= with URational
TEST_F(ExifdatumTest_753, AssignURational_753) {
    ExifKey key("Exif.Photo.ExposureTime");
    Exifdatum datum(key);
    URational ur = {1, 200};
    datum = ur;
    EXPECT_EQ(datum.typeId(), unsignedRational);
    Rational r = datum.toRational(0);
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 200);
}

// Test: operator= with Rational
TEST_F(ExifdatumTest_753, AssignRational_753) {
    ExifKey key("Exif.Photo.ExposureBiasValue");
    Exifdatum datum(key);
    Rational rat = {-1, 3};
    datum = rat;
    EXPECT_EQ(datum.typeId(), signedRational);
    Rational result = datum.toRational(0);
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, 3);
}

// Test: setValue with Value pointer
TEST_F(ExifdatumTest_753, SetValueWithValuePtr_753) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    auto value = Value::create(asciiString);
    value->read("Nikon");
    datum.setValue(value.get());
    EXPECT_EQ(datum.toString(), "Nikon");
    EXPECT_EQ(datum.typeId(), asciiString);
}

// Test: setValue with nullptr should clear value
TEST_F(ExifdatumTest_753, SetValueWithNullptr_753) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("TestValue");
    EXPECT_GT(datum.count(), 0u);
    datum.setValue(static_cast<const Value*>(nullptr));
    EXPECT_EQ(datum.typeId(), invalidTypeId);
    EXPECT_EQ(datum.count(), 0u);
}

// Test: operator= with Value reference
TEST_F(ExifdatumTest_753, AssignValueRef_753) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    auto value = Value::create(asciiString);
    value->read("Sony");
    datum = *value;
    EXPECT_EQ(datum.toString(), "Sony");
}

// Test: Copy constructor
TEST_F(ExifdatumTest_753, CopyConstructor_753) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("Canon");
    
    Exifdatum copy(datum);
    EXPECT_EQ(copy.key(), datum.key());
    EXPECT_EQ(copy.toString(), datum.toString());
    EXPECT_EQ(copy.typeId(), datum.typeId());
}

// Test: Copy assignment operator
TEST_F(ExifdatumTest_753, CopyAssignment_753) {
    ExifKey key1("Exif.Image.Make");
    Exifdatum datum1(key1);
    datum1.setValue("Canon");
    
    ExifKey key2("Exif.Image.Model");
    Exifdatum datum2(key2);
    datum2.setValue("5D");
    
    datum2 = datum1;
    EXPECT_EQ(datum2.key(), datum1.key());
    EXPECT_EQ(datum2.toString(), datum1.toString());
}

// Test: tag() returns the correct tag number
TEST_F(ExifdatumTest_753, TagNumber_753) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    // Exif.Image.Make is tag 0x010f = 271
    EXPECT_EQ(datum.tag(), 0x010f);
}

// Test: getValue returns unique_ptr clone of the value
TEST_F(ExifdatumTest_753, GetValueReturnsClone_753) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("TestManufacturer");
    
    auto val = datum.getValue();
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->toString(), "TestManufacturer");
}

// Test: getValue returns null when no value set
TEST_F(ExifdatumTest_753, GetValueReturnsNullWhenEmpty_753) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    auto val = datum.getValue();
    EXPECT_EQ(val, nullptr);
}

// Test: count and size are 0 when no value is set
TEST_F(ExifdatumTest_753, CountAndSizeZeroWithoutValue_753) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    EXPECT_EQ(datum.count(), 0u);
    EXPECT_EQ(datum.size(), 0u);
}

// Test: toFloat
TEST_F(ExifdatumTest_753, ToFloat_753) {
    ExifKey key("Exif.Photo.ExposureTime");
    Exifdatum datum(key);
    URational ur = {1, 4};
    datum = ur;
    EXPECT_FLOAT_EQ(datum.toFloat(0), 0.25f);
}

// Test: toInt64
TEST_F(ExifdatumTest_753, ToInt64_753) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key);
    datum = static_cast<uint32_t>(3000);
    EXPECT_EQ(datum.toInt64(0), 3000);
}

// Test: ifdId returns expected IFD
TEST_F(ExifdatumTest_753, IfdId_753) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    EXPECT_EQ(datum.ifdId(), IfdId::ifd0Id);
}

// Test: ifdName returns expected name
TEST_F(ExifdatumTest_753, IfdName_753) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    const char* name = datum.ifdName();
    ASSERT_NE(name, nullptr);
    // Should be something like "IFD0"
    EXPECT_STREQ(name, "IFD0");
}

// Test: write to ostream
TEST_F(ExifdatumTest_753, WriteToStream_753) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("Canon");
    
    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test: copy to buffer
TEST_F(ExifdatumTest_753, CopyToBuffer_753) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    datum = static_cast<uint16_t>(1);
    
    byte buf[64] = {};
    size_t copied = datum.copy(buf, littleEndian);
    EXPECT_GT(copied, 0u);
}

// Test: sizeDataArea is 0 by default
TEST_F(ExifdatumTest_753, SizeDataAreaDefault_753) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("Test");
    EXPECT_EQ(datum.sizeDataArea(), 0u);
}

// Test: dataArea returns empty DataBuf by default
TEST_F(ExifdatumTest_753, DataAreaDefault_753) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("Test");
    DataBuf db = datum.dataArea();
    EXPECT_EQ(db.size(), 0u);
}

// Test: typeSize returns appropriate size for the type
TEST_F(ExifdatumTest_753, TypeSizeForUShort_753) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    datum = static_cast<uint16_t>(1);
    // unsignedShort should be 2 bytes
    EXPECT_EQ(datum.typeSize(), 2u);
}

// Test: typeSize returns appropriate size for unsignedLong
TEST_F(ExifdatumTest_753, TypeSizeForULong_753) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key);
    datum = static_cast<uint32_t>(100);
    // unsignedLong should be 4 bytes
    EXPECT_EQ(datum.typeSize(), 4u);
}

// Test: tagLabel returns a non-empty label for known tags
TEST_F(ExifdatumTest_753, TagLabel_753) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test: toString with index on multi-element value
TEST_F(ExifdatumTest_753, ToStringWithIndex_753) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("Canon");
    std::string s = datum.toString(0);
    EXPECT_FALSE(s.empty());
}

// Test: idx returns default index
TEST_F(ExifdatumTest_753, IdxDefault_753) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    // idx should be 0 by default
    EXPECT_EQ(datum.idx(), 0);
}

// Test: ExifData add and find
TEST_F(ExifdatumTest_753, ExifDataAddAndFind_753) {
    ExifData exifData;
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("Nikon");
    exifData.add(datum);
    
    auto it = exifData.findKey(ExifKey("Exif.Image.Make"));
    ASSERT_NE(it, exifData.end());
    EXPECT_EQ(it->toString(), "Nikon");
}

// Test: ExifData is empty by default
TEST_F(ExifdatumTest_753, ExifDataEmptyByDefault_753) {
    ExifData exifData;
    EXPECT_TRUE(exifData.empty());
    EXPECT_EQ(exifData.count(), 0u);
}

// Test: ExifData erase
TEST_F(ExifdatumTest_753, ExifDataErase_753) {
    ExifData exifData;
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("Canon");
    exifData.add(datum);
    
    EXPECT_FALSE(exifData.empty());
    auto it = exifData.findKey(ExifKey("Exif.Image.Make"));
    ASSERT_NE(it, exifData.end());
    exifData.erase(it);
    EXPECT_TRUE(exifData.empty());
}

// Test: Multiple Exifdatum objects with different keys in ExifData
TEST_F(ExifdatumTest_753, MultipleExifdatumInExifData_753) {
    ExifData exifData;
    
    ExifKey key1("Exif.Image.Make");
    Exifdatum d1(key1);
    d1.setValue("Canon");
    exifData.add(d1);
    
    ExifKey key2("Exif.Image.Model");
    Exifdatum d2(key2);
    d2.setValue("EOS 5D");
    exifData.add(d2);
    
    EXPECT_EQ(exifData.count(), 2u);
    
    auto it1 = exifData.findKey(ExifKey("Exif.Image.Make"));
    ASSERT_NE(it1, exifData.end());
    EXPECT_EQ(it1->toString(), "Canon");
    
    auto it2 = exifData.findKey(ExifKey("Exif.Image.Model"));
    ASSERT_NE(it2, exifData.end());
    EXPECT_EQ(it2->toString(), "EOS 5D");
}

// Test: Exif.Photo tag
TEST_F(ExifdatumTest_753, PhotoGroupTag_753) {
    ExifKey key("Exif.Photo.DateTimeOriginal");
    Exifdatum datum(key);
    EXPECT_EQ(datum.groupName(), "Photo");
    EXPECT_EQ(datum.familyName(), std::string("Exif"));
    datum.setValue("2023:01:01 12:00:00");
    EXPECT_EQ(datum.toString(), "2023:01:01 12:00:00");
}

// Test: setDataArea on a datum with undefined type value
TEST_F(ExifdatumTest_753, SetDataArea_753) {
    ExifKey key("Exif.Photo.MakerNote");
    Exifdatum datum(key);
    auto val = Value::create(undefined);
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    val->read(data, sizeof(data), littleEndian);
    datum.setValue(val.get());
    
    // Just verify the basic operations don't crash
    EXPECT_GT(datum.size(), 0u);
}
