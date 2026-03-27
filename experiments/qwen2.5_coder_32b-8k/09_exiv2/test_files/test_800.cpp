#include <gtest/gtest.h>

#include <exiv2/value.hpp>



using namespace Exiv2;



class DataValueTest_800 : public ::testing::Test {

protected:

    TypeId typeId = TypeId::unsignedLong;

    DataValue dataValue{typeId};

};



TEST_F(DataValueTest_800, ToUint32_NormalOperation_800) {

    // Arrange

    std::vector<uint32_t> values = {10, 20, 30};

    dataValue.value_ = values;



    // Act & Assert

    EXPECT_EQ(dataValue.toUint32(0), 10);

    EXPECT_EQ(dataValue.toUint32(1), 20);

    EXPECT_EQ(dataValue.toUint32(2), 30);

}



TEST_F(DataValueTest_800, ToUint32_BoundaryCondition_800) {

    // Arrange

    std::vector<uint32_t> values = {42};

    dataValue.value_ = values;



    // Act & Assert

    EXPECT_EQ(dataValue.toUint32(0), 42);

}



TEST_F(DataValueTest_800, ToUint32_OutOfBounds_800) {

    // Arrange

    std::vector<uint32_t> values = {10};

    dataValue.value_ = values;



    // Act & Assert

    EXPECT_THROW(dataValue.toUint32(1), std::out_of_range);

}



TEST_F(DataValueTest_800, ToUint32_ErrorCase_800) {

    // Arrange

    dataValue.ok_ = false;



    // Act & Assert

    EXPECT_THROW(dataValue.toUint32(0), Error);

}
