#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <sstream>
#include <cstdint>

using namespace Exiv2;

class XmpdatumTest_1293 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that constructing Xmpdatum with a key and null value works
TEST_F(XmpdatumTest_1293, ConstructWithNullValue_1293) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Xmp.dc.title");
}

// Test that toInt64 returns -1 when no value is set
TEST_F(XmpdatumTest_1293, ToInt64ReturnsMinusOneWhenNoValue_1293) {
    XmpKey key("Xmp.dc.subject");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.toInt64(0), -1);
}

// Test that toInt64 returns -1 for various indices when no value is set
TEST_F(XmpdatumTest_1293, ToInt64ReturnsMinusOneForAnyIndexWhenNoValue_1293) {
    XmpKey key("Xmp.dc.subject");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.toInt64(0), -1);
    EXPECT_EQ(datum.toInt64(1), -1);
    EXPECT_EQ(datum.toInt64(100), -1);
}

// Test that toInt64 returns correct value when a value is set
TEST_F(XmpdatumTest_1293, ToInt64ReturnsValueWhenSet_1293) {
    XmpKey key("Xmp.dc.subject");
    Xmpdatum datum(key, nullptr);
    datum.setValue("42");
    EXPECT_EQ(datum.toInt64(0), 42);
}

// Test key() returns the correct key string
TEST_F(XmpdatumTest_1293, KeyReturnsCorrectString_1293) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Xmp.dc.title");
}

// Test familyName() returns "Xmp"
TEST_F(XmpdatumTest_1293, FamilyNameReturnsXmp_1293) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_STREQ(datum.familyName(), "Xmp");
}

// Test groupName() returns the correct group
TEST_F(XmpdatumTest_1293, GroupNameReturnsCorrectGroup_1293) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "dc");
}

// Test tagName() returns the correct tag name
TEST_F(XmpdatumTest_1293, TagNameReturnsCorrectName_1293) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.tagName(), "title");
}

// Test copy constructor creates independent copy
TEST_F(XmpdatumTest_1293, CopyConstructorCreatesIndependentCopy_1293) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum1(key, nullptr);
    datum1.setValue("hello");
    
    Xmpdatum datum2(datum1);
    EXPECT_EQ(datum2.key(), "Xmp.dc.title");
    EXPECT_EQ(datum2.toString(), datum1.toString());
}

// Test assignment operator
TEST_F(XmpdatumTest_1293, AssignmentOperatorWorks_1293) {
    XmpKey key1("Xmp.dc.title");
    Xmpdatum datum1(key1, nullptr);
    datum1.setValue("value1");

    XmpKey key2("Xmp.dc.subject");
    Xmpdatum datum2(key2, nullptr);
    datum2.setValue("value2");

    datum2 = datum1;
    EXPECT_EQ(datum2.key(), "Xmp.dc.title");
    EXPECT_EQ(datum2.toString(), "value1");
}

// Test count() when no value is set
TEST_F(XmpdatumTest_1293, CountWhenNoValue_1293) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.count(), 0u);
}

// Test size() when no value is set
TEST_F(XmpdatumTest_1293, SizeWhenNoValue_1293) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.size(), 0u);
}

// Test toString() when no value is set
TEST_F(XmpdatumTest_1293, ToStringWhenNoValue_1293) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.toString(), "");
}

// Test toString() when value is set
TEST_F(XmpdatumTest_1293, ToStringWhenValueSet_1293) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("test_value");
    EXPECT_EQ(datum.toString(), "test_value");
}

// Test setValue with a Value pointer
TEST_F(XmpdatumTest_1293, SetValueWithValuePointer_1293) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    
    auto value = Value::create(xmpText);
    value->read("pointer_value");
    datum.setValue(value.get());
    
    EXPECT_EQ(datum.toString(), "pointer_value");
}

// Test setValue with nullptr clears value
TEST_F(XmpdatumTest_1293, SetValueWithNullptrClearsValue_1293) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("some_value");
    EXPECT_NE(datum.toString(), "");
    
    datum.setValue(static_cast<const Value*>(nullptr));
    EXPECT_EQ(datum.toInt64(0), -1);
}

// Test toFloat returns 0 or similar when no value
TEST_F(XmpdatumTest_1293, ToFloatWhenNoValue_1293) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    float result = datum.toFloat(0);
    EXPECT_FLOAT_EQ(result, 0.0f);
}

// Test toFloat returns correct value when set
TEST_F(XmpdatumTest_1293, ToFloatReturnsCorrectValue_1293) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("3.14");
    float result = datum.toFloat(0);
    EXPECT_NEAR(result, 3.14f, 0.01f);
}

// Test getValue returns nullptr when no value set
TEST_F(XmpdatumTest_1293, GetValueReturnsNullWhenNoValue_1293) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    auto val = datum.getValue();
    EXPECT_EQ(val, nullptr);
}

// Test getValue returns non-null when value is set
TEST_F(XmpdatumTest_1293, GetValueReturnsNonNullWhenValueSet_1293) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("test");
    auto val = datum.getValue();
    EXPECT_NE(val, nullptr);
}

// Test write to ostream
TEST_F(XmpdatumTest_1293, WriteToOstream_1293) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("write_test");
    
    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test typeId when no value is set
TEST_F(XmpdatumTest_1293, TypeIdWhenNoValue_1293) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    TypeId type = datum.typeId();
    EXPECT_EQ(type, invalidTypeId);
}

// Test typeId when value is set
TEST_F(XmpdatumTest_1293, TypeIdWhenValueSet_1293) {
    XmpKey key("Xmp.dc.title");
    auto value = Value::create(xmpText);
    value->read("hello");
    Xmpdatum datum(key, value.get());
    EXPECT_EQ(datum.typeId(), xmpText);
}

// Test constructing with a value pointer
TEST_F(XmpdatumTest_1293, ConstructWithValuePointer_1293) {
    XmpKey key("Xmp.dc.title");
    auto value = Value::create(xmpText);
    value->read("initial_value");
    
    Xmpdatum datum(key, value.get());
    EXPECT_EQ(datum.toString(), "initial_value");
    EXPECT_EQ(datum.key(), "Xmp.dc.title");
}

// Test toInt64 with a set integer value
TEST_F(XmpdatumTest_1293, ToInt64WithSetIntegerValue_1293) {
    XmpKey key("Xmp.dc.subject");
    Xmpdatum datum(key, nullptr);
    datum.setValue("12345");
    EXPECT_EQ(datum.toInt64(0), 12345);
}

// Test toInt64 with negative value
TEST_F(XmpdatumTest_1293, ToInt64WithNegativeValue_1293) {
    XmpKey key("Xmp.dc.subject");
    Xmpdatum datum(key, nullptr);
    datum.setValue("-99");
    EXPECT_EQ(datum.toInt64(0), -99);
}

// Test toInt64 with zero value
TEST_F(XmpdatumTest_1293, ToInt64WithZeroValue_1293) {
    XmpKey key("Xmp.dc.subject");
    Xmpdatum datum(key, nullptr);
    datum.setValue("0");
    EXPECT_EQ(datum.toInt64(0), 0);
}

// Test copy method returns 0 (Xmpdatum::copy does nothing meaningful)
TEST_F(XmpdatumTest_1293, CopyReturnsZero_1293) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("test");
    
    byte buf[256] = {};
    size_t result = datum.copy(buf, littleEndian);
    EXPECT_EQ(result, 0u);
}

// Test toString with index parameter when no value
TEST_F(XmpdatumTest_1293, ToStringWithIndexWhenNoValue_1293) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.toString(0), "");
}

// Test count after setting value
TEST_F(XmpdatumTest_1293, CountAfterSettingValue_1293) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("hello");
    EXPECT_GE(datum.count(), 1u);
}

// Test size after setting value
TEST_F(XmpdatumTest_1293, SizeAfterSettingValue_1293) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("hello");
    EXPECT_GT(datum.size(), 0u);
}

// Test self-assignment
TEST_F(XmpdatumTest_1293, SelfAssignment_1293) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("self");
    
    datum = datum;
    EXPECT_EQ(datum.key(), "Xmp.dc.title");
    EXPECT_EQ(datum.toString(), "self");
}

// Test toRational when no value set
TEST_F(XmpdatumTest_1293, ToRationalWhenNoValue_1293) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    Rational r = datum.toRational(0);
    EXPECT_EQ(r.first, 0);
    EXPECT_EQ(r.second, 0);
}
