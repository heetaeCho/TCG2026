#include <gtest/gtest.h>

#include "client-glue/WXMP_Common.hpp"

#include "./TestProjects/exiv2/xmpsdk/src/WXMPMeta.cpp"



class WXMPMeta_Initialize_Test_1988 : public ::testing::Test {

protected:

    WXMP_Result result;

};



TEST_F(WXMPMeta_Initialize_Test_1988, Initialize_Success_1988) {

    WXMPMeta_Initialize_1(&result);

    EXPECT_EQ(result.int32Result, true);

}



TEST_F(WXMPMeta_Initialize_Test_1988, Initialize_Failure_1988) {

    // Assuming there's a way to force failure, if not this test will always pass

    WXMPMeta_Initialize_1(&result);

    EXPECT_EQ(result.int32Result, false);

}
