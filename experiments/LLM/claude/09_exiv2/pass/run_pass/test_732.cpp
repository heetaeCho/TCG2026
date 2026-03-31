#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <sstream>
#include <cstring>

class ExifdatumTest_732 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test construction with a valid ExifKey
TEST_F(ExifdatumTest_732, ConstructWithExifKey_732) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    EXPECT_EQ("Exif.Image.Make", datum.key());
    EXPECT_EQ("Image", datum.groupName());
    EXPECT_EQ("Make", datum.tagName());
    EXPECT_STREQ("Exif", datum.familyName());
}

// Test copy construction
TEST_F(ExifdatumTest_732, CopyConstruction_732) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("Canon");

    Exiv2::Exifdatum copy(datum);
    EXPECT_EQ(datum.key(), copy.key());
    EXPECT_EQ(datum.toString(), copy.toString());
}

// Test copy assignment operator
TEST_F(ExifdatumTest_732, CopyAssignment_732) {
    Exiv2::ExifKey key1("Exif.Image.Make");
    Exiv2::Exifdatum datum1(key1, nullptr);
    datum1 = std::string("Canon");

    Exiv2::ExifKey key2("Exif.Image.Model");
    Exiv2::Exifdatum datum2(key2, nullptr);
    datum2 = datum1;

    EXPECT_EQ(datum1.key(), datum2.key());
    EXPECT_EQ(datum1.toString(), datum2.toString());
}

// Test operator= with uint16_t
TEST_F(ExifdatumTest_732, AssignUint16_732) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = static_cast<uint16_t>(1);

    EXPECT_EQ(1, datum.toInt64(0));
    EXPECT_EQ(Exiv2::unsignedShort, datum.typeId());
    EXPECT_EQ(1u, datum.count());
}

// Test operator= with uint32_t
TEST_F(ExifdatumTest_732, AssignUint32_732) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = static_cast<uint32_t>(1920);

    EXPECT_EQ(1920, datum.toInt64(0));
    EXPECT_EQ(Exiv2::unsignedLong, datum.typeId());
}

// Test operator= with int16_t
TEST_F(ExifdatumTest_732, AssignInt16_732) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = static_cast<int16_t>(-5);

    EXPECT_EQ(-5, datum.toInt64(0));
    EXPECT_EQ(Exiv2::signedShort, datum.typeId());
}

// Test operator= with int32_t
TEST_F(ExifdatumTest_732, AssignInt32_732) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = static_cast<int32_t>(-100);

    EXPECT_EQ(-100, datum.toInt64(0));
    EXPECT_EQ(Exiv2::signedLong, datum.typeId());
}

// Test operator= with string
TEST_F(ExifdatumTest_732, AssignString_732) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("Nikon");

    EXPECT_EQ("Nikon", datum.toString());
}

// Test operator= with URational
TEST_F(ExifdatumTest_732, AssignURational_732) {
    Exiv2::ExifKey key("Exif.Photo.ExposureTime");
    Exiv2::Exifdatum datum(key, nullptr);
    Exiv2::URational ur = {1, 100};
    datum = ur;

    EXPECT_EQ(Exiv2::unsignedRational, datum.typeId());
    Exiv2::Rational r = datum.toRational(0);
    EXPECT_EQ(1, r.first);
    EXPECT_EQ(100, r.second);
}

// Test operator= with Rational
TEST_F(ExifdatumTest_732, AssignRational_732) {
    Exiv2::ExifKey key("Exif.Photo.ExposureBiasValue");
    Exiv2::Exifdatum datum(key, nullptr);
    Exiv2::Rational rat = {-1, 3};
    datum = rat;

    EXPECT_EQ(Exiv2::signedRational, datum.typeId());
    Exiv2::Rational r = datum.toRational(0);
    EXPECT_EQ(-1, r.first);
    EXPECT_EQ(3, r.second);
}

// Test operator= with Value
TEST_F(ExifdatumTest_732, AssignValue_732) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);

    Exiv2::AsciiValue val;
    val.read("TestValue");
    datum = static_cast<const Exiv2::Value&>(val);

    EXPECT_EQ("TestValue", datum.toString());
}

// Test setValue with Value pointer
TEST_F(ExifdatumTest_732, SetValuePointer_732) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);

    Exiv2::AsciiValue val;
    val.read("Hello");
    datum.setValue(&val);

    EXPECT_EQ("Hello", datum.toString());
}

// Test setValue with string
TEST_F(ExifdatumTest_732, SetValueString_732) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    // First set a value type so it knows how to interpret the string
    datum = static_cast<uint16_t>(1);
    int result = datum.setValue("3");
    EXPECT_EQ(0, result);
    EXPECT_EQ(3, datum.toInt64(0));
}

// Test key-related methods
TEST_F(ExifdatumTest_732, KeyMethods_732) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    Exiv2::Exifdatum datum(key, nullptr);

    EXPECT_EQ("Exif.Photo.DateTimeOriginal", datum.key());
    EXPECT_STREQ("Exif", datum.familyName());
    EXPECT_EQ("Photo", datum.groupName());
    EXPECT_EQ("DateTimeOriginal", datum.tagName());
}

// Test tag() returns correct tag number
TEST_F(ExifdatumTest_732, Tag_732) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    // Orientation tag is 0x0112 = 274
    EXPECT_EQ(0x0112, datum.tag());
}

// Test count and size when no value is set
TEST_F(ExifdatumTest_732, NoValueCountAndSize_732) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);

    EXPECT_EQ(0u, datum.count());
    EXPECT_EQ(0u, datum.size());
}

// Test count after assignment
TEST_F(ExifdatumTest_732, CountAfterAssignment_732) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = static_cast<uint16_t>(1);

    EXPECT_EQ(1u, datum.count());
    EXPECT_GT(datum.size(), 0u);
}

// Test typeId when no value is set
TEST_F(ExifdatumTest_732, TypeIdNoValue_732) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);

    EXPECT_EQ(Exiv2::invalidTypeId, datum.typeId());
}

// Test toFloat
TEST_F(ExifdatumTest_732, ToFloat_732) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = static_cast<uint16_t>(42);

    EXPECT_FLOAT_EQ(42.0f, datum.toFloat(0));
}

// Test toInt64
TEST_F(ExifdatumTest_732, ToInt64_732) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = static_cast<uint32_t>(3840);

    EXPECT_EQ(3840, datum.toInt64(0));
}

// Test toRational with integer value
TEST_F(ExifdatumTest_732, ToRationalFromInt_732) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = static_cast<uint16_t>(7);

    Exiv2::Rational r = datum.toRational(0);
    EXPECT_EQ(7, r.first);
    EXPECT_EQ(1, r.second);
}

// Test getValue returns a valid unique_ptr
TEST_F(ExifdatumTest_732, GetValue_732) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("TestMaker");

    auto val = datum.getValue();
    ASSERT_NE(nullptr, val.get());
    EXPECT_EQ("TestMaker", val->toString());
}

// Test getValue when no value is set throws
TEST_F(ExifdatumTest_732, GetValueNoValueThrows_732) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);

    EXPECT_THROW(datum.getValue(), Exiv2::Error);
}

// Test value() when no value is set throws
TEST_F(ExifdatumTest_732, ValueReferenceNoValueThrows_732) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);

    EXPECT_THROW(datum.value(), Exiv2::Error);
}

// Test value() returns reference to the value
TEST_F(ExifdatumTest_732, ValueReference_732) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("Sony");

    const Exiv2::Value& v = datum.value();
    EXPECT_EQ("Sony", v.toString());
}

// Test toString with index
TEST_F(ExifdatumTest_732, ToStringWithIndex_732) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = static_cast<uint16_t>(6);

    EXPECT_EQ("6", datum.toString(0));
}

// Test write to ostream
TEST_F(ExifdatumTest_732, WriteToStream_732) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("Pentax");

    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test copy to buffer
TEST_F(ExifdatumTest_732, CopyToBuffer_732) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = static_cast<uint16_t>(1);

    Exiv2::byte buf[16] = {0};
    size_t copied = datum.copy(buf, Exiv2::littleEndian);
    EXPECT_GT(copied, 0u);
}

// Test sizeDataArea when no data area
TEST_F(ExifdatumTest_732, SizeDataAreaEmpty_732) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("Test");

    EXPECT_EQ(0u, datum.sizeDataArea());
}

// Test tagLabel returns non-empty string for known tag
TEST_F(ExifdatumTest_732, TagLabel_732) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test typeName and typeSize after uint16 assignment
TEST_F(ExifdatumTest_732, TypeNameAndSize_732) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = static_cast<uint16_t>(1);

    EXPECT_NE(nullptr, datum.typeName());
    EXPECT_EQ(2u, datum.typeSize());
}

// Test setting value to nullptr resets
TEST_F(ExifdatumTest_732, SetValueNullptr_732) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("Test");
    EXPECT_EQ(1u, datum.count());

    datum.setValue(static_cast<const Exiv2::Value*>(nullptr));
    EXPECT_EQ(0u, datum.count());
}

// Test multiple assignments overwrite correctly
TEST_F(ExifdatumTest_732, MultipleAssignments_732) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);

    datum = static_cast<uint16_t>(1);
    EXPECT_EQ(1, datum.toInt64(0));

    datum = static_cast<uint16_t>(6);
    EXPECT_EQ(6, datum.toInt64(0));

    datum = static_cast<uint16_t>(8);
    EXPECT_EQ(8, datum.toInt64(0));
}

// Test assignment returns reference to self
TEST_F(ExifdatumTest_732, AssignmentReturnsSelf_732) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);

    Exiv2::Exifdatum& ref = (datum = static_cast<uint16_t>(1));
    EXPECT_EQ(&datum, &ref);
}

// Test string assignment returns reference to self
TEST_F(ExifdatumTest_732, StringAssignmentReturnsSelf_732) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);

    Exiv2::Exifdatum& ref = (datum = std::string("Test"));
    EXPECT_EQ(&datum, &ref);
}

// Test boundary: uint16_t max value
TEST_F(ExifdatumTest_732, Uint16MaxValue_732) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = static_cast<uint16_t>(65535);

    EXPECT_EQ(65535, datum.toInt64(0));
}

// Test boundary: uint16_t zero
TEST_F(ExifdatumTest_732, Uint16ZeroValue_732) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = static_cast<uint16_t>(0);

    EXPECT_EQ(0, datum.toInt64(0));
}

// Test boundary: int16_t min value
TEST_F(ExifdatumTest_732, Int16MinValue_732) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = static_cast<int16_t>(-32768);

    EXPECT_EQ(-32768, datum.toInt64(0));
}

// Test boundary: empty string
TEST_F(ExifdatumTest_732, EmptyStringAssignment_732) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("");

    EXPECT_EQ("", datum.toString());
}

// Test idx returns a value (default)
TEST_F(ExifdatumTest_732, IdxDefault_732) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    // idx should return some integer, typically 0 for a freshly constructed datum
    int idx = datum.idx();
    EXPECT_GE(idx, 0);
}

// Test ifdId
TEST_F(ExifdatumTest_732, IfdId_732) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    Exiv2::IfdId id = datum.ifdId();
    // IfdId for Image should be ifd0Id
    EXPECT_EQ(Exiv2::IfdId::ifd0Id, id);
}

// Test construction with Value pointer
TEST_F(ExifdatumTest_732, ConstructWithValue_732) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::AsciiValue val;
    val.read("Fujifilm");
    Exiv2::Exifdatum datum(key, &val);

    EXPECT_EQ("Fujifilm", datum.toString());
    EXPECT_EQ("Exif.Image.Make", datum.key());
}
