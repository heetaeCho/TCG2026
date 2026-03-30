#include <gtest/gtest.h>

#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"



namespace Exiv2 {

    namespace Internal {



        class TiffImageEntryTest : public ::testing::Test {

        protected:

            TiffImageEntry tiff_image_entry_;

        };



        TEST_F(TiffImageEntryTest_391, DoSize_ReturnsCorrectValueWhenStripsIsEmpty_391) {

            EXPECT_EQ(tiff_image_entry_.doSize(), 0);

        }



        TEST_F(TiffImageEntryTest_391, DoSize_ReturnsCorrectValueForOneStrip_391) {

            tiff_image_entry_.setStrips(nullptr, nullptr, 4, 0);

            EXPECT_EQ(tiff_image_entry_.doSize(), 4);

        }



        TEST_F(TiffImageEntryTest_391, DoSize_ReturnsCorrectValueForMultipleStrips_391) {

            const size_t strip_count = 5;

            tiff_image_entry_.setStrips(nullptr, nullptr, strip_count * 4, 0);

            EXPECT_EQ(tiff_image_entry_.doSize(), strip_count * 4);

        }



    } // namespace Internal

} // namespace Exiv2
