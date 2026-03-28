#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>
#include <exiv2/tags.hpp>
#include <exiv2/types.hpp>
#include <memory>
#include <string>
#include <sstream>

using namespace Exiv2;

class ExifdatumTest_760 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test construction with a known ExifKey
TEST_F(ExifdatumTest_760, ConstructWithExifKey_760) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
    EXPECT_EQ(datum.familyName(), std::string("Exif"));
    EXPECT_EQ(datum.groupName(), "Image");
    EXPECT_EQ(datum.tagName(), "Make");
}

// Test copy constructor
TEST_F(ExifdatumTest_760, CopyConstructor_760) {
    ExifKey key("Exif.Image.Model");
    Exifdatum datum(key);
    datum = std::string("TestCamera");

    Exifdatum copy(datum);
    EXPECT_EQ(copy.key(), "Exif.Image.Model");
    EXPECT_EQ(copy.toString(), "TestCamera");
}

// Test assignment operator (Exifdatum to Exifdatum)
TEST_F(ExifdatumTest_760, AssignmentOperator_760) {
    ExifKey key1("Exif.Image.Make");
    Exifdatum datum1(key1);
    datum1 = std::string("Canon");

    ExifKey key2("Exif.Image.Model");
    Exifdatum datum2(key2);
    datum2 = datum1;

    EXPECT_EQ(datum2.toString(), "Canon");
}

// Test setting and getting a string value
TEST_F(ExifdatumTest_760, SetStringValue_760) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum = std::string("Nikon");

    EXPECT_EQ(datum.toString(), "Nikon");
    EXPECT_GT(datum.count(), 0u);
    EXPECT_GT(datum.size(), 0u);
}

// Test setting uint16_t value
TEST_F(ExifdatumTest_760, SetUint16Value_760) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    uint16_t val = 1;
    datum = val;

    EXPECT_EQ(datum.toInt64(0), 1);
    EXPECT_EQ(datum.typeId(), unsignedShort);
}

// Test setting uint32_t value
TEST_F(ExifdatumTest_760, SetUint32Value_760) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key);
    uint32_t val = 4000;
    datum = val;

    EXPECT_EQ(datum.toInt64(0), 4000);
    EXPECT_EQ(datum.typeId(), unsignedLong);
}

// Test setting int16_t value
TEST_F(ExifdatumTest_760, SetInt16Value_760) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    int16_t val = -5;
    datum = val;

    EXPECT_EQ(datum.toInt64(0), -5);
    EXPECT_EQ(datum.typeId(), signedShort);
}

// Test setting int32_t value
TEST_F(ExifdatumTest_760, SetInt32Value_760) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key);
    int32_t val = -100;
    datum = val;

    EXPECT_EQ(datum.toInt64(0), -100);
    EXPECT_EQ(datum.typeId(), signedLong);
}

// Test setting URational value
TEST_F(ExifdatumTest_760, SetURationalValue_760) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key);
    URational val(72, 1);
    datum = val;

    EXPECT_EQ(datum.toInt64(0), 72);
    Rational r = datum.toRational(0);
    EXPECT_EQ(datum.typeId(), unsignedRational);
}

// Test setting Rational value
TEST_F(ExifdatumTest_760, SetRationalValue_760) {
    ExifKey key("Exif.Photo.ExposureBiasValue");
    Exifdatum datum(key);
    Rational val(-1, 3);
    datum = val;

    Rational r = datum.toRational(0);
    EXPECT_EQ(r.first, -1);
    EXPECT_EQ(r.second, 3);
    EXPECT_EQ(datum.typeId(), signedRational);
}

// Test toInt64 with no value set returns -1
TEST_F(ExifdatumTest_760, ToInt64NoValueReturnsNegOne_760) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);

    EXPECT_EQ(datum.toInt64(0), -1);
}

// Test toFloat with no value set
TEST_F(ExifdatumTest_760, ToFloatNoValue_760) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);

    // When no value is set, toFloat should return -1.0f (similar to toInt64)
    float result = datum.toFloat(0);
    EXPECT_FLOAT_EQ(result, -1.0f);
}

// Test tag() returns correct tag number
TEST_F(ExifdatumTest_760, TagReturnsCorrectValue_760) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);

    // Tag for Make is 0x010f
    EXPECT_EQ(datum.tag(), 0x010f);
}

// Test familyName returns "Exif"
TEST_F(ExifdatumTest_760, FamilyNameIsExif_760) {
    ExifKey key("Exif.Image.Model");
    Exifdatum datum(key);

    EXPECT_STREQ(datum.familyName(), "Exif");
}

// Test toString with index
TEST_F(ExifdatumTest_760, ToStringWithIndex_760) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum = std::string("Sony");

    std::string s = datum.toString(0);
    EXPECT_EQ(s, "Sony");
}

// Test setValue with string (returns int)
TEST_F(ExifdatumTest_760, SetValueString_760) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);

    int result = datum.setValue("TestValue");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "TestValue");
}

// Test count with no value
TEST_F(ExifdatumTest_760, CountNoValue_760) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);

    EXPECT_EQ(datum.count(), 0u);
}

// Test size with no value
TEST_F(ExifdatumTest_760, SizeNoValue_760) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);

    EXPECT_EQ(datum.size(), 0u);
}

// Test getValue when value is set
TEST_F(ExifdatumTest_760, GetValueWhenSet_760) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum = std::string("Fuji");

    auto val = datum.getValue();
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->toString(), "Fuji");
}

// Test getValue when no value is set
TEST_F(ExifdatumTest_760, GetValueWhenNotSet_760) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);

    auto val = datum.getValue();
    EXPECT_EQ(val, nullptr);
}

// Test setting value via Value object assignment
TEST_F(ExifdatumTest_760, SetValueViaValueObject_760) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);

    auto value = Value::create(unsignedShort);
    value->read("3");
    datum = *value;

    EXPECT_EQ(datum.toInt64(0), 3);
    EXPECT_EQ(datum.typeId(), unsignedShort);
}

// Test setValue with Value pointer
TEST_F(ExifdatumTest_760, SetValueWithPointer_760) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);

    auto value = Value::create(unsignedShort);
    value->read("6");
    datum.setValue(value.get());

    EXPECT_EQ(datum.toInt64(0), 6);
}

// Test setValue with nullptr
TEST_F(ExifdatumTest_760, SetValueWithNullptr_760) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    datum = uint16_t(3);

    datum.setValue(nullptr);

    // After setting nullptr, getValue should return null and toInt64 should return -1
    EXPECT_EQ(datum.toInt64(0), -1);
    EXPECT_EQ(datum.count(), 0u);
}

// Test write to ostream
TEST_F(ExifdatumTest_760, WriteToOstream_760) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum = std::string("Pentax");

    std::ostringstream os;
    datum.write(os, nullptr);

    EXPECT_FALSE(os.str().empty());
}

// Test typeId when no value set
TEST_F(ExifdatumTest_760, TypeIdNoValue_760) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);

    // When no value is set, typeId should return invalidTypeId or the default
    TypeId tid = datum.typeId();
    EXPECT_EQ(tid, invalidTypeId);
}

// Test typeName with value set
TEST_F(ExifdatumTest_760, TypeNameWithValue_760) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    datum = uint16_t(1);

    const char* tn = datum.typeName();
    ASSERT_NE(tn, nullptr);
    EXPECT_EQ(std::string(tn), "SHORT");
}

// Test sizeDataArea with no data area
TEST_F(ExifdatumTest_760, SizeDataAreaNoData_760) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum = std::string("Test");

    EXPECT_EQ(datum.sizeDataArea(), 0u);
}

// Test copy to buffer
TEST_F(ExifdatumTest_760, CopyToBuffer_760) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    datum = uint16_t(8);

    byte buf[4] = {0};
    size_t sz = datum.copy(buf, littleEndian);
    EXPECT_GT(sz, 0u);
}

// Test ifdId
TEST_F(ExifdatumTest_760, IfdId_760) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);

    IfdId id = datum.ifdId();
    EXPECT_EQ(id, IfdId::ifd0Id);
}

// Test tagLabel returns non-empty string for known tag
TEST_F(ExifdatumTest_760, TagLabelNonEmpty_760) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);

    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test toRational with no value
TEST_F(ExifdatumTest_760, ToRationalNoValue_760) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);

    Rational r = datum.toRational(0);
    EXPECT_EQ(r.first, -1);
    EXPECT_EQ(r.second, 1);
}

// Test multiple values (e.g., BitsPerSample can have multiple components)
TEST_F(ExifdatumTest_760, MultipleComponentValues_760) {
    ExifKey key("Exif.Image.BitsPerSample");
    Exifdatum datum(key);

    int result = datum.setValue("8 8 8");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.count(), 3u);
    EXPECT_EQ(datum.toInt64(0), 8);
    EXPECT_EQ(datum.toInt64(1), 8);
    EXPECT_EQ(datum.toInt64(2), 8);
}

// Test idx() default value
TEST_F(ExifdatumTest_760, IdxDefault_760) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);

    int idx = datum.idx();
    EXPECT_EQ(idx, 0);
}

// Test ExifData container basic operations
TEST_F(ExifdatumTest_760, ExifDataBasicOps_760) {
    ExifData exifData;
    EXPECT_TRUE(exifData.empty());
    EXPECT_EQ(exifData.count(), 0u);

    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum = std::string("TestMake");

    exifData.add(datum);
    EXPECT_FALSE(exifData.empty());
    EXPECT_EQ(exifData.count(), 1u);
}

// Test ExifData findKey
TEST_F(ExifdatumTest_760, ExifDataFindKey_760) {
    ExifData exifData;
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum = std::string("CanonTest");
    exifData.add(datum);

    auto it = exifData.findKey(ExifKey("Exif.Image.Make"));
    ASSERT_NE(it, exifData.end());
    EXPECT_EQ(it->toString(), "CanonTest");

    auto it2 = exifData.findKey(ExifKey("Exif.Image.Model"));
    EXPECT_EQ(it2, exifData.end());
}

// Test ExifData erase
TEST_F(ExifdatumTest_760, ExifDataErase_760) {
    ExifData exifData;
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum = std::string("TestBrand");
    exifData.add(datum);

    EXPECT_EQ(exifData.count(), 1u);

    auto it = exifData.begin();
    exifData.erase(it);
    EXPECT_TRUE(exifData.empty());
}

// Test ExifData clear
TEST_F(ExifdatumTest_760, ExifDataClear_760) {
    ExifData exifData;
    ExifKey key1("Exif.Image.Make");
    Exifdatum datum1(key1);
    datum1 = std::string("Brand");
    exifData.add(datum1);

    ExifKey key2("Exif.Image.Model");
    Exifdatum datum2(key2);
    datum2 = std::string("Camera");
    exifData.add(datum2);

    EXPECT_EQ(exifData.count(), 2u);

    exifData.clear();
    EXPECT_TRUE(exifData.empty());
    EXPECT_EQ(exifData.count(), 0u);
}

// Test operator[] on ExifData
TEST_F(ExifdatumTest_760, ExifDataSubscriptOperator_760) {
    ExifData exifData;
    exifData["Exif.Image.Make"] = "TestBrand";

    auto it = exifData.findKey(ExifKey("Exif.Image.Make"));
    ASSERT_NE(it, exifData.end());
    EXPECT_EQ(it->toString(), "TestBrand");
}

// Test typeSize for unsigned short
TEST_F(ExifdatumTest_760, TypeSizeUnsignedShort_760) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    datum = uint16_t(1);

    EXPECT_EQ(datum.typeSize(), 2u);
}

// Test typeSize for unsigned long
TEST_F(ExifdatumTest_760, TypeSizeUnsignedLong_760) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key);
    datum = uint32_t(100);

    EXPECT_EQ(datum.typeSize(), 4u);
}

// Test dataArea when no data area set
TEST_F(ExifdatumTest_760, DataAreaEmpty_760) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum = std::string("Test");

    DataBuf db = datum.dataArea();
    EXPECT_EQ(db.size(), 0u);
}
