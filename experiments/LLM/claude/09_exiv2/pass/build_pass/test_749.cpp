#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/tags.hpp>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

// Test fixture for Exifdatum tests
class ExifdatumTest_749 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Construction with ExifKey and ifdId retrieval
TEST_F(ExifdatumTest_749, ConstructWithExifKey_IfdIdIsCorrect_749) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.ifdId(), IfdId::ifd0Id);
}

// Test: Construction with GPS key returns gpsId
TEST_F(ExifdatumTest_749, ConstructWithGpsKey_IfdIdIsGps_749) {
    ExifKey key("Exif.GPSInfo.GPSLatitude");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.ifdId(), IfdId::gpsId);
}

// Test: Construction with Exif IFD key returns exifId
TEST_F(ExifdatumTest_749, ConstructWithExifIfdKey_IfdIdIsExif_749) {
    ExifKey key("Exif.Photo.ExposureTime");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.ifdId(), IfdId::exifId);
}

// Test: key() returns the correct key string
TEST_F(ExifdatumTest_749, KeyReturnsCorrectString_749) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
}

// Test: familyName() returns "Exif"
TEST_F(ExifdatumTest_749, FamilyNameReturnsExif_749) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_STREQ(datum.familyName(), "Exif");
}

// Test: groupName() returns correct group
TEST_F(ExifdatumTest_749, GroupNameReturnsCorrectGroup_749) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "Image");
}

// Test: tagName() returns correct tag name
TEST_F(ExifdatumTest_749, TagNameReturnsCorrectName_749) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.tagName(), "Make");
}

// Test: tag() returns correct tag number
TEST_F(ExifdatumTest_749, TagReturnsCorrectNumber_749) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.tag(), 0x010f);
}

// Test: Copy constructor produces equivalent datum
TEST_F(ExifdatumTest_749, CopyConstructorProducesEquivalent_749) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    Exifdatum copy(datum);
    EXPECT_EQ(copy.key(), datum.key());
    EXPECT_EQ(copy.ifdId(), datum.ifdId());
    EXPECT_EQ(copy.tag(), datum.tag());
}

// Test: Assignment operator produces equivalent datum
TEST_F(ExifdatumTest_749, AssignmentOperatorProducesEquivalent_749) {
    ExifKey key1("Exif.Image.Make");
    ExifKey key2("Exif.Photo.ExposureTime");
    Exifdatum datum1(key1, nullptr);
    Exifdatum datum2(key2, nullptr);
    datum2 = datum1;
    EXPECT_EQ(datum2.key(), datum1.key());
    EXPECT_EQ(datum2.ifdId(), datum1.ifdId());
}

// Test: setValue with string for a string-type tag
TEST_F(ExifdatumTest_749, SetValueWithString_749) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    int result = datum.setValue("Canon");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "Canon");
}

// Test: operator= with string value
TEST_F(ExifdatumTest_749, AssignStringValue_749) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("Nikon");
    EXPECT_EQ(datum.toString(), "Nikon");
}

// Test: operator= with uint16_t value
TEST_F(ExifdatumTest_749, AssignUint16Value_749) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    datum = static_cast<uint16_t>(1);
    EXPECT_EQ(datum.toInt64(0), 1);
}

// Test: operator= with uint32_t value
TEST_F(ExifdatumTest_749, AssignUint32Value_749) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    datum = static_cast<uint32_t>(1920);
    EXPECT_EQ(datum.toInt64(0), 1920);
}

// Test: operator= with int16_t value
TEST_F(ExifdatumTest_749, AssignInt16Value_749) {
    ExifKey key("Exif.Photo.ExposureCompensation");
    Exifdatum datum(key, nullptr);
    datum = static_cast<int16_t>(-5);
    EXPECT_EQ(datum.toInt64(0), -5);
}

// Test: operator= with Rational value
TEST_F(ExifdatumTest_749, AssignRationalValue_749) {
    ExifKey key("Exif.Photo.ExposureTime");
    Exifdatum datum(key, nullptr);
    Rational r(1, 100);
    datum = r;
    Rational result = datum.toRational(0);
    EXPECT_EQ(result.first, 1);
    EXPECT_EQ(result.second, 100);
}

// Test: operator= with URational value
TEST_F(ExifdatumTest_749, AssignURationalValue_749) {
    ExifKey key("Exif.Photo.FNumber");
    Exifdatum datum(key, nullptr);
    URational ur(28, 10);
    datum = ur;
    Rational result = datum.toRational(0);
    EXPECT_EQ(result.first, 28);
    EXPECT_EQ(result.second, 10);
}

// Test: count() returns 0 when no value is set
TEST_F(ExifdatumTest_749, CountReturnsZeroWhenNoValue_749) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.count(), 0u);
}

// Test: size() returns 0 when no value is set
TEST_F(ExifdatumTest_749, SizeReturnsZeroWhenNoValue_749) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.size(), 0u);
}

// Test: count() after setting a value
TEST_F(ExifdatumTest_749, CountAfterSetValue_749) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Test");
    EXPECT_GT(datum.count(), 0u);
}

// Test: size() after setting a value
TEST_F(ExifdatumTest_749, SizeAfterSetValue_749) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Test");
    EXPECT_GT(datum.size(), 0u);
}

// Test: getValue() returns non-null after setting value
TEST_F(ExifdatumTest_749, GetValueReturnsNonNullAfterSet_749) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("TestValue");
    auto val = datum.getValue();
    ASSERT_NE(val, nullptr);
}

// Test: typeId() for string tag
TEST_F(ExifdatumTest_749, TypeIdForStringTag_749) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Canon");
    EXPECT_EQ(datum.typeId(), asciiString);
}

// Test: typeId() for short tag (Orientation)
TEST_F(ExifdatumTest_749, TypeIdForShortTag_749) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    datum = static_cast<uint16_t>(1);
    EXPECT_EQ(datum.typeId(), unsignedShort);
}

// Test: ifdName() returns non-null
TEST_F(ExifdatumTest_749, IfdNameReturnsNonNull_749) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    const char* name = datum.ifdName();
    EXPECT_NE(name, nullptr);
}

// Test: tagLabel() returns non-empty for known tags
TEST_F(ExifdatumTest_749, TagLabelReturnsNonEmpty_749) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test: write() to ostream
TEST_F(ExifdatumTest_749, WriteToOstream_749) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Canon");
    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test: setValue with Value pointer
TEST_F(ExifdatumTest_749, SetValueWithValuePointer_749) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    AsciiValue val;
    val.read("TestMake");
    datum.setValue(&val);
    EXPECT_EQ(datum.toString(), "TestMake");
}

// Test: operator= with Value reference
TEST_F(ExifdatumTest_749, AssignValueReference_749) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    AsciiValue val;
    val.read("SomeValue");
    datum = static_cast<const Value&>(val);
    EXPECT_EQ(datum.toString(), "SomeValue");
}

// Test: toFloat returns correct value
TEST_F(ExifdatumTest_749, ToFloatReturnsCorrectValue_749) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    datum = static_cast<uint16_t>(3);
    EXPECT_FLOAT_EQ(datum.toFloat(0), 3.0f);
}

// Test: toInt64 returns correct value
TEST_F(ExifdatumTest_749, ToInt64ReturnsCorrectValue_749) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    datum = static_cast<uint16_t>(6);
    EXPECT_EQ(datum.toInt64(0), 6);
}

// Test: idx() default value
TEST_F(ExifdatumTest_749, IdxDefaultValue_749) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    // idx() should return some integer; by default typically 0
    int idx = datum.idx();
    EXPECT_GE(idx, 0);
}

// Test: Construction using tag number and group name
TEST_F(ExifdatumTest_749, ConstructWithTagNumberAndGroup_749) {
    ExifKey key(0x010f, "Image");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.tag(), 0x010f);
    EXPECT_EQ(datum.groupName(), "Image");
    EXPECT_EQ(datum.ifdId(), IfdId::ifd0Id);
}

// Test: copy() with a buffer
TEST_F(ExifdatumTest_749, CopyToBuffer_749) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    datum = static_cast<uint16_t>(1);
    byte buf[16] = {0};
    size_t copied = datum.copy(buf, littleEndian);
    EXPECT_GT(copied, 0u);
}

// Test: sizeDataArea() when no data area
TEST_F(ExifdatumTest_749, SizeDataAreaWhenNoDataArea_749) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Test");
    EXPECT_EQ(datum.sizeDataArea(), 0u);
}

// Test: Multiple assignment operators preserve last value
TEST_F(ExifdatumTest_749, MultipleAssignmentsPreserveLastValue_749) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    datum = static_cast<uint16_t>(1);
    EXPECT_EQ(datum.toInt64(0), 1);
    datum = static_cast<uint16_t>(8);
    EXPECT_EQ(datum.toInt64(0), 8);
}

// Test: Construct from IOP IFD
TEST_F(ExifdatumTest_749, ConstructWithIopKey_749) {
    ExifKey key("Exif.Iop.InteroperabilityIndex");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.ifdId(), IfdId::iopId);
}

// Test: toString with index n
TEST_F(ExifdatumTest_749, ToStringWithIndex_749) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Hello");
    std::string s = datum.toString(0);
    EXPECT_FALSE(s.empty());
}

// Test: operator= with int32_t
TEST_F(ExifdatumTest_749, AssignInt32Value_749) {
    ExifKey key("Exif.Photo.ExposureBiasValue");
    Exifdatum datum(key, nullptr);
    datum = static_cast<int32_t>(-100);
    EXPECT_EQ(datum.toInt64(0), -100);
}

// Test: Self-assignment
TEST_F(ExifdatumTest_749, SelfAssignment_749) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("SelfTest");
    datum = datum;
    EXPECT_EQ(datum.toString(), "SelfTest");
}

// Test: typeName for string datum
TEST_F(ExifdatumTest_749, TypeNameForAscii_749) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Test");
    const char* tn = datum.typeName();
    EXPECT_NE(tn, nullptr);
    EXPECT_STREQ(tn, "Ascii");
}

// Test: typeSize for short datum
TEST_F(ExifdatumTest_749, TypeSizeForShort_749) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    datum = static_cast<uint16_t>(1);
    EXPECT_EQ(datum.typeSize(), 2u);
}
