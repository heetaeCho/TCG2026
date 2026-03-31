#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/exiv2.hpp>
#include <cstring>

using namespace Exiv2;

class ExifdatumTest_741 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test construction with a valid ExifKey
TEST_F(ExifdatumTest_741, ConstructWithValidKey_741) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
    EXPECT_EQ(datum.familyName(), std::string("Exif"));
    EXPECT_EQ(datum.groupName(), "Image");
    EXPECT_EQ(datum.tagName(), "Make");
}

// Test copy construction
TEST_F(ExifdatumTest_741, CopyConstruction_741) {
    ExifKey key("Exif.Image.Model");
    Exifdatum datum1(key);
    datum1.setValue("Canon EOS 5D");
    Exifdatum datum2(datum1);
    EXPECT_EQ(datum2.key(), "Exif.Image.Model");
    EXPECT_EQ(datum2.toString(), "Canon EOS 5D");
}

// Test copy assignment operator
TEST_F(ExifdatumTest_741, CopyAssignment_741) {
    ExifKey key1("Exif.Image.Make");
    Exifdatum datum1(key1);
    datum1.setValue("Nikon");

    ExifKey key2("Exif.Image.Model");
    Exifdatum datum2(key2);
    datum2 = datum1;

    EXPECT_EQ(datum2.key(), "Exif.Image.Make");
    EXPECT_EQ(datum2.toString(), "Nikon");
}

// Test setValue with string
TEST_F(ExifdatumTest_741, SetValueString_741) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    // First set a value type so setValue(string) can parse
    AsciiValue av;
    datum.setValue(&av);
    int result = datum.setValue("TestMake");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "TestMake");
}

// Test assignment operator with string
TEST_F(ExifdatumTest_741, AssignString_741) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum = "SomeManufacturer";
    EXPECT_EQ(datum.toString(), "SomeManufacturer");
}

// Test assignment operator with uint16_t
TEST_F(ExifdatumTest_741, AssignUint16_741) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    uint16_t val = 1;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 1);
}

// Test assignment operator with uint32_t
TEST_F(ExifdatumTest_741, AssignUint32_741) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key);
    uint32_t val = 4000;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 4000);
}

// Test assignment operator with int16_t
TEST_F(ExifdatumTest_741, AssignInt16_741) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    int16_t val = -5;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), -5);
}

// Test assignment operator with int32_t
TEST_F(ExifdatumTest_741, AssignInt32_741) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key);
    int32_t val = -100;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), -100);
}

// Test assignment operator with URational
TEST_F(ExifdatumTest_741, AssignURational_741) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key);
    URational ur = {72, 1};
    datum = ur;
    EXPECT_EQ(datum.toInt64(0), 72);
}

// Test assignment operator with Rational
TEST_F(ExifdatumTest_741, AssignRational_741) {
    ExifKey key("Exif.Photo.ExposureBiasValue");
    Exifdatum datum(key);
    Rational r = {-1, 3};
    datum = r;
    Rational result = datum.toRational(0);
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, 3);
}

// Test assignment with Value object
TEST_F(ExifdatumTest_741, AssignValue_741) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    AsciiValue av;
    av.read("TestValue");
    datum = av;
    EXPECT_EQ(datum.toString(), "TestValue");
}

// Test tag() returns correct tag number
TEST_F(ExifdatumTest_741, TagNumber_741) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    EXPECT_EQ(datum.tag(), 0x010f);
}

// Test typeId when no value is set
TEST_F(ExifdatumTest_741, TypeIdNoValue_741) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    // When no value is set, typeId should return the default for the key
    TypeId tid = datum.typeId();
    // Make is typically asciiString
    EXPECT_EQ(tid, asciiString);
}

// Test count when no value is set
TEST_F(ExifdatumTest_741, CountNoValue_741) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    EXPECT_EQ(datum.count(), 0u);
}

// Test size when no value is set
TEST_F(ExifdatumTest_741, SizeNoValue_741) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    EXPECT_EQ(datum.size(), 0u);
}

// Test setDataArea when value_ is null (returns -1)
TEST_F(ExifdatumTest_741, SetDataAreaNoValue_741) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    // With no value set, setDataArea should return -1
    byte buf[] = {0x01, 0x02, 0x03};
    int result = datum.setDataArea(buf, sizeof(buf));
    EXPECT_EQ(result, -1);
}

// Test setDataArea when value_ is set
TEST_F(ExifdatumTest_741, SetDataAreaWithValue_741) {
    ExifKey key("Exif.Image.StripOffsets");
    Exifdatum datum(key);
    // Set a value first - DataValue supports data area operations
    auto val = Value::create(unsignedLong);
    datum.setValue(val.get());

    byte buf[] = {0x01, 0x02, 0x03, 0x04};
    int result = datum.setDataArea(buf, sizeof(buf));
    // Most Value implementations return -1 from setDataArea (base implementation)
    // The exact result depends on the Value type
    // We just verify it doesn't crash and returns an int
    (void)result;
}

// Test setDataArea with null buffer
TEST_F(ExifdatumTest_741, SetDataAreaNullBuffer_741) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    int result = datum.setDataArea(nullptr, 0);
    EXPECT_EQ(result, -1);
}

// Test setDataArea with zero length
TEST_F(ExifdatumTest_741, SetDataAreaZeroLength_741) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    byte buf[] = {0x01};
    int result = datum.setDataArea(buf, 0);
    EXPECT_EQ(result, -1);
}

// Test getValue when no value is set
TEST_F(ExifdatumTest_741, GetValueNoValue_741) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    auto val = datum.getValue();
    EXPECT_EQ(val, nullptr);
}

// Test getValue when value is set
TEST_F(ExifdatumTest_741, GetValueWithValue_741) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum = "TestValue";
    auto val = datum.getValue();
    EXPECT_NE(val, nullptr);
}

// Test sizeDataArea when no value is set
TEST_F(ExifdatumTest_741, SizeDataAreaNoValue_741) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    EXPECT_EQ(datum.sizeDataArea(), 0u);
}

// Test key properties
TEST_F(ExifdatumTest_741, KeyProperties_741) {
    ExifKey key("Exif.Photo.DateTimeOriginal");
    Exifdatum datum(key);
    EXPECT_EQ(datum.key(), "Exif.Photo.DateTimeOriginal");
    EXPECT_EQ(std::string(datum.familyName()), "Exif");
    EXPECT_EQ(datum.groupName(), "Photo");
    EXPECT_EQ(datum.tagName(), "DateTimeOriginal");
    EXPECT_EQ(datum.tag(), 0x9003);
}

// Test tagLabel returns a non-empty string for known tags
TEST_F(ExifdatumTest_741, TagLabel_741) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test write to stream
TEST_F(ExifdatumTest_741, WriteToStream_741) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum = "Canon";
    std::ostringstream os;
    datum.write(os, nullptr);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

// Test toString with index
TEST_F(ExifdatumTest_741, ToStringWithIndex_741) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum = "TestString";
    std::string result = datum.toString(0);
    EXPECT_EQ(result, "TestString");
}

// Test toFloat
TEST_F(ExifdatumTest_741, ToFloat_741) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key);
    URational ur = {72, 1};
    datum = ur;
    float val = datum.toFloat(0);
    EXPECT_FLOAT_EQ(val, 72.0f);
}

// Test idx
TEST_F(ExifdatumTest_741, Idx_741) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    int idx = datum.idx();
    // idx is typically 0 for a newly created datum
    EXPECT_EQ(idx, 0);
}

// Test setValue with Value pointer (nullptr)
TEST_F(ExifdatumTest_741, SetValueNullPtr_741) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue(nullptr);
    EXPECT_EQ(datum.count(), 0u);
}

// Test typeName
TEST_F(ExifdatumTest_741, TypeName_741) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum = "Test";
    const char* tn = datum.typeName();
    EXPECT_NE(tn, nullptr);
    EXPECT_EQ(std::string(tn), "Ascii");
}

// Test typeSize
TEST_F(ExifdatumTest_741, TypeSize_741) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum = "Test";
    size_t ts = datum.typeSize();
    EXPECT_EQ(ts, 1u); // Ascii type size is 1
}

// Test copy to buffer
TEST_F(ExifdatumTest_741, CopyToBuffer_741) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    uint16_t val = 1;
    datum = val;
    
    byte buf[16] = {};
    size_t copied = datum.copy(buf, littleEndian);
    EXPECT_GT(copied, 0u);
}

// Test dataArea when no value set
TEST_F(ExifdatumTest_741, DataAreaNoValue_741) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    DataBuf db = datum.dataArea();
    EXPECT_EQ(db.size(), 0u);
}

// Test multiple assignments overwrite value
TEST_F(ExifdatumTest_741, MultipleAssignments_741) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum = "First";
    EXPECT_EQ(datum.toString(), "First");
    datum = "Second";
    EXPECT_EQ(datum.toString(), "Second");
}

// Test ifdId
TEST_F(ExifdatumTest_741, IfdId_741) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    IfdId id = datum.ifdId();
    // Exif.Image tags belong to IfdId ifd0Id
    EXPECT_EQ(id, IfdId::ifd0Id);
}

// Test ifdName
TEST_F(ExifdatumTest_741, IfdName_741) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    const char* name = datum.ifdName();
    EXPECT_NE(name, nullptr);
}
