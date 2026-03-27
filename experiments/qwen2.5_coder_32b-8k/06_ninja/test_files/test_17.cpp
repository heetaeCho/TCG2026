#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <vector>

#include "explanations.h"



using ::testing::Return;

using ::testing::_;



class MockExplanations : public Explanations {

public:

    MOCK_METHOD(void, LookupAndAppend, (const void* item, std::vector<std::string>* out), (override));

};



class OptionalExplanationsTest_17 : public ::testing::Test {

protected:

    std::unique_ptr<MockExplanations> mock_explanations_;

    OptionalExplanations optional_explanations_;



    OptionalExplanationsTest_17() 

        : mock_explanations_(std::make_unique<MockExplanations>()),

          optional_explanations_(mock_explanations_.get()) {}

};



TEST_F(OptionalExplanationsTest_17, LookupAndAppend_CallsUnderlyingIfNotNull_17) {

    const void* test_item = reinterpret_cast<const void*>(0x1234);

    std::vector<std::string> out;

    EXPECT_CALL(*mock_explanations_, LookupAndAppend(test_item, &out)).Times(1);



    optional_explanations_.LookupAndAppend(test_item, &out);

}



TEST_F(OptionalExplanationsTest_17, LookupAndAppend_DoesNotCallIfNull_17) {

    const void* test_item = reinterpret_cast<const void*>(0x1234);

    std::vector<std::string> out;

    OptionalExplanations optional_explanations(nullptr);



    EXPECT_CALL(*mock_explanations_, LookupAndAppend(test_item, &out)).Times(0);



    optional_explanations.LookupAndAppend(test_item, &out);

}



TEST_F(OptionalExplanationsTest_17, ptr_ReturnsCorrectPointer_17) {

    Explanations* raw_ptr = mock_explanations_.get();

    EXPECT_EQ(optional_explanations_.ptr(), raw_ptr);

}
