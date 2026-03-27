#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the function declaration is available in a header file.

extern "C" char *poppler_get_nss_dir(void);

extern "C" void g_free(char *data);



class PopplerNSSDirTest_2410 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(PopplerNSSDirTest_2410, GetNSSDirReturnsNonNullWhenEnabled_2410) {

#if ENABLE_NSS3

    char* result = poppler_get_nss_dir();

    ASSERT_NE(result, nullptr);

    g_free(result);

#else

    GTEST_SKIP() << "ENABLE_NSS3 is not defined.";

#endif

}



TEST_F(PopplerNSSDirTest_2410, GetNSSDirReturnsNullWhenDisabled_2410) {

#if !ENABLE_NSS3

    char* result = poppler_get_nss_dir();

    EXPECT_EQ(result, nullptr);

#else

    GTEST_SKIP() << "ENABLE_NSS3 is defined.";

#endif

}
