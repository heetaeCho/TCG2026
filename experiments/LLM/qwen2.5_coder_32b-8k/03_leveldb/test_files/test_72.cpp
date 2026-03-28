#include <gtest/gtest.h>

#include "db/version_set.h"



using namespace leveldb;



class VersionSetTest_72 : public ::testing::Test {

protected:

    VersionSet* version_set;

    const std::string dbname = "test_db";

    Options options;

    TableCache table_cache;

    InternalKeyComparator icmp;



    void SetUp() override {

        version_set = new VersionSet(dbname, &options, &table_cache, &icmp);

    }



    void TearDown() override {

        delete version_set;

    }

};



TEST_F(VersionSetTest_72, NewFileNumberReturnsUniqueNumbers_72) {

    uint64_t first_number = version_set->NewFileNumber();

    uint64_t second_number = version_set->NewFileNumber();

    EXPECT_NE(first_number, second_number);

}



TEST_F(VersionSetTest_72, NewFileNumberStartsFromTwo_72) {

    uint64_t first_number = version_set->NewFileNumber();

    EXPECT_EQ(first_number, 2);

}
