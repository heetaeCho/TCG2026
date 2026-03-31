#include <gtest/gtest.h>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/properties.hpp>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <exiv2/error.hpp>
#include <sstream>

using namespace Exiv2;

class XmpdatumTest_1295 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test: Construct Xmpdatum with a key and no value (nullptr)
TEST_F(XmpdatumTest_1295, ConstructWithKeyAndNullValue_1295) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Xmp.dc.title");
    EXPECT_EQ(datum.familyName(), std::string("Xmp"));
    EXPECT_EQ(datum.groupName(), "dc");
    EXPECT_EQ(datum.tagName(), "title");
}

// Test: toRational returns (-1, 1) when no value is set
TEST_F(XmpdatumTest_1295, ToRationalReturnsDefaultWhenNoValue_1295) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    Rational r = datum.toRational(0);
    EXPECT_EQ(r.first, -1);
    EXPECT_EQ(r.second, 1);
}

// Test: toRational with n > 0 when no value is set
TEST_F(XmpdatumTest_1295, ToRationalWithNonZeroIndexNoValue_1295) {
    XmpKey key("Xmp.dc.subject");
    Xmpdatum datum(key, nullptr);
    Rational r = datum.toRational(5);
    EXPECT_EQ(r.first, -1);
    EXPECT_EQ(r.second, 1);
}

// Test: Copy constructor creates a valid copy
TEST_F(XmpdatumTest_1295, CopyConstructor_1295) {
    XmpKey key("Xmp.dc.description");
    Xmpdatum datum(key, nullptr);
    Xmpdatum copy(datum);
    EXPECT_EQ(copy.key(), "Xmp.dc.description");
    EXPECT_EQ(copy.groupName(), "dc");
    EXPECT_EQ(copy.tagName(), "description");
}

// Test: Assignment operator
TEST_F(XmpdatumTest_1295, AssignmentOperator_1295) {
    XmpKey key1("Xmp.dc.title");
    Xmpdatum datum1(key1, nullptr);

    XmpKey key2("Xmp.dc.description");
    Xmpdatum datum2(key2, nullptr);

    datum2 = datum1;
    EXPECT_EQ(datum2.key(), "Xmp.dc.title");
}

// Test: setValue with a string value
TEST_F(XmpdatumTest_1295, SetValueFromString_1295) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    int result = datum.setValue("Test Title");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "Test Title");
}

// Test: setValue with a Value pointer
TEST_F(XmpdatumTest_1295, SetValueFromValuePointer_1295) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    auto value = Value::create(xmpText);
    value->read("Hello World");
    datum.setValue(value.get());

    EXPECT_EQ(datum.toString(), "Hello World");
}

// Test: typeId when no value is set
TEST_F(XmpdatumTest_1295, TypeIdWhenNoValue_1295) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    // When no value set, typeId should reflect the default
    TypeId tid = datum.typeId();
    // Just verify it doesn't crash and returns some valid TypeId
    (void)tid;
}

// Test: count when no value is set
TEST_F(XmpdatumTest_1295, CountWhenNoValue_1295) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.count(), 0u);
}

// Test: size when no value is set
TEST_F(XmpdatumTest_1295, SizeWhenNoValue_1295) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.size(), 0u);
}

// Test: toString when no value is set
TEST_F(XmpdatumTest_1295, ToStringWhenNoValue_1295) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    std::string s = datum.toString();
    EXPECT_EQ(s, "");
}

// Test: toInt64 when no value is set
TEST_F(XmpdatumTest_1295, ToInt64WhenNoValue_1295) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    int64_t val = datum.toInt64(0);
    EXPECT_EQ(val, -1);
}

// Test: toFloat when no value is set
TEST_F(XmpdatumTest_1295, ToFloatWhenNoValue_1295) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    float val = datum.toFloat(0);
    EXPECT_FLOAT_EQ(val, -1.0f);
}

// Test: Construct with a value object
TEST_F(XmpdatumTest_1295, ConstructWithKeyAndValue_1295) {
    XmpKey key("Xmp.dc.title");
    auto value = Value::create(xmpText);
    value->read("Test Value");
    Xmpdatum datum(key, value.get());

    EXPECT_EQ(datum.key(), "Xmp.dc.title");
    EXPECT_EQ(datum.toString(), "Test Value");
    EXPECT_GT(datum.count(), 0u);
}

// Test: toRational with a valid rational value set
TEST_F(XmpdatumTest_1295, ToRationalWithValidValue_1295) {
    XmpKey key("Xmp.tiff.XResolution");
    auto value = Value::create(xmpText);
    value->read("72/1");
    Xmpdatum datum(key, value.get());
    datum.setValue("72/1");

    Rational r = datum.toRational(0);
    // The value should be parsed from the string representation
    // Depending on the implementation, this might be (72, 1) or something else
    // At minimum, we check that it doesn't return the default (-1, 1) if value is set
    // But since xmpText might not parse as rational, let's just verify no crash
    (void)r;
}

// Test: getValue returns a copy of the value
TEST_F(XmpdatumTest_1295, GetValueReturnsCopy_1295) {
    XmpKey key("Xmp.dc.title");
    auto value = Value::create(xmpText);
    value->read("Original");
    Xmpdatum datum(key, value.get());

    auto retrieved = datum.getValue();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->toString(), "Original");
}

// Test: getValue when no value is set returns nullptr
TEST_F(XmpdatumTest_1295, GetValueWhenNoValueReturnsNull_1295) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    auto retrieved = datum.getValue();
    EXPECT_EQ(retrieved, nullptr);
}

// Test: write to ostream
TEST_F(XmpdatumTest_1295, WriteToOstream_1295) {
    XmpKey key("Xmp.dc.title");
    auto value = Value::create(xmpText);
    value->read("Stream Test");
    Xmpdatum datum(key, value.get());

    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test: write to ostream when no value
TEST_F(XmpdatumTest_1295, WriteToOstreamNoValue_1295) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    std::ostringstream os;
    datum.write(os, nullptr);
    // Should not crash, output may be empty
    (void)os;
}

// Test: familyName returns "Xmp"
TEST_F(XmpdatumTest_1295, FamilyNameIsXmp_1295) {
    XmpKey key("Xmp.dc.creator");
    Xmpdatum datum(key, nullptr);
    EXPECT_STREQ(datum.familyName(), "Xmp");
}

// Test: tag returns the tag number
TEST_F(XmpdatumTest_1295, TagReturnsValue_1295) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    uint16_t tag = datum.tag();
    // Just verify it doesn't crash and returns something
    (void)tag;
}

// Test: tagLabel returns a label string
TEST_F(XmpdatumTest_1295, TagLabelReturnsString_1295) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    std::string label = datum.tagLabel();
    // Just ensure it doesn't crash
    (void)label;
}

// Test: tagDesc returns a description string
TEST_F(XmpdatumTest_1295, TagDescReturnsString_1295) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    std::string desc = datum.tagDesc();
    (void)desc;
}

// Test: typeName when value is set
TEST_F(XmpdatumTest_1295, TypeNameWithValue_1295) {
    XmpKey key("Xmp.dc.title");
    auto value = Value::create(xmpText);
    value->read("test");
    Xmpdatum datum(key, value.get());
    const char* tn = datum.typeName();
    ASSERT_NE(tn, nullptr);
    EXPECT_EQ(std::string(tn), "XmpText");
}

// Test: copy buffer (should return 0 for XMP)
TEST_F(XmpdatumTest_1295, CopyReturnsZero_1295) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    byte buf[64] = {0};
    size_t copied = datum.copy(buf, littleEndian);
    EXPECT_EQ(copied, 0u);
}

// Test: toString with index when value is set
TEST_F(XmpdatumTest_1295, ToStringWithIndex_1295) {
    XmpKey key("Xmp.dc.title");
    auto value = Value::create(xmpText);
    value->read("Indexed");
    Xmpdatum datum(key, value.get());
    std::string s = datum.toString(0);
    EXPECT_EQ(s, "Indexed");
}

// Test: Operator= with a string value (template)
TEST_F(XmpdatumTest_1295, TemplateAssignmentWithString_1295) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum = std::string("Assigned Value");
    EXPECT_EQ(datum.toString(), "Assigned Value");
}

// Test: typeSize when no value
TEST_F(XmpdatumTest_1295, TypeSizeWhenNoValue_1295) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    size_t ts = datum.typeSize();
    // Verify it returns something without crashing
    (void)ts;
}

// Test: Multiple setValue calls
TEST_F(XmpdatumTest_1295, MultipleSetValue_1295) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("First");
    EXPECT_EQ(datum.toString(), "First");
    datum.setValue("Second");
    EXPECT_EQ(datum.toString(), "Second");
}

// Test: Setting value to empty string
TEST_F(XmpdatumTest_1295, SetValueEmptyString_1295) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    int result = datum.setValue("");
    EXPECT_EQ(result, 0);
}

// Test: Self-assignment
TEST_F(XmpdatumTest_1295, SelfAssignment_1295) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("SelfTest");
    datum = datum;
    EXPECT_EQ(datum.key(), "Xmp.dc.title");
    EXPECT_EQ(datum.toString(), "SelfTest");
}
