// File: tests/XmlReporter_ListReporters_847.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_xml.hpp"
#include "catch2/internal/catch_list.hpp"

// If your project already has a helper for building ReporterConfig with a custom stream,
// use it. Otherwise, this tiny utility wraps the usual pattern of constructing an
// XmlReporter with a std::ostringstream so we can observe the output.
//
// NOTE: This does NOT re-implement any XmlReporter logic; it only prepares dependencies.
namespace {
    struct ReporterHarness {
        std::ostringstream out;
        std::unique_ptr<Catch::XmlReporter> reporter;

        ReporterHarness() {
            // Build a ReporterConfig that writes to `out`. The exact constructor for
            // ReporterConfig varies slightly across Catch2 versions; if your project
            // already has a factory/helper, prefer that here.
            Catch::ReporterConfig cfg{ Catch::Detail::getCurrentContext().getConfig(),
                                       out,
                                       Catch::ColourMode::None,
                                       {}, {} };
            reporter = std::make_unique<Catch::XmlReporter>(CATCH_MOVE(cfg));
        }

        std::string str() const { return out.str(); }
    };

    // Convenience to build ReporterDescription with name/description.
    inline Catch::ReporterDescription makeDesc(std::string name, std::string desc) {
        Catch::ReporterDescription d;
        d.name = std::move(name);
        d.description = std::move(desc);
        return d;
    }
}

using ::testing::HasSubstr;
using ::testing::Not;

// Normal operation: two reporters produce 2 <Reporter> blocks with Name then Description.
TEST(XmlReporter_ListReporters_847, EmitsTwoReportersWithNameAndDescription_847) {
    ReporterHarness h;

    std::vector<Catch::ReporterDescription> descs{
        makeDesc("console", "Standard console reporter"),
        makeDesc("junit",   "JUnit XML reporter")
    };

    h.reporter->listReporters(descs);
    const std::string xml = h.str();

    // Outer wrapper is present
    EXPECT_THAT(xml, HasSubstr("AvailableReporters"));

    // Both reporters appear
    EXPECT_THAT(xml, HasSubstr("Reporter"));

    // Names and descriptions appear as text nodes under their respective elements
    EXPECT_THAT(xml, HasSubstr("Name"));
    EXPECT_THAT(xml, HasSubstr("Description"));

    // Verify the provided values are written
    EXPECT_THAT(xml, HasSubstr("console"));
    EXPECT_THAT(xml, HasSubstr("Standard console reporter"));
    EXPECT_THAT(xml, HasSubstr("junit"));
    EXPECT_THAT(xml, HasSubstr("JUnit XML reporter"));

    // Ordering within a single reporter: Name element should come before Description.
    // We check using the first reporter's values to avoid depending on formatting.
    auto posName = xml.find("console");
    auto posDesc = xml.find("Standard console reporter");
    ASSERT_NE(posName, std::string::npos);
    ASSERT_NE(posDesc, std::string::npos);
    EXPECT_LT(posName, posDesc);
}

// Boundary: empty list — still emits the outer <AvailableReporters> container and no names/descriptions.
TEST(XmlReporter_ListReporters_847, EmitsContainerForEmptyList_847) {
    ReporterHarness h;

    std::vector<Catch::ReporterDescription> descs; // empty
    h.reporter->listReporters(descs);
    const std::string xml = h.str();

    EXPECT_THAT(xml, HasSubstr("AvailableReporters"));
    // Should not contain any Name/Description content
    EXPECT_THAT(xml, Not(HasSubstr("<Name")));
    EXPECT_THAT(xml, Not(HasSubstr("<Description")));
}

// Boundary: empty strings for name and description — elements are present, values are empty (or self-closed).
TEST(XmlReporter_ListReporters_847, HandlesEmptyStrings_847) {
    ReporterHarness h;

    std::vector<Catch::ReporterDescription> descs{
        makeDesc("", "")
    };
    h.reporter->listReporters(descs);
    const std::string xml = h.str();

    // Still has the structure
    EXPECT_THAT(xml, HasSubstr("AvailableReporters"));
    EXPECT_THAT(xml, HasSubstr("Reporter"));
    EXPECT_THAT(xml, HasSubstr("Name"));
    EXPECT_THAT(xml, HasSubstr("Description"));
}

// Exceptional-ish surface case: special characters should be safely represented in XML output.
// We do not assert *how* they are escaped (implementation detail), only that the output does
// not contain raw illegal sequences and still contains our reporter entries.
TEST(XmlReporter_ListReporters_847, EscapesSpecialCharactersInValues_847) {
    ReporterHarness h;

    std::vector<Catch::ReporterDescription> descs{
        makeDesc("con<sole&>", "desc with <tags> & ampersand")
    };
    h.reporter->listReporters(descs);
    const std::string xml = h.str();

    // Structural checks
    EXPECT_THAT(xml, HasSubstr("AvailableReporters"));
    EXPECT_THAT(xml, HasSubstr("Reporter"));
    EXPECT_THAT(xml, HasSubstr("Name"));
    EXPECT_THAT(xml, HasSubstr("Description"));

    // The raw unescaped sequences should not appear verbatim in element text.
    // (Exact escaping is an internal detail of XmlWriter.)
    EXPECT_THAT(xml, Not(HasSubstr(">con<sole&><")));
    EXPECT_THAT(xml, Not(HasSubstr(">desc with <tags> & ampersand<")));

    // But we still expect some representation of our inputs to be present.
    // This keeps the assertion on observable behavior without assuming the escaping scheme.
    EXPECT_NE(std::string::npos, xml.find("con")) << "Name content should be represented";
    EXPECT_NE(std::string::npos, xml.find("desc with")) << "Description content should be represented";
}
