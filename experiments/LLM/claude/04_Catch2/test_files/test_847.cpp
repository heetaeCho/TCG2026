#include <sstream>
#include <string>
#include <vector>
#include <memory>

#include "catch2/reporters/catch_reporter_xml.hpp"
#include "catch2/internal/catch_xmlwriter.hpp"
#include "catch2/internal/catch_list.hpp"
#include "catch2/catch_reporter_config.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/internal/catch_config_wchar.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/catch_get_random_seed.hpp"

#include <gtest/gtest.h>

using namespace Catch;

namespace {

// Helper to create a minimal Config for ReporterConfig
class MinimalConfig : public Catch::IConfig {
public:
    bool allowThrows() const override { return true; }
    StringRef name() const override { return "test"; }
    int abortAfter() const override { return -1; }
    bool showInvisibles() const override { return false; }
    ShowDurations showDurations() const override { return ShowDurations::DefaultForReporter; }
    double minDuration() const override { return -1; }
    TestRunOrder runOrder() const override { return TestRunOrder::Declared; }
    uint32_t rngSeed() const override { return 0; }
    unsigned int shardCount() const override { return 1; }
    unsigned int shardIndex() const override { return 0; }
    ColourMode defaultColourMode() const override { return ColourMode::None; }
    std::vector<std::string> const& getSectionsToRun() const override {
        static std::vector<std::string> empty;
        return empty;
    }
    std::vector<std::string> const& getTestsOrTags() const override {
        static std::vector<std::string> empty;
        return empty;
    }
    std::vector<std::string> const& getReporterSpecs() const override {
        static std::vector<std::string> empty;
        return empty;
    }
    bool hasTestFilters() const override { return false; }
    bool warnAboutMissingAssertions() const override { return false; }
    bool warnAboutUnmatchedTestSpecs() const override { return false; }
    bool zeroTestsCountAsSuccess() const override { return false; }
    std::ostream& stream() const override {
        static std::ostringstream os;
        return os;
    }
    bool benchmarkNoAnalysis() const override { return false; }
    unsigned int benchmarkSamples() const override { return 100; }
    double benchmarkConfidenceInterval() const override { return 0.95; }
    unsigned int benchmarkResamples() const override { return 100000; }
    std::chrono::milliseconds benchmarkWarmupTime() const override { return std::chrono::milliseconds(100); }
};

std::unique_ptr<XmlReporter> createXmlReporter(std::ostream& os) {
    auto config = std::make_shared<MinimalConfig>();
    ReporterConfig repConfig(config.get(), os, ColourMode::None, {});
    return std::make_unique<XmlReporter>(std::move(repConfig));
}

} // anonymous namespace

class XmlReporterListReportersTest_847 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

TEST_F(XmlReporterListReportersTest_847, EmptyDescriptions_847) {
    auto reporter = createXmlReporter(oss);
    std::vector<ReporterDescription> descriptions;
    reporter->listReporters(descriptions);
    
    std::string output = oss.str();
    // Should contain AvailableReporters tag even with empty list
    EXPECT_NE(output.find("AvailableReporters"), std::string::npos);
    // Should NOT contain Reporter tag
    EXPECT_EQ(output.find("<Reporter"), std::string::npos);
}

TEST_F(XmlReporterListReportersTest_847, SingleReporterDescription_847) {
    auto reporter = createXmlReporter(oss);
    
    std::vector<ReporterDescription> descriptions;
    ReporterDescription desc;
    desc.name = "console";
    desc.description = "Reports test results to console";
    descriptions.push_back(desc);
    
    reporter->listReporters(descriptions);
    
    std::string output = oss.str();
    EXPECT_NE(output.find("AvailableReporters"), std::string::npos);
    EXPECT_NE(output.find("Reporter"), std::string::npos);
    EXPECT_NE(output.find("Name"), std::string::npos);
    EXPECT_NE(output.find("console"), std::string::npos);
    EXPECT_NE(output.find("Description"), std::string::npos);
    EXPECT_NE(output.find("Reports test results to console"), std::string::npos);
}

TEST_F(XmlReporterListReportersTest_847, MultipleReporterDescriptions_847) {
    auto reporter = createXmlReporter(oss);
    
    std::vector<ReporterDescription> descriptions;
    
    ReporterDescription desc1;
    desc1.name = "console";
    desc1.description = "Console reporter";
    descriptions.push_back(desc1);
    
    ReporterDescription desc2;
    desc2.name = "xml";
    desc2.description = "XML reporter";
    descriptions.push_back(desc2);
    
    ReporterDescription desc3;
    desc3.name = "junit";
    desc3.description = "JUnit reporter";
    descriptions.push_back(desc3);
    
    reporter->listReporters(descriptions);
    
    std::string output = oss.str();
    EXPECT_NE(output.find("AvailableReporters"), std::string::npos);
    EXPECT_NE(output.find("console"), std::string::npos);
    EXPECT_NE(output.find("Console reporter"), std::string::npos);
    EXPECT_NE(output.find("xml"), std::string::npos);
    EXPECT_NE(output.find("XML reporter"), std::string::npos);
    EXPECT_NE(output.find("junit"), std::string::npos);
    EXPECT_NE(output.find("JUnit reporter"), std::string::npos);
}

TEST_F(XmlReporterListReportersTest_847, ReporterWithEmptyNameAndDescription_847) {
    auto reporter = createXmlReporter(oss);
    
    std::vector<ReporterDescription> descriptions;
    ReporterDescription desc;
    desc.name = "";
    desc.description = "";
    descriptions.push_back(desc);
    
    reporter->listReporters(descriptions);
    
    std::string output = oss.str();
    EXPECT_NE(output.find("AvailableReporters"), std::string::npos);
    EXPECT_NE(output.find("Reporter"), std::string::npos);
    EXPECT_NE(output.find("Name"), std::string::npos);
    EXPECT_NE(output.find("Description"), std::string::npos);
}

TEST_F(XmlReporterListReportersTest_847, ReporterWithSpecialXmlCharacters_847) {
    auto reporter = createXmlReporter(oss);
    
    std::vector<ReporterDescription> descriptions;
    ReporterDescription desc;
    desc.name = "test<>&\"reporter";
    desc.description = "A reporter with <special> & \"characters\"";
    descriptions.push_back(desc);
    
    reporter->listReporters(descriptions);
    
    std::string output = oss.str();
    EXPECT_NE(output.find("AvailableReporters"), std::string::npos);
    // The XML writer should escape special characters, so raw < > & " should not appear unescaped
    // We just verify the output is produced and contains the Reporter element
    EXPECT_NE(output.find("Reporter"), std::string::npos);
    EXPECT_NE(output.find("Name"), std::string::npos);
    EXPECT_NE(output.find("Description"), std::string::npos);
}

TEST_F(XmlReporterListReportersTest_847, ReporterOrderIsPreserved_847) {
    auto reporter = createXmlReporter(oss);
    
    std::vector<ReporterDescription> descriptions;
    
    ReporterDescription desc1;
    desc1.name = "alpha";
    desc1.description = "First";
    descriptions.push_back(desc1);
    
    ReporterDescription desc2;
    desc2.name = "beta";
    desc2.description = "Second";
    descriptions.push_back(desc2);
    
    reporter->listReporters(descriptions);
    
    std::string output = oss.str();
    auto alphaPos = output.find("alpha");
    auto betaPos = output.find("beta");
    
    ASSERT_NE(alphaPos, std::string::npos);
    ASSERT_NE(betaPos, std::string::npos);
    EXPECT_LT(alphaPos, betaPos);
}

TEST_F(XmlReporterListReportersTest_847, ReporterWithLongNameAndDescription_847) {
    auto reporter = createXmlReporter(oss);
    
    std::vector<ReporterDescription> descriptions;
    ReporterDescription desc;
    desc.name = std::string(1000, 'x');
    desc.description = std::string(5000, 'y');
    descriptions.push_back(desc);
    
    reporter->listReporters(descriptions);
    
    std::string output = oss.str();
    EXPECT_NE(output.find("AvailableReporters"), std::string::npos);
    EXPECT_NE(output.find(std::string(1000, 'x')), std::string::npos);
    EXPECT_NE(output.find(std::string(5000, 'y')), std::string::npos);
}

TEST_F(XmlReporterListReportersTest_847, OutputContainsProperXmlStructure_847) {
    auto reporter = createXmlReporter(oss);
    
    std::vector<ReporterDescription> descriptions;
    ReporterDescription desc;
    desc.name = "myreporter";
    desc.description = "My custom reporter";
    descriptions.push_back(desc);
    
    reporter->listReporters(descriptions);
    
    std::string output = oss.str();
    
    // Verify proper XML nesting: AvailableReporters should open before Reporter
    auto availStart = output.find("<AvailableReporters");
    auto reporterStart = output.find("<Reporter");
    auto availEnd = output.find("</AvailableReporters>");
    
    ASSERT_NE(availStart, std::string::npos);
    ASSERT_NE(reporterStart, std::string::npos);
    ASSERT_NE(availEnd, std::string::npos);
    
    EXPECT_LT(availStart, reporterStart);
    EXPECT_LT(reporterStart, availEnd);
}

TEST_F(XmlReporterListReportersTest_847, NameAndDescriptionElementsInsideReporter_847) {
    auto reporter = createXmlReporter(oss);
    
    std::vector<ReporterDescription> descriptions;
    ReporterDescription desc;
    desc.name = "testreporter";
    desc.description = "A test reporter";
    descriptions.push_back(desc);
    
    reporter->listReporters(descriptions);
    
    std::string output = oss.str();
    
    auto reporterStart = output.find("<Reporter");
    auto nameStart = output.find("<Name");
    auto descStart = output.find("<Description");
    
    ASSERT_NE(reporterStart, std::string::npos);
    ASSERT_NE(nameStart, std::string::npos);
    ASSERT_NE(descStart, std::string::npos);
    
    EXPECT_LT(reporterStart, nameStart);
    EXPECT_LT(nameStart, descStart);
}
