#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <sstream>

using namespace Exiv2;

// Test fixture for Xmpdatum tests
class XmpdatumTest_1285 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure XMP parser is initialized
        XmpParser::initialize();
    }

    void TearDown() override {
        XmpParser::terminate();
    }
};

// Test that constructing Xmpdatum with a valid XmpKey sets the key correctly
TEST_F(XmpdatumTest_1285, ConstructWithValidKey_1285) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ("Xmp.dc.title", datum.key());
}

// Test that tag() returns a valid tag number for a known key
TEST_F(XmpdatumTest_1285, TagReturnsNonZeroForValidKey_1285) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    uint16_t tag = datum.tag();
    // Tag should be non-zero for a valid key
    EXPECT_NE(0u, tag);
}

// Test familyName returns "Xmp"
TEST_F(XmpdatumTest_1285, FamilyNameReturnsXmp_1285) {
    XmpKey key("Xmp.dc.subject");
    Xmpdatum datum(key, nullptr);
    EXPECT_STREQ("Xmp", datum.familyName());
}

// Test groupName returns the correct group
TEST_F(XmpdatumTest_1285, GroupNameReturnsCorrectGroup_1285) {
    XmpKey key("Xmp.dc.subject");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ("dc", datum.groupName());
}

// Test tagName returns the correct property name
TEST_F(XmpdatumTest_1285, TagNameReturnsCorrectProperty_1285) {
    XmpKey key("Xmp.dc.subject");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ("subject", datum.tagName());
}

// Test copy constructor creates an independent copy
TEST_F(XmpdatumTest_1285, CopyConstructorCreatesIndependentCopy_1285) {
    XmpKey key("Xmp.dc.description");
    Xmpdatum datum1(key, nullptr);
    datum1.setValue("Test description");

    Xmpdatum datum2(datum1);
    EXPECT_EQ(datum1.key(), datum2.key());
    EXPECT_EQ(datum1.toString(), datum2.toString());
}

// Test assignment operator
TEST_F(XmpdatumTest_1285, AssignmentOperator_1285) {
    XmpKey key1("Xmp.dc.title");
    Xmpdatum datum1(key1, nullptr);
    datum1.setValue("Title1");

    XmpKey key2("Xmp.dc.description");
    Xmpdatum datum2(key2, nullptr);
    datum2.setValue("Description1");

    datum2 = datum1;
    EXPECT_EQ(datum1.key(), datum2.key());
    EXPECT_EQ(datum1.toString(), datum2.toString());
}

// Test setValue with string
TEST_F(XmpdatumTest_1285, SetValueWithString_1285) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    int result = datum.setValue("Hello World");
    EXPECT_EQ(0, result);
    EXPECT_EQ("Hello World", datum.toString());
}

// Test setValue with Value pointer (nullptr)
TEST_F(XmpdatumTest_1285, SetValueWithNullptr_1285) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("Some value");
    datum.setValue(static_cast<const Value*>(nullptr));
    // After setting nullptr, getValue should return null or equivalent
    auto val = datum.getValue();
    EXPECT_EQ(nullptr, val);
}

// Test setValue with a Value object
TEST_F(XmpdatumTest_1285, SetValueWithValueObject_1285) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    XmpTextValue value("Test Value");
    datum.setValue(&value);

    EXPECT_EQ("Test Value", datum.toString());
}

// Test typeId when no value is set
TEST_F(XmpdatumTest_1285, TypeIdWhenNoValue_1285) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    // When no value is set, typeId should return invalidTypeId or xmpText
    TypeId tid = datum.typeId();
    // Just ensure it doesn't crash and returns some valid type
    (void)tid;
}

// Test typeId with a value set
TEST_F(XmpdatumTest_1285, TypeIdWithValueSet_1285) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("test");
    Xmpdatum datum(key, &val);
    EXPECT_EQ(xmpText, datum.typeId());
}

// Test typeName
TEST_F(XmpdatumTest_1285, TypeNameWithXmpTextValue_1285) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("test");
    Xmpdatum datum(key, &val);
    const char* tn = datum.typeName();
    EXPECT_NE(nullptr, tn);
    EXPECT_STREQ("XmpText", tn);
}

// Test count when no value is set
TEST_F(XmpdatumTest_1285, CountWhenNoValueSet_1285) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(0u, datum.count());
}

// Test count when a value is set
TEST_F(XmpdatumTest_1285, CountWithValueSet_1285) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("Hello");
    EXPECT_EQ(1u, datum.count());
}

// Test size when no value is set
TEST_F(XmpdatumTest_1285, SizeWhenNoValueSet_1285) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(0u, datum.size());
}

// Test size when a value is set
TEST_F(XmpdatumTest_1285, SizeWithValueSet_1285) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("Hello");
    EXPECT_GT(datum.size(), 0u);
}

// Test toString with index
TEST_F(XmpdatumTest_1285, ToStringWithIndex_1285) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("Test");
    EXPECT_EQ("Test", datum.toString(0));
}

// Test toInt64
TEST_F(XmpdatumTest_1285, ToInt64WithNumericValue_1285) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("42");
    EXPECT_EQ(42, datum.toInt64(0));
}

// Test toFloat
TEST_F(XmpdatumTest_1285, ToFloatWithNumericValue_1285) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("3.14");
    EXPECT_FLOAT_EQ(3.14f, datum.toFloat(0));
}

// Test getValue returns a valid unique pointer when value is set
TEST_F(XmpdatumTest_1285, GetValueReturnsValidPtr_1285) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("Test");
    auto val = datum.getValue();
    EXPECT_NE(nullptr, val);
    EXPECT_EQ("Test", val->toString());
}

// Test write to ostream
TEST_F(XmpdatumTest_1285, WriteToOstream_1285) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("Output Test");
    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test copy method returns 0 (XMP doesn't support binary copy in typical use)
TEST_F(XmpdatumTest_1285, CopyReturnsZero_1285) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("Test");
    byte buf[256] = {};
    size_t result = datum.copy(buf, littleEndian);
    EXPECT_EQ(0u, result);
}

// Test template assignment operator with string
TEST_F(XmpdatumTest_1285, TemplateAssignmentWithString_1285) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum = std::string("Template Test");
    EXPECT_EQ("Template Test", datum.toString());
}

// Test tagLabel returns non-empty string for known property
TEST_F(XmpdatumTest_1285, TagLabelForKnownProperty_1285) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    std::string label = datum.tagLabel();
    // Known property should have a label
    EXPECT_FALSE(label.empty());
}

// Test tagDesc for known property
TEST_F(XmpdatumTest_1285, TagDescForKnownProperty_1285) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    std::string desc = datum.tagDesc();
    // Just ensure it doesn't crash; desc may or may not be empty
    (void)desc;
}

// Test with different XMP namespaces
TEST_F(XmpdatumTest_1285, DifferentNamespaceDcSubject_1285) {
    XmpKey key("Xmp.dc.subject");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ("Xmp.dc.subject", datum.key());
    EXPECT_EQ("dc", datum.groupName());
    EXPECT_EQ("subject", datum.tagName());
}

// Test with tiff namespace
TEST_F(XmpdatumTest_1285, TiffNamespace_1285) {
    XmpKey key("Xmp.tiff.ImageWidth");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ("Xmp.tiff.ImageWidth", datum.key());
    EXPECT_EQ("tiff", datum.groupName());
    EXPECT_EQ("ImageWidth", datum.tagName());
}

// Test with exif namespace
TEST_F(XmpdatumTest_1285, ExifNamespace_1285) {
    XmpKey key("Xmp.exif.DateTimeOriginal");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ("Xmp.exif.DateTimeOriginal", datum.key());
    EXPECT_EQ("exif", datum.groupName());
    EXPECT_EQ("DateTimeOriginal", datum.tagName());
}

// Test value() throws when no value is set
TEST_F(XmpdatumTest_1285, ValueThrowsWhenNoValueSet_1285) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_THROW(datum.value(), Error);
}

// Test typeSize
TEST_F(XmpdatumTest_1285, TypeSizeWithValue_1285) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("test");
    Xmpdatum datum(key, &val);
    // typeSize for XmpText should be non-zero or defined
    size_t ts = datum.typeSize();
    (void)ts; // Just ensure it doesn't crash
}

// Test constructing with prefix and property
TEST_F(XmpdatumTest_1285, ConstructKeyWithPrefixAndProperty_1285) {
    XmpKey key("dc", "creator");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ("Xmp.dc.creator", datum.key());
    EXPECT_EQ("dc", datum.groupName());
    EXPECT_EQ("creator", datum.tagName());
}

// Test setValue replaces existing value
TEST_F(XmpdatumTest_1285, SetValueReplacesExisting_1285) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("First");
    EXPECT_EQ("First", datum.toString());
    datum.setValue("Second");
    EXPECT_EQ("Second", datum.toString());
}

// Test self-assignment
TEST_F(XmpdatumTest_1285, SelfAssignment_1285) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("Self");
    datum = datum;
    EXPECT_EQ("Xmp.dc.title", datum.key());
    EXPECT_EQ("Self", datum.toString());
}
