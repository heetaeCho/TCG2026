#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming necessary includes for OPJ_BOOL, OPJ_OFF_T are present in JPEG2000Stream.cc



struct JPXData {

    const unsigned char * data;

    size_t pos;

    size_t size;

};



extern "C" OPJ_BOOL jpxSeek_callback(OPJ_OFF_T seek_pos, void *p_user_data);



class JPXSeekCallbackTest_2000 : public ::testing::Test {

protected:

    JPXData jpxData;



    void SetUp() override {

        jpxData.data = nullptr;

        jpxData.pos = 0;

        jpxData.size = 1024; // Example size

    }

};



TEST_F(JPXSeekCallbackTest_2000, SeekWithinBoundsReturnsTrue_2000) {

    EXPECT_EQ(jpxSeek_callback(512, &jpxData), OPJ_TRUE);

    EXPECT_EQ(jpxData.pos, 512U);

}



TEST_F(JPXSeekCallbackTest_2000, SeekAtBoundaryReturnsTrue_2000) {

    EXPECT_EQ(jpxSeek_callback(1024, &jpxData), OPJ_TRUE);

    EXPECT_EQ(jpxData.pos, 1024U);

}



TEST_F(JPXSeekCallbackTest_2000, SeekPastBoundsReturnsFalse_2000) {

    EXPECT_EQ(jpxSeek_callback(2048, &jpxData), OPJ_FALSE);

    EXPECT_EQ(jpxData.pos, 0U); // Ensure position is unchanged

}



TEST_F(JPXSeekCallbackTest_2000, SeekAtZeroReturnsTrue_2000) {

    jpxData.pos = 512; // Move to a non-zero position first

    EXPECT_EQ(jpxSeek_callback(0, &jpxData), OPJ_TRUE);

    EXPECT_EQ(jpxData.pos, 0U);

}



TEST_F(JPXSeekCallbackTest_2000, SeekToCurrentPositionReturnsTrue_2000) {

    jpxData.pos = 512; // Set a current position

    EXPECT_EQ(jpxSeek_callback(512, &jpxData), OPJ_TRUE);

    EXPECT_EQ(jpxData.pos, 512U); // Ensure position is unchanged

}
