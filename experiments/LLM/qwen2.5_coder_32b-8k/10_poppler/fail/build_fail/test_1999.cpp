#include <gtest/gtest.h>

#include <gmock/gmock.h>



struct JPXData {

    const unsigned char * data;

    size_t pos = 0;

    size_t size = 1024; // Assuming some reasonable size for testing

};



extern "C" OPJ_OFF_T jpxSkip_callback(OPJ_OFF_T skip, void *p_user_data);



class JPEG2000StreamTest_1999 : public ::testing::Test {

protected:

    JPXData jpxData;

    

    void SetUp() override {

        jpxData.pos = 0;

        jpxData.size = 1024; // Reset to a known state for each test

    }

};



TEST_F(JPEG2000StreamTest_1999, SkipWithinBounds_1999) {

    OPJ_OFF_T skipAmount = 100;

    OPJ_OFF_T result = jpxSkip_callback(skipAmount, &jpxData);

    

    EXPECT_EQ(result, skipAmount);

    EXPECT_EQ(jpxData.pos, static_cast<size_t>(skipAmount));

}



TEST_F(JPEG2000StreamTest_1999, SkipAtBoundary_1999) {

    jpxData.pos = jpxData.size - 50;

    OPJ_OFF_T skipAmount = 60;

    OPJ_OFF_T result = jpxSkip_callback(skipAmount, &jpxData);

    

    EXPECT_EQ(result, skipAmount);

    EXPECT_EQ(jpxData.pos, jpxData.size); // Should not exceed size

}



TEST_F(JPEG2000StreamTest_1999, SkipBeyondBoundary_1999) {

    jpxData.pos = jpxData.size - 50;

    OPJ_OFF_T skipAmount = 100;

    OPJ_OFF_T result = jpxSkip_callback(skipAmount, &jpxData);

    

    EXPECT_EQ(result, skipAmount);

    EXPECT_EQ(jpxData.pos, jpxData.size); // Should not exceed size

}



TEST_F(JPEG2000StreamTest_1999, SkipZero_1999) {

    OPJ_OFF_T skipAmount = 0;

    OPJ_OFF_T result = jpxSkip_callback(skipAmount, &jpxData);

    

    EXPECT_EQ(result, skipAmount);

    EXPECT_EQ(jpxData.pos, 0); // Position should not change

}
