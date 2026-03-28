#include <gtest/gtest.h>

#include "makernote_int.hpp"



using namespace Exiv2::Internal;



class SamsungMnHeaderTest : public ::testing::Test {

protected:

    SamsungMnHeader header;

};



TEST_F(SamsungMnHeaderTest, BaseOffset_ReturnsInput_1490) {

    size_t mnOffset = 42;

    EXPECT_EQ(header.baseOffset(mnOffset), mnOffset);

}



TEST_F(SamsungMnHeaderTest, BaseOffset_ZeroOffset_ReturnsZero_1490) {

    size_t mnOffset = 0;

    EXPECT_EQ(header.baseOffset(mnOffset), mnOffset);

}



TEST_F(SamsungMnHeaderTest, BaseOffset_MaxSize_ReturnsMaxSize_1490) {

    size_t mnOffset = std::numeric_limits<size_t>::max();

    EXPECT_EQ(header.baseOffset(mnOffset), mnOffset);

}
