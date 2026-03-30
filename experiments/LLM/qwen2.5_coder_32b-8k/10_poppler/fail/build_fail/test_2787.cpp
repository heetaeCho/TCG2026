#include <gtest/gtest.h>



class TextUnderlineTest_2787 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(TextUnderlineTest_2787, HorizontalLine_Detection_2787) {

    TextUnderline underline(0.0, 1.0, 5.0, 1.0);

    EXPECT_TRUE(underline.horiz);

}



TEST_F(TextUnderlineTest_2787, NonHorizontalLine_Detection_2787) {

    TextUnderline underline(0.0, 1.0, 5.0, 2.0);

    EXPECT_FALSE(underline.horiz);

}



TEST_F(TextUnderlineTest_2787, VerticalLine_Detection_2787) {

    TextUnderline underline(0.0, 1.0, 0.0, 6.0);

    EXPECT_FALSE(underline.horiz);

}



TEST_F(TextUnderlineTest_2787, ZeroLengthHorizontalLine_Detection_2787) {

    TextUnderline underline(0.0, 1.0, 0.0, 1.0);

    EXPECT_TRUE(underline.horiz);

}



TEST_F(TextUnderlineTest_2787, ZeroLengthNonHorizontalLine_Detection_2787) {

    TextUnderline underline(0.0, 1.0, 0.0, 0.0);

    EXPECT_FALSE(underline.horiz);

}
