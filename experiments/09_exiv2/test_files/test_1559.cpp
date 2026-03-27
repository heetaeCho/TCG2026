#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/asfvideo.hpp"



namespace {



using namespace Exiv2;



class GUIDTagTest_1559 : public ::testing::Test {

protected:

    using GUIDBytes = std::array<byte, 8>;



    GUIDTag CreateGUID(uint32_t data1, uint16_t data2, uint16_t data3, const GUIDBytes& data4) {

        return GUIDTag(data1, data2, data3, data4);

    }

};



TEST_F(GUIDTagTest_1559, ComparisonOperatorDifferentData1_1559) {

    auto guid1 = CreateGUID(1, 0, 0, {0});

    auto guid2 = CreateGUID(2, 0, 0, {0});

    EXPECT_TRUE(guid1 < guid2);

}



TEST_F(GUIDTagTest_1559, ComparisonOperatorSameData1DifferentData2_1559) {

    auto guid1 = CreateGUID(0, 1, 0, {0});

    auto guid2 = CreateGUID(0, 2, 0, {0});

    EXPECT_TRUE(guid1 < guid2);

}



TEST_F(GUIDTagTest_1559, ComparisonOperatorSameData1Data2DifferentData3_1559) {

    auto guid1 = CreateGUID(0, 0, 1, {0});

    auto guid2 = CreateGUID(0, 0, 2, {0});

    EXPECT_TRUE(guid1 < guid2);

}



TEST_F(GUIDTagTest_1559, ComparisonOperatorSameData1Data2Data3DifferentData4_1559) {

    GUIDBytes data4_1 = {0, 0, 0, 0, 0, 0, 0, 0};

    GUIDBytes data4_2 = {0, 0, 0, 0, 0, 0, 0, 1};



    auto guid1 = CreateGUID(0, 0, 0, data4_1);

    auto guid2 = CreateGUID(0, 0, 0, data4_2);



    EXPECT_TRUE(guid1 < guid2);

}



TEST_F(GUIDTagTest_1559, ComparisonOperatorEqualGUIDs_1559) {

    GUIDBytes data4 = {0};



    auto guid1 = CreateGUID(0, 0, 0, data4);

    auto guid2 = CreateGUID(0, 0, 0, data4);



    EXPECT_FALSE(guid1 < guid2);

}



TEST_F(GUIDTagTest_1559, EqualityOperatorDifferentData1_1559) {

    auto guid1 = CreateGUID(1, 0, 0, {0});

    auto guid2 = CreateGUID(2, 0, 0, {0});

    EXPECT_FALSE(guid1 == guid2);

}



TEST_F(GUIDTagTest_1559, EqualityOperatorSameData1DifferentData2_1559) {

    auto guid1 = CreateGUID(0, 1, 0, {0});

    auto guid2 = CreateGUID(0, 2, 0, {0});

    EXPECT_FALSE(guid1 == guid2);

}



TEST_F(GUIDTagTest_1559, EqualityOperatorSameData1Data2DifferentData3_1559) {

    auto guid1 = CreateGUID(0, 0, 1, {0});

    auto guid2 = CreateGUID(0, 0, 2, {0});

    EXPECT_FALSE(guid1 == guid2);

}



TEST_F(GUIDTagTest_1559, EqualityOperatorSameData1Data2Data3DifferentData4_1559) {

    GUIDBytes data4_1 = {0, 0, 0, 0, 0, 0, 0, 0};

    GUIDBytes data4_2 = {0, 0, 0, 0, 0, 0, 0, 1};



    auto guid1 = CreateGUID(0, 0, 0, data4_1);

    auto guid2 = CreateGUID(0, 0, 0, data4_2);



    EXPECT_FALSE(guid1 == guid2);

}



TEST_F(GUIDTagTest_1559, EqualityOperatorEqualGUIDs_1559) {

    GUIDBytes data4 = {0};



    auto guid1 = CreateGUID(0, 0, 0, data4);

    auto guid2 = CreateGUID(0, 0, 0, data4);



    EXPECT_TRUE(guid1 == guid2);

}



} // namespace
