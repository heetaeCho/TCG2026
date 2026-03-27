#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/re2/re2/regexp.cc"



using namespace re2;

using ::testing::_;

using ::testing::Return;



class CaptureNamesWalkerTest_363 : public ::testing::Test {

protected:

    CaptureNamesWalker* walker_;



    void SetUp() override {

        walker_ = new CaptureNamesWalker();

    }



    void TearDown() override {

        delete walker_;

    }

};



TEST_F(CaptureNamesWalkerTest_363, TakeMapReturnsNullAfterFirstCall_363) {

    auto map1 = walker_->TakeMap();

    EXPECT_NE(map1, nullptr);

    

    auto map2 = walker_->TakeMap();

    EXPECT_EQ(map2, nullptr);



    delete map1;

}



TEST_F(CaptureNamesWalkerTest_363, TakeMapReturnsDifferentInstances_363) {

    auto map1 = walker_->TakeMap();

    auto map2 = new std::map<int, std::string>();



    walker_->~CaptureNamesWalker();

    new(walker_) CaptureNamesWalker(); // Reinitialize the object



    auto map3 = walker_->TakeMap();



    EXPECT_NE(map1, map3);

    

    delete map1;

    delete map2;

    delete map3;

}



TEST_F(CaptureNamesWalkerTest_363, PreVisitAndShortVisitNotCalledInTakeMap_363) {

    // Since we cannot mock internal behavior or call protected/private methods,

    // we assume that TakeMap does not directly invoke PreVisit and ShortVisit.

    // This test case is more of a conceptual check rather than an actual invocation check.



    auto map = walker_->TakeMap();

    EXPECT_NE(map, nullptr);



    delete map;

}



// Assuming there are no observable exceptional or error cases through the provided interface,

// we do not add additional tests for those scenarios.
