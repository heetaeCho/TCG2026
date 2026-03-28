#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/version.cpp"



using namespace Exiv2;



// Test fixture for versionNumberHexString

class VersionNumberHexStringTest_987 : public ::testing::Test {

protected:

    // Setup and teardown can be done here if necessary

};



TEST_F(VersionNumberHexStringTest_987, ReturnsValidHexString_987) {

    std::string result = versionNumberHexString();

    EXPECT_EQ(result.size(), 6u); // Hex string should be 6 characters long

    EXPECT_THAT(result, ::testing::MatchesRegex("[0-9a-fA-F]+")); // Should only contain hex digits

}



TEST_F(VersionNumberHexStringTest_987, ConsistentOutput_987) {

    std::string result1 = versionNumberHexString();

    std::string result2 = versionNumberHexString();

    EXPECT_EQ(result1, result2); // Subsequent calls should return the same value

}
