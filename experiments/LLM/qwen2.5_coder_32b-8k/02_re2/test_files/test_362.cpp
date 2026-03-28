#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/regexp.h"

#include <map>



using namespace re2;



// Mocking Regexp class for testing CaptureNamesWalker

class MockRegexp : public Regexp {

public:

    MOCK_METHOD(Ignored, Type, (), (const override));

    MOCK_METHOD(std::string, ToString, (), (const override));

    MOCK_METHOD(int, NumSubs, (), (const override));

};



class CaptureNamesWalkerTest_362 : public ::testing::Test {

protected:

    CaptureNamesWalker* walker;



    void SetUp() override {

        walker = new CaptureNamesWalker();

    }



    void TearDown() override {

        delete walker;

    }

};



TEST_F(CaptureNamesWalkerTest_362, TakeMapReturnsValidPointer_362) {

    std::map<int, std::string>* map = walker->TakeMap();

    EXPECT_NE(map, nullptr);

}



TEST_F(CaptureNamesWalkerTest_362, PreVisitCalledWithCorrectParameters_362) {

    MockRegexp mock_regexp;

    bool stop = false;



    EXPECT_CALL(mock_regexp, Type()).WillOnce(::testing::Return(0));

    EXPECT_CALL(mock_regexp, ToString()).WillOnce(::testing::Return("mock"));

    EXPECT_CALL(mock_regexp, NumSubs()).WillOnce(::testing::Return(1));



    walker->PreVisit(&mock_regexp, 0, &stop);

}



TEST_F(CaptureNamesWalkerTest_362, ShortVisitCalledWithCorrectParameters_362) {

    MockRegexp mock_regexp;



    EXPECT_CALL(mock_regexp, Type()).WillOnce(::testing::Return(0));

    EXPECT_CALL(mock_regexp, ToString()).WillOnce(::testing::Return("mock"));

    EXPECT_CALL(mock_regexp, NumSubs()).WillOnce(::testing::Return(1));



    walker->ShortVisit(&mock_regexp, 0);

}
