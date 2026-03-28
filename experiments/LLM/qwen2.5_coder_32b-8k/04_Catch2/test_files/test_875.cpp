#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_json.hpp"

#include <vector>



using namespace Catch;



class JsonReporterTest : public ::testing::Test {

protected:

    std::ostringstream oss;

    ReporterConfig config{oss};

    JsonReporter reporter{std::move(config)};

};



TEST_F(JsonReporterTest_875, ListListenersWithEmptyDescriptions_875) {

    std::vector<ListenerDescription> descriptions;

    reporter.listListeners(descriptions);

}



TEST_F(JsonReporterTest_875, ListListenersWithSingleDescription_875) {

    ListenerDescription desc1 = {"name1", "description1"};

    std::vector<ListenerDescription> descriptions{desc1};

    reporter.listListeners(descriptions);

}



TEST_F(JsonReporterTest_875, ListListenersWithMultipleDescriptions_875) {

    ListenerDescription desc1 = {"name1", "description1"};

    ListenerDescription desc2 = {"name2", "description2"};

    std::vector<ListenerDescription> descriptions{desc1, desc2};

    reporter.listListeners(descriptions);

}
