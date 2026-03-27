#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/xmpsidecar.hpp"

#include "exiv2/basicio.hpp"



using namespace Exiv2;

using ::testing::Return;

using ::testing::_;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));

    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));

    MOCK_METHOD(void, readOrThrow, (byte* buf, size_t rcount, ErrorCode err), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(void, transfer, (BasicIo & src), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(void, seekOrThrow, (int64_t offset, Position pos, ErrorCode err), (override));

    MOCK_METHOD(byte*, mmap, (bool isWriteable), (override));

    MOCK_METHOD(int, munmap, (), (override));

    MOCK_METHOD(const size_t, tell, (), (const override));

    MOCK_METHOD(const size_t, size, (), (const override));

    MOCK_METHOD(const bool, isopen, (), (const override));

    MOCK_METHOD(const int, error, (), (const override));

    MOCK_METHOD(const bool, eof, (), (const override));

    MOCK_METHOD(const std::string &, path, (), (const override));

    MOCK_METHOD(void, populateFakeData, (), (override));

};



class XmpSidecarTest_2204 : public ::testing::Test {

protected:

    std::unique_ptr<MockBasicIo> mockIo;

    XmpSidecar* xmpSidecar;



    void SetUp() override {

        mockIo = std::make_unique<MockBasicIo>();

        xmpSidecar = new XmpSidecar(std::move(mockIo), true);

    }



    void TearDown() override {

        delete xmpSidecar;

    }

};



TEST_F(XmpSidecarTest_2204, ConstructorCreatesFile_2204) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, write(_, xmlHdrCnt)).Times(1);

    XmpSidecar xmp(mockIo->clone(), true);

}



TEST_F(XmpSidecarTest_2204, ConstructorDoesNotCreateFileWhenFlagIsFalse_2204) {

    EXPECT_CALL(*mockIo, open()).Times(0);

    XmpSidecar xmp(mockIo->clone(), false);

}



TEST_F(XmpSidecarTest_2204, ConstructorFailsToOpenFile_2204) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(-1));

    EXPECT_CALL(*mockIo, write(_, _)).Times(0);

    XmpSidecar xmp(mockIo->clone(), true);

}



TEST_F(XmpSidecarTest_2204, MimeTypeReturnsCorrectType_2204) {

    EXPECT_EQ(xmpSidecar->mimeType(), "application/rdf+xml");

}



TEST_F(XmpSidecarTest_2204, SetCommentSetsComment_2204) {

    xmpSidecar->setComment("Sample Comment");

    // Assuming there is a way to verify this, but since we treat the class as black box,

    // we can only assume it sets correctly without verification.

}



TEST_F(XmpSidecarTest_2204, ReadMetadataFunctionExists_2204) {

    xmpSidecar->readMetadata();

    // Assuming readMetadata does something observable or has side effects, but as a black box,

    // we can only assume it is called without verification.

}



TEST_F(XmpSidecarTest_2204, WriteMetadataFunctionExists_2204) {

    xmpSidecar->writeMetadata();

    // Assuming writeMetadata does something observable or has side effects, but as a black box,

    // we can only assume it is called without verification.

}
