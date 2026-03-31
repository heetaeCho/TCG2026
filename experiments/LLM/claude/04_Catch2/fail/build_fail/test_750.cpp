#include <gtest/gtest.h>
#include <sstream>
#include <memory>

#include "catch2/reporters/catch_reporter_junit.hpp"
#include "catch2/catch_test_run_info.hpp"
#include "catch2/internal/catch_test_run_info.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/reporters/catch_reporter_common_base.hpp"
#include "catch2/internal/catch_istream.hpp"
#include "catch2/catch_session.hpp"

// We need to create a minimal setup to construct a JunitReporter.
// This requires a ReporterConfig which needs an IStream and a ReporterConfig::Flags or similar.

namespace {

// Helper to create a ReporterConfig pointing to a given ostream
class StringStream : public Catch::IStream {
public:
    std::ostream& getStream() override { return m_ss; }
    std::stringstream m_ss;
};

class JunitReporterTest_750 : public ::testing::Test {
protected:
    void SetUp() override {
        m_stringStream = Catch::Detail::make_unique<StringStream>();
        m_streamPtr = m_stringStream.get();
    }

    std::unique_ptr<Catch::JunitReporter> createReporter() {
        auto config = Catch::ConfigData{};
        auto catchConfig = std::make_shared<Catch::Config>(config);
        
        auto streamPtr = Catch::Detail::make_unique<StringStream>();
        m_rawStreamPtr = static_cast<StringStream*>(streamPtr.get());
        
        Catch::ReporterConfig reporterConfig(catchConfig.get(), CATCH_MOVE(streamPtr), Catch::ColourMode::None, {});
        m_config = catchConfig;
        return std::make_unique<Catch::JunitReporter>(CATCH_MOVE(reporterConfig));
    }

    StringStream* m_rawStreamPtr = nullptr;
    Catch::Detail::unique_ptr<StringStream> m_stringStream;
    StringStream* m_streamPtr = nullptr;
    std::shared_ptr<Catch::Config> m_config;
};

} // anonymous namespace

TEST_F(JunitReporterTest_750, GetDescription_ReturnsNonEmptyString_750) {
    std::string desc = Catch::JunitReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

TEST_F(JunitReporterTest_750, TestRunStarting_WritesTestsuitesElement_750) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);

    Catch::TestRunInfo runInfo("TestRun");
    reporter->testRunStarting(runInfo);

    std::string output = m_rawStreamPtr->m_ss.str();
    // After testRunStarting, the XML should contain "testsuites" element
    EXPECT_NE(output.find("testsuites"), std::string::npos);
}

TEST_F(JunitReporterTest_750, TestRunStarting_WritesXmlDeclaration_750) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);

    Catch::TestRunInfo runInfo("TestRun");
    reporter->testRunStarting(runInfo);

    std::string output = m_rawStreamPtr->m_ss.str();
    // XmlWriter typically writes an XML declaration at the start
    EXPECT_NE(output.find("<?xml"), std::string::npos);
}

TEST_F(JunitReporterTest_750, TestRunStarting_WithEmptyName_750) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);

    Catch::TestRunInfo runInfo("");
    EXPECT_NO_THROW(reporter->testRunStarting(runInfo));

    std::string output = m_rawStreamPtr->m_ss.str();
    EXPECT_NE(output.find("testsuites"), std::string::npos);
}

TEST_F(JunitReporterTest_750, TestRunStarting_WithLongName_750) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);

    std::string longName(1000, 'A');
    Catch::TestRunInfo runInfo(longName);
    EXPECT_NO_THROW(reporter->testRunStarting(runInfo));

    std::string output = m_rawStreamPtr->m_ss.str();
    EXPECT_NE(output.find("testsuites"), std::string::npos);
}

TEST_F(JunitReporterTest_750, TestRunStarting_WithSpecialCharactersInName_750) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);

    Catch::TestRunInfo runInfo("Test<Run>&\"Special'");
    EXPECT_NO_THROW(reporter->testRunStarting(runInfo));

    std::string output = m_rawStreamPtr->m_ss.str();
    EXPECT_NE(output.find("testsuites"), std::string::npos);
}

TEST_F(JunitReporterTest_750, ConstructorDoesNotThrow_750) {
    EXPECT_NO_THROW({
        auto reporter = createReporter();
    });
}

TEST_F(JunitReporterTest_750, GetDescription_ReturnsConsistentResult_750) {
    std::string desc1 = Catch::JunitReporter::getDescription();
    std::string desc2 = Catch::JunitReporter::getDescription();
    EXPECT_EQ(desc1, desc2);
}
