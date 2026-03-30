#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



using namespace testing;



class MockBaseStream : public BaseStream {

public:

    MOCK_METHOD(void, setPos, (Goffset pos, int dir), (override));

    MOCK_METHOD(BaseStream*, getBaseStream, (), (override));



    explicit MockBaseStream(Object&& dictA, Goffset lengthA) : BaseStream(std::move(dictA), lengthA) {}

};



class BaseStreamStreamTest_1495 : public ::testing::Test {

protected:

    std::unique_ptr<MockBaseStream> mock_base_stream;

    std::unique_ptr<BaseStreamStream> base_stream_stream;



    void SetUp() override {

        Object dict; // Assuming Object can be default constructed

        mock_base_stream = std::make_unique<MockBaseStream>(std::move(dict), 1024);

        base_stream_stream = std::make_unique<BaseStreamStream>(std::move(mock_base_stream));

    }

};



TEST_F(BaseStreamStreamTest_1495, SetPosDelegatesToBaseStream_1495) {

    Goffset pos = 100;

    int dir = 0;



    EXPECT_CALL(*mock_base_stream, setPos(pos, dir))

        .Times(1);



    base_stream_stream->setPos(pos, dir);

}



TEST_F(BaseStreamStreamTest_1495, GetBaseStreamDelegatesToBaseStream_1495) {

    BaseStream* expected_base_stream = mock_base_stream.get();



    EXPECT_CALL(*mock_base_stream, getBaseStream())

        .WillOnce(Return(expected_base_stream));



    BaseStream* actual_base_stream = base_stream_stream->getBaseStream();

    EXPECT_EQ(actual_base_stream, expected_base_stream);

}
