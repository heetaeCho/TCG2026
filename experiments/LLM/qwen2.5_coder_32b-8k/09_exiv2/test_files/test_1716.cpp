#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/xmpsidecar.hpp"

#include "exiv2/basicio.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, read, (byte * buf, size_t rcount), (override));

    MOCK_METHOD(const std::string &, path, (), (const, override));

    MOCK_METHOD(int, error, (), (const, override));

    MOCK_METHOD(bool, eof, (), (const, override));

};



class XmpSidecarTest_1716 : public ::testing::Test {

protected:

    MockBasicIo mockIo;

    XmpSidecar xmpSidecar{std::make_unique<MockBasicIo>(mockIo), false};

};



TEST_F(XmpSidecarTest_1716, ReadMetadata_Success_1716) {

    EXPECT_CALL(mockIo, open()).WillOnce(::testing::Return(0));

    EXPECT_CALL(mockIo, path()).Times(::testing::AtLeast(1)).WillRepeatedly(::testing::Return("test.xmp"));

    EXPECT_CALL(mockIo, read(::testing::NotNull(), 65536))

        .WillOnce(::testing::DoAll(

            ::testing::SetArgReferee<0>("XMP packet data"),

            ::testing::Return(14)

        ))

        .WillOnce(::testing::DoAll(

            ::testing::SetArgReferee<0>(""),

            ::testing::Return(0)

        ));

    EXPECT_CALL(mockIo, error()).WillRepeatedly(::testing::Return(0));

    EXPECT_CALL(mockIo, eof()).WillOnce(::testing::Return(false)).WillOnce(::testing::Return(true));



    xmpSidecar.readMetadata();

}



TEST_F(XmpSidecarTest_1716, ReadMetadata_OpenFailed_1716) {

    EXPECT_CALL(mockIo, open()).WillOnce(::testing::Return(-1));

    EXPECT_CALL(mockIo, path()).Times(1).WillRepeatedly(::testing::Return("test.xmp"));



    EXPECT_THROW(xmpSidecar.readMetadata(), Error);

}



TEST_F(XmpSidecarTest_1716, ReadMetadata_NotAnImage_1716) {

    EXPECT_CALL(mockIo, open()).WillOnce(::testing::Return(0));

    EXPECT_CALL(mockIo, path()).Times(::testing::AtLeast(1)).WillRepeatedly(::testing::Return("test.xmp"));

    EXPECT_CALL(mockIo, read(::testing::NotNull(), 65536))

        .WillOnce(::testing::DoAll(

            ::testing::SetArgReferee<0>("Non-XMP data"),

            ::testing::Return(14)

        ))

        .WillOnce(::testing::DoAll(

            ::testing::SetArgReferee<0>(""),

            ::testing::Return(0)

        ));

    EXPECT_CALL(mockIo, error()).WillRepeatedly(::testing::Return(0));

    EXPECT_CALL(mockIo, eof()).WillOnce(::testing::Return(false)).WillOnce(::testing::Return(true));



    EXPECT_THROW(xmpSidecar.readMetadata(), Error);

}



TEST_F(XmpSidecarTest_1716, ReadMetadata_ReadFailed_1716) {

    EXPECT_CALL(mockIo, open()).WillOnce(::testing::Return(0));

    EXPECT_CALL(mockIo, path()).Times(::testing::AtLeast(1)).WillRepeatedly(::testing::Return("test.xmp"));

    EXPECT_CALL(mockIo, read(::testing::NotNull(), 65536))

        .WillOnce(::testing::DoAll(

            ::testing::SetArgReferee<0>("XMP packet data"),

            ::testing::Return(14)

        ))

        .WillOnce(::testing::DoAll(

            ::testing::SetArgReferee<0>(""),

            ::testing::Return(0)

        ));

    EXPECT_CALL(mockIo, error()).WillRepeatedly(::testing::Return(-1));

    EXPECT_CALL(mockIo, eof()).WillOnce(::testing::Return(false)).WillOnce(::testing::Return(true));



    EXPECT_THROW(xmpSidecar.readMetadata(), Error);

}
