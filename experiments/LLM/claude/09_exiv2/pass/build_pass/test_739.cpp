#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>
#include <exiv2/tags.hpp>
#include <memory>
#include <string>

using namespace Exiv2;

class ExifdatumTest_739 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    
    void TearDown() override {
    }
};

// Test construction with ExifKey and null Value pointer
TEST_F(ExifdatumTest_739, ConstructWithKeyAndNullValue_739) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
    EXPECT_EQ(datum.familyName(), std::string("Exif"));
    EXPECT_EQ(datum.groupName(), "Image");
    EXPECT_EQ(datum.tagName(), "Make");
    EXPECT_EQ(datum.count(), 0u);
    EXPECT_EQ(datum.size(), 0u);
}

// Test construction with ExifKey and a Value
TEST_F(ExifdatumTest_739, ConstructWithKeyAndValue_739) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    Exifdatum datum(key, &val);
    
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
    EXPECT_EQ(datum.toString(), "Canon");
    EXPECT_GT(datum.count(), 0u);
}

// Test copy constructor
TEST_F(ExifdatumTest_739, CopyConstructor_739) {
    ExifKey key("Exif.Image.Model");
    AsciiValue val;
    val.read("EOS 5D");
    Exifdatum original(key, &val);
    Exifdatum copy(original);
    
    EXPECT_EQ(copy.key(), original.key());
    EXPECT_EQ(copy.toString(), original.toString());
    EXPECT_EQ(copy.tag(), original.tag());
}

// Test copy assignment operator
TEST_F(ExifdatumTest_739, CopyAssignment_739) {
    ExifKey key1("Exif.Image.Make");
    AsciiValue val1;
    val1.read("Canon");
    Exifdatum datum1(key1, &val1);
    
    ExifKey key2("Exif.Image.Model");
    AsciiValue val2;
    val2.read("Nikon");
    Exifdatum datum2(key2, &val2);
    
    datum2 = datum1;
    EXPECT_EQ(datum2.key(), "Exif.Image.Make");
    EXPECT_EQ(datum2.toString(), "Canon");
}

// Test setValue with nullptr
TEST_F(ExifdatumTest_739, SetValueNullptr_739) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    Exifdatum datum(key, &val);
    
    EXPECT_EQ(datum.toString(), "Canon");
    
    // Set value to null
    datum.setValue(static_cast<const Value*>(nullptr));
    EXPECT_EQ(datum.count(), 0u);
    EXPECT_EQ(datum.size(), 0u);
}

// Test setValue with a valid Value pointer
TEST_F(ExifdatumTest_739, SetValueWithValidPointer_739) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    
    AsciiValue val;
    val.read("Nikon");
    datum.setValue(&val);
    
    EXPECT_EQ(datum.toString(), "Nikon");
    EXPECT_GT(datum.count(), 0u);
}

// Test setValue clones the value (modifying original doesn't affect datum)
TEST_F(ExifdatumTest_739, SetValueClones_739) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    
    AsciiValue val;
    val.read("Canon");
    datum.setValue(&val);
    
    // Modify original value
    val.read("Nikon");
    
    // Datum should still have "Canon"
    EXPECT_EQ(datum.toString(), "Canon");
}

// Test setValue with string
TEST_F(ExifdatumTest_739, SetValueWithString_739) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Initial");
    Exifdatum datum(key, &val);
    
    int result = datum.setValue("NewValue");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "NewValue");
}

// Test operator= with string
TEST_F(ExifdatumTest_739, AssignString_739) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Initial");
    Exifdatum datum(key, &val);
    
    datum = std::string("Updated");
    EXPECT_EQ(datum.toString(), "Updated");
}

// Test operator= with uint16_t
TEST_F(ExifdatumTest_739, AssignUint16_739) {
    ExifKey key("Exif.Image.Orientation");
    UShortValue val;
    val.read("1");
    Exifdatum datum(key, &val);
    
    datum = static_cast<uint16_t>(3);
    EXPECT_EQ(datum.toInt64(0), 3);
}

// Test operator= with uint32_t
TEST_F(ExifdatumTest_739, AssignUint32_739) {
    ExifKey key("Exif.Image.ImageWidth");
    ULongValue val;
    val.read("100");
    Exifdatum datum(key, &val);
    
    datum = static_cast<uint32_t>(200);
    EXPECT_EQ(datum.toInt64(0), 200);
}

// Test operator= with int16_t
TEST_F(ExifdatumTest_739, AssignInt16_739) {
    ExifKey key("Exif.Image.Orientation");
    ShortValue val;
    val.read("1");
    Exifdatum datum(key, &val);
    
    datum = static_cast<int16_t>(-5);
    EXPECT_EQ(datum.toInt64(0), -5);
}

// Test operator= with int32_t
TEST_F(ExifdatumTest_739, AssignInt32_739) {
    ExifKey key("Exif.Image.ImageWidth");
    LongValue val;
    val.read("100");
    Exifdatum datum(key, &val);
    
    datum = static_cast<int32_t>(-100);
    EXPECT_EQ(datum.toInt64(0), -100);
}

// Test operator= with URational
TEST_F(ExifdatumTest_739, AssignURational_739) {
    ExifKey key("Exif.Image.XResolution");
    URationalValue val;
    val.read("72/1");
    Exifdatum datum(key, &val);
    
    datum = URational(300, 1);
    EXPECT_EQ(datum.toRational(0), Rational(300, 1));
}

// Test operator= with Rational
TEST_F(ExifdatumTest_739, AssignRational_739) {
    ExifKey key("Exif.Photo.ExposureBiasValue");
    RationalValue val;
    val.read("0/1");
    Exifdatum datum(key, &val);
    
    datum = Rational(-1, 3);
    Rational r = datum.toRational(0);
    EXPECT_EQ(r.first, -1);
    EXPECT_EQ(r.second, 3);
}

// Test operator= with Value
TEST_F(ExifdatumTest_739, AssignValue_739) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    Exifdatum datum(key, &val);
    
    AsciiValue newVal;
    newVal.read("Nikon");
    datum = static_cast<const Value&>(newVal);
    EXPECT_EQ(datum.toString(), "Nikon");
}

// Test tag() returns correct tag
TEST_F(ExifdatumTest_739, TagReturnsCorrectValue_739) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.tag(), key.tag());
}

// Test typeId when no value set
TEST_F(ExifdatumTest_739, TypeIdWithNoValue_739) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    
    // When no value is set, typeId should return some default
    TypeId tid = datum.typeId();
    // Just ensure it doesn't crash; specific value depends on implementation
    (void)tid;
}

// Test typeId with value set
TEST_F(ExifdatumTest_739, TypeIdWithValue_739) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    Exifdatum datum(key, &val);
    
    EXPECT_EQ(datum.typeId(), asciiString);
}

// Test getValue returns clone
TEST_F(ExifdatumTest_739, GetValueReturnsClone_739) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    Exifdatum datum(key, &val);
    
    auto retrieved = datum.getValue();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->toString(), "Canon");
}

// Test getValue when no value is set
TEST_F(ExifdatumTest_739, GetValueWhenNoValue_739) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    
    auto retrieved = datum.getValue();
    // Should return nullptr or empty unique_ptr
    EXPECT_EQ(retrieved, nullptr);
}

// Test familyName returns "Exif"
TEST_F(ExifdatumTest_739, FamilyName_739) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    
    EXPECT_STREQ(datum.familyName(), "Exif");
}

// Test tagLabel returns non-empty string for known tags
TEST_F(ExifdatumTest_739, TagLabel_739) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test toFloat
TEST_F(ExifdatumTest_739, ToFloat_739) {
    ExifKey key("Exif.Image.XResolution");
    URationalValue val;
    val.read("72/1");
    Exifdatum datum(key, &val);
    
    EXPECT_FLOAT_EQ(datum.toFloat(0), 72.0f);
}

// Test toString with index
TEST_F(ExifdatumTest_739, ToStringWithIndex_739) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    Exifdatum datum(key, &val);
    
    std::string str = datum.toString(0);
    EXPECT_EQ(str, "Canon");
}

// Test setValue replaces existing value
TEST_F(ExifdatumTest_739, SetValueReplacesExistingValue_739) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val1;
    val1.read("Canon");
    Exifdatum datum(key, &val1);
    EXPECT_EQ(datum.toString(), "Canon");
    
    AsciiValue val2;
    val2.read("Sony");
    datum.setValue(&val2);
    EXPECT_EQ(datum.toString(), "Sony");
}

// Test setValue(nullptr) after having a value, then setting a new value
TEST_F(ExifdatumTest_739, SetValueNullThenNew_739) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val1;
    val1.read("Canon");
    Exifdatum datum(key, &val1);
    
    datum.setValue(static_cast<const Value*>(nullptr));
    EXPECT_EQ(datum.count(), 0u);
    
    AsciiValue val2;
    val2.read("Nikon");
    datum.setValue(&val2);
    EXPECT_EQ(datum.toString(), "Nikon");
}

// Test copy method
TEST_F(ExifdatumTest_739, CopyToBuffer_739) {
    ExifKey key("Exif.Image.Orientation");
    UShortValue val;
    val.read("1");
    Exifdatum datum(key, &val);
    
    byte buf[256] = {0};
    size_t copied = datum.copy(buf, littleEndian);
    EXPECT_GT(copied, 0u);
}

// Test sizeDataArea when no data area
TEST_F(ExifdatumTest_739, SizeDataAreaEmpty_739) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    Exifdatum datum(key, &val);
    
    EXPECT_EQ(datum.sizeDataArea(), 0u);
}

// Test ifdId
TEST_F(ExifdatumTest_739, IfdId_739) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    
    IfdId id = datum.ifdId();
    // Exif.Image.* should map to IfdId::ifd0Id
    EXPECT_EQ(id, IfdId::ifd0Id);
}

// Test write to ostream
TEST_F(ExifdatumTest_739, WriteToOstream_739) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    Exifdatum datum(key, &val);
    
    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test multiple setValue calls with pointer
TEST_F(ExifdatumTest_739, MultipleSetValueCalls_739) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    
    for (int i = 0; i < 10; ++i) {
        AsciiValue val;
        val.read("Value" + std::to_string(i));
        datum.setValue(&val);
        EXPECT_EQ(datum.toString(), "Value" + std::to_string(i));
    }
}

// Test idx returns valid index
TEST_F(ExifdatumTest_739, IdxReturnsValidValue_739) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    
    int index = datum.idx();
    // Default idx should be 0
    EXPECT_EQ(index, 0);
}

// Test typeName with value set
TEST_F(ExifdatumTest_739, TypeNameWithValue_739) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    Exifdatum datum(key, &val);
    
    const char* name = datum.typeName();
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "Ascii");
}

// Test typeSize with value set
TEST_F(ExifdatumTest_739, TypeSizeWithValue_739) {
    ExifKey key("Exif.Image.Orientation");
    UShortValue val;
    val.read("1");
    Exifdatum datum(key, &val);
    
    EXPECT_EQ(datum.typeSize(), 2u);
}
