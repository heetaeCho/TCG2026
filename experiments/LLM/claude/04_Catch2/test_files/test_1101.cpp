#include <catch2/catch_tag_alias_autoregistrar.hpp>
#include <catch2/internal/catch_source_line_info.hpp>
#include <gtest/gtest.h>

class RegistrarForTagAliasesTest_1101 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that constructing a RegistrarForTagAliases with valid alias and tag does not throw
TEST_F(RegistrarForTagAliasesTest_1101, ConstructWithValidAliasAndTag_1101) {
    Catch::SourceLineInfo lineInfo("test_file.cpp", 42);
    // A valid tag alias in Catch2 starts with [@, and tag starts with [
    // The constructor should not throw - it catches all exceptions internally
    EXPECT_NO_THROW({
        Catch::RegistrarForTagAliases registrar("[@validAlias]", "[validTag]", lineInfo);
    });
}

// Test that constructing with empty alias does not crash (error handled internally)
TEST_F(RegistrarForTagAliasesTest_1101, ConstructWithEmptyAlias_1101) {
    Catch::SourceLineInfo lineInfo("test_file.cpp", 1);
    // Empty alias - may trigger registerStartupException internally
    EXPECT_NO_THROW({
        Catch::RegistrarForTagAliases registrar("", "[tag]", lineInfo);
    });
}

// Test that constructing with empty tag does not crash (error handled internally)
TEST_F(RegistrarForTagAliasesTest_1101, ConstructWithEmptyTag_1101) {
    Catch::SourceLineInfo lineInfo("test_file.cpp", 1);
    EXPECT_NO_THROW({
        Catch::RegistrarForTagAliases registrar("[@alias]", "", lineInfo);
    });
}

// Test that constructing with both empty alias and tag does not crash
TEST_F(RegistrarForTagAliasesTest_1101, ConstructWithBothEmpty_1101) {
    Catch::SourceLineInfo lineInfo("test_file.cpp", 0);
    EXPECT_NO_THROW({
        Catch::RegistrarForTagAliases registrar("", "", lineInfo);
    });
}

// Test construction with large line number
TEST_F(RegistrarForTagAliasesTest_1101, ConstructWithLargeLineNumber_1101) {
    Catch::SourceLineInfo lineInfo("test_file.cpp", std::numeric_limits<std::size_t>::max());
    EXPECT_NO_THROW({
        Catch::RegistrarForTagAliases registrar("[@bigLine]", "[tag]", lineInfo);
    });
}

// Test construction with zero line number
TEST_F(RegistrarForTagAliasesTest_1101, ConstructWithZeroLineNumber_1101) {
    Catch::SourceLineInfo lineInfo("test_file.cpp", 0);
    EXPECT_NO_THROW({
        Catch::RegistrarForTagAliases registrar("[@zeroLine]", "[tag]", lineInfo);
    });
}

// Test that registering duplicate alias does not crash (internally caught)
TEST_F(RegistrarForTagAliasesTest_1101, ConstructDuplicateAlias_1101) {
    Catch::SourceLineInfo lineInfo1("test_file.cpp", 10);
    Catch::SourceLineInfo lineInfo2("test_file.cpp", 20);
    
    EXPECT_NO_THROW({
        Catch::RegistrarForTagAliases registrar1("[@dupAlias]", "[tag1]", lineInfo1);
    });
    // Duplicate registration - should be caught internally via CATCH_CATCH_ALL
    EXPECT_NO_THROW({
        Catch::RegistrarForTagAliases registrar2("[@dupAlias]", "[tag2]", lineInfo2);
    });
}

// Test construction with special characters in alias and tag
TEST_F(RegistrarForTagAliasesTest_1101, ConstructWithSpecialCharacters_1101) {
    Catch::SourceLineInfo lineInfo("special_file!@#.cpp", 99);
    EXPECT_NO_THROW({
        Catch::RegistrarForTagAliases registrar("[@special!@#$%]", "[tag with spaces]", lineInfo);
    });
}

// Test construction with very long strings
TEST_F(RegistrarForTagAliasesTest_1101, ConstructWithLongStrings_1101) {
    Catch::SourceLineInfo lineInfo("test_file.cpp", 1);
    std::string longAlias = "[@" + std::string(10000, 'a') + "]";
    std::string longTag = "[" + std::string(10000, 'b') + "]";
    EXPECT_NO_THROW({
        Catch::RegistrarForTagAliases registrar(longAlias.c_str(), longTag.c_str(), lineInfo);
    });
}

// Test that multiple different registrations work without crashing
TEST_F(RegistrarForTagAliasesTest_1101, MultipleDistinctRegistrations_1101) {
    EXPECT_NO_THROW({
        Catch::RegistrarForTagAliases r1("[@alias1_multi]", "[tag1]", Catch::SourceLineInfo("f.cpp", 1));
        Catch::RegistrarForTagAliases r2("[@alias2_multi]", "[tag2]", Catch::SourceLineInfo("f.cpp", 2));
        Catch::RegistrarForTagAliases r3("[@alias3_multi]", "[tag3]", Catch::SourceLineInfo("f.cpp", 3));
    });
}
