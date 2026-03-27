#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "explanations.h"

#include <cstdarg>

#include <vector>



using ::testing::_;

using ::testing::Return;

using ::testing::NotNull;



class ExplanationsMock : public Explanations {

public:

    MOCK_METHOD(void, RecordArgs, (const void* item, const char* fmt, va_list args), (override));

    MOCK_METHOD(void, LookupAndAppend, (const void* item, std::vector<std::string>* out), (override));

};



class OptionalExplanationsTest : public ::testing::Test {

protected:

    ExplanationsMock mockExplanations;

    OptionalExplanations optionalExplanations{&mockExplanations};

};



TEST_F(OptionalExplanationsTest_16, RecordArgs_CallsExplanationsRecordArgs_16) {

    const void* item = reinterpret_cast<const void*>(0x1234);

    const char* fmt = "test %d";

    va_list args;

    va_start(args, fmt);



    EXPECT_CALL(mockExplanations, RecordArgs(item, fmt, args));



    optionalExplanations.RecordArgs(item, fmt, args);



    va_end(args);

}



TEST_F(OptionalExplanationsTest_16, LookupAndAppend_CallsExplanationsLookupAndAppend_16) {

    const void* item = reinterpret_cast<const void*>(0x5678);

    std::vector<std::string> out;



    EXPECT_CALL(mockExplanations, LookupAndAppend(item, NotNull()));



    optionalExplanations.LookupAndAppend(item, &out);

}



TEST_F(OptionalExplanationsTest_16, Ptr_ReturnsExplanationsPointer_16) {

    EXPECT_EQ(optionalExplanations.ptr(), &mockExplanations);

}



TEST_F(OptionalExplanationsTest_16, RecordArgs_NoExplanationsPtr_DoesNothing_16) {

    OptionalExplanations noExplanations{nullptr};

    const void* item = reinterpret_cast<const void*>(0x1234);

    const char* fmt = "test %d";

    va_list args;

    va_start(args, fmt);



    EXPECT_CALL(mockExplanations, RecordArgs(_, _, _)).Times(0);



    noExplanations.RecordArgs(item, fmt, args);



    va_end(args);

}



TEST_F(OptionalExplanationsTest_16, LookupAndAppend_NoExplanationsPtr_DoesNothing_16) {

    OptionalExplanations noExplanations{nullptr};

    const void* item = reinterpret_cast<const void*>(0x5678);

    std::vector<std::string> out;



    EXPECT_CALL(mockExplanations, LookupAndAppend(_, _)).Times(0);



    noExplanations.LookupAndAppend(item, &out);

}
