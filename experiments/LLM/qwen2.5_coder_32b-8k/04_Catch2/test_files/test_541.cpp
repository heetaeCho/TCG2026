#include <gtest/gtest.h>

#include "catch_output_redirect.hpp"



namespace Catch {

    bool isRedirectAvailable(OutputRedirect::Kind kind);

}



class OutputRedirectTest_541 : public ::testing::Test {};



TEST_F(OutputRedirectTest_541, IsRedirectAvailable_None_ReturnsTrue_541) {

    EXPECT_TRUE(Catch::isRedirectAvailable(Catch::OutputRedirect::None));

}



TEST_F(OutputRedirectTest_541, IsRedirectAvailable_Streams_ReturnsTrue_541) {

    EXPECT_TRUE(Catch::isRedirectAvailable(Catch::OutputRedirect::Streams));

}



#if defined( CATCH_CONFIG_NEW_CAPTURE )

TEST_F(OutputRedirectTest_541, IsRedirectAvailable_FileDescriptors_ReturnsTrue_541) {

    EXPECT_TRUE(Catch::isRedirectAvailable(Catch::OutputRedirect::FileDescriptors));

}

#else

TEST_F(OutputRedirectTest_541, IsRedirectAvailable_FileDescriptors_ReturnsFalse_541) {

    EXPECT_FALSE(Catch::isRedirectAvailable(Catch::OutputRedirect::FileDescriptors));

}

#endif



TEST_F(OutputRedirectTest_541, IsRedirectAvailable_DefaultKind_ReturnsFalse_541) {

    EXPECT_FALSE(Catch::isRedirectAvailable(static_cast<Catch::OutputRedirect::Kind>(-1)));

}



TEST_F(OutputRedirectTest_541, IsRedirectAvailable_UnrecognizedKind_ReturnsFalse_541) {

    EXPECT_FALSE(Catch::isRedirectAvailable(static_cast<Catch::OutputRedirect::Kind>(3)));

}
