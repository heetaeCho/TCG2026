#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_clara.hpp"



using namespace Catch;

using namespace Catch::Clara;



class OptTest : public ::testing::Test {

protected:

    bool flag = false;

    Opt opt{flag};

};



TEST_F(OptTest, GetHelpColumns_NoOptions_662) {

    auto helpColumns = opt.getHelpColumns();

    EXPECT_EQ(helpColumns.first, "");

    EXPECT_EQ(helpColumns.second, "");

}



TEST_F(OptTest, GetHelpColumns_OneOption_662) {

    opt["--option"];

    auto helpColumns = opt.getHelpColumns();

    EXPECT_EQ(helpColumns.first, "--option");

    EXPECT_EQ(helpColumns.second, "");

}



TEST_F(OptTest, GetHelpColumns_MultipleOptions_662) {

    opt["--option1"]["--option2"];

    auto helpColumns = opt.getHelpColumns();

    EXPECT_EQ(helpColumns.first, "--option1, --option2");

    EXPECT_EQ(helpColumns.second, "");

}



TEST_F(OptTest, GetHelpColumns_WithHint_662) {

    Opt optWithHint(flag, "hint");

    optWithHint["--option"];

    auto helpColumns = optWithHint.getHelpColumns();

    EXPECT_EQ(helpColumns.first, "--option <hint>");

    EXPECT_EQ(helpColumns.second, "");

}



TEST_F(OptTest, GetHelpColumns_WithDescription_662) {

    opt["--option"]("description");

    auto helpColumns = opt.getHelpColumns();

    EXPECT_EQ(helpColumns.first, "--option");

    EXPECT_EQ(helpColumns.second, "description");

}
