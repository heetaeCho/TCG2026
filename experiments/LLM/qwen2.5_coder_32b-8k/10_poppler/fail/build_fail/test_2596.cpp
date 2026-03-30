#include <gtest/gtest.h>

#include <gmock/gmock.h>

extern "C" {

    #include "./TestProjects/poppler/glib/poppler.cc"

}



TEST(PopplerErrorQuarkTest_2596, ReturnsSameGQuarkOnMultipleCalls_2596) {

    GQuark quark1 = poppler_error_quark();

    GQuark quark2 = poppler_error_quark();

    EXPECT_EQ(quark1, quark2);

}



TEST(PopplerErrorQuarkTest_2596, ReturnsNonZeroGQuark_2596) {

    GQuark quark = poppler_error_quark();

    EXPECT_NE(quark, 0);

}
