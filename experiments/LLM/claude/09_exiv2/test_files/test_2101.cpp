#include <gtest/gtest.h>
#include <string>

// Include necessary headers from the project
#define TXMP_STRING_TYPE std::string
#include "public/include/XMP.hpp"
#include "XMPIterator.hpp"

// Since SetCurrSchema is static inline in the .cpp file, we need to include it
// or replicate the declaration for testing purposes.
// We include the cpp to get access to the static function.
#include "XMPIterator.cpp"

class SetCurrSchemaTest_2101 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that SetCurrSchema sets the currSchema field correctly with a normal string
TEST_F(SetCurrSchemaTest_2101, SetsCurrSchemaWithNormalString_2101) {
    IterInfo info;
    XMP_VarString schemaName = "http://ns.adobe.com/xap/1.0/";
    SetCurrSchema(info, schemaName);
    EXPECT_EQ(info.currSchema, "http://ns.adobe.com/xap/1.0/");
}

// Test that SetCurrSchema sets the currSchema field with an empty string
TEST_F(SetCurrSchemaTest_2101, SetsCurrSchemaWithEmptyString_2101) {
    IterInfo info;
    XMP_VarString schemaName = "";
    SetCurrSchema(info, schemaName);
    EXPECT_EQ(info.currSchema, "");
}

// Test that SetCurrSchema overwrites a previously set schema
TEST_F(SetCurrSchemaTest_2101, OverwritesPreviousSchema_2101) {
    IterInfo info;
    XMP_VarString schemaName1 = "http://ns.adobe.com/xap/1.0/";
    SetCurrSchema(info, schemaName1);
    EXPECT_EQ(info.currSchema, "http://ns.adobe.com/xap/1.0/");

    XMP_VarString schemaName2 = "http://purl.org/dc/elements/1.1/";
    SetCurrSchema(info, schemaName2);
    EXPECT_EQ(info.currSchema, "http://purl.org/dc/elements/1.1/");
}

// Test that SetCurrSchema handles a long schema name
TEST_F(SetCurrSchemaTest_2101, HandlesLongSchemaName_2101) {
    IterInfo info;
    XMP_VarString schemaName(1000, 'a');
    SetCurrSchema(info, schemaName);
    EXPECT_EQ(info.currSchema, schemaName);
    EXPECT_EQ(info.currSchema.size(), 1000u);
}

// Test that SetCurrSchema handles special characters in schema name
TEST_F(SetCurrSchemaTest_2101, HandlesSpecialCharacters_2101) {
    IterInfo info;
    XMP_VarString schemaName = "http://example.com/ns?param=value&other=123#fragment";
    SetCurrSchema(info, schemaName);
    EXPECT_EQ(info.currSchema, schemaName);
}

// Test that SetCurrSchema does not modify the input string
TEST_F(SetCurrSchemaTest_2101, DoesNotModifyInputString_2101) {
    IterInfo info;
    XMP_VarString schemaName = "http://ns.adobe.com/xap/1.0/";
    XMP_VarString originalCopy = schemaName;
    SetCurrSchema(info, schemaName);
    EXPECT_EQ(schemaName, originalCopy);
}

// Test that SetCurrSchema with the same value multiple times is idempotent
TEST_F(SetCurrSchemaTest_2101, IdempotentWithSameValue_2101) {
    IterInfo info;
    XMP_VarString schemaName = "http://ns.adobe.com/xap/1.0/";
    SetCurrSchema(info, schemaName);
    SetCurrSchema(info, schemaName);
    SetCurrSchema(info, schemaName);
    EXPECT_EQ(info.currSchema, "http://ns.adobe.com/xap/1.0/");
}

// Test IterInfo default constructor initializes properly
TEST_F(SetCurrSchemaTest_2101, IterInfoDefaultConstructorInitialization_2101) {
    IterInfo info;
    EXPECT_EQ(info.xmpObj, nullptr);
    EXPECT_TRUE(info.currSchema.empty());
}

// Test that currSchema is independent copy from the input
TEST_F(SetCurrSchemaTest_2101, CurrSchemaIsIndependentCopy_2101) {
    IterInfo info;
    XMP_VarString schemaName = "http://ns.adobe.com/xap/1.0/";
    SetCurrSchema(info, schemaName);
    
    // Modify the original string
    schemaName = "modified";
    
    // info.currSchema should not be affected
    EXPECT_EQ(info.currSchema, "http://ns.adobe.com/xap/1.0/");
}

// Test setting currSchema to string with null characters embedded
TEST_F(SetCurrSchemaTest_2101, HandlesEmbeddedNullCharacters_2101) {
    IterInfo info;
    XMP_VarString schemaName("hello\0world", 11);
    SetCurrSchema(info, schemaName);
    EXPECT_EQ(info.currSchema.size(), 11u);
    EXPECT_EQ(info.currSchema, schemaName);
}
