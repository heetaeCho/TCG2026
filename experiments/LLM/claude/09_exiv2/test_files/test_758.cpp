#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>
#include <string>
#include <memory>

using namespace Exiv2;

class ExifdatumTest_758 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test: Default constructed Exifdatum via ExifKey with no value set returns empty toString
TEST_F(ExifdatumTest_758, ToStringWithNoValueReturnsEmpty_758) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.toString(), "");
}

// Test: Exifdatum with a string value assigned returns correct toString
TEST_F(ExifdatumTest_758, ToStringWithStringValueAssigned_758) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("Canon");
    EXPECT_EQ(datum.toString(), "Canon");
}

// Test: Key returns correct key string
TEST_F(ExifdatumTest_758, KeyReturnsCorrectString_758) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
}

// Test: familyName returns "Exif"
TEST_F(ExifdatumTest_758, FamilyNameReturnsExif_758) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    std::string family = datum.familyName();
    EXPECT_EQ(family, "Exif");
}

// Test: groupName returns correct group
TEST_F(ExifdatumTest_758, GroupNameReturnsCorrectGroup_758) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "Image");
}

// Test: tagName returns correct tag name
TEST_F(ExifdatumTest_758, TagNameReturnsCorrectName_758) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.tagName(), "Make");
}

// Test: tag returns correct tag number
TEST_F(ExifdatumTest_758, TagReturnsCorrectNumber_758) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    // Make tag is 0x010f
    EXPECT_EQ(datum.tag(), 0x010f);
}

// Test: Assigning uint16_t value
TEST_F(ExifdatumTest_758, AssignUint16Value_758) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    datum = static_cast<uint16_t>(1);
    EXPECT_EQ(datum.toString(), "1");
    EXPECT_EQ(datum.toInt64(0), 1);
}

// Test: Assigning uint32_t value
TEST_F(ExifdatumTest_758, AssignUint32Value_758) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    datum = static_cast<uint32_t>(1920);
    EXPECT_EQ(datum.toString(), "1920");
    EXPECT_EQ(datum.toInt64(0), 1920);
}

// Test: Assigning int16_t value
TEST_F(ExifdatumTest_758, AssignInt16Value_758) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    datum = static_cast<int16_t>(-5);
    EXPECT_EQ(datum.toInt64(0), -5);
}

// Test: Assigning int32_t value
TEST_F(ExifdatumTest_758, AssignInt32Value_758) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    datum = static_cast<int32_t>(-100);
    EXPECT_EQ(datum.toInt64(0), -100);
}

// Test: Assigning URational value
TEST_F(ExifdatumTest_758, AssignURationalValue_758) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    URational ur(72, 1);
    datum = ur;
    EXPECT_EQ(datum.toInt64(0), 72);
    EXPECT_FLOAT_EQ(datum.toFloat(0), 72.0f);
}

// Test: Assigning Rational value
TEST_F(ExifdatumTest_758, AssignRationalValue_758) {
    ExifKey key("Exif.Photo.ExposureBiasValue");
    Exifdatum datum(key, nullptr);
    Rational r(-1, 3);
    datum = r;
    Rational result = datum.toRational(0);
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, 3);
}

// Test: Copy constructor
TEST_F(ExifdatumTest_758, CopyConstructor_758) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("Nikon");

    Exifdatum copy(datum);
    EXPECT_EQ(copy.toString(), "Nikon");
    EXPECT_EQ(copy.key(), "Exif.Image.Make");
}

// Test: Copy assignment operator
TEST_F(ExifdatumTest_758, CopyAssignmentOperator_758) {
    ExifKey key1("Exif.Image.Make");
    Exifdatum datum1(key1, nullptr);
    datum1 = std::string("Canon");

    ExifKey key2("Exif.Image.Model");
    Exifdatum datum2(key2, nullptr);
    datum2 = datum1;
    EXPECT_EQ(datum2.toString(), "Canon");
    EXPECT_EQ(datum2.key(), "Exif.Image.Make");
}

// Test: setValue with string
TEST_F(ExifdatumTest_758, SetValueWithString_758) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    int result = datum.setValue("Sony");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "Sony");
}

// Test: setValue with Value pointer
TEST_F(ExifdatumTest_758, SetValueWithValuePointer_758) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);

    auto value = Value::create(asciiString);
    value->read("Panasonic");
    datum.setValue(value.get());

    EXPECT_EQ(datum.toString(), "Panasonic");
}

// Test: setValue with nullptr clears the value
TEST_F(ExifdatumTest_758, SetValueWithNullptr_758) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("Canon");
    EXPECT_EQ(datum.toString(), "Canon");

    datum.setValue(nullptr);
    EXPECT_EQ(datum.toString(), "");
}

// Test: count returns 0 when no value is set
TEST_F(ExifdatumTest_758, CountReturnsZeroWithNoValue_758) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.count(), 0u);
}

// Test: count returns correct count after setting value
TEST_F(ExifdatumTest_758, CountReturnsCorrectAfterSetValue_758) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("Canon");
    EXPECT_GT(datum.count(), 0u);
}

// Test: size returns 0 when no value is set
TEST_F(ExifdatumTest_758, SizeReturnsZeroWithNoValue_758) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.size(), 0u);
}

// Test: size returns non-zero after setting value
TEST_F(ExifdatumTest_758, SizeReturnsNonZeroAfterSetValue_758) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("Canon");
    EXPECT_GT(datum.size(), 0u);
}

// Test: typeId with no value
TEST_F(ExifdatumTest_758, TypeIdWithNoValue_758) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    // When no value is set, typeId should return invalidTypeId or similar
    TypeId tid = datum.typeId();
    EXPECT_EQ(tid, invalidTypeId);
}

// Test: typeId after setting string value
TEST_F(ExifdatumTest_758, TypeIdAfterSettingStringValue_758) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Canon");
    TypeId tid = datum.typeId();
    EXPECT_EQ(tid, asciiString);
}

// Test: getValue returns nullptr when no value set
TEST_F(ExifdatumTest_758, GetValueReturnsNullptrWhenNoValue_758) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    auto val = datum.getValue();
    EXPECT_EQ(val, nullptr);
}

// Test: getValue returns non-null when value is set
TEST_F(ExifdatumTest_758, GetValueReturnsNonNullWhenValueSet_758) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("Canon");
    auto val = datum.getValue();
    EXPECT_NE(val, nullptr);
    EXPECT_EQ(val->toString(), "Canon");
}

// Test: sizeDataArea returns 0 when no data area
TEST_F(ExifdatumTest_758, SizeDataAreaReturnsZeroDefault_758) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.sizeDataArea(), 0u);
}

// Test: Assign Value object directly
TEST_F(ExifdatumTest_758, AssignValueObject_758) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);

    auto value = Value::create(asciiString);
    value->read("Olympus");
    datum = *value;

    EXPECT_EQ(datum.toString(), "Olympus");
}

// Test: toString(n) with valid index
TEST_F(ExifdatumTest_758, ToStringWithIndex_758) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("Canon");
    std::string s = datum.toString(0);
    EXPECT_EQ(s, "Canon");
}

// Test: toFloat returns correct value
TEST_F(ExifdatumTest_758, ToFloatReturnsCorrectValue_758) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    URational ur(72, 1);
    datum = ur;
    EXPECT_FLOAT_EQ(datum.toFloat(0), 72.0f);
}

// Test: toRational returns correct value
TEST_F(ExifdatumTest_758, ToRationalReturnsCorrectValue_758) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    URational ur(300, 1);
    datum = ur;
    Rational r = datum.toRational(0);
    EXPECT_EQ(r.first, 300);
    EXPECT_EQ(r.second, 1);
}

// Test: write to ostream
TEST_F(ExifdatumTest_758, WriteToOstream_758) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("Canon");

    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test: tagLabel returns non-empty for known tags
TEST_F(ExifdatumTest_758, TagLabelReturnsNonEmpty_758) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test: idx returns valid index
TEST_F(ExifdatumTest_758, IdxReturnsValue_758) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    int index = datum.idx();
    EXPECT_GE(index, 0);
}

// Test: Exifdatum constructed with a Value pointer
TEST_F(ExifdatumTest_758, ConstructWithValuePointer_758) {
    ExifKey key("Exif.Image.Make");
    auto value = Value::create(asciiString);
    value->read("Fujifilm");
    Exifdatum datum(key, value.get());
    EXPECT_EQ(datum.toString(), "Fujifilm");
}

// Test: copy method writes data to buffer
TEST_F(ExifdatumTest_758, CopyToBuffer_758) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    datum = static_cast<uint16_t>(1);

    byte buf[64] = {};
    size_t copied = datum.copy(buf, littleEndian);
    EXPECT_GT(copied, 0u);
}

// Test: Empty string assignment
TEST_F(ExifdatumTest_758, EmptyStringAssignment_758) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("");
    // Empty ASCII string still has a null terminator
    EXPECT_EQ(datum.toString(), "");
}

// Test: Multiple reassignments
TEST_F(ExifdatumTest_758, MultipleReassignments_758) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("Canon");
    EXPECT_EQ(datum.toString(), "Canon");

    datum = std::string("Nikon");
    EXPECT_EQ(datum.toString(), "Nikon");

    datum = std::string("Sony");
    EXPECT_EQ(datum.toString(), "Sony");
}

// Test: ExifData container operations
TEST_F(ExifdatumTest_758, ExifDataContainerBasicOperations_758) {
    ExifData exifData;
    EXPECT_TRUE(exifData.empty());
    EXPECT_EQ(exifData.count(), 0u);

    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("Canon");
    exifData.add(datum);

    EXPECT_FALSE(exifData.empty());
    EXPECT_EQ(exifData.count(), 1u);
}

// Test: ExifData find
TEST_F(ExifdatumTest_758, ExifDataFind_758) {
    ExifData exifData;
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("Canon");
    exifData.add(datum);

    auto pos = exifData.findKey(ExifKey("Exif.Image.Make"));
    ASSERT_NE(pos, exifData.end());
    EXPECT_EQ(pos->toString(), "Canon");
}

// Test: ExifData find non-existent key
TEST_F(ExifdatumTest_758, ExifDataFindNonExistent_758) {
    ExifData exifData;
    auto pos = exifData.findKey(ExifKey("Exif.Image.Make"));
    EXPECT_EQ(pos, exifData.end());
}

// Test: ExifData erase
TEST_F(ExifdatumTest_758, ExifDataErase_758) {
    ExifData exifData;
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("Canon");
    exifData.add(datum);

    auto pos = exifData.findKey(ExifKey("Exif.Image.Make"));
    ASSERT_NE(pos, exifData.end());
    exifData.erase(pos);
    EXPECT_TRUE(exifData.empty());
}

// Test: ExifData clear
TEST_F(ExifdatumTest_758, ExifDataClear_758) {
    ExifData exifData;
    ExifKey key1("Exif.Image.Make");
    Exifdatum datum1(key1, nullptr);
    datum1 = std::string("Canon");
    exifData.add(datum1);

    ExifKey key2("Exif.Image.Model");
    Exifdatum datum2(key2, nullptr);
    datum2 = std::string("EOS R5");
    exifData.add(datum2);

    EXPECT_EQ(exifData.count(), 2u);
    exifData.clear();
    EXPECT_TRUE(exifData.empty());
    EXPECT_EQ(exifData.count(), 0u);
}
