#include <gtest/gtest.h>

#include "XMP_Const.h"

#include "client-glue/WXMP_Common.hpp"



// Assuming WXMPMeta_SetGlobalOptions_1 is in a namespace or header file that needs to be included.

// For this test, we will assume it's accessible.



class WXMPMetaTest_1994 : public ::testing::Test {

protected:

    WXMP_Result wResult;

};



TEST_F(WXMPMetaTest_1994, SetGlobalOptions_DefaultOptions_1994) {

    XMP_OptionBits options = 0;

    WXMP_SetGlobalOptions_1(options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr); // Assuming no error message if successful

}



TEST_F(WXMPMetaTest_1994, SetGlobalOptions_NonDefaultOptions_1994) {

    XMP_OptionBits options = 0x0001; // Example non-default option

    WXMP_SetGlobalOptions_1(options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr); // Assuming no error message if successful

}



TEST_F(WXMPMetaTest_1994, SetGlobalOptions_AllBitsSet_1994) {

    XMP_OptionBits options = 0xFFFFFFFF; // All bits set

    WXMP_SetGlobalOptions_1(options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr); // Assuming no error message if successful

}



TEST_F(WXMPMetaTest_1994, SetGlobalOptions_InvalidOptions_1994) {

    XMP_OptionBits options = static_cast<XMP_OptionBits>(-1); // Invalid option scenario

    WXMP_SetGlobalOptions_1(options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr); // Expecting an error message for invalid options

}



TEST_F(WXMPMetaTest_1994, SetGlobalOptions_NullWResult_1994) {

    XMP_OptionBits options = 0x0001;

    WXMP_SetGlobalOptions_1(options, nullptr); // Passing null to wResult

    // No assertion here as the function should handle it gracefully.

}
