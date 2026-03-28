#include <gtest/gtest.h>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/properties.hpp>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>
#include <sstream>

using namespace Exiv2;

class XmpdatumTest_1281 : public ::testing::Test {
protected:
    void SetUp() override {
        // Register XMP namespaces if needed
        XmpParser::initialize();
    }
    void TearDown() override {
        XmpParser::terminate();
    }
};

// Test construction with a valid XmpKey and null value
TEST_F(XmpdatumTest_1281, ConstructWithKeyAndNullValue_1281) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Xmp.dc.title");
}

// Test groupName returns the expected group
TEST_F(XmpdatumTest_1281, GroupNameReturnsCorrectGroup_1281) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "dc");
}

// Test familyName returns "Xmp"
TEST_F(XmpdatumTest_1281, FamilyNameReturnsXmp_1281) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    std::string family = datum.familyName();
    EXPECT_EQ(family, "Xmp");
}

// Test tagName returns the property name
TEST_F(XmpdatumTest_1281, TagNameReturnsPropertyName_1281) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.tagName(), "title");
}

// Test key returns the full key string
TEST_F(XmpdatumTest_1281, KeyReturnsFullKeyString_1281) {
    XmpKey key("Xmp.dc.subject");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Xmp.dc.subject");
}

// Test copy construction
TEST_F(XmpdatumTest_1281, CopyConstruction_1281) {
    XmpKey key("Xmp.dc.creator");
    Xmpdatum datum1(key, nullptr);
    Xmpdatum datum2(datum1);
    EXPECT_EQ(datum2.key(), "Xmp.dc.creator");
    EXPECT_EQ(datum2.groupName(), "dc");
    EXPECT_EQ(datum2.tagName(), "creator");
}

// Test assignment operator
TEST_F(XmpdatumTest_1281, AssignmentOperator_1281) {
    XmpKey key1("Xmp.dc.title");
    XmpKey key2("Xmp.dc.description");
    Xmpdatum datum1(key1, nullptr);
    Xmpdatum datum2(key2, nullptr);
    datum2 = datum1;
    EXPECT_EQ(datum2.key(), "Xmp.dc.title");
    EXPECT_EQ(datum2.groupName(), "dc");
}

// Test setValue with a string value
TEST_F(XmpdatumTest_1281, SetValueWithString_1281) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    int result = datum.setValue("Test Title");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "Test Title");
}

// Test setValue with Value pointer
TEST_F(XmpdatumTest_1281, SetValueWithValuePointer_1281) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    auto val = Value::create(xmpText);
    val->read("Hello World");
    datum.setValue(val.get());
    EXPECT_EQ(datum.toString(), "Hello World");
}

// Test count with no value set (null value)
TEST_F(XmpdatumTest_1281, CountWithNullValue_1281) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.count(), 0u);
}

// Test size with no value
TEST_F(XmpdatumTest_1281, SizeWithNullValue_1281) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.size(), 0u);
}

// Test typeId with no value
TEST_F(XmpdatumTest_1281, TypeIdWithNullValue_1281) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    // When no value is set, typeId should return invalidTypeId or a default
    TypeId tid = datum.typeId();
    EXPECT_EQ(tid, invalidTypeId);
}

// Test setValue then count
TEST_F(XmpdatumTest_1281, SetValueThenCount_1281) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("Some text");
    EXPECT_GT(datum.count(), 0u);
}

// Test setValue then size
TEST_F(XmpdatumTest_1281, SetValueThenSize_1281) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("Some text");
    EXPECT_GT(datum.size(), 0u);
}

// Test write to ostream
TEST_F(XmpdatumTest_1281, WriteToOstream_1281) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("Test Output");
    std::ostringstream oss;
    datum.write(oss, nullptr);
    EXPECT_FALSE(oss.str().empty());
}

// Test getValue with null value returns empty unique_ptr
TEST_F(XmpdatumTest_1281, GetValueWithNullValue_1281) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    auto val = datum.getValue();
    // When no value is set, getValue should return a null unique_ptr
    EXPECT_EQ(val.get(), nullptr);
}

// Test getValue with a valid value
TEST_F(XmpdatumTest_1281, GetValueWithValidValue_1281) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("Hello");
    auto val = datum.getValue();
    EXPECT_NE(val.get(), nullptr);
    EXPECT_EQ(val->toString(), "Hello");
}

// Test value() throws when no value is set
TEST_F(XmpdatumTest_1281, ValueThrowsWhenNoValueSet_1281) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_THROW(datum.value(), Error);
}

// Test different XMP namespace group
TEST_F(XmpdatumTest_1281, DifferentNamespaceGroup_1281) {
    XmpKey key("Xmp.exif.DateTimeOriginal");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "exif");
    EXPECT_EQ(datum.tagName(), "DateTimeOriginal");
    EXPECT_EQ(datum.familyName(), std::string("Xmp"));
}

// Test with tiff namespace
TEST_F(XmpdatumTest_1281, TiffNamespaceGroup_1281) {
    XmpKey key("Xmp.tiff.ImageWidth");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "tiff");
    EXPECT_EQ(datum.tagName(), "ImageWidth");
}

// Test tag returns expected value
TEST_F(XmpdatumTest_1281, TagReturnsValue_1281) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    // tag() should return some value; we just verify it doesn't throw
    uint16_t tagVal = datum.tag();
    (void)tagVal; // suppress unused warning
    SUCCEED();
}

// Test tagLabel returns non-empty for known properties
TEST_F(XmpdatumTest_1281, TagLabelForKnownProperty_1281) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    std::string label = datum.tagLabel();
    // For known XMP properties, label should not be empty
    EXPECT_FALSE(label.empty());
}

// Test copy returns 0 when no value
TEST_F(XmpdatumTest_1281, CopyReturnsZeroWhenNoValue_1281) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    byte buf[256] = {};
    size_t copied = datum.copy(buf, littleEndian);
    EXPECT_EQ(copied, 0u);
}

// Test constructing Xmpdatum with a Value
TEST_F(XmpdatumTest_1281, ConstructWithKeyAndValue_1281) {
    XmpKey key("Xmp.dc.title");
    auto val = Value::create(xmpText);
    val->read("Initial Value");
    Xmpdatum datum(key, val.get());
    EXPECT_EQ(datum.toString(), "Initial Value");
    EXPECT_EQ(datum.key(), "Xmp.dc.title");
}

// Test toString with index on an XmpText value
TEST_F(XmpdatumTest_1281, ToStringWithIndex_1281) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("Hello");
    std::string s = datum.toString(0);
    EXPECT_EQ(s, "Hello");
}

// Test typeName when value is set
TEST_F(XmpdatumTest_1281, TypeNameWithValue_1281) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("text");
    const char* tn = datum.typeName();
    EXPECT_NE(tn, nullptr);
    EXPECT_EQ(std::string(tn), "XmpText");
}

// Test typeSize returns 0 for XmpText
TEST_F(XmpdatumTest_1281, TypeSizeForXmpText_1281) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("text");
    // XmpText doesn't have a fixed type size, typically returns 0
    size_t ts = datum.typeSize();
    EXPECT_EQ(ts, 0u);
}

// Test overwriting value
TEST_F(XmpdatumTest_1281, OverwriteValue_1281) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("First");
    EXPECT_EQ(datum.toString(), "First");
    datum.setValue("Second");
    EXPECT_EQ(datum.toString(), "Second");
}

// Test XmpKey with prefix and property constructor
TEST_F(XmpdatumTest_1281, XmpKeyPrefixPropertyConstructor_1281) {
    XmpKey key("dc", "creator");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Xmp.dc.creator");
    EXPECT_EQ(datum.groupName(), "dc");
    EXPECT_EQ(datum.tagName(), "creator");
}
