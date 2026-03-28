#include <gtest/gtest.h>



extern const char *poppler_get_version(void);



TEST(PopplerVersionTest_2598, ReturnsCorrectVersionString_2598) {

    EXPECT_STREQ(poppler_get_version(), "26.01.90");

}
