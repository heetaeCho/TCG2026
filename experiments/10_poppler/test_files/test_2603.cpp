#include <gtest/gtest.h>



// Mocking external collaborators or dependencies if needed.

// In this case, there are no external collaborators to mock.



struct SplashScreenPoint {

    int dist;

};



struct cmpDistancesFunctor {

    bool operator()(const SplashScreenPoint p0, const SplashScreenPoint p1) const;

};



class CmpDistancesFunctorTest : public ::testing::Test {

protected:

    cmpDistancesFunctor comparator;



    SplashScreenPoint createPoint(int distance) {

        return SplashScreenPoint{distance};

    }

};



TEST_F(CmpDistancesFunctorTest_2603, NormalOperation_FirstPointCloser_2603) {

    SplashScreenPoint p0 = createPoint(5);

    SplashScreenPoint p1 = createPoint(10);



    EXPECT_TRUE(comparator(p0, p1));

}



TEST_F(CmpDistancesFunctorTest_2603, NormalOperation_SecondPointCloser_2603) {

    SplashScreenPoint p0 = createPoint(15);

    SplashScreenPoint p1 = createPoint(10);



    EXPECT_FALSE(comparator(p0, p1));

}



TEST_F(CmpDistancesFunctorTest_2603, BoundaryConditions_EqualDistance_2603) {

    SplashScreenPoint p0 = createPoint(7);

    SplashScreenPoint p1 = createPoint(7);



    EXPECT_FALSE(comparator(p0, p1));

}



TEST_F(CmpDistancesFunctorTest_2603, BoundaryConditions_MaxIntValues_2603) {

    SplashScreenPoint p0 = createPoint(INT_MAX);

    SplashScreenPoint p1 = createPoint(INT_MAX - 1);



    EXPECT_FALSE(comparator(p0, p1));

}



TEST_F(CmpDistancesFunctorTest_2603, BoundaryConditions_MinIntValues_2603) {

    SplashScreenPoint p0 = createPoint(INT_MIN);

    SplashScreenPoint p1 = createPoint(INT_MIN + 1);



    EXPECT_TRUE(comparator(p0, p1));

}
