#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/types.hpp"



namespace Exiv2 {

    namespace Internal {

        static auto getModel(const ExifData* metadata, std::string& val);

    }

}



class SonyModelTest_1584 : public ::testing::Test {

protected:

    void SetUp() override {

        metadata = new Exiv2::ExifData();

    }



    void TearDown() override {

        delete metadata;

    }



    Exiv2::ExifData* metadata;

};



TEST_F(SonyModelTest_1584, GetModel_ExifImageModelFoundAsciiString_1584) {

    std::string modelValue = "Sony Model A";

    Exiv2::Exifdatum exifdatum(Exiv2::ExifKey("Exif.Image.Model"), new Exiv2::Value);

    exifdatum.setValue(modelValue);

    metadata->add(exifdatum);



    std::string result;

    bool success = Exiv2::Internal::getModel(metadata, result);



    EXPECT_TRUE(success);

    EXPECT_EQ(result, modelValue);

}



TEST_F(SonyModelTest_1584, GetModel_ExifSony1SonyModelIDFoundUnsignedShort_1584) {

    std::string modelValue = "100";

    Exiv2::Exifdatum exifdatum(Exiv2::ExifKey("Exif.Sony1.SonyModelID"), new Exiv2::Value);

    exifdatum.setValue(modelValue);

    metadata->add(exifdatum);



    std::string result;

    bool success = Exiv2::Internal::getModel(metadata, result);



    EXPECT_TRUE(success);

    EXPECT_EQ(result, modelValue);

}



TEST_F(SonyModelTest_1584, GetModel_ExifSony2SonyModelIDFoundUnsignedShort_1584) {

    std::string modelValue = "200";

    Exiv2::Exifdatum exifdatum(Exiv2::ExifKey("Exif.Sony2.SonyModelID"), new Exiv2::Value);

    exifdatum.setValue(modelValue);

    metadata->add(exifdatum);



    std::string result;

    bool success = Exiv2::Internal::getModel(metadata, result);



    EXPECT_TRUE(success);

    EXPECT_EQ(result, modelValue);

}



TEST_F(SonyModelTest_1584, GetModel_ModelNotFound_1584) {

    std::string result;

    bool success = Exiv2::Internal::getModel(metadata, result);



    EXPECT_FALSE(success);

    EXPECT_EQ(result, "");

}



TEST_F(SonyModelTest_1584, GetModel_ExifImageModelFoundButNotAsciiString_1584) {

    std::string modelValue = "Sony Model A";

    Exiv2::Exifdatum exifdatum(Exiv2::ExifKey("Exif.Image.Model"), new Exiv2::Value);

    exifdatum.setValue(modelValue);

    exifdatum.typeId() = Exiv2::unsignedShort; // Simulate wrong type

    metadata->add(exifdatum);



    std::string result;

    bool success = Exiv2::Internal::getModel(metadata, result);



    EXPECT_FALSE(success);

    EXPECT_EQ(result, "");

}



TEST_F(SonyModelTest_1584, GetModel_ExifSony1SonyModelIDFoundButContainsSpace_1584) {

    std::string modelValue = "Model 100";

    Exiv2::Exifdatum exifdatum(Exiv2::ExifKey("Exif.Sony1.SonyModelID"), new Exiv2::Value);

    exifdatum.setValue(modelValue);

    metadata->add(exifdatum);



    std::string result;

    bool success = Exiv2::Internal::getModel(metadata, result);



    EXPECT_FALSE(success);

    EXPECT_EQ(result, "");

}



TEST_F(SonyModelTest_1584, GetModel_ExifSony2SonyModelIDFoundButContainsSpace_1584) {

    std::string modelValue = "Model 200";

    Exiv2::Exifdatum exifdatum(Exiv2::ExifKey("Exif.Sony2.SonyModelID"), new Exiv2::Value);

    exifdatum.setValue(modelValue);

    metadata->add(exifdatum);



    std::string result;

    bool success = Exiv2::Internal::getModel(metadata, result);



    EXPECT_FALSE(success);

    EXPECT_EQ(result, "");

}



TEST_F(SonyModelTest_1584, GetModel_MultipleModelsFound_1584) {

    std::string modelValue1 = "Sony Model A";

    std::string modelValue2 = "100";



    Exiv2::Exifdatum exifdatum1(Exiv2::ExifKey("Exif.Image.Model"), new Exiv2::Value);

    exifdatum1.setValue(modelValue1);

    metadata->add(exifdatum1);



    Exiv2::Exifdatum exifdatum2(Exiv2::ExifKey("Exif.Sony1.SonyModelID"), new Exiv2::Value);

    exifdatum2.setValue(modelValue2);

    metadata->add(exifdatum2);



    std::string result;

    bool success = Exiv2::Internal::getModel(metadata, result);



    EXPECT_TRUE(success);

    EXPECT_EQ(result, modelValue1); // First found should be returned

}



TEST_F(SonyModelTest_1584, GetModel_ExifImageModelFoundButEmptyString_1584) {

    std::string modelValue = "";

    Exiv2::Exifdatum exifdatum(Exiv2::ExifKey("Exif.Image.Model"), new Exiv2::Value);

    exifdatum.setValue(modelValue);

    metadata->add(exifdatum);



    std::string result;

    bool success = Exiv2::Internal::getModel(metadata, result);



    EXPECT_FALSE(success);

    EXPECT_EQ(result, "");

}
