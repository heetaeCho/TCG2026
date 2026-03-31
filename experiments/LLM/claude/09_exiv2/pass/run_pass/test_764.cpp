#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/exiv2.hpp>
#include <cstring>

using namespace Exiv2;

class ExifdatumTest_764 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test construction with a known ExifKey and no value
TEST_F(ExifdatumTest_764, ConstructWithKeyNoValue_764) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
    EXPECT_EQ(datum.familyName(), std::string("Exif"));
    EXPECT_EQ(datum.groupName(), "Image");
    EXPECT_EQ(datum.tagName(), "Make");
}

// Test sizeDataArea returns 0 when no value is set
TEST_F(ExifdatumTest_764, SizeDataAreaNoValue_764) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.sizeDataArea(), 0u);
}

// Test sizeDataArea returns 0 when value is set but has no data area
TEST_F(ExifdatumTest_764, SizeDataAreaWithValueNoDataArea_764) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("TestMake");
    Exifdatum datum(key, &val);
    EXPECT_EQ(datum.sizeDataArea(), 0u);
}

// Test copy constructor
TEST_F(ExifdatumTest_764, CopyConstructor_764) {
    ExifKey key("Exif.Image.Model");
    AsciiValue val;
    val.read("TestModel");
    Exifdatum datum1(key, &val);
    Exifdatum datum2(datum1);
    EXPECT_EQ(datum2.key(), "Exif.Image.Model");
    EXPECT_EQ(datum2.toString(), datum1.toString());
}

// Test assignment operator
TEST_F(ExifdatumTest_764, AssignmentOperator_764) {
    ExifKey key1("Exif.Image.Make");
    AsciiValue val1;
    val1.read("Make1");
    Exifdatum datum1(key1, &val1);

    ExifKey key2("Exif.Image.Model");
    AsciiValue val2;
    val2.read("Model2");
    Exifdatum datum2(key2, &val2);

    datum2 = datum1;
    EXPECT_EQ(datum2.key(), "Exif.Image.Make");
    EXPECT_EQ(datum2.toString(), "Make1");
}

// Test setValue with string
TEST_F(ExifdatumTest_764, SetValueString_764) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("InitialValue");
    Exifdatum datum(key, &val);
    int result = datum.setValue("NewValue");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "NewValue");
}

// Test operator= with string
TEST_F(ExifdatumTest_764, AssignString_764) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("OldValue");
    Exifdatum datum(key, &val);
    datum = std::string("NewStringValue");
    EXPECT_EQ(datum.toString(), "NewStringValue");
}

// Test operator= with uint16_t
TEST_F(ExifdatumTest_764, AssignUint16_764) {
    ExifKey key("Exif.Image.Orientation");
    UShortValue val;
    val.read("1");
    Exifdatum datum(key, &val);
    uint16_t newVal = 3;
    datum = newVal;
    EXPECT_EQ(datum.toInt64(0), 3);
}

// Test operator= with uint32_t
TEST_F(ExifdatumTest_764, AssignUint32_764) {
    ExifKey key("Exif.Image.ImageWidth");
    ULongValue val;
    val.read("100");
    Exifdatum datum(key, &val);
    uint32_t newVal = 200;
    datum = newVal;
    EXPECT_EQ(datum.toInt64(0), 200);
}

// Test operator= with int16_t
TEST_F(ExifdatumTest_764, AssignInt16_764) {
    ExifKey key("Exif.Image.Orientation");
    ShortValue val;
    val.read("1");
    Exifdatum datum(key, &val);
    int16_t newVal = -5;
    datum = newVal;
    EXPECT_EQ(datum.toInt64(0), -5);
}

// Test operator= with int32_t
TEST_F(ExifdatumTest_764, AssignInt32_764) {
    ExifKey key("Exif.Image.ImageWidth");
    LongValue val;
    val.read("100");
    Exifdatum datum(key, &val);
    int32_t newVal = -300;
    datum = newVal;
    EXPECT_EQ(datum.toInt64(0), -300);
}

// Test operator= with URational
TEST_F(ExifdatumTest_764, AssignURational_764) {
    ExifKey key("Exif.Image.XResolution");
    URationalValue val;
    val.read("72/1");
    Exifdatum datum(key, &val);
    URational newVal(300, 1);
    datum = newVal;
    EXPECT_EQ(datum.toRational(0), Rational(300, 1));
}

// Test operator= with Rational
TEST_F(ExifdatumTest_764, AssignRational_764) {
    ExifKey key("Exif.Photo.ExposureBiasValue");
    RationalValue val;
    val.read("0/1");
    Exifdatum datum(key, &val);
    Rational newVal(-1, 3);
    datum = newVal;
    Rational result = datum.toRational(0);
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, 3);
}

// Test tag() returns correct tag number
TEST_F(ExifdatumTest_764, Tag_764) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    // Exif.Image.Make tag is 0x010f
    EXPECT_EQ(datum.tag(), 0x010f);
}

// Test typeId when no value is set
TEST_F(ExifdatumTest_764, TypeIdNoValue_764) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    // When no value, typeId should return the default type for the key
    TypeId tid = datum.typeId();
    // Make is of type Ascii typically
    EXPECT_EQ(tid, asciiString);
}

// Test typeId when value is set
TEST_F(ExifdatumTest_764, TypeIdWithValue_764) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("TestMake");
    Exifdatum datum(key, &val);
    EXPECT_EQ(datum.typeId(), asciiString);
}

// Test count when value is set
TEST_F(ExifdatumTest_764, CountWithValue_764) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Hello");
    Exifdatum datum(key, &val);
    EXPECT_GT(datum.count(), 0u);
}

// Test count when no value is set
TEST_F(ExifdatumTest_764, CountNoValue_764) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.count(), 0u);
}

// Test size when value is set
TEST_F(ExifdatumTest_764, SizeWithValue_764) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Test");
    Exifdatum datum(key, &val);
    EXPECT_GT(datum.size(), 0u);
}

// Test size when no value is set
TEST_F(ExifdatumTest_764, SizeNoValue_764) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.size(), 0u);
}

// Test toString
TEST_F(ExifdatumTest_764, ToString_764) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    Exifdatum datum(key, &val);
    EXPECT_EQ(datum.toString(), "Canon");
}

// Test toString with index
TEST_F(ExifdatumTest_764, ToStringWithIndex_764) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    Exifdatum datum(key, &val);
    EXPECT_EQ(datum.toString(0), "Canon");
}

// Test getValue returns a valid unique_ptr when value exists
TEST_F(ExifdatumTest_764, GetValueNotNull_764) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Nikon");
    Exifdatum datum(key, &val);
    auto v = datum.getValue();
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(v->toString(), "Nikon");
}

// Test getValue returns nullptr when no value set
TEST_F(ExifdatumTest_764, GetValueNull_764) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    auto v = datum.getValue();
    EXPECT_EQ(v, nullptr);
}

// Test setValue with Value pointer
TEST_F(ExifdatumTest_764, SetValueWithPointer_764) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);

    AsciiValue val;
    val.read("Sony");
    datum.setValue(&val);
    EXPECT_EQ(datum.toString(), "Sony");
    EXPECT_GT(datum.count(), 0u);
}

// Test setValue with nullptr resets value
TEST_F(ExifdatumTest_764, SetValueNullPointer_764) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Fuji");
    Exifdatum datum(key, &val);
    EXPECT_GT(datum.count(), 0u);

    datum.setValue(nullptr);
    EXPECT_EQ(datum.count(), 0u);
}

// Test operator= with Value
TEST_F(ExifdatumTest_764, AssignValue_764) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val1;
    val1.read("OldMake");
    Exifdatum datum(key, &val1);

    AsciiValue val2;
    val2.read("NewMake");
    datum = static_cast<const Value&>(val2);
    EXPECT_EQ(datum.toString(), "NewMake");
}

// Test setDataArea
TEST_F(ExifdatumTest_764, SetDataArea_764) {
    ExifKey key("Exif.Image.StripOffsets");
    auto val = Value::create(unsignedLong);
    val->read("0");
    Exifdatum datum(key, val.get());

    byte data[] = {0x01, 0x02, 0x03, 0x04};
    int result = datum.setDataArea(data, sizeof(data));
    // setDataArea may return 0 on success or -1 on failure depending on value type
    // We just check it doesn't crash; the return value depends on the Value impl
    (void)result;
}

// Test dataArea when no data area set
TEST_F(ExifdatumTest_764, DataAreaEmpty_764) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Test");
    Exifdatum datum(key, &val);
    DataBuf buf = datum.dataArea();
    EXPECT_EQ(buf.size(), 0u);
}

// Test toInt64
TEST_F(ExifdatumTest_764, ToInt64_764) {
    ExifKey key("Exif.Image.Orientation");
    UShortValue val;
    val.read("6");
    Exifdatum datum(key, &val);
    EXPECT_EQ(datum.toInt64(0), 6);
}

// Test toFloat
TEST_F(ExifdatumTest_764, ToFloat_764) {
    ExifKey key("Exif.Image.Orientation");
    UShortValue val;
    val.read("42");
    Exifdatum datum(key, &val);
    EXPECT_FLOAT_EQ(datum.toFloat(0), 42.0f);
}

// Test toRational
TEST_F(ExifdatumTest_764, ToRational_764) {
    ExifKey key("Exif.Image.XResolution");
    URationalValue val;
    val.read("72/1");
    Exifdatum datum(key, &val);
    Rational r = datum.toRational(0);
    EXPECT_EQ(r.first, 72);
    EXPECT_EQ(r.second, 1);
}

// Test tagLabel returns non-empty for known tags
TEST_F(ExifdatumTest_764, TagLabel_764) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test tagDesc
TEST_F(ExifdatumTest_764, TagDesc_764) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    // tagDesc may be empty or non-empty depending on the tag
    std::string desc = datum.tagDesc();
    // Just ensure it doesn't crash
    (void)desc;
}

// Test ifdId
TEST_F(ExifdatumTest_764, IfdId_764) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    IfdId id = datum.ifdId();
    EXPECT_EQ(id, IfdId::ifd0Id);
}

// Test ifdName
TEST_F(ExifdatumTest_764, IfdName_764) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    const char* name = datum.ifdName();
    ASSERT_NE(name, nullptr);
}

// Test typeName with value
TEST_F(ExifdatumTest_764, TypeName_764) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Test");
    Exifdatum datum(key, &val);
    const char* tn = datum.typeName();
    ASSERT_NE(tn, nullptr);
    EXPECT_STREQ(tn, "Ascii");
}

// Test typeSize
TEST_F(ExifdatumTest_764, TypeSize_764) {
    ExifKey key("Exif.Image.Orientation");
    UShortValue val;
    val.read("1");
    Exifdatum datum(key, &val);
    EXPECT_EQ(datum.typeSize(), 2u);
}

// Test copy to buffer
TEST_F(ExifdatumTest_764, CopyToBuffer_764) {
    ExifKey key("Exif.Image.Orientation");
    UShortValue val;
    val.read("1");
    Exifdatum datum(key, &val);
    byte buf[16] = {};
    size_t copied = datum.copy(buf, littleEndian);
    EXPECT_GT(copied, 0u);
}

// Test ExifData add and find
TEST_F(ExifdatumTest_764, ExifDataAddAndFind_764) {
    ExifData exifData;
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("TestCamera");
    exifData.add(key, &val);

    auto it = exifData.findKey(ExifKey("Exif.Image.Make"));
    ASSERT_NE(it, exifData.end());
    EXPECT_EQ(it->toString(), "TestCamera");
    EXPECT_EQ(it->sizeDataArea(), 0u);
}

// Test ExifData with multiple entries
TEST_F(ExifdatumTest_764, ExifDataMultipleEntries_764) {
    ExifData exifData;

    ExifKey key1("Exif.Image.Make");
    AsciiValue val1;
    val1.read("Canon");
    exifData.add(key1, &val1);

    ExifKey key2("Exif.Image.Model");
    AsciiValue val2;
    val2.read("EOS R5");
    exifData.add(key2, &val2);

    EXPECT_EQ(exifData.count(), 2u);

    auto it1 = exifData.findKey(ExifKey("Exif.Image.Make"));
    ASSERT_NE(it1, exifData.end());
    EXPECT_EQ(it1->toString(), "Canon");

    auto it2 = exifData.findKey(ExifKey("Exif.Image.Model"));
    ASSERT_NE(it2, exifData.end());
    EXPECT_EQ(it2->toString(), "EOS R5");
}

// Test write to ostream
TEST_F(ExifdatumTest_764, WriteToStream_764) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Nikon");
    Exifdatum datum(key, &val);
    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test idx returns valid index
TEST_F(ExifdatumTest_764, Idx_764) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    int index = datum.idx();
    // idx should have some default value
    (void)index; // Just ensure no crash
}
