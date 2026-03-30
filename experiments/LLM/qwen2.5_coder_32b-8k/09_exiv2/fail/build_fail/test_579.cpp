#include <gtest/gtest.h>

#include "exiv2/basicio.hpp"



using namespace Exiv2;



class MemIoTest_579 : public ::testing::Test {

protected:

    void SetUp() override {

        memIo = std::make_unique<MemIo>();

        srcIo = std::make_unique<BasicIoMock>();

    }



    void TearDown() override {

        memIo.reset();

        srcIo.reset();

    }



    std::unique_ptr<MemIo> memIo;

    std::unique_ptr<BasicIoMock> srcIo;



    class BasicIoMock : public BasicIo {

    public:

        MOCK_METHOD(int, open, (), (override));

        MOCK_METHOD(int, close, (), (override));

        MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));

        MOCK_METHOD(size_t, write, (BasicIo& src), (override));

        MOCK_METHOD(int, putb, (byte data), (override));

        MOCK_METHOD(DataBuf, read, (size_t rcount), (override));

        MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));

        MOCK_METHOD(int, getb, (), (override));

        MOCK_METHOD(void, transfer, (BasicIo& src), (override));

        MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

        MOCK_METHOD(byte*, mmap, (bool unnamed), (override));

        MOCK_METHOD(int, munmap, (), (override));

        MOCK_METHOD(const size_t, tell, (), (const, override));

        MOCK_METHOD(const size_t, size, (), (const, override));

        MOCK_METHOD(const bool, isopen, (), (const, override));

        MOCK_METHOD(const int, error, (), (const, override));

        MOCK_METHOD(const bool, eof, (), (const, override));

        MOCK_METHOD(const std::string&, path, (), (const, noexcept, override));

        MOCK_METHOD(void, populateFakeData, (), (override));

    };

};



TEST_F(MemIoTest_579, WriteSelfReturnsZero_579) {

    EXPECT_EQ(memIo->write(*memIo.get()), 0U);

}



TEST_F(MemIoTest_579, WriteClosedSrcReturnsZero_579) {

    EXPECT_CALL(*srcIo, isopen()).WillOnce(::testing::Return(false));

    EXPECT_EQ(memIo->write(*srcIo), 0U);

}



TEST_F(MemIoTest_579, WriteReadsAndWritesData_579) {

    byte testData[] = {1, 2, 3, 4, 5};

    EXPECT_CALL(*srcIo, isopen()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*srcIo, read(testing::NotNull(), sizeof(testData)))

        .WillOnce(testing::DoAll(

            testing::SetArrayArgument<0>(testData, testData + sizeof(testData)),

            testing::Return(sizeof(testData))));

    EXPECT_CALL(*memIo, write(testing::Eq(testData), sizeof(testData)))

        .WillOnce(::testing::Return(sizeof(testData)));



    EXPECT_EQ(memIo->write(*srcIo), sizeof(testData));

}



TEST_F(MemIoTest_579, WriteHandlesPartialReads_579) {

    byte testData1[] = {1, 2, 3};

    byte testData2[] = {4, 5, 6};

    EXPECT_CALL(*srcIo, isopen()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*srcIo, read(testing::NotNull(), sizeof(testData1)))

        .WillOnce(testing::DoAll(

            testing::SetArrayArgument<0>(testData1, testData1 + sizeof(testData1)),

            testing::Return(sizeof(testData1))));

    EXPECT_CALL(*memIo, write(testing::Eq(testData1), sizeof(testData1)))

        .WillOnce(::testing::Return(sizeof(testData1)));

    EXPECT_CALL(*srcIo, read(testing::NotNull(), sizeof(testData2)))

        .WillOnce(testing::DoAll(

            testing::SetArrayArgument<0>(testData2, testData2 + sizeof(testData2)),

            testing::Return(sizeof(testData2))));

    EXPECT_CALL(*memIo, write(testing::Eq(testData2), sizeof(testData2)))

        .WillOnce(::testing::Return(sizeof(testData2)));



    EXPECT_EQ(memIo->write(*srcIo), sizeof(testData1) + sizeof(testData2));

}



TEST_F(MemIoTest_579, WriteHandlesEmptyReads_579) {

    EXPECT_CALL(*srcIo, isopen()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*srcIo, read(testing::NotNull(), 4096)).WillOnce(::testing::Return(0U));



    EXPECT_EQ(memIo->write(*srcIo), 0U);

}
