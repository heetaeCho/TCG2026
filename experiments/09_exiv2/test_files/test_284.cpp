#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"

#include "error.hpp"



using namespace Exiv2::Internal;

using ::testing::_;



class MockOffsetWriter : public OffsetWriter {

public:

    MOCK_METHOD(void, setTarget, (OffsetId id, uint32_t target), (override));

};



class IoWrapperTest : public ::testing::Test {

protected:

    BasicIo mockBasicIo;

    byte mockHeader[10];

    const size_t mockSize = 10;

    MockOffsetWriter* mockPow;



    void SetUp() override {

        mockPow = new MockOffsetWriter();

    }



    void TearDown() override {

        delete mockPow;

    }

};



TEST_F(IoWrapperTest_284, SetTargetWithinRange_284) {

    IoWrapper ioWrapper(mockBasicIo, mockHeader, mockSize, mockPow);

    EXPECT_CALL(*mockPow, setTarget(static_cast<OffsetId>(1), static_cast<uint32_t>(100)));

    EXPECT_NO_THROW(ioWrapper.setTarget(1, 100));

}



TEST_F(IoWrapperTest_284, SetTargetMaxValue_284) {

    IoWrapper ioWrapper(mockBasicIo, mockHeader, mockSize, mockPow);

    EXPECT_CALL(*mockPow, setTarget(static_cast<OffsetId>(1), std::numeric_limits<uint32_t>::max()));

    EXPECT_NO_THROW(ioWrapper.setTarget(1, std::numeric_limits<uint32_t>::max()));

}



TEST_F(IoWrapperTest_284, SetTargetAboveRange_284) {

    IoWrapper ioWrapper(mockBasicIo, mockHeader, mockSize, mockPow);

    EXPECT_CALL(*mockPow, setTarget(_, _)).Times(0);

    EXPECT_THROW(ioWrapper.setTarget(1, std::numeric_limits<uint32_t>::max() + 1), Error);

}



TEST_F(IoWrapperTest_284, SetTargetBoundaryValue_284) {

    IoWrapper ioWrapper(mockBasicIo, mockHeader, mockSize, mockPow);

    EXPECT_CALL(*mockPow, setTarget(static_cast<OffsetId>(1), static_cast<uint32_t>(0)));

    EXPECT_NO_THROW(ioWrapper.setTarget(1, 0));

}



TEST_F(IoWrapperTest_284, SetTargetNegativeValue_284) {

    IoWrapper ioWrapper(mockBasicIo, mockHeader, mockSize, mockPow);

    EXPECT_CALL(*mockPow, setTarget(_, _)).Times(0);

    // size_t is unsigned, so negative value will be converted to a large positive number

    EXPECT_THROW(ioWrapper.setTarget(1, static_cast<size_t>(-1)), Error);

}
