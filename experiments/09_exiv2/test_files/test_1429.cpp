#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "makernote_int.hpp"



using namespace Exiv2::Internal;



class TiffMnRegistryTest_1429 : public ::testing::Test {

protected:

    const char* make_str = "Canon";

    IfdId mnGroup = 0x8765;

    NewMnFct newMnFunc = nullptr;

    NewMnFct2 newMnFunc2 = nullptr;



    TiffMnRegistry registry;



    void SetUp() override {

        registry.make_ = make_str;

        registry.mnGroup_ = mnGroup;

        registry.newMnFct_ = newMnFunc;

        registry.newMnFct2_ = newMnFunc2;

    }

};



TEST_F(TiffMnRegistryTest_1429, OperatorEquals_StringView_Match_1429) {

    EXPECT_TRUE(registry == std::string_view("Canon"));

}



TEST_F(TiffMnRegistryTest_1429, OperatorEquals_StringView_NoMatch_1429) {

    EXPECT_FALSE(registry == std::string_view("Nikon"));

}



TEST_F(TiffMnRegistryTest_1429, OperatorEquals_StringView_EmptyKey_1429) {

    EXPECT_FALSE(registry == std::string_view(""));

}



TEST_F(TiffMnRegistryTest_1429, OperatorEquals_StringView_StartsWithDash_1429) {

    EXPECT_FALSE(registry == std::string_view("-Canon"));

}



TEST_F(TiffMnRegistryTest_1429, OperatorEquals_StringView_CaseSensitive_1429) {

    EXPECT_FALSE(registry == std::string_view("canon"));

}
