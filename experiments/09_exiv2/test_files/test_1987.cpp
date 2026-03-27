#include <gtest/gtest.h>

#include "XMP_Const.h"

#include "client-glue/WXMP_Common.hpp"

#include "./TestProjects/exiv2/xmpsdk/src/XMPMeta.hpp"



TEST(WXMPMeta_GetVersionInfo_Test_1987, NormalOperation_1987) {

    XMP_VersionInfo info;

    WXMPMeta_GetVersionInfo_1(&info);



    // Assuming version components are positive numbers

    EXPECT_GE(info.major, 0);

    EXPECT_GE(info.minor, 0);

    EXPECT_GE(info.micro, 0);

    EXPECT_TRUE(info.isDebug == true || info.isDebug == false);

    EXPECT_GE(info.build, 0);

    EXPECT_GE(info.flags, 0);

}



TEST(WXMPMeta_GetVersionInfo_Test_1987, BoundaryConditions_1987) {

    XMP_VersionInfo info;

    WXMPMeta_GetVersionInfo_1(&info);



    // Check for minimum possible values

    EXPECT_LE(info.major, std::numeric_limits<XMP_Uns8>::max());

    EXPECT_LE(info.minor, std::numeric_limits<XMP_Uns8>::max());

    EXPECT_LE(info.micro, std::numeric_limits<XMP_Uns8>::max());

    EXPECT_TRUE(info.isDebug == true || info.isDebug == false);

    EXPECT_LE(info.build, std::numeric_limits<XMP_Uns32>::max());

    EXPECT_LE(info.flags, std::numeric_limits<XMP_Uns32>::max());



    // Check for message pointer

    EXPECT_NE(info.message, nullptr);  // Assuming message should not be null but empty string is acceptable

}



// No exceptional or error cases are observable through WXMPMeta_GetVersionInfo_1 based on the given interface.



TEST(WXMPMeta_GetVersionInfo_Test_1987, VerifyExternalInteractions_1987) {

    XMP_VersionInfo info;

    WXMPMeta_GetVersionInfo_1(&info);



    // Since WXMPMeta_GetVersionInfo_1 does not interact with any external collaborators,

    // there is nothing to verify in this case.

}
