#include <gtest/gtest.h>

#include "catch_reporter_tap.hpp"

#include "catch_interfaces_reporter.hpp"



namespace Catch {

    struct MockAssertionStats : AssertionStats {

        MockAssertionStats(AssertionResult result) : AssertionStats(result, {}, Totals{}) {}

    };

}



class TAPReporterTest_747 : public ::testing::Test {

protected:

    Catch::TAPReporter reporter{Catch::ReporterConfig{}};

    std::ostringstream outputStream;

    Catch::MockAssertionStats assertionStatsPass{Catch::ResultWas::Ok};

    Catch::MockAssertionStats assertionStatsFail{Catch::ResultWas::ExpressionFailed};



    TAPReporterTest_747() {

        reporter.m_stream.rdbuf(outputStream.rdbuf());

    }

};



TEST_F(TAPReporterTest_747, AssertionEndedPassesPrintsCorrectOutput_747) {

    reporter.assertionEnded(assertionStatsPass);

    EXPECT_EQ(outputStream.str(), "# \nnot ok 1 - \n\n");

}



TEST_F(TAPReporterTest_747, AssertionEndedFailsPrintsCorrectOutput_747) {

    reporter.assertionEnded(assertionStatsFail);

    EXPECT_EQ(outputStream.str(), "# \nnot ok 1 - \n\n");

}



TEST_F(TAPReporterTest_747, MultipleAssertionsIncrementCounter_747) {

    reporter.assertionEnded(assertionStatsPass);

    reporter.assertionEnded(assertionStatsFail);

    reporter.assertionEnded(assertionStatsPass);



    std::string expectedOutput = "# \nnot ok 1 - \n\n# \nnot ok 2 - \n\n# \nnot ok 3 - \n\n";

    EXPECT_EQ(outputStream.str(), expectedOutput);

}



TEST_F(TAPReporterTest_747, AssertionEndedNoCurrentTestCaseInfoDoesNotCrash_747) {

    reporter.currentTestCaseInfo = nullptr;

    EXPECT_NO_THROW(reporter.assertionEnded(assertionStatsPass));

}



TEST_F(TAPReporterTest_747, AssertionEndedWithCurrentTestCaseInfoPrintsName_747) {

    Catch::TestCaseInfo testCaseInfo("ClassName", {"TestName"}, {});

    reporter.currentTestCaseInfo = &testCaseInfo;

    reporter.assertionEnded(assertionStatsPass);



    std::string expectedOutput = "# TestName\nnot ok 1 - \n\n";

    EXPECT_EQ(outputStream.str(), expectedOutput);

}



TEST_F(TAPReporterTest_747, AssertionEndedWithEmptyCurrentTestCaseInfoPrintsDefault_747) {

    Catch::TestCaseInfo testCaseInfo("ClassName", {"", ""}, {});

    reporter.currentTestCaseInfo = &testCaseInfo;

    reporter.assertionEnded(assertionStatsPass);



    std::string expectedOutput = "# \nnot ok 1 - \n\n";

    EXPECT_EQ(outputStream.str(), expectedOutput);

}
