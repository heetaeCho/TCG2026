#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/walker-inl.h"



namespace re2 {



class MockRegexp : public Regexp {

public:

    MOCK_METHOD3(PreVisit, int(Regexp*, int, bool*));

    MOCK_METHOD5(PostVisit, int(Regexp*, int, int, int*, int));

    MOCK_METHOD1(Copy, int(int));

    MOCK_METHOD2(ShortVisit, int(Regexp*, int));

};



class WalkerTest_215 : public ::testing::Test {

protected:

    using WalkerType = Regexp::Walker<int>;

    WalkerType walker;

    MockRegexp mock_regexp;



    void SetUp() override {

        walker.Reset();

    }

};



TEST_F(WalkerTest_215, Reset_ClearsStack_215) {

    // Arrange

    EXPECT_CALL(mock_regexp, PreVisit).Times(0);

    EXPECT_CALL(mock_regexp, PostVisit).Times(0);



    walker.Walk(&mock_regexp, 0);

    ASSERT_FALSE(walker.stopped_early());



    // Act

    walker.Reset();



    // Assert

    EXPECT_TRUE(walker.stack_.empty());

}



TEST_F(WalkerTest_215, Walk_CallsPreVisitAndPostVisitOnce_215) {

    // Arrange

    bool stop = false;

    EXPECT_CALL(mock_regexp, PreVisit(&mock_regexp, 0, &stop)).Times(1).WillOnce(::testing::Return(42));

    EXPECT_CALL(mock_regexp, PostVisit(&mock_regexp, 0, 42, nullptr, 0)).Times(1).WillOnce(::testing::Return(84));



    // Act

    walker.Walk(&mock_regexp, 0);



    // Assert

    EXPECT_FALSE(walker.stopped_early());

}



TEST_F(WalkerTest_215, Walk_CallsCopyWhenUseCopyTrue_215) {

    // Arrange

    bool stop = false;

    EXPECT_CALL(mock_regexp, PreVisit(&mock_regexp, 0, &stop)).Times(1).WillOnce(::testing::Return(42));

    EXPECT_CALL(mock_regexp, PostVisit(&mock_regexp, 0, 42, nullptr, 0)).Times(1).WillOnce(::testing::Return(84));

    EXPECT_CALL(walker, Copy(42)).Times(1).WillOnce(::testing::Return(43));



    // Act

    walker.WalkExponential(&mock_regexp, 0, 1);



    // Assert

    EXPECT_FALSE(walker.stopped_early());

}



TEST_F(WalkerTest_215, Walk_WithNsubGreaterThanOne_DeletesChildArgs_215) {

    // Arrange

    bool stop = false;

    int* child_args = new int[2];

    mock_regexp.nsub_ = 3;  // Simulate nsub_ > 1



    EXPECT_CALL(mock_regexp, PreVisit(&mock_regexp, 0, &stop)).Times(1).WillOnce(::testing::Return(42));

    EXPECT_CALL(mock_regexp, PostVisit(&mock_regexp, 0, 42, child_args, 3))

        .Times(1)

        .WillOnce([child_args](Regexp*, int, int, int*, int) {

            delete[] child_args;

            return 84;

        });



    // Act

    walker.Walk(&mock_regexp, 0);



    // Assert

    EXPECT_FALSE(walker.stopped_early());

}



TEST_F(WalkerTest_215, WalkExponential_WithMaxVisits_ReachesLimit_215) {

    // Arrange

    bool stop = false;

    EXPECT_CALL(mock_regexp, PreVisit(&mock_regexp, 0, &stop)).Times(3).WillRepeatedly(::testing::Return(42));

    EXPECT_CALL(mock_regexp, PostVisit(&mock_regexp, 0, 42, nullptr, 0)).Times(3).WillRepeatedly(::testing::Return(84));



    // Act

    walker.WalkExponential(&mock_regexp, 0, 3);



    // Assert

    EXPECT_TRUE(walker.stopped_early());

}



}  // namespace re2
