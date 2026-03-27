#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/SplashOutputDev.cc"

#include "TestProjects/poppler/poppler/Object.h"



class T3FontCacheTest : public ::testing::Test {

protected:

    Ref validRef = {1, 0};

    double m11 = 1.0;

    double m12 = 0.0;

    double m21 = 0.0;

    double m22 = 1.0;



    T3FontCache* cache;



    void SetUp() override {

        cache = new T3FontCache(&validRef, m11, m12, m21, m22, 0, 0, 0, 0, true, false);

    }



    void TearDown() override {

        delete cache;

    }

};



TEST_F(T3FontCacheTest_1597, MatchesSameParameters_1597) {

    Ref sameRef = {1, 0};

    EXPECT_TRUE(cache->matches(&sameRef, m11, m12, m21, m22));

}



TEST_F(T3FontCacheTest_1597, MatchesDifferentID_1597) {

    Ref differentRef = {2, 0};

    EXPECT_FALSE(cache->matches(&differentRef, m11, m12, m21, m22));

}



TEST_F(T3FontCacheTest_1597, MatchesDifferentM11_1597) {

    EXPECT_FALSE(cache->matches(&validRef, m11 + 0.1, m12, m21, m22));

}



TEST_F(T3FontCacheTest_1597, MatchesDifferentM12_1597) {

    EXPECT_FALSE(cache->matches(&validRef, m11, m12 + 0.1, m21, m22));

}



TEST_F(T3FontCacheTest_1597, MatchesDifferentM21_1597) {

    EXPECT_FALSE(cache->matches(&validRef, m11, m12, m21 + 0.1, m22));

}



TEST_F(T3FontCacheTest_1597, MatchesDifferentM22_1597) {

    EXPECT_FALSE(cache->matches(&validRef, m11, m12, m21, m22 + 0.1));

}
