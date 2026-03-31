#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include <string>

namespace re2 {

class LookupPosixGroupTest_522 : public ::testing::Test {
protected:
    // Helper to check if a regex with POSIX class compiles and matches expected strings
    bool MatchesPosix(const std::string& pattern, const std::string& text) {
        RE2::Options opts;
        opts.set_posix_syntax(true);
        opts.set_perl_classes(false);
        RE2 re(pattern, opts);
        if (!re.ok()) return false;
        return RE2::FullMatch(text, re);
    }
    
    bool CompilesPosix(const std::string& pattern) {
        RE2::Options opts;
        opts.set_posix_syntax(true);
        opts.set_perl_classes(false);
        RE2 re(pattern, opts);
        return re.ok();
    }
};

// Test that [:alpha:] POSIX group is recognized and matches alphabetic characters
TEST_F(LookupPosixGroupTest_522, AlphaGroupMatchesLetters_522) {
    EXPECT_TRUE(MatchesPosix("[[:alpha:]]", "a"));
    EXPECT_TRUE(MatchesPosix("[[:alpha:]]", "Z"));
    EXPECT_FALSE(MatchesPosix("[[:alpha:]]", "5"));
    EXPECT_FALSE(MatchesPosix("[[:alpha:]]", " "));
}

// Test that [:digit:] POSIX group is recognized and matches digits
TEST_F(LookupPosixGroupTest_522, DigitGroupMatchesDigits_522) {
    EXPECT_TRUE(MatchesPosix("[[:digit:]]", "0"));
    EXPECT_TRUE(MatchesPosix("[[:digit:]]", "9"));
    EXPECT_FALSE(MatchesPosix("[[:digit:]]", "a"));
    EXPECT_FALSE(MatchesPosix("[[:digit:]]", " "));
}

// Test that [:alnum:] matches alphanumeric characters
TEST_F(LookupPosixGroupTest_522, AlnumGroupMatchesAlphanumeric_522) {
    EXPECT_TRUE(MatchesPosix("[[:alnum:]]", "a"));
    EXPECT_TRUE(MatchesPosix("[[:alnum:]]", "Z"));
    EXPECT_TRUE(MatchesPosix("[[:alnum:]]", "5"));
    EXPECT_FALSE(MatchesPosix("[[:alnum:]]", " "));
    EXPECT_FALSE(MatchesPosix("[[:alnum:]]", "!"));
}

// Test that [:space:] matches whitespace
TEST_F(LookupPosixGroupTest_522, SpaceGroupMatchesWhitespace_522) {
    EXPECT_TRUE(MatchesPosix("[[:space:]]", " "));
    EXPECT_TRUE(MatchesPosix("[[:space:]]", "\t"));
    EXPECT_TRUE(MatchesPosix("[[:space:]]", "\n"));
    EXPECT_FALSE(MatchesPosix("[[:space:]]", "a"));
}

// Test that [:upper:] matches uppercase letters only
TEST_F(LookupPosixGroupTest_522, UpperGroupMatchesUppercase_522) {
    EXPECT_TRUE(MatchesPosix("[[:upper:]]", "A"));
    EXPECT_TRUE(MatchesPosix("[[:upper:]]", "Z"));
    EXPECT_FALSE(MatchesPosix("[[:upper:]]", "a"));
    EXPECT_FALSE(MatchesPosix("[[:upper:]]", "1"));
}

// Test that [:lower:] matches lowercase letters only
TEST_F(LookupPosixGroupTest_522, LowerGroupMatchesLowercase_522) {
    EXPECT_TRUE(MatchesPosix("[[:lower:]]", "a"));
    EXPECT_TRUE(MatchesPosix("[[:lower:]]", "z"));
    EXPECT_FALSE(MatchesPosix("[[:lower:]]", "A"));
    EXPECT_FALSE(MatchesPosix("[[:lower:]]", "1"));
}

// Test that [:punct:] matches punctuation
TEST_F(LookupPosixGroupTest_522, PunctGroupMatchesPunctuation_522) {
    EXPECT_TRUE(MatchesPosix("[[:punct:]]", "!"));
    EXPECT_TRUE(MatchesPosix("[[:punct:]]", "."));
    EXPECT_FALSE(MatchesPosix("[[:punct:]]", "a"));
    EXPECT_FALSE(MatchesPosix("[[:punct:]]", "5"));
}

// Test that an invalid/unknown POSIX group name causes a compilation failure
TEST_F(LookupPosixGroupTest_522, UnknownPosixGroupFailsToCompile_522) {
    EXPECT_FALSE(CompilesPosix("[[:foobar:]]"));
    EXPECT_FALSE(CompilesPosix("[[:nonexistent:]]"));
}

// Test that [:print:] matches printable characters
TEST_F(LookupPosixGroupTest_522, PrintGroupMatchesPrintable_522) {
    EXPECT_TRUE(MatchesPosix("[[:print:]]", "a"));
    EXPECT_TRUE(MatchesPosix("[[:print:]]", " "));
    EXPECT_TRUE(MatchesPosix("[[:print:]]", "!"));
}

// Test that [:graph:] matches visible (graphical) characters
TEST_F(LookupPosixGroupTest_522, GraphGroupMatchesGraphical_522) {
    EXPECT_TRUE(MatchesPosix("[[:graph:]]", "a"));
    EXPECT_TRUE(MatchesPosix("[[:graph:]]", "!"));
    EXPECT_FALSE(MatchesPosix("[[:graph:]]", " "));
}

// Test that [:cntrl:] matches control characters
TEST_F(LookupPosixGroupTest_522, CntrlGroupMatchesControl_522) {
    std::string nul(1, '\0');
    EXPECT_TRUE(MatchesPosix("[[:cntrl:]]", std::string(1, '\x01')));
    EXPECT_FALSE(MatchesPosix("[[:cntrl:]]", "a"));
}

// Test that [:xdigit:] matches hex digits
TEST_F(LookupPosixGroupTest_522, XdigitGroupMatchesHexDigits_522) {
    EXPECT_TRUE(MatchesPosix("[[:xdigit:]]", "a"));
    EXPECT_TRUE(MatchesPosix("[[:xdigit:]]", "F"));
    EXPECT_TRUE(MatchesPosix("[[:xdigit:]]", "0"));
    EXPECT_TRUE(MatchesPosix("[[:xdigit:]]", "9"));
    EXPECT_FALSE(MatchesPosix("[[:xdigit:]]", "g"));
    EXPECT_FALSE(MatchesPosix("[[:xdigit:]]", "G"));
}

// Test that [:blank:] matches blank characters (space and tab)
TEST_F(LookupPosixGroupTest_522, BlankGroupMatchesBlanks_522) {
    EXPECT_TRUE(MatchesPosix("[[:blank:]]", " "));
    EXPECT_TRUE(MatchesPosix("[[:blank:]]", "\t"));
    EXPECT_FALSE(MatchesPosix("[[:blank:]]", "\n"));
    EXPECT_FALSE(MatchesPosix("[[:blank:]]", "a"));
}

// Test that [:ascii:] matches ASCII characters (0-127)
TEST_F(LookupPosixGroupTest_522, AsciiGroupMatchesAscii_522) {
    EXPECT_TRUE(MatchesPosix("[[:ascii:]]", "a"));
    EXPECT_TRUE(MatchesPosix("[[:ascii:]]", "\x00"));
    EXPECT_TRUE(MatchesPosix("[[:ascii:]]", "\x7F"));
}

// Test negated POSIX class
TEST_F(LookupPosixGroupTest_522, NegatedPosixClassWorks_522) {
    EXPECT_FALSE(MatchesPosix("[[:^alpha:]]", "a"));
    EXPECT_TRUE(MatchesPosix("[[:^alpha:]]", "5"));
    EXPECT_TRUE(MatchesPosix("[[:^alpha:]]", " "));
}

// Test case sensitivity: POSIX group names should be lowercase
TEST_F(LookupPosixGroupTest_522, UppercasePosixGroupNameFails_522) {
    EXPECT_FALSE(CompilesPosix("[[:ALPHA:]]"));
    EXPECT_FALSE(CompilesPosix("[[:DIGIT:]]"));
}

// Test combined POSIX classes in single bracket expression
TEST_F(LookupPosixGroupTest_522, CombinedPosixClasses_522) {
    EXPECT_TRUE(MatchesPosix("[[:alpha:][:digit:]]", "a"));
    EXPECT_TRUE(MatchesPosix("[[:alpha:][:digit:]]", "5"));
    EXPECT_FALSE(MatchesPosix("[[:alpha:][:digit:]]", "!"));
}

}  // namespace re2
