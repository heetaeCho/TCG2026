#include <gtest/gtest.h>

#include "tiffcomposite_int.hpp"

#include "error.hpp"



namespace Exiv2 {

    namespace Internal {



        class TiffMnEntryTest_360 : public ::testing::Test {

        protected:

            void SetUp() override {

                mnGroup = IfdId::ifdExif;

                tag = 0x927C; // Example tag for makernote

                tiffType = ttUnsignedByte; // Default type to avoid warning messages

                mnEntry = std::make_unique<TiffMnEntry>(tag, IfdId::ifdExif, mnGroup);

            }



            void TearDown() override {

                mnEntry.reset();

            }



            IfdId mnGroup;

            uint16_t tag;

            TiffType tiffType;

            std::unique_ptr<TiffMnEntry> mnEntry;

        };



        TEST_F(TiffMnEntryTest_360, DoCount_NoMakernote_360) {

            EXPECT_EQ(mnEntry->doCount(), 0);

        }



        TEST_F(TiffMnEntryTest_360, DoCount_WithMakernote_360) {

            mnEntry->mn_ = std::make_unique<TiffIfdMakernote>();

            size_t expectedSize = 1; // Assuming TiffIfdMakernote has a default size of 1 for testing

            mnEntry->mn_->resize(expectedSize);

            EXPECT_EQ(mnEntry->doCount(), expectedSize);

        }



        TEST_F(TiffMnEntryTest_360, DoCount_IncorrectType_WarningLogged_360) {

            tiffType = ttUnsignedLong; // Incorrect type to trigger warning

            mnEntry = std::make_unique<TiffMnEntry>(tag, IfdId::ifdExif, mnGroup);

            mnEntry->setTiffType(tiffType);



            testing::internal::CaptureStderr();

            EXPECT_EQ(mnEntry->doCount(), 0);

            std::string output = testing::internal::GetCapturedStderr();



            EXPECT_TRUE(output.find("Makernote entry") != std::string::npos);

        }



        TEST_F(TiffMnEntryTest_360, DoCount_TiffTypeUndefined_NoWarning_360) {

            tiffType = ttUndefined;

            mnEntry = std::make_unique<TiffMnEntry>(tag, IfdId::ifdExif, mnGroup);

            mnEntry->setTiffType(tiffType);



            testing::internal::CaptureStderr();

            EXPECT_EQ(mnEntry->doCount(), 0);

            std::string output = testing::internal::GetCapturedStderr();



            EXPECT_TRUE(output.empty());

        }



    } // namespace Internal

} // namespace Exiv2
