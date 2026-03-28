#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/slice.hpp"



namespace Exiv2 {

namespace Internal {



// Mocking external collaborators if needed (none in this case)

class MutableSliceBaseMock : public MutableSliceBase<std::vector, int> {

public:

    using Base = MutableSliceBase<std::vector, int>;

    using Base::MutableSliceBase;



    MOCK_METHOD(auto&, at, (size_t index));

    MOCK_METHOD(auto, begin, (), (noexcept));

    MOCK_METHOD(auto, end, (), (noexcept));

};



TEST_F(MutableSliceBaseMock_11, SubSliceValidRange_11) {

    std::vector<int> data = {0, 1, 2, 3, 4};

    MutableSliceBaseMock slice(data, 0, 5);



    auto sub_slice = slice.subSlice(1, 4);

    EXPECT_EQ(sub_slice.begin() - data.data(), 1);

    EXPECT_EQ(sub_slice.end() - data.data(), 4);

}



TEST_F(MutableSliceBaseMock_11, SubSliceBoundaryConditionStart_11) {

    std::vector<int> data = {0, 1, 2, 3, 4};

    MutableSliceBaseMock slice(data, 0, 5);



    auto sub_slice = slice.subSlice(0, 1);

    EXPECT_EQ(sub_slice.begin() - data.data(), 0);

    EXPECT_EQ(sub_slice.end() - data.data(), 1);

}



TEST_F(MutableSliceBaseMock_11, SubSliceBoundaryConditionEnd_11) {

    std::vector<int> data = {0, 1, 2, 3, 4};

    MutableSliceBaseMock slice(data, 0, 5);



    auto sub_slice = slice.subSlice(4, 5);

    EXPECT_EQ(sub_slice.begin() - data.data(), 4);

    EXPECT_EQ(sub_slice.end() - data.data(), 5);

}



TEST_F(MutableSliceBaseMock_11, SubSliceOutOfRangeEnd_11) {

    std::vector<int> data = {0, 1, 2, 3, 4};

    MutableSliceBaseMock slice(data, 0, 5);



    EXPECT_THROW(slice.subSlice(1, 6), std::out_of_range);

}



TEST_F(MutableSliceBaseMock_11, SubSliceOutOfRangeStart_11) {

    std::vector<int> data = {0, 1, 2, 3, 4};

    MutableSliceBaseMock slice(data, 0, 5);



    EXPECT_THROW(slice.subSlice(6, 7), std::out_of_range);

}



TEST_F(MutableSliceBaseMock_11, SubSliceInvalidRange_11) {

    std::vector<int> data = {0, 1, 2, 3, 4};

    MutableSliceBaseMock slice(data, 0, 5);



    EXPECT_THROW(slice.subSlice(3, 2), std::out_of_range);

}



} // namespace Internal

} // namespace Exiv2
