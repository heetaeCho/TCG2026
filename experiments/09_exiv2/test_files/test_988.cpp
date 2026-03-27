#include <gtest/gtest.h>

#include "version.cpp"



class VersionTest_988 : public ::testing::Test {

protected:

    // You can set up any common state here if needed.

};



TEST_F(VersionTest_988, ReturnsNonNullString_988) {

    const char* ver = Exiv2::version();

    EXPECT_NE(ver, nullptr);

}



TEST_F(VersionTest_988, StringIsNotEmpty_988) {

    const char* ver = Exiv2::version();

    EXPECT_GT(strlen(ver), 0);

}



TEST_F(VersionTest_988, ConsistentReturnValue_988) {

    const char* ver1 = Exiv2::version();

    const char* ver2 = Exiv2::version();

    EXPECT_STREQ(ver1, ver2);

}
