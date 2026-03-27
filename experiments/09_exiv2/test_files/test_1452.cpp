#include <gmock/gmock.h>

#include <gtest/gtest.h>



// Assuming IoWrapper and ByteOrder are defined somewhere in the codebase.

namespace Exiv2 {

    namespace Internal {

        class OMSystemMnHeader {

        public:

            size_t write(IoWrapper& ioWrapper, ByteOrder) const;

        };

    }

}



using namespace ::testing;



class MockIoWrapper : public IoWrapper {

public:

    MOCK_METHOD(size_t, write, (const uint8_t* data, size_t length), (override));

};



class OMSystemMnHeaderTest_1452 : public Test {

protected:

    MockIoWrapper mockIoWrapper;

    Exiv2::Internal::OMSystemMnHeader header;

};



TEST_F(OMSystemMnHeaderTest_1452, WriteCallsIoWrapperWriteWithCorrectLength_1452) {

    EXPECT_CALL(mockIoWrapper, write(_, Eq(header.sizeOfSignature())))

        .Times(1);



    header.write(mockIoWrapper, littleEndian);

}



TEST_F(OMSystemMnHeaderTest_1452, WriteReturnsSizeOfSignature_1452) {

    size_t result = header.write(mockIoWrapper, littleEndian);

    EXPECT_EQ(result, header.sizeOfSignature());

}
