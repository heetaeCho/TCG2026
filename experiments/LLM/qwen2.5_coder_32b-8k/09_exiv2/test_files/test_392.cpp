#include <gtest/gtest.h>

#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffSubIfdTest_392 : public ::testing::Test {

protected:

    Ifds ifds;

    TiffSubIfd tiffSubIfd{1, 2, 3};



    void SetUp() override {

        // Clear the IFDs for each test

        ifds.clear();

    }

};



TEST_F(TiffSubIfdTest_392, DoSize_ReturnsZeroForEmptyIfds_392) {

    EXPECT_EQ(tiffSubIfd.doSize(), 0U);

}



TEST_F(TiffSubIfdTest_392, DoSize_ReturnsCorrectSizeForNonEmptyIfds_392) {

    ifds.push_back(nullptr); // Adding a mock entry

    tiffSubIfd.ifds_ = ifds;

    EXPECT_EQ(tiffSubIfd.doSize(), 4U);



    ifds.push_back(nullptr); // Adding another mock entry

    tiffSubIfd.ifds_ = ifds;

    EXPECT_EQ(tiffSubIfd.doSize(), 8U);

}



TEST_F(TiffSubIfdTest_392, DoSize_ReturnsCorrectBoundaryValueForMaxIfds_392) {

    const size_t maxEntries = std::numeric_limits<size_t>::max() / 4;

    for (size_t i = 0; i < maxEntries; ++i) {

        ifds.push_back(nullptr);

    }

    tiffSubIfd.ifds_ = ifds;

    EXPECT_EQ(tiffSubIfd.doSize(), std::numeric_limits<size_t>::max() - 3); // Last entry will cause overflow



    // Adding one more entry to ensure it overflows correctly

    ifds.push_back(nullptr);

    tiffSubIfd.ifds_ = ifds;

    EXPECT_EQ(tiffSubIfd.doSize(), std::numeric_limits<size_t>::max());

}
