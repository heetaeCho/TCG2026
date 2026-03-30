#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/bitstate.h"

#include "re2/prog.h"



using namespace re2;

using ::testing::_;

using ::testing::Return;



class MockProg : public Prog {

public:

    MOCK_METHOD(bool, anchor_start, (), (const));

    MOCK_METHOD(bool, anchor_end, (), (const));

    MOCK_METHOD(int, start, (), (const));

    MOCK_METHOD(const void*, PrefixAccel, (const void* data, size_t size), (const));

    MOCK_METHOD(bool, can_prefix_accel, (), (const));

};



class BitStateTest_580 : public ::testing::Test {

protected:

    std::unique_ptr<MockProg> mock_prog_;

    std::unique_ptr<BitState> bit_state_;



    void SetUp() override {

        mock_prog_ = std::make_unique<MockProg>();

        bit_state_ = std::make_unique<BitState>(mock_prog_.get());

    }

};



TEST_F(BitStateTest_580, Search_ReturnsFalseWhenTextIsNull_580) {

    absl::string_view text = "";

    EXPECT_FALSE(bit_state_->Search(text, "", false, false, nullptr, 0));

}



TEST_F(BitStateTest_580, Search_ReturnsFalseWhenAnchoredStartMismatch_580) {

    absl::string_view text = "abc";

    EXPECT_CALL(*mock_prog_, anchor_start()).WillOnce(Return(true));

    EXPECT_FALSE(bit_state_->Search(text, "def", true, false, nullptr, 0));

}



TEST_F(BitStateTest_580, Search_ReturnsFalseWhenAnchoredEndMismatch_580) {

    absl::string_view text = "abc";

    EXPECT_CALL(*mock_prog_, anchor_start()).WillOnce(Return(false));

    EXPECT_CALL(*mock_prog_, anchor_end()).WillOnce(Return(true));

    EXPECT_FALSE(bit_state_->Search(text, "def", false, true, nullptr, 0));

}



TEST_F(BitStateTest_580, Search_ReturnsTrueWhenExactMatchAnchoredStartAndEnd_580) {

    absl::string_view text = "abc";

    EXPECT_CALL(*mock_prog_, anchor_start()).WillOnce(Return(true));

    EXPECT_CALL(*mock_prog_, anchor_end()).WillOnce(Return(true));

    EXPECT_CALL(*mock_prog_, start()).WillOnce(Return(1));

    EXPECT_CALL(*mock_prog_, can_prefix_accel()).WillOnce(Return(false));



    absl::string_view submatch[1];

    EXPECT_TRUE(bit_state_->Search(text, text, true, true, submatch, 1));

}



TEST_F(BitStateTest_580, Search_ReturnsTrueWhenExactMatchUnanchoredStartAndEnd_580) {

    absl::string_view text = "abc";

    EXPECT_CALL(*mock_prog_, anchor_start()).WillOnce(Return(false));

    EXPECT_CALL(*mock_prog_, anchor_end()).WillOnce(Return(false));

    EXPECT_CALL(*mock_prog_, start()).WillOnce(Return(1));

    EXPECT_CALL(*mock_prog_, can_prefix_accel()).WillOnce(Return(false));



    absl::string_view submatch[1];

    EXPECT_TRUE(bit_state_->Search(text, text, false, false, submatch, 1));

}



TEST_F(BitStateTest_580, Search_ReturnsFalseWhenPrefixAccelFails_580) {

    absl::string_view text = "abc";

    EXPECT_CALL(*mock_prog_, anchor_start()).WillOnce(Return(false));

    EXPECT_CALL(*mock_prog_, anchor_end()).WillOnce(Return(false));

    EXPECT_CALL(*mock_prog_, start()).WillOnce(Return(1));

    EXPECT_CALL(*mock_prog_, can_prefix_accel()).WillOnce(Return(true));

    EXPECT_CALL(*mock_prog_, PrefixAccel(_, _)).WillOnce(Return(nullptr));



    absl::string_view submatch[1];

    EXPECT_FALSE(bit_state_->Search(text, text, false, false, submatch, 1));

}



TEST_F(BitStateTest_580, Search_ReturnsTrueWhenPrefixAccelSucceedsAndMatches_580) {

    absl::string_view text = "abc";

    EXPECT_CALL(*mock_prog_, anchor_start()).WillOnce(Return(false));

    EXPECT_CALL(*mock_prog_, anchor_end()).WillOnce(Return(false));

    EXPECT_CALL(*mock_prog_, start()).WillOnce(Return(1));

    EXPECT_CALL(*mock_prog_, can_prefix_accel()).WillOnce(Return(true));

    EXPECT_CALL(*mock_prog_, PrefixAccel(_, _)).WillOnce(Return(text.data()));

    

    absl::string_view submatch[1];

    EXPECT_TRUE(bit_state_->Search(text, text, false, false, submatch, 1));

}



TEST_F(BitStateTest_580, Search_ReturnsFalseWhenTrySearchFails_580) {

    absl::string_view text = "abc";

    EXPECT_CALL(*mock_prog_, anchor_start()).WillOnce(Return(false));

    EXPECT_CALL(*mock_prog_, anchor_end()).WillOnce(Return(false));

    EXPECT_CALL(*mock_prog_, start()).WillOnce(Return(1));

    EXPECT_CALL(*mock_prog_, can_prefix_accel()).WillOnce(Return(false));



    absl::string_view submatch[1];

    EXPECT_FALSE(bit_state_->Search(text, text, false, false, submatch, 1));

}
