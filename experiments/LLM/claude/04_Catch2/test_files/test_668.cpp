#include <catch2/internal/catch_clara.hpp>
#include <catch2/catch_all.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include <string>

using namespace Catch::Clara;

class ParserTest_668 : public ::testing::Test {
protected:
    Parser parser;
};

// Test that default-constructed parser is valid
TEST_F(ParserTest_668, DefaultConstructedParserIsValid_668) {
    auto result = parser.validate();
    // A default parser should validate successfully (no options/args to conflict)
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test operator|= with another empty parser
TEST_F(ParserTest_668, MergeEmptyParsers_668) {
    Parser other;
    parser |= other;
    auto result = parser.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test operator|= returns reference to self
TEST_F(ParserTest_668, MergeReturnsReferenceToSelf_668) {
    Parser other;
    Parser& ref = (parser |= other);
    EXPECT_EQ(&ref, &parser);
}

// Test merging parser with itself
TEST_F(ParserTest_668, MergeParserWithItself_668) {
    parser |= parser;
    auto result = parser.validate();
    // Should not crash; result depends on implementation
    (void)result;
}

// Test chaining multiple merges
TEST_F(ParserTest_668, ChainMultipleMerges_668) {
    Parser p1;
    Parser p2;
    Parser p3;
    parser |= p1;
    parser |= p2;
    parser |= p3;
    auto result = parser.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test writeToStream on empty parser does not crash
TEST_F(ParserTest_668, WriteToStreamEmptyParser_668) {
    std::ostringstream oss;
    EXPECT_NO_THROW(parser.writeToStream(oss));
}

// Test getHelpColumns on empty parser returns empty
TEST_F(ParserTest_668, GetHelpColumnsEmptyParser_668) {
    auto columns = parser.getHelpColumns();
    EXPECT_TRUE(columns.empty());
}

// Test merging two empty parsers and then writing to stream
TEST_F(ParserTest_668, MergeAndWriteToStream_668) {
    Parser other;
    parser |= other;
    std::ostringstream oss;
    EXPECT_NO_THROW(parser.writeToStream(oss));
}

// Test that operator|= with Opt via another parser propagates options
TEST_F(ParserTest_668, MergeParserWithOptionsReflectedInHelpColumns_668) {
    bool flag = false;
    Opt opt(flag, "flag");
    opt["-f"]["--flag"].description("A test flag");
    
    Parser other;
    other |= opt;
    
    parser |= other;
    
    auto columns = parser.getHelpColumns();
    EXPECT_FALSE(columns.empty());
}

// Test operator|= with Arg
TEST_F(ParserTest_668, AddArgViaOperator_668) {
    std::string value;
    Arg arg(value, "value");
    arg.description("A test argument");
    
    parser |= arg;
    auto result = parser.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test merging parsers that both have args
TEST_F(ParserTest_668, MergeParsersWithArgs_668) {
    std::string val1, val2;
    
    Parser p1;
    Arg arg1(val1, "val1");
    p1 |= arg1;
    
    Parser p2;
    Arg arg2(val2, "val2");
    p2 |= arg2;
    
    p1 |= p2;
    
    // After merge, p1 should have both args
    std::ostringstream oss;
    EXPECT_NO_THROW(p1.writeToStream(oss));
}

// Test merging parsers with options preserves all options in help
TEST_F(ParserTest_668, MergeParsersWithOptionsCombinesHelpColumns_668) {
    bool flag1 = false, flag2 = false;
    
    Opt opt1(flag1, "flag1");
    opt1["-a"]["--alpha"].description("Alpha flag");
    
    Opt opt2(flag2, "flag2");
    opt2["-b"]["--beta"].description("Beta flag");
    
    Parser p1;
    p1 |= opt1;
    
    Parser p2;
    p2 |= opt2;
    
    auto cols1 = p1.getHelpColumns();
    auto cols2 = p2.getHelpColumns();
    
    p1 |= p2;
    
    auto mergedCols = p1.getHelpColumns();
    EXPECT_EQ(mergedCols.size(), cols1.size() + cols2.size());
}

// Test that the source parser is unchanged after merge
TEST_F(ParserTest_668, SourceParserUnchangedAfterMerge_668) {
    bool flag = false;
    Opt opt(flag, "flag");
    opt["-x"]["--xray"].description("Xray flag");
    
    Parser source;
    source |= opt;
    
    auto colsBefore = source.getHelpColumns();
    
    parser |= source;
    
    auto colsAfter = source.getHelpColumns();
    EXPECT_EQ(colsBefore.size(), colsAfter.size());
}
