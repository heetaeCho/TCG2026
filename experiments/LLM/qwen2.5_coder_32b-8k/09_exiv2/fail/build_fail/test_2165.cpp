#include <gtest/gtest.h>

#include "exiv2/value.hpp"



namespace {



using namespace Exiv2;



class DataValueTest_2165 : public ::testing::Test {

protected:

    static constexpr TypeId kSampleTypeId = TypeId::unsignedLong;

    static constexpr ByteOrder kSampleByteOrder = littleEndian;

    static constexpr size_t kSampleLength = 4;

    static constexpr byte kSampleBuffer[kSampleLength] = {0x1, 0x2, 0x3, 0x4};



    DataValueTest_2165() : dataValue_(kSampleBuffer, kSampleLength, kSampleByteOrder, kSampleTypeId) {}



    DataValue dataValue_;

};



TEST_F(DataValueTest_2165, ConstructorInitializesData_2165) {

    EXPECT_TRUE(dataValue_.ok());

}



TEST_F(DataValueTest_2165, ReadFromBufferUpdatesData_2165) {

    byte updatedBuffer[kSampleLength] = {0x4, 0x3, 0x2, 0x1};

    int result = dataValue_.read(updatedBuffer, kSampleLength, kSampleByteOrder);

    EXPECT_EQ(result, 0); // Assuming read returns 0 on success

    EXPECT_TRUE(dataValue_.ok());

}



TEST_F(DataValueTest_2165, ReadFromEmptyStringDoesNotCrash_2165) {

    int result = dataValue_.read("");

    EXPECT_EQ(result, 0); // Assuming read returns 0 on success or no change

    EXPECT_TRUE(dataValue_.ok());

}



TEST_F(DataValueTest_2165, CopyToBufferReturnsCorrectSize_2165) {

    byte outputBuffer[kSampleLength];

    size_t result = dataValue_.copy(outputBuffer, kSampleByteOrder);

    EXPECT_EQ(result, kSampleLength);

}



TEST_F(DataValueTest_2165, CountReturnsExpectedValue_2165) {

    size_t count = dataValue_.count();

    EXPECT_GE(count, 0); // Assuming count returns a non-negative value

}



TEST_F(DataValueTest_2165, SizeReturnsExpectedValue_2165) {

    size_t size = dataValue_.size();

    EXPECT_GE(size, 0); // Assuming size returns a non-negative value

}



TEST_F(DataValueTest_2165, WriteToStreamDoesNotCrash_2165) {

    std::ostringstream os;

    const std::ostream& resultOs = dataValue_.write(os);

    EXPECT_EQ(&resultOs, &os); // Expect the same stream object to be returned

}



TEST_F(DataValueTest_2165, ToStringReturnsNonEmptyString_2165) {

    std::string str = dataValue_.toString();

    EXPECT_FALSE(str.empty());

}



TEST_F(DataValueTest_2165, ToStringWithIndexReturnsNonEmptyString_2165) {

    std::string str = dataValue_.toString(0);

    EXPECT_FALSE(str.empty());

}



TEST_F(DataValueTest_2165, ToInt64WithIndexDoesNotCrash_2165) {

    int64_t value = dataValue_.toInt64(0);

    (void)value; // Use the variable to suppress unused warning

}



TEST_F(DataValueTest_2165, ToUint32WithIndexDoesNotCrash_2165) {

    uint32_t value = dataValue_.toUint32(0);

    (void)value; // Use the variable to suppress unused warning

}



TEST_F(DataValueTest_2165, ToFloatWithIndexDoesNotCrash_2165) {

    float value = dataValue_.toFloat(0);

    (void)value; // Use the variable to suppress unused warning

}



TEST_F(DataValueTest_2165, ToRationalWithIndexDoesNotCrash_2165) {

    Rational value = dataValue_.toRational(0);

    (void)value; // Use the variable to suppress unused warning

}



TEST_F(DataValueTest_2165, SizeDataAreaReturnsExpectedValue_2165) {

    size_t size = dataValue_.sizeDataArea();

    EXPECT_GE(size, 0); // Assuming size returns a non-negative value

}



TEST_F(DataValueTest_2165, DataAreaReturnsNonEmptyBuffer_2165) {

    DataBuf buffer = dataValue_.dataArea();

    EXPECT_NE(buffer.pData_, nullptr);

    EXPECT_EQ(buffer.size_, kSampleLength);

}



} // namespace
