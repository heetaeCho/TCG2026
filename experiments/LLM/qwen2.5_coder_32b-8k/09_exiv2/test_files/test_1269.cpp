#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/properties.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;



class XmpKeyImplTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup any necessary preconditions for the tests

    }



    void TearDown() override {

        // Cleanup after each test

    }

};



TEST_F(XmpKeyImplTest_NormalOperation_1269, DecomposeValidKey_1269) {

    XmpKey::Impl impl;

    std::string key = "Iptc.Application2.Caption";

    EXPECT_NO_THROW(impl.decomposeKey(key));

}



TEST_F(XmpKeyImplTest_BoundaryConditions_1269, DecomposeMinimalValidKey_1269) {

    XmpKey::Impl impl;

    std::string key = "Iptc.2.Property";

    EXPECT_NO_THROW(impl.decomposeKey(key));

}



TEST_F(XmpKeyImplTest_ErrorCases_1269, DecomposeEmptyKey_1269) {

    XmpKey::Impl impl;

    std::string key = "";

    EXPECT_THROW(impl.decomposeKey(key), Error);

}



TEST_F(XmpKeyImplTest_ErrorCases_1269, DecomposeInvalidPrefixKey_1269) {

    XmpKey::Impl impl;

    std::string key = "Invalid.Application2.Caption";

    EXPECT_THROW(impl.decomposeKey(key), Error);

}



TEST_F(XmpKeyImplTest_ErrorCases_1269, DecomposeMissingPropertyKey_1269) {

    XmpKey::Impl impl;

    std::string key = "Iptc.Application2.";

    EXPECT_THROW(impl.decomposeKey(key), Error);

}



TEST_F(XmpKeyImplTest_ErrorCases_1269, DecomposeNoPrefixSeparatorKey_1269) {

    XmpKey::Impl impl;

    std::string key = "IptcApplication2.Caption";

    EXPECT_THROW(impl.decomposeKey(key), Error);

}



TEST_F(XmpKeyImplTest_ErrorCases_1269, DecomposeMissingSecondDotKey_1269) {

    XmpKey::Impl impl;

    std::string key = "Iptc.Application2";

    EXPECT_THROW(impl.decomposeKey(key), Error);

}



TEST_F(XmpKeyImplTest_ErrorCases_1269, DecomposeEmptyPrefixKey_1269) {

    XmpKey::Impl impl;

    std::string key = "Iptc..Caption";

    EXPECT_THROW(impl.decomposeKey(key), Error);

}



TEST_F(XmpKeyImplTest_ErrorCases_1269, DecomposeUnknownNamespacePrefix_1269) {

    XmpKey::Impl impl;

    std::string key = "Iptc.Unknown.Caption";

    EXPECT_THROW(impl.decomposeKey(key), Error);

}
