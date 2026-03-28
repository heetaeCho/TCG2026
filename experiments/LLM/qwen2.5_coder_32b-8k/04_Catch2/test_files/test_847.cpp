#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_reporter_xml.hpp"

#include "catch_xmlwriter.hpp"



using namespace Catch;

using namespace testing;



class XmlReporterTest_847 : public Test {

protected:

    std::ostringstream oss;

    XmlWriter mockXmlWriter{oss};

    XmlReporter xmlReporter{ReporterConfig{"test_config"}};



    void SetUp() override {

        // Redirect the internal XmlWriter to our mock writer for observation

        new (&xmlReporter.m_xml) XmlWriter(oss);

    }

};



TEST_F(XmlReporterTest_847, ListReportersWithEmptyDescriptions_847) {

    std::vector<ReporterDescription> descriptions;

    xmlReporter.listReporters(descriptions);



    EXPECT_EQ(oss.str(), "<AvailableReporters/>\n");

}



TEST_F(XmlReporterTest_847, ListReportersWithSingleDescription_847) {

    std::vector<ReporterDescription> descriptions = {{"reporter_name", "reporter_description"}};

    xmlReporter.listReporters(descriptions);



    EXPECT_EQ(oss.str(), 

        "<AvailableReporters>\n"

        "  <Reporter>\n"

        "    <Name>reporter_name</Name>\n"

        "    <Description>reporter_description</Description>\n"

        "  </Reporter>\n"

        "</AvailableReporters>\n");

}



TEST_F(XmlReporterTest_847, ListReportersWithMultipleDescriptions_847) {

    std::vector<ReporterDescription> descriptions = {

        {"reporter_name1", "reporter_description1"},

        {"reporter_name2", "reporter_description2"}

    };

    xmlReporter.listReporters(descriptions);



    EXPECT_EQ(oss.str(), 

        "<AvailableReporters>\n"

        "  <Reporter>\n"

        "    <Name>reporter_name1</Name>\n"

        "    <Description>reporter_description1</Description>\n"

        "  </Reporter>\n"

        "  <Reporter>\n"

        "    <Name>reporter_name2</Name>\n"

        "    <Description>reporter_description2</Description>\n"

        "  </Reporter>\n"

        "</AvailableReporters>\n");

}
