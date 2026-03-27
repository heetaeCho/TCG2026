#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-media.h"



using ::testing::_;

using ::testing::Invoke;

using ::testing::Return;



// Mock class for PopplerMediaSaveFunc callback

class MockSaveFunc {

public:

    MOCK_METHOD4(call, gboolean(const gchar* buf, int len, gpointer user_data, GError** error));

};



gboolean mock_save_func_wrapper(const gchar* buf, int len, gpointer user_data, GError** error) {

    return static_cast<MockSaveFunc*>(user_data)->call(buf, len, user_data, error);

}



class PopplerMediaTest_2041 : public ::testing::Test {

protected:

    void SetUp() override {

        mock_save_func = new MockSaveFunc();

        poppler_media = g_new0(_PopplerMedia, 1);

        stream_mock = std::make_unique<Stream>();

        poppler_media->stream = Object(std::move(stream_mock));

    }



    void TearDown() override {

        g_free(poppler_media);

        delete mock_save_func;

    }



    _PopplerMedia* poppler_media;

    MockSaveFunc* mock_save_func;

    std::unique_ptr<Stream> stream_mock;

};



TEST_F(PopplerMediaTest_2041, NormalOperation_2041) {

    EXPECT_CALL(*mock_save_func, call(_, 1024, _, _)).WillOnce(Return(TRUE));

    EXPECT_CALL(*stream_mock, rewind()).WillOnce(Return(TRUE));

    EXPECT_CALL(*stream_mock, getChar())

        .WillOnce(Return('a'))

        .WillOnce(Return(EOF));



    GError* error = nullptr;

    gboolean result = poppler_media_save_to_callback(poppler_media, mock_save_func_wrapper, mock_save_func, &error);

    ASSERT_TRUE(result);

}



TEST_F(PopplerMediaTest_2041, BoundaryCondition_EmptyStream_2041) {

    EXPECT_CALL(*stream_mock, rewind()).WillOnce(Return(TRUE));

    EXPECT_CALL(*stream_mock, getChar()).WillOnce(Return(EOF));



    GError* error = nullptr;

    gboolean result = poppler_media_save_to_callback(poppler_media, mock_save_func_wrapper, mock_save_func, &error);

    ASSERT_TRUE(result);

}



TEST_F(PopplerMediaTest_2041, BoundaryCondition_MaxBufferFill_2041) {

    std::vector<char> data(BUF_SIZE, 'a');

    EXPECT_CALL(*mock_save_func, call(_, BUF_SIZE, _, _)).WillOnce(Return(TRUE));

    EXPECT_CALL(*stream_mock, rewind()).WillOnce(Return(TRUE));

    EXPECT_CALL(*stream_mock, getChar())

        .WillRepeatedly(Invoke([&data](int) {

            static int index = 0;

            return index < data.size() ? data[index++] : EOF;

        }));



    GError* error = nullptr;

    gboolean result = poppler_media_save_to_callback(poppler_media, mock_save_func_wrapper, mock_save_func, &error);

    ASSERT_TRUE(result);

}



TEST_F(PopplerMediaTest_2041, Exceptional_RewindFailure_2041) {

    EXPECT_CALL(*stream_mock, rewind()).WillOnce(Return(FALSE));



    GError* error = nullptr;

    gboolean result = poppler_media_save_to_callback(poppler_media, mock_save_func_wrapper, mock_save_func, &error);

    ASSERT_FALSE(result);

}



TEST_F(PopplerMediaTest_2041, Exceptional_SaveFuncFailure_2041) {

    EXPECT_CALL(*mock_save_func, call(_, 1024, _, _)).WillOnce(Return(FALSE));

    EXPECT_CALL(*stream_mock, rewind()).WillOnce(Return(TRUE));

    EXPECT_CALL(*stream_mock, getChar())

        .WillOnce(Return('a'))

        .WillOnce(Return(EOF));



    GError* error = nullptr;

    gboolean result = poppler_media_save_to_callback(poppler_media, mock_save_func_wrapper, mock_save_func, &error);

    ASSERT_FALSE(result);

}



TEST_F(PopplerMediaTest_2041, ExternalInteraction_CallSaveFuncWithCorrectData_2041) {

    std::vector<char> data(BUF_SIZE, 'a');

    EXPECT_CALL(*mock_save_func, call(_, BUF_SIZE, _, _)).WillOnce(Return(TRUE));

    EXPECT_CALL(*stream_mock, rewind()).WillOnce(Return(TRUE));

    EXPECT_CALL(*stream_mock, getChar())

        .WillRepeatedly(Invoke([&data](int) {

            static int index = 0;

            return index < data.size() ? data[index++] : EOF;

        }));



    GError* error = nullptr;

    gboolean result = poppler_media_save_to_callback(poppler_media, mock_save_func_wrapper, mock_save_func, &error);

    ASSERT_TRUE(result);

}
