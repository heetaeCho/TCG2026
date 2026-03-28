#include <gtest/gtest.h>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/properties.hpp>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <exiv2/error.hpp>
#include <sstream>
#include <memory>

namespace {

class XmpdatumTest_1289 : public ::testing::Test {
protected:
    void SetUp() override {
        // XMP namespace registration might be needed
        Exiv2::XmpParser::initialize();
    }

    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }
};

// Test: Default construction with key and null value
TEST_F(XmpdatumTest_1289, ConstructWithKeyAndNullValue_1289) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);

    EXPECT_EQ(datum.key(), "Xmp.dc.title");
    EXPECT_EQ(datum.count(), 0u);
    EXPECT_EQ(datum.size(), 0u);
}

// Test: count() returns 0 when no value is set
TEST_F(XmpdatumTest_1289, CountReturnsZeroWhenNoValue_1289) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    Exiv2::Xmpdatum datum(key, nullptr);

    EXPECT_EQ(datum.count(), 0u);
}

// Test: count() returns correct count after setValue with string
TEST_F(XmpdatumTest_1289, CountAfterSetValueString_1289) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);

    datum.setValue("Test Title");
    EXPECT_GT(datum.count(), 0u);
}

// Test: key() returns the correct key string
TEST_F(XmpdatumTest_1289, KeyReturnsCorrectString_1289) {
    Exiv2::XmpKey key("Xmp.dc.creator");
    Exiv2::Xmpdatum datum(key, nullptr);

    EXPECT_EQ(datum.key(), "Xmp.dc.creator");
}

// Test: familyName() returns "Xmp"
TEST_F(XmpdatumTest_1289, FamilyNameReturnsXmp_1289) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);

    EXPECT_STREQ(datum.familyName(), "Xmp");
}

// Test: groupName() returns the correct group
TEST_F(XmpdatumTest_1289, GroupNameReturnsCorrectGroup_1289) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);

    EXPECT_EQ(datum.groupName(), "dc");
}

// Test: tagName() returns the correct tag
TEST_F(XmpdatumTest_1289, TagNameReturnsCorrectTag_1289) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);

    EXPECT_EQ(datum.tagName(), "title");
}

// Test: Copy constructor creates independent copy
TEST_F(XmpdatumTest_1289, CopyConstructorCreatesIndependentCopy_1289) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum1(key, nullptr);
    datum1.setValue("Original");

    Exiv2::Xmpdatum datum2(datum1);

    EXPECT_EQ(datum2.key(), "Xmp.dc.title");
    EXPECT_EQ(datum2.toString(), datum1.toString());
}

// Test: Assignment operator works correctly
TEST_F(XmpdatumTest_1289, AssignmentOperatorWorks_1289) {
    Exiv2::XmpKey key1("Xmp.dc.title");
    Exiv2::Xmpdatum datum1(key1, nullptr);
    datum1.setValue("First");

    Exiv2::XmpKey key2("Xmp.dc.subject");
    Exiv2::Xmpdatum datum2(key2, nullptr);
    datum2.setValue("Second");

    datum2 = datum1;

    EXPECT_EQ(datum2.key(), "Xmp.dc.title");
    EXPECT_EQ(datum2.toString(), "First");
}

// Test: setValue with Value pointer
TEST_F(XmpdatumTest_1289, SetValueWithValuePointer_1289) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);

    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("Test Value");
    datum.setValue(value.get());

    EXPECT_EQ(datum.toString(), "Test Value");
    EXPECT_GT(datum.count(), 0u);
}

// Test: setValue with nullptr resets value
TEST_F(XmpdatumTest_1289, SetValueWithNullptrResetsValue_1289) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    datum.setValue("Some value");

    EXPECT_GT(datum.count(), 0u);

    datum.setValue(static_cast<const Exiv2::Value*>(nullptr));
    EXPECT_EQ(datum.count(), 0u);
}

// Test: size() returns 0 when no value is set
TEST_F(XmpdatumTest_1289, SizeReturnsZeroWhenNoValue_1289) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);

    EXPECT_EQ(datum.size(), 0u);
}

// Test: size() returns non-zero after setting a value
TEST_F(XmpdatumTest_1289, SizeReturnsNonZeroAfterSetValue_1289) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    datum.setValue("Hello World");

    EXPECT_GT(datum.size(), 0u);
}

// Test: toString() returns empty string when no value
TEST_F(XmpdatumTest_1289, ToStringReturnsEmptyWhenNoValue_1289) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);

    EXPECT_EQ(datum.toString(), "");
}

// Test: toString() returns correct value after setting
TEST_F(XmpdatumTest_1289, ToStringReturnsCorrectValue_1289) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    datum.setValue("Test String");

    EXPECT_EQ(datum.toString(), "Test String");
}

// Test: typeId() returns correct type
TEST_F(XmpdatumTest_1289, TypeIdReturnsCorrectType_1289) {
    Exiv2::XmpKey key("Xmp.dc.title");
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("text");
    Exiv2::Xmpdatum datum(key, value.get());

    EXPECT_EQ(datum.typeId(), Exiv2::xmpText);
}

// Test: typeId() returns invalidTypeId when no value
TEST_F(XmpdatumTest_1289, TypeIdReturnsInvalidWhenNoValue_1289) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);

    EXPECT_EQ(datum.typeId(), Exiv2::invalidTypeId);
}

// Test: write() to stream
TEST_F(XmpdatumTest_1289, WriteToStream_1289) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    datum.setValue("Stream Test");

    std::ostringstream oss;
    datum.write(oss, nullptr);

    EXPECT_FALSE(oss.str().empty());
}

// Test: getValue() returns nullptr-like when no value
TEST_F(XmpdatumTest_1289, GetValueReturnsNullWhenNoValue_1289) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);

    auto val = datum.getValue();
    EXPECT_EQ(val.get(), nullptr);
}

// Test: getValue() returns non-null when value is set
TEST_F(XmpdatumTest_1289, GetValueReturnsNonNullWhenValueSet_1289) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    datum.setValue("A value");

    auto val = datum.getValue();
    EXPECT_NE(val.get(), nullptr);
}

// Test: value() throws when no value set
TEST_F(XmpdatumTest_1289, ValueThrowsWhenNoValueSet_1289) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);

    EXPECT_THROW(datum.value(), Exiv2::Error);
}

// Test: value() returns reference when value is set
TEST_F(XmpdatumTest_1289, ValueReturnsReferenceWhenSet_1289) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    datum.setValue("Valid value");

    EXPECT_NO_THROW({
        const Exiv2::Value& val = datum.value();
        EXPECT_GT(val.count(), 0u);
    });
}

// Test: Template assignment operator with string
TEST_F(XmpdatumTest_1289, TemplateAssignmentWithString_1289) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);

    datum = std::string("Template Assigned");
    EXPECT_EQ(datum.toString(), "Template Assigned");
}

// Test: copy() returns 0 when no value
TEST_F(XmpdatumTest_1289, CopyReturnsZeroWhenNoValue_1289) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);

    Exiv2::byte buf[256];
    size_t result = datum.copy(buf, Exiv2::bigEndian);
    EXPECT_EQ(result, 0u);
}

// Test: Construction with Value pointer
TEST_F(XmpdatumTest_1289, ConstructWithValuePointer_1289) {
    Exiv2::XmpKey key("Xmp.dc.description");
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("Description text");

    Exiv2::Xmpdatum datum(key, value.get());

    EXPECT_EQ(datum.key(), "Xmp.dc.description");
    EXPECT_EQ(datum.toString(), "Description text");
    EXPECT_GT(datum.count(), 0u);
}

// Test: tag() returns a value
TEST_F(XmpdatumTest_1289, TagReturnsValue_1289) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);

    // tag() should return some uint16_t value
    uint16_t tag = datum.tag();
    // Just verify it doesn't crash; the actual value depends on internal mapping
    (void)tag;
}

// Test: tagLabel() returns a string
TEST_F(XmpdatumTest_1289, TagLabelReturnsString_1289) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);

    std::string label = datum.tagLabel();
    // Just check it's callable and returns something
    EXPECT_FALSE(label.empty());
}

// Test: Multiple setValue calls override previous value
TEST_F(XmpdatumTest_1289, MultipleSetValueOverrides_1289) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);

    datum.setValue("First");
    EXPECT_EQ(datum.toString(), "First");

    datum.setValue("Second");
    EXPECT_EQ(datum.toString(), "Second");
}

// Test: toString(n) with index 0
TEST_F(XmpdatumTest_1289, ToStringWithIndex_1289) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    datum.setValue("Indexed value");

    std::string result = datum.toString(0);
    EXPECT_EQ(result, "Indexed value");
}

// Test: typeName returns valid string when value is set
TEST_F(XmpdatumTest_1289, TypeNameReturnsValidString_1289) {
    Exiv2::XmpKey key("Xmp.dc.title");
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("text");
    Exiv2::Xmpdatum datum(key, value.get());

    const char* tn = datum.typeName();
    EXPECT_NE(tn, nullptr);
}

// Test: typeName returns empty/null when no value
TEST_F(XmpdatumTest_1289, TypeNameWhenNoValue_1289) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);

    // When no value is set, typeName should handle gracefully
    const char* tn = datum.typeName();
    // Could be nullptr or empty - just don't crash
    (void)tn;
}

// Test: typeSize when no value
TEST_F(XmpdatumTest_1289, TypeSizeWhenNoValue_1289) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);

    size_t ts = datum.typeSize();
    EXPECT_EQ(ts, 0u);
}

} // anonymous namespace
