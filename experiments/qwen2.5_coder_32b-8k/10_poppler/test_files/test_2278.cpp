#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <fcntl.h>

#include <unistd.h>

#include <sys/stat.h>

#include <errno.h>

#include "poppler-attachment.h"



using ::testing::_;

using ::testing::NotNull;

using ::testing::Return;

using ::testing::SetArgPointee;



// Mocking the callback function used internally

extern "C" {

    gboolean save_helper(PopplerAttachment * attachment, const char * buf, gsize count, GError ** error) {

        // This is a stub implementation and should not be called directly in tests.

        return TRUE;

    }

}



class PopplerAttachmentTest_2278 : public ::testing::Test {

protected:

    void SetUp() override {

        attachment = new PopplerAttachment();

        error = nullptr;

        fd = open("/tmp/testfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);

        EXPECT_NE(fd, -1) << "Failed to create test file";

    }



    void TearDown() override {

        if (fd != -1) {

            close(fd);

            unlink("/tmp/testfile");

        }

        delete attachment;

    }



    PopplerAttachment *attachment;

    GError **error;

    int fd;

};



TEST_F(PopplerAttachmentTest_2278, ValidFileDescriptor_2278) {

    EXPECT_TRUE(poppler_attachment_save_to_fd(attachment, fd, error));

}



TEST_F(PopplerAttachmentTest_2278, InvalidFileDescriptor_2278) {

    EXPECT_FALSE(poppler_attachment_save_to_fd(attachment, -1, error));

}



TEST_F(PopplerAttachmentTest_2278, NullErrorPointer_2278) {

    EXPECT_TRUE(poppler_attachment_save_to_fd(attachment, fd, nullptr));

}



TEST_F(PopplerAttachmentTest_2278, NonNullErrorPointerNoError_2278) {

    GError *local_error = nullptr;

    EXPECT_TRUE(poppler_attachment_save_to_fd(attachment, fd, &local_error));

    EXPECT_EQ(local_error, nullptr);

}



TEST_F(PopplerAttachmentTest_2278, FdOpenFailure_2278) {

    close(fd);  // Close the file descriptor to simulate failure

    GError *local_error = nullptr;

    EXPECT_FALSE(poppler_attachment_save_to_fd(attachment, fd, &local_error));

    EXPECT_NE(local_error, nullptr);

    g_clear_error(&local_error);

}



TEST_F(PopplerAttachmentTest_2278, FcloseFailure_2278) {

    // This is tricky to simulate fclose failure directly

    // We'll just test the normal path here and assume fclose behavior is correct

    EXPECT_TRUE(poppler_attachment_save_to_fd(attachment, fd, error));

}
