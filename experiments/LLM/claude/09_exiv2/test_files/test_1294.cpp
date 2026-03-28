#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/value.hpp>
#include <exiv2/properties.hpp>
#include <exiv2/types.hpp>
#include <memory>
#include <sstream>

namespace {

class XmpdatumTest_1294 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test: Constructing Xmpdatum with a key and null value
TEST_F(XmpdatumTest_1294, ConstructWithNullValue_1294) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Xmp.dc.title");
}

// Test: toFloat returns -1 when no value is set
TEST_F(XmpdatumTest_1294, ToFloatReturnsNegativeOneWhenNoValue_1294) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    float result = datum.toFloat(0);
    EXPECT_FLOAT_EQ(result, -1.0f);
}

// Test: toFloat with a valid value
TEST_F(XmpdatumTest_1294, ToFloatReturnsValueWhenSet_1294) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    datum.setValue("3.14");
    float result = datum.toFloat(0);
    EXPECT_NEAR(result, 3.14f, 0.01f);
}

// Test: key() returns the correct key string
TEST_F(XmpdatumTest_1294, KeyReturnsCorrectString_1294) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    Exiv2::Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Xmp.dc.subject");
}

// Test: familyName() returns "Xmp"
TEST_F(XmpdatumTest_1294, FamilyNameReturnsXmp_1294) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    EXPECT_STREQ(datum.familyName(), "Xmp");
}

// Test: groupName() returns the correct group
TEST_F(XmpdatumTest_1294, GroupNameReturnsCorrectGroup_1294) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "dc");
}

// Test: tagName() returns the correct tag name
TEST_F(XmpdatumTest_1294, TagNameReturnsCorrectTag_1294) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.tagName(), "title");
}

// Test: Copy constructor creates independent copy
TEST_F(XmpdatumTest_1294, CopyConstructorCreatesIndependentCopy_1294) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum1(key, nullptr);
    datum1.setValue("hello");
    
    Exiv2::Xmpdatum datum2(datum1);
    EXPECT_EQ(datum2.key(), "Xmp.dc.title");
    EXPECT_EQ(datum2.toString(), datum1.toString());
}

// Test: Assignment operator
TEST_F(XmpdatumTest_1294, AssignmentOperatorWorks_1294) {
    Exiv2::XmpKey key1("Xmp.dc.title");
    Exiv2::Xmpdatum datum1(key1, nullptr);
    datum1.setValue("value1");

    Exiv2::XmpKey key2("Xmp.dc.subject");
    Exiv2::Xmpdatum datum2(key2, nullptr);
    datum2.setValue("value2");

    datum2 = datum1;
    EXPECT_EQ(datum2.key(), "Xmp.dc.title");
    EXPECT_EQ(datum2.toString(), "value1");
}

// Test: setValue with string
TEST_F(XmpdatumTest_1294, SetValueWithString_1294) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    int result = datum.setValue("test_value");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "test_value");
}

// Test: setValue with Value pointer
TEST_F(XmpdatumTest_1294, SetValueWithValuePointer_1294) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);

    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("test_xmp_value");
    datum.setValue(value.get());

    EXPECT_EQ(datum.toString(), "test_xmp_value");
}

// Test: setValue with nullptr resets value
TEST_F(XmpdatumTest_1294, SetValueWithNullptrResetsValue_1294) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    datum.setValue("some_value");
    datum.setValue(nullptr);
    
    float result = datum.toFloat(0);
    EXPECT_FLOAT_EQ(result, -1.0f);
}

// Test: toString when no value is set
TEST_F(XmpdatumTest_1294, ToStringWhenNoValueSet_1294) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    std::string result = datum.toString();
    EXPECT_EQ(result, "");
}

// Test: toString(n) when no value
TEST_F(XmpdatumTest_1294, ToStringNWhenNoValue_1294) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    std::string result = datum.toString(0);
    EXPECT_EQ(result, "");
}

// Test: count when no value is set
TEST_F(XmpdatumTest_1294, CountWhenNoValueSet_1294) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.count(), 0u);
}

// Test: size when no value is set
TEST_F(XmpdatumTest_1294, SizeWhenNoValueSet_1294) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.size(), 0u);
}

// Test: toInt64 when no value is set
TEST_F(XmpdatumTest_1294, ToInt64WhenNoValueSet_1294) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    int64_t result = datum.toInt64(0);
    EXPECT_EQ(result, -1);
}

// Test: toInt64 with a valid integer value
TEST_F(XmpdatumTest_1294, ToInt64WithValidValue_1294) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    datum.setValue("42");
    int64_t result = datum.toInt64(0);
    EXPECT_EQ(result, 42);
}

// Test: toFloat with n=0 on a set value
TEST_F(XmpdatumTest_1294, ToFloatWithNZero_1294) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    datum.setValue("2.5");
    float result = datum.toFloat(0);
    EXPECT_NEAR(result, 2.5f, 0.01f);
}

// Test: typeId when no value is set
TEST_F(XmpdatumTest_1294, TypeIdWhenNoValueSet_1294) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    // When no value is set, typeId should reflect an invalid/default type
    Exiv2::TypeId tid = datum.typeId();
    EXPECT_EQ(tid, Exiv2::invalidTypeId);
}

// Test: typeId after setting a value
TEST_F(XmpdatumTest_1294, TypeIdAfterSettingValue_1294) {
    Exiv2::XmpKey key("Xmp.dc.title");
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("test");
    Exiv2::Xmpdatum datum(key, value.get());
    EXPECT_EQ(datum.typeId(), Exiv2::xmpText);
}

// Test: getValue when no value is set returns nullptr
TEST_F(XmpdatumTest_1294, GetValueWhenNoValueSetReturnsNull_1294) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    auto val = datum.getValue();
    EXPECT_EQ(val.get(), nullptr);
}

// Test: getValue when value is set returns non-null
TEST_F(XmpdatumTest_1294, GetValueWhenValueSetReturnsNonNull_1294) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    datum.setValue("hello");
    auto val = datum.getValue();
    EXPECT_NE(val.get(), nullptr);
}

// Test: write to ostream
TEST_F(XmpdatumTest_1294, WriteToOstream_1294) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    datum.setValue("test_output");
    std::ostringstream oss;
    datum.write(oss, nullptr);
    EXPECT_FALSE(oss.str().empty());
}

// Test: Constructing with a Value pointer
TEST_F(XmpdatumTest_1294, ConstructWithValuePointer_1294) {
    Exiv2::XmpKey key("Xmp.dc.description");
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("initial_value");
    Exiv2::Xmpdatum datum(key, value.get());
    EXPECT_EQ(datum.toString(), "initial_value");
    EXPECT_EQ(datum.key(), "Xmp.dc.description");
}

// Test: toRational when no value is set
TEST_F(XmpdatumTest_1294, ToRationalWhenNoValueSet_1294) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    Exiv2::Rational result = datum.toRational(0);
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, 1);
}

// Test: copy returns 0 when no value
TEST_F(XmpdatumTest_1294, CopyReturnsZeroWhenNoValue_1294) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    Exiv2::byte buf[64] = {};
    size_t copied = datum.copy(buf, Exiv2::bigEndian);
    EXPECT_EQ(copied, 0u);
}

// Test: Template assignment operator with string
TEST_F(XmpdatumTest_1294, TemplateAssignmentWithString_1294) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    datum = std::string("template_value");
    EXPECT_EQ(datum.toString(), "template_value");
}

// Test: count after setting value
TEST_F(XmpdatumTest_1294, CountAfterSettingValue_1294) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    datum.setValue("some value");
    EXPECT_GE(datum.count(), 1u);
}

// Test: size after setting value
TEST_F(XmpdatumTest_1294, SizeAfterSettingValue_1294) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    datum.setValue("some value");
    EXPECT_GT(datum.size(), 0u);
}

}  // namespace
