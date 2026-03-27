#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <Exiv2/exiv2.hpp>

#include "tags_int.cpp" // Assuming this file contains the implementation of print0x9202



using namespace Exiv2;

using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Return;



class ValueMock : public Value {

public:

    MOCK_CONST_METHOD0(count, size_t());

    MOCK_CONST_METHOD0(toRational, Rational<int64_t>());

    MOCK_CONST_METHOD0(toFloat, float());

};



TEST_F(Print0x9202Test_1401, NormalOperationWithValueCountZero_1401) {

    ValueMock mockValue;

    EXPECT_CALL(mockValue, count()).WillOnce(Return(0));



    std::ostringstream os;

    print0x9202(os, mockValue, nullptr);

    EXPECT_EQ(os.str(), "(<mock>)");

}



TEST_F(Print0x9202Test_1401, NormalOperationWithRationalSecondZero_1401) {

    ValueMock mockValue;

    EXPECT_CALL(mockValue, count()).WillOnce(Return(1));

    EXPECT_CALL(mockValue, toRational()).WillOnce(Return(Rational<int64_t>(1, 0)));



    std::ostringstream os;

    print0x9202(os, mockValue, nullptr);

    EXPECT_EQ(os.str(), "(<mock>)");

}



TEST_F(Print0x9202Test_1401, NormalOperationWithNonZeroRationalSecond_1401) {

    ValueMock mockValue;

    EXPECT_CALL(mockValue, count()).WillOnce(Return(1));

    EXPECT_CALL(mockValue, toRational()).WillOnce(Return(Rational<int64_t>(5, 2)));

    EXPECT_CALL(mockValue, toFloat()).WillOnce(Return(2.5f));



    std::ostringstream os;

    print0x9202(os, mockValue, nullptr);

    EXPECT_EQ(os.str(), "F2.5");

}



TEST_F(Print0x9202Test_1401, BoundaryConditionWithSmallFloatValue_1401) {

    ValueMock mockValue;

    EXPECT_CALL(mockValue, count()).WillOnce(Return(1));

    EXPECT_CALL(mockValue, toRational()).WillOnce(Return(Rational<int64_t>(1, 100000)));

    EXPECT_CALL(mockValue, toFloat()).WillOnce(Return(0.00001f));



    std::ostringstream os;

    print0x9202(os, mockValue, nullptr);

    EXPECT_EQ(os.str(), "F1e-05");

}



TEST_F(Print0x9202Test_1401, BoundaryConditionWithLargeFloatValue_1401) {

    ValueMock mockValue;

    EXPECT_CALL(mockValue, count()).WillOnce(Return(1));

    EXPECT_CALL(mockValue, toRational()).WillOnce(Return(Rational<int64_t>(100000, 1)));

    EXPECT_CALL(mockValue, toFloat()).WillOnce(Return(100000.0f));



    std::ostringstream os;

    print0x9202(os, mockValue, nullptr);

    EXPECT_EQ(os.str(), "F1e+05");

}
