#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/reporters/catch_reporter_helpers.hpp"

#include <sstream>

#include <vector>



using namespace Catch;



class ReporterDescriptionMock : public ReporterDescription {

public:

    ReporterDescriptionMock(const std::string& name, const std::string& description)

        : ReporterDescription({description}), name(name) {}



    std::string name;

};



TEST(defaultListReportersTest_821, NormalOperationQuietVerbosity_821) {

    std::ostringstream oss;

    std::vector<ReporterDescriptionMock> descriptions = {

        {"Console", "Reports results to console"},

        {"Junit", "Generates JUnit report"}

    };

    defaultListReporters(oss, descriptions, Verbosity::Quiet);

    EXPECT_EQ(oss.str(), "Available reporters:\n  Console\n  Junit\n\n");

}



TEST(defaultListReportersTest_821, NormalOperationNormalVerbosity_821) {

    std::ostringstream oss;

    std::vector<ReporterDescriptionMock> descriptions = {

        {"Console", "Reports results to console"},

        {"Junit", "Generates JUnit report"}

    };

    defaultListReporters(oss, descriptions, Verbosity::Normal);

    EXPECT_EQ(oss.str(), "Available reporters:\n  Console: Reports results to console\n  Junit: Generates JUnit report\n\n");

}



TEST(defaultListReportersTest_821, SingleReporterQuietVerbosity_821) {

    std::ostringstream oss;

    std::vector<ReporterDescriptionMock> descriptions = {

        {"Console", "Reports results to console"}

    };

    defaultListReporters(oss, descriptions, Verbosity::Quiet);

    EXPECT_EQ(oss.str(), "Available reporters:\n  Console\n\n");

}



TEST(defaultListReportersTest_821, SingleReporterNormalVerbosity_821) {

    std::ostringstream oss;

    std::vector<ReporterDescriptionMock> descriptions = {

        {"Console", "Reports results to console"}

    };

    defaultListReporters(oss, descriptions, Verbosity::Normal);

    EXPECT_EQ(oss.str(), "Available reporters:\n  Console: Reports results to console\n\n");

}



TEST(defaultListReportersTest_821, EmptyDescriptions_821) {

    std::ostringstream oss;

    std::vector<ReporterDescriptionMock> descriptions = {};

    defaultListReporters(oss, descriptions, Verbosity::Normal);

    EXPECT_EQ(oss.str(), "Available reporters:\n\n");

}



TEST(defaultListReportersTest_821, LongNamesQuietVerbosity_821) {

    std::ostringstream oss;

    std::vector<ReporterDescriptionMock> descriptions = {

        {"ShortName", "A short name"},

        {"AVeryLongReporterNameIndeed", "This is a very long reporter name"}

    };

    defaultListReporters(oss, descriptions, Verbosity::Quiet);

    EXPECT_EQ(oss.str(), "Available reporters:\n  ShortName\n  AVeryLongReporterNameIndeed\n\n");

}



TEST(defaultListReportersTest_821, LongNamesNormalVerbosity_821) {

    std::ostringstream oss;

    std::vector<ReporterDescriptionMock> descriptions = {

        {"ShortName", "A short name"},

        {"AVeryLongReporterNameIndeed", "This is a very long reporter name"}

    };

    defaultListReporters(oss, descriptions, Verbosity::Normal);

    EXPECT_EQ(oss.str(), "Available reporters:\n  ShortName: A short name\n  AVeryLongReporterNameIndeed: This is a very long reporter name\n\n");

}
