#include <gtest/gtest.h>

#include "SplashPath.h"



class SplashPathTest_1535 : public ::testing::Test {

protected:

    void SetUp() override {

        splashPath = new SplashPath();

    }



    void TearDown() override {

        delete splashPath;

    }



    SplashPath* splashPath;

};



TEST_F(SplashPathTest_1535, InitialLengthIsZero_1535) {

    EXPECT_EQ(splashPath->getLength(), 0);

}



TEST_F(SplashPathTest_1535, MoveToIncreasesLengthByOne_1535) {

    splashPath->moveTo(0.0, 0.0);

    EXPECT_EQ(splashPath->getLength(), 1);

}



TEST_F(SplashPathTest_1535, LineToAfterMoveToIncreasesLengthByOne_1535) {

    splashPath->moveTo(0.0, 0.0);

    splashPath->lineTo(1.0, 1.0);

    EXPECT_EQ(splashPath->getLength(), 2);

}



TEST_F(SplashPathTest_1535, CurveToAfterMoveToIncreasesLengthByThree_1535) {

    splashPath->moveTo(0.0, 0.0);

    splashPath->curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);

    EXPECT_EQ(splashPath->getLength(), 4);

}



TEST_F(SplashPathTest_1535, CloseAfterMoveToIncreasesLengthByOne_1535) {

    splashPath->moveTo(0.0, 0.0);

    splashPath->close(false);

    EXPECT_EQ(splashPath->getLength(), 2);

}



TEST_F(SplashPathTest_1535, AppendAnotherPathAddsItsPoints_1535) {

    SplashPath otherPath;

    otherPath.moveTo(0.0, 0.0);

    otherPath.lineTo(1.0, 1.0);



    splashPath->append(&otherPath);

    EXPECT_EQ(splashPath->getLength(), 2);

}



TEST_F(SplashPathTest_1535, AppendEmptyPathDoesNotChangeLength_1535) {

    SplashPath otherPath;

    int initialLength = splashPath->getLength();



    splashPath->append(&otherPath);

    EXPECT_EQ(splashPath->getLength(), initialLength);

}



TEST_F(SplashPathTest_1535, GetPointWithinBoundsDoesNotThrow_1535) {

    splashPath->moveTo(0.0, 0.0);

    double x, y;

    unsigned char f;



    EXPECT_NO_THROW(splashPath->getPoint(0, &x, &y, &f));

}



TEST_F(SplashPathTest_1535, GetPointOutOfBoundsThrowsException_1535) {

    splashPath->moveTo(0.0, 0.0);

    double x, y;

    unsigned char f;



    EXPECT_EQ(splashPath->getPoint(1, &x, &y, &f), splashErrRangeCheck);

}
