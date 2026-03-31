#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <sstream>
#include <string>

class XmpdatumTest_1291 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test construction with a key and no value (nullptr)
TEST_F(XmpdatumTest_1291, ConstructWithNullValue_1291) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.key(), "Xmp.dc.title");
    EXPECT_EQ(datum.toString(), "");
}

// Test construction with a key and a value
TEST_F(XmpdatumTest_1291, ConstructWithValue_1291) {
    Exiv2::XmpKey key("Xmp.dc.description");
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("Hello World");
    Exiv2::Xmpdatum datum(key, value.get());
    
    EXPECT_EQ(datum.key(), "Xmp.dc.description");
    EXPECT_EQ(datum.toString(), "Hello World");
}

// Test copy constructor
TEST_F(XmpdatumTest_1291, CopyConstructor_1291) {
    Exiv2::XmpKey key("Xmp.dc.creator");
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("Test Author");
    Exiv2::Xmpdatum original(key, value.get());
    
    Exiv2::Xmpdatum copy(original);
    
    EXPECT_EQ(copy.key(), "Xmp.dc.creator");
    EXPECT_EQ(copy.toString(), "Test Author");
}

// Test copy assignment operator
TEST_F(XmpdatumTest_1291, CopyAssignment_1291) {
    Exiv2::XmpKey key1("Xmp.dc.title");
    auto value1 = Exiv2::Value::create(Exiv2::xmpText);
    value1->read("Title1");
    Exiv2::Xmpdatum datum1(key1, value1.get());
    
    Exiv2::XmpKey key2("Xmp.dc.description");
    auto value2 = Exiv2::Value::create(Exiv2::xmpText);
    value2->read("Description2");
    Exiv2::Xmpdatum datum2(key2, value2.get());
    
    datum2 = datum1;
    
    EXPECT_EQ(datum2.key(), "Xmp.dc.title");
    EXPECT_EQ(datum2.toString(), "Title1");
}

// Test familyName returns "Xmp"
TEST_F(XmpdatumTest_1291, FamilyName_1291) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    EXPECT_STREQ(datum.familyName(), "Xmp");
}

// Test groupName
TEST_F(XmpdatumTest_1291, GroupName_1291) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.groupName(), "dc");
}

// Test tagName
TEST_F(XmpdatumTest_1291, TagName_1291) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.tagName(), "title");
}

// Test toString with no value returns empty string
TEST_F(XmpdatumTest_1291, ToStringNoValue_1291) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.toString(), "");
}

// Test toString with a value
TEST_F(XmpdatumTest_1291, ToStringWithValue_1291) {
    Exiv2::XmpKey key("Xmp.dc.title");
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("MyTitle");
    Exiv2::Xmpdatum datum(key, value.get());
    
    EXPECT_EQ(datum.toString(), "MyTitle");
}

// Test setValue with string
TEST_F(XmpdatumTest_1291, SetValueString_1291) {
    Exiv2::XmpKey key("Xmp.dc.title");
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("Initial");
    Exiv2::Xmpdatum datum(key, value.get());
    
    datum.setValue("Updated");
    
    EXPECT_EQ(datum.toString(), "Updated");
}

// Test setValue with Value pointer
TEST_F(XmpdatumTest_1291, SetValuePointer_1291) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("NewValue");
    datum.setValue(value.get());
    
    EXPECT_EQ(datum.toString(), "NewValue");
}

// Test setValue with nullptr resets value
TEST_F(XmpdatumTest_1291, SetValueNullptr_1291) {
    Exiv2::XmpKey key("Xmp.dc.title");
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("SomeValue");
    Exiv2::Xmpdatum datum(key, value.get());
    
    datum.setValue(static_cast<const Exiv2::Value*>(nullptr));
    
    EXPECT_EQ(datum.toString(), "");
}

// Test typeId when no value is set
TEST_F(XmpdatumTest_1291, TypeIdNoValue_1291) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    // When no value is set, typeId should indicate no type
    Exiv2::TypeId tid = datum.typeId();
    // Just verify it doesn't crash and returns some valid typeId
    (void)tid;
}

// Test typeId with xmpText value
TEST_F(XmpdatumTest_1291, TypeIdWithXmpText_1291) {
    Exiv2::XmpKey key("Xmp.dc.title");
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("Test");
    Exiv2::Xmpdatum datum(key, value.get());
    
    EXPECT_EQ(datum.typeId(), Exiv2::xmpText);
}

// Test count with no value
TEST_F(XmpdatumTest_1291, CountNoValue_1291) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.count(), 0u);
}

// Test count with a value
TEST_F(XmpdatumTest_1291, CountWithValue_1291) {
    Exiv2::XmpKey key("Xmp.dc.title");
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("Test");
    Exiv2::Xmpdatum datum(key, value.get());
    
    EXPECT_GE(datum.count(), 1u);
}

// Test size with no value
TEST_F(XmpdatumTest_1291, SizeNoValue_1291) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.size(), 0u);
}

// Test size with a value
TEST_F(XmpdatumTest_1291, SizeWithValue_1291) {
    Exiv2::XmpKey key("Xmp.dc.title");
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("Hello");
    Exiv2::Xmpdatum datum(key, value.get());
    
    EXPECT_GT(datum.size(), 0u);
}

// Test getValue with no value returns nullptr
TEST_F(XmpdatumTest_1291, GetValueNoValue_1291) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    auto val = datum.getValue();
    EXPECT_EQ(val.get(), nullptr);
}

// Test getValue with a value returns a clone
TEST_F(XmpdatumTest_1291, GetValueWithValue_1291) {
    Exiv2::XmpKey key("Xmp.dc.title");
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("Cloneable");
    Exiv2::Xmpdatum datum(key, value.get());
    
    auto val = datum.getValue();
    ASSERT_NE(val.get(), nullptr);
    EXPECT_EQ(val->toString(), "Cloneable");
}

// Test write to ostream
TEST_F(XmpdatumTest_1291, WriteToStream_1291) {
    Exiv2::XmpKey key("Xmp.dc.title");
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("StreamTest");
    Exiv2::Xmpdatum datum(key, value.get());
    
    std::ostringstream oss;
    datum.write(oss, nullptr);
    
    EXPECT_FALSE(oss.str().empty());
}

// Test write to ostream with no value
TEST_F(XmpdatumTest_1291, WriteToStreamNoValue_1291) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    std::ostringstream oss;
    datum.write(oss, nullptr);
    
    // Should not crash; output may be empty or contain something minimal
    (void)oss.str();
}

// Test template assignment operator with string
TEST_F(XmpdatumTest_1291, TemplateAssignString_1291) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    datum = std::string("Assigned");
    
    EXPECT_EQ(datum.toString(), "Assigned");
}

// Test toString with index n=0
TEST_F(XmpdatumTest_1291, ToStringWithIndex_1291) {
    Exiv2::XmpKey key("Xmp.dc.title");
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("IndexTest");
    Exiv2::Xmpdatum datum(key, value.get());
    
    EXPECT_EQ(datum.toString(0), "IndexTest");
}

// Test toInt64 with no value
TEST_F(XmpdatumTest_1291, ToInt64NoValue_1291) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    // Should handle gracefully - likely returns 0 or throws
    // Testing it doesn't crash
    try {
        int64_t val = datum.toInt64(0);
        (void)val;
    } catch (...) {
        // Acceptable if it throws for null value
    }
}

// Test toFloat with a numeric xmpText value
TEST_F(XmpdatumTest_1291, ToFloatWithValue_1291) {
    Exiv2::XmpKey key("Xmp.dc.title");
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("3.14");
    Exiv2::Xmpdatum datum(key, value.get());
    
    try {
        float f = datum.toFloat(0);
        EXPECT_NEAR(f, 3.14f, 0.01f);
    } catch (...) {
        // Some implementations may not support this conversion
    }
}

// Test copy constructor preserves independence
TEST_F(XmpdatumTest_1291, CopyConstructorIndependence_1291) {
    Exiv2::XmpKey key("Xmp.dc.title");
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("Original");
    Exiv2::Xmpdatum original(key, value.get());
    
    Exiv2::Xmpdatum copy(original);
    
    // Modify copy
    copy.setValue("Modified");
    
    // Original should remain unchanged
    EXPECT_EQ(original.toString(), "Original");
    EXPECT_EQ(copy.toString(), "Modified");
}

// Test tagLabel returns something (may be empty for custom properties)
TEST_F(XmpdatumTest_1291, TagLabel_1291) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    // Just check it doesn't crash
    std::string label = datum.tagLabel();
    (void)label;
}

// Test tagDesc returns something
TEST_F(XmpdatumTest_1291, TagDesc_1291) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    std::string desc = datum.tagDesc();
    (void)desc;
}

// Test tag returns a value
TEST_F(XmpdatumTest_1291, Tag_1291) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    uint16_t tag = datum.tag();
    (void)tag;
}

// Test typeName with no value
TEST_F(XmpdatumTest_1291, TypeNameNoValue_1291) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    // Should return something sensible or empty
    const char* tn = datum.typeName();
    (void)tn;
}

// Test typeName with xmpText value
TEST_F(XmpdatumTest_1291, TypeNameWithValue_1291) {
    Exiv2::XmpKey key("Xmp.dc.title");
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("Test");
    Exiv2::Xmpdatum datum(key, value.get());
    
    const char* tn = datum.typeName();
    ASSERT_NE(tn, nullptr);
    EXPECT_STREQ(tn, "XmpText");
}

// Test self-assignment
TEST_F(XmpdatumTest_1291, SelfAssignment_1291) {
    Exiv2::XmpKey key("Xmp.dc.title");
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("SelfAssign");
    Exiv2::Xmpdatum datum(key, value.get());
    
    datum = datum;
    
    EXPECT_EQ(datum.key(), "Xmp.dc.title");
    EXPECT_EQ(datum.toString(), "SelfAssign");
}

// Test empty string value
TEST_F(XmpdatumTest_1291, EmptyStringValue_1291) {
    Exiv2::XmpKey key("Xmp.dc.title");
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("");
    Exiv2::Xmpdatum datum(key, value.get());
    
    EXPECT_EQ(datum.toString(), "");
}

// Test very long string value
TEST_F(XmpdatumTest_1291, LongStringValue_1291) {
    Exiv2::XmpKey key("Xmp.dc.title");
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    std::string longStr(10000, 'A');
    value->read(longStr);
    Exiv2::Xmpdatum datum(key, value.get());
    
    EXPECT_EQ(datum.toString(), longStr);
}

// Test with special characters in value
TEST_F(XmpdatumTest_1291, SpecialCharactersValue_1291) {
    Exiv2::XmpKey key("Xmp.dc.title");
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("Hello <World> & \"Quotes\" 'Apostrophes'");
    Exiv2::Xmpdatum datum(key, value.get());
    
    EXPECT_EQ(datum.toString(), "Hello <World> & \"Quotes\" 'Apostrophes'");
}

// Test with Unicode content in value
TEST_F(XmpdatumTest_1291, UnicodeValue_1291) {
    Exiv2::XmpKey key("Xmp.dc.title");
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("日本語テスト");
    Exiv2::Xmpdatum datum(key, value.get());
    
    EXPECT_EQ(datum.toString(), "日本語テスト");
}

// Test different XMP namespaces
TEST_F(XmpdatumTest_1291, DifferentNamespace_1291) {
    Exiv2::XmpKey key("Xmp.xmp.CreateDate");
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("2023-01-01");
    Exiv2::Xmpdatum datum(key, value.get());
    
    EXPECT_EQ(datum.key(), "Xmp.xmp.CreateDate");
    EXPECT_EQ(datum.groupName(), "xmp");
    EXPECT_EQ(datum.tagName(), "CreateDate");
    EXPECT_EQ(datum.toString(), "2023-01-01");
}
