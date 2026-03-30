#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/metadatum.hpp"

#include <sstream>



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class KeyTest : public ::testing::Test {

protected:

    class MockKey : public Key {

    public:

        MOCK_METHOD0(key, const std::string());

        MOCK_METHOD0(familyName, const char*());

        MOCK_METHOD0(groupName, const std::string());

        MOCK_METHOD0(tagName, const std::string());

        MOCK_METHOD0(tagLabel, const std::string());

        MOCK_METHOD0(tagDesc, const std::string());

        MOCK_METHOD0(tag, const uint16_t());



    protected:

        MockKey() = default;

        ~MockKey() override = default;



        const Key* clone_() const override { return new MockKey(*this); }

    };



    MockKey mockKey;

};



TEST_F(KeyTest_36, Key_ReturnsExpectedValue_36) {

    EXPECT_CALL(mockKey, key()).WillOnce(Return("expected_key"));

    EXPECT_EQ(mockKey.key(), "expected_key");

}



TEST_F(KeyTest_36, FamilyName_ReturnsExpectedValue_36) {

    EXPECT_CALL(mockKey, familyName()).WillOnce(Return("expected_family_name"));

    EXPECT_STREQ(mockKey.familyName(), "expected_family_name");

}



TEST_F(KeyTest_36, GroupName_ReturnsExpectedValue_36) {

    EXPECT_CALL(mockKey, groupName()).WillOnce(Return("expected_group_name"));

    EXPECT_EQ(mockKey.groupName(), "expected_group_name");

}



TEST_F(KeyTest_36, TagName_ReturnsExpectedValue_36) {

    EXPECT_CALL(mockKey, tagName()).WillOnce(Return("expected_tag_name"));

    EXPECT_EQ(mockKey.tagName(), "expected_tag_name");

}



TEST_F(KeyTest_36, TagLabel_ReturnsExpectedValue_36) {

    EXPECT_CALL(mockKey, tagLabel()).WillOnce(Return("expected_tag_label"));

    EXPECT_EQ(mockKey.tagLabel(), "expected_tag_label");

}



TEST_F(KeyTest_36, TagDesc_ReturnsExpectedValue_36) {

    EXPECT_CALL(mockKey, tagDesc()).WillOnce(Return("expected_tag_desc"));

    EXPECT_EQ(mockKey.tagDesc(), "expected_tag_desc");

}



TEST_F(KeyTest_36, Tag_ReturnsExpectedValue_36) {

    EXPECT_CALL(mockKey, tag()).WillOnce(Return(12345));

    EXPECT_EQ(mockKey.tag(), 12345);

}



TEST_F(KeyTest_36, WriteToStream_OutputsKeyValue_36) {

    std::ostringstream oss;

    EXPECT_CALL(mockKey, key()).WillOnce(Return("expected_key"));

    mockKey.write(oss);

    EXPECT_EQ(oss.str(), "expected_key");

}



TEST_F(KeyTest_36, Clone_ReturnsNewInstance_36) {

    auto cloned = mockKey.clone();

    EXPECT_NE(&mockKey, cloned.get());

}
