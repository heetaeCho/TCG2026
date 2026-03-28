#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/exiv2.hpp>
#include <cstring>

using namespace Exiv2;

class ExifdatumTest_757 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test size() returns 0 when no value is set (default constructed via ExifKey)
TEST_F(ExifdatumTest_757, SizeReturnsZeroWhenNoValue_757) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.size(), 0u);
}

// Test size() returns non-zero when a value is assigned
TEST_F(ExifdatumTest_757, SizeReturnsNonZeroWhenValueSet_757) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Canon");
    EXPECT_GT(datum.size(), 0u);
}

// Test key() returns the correct key string
TEST_F(ExifdatumTest_757, KeyReturnsCorrectString_757) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
}

// Test familyName() returns "Exif"
TEST_F(ExifdatumTest_757, FamilyNameReturnsExif_757) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_STREQ(datum.familyName(), "Exif");
}

// Test groupName()
TEST_F(ExifdatumTest_757, GroupNameReturnsCorrectGroup_757) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "Image");
}

// Test tagName()
TEST_F(ExifdatumTest_757, TagNameReturnsCorrectTag_757) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.tagName(), "Make");
}

// Test tag() returns correct tag number
TEST_F(ExifdatumTest_757, TagReturnsCorrectNumber_757) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    // Make tag is 0x010f
    EXPECT_EQ(datum.tag(), 0x010f);
}

// Test copy constructor
TEST_F(ExifdatumTest_757, CopyConstructorWorks_757) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Nikon");

    Exifdatum copy(datum);
    EXPECT_EQ(copy.key(), "Exif.Image.Make");
    EXPECT_EQ(copy.toString(), datum.toString());
    EXPECT_EQ(copy.size(), datum.size());
}

// Test copy assignment operator
TEST_F(ExifdatumTest_757, CopyAssignmentWorks_757) {
    ExifKey key1("Exif.Image.Make");
    Exifdatum datum1(key1, nullptr);
    datum1.setValue("Canon");

    ExifKey key2("Exif.Image.Model");
    Exifdatum datum2(key2, nullptr);
    datum2.setValue("EOS");

    datum2 = datum1;
    EXPECT_EQ(datum2.key(), "Exif.Image.Make");
    EXPECT_EQ(datum2.toString(), "Canon");
}

// Test operator=(const std::string&)
TEST_F(ExifdatumTest_757, AssignStringValue_757) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("InitialValue");
    datum = std::string("NewValue");
    EXPECT_EQ(datum.toString(), "NewValue");
}

// Test operator=(const uint16_t&)
TEST_F(ExifdatumTest_757, AssignUint16Value_757) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    // Set an initial value so there's a type
    datum.setValue("1");
    uint16_t val = 3;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 3);
}

// Test operator=(const uint32_t&)
TEST_F(ExifdatumTest_757, AssignUint32Value_757) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    datum.setValue("100");
    uint32_t val = 1920;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 1920);
}

// Test operator=(const int16_t&)
TEST_F(ExifdatumTest_757, AssignInt16Value_757) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    datum.setValue("1");
    int16_t val = -5;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), -5);
}

// Test operator=(const int32_t&)
TEST_F(ExifdatumTest_757, AssignInt32Value_757) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    datum.setValue("100");
    int32_t val = -1000;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), -1000);
}

// Test operator=(const URational&)
TEST_F(ExifdatumTest_757, AssignURationalValue_757) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    datum.setValue("72/1");
    URational rat = {300, 1};
    datum = rat;
    EXPECT_EQ(datum.toRational(0), Rational(300, 1));
}

// Test operator=(const Rational&)
TEST_F(ExifdatumTest_757, AssignRationalValue_757) {
    ExifKey key("Exif.Photo.ExposureBiasValue");
    Exifdatum datum(key, nullptr);
    datum.setValue("0/1");
    Rational rat = {-1, 3};
    datum = rat;
    Rational result = datum.toRational(0);
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, 3);
}

// Test setValue with Value pointer
TEST_F(ExifdatumTest_757, SetValueWithValuePointer_757) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    
    auto value = Value::create(asciiString);
    value->read("TestCamera");
    datum.setValue(value.get());
    
    EXPECT_EQ(datum.toString(), "TestCamera");
    EXPECT_GT(datum.size(), 0u);
}

// Test setValue with nullptr resets value
TEST_F(ExifdatumTest_757, SetValueWithNullptrResetsSize_757) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("SomeValue");
    EXPECT_GT(datum.size(), 0u);
    
    datum.setValue(static_cast<const Value*>(nullptr));
    EXPECT_EQ(datum.size(), 0u);
}

// Test toString()
TEST_F(ExifdatumTest_757, ToStringReturnsCorrectValue_757) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("TestManufacturer");
    EXPECT_EQ(datum.toString(), "TestManufacturer");
}

// Test typeId() when value is set as ascii string
TEST_F(ExifdatumTest_757, TypeIdForAsciiString_757) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("SomeString");
    EXPECT_EQ(datum.typeId(), asciiString);
}

// Test count() 
TEST_F(ExifdatumTest_757, CountReturnsCorrectCount_757) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Hello");
    EXPECT_GT(datum.count(), 0u);
}

// Test count returns 0 when no value
TEST_F(ExifdatumTest_757, CountReturnsZeroWhenNoValue_757) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.count(), 0u);
}

// Test getValue() returns valid unique_ptr when value is set
TEST_F(ExifdatumTest_757, GetValueReturnsValidPtr_757) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("TestValue");
    auto val = datum.getValue();
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->toString(), "TestValue");
}

// Test getValue() returns nullptr when no value is set
TEST_F(ExifdatumTest_757, GetValueReturnsNullWhenNoValue_757) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    auto val = datum.getValue();
    EXPECT_EQ(val, nullptr);
}

// Test value() throws when no value is set
TEST_F(ExifdatumTest_757, ValueThrowsWhenNoValue_757) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_THROW(datum.value(), Error);
}

// Test operator=(const Value&)
TEST_F(ExifdatumTest_757, AssignValueObject_757) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    
    auto value = Value::create(asciiString);
    value->read("AssignedValue");
    datum = *value;
    
    EXPECT_EQ(datum.toString(), "AssignedValue");
}

// Test constructed with a Value pointer
TEST_F(ExifdatumTest_757, ConstructWithValue_757) {
    ExifKey key("Exif.Image.Make");
    auto value = Value::create(asciiString);
    value->read("InitialValue");
    Exifdatum datum(key, value.get());
    
    EXPECT_EQ(datum.toString(), "InitialValue");
    EXPECT_GT(datum.size(), 0u);
}

// Test tagLabel() returns a non-empty string for known tags
TEST_F(ExifdatumTest_757, TagLabelReturnsNonEmptyForKnownTag_757) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test idx() returns a value (default should be 0)
TEST_F(ExifdatumTest_757, IdxReturnsValue_757) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    // idx is typically 0 for newly constructed datum
    EXPECT_GE(datum.idx(), 0);
}

// Test ifdId() returns valid ifd id
TEST_F(ExifdatumTest_757, IfdIdReturnsValidId_757) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    IfdId id = datum.ifdId();
    EXPECT_NE(id, ifdIdNotSet);
}

// Test typeName() when value is set
TEST_F(ExifdatumTest_757, TypeNameReturnsCorrectType_757) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Test");
    const char* tn = datum.typeName();
    ASSERT_NE(tn, nullptr);
    EXPECT_STREQ(tn, "Ascii");
}

// Test typeSize() when value is set as ascii
TEST_F(ExifdatumTest_757, TypeSizeForAscii_757) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Test");
    EXPECT_EQ(datum.typeSize(), 1u);
}

// Test sizeDataArea() returns 0 when no data area
TEST_F(ExifdatumTest_757, SizeDataAreaReturnsZeroByDefault_757) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Test");
    EXPECT_EQ(datum.sizeDataArea(), 0u);
}

// Test copy() works for a simple value
TEST_F(ExifdatumTest_757, CopyWritesToBuffer_757) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Test");
    
    size_t sz = datum.size();
    ASSERT_GT(sz, 0u);
    std::vector<byte> buf(sz);
    size_t copied = datum.copy(buf.data(), littleEndian);
    EXPECT_EQ(copied, sz);
}

// Test toFloat when value is numeric
TEST_F(ExifdatumTest_757, ToFloatReturnsCorrectValue_757) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    datum.setValue("72/1");
    EXPECT_FLOAT_EQ(datum.toFloat(0), 72.0f);
}

// Test toInt64 with numeric value
TEST_F(ExifdatumTest_757, ToInt64ReturnsCorrectValue_757) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    datum.setValue("6");
    EXPECT_EQ(datum.toInt64(0), 6);
}

// Test write to ostream
TEST_F(ExifdatumTest_757, WriteToOstream_757) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("TestCamera");
    
    std::ostringstream oss;
    datum.write(oss, nullptr);
    EXPECT_FALSE(oss.str().empty());
}

// Test ExifData container basic operations
TEST_F(ExifdatumTest_757, ExifDataAddAndFind_757) {
    ExifData exifData;
    ExifKey key("Exif.Image.Make");
    
    exifData["Exif.Image.Make"] = "TestCam";
    
    auto pos = exifData.findKey(key);
    ASSERT_NE(pos, exifData.end());
    EXPECT_EQ(pos->toString(), "TestCam");
}

// Test ExifData empty initially
TEST_F(ExifdatumTest_757, ExifDataEmptyInitially_757) {
    ExifData exifData;
    EXPECT_TRUE(exifData.empty());
    EXPECT_EQ(exifData.count(), 0u);
}

// Test ExifData erase
TEST_F(ExifdatumTest_757, ExifDataErase_757) {
    ExifData exifData;
    exifData["Exif.Image.Make"] = "TestCam";
    EXPECT_FALSE(exifData.empty());
    
    ExifKey key("Exif.Image.Make");
    auto pos = exifData.findKey(key);
    ASSERT_NE(pos, exifData.end());
    exifData.erase(pos);
    EXPECT_TRUE(exifData.empty());
}

// Test multiple entries in ExifData
TEST_F(ExifdatumTest_757, ExifDataMultipleEntries_757) {
    ExifData exifData;
    exifData["Exif.Image.Make"] = "Canon";
    exifData["Exif.Image.Model"] = "EOS R5";
    exifData["Exif.Image.Orientation"] = uint16_t(1);
    
    EXPECT_EQ(exifData.count(), 3u);
    
    ExifKey makeKey("Exif.Image.Make");
    auto pos = exifData.findKey(makeKey);
    ASSERT_NE(pos, exifData.end());
    EXPECT_EQ(pos->toString(), "Canon");
}
