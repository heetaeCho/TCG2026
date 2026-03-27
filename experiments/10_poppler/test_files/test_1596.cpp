#include <gtest/gtest.h>

#include "SplashOutputDev.cc"

#include "SplashFontFileID.h"



class SplashOutFontFileIDTest_1596 : public ::testing::Test {

protected:

    Ref ref1 {1, 0};

    Ref ref2 {2, 0};



    std::unique_ptr<SplashOutFontFileID> fontFileID1;

    std::unique_ptr<SplashOutFontFileID> fontFileID2;



    void SetUp() override {

        fontFileID1 = std::make_unique<SplashOutFontFileID>(&ref1);

        fontFileID2 = std::make_unique<SplashOutFontFileID>(&ref2);

    }

};



TEST_F(SplashOutFontFileIDTest_1596, MatchesSameRef_1596) {

    EXPECT_TRUE(fontFileID1->matches(*fontFileID1));

}



TEST_F(SplashOutFontFileIDTest_1596, MatchesDifferentRef_1596) {

    EXPECT_FALSE(fontFileID1->matches(*fontFileID2));

}



TEST_F(SplashOutFontFileIDTest_1596, MatchesNullPtr_1596) {

    SplashFontFileID nullId;

    EXPECT_FALSE(fontFileID1->matches(nullId));

}
