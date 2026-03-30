#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/regexp.h"



using namespace re2;



class CaptureNamesWalkerTest : public ::testing::Test {

protected:

    CaptureNamesWalker* walker_;



    void SetUp() override {

        walker_ = new CaptureNamesWalker();

    }



    void TearDown() override {

        delete walker_;

    }

};



TEST_F(CaptureNamesWalkerTest, TakeMapReturnsNullInitially_364) {

    EXPECT_EQ(nullptr, walker_->TakeMap());

}



TEST_F(CaptureNamesWalkerTest, PreVisitCapturesNameForCaptureOp_364) {

    Regexp* captureRegexp = Regexp::Capture(Regexp::NewLiteral('a', 0), 0, 1);

    bool stop = false;

    walker_->PreVisit(captureRegexp, 0, &stop);



    std::map<int, std::string>* map = walker_->TakeMap();

    EXPECT_NE(nullptr, map);

    EXPECT_EQ("1", (*map)[1]);



    captureRegexp->Decref();

}



TEST_F(CaptureNamesWalkerTest, PreVisitDoesNotCaptureNameForNonCaptureOp_364) {

    Regexp* literalRegexp = Regexp::NewLiteral('a', 0);

    bool stop = false;

    walker_->PreVisit(literalRegexp, 0, &stop);



    std::map<int, std::string>* map = walker_->TakeMap();

    EXPECT_EQ(nullptr, map);



    literalRegexp->Decref();

}



TEST_F(CaptureNamesWalkerTest, PreVisitHandlesMultipleCaptures_364) {

    Regexp* capture1 = Regexp::Capture(Regexp::NewLiteral('a', 0), 0, 1);

    Regexp* capture2 = Regexp::Capture(Regexp::NewLiteral('b', 0), 0, 2);



    bool stop = false;

    walker_->PreVisit(capture1, 0, &stop);

    walker_->PreVisit(capture2, 0, &stop);



    std::map<int, std::string>* map = walker_->TakeMap();

    EXPECT_NE(nullptr, map);

    EXPECT_EQ("1", (*map)[1]);

    EXPECT_EQ("2", (*map)[2]);



    capture1->Decref();

    capture2->Decref();

}



TEST_F(CaptureNamesWalkerTest, TakeMapReturnsNonNullAfterCapture_364) {

    Regexp* captureRegexp = Regexp::Capture(Regexp::NewLiteral('a', 0), 0, 1);

    bool stop = false;

    walker_->PreVisit(captureRegexp, 0, &stop);



    std::map<int, std::string>* map = walker_->TakeMap();

    EXPECT_NE(nullptr, map);



    captureRegexp->Decref();

}



TEST_F(CaptureNamesWalkerTest, TakeMapReturnsEmptyMapAfterSecondCapture_364) {

    Regexp* capture1 = Regexp::Capture(Regexp::NewLiteral('a', 0), 0, 1);

    bool stop = false;

    walker_->PreVisit(capture1, 0, &stop);



    std::map<int, std::string>* map1 = walker_->TakeMap();

    EXPECT_NE(nullptr, map1);



    Regexp* capture2 = Regexp::Capture(Regexp::NewLiteral('b', 0), 0, 2);

    walker_->PreVisit(capture2, 0, &stop);



    std::map<int, std::string>* map2 = walker_->TakeMap();

    EXPECT_EQ(nullptr, map2);



    capture1->Decref();

    capture2->Decref();

}
