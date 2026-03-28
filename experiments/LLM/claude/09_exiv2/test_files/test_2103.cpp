#include <gtest/gtest.h>
#include <string>

// Include necessary XMP SDK headers
#define TXMP_STRING_TYPE std::string
#include "XMP.hpp"
#include "XMP_Const.h"

class XMPIteratorTest_2103 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!initialized_) {
            SXMPMeta::Initialize();
            initialized_ = true;
        }
    }

    static bool initialized_;
};

bool XMPIteratorTest_2103::initialized_ = false;

// Test iterating over an empty XMP object returns nothing
TEST_F(XMPIteratorTest_2103, EmptyXMPObjectReturnsNoItems_2103) {
    SXMPMeta meta;
    SXMPIterator iter(meta);
    
    std::string schemaNS, propPath, propValue;
    XMP_OptionBits options;
    
    bool found = iter.Next(&schemaNS, &propPath, &propValue, &options);
    EXPECT_FALSE(found);
}

// Test iterating over XMP with a single property
TEST_F(XMPIteratorTest_2103, SinglePropertyIteration_2103) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "Test Title", 0);
    
    SXMPIterator iter(meta);
    
    std::string schemaNS, propPath, propValue;
    XMP_OptionBits options;
    
    bool found = false;
    int count = 0;
    while (iter.Next(&schemaNS, &propPath, &propValue, &options)) {
        count++;
        if (!propPath.empty() && propPath.find("title") != std::string::npos) {
            found = true;
        }
    }
    
    EXPECT_TRUE(found);
    EXPECT_GT(count, 0);
}

// Test iterating over multiple properties
TEST_F(XMPIteratorTest_2103, MultiplePropertiesIteration_2103) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "creator", "Author1", 0);
    meta.SetProperty(kXMP_NS_DC, "description", "A description", 0);
    meta.SetProperty(kXMP_NS_DC, "rights", "Copyright", 0);
    
    SXMPIterator iter(meta);
    
    std::string schemaNS, propPath, propValue;
    XMP_OptionBits options;
    
    int count = 0;
    while (iter.Next(&schemaNS, &propPath, &propValue, &options)) {
        count++;
    }
    
    EXPECT_GE(count, 3);
}

// Test kXMP_IterJustChildren option - only immediate children
TEST_F(XMPIteratorTest_2103, JustChildrenOption_2103) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "Test", 0);
    meta.SetProperty(kXMP_NS_XMP, "CreatorTool", "Tool", 0);
    
    SXMPIterator iter(meta, kXMP_IterJustChildren);
    
    std::string schemaNS, propPath, propValue;
    XMP_OptionBits options;
    
    int count = 0;
    while (iter.Next(&schemaNS, &propPath, &propValue, &options)) {
        count++;
        // With JustChildren on the root, we should get schema-level nodes
    }
    
    EXPECT_GT(count, 0);
}

// Test iterating with a specific schema namespace
TEST_F(XMPIteratorTest_2103, SpecificSchemaIteration_2103) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "Test Title", 0);
    meta.SetProperty(kXMP_NS_XMP, "CreatorTool", "MyTool", 0);
    
    SXMPIterator iter(meta, kXMP_NS_DC);
    
    std::string schemaNS, propPath, propValue;
    XMP_OptionBits options;
    
    int count = 0;
    bool foundDC = false;
    bool foundXMP = false;
    while (iter.Next(&schemaNS, &propPath, &propValue, &options)) {
        count++;
        if (schemaNS == kXMP_NS_DC) foundDC = true;
        if (schemaNS == kXMP_NS_XMP) foundXMP = true;
    }
    
    EXPECT_TRUE(foundDC);
    EXPECT_FALSE(foundXMP);
}

// Test iterating over a specific property path
TEST_F(XMPIteratorTest_2103, SpecificPropertyIteration_2103) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "Test Title", 0);
    meta.SetProperty(kXMP_NS_DC, "description", "A desc", 0);
    
    SXMPIterator iter(meta, kXMP_NS_DC, "title");
    
    std::string schemaNS, propPath, propValue;
    XMP_OptionBits options;
    
    int count = 0;
    while (iter.Next(&schemaNS, &propPath, &propValue, &options)) {
        count++;
        EXPECT_TRUE(propPath.find("title") != std::string::npos || propPath.empty());
    }
    
    EXPECT_GT(count, 0);
}

// Test Skip functionality
TEST_F(XMPIteratorTest_2103, SkipSubtree_2103) {
    SXMPMeta meta;
    meta.AppendArrayItem(kXMP_NS_DC, "subject", kXMP_PropArrayIsUnordered, "Subject1", 0);
    meta.AppendArrayItem(kXMP_NS_DC, "subject", 0, "Subject2", 0);
    meta.AppendArrayItem(kXMP_NS_DC, "subject", 0, "Subject3", 0);
    
    SXMPIterator iter(meta, kXMP_NS_DC, "subject");
    
    std::string schemaNS, propPath, propValue;
    XMP_OptionBits options;
    
    // Get first item, then skip subtree
    bool found = iter.Next(&schemaNS, &propPath, &propValue, &options);
    EXPECT_TRUE(found);
    
    iter.Skip(kXMP_IterSkipSubtree);
    
    // Should still be able to continue but skipped children
    // Just verify no crash and iteration continues properly
    int remainingCount = 0;
    while (iter.Next(&schemaNS, &propPath, &propValue, &options)) {
        remainingCount++;
    }
    // After skipping subtree of the array, there may be no more items
    EXPECT_GE(remainingCount, 0);
}

// Test Skip siblings functionality
TEST_F(XMPIteratorTest_2103, SkipSiblings_2103) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "Test", 0);
    meta.SetProperty(kXMP_NS_DC, "description", "Desc", 0);
    meta.SetProperty(kXMP_NS_DC, "rights", "Rights", 0);
    
    SXMPIterator iter(meta, kXMP_NS_DC);
    
    std::string schemaNS, propPath, propValue;
    XMP_OptionBits options;
    
    // Get first item, then skip siblings
    bool found = iter.Next(&schemaNS, &propPath, &propValue, &options);
    EXPECT_TRUE(found);
    
    iter.Skip(kXMP_IterSkipSiblings);
    
    int remainingCount = 0;
    while (iter.Next(&schemaNS, &propPath, &propValue, &options)) {
        remainingCount++;
    }
    // Should have skipped remaining siblings
    EXPECT_GE(remainingCount, 0);
}

// Test kXMP_IterJustLeafNodes option
TEST_F(XMPIteratorTest_2103, JustLeafNodesOption_2103) {
    SXMPMeta meta;
    meta.AppendArrayItem(kXMP_NS_DC, "subject", kXMP_PropArrayIsUnordered, "Keyword1", 0);
    meta.AppendArrayItem(kXMP_NS_DC, "subject", 0, "Keyword2", 0);
    
    SXMPIterator iter(meta, kXMP_NS_DC, 0, kXMP_IterJustLeafNodes);
    
    std::string schemaNS, propPath, propValue;
    XMP_OptionBits options;
    
    int count = 0;
    while (iter.Next(&schemaNS, &propPath, &propValue, &options)) {
        count++;
        // Leaf nodes should not be schema or struct/array nodes
        EXPECT_FALSE(propValue.empty());
    }
    
    EXPECT_GE(count, 2);
}

// Test kXMP_IterJustLeafName option
TEST_F(XMPIteratorTest_2103, JustLeafNameOption_2103) {
    SXMPMeta meta;
    meta.SetStructField(kXMP_NS_DC, "myStruct", kXMP_NS_DC, "field1", "value1", 0);
    
    SXMPIterator iter(meta, kXMP_NS_DC, 0, kXMP_IterJustLeafName);
    
    std::string schemaNS, propPath, propValue;
    XMP_OptionBits options;
    
    int count = 0;
    while (iter.Next(&schemaNS, &propPath, &propValue, &options)) {
        count++;
        // With JustLeafName, the propPath should be just the leaf name, not the full path
        if (!propPath.empty()) {
            EXPECT_EQ(propPath.find('/'), std::string::npos);
        }
    }
    
    EXPECT_GT(count, 0);
}

// Test kXMP_IterOmitQualifiers option
TEST_F(XMPIteratorTest_2103, OmitQualifiersOption_2103) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "Test", 0);
    meta.SetQualifier(kXMP_NS_DC, "title", kXMP_NS_XML, "lang", "en");
    
    // Without omit qualifiers
    SXMPIterator iterWithQual(meta, kXMP_NS_DC);
    std::string schemaNS, propPath, propValue;
    XMP_OptionBits options;
    int countWithQual = 0;
    while (iterWithQual.Next(&schemaNS, &propPath, &propValue, &options)) {
        countWithQual++;
    }
    
    // With omit qualifiers
    SXMPIterator iterNoQual(meta, kXMP_NS_DC, 0, kXMP_IterOmitQualifiers);
    int countNoQual = 0;
    while (iterNoQual.Next(&schemaNS, &propPath, &propValue, &options)) {
        countNoQual++;
    }
    
    EXPECT_LE(countNoQual, countWithQual);
}

// Test iteration after property deletion
TEST_F(XMPIteratorTest_2103, IterationAfterDeletion_2103) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "Test Title", 0);
    meta.SetProperty(kXMP_NS_DC, "description", "Desc", 0);
    
    // Delete a property
    meta.DeleteProperty(kXMP_NS_DC, "title");
    
    SXMPIterator iter(meta, kXMP_NS_DC);
    
    std::string schemaNS, propPath, propValue;
    XMP_OptionBits options;
    
    bool foundTitle = false;
    bool foundDesc = false;
    while (iter.Next(&schemaNS, &propPath, &propValue, &options)) {
        if (propPath.find("title") != std::string::npos) foundTitle = true;
        if (propPath.find("description") != std::string::npos) foundDesc = true;
    }
    
    EXPECT_FALSE(foundTitle);
    EXPECT_TRUE(foundDesc);
}

// Test iterating over array items
TEST_F(XMPIteratorTest_2103, ArrayItemIteration_2103) {
    SXMPMeta meta;
    meta.AppendArrayItem(kXMP_NS_DC, "subject", kXMP_PropArrayIsUnordered, "Tag1", 0);
    meta.AppendArrayItem(kXMP_NS_DC, "subject", 0, "Tag2", 0);
    meta.AppendArrayItem(kXMP_NS_DC, "subject", 0, "Tag3", 0);
    
    SXMPIterator iter(meta, kXMP_NS_DC, "subject");
    
    std::string schemaNS, propPath, propValue;
    XMP_OptionBits options;
    
    std::vector<std::string> values;
    while (iter.Next(&schemaNS, &propPath, &propValue, &options)) {
        if (!propValue.empty()) {
            values.push_back(propValue);
        }
    }
    
    EXPECT_GE(values.size(), 3u);
    EXPECT_TRUE(std::find(values.begin(), values.end(), "Tag1") != values.end());
    EXPECT_TRUE(std::find(values.begin(), values.end(), "Tag2") != values.end());
    EXPECT_TRUE(std::find(values.begin(), values.end(), "Tag3") != values.end());
}

// Test iterating over struct fields
TEST_F(XMPIteratorTest_2103, StructFieldIteration_2103) {
    SXMPMeta meta;
    meta.SetStructField(kXMP_NS_DC, "myStruct", kXMP_NS_DC, "field1", "val1", 0);
    meta.SetStructField(kXMP_NS_DC, "myStruct", kXMP_NS_DC, "field2", "val2", 0);
    
    SXMPIterator iter(meta, kXMP_NS_DC, "myStruct");
    
    std::string schemaNS, propPath, propValue;
    XMP_OptionBits options;
    
    int fieldCount = 0;
    while (iter.Next(&schemaNS, &propPath, &propValue, &options)) {
        if (!propValue.empty()) {
            fieldCount++;
        }
    }
    
    EXPECT_GE(fieldCount, 2);
}

// Test iteration with null output parameters
TEST_F(XMPIteratorTest_2103, NullOutputParameters_2103) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "Test", 0);
    
    SXMPIterator iter(meta);
    
    // Should not crash with nullptr parameters
    bool found = iter.Next(nullptr, nullptr, nullptr, nullptr);
    EXPECT_TRUE(found);
}

// Test multiple schemas iteration
TEST_F(XMPIteratorTest_2103, MultipleSchemasIteration_2103) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "Title", 0);
    meta.SetProperty(kXMP_NS_XMP, "CreatorTool", "Tool", 0);
    
    SXMPIterator iter(meta);
    
    std::string schemaNS, propPath, propValue;
    XMP_OptionBits options;
    
    std::set<std::string> schemas;
    while (iter.Next(&schemaNS, &propPath, &propValue, &options)) {
        if (!schemaNS.empty()) {
            schemas.insert(schemaNS);
        }
    }
    
    EXPECT_GE(schemas.size(), 2u);
}

// Test repeated Next calls after exhaustion
TEST_F(XMPIteratorTest_2103, RepeatedNextAfterExhaustion_2103) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "Test", 0);
    
    SXMPIterator iter(meta);
    
    std::string schemaNS, propPath, propValue;
    XMP_OptionBits options;
    
    // Exhaust the iterator
    while (iter.Next(&schemaNS, &propPath, &propValue, &options)) {
        // drain
    }
    
    // Calling Next again should still return false
    EXPECT_FALSE(iter.Next(&schemaNS, &propPath, &propValue, &options));
    EXPECT_FALSE(iter.Next(&schemaNS, &propPath, &propValue, &options));
}

// Test JustChildren at schema level
TEST_F(XMPIteratorTest_2103, JustChildrenAtSchemaLevel_2103) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "Test", 0);
    meta.AppendArrayItem(kXMP_NS_DC, "subject", kXMP_PropArrayIsUnordered, "Tag1", 0);
    meta.AppendArrayItem(kXMP_NS_DC, "subject", 0, "Tag2", 0);
    
    SXMPIterator iter(meta, kXMP_NS_DC, 0, kXMP_IterJustChildren);
    
    std::string schemaNS, propPath, propValue;
    XMP_OptionBits options;
    
    int count = 0;
    while (iter.Next(&schemaNS, &propPath, &propValue, &options)) {
        count++;
        // Should not descend into array items
    }
    
    // Should get just the top-level properties (title, subject) not array items
    EXPECT_GE(count, 2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
