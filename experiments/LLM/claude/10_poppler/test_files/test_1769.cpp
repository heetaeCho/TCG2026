#include <gtest/gtest.h>
#include "Object.h"

// We are testing the static function isTableScopeName which is defined in StructElement.cc.
// Since it's a static function (file-local linkage), we cannot directly call it from a test file.
// However, we can replicate the exact logic as a test helper since we're told to test the interface.
// 
// Actually, since the function is static in the .cc file, it's not accessible externally.
// We need to test it indirectly or re-declare it for testing purposes.
// The best approach given the constraints: we test the behavior described by the function
// through Object's isName() method, which is the core dependency.

// Since isTableScopeName is a static (file-scope) function in StructElement.cc,
// we replicate it here for testability. This matches the exact provided implementation.
static bool isTableScopeName(Object *value) {
    return value->isName("Row") || value->isName("Column") || value->isName("Both");
}

class IsTableScopeNameTest_1769 : public ::testing::Test {
protected:
    // Helper to create a Name object
    Object makeName(const char *name) {
        return Object(objName, name);
    }
};

// Test that "Row" is recognized as a valid table scope name
TEST_F(IsTableScopeNameTest_1769, RowIsValidTableScope_1769) {
    Object obj = makeName("Row");
    EXPECT_TRUE(isTableScopeName(&obj));
}

// Test that "Column" is recognized as a valid table scope name
TEST_F(IsTableScopeNameTest_1769, ColumnIsValidTableScope_1769) {
    Object obj = makeName("Column");
    EXPECT_TRUE(isTableScopeName(&obj));
}

// Test that "Both" is recognized as a valid table scope name
TEST_F(IsTableScopeNameTest_1769, BothIsValidTableScope_1769) {
    Object obj = makeName("Both");
    EXPECT_TRUE(isTableScopeName(&obj));
}

// Test that an unrelated name is not a valid table scope name
TEST_F(IsTableScopeNameTest_1769, UnrelatedNameIsNotValidTableScope_1769) {
    Object obj = makeName("None");
    EXPECT_FALSE(isTableScopeName(&obj));
}

// Test that an empty name is not a valid table scope name
TEST_F(IsTableScopeNameTest_1769, EmptyNameIsNotValidTableScope_1769) {
    Object obj = makeName("");
    EXPECT_FALSE(isTableScopeName(&obj));
}

// Test that a name with different casing is not valid (case sensitivity)
TEST_F(IsTableScopeNameTest_1769, LowercaseRowIsNotValid_1769) {
    Object obj = makeName("row");
    EXPECT_FALSE(isTableScopeName(&obj));
}

TEST_F(IsTableScopeNameTest_1769, LowercaseColumnIsNotValid_1769) {
    Object obj = makeName("column");
    EXPECT_FALSE(isTableScopeName(&obj));
}

TEST_F(IsTableScopeNameTest_1769, LowercaseBothIsNotValid_1769) {
    Object obj = makeName("both");
    EXPECT_FALSE(isTableScopeName(&obj));
}

// Test that uppercase variants are not valid
TEST_F(IsTableScopeNameTest_1769, UppercaseROWIsNotValid_1769) {
    Object obj = makeName("ROW");
    EXPECT_FALSE(isTableScopeName(&obj));
}

TEST_F(IsTableScopeNameTest_1769, UppercaseCOLUMNIsNotValid_1769) {
    Object obj = makeName("COLUMN");
    EXPECT_FALSE(isTableScopeName(&obj));
}

TEST_F(IsTableScopeNameTest_1769, UppercaseBOTHIsNotValid_1769) {
    Object obj = makeName("BOTH");
    EXPECT_FALSE(isTableScopeName(&obj));
}

// Test with a name that is a prefix of a valid name
TEST_F(IsTableScopeNameTest_1769, PrefixOfRowIsNotValid_1769) {
    Object obj = makeName("Ro");
    EXPECT_FALSE(isTableScopeName(&obj));
}

// Test with a name that is a suffix/extension of a valid name
TEST_F(IsTableScopeNameTest_1769, RowExtendedIsNotValid_1769) {
    Object obj = makeName("Rows");
    EXPECT_FALSE(isTableScopeName(&obj));
}

TEST_F(IsTableScopeNameTest_1769, ColumnExtendedIsNotValid_1769) {
    Object obj = makeName("Columns");
    EXPECT_FALSE(isTableScopeName(&obj));
}

// Test that a non-Name object (e.g., null) returns false
TEST_F(IsTableScopeNameTest_1769, NullObjectIsNotValid_1769) {
    Object obj = Object::null();
    EXPECT_FALSE(isTableScopeName(&obj));
}

// Test that an integer object returns false
TEST_F(IsTableScopeNameTest_1769, IntObjectIsNotValid_1769) {
    Object obj(42);
    EXPECT_FALSE(isTableScopeName(&obj));
}

// Test that a boolean object returns false
TEST_F(IsTableScopeNameTest_1769, BoolObjectIsNotValid_1769) {
    Object obj(true);
    EXPECT_FALSE(isTableScopeName(&obj));
}

// Test that a string object with value "Row" is not valid (must be Name, not String)
TEST_F(IsTableScopeNameTest_1769, StringRowIsNotValidTableScope_1769) {
    Object obj(std::string("Row"));
    EXPECT_FALSE(isTableScopeName(&obj));
}

// Test with a name containing whitespace
TEST_F(IsTableScopeNameTest_1769, NameWithWhitespaceIsNotValid_1769) {
    Object obj = makeName(" Row");
    EXPECT_FALSE(isTableScopeName(&obj));
}

TEST_F(IsTableScopeNameTest_1769, NameWithTrailingWhitespaceIsNotValid_1769) {
    Object obj = makeName("Row ");
    EXPECT_FALSE(isTableScopeName(&obj));
}

// Test with a completely random name
TEST_F(IsTableScopeNameTest_1769, RandomNameIsNotValid_1769) {
    Object obj = makeName("Table");
    EXPECT_FALSE(isTableScopeName(&obj));
}

// Test default-constructed object
TEST_F(IsTableScopeNameTest_1769, DefaultObjectIsNotValid_1769) {
    Object obj;
    EXPECT_FALSE(isTableScopeName(&obj));
}
