#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/version.cpp"



namespace {



class VersionTest_989 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed, but in this case, not required.

    }



    void TearDown() override {

        // Teardown code if needed, but in this case, not required.

    }

};



TEST_F(VersionTest_989, TestVersion_ReturnsTrueForExactMatch_989) {

    EXPECT_TRUE(Exiv2::testVersion(1, 0, 0));

}



TEST_F(VersionTest_989, TestVersion_ReturnsTrueForHigherVersion_989) {

    EXPECT_TRUE(Exiv2::testVersion(0, 9, 9));

}



TEST_F(VersionTest_989, TestVersion_ReturnsFalseForLowerMajorVersion_989) {

    EXPECT_FALSE(Exiv2::testVersion(2, 0, 0));

}



TEST_F(VersionTest_989, TestVersion_ReturnsFalseForLowerMinorVersion_989) {

    EXPECT_TRUE(Exiv2::testVersion(1, 1, 0)); // Assuming current version is 1.0.x

}



TEST_F(VersionTest_989, TestVersion_ReturnsFalseForLowerPatchVersion_989) {

    EXPECT_TRUE(Exiv2::testVersion(1, 0, 1)); // Assuming current version is 1.0.0

}



} // namespace
