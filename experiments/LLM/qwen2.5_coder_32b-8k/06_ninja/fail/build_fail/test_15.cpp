#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "explanations.h"



using ::testing::_;

using ::testing::Return;

using ::testing::Mock;



class MockExplanations : public Explanations {

public:

    MOCK_METHOD(void, RecordArgs, (const void* item, const char* fmt, va_list args), (override));

};



class OptionalExplanationsTest_15 : public ::testing::Test {

protected:

    MockExplanations mock_explanations;

    OptionalExplanations optional_explanations{&mock_explanations};

};



TEST_F(OptionalExplanationsTest_15, Record_CallsRecordArgsWithCorrectParameters_15) {

    const void* test_item = reinterpret_cast<const void*>(0x1234);

    const char* test_fmt = "test format %d";

    int test_arg = 42;



    EXPECT_CALL(mock_explanations, RecordArgs(test_item, test_fmt, _));



    optional_explanations.Record(test_item, test_fmt, test_arg);

}



TEST_F(OptionalExplanationsTest_15, Record_DoesNotCallRecordArgsWhenExplanationsIsNull_15) {

    OptionalExplanations optional_explanations{nullptr};

    const void* test_item = reinterpret_cast<const void*>(0x1234);

    const char* test_fmt = "test format %d";

    int test_arg = 42;



    EXPECT_CALL(mock_explanations, RecordArgs(_, _, _)).Times(0);



    optional_explanations.Record(test_item, test_fmt, test_arg);

}



TEST_F(OptionalExplanationsTest_15, ptr_ReturnsCorrectPointer_15) {

    ASSERT_EQ(optional_explanations.ptr(), &mock_explanations);

}
