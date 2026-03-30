#include <gtest/gtest.h>

#include <cstdint>

#include <array>



// Mocking Mul Tables as they are external collaborators

class MockMul09Table {

public:

    MOCK_CONST_METHOD1(operator(), uint8_t(uint8_t));

};



class MockMul0bTable {

public:

    MOCK_CONST_METHOD1(operator(), uint8_t(uint8_t));

};



class MockMul0dTable {

public:

    MOCK_CONST_METHOD1(operator(), uint8_t(uint8_t));

};



class MockMul0eTable {

public:

    MOCK_CONST_METHOD1(operator(), uint8_t(uint8_t));

};



// Global mock instances

MockMul09Table mock_mul09;

MockMul0bTable mock_mul0b;

MockMul0dTable mock_mul0d;

MockMul0eTable mock_mul0e;



extern "C" {

    const MockMul09Table mul09 = mock_mul09;

    const MockMul0bTable mul0b = mock_mul0b;

    const MockMul0dTable mul0d = mock_mul0d;

    const MockMul0eTable mul0e = mock_mul0e;



    static inline void invMixColumns(unsigned char *state) {

        int c;

        unsigned char s0, s1, s2, s3;

        for (c = 0; c < 4; ++c) {

            s0 = state[c];

            s1 = state[4 + c];

            s2 = state[8 + c];

            s3 = state[12 + c];

            state[c] = mul0e(s0) ^ mul0b(s1) ^ mul0d(s2) ^ mul09(s3);

            state[4 + c] = mul09(s0) ^ mul0e(s1) ^ mul0b(s2) ^ mul0d(s3);

            state[8 + c] = mul0d(s0) ^ mul09(s1) ^ mul0e(s2) ^ mul0b(s3);

            state[12 + c] = mul0b(s0) ^ mul0d(s1) ^ mul09(s2) ^ mul0e(s3);

        }

    }

}



class InvMixColumnsTest : public ::testing::Test {

protected:

    std::array<uint8_t, 16> state;



    void SetUp() override {

        state.fill(0); // Initialize state to zero for consistency

    }



    void ExpectMulTableCalls(uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3) {

        EXPECT_CALL(mock_mul0e, operator()(s0)).Times(1);

        EXPECT_CALL(mock_mul0b, operator()(s1)).Times(1);

        EXPECT_CALL(mock_mul0d, operator()(s2)).Times(1);

        EXPECT_CALL(mock_mul09, operator()(s3)).Times(1);



        EXPECT_CALL(mock_mul09, operator()(s0)).Times(1);

        EXPECT_CALL(mock_mul0e, operator()(s1)).Times(1);

        EXPECT_CALL(mock_mul0b, operator()(s2)).Times(1);

        EXPECT_CALL(mock_mul0d, operator()(s3)).Times(1);



        EXPECT_CALL(mock_mul0d, operator()(s0)).Times(1);

        EXPECT_CALL(mock_mul09, operator()(s1)).Times(1);

        EXPECT_CALL(mock_mul0e, operator()(s2)).Times(1);

        EXPECT_CALL(mock_mul0b, operator()(s3)).Times(1);



        EXPECT_CALL(mock_mul0b, operator()(s0)).Times(1);

        EXPECT_CALL(mock_mul0d, operator()(s1)).Times(1);

        EXPECT_CALL(mock_mul09, operator()(s2)).Times(1);

        EXPECT_CALL(mock_mul0e, operator()(s3)).Times(1);

    }

};



TEST_F(InvMixColumnsTest_1610, AllZeros_1610) {

    invMixColumns(state.data());

    for (auto &byte : state) {

        EXPECT_EQ(byte, 0);

    }

}



TEST_F(InvMixColumnsTest_1610, SingleByteNonZero_1610) {

    uint8_t s0 = 1;

    state[0] = s0;



    ExpectMulTableCalls(s0, 0, 0, 0);



    invMixColumns(state.data());

    EXPECT_EQ(state[0], mock_mul0e(s0) ^ mock_mul0b(0) ^ mock_mul0d(0) ^ mock_mul09(0));

}



TEST_F(InvMixColumnsTest_1610, AllOnes_1610) {

    state.fill(255);



    ExpectMulTableCalls(255, 255, 255, 255);

    ExpectMulTableCalls(255, 255, 255, 255);

    ExpectMulTableCalls(255, 255, 255, 255);

    ExpectMulTableCalls(255, 255, 255, 255);



    invMixColumns(state.data());



    for (int c = 0; c < 4; ++c) {

        EXPECT_EQ(state[c], mock_mul0e(255) ^ mock_mul0b(255) ^ mock_mul0d(255) ^ mock_mul09(255));

        EXPECT_EQ(state[4 + c], mock_mul09(255) ^ mock_mul0e(255) ^ mock_mul0b(255) ^ mock_mul0d(255));

        EXPECT_EQ(state[8 + c], mock_mul0d(255) ^ mock_mul09(255) ^ mock_mul0e(255) ^ mock_mul0b(255));

        EXPECT_EQ(state[12 + c], mock_mul0b(255) ^ mock_mul0d(255) ^ mock_mul09(255) ^ mock_mul0e(255));

    }

}



TEST_F(InvMixColumnsTest_1610, RandomValues_1610) {

    state[0] = 1;

    state[4] = 2;

    state[8] = 3;

    state[12] = 4;



    ExpectMulTableCalls(1, 2, 3, 4);



    invMixColumns(state.data());

    EXPECT_EQ(state[0], mock_mul0e(1) ^ mock_mul0b(2) ^ mock_mul0d(3) ^ mock_mul09(4));

}



TEST_F(InvMixColumnsTest_1610, ExternalInteractions_1610) {

    uint8_t s0 = 5, s1 = 10, s2 = 15, s3 = 20;

    state[0] = s0; state[4] = s1; state[8] = s2; state[12] = s3;



    ExpectMulTableCalls(s0, s1, s2, s3);



    invMixColumns(state.data());

}



TEST_F(InvMixColumnsTest_1610, BoundaryValues_1610) {

    uint8_t max_val = 255;

    state[0] = max_val; state[4] = max_val; state[8] = max_val; state[12] = max_val;



    ExpectMulTableCalls(max_val, max_val, max_val, max_val);



    invMixColumns(state.data());

}



TEST_F(InvMixColumnsTest_1610, ZeroAndMaxValues_1610) {

    uint8_t zero_val = 0;

    uint8_t max_val = 255;

    state[0] = zero_val; state[4] = max_val; state[8] = zero_val; state[12] = max_val;



    ExpectMulTableCalls(zero_val, max_val, zero_val, max_val);



    invMixColumns(state.data());

}
