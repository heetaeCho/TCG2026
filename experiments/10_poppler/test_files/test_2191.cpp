#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"

#include "poppler-private.h"



// Mocking GDateTime and related functions if necessary

class MockGDateTime {

public:

    MOCK_METHOD0(get_year, int());

    MOCK_METHOD0(get_month, int());

    MOCK_METHOD0(get_day_of_month, int());

    MOCK_METHOD0(get_hour_utc, int());

    MOCK_METHOD0(get_minute_utc, int());

    MOCK_METHOD0(get_second_utc, int());

};



// Since GDateTime is an opaque type in glib, we need to create a mock class and use it

GDateTime* mock_g_date_time_new(int year, int month, int day, int hour, int minute, double seconds) {

    return reinterpret_cast<GDateTime*>(new MockGDateTime);

}



void mock_g_date_time_unref(GDateTime* datetime) {

    delete reinterpret_cast<MockGDateTime*>(datetime);

}



// Test fixture for PopplerDocument tests

class PopplerDocumentTest_2191 : public ::testing::Test {

protected:

    void SetUp() override {

        document = new PopplerDocument();

        document->doc = new _PopplerDocument();

    }



    void TearDown() override {

        delete document->doc;

        delete document;

    }



    PopplerDocument* document;

};



// Test case for normal operation

TEST_F(PopplerDocumentTest_2191, SetModificationDateTime_Normal_2191) {

    GDateTime* mock_datetime = mock_g_date_time_new(2023, 10, 5, 14, 30, 0.0);

    EXPECT_NO_THROW(poppler_document_set_modification_date_time(document, mock_datetime));

    mock_g_date_time_unref(mock_datetime);

}



// Test case for boundary condition with null GDateTime

TEST_F(PopplerDocumentTest_2191, SetModificationDateTime_Null_2191) {

    EXPECT_NO_THROW(poppler_document_set_modification_date_time(document, nullptr));

}



// Since the interface does not provide a way to verify the internal state or external interactions,

// we can only test for normal operation and boundary conditions based on the provided signature.

```


