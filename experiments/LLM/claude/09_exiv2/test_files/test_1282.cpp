#include <gtest/gtest.h>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/properties.hpp>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>
#include <sstream>

using namespace Exiv2;

// Test fixture for Xmpdatum tests
class XmpdatumTest_1282 : public ::testing::Test {
protected:
    void SetUp() override {
        // XmpParser::initialize() may be needed for some environments
    }

    void TearDown() override {
    }
};

// Test construction with a valid XmpKey and null value
TEST_F(XmpdatumTest_1282, ConstructWithKeyAndNullValue_1282) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Xmp.dc.title");
    EXPECT_EQ(datum.familyName(), std::string("Xmp"));
    EXPECT_EQ(datum.groupName(), "dc");
    EXPECT_EQ(datum.tagName(), "title");
}

// Test tagName returns expected property name
TEST_F(XmpdatumTest_1282, TagNameReturnsPropertyName_1282) {
    XmpKey key("Xmp.dc.subject");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.tagName(), "subject");
}

// Test key returns full key string
TEST_F(XmpdatumTest_1282, KeyReturnsFullKeyString_1282) {
    XmpKey key("Xmp.dc.creator");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Xmp.dc.creator");
}

// Test familyName returns "Xmp"
TEST_F(XmpdatumTest_1282, FamilyNameReturnsXmp_1282) {
    XmpKey key("Xmp.dc.description");
    Xmpdatum datum(key, nullptr);
    EXPECT_STREQ(datum.familyName(), "Xmp");
}

// Test groupName returns the namespace prefix
TEST_F(XmpdatumTest_1282, GroupNameReturnsNamespacePrefix_1282) {
    XmpKey key("Xmp.dc.rights");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "dc");
}

// Test copy constructor preserves key information
TEST_F(XmpdatumTest_1282, CopyConstructorPreservesKey_1282) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum original(key, nullptr);
    Xmpdatum copy(original);
    EXPECT_EQ(copy.key(), original.key());
    EXPECT_EQ(copy.tagName(), original.tagName());
    EXPECT_EQ(copy.groupName(), original.groupName());
    EXPECT_STREQ(copy.familyName(), original.familyName());
}

// Test assignment operator
TEST_F(XmpdatumTest_1282, AssignmentOperatorCopiesData_1282) {
    XmpKey key1("Xmp.dc.title");
    XmpKey key2("Xmp.dc.creator");
    Xmpdatum datum1(key1, nullptr);
    Xmpdatum datum2(key2, nullptr);
    datum2 = datum1;
    EXPECT_EQ(datum2.key(), "Xmp.dc.title");
    EXPECT_EQ(datum2.tagName(), "title");
}

// Test setValue with string value
TEST_F(XmpdatumTest_1282, SetValueWithString_1282) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    int result = datum.setValue("Test Title");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "Test Title");
}

// Test setValue with Value pointer
TEST_F(XmpdatumTest_1282, SetValueWithValuePointer_1282) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    auto value = Value::create(xmpText);
    value->read("Hello World");
    datum.setValue(value.get());
    EXPECT_EQ(datum.toString(), "Hello World");
}

// Test count when no value is set
TEST_F(XmpdatumTest_1282, CountWithNoValue_1282) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.count(), 0u);
}

// Test size when no value is set
TEST_F(XmpdatumTest_1282, SizeWithNoValue_1282) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.size(), 0u);
}

// Test count after setting a value
TEST_F(XmpdatumTest_1282, CountAfterSetValue_1282) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("Some text");
    EXPECT_GT(datum.count(), 0u);
}

// Test size after setting a value
TEST_F(XmpdatumTest_1282, SizeAfterSetValue_1282) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("Some text");
    EXPECT_GT(datum.size(), 0u);
}

// Test typeId when no value is set
TEST_F(XmpdatumTest_1282, TypeIdWithNoValue_1282) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    // When no value is set, typeId should return invalidTypeId or a default
    TypeId tid = datum.typeId();
    EXPECT_EQ(tid, invalidTypeId);
}

// Test typeId after setting xmpText value
TEST_F(XmpdatumTest_1282, TypeIdAfterSetXmpText_1282) {
    XmpKey key("Xmp.dc.title");
    auto value = Value::create(xmpText);
    value->read("Test");
    Xmpdatum datum(key, value.get());
    EXPECT_EQ(datum.typeId(), xmpText);
}

// Test toString with index
TEST_F(XmpdatumTest_1282, ToStringWithIndex_1282) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("Test Value");
    EXPECT_EQ(datum.toString(0), "Test Value");
}

// Test getValue returns valid pointer after setValue
TEST_F(XmpdatumTest_1282, GetValueReturnsValidPointer_1282) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("Test");
    auto val = datum.getValue();
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->toString(), "Test");
}

// Test write to ostream
TEST_F(XmpdatumTest_1282, WriteToOstream_1282) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("Output Test");
    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test copy method returns 0 (XMP doesn't use binary copy)
TEST_F(XmpdatumTest_1282, CopyReturnsZero_1282) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("Test");
    byte buf[256] = {};
    size_t result = datum.copy(buf, littleEndian);
    EXPECT_EQ(result, 0u);
}

// Test construction with Value
TEST_F(XmpdatumTest_1282, ConstructWithValue_1282) {
    XmpKey key("Xmp.dc.description");
    auto value = Value::create(xmpText);
    value->read("A description");
    Xmpdatum datum(key, value.get());
    EXPECT_EQ(datum.toString(), "A description");
    EXPECT_EQ(datum.key(), "Xmp.dc.description");
}

// Test tag returns expected value
TEST_F(XmpdatumTest_1282, TagReturnsValue_1282) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    // tag() should return some uint16_t value
    uint16_t t = datum.tag();
    // Just verify it doesn't throw; the actual value depends on internal mapping
    (void)t;
}

// Test tagLabel returns non-empty string for known properties
TEST_F(XmpdatumTest_1282, TagLabelForKnownProperty_1282) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    std::string label = datum.tagLabel();
    // dc.title should have a label
    EXPECT_FALSE(label.empty());
}

// Test typeName when value is set
TEST_F(XmpdatumTest_1282, TypeNameWhenValueSet_1282) {
    XmpKey key("Xmp.dc.title");
    auto value = Value::create(xmpText);
    value->read("Test");
    Xmpdatum datum(key, value.get());
    const char* tn = datum.typeName();
    ASSERT_NE(tn, nullptr);
    EXPECT_EQ(std::string(tn), "XmpText");
}

// Test typeName when no value is set
TEST_F(XmpdatumTest_1282, TypeNameWhenNoValue_1282) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    // typeName with no value - should handle gracefully
    const char* tn = datum.typeName();
    // Could be nullptr or empty depending on implementation
    (void)tn;
}

// Test construction with prefix and property XmpKey constructor
TEST_F(XmpdatumTest_1282, ConstructWithPrefixPropertyKey_1282) {
    XmpKey key("dc", "subject");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.tagName(), "subject");
    EXPECT_EQ(datum.groupName(), "dc");
    EXPECT_EQ(datum.key(), "Xmp.dc.subject");
}

// Test overwriting value with setValue
TEST_F(XmpdatumTest_1282, OverwriteValue_1282) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("First");
    EXPECT_EQ(datum.toString(), "First");
    datum.setValue("Second");
    EXPECT_EQ(datum.toString(), "Second");
}

// Test copy constructor with value
TEST_F(XmpdatumTest_1282, CopyConstructorPreservesValue_1282) {
    XmpKey key("Xmp.dc.title");
    auto value = Value::create(xmpText);
    value->read("Copy me");
    Xmpdatum original(key, value.get());
    Xmpdatum copy(original);
    EXPECT_EQ(copy.toString(), "Copy me");
    EXPECT_EQ(copy.key(), "Xmp.dc.title");
}

// Test assignment from different Xmpdatum with value
TEST_F(XmpdatumTest_1282, AssignmentPreservesValue_1282) {
    XmpKey key1("Xmp.dc.title");
    XmpKey key2("Xmp.dc.creator");
    Xmpdatum datum1(key1, nullptr);
    datum1.setValue("Title");
    Xmpdatum datum2(key2, nullptr);
    datum2.setValue("Creator");
    datum2 = datum1;
    EXPECT_EQ(datum2.toString(), "Title");
    EXPECT_EQ(datum2.key(), "Xmp.dc.title");
}

// Test value() throws when no value is set
TEST_F(XmpdatumTest_1282, ValueThrowsWhenNoValueSet_1282) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_THROW(datum.value(), Exiv2::Error);
}

// Test toInt64 with a numeric value
TEST_F(XmpdatumTest_1282, ToInt64WithNumericValue_1282) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("42");
    int64_t val = datum.toInt64(0);
    EXPECT_EQ(val, 42);
}

// Test toFloat with a numeric value
TEST_F(XmpdatumTest_1282, ToFloatWithNumericValue_1282) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("3.14");
    float val = datum.toFloat(0);
    EXPECT_NEAR(val, 3.14f, 0.01f);
}

// Test with xmpBag type namespace
TEST_F(XmpdatumTest_1282, XmpDatumWithTiffNamespace_1282) {
    XmpKey key("Xmp.tiff.ImageWidth");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Xmp.tiff.ImageWidth");
    EXPECT_EQ(datum.groupName(), "tiff");
    EXPECT_EQ(datum.tagName(), "ImageWidth");
}

// Test with exif namespace
TEST_F(XmpdatumTest_1282, XmpDatumWithExifNamespace_1282) {
    XmpKey key("Xmp.exif.DateTimeOriginal");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Xmp.exif.DateTimeOriginal");
    EXPECT_EQ(datum.groupName(), "exif");
    EXPECT_EQ(datum.tagName(), "DateTimeOriginal");
}

// Test typeSize when no value is set
TEST_F(XmpdatumTest_1282, TypeSizeWithNoValue_1282) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    size_t ts = datum.typeSize();
    EXPECT_EQ(ts, 0u);
}

// Test setValue with nullptr clears the value
TEST_F(XmpdatumTest_1282, SetValueNullptrClearsValue_1282) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("Some value");
    EXPECT_EQ(datum.toString(), "Some value");
    datum.setValue(static_cast<const Value*>(nullptr));
    EXPECT_EQ(datum.count(), 0u);
}
