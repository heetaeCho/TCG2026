#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <sstream>
#include <memory>

using namespace Exiv2;

class XmpdatumTest_1278 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize XMP parser if needed
        XmpParser::initialize();
    }

    void TearDown() override {
        XmpParser::terminate();
    }
};

// Test construction with a valid XmpKey and null value
TEST_F(XmpdatumTest_1278, ConstructWithKeyAndNullValue_1278) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    EXPECT_EQ("Xmp.dc.title", datum.key());
    EXPECT_EQ("Xmp", std::string(datum.familyName()));
    EXPECT_EQ("dc", datum.groupName());
    EXPECT_EQ("title", datum.tagName());
}

// Test construction with a valid XmpKey and a value
TEST_F(XmpdatumTest_1278, ConstructWithKeyAndValue_1278) {
    XmpKey key("Xmp.dc.description");
    XmpTextValue val("Test description");
    Xmpdatum datum(key, &val);

    EXPECT_EQ("Xmp.dc.description", datum.key());
    EXPECT_EQ("Test description", datum.toString());
    EXPECT_EQ(1u, datum.count());
}

// Test copy constructor
TEST_F(XmpdatumTest_1278, CopyConstructor_1278) {
    XmpKey key("Xmp.dc.subject");
    XmpTextValue val("Hello");
    Xmpdatum original(key, &val);

    Xmpdatum copy(original);

    EXPECT_EQ(original.key(), copy.key());
    EXPECT_EQ(original.toString(), copy.toString());
    EXPECT_EQ(original.familyName(), copy.familyName());
    EXPECT_EQ(original.groupName(), copy.groupName());
    EXPECT_EQ(original.tagName(), copy.tagName());
}

// Test copy assignment operator
TEST_F(XmpdatumTest_1278, CopyAssignmentOperator_1278) {
    XmpKey key1("Xmp.dc.title");
    XmpTextValue val1("Title 1");
    Xmpdatum datum1(key1, &val1);

    XmpKey key2("Xmp.dc.description");
    XmpTextValue val2("Description 2");
    Xmpdatum datum2(key2, &val2);

    datum1 = datum2;

    EXPECT_EQ("Xmp.dc.description", datum1.key());
    EXPECT_EQ("Description 2", datum1.toString());
}

// Test self-assignment
TEST_F(XmpdatumTest_1278, SelfAssignment_1278) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("Self Test");
    Xmpdatum datum(key, &val);

    datum = datum;

    EXPECT_EQ("Xmp.dc.title", datum.key());
    EXPECT_EQ("Self Test", datum.toString());
}

// Test setValue with string
TEST_F(XmpdatumTest_1278, SetValueFromString_1278) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    int result = datum.setValue("New Title");
    EXPECT_EQ(0, result);
    EXPECT_EQ("New Title", datum.toString());
}

// Test setValue with Value pointer
TEST_F(XmpdatumTest_1278, SetValueFromValuePointer_1278) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    XmpTextValue val("Pointer Value");
    datum.setValue(&val);

    EXPECT_EQ("Pointer Value", datum.toString());
}

// Test setValue with nullptr resets value
TEST_F(XmpdatumTest_1278, SetValueWithNullptr_1278) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("Some value");
    Xmpdatum datum(key, &val);

    datum.setValue(static_cast<const Value*>(nullptr));
    EXPECT_EQ(0u, datum.count());
}

// Test key components
TEST_F(XmpdatumTest_1278, KeyComponents_1278) {
    XmpKey key("Xmp.dc.creator");
    Xmpdatum datum(key, nullptr);

    EXPECT_EQ("Xmp.dc.creator", datum.key());
    EXPECT_STREQ("Xmp", datum.familyName());
    EXPECT_EQ("dc", datum.groupName());
    EXPECT_EQ("creator", datum.tagName());
}

// Test tagLabel returns a non-empty string for known tags
TEST_F(XmpdatumTest_1278, TagLabelForKnownTag_1278) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    std::string label = datum.tagLabel();
    // Known tag should have a label
    EXPECT_FALSE(label.empty());
}

// Test typeId when no value is set
TEST_F(XmpdatumTest_1278, TypeIdWithNoValue_1278) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    TypeId typeId = datum.typeId();
    EXPECT_EQ(invalidTypeId, typeId);
}

// Test typeId with a value
TEST_F(XmpdatumTest_1278, TypeIdWithValue_1278) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("test");
    Xmpdatum datum(key, &val);

    TypeId typeId = datum.typeId();
    EXPECT_EQ(xmpText, typeId);
}

// Test count with no value
TEST_F(XmpdatumTest_1278, CountWithNoValue_1278) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    EXPECT_EQ(0u, datum.count());
}

// Test count with a value set
TEST_F(XmpdatumTest_1278, CountWithValue_1278) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("something");
    Xmpdatum datum(key, &val);

    EXPECT_GE(datum.count(), 1u);
}

// Test size with no value
TEST_F(XmpdatumTest_1278, SizeWithNoValue_1278) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    EXPECT_EQ(0u, datum.size());
}

// Test size with a value
TEST_F(XmpdatumTest_1278, SizeWithValue_1278) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("hello");
    Xmpdatum datum(key, &val);

    EXPECT_GT(datum.size(), 0u);
}

// Test toString with index
TEST_F(XmpdatumTest_1278, ToStringWithIndex_1278) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("indexed");
    Xmpdatum datum(key, &val);

    std::string result = datum.toString(0);
    EXPECT_EQ("indexed", result);
}

// Test getValue returns a valid unique_ptr when value is set
TEST_F(XmpdatumTest_1278, GetValueReturnsValidPtr_1278) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("getValue test");
    Xmpdatum datum(key, &val);

    auto ptr = datum.getValue();
    ASSERT_NE(nullptr, ptr.get());
    EXPECT_EQ("getValue test", ptr->toString());
}

// Test getValue returns nullptr when no value is set
TEST_F(XmpdatumTest_1278, GetValueReturnsNullWhenNoValue_1278) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    auto ptr = datum.getValue();
    EXPECT_EQ(nullptr, ptr.get());
}

// Test write to ostream
TEST_F(XmpdatumTest_1278, WriteToStream_1278) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("stream test");
    Xmpdatum datum(key, &val);

    std::ostringstream oss;
    datum.write(oss, nullptr);

    EXPECT_FALSE(oss.str().empty());
    EXPECT_NE(std::string::npos, oss.str().find("stream test"));
}

// Test template operator= with string
TEST_F(XmpdatumTest_1278, TemplateAssignmentWithString_1278) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    datum = std::string("template assigned");

    EXPECT_EQ("template assigned", datum.toString());
}

// Test copy returns 0 (XMP doesn't support binary copy in the usual sense)
TEST_F(XmpdatumTest_1278, CopyReturnsZero_1278) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("copy test");
    Xmpdatum datum(key, &val);

    byte buf[256];
    size_t result = datum.copy(buf, bigEndian);
    EXPECT_EQ(0u, result);
}

// Test tag() returns a valid tag number
TEST_F(XmpdatumTest_1278, TagReturnsValue_1278) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    uint16_t tag = datum.tag();
    // Just verify it doesn't crash and returns something
    (void)tag;
}

// Test typeName when no value
TEST_F(XmpdatumTest_1278, TypeNameWhenNoValue_1278) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    const char* tn = datum.typeName();
    // When no value is set, typeName might be empty or null-like
    // Just check it doesn't crash
    (void)tn;
}

// Test typeName when value is set
TEST_F(XmpdatumTest_1278, TypeNameWithValue_1278) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("typename test");
    Xmpdatum datum(key, &val);

    const char* tn = datum.typeName();
    ASSERT_NE(nullptr, tn);
    EXPECT_EQ(std::string("XmpText"), std::string(tn));
}

// Test typeSize
TEST_F(XmpdatumTest_1278, TypeSize_1278) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("size test");
    Xmpdatum datum(key, &val);

    size_t ts = datum.typeSize();
    // Just check it doesn't crash; for XmpText it might be 1
    (void)ts;
}

// Test copy assignment doesn't affect original
TEST_F(XmpdatumTest_1278, CopyAssignmentIndependence_1278) {
    XmpKey key1("Xmp.dc.title");
    XmpTextValue val1("Original");
    Xmpdatum datum1(key1, &val1);

    XmpKey key2("Xmp.dc.description");
    XmpTextValue val2("Copy");
    Xmpdatum datum2(key2, &val2);

    datum2 = datum1;

    // Modify datum1 after copy
    datum1.setValue("Modified");

    // datum2 should remain unchanged
    EXPECT_EQ("Original", datum2.toString());
    EXPECT_EQ("Modified", datum1.toString());
}

// Test copy constructor independence
TEST_F(XmpdatumTest_1278, CopyConstructorIndependence_1278) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("Original Copy");
    Xmpdatum datum1(key, &val);

    Xmpdatum datum2(datum1);

    datum1.setValue("Changed");

    EXPECT_EQ("Changed", datum1.toString());
    EXPECT_EQ("Original Copy", datum2.toString());
}

// Test toInt64 with numeric value
TEST_F(XmpdatumTest_1278, ToInt64WithNumericValue_1278) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("42");
    Xmpdatum datum(key, &val);

    int64_t result = datum.toInt64(0);
    EXPECT_EQ(42, result);
}

// Test toFloat with numeric value
TEST_F(XmpdatumTest_1278, ToFloatWithNumericValue_1278) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("3.14");
    Xmpdatum datum(key, &val);

    float result = datum.toFloat(0);
    EXPECT_NEAR(3.14f, result, 0.01f);
}

// Test toRational
TEST_F(XmpdatumTest_1278, ToRational_1278) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("5");
    Xmpdatum datum(key, &val);

    Rational r = datum.toRational(0);
    // For "5", rational should be 5/1
    EXPECT_EQ(5, r.first);
    EXPECT_EQ(1, r.second);
}

// Test tagDesc returns something (may be empty for some tags)
TEST_F(XmpdatumTest_1278, TagDesc_1278) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    std::string desc = datum.tagDesc();
    // Just verify it doesn't crash
    (void)desc;
}

// Test setValue overwrites previous value
TEST_F(XmpdatumTest_1278, SetValueOverwritesPrevious_1278) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val1("First");
    Xmpdatum datum(key, &val1);

    EXPECT_EQ("First", datum.toString());

    XmpTextValue val2("Second");
    datum.setValue(&val2);

    EXPECT_EQ("Second", datum.toString());
}

// Test multiple setValue calls with string
TEST_F(XmpdatumTest_1278, MultipleSetValueString_1278) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    datum.setValue("Value1");
    EXPECT_EQ("Value1", datum.toString());

    datum.setValue("Value2");
    EXPECT_EQ("Value2", datum.toString());

    datum.setValue("Value3");
    EXPECT_EQ("Value3", datum.toString());
}
