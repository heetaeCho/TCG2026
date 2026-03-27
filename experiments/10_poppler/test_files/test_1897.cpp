#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <string>



// Assuming GooString and Entry are defined somewhere in the codebase.

class GooString {

public:

    std::string name;

    std::string toStr() const { return name; }

};



struct Entry {

    GooString* name;

};



struct EntryGooStringComparer {

public:

    static constexpr const std::string &get(const GooString *string) {

        return string->toStr();

    }



    static constexpr const std::string &get(const Entry &entry) {

        return entry.name->toStr();

    }



    auto operator()(const auto &lhs, const auto &rhs) {

        return get(lhs) < get(rhs);

    }

};



class EntryGooStringComparerTest : public ::testing::Test {

protected:

    GooString* gooString1;

    GooString* gooString2;

    Entry entry1;

    Entry entry2;



    void SetUp() override {

        gooString1 = new GooString{.name = "abc"};

        gooString2 = new GooString{.name = "def"};

        entry1.name = gooString1;

        entry2.name = gooString2;

    }



    void TearDown() override {

        delete gooString1;

        delete gooString2;

    }

};



TEST_F(EntryGooStringComparerTest_1897, GetReturnsCorrectStringFromGooString_1897) {

    EXPECT_EQ(EntryGooStringComparer::get(gooString1), "abc");

}



TEST_F(EntryGooStringComparerTest_1897, GetReturnsCorrectStringFromEntry_1897) {

    EXPECT_EQ(EntryGooStringComparer::get(entry1), "abc");

}



TEST_F(EntryGooStringComparerTest_1897, OperatorCallComparesEntriesLexicographically_1897) {

    EntryGooStringComparer comparer;

    EXPECT_TRUE(comparer(entry1, entry2));

    EXPECT_FALSE(comparer(entry2, entry1));

}



TEST_F(EntryGooStringComparerTest_1897, OperatorCallReturnsFalseForEqualEntries_1897) {

    GooString* gooString3 = new GooString{.name = "abc"};

    Entry entry3{.name = gooString3};

    EntryGooStringComparer comparer;

    EXPECT_FALSE(comparer(entry1, entry3));

    delete gooString3;

}



TEST_F(EntryGooStringComparerTest_1897, OperatorCallHandlesBoundaryConditions_1897) {

    GooString* emptyString = new GooString{.name = ""};

    Entry emptyEntry{.name = emptyString};

    EntryGooStringComparer comparer;

    EXPECT_TRUE(comparer(emptyEntry, entry1));

    EXPECT_FALSE(comparer(entry1, emptyEntry));

    delete emptyString;

}
