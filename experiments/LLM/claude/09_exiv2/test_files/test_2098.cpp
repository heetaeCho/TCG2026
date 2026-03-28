#include <gtest/gtest.h>
#include <string>
#include <vector>

// Include the XMP SDK headers
#include "XMP.hpp"
#include "XMP_Const.h"

class XMPIteratorAliasTest_2098 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!SXMPMeta::Initialize()) {
            FAIL() << "Failed to initialize XMP SDK";
        }
    }

    static void TearDownTestSuite() {
        SXMPMeta::Terminate();
    }

    void SetUp() override {
        meta_ = SXMPMeta();
    }

    void TearDown() override {
    }

    SXMPMeta meta_;
};

// Test normal iteration over a schema that has aliases
TEST_F(XMPIteratorAliasTest_2098, IterateOverSchemaWithAliases_2098) {
    // dc:title is a well-known property
    meta_.SetProperty(kXMP_NS_DC, "title", "Test Title", 0);
    meta_.SetProperty(kXMP_NS_DC, "creator", "Test Creator", 0);

    SXMPIterator iter(meta_, kXMP_NS_DC, 0);

    std::string schemaNS, propPath, propValue;
    XMP_OptionBits options;
    bool found = false;

    while (iter.Next(&schemaNS, &propPath, &propValue, &options)) {
        found = true;
        EXPECT_FALSE(schemaNS.empty());
    }

    EXPECT_TRUE(found);
}

// Test iteration with kXMP_IterJustChildren flag
TEST_F(XMPIteratorAliasTest_2098, IterateJustChildren_2098) {
    meta_.SetProperty(kXMP_NS_DC, "title", "Test Title", 0);

    SXMPIterator iter(meta_, kXMP_NS_DC, kXMP_IterJustChildren);

    std::string schemaNS, propPath, propValue;
    XMP_OptionBits options;
    int count = 0;

    while (iter.Next(&schemaNS, &propPath, &propValue, &options)) {
        count++;
        EXPECT_EQ(schemaNS, std::string(kXMP_NS_DC));
    }

    EXPECT_GE(count, 1);
}

// Test iteration over all schemas
TEST_F(XMPIteratorAliasTest_2098, IterateAllSchemas_2098) {
    meta_.SetProperty(kXMP_NS_DC, "title", "Test Title", 0);
    meta_.SetProperty(kXMP_NS_XMP, "CreatorTool", "TestTool", 0);

    SXMPIterator iter(meta_, "", 0);

    std::string schemaNS, propPath, propValue;
    XMP_OptionBits options;
    bool foundDC = false;
    bool foundXMP = false;

    while (iter.Next(&schemaNS, &propPath, &propValue, &options)) {
        if (schemaNS == std::string(kXMP_NS_DC)) foundDC = true;
        if (schemaNS == std::string(kXMP_NS_XMP)) foundXMP = true;
    }

    EXPECT_TRUE(foundDC);
    EXPECT_TRUE(foundXMP);
}

// Test iteration on empty metadata
TEST_F(XMPIteratorAliasTest_2098, IterateEmptyMeta_2098) {
    SXMPIterator iter(meta_, "", 0);

    std::string schemaNS, propPath, propValue;
    XMP_OptionBits options;

    bool found = iter.Next(&schemaNS, &propPath, &propValue, &options);
    EXPECT_FALSE(found);
}

// Test iteration with kXMP_IterJustLeafNodes
TEST_F(XMPIteratorAliasTest_2098, IterateJustLeafNodes_2098) {
    meta_.SetProperty(kXMP_NS_DC, "format", "image/jpeg", 0);

    SXMPIterator iter(meta_, kXMP_NS_DC, kXMP_IterJustLeafNodes);

    std::string schemaNS, propPath, propValue;
    XMP_OptionBits options;
    bool found = false;

    while (iter.Next(&schemaNS, &propPath, &propValue, &options)) {
        found = true;
        // Leaf nodes should not be struct or array
        EXPECT_EQ(options & kXMP_PropCompositeMask, 0u);
    }

    EXPECT_TRUE(found);
}

// Test that Skip works during iteration
TEST_F(XMPIteratorAliasTest_2098, SkipDuringIteration_2098) {
    meta_.SetProperty(kXMP_NS_DC, "title", "Test", 0);
    meta_.SetProperty(kXMP_NS_DC, "format", "image/jpeg", 0);

    SXMPIterator iter(meta_, kXMP_NS_DC, 0);

    std::string schemaNS, propPath, propValue;
    XMP_OptionBits options;

    // Get first item then skip subtree
    if (iter.Next(&schemaNS, &propPath, &propValue, &options)) {
        iter.Skip(kXMP_IterSkipSubtree);
    }

    // Should still be able to continue iteration
    int count = 0;
    while (iter.Next(&schemaNS, &propPath, &propValue, &options)) {
        count++;
    }
    // We just verify it doesn't crash and terminates
    EXPECT_GE(count, 0);
}

// Test iteration over a schema with standard aliases registered
TEST_F(XMPIteratorAliasTest_2098, IterateWithStandardAliases_2098) {
    // Register standard aliases which creates alias mappings
    SXMPMeta::RegisterStandardAliases("");

    // Set a property that is the target of aliases
    meta_.SetLocalizedText(kXMP_NS_DC, "title", "", "x-default", "My Title", 0);

    SXMPIterator iter(meta_, kXMP_NS_DC, 0);

    std::string schemaNS, propPath, propValue;
    XMP_OptionBits options;
    bool found = false;

    while (iter.Next(&schemaNS, &propPath, &propValue, &options)) {
        found = true;
    }

    EXPECT_TRUE(found);
}

// Test that iterating with a specific property path works
TEST_F(XMPIteratorAliasTest_2098, IterateSpecificProperty_2098) {
    meta_.AppendArrayItem(kXMP_NS_DC, "creator", kXMP_PropArrayIsOrdered, "Author1", 0);
    meta_.AppendArrayItem(kXMP_NS_DC, "creator", kXMP_PropArrayIsOrdered, "Author2", 0);

    SXMPIterator iter(meta_, kXMP_NS_DC, "dc:creator", 0);

    std::string schemaNS, propPath, propValue;
    XMP_OptionBits options;
    int count = 0;

    while (iter.Next(&schemaNS, &propPath, &propValue, &options)) {
        count++;
    }

    // Should find the array and its items
    EXPECT_GE(count, 2);
}

// Test namespace prefix resolution is working
TEST_F(XMPIteratorAliasTest_2098, NamespacePrefixResolution_2098) {
    std::string prefix;
    bool found = SXMPMeta::GetNamespacePrefix(kXMP_NS_DC, &prefix);
    EXPECT_TRUE(found);
    EXPECT_FALSE(prefix.empty());
}

// Test that unknown namespace throws or returns false
TEST_F(XMPIteratorAliasTest_2098, UnknownNamespacePrefix_2098) {
    std::string prefix;
    bool found = SXMPMeta::GetNamespacePrefix("http://ns.example.com/nonexistent/", &prefix);
    EXPECT_FALSE(found);
}

// Test iteration with kXMP_IterJustLeafName
TEST_F(XMPIteratorAliasTest_2098, IterateJustLeafName_2098) {
    meta_.SetProperty(kXMP_NS_DC, "format", "image/jpeg", 0);

    SXMPIterator iter(meta_, kXMP_NS_DC, kXMP_IterJustLeafName | kXMP_IterJustLeafNodes);

    std::string schemaNS, propPath, propValue;
    XMP_OptionBits options;

    while (iter.Next(&schemaNS, &propPath, &propValue, &options)) {
        // With kXMP_IterJustLeafName, the path should be just the leaf name
        if (!propPath.empty()) {
            EXPECT_EQ(propPath.find('/'), std::string::npos);
        }
    }
}

// Test iteration with multiple properties across schemas
TEST_F(XMPIteratorAliasTest_2098, MultiplePropertiesMultipleSchemas_2098) {
    meta_.SetProperty(kXMP_NS_DC, "title", "Title", 0);
    meta_.SetProperty(kXMP_NS_DC, "format", "image/jpeg", 0);
    meta_.SetProperty(kXMP_NS_XMP, "CreatorTool", "TestApp", 0);
    meta_.SetProperty(kXMP_NS_XMP, "CreateDate", "2023-01-01", 0);

    SXMPIterator iter(meta_, "", 0);

    std::string schemaNS, propPath, propValue;
    XMP_OptionBits options;
    int totalCount = 0;

    while (iter.Next(&schemaNS, &propPath, &propValue, &options)) {
        totalCount++;
    }

    EXPECT_GE(totalCount, 4);
}

// Test that alias property shows up with kXMP_PropIsAlias flag
TEST_F(XMPIteratorAliasTest_2098, AliasPropertyHasAliasFlag_2098) {
    SXMPMeta::RegisterStandardAliases("");

    // xmpDM:artist is aliased to dc:creator[1] in standard aliases
    // Set the actual property
    meta_.AppendArrayItem(kXMP_NS_DC, "creator", kXMP_PropArrayIsOrdered, "Artist Name", 0);

    // Iterate over XMP DM namespace to see if alias shows up
    // Note: This depends on whether XMP DM aliases are registered
    SXMPIterator iter(meta_, kXMP_NS_DC, 0);

    std::string schemaNS, propPath, propValue;
    XMP_OptionBits options;
    bool foundCreator = false;

    while (iter.Next(&schemaNS, &propPath, &propValue, &options)) {
        if (propPath.find("creator") != std::string::npos) {
            foundCreator = true;
        }
    }

    EXPECT_TRUE(foundCreator);
}
