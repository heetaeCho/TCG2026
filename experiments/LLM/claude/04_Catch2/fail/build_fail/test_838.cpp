#include <sstream>
#include <string>
#include <vector>

#include "catch2/catch_test_macros.hpp"
#include "catch2/reporters/catch_reporter_xml.hpp"
#include "catch2/catch_section_info.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/internal/catch_source_line_info.hpp"
#include "catch2/reporters/catch_reporter_registrars.hpp"

#include <gtest/gtest.h>

using namespace Catch;

namespace {

// Helper to create a ReporterConfig that writes to a given stream
class XmlReporterTestFixture : public ::testing::Test {
protected:
    std::stringstream ss;
    
    std::unique_ptr<XmlReporter> createReporter() {
        // We need a config to create ReporterConfig
        // Using Catch2's internal mechanisms
        char const* argv[] = {"test"};
        Catch::ConfigData configData;
        auto config = std::make_shared<Catch::Config>(configData);
        
        auto prefs = ReporterConfig(config.get(), Detail::unique_ptr<std::ostream>(new std::ostream(ss.rdbuf())), ColourMode::None, {});
        
        auto reporter = std::make_unique<XmlReporter>(CATCH_MOVE(prefs));
        m_config = config; // prevent config from being destroyed
        return reporter;
    }
    
    std::shared_ptr<Catch::Config> m_config;
};

} // anonymous namespace

TEST_F(XmlReporterTestFixture, SectionStartingFirstSection_NoXmlSectionElement_838) {
    auto reporter = createReporter();
    
    // Clear any output from construction
    ss.str("");
    ss.clear();
    
    SectionInfo sectionInfo(SourceLineInfo("test_file.cpp", 10), "RootSection");
    reporter->sectionStarting(sectionInfo);
    
    std::string output = ss.str();
    // First call (m_sectionDepth was 0), should NOT write a <Section> element
    EXPECT_EQ(output.find("<Section"), std::string::npos);
}

TEST_F(XmlReporterTestFixture, SectionStartingSecondSection_WritesXmlSectionElement_838) {
    auto reporter = createReporter();
    
    SectionInfo rootSection(SourceLineInfo("test_file.cpp", 10), "RootSection");
    reporter->sectionStarting(rootSection);
    
    // Clear output after first call
    ss.str("");
    ss.clear();
    
    SectionInfo nestedSection(SourceLineInfo("test_file.cpp", 20), "NestedSection");
    reporter->sectionStarting(nestedSection);
    
    std::string output = ss.str();
    // Second call (m_sectionDepth was 1), should write <Section> element
    EXPECT_NE(output.find("Section"), std::string::npos);
    EXPECT_NE(output.find("NestedSection"), std::string::npos);
}

TEST_F(XmlReporterTestFixture, SectionStartingTrimsWhitespaceInName_838) {
    auto reporter = createReporter();
    
    SectionInfo rootSection(SourceLineInfo("test_file.cpp", 10), "Root");
    reporter->sectionStarting(rootSection);
    
    ss.str("");
    ss.clear();
    
    SectionInfo nestedSection(SourceLineInfo("test_file.cpp", 20), "  TrimMe  ");
    reporter->sectionStarting(nestedSection);
    
    std::string output = ss.str();
    // The name should be trimmed
    EXPECT_NE(output.find("TrimMe"), std::string::npos);
    // Should not contain the leading/trailing spaces in the attribute value
    // (depending on how trim works, we check the trimmed version appears)
    EXPECT_NE(output.find("\"TrimMe\""), std::string::npos);
}

TEST_F(XmlReporterTestFixture, SectionStartingWritesSourceInfo_838) {
    auto reporter = createReporter();
    
    SectionInfo rootSection(SourceLineInfo("test_file.cpp", 10), "Root");
    reporter->sectionStarting(rootSection);
    
    ss.str("");
    ss.clear();
    
    SectionInfo nestedSection(SourceLineInfo("my_source.cpp", 42), "Nested");
    reporter->sectionStarting(nestedSection);
    
    std::string output = ss.str();
    // Should contain source file info
    EXPECT_NE(output.find("my_source.cpp"), std::string::npos);
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(XmlReporterTestFixture, SectionStartingMultipleNestedSections_838) {
    auto reporter = createReporter();
    
    SectionInfo rootSection(SourceLineInfo("file.cpp", 1), "Root");
    reporter->sectionStarting(rootSection);
    
    SectionInfo level1(SourceLineInfo("file.cpp", 10), "Level1");
    reporter->sectionStarting(level1);
    
    ss.str("");
    ss.clear();
    
    SectionInfo level2(SourceLineInfo("file.cpp", 20), "Level2");
    reporter->sectionStarting(level2);
    
    std::string output = ss.str();
    // Third call, depth was 2, should still write Section element
    EXPECT_NE(output.find("Section"), std::string::npos);
    EXPECT_NE(output.find("Level2"), std::string::npos);
}

TEST_F(XmlReporterTestFixture, SectionStartingEmptyName_838) {
    auto reporter = createReporter();
    
    SectionInfo rootSection(SourceLineInfo("file.cpp", 1), "Root");
    reporter->sectionStarting(rootSection);
    
    ss.str("");
    ss.clear();
    
    SectionInfo emptySection(SourceLineInfo("file.cpp", 5), "");
    reporter->sectionStarting(emptySection);
    
    std::string output = ss.str();
    // Should still write a Section element even with empty name
    EXPECT_NE(output.find("Section"), std::string::npos);
}

TEST_F(XmlReporterTestFixture, SectionStartingNameAttributePresent_838) {
    auto reporter = createReporter();
    
    SectionInfo rootSection(SourceLineInfo("file.cpp", 1), "Root");
    reporter->sectionStarting(rootSection);
    
    ss.str("");
    ss.clear();
    
    SectionInfo nested(SourceLineInfo("file.cpp", 10), "TestName");
    reporter->sectionStarting(nested);
    
    std::string output = ss.str();
    // Should contain "name" attribute
    EXPECT_NE(output.find("name"), std::string::npos);
    EXPECT_NE(output.find("TestName"), std::string::npos);
}
