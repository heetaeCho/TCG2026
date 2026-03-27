#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <cstring>



// Assuming these are defined somewhere in the codebase

enum class Attribute {

    Unknown,

    // Other types...

};



struct Object;

using AttributeCheckFunc = bool(*)(const Object*);



struct AttributeMapEntry {

    public: Attribute type;

    public: const Object *defval;

    public: bool inherit;

    public: AttributeCheckFunc check;

};



// Mocking the necessary external dependencies

class MockObject {};



static inline const AttributeMapEntry *getAttributeMapEntry(const AttributeMapEntry **entryList, const char *name) {

    assert(entryList);

    while (*entryList) {

        const AttributeMapEntry *entry = *entryList;

        while (entry->type != Attribute::Unknown) {

            assert(entry->name);

            if (strcmp(name, entry->name) == 0) {

                return entry;

            }

            entry++;

        }

        entryList++;

    }

    return nullptr;

}



// Test suite for getAttributeMapEntry

class GetAttributeMapEntryTest_1777 : public ::testing::Test {

protected:

    AttributeMapEntry entries[3];



    void SetUp() override {

        entries[0] = {Attribute::Unknown, nullptr, false, nullptr};

        entries[1] = {Attribute::Unknown, nullptr, false, nullptr};



        // Setting up a list of attribute map entries

        static const AttributeMapEntry type1[] = {

            {Attribute::Type(1), reinterpret_cast<const Object*>(new MockObject()), true, nullptr},

            {Attribute::Type(2), reinterpret_cast<const Object*>(new MockObject()), false, nullptr},

            {Attribute::Unknown, nullptr, false, nullptr}

        };



        static const AttributeMapEntry type2[] = {

            {Attribute::Type(3), reinterpret_cast<const Object*>(new MockObject()), true, nullptr},

            {Attribute::Unknown, nullptr, false, nullptr}

        };



        entryList[0] = type1;

        entryList[1] = type2;

        entryList[2] = nullptr;

    }



    void TearDown() override {

        // Clean up any allocated memory

        for (int i = 0; i < 3; ++i) {

            if (entryList[i]) {

                const AttributeMapEntry* entry = entryList[i];

                while (entry->type != Attribute::Unknown) {

                    delete reinterpret_cast<const MockObject*>(entry->defval);

                    entry++;

                }

            }

        }

    }



    const AttributeMapEntry** entryList;

};



// Test case for normal operation

TEST_F(GetAttributeMapEntryTest_1777, FindExistingAttribute_1777) {

    const AttributeMapEntry* result = getAttributeMapEntry(entryList, "type2");

    ASSERT_NE(result, nullptr);

    EXPECT_EQ(result->type, Attribute::Type(2));

}



// Test case for boundary condition with empty entry list

TEST_F(GetAttributeMapEntryTest_1777, EmptyEntryList_1777) {

    const AttributeMapEntry** emptyList = nullptr;

    const AttributeMapEntry* result = getAttributeMapEntry(emptyList, "type1");

    EXPECT_EQ(result, nullptr);

}



// Test case for boundary condition with no matching attribute

TEST_F(GetAttributeMapEntryTest_1777, NonExistingAttribute_1777) {

    const AttributeMapEntry* result = getAttributeMapEntry(entryList, "nonexistent");

    EXPECT_EQ(result, nullptr);

}
