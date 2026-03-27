#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"

#include "xmpsidecar.cpp"



using namespace Exiv2;

using namespace testing;



class BasicIoMock : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));

    MOCK_METHOD(size_t, write, (BasicIo& src), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));

    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));

    MOCK_METHOD(void, readOrThrow, (byte* buf, size_t rcount, ErrorCode err), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(void, transfer, (BasicIo& src), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(void, seekOrThrow, (int64_t offset, Position pos, ErrorCode err), (override));

    MOCK_METHOD(byte*, mmap, (bool isWriteable), (override));

    MOCK_METHOD(int, munmap, (), (override));

    MOCK_METHOD(const size_t, tell, (), (const override));

    MOCK_METHOD(const size_t, size, (), (const override));

    MOCK_METHOD(const bool, isopen, (), (const override));

    MOCK_METHOD(const int, error, (), (const override));

    MOCK_METHOD(const bool, eof, (), (const override));

    MOCK_METHOD(const std::string&, path, (), (const override));

};



class XmpSidecarTest_1720 : public Test {

protected:

    BasicIoMock mockBasicIo;

};



TEST_F(XmpSidecarTest_1720, NormalOperation_XmlHeaderOnly_1720) {

    const char xmlHeader[] = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";

    EXPECT_CALL(mockBasicIo, read(_, 80)).WillOnce(DoAll(SetArrayArgument<0>(xmlHeader, xmlHeader + sizeof(xmlHeader) - 1), Return(sizeof(xmlHeader) - 1)));

    EXPECT_CALL(mockBasicIo, eof()).WillOnce(Return(false));

    EXPECT_CALL(mockBasicIo, error()).WillOnce(Return(0));



    bool result = isXmpType(mockBasicIo, false);

    EXPECT_TRUE(result);

}



TEST_F(XmpSidecarTest_1720, NormalOperation_XmpPacketHeader_1720) {

    const char xmpPacket[] = "<?xpacket begin=\"\357\273\277\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>\n";

    EXPECT_CALL(mockBasicIo, read(_, 80)).WillOnce(DoAll(SetArrayArgument<0>(xmpPacket, xmpPacket + sizeof(xmpPacket) - 1), Return(sizeof(xmpPacket) - 1)));

    EXPECT_CALL(mockBasicIo, eof()).WillOnce(Return(false));

    EXPECT_CALL(mockBasicIo, error()).WillOnce(Return(0));



    bool result = isXmpType(mockBasicIo, false);

    EXPECT_TRUE(result);

}



TEST_F(XmpSidecarTest_1720, NormalOperation_XmpMetaElement_1720) {

    const char xmpMeta[] = "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">\n";

    EXPECT_CALL(mockBasicIo, read(_, 80)).WillOnce(DoAll(SetArrayArgument<0>(xmpMeta, xmpMeta + sizeof(xmpMeta) - 1), Return(sizeof(xmpMeta) - 1)));

    EXPECT_CALL(mockBasicIo, eof()).WillOnce(Return(false));

    EXPECT_CALL(mockBasicIo, error()).WillOnce(Return(0));



    bool result = isXmpType(mockBasicIo, false);

    EXPECT_TRUE(result);

}



TEST_F(XmpSidecarTest_1720, BoundaryCondition_EmptyFile_1720) {

    EXPECT_CALL(mockBasicIo, read(_, 80)).WillOnce(Return(0));

    EXPECT_CALL(mockBasicIo, eof()).WillOnce(Return(true));



    bool result = isXmpType(mockBasicIo, false);

    EXPECT_FALSE(result);

}



TEST_F(XmpSidecarTest_1720, BoundaryCondition_ShortFile_1720) {

    const char shortXml[] = "<?xml";

    EXPECT_CALL(mockBasicIo, read(_, 80)).WillOnce(DoAll(SetArrayArgument<0>(shortXml, shortXml + sizeof(shortXml) - 1), Return(sizeof(shortXml) - 1)));

    EXPECT_CALL(mockBasicIo, eof()).WillOnce(Return(true));



    bool result = isXmpType(mockBasicIo, false);

    EXPECT_FALSE(result);

}



TEST_F(XmpSidecarTest_1720, ExceptionalCase_ReadError_1720) {

    EXPECT_CALL(mockBasicIo, read(_, 80)).WillOnce(Return(0));

    EXPECT_CALL(mockBasicIo, eof()).WillOnce(Return(false));

    EXPECT_CALL(mockBasicIo, error()).WillOnce(Return(1));



    bool result = isXmpType(mockBasicIo, false);

    EXPECT_FALSE(result);

}



TEST_F(XmpSidecarTest_1720, ExceptionalCase_SeekErrorAfterRead_1720) {

    const char xmlHeader[] = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";

    EXPECT_CALL(mockBasicIo, read(_, 80)).WillOnce(DoAll(SetArrayArgument<0>(xmlHeader, xmlHeader + sizeof(xmlHeader) - 1), Return(sizeof(xmlHeader) - 1)));

    EXPECT_CALL(mockBasicIo, eof()).WillOnce(Return(false));

    EXPECT_CALL(mockBasicIo, error()).WillOnce(Return(0));

    EXPECT_CALL(mockBasicIo, seek(-59, BasicIo::cur)).WillOnce(Return(-1));



    bool result = isXmpType(mockBasicIo, true);

    EXPECT_FALSE(result);

}



TEST_F(XmpSidecarTest_1720, ExternalInteraction_SeekCalledWhenAdvanceTrueAndValidHeader_1720) {

    const char xmlHeader[] = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";

    EXPECT_CALL(mockBasicIo, read(_, 80)).WillOnce(DoAll(SetArrayArgument<0>(xmlHeader, xmlHeader + sizeof(xmlHeader) - 1), Return(sizeof(xmlHeader) - 1)));

    EXPECT_CALL(mockBasicIo, eof()).WillOnce(Return(false));

    EXPECT_CALL(mockBasicIo, error()).WillOnce(Return(0));

    EXPECT_CALL(mockBasicIo, seek(-59, BasicIo::cur)).Times(1);



    bool result = isXmpType(mockBasicIo, true);

    EXPECT_TRUE(result);

}



TEST_F(XmpSidecarTest_1720, ExternalInteraction_SeekNotCalledWhenAdvanceFalseAndValidHeader_1720) {

    const char xmlHeader[] = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";

    EXPECT_CALL(mockBasicIo, read(_, 80)).WillOnce(DoAll(SetArrayArgument<0>(xmlHeader, xmlHeader + sizeof(xmlHeader) - 1), Return(sizeof(xmlHeader) - 1)));

    EXPECT_CALL(mockBasicIo, eof()).WillOnce(Return(false));

    EXPECT_CALL(mockBasicIo, error()).WillOnce(Return(0));

    EXPECT_CALL(mockBasicIo, seek(-59, BasicIo::cur)).Times(0);



    bool result = isXmpType(mockBasicIo, false);

    EXPECT_TRUE(result);

}



TEST_F(XmpSidecarTest_1720, ExternalInteraction_SeekCalledWithBOMOffsetWhenAdvanceTrueAndValidHeader_1720) {

    const char xmlHeader[] = "\xef\xbb\xbf<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";

    EXPECT_CALL(mockBasicIo, read(_, 80)).WillOnce(DoAll(SetArrayArgument<0>(xmlHeader, xmlHeader + sizeof(xmlHeader) - 1), Return(sizeof(xmlHeader) - 1)));

    EXPECT_CALL(mockBasicIo, eof()).WillOnce(Return(false));

    EXPECT_CALL(mockBasicIo, error()).WillOnce(Return(0));

    EXPECT_CALL(mockBasicIo, seek(-56, BasicIo::cur)).Times(1);



    bool result = isXmpType(mockBasicIo, true);

    EXPECT_TRUE(result);

}
