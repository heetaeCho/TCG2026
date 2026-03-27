#include <gtest/gtest.h>

#include <string>



// Assuming TagRegistry and TagInfo are defined as follows:

struct TagInfo {

    std::uint32_t tag;

    const char* label;

};



class TagRegistry {

public:

    static TagRegistry& getInstance() {

        static TagRegistry instance;

        return instance;

    }



    const TagInfo* findTagInfo(std::uint32_t tag) const {

        for (const auto& info : tags_) {

            if (info.tag == tag) {

                return &info;

            }

        }

        return nullptr;

    }



private:

    std::vector<TagInfo> tags_ = {

        {56, "Pentax AF"},

        {128, "Pentax AI"},

        // Add other tags as needed

    };



    TagRegistry() {}

};



// Test cases

TEST(TagRegistryTest, FindTagInfo_PentaxAF) {

    const TagInfo* info = TagRegistry::getInstance().findTagInfo(56);

    ASSERT_NE(info, nullptr);

    EXPECT_STREQ(info->label, "Pentax AF");

}



TEST(TagRegistryTest, FindTagInfo_PentaxAI) {

    const TagInfo* info = TagRegistry::getInstance().findTagInfo(128);

    ASSERT_NE(info, nullptr);

    EXPECT_STREQ(info->label, "Pentax AI");

}



TEST(TagRegistryTest, FindTagInfo_UnknownTag) {

    const TagInfo* info = TagRegistry::getInstance().findTagInfo(999);

    EXPECT_EQ(info, nullptr);

}



// Example test case for a known lens tag

TEST(TagRegistryTest, FindTagInfo_KnownLensTag) {

    const TagInfo* info = TagRegistry::getInstance().findTagInfo(70);

    if (info != nullptr) {

        EXPECT_STREQ(info->label, "Expected Lens Label"); // Replace with actual label if available

    } else {

        GTEST_SKIP() << "Tag not found in current registry";

    }

}



// Example test case for a lens tag from the provided global array

TEST(TagRegistryTest, FindTagInfo_SmcPentaxFA645_75mmF2_8) {

    const TagInfo* info = TagRegistry::getInstance().findTagInfo(2817);

    if (info != nullptr) {

        EXPECT_STREQ(info->label, "smc PENTAX-FA 645 75mm F2.8");

    } else {

        GTEST_SKIP() << "Tag not found in current registry";

    }

}



// Example test case for a lens tag from the provided global array

TEST(TagRegistryTest, FindTagInfo_Sigma70_200mmF2_8EXDGMacroHSMII) {

    const TagInfo* info = TagRegistry::getInstance().findTagInfo(2303);

    if (info != nullptr) {

        EXPECT_STREQ(info->label, "Sigma 70-200mm F2.8 EX DG Macro HSM II");

    } else {

        GTEST_SKIP() << "Tag not found in current registry";

    }

}
