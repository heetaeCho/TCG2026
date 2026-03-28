#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/reporters/catch_reporter_xml.hpp"

#include "./TestProjects/Catch2/src/catch2/internal/catch_xmlwriter.hpp"

#include <vector>



using namespace Catch;

using ::testing::_;

using ::testing::InSequence;



class XmlReporterTest_848 : public ::testing::Test {

protected:

    std::ostringstream oss;

    ReporterConfig config{oss};

    XmlReporter xmlReporter{std::move(config)};

};



TEST_F(XmlReporterTest_848, ListListenersWithEmptyDescriptions_848) {

    std::vector<ListenerDescription> descriptions;

    xmlReporter.listListeners(descriptions);

}



TEST_F(XmlReporterTest_848, ListListenersWithSingleDescription_848) {

    ListenerDescription description1{"Name1", "Description1"};

    std::vector<ListenerDescription> descriptions{description1};

    xmlReporter.listListeners(descriptions);

}



TEST_F(XmlReporterTest_848, ListListenersWithMultipleDescriptions_848) {

    ListenerDescription description1{"Name1", "Description1"};

    ListenerDescription description2{"Name2", "Description2"};

    std::vector<ListenerDescription> descriptions{description1, description2};

    xmlReporter.listListeners(descriptions);

}



TEST_F(XmlReporterTest_848, ListListenersWithLongDescriptions_848) {

    ListenerDescription description1{"Name1", "A very long and detailed description that goes on for a while"};

    std::vector<ListenerDescription> descriptions{description1};

    xmlReporter.listListeners(descriptions);

}



TEST_F(XmlReporterTest_848, ListListenersWithEmptyNames_848) {

    ListenerDescription description1{"", "Description1"};

    std::vector<ListenerDescription> descriptions{description1};

    xmlReporter.listListeners(descriptions);

}
