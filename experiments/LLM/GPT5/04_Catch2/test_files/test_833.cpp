// File: tests/XmlReporter_getDescription_833_tests.cpp

#include <gtest/gtest.h>

// Include the partial implementation under test.
// Adjust the relative path as needed in your project.
#include "Catch2/src/catch2/reporters/catch_reporter_xml.cpp"

using Catch::XmlReporter;

// A simple fixture for consistency/extension if needed later.
class XmlReporterTest_833 : public ::testing::Test {
protected:
    XmlReporter uut; // Uses the default-constructible class from the partial code.
};

// [Normal] It returns the exact, documented description.
TEST_F(XmlReporterTest_833, ReturnsExactDescription_833) {
    const std::string expected = "Reports test results as an XML document";
    EXPECT_EQ(uut.getDescription(), expected);
}

// [Boundary-ish] Non-empty and mentions "XML" (broad observable properties without assuming internals).
TEST_F(XmlReporterTest_833, NonEmptyAndContainsXMLWord_833) {
    const std::string desc = uut.getDescription();
    EXPECT_FALSE(desc.empty());
    // Case-sensitive check based on provided string.
    EXPECT_NE(desc.find("XML"), std::string::npos);
}

// [Stability] Multiple calls yield the same result (no observable side effects).
TEST_F(XmlReporterTest_833, MultipleCallsIdempotent_833) {
    const std::string first  = uut.getDescription();
    const std::string second = uut.getDescription();
    EXPECT_EQ(first, second);
}

// [Isolation] Modifying the returned string does not affect subsequent calls.
TEST_F(XmlReporterTest_833, ModifyingReturnDoesNotAffectSubsequentCalls_833) {
    std::string s = uut.getDescription();
    s += " (modified)";
    const std::string fresh = uut.getDescription();
    EXPECT_NE(s, fresh); // Verify previous modification didn't persist inside the object
}
