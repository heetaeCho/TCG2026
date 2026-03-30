#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-attachment.h"

#include "Object.h"

#include "Stream.h"



using namespace testing;



class MockSaveFunc {

public:

    MOCK_METHOD4(call, gboolean(const gchar*, gsize, gpointer, GError**));

};



gboolean mock_save_func_wrapper(const gchar* buf, gsize size, gpointer user_data, GError** error) {

    return static_cast<MockSaveFunc*>(user_data)->call(buf, size, user_data, error);

}



class PopplerAttachmentTest_2279 : public ::testing::Test {

protected:

    MockSaveFunc mock_save_func;

    Stream* mock_stream;

    Object obj_stream;

    PopplerAttachment attachment;



    void SetUp() override {

        mock_stream = new NiceMock<StrictMock<Stream>>();

        ON_CALL(*mock_stream, rewind()).WillByDefault(Return(true));

        ON_CALL(*mock_stream, getChar()).WillByDefault(InvokeWithoutArgs([this]() {

            static int i = 0;

            if (i < test_data.size()) return test_data[i++];

            return EOF;

        }));

        obj_stream = Object(mock_stream);

        attachment.parent = 0;

        attachment.name = nullptr;

        attachment.description = nullptr;

        attachment.GTime = 0;

        attachment.ctime = 0;

        attachment.GString = 0;



        PopplerAttachmentPrivate* priv = new PopplerAttachmentPrivate();

        priv->obj_stream = obj_stream;

        attachment.m_private = priv;

    }



    void TearDown() override {

        delete mock_stream;

        delete attachment.m_private;

    }



    std::vector<gchar> test_data;

};



TEST_F(PopplerAttachmentTest_2279, SaveSuccessWithMockStream_2279) {

    test_data = {'H', 'e', 'l', 'l', 'o', '\0'};



    EXPECT_CALL(mock_save_func, call(StrEq("Hell"), 4, A<gpointer>(), A<GError**>())).WillOnce(Return(TRUE));

    EXPECT_CALL(mock_save_func, call(StrEq("o\0"), 2, A<gpointer>(), A<GError**>())).WillOnce(Return(TRUE));



    GError* error = nullptr;

    gboolean result = poppler_attachment_save_to_callback(&attachment, mock_save_func_wrapper, &mock_save_func, &error);

    EXPECT_TRUE(result);

    EXPECT_EQ(error, nullptr);

}



TEST_F(PopplerAttachmentTest_2279, SaveFailureWithMockStream_2279) {

    test_data = {'H', 'e', 'l', 'l', 'o', '\0'};



    EXPECT_CALL(mock_save_func, call(StrEq("Hell"), 4, A<gpointer>(), A<GError**>())).WillOnce(Return(FALSE));



    GError* error = nullptr;

    gboolean result = poppler_attachment_save_to_callback(&attachment, mock_save_func_wrapper, &mock_save_func, &error);

    EXPECT_FALSE(result);

    EXPECT_NE(error, nullptr);

    g_clear_error(&error);

}



TEST_F(PopplerAttachmentTest_2279, SaveEmptyStream_2279) {

    test_data = {};



    GError* error = nullptr;

    gboolean result = poppler_attachment_save_to_callback(&attachment, mock_save_func_wrapper, &mock_save_func, &error);

    EXPECT_TRUE(result);

    EXPECT_EQ(error, nullptr);

}



TEST_F(PopplerAttachmentTest_2279, StreamRewindFailure_2279) {

    test_data = {'H', 'e', 'l', 'l', 'o', '\0'};

    ON_CALL(*mock_stream, rewind()).WillByDefault(Return(false));



    GError* error = nullptr;

    gboolean result = poppler_attachment_save_to_callback(&attachment, mock_save_func_wrapper, &mock_save_func, &error);

    EXPECT_FALSE(result);

    EXPECT_NE(error, nullptr);

    g_clear_error(&error);

}



TEST_F(PopplerAttachmentTest_2279, BoundaryConditionExactBufferSize_2279) {

    test_data = std::vector<gchar>(1024, 'A');



    EXPECT_CALL(mock_save_func, call(StrEq(std::string(1024, 'A').c_str()), 1024, A<gpointer>(), A<GError**>())).WillOnce(Return(TRUE));

    EXPECT_CALL(mock_save_func, call(A<const gchar*>(), A<gsize>(), A<gpointer>(), A<GError**>())).Times(0);



    GError* error = nullptr;

    gboolean result = poppler_attachment_save_to_callback(&attachment, mock_save_func_wrapper, &mock_save_func, &error);

    EXPECT_TRUE(result);

    EXPECT_EQ(error, nullptr);

}



TEST_F(PopplerAttachmentTest_2279, BoundaryConditionLargerThanBufferSize_2279) {

    test_data = std::vector<gchar>(1025, 'A');



    EXPECT_CALL(mock_save_func, call(StrEq(std::string(1024, 'A').c_str()), 1024, A<gpointer>(), A<GError**>())).WillOnce(Return(TRUE));

    EXPECT_CALL(mock_save_func, call(StrEq("A"), 1, A<gpointer>(), A<GError**>())).WillOnce(Return(TRUE));



    GError* error = nullptr;

    gboolean result = poppler_attachment_save_to_callback(&attachment, mock_save_func_wrapper, &mock_save_func, &error);

    EXPECT_TRUE(result);

    EXPECT_EQ(error, nullptr);

}
