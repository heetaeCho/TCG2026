#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"

#include "exiv2/exif.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class PrintBitmaskTest : public ::testing::Test {

protected:

    std::ostringstream os;

    MockValue mockValue;

    const ExifData* metadata = nullptr; // Assuming no interaction with metadata for these tests



    void SetUp() override {

        ON_CALL(mockValue, count()).WillByDefault(::testing::Return(1));

        ON_CALL(mockValue, toInt64(::testing::AnyOf(0u))).WillByDefault(::testing::Return(0));

        ON_CALL(mockValue, typeId()).WillByDefault(::testing::Return(unsignedShort));

    }

};



TEST_F(PrintBitmaskTest_1373, EmptyBitmaskForUnsignedShort_1373) {

    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Return(1));

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(0));

    printBitmask(os, mockValue, metadata);

    EXPECT_EQ(os.str(), "(none)");

}



TEST_F(PrintBitmaskTest_1373, SingleSetBitForUnsignedShort_1373) {

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(1));

    printBitmask(os, mockValue, metadata);

    EXPECT_EQ(os.str(), "0");

}



TEST_F(PrintBitmaskTest_1373, MultipleSetBitsForUnsignedShort_1373) {

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(5)); // Binary 101

    printBitmask(os, mockValue, metadata);

    EXPECT_EQ(os.str(), "0,2");

}



TEST_F(PrintBitmaskTest_1373, AllBitsSetForUnsignedShort_1373) {

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(0xFFFF)); // All bits set

    printBitmask(os, mockValue, metadata);

    EXPECT_EQ(os.str(), "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15");

}



TEST_F(PrintBitmaskTest_1373, EmptyBitmaskForSignedShort_1373) {

    EXPECT_CALL(mockValue, typeId()).WillOnce(::testing::Return(signedShort));

    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Return(1));

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(0));

    printBitmask(os, mockValue, metadata);

    EXPECT_EQ(os.str(), "(none)");

}



TEST_F(PrintBitmaskTest_1373, SingleSetBitForSignedShort_1373) {

    EXPECT_CALL(mockValue, typeId()).WillOnce(::testing::Return(signedShort));

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(1));

    printBitmask(os, mockValue, metadata);

    EXPECT_EQ(os.str(), "0");

}



TEST_F(PrintBitmaskTest_1373, MultipleSetBitsForSignedShort_1373) {

    EXPECT_CALL(mockValue, typeId()).WillOnce(::testing::Return(signedShort));

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(5)); // Binary 101

    printBitmask(os, mockValue, metadata);

    EXPECT_EQ(os.str(), "0,2");

}



TEST_F(PrintBitmaskTest_1373, AllBitsSetForSignedShort_1373) {

    EXPECT_CALL(mockValue, typeId()).WillOnce(::testing::Return(signedShort));

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(0xFFFF)); // All bits set

    printBitmask(os, mockValue, metadata);

    EXPECT_EQ(os.str(), "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15");

}



TEST_F(PrintBitmaskTest_1373, InvalidTypeIdDoesNotCrash_1373) {

    EXPECT_CALL(mockValue, typeId()).WillOnce(::testing::Return(invalidTypeId));

    printBitmask(os, mockValue, metadata);

    // No specific expectation on output as behavior for invalid type is not specified

}



class MockValue : public Value {

public:

    MockValue() : Value(unsignedShort) {}



    MOCK_METHOD(size_t, count, (), (const, override));

    MOCK_METHOD(int64_t, toInt64, (size_t), (const, override));

    MOCK_METHOD(TypeId, typeId, (), (const, override));

};


