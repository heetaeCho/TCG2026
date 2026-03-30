#include <gtest/gtest.h>

#include "Stream.h"



using namespace std;



class BaseStreamStreamTest : public ::testing::Test {

protected:

    std::unique_ptr<Stream> mockBaseStream = make_unique<MockStream>();

    std::unique_ptr<BaseStreamStream> baseStreamStream = make_unique<BaseStreamStream>(std::move(mockBaseStream));

};



// Mock class for Stream

class MockStream : public Stream {

public:

    MOCK_METHOD(const StreamKind, getKind, (), (override));

    MOCK_METHOD(bool, rewind, (), (override));

    MOCK_METHOD(int, getChar, (), (override));

    MOCK_METHOD(int, lookChar, (), (override));

    MOCK_METHOD(bool, isBinary, (bool), (const, override));

    MOCK_METHOD(int, getUnfilteredChar, (), (override));

    MOCK_METHOD(bool, unfilteredRewind, (), (override));

    MOCK_METHOD(Goffset, getPos, (), (override));

    MOCK_METHOD(void, setPos, (Goffset pos, int dir), (override));

    MOCK_METHOD(BaseStream*, getBaseStream, (), (override));

    MOCK_METHOD(Stream*, getUndecodedStream, (), (override));

    MOCK_METHOD(Dict*, getDict, (), (override));

    MOCK_METHOD(Object*, getDictObject, (), (override));

};



TEST_F(BaseStreamStreamTest, GetDictObject_DelegatesToBaseStream_1499) {

    Object* expectedObject = new Object();

    EXPECT_CALL(*mockBaseStream, getBaseStream())

        .WillOnce(testing::Return(mockBaseStream.get()));

    EXPECT_CALL(*mockBaseStream, getDictObject())

        .WillOnce(testing::Return(expectedObject));



    Object* result = baseStreamStream->getDictObject();



    EXPECT_EQ(result, expectedObject);

}
