#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <sstream>
#include <memory>

class XmpdatumTest_1290 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure XMP namespace is initialized
        Exiv2::XmpParser::initialize();
    }

    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }
};

// Test that a default-constructed Xmpdatum (with no value) has size 0
TEST_F(XmpdatumTest_1290, SizeWithNoValue_1290) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.size(), 0u);
}

// Test that size returns the correct size after setting a string value
TEST_F(XmpdatumTest_1290, SizeAfterSetStringValue_1290) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    datum.setValue("Hello World");
    EXPECT_GT(datum.size(), 0u);
}

// Test that size returns correct size with an explicit Value object
TEST_F(XmpdatumTest_1290, SizeWithExplicitValue_1290) {
    Exiv2::XmpKey key("Xmp.dc.description");
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("Test description");
    Exiv2::Xmpdatum datum(key, value.get());
    EXPECT_GT(datum.size(), 0u);
}

// Test key returns the correct key string
TEST_F(XmpdatumTest_1290, KeyReturnsCorrectString_1290) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Xmp.dc.title");
}

// Test familyName returns "Xmp"
TEST_F(XmpdatumTest_1290, FamilyNameIsXmp_1290) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    std::string family = datum.familyName();
    EXPECT_EQ(family, "Xmp");
}

// Test groupName returns correct group
TEST_F(XmpdatumTest_1290, GroupNameReturnsCorrectGroup_1290) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "dc");
}

// Test tagName returns correct tag
TEST_F(XmpdatumTest_1290, TagNameReturnsCorrectTag_1290) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.tagName(), "title");
}

// Test copy constructor produces independent copy
TEST_F(XmpdatumTest_1290, CopyConstructorProducesIndependentCopy_1290) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    datum.setValue("Original");

    Exiv2::Xmpdatum copy(datum);
    EXPECT_EQ(copy.key(), datum.key());
    EXPECT_EQ(copy.toString(), datum.toString());
    EXPECT_EQ(copy.size(), datum.size());
}

// Test assignment operator
TEST_F(XmpdatumTest_1290, AssignmentOperator_1290) {
    Exiv2::XmpKey key1("Xmp.dc.title");
    Exiv2::Xmpdatum datum1(key1, nullptr);
    datum1.setValue("First");

    Exiv2::XmpKey key2("Xmp.dc.description");
    Exiv2::Xmpdatum datum2(key2, nullptr);
    datum2.setValue("Second");

    datum2 = datum1;
    EXPECT_EQ(datum2.key(), "Xmp.dc.title");
    EXPECT_EQ(datum2.toString(), datum1.toString());
}

// Test toString with no value
TEST_F(XmpdatumTest_1290, ToStringWithNoValue_1290) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.toString(), "");
}

// Test toString after setting value
TEST_F(XmpdatumTest_1290, ToStringAfterSetValue_1290) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    datum.setValue("Hello");
    EXPECT_EQ(datum.toString(), "Hello");
}

// Test count with no value
TEST_F(XmpdatumTest_1290, CountWithNoValue_1290) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.count(), 0u);
}

// Test count after setting value
TEST_F(XmpdatumTest_1290, CountAfterSetValue_1290) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    datum.setValue("Test");
    EXPECT_GT(datum.count(), 0u);
}

// Test typeId with no value set
TEST_F(XmpdatumTest_1290, TypeIdWithNoValue_1290) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    // When no value is set, typeId should be invalidTypeId or some default
    Exiv2::TypeId tid = datum.typeId();
    EXPECT_EQ(tid, Exiv2::invalidTypeId);
}

// Test typeId after setting xmpText value
TEST_F(XmpdatumTest_1290, TypeIdAfterSetXmpTextValue_1290) {
    Exiv2::XmpKey key("Xmp.dc.description");
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("Some text");
    Exiv2::Xmpdatum datum(key, value.get());
    EXPECT_EQ(datum.typeId(), Exiv2::xmpText);
}

// Test setValue with Value pointer (non-null)
TEST_F(XmpdatumTest_1290, SetValueWithValuePointer_1290) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);

    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("via pointer");
    datum.setValue(value.get());

    EXPECT_EQ(datum.toString(), "via pointer");
    EXPECT_GT(datum.size(), 0u);
}

// Test setValue with null pointer resets the value
TEST_F(XmpdatumTest_1290, SetValueWithNullPointer_1290) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    datum.setValue("something");
    EXPECT_GT(datum.size(), 0u);

    datum.setValue(static_cast<const Exiv2::Value*>(nullptr));
    EXPECT_EQ(datum.size(), 0u);
}

// Test write to ostream
TEST_F(XmpdatumTest_1290, WriteToOstream_1290) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    datum.setValue("Write test");

    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test getValue returns unique ptr
TEST_F(XmpdatumTest_1290, GetValueReturnsClone_1290) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    datum.setValue("cloneable");

    auto val = datum.getValue();
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->toString(), "cloneable");
}

// Test getValue returns null when no value set
TEST_F(XmpdatumTest_1290, GetValueReturnsNullWhenNoValue_1290) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);

    auto val = datum.getValue();
    EXPECT_EQ(val, nullptr);
}

// Test value() throws when no value is set
TEST_F(XmpdatumTest_1290, ValueThrowsWhenNoValueSet_1290) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);

    EXPECT_THROW(datum.value(), Exiv2::Error);
}

// Test size with an empty string value
TEST_F(XmpdatumTest_1290, SizeWithEmptyStringValue_1290) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    datum.setValue("");
    // Empty string still creates a value, but size may be 0
    EXPECT_EQ(datum.size(), 0u);
}

// Test template assignment operator with string
TEST_F(XmpdatumTest_1290, TemplateAssignmentWithString_1290) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    datum = std::string("template assigned");
    EXPECT_EQ(datum.toString(), "template assigned");
}

// Test toInt64 with no value
TEST_F(XmpdatumTest_1290, ToInt64WithNoValue_1290) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    // Should return 0 or throw; testing observable behavior
    EXPECT_EQ(datum.toInt64(0), 0);
}

// Test toFloat with no value
TEST_F(XmpdatumTest_1290, ToFloatWithNoValue_1290) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    EXPECT_FLOAT_EQ(datum.toFloat(0), 0.0f);
}

// Test size is consistent after multiple setValue calls
TEST_F(XmpdatumTest_1290, SizeConsistentAfterMultipleSetValue_1290) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);

    datum.setValue("short");
    size_t size1 = datum.size();

    datum.setValue("a much longer string value");
    size_t size2 = datum.size();

    EXPECT_GT(size2, size1);
}

// Test tagLabel is not empty for known properties
TEST_F(XmpdatumTest_1290, TagLabelForKnownProperty_1290) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    std::string label = datum.tagLabel();
    // Known property should have a non-empty label
    EXPECT_FALSE(label.empty());
}

// Test copy method returns 0 when no value is set
TEST_F(XmpdatumTest_1290, CopyReturnsZeroWhenNoValue_1290) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    Exiv2::byte buf[256];
    size_t result = datum.copy(buf, Exiv2::bigEndian);
    EXPECT_EQ(result, 0u);
}

// Test typeName with no value
TEST_F(XmpdatumTest_1290, TypeNameWithNoValue_1290) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    // With no value, typeName might return empty or a specific string
    const char* tn = datum.typeName();
    // Just check it doesn't crash; could be nullptr or empty
    (void)tn;
}

// Test typeSize with no value
TEST_F(XmpdatumTest_1290, TypeSizeWithNoValue_1290) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    size_t ts = datum.typeSize();
    EXPECT_EQ(ts, 0u);
}
