#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/types.cpp"



namespace Exiv2 {

    class URational {

    public:

        using value_type = std::pair<int, int>;

        URational(int numerator, int denominator) : first(numerator), second(denominator) {}

        value_type first;

        value_type second;

    };

}



using namespace ::testing;



TEST(URationalOutputTest_1135, NormalOperation_1135) {

    Exiv2::URational ur(1, 2);

    std::ostringstream oss;

    oss << ur;

    EXPECT_EQ("1/2", oss.str());

}



TEST(URationalOutputTest_1135, BoundaryConditionZeroDenominator_1135) {

    Exiv2::URational ur(1, 0);

    std::ostringstream oss;

    oss << ur;

    EXPECT_EQ("1/0", oss.str());

}



TEST(URationalOutputTest_1135, BoundaryConditionNegativeNumerator_1135) {

    Exiv2::URational ur(-1, 2);

    std::ostringstream oss;

    oss << ur;

    EXPECT_EQ("-1/2", oss.str());

}



TEST(URationalOutputTest_1135, BoundaryConditionNegativeDenominator_1135) {

    Exiv2::URational ur(1, -2);

    std::ostringstream oss;

    oss << ur;

    EXPECT_EQ("1/-2", oss.str());

}



TEST(URationalOutputTest_1135, BoundaryConditionBothNegative_1135) {

    Exiv2::URational ur(-1, -2);

    std::ostringstream oss;

    oss << ur;

    EXPECT_EQ("-1/-2", oss.str());

}
