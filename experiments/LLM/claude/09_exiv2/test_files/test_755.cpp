#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/tags.hpp>
#include <exiv2/types.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

class ExifdatumTest_755 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test basic construction with a known ExifKey
TEST_F(ExifdatumTest_755, ConstructWithExifKey_755) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ("Exif.Image.Make", datum.key());
}

// Test familyName returns "Exif"
TEST_F(ExifdatumTest_755, FamilyNameIsExif_755) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_STREQ("Exif", datum.familyName());
}

// Test groupName returns the correct group
TEST_F(ExifdatumTest_755, GroupNameIsImage_755) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ("Image", datum.groupName());
}

// Test tagName returns the correct tag name
TEST_F(ExifdatumTest_755, TagNameIsMake_755) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ("Make", datum.tagName());
}

// Test tag returns the correct tag number
TEST_F(ExifdatumTest_755, TagNumberForMake_755) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    // Make tag is 0x010f
    EXPECT_EQ(0x010f, datum.tag());
}

// Test copy constructor
TEST_F(ExifdatumTest_755, CopyConstructor_755) {
    ExifKey key("Exif.Image.Model");
    Exifdatum datum1(key, nullptr);
    datum1 = std::string("TestCamera");

    Exifdatum datum2(datum1);
    EXPECT_EQ(datum1.key(), datum2.key());
    EXPECT_EQ(datum1.toString(), datum2.toString());
}

// Test copy assignment operator
TEST_F(ExifdatumTest_755, CopyAssignment_755) {
    ExifKey key1("Exif.Image.Make");
    Exifdatum datum1(key1, nullptr);
    datum1 = std::string("Canon");

    ExifKey key2("Exif.Image.Model");
    Exifdatum datum2(key2, nullptr);
    datum2 = datum1;

    EXPECT_EQ(datum1.key(), datum2.key());
    EXPECT_EQ(datum1.toString(), datum2.toString());
}

// Test assignment with string value
TEST_F(ExifdatumTest_755, AssignStringValue_755) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("Nikon");
    EXPECT_EQ("Nikon", datum.toString());
}

// Test assignment with uint16_t value
TEST_F(ExifdatumTest_755, AssignUint16Value_755) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    uint16_t val = 1;
    datum = val;
    EXPECT_EQ(1, datum.toInt64(0));
}

// Test assignment with uint32_t value
TEST_F(ExifdatumTest_755, AssignUint32Value_755) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    uint32_t val = 4000;
    datum = val;
    EXPECT_EQ(4000, datum.toInt64(0));
}

// Test assignment with int16_t value
TEST_F(ExifdatumTest_755, AssignInt16Value_755) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    int16_t val = -5;
    datum = val;
    EXPECT_EQ(-5, datum.toInt64(0));
}

// Test assignment with int32_t value
TEST_F(ExifdatumTest_755, AssignInt32Value_755) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    int32_t val = -100;
    datum = val;
    EXPECT_EQ(-100, datum.toInt64(0));
}

// Test assignment with Rational value
TEST_F(ExifdatumTest_755, AssignRationalValue_755) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    URational val(72, 1);
    datum = val;
    EXPECT_EQ(72, datum.toInt64(0));
}

// Test assignment with signed Rational value
TEST_F(ExifdatumTest_755, AssignSignedRationalValue_755) {
    ExifKey key("Exif.Photo.ExposureBiasValue");
    Exifdatum datum(key, nullptr);
    Rational val(-1, 3);
    datum = val;
    Rational result = datum.toRational(0);
    EXPECT_EQ(-1, result.first);
    EXPECT_EQ(3, result.second);
}

// Test setValue with string
TEST_F(ExifdatumTest_755, SetValueString_755) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    int rc = datum.setValue("TestMake");
    EXPECT_EQ(0, rc);
    EXPECT_EQ("TestMake", datum.toString());
}

// Test typeId when value is set
TEST_F(ExifdatumTest_755, TypeIdAfterStringAssignment_755) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("Canon");
    // Make is an Ascii type tag
    EXPECT_EQ(asciiString, datum.typeId());
}

// Test typeName after value is set
TEST_F(ExifdatumTest_755, TypeNameAfterAssignment_755) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("Canon");
    EXPECT_STREQ("Ascii", datum.typeName());
}

// Test typeSize
TEST_F(ExifdatumTest_755, TypeSizeForAscii_755) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("Canon");
    EXPECT_EQ(1u, datum.typeSize());
}

// Test count after setting a value
TEST_F(ExifdatumTest_755, CountAfterSettingValue_755) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("Canon");
    // "Canon" + null terminator = 6
    EXPECT_EQ(6u, datum.count());
}

// Test size after setting a value
TEST_F(ExifdatumTest_755, SizeAfterSettingValue_755) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("Canon");
    // "Canon\0" = 6 bytes
    EXPECT_EQ(6u, datum.size());
}

// Test that a datum with no value has invalidTypeId
TEST_F(ExifdatumTest_755, NoValueTypeIdIsInvalid_755) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(invalidTypeId, datum.typeId());
}

// Test toString with index
TEST_F(ExifdatumTest_755, ToStringWithIndex_755) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("TestBrand");
    std::string result = datum.toString(0);
    EXPECT_EQ("TestBrand", result);
}

// Test getValue returns a valid unique_ptr
TEST_F(ExifdatumTest_755, GetValueReturnsNonNull_755) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("Canon");
    auto val = datum.getValue();
    ASSERT_NE(nullptr, val.get());
    EXPECT_EQ("Canon", val->toString());
}

// Test value() reference
TEST_F(ExifdatumTest_755, ValueReferenceWorks_755) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("Sony");
    const Value& val = datum.value();
    EXPECT_EQ("Sony", val.toString());
}

// Test write to stream
TEST_F(ExifdatumTest_755, WriteToStream_755) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("Olympus");
    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test tagLabel returns a non-empty string for a known tag
TEST_F(ExifdatumTest_755, TagLabelNonEmpty_755) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test toFloat
TEST_F(ExifdatumTest_755, ToFloatConversion_755) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    URational val(72, 1);
    datum = val;
    EXPECT_FLOAT_EQ(72.0f, datum.toFloat(0));
}

// Test copy to buffer
TEST_F(ExifdatumTest_755, CopyToBuffer_755) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    uint16_t val = 1;
    datum = val;

    byte buf[64];
    std::memset(buf, 0, sizeof(buf));
    size_t sz = datum.copy(buf, littleEndian);
    EXPECT_GT(sz, 0u);
}

// Test setting value with a Value object
TEST_F(ExifdatumTest_755, AssignValueObject_755) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);

    AsciiValue val;
    val.read("Pentax");
    datum = val;

    EXPECT_EQ("Pentax", datum.toString());
    EXPECT_EQ(asciiString, datum.typeId());
}

// Test setValue with pointer to Value
TEST_F(ExifdatumTest_755, SetValueWithPointer_755) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);

    auto val = std::make_unique<AsciiValue>();
    val->read("Fuji");
    datum.setValue(val.get());

    EXPECT_EQ("Fuji", datum.toString());
}

// Test with Photo group key
TEST_F(ExifdatumTest_755, PhotoGroupKey_755) {
    ExifKey key("Exif.Photo.ExposureTime");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ("Photo", datum.groupName());
    EXPECT_EQ("ExposureTime", datum.tagName());
}

// Test sizeDataArea when no data area is set
TEST_F(ExifdatumTest_755, SizeDataAreaDefault_755) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("Test");
    EXPECT_EQ(0u, datum.sizeDataArea());
}

// Test dataArea when no data area is set
TEST_F(ExifdatumTest_755, DataAreaDefault_755) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("Test");
    DataBuf db = datum.dataArea();
    EXPECT_EQ(0u, db.size());
}

// Test typeSize for short type
TEST_F(ExifdatumTest_755, TypeSizeForShort_755) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    uint16_t val = 3;
    datum = val;
    EXPECT_EQ(2u, datum.typeSize());
}

// Test typeSize for long type
TEST_F(ExifdatumTest_755, TypeSizeForLong_755) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    uint32_t val = 1920;
    datum = val;
    EXPECT_EQ(4u, datum.typeSize());
}

// Test that idx() returns a value (typically 0 for new datum)
TEST_F(ExifdatumTest_755, IdxReturnsValue_755) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    int idx = datum.idx();
    EXPECT_GE(idx, 0);
}

// Test ifdName returns a non-null string
TEST_F(ExifdatumTest_755, IfdNameNonNull_755) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    const char* name = datum.ifdName();
    EXPECT_NE(nullptr, name);
}

// Test multiple assignment overwrites previous value
TEST_F(ExifdatumTest_755, MultipleAssignmentsOverwrite_755) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("First");
    EXPECT_EQ("First", datum.toString());

    datum = std::string("Second");
    EXPECT_EQ("Second", datum.toString());
}

// Test ExifData add and find workflow
TEST_F(ExifdatumTest_755, ExifDataAddAndFind_755) {
    ExifData exifData;
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("TestMaker");

    exifData.add(datum);

    auto it = exifData.findKey(key);
    ASSERT_NE(it, exifData.end());
    EXPECT_EQ("TestMaker", it->toString());
}

// Test ExifData empty and count
TEST_F(ExifdatumTest_755, ExifDataEmptyAndCount_755) {
    ExifData exifData;
    EXPECT_TRUE(exifData.empty());
    EXPECT_EQ(0u, exifData.count());

    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("Test");
    exifData.add(datum);

    EXPECT_FALSE(exifData.empty());
    EXPECT_EQ(1u, exifData.count());
}

// Test ExifData erase
TEST_F(ExifdatumTest_755, ExifDataErase_755) {
    ExifData exifData;
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("Test");
    exifData.add(datum);

    auto it = exifData.findKey(key);
    ASSERT_NE(it, exifData.end());
    exifData.erase(it);
    EXPECT_TRUE(exifData.empty());
}

// Test ExifData clear
TEST_F(ExifdatumTest_755, ExifDataClear_755) {
    ExifData exifData;

    ExifKey key1("Exif.Image.Make");
    Exifdatum datum1(key1, nullptr);
    datum1 = std::string("Brand1");
    exifData.add(datum1);

    ExifKey key2("Exif.Image.Model");
    Exifdatum datum2(key2, nullptr);
    datum2 = std::string("Model1");
    exifData.add(datum2);

    EXPECT_EQ(2u, exifData.count());
    exifData.clear();
    EXPECT_TRUE(exifData.empty());
}
