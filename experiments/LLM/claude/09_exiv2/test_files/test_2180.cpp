#include <gtest/gtest.h>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/properties.hpp>
#include <exiv2/value.hpp>
#include <exiv2/error.hpp>

using namespace Exiv2;

// Test fixture for Xmpdatum tests
class XmpdatumTest_2180 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test default construction via XmpKey
TEST_F(XmpdatumTest_2180, ConstructWithKey_2180) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key);
    EXPECT_EQ("Xmp.dc.title", datum.key());
    EXPECT_EQ("Xmp", std::string(datum.familyName()));
    EXPECT_EQ("dc", datum.groupName());
    EXPECT_EQ("title", datum.tagName());
}

// Test copy construction of Xmpdatum
TEST_F(XmpdatumTest_2180, CopyConstruction_2180) {
    XmpKey key("Xmp.dc.description");
    Xmpdatum datum(key);
    datum.setValue("Test description");
    
    Xmpdatum copy(datum);
    EXPECT_EQ(datum.key(), copy.key());
    EXPECT_EQ(datum.toString(), copy.toString());
}

// Test copy assignment operator
TEST_F(XmpdatumTest_2180, CopyAssignment_2180) {
    XmpKey key1("Xmp.dc.title");
    Xmpdatum datum1(key1);
    datum1.setValue("Title value");
    
    XmpKey key2("Xmp.dc.description");
    Xmpdatum datum2(key2);
    datum2.setValue("Description value");
    
    datum2 = datum1;
    EXPECT_EQ("Xmp.dc.title", datum2.key());
    EXPECT_EQ(datum1.toString(), datum2.toString());
}

// Test that copy is deep - modifying original doesn't affect copy
TEST_F(XmpdatumTest_2180, DeepCopyKey_2180) {
    XmpKey key("Xmp.dc.subject");
    Xmpdatum original(key);
    original.setValue("Original value");
    
    Xmpdatum copy(original);
    
    // Modify original
    original.setValue("Modified value");
    
    // Copy should retain original value
    EXPECT_EQ("Original value", copy.toString());
    EXPECT_EQ("Modified value", original.toString());
}

// Test deep copy via assignment
TEST_F(XmpdatumTest_2180, DeepCopyAssignment_2180) {
    XmpKey key1("Xmp.dc.creator");
    Xmpdatum datum1(key1);
    datum1.setValue("Creator 1");
    
    XmpKey key2("Xmp.dc.rights");
    Xmpdatum datum2(key2);
    datum2.setValue("Rights value");
    
    datum2 = datum1;
    
    // Modify datum1 after assignment
    datum1.setValue("Modified Creator");
    
    // datum2 should not be affected
    EXPECT_EQ("Creator 1", datum2.toString());
    EXPECT_EQ("Xmp.dc.creator", datum2.key());
}

// Test construction with no value set
TEST_F(XmpdatumTest_2180, ConstructWithoutValue_2180) {
    XmpKey key("Xmp.dc.format");
    Xmpdatum datum(key);
    EXPECT_EQ("Xmp.dc.format", datum.key());
    // Value count should be 0 when no value is set
    EXPECT_EQ(0u, datum.count());
}

// Test setting a string value
TEST_F(XmpdatumTest_2180, SetStringValue_2180) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key);
    datum.setValue("Hello World");
    EXPECT_EQ("Hello World", datum.toString());
}

// Test familyName returns "Xmp"
TEST_F(XmpdatumTest_2180, FamilyName_2180) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key);
    EXPECT_STREQ("Xmp", datum.familyName());
}

// Test groupName
TEST_F(XmpdatumTest_2180, GroupName_2180) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key);
    EXPECT_EQ("dc", datum.groupName());
}

// Test tagName
TEST_F(XmpdatumTest_2180, TagName_2180) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key);
    EXPECT_EQ("title", datum.tagName());
}

// Test XmpKey construction and cloning
TEST_F(XmpdatumTest_2180, XmpKeyClone_2180) {
    XmpKey key("Xmp.dc.title");
    auto cloned = key.clone();
    EXPECT_EQ(key.key(), cloned->key());
    EXPECT_EQ(key.groupName(), cloned->groupName());
    EXPECT_EQ(key.tagName(), cloned->tagName());
}

// Test XmpKey copy constructor
TEST_F(XmpdatumTest_2180, XmpKeyCopyConstructor_2180) {
    XmpKey key("Xmp.dc.subject");
    XmpKey keyCopy(key);
    EXPECT_EQ(key.key(), keyCopy.key());
    EXPECT_EQ(key.groupName(), keyCopy.groupName());
    EXPECT_EQ(key.tagName(), keyCopy.tagName());
    EXPECT_EQ(key.ns(), keyCopy.ns());
}

// Test XmpKey assignment operator
TEST_F(XmpdatumTest_2180, XmpKeyAssignment_2180) {
    XmpKey key1("Xmp.dc.title");
    XmpKey key2("Xmp.dc.description");
    key2 = key1;
    EXPECT_EQ(key1.key(), key2.key());
    EXPECT_EQ(key1.tagName(), key2.tagName());
}

// Test copy of Xmpdatum with null value (no value set)
TEST_F(XmpdatumTest_2180, CopyWithNullValue_2180) {
    XmpKey key("Xmp.dc.language");
    Xmpdatum datum(key);
    // No value set
    
    Xmpdatum copy(datum);
    EXPECT_EQ("Xmp.dc.language", copy.key());
    EXPECT_EQ(0u, copy.count());
}

// Test setting value via Value object
TEST_F(XmpdatumTest_2180, SetValueObject_2180) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key);
    
    auto value = Value::create(xmpText);
    value->read("Test Title");
    datum.setValue(value.get());
    
    EXPECT_EQ("Test Title", datum.toString());
}

// Test that after copy, both key and value are independent
TEST_F(XmpdatumTest_2180, CopyIndependence_2180) {
    XmpKey key("Xmp.dc.creator");
    Xmpdatum datum1(key);
    
    auto value = Value::create(xmpText);
    value->read("Author Name");
    datum1.setValue(value.get());
    
    Xmpdatum datum2(datum1);
    
    // Verify both have same values
    EXPECT_EQ(datum1.key(), datum2.key());
    EXPECT_EQ(datum1.toString(), datum2.toString());
    
    // Modify one, ensure the other is unaffected
    datum1.setValue("New Author");
    EXPECT_EQ("New Author", datum1.toString());
    EXPECT_EQ("Author Name", datum2.toString());
}

// Test XmpKey with prefix and property constructor
TEST_F(XmpdatumTest_2180, XmpKeyPrefixProperty_2180) {
    XmpKey key("dc", "title");
    EXPECT_EQ("Xmp.dc.title", key.key());
    EXPECT_EQ("dc", key.groupName());
    EXPECT_EQ("title", key.tagName());
}

// Test self-assignment of Xmpdatum
TEST_F(XmpdatumTest_2180, SelfAssignment_2180) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key);
    datum.setValue("Self test");
    
    datum = datum;
    EXPECT_EQ("Xmp.dc.title", datum.key());
    EXPECT_EQ("Self test", datum.toString());
}

// Test XmpData container operations with Xmpdatum
TEST_F(XmpdatumTest_2180, XmpDataAddAndAccess_2180) {
    XmpData xmpData;
    
    xmpData["Xmp.dc.title"] = "Test Title";
    xmpData["Xmp.dc.description"] = "Test Description";
    
    EXPECT_EQ(2u, xmpData.count());
    
    auto it = xmpData.findKey(XmpKey("Xmp.dc.title"));
    ASSERT_NE(it, xmpData.end());
    EXPECT_EQ("Test Title", it->toString());
}

// Test XmpData copy semantics
TEST_F(XmpdatumTest_2180, XmpDataCopy_2180) {
    XmpData xmpData1;
    xmpData1["Xmp.dc.title"] = "Original";
    
    XmpData xmpData2(xmpData1);
    
    auto it = xmpData2.findKey(XmpKey("Xmp.dc.title"));
    ASSERT_NE(it, xmpData2.end());
    EXPECT_EQ("Original", it->toString());
    
    // Modify original, copy should be unaffected
    xmpData1["Xmp.dc.title"] = "Modified";
    it = xmpData2.findKey(XmpKey("Xmp.dc.title"));
    ASSERT_NE(it, xmpData2.end());
    EXPECT_EQ("Original", it->toString());
}
