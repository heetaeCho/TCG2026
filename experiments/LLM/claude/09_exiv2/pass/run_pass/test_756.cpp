#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/exiv2.hpp>
#include <string>
#include <cstdint>

using namespace Exiv2;

class ExifdatumTest_756 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that a default-constructed Exifdatum (with no value set) has count() == 0
TEST_F(ExifdatumTest_756, CountReturnsZeroWhenNoValue_756) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.count(), 0u);
}

// Test that after setting a value, count() returns the expected count
TEST_F(ExifdatumTest_756, CountReturnsCorrectValueAfterSetValue_756) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Canon");
    EXPECT_GT(datum.count(), 0u);
}

// Test key() returns the correct key string
TEST_F(ExifdatumTest_756, KeyReturnsCorrectString_756) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
}

// Test familyName() returns "Exif"
TEST_F(ExifdatumTest_756, FamilyNameReturnsExif_756) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_STREQ(datum.familyName(), "Exif");
}

// Test groupName() returns the expected group
TEST_F(ExifdatumTest_756, GroupNameReturnsCorrectGroup_756) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "Image");
}

// Test tagName() returns the expected tag name
TEST_F(ExifdatumTest_756, TagNameReturnsCorrectTagName_756) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.tagName(), "Make");
}

// Test tag() returns the correct tag number
TEST_F(ExifdatumTest_756, TagReturnsCorrectTagNumber_756) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    // Make tag is 0x010f
    EXPECT_EQ(datum.tag(), 0x010f);
}

// Test copy constructor
TEST_F(ExifdatumTest_756, CopyConstructorCopiesCorrectly_756) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Nikon");

    Exifdatum copy(datum);
    EXPECT_EQ(copy.key(), "Exif.Image.Make");
    EXPECT_EQ(copy.toString(), datum.toString());
    EXPECT_EQ(copy.count(), datum.count());
}

// Test copy assignment operator
TEST_F(ExifdatumTest_756, CopyAssignmentOperatorWorks_756) {
    ExifKey key1("Exif.Image.Make");
    Exifdatum datum1(key1, nullptr);
    datum1.setValue("Canon");

    ExifKey key2("Exif.Image.Model");
    Exifdatum datum2(key2, nullptr);
    datum2.setValue("EOS 5D");

    datum2 = datum1;
    EXPECT_EQ(datum2.key(), "Exif.Image.Make");
    EXPECT_EQ(datum2.toString(), "Canon");
}

// Test operator=(const std::string&)
TEST_F(ExifdatumTest_756, AssignStringValue_756) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    // Need to set an initial value to establish the type
    AsciiValue av;
    datum.setValue(&av);
    datum = std::string("Sony");
    EXPECT_EQ(datum.toString(), "Sony");
}

// Test operator=(const uint16_t&)
TEST_F(ExifdatumTest_756, AssignUint16Value_756) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    UShortValue usv;
    datum.setValue(&usv);
    uint16_t val = 1;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 1);
}

// Test operator=(const uint32_t&)
TEST_F(ExifdatumTest_756, AssignUint32Value_756) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    ULongValue ulv;
    datum.setValue(&ulv);
    uint32_t val = 4000;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 4000);
}

// Test operator=(const int16_t&)
TEST_F(ExifdatumTest_756, AssignInt16Value_756) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    ShortValue sv;
    datum.setValue(&sv);
    int16_t val = -5;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), -5);
}

// Test operator=(const int32_t&)
TEST_F(ExifdatumTest_756, AssignInt32Value_756) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    LongValue lv;
    datum.setValue(&lv);
    int32_t val = -100;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), -100);
}

// Test operator=(const URational&)
TEST_F(ExifdatumTest_756, AssignURationalValue_756) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    URationalValue urv;
    datum.setValue(&urv);
    URational val(72, 1);
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 72);
}

// Test operator=(const Rational&)
TEST_F(ExifdatumTest_756, AssignRationalValue_756) {
    ExifKey key("Exif.Photo.ExposureBiasValue");
    Exifdatum datum(key, nullptr);
    RationalValue rv;
    datum.setValue(&rv);
    Rational val(-1, 3);
    datum = val;
    Rational result = datum.toRational(0);
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, 3);
}

// Test size() with no value returns 0
TEST_F(ExifdatumTest_756, SizeReturnsZeroWhenNoValue_756) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.size(), 0u);
}

// Test size() with a value set
TEST_F(ExifdatumTest_756, SizeReturnsCorrectValueAfterSetValue_756) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Canon");
    EXPECT_GT(datum.size(), 0u);
}

// Test typeId() when no value is set
TEST_F(ExifdatumTest_756, TypeIdWhenNoValue_756) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    // When no value is set, typeId should return some default
    TypeId tid = datum.typeId();
    // Just check it doesn't crash; the value is implementation-defined
    (void)tid;
}

// Test typeId() returns correct type after setting a value
TEST_F(ExifdatumTest_756, TypeIdAfterSetStringValue_756) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    AsciiValue av;
    datum.setValue(&av);
    datum = std::string("Canon");
    EXPECT_EQ(datum.typeId(), asciiString);
}

// Test toString() with no value set
TEST_F(ExifdatumTest_756, ToStringWhenNoValue_756) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    std::string s = datum.toString();
    EXPECT_TRUE(s.empty());
}

// Test toString() with value set
TEST_F(ExifdatumTest_756, ToStringWithValue_756) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Canon");
    EXPECT_FALSE(datum.toString().empty());
}

// Test getValue() returns nullptr-like when no value is set
TEST_F(ExifdatumTest_756, GetValueReturnsNullWhenNoValue_756) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    auto val = datum.getValue();
    EXPECT_EQ(val.get(), nullptr);
}

// Test getValue() returns valid pointer when value is set
TEST_F(ExifdatumTest_756, GetValueReturnsNonNullWhenValueSet_756) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Canon");
    auto val = datum.getValue();
    EXPECT_NE(val.get(), nullptr);
}

// Test toFloat()
TEST_F(ExifdatumTest_756, ToFloatAfterSetValue_756) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    URationalValue urv;
    datum.setValue(&urv);
    URational val(72, 1);
    datum = val;
    float f = datum.toFloat(0);
    EXPECT_FLOAT_EQ(f, 72.0f);
}

// Test toInt64()
TEST_F(ExifdatumTest_756, ToInt64AfterSetValue_756) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    UShortValue usv;
    datum.setValue(&usv);
    uint16_t val = 6;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 6);
}

// Test setValue with Value pointer
TEST_F(ExifdatumTest_756, SetValueWithValuePointer_756) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    AsciiValue av;
    av.read("TestValue");
    datum.setValue(&av);
    EXPECT_EQ(datum.toString(), "TestValue");
}

// Test setValue with nullptr resets value
TEST_F(ExifdatumTest_756, SetValueWithNullptrResetsValue_756) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Canon");
    EXPECT_GT(datum.count(), 0u);
    datum.setValue(static_cast<const Value*>(nullptr));
    EXPECT_EQ(datum.count(), 0u);
}

// Test tagLabel() returns non-empty string for known tags
TEST_F(ExifdatumTest_756, TagLabelReturnsNonEmptyForKnownTag_756) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test sizeDataArea() with no data area
TEST_F(ExifdatumTest_756, SizeDataAreaReturnsZeroByDefault_756) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Canon");
    EXPECT_EQ(datum.sizeDataArea(), 0u);
}

// Test idx() returns default value
TEST_F(ExifdatumTest_756, IdxReturnsDefaultValue_756) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    int idx = datum.idx();
    EXPECT_EQ(idx, 0);
}

// Test multiple assignments maintain correct state
TEST_F(ExifdatumTest_756, MultipleAssignmentsMaintainState_756) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    AsciiValue av;
    datum.setValue(&av);
    datum = std::string("First");
    EXPECT_EQ(datum.toString(), "First");
    datum = std::string("Second");
    EXPECT_EQ(datum.toString(), "Second");
}

// Test operator=(const Value&)
TEST_F(ExifdatumTest_756, AssignValueRefSetsCorrectly_756) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    AsciiValue av;
    av.read("TestBrand");
    datum = static_cast<const Value&>(av);
    EXPECT_EQ(datum.toString(), "TestBrand");
    EXPECT_EQ(datum.typeId(), asciiString);
}

// Test creating Exifdatum with initial Value pointer
TEST_F(ExifdatumTest_756, ConstructWithInitialValue_756) {
    ExifKey key("Exif.Image.Make");
    AsciiValue av;
    av.read("InitialValue");
    Exifdatum datum(key, &av);
    EXPECT_EQ(datum.toString(), "InitialValue");
    EXPECT_GT(datum.count(), 0u);
}

// Test copy and write operations
TEST_F(ExifdatumTest_756, CopyToBufferDoesNotCrash_756) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    UShortValue usv;
    datum.setValue(&usv);
    uint16_t val = 1;
    datum = val;

    byte buf[16] = {};
    size_t copied = datum.copy(buf, littleEndian);
    EXPECT_GT(copied, 0u);
}

// Test write to ostream
TEST_F(ExifdatumTest_756, WriteToOstream_756) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Canon");

    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test typeName()
TEST_F(ExifdatumTest_756, TypeNameReturnsCorrectName_756) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    UShortValue usv;
    datum.setValue(&usv);
    uint16_t val = 1;
    datum = val;
    const char* tn = datum.typeName();
    EXPECT_NE(tn, nullptr);
    EXPECT_STREQ(tn, "Short");
}

// Test typeSize()
TEST_F(ExifdatumTest_756, TypeSizeReturnsCorrectSize_756) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    UShortValue usv;
    datum.setValue(&usv);
    uint16_t val = 1;
    datum = val;
    EXPECT_EQ(datum.typeSize(), 2u);
}
