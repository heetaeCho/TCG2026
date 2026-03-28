#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/emitter.h"

#include "yaml-cpp/exceptions.h"



using namespace YAML;

using ::testing::Eq;



class EmitterTest_540 : public ::testing::Test {

protected:

    Emitter emitter;

};



TEST_F(EmitterTest_540, WriteTag_Verbatim_Success_540) {

    _Tag tag("!example", "tag:example.com,2019:foo", _Tag::Type::Verbatim);

    auto& result = emitter.Write(tag);

    EXPECT_EQ(&result, &emitter);

}



TEST_F(EmitterTest_540, WriteTag_PrimaryHandle_Success_540) {

    _Tag tag("!", "example", _Tag::Type::PrimaryHandle);

    auto& result = emitter.Write(tag);

    EXPECT_EQ(&result, &emitter);

}



TEST_F(EmitterTest_540, WriteTag_Prefix_Success_540) {

    _Tag tag("!prefix", "tag:example.com,2019:foo", _Tag::Type::Prefix);

    auto& result = emitter.Write(tag);

    EXPECT_EQ(&result, &emitter);

}



TEST_F(EmitterTest_540, WriteTag_Multiple_Success_540) {

    _Tag tag1("!prefix", "tag:example.com,2019:foo", _Tag::Type::Prefix);

    emitter.Write(tag1);



    _Tag tag2("!", "example", _Tag::Type::PrimaryHandle);

    auto& result = emitter.Write(tag2);

    EXPECT_EQ(&result, &emitter);

}



TEST_F(EmitterTest_540, WriteTag_InvalidAfterValidTag_Error_540) {

    _Tag validTag("!prefix", "tag:example.com,2019:foo", _Tag::Type::Prefix);

    emitter.Write(validTag);



    _Tag invalidTag("!invalid", "tag:example.com,2019:bar", _Tag::Type::Verbatim);

    auto& result = emitter.Write(invalidTag);

    EXPECT_EQ(&result, &emitter);

    EXPECT_FALSE(emitter.good());

    EXPECT_EQ(emitter.GetLastError(), ErrorMsg::INVALID_TAG);

}



TEST_F(EmitterTest_540, WriteTag_EmptyPrefix_Error_540) {

    _Tag tag("", "tag:example.com,2019:foo", _Tag::Type::Prefix);

    auto& result = emitter.Write(tag);

    EXPECT_EQ(&result, &emitter);

    EXPECT_FALSE(emitter.good());

    EXPECT_EQ(emitter.GetLastError(), ErrorMsg::INVALID_TAG);

}



TEST_F(EmitterTest_540, WriteTag_EmptyContent_Error_540) {

    _Tag tag("!prefix", "", _Tag::Type::Verbatim);

    auto& result = emitter.Write(tag);

    EXPECT_EQ(&result, &emitter);

    EXPECT_FALSE(emitter.good());

    EXPECT_EQ(emitter.GetLastError(), ErrorMsg::INVALID_TAG);

}



TEST_F(EmitterTest_540, WriteTag_EmptyPrefixAndContent_Error_540) {

    _Tag tag("", "", _Tag::Type::PrimaryHandle);

    auto& result = emitter.Write(tag);

    EXPECT_EQ(&result, &emitter);

    EXPECT_FALSE(emitter.good());

    EXPECT_EQ(emitter.GetLastError(), ErrorMsg::INVALID_TAG);

}



TEST_F(EmitterTest_540, WriteTag_BadState_Error_540) {

    emitter.SetError("previous error");

    _Tag tag("!prefix", "tag:example.com,2019:foo", _Tag::Type::Prefix);

    auto& result = emitter.Write(tag);

    EXPECT_EQ(&result, &emitter);

    EXPECT_FALSE(emitter.good());

    EXPECT_EQ(emitter.GetLastError(), "previous error");

}
