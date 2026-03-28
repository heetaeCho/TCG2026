#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "explanations.h"

#include <vector>

#include <string>

#include <cstdarg>



using ::testing::_;

using ::testing::ElementsAre;

using ::testing::Return;



class MockExplanations : public Explanations {

public:

    MOCK_METHOD(void, Record, (const void* item, const char* fmt, ...), (override));

    MOCK_METHOD(void, RecordArgs, (const void* item, const char* fmt, va_list args), (override));

    MOCK_METHOD(void, LookupAndAppend, (const void* item, std::vector<std::string>* out), (override));

};



class OptionalExplanationsTest_18 : public ::testing::Test {

protected:

    MockExplanations mockExplanations;

    OptionalExplanations optionalExplanations{&mockExplanations};

};



TEST_F(OptionalExplanationsTest_18, RecordDelegatesToExplanations_18) {

    const void* item = reinterpret_cast<const void*>(0x1);

    const char* fmt = "test %d";

    int arg = 42;



    EXPECT_CALL(mockExplanations, Record(item, fmt, arg));



    optionalExplanations.Record(item, fmt, arg);

}



TEST_F(OptionalExplanationsTest_18, RecordArgsDelegatesToExplanations_18) {

    const void* item = reinterpret_cast<const void*>(0x2);

    const char* fmt = "test %d";

    va_list args;



    EXPECT_CALL(mockExplanations, RecordArgs(item, fmt, _));



    optionalExplanations.RecordArgs(item, fmt, args);

}



TEST_F(OptionalExplanationsTest_18, LookupAndAppendDelegatesToExplanations_18) {

    const void* item = reinterpret_cast<const void*>(0x3);

    std::vector<std::string> out;



    EXPECT_CALL(mockExplanations, LookupAndAppend(item, &out));



    optionalExplanations.LookupAndAppend(item, &out);

}



TEST_F(OptionalExplanationsTest_18, PtrReturnsCorrectPointer_18) {

    EXPECT_EQ(optionalExplanations.ptr(), &mockExplanations);

}
