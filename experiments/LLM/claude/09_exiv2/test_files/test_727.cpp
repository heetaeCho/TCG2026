#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <cstdint>
#include <string>
#include <memory>

class ExifdatumTest_727 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test: Construct Exifdatum with a known ExifKey and verify key properties
TEST_F(ExifdatumTest_727, ConstructWithExifKey_727) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);

    EXPECT_EQ("Exif.Image.Make", datum.key());
    EXPECT_STREQ("Exif", datum.familyName());
    EXPECT_EQ("Image", datum.groupName());
    EXPECT_EQ("Make", datum.tagName());
}

// Test: tag() returns the correct tag number
TEST_F(ExifdatumTest_727, TagReturnsCorrectValue_727) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);

    // Make tag is 0x010f
    EXPECT_EQ(0x010f, datum.tag());
}

// Test: Copy constructor creates an independent copy
TEST_F(ExifdatumTest_727, CopyConstructor_727) {
    Exiv2::ExifKey key("Exif.Image.Model");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("TestCamera");

    Exiv2::Exifdatum copy(datum);
    EXPECT_EQ(copy.key(), datum.key());
    EXPECT_EQ(copy.toString(), "TestCamera");
}

// Test: Assignment operator from another Exifdatum
TEST_F(ExifdatumTest_727, AssignmentOperatorExifdatum_727) {
    Exiv2::ExifKey key1("Exif.Image.Make");
    Exiv2::Exifdatum datum1(key1, nullptr);
    datum1 = std::string("Canon");

    Exiv2::ExifKey key2("Exif.Image.Model");
    Exiv2::Exifdatum datum2(key2, nullptr);
    datum2 = datum1;

    EXPECT_EQ("Canon", datum2.toString());
}

// Test: Assign string value using operator=
TEST_F(ExifdatumTest_727, AssignStringValue_727) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("Nikon");

    EXPECT_EQ("Nikon", datum.toString());
    EXPECT_EQ(1u, datum.count());
}

// Test: Assign uint16_t value using operator=
TEST_F(ExifdatumTest_727, AssignUint16Value_727) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);

    uint16_t val = 6;
    datum = val;

    EXPECT_EQ(6, datum.toInt64(0));
    EXPECT_EQ(1u, datum.count());
}

// Test: Assign uint32_t value using operator=
TEST_F(ExifdatumTest_727, AssignUint32Value_727) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    Exiv2::Exifdatum datum(key, nullptr);

    uint32_t val = 4000;
    datum = val;

    EXPECT_EQ(4000, datum.toInt64(0));
}

// Test: Assign int16_t value using operator=
TEST_F(ExifdatumTest_727, AssignInt16Value_727) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);

    int16_t val = -5;
    datum = val;

    EXPECT_EQ(-5, datum.toInt64(0));
}

// Test: Assign int32_t value using operator=
TEST_F(ExifdatumTest_727, AssignInt32Value_727) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    Exiv2::Exifdatum datum(key, nullptr);

    int32_t val = -12345;
    datum = val;

    EXPECT_EQ(-12345, datum.toInt64(0));
}

// Test: Assign URational value using operator=
TEST_F(ExifdatumTest_727, AssignURationalValue_727) {
    Exiv2::ExifKey key("Exif.Image.XResolution");
    Exiv2::Exifdatum datum(key, nullptr);

    Exiv2::URational val(72, 1);
    datum = val;

    EXPECT_EQ(1u, datum.count());
    Exiv2::Rational r = datum.toRational(0);
    EXPECT_EQ(72, r.first);
    EXPECT_EQ(1, r.second);
}

// Test: Assign Rational value using operator=
TEST_F(ExifdatumTest_727, AssignRationalValue_727) {
    Exiv2::ExifKey key("Exif.Photo.ExposureBiasValue");
    Exiv2::Exifdatum datum(key, nullptr);

    Exiv2::Rational val(-1, 3);
    datum = val;

    EXPECT_EQ(1u, datum.count());
    Exiv2::Rational r = datum.toRational(0);
    EXPECT_EQ(-1, r.first);
    EXPECT_EQ(3, r.second);
}

// Test: setValue with string
TEST_F(ExifdatumTest_727, SetValueString_727) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);

    // First set a type via operator= so the value object exists
    datum = std::string("Initial");
    int result = datum.setValue("Updated");
    EXPECT_EQ(0, result);
    EXPECT_EQ("Updated", datum.toString());
}

// Test: setValue with Value pointer (nullptr)
TEST_F(ExifdatumTest_727, SetValueWithNullptr_727) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);

    datum = std::string("SomeValue");
    datum.setValue(nullptr);

    // After setting nullptr, value should throw or count should be 0
    EXPECT_EQ(0u, datum.count());
}

// Test: setValue with a concrete Value object
TEST_F(ExifdatumTest_727, SetValueWithValueObject_727) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);

    Exiv2::AsciiValue val("TestValue");
    datum = val;

    EXPECT_EQ("TestValue", datum.toString());
}

// Test: Template setValue function with uint16_t
TEST_F(ExifdatumTest_727, TemplateSetValueUint16_727) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);

    uint16_t val = 42;
    Exiv2::setValue(datum, val);

    EXPECT_EQ(42, datum.toInt64(0));
    EXPECT_EQ(1u, datum.count());
}

// Test: Template setValue function with int32_t
TEST_F(ExifdatumTest_727, TemplateSetValueInt32_727) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    Exiv2::Exifdatum datum(key, nullptr);

    int32_t val = 99999;
    Exiv2::setValue(datum, val);

    EXPECT_EQ(99999, datum.toInt64(0));
}

// Test: Template setValue function with URational
TEST_F(ExifdatumTest_727, TemplateSetValueURational_727) {
    Exiv2::ExifKey key("Exif.Image.XResolution");
    Exiv2::Exifdatum datum(key, nullptr);

    Exiv2::URational val(300, 1);
    Exiv2::setValue(datum, val);

    Exiv2::Rational r = datum.toRational(0);
    EXPECT_EQ(300, r.first);
    EXPECT_EQ(1, r.second);
}

// Test: Template setValue function with Rational
TEST_F(ExifdatumTest_727, TemplateSetValueRational_727) {
    Exiv2::ExifKey key("Exif.Photo.ExposureBiasValue");
    Exiv2::Exifdatum datum(key, nullptr);

    Exiv2::Rational val(-2, 3);
    Exiv2::setValue(datum, val);

    Exiv2::Rational r = datum.toRational(0);
    EXPECT_EQ(-2, r.first);
    EXPECT_EQ(3, r.second);
}

// Test: Template setValue returns reference to the same datum
TEST_F(ExifdatumTest_727, TemplateSetValueReturnsSameDatum_727) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);

    uint16_t val = 1;
    Exiv2::Exifdatum& ref = Exiv2::setValue(datum, val);

    EXPECT_EQ(&datum, &ref);
}

// Test: typeId after assigning uint16_t
TEST_F(ExifdatumTest_727, TypeIdAfterUint16Assignment_727) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);

    uint16_t val = 1;
    datum = val;

    EXPECT_EQ(Exiv2::unsignedShort, datum.typeId());
}

// Test: typeId after assigning int32_t
TEST_F(ExifdatumTest_727, TypeIdAfterInt32Assignment_727) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    Exiv2::Exifdatum datum(key, nullptr);

    int32_t val = 100;
    datum = val;

    EXPECT_EQ(Exiv2::signedLong, datum.typeId());
}

// Test: typeId after assigning URational
TEST_F(ExifdatumTest_727, TypeIdAfterURationalAssignment_727) {
    Exiv2::ExifKey key("Exif.Image.XResolution");
    Exiv2::Exifdatum datum(key, nullptr);

    Exiv2::URational val(72, 1);
    datum = val;

    EXPECT_EQ(Exiv2::unsignedRational, datum.typeId());
}

// Test: typeId after assigning Rational
TEST_F(ExifdatumTest_727, TypeIdAfterRationalAssignment_727) {
    Exiv2::ExifKey key("Exif.Photo.ExposureBiasValue");
    Exiv2::Exifdatum datum(key, nullptr);

    Exiv2::Rational val(1, 3);
    datum = val;

    EXPECT_EQ(Exiv2::signedRational, datum.typeId());
}

// Test: size() after assignment
TEST_F(ExifdatumTest_727, SizeAfterAssignment_727) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);

    uint16_t val = 1;
    datum = val;

    EXPECT_GT(datum.size(), 0u);
}

// Test: toFloat after assignment
TEST_F(ExifdatumTest_727, ToFloatAfterAssignment_727) {
    Exiv2::ExifKey key("Exif.Image.XResolution");
    Exiv2::Exifdatum datum(key, nullptr);

    Exiv2::URational val(72, 1);
    datum = val;

    EXPECT_FLOAT_EQ(72.0f, datum.toFloat(0));
}

// Test: getValue returns a non-null unique_ptr after assignment
TEST_F(ExifdatumTest_727, GetValueReturnsNonNull_727) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("TestCamera");

    auto val = datum.getValue();
    ASSERT_NE(nullptr, val.get());
    EXPECT_EQ("TestCamera", val->toString());
}

// Test: value() reference after assignment
TEST_F(ExifdatumTest_727, ValueReferenceAfterAssignment_727) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("Sony");

    const Exiv2::Value& val = datum.value();
    EXPECT_EQ("Sony", val.toString());
}

// Test: Construct with Value pointer (non-null)
TEST_F(ExifdatumTest_727, ConstructWithValuePointer_727) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::AsciiValue val("InitialMake");
    Exiv2::Exifdatum datum(key, &val);

    EXPECT_EQ("InitialMake", datum.toString());
    EXPECT_EQ("Exif.Image.Make", datum.key());
}

// Test: tagLabel and tagDesc return non-empty strings for known tags
TEST_F(ExifdatumTest_727, TagLabelAndDesc_727) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);

    std::string label = datum.tagLabel();
    // Make tag should have a non-empty label
    EXPECT_FALSE(label.empty());
}

// Test: count() returns 0 when no value is set
TEST_F(ExifdatumTest_727, CountZeroWhenNoValue_727) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);

    EXPECT_EQ(0u, datum.count());
}

// Test: Assigning uint32_t then checking typeId
TEST_F(ExifdatumTest_727, TypeIdAfterUint32Assignment_727) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    Exiv2::Exifdatum datum(key, nullptr);

    uint32_t val = 5000;
    datum = val;

    EXPECT_EQ(Exiv2::unsignedLong, datum.typeId());
}

// Test: Multiple assignments overwrite previous value
TEST_F(ExifdatumTest_727, MultipleAssignmentsOverwrite_727) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);

    datum = std::string("First");
    EXPECT_EQ("First", datum.toString());

    datum = std::string("Second");
    EXPECT_EQ("Second", datum.toString());
}

// Test: Template setValue with uint32_t
TEST_F(ExifdatumTest_727, TemplateSetValueUint32_727) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    Exiv2::Exifdatum datum(key, nullptr);

    uint32_t val = 8192;
    Exiv2::setValue(datum, val);

    EXPECT_EQ(8192, datum.toInt64(0));
    EXPECT_EQ(Exiv2::unsignedLong, datum.typeId());
}

// Test: idx() returns some value (basic sanity)
TEST_F(ExifdatumTest_727, IdxReturnsValue_727) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);

    // idx is typically 0 for a freshly created datum
    int idx = datum.idx();
    EXPECT_GE(idx, 0);
}

// Test: ifdId returns valid IFD ID
TEST_F(ExifdatumTest_727, IfdIdReturnsValid_727) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);

    Exiv2::IfdId id = datum.ifdId();
    EXPECT_NE(Exiv2::IfdId::ifdIdNotSet, id);
}

// Test: typeName returns non-null after value assignment
TEST_F(ExifdatumTest_727, TypeNameAfterAssignment_727) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);

    uint16_t val = 1;
    datum = val;

    const char* tn = datum.typeName();
    ASSERT_NE(nullptr, tn);
    EXPECT_STREQ("SHORT", tn);
}

// Test: typeSize returns correct size for uint16_t
TEST_F(ExifdatumTest_727, TypeSizeForUint16_727) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);

    uint16_t val = 1;
    datum = val;

    EXPECT_EQ(2u, datum.typeSize());
}

// Test: copy to buffer
TEST_F(ExifdatumTest_727, CopyToBuffer_727) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);

    uint16_t val = 1;
    datum = val;

    Exiv2::byte buf[16] = {};
    size_t copied = datum.copy(buf, Exiv2::littleEndian);
    EXPECT_GT(copied, 0u);
}
