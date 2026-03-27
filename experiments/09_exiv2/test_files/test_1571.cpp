#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "asfvideo.hpp"

#include "xmp_exiv2.hpp"

#include "image.hpp"



using namespace Exiv2;

using testing::Return;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(uint16_t, readWORDTag, (), (override));

    MOCK_METHOD(std::string, readStringWcharTag, (size_t length), (override));

};



class AsfVideoTest_1571 : public ::testing::Test {

protected:

    std::unique_ptr<MockBasicIo> mock_io;

    AsfVideo asf_video;



    AsfVideoTest_1571() : mock_io(std::make_unique<MockBasicIo>()), asf_video(std::move(mock_io)) {}



    void SetUp() override {

        asf_video.xmpData().clear();

    }

};



TEST_F(AsfVideoTest_1571, ContentDescription_EmptyTags_1571) {

    EXPECT_CALL(*mock_io, readWORDTag())

        .WillOnce(Return(0))

        .WillOnce(Return(0))

        .WillOnce(Return(0))

        .WillOnce(Return(0))

        .WillOnce(Return(0));



    asf_video.contentDescription();

    EXPECT_TRUE(asf_video.xmpData().empty());

}



TEST_F(AsfVideoTest_1571, ContentDescription_NormalOperation_1571) {

    EXPECT_CALL(*mock_io, readWORDTag())

        .WillOnce(Return(4))

        .WillOnce(Return(6))

        .WillOnce(Return(8))

        .WillOnce(Return(10))

        .WillOnce(Return(12));

    EXPECT_CALL(*mock_io, readStringWcharTag(4)).WillOnce(Return("Title"));

    EXPECT_CALL(*mock_io, readStringWcharTag(6)).WillOnce(Return("Author"));

    EXPECT_CALL(*mock_io, readStringWcharTag(8)).WillOnce(Return("Copyright"));

    EXPECT_CALL(*mock_io, readStringWcharTag(10)).WillOnce(Return("Description"));

    EXPECT_CALL(*mock_io, readStringWcharTag(12)).WillOnce(Return("Rating"));



    asf_video.contentDescription();

    EXPECT_EQ(asf_video.xmpData()["Xmp.video.Title"].toString(), "Title");

    EXPECT_EQ(asf_video.xmpData()["Xmp.video.Author"].toString(), "Author");

    EXPECT_EQ(asf_video.xmpData()["Xmp.video.Copyright"].toString(), "Copyright");

    EXPECT_EQ(asf_video.xmpData()["Xmp.video.Description"].toString(), "Description");

    EXPECT_EQ(asf_video.xmpData()["Xmp.video.Rating"].toString(), "Rating");

}



TEST_F(AsfVideoTest_1571, ContentDescription_MaxLengthTags_1571) {

    // Assuming a reasonable maximum length for tags based on typical usage

    const size_t max_length = 256;

    EXPECT_CALL(*mock_io, readWORDTag())

        .WillOnce(Return(max_length))

        .WillOnce(Return(max_length))

        .WillOnce(Return(max_length))

        .WillOnce(Return(max_length))

        .WillOnce(Return(max_length));

    EXPECT_CALL(*mock_io, readStringWcharTag(max_length)).WillRepeatedly(Return(std::string(max_length / 2, 'X')));



    asf_video.contentDescription();

    EXPECT_EQ(asf_video.xmpData()["Xmp.video.Title"].toString(), std::string(max_length / 2, 'X'));

    EXPECT_EQ(asf_video.xmpData()["Xmp.video.Author"].toString(), std::string(max_length / 2, 'X'));

    EXPECT_EQ(asf_video.xmpData()["Xmp.video.Copyright"].toString(), std::string(max_length / 2, 'X'));

    EXPECT_EQ(asf_video.xmpData()["Xmp.video.Description"].toString(), std::string(max_length / 2, 'X'));

    EXPECT_EQ(asf_video.xmpData()["Xmp.video.Rating"].toString(), std::string(max_length / 2, 'X'));

}



TEST_F(AsfVideoTest_1571, ContentDescription_ErrorHandling_ReadWORDTagFailure_1571) {

    // Assuming readWORDTag might fail and return an invalid value

    EXPECT_CALL(*mock_io, readWORDTag()).WillOnce(Return(std::numeric_limits<uint16_t>::max()));



    asf_video.contentDescription();

    EXPECT_TRUE(asf_video.xmpData().empty());

}



TEST_F(AsfVideoTest_1571, ContentDescription_ErrorHandling_ReadStringWcharTagFailure_1571) {

    // Assuming readStringWcharTag might fail and return an empty string

    EXPECT_CALL(*mock_io, readWORDTag())

        .WillOnce(Return(4))

        .WillOnce(Return(6));

    EXPECT_CALL(*mock_io, readStringWcharTag(4)).WillOnce(Return(""));

    EXPECT_CALL(*mock_io, readStringWcharTag(6)).WillOnce(Return(""));



    asf_video.contentDescription();

    EXPECT_TRUE(asf_video.xmpData().empty());

}
