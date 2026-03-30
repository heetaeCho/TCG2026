#include <gtest/gtest.h>

#include "catch2/reporters/catch_reporter_tap.hpp"

#include "catch2/internal/catch_stringref.hpp"



using namespace Catch;



class TAPReporterTest_746 : public ::testing::Test {

protected:

    std::ostringstream stream;

    ReporterConfig config{Detail::unique_ptr<IStream>(new OstreamRaii(stream)), ColourMode::None, ""};

    TAPReporter reporter{CATCH_MOVE(config)};

};



TEST_F(TAPReporterTest_746, NoMatchingTestCases_EmptySpec_746) {

    StringRef spec("");

    reporter.noMatchingTestCases(spec);

    EXPECT_EQ("# No test cases matched ''\n", stream.str());

}



TEST_F(TAPReporterTest_746, NoMatchingTestCases_NonEmptySpec_746) {

    StringRef spec("test_spec");

    reporter.noMatchingTestCases(spec);

    EXPECT_EQ("# No test cases matched 'test_spec'\n", stream.str());

}



TEST_F(TAPReporterTest_746, NoMatchingTestCases_SpecialCharactersInSpec_746) {

    StringRef spec("!@#$%^&*()");

    reporter.noMatchingTestCases(spec);

    EXPECT_EQ("# No test cases matched '!@#$%^&*()'\n", stream.str());

}
