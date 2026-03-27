#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/regexp.h"

#include "re2/walker-inl.h"



using namespace re2;



class MockWalker : public Regexp::Walker<int> {

public:

    MOCK_METHOD3(PreVisit, int(Regexp* re, int parent_arg, bool* stop));

    MOCK_METHOD5(PostVisit, int(Regexp* re, int parent_arg, int pre_arg, int* child_args, int nchild_args));

    MOCK_METHOD1(Copy, int(int arg));

    MOCK_METHOD2(ShortVisit, int(Regexp* re, int parent_arg));

};



class WalkerTest_216 : public ::testing::Test {

protected:

    void SetUp() override {

        walker = new MockWalker();

        regexp = Regexp::Parse("a", Regexp::ParseFlags(0), &status);

    }



    void TearDown() override {

        delete walker;

        delete regexp;

    }



    MockWalker* walker;

    Regexp* regexp;

    RegexpStatus status;

};



TEST_F(WalkerTest_216, WalkNormalOperation_216) {

    EXPECT_CALL(*walker, PreVisit(regexp, 0, testing::_))

        .WillOnce(testing::DoAll(testing::SetArgReferee<2>(false), testing::Return(1)));

    EXPECT_CALL(*walker, PostVisit(regexp, 0, 1, nullptr, 0))

        .WillOnce(testing::Return(2));



    int result = walker->Walk(regexp, 0);

    EXPECT_EQ(result, 2);

}



TEST_F(WalkerTest_216, WalkEarlyStop_216) {

    EXPECT_CALL(*walker, PreVisit(regexp, 0, testing::_))

        .WillOnce(testing::DoAll(testing::SetArgReferee<2>(true), testing::Return(1)));



    int result = walker->Walk(regexp, 0);

    EXPECT_EQ(result, 1);

}



TEST_F(WalkerTest_216, WalkWithChild_216) {

    Regexp* child = Regexp::Parse("b", Regexp::ParseFlags(0), &status);

    Regexp** subs = new Regexp*[2];

    subs[0] = regexp;

    subs[1] = child;



    ON_CALL(*walker, PreVisit(regexp, 0, testing::_))

        .WillByDefault(testing::DoAll(testing::SetArgReferee<2>(false), testing::Return(1)));

    ON_CALL(*walker, PreVisit(child, 0, testing::_))

        .WillByDefault(testing::DoAll(testing::SetArgReferee<2>(false), testing::Return(3)));



    EXPECT_CALL(*walker, PostVisit(regexp, 0, 1, testing::ElementsAre(1, 3), 2))

        .WillOnce(testing::Return(4));



    Regexp* concat = Regexp::Concat(subs, 2, Regexp::ParseFlags(0));

    int result = walker->Walk(concat, 0);

    EXPECT_EQ(result, 4);



    delete[] subs;

    delete child;

    delete concat;

}



TEST_F(WalkerTest_216, WalkShortVisit_216) {

    ON_CALL(*walker, PreVisit(regexp, 0, testing::_))

        .WillByDefault(testing::DoAll(testing::SetArgReferee<2>(false), testing::Return(1)));



    EXPECT_CALL(*walker, ShortVisit(regexp, 0))

        .WillOnce(testing::Return(5));



    int result = walker->Walk(regexp, 0);

    EXPECT_EQ(result, 5);

}



TEST_F(WalkerTest_216, WalkInvalidRegex_216) {

    Regexp* invalid_regexp = Regexp::Parse("(", Regexp::ParseFlags(0), &status);



    ON_CALL(*walker, PreVisit(invalid_regexp, 0, testing::_))

        .WillByDefault(testing::DoAll(testing::SetArgReferee<2>(false), testing::Return(1)));



    EXPECT_CALL(*walker, PostVisit(invalid_regexp, 0, 1, nullptr, 0))

        .WillOnce(testing::Return(2));



    int result = walker->Walk(invalid_regexp, 0);

    EXPECT_EQ(result, 2);



    delete invalid_regexp;

}
