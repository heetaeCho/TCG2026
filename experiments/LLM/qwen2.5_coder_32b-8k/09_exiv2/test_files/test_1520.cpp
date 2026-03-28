#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "makernote_int.cpp"



namespace Exiv2 {

    namespace Internal {



        class Nikon3Mn2Test : public ::testing::Test {

        protected:

            void SetUp() override {

                // No setup required for this test

            }



            void TearDown() override {

                // No teardown required for this test

            }

        };



        TEST_F(Nikon3Mn2Test_1520, CreateInstanceWithValidParameters_1520) {

            uint16_t tag = 0x0001;

            IfdId group = ifdExif;

            IfdId mnGroup = ifdExif;



            auto makernote = newNikon3Mn2(tag, group, mnGroup);



            EXPECT_NE(makernote, nullptr);

        }



        TEST_F(Nikon3Mn2Test_1520, CreateInstanceWithZeroTag_1520) {

            uint16_t tag = 0x0000;

            IfdId group = ifdExif;

            IfdId mnGroup = ifdExif;



            auto makernote = newNikon3Mn2(tag, group, mnGroup);



            EXPECT_NE(makernote, nullptr);

        }



        TEST_F(Nikon3Mn2Test_1520, CreateInstanceWithMaxTagValue_1520) {

            uint16_t tag = 0xFFFF;

            IfdId group = ifdExif;

            IfdId mnGroup = ifdExif;



            auto makernote = newNikon3Mn2(tag, group, mnGroup);



            EXPECT_NE(makernote, nullptr);

        }



    } // namespace Internal

} // namespace Exiv2
