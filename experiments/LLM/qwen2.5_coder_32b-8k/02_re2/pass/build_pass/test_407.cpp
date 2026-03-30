#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/prog.h"

#include "absl/strings/string_view.h"



using namespace re2;



TEST(ProgTest_407, EmptyFlags_BeginningOfText_407) {

    absl::string_view text = "example";

    const char* p = text.data();

    uint32_t flags = Prog::EmptyFlags(text, p);

    EXPECT_EQ(flags & (kEmptyBeginText | kEmptyBeginLine), kEmptyBeginText | kEmptyBeginLine);

}



TEST(ProgTest_407, EmptyFlags_EndOfText_407) {

    absl::string_view text = "example";

    const char* p = text.data() + text.size();

    uint32_t flags = Prog::EmptyFlags(text, p);

    EXPECT_EQ(flags & (kEmptyEndText | kEmptyEndLine), kEmptyEndText | kEmptyEndLine);

}



TEST(ProgTest_407, EmptyFlags_MiddleOfText_NotWordBoundary_407) {

    absl::string_view text = "example";

    const char* p = text.data() + 3; // Points to 'a' in "example"

    uint32_t flags = Prog::EmptyFlags(text, p);

    EXPECT_EQ(flags & kEmptyWordBoundary, 0);

    EXPECT_EQ(flags & kEmptyNonWordBoundary, kEmptyNonWordBoundary);

}



TEST(ProgTest_407, EmptyFlags_MiddleOfText_WordBoundary_407) {

    absl::string_view text = "ex ample";

    const char* p = text.data() + 2; // Points to space in "ex ample"

    uint32_t flags = Prog::EmptyFlags(text, p);

    EXPECT_EQ(flags & kEmptyWordBoundary, kEmptyWordBoundary);

}



TEST(ProgTest_407, EmptyFlags_BeginningOfText_WordChar_407) {

    absl::string_view text = "example";

    const char* p = text.data();

    uint32_t flags = Prog::EmptyFlags(text, p);

    EXPECT_EQ(flags & kEmptyWordBoundary, 0);

}



TEST(ProgTest_407, EmptyFlags_EndOfText_WordChar_407) {

    absl::string_view text = "example";

    const char* p = text.data() + text.size();

    uint32_t flags = Prog::EmptyFlags(text, p);

    EXPECT_EQ(flags & kEmptyWordBoundary, 0);

}



TEST(ProgTest_407, EmptyFlags_NewlineAtBeginning_407) {

    absl::string_view text = "\nexample";

    const char* p = text.data() + 1;

    uint32_t flags = Prog::EmptyFlags(text, p);

    EXPECT_EQ(flags & (kEmptyBeginLine | kEmptyWordBoundary), kEmptyBeginLine | kEmptyWordBoundary);

}



TEST(ProgTest_407, EmptyFlags_NewlineAtEnd_407) {

    absl::string_view text = "example\n";

    const char* p = text.data() + 7; // Points to '\n' in "example\n"

    uint32_t flags = Prog::EmptyFlags(text, p);

    EXPECT_EQ(flags & (kEmptyEndLine | kEmptyWordBoundary), kEmptyEndLine | kEmptyWordBoundary);

}



TEST(ProgTest_407, EmptyFlags_EmptyText_407) {

    absl::string_view text = "";

    const char* p = text.data();

    uint32_t flags = Prog::EmptyFlags(text, p);

    EXPECT_EQ(flags & (kEmptyBeginText | kEmptyEndText), kEmptyBeginText | kEmptyEndText);

}
