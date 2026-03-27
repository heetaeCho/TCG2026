#include <gtest/gtest.h>

#include <gmock/gmock.h>



extern "C" {

    void grandom_fill(unsigned char *buff, int size);

}



class GrandomFillTest : public ::testing::Test {

protected:

    static constexpr int bufferSize = 1024;

    unsigned char buffer[bufferSize];



    void SetUp() override {

        memset(buffer, 0, bufferSize);

    }

};



TEST_F(GrandomFillTest_26, NormalOperation_26) {

    grandom_fill(buffer, bufferSize);

    for (int i = 0; i < bufferSize; ++i) {

        EXPECT_GE(buffer[i], static_cast<unsigned char>(std::numeric_limits<unsigned char>::min()));

        EXPECT_LE(buffer[i], static_cast<unsigned char>(std::numeric_limits<unsigned char>::max()));

    }

}



TEST_F(GrandomFillTest_26, BoundaryCondition_ZeroSize_26) {

    grandom_fill(buffer, 0);

    // Expecting no change in the buffer

    for (int i = 0; i < bufferSize; ++i) {

        EXPECT_EQ(buffer[i], static_cast<unsigned char>(0));

    }

}



TEST_F(GrandomFillTest_26, BoundaryCondition_MaxSize_26) {

    grandom_fill(buffer, bufferSize);

    // Expecting all values to be within the range of unsigned char

    for (int i = 0; i < bufferSize; ++i) {

        EXPECT_GE(buffer[i], static_cast<unsigned char>(std::numeric_limits<unsigned char>::min()));

        EXPECT_LE(buffer[i], static_cast<unsigned char>(std::numeric_limits<unsigned char>::max()));

    }

}



TEST_F(GrandomFillTest_26, BoundaryCondition_OneElement_26) {

    grandom_fill(buffer, 1);

    // Expecting the single element to be within the range of unsigned char

    EXPECT_GE(buffer[0], static_cast<unsigned char>(std::numeric_limits<unsigned char>::min()));

    EXPECT_LE(buffer[0], static_cast<unsigned char>(std::numeric_limits<unsigned char>::max()));

}



TEST_F(GrandomFillTest_26, Exceptional_NegativeSize_26) {

    // Assuming negative size is not handled gracefully and results in no change

    grandom_fill(buffer, -1);

    for (int i = 0; i < bufferSize; ++i) {

        EXPECT_EQ(buffer[i], static_cast<unsigned char>(0));

    }

}
