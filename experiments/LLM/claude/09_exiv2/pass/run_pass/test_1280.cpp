#include <gtest/gtest.h>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/properties.hpp>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>
#include <sstream>

using namespace Exiv2;

class XmpdatumTest_1280 : public ::testing::Test {
protected:
    void SetUp() override {
        // Enable XMP support if needed
        XmpParser::initialize();
    }
    void TearDown() override {
        XmpParser::terminate();
    }
};

// Test that familyName returns "Xmp" for a valid Xmpdatum
TEST_F(XmpdatumTest_1280, FamilyNameReturnsXmp_1280) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_STREQ(datum.familyName(), "Xmp");
}

// Test that key() returns the expected key string
TEST_F(XmpdatumTest_1280, KeyReturnsCorrectString_1280) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Xmp.dc.title");
}

// Test groupName returns the correct group
TEST_F(XmpdatumTest_1280, GroupNameReturnsCorrectGroup_1280) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "dc");
}

// Test tagName returns the correct tag
TEST_F(XmpdatumTest_1280, TagNameReturnsCorrectTag_1280) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.tagName(), "title");
}

// Test that constructing Xmpdatum with nullptr value results in no value
TEST_F(XmpdatumTest_1280, NullValueConstruction_1280) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    // getValue should return nullptr when no value is set
    auto val = datum.getValue();
    EXPECT_EQ(val.get(), nullptr);
}

// Test copy constructor
TEST_F(XmpdatumTest_1280, CopyConstructor_1280) {
    XmpKey key("Xmp.dc.subject");
    Xmpdatum datum(key, nullptr);
    datum.setValue("test value");
    
    Xmpdatum copy(datum);
    EXPECT_EQ(copy.key(), datum.key());
    EXPECT_EQ(copy.familyName(), std::string("Xmp"));
    EXPECT_EQ(copy.toString(), datum.toString());
}

// Test assignment operator
TEST_F(XmpdatumTest_1280, AssignmentOperator_1280) {
    XmpKey key1("Xmp.dc.title");
    Xmpdatum datum1(key1, nullptr);
    datum1.setValue("value1");

    XmpKey key2("Xmp.dc.subject");
    Xmpdatum datum2(key2, nullptr);
    datum2.setValue("value2");

    datum2 = datum1;
    EXPECT_EQ(datum2.key(), "Xmp.dc.title");
    EXPECT_EQ(datum2.toString(), datum1.toString());
}

// Test setValue with string
TEST_F(XmpdatumTest_1280, SetValueWithString_1280) {
    XmpKey key("Xmp.dc.description");
    Xmpdatum datum(key, nullptr);
    int result = datum.setValue("Hello World");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "Hello World");
}

// Test setValue with Value pointer
TEST_F(XmpdatumTest_1280, SetValueWithValuePointer_1280) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    
    auto value = Value::create(xmpText);
    value->read("Test Title");
    datum.setValue(value.get());
    
    EXPECT_EQ(datum.toString(), "Test Title");
}

// Test setValue with nullptr Value pointer
TEST_F(XmpdatumTest_1280, SetValueWithNullptr_1280) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("some value");
    
    // Setting nullptr should clear the value
    datum.setValue(nullptr);
    auto val = datum.getValue();
    EXPECT_EQ(val.get(), nullptr);
}

// Test typeId when no value is set
TEST_F(XmpdatumTest_1280, TypeIdWithNoValue_1280) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    // When no value is set, typeId should return unsignedByte or invalidTypeId
    TypeId typeId = datum.typeId();
    // Just check it doesn't crash; the specific value depends on implementation
    (void)typeId;
}

// Test count when no value is set
TEST_F(XmpdatumTest_1280, CountWithNoValue_1280) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.count(), 0u);
}

// Test size when no value is set
TEST_F(XmpdatumTest_1280, SizeWithNoValue_1280) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.size(), 0u);
}

// Test toString with index when value is set
TEST_F(XmpdatumTest_1280, ToStringWithIndex_1280) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("Test String");
    EXPECT_EQ(datum.toString(0), "Test String");
}

// Test count after setting a value
TEST_F(XmpdatumTest_1280, CountAfterSetValue_1280) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("Some value");
    EXPECT_GE(datum.count(), 1u);
}

// Test size after setting a value
TEST_F(XmpdatumTest_1280, SizeAfterSetValue_1280) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("Some value");
    EXPECT_GT(datum.size(), 0u);
}

// Test write to ostream
TEST_F(XmpdatumTest_1280, WriteToStream_1280) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("Stream Test");
    
    std::ostringstream oss;
    datum.write(oss, nullptr);
    EXPECT_FALSE(oss.str().empty());
}

// Test copy method returns 0 (XMP data typically doesn't support raw copy)
TEST_F(XmpdatumTest_1280, CopyReturnsZero_1280) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("Copy Test");
    
    byte buf[256] = {};
    size_t result = datum.copy(buf, bigEndian);
    // XMP copy typically returns 0
    EXPECT_EQ(result, 0u);
}

// Test toInt64 with a numeric value
TEST_F(XmpdatumTest_1280, ToInt64WithNumericValue_1280) {
    XmpKey key("Xmp.xmp.Rating");
    Xmpdatum datum(key, nullptr);
    datum.setValue("42");
    EXPECT_EQ(datum.toInt64(0), 42);
}

// Test toFloat with a float value
TEST_F(XmpdatumTest_1280, ToFloatWithFloatValue_1280) {
    XmpKey key("Xmp.xmp.Rating");
    Xmpdatum datum(key, nullptr);
    datum.setValue("3.14");
    EXPECT_NEAR(datum.toFloat(0), 3.14f, 0.01f);
}

// Test template assignment operator with string
TEST_F(XmpdatumTest_1280, TemplateAssignmentWithString_1280) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum = std::string("Template Test");
    EXPECT_EQ(datum.toString(), "Template Test");
}

// Test with different XMP namespaces
TEST_F(XmpdatumTest_1280, DifferentNamespaces_1280) {
    XmpKey key1("Xmp.dc.creator");
    Xmpdatum datum1(key1, nullptr);
    EXPECT_EQ(datum1.groupName(), "dc");
    
    XmpKey key2("Xmp.xmp.CreateDate");
    Xmpdatum datum2(key2, nullptr);
    EXPECT_EQ(datum2.groupName(), "xmp");
}

// Test tag returns a valid value
TEST_F(XmpdatumTest_1280, TagReturnsValue_1280) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    // tag() should return a value; just verify it doesn't crash
    uint16_t tag = datum.tag();
    (void)tag;
}

// Test tagLabel returns a non-empty string for known properties
TEST_F(XmpdatumTest_1280, TagLabelForKnownProperty_1280) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    std::string label = datum.tagLabel();
    // Known properties should have a label
    EXPECT_FALSE(label.empty());
}

// Test getValue returns a valid unique_ptr when value is set
TEST_F(XmpdatumTest_1280, GetValueReturnsValidPtr_1280) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("Get Value Test");
    
    auto val = datum.getValue();
    EXPECT_NE(val.get(), nullptr);
    EXPECT_EQ(val->toString(), "Get Value Test");
}

// Test value() reference when value is set
TEST_F(XmpdatumTest_1280, ValueReferenceWhenSet_1280) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("Reference Test");
    
    const Value& val = datum.value();
    EXPECT_EQ(val.toString(), "Reference Test");
}

// Test typeName when value is set
TEST_F(XmpdatumTest_1280, TypeNameWhenValueSet_1280) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("Type Name Test");
    
    const char* tn = datum.typeName();
    EXPECT_NE(tn, nullptr);
}

// Test typeSize when value is set
TEST_F(XmpdatumTest_1280, TypeSizeWhenValueSet_1280) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("Type Size Test");
    
    size_t ts = datum.typeSize();
    (void)ts; // Just verify it doesn't crash
}

// Test constructing with a Value
TEST_F(XmpdatumTest_1280, ConstructWithValue_1280) {
    XmpKey key("Xmp.dc.title");
    auto value = Value::create(xmpText);
    value->read("Constructed Value");
    
    Xmpdatum datum(key, value.get());
    EXPECT_EQ(datum.toString(), "Constructed Value");
    EXPECT_EQ(datum.key(), "Xmp.dc.title");
}

// Test self-assignment
TEST_F(XmpdatumTest_1280, SelfAssignment_1280) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("Self Assignment");
    
    datum = datum;
    EXPECT_EQ(datum.key(), "Xmp.dc.title");
    EXPECT_EQ(datum.toString(), "Self Assignment");
}
