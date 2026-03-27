#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include <sstream>



using namespace Exiv2;



class ExifdatumTest_728 : public ::testing::Test {

protected:

    std::unique_ptr<ExifKey> key_;

    std::unique_ptr<Value> value_;

    Exifdatum exifdatum_;



    void SetUp() override {

        key_ = std::make_unique<ExifKey>("Exif.Image.Artist");

        value_ = Value::create(string);

        exifdatum_ = Exifdatum(*key_, value_.get());

    }

};



TEST_F(ExifdatumTest_728, WriteWithEmptyValue_728) {

    std::ostringstream os;

    const ExifData* pMetadata = nullptr;

    exifdatum_.setValue("");

    exifdatum_.write(os, pMetadata);

    EXPECT_EQ(os.str(), "");

}



TEST_F(ExifdatumTest_728, WriteWithNonEmptyValue_728) {

    std::ostringstream os;

    const ExifData* pMetadata = nullptr;

    exifdatum_.setValue("John Doe");

    exifdatum_.write(os, pMetadata);

    EXPECT_EQ(os.str(), "John Doe");

}



TEST_F(ExifdatumTest_728, WriteWithCommentType_728) {

    std::ostringstream os;

    const ExifData* pMetadata = nullptr;

    value_->setValue("This is a comment", 19);

    exifdatum_.setValue(value_.get());

    exifdatum_.typeId() = comment;

    exifdatum_.write(os, pMetadata);

    EXPECT_EQ(os.str(), "This is a comment");

}



TEST_F(ExifdatumTest_728, WriteWithOutOfRangeValue_728) {

    std::ostringstream os;

    const ExifData* pMetadata = nullptr;

    // Assuming value_->setValue can be set in a way to cause out_of_range exception

    try {

        exifdatum_.write(os, pMetadata);

    } catch (...) {

        FAIL() << "Unexpected exception caught";

    }

    EXPECT_EQ(os.str(), "Bad value");

}
