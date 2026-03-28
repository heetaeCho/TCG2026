#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "catch2/catch_test_spec.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"

// We need a concrete Pattern implementation for testing
// Pattern must support operator<< via friend or member (since serializeTo uses out << *pattern)
namespace Catch {

    // TestPattern is a simple concrete pattern for testing
    class TestPattern : public TestSpec::Pattern {
        std::string m_name;
    public:
        explicit TestPattern(std::string name) : m_name(std::move(name)) {}
        
        bool matches(TestCaseInfo const&) const override { return false; }
        
        void serializeTo(std::ostream& out) const override {
            out << m_name;
        }
    };

} // namespace Catch

class TestSpecFilterSerializeTo_1006 : public ::testing::Test {
protected:
    Catch::TestSpec::Filter filter;
    std::ostringstream oss;
};

TEST_F(TestSpecFilterSerializeTo_1006, EmptyFilter_ProducesEmptyOutput_1006) {
    // Both m_required and m_forbidden are empty
    filter.serializeTo(oss);
    EXPECT_EQ(oss.str(), "");
}

TEST_F(TestSpecFilterSerializeTo_1006, SingleRequiredPattern_ProducesPatternName_1006) {
    filter.m_required.push_back(
        Catch::Detail::unique_ptr<Catch::TestSpec::Pattern>(new Catch::TestPattern("foo")));
    filter.serializeTo(oss);
    EXPECT_EQ(oss.str(), "foo");
}

TEST_F(TestSpecFilterSerializeTo_1006, MultipleRequiredPatterns_SpaceSeparated_1006) {
    filter.m_required.push_back(
        Catch::Detail::unique_ptr<Catch::TestSpec::Pattern>(new Catch::TestPattern("foo")));
    filter.m_required.push_back(
        Catch::Detail::unique_ptr<Catch::TestSpec::Pattern>(new Catch::TestPattern("bar")));
    filter.serializeTo(oss);
    EXPECT_EQ(oss.str(), "foo bar");
}

TEST_F(TestSpecFilterSerializeTo_1006, SingleForbiddenPattern_ProducesPatternName_1006) {
    filter.m_forbidden.push_back(
        Catch::Detail::unique_ptr<Catch::TestSpec::Pattern>(new Catch::TestPattern("~baz")));
    filter.serializeTo(oss);
    EXPECT_EQ(oss.str(), "~baz");
}

TEST_F(TestSpecFilterSerializeTo_1006, MultipleForbiddenPatterns_SpaceSeparated_1006) {
    filter.m_forbidden.push_back(
        Catch::Detail::unique_ptr<Catch::TestSpec::Pattern>(new Catch::TestPattern("~a")));
    filter.m_forbidden.push_back(
        Catch::Detail::unique_ptr<Catch::TestSpec::Pattern>(new Catch::TestPattern("~b")));
    filter.serializeTo(oss);
    EXPECT_EQ(oss.str(), "~a ~b");
}

TEST_F(TestSpecFilterSerializeTo_1006, RequiredAndForbiddenPatterns_SpaceSeparated_1006) {
    filter.m_required.push_back(
        Catch::Detail::unique_ptr<Catch::TestSpec::Pattern>(new Catch::TestPattern("req1")));
    filter.m_required.push_back(
        Catch::Detail::unique_ptr<Catch::TestSpec::Pattern>(new Catch::TestPattern("req2")));
    filter.m_forbidden.push_back(
        Catch::Detail::unique_ptr<Catch::TestSpec::Pattern>(new Catch::TestPattern("~forb1")));
    filter.m_forbidden.push_back(
        Catch::Detail::unique_ptr<Catch::TestSpec::Pattern>(new Catch::TestPattern("~forb2")));
    filter.serializeTo(oss);
    EXPECT_EQ(oss.str(), "req1 req2 ~forb1 ~forb2");
}

TEST_F(TestSpecFilterSerializeTo_1006, RequiredOnlyThenForbiddenEmpty_CorrectOutput_1006) {
    filter.m_required.push_back(
        Catch::Detail::unique_ptr<Catch::TestSpec::Pattern>(new Catch::TestPattern("alpha")));
    // m_forbidden is empty
    filter.serializeTo(oss);
    EXPECT_EQ(oss.str(), "alpha");
}

TEST_F(TestSpecFilterSerializeTo_1006, EmptyPatternName_ProducesEmptyTokens_1006) {
    filter.m_required.push_back(
        Catch::Detail::unique_ptr<Catch::TestSpec::Pattern>(new Catch::TestPattern("")));
    filter.m_required.push_back(
        Catch::Detail::unique_ptr<Catch::TestSpec::Pattern>(new Catch::TestPattern("x")));
    filter.serializeTo(oss);
    EXPECT_EQ(oss.str(), " x");
}

TEST_F(TestSpecFilterSerializeTo_1006, PatternWithSpaces_PreservedInOutput_1006) {
    filter.m_required.push_back(
        Catch::Detail::unique_ptr<Catch::TestSpec::Pattern>(new Catch::TestPattern("hello world")));
    filter.serializeTo(oss);
    EXPECT_EQ(oss.str(), "hello world");
}

TEST_F(TestSpecFilterSerializeTo_1006, ThreeRequiredPatterns_CorrectSpacing_1006) {
    filter.m_required.push_back(
        Catch::Detail::unique_ptr<Catch::TestSpec::Pattern>(new Catch::TestPattern("a")));
    filter.m_required.push_back(
        Catch::Detail::unique_ptr<Catch::TestSpec::Pattern>(new Catch::TestPattern("b")));
    filter.m_required.push_back(
        Catch::Detail::unique_ptr<Catch::TestSpec::Pattern>(new Catch::TestPattern("c")));
    filter.serializeTo(oss);
    EXPECT_EQ(oss.str(), "a b c");
}

TEST_F(TestSpecFilterSerializeTo_1006, OneRequiredOneForbidden_CorrectOrder_1006) {
    filter.m_required.push_back(
        Catch::Detail::unique_ptr<Catch::TestSpec::Pattern>(new Catch::TestPattern("include")));
    filter.m_forbidden.push_back(
        Catch::Detail::unique_ptr<Catch::TestSpec::Pattern>(new Catch::TestPattern("~exclude")));
    filter.serializeTo(oss);
    EXPECT_EQ(oss.str(), "include ~exclude");
}
