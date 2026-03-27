#include <gtest/gtest.h>

#include "exiv2/exif.hpp"



using namespace Exiv2;



class ExifdatumTest_748 : public ::testing::Test {

protected:

    std::unique_ptr<ExifKey> key;

    Exifdatum exifdatum;



    void SetUp() override {

        key = std::make_unique<ExifKey>(0x1C0, "Exif.Image");

        exifdatum = Exifdatum(*key, nullptr);

    }

};



TEST_F(ExifdatumTest_748, TagReturnsCorrectValue_748) {

    EXPECT_EQ(exifdatum.tag(), 0x1C0);

}



TEST_F(ExifdatumTest_748, TagReturnsDefaultValueWhenKeyIsNull_748) {

    Exifdatum exifdatumWithoutKey(nullptr, nullptr);

    EXPECT_EQ(exifdatumWithoutKey.tag(), 0xffff);

}



TEST_F(ExifdatumTest_748, KeyIsProperlyInitialized_748) {

    EXPECT_EQ(exifdatum.key()->tag(), 0x1C0);

    EXPECT_EQ(exifdatum.key()->groupName(), "Exif.Image");

}
