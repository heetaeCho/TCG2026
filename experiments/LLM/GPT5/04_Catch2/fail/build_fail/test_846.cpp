// File: tests/XmlReporter_benchmarkFailed_846.tests.cpp

#include <gtest/gtest.h>
#include <sstream>

// Catch2 reporter under test
#include "catch2/reporters/catch_reporter_xml.hpp"

// If your project exposes ReporterConfig in a different header, adjust include accordingly.
// These tests assume Catch2 v3-style ReporterConfig taking (IConfig const*, std::ostream&).

namespace {

class XmlReporterTest_846 : public ::testing::Test {
protected:
    std::ostringstream oss;

    // Helper that constructs an XmlReporter writing to our ostringstream.
    // We pass nullptr for config because benchmarkFailed does not rely on it.
    Catch::XmlReporter makeReporter() {
        Catch::ReporterConfig rc(nullptr, oss);
        return Catch::XmlReporter(std::move(rc));
    }
};

} // namespace

// Normal operation: non-empty message should produce a <failed> element
// that contains a "message" attribute. We do NOT rely on exact formatting
// or escaping details—only on the observable tag/attribute presence.
TEST_F(XmlReporterTest_846, WritesFailedElementWithMessage_846) {
    auto reporter = makeReporter();

    const char* msg = "benchmark blew up";
    reporter.benchmarkFailed(Catch::StringRef(msg));

    const std::string out = oss.str();
    EXPECT_NE(out.find("<failed"), std::string::npos)    << "Should open a <failed> element";
    EXPECT_NE(out.find("message="), std::string::npos)   << "Should write a message attribute";
    // We avoid asserting the raw message text appears verbatim,
    // because the XmlWriter may escape characters.
    // But at least ensure the tag is closed somehow.
    EXPECT_TRUE(out.find("</failed>") != std::string::npos ||
                out.find("/>") != std::string::npos)
        << "Should close the <failed> element";
}

// Boundary condition: empty message. Still expect a "message" attribute to be present.
// We don't enforce exact value/quotes beyond attribute presence because formatting is XmlWriter's concern.
TEST_F(XmlReporterTest_846, WritesFailedElementWithEmptyMessage_846) {
    auto reporter = makeReporter();

    reporter.benchmarkFailed(Catch::StringRef(""));

    const std::string out = oss.str();
    EXPECT_NE(out.find("<failed"), std::string::npos);
    EXPECT_NE(out.find("message="), std::string::npos)
        << "Empty input should still result in a message attribute";
    EXPECT_TRUE(out.find("</failed>") != std::string::npos ||
                out.find("/>") != std::string::npos);
}

// Special characters: ensure call does not throw and observable structure stays intact.
// We do NOT assert on exact escaping; we only verify that a failed element with a message attribute exists.
TEST_F(XmlReporterTest_846, WritesFailedElementWithSpecialChars_846) {
    auto reporter = makeReporter();

    // Includes characters that typically require XML escaping.
    const std::string tricky = "Ω & < > \" '";
    reporter.benchmarkFailed(Catch::StringRef(tricky));

    const std::string out = oss.str();
    EXPECT_NE(out.find("<failed"), std::string::npos);
    EXPECT_NE(out.find("message="), std::string::npos)
        << "Should include a message attribute even with special characters";
    EXPECT_TRUE(out.find("</failed>") != std::string::npos ||
                out.find("/>") != std::string::npos);
}
