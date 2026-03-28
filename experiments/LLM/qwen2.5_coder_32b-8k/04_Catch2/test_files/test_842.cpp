#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "catch_reporter_xml.hpp"

#include "catch_totals.hpp"

#include "catch_interfaces_reporter.hpp"

#include <sstream>



using namespace Catch;

using ::testing::_;

using ::testing::InSequence;



class XmlReporterTest_842 : public ::testing::Test {

protected:

    std::ostringstream outputStream;

    ReporterConfig config;

    XmlReporter xmlReporter{CATCH_MOVE(config)};

    Totals totals;

    TestRunInfo testRunInfo{"test suite"};

    TestRunStats testRunStats{testRunInfo, totals, false};



    void SetUp() override {

        xmlReporter.m_xml = XmlWriter(outputStream);

    }



    std::string getOutput() {

        return outputStream.str();

    }

};



TEST_F(XmlReporterTest_842, TestRunEnded_EmptyTotals_842) {

    xmlReporter.testRunEnded(testRunStats);



    EXPECT_EQ(getOutput(), R"(<OverallResults successes="0" failures="0" expectedFailures="0" skips="0"/>

<OverallResultsCases successes="0" failures="0" expectedFailures="0" skips="0"/>)");

}



TEST_F(XmlReporterTest_842, TestRunEnded_AllCountsPositive_842) {

    totals.assertions = {1, 2, 3, 4};

    totals.testCases = {5, 6, 7, 8};



    xmlReporter.testRunEnded(testRunStats);



    EXPECT_EQ(getOutput(), R"(<OverallResults successes="1" failures="2" expectedFailures="3" skips="4"/>

<OverallResultsCases successes="5" failures="6" expectedFailures="7" skips="8"/>)");

}



TEST_F(XmlReporterTest_842, TestRunEnded_BoundaryConditions_842) {

    totals.assertions = {0, 1, 0, 1};

    totals.testCases = {1, 0, 1, 0};



    xmlReporter.testRunEnded(testRunStats);



    EXPECT_EQ(getOutput(), R"(<OverallResults successes="0" failures="1" expectedFailures="0" skips="1"/>

<OverallResultsCases successes="1" failures="0" expectedFailures="1" skips="0"/>)");

}



TEST_F(XmlReporterTest_842, TestRunEnded_MaxCounts_842) {

    totals.assertions = {std::numeric_limits<std::uint64_t>::max(), 0, 0, 0};

    totals.testCases = {0, std::numeric_limits<std::uint64_t>::max(), 0, 0};



    xmlReporter.testRunEnded(testRunStats);



    EXPECT_EQ(getOutput(),

              "<OverallResults successes=\"" + std::to_string(std::numeric_limits<std::uint64_t>::max()) +

                  "\" failures=\"0\" expectedFailures=\"0\" skips=\"0\"/>"

                  "<OverallResultsCases successes=\"0\" failures=\"" +

                  std::to_string(std::numeric_limits<std::uint64_t>::max()) + "\" expectedFailures=\"0\" skips=\"0\"/>");

}
