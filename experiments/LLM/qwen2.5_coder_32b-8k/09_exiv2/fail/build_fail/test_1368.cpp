#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/tags.hpp"

#include "TestProjects/exiv2/src/tags_int.cpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class TagInfoTest_1368 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup can be used for common initialization if needed

    }

};



TEST_F(TagInfoTest_1368, FindExistingTag_1368) {

    const std::string tagName = "SomeTagName";

    IfdId ifdId = 0; // Assuming a valid IFD ID for testing purposes



    // Mocking tagList to return a predefined list of TagInfo

    const TagInfo mockTags[] = {

        {"AnotherTag", SectionId::imageIFD, TypeId::undefined, nullptr},

        {tagName, SectionId::imageIFD, TypeId::asciiString, nullptr},

        {"LastTag", SectionId::imageIFD, TypeId::unsignedShort, nullptr},

        {"", SectionId::unknown, TypeId::undefined, nullptr} // Terminator

    };



    auto originalTagList = tagList;

    tagList = [](IfdId ifd) -> const TagInfo* {

        return mockTags;

    };



    const TagInfo* result = tagInfo(tagName, ifdId);

    EXPECT_NE(result, nullptr);

    EXPECT_EQ(std::string(result->name_), tagName);



    // Restore original function

    tagList = originalTagList;

}



TEST_F(TagInfoTest_1368, FindNonExistingTag_1368) {

    const std::string tagName = "NonExistentTagName";

    IfdId ifdId = 0; // Assuming a valid IFD ID for testing purposes



    // Mocking tagList to return a predefined list of TagInfo

    const TagInfo mockTags[] = {

        {"AnotherTag", SectionId::imageIFD, TypeId::undefined, nullptr},

        {"LastTag", SectionId::imageIFD, TypeId::unsignedShort, nullptr},

        {"", SectionId::unknown, TypeId::undefined, nullptr} // Terminator

    };



    auto originalTagList = tagList;

    tagList = [](IfdId ifd) -> const TagInfo* {

        return mockTags;

    };



    const TagInfo* result = tagInfo(tagName, ifdId);

    EXPECT_EQ(result, nullptr);



    // Restore original function

    tagList = originalTagList;

}



TEST_F(TagInfoTest_1368, EmptyTagName_1368) {

    IfdId ifdId = 0; // Assuming a valid IFD ID for testing purposes



    const TagInfo* result = tagInfo("", ifdId);

    EXPECT_EQ(result, nullptr);

}



TEST_F(TagInfoTest_1368, InvalidIfdId_1368) {

    const std::string tagName = "SomeTagName";

    IfdId invalidIfdId = static_cast<IfdId>(-1); // Assuming an invalid IFD ID for testing purposes



    // Mocking tagList to return a predefined list of TagInfo

    const TagInfo mockTags[] = {

        {"AnotherTag", SectionId::imageIFD, TypeId::undefined, nullptr},

        {tagName, SectionId::imageIFD, TypeId::asciiString, nullptr},

        {"LastTag", SectionId::imageIFD, TypeId::unsignedShort, nullptr},

        {"", SectionId::unknown, TypeId::undefined, nullptr} // Terminator

    };



    auto originalTagList = tagList;

    tagList = [](IfdId ifd) -> const TagInfo* {

        return mockTags;

    };



    const TagInfo* result = tagInfo(tagName, invalidIfdId);

    EXPECT_EQ(result, nullptr);



    // Restore original function

    tagList = originalTagList;

}
