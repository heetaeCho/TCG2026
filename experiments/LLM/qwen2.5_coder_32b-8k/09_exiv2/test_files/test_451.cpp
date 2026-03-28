#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "nikonmn_int.hpp"

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"



namespace Exiv2 {

    namespace Internal {

        class Nikon1MakerNoteTest : public ::testing::Test {

        protected:

            Nikon1MakerNote nikonMakerNote;

            std::ostringstream os;

            Value value;

            testing::NiceMock<Exiv2::ExifData> mockExifData;



            void SetUp() override {

                // Initialize the value with a known size and data

                value.setDataArea(reinterpret_cast<const byte*>(LARGE_INT), 8);

            }

        };



        TEST_F(Nikon1MakerNoteTest_451, PrintBarValue_ExifDataNull_ReturnsUndefined_451) {

            EXPECT_EQ(nikonMakerNote.printBarValue(os, value, nullptr).str(), "undefined");

        }



        TEST_F(Nikon1MakerNoteTest_451, PrintBarValue_ValueCountLessThan9_ReturnsEmptyString_451) {

            EXPECT_CALL(mockExifData, count()).WillOnce(::testing::Return(8));

            EXPECT_EQ(nikonMakerNote.printBarValue(os, value, &mockExifData).str(), "");

        }



        TEST_F(Nikon1MakerNoteTest_451, PrintBarValue_ValueCountAtLeast9_BigEndian_ReturnsCorrectLong_451) {

            EXPECT_CALL(mockExifData, count()).WillOnce(::testing::Return(9));

            EXPECT_CALL(mockExifData, operator[]("Exif.MakerNote.ByteOrder")).WillRepeatedly(testing::ReturnRefOfCopy(

                Exiv2::Exifdatum("Exif.MakerNote.ByteOrder", "MM")));



            os.str("");

            nikonMakerNote.printBarValue(os, value, &mockExifData);

            EXPECT_EQ(os.str(), "16777215"); // 0xFFFFFF in big-endian

        }



        TEST_F(Nikon1MakerNoteTest_451, PrintBarValue_ValueCountAtLeast9_LittleEndian_ReturnsCorrectLong_451) {

            EXPECT_CALL(mockExifData, count()).WillOnce(::testing::Return(9));

            EXPECT_CALL(mockExifData, operator[]("Exif.MakerNote.ByteOrder")).WillRepeatedly(testing::ReturnRefOfCopy(

                Exiv2::Exifdatum("Exif.MakerNote.ByteOrder", "II")));



            os.str("");

            nikonMakerNote.printBarValue(os, value, &mockExifData);

            EXPECT_EQ(os.str(), "16711935"); // 0xFFFEFF in little-endian

        }

    } // namespace Internal

} // namespace Exiv2
