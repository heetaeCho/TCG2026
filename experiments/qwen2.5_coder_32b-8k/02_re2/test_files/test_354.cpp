#include <gtest/gtest.h>

#include "re2/regexp.h"



using namespace re2;



class NumCapturesWalkerTest_354 : public ::testing::Test {

protected:

    void SetUp() override {

        walker = new NumCapturesWalker();

    }



    void TearDown() override {

        delete walker;

    }



    NumCapturesWalker* walker;

};



TEST_F(NumCapturesWalkerTest_354, PreVisit_CaptureOp_IncrementsCount_354) {

    Regexp* captureRegexp = Regexp::Capture(nullptr, 0, 1);

    bool stop = false;

    walker->PreVisit(captureRegexp, 0, &stop);



    EXPECT_EQ(walker->ncapture(), 1);

    captureRegexp->Decref();

}



TEST_F(NumCapturesWalkerTest_354, PreVisit_NonCaptureOp_DoesNotIncrementCount_354) {

    Regexp* literalRegexp = Regexp::NewLiteral('a', 0);

    bool stop = false;

    walker->PreVisit(literalRegexp, 0, &stop);



    EXPECT_EQ(walker->ncapture(), 0);

    literalRegexp->Decref();

}



TEST_F(NumCapturesWalkerTest_354, PreVisit_MultipleCaptureOps_IncrementsCountCorrectly_354) {

    Regexp* capture1 = Regexp::Capture(nullptr, 0, 1);

    Regexp* capture2 = Regexp::Capture(nullptr, 0, 2);



    bool stop = false;

    walker->PreVisit(capture1, 0, &stop);

    walker->PreVisit(capture2, 0, &stop);



    EXPECT_EQ(walker->ncapture(), 2);



    capture1->Decref();

    capture2->Decref();

}



TEST_F(NumCapturesWalkerTest_354, PreVisit_NoOp_DoesNotChangeCount_354) {

    bool stop = false;

    walker->PreVisit(nullptr, 0, &stop);



    EXPECT_EQ(walker->ncapture(), 0);

}
