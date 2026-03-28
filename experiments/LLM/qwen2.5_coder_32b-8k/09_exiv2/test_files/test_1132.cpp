#include <gtest/gtest.h>

#include "exiv2/types.hpp"



namespace Exiv2 {

    Slice<const byte*> makeSlice(const DataBuf& buf, size_t begin, size_t end);

}



TEST(makeSliceTest_1132, NormalOperation_1132) {

    Exiv2::DataBuf data(5);

    for (size_t i = 0; i < 5; ++i) {

        data.write_uint8(i, static_cast<uint8_t>(i + 1));

    }

    auto slice = Exiv2::makeSlice(data, 1, 4);

    EXPECT_EQ(slice.size(), 3u);

    for (size_t i = 0; i < 3; ++i) {

        EXPECT_EQ(slice.data()[i], static_cast<uint8_t>(i + 2));

    }

}



TEST(makeSliceTest_1132, BoundaryCondition_StartEqualsEnd_1132) {

    Exiv2::DataBuf data(5);

    auto slice = Exiv2::makeSlice(data, 2, 2);

    EXPECT_EQ(slice.size(), 0u);

}



TEST(makeSliceTest_1132, BoundaryCondition_FullBuffer_1132) {

    Exiv2::DataBuf data(5);

    auto slice = Exiv2::makeSlice(data, 0, 5);

    EXPECT_EQ(slice.size(), 5u);

}



TEST(makeSliceTest_1132, ExceptionalCase_OutOfBounds_1132) {

    Exiv2::DataBuf data(5);

    EXPECT_THROW(Exiv2::makeSlice(data, 0, 6), std::out_of_range);

}



TEST(makeSliceTest_1132, ExceptionalCase_BeginGreaterThanEnd_1132) {

    Exiv2::DataBuf data(5);

    EXPECT_THROW(Exiv2::makeSlice(data, 3, 2), std::invalid_argument);

}
