#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <catch2/internal/catch_random_integer_helpers.hpp>



using namespace Catch::Detail;



// Mocking a generator for testing purposes

class MockGenerator {

public:

    using result_type = uint64_t;

    static constexpr result_type min() { return 0; }

    static constexpr result_type max() { return static_cast<result_type>(-1); }



    MOCK_METHOD(result_type, operator(), (), ());

};



// Test fixture for fillBitsFrom

class FillBitsFromTest_334 : public ::testing::Test {

protected:

    MockGenerator mockGen;

};



TEST_F(FillBitsFromTest_334, NormalOperation_Uint8_334) {

    EXPECT_CALL(mockGen, operator()()).WillOnce(::testing::Return(0xFFFFFFFFFFFFFFFF));

    uint8_t result = fillBitsFrom<uint8_t>(mockGen);

    EXPECT_EQ(result, 0xFF);

}



TEST_F(FillBitsFromTest_334, NormalOperation_Uint16_334) {

    EXPECT_CALL(mockGen, operator()()).WillOnce(::testing::Return(0xFFFFFFFFFFFFFFFF));

    uint16_t result = fillBitsFrom<uint16_t>(mockGen);

    EXPECT_EQ(result, 0xFFFF);

}



TEST_F(FillBitsFromTest_334, NormalOperation_Uint32_334) {

    EXPECT_CALL(mockGen, operator()()).WillOnce(::testing::Return(0xFFFFFFFFFFFFFFFF));

    uint32_t result = fillBitsFrom<uint32_t>(mockGen);

    EXPECT_EQ(result, 0xFFFFFFFF);

}



TEST_F(FillBitsFromTest_334, NormalOperation_Uint64_334) {

    EXPECT_CALL(mockGen, operator()()).WillOnce(::testing::Return(0xFFFFFFFFFFFFFFFF));

    uint64_t result = fillBitsFrom<uint64_t>(mockGen);

    EXPECT_EQ(result, 0xFFFFFFFFFFFFFFFF);

}



TEST_F(FillBitsFromTest_334, BoundaryCondition_Zero_334) {

    EXPECT_CALL(mockGen, operator()()).WillOnce(::testing::Return(0));

    uint8_t result = fillBitsFrom<uint8_t>(mockGen);

    EXPECT_EQ(result, 0);

}



TEST_F(FillBitsFromTest_334, ExceptionalCase_Negative_Return_Type_Not_Allowed_334) {

    // This test is not applicable as the function template is only enabled for unsigned types.

    // Therefore, it will not compile if a signed type is passed, which is tested by static_assert.

}



TEST_F(FillBitsFromTest_334, ExternalInteraction_Generator_Call_334) {

    EXPECT_CALL(mockGen, operator()()).Times(1);

    fillBitsFrom<uint8_t>(mockGen);

}
