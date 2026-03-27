#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"

#include "exiv2/types.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class ArrayDefTest_312 : public ::testing::Test {

protected:

    ArrayDef arrayDef;



    void SetUp() override {

        // Initialize necessary members if needed

        arrayDef.idx_ = 0;

        arrayDef.count_ = 5; // Example count value

    }

};



TEST_F(ArrayDefTest_312, SizeCalculation_NormalOperation_312) {

    uint16_t tag = 0x100; // Example tag value

    IfdId group = ifd0;   // Example IFD group



    TypeId typeId = toTypeId(tiffType_, tag, group);

    size_t expectedSize = arrayDef.count_ * TypeInfo::typeSize(typeId);



    EXPECT_EQ(arrayDef.size(tag, group), expectedSize);

}



TEST_F(ArrayDefTest_312, SizeCalculation_ZeroCount_312) {

    uint16_t tag = 0x100; // Example tag value

    IfdId group = ifd0;   // Example IFD group



    arrayDef.count_ = 0;

    EXPECT_EQ(arrayDef.size(tag, group), 0);

}



TEST_F(ArrayDefTest_312, SizeCalculation_MaxCount_312) {

    uint16_t tag = 0x100; // Example tag value

    IfdId group = ifd0;   // Example IFD group



    arrayDef.count_ = std::numeric_limits<size_t>::max();

    TypeId typeId = toTypeId(tiffType_, tag, group);

    size_t typeSize = TypeInfo::typeSize(typeId);



    if (typeSize != 0) {

        EXPECT_EQ(arrayDef.size(tag, group), std::numeric_limits<size_t>::max());

    } else {

        EXPECT_EQ(arrayDef.size(tag, group), 0);

    }

}



TEST_F(ArrayDefTest_312, SizeCalculation_TypeIdZero_312) {

    uint16_t tag = 0x0;   // Tag value that might result in TypeId::none

    IfdId group = ifd0;   // Example IFD group



    EXPECT_EQ(arrayDef.size(tag, group), 0);

}
