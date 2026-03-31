#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/tags.hpp>
#include <exiv2/value.hpp>
#include <exiv2/exiv2.hpp>
#include <string>
#include <memory>

using namespace Exiv2;

class ExifdatumTest_730 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test construction with ExifKey and null value
TEST_F(ExifdatumTest_730, ConstructWithKeyAndNullValue_730) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);

    EXPECT_EQ("Exif.Image.Make", datum.key());
    EXPECT_EQ("Exif", std::string(datum.familyName()));
    EXPECT_EQ("Image", datum.groupName());
    EXPECT_EQ("Make", datum.tagName());
}

// Test construction with ExifKey and a value
TEST_F(ExifdatumTest_730, ConstructWithKeyAndValue_730) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    Exifdatum datum(key, &val);

    EXPECT_EQ("Exif.Image.Make", datum.key());
    EXPECT_EQ("Canon", datum.toString());
    EXPECT_EQ(asciiString, datum.typeId());
}

// Test copy construction
TEST_F(ExifdatumTest_730, CopyConstruction_730) {
    ExifKey key("Exif.Image.Model");
    AsciiValue val;
    val.read("Nikon");
    Exifdatum original(key, &val);

    Exifdatum copy(original);

    EXPECT_EQ(original.key(), copy.key());
    EXPECT_EQ(original.toString(), copy.toString());
    EXPECT_EQ(original.tag(), copy.tag());
    EXPECT_EQ(original.typeId(), copy.typeId());
}

// Test copy assignment operator
TEST_F(ExifdatumTest_730, CopyAssignment_730) {
    ExifKey key1("Exif.Image.Make");
    AsciiValue val1;
    val1.read("Canon");
    Exifdatum datum1(key1, &val1);

    ExifKey key2("Exif.Image.Model");
    AsciiValue val2;
    val2.read("EOS");
    Exifdatum datum2(key2, &val2);

    datum2 = datum1;

    EXPECT_EQ("Exif.Image.Make", datum2.key());
    EXPECT_EQ("Canon", datum2.toString());
}

// Test self-assignment
TEST_F(ExifdatumTest_730, SelfAssignment_730) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Sony");
    Exifdatum datum(key, &val);

    datum = datum;

    EXPECT_EQ("Exif.Image.Make", datum.key());
    EXPECT_EQ("Sony", datum.toString());
}

// Test assignment from string
TEST_F(ExifdatumTest_730, AssignFromString_730) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    Exifdatum datum(key, &val);

    datum = std::string("Nikon");

    EXPECT_EQ("Nikon", datum.toString());
}

// Test assignment from uint16_t
TEST_F(ExifdatumTest_730, AssignFromUint16_730) {
    ExifKey key("Exif.Image.Orientation");
    auto val = Value::create(unsignedShort);
    val->read("1");
    Exifdatum datum(key, val.get());

    uint16_t newVal = 6;
    datum = newVal;

    EXPECT_EQ(6, datum.toInt64());
}

// Test assignment from uint32_t
TEST_F(ExifdatumTest_730, AssignFromUint32_730) {
    ExifKey key("Exif.Image.ImageWidth");
    auto val = Value::create(unsignedLong);
    val->read("100");
    Exifdatum datum(key, val.get());

    uint32_t newVal = 1920;
    datum = newVal;

    EXPECT_EQ(1920, datum.toInt64());
}

// Test assignment from int16_t
TEST_F(ExifdatumTest_730, AssignFromInt16_730) {
    ExifKey key("Exif.Image.Orientation");
    auto val = Value::create(signedShort);
    val->read("1");
    Exifdatum datum(key, val.get());

    int16_t newVal = -5;
    datum = newVal;

    EXPECT_EQ(-5, datum.toInt64());
}

// Test assignment from int32_t
TEST_F(ExifdatumTest_730, AssignFromInt32_730) {
    ExifKey key("Exif.Image.ImageWidth");
    auto val = Value::create(signedLong);
    val->read("100");
    Exifdatum datum(key, val.get());

    int32_t newVal = -1000;
    datum = newVal;

    EXPECT_EQ(-1000, datum.toInt64());
}

// Test assignment from URational
TEST_F(ExifdatumTest_730, AssignFromURational_730) {
    ExifKey key("Exif.Image.XResolution");
    auto val = Value::create(unsignedRational);
    val->read("72/1");
    Exifdatum datum(key, val.get());

    URational newVal(300, 1);
    datum = newVal;

    EXPECT_EQ(Rational(300, 1), datum.toRational());
}

// Test assignment from Rational
TEST_F(ExifdatumTest_730, AssignFromRational_730) {
    ExifKey key("Exif.Photo.ExposureBiasValue");
    auto val = Value::create(signedRational);
    val->read("0/1");
    Exifdatum datum(key, val.get());

    Rational newVal(-1, 3);
    datum = newVal;

    Rational result = datum.toRational();
    EXPECT_EQ(-1, result.first);
    EXPECT_EQ(3, result.second);
}

// Test assignment from Value
TEST_F(ExifdatumTest_730, AssignFromValue_730) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    Exifdatum datum(key, &val);

    AsciiValue newVal;
    newVal.read("Panasonic");
    datum = static_cast<const Value&>(newVal);

    EXPECT_EQ("Panasonic", datum.toString());
}

// Test setValue with Value pointer
TEST_F(ExifdatumTest_730, SetValueWithPointer_730) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);

    AsciiValue val;
    val.read("Fuji");
    datum.setValue(&val);

    EXPECT_EQ("Fuji", datum.toString());
}

// Test setValue with nullptr
TEST_F(ExifdatumTest_730, SetValueWithNullPointer_730) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    Exifdatum datum(key, &val);

    datum.setValue(nullptr);
    // After setting null, getValue should return null-like
    EXPECT_THROW(datum.value(), Exiv2::Error);
}

// Test setValue with string
TEST_F(ExifdatumTest_730, SetValueWithString_730) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    Exifdatum datum(key, &val);

    int result = datum.setValue("Olympus");
    EXPECT_EQ(0, result);
    EXPECT_EQ("Olympus", datum.toString());
}

// Test tag() method
TEST_F(ExifdatumTest_730, TagMethod_730) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);

    EXPECT_EQ(0x010f, datum.tag());
}

// Test familyName
TEST_F(ExifdatumTest_730, FamilyName_730) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);

    EXPECT_STREQ("Exif", datum.familyName());
}

// Test groupName
TEST_F(ExifdatumTest_730, GroupName_730) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);

    EXPECT_EQ("Image", datum.groupName());
}

// Test tagName
TEST_F(ExifdatumTest_730, TagName_730) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);

    EXPECT_EQ("Make", datum.tagName());
}

// Test count when no value is set
TEST_F(ExifdatumTest_730, CountWithNoValue_730) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);

    EXPECT_EQ(0u, datum.count());
}

// Test count with a value set
TEST_F(ExifdatumTest_730, CountWithValue_730) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    Exifdatum datum(key, &val);

    EXPECT_GT(datum.count(), 0u);
}

// Test size when no value
TEST_F(ExifdatumTest_730, SizeWithNoValue_730) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);

    EXPECT_EQ(0u, datum.size());
}

// Test size with value
TEST_F(ExifdatumTest_730, SizeWithValue_730) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    Exifdatum datum(key, &val);

    EXPECT_GT(datum.size(), 0u);
}

// Test typeId when no value set
TEST_F(ExifdatumTest_730, TypeIdNoValue_730) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);

    EXPECT_EQ(invalidTypeId, datum.typeId());
}

// Test typeId with value
TEST_F(ExifdatumTest_730, TypeIdWithValue_730) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    Exifdatum datum(key, &val);

    EXPECT_EQ(asciiString, datum.typeId());
}

// Test getValue
TEST_F(ExifdatumTest_730, GetValue_730) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    Exifdatum datum(key, &val);

    auto retrieved = datum.getValue();
    ASSERT_NE(nullptr, retrieved.get());
    EXPECT_EQ("Canon", retrieved->toString());
}

// Test getValue returns null when no value
TEST_F(ExifdatumTest_730, GetValueReturnsNullWhenNoValue_730) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);

    auto retrieved = datum.getValue();
    EXPECT_EQ(nullptr, retrieved.get());
}

// Test value() throws when no value is set
TEST_F(ExifdatumTest_730, ValueThrowsWhenNoValue_730) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);

    EXPECT_THROW(datum.value(), Exiv2::Error);
}

// Test toString with no value
TEST_F(ExifdatumTest_730, ToStringNoValue_730) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);

    EXPECT_EQ("", datum.toString());
}

// Test toInt64 with unsigned short
TEST_F(ExifdatumTest_730, ToInt64_730) {
    ExifKey key("Exif.Image.Orientation");
    auto val = Value::create(unsignedShort);
    val->read("3");
    Exifdatum datum(key, val.get());

    EXPECT_EQ(3, datum.toInt64());
}

// Test toFloat
TEST_F(ExifdatumTest_730, ToFloat_730) {
    ExifKey key("Exif.Image.XResolution");
    auto val = Value::create(unsignedRational);
    val->read("72/1");
    Exifdatum datum(key, val.get());

    EXPECT_FLOAT_EQ(72.0f, datum.toFloat());
}

// Test copy assignment with different keys produces deep copy
TEST_F(ExifdatumTest_730, DeepCopyOnAssignment_730) {
    ExifKey key1("Exif.Image.Make");
    AsciiValue val1;
    val1.read("Canon");
    Exifdatum datum1(key1, &val1);

    ExifKey key2("Exif.Image.Model");
    AsciiValue val2;
    val2.read("D5600");
    Exifdatum datum2(key2, &val2);

    datum2 = datum1;

    // Modify datum1, datum2 should not be affected
    datum1 = std::string("Nikon");

    EXPECT_EQ("Canon", datum2.toString());
    EXPECT_EQ("Nikon", datum1.toString());
}

// Test copy construction produces deep copy
TEST_F(ExifdatumTest_730, DeepCopyOnCopyConstruction_730) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Sony");
    Exifdatum original(key, &val);

    Exifdatum copy(original);

    original = std::string("Panasonic");

    EXPECT_EQ("Panasonic", original.toString());
    EXPECT_EQ("Sony", copy.toString());
}

// Test tagLabel
TEST_F(ExifdatumTest_730, TagLabel_730) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);

    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test ifdId
TEST_F(ExifdatumTest_730, IfdId_730) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);

    IfdId id = datum.ifdId();
    EXPECT_NE(ifdIdNotSet, id);
}

// Test sizeDataArea with no data area
TEST_F(ExifdatumTest_730, SizeDataAreaDefault_730) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    Exifdatum datum(key, &val);

    EXPECT_EQ(0u, datum.sizeDataArea());
}

// Test write to ostream
TEST_F(ExifdatumTest_730, WriteToStream_730) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    Exifdatum datum(key, &val);

    std::ostringstream os;
    datum.write(os, nullptr);

    EXPECT_FALSE(os.str().empty());
}

// Test idx
TEST_F(ExifdatumTest_730, IdxDefault_730) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);

    // idx should have a default value
    int idx = datum.idx();
    EXPECT_GE(idx, 0);
}

// Test typeName with value
TEST_F(ExifdatumTest_730, TypeNameWithValue_730) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    Exifdatum datum(key, &val);

    EXPECT_STREQ("Ascii", datum.typeName());
}

// Test typeName when no value
TEST_F(ExifdatumTest_730, TypeNameNoValue_730) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);

    // When no value, typeName may return something related to invalidTypeId
    const char* tn = datum.typeName();
    // Could be nullptr or a specific string
    // Just ensure no crash
    (void)tn;
}

// Test typeSize with value
TEST_F(ExifdatumTest_730, TypeSizeWithValue_730) {
    ExifKey key("Exif.Image.Orientation");
    auto val = Value::create(unsignedShort);
    val->read("1");
    Exifdatum datum(key, val.get());

    EXPECT_EQ(2u, datum.typeSize());
}

// Test copy to buffer
TEST_F(ExifdatumTest_730, CopyToBuffer_730) {
    ExifKey key("Exif.Image.Orientation");
    auto val = Value::create(unsignedShort);
    val->read("1");
    Exifdatum datum(key, val.get());

    byte buf[32] = {};
    size_t copied = datum.copy(buf, littleEndian);

    EXPECT_GT(copied, 0u);
}

// Test assignment from Exifdatum with null value
TEST_F(ExifdatumTest_730, AssignFromDatumWithNullValue_730) {
    ExifKey key1("Exif.Image.Make");
    Exifdatum datum1(key1, nullptr);

    ExifKey key2("Exif.Image.Model");
    AsciiValue val2;
    val2.read("Test");
    Exifdatum datum2(key2, &val2);

    datum2 = datum1;

    EXPECT_EQ("Exif.Image.Make", datum2.key());
    EXPECT_EQ(0u, datum2.count());
}
