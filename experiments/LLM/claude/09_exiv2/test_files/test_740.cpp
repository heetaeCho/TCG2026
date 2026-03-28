#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/tags.hpp>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

// Test fixture for Exifdatum tests
class ExifdatumTest_740 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test construction with a known ExifKey
TEST_F(ExifdatumTest_740, ConstructWithExifKey_740) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ("Exif.Image.ImageWidth", datum.key());
    EXPECT_EQ("Exif", std::string(datum.familyName()));
    EXPECT_EQ("Image", datum.groupName());
    EXPECT_EQ("ImageWidth", datum.tagName());
}

// Test copy constructor
TEST_F(ExifdatumTest_740, CopyConstructor_740) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    datum.setValue("1024");

    Exifdatum copy(datum);
    EXPECT_EQ(datum.key(), copy.key());
    EXPECT_EQ(datum.toString(), copy.toString());
}

// Test assignment operator
TEST_F(ExifdatumTest_740, AssignmentOperator_740) {
    ExifKey key1("Exif.Image.ImageWidth");
    Exifdatum datum1(key1, nullptr);
    datum1.setValue("1024");

    ExifKey key2("Exif.Image.ImageLength");
    Exifdatum datum2(key2, nullptr);
    datum2 = datum1;

    EXPECT_EQ(datum1.key(), datum2.key());
    EXPECT_EQ(datum1.toString(), datum2.toString());
}

// Test setValue with string
TEST_F(ExifdatumTest_740, SetValueString_740) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    int result = datum.setValue("1024");
    EXPECT_EQ(0, result);
    EXPECT_EQ("1024", datum.toString());
}

// Test setValue with Value pointer
TEST_F(ExifdatumTest_740, SetValuePointer_740) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);

    auto value = Value::create(unsignedLong);
    value->read("2048");
    datum.setValue(value.get());

    EXPECT_EQ("2048", datum.toString());
    EXPECT_EQ(unsignedLong, datum.typeId());
}

// Test operator= with uint16_t
TEST_F(ExifdatumTest_740, AssignUint16_740) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    datum = static_cast<uint16_t>(1);
    EXPECT_EQ("1", datum.toString());
}

// Test operator= with uint32_t
TEST_F(ExifdatumTest_740, AssignUint32_740) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    datum = static_cast<uint32_t>(4096);
    EXPECT_EQ("4096", datum.toString());
}

// Test operator= with int16_t
TEST_F(ExifdatumTest_740, AssignInt16_740) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    datum = static_cast<int16_t>(-5);
    EXPECT_EQ("-5", datum.toString());
}

// Test operator= with int32_t
TEST_F(ExifdatumTest_740, AssignInt32_740) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    datum = static_cast<int32_t>(-100);
    EXPECT_EQ("-100", datum.toString());
}

// Test operator= with string
TEST_F(ExifdatumTest_740, AssignString_740) {
    ExifKey key("Exif.Image.Model");
    Exifdatum datum(key, nullptr);
    datum = std::string("TestCamera");
    EXPECT_EQ("TestCamera", datum.toString());
}

// Test operator= with URational
TEST_F(ExifdatumTest_740, AssignURational_740) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    URational ur(72, 1);
    datum = ur;
    EXPECT_EQ("72/1", datum.toString());
}

// Test operator= with Rational
TEST_F(ExifdatumTest_740, AssignRational_740) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    Rational r(1, 3);
    datum = r;
    EXPECT_EQ("1/3", datum.toString());
}

// Test operator= with Value
TEST_F(ExifdatumTest_740, AssignValue_740) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);

    auto value = Value::create(unsignedLong);
    value->read("999");
    datum = *value;

    EXPECT_EQ("999", datum.toString());
}

// Test key() returns correct key string
TEST_F(ExifdatumTest_740, Key_740) {
    ExifKey key("Exif.Photo.DateTimeOriginal");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ("Exif.Photo.DateTimeOriginal", datum.key());
}

// Test familyName() returns "Exif"
TEST_F(ExifdatumTest_740, FamilyName_740) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    EXPECT_STREQ("Exif", datum.familyName());
}

// Test groupName()
TEST_F(ExifdatumTest_740, GroupName_740) {
    ExifKey key("Exif.Photo.DateTimeOriginal");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ("Photo", datum.groupName());
}

// Test tagName()
TEST_F(ExifdatumTest_740, TagName_740) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ("ImageWidth", datum.tagName());
}

// Test tag() returns correct tag number
TEST_F(ExifdatumTest_740, Tag_740) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(0x0100, datum.tag());
}

// Test typeId() after setValue
TEST_F(ExifdatumTest_740, TypeId_740) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    datum.setValue("1024");
    TypeId tid = datum.typeId();
    // After setValue, typeId should be the default type for this key
    EXPECT_NE(invalidTypeId, tid);
}

// Test count() after setting a value
TEST_F(ExifdatumTest_740, Count_740) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    datum.setValue("1024");
    EXPECT_EQ(1u, datum.count());
}

// Test size() after setting a value
TEST_F(ExifdatumTest_740, Size_740) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    datum.setValue("1024");
    EXPECT_GT(datum.size(), 0u);
}

// Test toInt64
TEST_F(ExifdatumTest_740, ToInt64_740) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    datum.setValue("512");
    EXPECT_EQ(512, datum.toInt64(0));
}

// Test toFloat
TEST_F(ExifdatumTest_740, ToFloat_740) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    datum.setValue("72/1");
    EXPECT_FLOAT_EQ(72.0f, datum.toFloat(0));
}

// Test toRational
TEST_F(ExifdatumTest_740, ToRational_740) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    datum.setValue("72/1");
    Rational r = datum.toRational(0);
    EXPECT_EQ(72, r.first);
    EXPECT_EQ(1, r.second);
}

// Test toString with index
TEST_F(ExifdatumTest_740, ToStringWithIndex_740) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    datum.setValue("1024");
    EXPECT_EQ("1024", datum.toString(0));
}

// Test getValue returns a valid unique_ptr
TEST_F(ExifdatumTest_740, GetValue_740) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    datum.setValue("256");
    auto val = datum.getValue();
    ASSERT_NE(nullptr, val.get());
    EXPECT_EQ("256", val->toString());
}

// Test value() reference
TEST_F(ExifdatumTest_740, ValueRef_740) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    datum.setValue("128");
    const Value& val = datum.value();
    EXPECT_EQ("128", val.toString());
}

// Test sizeDataArea for datum without data area
TEST_F(ExifdatumTest_740, SizeDataAreaEmpty_740) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    datum.setValue("64");
    EXPECT_EQ(0u, datum.sizeDataArea());
}

// Test copy method
TEST_F(ExifdatumTest_740, CopyToBuffer_740) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    datum.setValue("1024");
    
    size_t sz = datum.size();
    std::vector<byte> buf(sz);
    size_t copied = datum.copy(buf.data(), littleEndian);
    EXPECT_GT(copied, 0u);
}

// Test write to ostream
TEST_F(ExifdatumTest_740, WriteToStream_740) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    datum.setValue("2048");

    std::ostringstream os;
    datum.write(os, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test typeName
TEST_F(ExifdatumTest_740, TypeName_740) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    datum.setValue("512");
    const char* tn = datum.typeName();
    EXPECT_NE(nullptr, tn);
}

// Test typeSize
TEST_F(ExifdatumTest_740, TypeSize_740) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    datum.setValue("512");
    EXPECT_GT(datum.typeSize(), 0u);
}

// Test construction with a Value pointer
TEST_F(ExifdatumTest_740, ConstructWithValue_740) {
    ExifKey key("Exif.Image.Model");
    auto value = Value::create(asciiString);
    value->read("TestModel");
    Exifdatum datum(key, value.get());
    EXPECT_EQ("TestModel", datum.toString());
}

// Test tagLabel
TEST_F(ExifdatumTest_740, TagLabel_740) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    std::string label = datum.tagLabel();
    // tagLabel should return a non-empty label for a known tag
    EXPECT_FALSE(label.empty());
}

// Test idx
TEST_F(ExifdatumTest_740, Idx_740) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    // Default idx should be 0
    EXPECT_EQ(0, datum.idx());
}

// Test ifdId
TEST_F(ExifdatumTest_740, IfdId_740) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    IfdId id = datum.ifdId();
    EXPECT_NE(ifdIdNotSet, id);
}

// Test setValue creates value from default type when value_ is null
TEST_F(ExifdatumTest_740, SetValueCreatesDefaultType_740) {
    ExifKey key("Exif.Image.Model");
    Exifdatum datum(key, nullptr);
    // Model's default type is asciiString
    int result = datum.setValue("Hello");
    EXPECT_EQ(0, result);
    EXPECT_EQ(asciiString, datum.typeId());
}

// Test multiple setValue calls
TEST_F(ExifdatumTest_740, MultipleSetValue_740) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    datum.setValue("100");
    EXPECT_EQ("100", datum.toString());
    
    datum.setValue("200");
    EXPECT_EQ("200", datum.toString());
}

// Test setting value with null Value pointer
TEST_F(ExifdatumTest_740, SetValueNullPointer_740) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    datum.setValue("512");
    // Set to null should clear the value
    datum.setValue(static_cast<const Value*>(nullptr));
    // After setting null, count and size should reflect empty state
    EXPECT_EQ(0u, datum.count());
}

// Test dataArea for datum without data area
TEST_F(ExifdatumTest_740, DataAreaEmpty_740) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    datum.setValue("64");
    DataBuf buf = datum.dataArea();
    EXPECT_EQ(0u, buf.size());
}

// Test setDataArea
TEST_F(ExifdatumTest_740, SetDataArea_740) {
    ExifKey key("Exif.Image.StripOffsets");
    Exifdatum datum(key, nullptr);
    datum.setValue("0");
    
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    // setDataArea may or may not succeed depending on the value type
    datum.setDataArea(data, sizeof(data));
    // Just verify no crash
}

// Test with Exif.Photo tags
TEST_F(ExifdatumTest_740, PhotoTag_740) {
    ExifKey key("Exif.Photo.ExposureTime");
    Exifdatum datum(key, nullptr);
    datum.setValue("1/125");
    EXPECT_EQ("1/125", datum.toString());
    EXPECT_EQ("Photo", datum.groupName());
    EXPECT_EQ("ExposureTime", datum.tagName());
}

// Test copy of Exifdatum with value
TEST_F(ExifdatumTest_740, CopyWithValue_740) {
    ExifKey key("Exif.Image.Model");
    auto value = Value::create(asciiString);
    value->read("Canon EOS");
    Exifdatum datum(key, value.get());
    
    Exifdatum copy(datum);
    EXPECT_EQ(datum.toString(), copy.toString());
    EXPECT_EQ(datum.typeId(), copy.typeId());
    EXPECT_EQ(datum.count(), copy.count());
}
