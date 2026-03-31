#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <sstream>

// Include the header for the class under test
#include "catch2/catch_test_spec.hpp"

// Since Pattern is an abstract class (has virtual methods), we need a concrete implementation for testing
namespace {

class ConcretePattern : public Catch::TestSpec::Pattern {
public:
    explicit ConcretePattern(std::string const& name) : Pattern(name) {}

    bool matches(Catch::TestCaseInfo const& testCase) const override {
        // Minimal implementation for testing purposes
        return false;
    }

private:
    void serializeTo(std::ostream& out) const override {
        out << name();
    }
};

} // anonymous namespace

class PatternTest_1002 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that name() returns the name passed to the constructor
TEST_F(PatternTest_1002, NameReturnsConstructorArgument_1002) {
    ConcretePattern pattern("TestPatternName");
    EXPECT_EQ(pattern.name(), "TestPatternName");
}

// Test that name() returns empty string when constructed with empty string
TEST_F(PatternTest_1002, NameReturnsEmptyStringWhenConstructedWithEmpty_1002) {
    ConcretePattern pattern("");
    EXPECT_EQ(pattern.name(), "");
}

// Test that name() returns the correct string for a single character name
TEST_F(PatternTest_1002, NameReturnsSingleCharacter_1002) {
    ConcretePattern pattern("X");
    EXPECT_EQ(pattern.name(), "X");
}

// Test that name() returns the correct string for a name with special characters
TEST_F(PatternTest_1002, NameReturnsStringWithSpecialCharacters_1002) {
    ConcretePattern pattern("test*[pattern]?");
    EXPECT_EQ(pattern.name(), "test*[pattern]?");
}

// Test that name() returns a reference to the stored string consistently
TEST_F(PatternTest_1002, NameReturnsConsistentReference_1002) {
    ConcretePattern pattern("ConsistentName");
    std::string const& ref1 = pattern.name();
    std::string const& ref2 = pattern.name();
    EXPECT_EQ(&ref1, &ref2);
}

// Test that name() returns correct string with spaces
TEST_F(PatternTest_1002, NameReturnsStringWithSpaces_1002) {
    ConcretePattern pattern("name with spaces");
    EXPECT_EQ(pattern.name(), "name with spaces");
}

// Test that name() returns correct string for very long name
TEST_F(PatternTest_1002, NameReturnsVeryLongString_1002) {
    std::string longName(10000, 'a');
    ConcretePattern pattern(longName);
    EXPECT_EQ(pattern.name(), longName);
    EXPECT_EQ(pattern.name().size(), 10000u);
}

// Test that name() returns correct string with unicode-like characters
TEST_F(PatternTest_1002, NameReturnsStringWithUnicodeCharacters_1002) {
    ConcretePattern pattern("tëst_pättérn");
    EXPECT_EQ(pattern.name(), "tëst_pättérn");
}

// Test that name() returns correct string with newlines and tabs
TEST_F(PatternTest_1002, NameReturnsStringWithWhitespaceCharacters_1002) {
    ConcretePattern pattern("line1\nline2\ttab");
    EXPECT_EQ(pattern.name(), "line1\nline2\ttab");
}

// Test that the Pattern destructor can be called (via unique_ptr to base)
TEST_F(PatternTest_1002, DestructorIsVirtualAndWorks_1002) {
    std::unique_ptr<Catch::TestSpec::Pattern> pattern = 
        std::make_unique<ConcretePattern>("destructorTest");
    EXPECT_EQ(pattern->name(), "destructorTest");
    // Destructor called when unique_ptr goes out of scope - should not crash
    pattern.reset();
    SUCCEED();
}

// Test that multiple patterns can have different names
TEST_F(PatternTest_1002, MultiplePatternsHaveDifferentNames_1002) {
    ConcretePattern pattern1("first");
    ConcretePattern pattern2("second");
    ConcretePattern pattern3("third");
    
    EXPECT_EQ(pattern1.name(), "first");
    EXPECT_EQ(pattern2.name(), "second");
    EXPECT_EQ(pattern3.name(), "third");
    EXPECT_NE(pattern1.name(), pattern2.name());
    EXPECT_NE(pattern2.name(), pattern3.name());
}

// Test name with null character embedded
TEST_F(PatternTest_1002, NameWithEmbeddedNullCharacter_1002) {
    std::string nameWithNull("test\0pattern", 12);
    ConcretePattern pattern(nameWithNull);
    EXPECT_EQ(pattern.name(), nameWithNull);
    EXPECT_EQ(pattern.name().size(), 12u);
}
