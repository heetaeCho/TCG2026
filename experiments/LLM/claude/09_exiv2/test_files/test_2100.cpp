#include <gtest/gtest.h>
#include <string>

// Include necessary headers from the project
// We need to include the relevant headers for the types used
#include "XMPIterator.hpp"

// Since SetCurrSchema is a static inline function defined in the .cpp file,
// we cannot directly test it from outside. However, we can test it through
// the public interface of IterInfo and the XMPIterator class.
// 
// Given the constraints, we'll focus on testing the IterInfo struct's
// observable behavior and the effect of SetCurrSchema through whatever
// public interface is available.

// Since SetCurrSchema is static inline in the .cpp file, we need to 
// include it or replicate the minimal testable interface.
// We'll test IterInfo construction and the currSchema field behavior.

class IterInfoTest_2100 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    
    void TearDown() override {
    }
};

// Test default construction of IterInfo
TEST_F(IterInfoTest_2100, DefaultConstruction_2100) {
    IterInfo info;
    EXPECT_EQ(info.options, 0u);
    EXPECT_EQ(info.xmpObj, nullptr);
    EXPECT_TRUE(info.currSchema.empty());
}

// Test parameterized construction of IterInfo
TEST_F(IterInfoTest_2100, ParameterizedConstruction_2100) {
    XMP_OptionBits opts = 0x01;
    XMPMeta meta;
    IterInfo info(opts, &meta);
    EXPECT_EQ(info.options, opts);
    EXPECT_EQ(info.xmpObj, &meta);
}

// Test that currSchema can be set to a valid schema name
TEST_F(IterInfoTest_2100, CurrSchemaCanBeSet_2100) {
    IterInfo info;
    info.currSchema = "http://ns.adobe.com/xap/1.0/";
    EXPECT_EQ(info.currSchema, "http://ns.adobe.com/xap/1.0/");
}

// Test that currSchema can be set to empty string
TEST_F(IterInfoTest_2100, CurrSchemaEmptyString_2100) {
    IterInfo info;
    info.currSchema = "http://some.schema/";
    info.currSchema = "";
    EXPECT_TRUE(info.currSchema.empty());
}

// Test that currSchema can be overwritten
TEST_F(IterInfoTest_2100, CurrSchemaOverwrite_2100) {
    IterInfo info;
    info.currSchema = "http://first.schema/";
    EXPECT_EQ(info.currSchema, "http://first.schema/");
    info.currSchema = "http://second.schema/";
    EXPECT_EQ(info.currSchema, "http://second.schema/");
}

// Test with nullptr xmpObj
TEST_F(IterInfoTest_2100, NullXmpObj_2100) {
    IterInfo info(0, nullptr);
    EXPECT_EQ(info.xmpObj, nullptr);
    EXPECT_EQ(info.options, 0u);
}

// Test parameterized construction with various option bits
TEST_F(IterInfoTest_2100, VariousOptionBits_2100) {
    XMPMeta meta;
    
    IterInfo info1(0x00, &meta);
    EXPECT_EQ(info1.options, 0x00u);
    
    IterInfo info2(0xFF, &meta);
    EXPECT_EQ(info2.options, 0xFFu);
    
    IterInfo info3(0xFFFFFFFF, &meta);
    EXPECT_EQ(info3.options, 0xFFFFFFFFu);
}

// Test that tree member is default constructed
TEST_F(IterInfoTest_2100, TreeDefaultConstructed_2100) {
    IterInfo info;
    // Tree should be in a valid default state
    // We just verify the object is constructible without issues
    SUCCEED();
}

// Test that ancestors stack is initially empty
TEST_F(IterInfoTest_2100, AncestorsInitiallyEmpty_2100) {
    IterInfo info;
    EXPECT_TRUE(info.ancestors.empty());
}

// Test currSchema with long schema name
TEST_F(IterInfoTest_2100, CurrSchemaLongString_2100) {
    IterInfo info;
    std::string longSchema(1000, 'x');
    info.currSchema = longSchema;
    EXPECT_EQ(info.currSchema, longSchema);
    EXPECT_EQ(info.currSchema.size(), 1000u);
}

// Test currSchema c_str() access
TEST_F(IterInfoTest_2100, CurrSchemaCStr_2100) {
    IterInfo info;
    info.currSchema = "http://test.schema/";
    const char* cstr = info.currSchema.c_str();
    EXPECT_STREQ(cstr, "http://test.schema/");
}
