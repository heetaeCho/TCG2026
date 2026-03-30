#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/reporters/catch_reporter_helpers.hpp"

#include <sstream>



using namespace Catch;

using namespace testing;



TEST(ReporterHelpersTests_820, NormalOperationPrintsCorrectNumberOfChars_820) {

    std::ostringstream oss;

    lineOfChars loc('*');

    oss << loc;

    EXPECT_EQ(oss.str().length(), CATCH_CONFIG_CONSOLE_WIDTH - 1);

    EXPECT_TRUE(std::all_of(oss.str().begin(), oss.str().end(), [](char c){ return c == '*'; }));

}



TEST(ReporterHelpersTests_820, BoundaryConditionConsoleWidthZeroDoesNotPrint_820) {

    std::ostringstream oss;

    lineOfChars loc('*');

#define CATCH_CONFIG_CONSOLE_WIDTH 0

    oss << loc;

#undef CATCH_CONFIG_CONSOLE_WIDTH

    EXPECT_EQ(oss.str().length(), 0);

}



TEST(ReporterHelpersTests_820, BoundaryConditionConsoleWidthOnePrintsSingleChar_820) {

    std::ostringstream oss;

    lineOfChars loc('*');

#define CATCH_CONFIG_CONSOLE_WIDTH 1

    oss << loc;

#undef CATCH_CONFIG_CONSOLE_WIDTH

    EXPECT_EQ(oss.str().length(), 0); // Since loop runs till CATCH_CONFIG_CONSOLE_WIDTH - 1, it should be 0

}



TEST(ReporterHelpersTests_820, BoundaryConditionConsoleWidthLargePrintsCorrectNumberOfChars_820) {

    std::ostringstream oss;

    lineOfChars loc('*');

#define CATCH_CONFIG_CONSOLE_WIDTH 1000

    oss << loc;

#undef CATCH_CONFIG_CONSOLE_WIDTH

    EXPECT_EQ(oss.str().length(), 999);

    EXPECT_TRUE(std::all_of(oss.str().begin(), oss.str().end(), [](char c){ return c == '*'; }));

}
