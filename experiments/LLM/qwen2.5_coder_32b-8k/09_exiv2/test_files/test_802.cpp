#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



class DataValueTest_802 : public ::testing::Test {

protected:

    TypeId typeId = static_cast<TypeId>(1); // Assuming a valid TypeId for testing

    std::unique_ptr<DataValue> dataValue;



    void SetUp() override {

        dataValue = std::make_unique<DataValue>(typeId);

    }

};



TEST_F(DataValueTest_802, ToRational_NormalOperation_802) {

    size_t n = 0;

    Rational result = dataValue->toRational(n);

    EXPECT_EQ(result.first, 1); // Assuming default value_.at(0) is 1

    EXPECT_EQ(result.second, 1);

}



TEST_F(DataValueTest_802, ToRational_BoundaryCondition_802) {

    size_t n = 0;

    Rational result = dataValue->toRational(n);

    EXPECT_EQ(result.first, 1); // Assuming default value_.at(0) is 1

    EXPECT_EQ(result.second, 1);



    n = dataValue->count() - 1; // Last valid index

    result = dataValue->toRational(n);

    EXPECT_EQ(result.first, 1); // Assuming default value_.at(count()-1) is 1

    EXPECT_EQ(result.second, 1);

}



TEST_F(DataValueTest_802, ToRational_ErrorCase_OutOfBounds_802) {

    size_t n = dataValue->count(); // Out of bounds index

    EXPECT_THROW(dataValue->toRational(n), std::out_of_range); // Assuming out_of_range is thrown for invalid index

}



TEST_F(DataValueTest_802, Ok_ReturnsTrue_AfterToRational_802) {

    size_t n = 0;

    dataValue->toRational(n);

    EXPECT_TRUE(dataValue->ok());

}
