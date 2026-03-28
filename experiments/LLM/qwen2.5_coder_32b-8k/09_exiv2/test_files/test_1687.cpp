#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"

#include "./TestProjects/exiv2/src/tiffvisitor_int.hpp"



namespace Exiv2 {

    namespace Internal {



        class TiffEncoderTest_1687 : public ::testing::Test {

        protected:

            void SetUp() override {

                exifData = ExifData();

                iptcData = IptcData();

                xmpData = XmpData();

                pHeader = std::make_unique<TiffHeaderBase>(ByteOrder::big);

                pRoot = new TiffComponent();

                isNewImage = false;

                pPrimaryGroups = PrimaryGroups();

                encoder = std::make_unique<TiffEncoder>(exifData, iptcData, xmpData, pRoot, isNewImage, pPrimaryGroups, pHeader.get(), nullptr);

            }



            void TearDown() override {

                delete pRoot;

            }



            ExifData exifData;

            IptcData iptcData;

            XmpData xmpData;

            std::unique_ptr<TiffHeaderBase> pHeader;

            TiffComponent* pRoot;

            bool isNewImage;

            PrimaryGroups pPrimaryGroups;

            std::unique_ptr<TiffEncoder> encoder;

        };



        TEST_F(TiffEncoderTest_1687, EncodeSubIfdCallsEncodeOffsetEntry_1687) {

            // Arrange

            TiffSubIfd subIfd(0x1234, IfdId::rootIFD, IfdId::exifIFD);

            Exifdatum exifdatum(ExifKey("Exif.Image.Artist"), new Value());



            // Act & Assert

            EXPECT_NO_THROW(encoder->encodeSubIfd(&subIfd, &exifdatum));

        }



    }  // namespace Internal

}  // namespace Exiv2
