#include <gtest/gtest.h>

#include "poppler-form.cc" // Adjust path as necessary



class PopplerNSSSupportTest_1370 : public ::testing::Test {

protected:

    // Setup and teardown can be done here if needed

};



TEST_F(PopplerNSSSupportTest_1370, HasNSSSupport_ReturnsTrue_WhenEnabled_1370) {

#if ENABLE_NSS3

    EXPECT_TRUE(Poppler::hasNSSSupport());

#else

    GTEST_SKIP() << "NSS is not enabled in this build configuration.";

#endif

}



TEST_F(PopplerNSSSupportTest_1370, HasNSSSupport_ReturnsFalse_WhenDisabled_1370) {

#if !ENABLE_NSS3

    EXPECT_FALSE(Poppler::hasNSSSupport());

#else

    GTEST_SKIP() << "NSS is enabled in this build configuration.";

#endif

}
