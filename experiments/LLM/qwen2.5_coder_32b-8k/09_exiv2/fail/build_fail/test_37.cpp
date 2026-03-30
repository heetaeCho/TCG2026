#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/metadatum.hpp"

#include <sstream>



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class MockKey : public Key {

public:

    MOCK_CONST_METHOD0(key, std::string());

    MOCK_CONST_METHOD0(familyName, const char*());

    MOCK_CONST_METHOD0(groupName, std::string());

    MOCK_CONST_METHOD0(tagName, std::string());

    MOCK_CONST_METHOD0(tagLabel, std::string());

    MOCK_CONST_METHOD0(tagDesc, std::string());

    MOCK_CONST_METHOD0(tag, uint16_t());

};



class KeyTest_37 : public ::testing::Test {

protected:

    MockKey mockKey;

};



TEST_F(KeyTest_37, KeyReturnsCorrectValue_37) {

    EXPECT_CALL(mockKey, key()).WillOnce(Return("test_key"));

    EXPECT_EQ(mockKey.key(), "test_key");

}



TEST_F(KeyTest_37, FamilyNameReturnsCorrectValue_37) {

    EXPECT_CALL(mockKey, familyName()).WillOnce(Return("test_family"));

    EXPECT_STREQ(mockKey.familyName(), "test_family");

}



TEST_F(KeyTest_37, GroupNameReturnsCorrectValue_37) {

    EXPECT_CALL(mockKey, groupName()).WillOnce(Return("test_group"));

    EXPECT_EQ(mockKey.groupName(), "test_group");

}



TEST_F(KeyTest_37, TagNameReturnsCorrectValue_37) {

    EXPECT_CALL(mockKey, tagName()).WillOnce(Return("test_tag_name"));

    EXPECT_EQ(mockKey.tagName(), "test_tag_name");

}



TEST_F(KeyTest_37, TagLabelReturnsCorrectValue_37) {

    EXPECT_CALL(mockKey, tagLabel()).WillOnce(Return("test_tag_label"));

    EXPECT_EQ(mockKey.tagLabel(), "test_tag_label");

}



TEST_F(KeyTest_37, TagDescReturnsCorrectValue_37) {

    EXPECT_CALL(mockKey, tagDesc()).WillOnce(Return("test_tag_desc"));

    EXPECT_EQ(mockKey.tagDesc(), "test_tag_desc");

}



TEST_F(KeyTest_37, TagReturnsCorrectValue_37) {

    EXPECT_CALL(mockKey, tag()).WillOnce(Return(12345));

    EXPECT_EQ(mockKey.tag(), 12345);

}



TEST_F(KeyTest_37, WriteOutputsCorrectString_37) {

    std::ostringstream oss;

    EXPECT_CALL(mockKey, write(_)).WillOnce([](std::ostream& os) -> std::ostream& {

        return os << "test_output";

    });

    mockKey.write(oss);

    EXPECT_EQ(oss.str(), "test_output");

}



TEST_F(KeyTest_37, CloneReturnsNonNullPtr_37) {

    auto cloned = mockKey.clone();

    EXPECT_NE(cloned.get(), nullptr);

}
