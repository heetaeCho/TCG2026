#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/matroskavideo.cpp"

#include "exiv2/error.hpp"



using namespace Exiv2::Internal;



class ReturnTagValueTest_94 : public ::testing::Test {

protected:

    static constexpr size_t MaxSize = 8;

    byte buffer[MaxSize];

};



TEST_F(ReturnTagValueTest_94, NormalOperation_94) {

    // Test with a single-byte tag

    buffer[0] = 0x12;

    EXPECT_EQ(returnTagValue(buffer, 1), 0x12);



    // Test with a two-byte tag

    buffer[0] = 0x12; buffer[1] = 0x34;

    EXPECT_EQ(returnTagValue(buffer, 2), 0x1234);



    // Test with an eight-byte tag

    for (size_t i = 0; i < MaxSize; ++i) {

        buffer[i] = static_cast<byte>(i);

    }

    EXPECT_EQ(returnTagValue(buffer, MaxSize), 0x0706050403020100ULL);

}



TEST_F(ReturnTagValueTest_94, BoundaryConditions_94) {

    // Test with size equal to 1

    buffer[0] = 0xFF;

    EXPECT_EQ(returnTagValue(buffer, 1), 0x7F);



    // Test with size equal to 8

    for (size_t i = 0; i < MaxSize; ++i) {

        buffer[i] = 0xFF;

    }

    EXPECT_EQ(returnTagValue(buffer, MaxSize), 0xFFFFFFFFFFFFFFFFULL);

}



TEST_F(ReturnTagValueTest_94, ExceptionalCases_94) {

    // Test with size zero

    EXPECT_THROW(returnTagValue(buffer, 0), Exiv2::Error);



    // Test with size greater than 8

    EXPECT_THROW(returnTagValue(buffer, MaxSize + 1), Exiv2::Error);

}



TEST_F(ReturnTagValueTest_94, MaskingBehavior_94) {

    // Test masking for different sizes

    buffer[0] = 0xFF;

    

    // Size 1: should mask to 7 bits (0x7F)

    EXPECT_EQ(returnTagValue(buffer, 1), 0x7F);



    // Size 2: should mask to full byte (0xFF)

    EXPECT_EQ(returnTagValue(buffer, 2), 0xFF);



    buffer[0] = 0xAA;



    // Size 3: should mask to 5 bits of the first byte (0x1A << 16)

    EXPECT_EQ(returnTagValue(buffer, 3), 0x1A0000);

}
