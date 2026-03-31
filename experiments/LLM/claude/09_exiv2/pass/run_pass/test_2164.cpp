#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/tags.hpp>
#include <exiv2/value.hpp>
#include <sstream>
#include <memory>

using namespace Exiv2;

class ExifdatumTest_2164 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test construction with ExifKey and no value
TEST_F(ExifdatumTest_2164, ConstructWithKeyNoValue_2164) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
    EXPECT_EQ(datum.familyName(), std::string("Exif"));
    EXPECT_EQ(datum.groupName(), "Image");
    EXPECT_EQ(datum.tagName(), "Make");
}

// Test construction with ExifKey and a value
TEST_F(ExifdatumTest_2164, ConstructWithKeyAndValue_2164) {
    ExifKey key("Exif.Image.Model");
    auto value = Value::create(asciiString);
    value->read("Canon EOS R5");
    Exifdatum datum(key, value.get());
    EXPECT_EQ(datum.key(), "Exif.Image.Model");
    EXPECT_EQ(datum.toString(), "Canon EOS R5");
    EXPECT_EQ(datum.count(), 13u); // includes null terminator for ASCII
}

// Test copy constructor with value
TEST_F(ExifdatumTest_2164, CopyConstructorWithValue_2164) {
    ExifKey key("Exif.Image.Make");
    auto value = Value::create(asciiString);
    value->read("Nikon");
    Exifdatum original(key, value.get());
    
    Exifdatum copy(original);
    EXPECT_EQ(copy.key(), "Exif.Image.Make");
    EXPECT_EQ(copy.toString(), "Nikon");
    EXPECT_EQ(copy.count(), original.count());
}

// Test copy constructor without value (nullptr)
TEST_F(ExifdatumTest_2164, CopyConstructorWithoutValue_2164) {
    ExifKey key("Exif.Image.Make");
    Exifdatum original(key, nullptr);
    
    Exifdatum copy(original);
    EXPECT_EQ(copy.key(), "Exif.Image.Make");
}

// Test copy constructor deep copy independence
TEST_F(ExifdatumTest_2164, CopyConstructorDeepCopy_2164) {
    ExifKey key("Exif.Image.Make");
    auto value = Value::create(asciiString);
    value->read("Sony");
    Exifdatum original(key, value.get());
    
    Exifdatum copy(original);
    
    // Modify original
    original.setValue("Canon");
    
    // Copy should remain unchanged
    EXPECT_EQ(copy.toString(), "Sony");
    EXPECT_EQ(original.toString(), "Canon");
}

// Test assignment operator
TEST_F(ExifdatumTest_2164, AssignmentOperator_2164) {
    ExifKey key1("Exif.Image.Make");
    auto value1 = Value::create(asciiString);
    value1->read("Sony");
    Exifdatum datum1(key1, value1.get());
    
    ExifKey key2("Exif.Image.Model");
    auto value2 = Value::create(asciiString);
    value2->read("Alpha");
    Exifdatum datum2(key2, value2.get());
    
    datum2 = datum1;
    EXPECT_EQ(datum2.key(), "Exif.Image.Make");
    EXPECT_EQ(datum2.toString(), "Sony");
}

// Test assignment operator deep copy independence
TEST_F(ExifdatumTest_2164, AssignmentOperatorDeepCopy_2164) {
    ExifKey key1("Exif.Image.Make");
    auto value1 = Value::create(asciiString);
    value1->read("Pentax");
    Exifdatum datum1(key1, value1.get());
    
    ExifKey key2("Exif.Image.Model");
    Exifdatum datum2(key2, nullptr);
    
    datum2 = datum1;
    datum1.setValue("Olympus");
    
    EXPECT_EQ(datum2.toString(), "Pentax");
    EXPECT_EQ(datum1.toString(), "Olympus");
}

// Test self-assignment
TEST_F(ExifdatumTest_2164, SelfAssignment_2164) {
    ExifKey key("Exif.Image.Make");
    auto value = Value::create(asciiString);
    value->read("Fuji");
    Exifdatum datum(key, value.get());
    
    datum = datum;
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
    EXPECT_EQ(datum.toString(), "Fuji");
}

// Test setValue with string
TEST_F(ExifdatumTest_2164, SetValueString_2164) {
    ExifKey key("Exif.Image.Make");
    auto value = Value::create(asciiString);
    value->read("Initial");
    Exifdatum datum(key, value.get());
    
    datum.setValue("Updated");
    EXPECT_EQ(datum.toString(), "Updated");
}

// Test setValue with Value pointer
TEST_F(ExifdatumTest_2164, SetValuePointer_2164) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    
    auto value = Value::create(asciiString);
    value->read("TestValue");
    datum.setValue(value.get());
    
    EXPECT_EQ(datum.toString(), "TestValue");
}

// Test assignment operator with uint16_t
TEST_F(ExifdatumTest_2164, AssignUint16_2164) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    
    uint16_t val = 6;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 6);
}

// Test assignment operator with uint32_t
TEST_F(ExifdatumTest_2164, AssignUint32_2164) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    
    uint32_t val = 4000;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 4000);
}

// Test assignment operator with int16_t
TEST_F(ExifdatumTest_2164, AssignInt16_2164) {
    ExifKey key("Exif.Photo.ExposureCompensation");
    Exifdatum datum(key, nullptr);
    
    int16_t val = -3;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), -3);
}

// Test assignment operator with int32_t
TEST_F(ExifdatumTest_2164, AssignInt32_2164) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    
    int32_t val = 8000;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 8000);
}

// Test assignment operator with string
TEST_F(ExifdatumTest_2164, AssignString_2164) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    
    std::string val = "TestMake";
    datum = val;
    EXPECT_EQ(datum.toString(), "TestMake");
}

// Test assignment operator with Rational
TEST_F(ExifdatumTest_2164, AssignRational_2164) {
    ExifKey key("Exif.Photo.ExposureTime");
    Exifdatum datum(key, nullptr);
    
    Rational val(1, 250);
    datum = val;
    Rational result = datum.toRational(0);
    EXPECT_EQ(result.first, 1);
    EXPECT_EQ(result.second, 250);
}

// Test assignment operator with URational
TEST_F(ExifdatumTest_2164, AssignURational_2164) {
    ExifKey key("Exif.Photo.FNumber");
    Exifdatum datum(key, nullptr);
    
    URational val(28, 10);
    datum = val;
    EXPECT_FLOAT_EQ(datum.toFloat(0), 2.8f);
}

// Test assignment operator with Value reference
TEST_F(ExifdatumTest_2164, AssignValueRef_2164) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    
    auto value = Value::create(asciiString);
    value->read("TestAssign");
    datum = *value;
    
    EXPECT_EQ(datum.toString(), "TestAssign");
}

// Test key properties
TEST_F(ExifdatumTest_2164, KeyProperties_2164) {
    ExifKey key("Exif.Image.Make");
    auto value = Value::create(asciiString);
    value->read("TestMake");
    Exifdatum datum(key, value.get());
    
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
    EXPECT_EQ(std::string(datum.familyName()), "Exif");
    EXPECT_EQ(datum.groupName(), "Image");
    EXPECT_EQ(datum.tagName(), "Make");
    EXPECT_EQ(datum.tag(), 0x010f);
}

// Test tag label and description
TEST_F(ExifdatumTest_2164, TagLabelAndDesc_2164) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test typeId, typeName, typeSize for ASCII value
TEST_F(ExifdatumTest_2164, TypeInfoAscii_2164) {
    ExifKey key("Exif.Image.Make");
    auto value = Value::create(asciiString);
    value->read("TestMake");
    Exifdatum datum(key, value.get());
    
    EXPECT_EQ(datum.typeId(), asciiString);
    EXPECT_NE(datum.typeName(), nullptr);
    EXPECT_EQ(datum.typeSize(), 1u);
}

// Test count and size
TEST_F(ExifdatumTest_2164, CountAndSize_2164) {
    ExifKey key("Exif.Image.Make");
    auto value = Value::create(asciiString);
    value->read("Test");
    Exifdatum datum(key, value.get());
    
    EXPECT_GT(datum.count(), 0u);
    EXPECT_GT(datum.size(), 0u);
}

// Test toString with index
TEST_F(ExifdatumTest_2164, ToStringWithIndex_2164) {
    ExifKey key("Exif.Image.Make");
    auto value = Value::create(asciiString);
    value->read("TestBrand");
    Exifdatum datum(key, value.get());
    
    EXPECT_EQ(datum.toString(0), "TestBrand");
}

// Test toFloat
TEST_F(ExifdatumTest_2164, ToFloat_2164) {
    ExifKey key("Exif.Photo.FNumber");
    Exifdatum datum(key, nullptr);
    
    URational val(56, 10);
    datum = val;
    EXPECT_FLOAT_EQ(datum.toFloat(0), 5.6f);
}

// Test getValue returns a unique copy
TEST_F(ExifdatumTest_2164, GetValueReturnsUniqueCopy_2164) {
    ExifKey key("Exif.Image.Make");
    auto value = Value::create(asciiString);
    value->read("TestCopy");
    Exifdatum datum(key, value.get());
    
    auto retrieved = datum.getValue();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->toString(), "TestCopy");
}

// Test value() returns reference
TEST_F(ExifdatumTest_2164, ValueReturnsReference_2164) {
    ExifKey key("Exif.Image.Make");
    auto value = Value::create(asciiString);
    value->read("RefTest");
    Exifdatum datum(key, value.get());
    
    const Value& ref = datum.value();
    EXPECT_EQ(ref.toString(), "RefTest");
}

// Test ifdId
TEST_F(ExifdatumTest_2164, IfdId_2164) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    
    IfdId id = datum.ifdId();
    // ifdId for Image group should be ifd0Id
    EXPECT_NE(static_cast<int>(id), -1);
}

// Test ifdName
TEST_F(ExifdatumTest_2164, IfdName_2164) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    
    const char* name = datum.ifdName();
    EXPECT_NE(name, nullptr);
}

// Test idx
TEST_F(ExifdatumTest_2164, Idx_2164) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    
    // idx should return some default value
    int idx = datum.idx();
    (void)idx; // just ensure it doesn't crash
}

// Test write to ostream
TEST_F(ExifdatumTest_2164, WriteToOstream_2164) {
    ExifKey key("Exif.Image.Make");
    auto value = Value::create(asciiString);
    value->read("StreamTest");
    Exifdatum datum(key, value.get());
    
    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test copy to buffer
TEST_F(ExifdatumTest_2164, CopyToBuffer_2164) {
    ExifKey key("Exif.Image.Make");
    auto value = Value::create(asciiString);
    value->read("BufTest");
    Exifdatum datum(key, value.get());
    
    size_t dataSize = datum.size();
    std::vector<byte> buf(dataSize + 10, 0);
    size_t copied = datum.copy(buf.data(), littleEndian);
    EXPECT_GT(copied, 0u);
}

// Test sizeDataArea with no data area
TEST_F(ExifdatumTest_2164, SizeDataAreaEmpty_2164) {
    ExifKey key("Exif.Image.Make");
    auto value = Value::create(asciiString);
    value->read("NoDataArea");
    Exifdatum datum(key, value.get());
    
    EXPECT_EQ(datum.sizeDataArea(), 0u);
}

// Test dataArea with no data area
TEST_F(ExifdatumTest_2164, DataAreaEmpty_2164) {
    ExifKey key("Exif.Image.Make");
    auto value = Value::create(asciiString);
    value->read("NoDataArea");
    Exifdatum datum(key, value.get());
    
    DataBuf area = datum.dataArea();
    EXPECT_EQ(area.size(), 0u);
}

// Test with numeric value (unsigned short)
TEST_F(ExifdatumTest_2164, NumericUnsignedShortValue_2164) {
    ExifKey key("Exif.Image.Orientation");
    auto value = Value::create(unsignedShort);
    value->read("1");
    Exifdatum datum(key, value.get());
    
    EXPECT_EQ(datum.toInt64(0), 1);
    EXPECT_EQ(datum.typeId(), unsignedShort);
}

// Test with unsigned long value
TEST_F(ExifdatumTest_2164, NumericUnsignedLongValue_2164) {
    ExifKey key("Exif.Image.ImageWidth");
    auto value = Value::create(unsignedLong);
    value->read("6000");
    Exifdatum datum(key, value.get());
    
    EXPECT_EQ(datum.toInt64(0), 6000);
    EXPECT_EQ(datum.typeId(), unsignedLong);
}

// Test with rational value
TEST_F(ExifdatumTest_2164, RationalValue_2164) {
    ExifKey key("Exif.Photo.ExposureTime");
    auto value = Value::create(unsignedRational);
    value->read("1/125");
    Exifdatum datum(key, value.get());
    
    Rational r = datum.toRational(0);
    EXPECT_EQ(r.first, 1u);
    EXPECT_EQ(r.second, 125u);
}

// Test construction with tag and group name
TEST_F(ExifdatumTest_2164, ConstructWithTagAndGroupName_2164) {
    ExifKey key(0x010f, "Image");
    Exifdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.tag(), 0x010f);
    EXPECT_EQ(datum.groupName(), "Image");
    EXPECT_EQ(datum.tagName(), "Make");
}

// Test setting value to nullptr (clearing value)
TEST_F(ExifdatumTest_2164, SetValueNullptr_2164) {
    ExifKey key("Exif.Image.Make");
    auto value = Value::create(asciiString);
    value->read("SomeValue");
    Exifdatum datum(key, value.get());
    
    datum.setValue(static_cast<const Value*>(nullptr));
    // After setting nullptr, count should be 0
    EXPECT_EQ(datum.count(), 0u);
}

// Test print method
TEST_F(ExifdatumTest_2164, PrintMethod_2164) {
    ExifKey key("Exif.Image.Make");
    auto value = Value::create(asciiString);
    value->read("PrintTest");
    Exifdatum datum(key, value.get());
    
    std::string printed = datum.print(nullptr);
    EXPECT_FALSE(printed.empty());
}

// Test toUint32
TEST_F(ExifdatumTest_2164, ToUint32_2164) {
    ExifKey key("Exif.Image.ImageWidth");
    auto value = Value::create(unsignedLong);
    value->read("12345");
    Exifdatum datum(key, value.get());
    
    EXPECT_EQ(datum.toUint32(0), 12345u);
}

// Test multiple setValue calls
TEST_F(ExifdatumTest_2164, MultipleSetValue_2164) {
    ExifKey key("Exif.Image.Make");
    auto value = Value::create(asciiString);
    value->read("First");
    Exifdatum datum(key, value.get());
    
    EXPECT_EQ(datum.toString(), "First");
    
    datum.setValue("Second");
    EXPECT_EQ(datum.toString(), "Second");
    
    datum.setValue("Third");
    EXPECT_EQ(datum.toString(), "Third");
}

// Test Exif.Photo group
TEST_F(ExifdatumTest_2164, PhotoGroupKey_2164) {
    ExifKey key("Exif.Photo.DateTimeOriginal");
    auto value = Value::create(asciiString);
    value->read("2023:01:15 10:30:00");
    Exifdatum datum(key, value.get());
    
    EXPECT_EQ(datum.groupName(), "Photo");
    EXPECT_EQ(datum.familyName(), std::string("Exif"));
    EXPECT_EQ(datum.toString(), "2023:01:15 10:30:00");
}

// Test copy constructor preserves type
TEST_F(ExifdatumTest_2164, CopyConstructorPreservesType_2164) {
    ExifKey key("Exif.Image.Orientation");
    auto value = Value::create(unsignedShort);
    value->read("3");
    Exifdatum original(key, value.get());
    
    Exifdatum copy(original);
    EXPECT_EQ(copy.typeId(), unsignedShort);
    EXPECT_EQ(copy.toInt64(0), 3);
}

// Test assignment operator preserves type from source
TEST_F(ExifdatumTest_2164, AssignmentPreservesSourceType_2164) {
    ExifKey key1("Exif.Image.Orientation");
    auto value1 = Value::create(unsignedShort);
    value1->read("5");
    Exifdatum datum1(key1, value1.get());
    
    ExifKey key2("Exif.Image.Make");
    auto value2 = Value::create(asciiString);
    value2->read("Test");
    Exifdatum datum2(key2, value2.get());
    
    datum2 = datum1;
    EXPECT_EQ(datum2.typeId(), unsignedShort);
    EXPECT_EQ(datum2.toInt64(0), 5);
    EXPECT_EQ(datum2.key(), "Exif.Image.Orientation");
}
