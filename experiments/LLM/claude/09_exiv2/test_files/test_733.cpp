#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <cstdint>
#include <string>
#include <memory>

class ExifdatumTest_733 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test constructing an Exifdatum with a known ExifKey
TEST_F(ExifdatumTest_733, ConstructWithExifKey_733) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
    EXPECT_EQ(datum.familyName(), std::string("Exif"));
    EXPECT_EQ(datum.groupName(), "Image");
    EXPECT_EQ(datum.tagName(), "Make");
}

// Test copy constructor
TEST_F(ExifdatumTest_733, CopyConstructor_733) {
    Exiv2::ExifKey key("Exif.Image.Model");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("TestCamera");

    Exiv2::Exifdatum copy(datum);
    EXPECT_EQ(copy.key(), "Exif.Image.Model");
    EXPECT_EQ(copy.toString(), "TestCamera");
}

// Test copy assignment operator
TEST_F(ExifdatumTest_733, CopyAssignment_733) {
    Exiv2::ExifKey key1("Exif.Image.Make");
    Exiv2::Exifdatum datum1(key1, nullptr);
    datum1 = std::string("Canon");

    Exiv2::ExifKey key2("Exif.Image.Model");
    Exiv2::Exifdatum datum2(key2, nullptr);
    datum2 = datum1;

    EXPECT_EQ(datum2.key(), "Exif.Image.Make");
    EXPECT_EQ(datum2.toString(), "Canon");
}

// Test assignment with string value
TEST_F(ExifdatumTest_733, AssignStringValue_733) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("Nikon");

    EXPECT_EQ(datum.toString(), "Nikon");
    EXPECT_EQ(datum.count(), 1u);
}

// Test assignment with uint16_t value
TEST_F(ExifdatumTest_733, AssignUint16Value_733) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    uint16_t val = 6;
    datum = val;

    EXPECT_EQ(datum.toInt64(0), 6);
    EXPECT_EQ(datum.count(), 1u);
}

// Test assignment with uint32_t value
TEST_F(ExifdatumTest_733, AssignUint32Value_733) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    Exiv2::Exifdatum datum(key, nullptr);
    uint32_t val = 4000;
    datum = val;

    EXPECT_EQ(datum.toInt64(0), 4000);
    EXPECT_EQ(datum.count(), 1u);
}

// Test assignment with int16_t value
TEST_F(ExifdatumTest_733, AssignInt16Value_733) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    int16_t val = -3;
    datum = val;

    EXPECT_EQ(datum.toInt64(0), -3);
}

// Test assignment with int32_t value
TEST_F(ExifdatumTest_733, AssignInt32Value_733) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    Exiv2::Exifdatum datum(key, nullptr);
    int32_t val = -100;
    datum = val;

    EXPECT_EQ(datum.toInt64(0), -100);
}

// Test assignment with URational value
TEST_F(ExifdatumTest_733, AssignURationalValue_733) {
    Exiv2::ExifKey key("Exif.Photo.ExposureTime");
    Exiv2::Exifdatum datum(key, nullptr);
    Exiv2::URational val(1, 250);
    datum = val;

    EXPECT_EQ(datum.count(), 1u);
    Exiv2::Rational r = datum.toRational(0);
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 250);
}

// Test assignment with Rational value
TEST_F(ExifdatumTest_733, AssignRationalValue_733) {
    Exiv2::ExifKey key("Exif.Photo.ExposureBiasValue");
    Exiv2::Exifdatum datum(key, nullptr);
    Exiv2::Rational val(-1, 3);
    datum = val;

    EXPECT_EQ(datum.count(), 1u);
    Exiv2::Rational r = datum.toRational(0);
    EXPECT_EQ(r.first, -1);
    EXPECT_EQ(r.second, 3);
}

// Test key() returns correct key string
TEST_F(ExifdatumTest_733, KeyReturnsCorrectString_733) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    Exiv2::Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Exif.Photo.DateTimeOriginal");
}

// Test familyName()
TEST_F(ExifdatumTest_733, FamilyNameReturnsExif_733) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    EXPECT_STREQ(datum.familyName(), "Exif");
}

// Test tag()
TEST_F(ExifdatumTest_733, TagReturnsCorrectValue_733) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    // Orientation tag number is 0x0112 = 274
    EXPECT_EQ(datum.tag(), 0x0112);
}

// Test tagLabel() returns non-empty string for known tags
TEST_F(ExifdatumTest_733, TagLabelReturnsNonEmpty_733) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test setValue with string
TEST_F(ExifdatumTest_733, SetValueWithString_733) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    int result = datum.setValue("TestValue");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "TestValue");
}

// Test setValue with Value pointer (nullptr)
TEST_F(ExifdatumTest_733, SetValueWithNullptr_733) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum.setValue(nullptr);
    // After setting nullptr, getValue should return nullptr
    auto val = datum.getValue();
    EXPECT_EQ(val.get(), nullptr);
}

// Test typeId when no value is set
TEST_F(ExifdatumTest_733, TypeIdWhenNoValue_733) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    // When no value is set, typeId should return invalidTypeId or some default
    // The behavior depends on implementation, but it should not crash
    Exiv2::TypeId tid = datum.typeId();
    (void)tid; // Just ensure no crash
}

// Test count() when no value is set
TEST_F(ExifdatumTest_733, CountWhenNoValue_733) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.count(), 0u);
}

// Test size() when no value is set
TEST_F(ExifdatumTest_733, SizeWhenNoValue_733) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.size(), 0u);
}

// Test toString() with index
TEST_F(ExifdatumTest_733, ToStringWithIndex_733) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("Hello");
    std::string s = datum.toString(0);
    EXPECT_EQ(s, "Hello");
}

// Test toFloat
TEST_F(ExifdatumTest_733, ToFloat_733) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    Exiv2::Exifdatum datum(key, nullptr);
    uint32_t val = 1920;
    datum = val;
    float f = datum.toFloat(0);
    EXPECT_FLOAT_EQ(f, 1920.0f);
}

// Test toInt64
TEST_F(ExifdatumTest_733, ToInt64_733) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    Exiv2::Exifdatum datum(key, nullptr);
    uint32_t val = 3840;
    datum = val;
    int64_t i = datum.toInt64(0);
    EXPECT_EQ(i, 3840);
}

// Test getValue returns a valid unique_ptr when value is set
TEST_F(ExifdatumTest_733, GetValueReturnsValid_733) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("TestMaker");
    auto val = datum.getValue();
    ASSERT_NE(val.get(), nullptr);
    EXPECT_EQ(val->toString(), "TestMaker");
}

// Test value() throws when no value is set
TEST_F(ExifdatumTest_733, ValueThrowsWhenNoValue_733) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    EXPECT_THROW(datum.value(), Exiv2::Error);
}

// Test assignment with Value object
TEST_F(ExifdatumTest_733, AssignWithValueObject_733) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);

    Exiv2::AsciiValue asciiVal("TestBrand");
    datum = static_cast<const Exiv2::Value&>(asciiVal);

    EXPECT_EQ(datum.toString(), "TestBrand");
}

// Test sizeDataArea when no data area is set
TEST_F(ExifdatumTest_733, SizeDataAreaWhenEmpty_733) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("Test");
    EXPECT_EQ(datum.sizeDataArea(), 0u);
}

// Test groupName()
TEST_F(ExifdatumTest_733, GroupName_733) {
    Exiv2::ExifKey key("Exif.Photo.FNumber");
    Exiv2::Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "Photo");
}

// Test tagName()
TEST_F(ExifdatumTest_733, TagName_733) {
    Exiv2::ExifKey key("Exif.Photo.FNumber");
    Exiv2::Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.tagName(), "FNumber");
}

// Test idx() returns a valid index
TEST_F(ExifdatumTest_733, IdxReturnsValue_733) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    int idx = datum.idx();
    EXPECT_EQ(idx, 0); // Default idx should be 0
}

// Test assigning uint32_t boundary value 0
TEST_F(ExifdatumTest_733, AssignUint32Zero_733) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    Exiv2::Exifdatum datum(key, nullptr);
    uint32_t val = 0;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 0);
}

// Test assigning uint32_t max value
TEST_F(ExifdatumTest_733, AssignUint32Max_733) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    Exiv2::Exifdatum datum(key, nullptr);
    uint32_t val = UINT32_MAX;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), static_cast<int64_t>(UINT32_MAX));
}

// Test assigning uint16_t max value
TEST_F(ExifdatumTest_733, AssignUint16Max_733) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    uint16_t val = UINT16_MAX;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), static_cast<int64_t>(UINT16_MAX));
}

// Test assigning empty string
TEST_F(ExifdatumTest_733, AssignEmptyString_733) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("");
    EXPECT_EQ(datum.toString(), "");
}

// Test construct with a Value pointer
TEST_F(ExifdatumTest_733, ConstructWithValue_733) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::AsciiValue val("InitialValue");
    Exiv2::Exifdatum datum(key, &val);
    EXPECT_EQ(datum.toString(), "InitialValue");
    EXPECT_EQ(datum.count(), 1u);
}

// Test typeName when value is set
TEST_F(ExifdatumTest_733, TypeNameWhenValueSet_733) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("Test");
    const char* tn = datum.typeName();
    ASSERT_NE(tn, nullptr);
    EXPECT_EQ(std::string(tn), "Ascii");
}

// Test typeSize when value is set to uint32
TEST_F(ExifdatumTest_733, TypeSizeForUint32_733) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    Exiv2::Exifdatum datum(key, nullptr);
    uint32_t val = 100;
    datum = val;
    EXPECT_EQ(datum.typeSize(), 4u);
}

// Test typeSize when value is set to uint16
TEST_F(ExifdatumTest_733, TypeSizeForUint16_733) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    uint16_t val = 1;
    datum = val;
    EXPECT_EQ(datum.typeSize(), 2u);
}

// Test ifdName returns non-null
TEST_F(ExifdatumTest_733, IfdNameReturnsNonNull_733) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    const char* name = datum.ifdName();
    ASSERT_NE(name, nullptr);
}

// Test writing to an ostream
TEST_F(ExifdatumTest_733, WriteToOstream_733) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("TestBrand");
    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test copy to buffer
TEST_F(ExifdatumTest_733, CopyToBuffer_733) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    Exiv2::Exifdatum datum(key, nullptr);
    uint32_t val = 1024;
    datum = val;

    Exiv2::byte buf[16] = {0};
    size_t copied = datum.copy(buf, Exiv2::littleEndian);
    EXPECT_GT(copied, 0u);
}

// Test dataArea when no data area
TEST_F(ExifdatumTest_733, DataAreaWhenEmpty_733) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("Test");
    Exiv2::DataBuf db = datum.dataArea();
    EXPECT_EQ(db.size(), 0u);
}

// Test self-assignment does not corrupt data
TEST_F(ExifdatumTest_733, SelfAssignment_733) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("SelfTest");
    datum = datum;
    EXPECT_EQ(datum.toString(), "SelfTest");
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
}

// Test Rational with zero denominator
TEST_F(ExifdatumTest_733, RationalZeroDenominator_733) {
    Exiv2::ExifKey key("Exif.Photo.ExposureBiasValue");
    Exiv2::Exifdatum datum(key, nullptr);
    Exiv2::Rational val(0, 0);
    datum = val;
    Exiv2::Rational r = datum.toRational(0);
    EXPECT_EQ(r.first, 0);
    EXPECT_EQ(r.second, 0);
}

// Test multiple reassignments
TEST_F(ExifdatumTest_733, MultipleReassignments_733) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);

    datum = std::string("First");
    EXPECT_EQ(datum.toString(), "First");

    datum = std::string("Second");
    EXPECT_EQ(datum.toString(), "Second");

    datum = std::string("Third");
    EXPECT_EQ(datum.toString(), "Third");
}
