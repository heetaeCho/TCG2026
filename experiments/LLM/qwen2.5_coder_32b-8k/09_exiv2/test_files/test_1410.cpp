#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "./TestProjects/exiv2/src/tags_int.cpp"



namespace Exiv2 {

    namespace Internal {

        class TagsIntTest : public ::testing::Test {

        protected:

            std::ostream os;

            Value value;

            ExifData metadata;



            TagsIntTest() : value(TypeId::string) {}

        };

    }

}



using namespace Exiv2::Internal;



TEST_F(TagsIntTest_1410, PrintTagWithValidValue_1410) {

    std::stringstream ss;

    Value value(TypeId::string);

    value.setDataArea(reinterpret_cast<const byte*>("Directly photographed"), 19);

    metadata.add(ExifKey("Exif.Image.SceneType"), &value);



    print0xa301(ss, value, &metadata);



    EXPECT_EQ(ss.str(), "Directly photographed");

}



TEST_F(TagsIntTest_1410, PrintTagWithEmptyValue_1410) {

    std::stringstream ss;

    Value value(TypeId::string);

    metadata.add(ExifKey("Exif.Image.SceneType"), &value);



    print0xa301(ss, value, &metadata);



    EXPECT_EQ(ss.str(), "");

}



TEST_F(TagsIntTest_1410, PrintTagWithNullMetadata_1410) {

    std::stringstream ss;

    Value value(TypeId::string);

    value.setDataArea(reinterpret_cast<const byte*>("Directly photographed"), 19);



    print0xa301(ss, value, nullptr);



    EXPECT_EQ(ss.str(), "Directly photographed");

}



TEST_F(TagsIntTest_1410, PrintTagWithDifferentValue_1410) {

    std::stringstream ss;

    Value value(TypeId::string);

    value.setDataArea(reinterpret_cast<const byte*>("Not directly photographed"), 25);

    metadata.add(ExifKey("Exif.Image.SceneType"), &value);



    print0xa301(ss, value, &metadata);



    EXPECT_EQ(ss.str(), "Directly photographed");

}
