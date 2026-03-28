#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "makernote_int.hpp"



using namespace Exiv2::Internal;

using namespace testing;



class PanasonicMnHeaderTest_1474 : public Test {

protected:

    PanasonicMnHeader mnHeader;

};



TEST_F(PanasonicMnHeaderTest_1474, SizeReturnsSizeOfSignature_1474) {

    EXPECT_EQ(mnHeader.size(), PanasonicMnHeader::sizeOfSignature());

}



TEST_F(PanasonicMnHeaderTest_1474, ReadFunctionExists_1474) {

    byte data[1] = {0};

    ByteOrder byteOrder = littleEndian;

    mnHeader.read(data, sizeof(data), byteOrder);

    // Assuming read does not throw and can be called without issues

}



TEST_F(PanasonicMnHeaderTest_1474, WriteFunctionExists_1474) {

    MockIoWrapper mockIoWrapper;

    ByteOrder byteOrder = littleEndian;

    EXPECT_CALL(mockIoWrapper, write(_, _)).Times(AtLeast(0));

    mnHeader.write(mockIoWrapper, byteOrder);

}



TEST_F(PanasonicMnHeaderTest_1474, IfdOffsetFunctionExists_1474) {

    size_t ifdOffset = mnHeader.ifdOffset();

    // Assuming ifdOffset does not throw and can be called without issues

}



class MockIoWrapper : public IoWrapper {

public:

    MOCK_METHOD2(write, std::size_t(const byte* data, std::size_t length));

};



TEST_F(PanasonicMnHeaderTest_1474, SizeOfSignatureStaticFunctionExists_1474) {

    size_t signatureSize = PanasonicMnHeader::sizeOfSignature();

    // Assuming sizeOfSignature does not throw and can be called without issues

}
