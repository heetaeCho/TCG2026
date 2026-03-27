#include <gtest/gtest.h>

#include "makernote_int.hpp"



using namespace Exiv2::Internal;



class FujiMnHeaderTest_1457 : public ::testing::Test {

protected:

    FujiMnHeader header;

};



TEST_F(FujiMnHeaderTest_1457, BaseOffset_ReturnsSameAsInput_1457) {

    size_t mnOffset = 100;

    EXPECT_EQ(header.baseOffset(mnOffset), mnOffset);

}



TEST_F(FujiMnHeaderTest_1457, BaseOffset_ZeroOffset_ReturnsZero_1457) {

    size_t mnOffset = 0;

    EXPECT_EQ(header.baseOffset(mnOffset), mnOffset);

}



TEST_F(FujiMnHeaderTest_1457, BaseOffset_MaxSize_ReturnsMaxSize_1457) {

    size_t mnOffset = std::numeric_limits<size_t>::max();

    EXPECT_EQ(header.baseOffset(mnOffset), mnOffset);

}
