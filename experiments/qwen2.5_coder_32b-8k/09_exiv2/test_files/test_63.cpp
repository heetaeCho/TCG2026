#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/image_int.hpp"



using namespace Exiv2::Internal;



// Mocking any necessary dependencies here would go here.

// However, for this particular function, there are no external collaborators to mock.



class BinaryToStringTest_63 : public ::testing::Test {

protected:

    // Setup code if needed

};



TEST_F(BinaryToStringTest_63, NormalOperation_63) {

    std::vector<char> data = {'H', 'e', 'l', 'l', 'o'};

    Slice<char> sl(data.data(), data.size());

    auto result = binaryToString(std::move(sl));

    EXPECT_EQ(result, "Hello");

}



TEST_F(BinaryToStringTest_63, EmptyData_63) {

    std::vector<char> empty_data;

    Slice<char> sl(empty_data.data(), empty_data.size());

    auto result = binaryToString(std::move(sl));

    EXPECT_EQ(result, "");

}



TEST_F(BinaryToStringTest_63, SingleCharacter_63) {

    std::vector<char> data = {'A'};

    Slice<char> sl(data.data(), data.size());

    auto result = binaryToString(std::move(sl));

    EXPECT_EQ(result, "A");

}



TEST_F(BinaryToStringTest_63, BoundaryConditionMaxSize_63) {

    std::string max_data(1024, 'x'); // Assuming a reasonable max size for testing

    Slice<char> sl(const_cast<char*>(max_data.data()), max_data.size());

    auto result = binaryToString(std::move(sl));

    EXPECT_EQ(result, max_data);

}



TEST_F(BinaryToStringTest_63, BinaryData_63) {

    std::vector<char> data = {0x48, 0x65, 0x6c, 0x6c, 0x6f};

    Slice<char> sl(data.data(), data.size());

    auto result = binaryToString(std::move(sl));

    EXPECT_EQ(result, "Hello");

}



TEST_F(BinaryToStringTest_63, NonPrintableCharacters_63) {

    std::vector<char> data = {0x07, 0x08, 0x09};

    Slice<char> sl(data.data(), data.size());

    auto result = binaryToString(std::move(sl));

    EXPECT_EQ(result, "\a\b\t");

}
