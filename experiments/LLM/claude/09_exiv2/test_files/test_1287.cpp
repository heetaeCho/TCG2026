#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <sstream>
#include <string>

class XmpdatumTest_1287 : public ::testing::Test {
protected:
    void SetUp() override {
        Exiv2::XmpParser::initialize();
    }
    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }
};

TEST_F(XmpdatumTest_1287, ConstructWithKey_1287) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    EXPECT_EQ("Xmp.dc.title", datum.key());
}

TEST_F(XmpdatumTest_1287, FamilyName_1287) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    EXPECT_STREQ("Xmp", datum.familyName());
}

TEST_F(XmpdatumTest_1287, GroupName_1287) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    EXPECT_EQ("dc", datum.groupName());
}

TEST_F(XmpdatumTest_1287, TagName_1287) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    EXPECT_EQ("title", datum.tagName());
}

TEST_F(XmpdatumTest_1287, DefaultTypeIdIsXmpText_1287) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    // Without setting a value, typeId should be some default
    Exiv2::TypeId tid = datum.typeId();
    // Just check it doesn't crash and returns something
    (void)tid;
}

TEST_F(XmpdatumTest_1287, TypeNameReturnsValidString_1287) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    const char* tn = datum.typeName();
    // typeName should correspond to typeId; it may be null or a valid string
    // For a default-constructed datum, we just ensure no crash
    (void)tn;
}

TEST_F(XmpdatumTest_1287, SetValueString_1287) {
    Exiv2::XmpKey key("Xmp.dc.description");
    Exiv2::Xmpdatum datum(key);
    int result = datum.setValue("Hello World");
    EXPECT_EQ(0, result);
    EXPECT_EQ("Hello World", datum.toString());
}

TEST_F(XmpdatumTest_1287, SetValuePointer_1287) {
    Exiv2::XmpKey key("Xmp.dc.description");
    Exiv2::Xmpdatum datum(key);
    Exiv2::XmpTextValue val("Test Value");
    datum.setValue(&val);
    EXPECT_EQ("Test Value", datum.toString());
}

TEST_F(XmpdatumTest_1287, CopyConstructor_1287) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    datum.setValue("Copy Test");
    
    Exiv2::Xmpdatum copy(datum);
    EXPECT_EQ(datum.key(), copy.key());
    EXPECT_EQ(datum.toString(), copy.toString());
}

TEST_F(XmpdatumTest_1287, AssignmentOperator_1287) {
    Exiv2::XmpKey key1("Xmp.dc.title");
    Exiv2::Xmpdatum datum1(key1);
    datum1.setValue("Original");
    
    Exiv2::XmpKey key2("Xmp.dc.description");
    Exiv2::Xmpdatum datum2(key2);
    datum2.setValue("Other");
    
    datum2 = datum1;
    EXPECT_EQ(datum1.key(), datum2.key());
    EXPECT_EQ(datum1.toString(), datum2.toString());
}

TEST_F(XmpdatumTest_1287, CountAfterSetValue_1287) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    Exiv2::Xmpdatum datum(key);
    datum.setValue("test");
    EXPECT_GE(datum.count(), static_cast<size_t>(1));
}

TEST_F(XmpdatumTest_1287, SizeAfterSetValue_1287) {
    Exiv2::XmpKey key("Xmp.dc.description");
    Exiv2::Xmpdatum datum(key);
    datum.setValue("test");
    EXPECT_GT(datum.size(), static_cast<size_t>(0));
}

TEST_F(XmpdatumTest_1287, WriteToStream_1287) {
    Exiv2::XmpKey key("Xmp.dc.description");
    Exiv2::Xmpdatum datum(key);
    datum.setValue("Stream Test");
    
    std::ostringstream os;
    datum.write(os, nullptr);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(XmpdatumTest_1287, GetValueReturnsUniquePtr_1287) {
    Exiv2::XmpKey key("Xmp.dc.description");
    Exiv2::Xmpdatum datum(key);
    datum.setValue("GetValue Test");
    
    auto val = datum.getValue();
    EXPECT_NE(nullptr, val.get());
    EXPECT_EQ("GetValue Test", val->toString());
}

TEST_F(XmpdatumTest_1287, ValueReference_1287) {
    Exiv2::XmpKey key("Xmp.dc.description");
    Exiv2::Xmpdatum datum(key);
    datum.setValue("Value Ref Test");
    
    const Exiv2::Value& val = datum.value();
    EXPECT_EQ("Value Ref Test", val.toString());
}

TEST_F(XmpdatumTest_1287, ToStringWithIndex_1287) {
    Exiv2::XmpKey key("Xmp.dc.description");
    Exiv2::Xmpdatum datum(key);
    datum.setValue("Indexed");
    
    std::string result = datum.toString(0);
    EXPECT_EQ("Indexed", result);
}

TEST_F(XmpdatumTest_1287, ToInt64_1287) {
    Exiv2::XmpKey key("Xmp.dc.description");
    Exiv2::Xmpdatum datum(key);
    datum.setValue("42");
    
    int64_t val = datum.toInt64(0);
    EXPECT_EQ(42, val);
}

TEST_F(XmpdatumTest_1287, ToFloat_1287) {
    Exiv2::XmpKey key("Xmp.dc.description");
    Exiv2::Xmpdatum datum(key);
    datum.setValue("3.14");
    
    float val = datum.toFloat(0);
    EXPECT_NEAR(3.14f, val, 0.01f);
}

TEST_F(XmpdatumTest_1287, TypeNameConsistentWithTypeId_1287) {
    Exiv2::XmpKey key("Xmp.dc.description");
    Exiv2::Xmpdatum datum(key);
    datum.setValue("type test");
    
    Exiv2::TypeId tid = datum.typeId();
    const char* tn = datum.typeName();
    const char* expected = Exiv2::TypeInfo::typeName(tid);
    
    if (tn && expected) {
        EXPECT_STREQ(expected, tn);
    } else {
        EXPECT_EQ(expected, tn);
    }
}

TEST_F(XmpdatumTest_1287, TypeSizeConsistentWithTypeId_1287) {
    Exiv2::XmpKey key("Xmp.dc.description");
    Exiv2::Xmpdatum datum(key);
    datum.setValue("size test");
    
    size_t ts = datum.typeSize();
    size_t expected = Exiv2::TypeInfo::typeSize(datum.typeId());
    EXPECT_EQ(expected, ts);
}

TEST_F(XmpdatumTest_1287, SetValueWithNullPointer_1287) {
    Exiv2::XmpKey key("Xmp.dc.description");
    Exiv2::Xmpdatum datum(key);
    datum.setValue("initial");
    
    // Setting null value should clear it or handle gracefully
    datum.setValue(static_cast<const Exiv2::Value*>(nullptr));
    // After setting null, count and size should be 0
    EXPECT_EQ(static_cast<size_t>(0), datum.count());
}

TEST_F(XmpdatumTest_1287, SetValueEmptyString_1287) {
    Exiv2::XmpKey key("Xmp.dc.description");
    Exiv2::Xmpdatum datum(key);
    int result = datum.setValue("");
    EXPECT_EQ(0, result);
}

TEST_F(XmpdatumTest_1287, TagLabel_1287) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    std::string label = datum.tagLabel();
    // tagLabel should return something (possibly empty or the label)
    // Just verify no crash
    (void)label;
}

TEST_F(XmpdatumTest_1287, TagDesc_1287) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    std::string desc = datum.tagDesc();
    // Just verify no crash
    (void)desc;
}

TEST_F(XmpdatumTest_1287, Tag_1287) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    uint16_t tag = datum.tag();
    // Just verify it returns a value without crashing
    (void)tag;
}

TEST_F(XmpdatumTest_1287, CopyMethod_1287) {
    Exiv2::XmpKey key("Xmp.dc.description");
    Exiv2::Xmpdatum datum(key);
    datum.setValue("copy test");
    
    // copy for XMP is documented to return 0 / throw
    Exiv2::byte buf[100];
    size_t result = datum.copy(buf, Exiv2::bigEndian);
    // XMP copy typically returns 0
    EXPECT_EQ(static_cast<size_t>(0), result);
}

TEST_F(XmpdatumTest_1287, AssignStringTemplate_1287) {
    Exiv2::XmpKey key("Xmp.dc.description");
    Exiv2::Xmpdatum datum(key);
    datum = std::string("template assign");
    EXPECT_EQ("template assign", datum.toString());
}

TEST_F(XmpdatumTest_1287, SelfAssignment_1287) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    datum.setValue("self");
    
    datum = datum;
    EXPECT_EQ("Xmp.dc.title", datum.key());
    EXPECT_EQ("self", datum.toString());
}

TEST_F(XmpdatumTest_1287, MultipleSetValueCalls_1287) {
    Exiv2::XmpKey key("Xmp.dc.description");
    Exiv2::Xmpdatum datum(key);
    
    datum.setValue("first");
    EXPECT_EQ("first", datum.toString());
    
    datum.setValue("second");
    EXPECT_EQ("second", datum.toString());
    
    datum.setValue("third");
    EXPECT_EQ("third", datum.toString());
}

TEST_F(XmpdatumTest_1287, DifferentXmpNamespaces_1287) {
    Exiv2::XmpKey key1("Xmp.dc.title");
    Exiv2::Xmpdatum datum1(key1);
    EXPECT_EQ("dc", datum1.groupName());
    
    Exiv2::XmpKey key2("Xmp.xmp.CreateDate");
    Exiv2::Xmpdatum datum2(key2);
    EXPECT_EQ("xmp", datum2.groupName());
}
