#include <gtest/gtest.h>

#include "catch2/reporters/catch_reporter_json.hpp"

#include "catch2/internal/catch_stringref.hpp"



using namespace Catch;



class JsonReporterTest_872 : public ::testing::Test {

protected:

    JsonReporter* reporter;



    void SetUp() override {

        ReporterConfig config;

        reporter = new JsonReporter(std::move(config));

    }



    void TearDown() override {

        delete reporter;

    }

};



TEST_F(JsonReporterTest_872, BenchmarkPreparing_NoCrashWithEmptyString_872) {

    StringRef name("");

    EXPECT_NO_THROW(reporter->benchmarkPreparing(name));

}



TEST_F(JsonReporterTest_872, BenchmarkPreparing_NoCrashWithNonEmptyString_872) {

    StringRef name("BenchmarkName");

    EXPECT_NO_THROW(reporter->benchmarkPreparing(name));

}



TEST_F(JsonReporterTest_872, BenchmarkPreparing_NoCrashWithNullptr_872) {

    const char* rawChars = nullptr;

    StringRef name(rawChars);

    EXPECT_NO_THROW(reporter->benchmarkPreparing(name));

}
