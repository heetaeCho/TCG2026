#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <sstream>

using namespace Exiv2;

// Test fixture for Xmpdatum tests
class XmpdatumTest_1283 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure XMP parser is initialized
        XmpParser::initialize();
    }

    void TearDown() override {
        XmpParser::terminate();
    }
};

// Test construction with a valid XmpKey and null value
TEST_F(XmpdatumTest_1283, ConstructWithKeyAndNullValue_1283) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    EXPECT_EQ(datum.key(), "Xmp.dc.title");
    EXPECT_STREQ(datum.familyName(), "Xmp");
    EXPECT_EQ(datum.groupName(), "dc");
    EXPECT_EQ(datum.tagName(), "title");
}

// Test tagLabel returns a non-empty label for a known property
TEST_F(XmpdatumTest_1283, TagLabelForKnownProperty_1283) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test tagDesc returns a description for a known property
TEST_F(XmpdatumTest_1283, TagDescForKnownProperty_1283) {
    XmpKey key("Xmp.dc.description");
    Xmpdatum datum(key, nullptr);

    std::string desc = datum.tagDesc();
    // Known properties should have some description
    // (may or may not be empty depending on the property)
    EXPECT_NO_THROW(datum.tagDesc());
}

// Test copy construction
TEST_F(XmpdatumTest_1283, CopyConstruction_1283) {
    XmpKey key("Xmp.dc.creator");
    Xmpdatum original(key, nullptr);
    Xmpdatum copy(original);

    EXPECT_EQ(copy.key(), original.key());
    EXPECT_EQ(copy.tagName(), original.tagName());
    EXPECT_EQ(copy.groupName(), original.groupName());
    EXPECT_EQ(copy.tagLabel(), original.tagLabel());
}

// Test copy assignment
TEST_F(XmpdatumTest_1283, CopyAssignment_1283) {
    XmpKey key1("Xmp.dc.title");
    XmpKey key2("Xmp.dc.creator");
    Xmpdatum datum1(key1, nullptr);
    Xmpdatum datum2(key2, nullptr);

    datum2 = datum1;
    EXPECT_EQ(datum2.key(), "Xmp.dc.title");
    EXPECT_EQ(datum2.tagName(), "title");
}

// Test setValue with string and then read it back
TEST_F(XmpdatumTest_1283, SetValueWithString_1283) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    int result = datum.setValue("Test Title");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "Test Title");
}

// Test count after setting a value
TEST_F(XmpdatumTest_1283, CountAfterSetValue_1283) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    datum.setValue("Hello");
    EXPECT_GE(datum.count(), static_cast<size_t>(1));
}

// Test size after setting a value
TEST_F(XmpdatumTest_1283, SizeAfterSetValue_1283) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    datum.setValue("Hello");
    EXPECT_GT(datum.size(), static_cast<size_t>(0));
}

// Test typeId when value is set
TEST_F(XmpdatumTest_1283, TypeIdAfterSetValue_1283) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    datum.setValue("Test");
    TypeId tid = datum.typeId();
    // Should return a valid type ID (xmpText or similar)
    EXPECT_NE(tid, invalidTypeId);
}

// Test typeName when value is set
TEST_F(XmpdatumTest_1283, TypeNameAfterSetValue_1283) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    datum.setValue("Test");
    const char* tn = datum.typeName();
    EXPECT_NE(tn, nullptr);
}

// Test getValue when no value is set
TEST_F(XmpdatumTest_1283, GetValueWhenNoValueSet_1283) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    auto val = datum.getValue();
    // When no value is set, getValue may return nullptr
    // This is observable behavior
    EXPECT_EQ(val.get(), nullptr);
}

// Test getValue after setting a value
TEST_F(XmpdatumTest_1283, GetValueAfterSetValue_1283) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    datum.setValue("Test Value");
    auto val = datum.getValue();
    EXPECT_NE(val.get(), nullptr);
    EXPECT_EQ(val->toString(), "Test Value");
}

// Test setValue with Value pointer
TEST_F(XmpdatumTest_1283, SetValueWithValuePointer_1283) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    XmpTextValue val("Pointer Value");
    datum.setValue(&val);

    EXPECT_EQ(datum.toString(), "Pointer Value");
}

// Test setValue with nullptr Value pointer
TEST_F(XmpdatumTest_1283, SetValueWithNullptrValuePointer_1283) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    datum.setValue("Something");
    datum.setValue(static_cast<const Value*>(nullptr));

    // After setting null, getValue should return null
    auto val = datum.getValue();
    EXPECT_EQ(val.get(), nullptr);
}

// Test write to ostream
TEST_F(XmpdatumTest_1283, WriteToOstream_1283) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    datum.setValue("Write Test");
    std::ostringstream os;
    datum.write(os, nullptr);

    EXPECT_FALSE(os.str().empty());
    EXPECT_NE(os.str().find("Write Test"), std::string::npos);
}

// Test tag() returns a valid tag number
TEST_F(XmpdatumTest_1283, TagReturnsValue_1283) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    uint16_t tag = datum.tag();
    // Just verify it doesn't crash and returns something
    EXPECT_NO_THROW(datum.tag());
    (void)tag;
}

// Test familyName returns "Xmp"
TEST_F(XmpdatumTest_1283, FamilyNameIsXmp_1283) {
    XmpKey key("Xmp.dc.subject");
    Xmpdatum datum(key, nullptr);

    EXPECT_STREQ(datum.familyName(), "Xmp");
}

// Test with different XMP namespace (exif)
TEST_F(XmpdatumTest_1283, DifferentNamespace_1283) {
    XmpKey key("Xmp.exif.DateTimeOriginal");
    Xmpdatum datum(key, nullptr);

    EXPECT_EQ(datum.key(), "Xmp.exif.DateTimeOriginal");
    EXPECT_EQ(datum.groupName(), "exif");
    EXPECT_EQ(datum.tagName(), "DateTimeOriginal");
}

// Test toString with index parameter
TEST_F(XmpdatumTest_1283, ToStringWithIndex_1283) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    datum.setValue("Indexed Value");
    std::string result = datum.toString(0);
    EXPECT_EQ(result, "Indexed Value");
}

// Test toInt64 for numeric value
TEST_F(XmpdatumTest_1283, ToInt64ForNumericValue_1283) {
    XmpKey key("Xmp.exif.ImageWidth");
    Xmpdatum datum(key, nullptr);

    datum.setValue("42");
    int64_t val = datum.toInt64(0);
    EXPECT_EQ(val, 42);
}

// Test toFloat for float value
TEST_F(XmpdatumTest_1283, ToFloatForFloatValue_1283) {
    XmpKey key("Xmp.exif.FNumber");
    Xmpdatum datum(key, nullptr);

    datum.setValue("2.8");
    float val = datum.toFloat(0);
    EXPECT_FLOAT_EQ(val, 2.8f);
}

// Test copy always returns 0 for XMP
TEST_F(XmpdatumTest_1283, CopyReturnsZero_1283) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    datum.setValue("Test");
    byte buf[256] = {};
    size_t result = datum.copy(buf, bigEndian);
    EXPECT_EQ(result, static_cast<size_t>(0));
}

// Test construction using prefix and property name for XmpKey
TEST_F(XmpdatumTest_1283, ConstructWithPrefixAndProperty_1283) {
    XmpKey key("dc", "rights");
    Xmpdatum datum(key, nullptr);

    EXPECT_EQ(datum.key(), "Xmp.dc.rights");
    EXPECT_EQ(datum.tagName(), "rights");
    EXPECT_EQ(datum.groupName(), "dc");
}

// Test typeSize when no value set
TEST_F(XmpdatumTest_1283, TypeSizeWhenNoValue_1283) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    size_t ts = datum.typeSize();
    // With no value, expect 0
    EXPECT_EQ(ts, static_cast<size_t>(0));
}

// Test count when no value set
TEST_F(XmpdatumTest_1283, CountWhenNoValue_1283) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    EXPECT_EQ(datum.count(), static_cast<size_t>(0));
}

// Test size when no value set
TEST_F(XmpdatumTest_1283, SizeWhenNoValue_1283) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    EXPECT_EQ(datum.size(), static_cast<size_t>(0));
}

// Test assignment with template operator= for string
TEST_F(XmpdatumTest_1283, TemplateAssignmentString_1283) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    datum = std::string("Template Assigned");
    EXPECT_EQ(datum.toString(), "Template Assigned");
}

// Test that value() throws when no value is set
TEST_F(XmpdatumTest_1283, ValueThrowsWhenNoValue_1283) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    EXPECT_THROW(datum.value(), Error);
}

// Test setting value with XmpTextValue
TEST_F(XmpdatumTest_1283, SetXmpTextValue_1283) {
    XmpKey key("Xmp.dc.description");
    XmpTextValue textVal("A description");
    Xmpdatum datum(key, &textVal);

    EXPECT_EQ(datum.toString(), "A description");
    EXPECT_NE(datum.getValue().get(), nullptr);
}

// Test overwriting value
TEST_F(XmpdatumTest_1283, OverwriteValue_1283) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    datum.setValue("First");
    EXPECT_EQ(datum.toString(), "First");

    datum.setValue("Second");
    EXPECT_EQ(datum.toString(), "Second");
}
