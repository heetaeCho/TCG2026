#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "fujimn_int.cpp"  // Assuming this is how we include the partial implementation



namespace Exiv2 {

namespace Internal {



class ValueMock : public Exiv2::Value {

public:

    MOCK_CONST_METHOD0(size, size_t());

    MOCK_CONST_METHOD0(toInt64, int64_t());

};



TEST_F(PrintFujiMonochromaticColorTest_624, SingleValuePositive_624) {

    ValueMock valueMock;

    EXPECT_CALL(valueMock, size()).WillOnce(::testing::Return(1));

    EXPECT_CALL(valueMock, toInt64()).WillOnce(::testing::Return(5));



    std::ostringstream os;

    printFujiMonochromaticColor(os, valueMock, nullptr);

    EXPECT_EQ("+5", os.str());

}



TEST_F(PrintFujiMonochromaticColorTest_624, SingleValueZero_624) {

    ValueMock valueMock;

    EXPECT_CALL(valueMock, size()).WillOnce(::testing::Return(1));

    EXPECT_CALL(valueMock, toInt64()).WillOnce(::testing::Return(0));



    std::ostringstream os;

    printFujiMonochromaticColor(os, valueMock, nullptr);

    EXPECT_EQ("0", os.str());

}



TEST_F(PrintFujiMonochromaticColorTest_624, SingleValueNegative_624) {

    ValueMock valueMock;

    EXPECT_CALL(valueMock, size()).WillOnce(::testing::Return(1));

    EXPECT_CALL(valueMock, toInt64()).WillOnce(::testing::Return(-3));



    std::ostringstream os;

    printFujiMonochromaticColor(os, valueMock, nullptr);

    EXPECT_EQ("-3", os.str());

}



TEST_F(PrintFujiMonochromaticColorTest_624, MultipleValues_624) {

    ValueMock valueMock;

    EXPECT_CALL(valueMock, size()).WillOnce(::testing::Return(2));

    // No need to mock toInt64 as it won't be called



    std::ostringstream os;

    printFujiMonochromaticColor(os, valueMock, nullptr);

    EXPECT_EQ("(value)", os.str());  // Assuming the output is literally "(value)" when size() != 1

}



}  // namespace Internal

}  // namespace Exiv2
