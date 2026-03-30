#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "dyndep_parser.h"



using ::testing::_;

using ::testing::Eq;

using ::testing::StrEq;



class DyndepParserTest_110 : public ::testing::Test {

protected:

    State mock_state;

    FileReader mock_file_reader;

    DyndepFile mock_dyndep_file;

    DyndepParser parser;



    DyndepParserTest_110() : parser(&mock_state, &mock_file_reader, &mock_dyndep_file) {}

};



TEST_F(DyndepParserTest_110, ParseValidInput_ReturnsTrue_110) {

    std::string input = "valid_input";

    std::string err;



    bool result = parser.ParseTest(input, &err);



    EXPECT_TRUE(result);

    EXPECT_EQ(err, "");

}



TEST_F(DyndepParserTest_110, ParseInvalidInput_ReturnsFalseAndSetsError_110) {

    std::string input = "invalid_input";

    std::string err;



    bool result = parser.ParseTest(input, &err);



    EXPECT_FALSE(result);

    EXPECT_NE(err, "");

}



TEST_F(DyndepParserTest_110, ParseEmptyInput_ReturnsFalseAndSetsError_110) {

    std::string input = "";

    std::string err;



    bool result = parser.ParseTest(input, &err);



    EXPECT_FALSE(result);

    EXPECT_NE(err, "");

}



TEST_F(DyndepParserTest_110, ParseNullptrForErr_ReturnsFalse_110) {

    std::string input = "valid_input";

    std::string* err = nullptr;



    bool result = parser.ParseTest(input, err);



    EXPECT_FALSE(result);

}
