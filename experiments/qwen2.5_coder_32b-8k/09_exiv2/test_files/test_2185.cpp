#include <gtest/gtest.h>

#include "makernote_int.hpp"

#include "exiv2/types.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class Olympus2MnHeaderTest_2185 : public ::testing::Test {

protected:

    Olympus2MnHeader olympus_header;

};



TEST_F(Olympus2MnHeaderTest_2185, DefaultConstructorInitializesCorrectly_2185) {

    // Since we treat the implementation as a black box, we can only verify observable behavior.

    // Here, we assume that the default constructor initializes some internal state correctly

    // by checking if subsequent methods behave as expected without exceptions.

    EXPECT_NO_THROW(olympus_header.size());

}



TEST_F(Olympus2MnHeaderTest_2185, ReadFunctionWithValidData_2185) {

    byte data[] = {0x4F, 0x4C, 0x59, 0x4D};

    EXPECT_TRUE(olympus_header.read(data, sizeof(data), littleEndian));

}



TEST_F(Olympus2MnHeaderTest_2185, ReadFunctionWithInvalidDataSize_2185) {

    byte data[] = {0x4F, 0x4C};

    EXPECT_FALSE(olympus_header.read(data, sizeof(data), littleEndian));

}



TEST_F(Olympus2MnHeaderTest_2185, SizeOfSignatureReturnsCorrectValue_2185) {

    EXPECT_EQ(Olympus2MnHeader::sizeOfSignature(), 4u); // Assuming signature size is 4 bytes

}



TEST_F(Olympus2MnHeaderTest_2185, SetByteOrderAndGetByteOrderConsistent_2185) {

    olympus_header.setByteOrder(littleEndian);

    EXPECT_EQ(olympus_header.byteOrder(), littleEndian);



    olympus_header.setByteOrder(bigEndian);

    EXPECT_EQ(olympus_header.byteOrder(), bigEndian);

}



TEST_F(Olympus2MnHeaderTest_2185, IfdOffsetReturnsValidValue_2185) {

    // Assuming ifdOffset returns a non-negative value

    EXPECT_GE(olympus_header.ifdOffset(), 0u);

}



TEST_F(Olympus2MnHeaderTest_2185, BaseOffsetReturnsValidValue_2185) {

    size_t mnOffset = 10;

    // Assuming baseOffset returns a non-negative value

    EXPECT_GE(olympus_header.baseOffset(mnOffset), 0u);

}



TEST_F(Olympus2MnHeaderTest_2185, WriteFunctionWithValidIoWrapper_2185) {

    class MockIoWrapper : public IoWrapper {

    public:

        MOCK_METHOD(void, write, (const byte* data, size_t wcount), (override));

    };



    MockIoWrapper mock_io_wrapper;

    EXPECT_CALL(mock_io_wrapper, write(::testing::_, ::testing::_)).Times(1);



    olympus_header.write(mock_io_wrapper, littleEndian);

}
