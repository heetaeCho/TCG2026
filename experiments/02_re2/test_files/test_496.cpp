#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/regexp.h"

#include "re2/parse.cc"



namespace re2 {



using ::testing::NiceMock;

using ::testing::_;



class MockStopFlag {

public:

    MOCK_METHOD(void, SetStopFlag, (bool), ());

};



TEST_F(RepetitionWalkerTest_496, NormalOperationWithRepeat_496) {

    int parent_arg = 100;

    bool stop = false;



    Regexp* re = Regexp::Repeat(Regexp::NewLiteral('a', 0), 0, 5);

    RepetitionWalker walker;

    int result = walker.PreVisit(re, parent_arg, &stop);



    EXPECT_EQ(result, 20); // 100 / 5

}



TEST_F(RepetitionWalkerTest_496, NormalOperationWithoutRepeat_496) {

    int parent_arg = 100;

    bool stop = false;



    Regexp* re = Regexp::NewLiteral('a', 0);

    RepetitionWalker walker;

    int result = walker.PreVisit(re, parent_arg, &stop);



    EXPECT_EQ(result, 100); // No change

}



TEST_F(RepetitionWalkerTest_496, BoundaryConditionMaxNegativeMinPositive_496) {

    int parent_arg = 100;

    bool stop = false;



    Regexp* re = Regexp::Repeat(Regexp::NewLiteral('a', 0), 5, -1);

    RepetitionWalker walker;

    int result = walker.PreVisit(re, parent_arg, &stop);



    EXPECT_EQ(result, 20); // 100 / 5

}



TEST_F(RepetitionWalkerTest_496, BoundaryConditionMaxNegativeMinZero_496) {

    int parent_arg = 100;

    bool stop = false;



    Regexp* re = Regexp::Repeat(Regexp::NewLiteral('a', 0), 0, -1);

    RepetitionWalker walker;

    int result = walker.PreVisit(re, parent_arg, &stop);



    EXPECT_EQ(result, 100); // No change

}



TEST_F(RepetitionWalkerTest_496, BoundaryConditionMaxPositiveMinZero_496) {

    int parent_arg = 100;

    bool stop = false;



    Regexp* re = Regexp::Repeat(Regexp::NewLiteral('a', 0), 0, 5);

    RepetitionWalker walker;

    int result = walker.PreVisit(re, parent_arg, &stop);



    EXPECT_EQ(result, 20); // 100 / 5

}



TEST_F(RepetitionWalkerTest_496, BoundaryConditionMaxZeroMinPositive_496) {

    int parent_arg = 100;

    bool stop = false;



    Regexp* re = Regexp::Repeat(Regexp::NewLiteral('a', 0), 5, 0);

    RepetitionWalker walker;

    int result = walker.PreVisit(re, parent_arg, &stop);



    EXPECT_EQ(result, 20); // 100 / 5

}



TEST_F(RepetitionWalkerTest_496, StopFlagSet_496) {

    int parent_arg = 100;

    bool stop = false;



    Regexp* re = Regexp::Repeat(Regexp::NewLiteral('a', 0), 5, 5);

    RepetitionWalker walker;

    int result = walker.PreVisit(re, parent_arg, &stop);



    EXPECT_EQ(result, 4); // 100 / 25

}



TEST_F(RepetitionWalkerTest_496, StopFlagNotSet_496) {

    int parent_arg = 100;

    bool stop = false;



    Regexp* re = Regexp::Repeat(Regexp::NewLiteral('a', 0), 5, 5);

    RepetitionWalker walker;

    int result = walker.PreVisit(re, parent_arg, &stop);



    EXPECT_FALSE(stop); // Stop flag should not be set by PreVisit

}



TEST_F(RepetitionWalkerTest_496, ExceptionalCaseMaxNegativeMinNegative_496) {

    int parent_arg = 100;

    bool stop = false;



    Regexp* re = Regexp::Repeat(Regexp::NewLiteral('a', 0), -5, -1);

    RepetitionWalker walker;

    int result = walker.PreVisit(re, parent_arg, &stop);



    EXPECT_EQ(result, 100); // No change

}



TEST_F(RepetitionWalkerTest_496, ExceptionalCaseMaxZeroMinZero_496) {

    int parent_arg = 100;

    bool stop = false;



    Regexp* re = Regexp::Repeat(Regexp::NewLiteral('a', 0), 0, 0);

    RepetitionWalker walker;

    int result = walker.PreVisit(re, parent_arg, &stop);



    EXPECT_EQ(result, 100); // No change

}



}  // namespace re2
