#include "catch2/internal/catch_clara.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>

using namespace Catch::Clara;

class ParserTest_394 : public ::testing::Test {
protected:
    Parser parser;
};

// Test that operator|= with ExeName returns a reference to the same parser
TEST_F(ParserTest_394, OperatorOrAssignExeNameReturnsSelf_394) {
    std::string name = "myapp";
    ExeName exeName(name);
    Parser& result = (parser |= exeName);
    EXPECT_EQ(&result, &parser);
}

// Test that operator|= with default ExeName works
TEST_F(ParserTest_394, OperatorOrAssignDefaultExeName_394) {
    ExeName exeName;
    Parser& result = (parser |= exeName);
    EXPECT_EQ(&result, &parser);
}

// Test that operator|= with another Parser returns a reference to this parser
TEST_F(ParserTest_394, OperatorOrAssignParserReturnsSelf_394) {
    Parser other;
    Parser& result = (parser |= other);
    EXPECT_EQ(&result, &parser);
}

// Test that chaining multiple operator|= with ExeName works
TEST_F(ParserTest_394, ChainingExeNameAssignments_394) {
    std::string name1 = "app1";
    std::string name2 = "app2";
    ExeName exeName1(name1);
    ExeName exeName2(name2);
    
    Parser& result = (parser |= exeName1);
    EXPECT_EQ(&result, &parser);
    
    Parser& result2 = (parser |= exeName2);
    EXPECT_EQ(&result2, &parser);
}

// Test that getHelpColumns returns a vector (possibly empty for default parser)
TEST_F(ParserTest_394, GetHelpColumnsOnDefaultParser_394) {
    auto columns = parser.getHelpColumns();
    // Default parser with no options or args should have empty help columns
    EXPECT_TRUE(columns.empty());
}

// Test that writeToStream does not crash on a default parser
TEST_F(ParserTest_394, WriteToStreamDefaultParser_394) {
    std::ostringstream oss;
    EXPECT_NO_THROW(parser.writeToStream(oss));
}

// Test that validate succeeds on a default parser
TEST_F(ParserTest_394, ValidateDefaultParser_394) {
    auto result = parser.validate();
    // A default parser with no args should validate successfully
    // We check it doesn't indicate an error (assuming Result has some way to check)
    // Since Result type details aren't fully known, just ensure no crash
    EXPECT_NO_THROW(parser.validate());
}

// Test ExeName default constructor gives default name
TEST(ExeNameTest_394, DefaultConstructorName_394) {
    ExeName exeName;
    EXPECT_EQ(exeName.name(), "<executable>");
}

// Test ExeName with string reference
TEST(ExeNameTest_394, StringRefConstructor_394) {
    std::string name = "testapp";
    ExeName exeName(name);
    // After construction, name() should return the default since set hasn't been called via parse
    EXPECT_EQ(exeName.name(), "<executable>");
}

// Test ExeName set method with valid name
TEST(ExeNameTest_394, SetValidName_394) {
    ExeName exeName;
    auto result = exeName.set("myprogram");
    EXPECT_EQ(exeName.name(), "myprogram");
}

// Test ExeName set method with empty string
TEST(ExeNameTest_394, SetEmptyName_394) {
    ExeName exeName;
    auto result = exeName.set("");
    // Behavior with empty string - should still set it
    EXPECT_EQ(exeName.name(), "");
}

// Test combining parser with another parser
TEST_F(ParserTest_394, CombineWithEmptyParser_394) {
    Parser other;
    EXPECT_NO_THROW(parser |= other);
}

// Test writeToStream after setting exe name
TEST_F(ParserTest_394, WriteToStreamAfterExeName_394) {
    std::string name = "myapp";
    ExeName exeName(name);
    parser |= exeName;
    
    std::ostringstream oss;
    EXPECT_NO_THROW(parser.writeToStream(oss));
}

// Test that multiple parser combinations don't crash
TEST_F(ParserTest_394, MultipleCombinations_394) {
    Parser p1, p2, p3;
    EXPECT_NO_THROW({
        parser |= p1;
        parser |= p2;
        parser |= p3;
    });
}

// Test validate after combining parsers
TEST_F(ParserTest_394, ValidateAfterCombining_394) {
    Parser other;
    parser |= other;
    EXPECT_NO_THROW(parser.validate());
}

// Test ExeName set with a path-like name
TEST(ExeNameTest_394, SetPathLikeName_394) {
    ExeName exeName;
    exeName.set("/usr/bin/myprogram");
    EXPECT_EQ(exeName.name(), "/usr/bin/myprogram");
}

// Test ExeName set with Windows path
TEST(ExeNameTest_394, SetWindowsPathName_394) {
    ExeName exeName;
    exeName.set("C:\\Program Files\\myapp.exe");
    EXPECT_EQ(exeName.name(), "C:\\Program Files\\myapp.exe");
}

// Test that overwriting ExeName works
TEST_F(ParserTest_394, OverwriteExeName_394) {
    std::string name1 = "first";
    std::string name2 = "second";
    ExeName exe1(name1);
    ExeName exe2(name2);
    
    parser |= exe1;
    parser |= exe2;
    
    // Should not crash - second assignment overwrites first
    EXPECT_NO_THROW(parser.validate());
}
