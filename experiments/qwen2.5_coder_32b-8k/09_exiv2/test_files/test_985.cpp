#include <gtest/gtest.h>

#include "version.cpp"



namespace {



class VersionTest_985 : public ::testing::Test {

protected:

    // No additional setup or teardown needed for this simple function.

};



TEST_F(VersionTest_985, ReturnsCorrectVersionNumber_985) {

    uint32_t version = Exiv2::versionNumber();

    // Assuming EXIV2_MAJOR_VERSION, EXIV2_MINOR_VERSION, and EXIV2_PATCH_VERSION are defined correctly

    // This test checks if the version number is constructed as expected.

    EXPECT_EQ(version, EXIV2_MAKE_VERSION(EXIV2_MAJOR_VERSION, EXIV2_MINOR_VERSION, EXIV2_PATCH_VERSION));

}



}  // namespace
