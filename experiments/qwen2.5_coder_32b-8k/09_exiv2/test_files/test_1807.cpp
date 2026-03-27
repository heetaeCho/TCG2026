#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "futils.cpp"



namespace {



class StrErrorTest_1807 : public ::testing::Test {

protected:

    void SetUp() override {

        errno = 0; // Reset errno before each test

    }

};



TEST_F(StrErrorTest_1807, NormalOperation_ZeroErrno_1807) {

    EXPECT_EQ(Exiv2::strError(), "Success (errno = 0)");

}



TEST_F(StrErrorTest_1807, BoundaryCondition_MaximumErrno_1807) {

    errno = INT_MAX;

    std::string result = Exiv2::strError();

    EXPECT_TRUE(result.find("errno = ") != std::string::npos);

    EXPECT_TRUE(result.find(std::to_string(INT_MAX)) != std::string::npos);

}



TEST_F(StrErrorTest_1807, BoundaryCondition_MinimumErrno_1807) {

    errno = INT_MIN;

    std::string result = Exiv2::strError();

    EXPECT_TRUE(result.find("errno = ") != std::string::npos);

    EXPECT_TRUE(result.find(std::to_string(INT_MIN)) != std::string::npos);

}



TEST_F(StrErrorTest_1807, ExceptionalCase_ERange_1807) {

#ifdef EXV_STRERROR_R_CHAR_P

    // Simulate ERANGE by forcing a large error number that would exceed buffer size

    errno = 99999; // Assuming this is not a valid error code and will trigger ERANGE

    std::string result = Exiv2::strError();

    EXPECT_TRUE(result.find("Call failed (errno = ") != std::string::npos);

#else

    GTEST_SKIP() << "This test case is not applicable for the current configuration.";

#endif

}



} // namespace
