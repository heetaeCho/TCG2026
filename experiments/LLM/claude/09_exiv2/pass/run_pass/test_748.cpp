#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/tags.hpp>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

class ExifdatumTest_748 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test construction with a known ExifKey and verifying tag()
TEST_F(ExifdatumTest_748, ConstructWithExifKeyTag_748) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    // "Make" tag is 0x010f
    EXPECT_EQ(datum.tag(), 0x010f);
}

// Test that key() returns the correct key string
TEST_F(ExifdatumTest_748, KeyReturnsCorrectString_748) {
    ExifKey key("Exif.Image.Model");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Exif.Image.Model");
}

// Test familyName() returns "Exif"
TEST_F(ExifdatumTest_748, FamilyNameReturnsExif_748) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_STREQ(datum.familyName(), "Exif");
}

// Test groupName() returns the correct group
TEST_F(ExifdatumTest_748, GroupNameReturnsCorrectGroup_748) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "Image");
}

// Test tagName() returns the correct tag name
TEST_F(ExifdatumTest_748, TagNameReturnsCorrectName_748) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.tagName(), "Make");
}

// Test copy constructor
TEST_F(ExifdatumTest_748, CopyConstructor_748) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("Canon");

    Exifdatum copy(datum);
    EXPECT_EQ(copy.tag(), datum.tag());
    EXPECT_EQ(copy.key(), datum.key());
    EXPECT_EQ(copy.toString(), "Canon");
}

// Test assignment operator (Exifdatum = Exifdatum)
TEST_F(ExifdatumTest_748, CopyAssignment_748) {
    ExifKey key1("Exif.Image.Make");
    Exifdatum datum1(key1, nullptr);
    datum1 = std::string("Canon");

    ExifKey key2("Exif.Image.Model");
    Exifdatum datum2(key2, nullptr);
    datum2 = datum1;

    EXPECT_EQ(datum2.tag(), datum1.tag());
    EXPECT_EQ(datum2.toString(), "Canon");
}

// Test operator=(const std::string&)
TEST_F(ExifdatumTest_748, AssignString_748) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("Nikon");
    EXPECT_EQ(datum.toString(), "Nikon");
}

// Test operator=(const uint16_t&)
TEST_F(ExifdatumTest_748, AssignUint16_748) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    uint16_t val = 1;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 1);
}

// Test operator=(const uint32_t&)
TEST_F(ExifdatumTest_748, AssignUint32_748) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    uint32_t val = 4000;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 4000);
}

// Test operator=(const int16_t&)
TEST_F(ExifdatumTest_748, AssignInt16_748) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    int16_t val = -5;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), -5);
}

// Test operator=(const int32_t&)
TEST_F(ExifdatumTest_748, AssignInt32_748) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    int32_t val = -100;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), -100);
}

// Test operator=(const URational&)
TEST_F(ExifdatumTest_748, AssignURational_748) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    URational val = {72, 1};
    datum = val;
    EXPECT_EQ(datum.toRational(0), Rational(72, 1));
}

// Test operator=(const Rational&)
TEST_F(ExifdatumTest_748, AssignRational_748) {
    ExifKey key("Exif.Photo.ExposureBiasValue");
    Exifdatum datum(key, nullptr);
    Rational val = {-1, 3};
    datum = val;
    Rational result = datum.toRational(0);
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, 3);
}

// Test setValue(const std::string&)
TEST_F(ExifdatumTest_748, SetValueString_748) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    int result = datum.setValue("TestValue");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "TestValue");
}

// Test count() with no value set returns 0
TEST_F(ExifdatumTest_748, CountWithNoValue_748) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.count(), 0u);
}

// Test count() after setting a value
TEST_F(ExifdatumTest_748, CountAfterSetValue_748) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("Test");
    EXPECT_GT(datum.count(), 0u);
}

// Test size() with no value
TEST_F(ExifdatumTest_748, SizeWithNoValue_748) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.size(), 0u);
}

// Test size() after setting value
TEST_F(ExifdatumTest_748, SizeAfterSetValue_748) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("Canon");
    EXPECT_GT(datum.size(), 0u);
}

// Test tag() with ExifKey constructed from tag number and group name
TEST_F(ExifdatumTest_748, TagFromNumericKey_748) {
    ExifKey key(0x010f, "Image");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.tag(), 0x010f);
}

// Test typeId() with no value
TEST_F(ExifdatumTest_748, TypeIdNoValue_748) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    // When no value is set, typeId should return invalidTypeId or some default
    TypeId tid = datum.typeId();
    // Just verify it doesn't crash and returns something
    (void)tid;
}

// Test getValue() returns nullptr when no value is set
TEST_F(ExifdatumTest_748, GetValueNoValue_748) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    auto val = datum.getValue();
    EXPECT_EQ(val.get(), nullptr);
}

// Test getValue() returns non-null after setting a value
TEST_F(ExifdatumTest_748, GetValueAfterSet_748) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("Canon");
    auto val = datum.getValue();
    EXPECT_NE(val.get(), nullptr);
}

// Test write() to ostream
TEST_F(ExifdatumTest_748, WriteToStream_748) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("Canon");
    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test toString(size_t n)
TEST_F(ExifdatumTest_748, ToStringWithIndex_748) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("Canon");
    std::string result = datum.toString(0);
    EXPECT_EQ(result, "Canon");
}

// Test ifdId() returns a valid IfdId
TEST_F(ExifdatumTest_748, IfdIdReturnsValid_748) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    IfdId id = datum.ifdId();
    // IfdId for Image group should be ifd0Id
    EXPECT_EQ(id, IfdId::ifd0Id);
}

// Test tagLabel() returns non-empty string for known tag
TEST_F(ExifdatumTest_748, TagLabelNonEmpty_748) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test tagDesc() for a known tag
TEST_F(ExifdatumTest_748, TagDescForKnownTag_748) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    std::string desc = datum.tagDesc();
    // Description should be non-empty for a well-known tag
    EXPECT_FALSE(desc.empty());
}

// Test sizeDataArea() with no data area
TEST_F(ExifdatumTest_748, SizeDataAreaDefault_748) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("Canon");
    EXPECT_EQ(datum.sizeDataArea(), 0u);
}

// Test setting value via Value object pointer
TEST_F(ExifdatumTest_748, SetValueViaPointer_748) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);

    auto value = Value::create(asciiString);
    value->read("TestBrand");
    datum.setValue(value.get());

    EXPECT_EQ(datum.toString(), "TestBrand");
}

// Test operator=(const Value&)
TEST_F(ExifdatumTest_748, AssignValueObject_748) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);

    auto value = Value::create(asciiString);
    value->read("Olympus");
    datum = *value;

    EXPECT_EQ(datum.toString(), "Olympus");
}

// Test toFloat()
TEST_F(ExifdatumTest_748, ToFloat_748) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    URational val = {72, 1};
    datum = val;
    float f = datum.toFloat(0);
    EXPECT_FLOAT_EQ(f, 72.0f);
}

// Test toInt64()
TEST_F(ExifdatumTest_748, ToInt64_748) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    uint16_t val = 6;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 6);
}

// Test copy() to buffer
TEST_F(ExifdatumTest_748, CopyToBuffer_748) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    uint16_t val = 1;
    datum = val;

    byte buf[64] = {};
    size_t copied = datum.copy(buf, littleEndian);
    EXPECT_GT(copied, 0u);
}

// Test typeName() for known type
TEST_F(ExifdatumTest_748, TypeNameForAscii_748) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("Canon");
    const char* tn = datum.typeName();
    EXPECT_NE(tn, nullptr);
    EXPECT_STREQ(tn, "Ascii");
}

// Test typeSize() for short type
TEST_F(ExifdatumTest_748, TypeSizeForShort_748) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    uint16_t val = 1;
    datum = val;
    EXPECT_EQ(datum.typeSize(), 2u);
}

// Test idx() default
TEST_F(ExifdatumTest_748, IdxDefault_748) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    // idx default should be 0
    EXPECT_EQ(datum.idx(), 0);
}

// Test construction with ExifKey from Photo group
TEST_F(ExifdatumTest_748, PhotoGroupTag_748) {
    ExifKey key("Exif.Photo.ExposureTime");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "Photo");
    EXPECT_EQ(datum.tagName(), "ExposureTime");
    // ExposureTime tag is 0x829a
    EXPECT_EQ(datum.tag(), 0x829a);
}

// Test construction with ExifKey from GPSInfo group
TEST_F(ExifdatumTest_748, GPSGroupTag_748) {
    ExifKey key("Exif.GPSInfo.GPSLatitude");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "GPSInfo");
    EXPECT_EQ(datum.tagName(), "GPSLatitude");
}

// Test dataArea() with no data area set
TEST_F(ExifdatumTest_748, DataAreaEmpty_748) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("Canon");
    DataBuf buf = datum.dataArea();
    EXPECT_EQ(buf.size(), 0u);
}

// Test construction with Value provided
TEST_F(ExifdatumTest_748, ConstructWithValue_748) {
    ExifKey key("Exif.Image.Make");
    auto value = Value::create(asciiString);
    value->read("Sony");
    Exifdatum datum(key, value.get());
    EXPECT_EQ(datum.toString(), "Sony");
    EXPECT_EQ(datum.tag(), 0x010f);
}

// Test ifdName()
TEST_F(ExifdatumTest_748, IfdName_748) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    const char* name = datum.ifdName();
    EXPECT_NE(name, nullptr);
}
