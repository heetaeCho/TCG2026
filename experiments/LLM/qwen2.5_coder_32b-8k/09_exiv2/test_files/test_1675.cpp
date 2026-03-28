#include <gtest/gtest.h>

#include "tiffvisitor_int.hpp"

#include "exif.hpp"



namespace Exiv2 {

    namespace Internal {



        class TiffEncoderTest : public ::testing::Test {

        protected:

            ExifData exifData_;

            IptcData iptcData_;

            XmpData xmpData_;

            bool isNewImage_ = false;

            PrimaryGroups pPrimaryGroups_{};

            const TiffHeaderBase* pHeader_ = nullptr; // Assuming default constructor is valid or mock this if necessary

            FindEncoderFct findEncoderFct_{}; // Assuming default constructor is valid or mock this if necessary



            std::unique_ptr<MnHeader> createMnHeader() {

                return std::make_unique<MnHeader>();

            }



            TiffIfdMakernote* createTiffIfdMakernote(ByteOrder byteOrder) {

                auto pHeader = createMnHeader();

                auto* tiffIfdMakernote = new TiffIfdMakernote(0x1234, ifdExif, ifdMakernoteCanon, std::move(pHeader), false);

                tiffIfdMakernote->setByteOrder(byteOrder);

                return tiffIfdMakernote;

            }



            TiffEncoder* createTiffEncoder(bool del = true) {

                auto* encoder = new TiffEncoder(exifData_, iptcData_, xmpData_, nullptr, isNewImage_, pPrimaryGroups_, pHeader_, findEncoderFct_);

                encoder->del_ = del;

                return encoder;

            }

        };



        TEST_F(TiffEncoderTest_1675, NormalOperationSameByteOrder_1675) {

            auto* tiffIfdMakernote = createTiffIfdMakernote(bigEndian);

            exifData_.add(ExifKey("Exif.MakerNote.ByteOrder"), new StringValue("bigEndian"));

            TiffEncoder encoder(exifData_, iptcData_, xmpData_, nullptr, isNewImage_, pPrimaryGroups_, pHeader_, findEncoderFct_);

            

            EXPECT_EQ(tiffIfdMakernote->byteOrder(), bigEndian);

            encoder.visitIfdMakernote(tiffIfdMakernote);

            EXPECT_EQ(tiffIfdMakernote->byteOrder(), bigEndian);



            delete tiffIfdMakernote;

        }



        TEST_F(TiffEncoderTest_1675, NormalOperationDifferentByteOrder_1675) {

            auto* tiffIfdMakernote = createTiffIfdMakernote(bigEndian);

            exifData_.add(ExifKey("Exif.MakerNote.ByteOrder"), new StringValue("littleEndian"));

            TiffEncoder encoder(exifData_, iptcData_, xmpData_, nullptr, isNewImage_, pPrimaryGroups_, pHeader_, findEncoderFct_);

            

            EXPECT_EQ(tiffIfdMakernote->byteOrder(), bigEndian);

            encoder.visitIfdMakernote(tiffIfdMakernote);

            EXPECT_EQ(tiffIfdMakernote->byteOrder(), littleEndian);



            delete tiffIfdMakernote;

        }



        TEST_F(TiffEncoderTest_1675, BoundaryConditionInvalidByteOrder_1675) {

            auto* tiffIfdMakernote = createTiffIfdMakernote(bigEndian);

            exifData_.add(ExifKey("Exif.MakerNote.ByteOrder"), new StringValue("invalid"));

            TiffEncoder encoder(exifData_, iptcData_, xmpData_, nullptr, isNewImage_, pPrimaryGroups_, pHeader_, findEncoderFct_);

            

            EXPECT_EQ(tiffIfdMakernote->byteOrder(), bigEndian);

            encoder.visitIfdMakernote(tiffIfdMakernote);

            EXPECT_EQ(tiffIfdMakernote->byteOrder(), bigEndian);



            delete tiffIfdMakernote;

        }



        TEST_F(TiffEncoderTest_1675, ExceptionalCaseKeyNotFound_1675) {

            auto* tiffIfdMakernote = createTiffIfdMakernote(bigEndian);

            TiffEncoder encoder(exifData_, iptcData_, xmpData_, nullptr, isNewImage_, pPrimaryGroups_, pHeader_, findEncoderFct_);

            

            EXPECT_EQ(tiffIfdMakernote->byteOrder(), bigEndian);

            encoder.visitIfdMakernote(tiffIfdMakernote);

            EXPECT_EQ(tiffIfdMakernote->byteOrder(), bigEndian);



            delete tiffIfdMakernote;

        }



        TEST_F(TiffEncoderTest_1675, VerificationOfExternalInteractions_1675) {

            auto* tiffIfdMakernote = createTiffIfdMakernote(bigEndian);

            exifData_.add(ExifKey("Exif.MakerNote.ByteOrder"), new StringValue("littleEndian"));

            exifData_.add(ExifKey("Exif.MakerNote.Offset"), new LongValue(0x1234));

            

            EXPECT_EQ(exifData_.count(), 2);

            TiffEncoder encoder(exifData_, iptcData_, xmpData_, nullptr, isNewImage_, pPrimaryGroups_, pHeader_, findEncoderFct_);

            encoder.visitIfdMakernote(tiffIfdMakernote);

            EXPECT_EQ(exifData_.count(), 0);



            delete tiffIfdMakernote;

        }



    } // namespace Internal

} // namespace Exiv2
