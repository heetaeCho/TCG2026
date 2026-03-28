#include <gtest/gtest.h>

#include "catch2/reporters/catch_reporter_json.hpp"

#include <vector>



using namespace Catch;



class JsonReporterTest : public ::testing::Test {

protected:

    std::ostringstream os;

    ReporterConfig config = ReporterConfig();

    JsonReporter reporter = JsonReporter(std::move(config));



    std::vector<ReporterDescription> getSampleDescriptions() {

        return {{"reporter1", "description1"}, {"reporter2", "description2"}};

    }

};



TEST_F(JsonReporterTest_874, ListReportersGeneratesCorrectJson_874) {

    auto descriptions = getSampleDescriptions();

    reporter.listReporters(descriptions);

    

    std::string expected_output = R"({"reporters":[{"name":"reporter1","description":"description1"},{"name":"reporter2","description":"description2"}]})";

    EXPECT_EQ(os.str(), expected_output);

}



TEST_F(JsonReporterTest_874, ListReportersHandlesEmptyDescriptions_874) {

    std::vector<ReporterDescription> descriptions;

    reporter.listReporters(descriptions);



    std::string expected_output = R"({"reporters":[]})";

    EXPECT_EQ(os.str(), expected_output);

}



TEST_F(JsonReporterTest_874, ListReportersHandlesSingleDescription_874) {

    auto descriptions = getSampleDescriptions().front();

    reporter.listReporters({descriptions});



    std::string expected_output = R"({"reporters":[{"name":"reporter1","description":"description1"}]})";

    EXPECT_EQ(os.str(), expected_output);

}
