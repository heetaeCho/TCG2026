#include <gtest/gtest.h>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/properties.hpp>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>
#include <sstream>

using namespace Exiv2;

class XmpdatumTest_1284 : public ::testing::Test {
protected:
    void SetUp() override {
        // XMP properties need to be registered
        XmpParser::initialize();
    }
    void TearDown() override {
        XmpParser::terminate();
    }
};

// Test construction with a valid XmpKey and null Value
TEST_F(XmpdatumTest_1284, ConstructWithKeyAndNullValue_1284) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Xmp.dc.title");
}

// Test construction with a valid XmpKey and a Value
TEST_F(XmpdatumTest_1284, ConstructWithKeyAndValue_1284) {
    XmpKey key("Xmp.dc.creator");
    XmpTextValue val("John Doe");
    Xmpdatum datum(key, &val);
    EXPECT_EQ(datum.key(), "Xmp.dc.creator");
    EXPECT_EQ(datum.toString(), "John Doe");
}

// Test copy constructor
TEST_F(XmpdatumTest_1284, CopyConstructor_1284) {
    XmpKey key("Xmp.dc.description");
    XmpTextValue val("A description");
    Xmpdatum original(key, &val);
    Xmpdatum copy(original);
    EXPECT_EQ(copy.key(), original.key());
    EXPECT_EQ(copy.toString(), original.toString());
}

// Test assignment operator
TEST_F(XmpdatumTest_1284, AssignmentOperator_1284) {
    XmpKey key1("Xmp.dc.title");
    XmpTextValue val1("Title1");
    Xmpdatum datum1(key1, &val1);

    XmpKey key2("Xmp.dc.creator");
    XmpTextValue val2("Creator1");
    Xmpdatum datum2(key2, &val2);

    datum2 = datum1;
    EXPECT_EQ(datum2.key(), "Xmp.dc.title");
    EXPECT_EQ(datum2.toString(), "Title1");
}

// Test familyName returns "Xmp"
TEST_F(XmpdatumTest_1284, FamilyNameIsXmp_1284) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_STREQ(datum.familyName(), "Xmp");
}

// Test groupName
TEST_F(XmpdatumTest_1284, GroupName_1284) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "dc");
}

// Test tagName
TEST_F(XmpdatumTest_1284, TagName_1284) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.tagName(), "title");
}

// Test tagLabel returns a non-empty string for known properties
TEST_F(XmpdatumTest_1284, TagLabel_1284) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    std::string label = datum.tagLabel();
    // dc.title should have a known label
    EXPECT_FALSE(label.empty());
}

// Test tagDesc returns a string (may be empty for some properties)
TEST_F(XmpdatumTest_1284, TagDesc_1284) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    std::string desc = datum.tagDesc();
    // tagDesc should return a string; it may or may not be empty depending on the property
    // Just verify it doesn't throw
    SUCCEED();
}

// Test tag() returns a numeric tag
TEST_F(XmpdatumTest_1284, Tag_1284) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    uint16_t tag = datum.tag();
    // Just verify it returns some value without crashing
    (void)tag;
    SUCCEED();
}

// Test typeId with no value set returns invalidTypeId or a default
TEST_F(XmpdatumTest_1284, TypeIdNoValue_1284) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    TypeId tid = datum.typeId();
    EXPECT_EQ(tid, invalidTypeId);
}

// Test typeId with a value set
TEST_F(XmpdatumTest_1284, TypeIdWithValue_1284) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("Test");
    Xmpdatum datum(key, &val);
    TypeId tid = datum.typeId();
    EXPECT_EQ(tid, xmpText);
}

// Test typeName with no value
TEST_F(XmpdatumTest_1284, TypeNameNoValue_1284) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    const char* tn = datum.typeName();
    // With no value, typeName might return empty or nullptr
    // Just ensure no crash
    (void)tn;
    SUCCEED();
}

// Test count with no value
TEST_F(XmpdatumTest_1284, CountNoValue_1284) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.count(), 0u);
}

// Test count with a value
TEST_F(XmpdatumTest_1284, CountWithValue_1284) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("Hello");
    Xmpdatum datum(key, &val);
    EXPECT_GE(datum.count(), 1u);
}

// Test size with no value
TEST_F(XmpdatumTest_1284, SizeNoValue_1284) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.size(), 0u);
}

// Test size with a value
TEST_F(XmpdatumTest_1284, SizeWithValue_1284) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("Hello");
    Xmpdatum datum(key, &val);
    EXPECT_GT(datum.size(), 0u);
}

// Test toString with no value
TEST_F(XmpdatumTest_1284, ToStringNoValue_1284) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.toString(), "");
}

// Test toString with a value
TEST_F(XmpdatumTest_1284, ToStringWithValue_1284) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("Test Title");
    Xmpdatum datum(key, &val);
    EXPECT_EQ(datum.toString(), "Test Title");
}

// Test toString(n) with a value
TEST_F(XmpdatumTest_1284, ToStringWithIndex_1284) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("Test Title");
    Xmpdatum datum(key, &val);
    EXPECT_EQ(datum.toString(0), "Test Title");
}

// Test setValue with a string
TEST_F(XmpdatumTest_1284, SetValueString_1284) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    int result = datum.setValue("New Title");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "New Title");
}

// Test setValue with a Value pointer
TEST_F(XmpdatumTest_1284, SetValuePointer_1284) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    XmpTextValue val("Value from pointer");
    datum.setValue(&val);
    EXPECT_EQ(datum.toString(), "Value from pointer");
}

// Test setValue with nullptr Value pointer
TEST_F(XmpdatumTest_1284, SetValueNullPointer_1284) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("Initial");
    Xmpdatum datum(key, &val);
    datum.setValue(static_cast<const Value*>(nullptr));
    // After setting nullptr, count and size should be 0
    EXPECT_EQ(datum.count(), 0u);
    EXPECT_EQ(datum.size(), 0u);
}

// Test getValue with a value
TEST_F(XmpdatumTest_1284, GetValueWithValue_1284) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("Get me");
    Xmpdatum datum(key, &val);
    auto v = datum.getValue();
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(v->toString(), "Get me");
}

// Test getValue with no value
TEST_F(XmpdatumTest_1284, GetValueNoValue_1284) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    auto v = datum.getValue();
    EXPECT_EQ(v, nullptr);
}

// Test write to ostream
TEST_F(XmpdatumTest_1284, WriteToStream_1284) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("Stream Test");
    Xmpdatum datum(key, &val);
    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test copy function returns 0 (XMP doesn't support binary copy)
TEST_F(XmpdatumTest_1284, CopyReturnsZero_1284) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("Copy test");
    Xmpdatum datum(key, &val);
    byte buf[100];
    size_t result = datum.copy(buf, bigEndian);
    EXPECT_EQ(result, 0u);
}

// Test toInt64 with a numeric XmpText value
TEST_F(XmpdatumTest_1284, ToInt64_1284) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("42");
    Xmpdatum datum(key, &val);
    EXPECT_EQ(datum.toInt64(0), 42);
}

// Test toFloat with a numeric XmpText value
TEST_F(XmpdatumTest_1284, ToFloat_1284) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("3.14");
    Xmpdatum datum(key, &val);
    EXPECT_FLOAT_EQ(datum.toFloat(0), 3.14f);
}

// Test template assignment operator with string
TEST_F(XmpdatumTest_1284, TemplateAssignmentString_1284) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum = std::string("Assigned via template");
    EXPECT_EQ(datum.toString(), "Assigned via template");
}

// Test with different XMP namespaces
TEST_F(XmpdatumTest_1284, DifferentNamespace_1284) {
    XmpKey key("Xmp.exif.DateTimeOriginal");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Xmp.exif.DateTimeOriginal");
    EXPECT_EQ(datum.groupName(), "exif");
    EXPECT_EQ(datum.tagName(), "DateTimeOriginal");
    EXPECT_STREQ(datum.familyName(), "Xmp");
}

// Test XmpKey construction with prefix and property
TEST_F(XmpdatumTest_1284, XmpKeyPrefixProperty_1284) {
    XmpKey key("dc", "subject");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Xmp.dc.subject");
    EXPECT_EQ(datum.groupName(), "dc");
    EXPECT_EQ(datum.tagName(), "subject");
}

// Test that modifying a copy doesn't affect original
TEST_F(XmpdatumTest_1284, CopyIndependence_1284) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("Original");
    Xmpdatum original(key, &val);
    Xmpdatum copy(original);
    
    copy.setValue("Modified");
    EXPECT_EQ(original.toString(), "Original");
    EXPECT_EQ(copy.toString(), "Modified");
}

// Test self-assignment
TEST_F(XmpdatumTest_1284, SelfAssignment_1284) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("Self");
    Xmpdatum datum(key, &val);
    datum = datum;
    EXPECT_EQ(datum.toString(), "Self");
    EXPECT_EQ(datum.key(), "Xmp.dc.title");
}

// Test typeSize with no value
TEST_F(XmpdatumTest_1284, TypeSizeNoValue_1284) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    size_t ts = datum.typeSize();
    // With no value, typeSize should return 0 or a default
    (void)ts;
    SUCCEED();
}

// Test value() throws when no value is set
TEST_F(XmpdatumTest_1284, ValueThrowsWhenNoValue_1284) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_THROW(datum.value(), Error);
}

// Test with XmpArrayValue (bag)
TEST_F(XmpdatumTest_1284, XmpArrayValue_1284) {
    XmpKey key("Xmp.dc.subject");
    XmpArrayValue val(xmpBag);
    val.read("keyword1");
    val.read("keyword2");
    Xmpdatum datum(key, &val);
    EXPECT_GE(datum.count(), 2u);
}
