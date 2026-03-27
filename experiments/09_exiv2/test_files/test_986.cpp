#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/version.cpp"



namespace Exiv2 {

    // Mocking external collaborators if needed (none in this case)

}



class VersionStringTest_986 : public ::testing::Test {

protected:

    // Setup and teardown can be done here if necessary

};



TEST_F(VersionStringTest_986, ReturnsFormattedVersionString_986) {

    std::string version = Exiv2::versionString();

    EXPECT_EQ(version, stringFormat("{}.{}.{}", EXIV2_MAJOR_VERSION, EXIV2_MINOR_VERSION, EXIV2_PATCH_VERSION));

}



TEST_F(VersionStringTest_986, ConsistentOutputOnRepeatedCalls_986) {

    std::string version1 = Exiv2::versionString();

    std::string version2 = Exiv2::versionString();

    EXPECT_EQ(version1, version2);

}

```


