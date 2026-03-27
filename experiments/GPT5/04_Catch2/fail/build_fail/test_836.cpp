// File: tests/XmlReporter_testRunStarting_836.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>

// Catch2 headers (paths may vary in your repo)
#include "catch2/reporters/catch_reporter_xml.hpp"
#include "catch2/reporters/catch_reporter_helpers.hpp"   // for ReporterConfig (path may vary)
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/internal/catch_stringref.hpp"
#include "catch2/internal/catch_xmlwriter.hpp"
#include "catch2/internal/catch_test_run_info.hpp"

using ::testing::ReturnRef;
using ::testing::Return;
using ::testing::NiceMock;

namespace Catch {

// ---- Mock for IConfig: only the methods used by the code under test are mocked.
class MockConfig_836 : public IConfig {
public:
    MOCK_METHOD(StringRef, name, (), (const, override));
    MOCK_METHOD(uint32_t, rngSeed, (), (const, override));
    MOCK_METHOD(TestSpec const&, testSpec, (), (const, override));

    // Provide harmless defaults for other pure virtuals so the mock can be instantiated.
    MOCK_METHOD(bool, allowThrows, (), (const, override));
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));
    MOCK_METHOD(bool, shouldDebugBreak, (), (const, override));
    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const, override));
    MOCK_METHOD(bool, warnAboutUnmatchedTestSpecs, (), (const, override));
    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (const, override));
    MOCK_METHOD(int, abortAfter, (), (const, override));
    MOCK_METHOD(bool, showInvisibles, (), (const, override));
    MOCK_METHOD(ShowDurations, showDurations, (), (const, override));
    MOCK_METHOD(double, minDuration, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD((std::vector<std::string> const&), getTestsOrTags, (), (const, override));
    MOCK_METHOD(TestRunOrder, runOrder, (), (const, override));
    MOCK_METHOD(unsigned int, shardCount, (), (const, override));
    MOCK_METHOD(unsigned int, shardIndex, (), (const, override));
    MOCK_METHOD(ColourMode, defaultColourMode, (), (const, override));
    MOCK_METHOD((std::vector<std::string> const&), getSectionsToRun, (), (const, override));
    MOCK_METHOD(Verbosity, verbosity, (), (const, override));
    MOCK_METHOD(bool, skipBenchmarks, (), (const, override));
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));
    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));
    MOCK_METHOD((std::chrono::milliseconds), benchmarkWarmupTime, (), (const, override));
    // dtor already virtual in base
};

// Small helper subclass to control stylesheet reference through the public virtual
class TestXmlReporter_836 : public XmlReporter {
public:
    using XmlReporter::XmlReporter;
    void setStylesheet(std::string s) { sheet_ = std::move(s); }
    std::string getStylesheetRef() const override { return sheet_; }
private:
    std::string sheet_;
};

class XmlReporterTest_836 : public ::testing::Test {
protected:
    std::ostringstream out;
    NiceMock<MockConfig_836> config;      // NiceMock to ignore unused method calls
    TestSpec emptySpec;                   // Default-constructed TestSpec

    // ReporterConfig signature may differ slightly across Catch2 versions;
    // adjust includes/ctor if your tree differs.
    ReporterConfig makeReporterConfig() {
        // Defaults: colour mode & stream selection are handled by ReporterConfig;
        // we pass our output stream to observe XmlWriter output.
        ReporterConfig rc(&config, out);
        return rc;
    }

    // Common setup for config defaults used across tests.
    void SetUp() override {
        // Name and rng seed are read for attributes
        ON_CALL(config, name()).WillByDefault(Return(StringRef("MyRun")));
        ON_CALL(config, rngSeed()).WillByDefault(Return(uint32_t{123u}));

        // Unless a test overrides it, provide a TestSpec with no filters.
        ON_CALL(config, testSpec()).WillByDefault(ReturnRef(emptySpec));

        // Harmless defaults for required pure virtuals not under test
        static const std::vector<std::string> emptyVec;
        ON_CALL(config, allowThrows()).WillByDefault(Return(true));
        ON_CALL(config, includeSuccessfulResults()).WillByDefault(Return(true));
        ON_CALL(config, shouldDebugBreak()).WillByDefault(Return(false));
        ON_CALL(config, warnAboutMissingAssertions()).WillByDefault(Return(false));
        ON_CALL(config, warnAboutUnmatchedTestSpecs()).WillByDefault(Return(false));
        ON_CALL(config, zeroTestsCountAsSuccess()).WillByDefault(Return(false));
        ON_CALL(config, abortAfter()).WillByDefault(Return(0));
        ON_CALL(config, showInvisibles()).WillByDefault(Return(false));
        ON_CALL(config, showDurations()).WillByDefault(Return(ShowDurations::DefaultForReporter));
        ON_CALL(config, minDuration()).WillByDefault(Return(0.0));
        ON_CALL(config, hasTestFilters()).WillByDefault(Return(false));
        ON_CALL(config, getTestsOrTags()).WillByDefault(ReturnRef(emptyVec));
        ON_CALL(config, runOrder()).WillByDefault(Return(TestRunOrder::Declared));
        ON_CALL(config, shardCount()).WillByDefault(Return(1u));
        ON_CALL(config, shardIndex()).WillByDefault(Return(0u));
        ON_CALL(config, defaultColourMode()).WillByDefault(Return(ColourMode::PlatformDefault));
        ON_CALL(config, getSectionsToRun()).WillByDefault(ReturnRef(emptyVec));
        ON_CALL(config, verbosity()).WillByDefault(Return(Verbosity::Normal));
        ON_CALL(config, skipBenchmarks()).WillByDefault(Return(false));
        ON_CALL(config, benchmarkNoAnalysis()).WillByDefault(Return(false));
        ON_CALL(config, benchmarkSamples()).WillByDefault(Return(0u));
        ON_CALL(config, benchmarkConfidenceInterval()).WillByDefault(Return(0.95));
        ON_CALL(config, benchmarkResamples()).WillByDefault(Return(0u));
        ON_CALL(config, benchmarkWarmupTime()).WillByDefault(Return(std::chrono::milliseconds{0}));
    }
};

} // namespace Catch

// ----------------------- TESTS -----------------------

using namespace Catch;

// Normal operation: writes root element + key attributes (name, rng-seed, xml-format-version, catch2-version).
TEST_F(XmlReporterTest_836, WritesRootElementAndAttributes_836) {
    ReporterConfig rc = makeReporterConfig();
    TestXmlReporter_836 reporter(std::move(rc));
    // No stylesheet; default TestSpec has no filters

    const TestRunInfo tri{"RunA"_sr};

    ASSERT_NO_THROW(reporter.testRunStarting(tri));

    const std::string xml = out.str();

    // Observable substrings; do not depend on exact formatting/quoting layout.
    EXPECT_NE(xml.find("Catch2TestRun"), std::string::npos) << xml;
    EXPECT_NE(xml.find("name="), std::string::npos) << xml;
    EXPECT_NE(xml.find("MyRun"), std::string::npos) << xml; // value from mocked config::name()

    EXPECT_NE(xml.find("rng-seed"), std::string::npos) << xml;
    EXPECT_NE(xml.find("123"), std::string::npos) << xml;   // value from mocked config::rngSeed()

    EXPECT_NE(xml.find("xml-format-version"), std::string::npos) << xml;
    EXPECT_NE(xml.find("catch2-version"), std::string::npos) << xml;

    // With no filters in TestSpec, there must be no "filters" attribute written here.
    EXPECT_EQ(xml.find("filters"), std::string::npos) << "Unexpected 'filters' attribute when TestSpec::hasFilters() is false.\n" << xml;
}

// Boundary behavior: when getStylesheetRef() returns non-empty, a stylesheet reference is written.
TEST_F(XmlReporterTest_836, WritesStylesheetReferenceWhenProvided_836) {
    ReporterConfig rc = makeReporterConfig();
    TestXmlReporter_836 reporter(std::move(rc));
    reporter.setStylesheet("res://xsl/catch2.xsl"); // drive via the public virtual

    const TestRunInfo tri{"RunB"_sr};

    ASSERT_NO_THROW(reporter.testRunStarting(tri));

    const std::string xml = out.str();

    // We only assert observable presence of the provided URL token.
    // (Do not rely on exact PI formatting.)
    EXPECT_NE(xml.find("res://xsl/catch2.xsl"), std::string::npos) << xml;
    // Root element should still be started with attributes
    EXPECT_NE(xml.find("Catch2TestRun"), std::string::npos) << xml;
}

// Negative/branch check within observable constraints: No stylesheet when ref is empty; no filters when TestSpec has none.
TEST_F(XmlReporterTest_836, NoStylesheetAndNoFiltersByDefault_836) {
    ReporterConfig rc = makeReporterConfig();
    TestXmlReporter_836 reporter(std::move(rc));
    reporter.setStylesheet(""); // explicitly empty

    const TestRunInfo tri{"RunC"_sr};
    reporter.testRunStarting(tri);

    const std::string xml = out.str();

    // Ensure our URL token is not present
    EXPECT_EQ(xml.find("res://"), std::string::npos) << xml;

    // Ensure "filters" attribute is absent under default empty TestSpec
    EXPECT_EQ(xml.find("filters"), std::string::npos) << xml;
}

