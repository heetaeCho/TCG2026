#include <gtest/gtest.h>

#define XMP_INCLUDE_XMPFILES 0
#include "XMP.hpp"
#include "XMP.incl_cpp"

class TXMPMetaTest_1276 : public ::testing::Test {
protected:
    void SetUp() override {
        SXMPMeta::Initialize();
    }

    void TearDown() override {
        SXMPMeta::Terminate();
    }
};

// Test that default construction creates a valid object
TEST_F(TXMPMetaTest_1276, DefaultConstructorCreatesValidObject_1276) {
    SXMPMeta meta;
    // A default-constructed object should exist without throwing
    EXPECT_NO_THROW(SXMPMeta());
}

// Test that default constructed meta has no properties
TEST_F(TXMPMetaTest_1276, DefaultConstructorCreatesEmptyMeta_1276) {
    SXMPMeta meta;
    std::string value;
    // Should not find any property in a freshly constructed object
    bool found = meta.GetProperty("http://ns.adobe.com/xap/1.0/", "CreatorTool", &value, nullptr);
    EXPECT_FALSE(found);
}

// Test that multiple default constructions create independent objects
TEST_F(TXMPMetaTest_1276, MultipleDefaultConstructionsAreIndependent_1276) {
    SXMPMeta meta1;
    SXMPMeta meta2;

    meta1.SetProperty("http://ns.adobe.com/xap/1.0/", "CreatorTool", "TestTool");

    std::string value;
    bool found1 = meta1.GetProperty("http://ns.adobe.com/xap/1.0/", "CreatorTool", &value, nullptr);
    EXPECT_TRUE(found1);
    EXPECT_EQ(value, "TestTool");

    // meta2 should not have the property set on meta1
    bool found2 = meta2.GetProperty("http://ns.adobe.com/xap/1.0/", "CreatorTool", &value, nullptr);
    EXPECT_FALSE(found2);
}

// Test that default constructed object can serialize to empty/minimal XMP
TEST_F(TXMPMetaTest_1276, DefaultConstructorCanSerialize_1276) {
    SXMPMeta meta;
    std::string xmpPacket;
    EXPECT_NO_THROW(meta.SerializeToBuffer(&xmpPacket));
    // The serialized output should be a non-empty string (at minimum contains XML header)
    EXPECT_FALSE(xmpPacket.empty());
}

// Test that default constructed object can have properties set and retrieved
TEST_F(TXMPMetaTest_1276, DefaultConstructorAllowsSetAndGet_1276) {
    SXMPMeta meta;
    meta.SetProperty("http://purl.org/dc/elements/1.1/", "title", "Test Title");

    std::string value;
    bool found = meta.GetProperty("http://purl.org/dc/elements/1.1/", "title", &value, nullptr);
    EXPECT_TRUE(found);
    EXPECT_EQ(value, "Test Title");
}

// Test that copy of default-constructed object works
TEST_F(TXMPMetaTest_1276, CopyConstructorFromDefault_1276) {
    SXMPMeta meta1;
    meta1.SetProperty("http://ns.adobe.com/xap/1.0/", "CreatorTool", "CopyTest");

    SXMPMeta meta2(meta1);
    std::string value;
    bool found = meta2.GetProperty("http://ns.adobe.com/xap/1.0/", "CreatorTool", &value, nullptr);
    EXPECT_TRUE(found);
    EXPECT_EQ(value, "CopyTest");
}

// Test that CountArrayItems returns 0 for empty default constructed meta
TEST_F(TXMPMetaTest_1276, DefaultConstructorCountArrayItemsIsZero_1276) {
    SXMPMeta meta;
    XMP_Index count = meta.CountArrayItems("http://purl.org/dc/elements/1.1/", "subject");
    EXPECT_EQ(count, 0);
}

// Test constructing many objects rapidly (stress/boundary)
TEST_F(TXMPMetaTest_1276, MultipleRapidDefaultConstructions_1276) {
    for (int i = 0; i < 100; ++i) {
        SXMPMeta meta;
        EXPECT_NO_THROW(meta.SetProperty("http://ns.adobe.com/xap/1.0/", "CreatorTool", "StressTest"));
    }
}
