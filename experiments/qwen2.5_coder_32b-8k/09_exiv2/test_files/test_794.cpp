#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"

#include <sstream>



using namespace Exiv2;



class DataValueTest_794 : public ::testing::Test {

protected:

    DataValue dataValue_{TypeId::int8};



    void SetUp() override {

        // Initialization code if needed

    }

};



TEST_F(DataValueTest_794, ReadValidString_794) {

    std::string input = "1 2 3";

    int result = dataValue_.read(input);

    EXPECT_EQ(result, 0);

    EXPECT_EQ(dataValue_.count(), 3U);

}



TEST_F(DataValueTest_794, ReadEmptyString_794) {

    std::string input = "";

    int result = dataValue_.read(input);

    EXPECT_EQ(result, 0);

    EXPECT_EQ(dataValue_.count(), 0U);

}



TEST_F(DataValueTest_794, ReadSingleNumber_794) {

    std::string input = "42";

    int result = dataValue_.read(input);

    EXPECT_EQ(result, 0);

    EXPECT_EQ(dataValue_.count(), 1U);

}



TEST_F(DataValueTest_794, ReadInvalidString_794) {

    std::string input = "1 2 invalid";

    int result = dataValue_.read(input);

    EXPECT_NE(result, 0);

}



TEST_F(DataValueTest_794, ReadTrailingSpaces_794) {

    std::string input = "1 2 3   ";

    int result = dataValue_.read(input);

    EXPECT_EQ(result, 0);

    EXPECT_EQ(dataValue_.count(), 3U);

}



TEST_F(DataValueTest_794, ReadNegativeNumbers_794) {

    std::string input = "-1 -2 -3";

    int result = dataValue_.read(input);

    EXPECT_EQ(result, 0);

    EXPECT_EQ(dataValue_.count(), 3U);

}



TEST_F(DataValueTest_794, ReadLargeNumbers_794) {

    std::string input = "1000000 2000000";

    int result = dataValue_.read(input);

    EXPECT_EQ(result, 0);

    EXPECT_EQ(dataValue_.count(), 2U);

}
