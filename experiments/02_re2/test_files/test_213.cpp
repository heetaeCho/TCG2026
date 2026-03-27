#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/walker-inl.h"

#include <stack>



using namespace re2;



class MockRegexp : public Regexp {

public:

    MOCK_METHOD3(PreVisit, int(MockRegexp*, int, bool*));

    MOCK_METHOD5(PostVisit, int(MockRegexp*, int, int, int*, int));

    MOCK_METHOD1(Copy, int(int));

    MOCK_METHOD2(ShortVisit, int(MockRegexp*, int));

};



class WalkerTest_213 : public ::testing::Test {

protected:

    Walker<int> walker;

    MockRegexp mock_regexp;

};



TEST_F(WalkerTest_213, CopyIncreasesCount_213) {

    int arg = 42;

    EXPECT_EQ(walker.Copy(arg), arg);

}



TEST_F(WalkerTest_213, WalkNormalOperation_213) {

    bool stop = false;

    int top_arg = 0;



    EXPECT_CALL(mock_regexp, PreVisit(&mock_regexp, top_arg, &stop)).WillOnce(::testing::Return(1));

    EXPECT_CALL(mock_regexp, PostVisit(&mock_regexp, top_arg, 1, nullptr, 0)).WillOnce(::testing::Return(2));



    int result = walker.Walk(&mock_regexp, top_arg);

    EXPECT_EQ(result, 2);

}



TEST_F(WalkerTest_213, WalkExponentialNormalOperation_213) {

    bool stop = false;

    int top_arg = 0;

    int max_visits = 10;



    EXPECT_CALL(mock_regexp, PreVisit(&mock_regexp, top_arg, &stop)).WillOnce(::testing::Return(1));

    EXPECT_CALL(mock_regexp, PostVisit(&mock_regexp, top_arg, 1, nullptr, 0)).WillOnce(::testing::Return(2));



    int result = walker.WalkExponential(&mock_regexp, top_arg, max_visits);

    EXPECT_EQ(result, 2);

}



TEST_F(WalkerTest_213, WalkBoundaryCondition_213) {

    bool stop = false;

    int top_arg = 0;



    EXPECT_CALL(mock_regexp, PreVisit(&mock_regexp, top_arg, &stop)).WillOnce(::testing::Return(1));

    EXPECT_CALL(mock_regexp, PostVisit(&mock_regexp, top_arg, 1, nullptr, 0)).WillOnce(::testing::Return(1));



    int result = walker.Walk(&mock_regexp, top_arg);

    EXPECT_EQ(result, 1);

}



TEST_F(WalkerTest_213, WalkExponentialBoundaryCondition_213) {

    bool stop = false;

    int top_arg = 0;

    int max_visits = 1;



    EXPECT_CALL(mock_regexp, PreVisit(&mock_regexp, top_arg, &stop)).WillOnce(::testing::Return(1));

    EXPECT_CALL(mock_regexp, PostVisit(&mock_regexp, top_arg, 1, nullptr, 0)).WillOnce(::testing::Return(1));



    int result = walker.WalkExponential(&mock_regexp, top_arg, max_visits);

    EXPECT_EQ(result, 1);

}



TEST_F(WalkerTest_213, WalkStoppedEarly_213) {

    bool stop = true;

    int top_arg = 0;



    EXPECT_CALL(mock_regexp, PreVisit(&mock_regexp, top_arg, &stop)).WillOnce(::testing::DoAll(::testing::SetArgReferee<2>(true), ::testing::Return(1)));



    walker.Walk(&mock_regexp, top_arg);

    EXPECT_TRUE(walker.stopped_early());

}



TEST_F(WalkerTest_213, WalkExponentialStoppedEarly_213) {

    bool stop = true;

    int top_arg = 0;

    int max_visits = 10;



    EXPECT_CALL(mock_regexp, PreVisit(&mock_regexp, top_arg, &stop)).WillOnce(::testing::DoAll(::testing::SetArgReferee<2>(true), ::testing::Return(1)));



    walker.WalkExponential(&mock_regexp, top_arg, max_visits);

    EXPECT_TRUE(walker.stopped_early());

}



TEST_F(WalkerTest_213, ResetFunctionality_213) {

    bool stop = true;

    int top_arg = 0;



    EXPECT_CALL(mock_regexp, PreVisit(&mock_regexp, top_arg, &stop)).WillOnce(::testing::DoAll(::testing::SetArgReferee<2>(true), ::testing::Return(1)));



    walker.Walk(&mock_regexp, top_arg);

    EXPECT_TRUE(walker.stopped_early());



    walker.Reset();

    EXPECT_FALSE(walker.stopped_early());

}
