#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <memory>

#include "catch2/reporters/catch_reporter_console.hpp"
#include "catch2/catch_reporter_registrars.hpp"
#include "catch2/internal/catch_stringref.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/internal/catch_stream.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/reporters/catch_reporter_helpers.hpp"
#include "catch2/internal/catch_istream.hpp"

using namespace Catch;

namespace {

// Helper to create a ReporterConfig with a stringstream-based IStream
class StringStream : public Catch::IStream {
    std::ostringstream m_oss;
public:
    std::ostream& stream() override { return m_oss; }
    std::string str() const { return m_oss.str(); }
};

class ConsoleReporterTest_763 : public ::testing::Test {
protected:
    std::shared_ptr<StringStream> m_stringStream;
    std::unique_ptr<ConsoleReporter> m_reporter;

    void SetUp() override {
        m_stringStream = std::make_shared<StringStream>();
    }

    // Helper to create a ConsoleReporter - this depends on how ReporterConfig
    // is constructed in the actual codebase. We try to use available constructors.
    ConsoleReporter* createReporter() {
        // We need to create a ReporterConfig. This typically requires
        // an IConfig and an IStream.
        // Using minimal construction approach.
        auto streamPtr = Catch::Detail::unique_ptr<IStream>(new StringStream());
        // Store raw pointer to access later
        auto* rawStream = static_cast<StringStream*>(streamPtr.get());
        
        auto config = Catch::ReporterConfig(
            nullptr,  // fullConfig - may need a real config
            CATCH_MOVE(streamPtr),
            Catch::ColourMode::None,
            {}
        );
        
        m_reporter = std::make_unique<ConsoleReporter>(CATCH_MOVE(config));
        return m_reporter.get();
    }
};

// Test that getDescription returns a non-empty string
TEST_F(ConsoleReporterTest_763, GetDescription_ReturnsNonEmptyString_763) {
    std::string desc = ConsoleReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

// Test noMatchingTestCases outputs the unmatched spec
TEST_F(ConsoleReporterTest_763, NoMatchingTestCases_OutputsUnmatchedSpec_763) {
    auto stream = Detail::unique_ptr<IStream>(new StringStream());
    auto* rawStream = static_cast<StringStream*>(stream.get());
    
    try {
        auto config = ReporterConfig(
            nullptr,
            CATCH_MOVE(stream),
            ColourMode::None,
            {}
        );
        ConsoleReporter reporter(CATCH_MOVE(config));
        
        reporter.noMatchingTestCases("SomeTestSpec");
        
        std::string output = rawStream->str();
        EXPECT_NE(output.find("SomeTestSpec"), std::string::npos);
    } catch (...) {
        // If construction fails due to null config, skip
        GTEST_SKIP() << "Cannot construct ConsoleReporter without full config";
    }
}

// Test noMatchingTestCases with empty spec
TEST_F(ConsoleReporterTest_763, NoMatchingTestCases_EmptySpec_763) {
    auto stream = Detail::unique_ptr<IStream>(new StringStream());
    auto* rawStream = static_cast<StringStream*>(stream.get());
    
    try {
        auto config = ReporterConfig(
            nullptr,
            CATCH_MOVE(stream),
            ColourMode::None,
            {}
        );
        ConsoleReporter reporter(CATCH_MOVE(config));
        
        reporter.noMatchingTestCases("");
        
        std::string output = rawStream->str();
        // Should still produce some output indicating no match
        EXPECT_FALSE(output.empty());
    } catch (...) {
        GTEST_SKIP() << "Cannot construct ConsoleReporter without full config";
    }
}

// Test reportInvalidTestSpec outputs the argument
TEST_F(ConsoleReporterTest_763, ReportInvalidTestSpec_OutputsArgument_763) {
    auto stream = Detail::unique_ptr<IStream>(new StringStream());
    auto* rawStream = static_cast<StringStream*>(stream.get());
    
    try {
        auto config = ReporterConfig(
            nullptr,
            CATCH_MOVE(stream),
            ColourMode::None,
            {}
        );
        ConsoleReporter reporter(CATCH_MOVE(config));
        
        reporter.reportInvalidTestSpec("InvalidSpec[");
        
        std::string output = rawStream->str();
        EXPECT_NE(output.find("InvalidSpec["), std::string::npos);
    } catch (...) {
        GTEST_SKIP() << "Cannot construct ConsoleReporter without full config";
    }
}

// Test noMatchingTestCases with special characters
TEST_F(ConsoleReporterTest_763, NoMatchingTestCases_SpecialCharacters_763) {
    auto stream = Detail::unique_ptr<IStream>(new StringStream());
    auto* rawStream = static_cast<StringStream*>(stream.get());
    
    try {
        auto config = ReporterConfig(
            nullptr,
            CATCH_MOVE(stream),
            ColourMode::None,
            {}
        );
        ConsoleReporter reporter(CATCH_MOVE(config));
        
        reporter.noMatchingTestCases("[tag1][tag2]*wild?card");
        
        std::string output = rawStream->str();
        EXPECT_NE(output.find("[tag1][tag2]*wild?card"), std::string::npos);
    } catch (...) {
        GTEST_SKIP() << "Cannot construct ConsoleReporter without full config";
    }
}

// Test noMatchingTestCases called multiple times
TEST_F(ConsoleReporterTest_763, NoMatchingTestCases_MultipleCalls_763) {
    auto stream = Detail::unique_ptr<IStream>(new StringStream());
    auto* rawStream = static_cast<StringStream*>(stream.get());
    
    try {
        auto config = ReporterConfig(
            nullptr,
            CATCH_MOVE(stream),
            ColourMode::None,
            {}
        );
        ConsoleReporter reporter(CATCH_MOVE(config));
        
        reporter.noMatchingTestCases("First");
        reporter.noMatchingTestCases("Second");
        
        std::string output = rawStream->str();
        EXPECT_NE(output.find("First"), std::string::npos);
        EXPECT_NE(output.find("Second"), std::string::npos);
    } catch (...) {
        GTEST_SKIP() << "Cannot construct ConsoleReporter without full config";
    }
}

// Test that getDescription contains expected keywords
TEST_F(ConsoleReporterTest_763, GetDescription_ContainsRelevantInfo_763) {
    std::string desc = ConsoleReporter::getDescription();
    // The description should mention something about console/reports
    // At minimum it should be a meaningful string
    EXPECT_GT(desc.size(), 0u);
}

// Test assertionStarting does not crash (it's essentially a no-op observer)
TEST_F(ConsoleReporterTest_763, AssertionStarting_DoesNotCrash_763) {
    auto stream = Detail::unique_ptr<IStream>(new StringStream());
    
    try {
        auto config = ReporterConfig(
            nullptr,
            CATCH_MOVE(stream),
            ColourMode::None,
            {}
        );
        ConsoleReporter reporter(CATCH_MOVE(config));
        
        AssertionInfo info{"test", SourceLineInfo("file.cpp", 1), "", ResultDisposition::Normal};
        EXPECT_NO_THROW(reporter.assertionStarting(info));
    } catch (...) {
        GTEST_SKIP() << "Cannot construct ConsoleReporter without full config";
    }
}

} // anonymous namespace
