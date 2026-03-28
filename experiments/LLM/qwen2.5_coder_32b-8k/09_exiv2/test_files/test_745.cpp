#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"



namespace Exiv2 {

    class MockExifKey : public ExifKey {

    public:

        MOCK_CONST_METHOD0(tagName, std::string());

        MOCK_CONST_METHOD0(key, std::string());

    };

}



using namespace ::testing;



class ExifdatumTest_745 : public Test {

protected:

    std::unique_ptr<Exiv2::MockExifKey> mock_key_;

    std::unique_ptr<Exiv2::Value> value_;

    Exiv2::Exifdatum exif_datum_;



    void SetUp() override {

        mock_key_ = std::make_unique<Exiv2::MockExifKey>();

        exif_datum_ = Exiv2::Exifdatum(*mock_key_, value_.get());

    }

};



TEST_F(ExifdatumTest_745, TagName_ReturnsCorrectValue_745) {

    EXPECT_CALL(*mock_key_, tagName()).WillOnce(Return("SampleTagName"));

    EXPECT_EQ(exif_datum_.tagName(), "SampleTagName");

}



TEST_F(ExifdatumTest_745, TagName_ReturnsEmptyStringWhenKeyIsNull_745) {

    exif_datum_ = Exiv2::Exifdatum(nullptr, value_.get());

    EXPECT_EQ(exif_datum_.tagName(), "");

}
