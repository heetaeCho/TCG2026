#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-attachment.h"

#include <gio/gio.h>



// Mock class for GDateTime if needed, but in this case, we only need to mock return values



class PopplerAttachmentTest_2274 : public ::testing::Test {

protected:

    void SetUp() override {

        attachment = reinterpret_cast<PopplerAttachment*>(g_malloc0(sizeof(PopplerAttachment)));

    }



    void TearDown() override {

        g_free(attachment);

    }



    PopplerAttachment* attachment;

};



TEST_F(PopplerAttachmentTest_2274, GetMTime_ReturnsNull_WhenUnset_2274) {

    GDateTime *mtime = poppler_attachment_get_mtime(attachment);

    EXPECT_EQ(mtime, nullptr);

}



TEST_F(PopplerAttachmentTest_2274, GetMTime_ReturnsSetValue_WhenSet_2274) {

    // Assuming we can set the private mtime for testing purposes

    GDateTime *expected_mtime = g_date_time_new_now_utc();

    GET_PRIVATE(attachment)->mtime = expected_mtime;



    GDateTime *mtime = poppler_attachment_get_mtime(attachment);

    EXPECT_EQ(mtime, expected_mtime);



    g_date_time_unref(expected_mtime);

}



// Assuming boundary and exceptional cases are not directly observable from the interface

```


