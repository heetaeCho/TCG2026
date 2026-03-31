#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <sstream>
#include <memory>

class XmpdatumTest_1292 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test default construction with key and null value
TEST_F(XmpdatumTest_1292, ConstructWithNullValue_1292) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.key(), "Xmp.dc.title");
    EXPECT_EQ(datum.familyName(), std::string("Xmp"));
    EXPECT_EQ(datum.groupName(), "dc");
    EXPECT_EQ(datum.tagName(), "title");
}

// Test toString with null value returns empty string
TEST_F(XmpdatumTest_1292, ToStringWithNullValueReturnsEmpty_1292) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.toString(), "");
}

// Test toString(n) with null value returns empty string
TEST_F(XmpdatumTest_1292, ToStringNWithNullValueReturnsEmpty_1292) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.toString(0), "");
    EXPECT_EQ(datum.toString(1), "");
    EXPECT_EQ(datum.toString(100), "");
}

// Test setValue with string and then toString
TEST_F(XmpdatumTest_1292, SetValueStringAndToString_1292) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    datum.setValue("Test Title");
    EXPECT_EQ(datum.toString(), "Test Title");
}

// Test setValue with Value pointer
TEST_F(XmpdatumTest_1292, SetValuePointerAndToString_1292) {
    Exiv2::XmpKey key("Xmp.dc.description");
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("A description");
    
    Exiv2::Xmpdatum datum(key, value.get());
    EXPECT_EQ(datum.toString(), "A description");
}

// Test copy constructor
TEST_F(XmpdatumTest_1292, CopyConstructor_1292) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum1(key, nullptr);
    datum1.setValue("Original");
    
    Exiv2::Xmpdatum datum2(datum1);
    EXPECT_EQ(datum2.toString(), "Original");
    EXPECT_EQ(datum2.key(), "Xmp.dc.title");
}

// Test assignment operator
TEST_F(XmpdatumTest_1292, AssignmentOperator_1292) {
    Exiv2::XmpKey key1("Xmp.dc.title");
    Exiv2::Xmpdatum datum1(key1, nullptr);
    datum1.setValue("First");
    
    Exiv2::XmpKey key2("Xmp.dc.description");
    Exiv2::Xmpdatum datum2(key2, nullptr);
    datum2.setValue("Second");
    
    datum2 = datum1;
    EXPECT_EQ(datum2.toString(), "First");
    EXPECT_EQ(datum2.key(), "Xmp.dc.title");
}

// Test key components
TEST_F(XmpdatumTest_1292, KeyComponents_1292) {
    Exiv2::XmpKey key("Xmp.dc.creator");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.key(), "Xmp.dc.creator");
    EXPECT_EQ(datum.familyName(), std::string("Xmp"));
    EXPECT_EQ(datum.groupName(), "dc");
    EXPECT_EQ(datum.tagName(), "creator");
}

// Test count with null value
TEST_F(XmpdatumTest_1292, CountWithNullValue_1292) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.count(), 0u);
}

// Test count after setting value
TEST_F(XmpdatumTest_1292, CountAfterSetValue_1292) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    datum.setValue("Some text");
    
    EXPECT_GE(datum.count(), 1u);
}

// Test size with null value
TEST_F(XmpdatumTest_1292, SizeWithNullValue_1292) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.size(), 0u);
}

// Test typeId with null value
TEST_F(XmpdatumTest_1292, TypeIdWithNullValue_1292) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    // When no value is set, typeId should return some default
    Exiv2::TypeId tid = datum.typeId();
    // Just verify it doesn't crash and returns a valid TypeId
    (void)tid;
}

// Test getValue with null value
TEST_F(XmpdatumTest_1292, GetValueWithNullValue_1292) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    auto val = datum.getValue();
    EXPECT_EQ(val.get(), nullptr);
}

// Test getValue after setting value
TEST_F(XmpdatumTest_1292, GetValueAfterSetValue_1292) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    datum.setValue("Hello");
    
    auto val = datum.getValue();
    EXPECT_NE(val.get(), nullptr);
    EXPECT_EQ(val->toString(), "Hello");
}

// Test write to ostream
TEST_F(XmpdatumTest_1292, WriteToOstream_1292) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    datum.setValue("Test output");
    
    std::ostringstream oss;
    datum.write(oss, nullptr);
    // The output should contain the value
    EXPECT_FALSE(oss.str().empty());
}

// Test setValue with Value* pointer (setting to null clears value)
TEST_F(XmpdatumTest_1292, SetValueWithNullPointer_1292) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    datum.setValue("Something");
    EXPECT_EQ(datum.toString(), "Something");
    
    datum.setValue(static_cast<const Exiv2::Value*>(nullptr));
    EXPECT_EQ(datum.toString(), "");
}

// Test template assignment operator with string
TEST_F(XmpdatumTest_1292, TemplateAssignmentString_1292) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    datum = std::string("Assigned value");
    EXPECT_EQ(datum.toString(), "Assigned value");
}

// Test copy operation returns 0 (XMP data doesn't support byte copy typically)
TEST_F(XmpdatumTest_1292, CopyReturnsZero_1292) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    datum.setValue("Test");
    
    Exiv2::byte buf[256];
    size_t result = datum.copy(buf, Exiv2::bigEndian);
    // For XMP, copy typically returns 0
    EXPECT_EQ(result, 0u);
}

// Test with xmpText type
TEST_F(XmpdatumTest_1292, XmpTextType_1292) {
    Exiv2::XmpKey key("Xmp.dc.title");
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("XMP Text Value");
    
    Exiv2::Xmpdatum datum(key, value.get());
    
    EXPECT_EQ(datum.typeId(), Exiv2::xmpText);
    EXPECT_EQ(datum.toString(), "XMP Text Value");
    EXPECT_EQ(datum.toString(0), "XMP Text Value");
}

// Test toString(0) returns same as toString() for simple values
TEST_F(XmpdatumTest_1292, ToStringZeroEqualsToString_1292) {
    Exiv2::XmpKey key("Xmp.dc.title");
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("Simple Text");
    
    Exiv2::Xmpdatum datum(key, value.get());
    
    EXPECT_EQ(datum.toString(0), datum.toString());
}

// Test tagLabel is not empty for known tags
TEST_F(XmpdatumTest_1292, TagLabelForKnownTag_1292) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    std::string label = datum.tagLabel();
    // Known tag should have a label
    EXPECT_FALSE(label.empty());
}

// Test self-assignment
TEST_F(XmpdatumTest_1292, SelfAssignment_1292) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    datum.setValue("Self assign test");
    
    datum = datum;
    EXPECT_EQ(datum.toString(), "Self assign test");
    EXPECT_EQ(datum.key(), "Xmp.dc.title");
}

// Test empty string value
TEST_F(XmpdatumTest_1292, EmptyStringValue_1292) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    datum.setValue("");
    
    EXPECT_EQ(datum.toString(), "");
}

// Test value() throws when no value is set
TEST_F(XmpdatumTest_1292, ValueThrowsWhenNullValue_1292) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    EXPECT_THROW(datum.value(), Exiv2::Error);
}

// Test typeName with null value
TEST_F(XmpdatumTest_1292, TypeNameWithNullValue_1292) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    // When no value set, typeName might return empty or null
    const char* tn = datum.typeName();
    // Just verify it doesn't crash
    (void)tn;
}

// Test typeName after setting xmpText value
TEST_F(XmpdatumTest_1292, TypeNameAfterSetValue_1292) {
    Exiv2::XmpKey key("Xmp.dc.title");
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("Test");
    
    Exiv2::Xmpdatum datum(key, value.get());
    
    const char* tn = datum.typeName();
    EXPECT_NE(tn, nullptr);
    EXPECT_EQ(std::string(tn), "XmpText");
}

// Test with different XMP namespaces
TEST_F(XmpdatumTest_1292, DifferentNamespaces_1292) {
    Exiv2::XmpKey key1("Xmp.dc.title");
    Exiv2::Xmpdatum datum1(key1, nullptr);
    EXPECT_EQ(datum1.groupName(), "dc");
    
    Exiv2::XmpKey key2("Xmp.xmp.CreateDate");
    Exiv2::Xmpdatum datum2(key2, nullptr);
    EXPECT_EQ(datum2.groupName(), "xmp");
}

// Test toInt64 with null value
TEST_F(XmpdatumTest_1292, ToInt64WithNullValue_1292) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    // Should return 0 or default when no value
    int64_t val = datum.toInt64(0);
    EXPECT_EQ(val, 0);
}

// Test toFloat with null value
TEST_F(XmpdatumTest_1292, ToFloatWithNullValue_1292) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    float val = datum.toFloat(0);
    EXPECT_FLOAT_EQ(val, 0.0f);
}
