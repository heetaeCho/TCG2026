#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "regexp.h"



namespace re2 {



class NamedCapturesWalkerTest : public ::testing::Test {

protected:

    NamedCapturesWalker* walker;



    void SetUp() override {

        walker = new NamedCapturesWalker();

    }



    void TearDown() override {

        delete walker;

    }

};



TEST_F(NamedCapturesWalkerTest_358, TakeMapReturnsNullAfterCall_358) {

    std::map<std::string, int>* map = walker->TakeMap();

    EXPECT_EQ(map, nullptr);

}



TEST_F(NamedCapturesWalkerTest_358, TakeMapReturnsDifferentMapsOnConsecutiveCalls_358) {

    std::map<std::string, int>* map1 = new std::map<std::string, int>();

    walker->TakeMap(); // Set map_ to nullptr

    walker->map_ = map1; // Manually set a new map



    std::map<std::string, int>* returnedMap1 = walker->TakeMap();

    EXPECT_EQ(returnedMap1, map1);



    std::map<std::string, int>* map2 = new std::map<std::string, int>();

    walker->map_ = map2; // Manually set another new map



    std::map<std::string, int>* returnedMap2 = walker->TakeMap();

    EXPECT_EQ(returnedMap2, map2);

    EXPECT_NE(returnedMap1, returnedMap2);



    delete map1;

    delete map2;

}



}  // namespace re2
