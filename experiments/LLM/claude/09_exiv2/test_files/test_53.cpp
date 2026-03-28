#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <sstream>
#include <string>
#include <memory>

class XmpdatumTest_53 : public ::testing::Test {
protected:
    void SetUp() override {
        Exiv2::XmpParser::initialize();
    }

    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }
};

// Test basic construction with XmpKey
TEST_F(XmpdatumTest_53, ConstructWithKey_53) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    
    EXPECT_EQ("Xmp.dc.title", datum.key());
    EXPECT_STREQ("Xmp", datum.familyName());
    EXPECT_EQ("dc", datum.groupName());
    EXPECT_EQ("title", datum.tagName());
}

// Test copy construction
TEST_F(XmpdatumTest_53, CopyConstruction_53) {
    Exiv2::XmpKey key("Xmp.dc.description");
    Exiv2::Xmpdatum datum(key);
    datum = std::string("test value");
    
    Exiv2::Xmpdatum copy(datum);
    EXPECT_EQ(datum.key(), copy.key());
    EXPECT_EQ(datum.toString(), copy.toString());
}

// Test copy assignment operator
TEST_F(XmpdatumTest_53, CopyAssignment_53) {
    Exiv2::XmpKey key1("Xmp.dc.title");
    Exiv2::Xmpdatum datum1(key1);
    datum1 = std::string("value1");
    
    Exiv2::XmpKey key2("Xmp.dc.description");
    Exiv2::Xmpdatum datum2(key2);
    datum2 = datum1;
    
    EXPECT_EQ(datum1.key(), datum2.key());
    EXPECT_EQ(datum1.toString(), datum2.toString());
}

// Test operator= with bool true
TEST_F(XmpdatumTest_53, AssignBoolTrue_53) {
    Exiv2::XmpKey key("Xmp.xmp.Thumbnails");
    Exiv2::Xmpdatum datum(key);
    datum = true;
    
    EXPECT_EQ("True", datum.toString());
}

// Test operator= with bool false
TEST_F(XmpdatumTest_53, AssignBoolFalse_53) {
    Exiv2::XmpKey key("Xmp.xmp.Thumbnails");
    Exiv2::Xmpdatum datum(key);
    datum = false;
    
    EXPECT_EQ("False", datum.toString());
}

// Test operator= with std::string
TEST_F(XmpdatumTest_53, AssignString_53) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    datum = std::string("Hello World");
    
    EXPECT_EQ("Hello World", datum.toString());
}

// Test operator= with const char*
TEST_F(XmpdatumTest_53, AssignCString_53) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    datum = "Hello CString";
    
    EXPECT_EQ("Hello CString", datum.toString());
}

// Test operator= with integer
TEST_F(XmpdatumTest_53, AssignInt_53) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    datum = 42;
    
    EXPECT_EQ("42", datum.toString());
}

// Test operator= with negative integer
TEST_F(XmpdatumTest_53, AssignNegativeInt_53) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    datum = -100;
    
    EXPECT_EQ("-100", datum.toString());
}

// Test setValue with string
TEST_F(XmpdatumTest_53, SetValueString_53) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    int result = datum.setValue("test string");
    
    EXPECT_EQ(0, result);
    EXPECT_EQ("test string", datum.toString());
}

// Test setValue with empty string
TEST_F(XmpdatumTest_53, SetValueEmptyString_53) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    int result = datum.setValue("");
    
    EXPECT_EQ(0, result);
}

// Test setValue with Value pointer (nullptr)
TEST_F(XmpdatumTest_53, SetValueNullptr_53) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    datum.setValue(nullptr);
    
    // After setting null value, count should be 0
    EXPECT_EQ(0u, datum.count());
}

// Test setValue with Value pointer
TEST_F(XmpdatumTest_53, SetValueWithValuePtr_53) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    
    Exiv2::XmpTextValue val("Some XMP Text");
    datum.setValue(&val);
    
    EXPECT_EQ("Some XMP Text", datum.toString());
}

// Test operator= with Value object (base_of<Value>)
TEST_F(XmpdatumTest_53, AssignValueObject_53) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    
    Exiv2::XmpTextValue val("XMP Value Object");
    datum = val;
    
    EXPECT_EQ("XMP Value Object", datum.toString());
}

// Test key() returns correct key
TEST_F(XmpdatumTest_53, KeyReturnsCorrectKey_53) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    Exiv2::Xmpdatum datum(key);
    
    EXPECT_EQ("Xmp.dc.subject", datum.key());
}

// Test familyName() returns "Xmp"
TEST_F(XmpdatumTest_53, FamilyNameReturnsXmp_53) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    
    EXPECT_STREQ("Xmp", datum.familyName());
}

// Test groupName() 
TEST_F(XmpdatumTest_53, GroupNameReturnsCorrect_53) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    
    EXPECT_EQ("dc", datum.groupName());
}

// Test tagName()
TEST_F(XmpdatumTest_53, TagNameReturnsCorrect_53) {
    Exiv2::XmpKey key("Xmp.dc.creator");
    Exiv2::Xmpdatum datum(key);
    
    EXPECT_EQ("creator", datum.tagName());
}

// Test count() with no value set
TEST_F(XmpdatumTest_53, CountWithNoValue_53) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    
    EXPECT_EQ(0u, datum.count());
}

// Test count() after setting a value
TEST_F(XmpdatumTest_53, CountAfterSetValue_53) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    datum.setValue("hello");
    
    EXPECT_GT(datum.count(), 0u);
}

// Test size() with no value
TEST_F(XmpdatumTest_53, SizeWithNoValue_53) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    
    EXPECT_EQ(0u, datum.size());
}

// Test size() after setting a value
TEST_F(XmpdatumTest_53, SizeAfterSetValue_53) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    datum.setValue("hello");
    
    EXPECT_GT(datum.size(), 0u);
}

// Test toString(size_t n) 
TEST_F(XmpdatumTest_53, ToStringWithIndex_53) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    datum.setValue("test value");
    
    std::string result = datum.toString(0);
    EXPECT_EQ("test value", result);
}

// Test write to ostream
TEST_F(XmpdatumTest_53, WriteToOstream_53) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    datum.setValue("output test");
    
    std::ostringstream oss;
    datum.write(oss, nullptr);
    
    EXPECT_FALSE(oss.str().empty());
}

// Test getValue returns non-null after setting value
TEST_F(XmpdatumTest_53, GetValueAfterSet_53) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    datum.setValue("some value");
    
    auto val = datum.getValue();
    ASSERT_NE(nullptr, val.get());
    EXPECT_EQ("some value", val->toString());
}

// Test getValue returns null when no value set
TEST_F(XmpdatumTest_53, GetValueWithNoValueSet_53) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    
    auto val = datum.getValue();
    // getValue() may return nullptr or throw when no value is set
    // The behavior depends on implementation
}

// Test value() throws when no value is set
TEST_F(XmpdatumTest_53, ValueThrowsWhenNoValueSet_53) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    
    EXPECT_THROW(datum.value(), Exiv2::Error);
}

// Test typeId with no value set
TEST_F(XmpdatumTest_53, TypeIdWithNoValue_53) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    
    // When no value is set, typeId should return some default
    Exiv2::TypeId tid = datum.typeId();
    // Just verify it doesn't crash; actual value depends on implementation
    (void)tid;
}

// Test tagLabel returns non-empty string for known tag
TEST_F(XmpdatumTest_53, TagLabelForKnownTag_53) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    
    std::string label = datum.tagLabel();
    // Known tags should have labels
    EXPECT_FALSE(label.empty());
}

// Test assigning multiple times overwrites value
TEST_F(XmpdatumTest_53, MultipleAssignmentsOverwrite_53) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    
    datum = std::string("first");
    EXPECT_EQ("first", datum.toString());
    
    datum = std::string("second");
    EXPECT_EQ("second", datum.toString());
    
    datum = std::string("third");
    EXPECT_EQ("third", datum.toString());
}

// Test assigning zero
TEST_F(XmpdatumTest_53, AssignZero_53) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    datum = 0;
    
    EXPECT_EQ("0", datum.toString());
}

// Test toInt64 after setting integer value
TEST_F(XmpdatumTest_53, ToInt64AfterSetInt_53) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    datum = 12345;
    
    EXPECT_EQ(12345, datum.toInt64(0));
}

// Test toFloat after setting numeric value
TEST_F(XmpdatumTest_53, ToFloatAfterSetNumeric_53) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    datum = std::string("3.14");
    
    float val = datum.toFloat(0);
    EXPECT_NEAR(3.14f, val, 0.01f);
}

// Test copy method returns 0 for XMP data
TEST_F(XmpdatumTest_53, CopyReturnsZero_53) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    datum.setValue("test");
    
    Exiv2::byte buf[256];
    size_t copied = datum.copy(buf, Exiv2::littleEndian);
    // XMP copy typically returns 0 as it's not a binary format
    EXPECT_EQ(0u, copied);
}

// Test different XMP namespaces
TEST_F(XmpdatumTest_53, DifferentNamespaces_53) {
    {
        Exiv2::XmpKey key("Xmp.xmp.Rating");
        Exiv2::Xmpdatum datum(key);
        EXPECT_EQ("xmp", datum.groupName());
        EXPECT_EQ("Rating", datum.tagName());
    }
    {
        Exiv2::XmpKey key("Xmp.photoshop.City");
        Exiv2::Xmpdatum datum(key);
        EXPECT_EQ("photoshop", datum.groupName());
        EXPECT_EQ("City", datum.tagName());
    }
}

// Test assigning long string
TEST_F(XmpdatumTest_53, AssignLongString_53) {
    Exiv2::XmpKey key("Xmp.dc.description");
    Exiv2::Xmpdatum datum(key);
    
    std::string longStr(10000, 'A');
    datum = longStr;
    
    EXPECT_EQ(longStr, datum.toString());
}

// Test assigning unicode-like string (UTF-8)
TEST_F(XmpdatumTest_53, AssignUTF8String_53) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    
    std::string utf8str = u8"Héllo Wörld";
    datum = utf8str;
    
    EXPECT_EQ(utf8str, datum.toString());
}

// Test self-assignment
TEST_F(XmpdatumTest_53, SelfAssignment_53) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    datum = std::string("self test");
    
    datum = datum;
    
    EXPECT_EQ("Xmp.dc.title", datum.key());
    EXPECT_EQ("self test", datum.toString());
}

// Test tag() returns a numeric tag
TEST_F(XmpdatumTest_53, TagReturnsNumeric_53) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    
    uint16_t tag = datum.tag();
    // Just verify it returns something without crashing
    (void)tag;
}

// Test typeSize with no value
TEST_F(XmpdatumTest_53, TypeSizeNoValue_53) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    
    size_t ts = datum.typeSize();
    (void)ts; // Just verify no crash
}

// Test assigning int64_t large value
TEST_F(XmpdatumTest_53, AssignLargeInt_53) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    int64_t largeVal = 9999999999LL;
    datum = largeVal;
    
    EXPECT_EQ("9999999999", datum.toString());
}
