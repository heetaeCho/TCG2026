#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

class ExifdatumTest_737 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test construction with a valid ExifKey
TEST_F(ExifdatumTest_737, ConstructWithValidKey_737) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
    EXPECT_EQ(datum.familyName(), std::string("Exif"));
    EXPECT_EQ(datum.groupName(), "Image");
    EXPECT_EQ(datum.tagName(), "Make");
}

// Test construction with a key and a value
TEST_F(ExifdatumTest_737, ConstructWithKeyAndValue_737) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    Exifdatum datum(key, &val);
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
    EXPECT_EQ(datum.toString(), "Canon");
    EXPECT_EQ(datum.count(), 6u); // "Canon" + null terminator for ASCII
}

// Test copy constructor
TEST_F(ExifdatumTest_737, CopyConstructor_737) {
    ExifKey key("Exif.Image.Model");
    AsciiValue val;
    val.read("TestModel");
    Exifdatum original(key, &val);
    Exifdatum copy(original);
    EXPECT_EQ(copy.key(), original.key());
    EXPECT_EQ(copy.toString(), original.toString());
    EXPECT_EQ(copy.tag(), original.tag());
}

// Test copy assignment operator
TEST_F(ExifdatumTest_737, CopyAssignment_737) {
    ExifKey key1("Exif.Image.Make");
    AsciiValue val1;
    val1.read("Canon");
    Exifdatum datum1(key1, &val1);

    ExifKey key2("Exif.Image.Model");
    AsciiValue val2;
    val2.read("EOS");
    Exifdatum datum2(key2, &val2);

    datum2 = datum1;
    EXPECT_EQ(datum2.key(), "Exif.Image.Make");
    EXPECT_EQ(datum2.toString(), "Canon");
}

// Test operator=(const std::string&)
TEST_F(ExifdatumTest_737, AssignString_737) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Initial");
    Exifdatum datum(key, &val);

    datum = std::string("NewValue");
    EXPECT_EQ(datum.toString(), "NewValue");
}

// Test operator=(const uint16_t&)
TEST_F(ExifdatumTest_737, AssignUint16_737) {
    ExifKey key("Exif.Image.Orientation");
    UShortValue val;
    val.read("1");
    Exifdatum datum(key, &val);

    uint16_t newVal = 3;
    datum = newVal;
    EXPECT_EQ(datum.toInt64(0), 3);
    EXPECT_EQ(datum.typeId(), unsignedShort);
}

// Test operator=(const uint32_t&)
TEST_F(ExifdatumTest_737, AssignUint32_737) {
    ExifKey key("Exif.Image.ImageWidth");
    ULongValue val;
    val.read("100");
    Exifdatum datum(key, &val);

    uint32_t newVal = 1920;
    datum = newVal;
    EXPECT_EQ(datum.toInt64(0), 1920);
    EXPECT_EQ(datum.typeId(), unsignedLong);
}

// Test operator=(const int16_t&)
TEST_F(ExifdatumTest_737, AssignInt16_737) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);

    int16_t newVal = -5;
    datum = newVal;
    EXPECT_EQ(datum.toInt64(0), -5);
    EXPECT_EQ(datum.typeId(), signedShort);
}

// Test operator=(const int32_t&)
TEST_F(ExifdatumTest_737, AssignInt32_737) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);

    int32_t newVal = -1000;
    datum = newVal;
    EXPECT_EQ(datum.toInt64(0), -1000);
    EXPECT_EQ(datum.typeId(), signedLong);
}

// Test operator=(const URational&)
TEST_F(ExifdatumTest_737, AssignURational_737) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);

    URational ur = {72, 1};
    datum = ur;
    EXPECT_EQ(datum.toInt64(0), 72);
    EXPECT_FLOAT_EQ(datum.toFloat(0), 72.0f);
    EXPECT_EQ(datum.typeId(), unsignedRational);
}

// Test operator=(const Rational&) - the specific method from the partial code
TEST_F(ExifdatumTest_737, AssignRational_737) {
    ExifKey key("Exif.Photo.ExposureBiasValue");
    Exifdatum datum(key, nullptr);

    Rational r = {-1, 3};
    datum = r;
    Rational result = datum.toRational(0);
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, 3);
    EXPECT_EQ(datum.typeId(), signedRational);
}

// Test operator=(const Value&)
TEST_F(ExifdatumTest_737, AssignValue_737) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);

    AsciiValue val;
    val.read("TestBrand");
    datum = static_cast<const Value&>(val);
    EXPECT_EQ(datum.toString(), "TestBrand");
}

// Test setValue(const Value* pValue)
TEST_F(ExifdatumTest_737, SetValuePointer_737) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);

    AsciiValue val;
    val.read("Nikon");
    datum.setValue(&val);
    EXPECT_EQ(datum.toString(), "Nikon");
}

// Test setValue(const std::string&) 
TEST_F(ExifdatumTest_737, SetValueString_737) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Initial");
    Exifdatum datum(key, &val);

    int result = datum.setValue("Updated");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "Updated");
}

// Test setValue with nullptr
TEST_F(ExifdatumTest_737, SetValueNullptr_737) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("HasValue");
    Exifdatum datum(key, &val);

    datum.setValue(static_cast<const Value*>(nullptr));
    EXPECT_EQ(datum.count(), 0u);
}

// Test key-related methods
TEST_F(ExifdatumTest_737, KeyMethods_737) {
    ExifKey key("Exif.Photo.DateTimeOriginal");
    Exifdatum datum(key, nullptr);

    EXPECT_EQ(datum.key(), "Exif.Photo.DateTimeOriginal");
    EXPECT_EQ(std::string(datum.familyName()), "Exif");
    EXPECT_EQ(datum.groupName(), "Photo");
    EXPECT_EQ(datum.tagName(), "DateTimeOriginal");
}

// Test tag() returns correct tag number
TEST_F(ExifdatumTest_737, TagNumber_737) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);

    // ImageWidth tag is 0x0100 = 256
    EXPECT_EQ(datum.tag(), 0x0100);
}

// Test typeId, typeName, typeSize for unsigned short value
TEST_F(ExifdatumTest_737, TypeInfoUnsignedShort_737) {
    ExifKey key("Exif.Image.Orientation");
    UShortValue val;
    val.read("1");
    Exifdatum datum(key, &val);

    EXPECT_EQ(datum.typeId(), unsignedShort);
    EXPECT_NE(datum.typeName(), nullptr);
    EXPECT_EQ(std::string(datum.typeName()), "Short");
    EXPECT_EQ(datum.typeSize(), 2u);
}

// Test count and size
TEST_F(ExifdatumTest_737, CountAndSize_737) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Test");
    Exifdatum datum(key, &val);

    EXPECT_GT(datum.count(), 0u);
    EXPECT_GT(datum.size(), 0u);
}

// Test count with no value set
TEST_F(ExifdatumTest_737, CountNoValue_737) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);

    EXPECT_EQ(datum.count(), 0u);
    EXPECT_EQ(datum.size(), 0u);
}

// Test toInt64
TEST_F(ExifdatumTest_737, ToInt64_737) {
    ExifKey key("Exif.Image.Orientation");
    UShortValue val;
    val.read("6");
    Exifdatum datum(key, &val);

    EXPECT_EQ(datum.toInt64(0), 6);
}

// Test toFloat
TEST_F(ExifdatumTest_737, ToFloat_737) {
    ExifKey key("Exif.Image.XResolution");
    URationalValue val;
    val.read("72/1");
    Exifdatum datum(key, &val);

    EXPECT_FLOAT_EQ(datum.toFloat(0), 72.0f);
}

// Test toRational
TEST_F(ExifdatumTest_737, ToRational_737) {
    ExifKey key("Exif.Photo.ExposureBiasValue");
    RationalValue val;
    val.read("1/3");
    Exifdatum datum(key, &val);

    Rational r = datum.toRational(0);
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 3);
}

// Test toString with index
TEST_F(ExifdatumTest_737, ToStringWithIndex_737) {
    ExifKey key("Exif.Image.Orientation");
    UShortValue val;
    val.read("1");
    Exifdatum datum(key, &val);

    std::string s = datum.toString(0);
    EXPECT_EQ(s, "1");
}

// Test getValue returns a unique_ptr
TEST_F(ExifdatumTest_737, GetValue_737) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Sony");
    Exifdatum datum(key, &val);

    auto v = datum.getValue();
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(v->toString(), "Sony");
}

// Test getValue returns nullptr when no value
TEST_F(ExifdatumTest_737, GetValueNoValue_737) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);

    auto v = datum.getValue();
    EXPECT_EQ(v, nullptr);
}

// Test write to ostream
TEST_F(ExifdatumTest_737, WriteToStream_737) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Pentax");
    Exifdatum datum(key, &val);

    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test tagLabel returns something (may be empty for some tags)
TEST_F(ExifdatumTest_737, TagLabel_737) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);

    std::string label = datum.tagLabel();
    // TagLabel should not throw, it may or may not be empty
    EXPECT_NO_THROW(datum.tagLabel());
}

// Test tagDesc
TEST_F(ExifdatumTest_737, TagDesc_737) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);

    EXPECT_NO_THROW(datum.tagDesc());
}

// Test ifdId and ifdName
TEST_F(ExifdatumTest_737, IfdIdAndName_737) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);

    IfdId id = datum.ifdId();
    const char* name = datum.ifdName();
    EXPECT_NE(name, nullptr);
    // IFD0 is the expected IFD for Image group
    EXPECT_EQ(id, IfdId::ifd0Id);
}

// Test copy to buffer
TEST_F(ExifdatumTest_737, CopyToBuffer_737) {
    ExifKey key("Exif.Image.Orientation");
    UShortValue val;
    val.read("1");
    Exifdatum datum(key, &val);

    byte buf[16] = {};
    size_t copied = datum.copy(buf, littleEndian);
    EXPECT_GT(copied, 0u);
}

// Test copy to buffer with no value
TEST_F(ExifdatumTest_737, CopyToBufferNoValue_737) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);

    byte buf[16] = {};
    size_t copied = datum.copy(buf, littleEndian);
    EXPECT_EQ(copied, 0u);
}

// Test Rational with zero denominator
TEST_F(ExifdatumTest_737, AssignRationalZeroDenominator_737) {
    ExifKey key("Exif.Photo.ExposureBiasValue");
    Exifdatum datum(key, nullptr);

    Rational r = {0, 0};
    datum = r;
    Rational result = datum.toRational(0);
    EXPECT_EQ(result.first, 0);
    EXPECT_EQ(result.second, 0);
}

// Test assigning Rational with negative values
TEST_F(ExifdatumTest_737, AssignRationalNegative_737) {
    ExifKey key("Exif.Photo.ExposureBiasValue");
    Exifdatum datum(key, nullptr);

    Rational r = {-2, 1};
    datum = r;
    EXPECT_EQ(datum.toInt64(0), -2);
    EXPECT_FLOAT_EQ(datum.toFloat(0), -2.0f);
}

// Test multiple assignments overwrite
TEST_F(ExifdatumTest_737, MultipleAssignments_737) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);

    uint16_t val1 = 1;
    datum = val1;
    EXPECT_EQ(datum.toInt64(0), 1);

    uint16_t val2 = 8;
    datum = val2;
    EXPECT_EQ(datum.toInt64(0), 8);
}

// Test sizeDataArea with no data area
TEST_F(ExifdatumTest_737, SizeDataAreaNoData_737) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Test");
    Exifdatum datum(key, &val);

    EXPECT_EQ(datum.sizeDataArea(), 0u);
}

// Test dataArea with no data area
TEST_F(ExifdatumTest_737, DataAreaNoData_737) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Test");
    Exifdatum datum(key, &val);

    DataBuf db = datum.dataArea();
    EXPECT_EQ(db.size(), 0u);
}

// Test idx
TEST_F(ExifdatumTest_737, Idx_737) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);

    // idx is default 0
    EXPECT_EQ(datum.idx(), 0);
}

// Test that assigning a Value object by reference properly copies
TEST_F(ExifdatumTest_737, AssignValueRefCopies_737) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);

    AsciiValue val;
    val.read("Fuji");
    datum = static_cast<const Value&>(val);

    // Modify original - should not affect datum
    val.read("Modified");
    EXPECT_EQ(datum.toString(), "Fuji");
}

// Test URational boundary: max values
TEST_F(ExifdatumTest_737, AssignURationalMaxValues_737) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);

    URational ur = {UINT32_MAX, 1};
    datum = ur;
    EXPECT_EQ(datum.toRational(0).first, static_cast<int32_t>(UINT32_MAX));
    EXPECT_EQ(datum.typeId(), unsignedRational);
}

// Test self-assignment
TEST_F(ExifdatumTest_737, SelfAssignment_737) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Leica");
    Exifdatum datum(key, &val);

    datum = datum;
    EXPECT_EQ(datum.toString(), "Leica");
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
}
