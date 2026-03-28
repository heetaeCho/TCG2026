#include <gtest/gtest.h>

#include "exiv2/exif.hpp"



namespace Exiv2 {



class ExifdatumTest_736 : public ::testing::Test {

protected:

    ExifKey key;

    Value* pValue = nullptr;

    Exifdatum exifdatum;



    ExifdatumTest_736() : exifdatum(key, pValue) {}

};



TEST_F(ExifdatumTest_736, AssignmentOperatorInt32_NormalOperation_736) {

    int32_t value = 12345;

    Exifdatum& result = exifdatum.operator=(value);

    EXPECT_EQ(&result, &exifdatum); // Check that the assignment operator returns *this

}



TEST_F(ExifdatumTest_736, AssignmentOperatorInt32_BoundaryConditionMin_736) {

    int32_t minValue = std::numeric_limits<int32_t>::min();

    Exifdatum& result = exifdatum.operator=(minValue);

    EXPECT_EQ(&result, &exifdatum); // Check that the assignment operator returns *this

}



TEST_F(ExifdatumTest_736, AssignmentOperatorInt32_BoundaryConditionMax_736) {

    int32_t maxValue = std::numeric_limits<int32_t>::max();

    Exifdatum& result = exifdatum.operator=(maxValue);

    EXPECT_EQ(&result, &exifdatum); // Check that the assignment operator returns *this

}



} // namespace Exiv2
