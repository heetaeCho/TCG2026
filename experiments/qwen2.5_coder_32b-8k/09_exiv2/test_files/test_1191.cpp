#include <gtest/gtest.h>

#include "exiv2/bmffimage.hpp"



using namespace Exiv2;



class IlocTest_1191 : public ::testing::Test {

protected:

    Iloc defaultIloc;

    Iloc customIloc;



    IlocTest_1191() : defaultIloc(0, 0, 0), customIloc(42, 100, 50) {}

};



TEST_F(IlocTest_1191, DefaultConstructorInitializesValuesToZero_1191) {

    EXPECT_EQ(defaultIloc.ID_, 0);

    EXPECT_EQ(defaultIloc.start_, 0);

    EXPECT_EQ(defaultIloc.length_, 0);

}



TEST_F(IlocTest_1191, ParameterizedConstructorSetsCorrectValues_1191) {

    EXPECT_EQ(customIloc.ID_, 42);

    EXPECT_EQ(customIloc.start_, 100);

    EXPECT_EQ(customIloc.length_, 50);

}



TEST_F(IlocTest_1191, ToStringReturnsFormattedStringWithDefaultValues_1191) {

    std::string expected = "ID = 0 from,length = 0,0";

    EXPECT_EQ(defaultIloc.toString(), expected);

}



TEST_F(IlocTest_1191, ToStringReturnsFormattedStringWithCustomValues_1191) {

    std::string expected = "ID = 42 from,length = 100,50";

    EXPECT_EQ(customIloc.toString(), expected);

}



TEST_F(IlocTest_1191, BoundaryConditionsWithZeroLength_1191) {

    Iloc boundaryIloc(1, 2, 0);

    std::string expected = "ID = 1 from,length = 2,0";

    EXPECT_EQ(boundaryIloc.toString(), expected);

}



TEST_F(IlocTest_1191, BoundaryConditionsWithMaximumValues_1191) {

    Iloc boundaryIloc(UINT32_MAX, UINT32_MAX, UINT32_MAX);

    std::string expected = "ID = 4294967295 from,length = 4294967295,4294967295";

    EXPECT_EQ(boundaryIloc.toString(), expected);

}
