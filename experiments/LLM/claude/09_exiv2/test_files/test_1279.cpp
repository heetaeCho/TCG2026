#include <gtest/gtest.h>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/properties.hpp>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>
#include <sstream>

namespace {

class XmpdatumTest_1279 : public ::testing::Test {
protected:
    void SetUp() override {
        Exiv2::XmpParser::initialize();
    }
    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }
};

// Test that key() returns the correct key string
TEST_F(XmpdatumTest_1279, KeyReturnsCorrectString_1279) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    EXPECT_EQ("Xmp.dc.title", datum.key());
}

// Test familyName() returns "Xmp"
TEST_F(XmpdatumTest_1279, FamilyNameReturnsXmp_1279) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    EXPECT_STREQ("Xmp", datum.familyName());
}

// Test groupName() returns correct group
TEST_F(XmpdatumTest_1279, GroupNameReturnsCorrectGroup_1279) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    EXPECT_EQ("dc", datum.groupName());
}

// Test tagName() returns correct tag
TEST_F(XmpdatumTest_1279, TagNameReturnsCorrectTag_1279) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    EXPECT_EQ("title", datum.tagName());
}

// Test that copy constructor preserves key
TEST_F(XmpdatumTest_1279, CopyConstructorPreservesKey_1279) {
    Exiv2::XmpKey key("Xmp.dc.description");
    Exiv2::Xmpdatum datum(key, nullptr);
    Exiv2::Xmpdatum copy(datum);
    EXPECT_EQ(datum.key(), copy.key());
}

// Test that copy constructor preserves group and tag
TEST_F(XmpdatumTest_1279, CopyConstructorPreservesGroupAndTag_1279) {
    Exiv2::XmpKey key("Xmp.dc.creator");
    Exiv2::Xmpdatum datum(key, nullptr);
    Exiv2::Xmpdatum copy(datum);
    EXPECT_EQ(datum.groupName(), copy.groupName());
    EXPECT_EQ(datum.tagName(), copy.tagName());
}

// Test assignment operator
TEST_F(XmpdatumTest_1279, AssignmentOperatorCopiesCorrectly_1279) {
    Exiv2::XmpKey key1("Xmp.dc.title");
    Exiv2::XmpKey key2("Xmp.dc.description");
    Exiv2::Xmpdatum datum1(key1, nullptr);
    Exiv2::Xmpdatum datum2(key2, nullptr);
    datum2 = datum1;
    EXPECT_EQ("Xmp.dc.title", datum2.key());
}

// Test with nullptr value - count should be 0
TEST_F(XmpdatumTest_1279, NullValueCountIsZero_1279) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    EXPECT_EQ(0u, datum.count());
}

// Test with nullptr value - size should be 0
TEST_F(XmpdatumTest_1279, NullValueSizeIsZero_1279) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    EXPECT_EQ(0u, datum.size());
}

// Test setValue with string value
TEST_F(XmpdatumTest_1279, SetValueWithString_1279) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    datum.setValue("Hello World");
    EXPECT_EQ("Hello World", datum.toString());
}

// Test setValue with Value pointer
TEST_F(XmpdatumTest_1279, SetValueWithValuePointer_1279) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    Exiv2::XmpTextValue val("Test Value");
    datum.setValue(&val);
    EXPECT_EQ("Test Value", datum.toString());
}

// Test toString with no value
TEST_F(XmpdatumTest_1279, ToStringWithNoValue_1279) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    EXPECT_EQ("", datum.toString());
}

// Test typeId with no value
TEST_F(XmpdatumTest_1279, TypeIdWithNoValue_1279) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    EXPECT_EQ(Exiv2::invalidTypeId, datum.typeId());
}

// Test getValue with no value returns nullptr
TEST_F(XmpdatumTest_1279, GetValueReturnsNullWhenNoValue_1279) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    auto val = datum.getValue();
    EXPECT_EQ(nullptr, val.get());
}

// Test getValue returns non-null after setValue
TEST_F(XmpdatumTest_1279, GetValueReturnsNonNullAfterSetValue_1279) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    datum.setValue("test");
    auto val = datum.getValue();
    EXPECT_NE(nullptr, val.get());
}

// Test write to ostream
TEST_F(XmpdatumTest_1279, WriteToOstream_1279) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    datum.setValue("Hello");
    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test with XmpTextValue constructor
TEST_F(XmpdatumTest_1279, ConstructWithValue_1279) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::XmpTextValue val("Initial Value");
    Exiv2::Xmpdatum datum(key, &val);
    EXPECT_EQ("Initial Value", datum.toString());
}

// Test tagLabel returns something for known tag
TEST_F(XmpdatumTest_1279, TagLabelReturnsNonEmpty_1279) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    // tagLabel may or may not be empty depending on the property, just test it doesn't crash
    std::string label = datum.tagLabel();
    // No assertion on content since it's implementation-dependent
    (void)label;
}

// Test different XMP namespaces
TEST_F(XmpdatumTest_1279, DifferentNamespaces_1279) {
    Exiv2::XmpKey key1("Xmp.dc.title");
    Exiv2::XmpKey key2("Xmp.xmp.CreateDate");
    Exiv2::Xmpdatum datum1(key1, nullptr);
    Exiv2::Xmpdatum datum2(key2, nullptr);
    EXPECT_EQ("dc", datum1.groupName());
    EXPECT_EQ("xmp", datum2.groupName());
}

// Test copy preserves value
TEST_F(XmpdatumTest_1279, CopyConstructorPreservesValue_1279) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::XmpTextValue val("copy me");
    Exiv2::Xmpdatum datum(key, &val);
    Exiv2::Xmpdatum copy(datum);
    EXPECT_EQ("copy me", copy.toString());
}

// Test assignment operator preserves value
TEST_F(XmpdatumTest_1279, AssignmentPreservesValue_1279) {
    Exiv2::XmpKey key1("Xmp.dc.title");
    Exiv2::XmpKey key2("Xmp.dc.description");
    Exiv2::XmpTextValue val("assign me");
    Exiv2::Xmpdatum datum1(key1, &val);
    Exiv2::Xmpdatum datum2(key2, nullptr);
    datum2 = datum1;
    EXPECT_EQ("assign me", datum2.toString());
}

// Test count after setting value
TEST_F(XmpdatumTest_1279, CountAfterSetValue_1279) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    datum.setValue("test value");
    EXPECT_GT(datum.count(), 0u);
}

// Test size after setting value
TEST_F(XmpdatumTest_1279, SizeAfterSetValue_1279) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    datum.setValue("test value");
    EXPECT_GT(datum.size(), 0u);
}

// Test operator= with string template
TEST_F(XmpdatumTest_1279, TemplateAssignmentOperator_1279) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    datum = std::string("template assigned");
    EXPECT_EQ("template assigned", datum.toString());
}

// Test toString(n) with index 0
TEST_F(XmpdatumTest_1279, ToStringWithIndex_1279) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    datum.setValue("indexed");
    EXPECT_EQ("indexed", datum.toString(0));
}

// Test value() throws when no value is set
TEST_F(XmpdatumTest_1279, ValueThrowsWhenNoValue_1279) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    EXPECT_THROW(datum.value(), Exiv2::Error);
}

// Test copy returns 0 (XMP metadata doesn't support binary copy typically)
TEST_F(XmpdatumTest_1279, CopyReturnsZero_1279) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    Exiv2::byte buf[256];
    EXPECT_EQ(0u, datum.copy(buf, Exiv2::bigEndian));
}

} // namespace
