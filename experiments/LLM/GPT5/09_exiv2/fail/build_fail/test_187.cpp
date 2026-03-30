#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include <string>
#include <vector>

// Mock ExifData class since it's not provided.
class ExifData {};

// Mock the TagVocabulary structure, which is part of the function signature
struct Tag {
    std::string label_;
};

namespace Exiv2 {
    namespace Internal {

        // Mock find function used in printTagVocabularyMulti.
        const Tag* find(const Tag* array, const std::string& str) {
            for (size_t i = 0; array[i].label_ != ""; ++i) {
                if (array[i].label_ == str) {
                    return &array[i];
                }
            }
            return nullptr;
        }

        // Define the function from the partial code snippet.
        template <size_t N, const TagVocabulary (&array)[N]>
        std::ostream& printTagVocabularyMulti(std::ostream& os, const std::vector<std::string>& value, const ExifData*) {
            static_assert(N > 0, "Passed zero length printTagVocabularyMulti");
            if (value.empty()) {
                return os << "(" << value.size() << ")";
            }
            for (size_t i = 0; i < value.size(); i++) {
                if (i != 0) os << ", ";
                auto td = Exiv2::find(array, value[i]);
                if (td) {
                    os << td->label_;
                } else {
                    os << "(" << value[i] << ")";
                }
            }
            return os;
        }
    }
}

// Test case for the printTagVocabularyMulti function
class PrintTagVocabularyMultiTest_187 : public ::testing::Test {
protected:
    // TagVocabulary setup for the test case
    static constexpr Tag TagArray[] = {
        {"Tag1"},
        {"Tag2"},
        {"Tag3"},
        {""} // End marker
    };

    ExifData exifData;
};

TEST_F(PrintTagVocabularyMultiTest_187, TestEmptyValue_187) {
    std::vector<std::string> value = {};
    std::ostringstream os;
    Exiv2::Internal::printTagVocabularyMulti<3, TagArray>(os, value, &exifData);
    EXPECT_EQ(os.str(), "(0)");
}

TEST_F(PrintTagVocabularyMultiTest_187, TestSingleTag_187) {
    std::vector<std::string> value = {"Tag1"};
    std::ostringstream os;
    Exiv2::Internal::printTagVocabularyMulti<3, TagArray>(os, value, &exifData);
    EXPECT_EQ(os.str(), "Tag1");
}

TEST_F(PrintTagVocabularyMultiTest_187, TestMultipleTags_187) {
    std::vector<std::string> value = {"Tag1", "Tag2"};
    std::ostringstream os;
    Exiv2::Internal::printTagVocabularyMulti<3, TagArray>(os, value, &exifData);
    EXPECT_EQ(os.str(), "Tag1, Tag2");
}

TEST_F(PrintTagVocabularyMultiTest_187, TestTagsWithUnknownValue_187) {
    std::vector<std::string> value = {"Tag1", "UnknownTag"};
    std::ostringstream os;
    Exiv2::Internal::printTagVocabularyMulti<3, TagArray>(os, value, &exifData);
    EXPECT_EQ(os.str(), "Tag1, (UnknownTag)");
}

TEST_F(PrintTagVocabularyMultiTest_187, TestTagCountBoundary_187) {
    std::vector<std::string> value = {"Tag1", "Tag2", "Tag3"};
    std::ostringstream os;
    Exiv2::Internal::printTagVocabularyMulti<3, TagArray>(os, value, &exifData);
    EXPECT_EQ(os.str(), "Tag1, Tag2, Tag3");
}

TEST_F(PrintTagVocabularyMultiTest_187, TestTagCountBeyondVocabulary_187) {
    std::vector<std::string> value = {"Tag1", "Tag2", "UnknownTag", "Tag3"};
    std::ostringstream os;
    Exiv2::Internal::printTagVocabularyMulti<3, TagArray>(os, value, &exifData);
    EXPECT_EQ(os.str(), "Tag1, Tag2, (UnknownTag), Tag3");
}