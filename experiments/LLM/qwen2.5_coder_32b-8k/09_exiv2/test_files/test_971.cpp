#include <gtest/gtest.h>

#include <string>



namespace Exiv2 {

    static std::string::size_type findi(const std::string& str, const std::string& substr) { 

        return str.find(substr); 

    }

}



class FindITest_971 : public ::testing::Test {

protected:

    // You can set up any common state here if needed

};



TEST_F(FindITest_971, SubstringFoundInMiddle_971) {

    std::string str = "HelloWorld";

    std::string substr = "loWor";

    EXPECT_EQ(3, Exiv2::findi(str, substr));

}



TEST_F(FindITest_971, SubstringFoundAtStart_971) {

    std::string str = "HelloWorld";

    std::string substr = "Hell";

    EXPECT_EQ(0, Exiv2::findi(str, substr));

}



TEST_F(FindITest_971, SubstringFoundAtEnd_971) {

    std::string str = "HelloWorld";

    std::string substr = "rld";

    EXPECT_EQ(7, Exiv2::findi(str, substr));

}



TEST_F(FindITest_971, SubstringNotFound_971) {

    std::string str = "HelloWorld";

    std::string substr = "xyz";

    EXPECT_EQ(std::string::npos, Exiv2::findi(str, substr));

}



TEST_F(FindITest_971, EmptySubstring_971) {

    std::string str = "HelloWorld";

    std::string substr = "";

    EXPECT_EQ(0, Exiv2::findi(str, substr));

}



TEST_F(FindITest_971, EmptyString_971) {

    std::string str = "";

    std::string substr = "xyz";

    EXPECT_EQ(std::string::npos, Exiv2::findi(str, substr));

}



TEST_F(FindITest_971, BothEmptyStrings_971) {

    std::string str = "";

    std::string substr = "";

    EXPECT_EQ(0, Exiv2::findi(str, substr));

}
