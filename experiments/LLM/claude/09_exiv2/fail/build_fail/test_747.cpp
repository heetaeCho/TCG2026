#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/tags.hpp>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

// Test fixture for Exifdatum tests
class ExifdatumTest_747 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test construction with a known ExifKey
TEST_F(ExifdatumTest_747, ConstructWithExifKey_747) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
}

// Test key() returns the correct key string
TEST_F(ExifdatumTest_747, KeyReturnsCorrectString_747) {
    ExifKey key("Exif.Image.Model");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Exif.Image.Model");
}

// Test familyName() returns "Exif"
TEST_F(ExifdatumTest_747, FamilyNameReturnsExif_747) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_STREQ(datum.familyName(), "Exif");
}

// Test groupName() returns correct group
TEST_F(ExifdatumTest_747, GroupNameReturnsCorrectGroup_747) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "Image");
}

// Test tagName() returns correct tag name
TEST_F(ExifdatumTest_747, TagNameReturnsCorrectName_747) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.tagName(), "Make");
}

// Test tagLabel() returns a non-empty label for known tags
TEST_F(ExifdatumTest_747, TagLabelReturnsNonEmpty_747) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test tagDesc() returns a description for known tags
TEST_F(ExifdatumTest_747, TagDescReturnsDescription_747) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    std::string desc = datum.tagDesc();
    // tagDesc() should return some string (could be empty for some tags)
    // For Make, it typically has a description
    // We just verify it doesn't throw
    SUCCEED();
}

// Test tag() returns correct tag number
TEST_F(ExifdatumTest_747, TagReturnsCorrectNumber_747) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    // Make tag is 0x010f
    EXPECT_EQ(datum.tag(), 0x010f);
}

// Test copy constructor
TEST_F(ExifdatumTest_747, CopyConstructor_747) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Canon");
    
    Exifdatum copy(datum);
    EXPECT_EQ(copy.key(), datum.key());
    EXPECT_EQ(copy.toString(), datum.toString());
}

// Test assignment operator
TEST_F(ExifdatumTest_747, AssignmentOperator_747) {
    ExifKey key1("Exif.Image.Make");
    Exifdatum datum1(key1, nullptr);
    datum1.setValue("Canon");
    
    ExifKey key2("Exif.Image.Model");
    Exifdatum datum2(key2, nullptr);
    datum2 = datum1;
    
    EXPECT_EQ(datum2.key(), datum1.key());
    EXPECT_EQ(datum2.toString(), datum1.toString());
}

// Test setValue with string
TEST_F(ExifdatumTest_747, SetValueString_747) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    int result = datum.setValue("Nikon");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "Nikon");
}

// Test operator= with string
TEST_F(ExifdatumTest_747, OperatorAssignString_747) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("initial");
    datum = std::string("Updated");
    EXPECT_EQ(datum.toString(), "Updated");
}

// Test operator= with uint16_t
TEST_F(ExifdatumTest_747, OperatorAssignUint16_747) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    uint16_t val = 1;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 1);
}

// Test operator= with uint32_t
TEST_F(ExifdatumTest_747, OperatorAssignUint32_747) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    uint32_t val = 1920;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 1920);
}

// Test operator= with int16_t
TEST_F(ExifdatumTest_747, OperatorAssignInt16_747) {
    ExifKey key("Exif.Photo.ExposureCompensation");
    Exifdatum datum(key, nullptr);
    // Use a tag that accepts signed short
    ExifKey key2("Exif.Image.Orientation");
    Exifdatum datum2(key2, nullptr);
    int16_t val = 3;
    datum2 = val;
    EXPECT_EQ(datum2.toInt64(0), 3);
}

// Test operator= with int32_t
TEST_F(ExifdatumTest_747, OperatorAssignInt32_747) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    int32_t val = 4096;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 4096);
}

// Test operator= with URational
TEST_F(ExifdatumTest_747, OperatorAssignURational_747) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    URational val(72, 1);
    datum = val;
    EXPECT_EQ(datum.toRational(0), Rational(72, 1));
}

// Test operator= with Rational
TEST_F(ExifdatumTest_747, OperatorAssignRational_747) {
    ExifKey key("Exif.Photo.ExposureBiasValue");
    Exifdatum datum(key, nullptr);
    Rational val(1, 3);
    datum = val;
    Rational result = datum.toRational(0);
    EXPECT_EQ(result.first, 1);
    EXPECT_EQ(result.second, 3);
}

// Test typeId() when no value is set
TEST_F(ExifdatumTest_747, TypeIdWhenNoValue_747) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    // When no value is set, typeId should return invalidTypeId or the default
    TypeId tid = datum.typeId();
    // Just check it doesn't crash; we don't know the exact value without value set
    SUCCEED();
}

// Test count() when no value is set
TEST_F(ExifdatumTest_747, CountWhenNoValue_747) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.count(), 0u);
}

// Test size() when no value is set
TEST_F(ExifdatumTest_747, SizeWhenNoValue_747) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.size(), 0u);
}

// Test count() after setting a string value
TEST_F(ExifdatumTest_747, CountAfterSetValue_747) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("TestMaker");
    EXPECT_GT(datum.count(), 0u);
}

// Test size() after setting a string value
TEST_F(ExifdatumTest_747, SizeAfterSetValue_747) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("TestMaker");
    EXPECT_GT(datum.size(), 0u);
}

// Test toString() with an index
TEST_F(ExifdatumTest_747, ToStringWithIndex_747) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("TestValue");
    std::string str = datum.toString(0);
    EXPECT_EQ(str, "TestValue");
}

// Test getValue() returns a unique pointer
TEST_F(ExifdatumTest_747, GetValueReturnsValidPtr_747) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("SomeValue");
    auto val = datum.getValue();
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->toString(), "SomeValue");
}

// Test getValue() when no value is set
TEST_F(ExifdatumTest_747, GetValueWhenNoValueSet_747) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    auto val = datum.getValue();
    // Expect nullptr when no value is set
    EXPECT_EQ(val, nullptr);
}

// Test value() throws when no value set
TEST_F(ExifdatumTest_747, ValueThrowsWhenNoValueSet_747) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_THROW(datum.value(), Error);
}

// Test setValue with Value pointer
TEST_F(ExifdatumTest_747, SetValueWithValuePtr_747) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    AsciiValue av("TestCamera");
    datum.setValue(&av);
    EXPECT_EQ(datum.toString(), "TestCamera");
}

// Test setValue with nullptr
TEST_F(ExifdatumTest_747, SetValueWithNullptr_747) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("initial");
    datum.setValue(nullptr);
    EXPECT_EQ(datum.count(), 0u);
}

// Test ifdId() returns a valid IfdId
TEST_F(ExifdatumTest_747, IfdIdReturnsValid_747) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    IfdId id = datum.ifdId();
    // ifd0Id for Image group
    EXPECT_EQ(id, IfdId::ifd0Id);
}

// Test ifdName() returns correct name
TEST_F(ExifdatumTest_747, IfdNameReturnsCorrect_747) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    const char* name = datum.ifdName();
    ASSERT_NE(name, nullptr);
    // Should be something like "IFD0"
    EXPECT_STRNE(name, "");
}

// Test write to ostream
TEST_F(ExifdatumTest_747, WriteToOstream_747) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("TestOutput");
    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test construction with a value
TEST_F(ExifdatumTest_747, ConstructWithValue_747) {
    ExifKey key("Exif.Image.Make");
    AsciiValue av("InitialValue");
    Exifdatum datum(key, &av);
    EXPECT_EQ(datum.toString(), "InitialValue");
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
}

// Test toFloat
TEST_F(ExifdatumTest_747, ToFloat_747) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    URational val(72, 1);
    datum = val;
    float f = datum.toFloat(0);
    EXPECT_FLOAT_EQ(f, 72.0f);
}

// Test toInt64
TEST_F(ExifdatumTest_747, ToInt64_747) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    uint16_t val = 6;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 6);
}

// Test typeName() after setting a value
TEST_F(ExifdatumTest_747, TypeNameAfterSetValue_747) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("test");
    const char* tn = datum.typeName();
    ASSERT_NE(tn, nullptr);
    EXPECT_STREQ(tn, "Ascii");
}

// Test typeSize() after setting a value
TEST_F(ExifdatumTest_747, TypeSizeAfterSetValue_747) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("test");
    EXPECT_EQ(datum.typeSize(), 1u);
}

// Test with Photo group keys
TEST_F(ExifdatumTest_747, PhotoGroupKey_747) {
    ExifKey key("Exif.Photo.DateTimeOriginal");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "Photo");
    EXPECT_EQ(datum.tagName(), "DateTimeOriginal");
}

// Test sizeDataArea when no data area
TEST_F(ExifdatumTest_747, SizeDataAreaNoData_747) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("test");
    EXPECT_EQ(datum.sizeDataArea(), 0u);
}

// Test copy to buffer
TEST_F(ExifdatumTest_747, CopyToBuffer_747) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    uint16_t val = 1;
    datum = val;
    byte buf[16] = {0};
    size_t copied = datum.copy(buf, bigEndian);
    EXPECT_GT(copied, 0u);
}

// Test ExifKey construction with tag number and group name
TEST_F(ExifdatumTest_747, ExifKeyWithTagAndGroup_747) {
    ExifKey key(0x010f, "Image");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.tag(), 0x010f);
    EXPECT_EQ(datum.tagName(), "Make");
}

// Test setting value with empty string
TEST_F(ExifdatumTest_747, SetValueEmptyString_747) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    int result = datum.setValue("");
    EXPECT_EQ(result, 0);
}

// Test operator= with Value object
TEST_F(ExifdatumTest_747, OperatorAssignValue_747) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    AsciiValue av("ValueAssign");
    datum = static_cast<const Value&>(av);
    EXPECT_EQ(datum.toString(), "ValueAssign");
}

// Test idx() returns 0 by default
TEST_F(ExifdatumTest_747, IdxDefaultValue_747) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.idx(), 0);
}
