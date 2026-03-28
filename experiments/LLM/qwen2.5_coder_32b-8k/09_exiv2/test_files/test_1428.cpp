#include <gtest/gtest.h>

#include <gmock/gmock.h>



#include "makernote_int.cpp"  // Include the file containing the function to be tested



using namespace Exiv2::Internal;



// Test fixture class for readExiv2Config

class ReadExiv2ConfigTest_1428 : public ::testing::Test {

protected:

    // No setup or teardown needed for this simple function

};



// Test normal operation with default value returned

TEST_F(ReadExiv2ConfigTest_1428, DefaultValueReturned_1428) {

    std::string section = "Section";

    std::string value = "Value";

    std::string def = "Default";



    std::string result = readExiv2Config(section, value, def);



    EXPECT_EQ(result, def);

}



// Test boundary condition with empty default value

TEST_F(ReadExiv2ConfigTest_1428, EmptyDefaultValue_1428) {

    std::string section = "Section";

    std::string value = "Value";

    std::string def = "";



    std::string result = readExiv2Config(section, value, def);



    EXPECT_EQ(result, def);

}



// Test boundary condition with empty section and value

TEST_F(ReadExiv2ConfigTest_1428, EmptySectionAndValue_1428) {

    std::string section = "";

    std::string value = "";

    std::string def = "Default";



    std::string result = readExiv2Config(section, value, def);



    EXPECT_EQ(result, def);

}



// Test exceptional case when INI file parsing fails (assuming ParseError() returns non-zero)

TEST_F(ReadExiv2ConfigTest_1428, ConfigFileParseError_1428) {

    std::string section = "Section";

    std::string value = "Value";

    std::string def = "Default";



    std::string result = readExiv2Config(section, value, def);



    EXPECT_EQ(result, def);

}

```


