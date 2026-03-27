#include <gtest/gtest.h>

#include "exiv2/types.hpp"



using namespace Exiv2;



class DataBufTest_1128 : public ::testing::Test {

protected:

    DataBuf dataBuf;

};



TEST_F(DataBufTest_1128, CDataReturnsNullptrWhenOffsetIsEqualToSize_1128) {

    const size_t size = 5;

    byte testData[size] = {0};

    DataBuf db(testData, size);

    EXPECT_EQ(db.c_data(size), nullptr);

}



TEST_F(DataBufTest_1128, CDataReturnsNullptrWhenEmpty_1128) {

    DataBuf db;

    EXPECT_EQ(db.c_data(0), nullptr);

}



TEST_F(DataBufTest_1128, CDataThrowsExceptionWhenOffsetGreaterThanSize_1128) {

    const size_t size = 5;

    byte testData[size] = {0};

    DataBuf db(testData, size);

    EXPECT_THROW(db.c_data(size + 1), std::out_of_range);

}



TEST_F(DataBufTest_1128, CDataReturnsValidPointerForValidOffset_1128) {

    const size_t size = 5;

    byte testData[size] = {0};

    DataBuf db(testData, size);

    EXPECT_NE(db.c_data(0), nullptr);

}



TEST_F(DataBufTest_1128, CDataReturnsCorrectPointerForValidOffset_1128) {

    const size_t size = 5;

    byte testData[size] = {1, 2, 3, 4, 5};

    DataBuf db(testData, size);

    EXPECT_EQ(db.c_data(2), &testData[2]);

}



TEST_F(DataBufTest_1128, CDataReturnsNullptrForNegativeOffsetWhenTreatedAsSizeT_1128) {

    // Note: In C++, negative values passed to functions expecting size_t are typically

    // implicitly converted to very large positive values due to unsigned integer wrap-around.

    // This test checks the behavior when a large offset is provided, which should be out of range.

    const size_t size = 5;

    byte testData[size] = {0};

    DataBuf db(testData, size);

    EXPECT_EQ(db.c_data(static_cast<size_t>(-1)), nullptr);

}
