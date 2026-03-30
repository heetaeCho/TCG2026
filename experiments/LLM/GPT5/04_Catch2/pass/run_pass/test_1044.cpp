// File: tests/TestSpecParser_parse_1044.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include the real headers if available in your tree.
// If your project uses different include paths, adjust accordingly.
#include "catch2/internal/catch_test_spec_parser.hpp"
#include "catch2/interfaces/catch_interfaces_tag_alias_registry.hpp"
#include "catch2/catch_test_spec.hpp"  // For TestSpec + getInvalidSpecs

using ::testing::_;
using ::testing::Return;
using ::testing::Exactly;

namespace Catch {

// Mock for ITagAliasRegistry that we can pass into TestSpecParser
class MockTagAliasRegistry : public ITagAliasRegistry {
public:
    // Ensure a virtual destructor exists as per interface
    ~MockTagAliasRegistry() override = default;

    // We only need expandAliases for these tests; the others can be no-ops.
    MOCK_METHOD(std::string, expandAliases, (const std::string& unexpandedTestSpec), (const, override));

    // Provide stubs for the other virtuals so the class is concrete if needed
    MOCK_METHOD((const TagAlias*), find, (const std::string& alias), (const, override));
};

} // namespace Catch

// A small fixture to construct the parser around the mock registry
class TestSpecParserParseTest_1044 : public ::testing::Test {
protected:
    Catch::MockTagAliasRegistry mockAliases{};

    // Helper to create parser with the mock registry
    Catch::TestSpecParser makeParser() {
        return Catch::TestSpecParser(static_cast<const Catch::ITagAliasRegistry&>(mockAliases));
    }
};

// --- Tests ---

// Verifies: external interaction -- parse() calls expandAliases on the provided argument
// and successful parse produces no invalid specs for simple input.
// Also verifies fluent interface (returns *this).
TEST_F(TestSpecParserParseTest_1044, ParseCallsExpandAliases_AndFluentReturn_1044) {
    using namespace Catch;

    const std::string input = "SimpleName";
    const std::string expanded = "SimpleName"; // expanded equals input in this case

    EXPECT_CALL(mockAliases, expandAliases(input))
        .Times(Exactly(1))
        .WillOnce(Return(expanded));

    auto parser = makeParser();

    // Fluent interface: parse returns a reference to *this
    TestSpecParser& ret = parser.parse(input);
    EXPECT_EQ(&ret, &parser) << "parse should return *this for chaining";

    // Observable behavior: for a simple valid name, there should be no invalid specs recorded
    const auto invalid = parser.testSpec().getInvalidSpecs();
    EXPECT_TRUE(invalid.empty()) << "Valid input should not be recorded as invalid";
}

// Verifies: when parsing fails for any character (visitChar returns false),
// the ORIGINAL (unexpanded) argument is pushed to TestSpec::getInvalidSpecs().
// We simulate this by returning an expanded string that is likely invalid (e.g., “[”).
TEST_F(TestSpecParserParseTest_1044, OnParseFailure_OriginalArgIsRecordedAsInvalid_1044) {
    using namespace Catch;

    const std::string original = "@aliasThatExpandsToInvalid";
    const std::string expandedInvalid = "["; // Likely to cause parse failure

    EXPECT_CALL(mockAliases, expandAliases(original))
        .Times(Exactly(1))
        .WillOnce(Return(expandedInvalid));

    auto parser = makeParser();
    (void)parser.parse(original);

    const auto& invalid = parser.testSpec().getInvalidSpecs();
    ASSERT_FALSE(invalid.empty()) << "A failed parse should record the original argument as invalid";
    EXPECT_EQ(invalid.front(), original)
        << "On failure, parser must push_back the ORIGINAL (unexpanded) argument per interface snippet";
}

// Verifies: boundary condition -- empty string input. We expect a call to expandAliases("")
// and (for an empty spec) no invalid specs recorded.
TEST_F(TestSpecParserParseTest_1044, EmptyString_YieldsNoInvalidSpecs_AndExpands_1044) {
    using namespace Catch;

    const std::string input;
    const std::string expanded; // also empty

    EXPECT_CALL(mockAliases, expandAliases(input))
        .Times(Exactly(1))
        .WillOnce(Return(expanded));

    auto parser = makeParser();
    (void)parser.parse(input);

    const auto& invalid = parser.testSpec().getInvalidSpecs();
    EXPECT_TRUE(invalid.empty()) << "Empty input should not be marked invalid";
}

// Verifies: chaining multiple parses returns the same object each time (fluent API),
// and expandAliases is invoked for each parse call with the respective input.
TEST_F(TestSpecParserParseTest_1044, MultipleParseChaining_ReturnsSelf_AndExpandsEach_1044) {
    using namespace Catch;

    const std::string a = "First";
    const std::string b = "[tag]";
    EXPECT_CALL(mockAliases, expandAliases(a)).Times(Exactly(1)).WillOnce(Return(a));
    EXPECT_CALL(mockAliases, expandAliases(b)).Times(Exactly(1)).WillOnce(Return(b));

    auto parser = makeParser();

    TestSpecParser& r1 = parser.parse(a);
    EXPECT_EQ(&r1, &parser);

    TestSpecParser& r2 = parser.parse(b);
    EXPECT_EQ(&r2, &parser);

    // We do not assert specifics about invalid specs here; the focus is external calls + chaining.
}

// Verifies: if the alias expansion itself is a complex (but valid) spec,
// parsing should proceed without recording the original as invalid.
// This guards that we are parsing the EXPANDED string, but recording the ORIGINAL only on failure.
TEST_F(TestSpecParserParseTest_1044, UsesExpandedValueForParsing_ButRecordsOriginalOnlyOnFailure_1044) {
    using namespace Catch;

    const std::string original = "@alias";
    const std::string expandedValid = "SomeNameOrTag"; // benign, should parse

    EXPECT_CALL(mockAliases, expandAliases(original))
        .Times(Exactly(1))
        .WillOnce(Return(expandedValid));

    auto parser = makeParser();
    (void)parser.parse(original);

    const auto& invalid = parser.testSpec().getInvalidSpecs();
    EXPECT_TRUE(invalid.empty())
        << "If expanded spec parses fine, original should not be recorded as invalid";
}
