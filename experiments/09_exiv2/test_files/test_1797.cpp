#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/crwimage_int.hpp"



using namespace Exiv2::Internal;



class CrwMapTest_1797 : public ::testing::Test {

protected:

    CrwMap crwMap;

    std::vector<std::pair<uint16_t, uint16_t>> crwSubDir_{ {1, 0}, {2, 1}, {3, 2} };

};



TEST_F(CrwMapTest_1797, LoadStack_NormalOperation_1797) {

    CrwDirs crwDirs;

    uint16_t crwDir = 3;



    crwMap.loadStack(crwDirs, crwDir);



    ASSERT_EQ(crwDirs.size(), 3);

    EXPECT_EQ(crwDirs[0], std::make_pair(3, 2));

    EXPECT_EQ(crwDirs[1], std::make_pair(2, 1));

    EXPECT_EQ(crwDirs[2], std::make_pair(1, 0));

}



TEST_F(CrwMapTest_1797, LoadStack_BoundaryCondition_NoMatch_1797) {

    CrwDirs crwDirs;

    uint16_t crwDir = 4;



    crwMap.loadStack(crwDirs, crwDir);



    EXPECT_TRUE(crwDirs.empty());

}



TEST_F(CrwMapTest_1797, LoadStack_BoundaryCondition_EmptySubDir_1797) {

    CrwDirs crwDirs;

    uint16_t crwDir = 3;



    crwSubDir_.clear();

    crwMap.loadStack(crwDirs, crwDir);



    EXPECT_TRUE(crwDirs.empty());

}



TEST_F(CrwMapTest_1797, LoadStack_ExceptionalCase_SelfReferencing_1797) {

    CrwDirs crwDirs;

    uint16_t crwDir = 1;



    crwSubDir_[0].second = 1; // Self-referencing

    crwMap.loadStack(crwDirs, crwDir);



    EXPECT_EQ(crwDirs.size(), 1);

    EXPECT_EQ(crwDirs[0], std::make_pair(1, 1));

}
