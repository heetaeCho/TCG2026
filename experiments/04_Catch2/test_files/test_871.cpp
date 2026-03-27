#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_json.hpp"

#include "catch2/catch_assertion_result.hpp"

#include "catch2/interfaces/catch_interfaces_reporter.hpp"

#include <sstream>



using namespace Catch;

using namespace testing;



class JsonReporterTest : public Test {

protected:

    std::ostringstream oss;

    ReporterConfig config{oss};

    JsonReporter reporter{std::move(config)};



    AssertionInfo createAssertionInfo() {

        return AssertionInfo{"Expression", "File.cpp", 42, "Macro"};

    }



    AssertionResultData createAssertionResultData(bool isOk) {

        AssertionResultData data;

        ON_CALL(data, isOk()).WillByDefault(Return(isOk));

        return data;

    }



    AssertionStats createAssertionStats(bool isOk) {

        AssertionInfo info = createAssertionInfo();

        AssertionResultData resultData = createAssertionResultData(isOk);

        AssertionResult assertionResult(info, std::move(resultData));

        return AssertionStats(assertionResult, {}, Totals{});

    }

};



TEST_F(JsonReporterTest, AssertionEnded_StatusTrue_871) {

    AssertionStats stats = createAssertionStats(true);

    reporter.assertionEnded(stats);

}



TEST_F(JsonReporterTest, AssertionEnded_StatusFalse_871) {

    AssertionStats stats = createAssertionStats(false);

    reporter.assertionEnded(stats);

}



TEST_F(JsonReporterTest, AssertionEnded_ValidSourceInfo_871) {

    AssertionStats stats = createAssertionStats(true);

    EXPECT_CALL(stats.assertionResult.getSourceInfo(), getFile()).WillOnce(Return("File.cpp"));

    EXPECT_CALL(stats.assertionResult.getSourceInfo(), getLine()).WillOnce(Return(42));

    reporter.assertionEnded(stats);

}



TEST_F(JsonReporterTest, AssertionEnded_ValidKind_871) {

    AssertionStats stats = createAssertionStats(true);

    reporter.assertionEnded(stats);

}
