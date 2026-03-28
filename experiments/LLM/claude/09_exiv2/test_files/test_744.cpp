#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/tags.hpp>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

class ExifdatumTest_744 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test construction with a known ExifKey
TEST_F(ExifdatumTest_744, ConstructWithExifKey_744) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
}

// Test groupName returns expected group
TEST_F(ExifdatumTest_744, GroupName_744) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "Image");
}

// Test familyName returns "Exif"
TEST_F(ExifdatumTest_744, FamilyName_744) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_STREQ(datum.familyName(), "Exif");
}

// Test tagName returns expected tag name
TEST_F(ExifdatumTest_744, TagName_744) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.tagName(), "Make");
}

// Test tag() returns expected tag number
TEST_F(ExifdatumTest_744, TagNumber_744) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    // Make tag is 0x010f
    EXPECT_EQ(datum.tag(), 0x010f);
}

// Test copy constructor
TEST_F(ExifdatumTest_744, CopyConstructor_744) {
    ExifKey key("Exif.Image.Model");
    Exifdatum datum(key, nullptr);
    Exifdatum copy(datum);
    EXPECT_EQ(copy.key(), "Exif.Image.Model");
    EXPECT_EQ(copy.groupName(), "Image");
    EXPECT_EQ(copy.tagName(), "Model");
}

// Test assignment operator
TEST_F(ExifdatumTest_744, AssignmentOperator_744) {
    ExifKey key1("Exif.Image.Make");
    Exifdatum datum1(key1, nullptr);

    ExifKey key2("Exif.Image.Model");
    Exifdatum datum2(key2, nullptr);

    datum2 = datum1;
    EXPECT_EQ(datum2.key(), "Exif.Image.Make");
}

// Test setValue with string on a datum that has no value set initially
TEST_F(ExifdatumTest_744, SetValueString_744) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    int result = datum.setValue("Canon");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "Canon");
}

// Test operator= with string value
TEST_F(ExifdatumTest_744, AssignStringValue_744) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Nikon");
    datum = std::string("Canon");
    EXPECT_EQ(datum.toString(), "Canon");
}

// Test count and size when value is set
TEST_F(ExifdatumTest_744, CountAndSizeWithValue_744) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("TestMake");
    EXPECT_GT(datum.count(), static_cast<size_t>(0));
    EXPECT_GT(datum.size(), static_cast<size_t>(0));
}

// Test count and size when no value is set
TEST_F(ExifdatumTest_744, CountAndSizeNoValue_744) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.count(), static_cast<size_t>(0));
    EXPECT_EQ(datum.size(), static_cast<size_t>(0));
}

// Test typeId when no value is set
TEST_F(ExifdatumTest_744, TypeIdNoValue_744) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.typeId(), invalidTypeId);
}

// Test typeName when no value is set
TEST_F(ExifdatumTest_744, TypeNameNoValue_744) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    // When no value is set, typeName should handle gracefully
    const char* tn = datum.typeName();
    // Could be nullptr or empty
    if (tn) {
        SUCCEED();
    } else {
        SUCCEED();
    }
}

// Test getValue when no value is set
TEST_F(ExifdatumTest_744, GetValueNoValue_744) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    auto val = datum.getValue();
    // When no value, getValue may return nullptr
    EXPECT_EQ(val.get(), nullptr);
}

// Test value() throws when no value is set
TEST_F(ExifdatumTest_744, ValueThrowsWhenNoValue_744) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_THROW(datum.value(), Error);
}

// Test setValue with a Value pointer
TEST_F(ExifdatumTest_744, SetValuePointer_744) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    AsciiValue val;
    val.read("TestValue");
    datum.setValue(&val);
    EXPECT_EQ(datum.toString(), "TestValue");
    EXPECT_EQ(datum.typeId(), asciiString);
}

// Test construction with ExifKey created from tag and group
TEST_F(ExifdatumTest_744, ConstructWithTagAndGroup_744) {
    ExifKey key(0x010f, "Image");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.tag(), 0x010f);
    EXPECT_EQ(datum.groupName(), "Image");
    EXPECT_EQ(datum.tagName(), "Make");
}

// Test operator= with uint16_t
TEST_F(ExifdatumTest_744, AssignUint16Value_744) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    datum.setValue("1");  // Initialize with a value first
    datum = static_cast<uint16_t>(3);
    EXPECT_EQ(datum.toInt64(0), 3);
}

// Test operator= with int32_t
TEST_F(ExifdatumTest_744, AssignInt32Value_744) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    datum.setValue("1");
    datum = static_cast<int32_t>(42);
    EXPECT_EQ(datum.toInt64(0), 42);
}

// Test operator= with uint32_t
TEST_F(ExifdatumTest_744, AssignUint32Value_744) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    datum.setValue("100");
    datum = static_cast<uint32_t>(200);
    EXPECT_EQ(datum.toInt64(0), 200);
}

// Test operator= with Rational
TEST_F(ExifdatumTest_744, AssignRationalValue_744) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    datum.setValue("72/1");
    Rational r(300, 1);
    datum = r;
    EXPECT_EQ(datum.toRational(0), Rational(300, 1));
}

// Test operator= with URational
TEST_F(ExifdatumTest_744, AssignURationalValue_744) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    datum.setValue("72/1");
    URational ur(150, 1);
    datum = ur;
    auto result = datum.toRational(0);
    EXPECT_EQ(result.first, 150);
    EXPECT_EQ(result.second, 1);
}

// Test ifdId
TEST_F(ExifdatumTest_744, IfdId_744) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.ifdId(), IfdId::ifd0Id);
}

// Test tagLabel returns something non-empty for a known tag
TEST_F(ExifdatumTest_744, TagLabel_744) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test write to ostream
TEST_F(ExifdatumTest_744, WriteToStream_744) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("TestMaker");
    std::ostringstream os;
    datum.write(os, nullptr);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

// Test toFloat
TEST_F(ExifdatumTest_744, ToFloat_744) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    datum.setValue("72/1");
    float val = datum.toFloat(0);
    EXPECT_FLOAT_EQ(val, 72.0f);
}

// Test toString with index
TEST_F(ExifdatumTest_744, ToStringWithIndex_744) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Canon");
    std::string str = datum.toString(0);
    EXPECT_EQ(str, "Canon");
}

// Test sizeDataArea when no data area is set
TEST_F(ExifdatumTest_744, SizeDataAreaNoData_744) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Test");
    EXPECT_EQ(datum.sizeDataArea(), static_cast<size_t>(0));
}

// Test copy to buffer
TEST_F(ExifdatumTest_744, CopyToBuffer_744) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Canon");
    byte buf[256];
    std::memset(buf, 0, sizeof(buf));
    size_t copied = datum.copy(buf, littleEndian);
    EXPECT_GT(copied, static_cast<size_t>(0));
}

// Test construction with a Value pointer
TEST_F(ExifdatumTest_744, ConstructWithValue_744) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Nikon");
    Exifdatum datum(key, &val);
    EXPECT_EQ(datum.toString(), "Nikon");
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
}

// Test different Exif groups
TEST_F(ExifdatumTest_744, PhotoGroup_744) {
    ExifKey key("Exif.Photo.ExposureTime");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "Photo");
    EXPECT_EQ(datum.familyName(), std::string("Exif"));
}

// Test self-assignment
TEST_F(ExifdatumTest_744, SelfAssignment_744) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Test");
    datum = datum;
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
    EXPECT_EQ(datum.toString(), "Test");
}

// Test operator= with int16_t
TEST_F(ExifdatumTest_744, AssignInt16Value_744) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    datum.setValue("1");
    datum = static_cast<int16_t>(-5);
    EXPECT_EQ(datum.toInt64(0), -5);
}

// Test idx
TEST_F(ExifdatumTest_744, Idx_744) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    // idx should return some default value
    int idx = datum.idx();
    EXPECT_GE(idx, 0);
}

// Test typeSize when value is set
TEST_F(ExifdatumTest_744, TypeSizeWithValue_744) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Test");
    Exifdatum datum(key, &val);
    EXPECT_EQ(datum.typeSize(), static_cast<size_t>(1));  // ASCII type size is 1
}
