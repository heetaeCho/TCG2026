#include <catch2/reporters/catch_reporter_xml.hpp>
#include <catch2/internal/catch_xmlwriter.hpp>
#include <catch2/internal/catch_list.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/reporters/catch_reporter_streaming_base.hpp>
#include <catch2/internal/catch_reporter_spec_parser.hpp>
#include <catch2/catch_config.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include <vector>
#include <memory>

using namespace Catch;
using ::testing::HasSubstr;
using ::testing::Not;

namespace {

// Helper to create an XmlReporter writing to a given stream
std::unique_ptr<XmlReporter> makeXmlReporter(std::ostream& os) {
    // We need to create a ReporterConfig that points to our stream.
    // This requires a Catch2 Config object. We'll create minimal ones.
    
    // Create a minimal config
    auto configData = ConfigData{};
    auto config = std::make_shared<Config>(configData);
    
    // Create reporter config pointing to our ostream
    ReporterConfig repConfig(config.get(), os, ColourMode::None, {});
    
    auto reporter = std::make_unique<XmlReporter>(std::move(repConfig));
    return reporter;
}

} // anonymous namespace

class XmlReporterListListenersTest_848 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

TEST_F(XmlReporterListListenersTest_848, EmptyListeners_848) {
    auto reporter = makeXmlReporter(oss);
    
    std::vector<ListenerDescription> descriptions;
    reporter->listListeners(descriptions);
    
    std::string output = oss.str();
    
    // Should contain the outer RegisteredListeners tag
    EXPECT_THAT(output, HasSubstr("RegisteredListeners"));
    // Should not contain any Listener elements
    EXPECT_THAT(output, Not(HasSubstr("<Listener")));
    EXPECT_THAT(output, Not(HasSubstr("<Name")));
    EXPECT_THAT(output, Not(HasSubstr("<Description")));
}

TEST_F(XmlReporterListListenersTest_848, SingleListener_848) {
    auto reporter = makeXmlReporter(oss);
    
    std::vector<ListenerDescription> descriptions;
    ListenerDescription desc;
    desc.name = "MyListener";
    desc.description = "A test listener";
    descriptions.push_back(desc);
    
    reporter->listListeners(descriptions);
    
    std::string output = oss.str();
    
    EXPECT_THAT(output, HasSubstr("RegisteredListeners"));
    EXPECT_THAT(output, HasSubstr("Listener"));
    EXPECT_THAT(output, HasSubstr("Name"));
    EXPECT_THAT(output, HasSubstr("MyListener"));
    EXPECT_THAT(output, HasSubstr("Description"));
    EXPECT_THAT(output, HasSubstr("A test listener"));
}

TEST_F(XmlReporterListListenersTest_848, MultipleListeners_848) {
    auto reporter = makeXmlReporter(oss);
    
    std::vector<ListenerDescription> descriptions;
    
    ListenerDescription desc1;
    desc1.name = "ListenerOne";
    desc1.description = "First listener";
    descriptions.push_back(desc1);
    
    ListenerDescription desc2;
    desc2.name = "ListenerTwo";
    desc2.description = "Second listener";
    descriptions.push_back(desc2);
    
    reporter->listListeners(descriptions);
    
    std::string output = oss.str();
    
    EXPECT_THAT(output, HasSubstr("RegisteredListeners"));
    EXPECT_THAT(output, HasSubstr("ListenerOne"));
    EXPECT_THAT(output, HasSubstr("First listener"));
    EXPECT_THAT(output, HasSubstr("ListenerTwo"));
    EXPECT_THAT(output, HasSubstr("Second listener"));
}

TEST_F(XmlReporterListListenersTest_848, ListenerWithEmptyNameAndDescription_848) {
    auto reporter = makeXmlReporter(oss);
    
    std::vector<ListenerDescription> descriptions;
    ListenerDescription desc;
    desc.name = "";
    desc.description = "";
    descriptions.push_back(desc);
    
    reporter->listListeners(descriptions);
    
    std::string output = oss.str();
    
    EXPECT_THAT(output, HasSubstr("RegisteredListeners"));
    EXPECT_THAT(output, HasSubstr("Listener"));
    EXPECT_THAT(output, HasSubstr("Name"));
    EXPECT_THAT(output, HasSubstr("Description"));
}

TEST_F(XmlReporterListListenersTest_848, ListenerWithSpecialXmlCharacters_848) {
    auto reporter = makeXmlReporter(oss);
    
    std::vector<ListenerDescription> descriptions;
    ListenerDescription desc;
    desc.name = "Listener<with>&\"special'chars";
    desc.description = "Desc with <xml> & \"quotes\"";
    descriptions.push_back(desc);
    
    reporter->listListeners(descriptions);
    
    std::string output = oss.str();
    
    EXPECT_THAT(output, HasSubstr("RegisteredListeners"));
    // The XML writer should escape special characters
    // The raw special chars should not appear unescaped in valid XML
    EXPECT_THAT(output, HasSubstr("Listener"));
    EXPECT_THAT(output, HasSubstr("Name"));
    EXPECT_THAT(output, HasSubstr("Description"));
    // Verify that & is escaped (as &amp;)
    EXPECT_THAT(output, HasSubstr("&amp;"));
}

TEST_F(XmlReporterListListenersTest_848, ListenerWithLongNameAndDescription_848) {
    auto reporter = makeXmlReporter(oss);
    
    std::string longName(1000, 'A');
    std::string longDesc(1000, 'B');
    
    std::vector<ListenerDescription> descriptions;
    ListenerDescription desc;
    desc.name = longName;
    desc.description = longDesc;
    descriptions.push_back(desc);
    
    reporter->listListeners(descriptions);
    
    std::string output = oss.str();
    
    EXPECT_THAT(output, HasSubstr("RegisteredListeners"));
    EXPECT_THAT(output, HasSubstr(longName));
    EXPECT_THAT(output, HasSubstr(longDesc));
}

TEST_F(XmlReporterListListenersTest_848, OutputIsWellFormedXmlStructure_848) {
    auto reporter = makeXmlReporter(oss);
    
    std::vector<ListenerDescription> descriptions;
    ListenerDescription desc;
    desc.name = "TestListener";
    desc.description = "Test description";
    descriptions.push_back(desc);
    
    reporter->listListeners(descriptions);
    
    std::string output = oss.str();
    
    // Check that opening and closing tags are present
    EXPECT_THAT(output, HasSubstr("<RegisteredListeners"));
    EXPECT_THAT(output, HasSubstr("</RegisteredListeners>"));
    EXPECT_THAT(output, HasSubstr("<Listener"));
    EXPECT_THAT(output, HasSubstr("</Listener>"));
    EXPECT_THAT(output, HasSubstr("<Name"));
    EXPECT_THAT(output, HasSubstr("</Name>"));
    EXPECT_THAT(output, HasSubstr("<Description"));
    EXPECT_THAT(output, HasSubstr("</Description>"));
}

TEST_F(XmlReporterListListenersTest_848, OrderOfListenersPreserved_848) {
    auto reporter = makeXmlReporter(oss);
    
    std::vector<ListenerDescription> descriptions;
    
    ListenerDescription desc1;
    desc1.name = "Alpha";
    desc1.description = "First";
    descriptions.push_back(desc1);
    
    ListenerDescription desc2;
    desc2.name = "Beta";
    desc2.description = "Second";
    descriptions.push_back(desc2);
    
    ListenerDescription desc3;
    desc3.name = "Gamma";
    desc3.description = "Third";
    descriptions.push_back(desc3);
    
    reporter->listListeners(descriptions);
    
    std::string output = oss.str();
    
    // Verify order is preserved: Alpha before Beta before Gamma
    auto posAlpha = output.find("Alpha");
    auto posBeta = output.find("Beta");
    auto posGamma = output.find("Gamma");
    
    ASSERT_NE(posAlpha, std::string::npos);
    ASSERT_NE(posBeta, std::string::npos);
    ASSERT_NE(posGamma, std::string::npos);
    
    EXPECT_LT(posAlpha, posBeta);
    EXPECT_LT(posBeta, posGamma);
}

TEST_F(XmlReporterListListenersTest_848, ListenerNameAndDescriptionInCorrectElements_848) {
    auto reporter = makeXmlReporter(oss);
    
    std::vector<ListenerDescription> descriptions;
    ListenerDescription desc;
    desc.name = "UNIQUE_NAME_XYZ";
    desc.description = "UNIQUE_DESC_ABC";
    descriptions.push_back(desc);
    
    reporter->listListeners(descriptions);
    
    std::string output = oss.str();
    
    // Name should appear between <Name> tags
    auto nameStart = output.find("<Name");
    auto nameEnd = output.find("</Name>");
    auto nameTextPos = output.find("UNIQUE_NAME_XYZ");
    
    ASSERT_NE(nameStart, std::string::npos);
    ASSERT_NE(nameEnd, std::string::npos);
    ASSERT_NE(nameTextPos, std::string::npos);
    EXPECT_GT(nameTextPos, nameStart);
    EXPECT_LT(nameTextPos, nameEnd);
    
    // Description should appear between <Description> tags
    auto descStart = output.find("<Description");
    auto descEnd = output.find("</Description>");
    auto descTextPos = output.find("UNIQUE_DESC_ABC");
    
    ASSERT_NE(descStart, std::string::npos);
    ASSERT_NE(descEnd, std::string::npos);
    ASSERT_NE(descTextPos, std::string::npos);
    EXPECT_GT(descTextPos, descStart);
    EXPECT_LT(descTextPos, descEnd);
}
