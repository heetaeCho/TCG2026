#include <gtest/gtest.h>

#include "exiv2/iptc.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;



class IptcdatumTest_663 : public ::testing::Test {

protected:

    virtual void SetUp() {

        IptcKey key("Iptc.Envelope.CodedCharacterSet");

        Value* value = new StringValue;

        iptcdatum = std::make_unique<Iptcdatum>(key, value);

    }



    std::unique_ptr<Iptcdatum> iptcdatum;

};



TEST_F(IptcdatumTest_663, CopyWithNonNullValue_663) {

    byte buffer[10];

    ByteOrder byteOrder = littleEndian;

    size_t result = iptcdatum->copy(buffer, byteOrder);

    EXPECT_EQ(result, 0); // Assuming no actual data is copied in this context

}



TEST_F(IptcdatumTest_663, CopyWithNullValue_663) {

    iptcdatum->setValue(nullptr);

    byte buffer[10];

    ByteOrder byteOrder = littleEndian;

    size_t result = iptcdatum->copy(buffer, byteOrder);

    EXPECT_EQ(result, 0);

}



TEST_F(IptcdatumTest_663, BoundaryConditionEmptyBuffer_663) {

    byte* emptyBuffer = nullptr;

    ByteOrder byteOrder = littleEndian;

    size_t result = iptcdatum->copy(emptyBuffer, byteOrder);

    EXPECT_EQ(result, 0); // Assuming no actual data is copied in this context

}



TEST_F(IptcdatumTest_663, BoundaryConditionLargeBuffer_663) {

    const size_t bufferSize = 1000;

    byte largeBuffer[bufferSize];

    ByteOrder byteOrder = littleEndian;

    size_t result = iptcdatum->copy(largeBuffer, byteOrder);

    EXPECT_EQ(result, 0); // Assuming no actual data is copied in this context

}



TEST_F(IptcdatumTest_663, BoundaryConditionBigEndian_663) {

    byte buffer[10];

    ByteOrder byteOrder = bigEndian;

    size_t result = iptcdatum->copy(buffer, byteOrder);

    EXPECT_EQ(result, 0); // Assuming no actual data is copied in this context

}



TEST_F(IptcdatumTest_663, BoundaryConditionLittleEndian_663) {

    byte buffer[10];

    ByteOrder byteOrder = littleEndian;

    size_t result = iptcdatum->copy(buffer, byteOrder);

    EXPECT_EQ(result, 0); // Assuming no actual data is copied in this context

}
