#include <gtest/gtest.h>
#include "makernote_int.hpp"

using namespace Exiv2::Internal;

class SamsungMnHeaderTest_1489 : public ::testing::Test {
protected:
    SamsungMnHeader header;
};

TEST_F(SamsungMnHeaderTest_1489, DefaultConstructor_1489) {
    SamsungMnHeader h;
    // Should be constructible without issues
    SUCCEED();
}

TEST_F(SamsungMnHeaderTest_1489, SizeReturnsZero_1489) {
    EXPECT_EQ(header.size(), 0u);
}

TEST_F(SamsungMnHeaderTest_1489, SizeIsConsistent_1489) {
    // Calling size multiple times should return the same value
    EXPECT_EQ(header.size(), header.size());
}

TEST_F(SamsungMnHeaderTest_1489, SizeReturnsSizeT_1489) {
    size_t s = header.size();
    EXPECT_EQ(s, 0u);
}

TEST_F(SamsungMnHeaderTest_1489, MultipleInstancesSameSize_1489) {
    SamsungMnHeader header2;
    EXPECT_EQ(header.size(), header2.size());
}
