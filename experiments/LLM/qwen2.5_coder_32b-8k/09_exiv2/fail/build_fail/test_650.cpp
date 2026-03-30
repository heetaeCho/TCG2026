#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "datasets.hpp"

#include "error.hpp"



namespace Exiv2 {



class IptcKeyTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if necessary, but since we treat the implementation as a black box,

        // no specific setup is required here.

    }



    void TearDown() override {

        // Teardown if necessary

    }

};



TEST_F(IptcKeyTest_650, DecomposeKeyValidInput_650) {

    IptcKey key("Iptc.Application2.Caption");

    EXPECT_NO_THROW(key.decomposeKey());

    EXPECT_EQ(key.recordName(), "Application2");

    EXPECT_EQ(key.tagName(), "Caption");

}



TEST_F(IptcKeyTest_650, DecomposeKeyInvalidFamilyName_650) {

    IptcKey key("Xmp.Application2.Caption");

    EXPECT_THROW(key.decomposeKey(), Exiv2::Error);

    try {

        key.decomposeKey();

    } catch (const Exiv2::Error& e) {

        EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerInvalidKey);

    }

}



TEST_F(IptcKeyTest_650, DecomposeKeyMissingDots_650) {

    IptcKey key("IptcApplication2Caption");

    EXPECT_THROW(key.decomposeKey(), Exiv2::Error);

    try {

        key.decomposeKey();

    } catch (const Exiv2::Error& e) {

        EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerInvalidKey);

    }

}



TEST_F(IptcKeyTest_650, DecomposeKeyTooManyDots_650) {

    IptcKey key("Iptc.Application2.Caption.Extra");

    EXPECT_THROW(key.decomposeKey(), Exiv2::Error);

    try {

        key.decomposeKey();

    } catch (const Exiv2::Error& e) {

        EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerInvalidKey);

    }

}



TEST_F(IptcKeyTest_650, DecomposeKeyEmptyString_650) {

    IptcKey key("");

    EXPECT_THROW(key.decomposeKey(), Exiv2::Error);

    try {

        key.decomposeKey();

    } catch (const Exiv2::Error& e) {

        EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerInvalidKey);

    }

}



} // namespace Exiv2
