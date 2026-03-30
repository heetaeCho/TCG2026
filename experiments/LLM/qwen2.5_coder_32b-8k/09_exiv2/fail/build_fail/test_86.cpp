#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/jp2image.hpp"

#include "exiv2/basicio.hpp"



namespace Exiv2 {



using namespace testing;



class Jp2ImageTest_86 : public Test {

protected:

    std::unique_ptr<BasicIo> io_;

    std::unique_ptr<Jp2Image> jp2Image_;



    void SetUp() override {

        io_ = std::make_unique<MemIo>();

        jp2Image_ = std::make_unique<Jp2Image>(std::move(io_), false);

    }

};



TEST_F(Jp2ImageTest_86, PrintStructure_SuccessfulBasicPrint_86) {

    // Arrange

    constexpr char validJp2[] = {13, 0, 0, 0, 'j', 'P', ' ', ' \0'};

    io_->write(reinterpret_cast<const byte*>(validJp2), sizeof(validJp2));

    io_->seek(0);

    std::ostringstream oss;



    // Act

    jp2Image_->printStructure(oss, kpsBasic, 0);



    // Assert

    EXPECT_TRUE(!oss.str().empty());

}



TEST_F(Jp2ImageTest_86, PrintStructure_SuccessfulRecursivePrint_86) {

    // Arrange

    constexpr char validJp2[] = {13, 0, 0, 0, 'j', 'P', ' ', ' \0'};

    io_->write(reinterpret_cast<const byte*>(validJp2), sizeof(validJp2));

    io_->seek(0);

    std::ostringstream oss;



    // Act

    jp2Image_->printStructure(oss, kpsRecursive, 0);



    // Assert

    EXPECT_TRUE(!oss.str().empty());

}



TEST_F(Jp2ImageTest_86, PrintStructure_SuccessfulIccProfilePrint_86) {

    // Arrange

    constexpr char validJp2[] = {13, 0, 0, 0, 'j', 'P', ' ', ' \0'};

    io_->write(reinterpret_cast<const byte*>(validJp2), sizeof(validJp2));

    io_->seek(0);

    std::ostringstream oss;



    // Act

    jp2Image_->printStructure(oss, kpsIccProfile, 0);



    // Assert

    EXPECT_TRUE(!oss.str().empty());

}



TEST_F(Jp2ImageTest_86, PrintStructure_SuccessfulXmpPrint_86) {

    // Arrange

    constexpr char validJp2[] = {13, 0, 0, 0, 'j', 'P', ' ', ' \0'};

    io_->write(reinterpret_cast<const byte*>(validJp2), sizeof(validJp2));

    io_->seek(0);

    std::ostringstream oss;



    // Act

    jp2Image_->printStructure(oss, kpsXMP, 0);



    // Assert

    EXPECT_TRUE(!oss.str().empty());

}



TEST_F(Jp2ImageTest_86, PrintStructure_SuccessfulIptcErasePrint_86) {

    // Arrange

    constexpr char validJp2[] = {13, 0, 0, 0, 'j', 'P', ' ', ' \0'};

    io_->write(reinterpret_cast<const byte*>(validJp2), sizeof(validJp2));

    io_->seek(0);

    std::ostringstream oss;



    // Act

    jp2Image_->printStructure(oss, kpsIptcErase, 0);



    // Assert

    EXPECT_TRUE(!oss.str().empty());

}



TEST_F(Jp2ImageTest_86, PrintStructure_FailureOnInvalidDataSource_86) {

    // Arrange

    std::ostringstream oss;



    // Act & Assert

    EXPECT_THROW(jp2Image_->printStructure(oss, kpsBasic, 0), Error);

}



TEST_F(Jp2ImageTest_86, PrintStructure_FailureOnNonJpegFile_86) {

    // Arrange

    constexpr char invalidJp2[] = {13, 0, 0, 0, 'N', 'O', 'T', ' \0'};

    io_->write(reinterpret_cast<const byte*>(invalidJp2), sizeof(invalidJp2));

    io_->seek(0);

    std::ostringstream oss;



    // Act & Assert

    EXPECT_THROW(jp2Image_->printStructure(oss, kpsBasic, 0), Error);

}



TEST_F(Jp2ImageTest_86, PrintStructure_SuccessfulFileTypeBoxPrint_86) {

    // Arrange

    constexpr char validJp2[] = {32, 0, 0, 0, 'f', 't', 'y', 'p',

                                'j', 'p', '2', ' ', 12, 0, 0, 0,

                                'm', 's', 'f', 't'};

    io_->write(reinterpret_cast<const byte*>(validJp2), sizeof(validJp2));

    io_->seek(0);

    std::ostringstream oss;



    // Act

    jp2Image_->printStructure(oss, kpsBasic, 0);



    // Assert

    EXPECT_TRUE(!oss.str().empty());

}



TEST_F(Jp2ImageTest_86, PrintStructure_SuccessfulHeaderBoxPrint_86) {

    // Arrange

    constexpr char validJp2[] = {32, 0, 0, 0, 'j', 'P', ' ', ' ',

                                16, 0, 0, 0, 'h', 'l', 'h', 'l',

                                0x0d, 0x0a, 87, 13, 0, 0};

    io_->write(reinterpret_cast<const byte*>(validJp2), sizeof(validJp2));

    io_->seek(0);

    std::ostringstream oss;



    // Act

    jp2Image_->printStructure(oss, kpsBasic, 0);



    // Assert

    EXPECT_TRUE(!oss.str().empty());

}



TEST_F(Jp2ImageTest_86, PrintStructure_SuccessfulUuidBoxPrint_86) {

    // Arrange

    constexpr char validJp2[] = {32, 0, 0, 0, 'j', 'P', ' ', ' ',

                                36, 0, 0, 0, 'u', 'u', 'i', 'd',

                                190, 122, 207, 203, 151, 169, 66, 232,

                                156, 113, 153, 148, 145, 227, 175, 172};

    io_->write(reinterpret_cast<const byte*>(validJp2), sizeof(validJp2));

    io_->seek(0);

    std::ostringstream oss;



    // Act

    jp2Image_->printStructure(oss, kpsBasic, 0);



    // Assert

    EXPECT_TRUE(!oss.str().empty());

}



TEST_F(Jp2ImageTest_86, PrintStructure_SuccessfulColorSpecBoxPrint_86) {

    // Arrange

    constexpr char validJp2[] = {32, 0, 0, 0, 'j', 'P', ' ', ' ',

                                16, 0, 0, 0, 'c', 'o', 'l', 'r',

                                0x0d, 0x0a, 87, 13};

    io_->write(reinterpret_cast<const byte*>(validJp2), sizeof(validJp2));

    io_->seek(0);

    std::ostringstream oss;



    // Act

    jp2Image_->printStructure(oss, kpsBasic, 0);



    // Assert

    EXPECT_TRUE(!oss.str().empty());

}



TEST_F(Jp2ImageTest_86, PrintStructure_SuccessfulSignatureBoxPrint_86) {

    // Arrange

    constexpr char validJp2[] = {32, 0, 0, 0, 'j', 'P', ' ', ' ',

                                16, 0, 0, 0, 'i', 'h', 'd', 'r',

                                0x0d, 0x0a, 87, 13};

    io_->write(reinterpret_cast<const byte*>(validJp2), sizeof(validJp2));

    io_->seek(0);

    std::ostringstream oss;



    // Act

    jp2Image_->printStructure(oss, kpsBasic, 0);



    // Assert

    EXPECT_TRUE(!oss.str().empty());

}



}  // namespace Exiv2
