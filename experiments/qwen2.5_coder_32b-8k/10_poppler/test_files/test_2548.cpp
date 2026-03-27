#include <gtest/gtest.h>

#include <gmock/gmock.h>



extern "C" {

    struct _PopplerTextSpan { const gchar *text; };

    typedef struct _PopplerTextSpan PopplerTextSpan;



    const gchar *poppler_text_span_get_text(PopplerTextSpan *poppler_text_span);

}



class PopplerTextSpanTest_2548 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize test objects if necessary

        testSpan = new PopplerTextSpan();

        testSpan->text = "Sample Text";

    }



    void TearDown() override {

        // Clean up test objects if necessary

        delete testSpan;

    }



    PopplerTextSpan* testSpan;

};



TEST_F(PopplerTextSpanTest_2548, GetText_ReturnsCorrectText_2548) {

    EXPECT_STREQ("Sample Text", poppler_text_span_get_text(testSpan));

}



TEST_F(PopplerTextSpanTest_2548, GetText_ReturnsNullForNullPointer_2548) {

    EXPECT_EQ(nullptr, poppler_text_span_get_text(nullptr));

}
