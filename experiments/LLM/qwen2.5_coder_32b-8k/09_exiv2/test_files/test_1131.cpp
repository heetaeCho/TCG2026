#include <gtest/gtest.h>

#include "exiv2/types.hpp"



namespace Exiv2 {



class SliceTest_1131 : public ::testing::Test {

protected:

    DataBuf dataBuf;

    const size_t bufferSize = 10;



    void SetUp() override {

        byte initialData[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

        dataBuf = DataBuf(initialData, bufferSize);

    }

};



TEST_F(SliceTest_1131, NormalOperation_1131) {

    Slice<byte*> slice = makeSlice(dataBuf, 2, 5);

    EXPECT_EQ(slice.begin_, dataBuf.data() + 2);

    EXPECT_EQ(slice.end_, dataBuf.data() + 5);

}



TEST_F(SliceTest_1131, BoundaryConditions_Start_1131) {

    Slice<byte*> slice = makeSlice(dataBuf, 0, bufferSize);

    EXPECT_EQ(slice.begin_, dataBuf.data());

    EXPECT_EQ(slice.end_, dataBuf.data() + bufferSize);

}



TEST_F(SliceTest_1131, BoundaryConditions_End_1131) {

    Slice<byte*> slice = makeSlice(dataBuf, 5, bufferSize);

    EXPECT_EQ(slice.begin_, dataBuf.data() + 5);

    EXPECT_EQ(slice.end_, dataBuf.data() + bufferSize);

}



TEST_F(SliceTest_1131, ExceptionalCase_OutOfBounds_1131) {

    EXPECT_THROW(makeSlice(dataBuf, 0, bufferSize + 1), std::out_of_range);

}



TEST_F(SliceTest_1131, ExceptionalCase_StartGreaterThanEnd_1131) {

    EXPECT_THROW(makeSlice(dataBuf, 5, 2), std::invalid_argument);

}



} // namespace Exiv2
