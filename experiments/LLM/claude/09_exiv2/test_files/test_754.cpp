#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/exifdata.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>
#include <exiv2/tags.hpp>
#include <string>
#include <cstdint>

using namespace Exiv2;

class ExifdatumTest_754 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test constructing Exifdatum with a known ExifKey
TEST_F(ExifdatumTest_754, ConstructWithExifKey_754) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    EXPECT_EQ("Exif.Image.Make", datum.key());
    EXPECT_EQ("Exif", std::string(datum.familyName()));
    EXPECT_EQ("Image", datum.groupName());
    EXPECT_EQ("Make", datum.tagName());
}

// Test copy constructor
TEST_F(ExifdatumTest_754, CopyConstructor_754) {
    ExifKey key("Exif.Image.Model");
    Exifdatum datum1(key);
    datum1 = std::string("TestCamera");

    Exifdatum datum2(datum1);
    EXPECT_EQ(datum1.key(), datum2.key());
    EXPECT_EQ(datum1.toString(), datum2.toString());
    EXPECT_EQ(datum1.tag(), datum2.tag());
}

// Test copy assignment operator
TEST_F(ExifdatumTest_754, CopyAssignment_754) {
    ExifKey key1("Exif.Image.Make");
    Exifdatum datum1(key1);
    datum1 = std::string("Canon");

    ExifKey key2("Exif.Image.Model");
    Exifdatum datum2(key2);
    datum2 = datum1;

    EXPECT_EQ(datum1.key(), datum2.key());
    EXPECT_EQ(datum1.toString(), datum2.toString());
}

// Test assignment with string value
TEST_F(ExifdatumTest_754, AssignStringValue_754) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum = std::string("Nikon");
    EXPECT_EQ("Nikon", datum.toString());
}

// Test assignment with uint16_t value
TEST_F(ExifdatumTest_754, AssignUint16Value_754) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    uint16_t val = 1;
    datum = val;
    EXPECT_EQ(1, datum.toInt64());
}

// Test assignment with uint32_t value
TEST_F(ExifdatumTest_754, AssignUint32Value_754) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key);
    uint32_t val = 4000;
    datum = val;
    EXPECT_EQ(4000, datum.toInt64());
}

// Test assignment with int16_t value
TEST_F(ExifdatumTest_754, AssignInt16Value_754) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    int16_t val = -5;
    datum = val;
    EXPECT_EQ(-5, datum.toInt64());
}

// Test assignment with int32_t value
TEST_F(ExifdatumTest_754, AssignInt32Value_754) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key);
    int32_t val = -100;
    datum = val;
    EXPECT_EQ(-100, datum.toInt64());
}

// Test assignment with URational value
TEST_F(ExifdatumTest_754, AssignURationalValue_754) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key);
    URational val(72, 1);
    datum = val;
    EXPECT_EQ(72, datum.toInt64());
    Rational r = datum.toRational();
    EXPECT_EQ(72u, static_cast<uint32_t>(r.first));
    EXPECT_EQ(1u, static_cast<uint32_t>(r.second));
}

// Test assignment with Rational value
TEST_F(ExifdatumTest_754, AssignRationalValue_754) {
    ExifKey key("Exif.Photo.ExposureBiasValue");
    Exifdatum datum(key);
    Rational val(-1, 3);
    datum = val;
    Rational r = datum.toRational();
    EXPECT_EQ(-1, r.first);
    EXPECT_EQ(3, r.second);
}

// Test assignment with Value object
TEST_F(ExifdatumTest_754, AssignValueObject_754) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    AsciiValue ascVal;
    ascVal.read("SonyTest");
    datum = static_cast<const Value&>(ascVal);
    EXPECT_EQ("SonyTest", datum.toString());
}

// Test key() method
TEST_F(ExifdatumTest_754, KeyMethod_754) {
    ExifKey key("Exif.Photo.DateTimeOriginal");
    Exifdatum datum(key);
    EXPECT_EQ("Exif.Photo.DateTimeOriginal", datum.key());
}

// Test familyName() method
TEST_F(ExifdatumTest_754, FamilyNameMethod_754) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    EXPECT_STREQ("Exif", datum.familyName());
}

// Test groupName() method
TEST_F(ExifdatumTest_754, GroupNameMethod_754) {
    ExifKey key("Exif.Photo.ISOSpeedRatings");
    Exifdatum datum(key);
    EXPECT_EQ("Photo", datum.groupName());
}

// Test tagName() method
TEST_F(ExifdatumTest_754, TagNameMethod_754) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    EXPECT_EQ("Make", datum.tagName());
}

// Test tag() method
TEST_F(ExifdatumTest_754, TagMethod_754) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    // Make tag is 0x010f
    EXPECT_EQ(0x010f, datum.tag());
}

// Test typeName() method
TEST_F(ExifdatumTest_754, TypeNameMethod_754) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum = std::string("TestMake");
    const char* tn = datum.typeName();
    EXPECT_NE(nullptr, tn);
}

// Test typeId() method
TEST_F(ExifdatumTest_754, TypeIdMethod_754) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum = std::string("TestMake");
    TypeId tid = datum.typeId();
    EXPECT_EQ(asciiString, tid);
}

// Test count() returns correct number of values
TEST_F(ExifdatumTest_754, CountMethod_754) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum = std::string("Canon");
    EXPECT_GT(datum.count(), 0u);
}

// Test size() returns correct size
TEST_F(ExifdatumTest_754, SizeMethod_754) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum = std::string("Canon");
    EXPECT_GT(datum.size(), 0u);
}

// Test toString() method
TEST_F(ExifdatumTest_754, ToStringMethod_754) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum = std::string("Pentax");
    EXPECT_EQ("Pentax", datum.toString());
}

// Test toString(n) with index
TEST_F(ExifdatumTest_754, ToStringWithIndex_754) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum = std::string("Olympus");
    std::string s = datum.toString(0);
    EXPECT_FALSE(s.empty());
}

// Test toInt64() method
TEST_F(ExifdatumTest_754, ToInt64Method_754) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    uint16_t val = 6;
    datum = val;
    EXPECT_EQ(6, datum.toInt64());
}

// Test toFloat() method
TEST_F(ExifdatumTest_754, ToFloatMethod_754) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key);
    URational val(72, 1);
    datum = val;
    EXPECT_FLOAT_EQ(72.0f, datum.toFloat());
}

// Test toRational() method
TEST_F(ExifdatumTest_754, ToRationalMethod_754) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key);
    URational val(300, 1);
    datum = val;
    Rational r = datum.toRational();
    EXPECT_EQ(300, r.first);
    EXPECT_EQ(1, r.second);
}

// Test getValue() returns a valid unique_ptr
TEST_F(ExifdatumTest_754, GetValueMethod_754) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum = std::string("Fuji");
    auto val = datum.getValue();
    EXPECT_NE(nullptr, val.get());
    EXPECT_EQ("Fuji", val->toString());
}

// Test value() reference method
TEST_F(ExifdatumTest_754, ValueReferenceMethod_754) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum = std::string("Leica");
    const Value& val = datum.value();
    EXPECT_EQ("Leica", val.toString());
}

// Test setValue with string
TEST_F(ExifdatumTest_754, SetValueString_754) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    int result = datum.setValue("Sigma");
    EXPECT_EQ(0, result);
    EXPECT_EQ("Sigma", datum.toString());
}

// Test setValue with Value pointer
TEST_F(ExifdatumTest_754, SetValuePointer_754) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    AsciiValue ascVal;
    ascVal.read("Panasonic");
    datum.setValue(&ascVal);
    EXPECT_EQ("Panasonic", datum.toString());
}

// Test ifdId() method
TEST_F(ExifdatumTest_754, IfdIdMethod_754) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    IfdId id = datum.ifdId();
    EXPECT_EQ(IfdId::ifd0Id, id);
}

// Test ifdName() method
TEST_F(ExifdatumTest_754, IfdNameMethod_754) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    const char* name = datum.ifdName();
    EXPECT_NE(nullptr, name);
}

// Test with Exif.Photo group key
TEST_F(ExifdatumTest_754, PhotoGroupKey_754) {
    ExifKey key("Exif.Photo.ExposureTime");
    Exifdatum datum(key);
    EXPECT_EQ("Photo", datum.groupName());
    EXPECT_EQ("ExposureTime", datum.tagName());
}

// Test typeSize() method
TEST_F(ExifdatumTest_754, TypeSizeMethod_754) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    uint16_t val = 1;
    datum = val;
    // uint16 (short) should have typeSize of 2
    EXPECT_EQ(2u, datum.typeSize());
}

// Test copy() method
TEST_F(ExifdatumTest_754, CopyMethod_754) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    uint16_t val = 1;
    datum = val;
    byte buf[16] = {};
    size_t copied = datum.copy(buf, littleEndian);
    EXPECT_GT(copied, 0u);
}

// Test sizeDataArea() when no data area is set
TEST_F(ExifdatumTest_754, SizeDataAreaNoData_754) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum = std::string("Test");
    EXPECT_EQ(0u, datum.sizeDataArea());
}

// Test dataArea() when no data area
TEST_F(ExifdatumTest_754, DataAreaNoData_754) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum = std::string("Test");
    DataBuf db = datum.dataArea();
    EXPECT_EQ(0u, db.size());
}

// Test write() method to ostream
TEST_F(ExifdatumTest_754, WriteMethod_754) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum = std::string("TestWrite");
    std::ostringstream os;
    datum.write(os, nullptr);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

// Test datum without value set - getValue should still work
TEST_F(ExifdatumTest_754, NoValueSet_754) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    EXPECT_EQ(0u, datum.count());
}

// Test tagLabel() returns non-empty for well-known tags
TEST_F(ExifdatumTest_754, TagLabelMethod_754) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test idx() method
TEST_F(ExifdatumTest_754, IdxMethod_754) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    int idx = datum.idx();
    // idx is a metadata index, just check it doesn't crash
    (void)idx;
}

// Test multiple assignments overwrite previous value
TEST_F(ExifdatumTest_754, MultipleAssignmentsOverwrite_754) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum = std::string("First");
    EXPECT_EQ("First", datum.toString());
    datum = std::string("Second");
    EXPECT_EQ("Second", datum.toString());
}

// Test uint32 type size
TEST_F(ExifdatumTest_754, Uint32TypeSize_754) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key);
    uint32_t val = 1920;
    datum = val;
    EXPECT_EQ(4u, datum.typeSize());
}

// Test Rational typeId
TEST_F(ExifdatumTest_754, RationalTypeId_754) {
    ExifKey key("Exif.Photo.ExposureBiasValue");
    Exifdatum datum(key);
    Rational val(1, 3);
    datum = val;
    EXPECT_EQ(signedRational, datum.typeId());
}
