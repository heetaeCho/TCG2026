#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/splash/SplashFontFileID.h"

#include "TestProjects/poppler/poppler/Ref.h"



class SplashOutFontFileIDTest : public ::testing::Test {

protected:

    Ref ref1{42, 0};

    Ref ref2{43, 1};



    std::unique_ptr<SplashOutFontFileID> fontFileID1;

    std::unique_ptr<SplashOutFontFileID> fontFileID2;

    std::unique_ptr<SplashOutFontFileID> fontFileIDSameRef;



    void SetUp() override {

        fontFileID1 = std::make_unique<SplashOutFontFileID>(&ref1);

        fontFileID2 = std::make_unique<SplashOutFontFileID>(&ref2);

        fontFileIDSameRef = std::make_unique<SplashOutFontFileID>(&ref1);

    }

};



TEST_F(SplashOutFontFileIDTest_2778, MatchesSameReference_2778) {

    EXPECT_TRUE(fontFileID1->matches(*fontFileIDSameRef));

}



TEST_F(SplashOutFontFileIDTest_2778, MatchesDifferentReferences_2778) {

    EXPECT_FALSE(fontFileID1->matches(*fontFileID2));

}



TEST_F(SplashOutFontFileIDTest_2778, MatchesSelf_2778) {

    EXPECT_TRUE(fontFileID1->matches(*fontFileID1));

}



TEST_F(SplashOutFontFileIDTest_2778, MatchesInvalidReference_2778) {

    Ref invalidRef = Ref::INVALID();

    std::unique_ptr<SplashOutFontFileID> fontFileIDInvalid = std::make_unique<SplashOutFontFileID>(&invalidRef);

    EXPECT_FALSE(fontFileID1->matches(*fontFileIDInvalid));

}



TEST_F(SplashOutFontFileIDTest_2778, MatchesBoundaryConditions_2778) {

    Ref boundaryRef1{0, 0};

    Ref boundaryRef2{INT_MAX, INT_MAX};

    std::unique_ptr<SplashOutFontFileID> fontFileIDBoundary1 = std::make_unique<SplashOutFontFileID>(&boundaryRef1);

    std::unique_ptr<SplashOutFontFileID> fontFileIDBoundary2 = std::make_unique<SplashOutFontFileID>(&boundaryRef2);



    EXPECT_TRUE(fontFileIDBoundary1->matches(*fontFileIDBoundary1));

    EXPECT_FALSE(fontFileIDBoundary1->matches(*fontFileIDBoundary2));

}
