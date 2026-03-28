#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <sstream>
#include <string>

// Include the header under test
#include "catch2/catch_test_spec.hpp"
#include "catch2/catch_test_case_info.hpp"

using namespace Catch;

// Since Pattern is abstract (has virtual methods), we need a concrete subclass for testing
class ConcretePattern : public TestSpec::Pattern {
public:
    explicit ConcretePattern(const std::string& name)
        : TestSpec::Pattern(name) {}

    bool matches(TestCaseInfo const& testCase) const override {
        // Simple implementation for testing - match if test case name contains pattern name
        return testCase.name.find(name()) != std::string::npos;
    }

private:
    void serializeTo(std::ostream& out) const override {
        out << name();
    }
};

class PatternTest_32 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that Pattern stores and returns the name correctly
TEST_F(PatternTest_32, NameReturnsConstructedName_32) {
    ConcretePattern pattern("TestPattern");
    EXPECT_EQ(pattern.name(), "TestPattern");
}

// Test that Pattern stores an empty name correctly
TEST_F(PatternTest_32, EmptyNameIsStored_32) {
    ConcretePattern pattern("");
    EXPECT_EQ(pattern.name(), "");
}

// Test that Pattern stores a name with special characters
TEST_F(PatternTest_32, SpecialCharactersInName_32) {
    ConcretePattern pattern("test*[special]?chars");
    EXPECT_EQ(pattern.name(), "test*[special]?chars");
}

// Test that Pattern stores a name with spaces
TEST_F(PatternTest_32, NameWithSpaces_32) {
    ConcretePattern pattern("test pattern with spaces");
    EXPECT_EQ(pattern.name(), "test pattern with spaces");
}

// Test the operator<< serialization
TEST_F(PatternTest_32, StreamOperatorOutputsSerializedPattern_32) {
    ConcretePattern pattern("MyTestPattern");
    std::ostringstream oss;
    oss << pattern;
    EXPECT_EQ(oss.str(), "MyTestPattern");
}

// Test the operator<< with empty pattern name
TEST_F(PatternTest_32, StreamOperatorWithEmptyName_32) {
    ConcretePattern pattern("");
    std::ostringstream oss;
    oss << pattern;
    EXPECT_EQ(oss.str(), "");
}

// Test that destructor can be called (no crash on destruction)
TEST_F(PatternTest_32, DestructorDoesNotCrash_32) {
    auto* pattern = new ConcretePattern("Temporary");
    EXPECT_NO_THROW(delete pattern);
}

// Test that Pattern can be destroyed through base pointer (virtual destructor)
TEST_F(PatternTest_32, VirtualDestructorWorksCorrectly_32) {
    TestSpec::Pattern* pattern = new ConcretePattern("VirtualDestructorTest");
    EXPECT_EQ(pattern->name(), "VirtualDestructorTest");
    EXPECT_NO_THROW(delete pattern);
}

// Test with a very long name
TEST_F(PatternTest_32, LongNameIsStoredCorrectly_32) {
    std::string longName(10000, 'x');
    ConcretePattern pattern(longName);
    EXPECT_EQ(pattern.name(), longName);
    EXPECT_EQ(pattern.name().size(), 10000u);
}

// Test stream operator with a long name
TEST_F(PatternTest_32, StreamOperatorWithLongName_32) {
    std::string longName(10000, 'y');
    ConcretePattern pattern(longName);
    std::ostringstream oss;
    oss << pattern;
    EXPECT_EQ(oss.str(), longName);
}

// Test that name returns a const reference (multiple calls return same value)
TEST_F(PatternTest_32, NameIsConsistent_32) {
    ConcretePattern pattern("ConsistentName");
    const std::string& name1 = pattern.name();
    const std::string& name2 = pattern.name();
    EXPECT_EQ(name1, name2);
    EXPECT_EQ(&name1, &name2);  // Should be the same reference
}

// Test with unicode-like characters in name
TEST_F(PatternTest_32, NameWithUnicodeChars_32) {
    ConcretePattern pattern("tëst_pàttern_ñ");
    EXPECT_EQ(pattern.name(), "tëst_pàttern_ñ");
}

// Test multiple patterns can coexist independently
TEST_F(PatternTest_32, MultiplePatternsAreIndependent_32) {
    ConcretePattern pattern1("First");
    ConcretePattern pattern2("Second");
    ConcretePattern pattern3("Third");
    
    EXPECT_EQ(pattern1.name(), "First");
    EXPECT_EQ(pattern2.name(), "Second");
    EXPECT_EQ(pattern3.name(), "Third");
}

// Test stream operator chaining
TEST_F(PatternTest_32, StreamOperatorChaining_32) {
    ConcretePattern pattern1("Hello");
    ConcretePattern pattern2("World");
    std::ostringstream oss;
    oss << pattern1 << " " << pattern2;
    EXPECT_EQ(oss.str(), "Hello World");
}
