#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/properties.hpp>
#include <exiv2/value.hpp>
#include <exiv2/error.hpp>

namespace {

// Helper to create a valid XMP key string
const std::string kValidXmpKey = "Xmp.dc.title";
const std::string kValidXmpKey2 = "Xmp.dc.description";
const std::string kValidPrefix = "dc";
const std::string kValidProperty = "title";

class XmpdatumTest_2179 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test default construction with XmpKey
TEST_F(XmpdatumTest_2179, ConstructWithKey_2179) {
    Exiv2::XmpKey key(kValidXmpKey);
    Exiv2::Xmpdatum datum(key);
    
    EXPECT_EQ(datum.key(), kValidXmpKey);
    EXPECT_EQ(datum.count(), 0u);
}

// Test construction with key and value
TEST_F(XmpdatumTest_2179, ConstructWithKeyAndValue_2179) {
    Exiv2::XmpKey key(kValidXmpKey);
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("Test Value");
    
    Exiv2::Xmpdatum datum(key, value.get());
    
    EXPECT_EQ(datum.key(), kValidXmpKey);
    EXPECT_EQ(datum.toString(), "Test Value");
}

// Test construction with null value
TEST_F(XmpdatumTest_2179, ConstructWithNullValue_2179) {
    Exiv2::XmpKey key(kValidXmpKey);
    Exiv2::Xmpdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.key(), kValidXmpKey);
    EXPECT_EQ(datum.count(), 0u);
}

// Test copy constructor
TEST_F(XmpdatumTest_2179, CopyConstructor_2179) {
    Exiv2::XmpKey key(kValidXmpKey);
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("Copy Test");
    
    Exiv2::Xmpdatum datum1(key, value.get());
    Exiv2::Xmpdatum datum2(datum1);
    
    EXPECT_EQ(datum2.key(), kValidXmpKey);
    EXPECT_EQ(datum2.toString(), "Copy Test");
}

// Test assignment operator
TEST_F(XmpdatumTest_2179, AssignmentOperator_2179) {
    Exiv2::XmpKey key1(kValidXmpKey);
    auto value1 = Exiv2::Value::create(Exiv2::xmpText);
    value1->read("Original");
    Exiv2::Xmpdatum datum1(key1, value1.get());
    
    Exiv2::XmpKey key2(kValidXmpKey2);
    auto value2 = Exiv2::Value::create(Exiv2::xmpText);
    value2->read("Assigned");
    Exiv2::Xmpdatum datum2(key2, value2.get());
    
    datum1 = datum2;
    
    EXPECT_EQ(datum1.key(), kValidXmpKey2);
    EXPECT_EQ(datum1.toString(), "Assigned");
}

// Test familyName returns "Xmp"
TEST_F(XmpdatumTest_2179, FamilyNameIsXmp_2179) {
    Exiv2::XmpKey key(kValidXmpKey);
    Exiv2::Xmpdatum datum(key);
    
    EXPECT_STREQ(datum.familyName(), "Xmp");
}

// Test groupName
TEST_F(XmpdatumTest_2179, GroupName_2179) {
    Exiv2::XmpKey key(kValidXmpKey);
    Exiv2::Xmpdatum datum(key);
    
    EXPECT_EQ(datum.groupName(), "dc");
}

// Test tagName
TEST_F(XmpdatumTest_2179, TagName_2179) {
    Exiv2::XmpKey key(kValidXmpKey);
    Exiv2::Xmpdatum datum(key);
    
    EXPECT_EQ(datum.tagName(), "title");
}

// Test key() method
TEST_F(XmpdatumTest_2179, KeyMethod_2179) {
    Exiv2::XmpKey key(kValidXmpKey);
    Exiv2::Xmpdatum datum(key);
    
    EXPECT_EQ(datum.key(), kValidXmpKey);
}

// Test setValue with string
TEST_F(XmpdatumTest_2179, SetValueWithString_2179) {
    Exiv2::XmpKey key(kValidXmpKey);
    Exiv2::Xmpdatum datum(key);
    
    datum.setValue("Hello World");
    
    EXPECT_EQ(datum.toString(), "Hello World");
}

// Test setValue with Value object
TEST_F(XmpdatumTest_2179, SetValueWithValueObject_2179) {
    Exiv2::XmpKey key(kValidXmpKey);
    Exiv2::Xmpdatum datum(key);
    
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("Value Object Test");
    datum.setValue(value.get());
    
    EXPECT_EQ(datum.toString(), "Value Object Test");
}

// Test typeId when no value is set
TEST_F(XmpdatumTest_2179, TypeIdNoValue_2179) {
    Exiv2::XmpKey key(kValidXmpKey);
    Exiv2::Xmpdatum datum(key);
    
    // When no value is set, typeId should be invalidTypeId or similar default
    Exiv2::TypeId typeId = datum.typeId();
    // Just check it doesn't crash; the exact value depends on implementation
    (void)typeId;
}

// Test typeId with xmpText value
TEST_F(XmpdatumTest_2179, TypeIdWithXmpTextValue_2179) {
    Exiv2::XmpKey key(kValidXmpKey);
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("test");
    Exiv2::Xmpdatum datum(key, value.get());
    
    EXPECT_EQ(datum.typeId(), Exiv2::xmpText);
}

// Test count with value
TEST_F(XmpdatumTest_2179, CountWithValue_2179) {
    Exiv2::XmpKey key(kValidXmpKey);
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("test");
    Exiv2::Xmpdatum datum(key, value.get());
    
    EXPECT_GT(datum.count(), 0u);
}

// Test count without value
TEST_F(XmpdatumTest_2179, CountWithoutValue_2179) {
    Exiv2::XmpKey key(kValidXmpKey);
    Exiv2::Xmpdatum datum(key);
    
    EXPECT_EQ(datum.count(), 0u);
}

// Test size without value
TEST_F(XmpdatumTest_2179, SizeWithoutValue_2179) {
    Exiv2::XmpKey key(kValidXmpKey);
    Exiv2::Xmpdatum datum(key);
    
    EXPECT_EQ(datum.size(), 0u);
}

// Test size with value
TEST_F(XmpdatumTest_2179, SizeWithValue_2179) {
    Exiv2::XmpKey key(kValidXmpKey);
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("test data");
    Exiv2::Xmpdatum datum(key, value.get());
    
    EXPECT_GT(datum.size(), 0u);
}

// Test toString
TEST_F(XmpdatumTest_2179, ToString_2179) {
    Exiv2::XmpKey key(kValidXmpKey);
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("StringValue");
    Exiv2::Xmpdatum datum(key, value.get());
    
    EXPECT_EQ(datum.toString(), "StringValue");
}

// Test value() method returns reference
TEST_F(XmpdatumTest_2179, ValueMethodReturnsValue_2179) {
    Exiv2::XmpKey key(kValidXmpKey);
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("val");
    Exiv2::Xmpdatum datum(key, value.get());
    
    const Exiv2::Value& val = datum.value();
    EXPECT_EQ(val.toString(), "val");
}

// Test constructing XmpKey with prefix and property
TEST_F(XmpdatumTest_2179, XmpKeyWithPrefixAndProperty_2179) {
    Exiv2::XmpKey key(kValidPrefix, kValidProperty);
    Exiv2::Xmpdatum datum(key);
    
    EXPECT_EQ(datum.key(), kValidXmpKey);
    EXPECT_EQ(datum.groupName(), kValidPrefix);
    EXPECT_EQ(datum.tagName(), kValidProperty);
}

// Test overwriting value with new setValue call
TEST_F(XmpdatumTest_2179, OverwriteValue_2179) {
    Exiv2::XmpKey key(kValidXmpKey);
    Exiv2::Xmpdatum datum(key);
    
    datum.setValue("First");
    EXPECT_EQ(datum.toString(), "First");
    
    datum.setValue("Second");
    EXPECT_EQ(datum.toString(), "Second");
}

// Test copy preserves value independently
TEST_F(XmpdatumTest_2179, CopyIsIndependent_2179) {
    Exiv2::XmpKey key(kValidXmpKey);
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("Independent");
    Exiv2::Xmpdatum datum1(key, value.get());
    
    Exiv2::Xmpdatum datum2(datum1);
    
    datum2.setValue("Modified");
    
    EXPECT_EQ(datum1.toString(), "Independent");
    EXPECT_EQ(datum2.toString(), "Modified");
}

// Test self-assignment
TEST_F(XmpdatumTest_2179, SelfAssignment_2179) {
    Exiv2::XmpKey key(kValidXmpKey);
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("SelfAssign");
    Exiv2::Xmpdatum datum(key, value.get());
    
    datum = datum;
    
    EXPECT_EQ(datum.key(), kValidXmpKey);
    EXPECT_EQ(datum.toString(), "SelfAssign");
}

// Test with empty string value
TEST_F(XmpdatumTest_2179, EmptyStringValue_2179) {
    Exiv2::XmpKey key(kValidXmpKey);
    Exiv2::Xmpdatum datum(key);
    
    datum.setValue("");
    
    EXPECT_EQ(datum.toString(), "");
}

// Test XmpKey clone used internally
TEST_F(XmpdatumTest_2179, KeyClonedIndependently_2179) {
    Exiv2::XmpKey key(kValidXmpKey);
    Exiv2::Xmpdatum datum(key);
    
    // The datum should have its own copy of the key
    EXPECT_EQ(datum.key(), kValidXmpKey);
}

// Test with different XmpKey prefixes
TEST_F(XmpdatumTest_2179, DifferentPrefixes_2179) {
    Exiv2::XmpKey key1("Xmp.dc.title");
    Exiv2::Xmpdatum datum1(key1);
    EXPECT_EQ(datum1.groupName(), "dc");
    
    Exiv2::XmpKey key2("Xmp.xmp.CreateDate");
    Exiv2::Xmpdatum datum2(key2);
    EXPECT_EQ(datum2.groupName(), "xmp");
}

// Test tag() method
TEST_F(XmpdatumTest_2179, TagMethod_2179) {
    Exiv2::XmpKey key(kValidXmpKey);
    Exiv2::Xmpdatum datum(key);
    
    // tag() should return some value; we just verify it doesn't crash
    uint16_t tag = datum.tag();
    (void)tag;
}

}  // namespace
