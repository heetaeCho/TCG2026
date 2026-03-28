#include <gtest/gtest.h>

#include "makernote_int.hpp"

#include "types.hpp"



namespace Exiv2 {

    namespace Internal {



        class SamsungMnHeaderTest_2193 : public ::testing::Test {

        protected:

            SamsungMnHeader header;

        };



        TEST_F(SamsungMnHeaderTest_2193, DefaultConstructorInitializesInvalidByteOrder_2193) {

            EXPECT_EQ(header.byteOrder(), invalidByteOrder);

        }



        TEST_F(SamsungMnHeaderTest_2193, SetByteOrderUpdatesByteOrder_2193) {

            header.setByteOrder(littleEndian);

            EXPECT_EQ(header.byteOrder(), littleEndian);



            header.setByteOrder(bigEndian);

            EXPECT_EQ(header.byteOrder(), bigEndian);

        }



        TEST_F(SamsungMnHeaderTest_2193, ReadWithNullDataReturnsFalse_2193) {

            bool result = header.read(nullptr, 0, invalidByteOrder);

            EXPECT_FALSE(result);

        }



        TEST_F(SamsungMnHeaderTest_2193, BaseOffsetReturnsZeroForAnyOffset_2193) {

            size_t offset = header.baseOffset(100);

            EXPECT_EQ(offset, 0);

        }



        TEST_F(SamsungMnHeaderTest_2193, SizeReturnsZeroByDefault_2193) {

            size_t size = header.size();

            EXPECT_EQ(size, 0);

        }



        // Assuming write and ifdOffset have no observable effects without additional context

    }

}
