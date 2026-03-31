#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>

// Include necessary headers
#include "catch2/reporters/catch_reporter_helpers.hpp"
#include "catch2/internal/catch_list.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/internal/catch_textflow.hpp"

using namespace Catch;

class DefaultListReportersTest_821 : public ::testing::Test {
protected:
    std::ostringstream out;
};

// Test: Normal operation with a single reporter and Normal verbosity
TEST_F(DefaultListReportersTest_821, SingleReporterNormalVerbosity_821) {
    std::vector<ReporterDescription> descriptions;
    ReporterDescription desc;
    desc.name = "console";
    desc.description = "Reports test results to the console";
    descriptions.push_back(desc);

    defaultListReporters(out, descriptions, Verbosity::Normal);

    std::string result = out.str();
    EXPECT_NE(result.find("Available reporters:"), std::string::npos);
    EXPECT_NE(result.find("console"), std::string::npos);
    EXPECT_NE(result.find("Reports test results to the console"), std::string::npos);
}

// Test: Normal operation with a single reporter and Quiet verbosity (name only)
TEST_F(DefaultListReportersTest_821, SingleReporterQuietVerbosity_821) {
    std::vector<ReporterDescription> descriptions;
    ReporterDescription desc;
    desc.name = "console";
    desc.description = "Reports test results to the console";
    descriptions.push_back(desc);

    defaultListReporters(out, descriptions, Verbosity::Quiet);

    std::string result = out.str();
    EXPECT_NE(result.find("Available reporters:"), std::string::npos);
    EXPECT_NE(result.find("console"), std::string::npos);
    // In Quiet mode, description should not be present
    EXPECT_EQ(result.find("Reports test results to the console"), std::string::npos);
}

// Test: Multiple reporters with Normal verbosity
TEST_F(DefaultListReportersTest_821, MultipleReportersNormalVerbosity_821) {
    std::vector<ReporterDescription> descriptions;

    ReporterDescription desc1;
    desc1.name = "console";
    desc1.description = "Reports to console";
    descriptions.push_back(desc1);

    ReporterDescription desc2;
    desc2.name = "xml";
    desc2.description = "Reports in XML format";
    descriptions.push_back(desc2);

    ReporterDescription desc3;
    desc3.name = "junit";
    desc3.description = "Reports in JUnit format";
    descriptions.push_back(desc3);

    defaultListReporters(out, descriptions, Verbosity::Normal);

    std::string result = out.str();
    EXPECT_NE(result.find("Available reporters:"), std::string::npos);
    EXPECT_NE(result.find("console"), std::string::npos);
    EXPECT_NE(result.find("xml"), std::string::npos);
    EXPECT_NE(result.find("junit"), std::string::npos);
    EXPECT_NE(result.find("Reports to console"), std::string::npos);
    EXPECT_NE(result.find("Reports in XML format"), std::string::npos);
    EXPECT_NE(result.find("Reports in JUnit format"), std::string::npos);
}

// Test: Multiple reporters with Quiet verbosity
TEST_F(DefaultListReportersTest_821, MultipleReportersQuietVerbosity_821) {
    std::vector<ReporterDescription> descriptions;

    ReporterDescription desc1;
    desc1.name = "console";
    desc1.description = "Reports to console";
    descriptions.push_back(desc1);

    ReporterDescription desc2;
    desc2.name = "xml";
    desc2.description = "Reports in XML format";
    descriptions.push_back(desc2);

    defaultListReporters(out, descriptions, Verbosity::Quiet);

    std::string result = out.str();
    EXPECT_NE(result.find("Available reporters:"), std::string::npos);
    EXPECT_NE(result.find("console"), std::string::npos);
    EXPECT_NE(result.find("xml"), std::string::npos);
    // Descriptions should not appear in Quiet mode
    EXPECT_EQ(result.find("Reports to console"), std::string::npos);
    EXPECT_EQ(result.find("Reports in XML format"), std::string::npos);
}

// Test: High verbosity (should behave like Normal, showing descriptions)
TEST_F(DefaultListReportersTest_821, SingleReporterHighVerbosity_821) {
    std::vector<ReporterDescription> descriptions;
    ReporterDescription desc;
    desc.name = "console";
    desc.description = "Reports test results to the console";
    descriptions.push_back(desc);

    defaultListReporters(out, descriptions, Verbosity::High);

    std::string result = out.str();
    EXPECT_NE(result.find("Available reporters:"), std::string::npos);
    EXPECT_NE(result.find("console"), std::string::npos);
    EXPECT_NE(result.find("Reports test results to the console"), std::string::npos);
}

// Test: Output starts with "Available reporters:" header
TEST_F(DefaultListReportersTest_821, OutputStartsWithHeader_821) {
    std::vector<ReporterDescription> descriptions;
    ReporterDescription desc;
    desc.name = "test";
    desc.description = "A test reporter";
    descriptions.push_back(desc);

    defaultListReporters(out, descriptions, Verbosity::Normal);

    std::string result = out.str();
    EXPECT_EQ(result.find("Available reporters:\n"), 0u);
}

// Test: Output ends with a trailing newline (from the final out << '\n' << std::flush)
TEST_F(DefaultListReportersTest_821, OutputEndsWithNewline_821) {
    std::vector<ReporterDescription> descriptions;
    ReporterDescription desc;
    desc.name = "test";
    desc.description = "A test reporter";
    descriptions.push_back(desc);

    defaultListReporters(out, descriptions, Verbosity::Normal);

    std::string result = out.str();
    ASSERT_FALSE(result.empty());
    EXPECT_EQ(result.back(), '\n');
}

// Test: Reporters with varying name lengths (alignment test)
TEST_F(DefaultListReportersTest_821, VaryingNameLengthsAlignment_821) {
    std::vector<ReporterDescription> descriptions;

    ReporterDescription desc1;
    desc1.name = "a";
    desc1.description = "Short name reporter";
    descriptions.push_back(desc1);

    ReporterDescription desc2;
    desc2.name = "verylongreportername";
    desc2.description = "Long name reporter";
    descriptions.push_back(desc2);

    defaultListReporters(out, descriptions, Verbosity::Normal);

    std::string result = out.str();
    EXPECT_NE(result.find("a:"), std::string::npos);
    EXPECT_NE(result.find("verylongreportername:"), std::string::npos);
    EXPECT_NE(result.find("Short name reporter"), std::string::npos);
    EXPECT_NE(result.find("Long name reporter"), std::string::npos);
}

// Test: Reporter with empty description in Normal verbosity
TEST_F(DefaultListReportersTest_821, EmptyDescriptionNormalVerbosity_821) {
    std::vector<ReporterDescription> descriptions;
    ReporterDescription desc;
    desc.name = "nodesc";
    desc.description = "";
    descriptions.push_back(desc);

    defaultListReporters(out, descriptions, Verbosity::Normal);

    std::string result = out.str();
    EXPECT_NE(result.find("Available reporters:"), std::string::npos);
    EXPECT_NE(result.find("nodesc"), std::string::npos);
}

// Test: In Normal verbosity, colon is appended after the reporter name
TEST_F(DefaultListReportersTest_821, ColonAppendedInNormalVerbosity_821) {
    std::vector<ReporterDescription> descriptions;
    ReporterDescription desc;
    desc.name = "myreporter";
    desc.description = "My description";
    descriptions.push_back(desc);

    defaultListReporters(out, descriptions, Verbosity::Normal);

    std::string result = out.str();
    EXPECT_NE(result.find("myreporter:"), std::string::npos);
}

// Test: In Quiet verbosity, no colon is appended after the reporter name
TEST_F(DefaultListReportersTest_821, NoColonInQuietVerbosity_821) {
    std::vector<ReporterDescription> descriptions;
    ReporterDescription desc;
    desc.name = "myreporter";
    desc.description = "My description";
    descriptions.push_back(desc);

    defaultListReporters(out, descriptions, Verbosity::Quiet);

    std::string result = out.str();
    // The name should appear without colon; colon should not follow the name
    EXPECT_NE(result.find("myreporter"), std::string::npos);
    // Check that "myreporter:" does NOT appear
    EXPECT_EQ(result.find("myreporter:"), std::string::npos);
}

// Test: Reporters appear indented (at least 2 spaces before name)
TEST_F(DefaultListReportersTest_821, ReporterNamesAreIndented_821) {
    std::vector<ReporterDescription> descriptions;
    ReporterDescription desc;
    desc.name = "testreporter";
    desc.description = "Test description";
    descriptions.push_back(desc);

    defaultListReporters(out, descriptions, Verbosity::Quiet);

    std::string result = out.str();
    // After the header line, the reporter name should be indented
    auto headerEnd = result.find('\n');
    ASSERT_NE(headerEnd, std::string::npos);
    std::string afterHeader = result.substr(headerEnd + 1);
    // Should start with spaces (indent of 2)
    EXPECT_EQ(afterHeader.substr(0, 2), "  ");
}

// Test: Multiple reporters order is preserved
TEST_F(DefaultListReportersTest_821, ReporterOrderPreserved_821) {
    std::vector<ReporterDescription> descriptions;

    ReporterDescription desc1;
    desc1.name = "alpha";
    desc1.description = "First";
    descriptions.push_back(desc1);

    ReporterDescription desc2;
    desc2.name = "beta";
    desc2.description = "Second";
    descriptions.push_back(desc2);

    ReporterDescription desc3;
    desc3.name = "gamma";
    desc3.description = "Third";
    descriptions.push_back(desc3);

    defaultListReporters(out, descriptions, Verbosity::Normal);

    std::string result = out.str();
    auto posAlpha = result.find("alpha");
    auto posBeta = result.find("beta");
    auto posGamma = result.find("gamma");

    ASSERT_NE(posAlpha, std::string::npos);
    ASSERT_NE(posBeta, std::string::npos);
    ASSERT_NE(posGamma, std::string::npos);
    EXPECT_LT(posAlpha, posBeta);
    EXPECT_LT(posBeta, posGamma);
}

// Test: Reporter with very long name
TEST_F(DefaultListReportersTest_821, VeryLongReporterName_821) {
    std::vector<ReporterDescription> descriptions;
    ReporterDescription desc;
    desc.name = std::string(100, 'x');
    desc.description = "A reporter with a very long name";
    descriptions.push_back(desc);

    defaultListReporters(out, descriptions, Verbosity::Normal);

    std::string result = out.str();
    EXPECT_NE(result.find(std::string(100, 'x')), std::string::npos);
    EXPECT_NE(result.find("Available reporters:"), std::string::npos);
}

// Test: Reporter with special characters in name and description
TEST_F(DefaultListReportersTest_821, SpecialCharactersInNameAndDescription_821) {
    std::vector<ReporterDescription> descriptions;
    ReporterDescription desc;
    desc.name = "my-reporter_v2.0";
    desc.description = "Handles <xml> & \"special\" chars";
    descriptions.push_back(desc);

    defaultListReporters(out, descriptions, Verbosity::Normal);

    std::string result = out.str();
    EXPECT_NE(result.find("my-reporter_v2.0"), std::string::npos);
    EXPECT_NE(result.find("Handles <xml> & \"special\" chars"), std::string::npos);
}
