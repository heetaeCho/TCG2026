#include <gtest/gtest.h>

#include "Stream.h"



class CCITTFaxStreamTest_195 : public ::testing::Test {

protected:

    std::unique_ptr<Stream> dummyStream = std::make_unique<Stream>();

    int encoding = 0;

    bool endOfLine = false;

    bool byteAlign = false;

    int columns = 0;

    int rows = 0;

    bool endOfBlock = false;

    bool black = false;

    int damagedRowsBeforeError = 5;



    CCITTFaxStream* ccittFaxStream;



    void SetUp() override {

        ccittFaxStream = new CCITTFaxStream(std::move(dummyStream), encoding, endOfLine, byteAlign, columns, rows, endOfBlock, black, damagedRowsBeforeError);

    }



    void TearDown() override {

        delete ccittFaxStream;

    }

};



TEST_F(CCITTFaxStreamTest_195, GetDamagedRowsBeforeError_NormalOperation_195) {

    EXPECT_EQ(ccittFaxStream->getDamagedRowsBeforeError(), damagedRowsBeforeError);

}



TEST_F(CCITTFaxStreamTest_195, GetDamagedRowsBeforeError_BoundaryCondition_Zero_195) {

    CCITTFaxStream streamWithZero(std::move(dummyStream), encoding, endOfLine, byteAlign, columns, rows, endOfBlock, black, 0);

    EXPECT_EQ(streamWithZero.getDamagedRowsBeforeError(), 0);

}



TEST_F(CCITTFaxStreamTest_195, GetDamagedRowsBeforeError_BoundaryCondition_MaxInt_195) {

    CCITTFaxStream streamWithMaxInt(std::move(dummyStream), encoding, endOfLine, byteAlign, columns, rows, endOfBlock, black, std::numeric_limits<int>::max());

    EXPECT_EQ(streamWithMaxInt.getDamagedRowsBeforeError(), std::numeric_limits<int>::max());

}



TEST_F(CCITTFaxStreamTest_195, GetDamagedRowsBeforeError_BoundaryCondition_MinInt_195) {

    CCITTFaxStream streamWithMinInt(std::move(dummyStream), encoding, endOfLine, byteAlign, columns, rows, endOfBlock, black, std::numeric_limits<int>::min());

    EXPECT_EQ(streamWithMinInt.getDamagedRowsBeforeError(), std::numeric_limits<int>::min());

}
