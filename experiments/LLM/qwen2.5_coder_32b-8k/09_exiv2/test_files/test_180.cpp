#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "TestProjects/exiv2/src/tags_int.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class PrintTagString4Test_180 : public ::testing::Test {

protected:

    std::ostringstream os_;

    Value value_;

    const ExifData* data_ = nullptr;



    static constexpr StringTagDetails tagDetails_[1] = {{"", 0, 0}};



    PrintTagString4Test_180() : value_(TypeId::unsignedLong) {

        // Initialize the value with some test data

        std::vector<uint32_t> testData = {1, 2, 3, 4};

        value_.setDataArea(reinterpret_cast<const byte*>(testData.data()), testData.size() * sizeof(uint32_t));

    }

};



TEST_F(PrintTagString4Test_180, ValueCountLessThanFour_180) {

    // Arrange

    value_.setDataArea(nullptr, 0); // Set count to 0



    // Act

    printTagString4<1>(os_, value_, data_);



    // Assert

    EXPECT_EQ(os_.str(), "(Exiv2::Value())");

}



TEST_F(PrintTagString4Test_180, ValueCountExactlyFour_180) {

    // Arrange

    std::vector<uint32_t> testData = {1, 2, 3, 4};

    value_.setDataArea(reinterpret_cast<const byte*>(testData.data()), testData.size() * sizeof(uint32_t));



    // Act

    printTagString4<1>(os_, value_, data_);



    // Assert

    EXPECT_EQ(os_.str(), "1 2 3 4");

}



TEST_F(PrintTagString4Test_180, ValueCountMoreThanFour_180) {

    // Arrange

    std::vector<uint32_t> testData = {1, 2, 3, 4, 5};

    value_.setDataArea(reinterpret_cast<const byte*>(testData.data()), testData.size() * sizeof(uint32_t));



    // Act

    printTagString4<1>(os_, value_, data_);



    // Assert

    EXPECT_EQ(os_.str(), "1 2 3 4");

}



TEST_F(PrintTagString4Test_180, EmptyExifData_180) {

    // Arrange

    ExifData emptyData;



    // Act

    printTagString4<1>(os_, value_, &emptyData);



    // Assert

    EXPECT_EQ(os_.str(), "1 2 3 4");

}



TEST_F(PrintTagString4Test_180, NonEmptyExifData_180) {

    // Arrange

    ExifData data;

    std::vector<uint32_t> testData = {1, 2, 3, 4};

    value_.setDataArea(reinterpret_cast<const byte*>(testData.data()), testData.size() * sizeof(uint32_t));



    // Act

    printTagString4<1>(os_, value_, &data);



    // Assert

    EXPECT_EQ(os_.str(), "1 2 3 4");

}
