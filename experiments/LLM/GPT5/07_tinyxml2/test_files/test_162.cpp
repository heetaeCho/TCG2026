// TEST_ID: 162
#include <gtest/gtest.h>

#include "tinyxml2.h"

#include <cstring>

class ReadBOMTest_162 : public ::testing::Test {
protected:
	tinyxml2::XMLUtil util_;
};

TEST_F(ReadBOMTest_162, DetectsUtf8BOMAndAdvancesPointer_162) {
	// UTF-8 BOM: 0xEF 0xBB 0xBF
	const char input[] = "\xEF\xBB\xBF" "abc";

	bool hasBom = false;
	const char* out = util_.ReadBOM(input, &hasBom);

	EXPECT_TRUE(hasBom);
	EXPECT_EQ(out, input + 3);
	EXPECT_STREQ(out, "abc");
}

TEST_F(ReadBOMTest_162, NoBOMReturnsSamePointerAndSetsFalse_162) {
	const char input[] = "abc";

	bool hasBom = true;  // should be overwritten to false
	const char* out = util_.ReadBOM(input, &hasBom);

	EXPECT_FALSE(hasBom);
	EXPECT_EQ(out, input);
	EXPECT_STREQ(out, "abc");
}

TEST_F(ReadBOMTest_162, PartialBOMDoesNotTrigger_162) {
	// Only first two BOM bytes present; third byte is '\0' due to string terminator.
	const char input[] = "\xEF\xBB";

	bool hasBom = true;  // should be overwritten to false
	const char* out = util_.ReadBOM(input, &hasBom);

	EXPECT_FALSE(hasBom);
	EXPECT_EQ(out, input);
	// Ensure the returned pointer still points to the original buffer start.
	EXPECT_EQ(static_cast<unsigned char>(out[0]), 0xEF);
	EXPECT_EQ(static_cast<unsigned char>(out[1]), 0xBB);
	EXPECT_EQ(out[2], '\0');
}

#if defined(GTEST_HAS_DEATH_TEST) && GTEST_HAS_DEATH_TEST && !defined(NDEBUG)
TEST_F(ReadBOMTest_162, NullArgumentsCauseDeath_162) {
	bool hasBom = false;
	const char input[] = "abc";

	// These are expected to trip TIXMLASSERT in debug builds.
	EXPECT_DEATH({ util_.ReadBOM(nullptr, &hasBom); }, "");
	EXPECT_DEATH({ util_.ReadBOM(input, nullptr); }, "");
}
#endif
