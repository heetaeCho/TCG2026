#include <gtest/gtest.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffDirectoryTest_358 : public ::testing::Test {

protected:

    TiffDirectoryTest_358() 

        : directory(1, IfdId::rootIfd, false) {}



    TiffDirectory directory;

};



TEST_F(TiffDirectoryTest_358, InitialCountIsZero_358) {

    EXPECT_EQ(directory.doCount(), 0);

}



TEST_F(TiffDirectoryTest_358, CountIncreasesWithAddChild_358) {

    auto child = std::make_shared<TiffComponent>(1, IfdId::rootIfd);

    directory.doAddChild(child);

    EXPECT_EQ(directory.doCount(), 1);

}



TEST_F(TiffDirectoryTest_358, MultipleAddsIncreaseCount_358) {

    for (int i = 0; i < 5; ++i) {

        auto child = std::make_shared<TiffComponent>(i, IfdId::rootIfd);

        directory.doAddChild(child);

    }

    EXPECT_EQ(directory.doCount(), 5);

}



TEST_F(TiffDirectoryTest_358, CountDoesNotDecreaseAfterAddingAndRemoving_358) {

    auto child = std::make_shared<TiffComponent>(1, IfdId::rootIfd);

    directory.doAddChild(child);

    // Assuming there's no remove functionality provided in the interface,

    // we can't directly test decrease. But we ensure count doesn't go below added.

    EXPECT_GE(directory.doCount(), 1);

}



TEST_F(TiffDirectoryTest_358, HasNextReturnsFalseInitially_358) {

    EXPECT_FALSE(directory.hasNext());

}



// Assuming there's a way to set hasNext externally or through constructor

// Since the constructor sets it and we have no other method, this is boundary.

TEST_F(TiffDirectoryTest_358, HasNextReflectsConstructorValue_358) {

    TiffDirectory directoryWithNext(1, IfdId::rootIfd, true);

    EXPECT_TRUE(directoryWithNext.hasNext());

}
