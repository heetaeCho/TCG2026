#include <gtest/gtest.h>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/properties.hpp>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <sstream>
#include <string>

using namespace Exiv2;

class XmpdatumTest_1301 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test basic construction with a known XmpKey
TEST_F(XmpdatumTest_1301, ConstructWithKey_1301) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ("Xmp.dc.title", datum.key());
}

// Test that familyName returns "Xmp"
TEST_F(XmpdatumTest_1301, FamilyName_1301) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_STREQ("Xmp", datum.familyName());
}

// Test groupName
TEST_F(XmpdatumTest_1301, GroupName_1301) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ("dc", datum.groupName());
}

// Test tagName
TEST_F(XmpdatumTest_1301, TagName_1301) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ("title", datum.tagName());
}

// Test setValue with string on a datum with no prior value
TEST_F(XmpdatumTest_1301, SetValueString_NoExistingValue_1301) {
    XmpKey key("Xmp.dc.description");
    Xmpdatum datum(key, nullptr);
    int result = datum.setValue("Hello World");
    EXPECT_EQ(0, result);
    EXPECT_EQ("Hello World", datum.toString());
}

// Test setValue with string on a datum that already has a value
TEST_F(XmpdatumTest_1301, SetValueString_OverwriteExistingValue_1301) {
    XmpKey key("Xmp.dc.description");
    Xmpdatum datum(key, nullptr);
    datum.setValue("First");
    int result = datum.setValue("Second");
    EXPECT_EQ(0, result);
    EXPECT_EQ("Second", datum.toString());
}

// Test setValue with an empty string
TEST_F(XmpdatumTest_1301, SetValueString_EmptyString_1301) {
    XmpKey key("Xmp.dc.description");
    Xmpdatum datum(key, nullptr);
    int result = datum.setValue("");
    EXPECT_EQ(0, result);
    EXPECT_EQ("", datum.toString());
}

// Test setValue with a Value pointer
TEST_F(XmpdatumTest_1301, SetValuePointer_1301) {
    XmpKey key("Xmp.dc.description");
    Xmpdatum datum(key, nullptr);
    auto val = Value::create(xmpText);
    val->read("Test Value");
    datum.setValue(val.get());
    EXPECT_EQ("Test Value", datum.toString());
}

// Test setValue with nullptr Value pointer
TEST_F(XmpdatumTest_1301, SetValuePointer_Null_1301) {
    XmpKey key("Xmp.dc.description");
    Xmpdatum datum(key, nullptr);
    datum.setValue("Something");
    datum.setValue(static_cast<const Value*>(nullptr));
    // After setting null value, getValue should reflect that
    auto val = datum.getValue();
    EXPECT_EQ(nullptr, val);
}

// Test copy constructor
TEST_F(XmpdatumTest_1301, CopyConstructor_1301) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum1(key, nullptr);
    datum1.setValue("Original");
    Xmpdatum datum2(datum1);
    EXPECT_EQ("Original", datum2.toString());
    EXPECT_EQ(datum1.key(), datum2.key());
}

// Test assignment operator
TEST_F(XmpdatumTest_1301, AssignmentOperator_1301) {
    XmpKey key1("Xmp.dc.title");
    Xmpdatum datum1(key1, nullptr);
    datum1.setValue("Value1");

    XmpKey key2("Xmp.dc.description");
    Xmpdatum datum2(key2, nullptr);
    datum2.setValue("Value2");

    datum2 = datum1;
    EXPECT_EQ("Xmp.dc.title", datum2.key());
    EXPECT_EQ("Value1", datum2.toString());
}

// Test typeId when using xmpText property
TEST_F(XmpdatumTest_1301, TypeId_XmpText_1301) {
    XmpKey key("Xmp.dc.description");
    Xmpdatum datum(key, nullptr);
    datum.setValue("test");
    TypeId tid = datum.typeId();
    // The type should be determined by XmpProperties::propertyType for the key
    EXPECT_NE(invalidTypeId, tid);
}

// Test count after setting a value
TEST_F(XmpdatumTest_1301, Count_AfterSetValue_1301) {
    XmpKey key("Xmp.dc.description");
    Xmpdatum datum(key, nullptr);
    datum.setValue("test value");
    EXPECT_GE(datum.count(), static_cast<size_t>(1));
}

// Test size after setting a value
TEST_F(XmpdatumTest_1301, Size_AfterSetValue_1301) {
    XmpKey key("Xmp.dc.description");
    Xmpdatum datum(key, nullptr);
    datum.setValue("test value");
    EXPECT_GT(datum.size(), static_cast<size_t>(0));
}

// Test write to ostream
TEST_F(XmpdatumTest_1301, Write_1301) {
    XmpKey key("Xmp.dc.description");
    Xmpdatum datum(key, nullptr);
    datum.setValue("hello");
    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test getValue returns a valid pointer after setValue
TEST_F(XmpdatumTest_1301, GetValue_AfterSetValue_1301) {
    XmpKey key("Xmp.dc.description");
    Xmpdatum datum(key, nullptr);
    datum.setValue("some value");
    auto val = datum.getValue();
    ASSERT_NE(nullptr, val);
    EXPECT_EQ("some value", val->toString());
}

// Test value() reference access after setValue
TEST_F(XmpdatumTest_1301, ValueRef_AfterSetValue_1301) {
    XmpKey key("Xmp.dc.description");
    Xmpdatum datum(key, nullptr);
    datum.setValue("ref test");
    const Value& val = datum.value();
    EXPECT_EQ("ref test", val.toString());
}

// Test toString with index parameter
TEST_F(XmpdatumTest_1301, ToStringWithIndex_1301) {
    XmpKey key("Xmp.dc.description");
    Xmpdatum datum(key, nullptr);
    datum.setValue("indexed");
    std::string s = datum.toString(0);
    EXPECT_EQ("indexed", s);
}

// Test toInt64
TEST_F(XmpdatumTest_1301, ToInt64_1301) {
    XmpKey key("Xmp.dc.description");
    Xmpdatum datum(key, nullptr);
    datum.setValue("42");
    int64_t val = datum.toInt64(0);
    EXPECT_EQ(42, val);
}

// Test toFloat
TEST_F(XmpdatumTest_1301, ToFloat_1301) {
    XmpKey key("Xmp.dc.description");
    Xmpdatum datum(key, nullptr);
    datum.setValue("3.14");
    float val = datum.toFloat(0);
    EXPECT_NEAR(3.14f, val, 0.01f);
}

// Test construction with a non-null Value
TEST_F(XmpdatumTest_1301, ConstructWithValue_1301) {
    XmpKey key("Xmp.dc.title");
    auto val = Value::create(xmpText);
    val->read("Initial Value");
    Xmpdatum datum(key, val.get());
    EXPECT_EQ("Initial Value", datum.toString());
}

// Test template assignment operator with string
TEST_F(XmpdatumTest_1301, TemplateAssignment_String_1301) {
    XmpKey key("Xmp.dc.description");
    Xmpdatum datum(key, nullptr);
    datum = std::string("assigned value");
    EXPECT_EQ("assigned value", datum.toString());
}

// Test setValue multiple times to ensure state is updated correctly
TEST_F(XmpdatumTest_1301, SetValue_MultipleTimes_1301) {
    XmpKey key("Xmp.dc.description");
    Xmpdatum datum(key, nullptr);
    datum.setValue("first");
    EXPECT_EQ("first", datum.toString());
    datum.setValue("second");
    EXPECT_EQ("second", datum.toString());
    datum.setValue("third");
    EXPECT_EQ("third", datum.toString());
}

// Test typeName after setting a value
TEST_F(XmpdatumTest_1301, TypeName_AfterSetValue_1301) {
    XmpKey key("Xmp.dc.description");
    Xmpdatum datum(key, nullptr);
    datum.setValue("test");
    const char* tn = datum.typeName();
    EXPECT_NE(nullptr, tn);
}

// Test copy returns 0 (as per the implementation that does nothing for XMP)
TEST_F(XmpdatumTest_1301, Copy_ReturnsZero_1301) {
    XmpKey key("Xmp.dc.description");
    Xmpdatum datum(key, nullptr);
    datum.setValue("copy test");
    byte buf[256] = {};
    size_t copied = datum.copy(buf, littleEndian);
    // XMP copy typically returns 0
    EXPECT_EQ(static_cast<size_t>(0), copied);
}

// Test with a different XMP namespace (xmpRights)
TEST_F(XmpdatumTest_1301, DifferentNamespace_XmpRights_1301) {
    XmpKey key("Xmp.xmpRights.UsageTerms");
    Xmpdatum datum(key, nullptr);
    datum.setValue("Creative Commons");
    EXPECT_EQ("Xmp.xmpRights.UsageTerms", datum.key());
    EXPECT_EQ("xmpRights", datum.groupName());
    EXPECT_EQ("UsageTerms", datum.tagName());
}

// Test with photoshop namespace
TEST_F(XmpdatumTest_1301, DifferentNamespace_Photoshop_1301) {
    XmpKey key("Xmp.photoshop.City");
    Xmpdatum datum(key, nullptr);
    datum.setValue("New York");
    EXPECT_EQ("New York", datum.toString());
}

// Test setValue with a very long string
TEST_F(XmpdatumTest_1301, SetValue_VeryLongString_1301) {
    XmpKey key("Xmp.dc.description");
    Xmpdatum datum(key, nullptr);
    std::string longStr(10000, 'A');
    int result = datum.setValue(longStr);
    EXPECT_EQ(0, result);
    EXPECT_EQ(longStr, datum.toString());
}

// Test setValue with special characters
TEST_F(XmpdatumTest_1301, SetValue_SpecialCharacters_1301) {
    XmpKey key("Xmp.dc.description");
    Xmpdatum datum(key, nullptr);
    std::string special = "Hello <World> & \"Test\" 'Quotes'";
    int result = datum.setValue(special);
    EXPECT_EQ(0, result);
    EXPECT_EQ(special, datum.toString());
}

// Test setValue with unicode-like content
TEST_F(XmpdatumTest_1301, SetValue_UnicodeContent_1301) {
    XmpKey key("Xmp.dc.description");
    Xmpdatum datum(key, nullptr);
    std::string utf8 = u8"Héllo Wörld";
    int result = datum.setValue(utf8);
    EXPECT_EQ(0, result);
    EXPECT_EQ(utf8, datum.toString());
}
