#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "prefilter.h"



using namespace re2;



// Mocking Prefilter::Info for external interactions if needed

class MockPrefilterInfo : public Prefilter::Info {

public:

    MOCK_METHOD(Info*, TakeMatch, (), (override));

    MOCK_METHOD(SSet&, exact, (), (override));

    MOCK_METHOD(bool, is_exact, (), (const, override));

};



// Test suite for Prefilter::Info::Alt

class PrefilterInfoAltTest_546 : public ::testing::Test {

protected:

    void SetUp() override {

        a = new MockPrefilterInfo();

        b = new MockPrefilterInfo();

    }



    void TearDown() override {

        delete a;

        delete b;

    }



    Prefilter::Info* a;

    Prefilter::Info* b;

};



// Test normal operation where both Info objects are exact

TEST_F(PrefilterInfoAltTest_546, BothExact_NormalOperation_546) {

    SSet expected_exact = {"a", "b"};

    EXPECT_CALL(*a, is_exact()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*b, is_exact()).WillOnce(::testing::Return(true));



    ON_CALL(*a, exact()).WillByDefault(::testing::ReturnRef(a_exact));

    ON_CALL(*b, exact()).WillByDefault(::testing::ReturnRef(b_exact));



    a_exact = {"a"};

    b_exact = {"b"};



    Prefilter::Info* result = Prefilter::Info::Alt(a, b);



    EXPECT_TRUE(result->is_exact());

    EXPECT_EQ(result->exact(), expected_exact);

}



// Test normal operation where one Info object is exact and the other is not

TEST_F(PrefilterInfoAltTest_546, OneExact_OneNotExact_NormalOperation_546) {

    Prefilter* mock_match = new Prefilter(Op::kOpStar);

    EXPECT_CALL(*a, is_exact()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*b, is_exact()).WillOnce(::testing::Return(false));

    EXPECT_CALL(*b, TakeMatch()).WillOnce(::testing::Return(mock_match));



    ON_CALL(*a, exact()).WillByDefault(::testing::ReturnRef(a_exact));



    a_exact = {"a"};



    Prefilter::Info* result = Prefilter::Info::Alt(a, b);



    EXPECT_FALSE(result->is_exact());

    EXPECT_EQ(result->TakeMatch(), mock_match);

}



// Test boundary condition where both Info objects are empty exact sets

TEST_F(PrefilterInfoAltTest_546, BothEmptyExact_NormalOperation_546) {

    EXPECT_CALL(*a, is_exact()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*b, is_exact()).WillOnce(::testing::Return(true));



    ON_CALL(*a, exact()).WillByDefault(::testing::ReturnRef(a_exact));

    ON_CALL(*b, exact()).WillByDefault(::testing::ReturnRef(b_exact));



    a_exact = {};

    b_exact = {};



    Prefilter::Info* result = Prefilter::Info::Alt(a, b);



    EXPECT_TRUE(result->is_exact());

    EXPECT_EQ(result->exact(), SSet{});

}



// Test exceptional case where TakeMatch() returns null

TEST_F(PrefilterInfoAltTest_546, OneExact_OneNotExact_TakeMatchNull_ExceptionalCase_546) {

    EXPECT_CALL(*a, is_exact()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*b, is_exact()).WillOnce(::testing::Return(false));

    EXPECT_CALL(*b, TakeMatch()).WillOnce(::testing::Return(nullptr));



    ON_CALL(*a, exact()).WillByDefault(::testing::ReturnRef(a_exact));



    a_exact = {"a"};



    Prefilter::Info* result = Prefilter::Info::Alt(a, b);



    EXPECT_FALSE(result->is_exact());

    EXPECT_EQ(result->TakeMatch(), nullptr);

}



SSet a_exact;

SSet b_exact;
