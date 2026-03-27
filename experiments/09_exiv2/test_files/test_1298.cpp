#include <gtest/gtest.h>

#include <gmock/gmock.h>



#include "./TestProjects/exiv2/src/xmp.cpp"



using namespace Exiv2;

using ::testing::HasSubstr;



class XmpdatumTest_1298 : public ::testing::Test {

protected:

    Xmpdatum xmpDatum;

};



TEST_F(XmpdatumTest_1298, CopyThrowsFunctionNotSupportedError_1298) {

    byte buffer[10];

    ByteOrder order = littleEndian;



    EXPECT_THROW({

        try {

            xmpDatum.copy(buffer, order);

        } catch (const Error& e) {

            EXPECT_EQ(e.code(), ErrorCode::kerFunctionNotSupported);

            EXPECT_THAT(e.what(), HasSubstr("copy"));

            throw;

        }

    }, Error);

}
