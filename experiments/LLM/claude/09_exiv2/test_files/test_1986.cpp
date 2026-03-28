#include <gtest/gtest.h>
#include <string>
#include <cstring>

// Include necessary XMP SDK headers
#define TXMP_STRING_TYPE std::string
#include "XMP.hpp"
#include "XMPMeta.hpp"

// Test fixture that initializes XMP SDK
class XMPUtilsTest_1986 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!SXMPMeta::Initialize()) {
            // If already initialized, that's fine
        }
    }

    static void TearDownTestSuite() {
        SXMPMeta::Terminate();
    }

    void SetUp() override {
        meta_ = XMPMeta();
    }

    XMPMeta meta_;
};

// Test setting and getting a simple property
TEST_F(XMPUtilsTest_1986, SetAndGetProperty_1986) {
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* propName = "xmp:CreateDate";
    const char* propValue = "2023-01-01";

    meta_.SetProperty(schemaNS, propName, propValue, 0);

    XMP_StringPtr resultValue = nullptr;
    XMP_StringLen resultLen = 0;
    XMP_OptionBits options = 0;
    bool found = meta_.GetProperty(schemaNS, propName, &resultValue, &resultLen, &options);

    EXPECT_TRUE(found);
    EXPECT_STREQ(resultValue, propValue);
}

// Test DoesPropertyExist returns false for non-existent property
TEST_F(XMPUtilsTest_1986, PropertyDoesNotExist_1986) {
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* propName = "xmp:NonExistent";

    bool exists = meta_.DoesPropertyExist(schemaNS, propName);
    EXPECT_FALSE(exists);
}

// Test DoesPropertyExist returns true after setting property
TEST_F(XMPUtilsTest_1986, PropertyExistsAfterSet_1986) {
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* propName = "xmp:CreatorTool";

    meta_.SetProperty(schemaNS, propName, "TestTool", 0);
    bool exists = meta_.DoesPropertyExist(schemaNS, propName);
    EXPECT_TRUE(exists);
}

// Test DeleteProperty removes property
TEST_F(XMPUtilsTest_1986, DeletePropertyRemovesIt_1986) {
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* propName = "xmp:CreatorTool";

    meta_.SetProperty(schemaNS, propName, "TestTool", 0);
    EXPECT_TRUE(meta_.DoesPropertyExist(schemaNS, propName));

    meta_.DeleteProperty(schemaNS, propName);
    EXPECT_FALSE(meta_.DoesPropertyExist(schemaNS, propName));
}

// Test Erase clears all properties
TEST_F(XMPUtilsTest_1986, EraseClearsAllProperties_1986) {
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";

    meta_.SetProperty(schemaNS, "xmp:CreatorTool", "Tool1", 0);
    meta_.SetProperty(schemaNS, "xmp:CreateDate", "2023-01-01", 0);

    meta_.Erase();

    EXPECT_FALSE(meta_.DoesPropertyExist(schemaNS, "xmp:CreatorTool"));
    EXPECT_FALSE(meta_.DoesPropertyExist(schemaNS, "xmp:CreateDate"));
}

// Test SetProperty_Bool and GetProperty_Bool
TEST_F(XMPUtilsTest_1986, SetAndGetBoolProperty_1986) {
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* propName = "xmp:BoolProp";

    meta_.SetProperty_Bool(schemaNS, propName, true, 0);

    bool propValue = false;
    XMP_OptionBits options = 0;
    bool found = meta_.GetProperty_Bool(schemaNS, propName, &propValue, &options);

    EXPECT_TRUE(found);
    EXPECT_TRUE(propValue);
}

// Test SetProperty_Int and GetProperty_Int
TEST_F(XMPUtilsTest_1986, SetAndGetIntProperty_1986) {
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* propName = "xmp:IntProp";

    meta_.SetProperty_Int(schemaNS, propName, 42, 0);

    XMP_Int32 propValue = 0;
    XMP_OptionBits options = 0;
    bool found = meta_.GetProperty_Int(schemaNS, propName, &propValue, &options);

    EXPECT_TRUE(found);
    EXPECT_EQ(propValue, 42);
}

// Test SetProperty_Int64 and GetProperty_Int64
TEST_F(XMPUtilsTest_1986, SetAndGetInt64Property_1986) {
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* propName = "xmp:Int64Prop";

    XMP_Int64 bigVal = 9876543210LL;
    meta_.SetProperty_Int64(schemaNS, propName, bigVal, 0);

    XMP_Int64 propValue = 0;
    XMP_OptionBits options = 0;
    bool found = meta_.GetProperty_Int64(schemaNS, propName, &propValue, &options);

    EXPECT_TRUE(found);
    EXPECT_EQ(propValue, bigVal);
}

// Test SetProperty_Float and GetProperty_Float
TEST_F(XMPUtilsTest_1986, SetAndGetFloatProperty_1986) {
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* propName = "xmp:FloatProp";

    meta_.SetProperty_Float(schemaNS, propName, 3.14, 0);

    double propValue = 0.0;
    XMP_OptionBits options = 0;
    bool found = meta_.GetProperty_Float(schemaNS, propName, &propValue, &options);

    EXPECT_TRUE(found);
    EXPECT_NEAR(propValue, 3.14, 0.001);
}

// Test SetObjectName and GetObjectName
TEST_F(XMPUtilsTest_1986, SetAndGetObjectName_1986) {
    meta_.SetObjectName("TestObject");

    XMP_StringPtr namePtr = nullptr;
    XMP_StringLen nameLen = 0;
    meta_.GetObjectName(&namePtr, &nameLen);

    EXPECT_STREQ(namePtr, "TestObject");
    EXPECT_GT(nameLen, 0u);
}

// Test Clone produces equivalent metadata
TEST_F(XMPUtilsTest_1986, CloneProducesEquivalentMeta_1986) {
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* propName = "xmp:CreatorTool";
    const char* propValue = "CloneTest";

    meta_.SetProperty(schemaNS, propName, propValue, 0);

    XMPMeta cloned;
    meta_.Clone(&cloned, 0);

    XMP_StringPtr resultValue = nullptr;
    XMP_StringLen resultLen = 0;
    XMP_OptionBits options = 0;
    bool found = cloned.GetProperty(schemaNS, propName, &resultValue, &resultLen, &options);

    EXPECT_TRUE(found);
    EXPECT_STREQ(resultValue, propValue);
}

// Test AppendArrayItem and CountArrayItems
TEST_F(XMPUtilsTest_1986, AppendArrayItemAndCount_1986) {
    const char* schemaNS = "http://purl.org/dc/elements/1.1/";
    const char* arrayName = "dc:subject";

    meta_.AppendArrayItem(schemaNS, arrayName, kXMP_PropArrayIsUnordered, "Keyword1", 0);
    meta_.AppendArrayItem(schemaNS, arrayName, kXMP_PropArrayIsUnordered, "Keyword2", 0);
    meta_.AppendArrayItem(schemaNS, arrayName, kXMP_PropArrayIsUnordered, "Keyword3", 0);

    XMP_Index count = meta_.CountArrayItems(schemaNS, arrayName);
    EXPECT_EQ(count, 3);
}

// Test GetArrayItem retrieves correct value
TEST_F(XMPUtilsTest_1986, GetArrayItemRetrievesCorrectValue_1986) {
    const char* schemaNS = "http://purl.org/dc/elements/1.1/";
    const char* arrayName = "dc:subject";

    meta_.AppendArrayItem(schemaNS, arrayName, kXMP_PropArrayIsUnordered, "Alpha", 0);
    meta_.AppendArrayItem(schemaNS, arrayName, kXMP_PropArrayIsUnordered, "Beta", 0);

    XMP_StringPtr itemValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;
    bool found = meta_.GetArrayItem(schemaNS, arrayName, 1, &itemValue, &valueSize, &options);

    EXPECT_TRUE(found);
    EXPECT_STREQ(itemValue, "Alpha");

    found = meta_.GetArrayItem(schemaNS, arrayName, 2, &itemValue, &valueSize, &options);
    EXPECT_TRUE(found);
    EXPECT_STREQ(itemValue, "Beta");
}

// Test DeleteArrayItem removes an item
TEST_F(XMPUtilsTest_1986, DeleteArrayItemRemovesItem_1986) {
    const char* schemaNS = "http://purl.org/dc/elements/1.1/";
    const char* arrayName = "dc:subject";

    meta_.AppendArrayItem(schemaNS, arrayName, kXMP_PropArrayIsUnordered, "One", 0);
    meta_.AppendArrayItem(schemaNS, arrayName, kXMP_PropArrayIsUnordered, "Two", 0);

    EXPECT_EQ(meta_.CountArrayItems(schemaNS, arrayName), 2);

    meta_.DeleteArrayItem(schemaNS, arrayName, 1);
    EXPECT_EQ(meta_.CountArrayItems(schemaNS, arrayName), 1);
}

// Test GetProperty returns false for non-existent property
TEST_F(XMPUtilsTest_1986, GetPropertyReturnsFalseForNonExistent_1986) {
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* propName = "xmp:DoesNotExist";

    XMP_StringPtr resultValue = nullptr;
    XMP_StringLen resultLen = 0;
    XMP_OptionBits options = 0;
    bool found = meta_.GetProperty(schemaNS, propName, &resultValue, &resultLen, &options);

    EXPECT_FALSE(found);
}

// Test overwriting a property value
TEST_F(XMPUtilsTest_1986, OverwritePropertyValue_1986) {
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* propName = "xmp:CreatorTool";

    meta_.SetProperty(schemaNS, propName, "OldValue", 0);
    meta_.SetProperty(schemaNS, propName, "NewValue", 0);

    XMP_StringPtr resultValue = nullptr;
    XMP_StringLen resultLen = 0;
    XMP_OptionBits options = 0;
    bool found = meta_.GetProperty(schemaNS, propName, &resultValue, &resultLen, &options);

    EXPECT_TRUE(found);
    EXPECT_STREQ(resultValue, "NewValue");
}

// Test setting property with empty string value
TEST_F(XMPUtilsTest_1986, SetPropertyEmptyStringValue_1986) {
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* propName = "xmp:CreatorTool";

    meta_.SetProperty(schemaNS, propName, "", 0);

    XMP_StringPtr resultValue = nullptr;
    XMP_StringLen resultLen = 0;
    XMP_OptionBits options = 0;
    bool found = meta_.GetProperty(schemaNS, propName, &resultValue, &resultLen, &options);

    EXPECT_TRUE(found);
    EXPECT_STREQ(resultValue, "");
}

// Test multiple properties in different schemas
TEST_F(XMPUtilsTest_1986, MultiplePropertiesDifferentSchemas_1986) {
    const char* xmpNS = "http://ns.adobe.com/xap/1.0/";
    const char* dcNS = "http://purl.org/dc/elements/1.1/";

    meta_.SetProperty(xmpNS, "xmp:CreatorTool", "ToolA", 0);
    meta_.SetProperty(dcNS, "dc:format", "image/jpeg", 0);

    EXPECT_TRUE(meta_.DoesPropertyExist(xmpNS, "xmp:CreatorTool"));
    EXPECT_TRUE(meta_.DoesPropertyExist(dcNS, "dc:format"));

    // Delete one, other should remain
    meta_.DeleteProperty(xmpNS, "xmp:CreatorTool");
    EXPECT_FALSE(meta_.DoesPropertyExist(xmpNS, "xmp:CreatorTool"));
    EXPECT_TRUE(meta_.DoesPropertyExist(dcNS, "dc:format"));
}

// Test SetProperty_Bool with false
TEST_F(XMPUtilsTest_1986, SetAndGetBoolPropertyFalse_1986) {
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* propName = "xmp:BoolPropFalse";

    meta_.SetProperty_Bool(schemaNS, propName, false, 0);

    bool propValue = true;
    XMP_OptionBits options = 0;
    bool found = meta_.GetProperty_Bool(schemaNS, propName, &propValue, &options);

    EXPECT_TRUE(found);
    EXPECT_FALSE(propValue);
}

// Test SetProperty_Int with negative value
TEST_F(XMPUtilsTest_1986, SetAndGetNegativeIntProperty_1986) {
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* propName = "xmp:NegInt";

    meta_.SetProperty_Int(schemaNS, propName, -100, 0);

    XMP_Int32 propValue = 0;
    XMP_OptionBits options = 0;
    bool found = meta_.GetProperty_Int(schemaNS, propName, &propValue, &options);

    EXPECT_TRUE(found);
    EXPECT_EQ(propValue, -100);
}

// Test SetProperty_Int with zero
TEST_F(XMPUtilsTest_1986, SetAndGetZeroIntProperty_1986) {
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* propName = "xmp:ZeroInt";

    meta_.SetProperty_Int(schemaNS, propName, 0, 0);

    XMP_Int32 propValue = 999;
    XMP_OptionBits options = 0;
    bool found = meta_.GetProperty_Int(schemaNS, propName, &propValue, &options);

    EXPECT_TRUE(found);
    EXPECT_EQ(propValue, 0);
}

// Test Sort doesn't lose properties
TEST_F(XMPUtilsTest_1986, SortPreservesProperties_1986) {
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";

    meta_.SetProperty(schemaNS, "xmp:CreatorTool", "Tool", 0);
    meta_.SetProperty(schemaNS, "xmp:CreateDate", "2023-01-01", 0);

    meta_.Sort();

    EXPECT_TRUE(meta_.DoesPropertyExist(schemaNS, "xmp:CreatorTool"));
    EXPECT_TRUE(meta_.DoesPropertyExist(schemaNS, "xmp:CreateDate"));
}

// Test CountArrayItems on empty/non-existent array
TEST_F(XMPUtilsTest_1986, CountArrayItemsNonExistent_1986) {
    const char* schemaNS = "http://purl.org/dc/elements/1.1/";
    const char* arrayName = "dc:subject";

    XMP_Index count = meta_.CountArrayItems(schemaNS, arrayName);
    EXPECT_EQ(count, 0);
}

// Test struct field set and get
TEST_F(XMPUtilsTest_1986, SetAndGetStructField_1986) {
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* structName = "xmp:TestStruct";
    const char* fieldNS = "http://ns.adobe.com/xap/1.0/";
    const char* fieldName = "xmp:FieldOne";

    meta_.SetStructField(schemaNS, structName, fieldNS, fieldName, "FieldValue", 0);

    XMP_StringPtr fieldValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;
    bool found = meta_.GetStructField(schemaNS, structName, fieldNS, fieldName, &fieldValue, &valueSize, &options);

    EXPECT_TRUE(found);
    EXPECT_STREQ(fieldValue, "FieldValue");
}

// Test DoesStructFieldExist
TEST_F(XMPUtilsTest_1986, DoesStructFieldExist_1986) {
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* structName = "xmp:TestStruct";
    const char* fieldNS = "http://ns.adobe.com/xap/1.0/";
    const char* fieldName = "xmp:FieldOne";

    EXPECT_FALSE(meta_.DoesStructFieldExist(schemaNS, structName, fieldNS, fieldName));

    meta_.SetStructField(schemaNS, structName, fieldNS, fieldName, "Value", 0);
    EXPECT_TRUE(meta_.DoesStructFieldExist(schemaNS, structName, fieldNS, fieldName));
}

// Test DeleteStructField
TEST_F(XMPUtilsTest_1986, DeleteStructField_1986) {
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* structName = "xmp:TestStruct";
    const char* fieldNS = "http://ns.adobe.com/xap/1.0/";
    const char* fieldName = "xmp:FieldOne";

    meta_.SetStructField(schemaNS, structName, fieldNS, fieldName, "Value", 0);
    EXPECT_TRUE(meta_.DoesStructFieldExist(schemaNS, structName, fieldNS, fieldName));

    meta_.DeleteStructField(schemaNS, structName, fieldNS, fieldName);
    EXPECT_FALSE(meta_.DoesStructFieldExist(schemaNS, structName, fieldNS, fieldName));
}

// Test SetProperty_Float with zero
TEST_F(XMPUtilsTest_1986, SetAndGetZeroFloatProperty_1986) {
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* propName = "xmp:ZeroFloat";

    meta_.SetProperty_Float(schemaNS, propName, 0.0, 0);

    double propValue = 999.0;
    XMP_OptionBits options = 0;
    bool found = meta_.GetProperty_Float(schemaNS, propName, &propValue, &options);

    EXPECT_TRUE(found);
    EXPECT_DOUBLE_EQ(propValue, 0.0);
}

// Test SetProperty_Float with negative value
TEST_F(XMPUtilsTest_1986, SetAndGetNegativeFloatProperty_1986) {
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* propName = "xmp:NegFloat";

    meta_.SetProperty_Float(schemaNS, propName, -2.5, 0);

    double propValue = 0.0;
    XMP_OptionBits options = 0;
    bool found = meta_.GetProperty_Float(schemaNS, propName, &propValue, &options);

    EXPECT_TRUE(found);
    EXPECT_NEAR(propValue, -2.5, 0.001);
}

// Test GetProperty with null output pointers (should still return found status)
TEST_F(XMPUtilsTest_1986, GetPropertyWithNullOutputs_1986) {
    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* propName = "xmp:CreatorTool";

    meta_.SetProperty(schemaNS, propName, "TestTool", 0);

    bool found = meta_.GetProperty(schemaNS, propName, nullptr, nullptr, nullptr);
    EXPECT_TRUE(found);
}

// Test setting localized text
TEST_F(XMPUtilsTest_1986, SetAndGetLocalizedText_1986) {
    const char* schemaNS = "http://purl.org/dc/elements/1.1/";
    const char* altTextName = "dc:title";

    meta_.SetLocalizedText(schemaNS, altTextName, "", "x-default", "Test Title", 0);

    XMP_StringPtr actualLang = nullptr;
    XMP_StringLen langSize = 0;
    XMP_StringPtr itemValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    bool found = meta_.GetLocalizedText(schemaNS, altTextName, "", "x-default",
                                         &actualLang, &langSize, &itemValue, &valueSize, &options);

    EXPECT_TRUE(found);
    EXPECT_STREQ(itemValue, "Test Title");
}
