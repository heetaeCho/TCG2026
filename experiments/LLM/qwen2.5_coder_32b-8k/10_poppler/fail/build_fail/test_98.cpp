#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Object.h"

#include "TestProjects/poppler/poppler/GooString.h"



class ObjectTest_98 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(ObjectTest_98, GetHexString_ReturnsNullForNonHexStringType_98) {

    Object obj(objInt);

    EXPECT_EQ(obj.getHexString(), nullptr);

}



TEST_F(ObjectTest_98, GetHexString_ReturnsValidPointerForHexStringType_98) {

    std::unique_ptr<GooString> hexString = std::make_unique<GooString>("1A2B3C");

    Object obj(std::move(hexString));

    EXPECT_NE(obj.getHexString(), nullptr);

}



TEST_F(ObjectTest_98, GetHexString_ReturnsCorrectValueForHexStringType_98) {

    std::unique_ptr<GooString> hexString = std::make_unique<GooString>("1A2B3C");

    Object obj(std::move(hexString));

    EXPECT_STREQ(obj.getHexString()->getCString(), "1A2B3C");

}



TEST_F(ObjectTest_98, GetHexString_ReturnsSamePointerForMultipleCalls_98) {

    std::unique_ptr<GooString> hexString = std::make_unique<GooString>("1A2B3C");

    Object obj(std::move(hexString));

    const GooString* ptr1 = obj.getHexString();

    const GooString* ptr2 = obj.getHexString();

    EXPECT_EQ(ptr1, ptr2);

}
