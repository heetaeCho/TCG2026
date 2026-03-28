#include <gtest/gtest.h>

#include "exiv2/types.hpp"



using namespace Exiv2;



class DataBufTest_1126 : public ::testing::Test {

protected:

    DataBuf dataBuf;

};



TEST_F(DataBufTest_1126, CmpBytesNormalOperation_1126) {

    const byte testData[] = {0x01, 0x02, 0x03};

    dataBuf.alloc(3);

    memcpy(dataBuf.data(0), testData, 3);



    EXPECT_EQ(0, dataBuf.cmpBytes(0, testData, 3));

}



TEST_F(DataBufTest_1126, CmpBytesPartialMatch_1126) {

    const byte testData[] = {0x01, 0x02, 0x03};

    dataBuf.alloc(3);

    memcpy(dataBuf.data(0), testData, 3);



    EXPECT_NE(0, dataBuf.cmpBytes(0, testData, 2));

}



TEST_F(DataBufTest_1126, CmpBytesOffset_1126) {

    const byte testData[] = {0x01, 0x02, 0x03};

    dataBuf.alloc(4);

    memcpy(dataBuf.data(1), testData, 3);



    EXPECT_EQ(0, dataBuf.cmpBytes(1, testData, 3));

}



TEST_F(DataBufTest_1126, CmpBytesBoundaryConditionStart_1126) {

    const byte testData[] = {0x01};

    dataBuf.alloc(1);

    memcpy(dataBuf.data(0), testData, 1);



    EXPECT_EQ(0, dataBuf.cmpBytes(0, testData, 1));

}



TEST_F(DataBufTest_1126, CmpBytesBoundaryConditionEnd_1126) {

    const byte testData[] = {0x03};

    dataBuf.alloc(3);

    memcpy(dataBuf.data(2), testData, 1);



    EXPECT_EQ(0, dataBuf.cmpBytes(2, testData, 1));

}



TEST_F(DataBufTest_1126, CmpBytesEmptyBuffer_1126) {

    const byte testData[] = {};

    dataBuf.alloc(3);



    EXPECT_EQ(0, dataBuf.cmpBytes(0, testData, 0));

}



TEST_F(DataBufTest_1126, CmpBytesSizeMismatch_1126) {

    const byte testData[] = {0x01, 0x02};

    dataBuf.alloc(3);

    memcpy(dataBuf.data(0), testData, 2);



    EXPECT_THROW(dataBuf.cmpBytes(0, testData, 4), std::out_of_range);

}



TEST_F(DataBufTest_1126, CmpBytesOffsetOverflow_1126) {

    const byte testData[] = {0x01};

    dataBuf.alloc(3);



    EXPECT_THROW(dataBuf.cmpBytes(4, testData, 1), std::out_of_range);

}



TEST_F(DataBufTest_1126, CmpBytesEmptyDataBuf_1126) {

    const byte testData[] = {0x01};



    EXPECT_THROW(dataBuf.cmpBytes(0, testData, 1), std::out_of_range);

}
