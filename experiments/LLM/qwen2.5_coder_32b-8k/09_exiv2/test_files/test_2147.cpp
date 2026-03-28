#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/slice.hpp"



namespace {



using namespace Exiv2::Internal;



class ContainerStorageTest : public ::testing::Test {

protected:

    std::vector<int> data;

};



TEST_F(ContainerStorageTest_2147, Constructor_ValidRange_2147) {

    size_t end = 5;

    data.resize(end);

    EXPECT_NO_THROW(ContainerStorage cs(data, 0, end));

}



TEST_F(ContainerStorageTest_2147, Constructor_EndEqualsSize_2147) {

    size_t end = data.size();

    EXPECT_NO_THROW(ContainerStorage cs(data, 0, end));

}



TEST_F(ContainerStorageTest_2147, Constructor_OutOfRange_2147) {

    size_t end = data.size() + 1;

    EXPECT_THROW(ContainerStorage cs(data, 0, end), std::out_of_range);

}



TEST_F(ContainerStorageTest_2147, Constructor_BeginGreaterThanEnd_2147) {

    size_t begin = 5;

    size_t end = 3;

    data.resize(begin);

    EXPECT_THROW(ContainerStorage cs(data, begin, end), std::out_of_range);

}



} // namespace
