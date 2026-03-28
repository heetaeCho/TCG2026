#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mock IoWrapper for testing purposes

class MockIoWrapper {

public:

    MOCK_METHOD(size_t, write, (const byte* data, size_t count), ());

};



namespace Exiv2 { namespace Internal {



class Nikon2MnHeaderTest_1464 : public ::testing::Test {

protected:

    Nikon2MnHeader header_;

    MockIoWrapper mockIoWrapper_;

};



TEST_F(Nikon2MnHeaderTest_1464, WriteCallsIoWrapperWithCorrectParameters_1464) {

    EXPECT_CALL(mockIoWrapper_, write(::testing::NotNull(), ::testing::Eq(header_.sizeOfSignature())))

        .WillOnce(::testing::Return(header_.sizeOfSignature()));



    size_t result = header_.write(mockIoWrapper_, littleEndian);



    EXPECT_EQ(result, header_.sizeOfSignature());

}



TEST_F(Nikon2MnHeaderTest_1464, WriteReturnsCorrectSize_1464) {

    EXPECT_CALL(mockIoWrapper_, write(::testing::NotNull(), ::testing::Eq(header_.sizeOfSignature())))

        .WillOnce(::testing::Return(header_.sizeOfSignature()));



    size_t result = header_.write(mockIoWrapper_, littleEndian);



    EXPECT_EQ(result, header_.sizeOfSignature());

}



TEST_F(Nikon2MnHeaderTest_1464, WriteHandlesDifferentByteOrder_1464) {

    EXPECT_CALL(mockIoWrapper_, write(::testing::NotNull(), ::testing::Eq(header_.sizeOfSignature())))

        .WillOnce(::testing::Return(header_.sizeOfSignature()));



    size_t result = header_.write(mockIoWrapper_, bigEndian);



    EXPECT_EQ(result, header_.sizeOfSignature());

}



} } // namespace Exiv2::Internal
