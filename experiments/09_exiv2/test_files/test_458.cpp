#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include <Exiv2/nikonmn_int.hpp>



using namespace Exiv2::Internal;

using ::testing::Test;



class PrintFlashCompensationValueTest_458 : public Test {

protected:

    std::ostringstream os;

};



TEST_F(PrintFlashCompensationValueTest_458, NormalOperationManualScale_458) {

    printFlashCompensationValue(os, 3, true);

    EXPECT_EQ(os.str(), "1/1 (-1/2 EV)");

}



TEST_F(PrintFlashCompensationValueTest_458, BoundaryConditionManualScaleMin_458) {

    printFlashCompensationValue(os, 0, true);

    EXPECT_EQ(os.str(), "1/1");

}



TEST_F(PrintFlashCompensationValueTest_458, BoundaryConditionManualScaleMax_458) {

    printFlashCompensationValue(os, 48, true);

    EXPECT_EQ(os.str(), "1/256");

}



TEST_F(PrintFlashCompensationValueTest_458, OutOfBoundsManualScale_458) {

    printFlashCompensationValue(os, 49, true);

    EXPECT_EQ(os.str(), "(49)");

}



TEST_F(PrintFlashCompensationValueTest_458, NormalOperationAutoScalePositive_458) {

    printFlashCompensationValue(os, 130, false);

    EXPECT_EQ(os.str(), "+21.0 EV");

}



TEST_F(PrintFlashCompensationValueTest_458, NormalOperationAutoScaleNegative_458) {

    printFlashCompensationValue(os, 7, false);

    EXPECT_EQ(os.str(), "-1.2 EV");

}



TEST_F(PrintFlashCompensationValueTest_458, BoundaryConditionAutoScaleZero_458) {

    printFlashCompensationValue(os, 0, false);

    EXPECT_EQ(os.str(), "0.0EV");

}



TEST_F(PrintFlashCompensationValueTest_458, BoundaryConditionAutoScaleMinPositive_458) {

    printFlashCompensationValue(os, 128, false);

    EXPECT_EQ(os.str(), "+21.3 EV");

}



TEST_F(PrintFlashCompensationValueTest_458, BoundaryConditionAutoScaleMaxNegative_458) {

    printFlashCompensationValue(os, 255, false);

    EXPECT_EQ(os.str(), "+0.2 EV");

}
