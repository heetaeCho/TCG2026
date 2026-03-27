#include <gtest/gtest.h>
#include <cstring>  // for strcmp

// Assuming the getTypeMapEntry function and TypeMapEntry structure are declared as mentioned in the prompt.
extern const TypeMapEntry typeMap[];

static inline const TypeMapEntry *getTypeMapEntry(const char *name);

class StructElementTest_1783 : public ::testing::Test {};

// Normal Operation Tests
TEST_F(StructElementTest_1783, GetTypeMapEntryValidName_1783) {
    const char *validName = "Document";
    const TypeMapEntry *entry = getTypeMapEntry(validName);
    
    ASSERT_NE(entry, nullptr);  // Ensure the entry is found
    EXPECT_EQ(entry->name, validName);  // Ensure the name matches
    EXPECT_EQ(entry->type, StructElement::Document);  // Ensure the type is correct
}

TEST_F(StructElementTest_1783, GetTypeMapEntryInvalidName_1783) {
    const char *invalidName = "NonExistentElement";
    const TypeMapEntry *entry = getTypeMapEntry(invalidName);
    
    EXPECT_EQ(entry, nullptr);  // Ensure no entry is found for an invalid name
}

// Boundary Condition Tests
TEST_F(StructElementTest_1783, GetTypeMapEntryFirstElement_1783) {
    const char *firstElementName = "Document";  // First element in the typeMap
    const TypeMapEntry *entry = getTypeMapEntry(firstElementName);
    
    ASSERT_NE(entry, nullptr);  // Ensure the entry is found
    EXPECT_EQ(entry->name, firstElementName);  // Ensure the name matches
}

TEST_F(StructElementTest_1783, GetTypeMapEntryLastElement_1783) {
    const char *lastElementName = "TOCI";  // Last element in the typeMap
    const TypeMapEntry *entry = getTypeMapEntry(lastElementName);
    
    ASSERT_NE(entry, nullptr);  // Ensure the entry is found
    EXPECT_EQ(entry->name, lastElementName);  // Ensure the name matches
}

// Exceptional/Error Case Tests
TEST_F(StructElementTest_1783, GetTypeMapEntryNullName_1783) {
    const TypeMapEntry *entry = getTypeMapEntry(nullptr);
    
    EXPECT_EQ(entry, nullptr);  // Ensure no entry is found for a nullptr input
}

TEST_F(StructElementTest_1783, GetTypeMapEntryEmptyString_1783) {
    const char *emptyName = "";
    const TypeMapEntry *entry = getTypeMapEntry(emptyName);
    
    EXPECT_EQ(entry, nullptr);  // Ensure no entry is found for an empty string input
}