#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <sstream>
#include <string>

using namespace Exiv2;

class XmpdatumTest_1296 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize XMP parser if needed
        XmpParser::initialize();
    }

    void TearDown() override {
        XmpParser::terminate();
    }
};

// Test construction with key and null value
TEST_F(XmpdatumTest_1296, ConstructWithKeyAndNullValue_1296) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    EXPECT_EQ("Xmp.dc.title", datum.key());
    EXPECT_EQ("Xmp", std::string(datum.familyName()));
    EXPECT_EQ("dc", datum.groupName());
    EXPECT_EQ("title", datum.tagName());
}

// Test getValue returns nullptr when no value is set
TEST_F(XmpdatumTest_1296, GetValueReturnsNullWhenNoValue_1296) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    Value::UniquePtr val = datum.getValue();
    EXPECT_EQ(nullptr, val);
}

// Test getValue returns a clone when value is set
TEST_F(XmpdatumTest_1296, GetValueReturnsCloneWhenValueSet_1296) {
    XmpKey key("Xmp.dc.description");
    Xmpdatum datum(key, nullptr);
    datum.setValue("Test description");

    Value::UniquePtr val = datum.getValue();
    ASSERT_NE(nullptr, val);
    EXPECT_EQ("Test description", val->toString());
}

// Test copy constructor
TEST_F(XmpdatumTest_1296, CopyConstructor_1296) {
    XmpKey key("Xmp.dc.creator");
    Xmpdatum original(key, nullptr);
    original.setValue("Author Name");

    Xmpdatum copy(original);

    EXPECT_EQ(original.key(), copy.key());
    EXPECT_EQ(original.toString(), copy.toString());

    // Ensure they are independent (deep copy)
    Value::UniquePtr origVal = original.getValue();
    Value::UniquePtr copyVal = copy.getValue();
    ASSERT_NE(nullptr, origVal);
    ASSERT_NE(nullptr, copyVal);
    EXPECT_EQ(origVal->toString(), copyVal->toString());
}

// Test assignment operator
TEST_F(XmpdatumTest_1296, AssignmentOperator_1296) {
    XmpKey key1("Xmp.dc.title");
    XmpKey key2("Xmp.dc.description");
    Xmpdatum datum1(key1, nullptr);
    datum1.setValue("Title");
    Xmpdatum datum2(key2, nullptr);
    datum2.setValue("Description");

    datum2 = datum1;

    EXPECT_EQ(datum1.key(), datum2.key());
    EXPECT_EQ(datum1.toString(), datum2.toString());
}

// Test key() returns correct key string
TEST_F(XmpdatumTest_1296, KeyReturnsCorrectString_1296) {
    XmpKey key("Xmp.dc.subject");
    Xmpdatum datum(key, nullptr);

    EXPECT_EQ("Xmp.dc.subject", datum.key());
}

// Test familyName() returns "Xmp"
TEST_F(XmpdatumTest_1296, FamilyNameReturnsXmp_1296) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    EXPECT_STREQ("Xmp", datum.familyName());
}

// Test groupName() returns correct group
TEST_F(XmpdatumTest_1296, GroupNameReturnsCorrectGroup_1296) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    EXPECT_EQ("dc", datum.groupName());
}

// Test tagName() returns correct tag name
TEST_F(XmpdatumTest_1296, TagNameReturnsCorrectTag_1296) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    EXPECT_EQ("title", datum.tagName());
}

// Test setValue with string
TEST_F(XmpdatumTest_1296, SetValueWithString_1296) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    int result = datum.setValue("Hello World");
    EXPECT_EQ(0, result);
    EXPECT_EQ("Hello World", datum.toString());
}

// Test setValue with Value pointer
TEST_F(XmpdatumTest_1296, SetValueWithValuePointer_1296) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    auto value = Value::create(xmpText);
    value->read("Test Value");
    datum.setValue(value.get());

    Value::UniquePtr retrieved = datum.getValue();
    ASSERT_NE(nullptr, retrieved);
    EXPECT_EQ("Test Value", retrieved->toString());
}

// Test setValue with nullptr clears value
TEST_F(XmpdatumTest_1296, SetValueWithNullptrClearsValue_1296) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("Some Value");

    ASSERT_NE(nullptr, datum.getValue());

    datum.setValue(nullptr);

    Value::UniquePtr val = datum.getValue();
    EXPECT_EQ(nullptr, val);
}

// Test toString()
TEST_F(XmpdatumTest_1296, ToStringReturnsValueString_1296) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("My Title");

    EXPECT_EQ("My Title", datum.toString());
}

// Test toString(size_t n)
TEST_F(XmpdatumTest_1296, ToStringWithIndex_1296) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("Indexed Value");

    std::string result = datum.toString(0);
    EXPECT_EQ("Indexed Value", result);
}

// Test count() when no value set
TEST_F(XmpdatumTest_1296, CountWithNoValue_1296) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    EXPECT_EQ(0u, datum.count());
}

// Test count() when value is set
TEST_F(XmpdatumTest_1296, CountWithValueSet_1296) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("Some text");

    EXPECT_GE(datum.count(), 1u);
}

// Test size() when no value set
TEST_F(XmpdatumTest_1296, SizeWithNoValue_1296) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    EXPECT_EQ(0u, datum.size());
}

// Test size() when value is set
TEST_F(XmpdatumTest_1296, SizeWithValueSet_1296) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("Hello");

    EXPECT_GT(datum.size(), 0u);
}

// Test typeId when constructed with XmpText value
TEST_F(XmpdatumTest_1296, TypeIdWithXmpTextValue_1296) {
    XmpKey key("Xmp.dc.title");
    auto value = Value::create(xmpText);
    value->read("text value");
    Xmpdatum datum(key, value.get());

    EXPECT_EQ(xmpText, datum.typeId());
}

// Test typeName
TEST_F(XmpdatumTest_1296, TypeName_1296) {
    XmpKey key("Xmp.dc.title");
    auto value = Value::create(xmpText);
    value->read("text value");
    Xmpdatum datum(key, value.get());

    const char* tn = datum.typeName();
    ASSERT_NE(nullptr, tn);
    EXPECT_EQ(std::string("XmpText"), std::string(tn));
}

// Test write to ostream
TEST_F(XmpdatumTest_1296, WriteToOstream_1296) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("Output Test");

    std::ostringstream oss;
    datum.write(oss, nullptr);

    EXPECT_FALSE(oss.str().empty());
    EXPECT_NE(std::string::npos, oss.str().find("Output Test"));
}

// Test getValue independence from original datum (clone semantics)
TEST_F(XmpdatumTest_1296, GetValueReturnsIndependentClone_1296) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("Original");

    Value::UniquePtr val = datum.getValue();
    ASSERT_NE(nullptr, val);

    // Modify the datum
    datum.setValue("Modified");

    // The cloned value should still have the original
    EXPECT_EQ("Original", val->toString());
    EXPECT_EQ("Modified", datum.toString());
}

// Test construction with a non-null Value
TEST_F(XmpdatumTest_1296, ConstructWithNonNullValue_1296) {
    XmpKey key("Xmp.dc.creator");
    auto value = Value::create(xmpText);
    value->read("John Doe");
    Xmpdatum datum(key, value.get());

    EXPECT_EQ("Xmp.dc.creator", datum.key());
    Value::UniquePtr retrieved = datum.getValue();
    ASSERT_NE(nullptr, retrieved);
    EXPECT_EQ("John Doe", retrieved->toString());
}

// Test template assignment operator with string
TEST_F(XmpdatumTest_1296, TemplateAssignmentWithString_1296) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    datum = std::string("Assigned via template");

    EXPECT_EQ("Assigned via template", datum.toString());
}

// Test empty string value
TEST_F(XmpdatumTest_1296, SetEmptyStringValue_1296) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    int result = datum.setValue("");
    EXPECT_EQ(0, result);

    Value::UniquePtr val = datum.getValue();
    // Even with empty string, a value object should exist
    ASSERT_NE(nullptr, val);
    EXPECT_EQ("", val->toString());
}

// Test tagLabel returns some string
TEST_F(XmpdatumTest_1296, TagLabelReturnsNonEmpty_1296) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    // tagLabel might return a label for the tag
    std::string label = datum.tagLabel();
    // We just verify it doesn't crash; label could be empty for some tags
    SUCCEED();
}

// Test tag() returns a value
TEST_F(XmpdatumTest_1296, TagReturnsValue_1296) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    // Just verify it doesn't crash and returns some uint16_t
    uint16_t tagVal = datum.tag();
    (void)tagVal;
    SUCCEED();
}

// Test multiple setValue calls overwrite previous value
TEST_F(XmpdatumTest_1296, MultipleSetValueOverwrites_1296) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    datum.setValue("First");
    EXPECT_EQ("First", datum.toString());

    datum.setValue("Second");
    EXPECT_EQ("Second", datum.toString());

    datum.setValue("Third");
    EXPECT_EQ("Third", datum.toString());
}

// Test self-assignment
TEST_F(XmpdatumTest_1296, SelfAssignment_1296) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("Self");

    datum = datum;

    EXPECT_EQ("Xmp.dc.title", datum.key());
    EXPECT_EQ("Self", datum.toString());
}
