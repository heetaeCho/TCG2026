#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "exiv2/tags.hpp"



namespace Exiv2 {

    class ExifdatumTest_2164 : public ::testing::Test {

    protected:

        void SetUp() override {

            ExifKey key("Exif.Image.Artist");

            Value* value = Value::create(string);

            exifdatum1 = std::make_unique<Exifdatum>(key, value);

            exifdatum2 = std::make_unique<Exifdatum>(*exifdatum1);

        }



        std::unique_ptr<Exifdatum> exifdatum1;

        std::unique_ptr<Exifdatum> exifdatum2;

    };



    TEST_F(ExifdatumTest_2164, CopyConstructorClonesKeyAndValue_2164) {

        EXPECT_EQ(exifdatum1->key(), exifdatum2->key());

        EXPECT_NE(&exifdatum1->value(), &exifdatum2->value());

    }



    TEST_F(ExifdatumTest_2164, SetValueWithStringUpdatesValue_2164) {

        std::string newValue = "New Artist";

        *exifdatum1 = newValue;

        EXPECT_EQ(exifdatum1->toString(), newValue);

    }



    TEST_F(ExifdatumTest_2164, SetValueWithIntUpdatesValue_2164) {

        uint32_t newValue = 12345;

        *exifdatum1 = newValue;

        EXPECT_EQ(exifdatum1->toUint32(), newValue);

    }



    TEST_F(ExifdatumTest_2164, SetDataAreaUpdatesValue_2164) {

        byte data[] = {0x41, 0x72, 0x74, 0x69, 0x73, 0x74}; // ASCII for "Artist"

        size_t len = sizeof(data);

        exifdatum1->setDataArea(data, len);

        EXPECT_EQ(exifdatum1->toString(), "Artist");

    }



    TEST_F(ExifdatumTest_2164, KeyReturnsCorrectKey_2164) {

        EXPECT_EQ(exifdatum1->key(), "Exif.Image.Artist");

    }



    TEST_F(ExifdatumTest_2164, FamilyNameReturnsCorrectFamilyName_2164) {

        EXPECT_EQ(exifdatum1->familyName(), "Exif");

    }



    TEST_F(ExifdatumTest_2164, GroupNameReturnsCorrectGroupName_2164) {

        EXPECT_EQ(exifdatum1->groupName(), "Image");

    }



    TEST_F(ExifdatumTest_2164, TagNameReturnsCorrectTagName_2164) {

        EXPECT_EQ(exifdatum1->tagName(), "Artist");

    }

}
