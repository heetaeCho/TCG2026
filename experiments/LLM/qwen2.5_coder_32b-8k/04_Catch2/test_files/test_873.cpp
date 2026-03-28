#include <gtest/gtest.h>

#include "catch2/reporters/catch_reporter_json.hpp"



namespace Catch {

    class JsonReporter;

}



using namespace Catch;



class JsonReporterTest_873 : public ::testing::Test {

protected:

    JsonReporter* reporter = nullptr;



    void SetUp() override {

        ReporterConfig config; // Assuming a default constructor for ReporterConfig

        reporter = new JsonReporter(std::move(config));

    }



    void TearDown() override {

        delete reporter;

        reporter = nullptr;

    }

};



TEST_F(JsonReporterTest_873, BenchmarkFailed_NoError_873) {

    StringRef error("");

    EXPECT_NO_THROW(reporter->benchmarkFailed(error));

}



TEST_F(JsonReporterTest_873, BenchmarkFailed_NonEmptyError_873) {

    StringRef error("Some benchmark failed");

    EXPECT_NO_THROW(reporter->benchmarkFailed(error));

}



TEST_F(JsonReporterTest_873, BenchmarkFailed_LongErrorMessage_873) {

    std::string longErrorMessage(1024, 'a'); // 1024 characters of 'a'

    StringRef error(longErrorMessage);

    EXPECT_NO_THROW(reporter->benchmarkFailed(error));

}
