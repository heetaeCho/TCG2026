#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"

#include "exiv2/helper_functions.cpp"



using namespace Exiv2;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(size_t, size, (), (const, override));

    MOCK_METHOD(void, seekOrThrow, (int64_t offset, Position pos, ErrorCode err), (override));

    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));

};



TEST_F(MockBasicIo, ReadStringTag_NormalOperation_120) {

    MockBasicIo mockIo;

    std::string expected = "HelloWorld";

    const size_t length = expected.size();

    

    EXPECT_CALL(mockIo, size()).WillOnce(::testing::Return(length + 5));

    EXPECT_CALL(mockIo, seekOrThrow(0, BasicIo::beg, ErrorCode::kerCorruptedMetadata)).Times(1);

    EXPECT_CALL(mockIo, read(::testing::NotNull(), length))

        .WillOnce([expected](byte* buf, size_t rcount) {

            std::copy(expected.begin(), expected.end(), buf);

            return rcount;

        });



    BasicIo::UniquePtr io(&mockIo, [](BasicIo*){});

    std::string result = readStringTag(io, length);

    EXPECT_EQ(result, expected);

}



TEST_F(MockBasicIo, ReadStringTag_BoundaryCondition_ZeroLength_120) {

    MockBasicIo mockIo;

    const size_t length = 0;



    EXPECT_CALL(mockIo, size()).WillOnce(::testing::Return(5));

    EXPECT_CALL(mockIo, seekOrThrow(0, BasicIo::beg, ErrorCode::kerCorruptedMetadata)).Times(1);

    EXPECT_CALL(mockIo, read(::testing::NotNull(), length))

        .WillOnce([](byte* buf, size_t rcount) {

            return rcount;

        });



    BasicIo::UniquePtr io(&mockIo, [](BasicIo*){});

    std::string result = readStringTag(io, length);

    EXPECT_EQ(result, "");

}



TEST_F(MockBasicIo, ReadStringTag_ExceptionalCase_ExceedSize_120) {

    MockBasicIo mockIo;

    const size_t length = 10;



    EXPECT_CALL(mockIo, size()).WillOnce(::testing::Return(5));

    EXPECT_CALL(mockIo, seekOrThrow(0, BasicIo::beg, ErrorCode::kerCorruptedMetadata))

        .WillOnce([](int64_t offset, Position pos, ErrorCode err) {

            throw Error(err);

        });



    BasicIo::UniquePtr io(&mockIo, [](BasicIo*){});

    EXPECT_THROW(readStringTag(io, length), Exiv2::Error);

}



TEST_F(MockBasicIo, ReadStringTag_ExceptionalCase_ReadFailure_120) {

    MockBasicIo mockIo;

    std::string expected = "HelloWorld";

    const size_t length = expected.size();

    

    EXPECT_CALL(mockIo, size()).WillOnce(::testing::Return(length + 5));

    EXPECT_CALL(mockIo, seekOrThrow(0, BasicIo::beg, ErrorCode::kerCorruptedMetadata)).Times(1);

    EXPECT_CALL(mockIo, read(::testing::NotNull(), length))

        .WillOnce([](byte* buf, size_t rcount) {

            return rcount - 1; // Simulate a failure by not reading the full expected amount

        });



    BasicIo::UniquePtr io(&mockIo, [](BasicIo*){});

    EXPECT_THROW(readStringTag(io, length), Exiv2::Error);

}
