#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tags_int.cpp"

#include <sstream>



using namespace Exiv2::Internal;

using ::testing::_;



class Print0x0007Test_1386 : public ::testing::Test {

protected:

    Value value;

    std::ostringstream os;



    void SetUp() override {

        // Setup any common state before tests (if needed)

    }



    void TearDown() override {

        // Cleanup any common state after tests (if needed)

    }

};



TEST_F(Print0x0007Test_1386, NormalOperation_1386) {

    value = Value(std::vector<Rational>({{3600, 1}, {60, 1}, {45, 1}}));

    print0x0007(os, value, nullptr);

    EXPECT_EQ(os.str(), "01:01:45");

}



TEST_F(Print0x0007Test_1386, BoundaryCondition_ZeroTime_1386) {

    value = Value(std::vector<Rational>({{0, 1}, {0, 1}, {0, 1}}));

    print0x0007(os, value, nullptr);

    EXPECT_EQ(os.str(), "00:00:00");

}



TEST_F(Print0x0007Test_1386, BoundaryCondition_MaxTime_1386) {

    value = Value(std::vector<Rational>({{24, 1}, {59, 1}, {59, 1}}));

    print0x0007(os, value, nullptr);

    EXPECT_EQ(os.str(), "24:59:59");

}



TEST_F(Print0x0007Test_1386, BoundaryCondition_OverflowHours_1386) {

    value = Value(std::vector<Rational>({{25, 1}, {0, 1}, {0, 1}}));

    print0x0007(os, value, nullptr);

    EXPECT_EQ(os.str(), "01:00:00");

}



TEST_F(Print0x0007Test_1386, BoundaryCondition_FractionalSeconds_1386) {

    value = Value(std::vector<Rational>({{0, 1}, {0, 1}, {455, 10}}));

    print0x0007(os, value, nullptr);

    EXPECT_EQ(os.str(), "00:00:45.5");

}



TEST_F(Print0x0007Test_1386, ErrorCase_NonFiniteTimeValue_1386) {

    value = Value(std::vector<Rational>({{std::numeric_limits<int>::max(), 1}, {0, 1}, {0, 1}}));

    EXPECT_THROW(print0x0007(os, value, nullptr), std::overflow_error);

}



TEST_F(Print0x0007Test_1386, ErrorCase_ZeroDenominator_1386) {

    value = Value(std::vector<Rational>({{1, 0}, {1, 1}, {1, 1}}));

    print0x0007(os, value, nullptr);

    EXPECT_EQ(os.str(), "(1/0)");

}



TEST_F(Print0x0007Test_1386, ErrorCase_ValueCountNotThree_1386) {

    value = Value(std::vector<Rational>({{1, 1}, {1, 1}}));

    print0x0007(os, value, nullptr);

    EXPECT_EQ(os.str(), "1/1 1/1");

}
