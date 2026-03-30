#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "basicio.hpp"



using namespace Exiv2;

using ::testing::NiceMock;

using ::testing::Return;

using ::testing::_;



class MockBasicIo : public BasicIo {

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

    MOCK_METHOD(byte*, mmap, (bool isWriteable), (override));

    MOCK_METHOD(int, munmap, (), (override));

    MOCK_METHOD(const size_t, tell, (), (const override));

    MOCK_METHOD(const size_t, size, (), (const override));

    MOCK_METHOD(const bool, isopen, (), (const override));

    MOCK_METHOD(const int, error, (), (const override));

    MOCK_METHOD(const bool, eof, (), (const override));

    MOCK_METHOD(const std::string&, path, (), (const override));

};



class XPathIoTest_596 : public ::testing::Test {

protected:

    NiceMock<MockBasicIo> mockSrc;

    XPathIo xPathIo{"original_path"};



    void SetUp() override {

        ON_CALL(mockSrc, path()).WillByDefault(Return("source_path"));

    }

};



TEST_F(XPathIoTest_596, TransferRenamesTempFile_596) {

    EXPECT_CALL(mockSrc, path()).Times(1);

    xPathIo.transfer(mockSrc);

}



TEST_F(XPathIoTest_596, TransferCallsBaseTransfer_596) {

    EXPECT_CALL(mockSrc, path()).Times(1);

    EXPECT_CALL(mockSrc, transfer(_)).Times(1);

    xPathIo.transfer(mockSrc);

}



TEST_F(XPathIoTest_596, TransferDoesNotRenameIfNotTemp_596) {

    xPathIo.isTemp_ = false;

    EXPECT_CALL(mockSrc, path()).Times(0);

    xPathIo.transfer(mockSrc);

}



TEST_F(XPathIoTest_596, PathReflectsNewNameAfterTransfer_596) {

    std::string initialPath = xPathIo.path();

    xPathIo.transfer(mockSrc);

    EXPECT_NE(initialPath, xPathIo.path());

}



TEST_F(XPathIoTest_596, TransferSetsIsTempToFalse_596) {

    xPathIo.transfer(mockSrc);

    EXPECT_FALSE(xPathIo.isTemp_);

}
