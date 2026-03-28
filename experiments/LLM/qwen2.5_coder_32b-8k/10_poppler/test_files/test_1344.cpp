#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/qt5/src/poppler-qiodeviceinstream.cc"

#include "./TestProjects/poppler/Object.h"



using namespace Poppler;

using testing::_;

using testing::NiceMock;



class MockQIODevice : public QIODevice {

public:

    MOCK_METHOD(qint64, readData(char *data, qint64 maxlen), (override));

    MOCK_METHOD(qint64, writeData(const char *data, qint64 len), (override));

    MOCK_METHOD(bool, seek(qint64 pos), (override));

    MOCK_METHOD(qint64, size, (), (const override));

};



class QIODeviceInStreamTest : public ::testing::Test {

protected:

    NiceMock<MockQIODevice> mockDevice;

    Object dict;

    std::unique_ptr<QIODeviceInStream> stream;



    void SetUp() override {

        stream = std::make_unique<QIODeviceInStream>(&mockDevice, 0, true, 1024, std::move(dict));

    }

};



TEST_F(QIODeviceInStreamTest_1344, MakeSubStreamNormalOperation_1344) {

    auto subStream = stream->makeSubStream(0, true, 512, Object());

    EXPECT_NE(subStream.get(), nullptr);

}



TEST_F(QIODeviceInStreamTest_1344, MakeSubStreamBoundaryConditions_1344) {

    auto subStreamStartZero = stream->makeSubStream(0, true, 0, Object());

    EXPECT_NE(subStreamStartZero.get(), nullptr);



    auto subStreamFullLength = stream->makeSubStream(0, true, 1024, Object());

    EXPECT_NE(subStreamFullLength.get(), nullptr);

}



TEST_F(QIODeviceInStreamTest_1344, MakeSubStreamLimitedFalse_1344) {

    auto subStreamUnlimited = stream->makeSubStream(0, false, 512, Object());

    EXPECT_NE(subStreamUnlimited.get(), nullptr);

}
