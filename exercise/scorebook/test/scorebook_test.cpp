
#include <eosio/eosio.hpp>
#include <eosio/tester.hpp>
#include "../include/scorebook.hpp"

using namespace eosio;
using namespace eosio::native;

EOSIO_DISPATCH(scorebook, (elect))

EOSIO_TEST_BEGIN(scorebook_partial_table_records_added)
/*
//*****************************************************************************
//
//   check if record is added when: less then 15 records
//
//*****************************************************************************

// add record to table and check the print buffer for number of records
for(int

for i<15;++i
    elect(i,random_double)
    REQUIRE_EQUAL( "Number of records:  "+"i", action_print_buffer)
*/
EOSIO_TEST_END

EOSIO_TEST_BEGIN(scorebook_partial_table_records_dropped_tied)
/*
//*****************************************************************************
//
//   check if elected record is dropped when: score is tied
//
//*****************************************************************************

for i<15;++i
    random_double;
    elect(i,random_double)
    elect(i,random_double)
    REQUIRE_EQUAL( "Elected score tied. Record was not added to the index.",
                    action_print_buffer)

*/
EOSIO_TEST_END

EOSIO_TEST_BEGIN(scorebook_full_table_records_added_higher_lowest)
/*
//*****************************************************************************
//
//   check if record is added when: score is higher than lowest score
//
//*****************************************************************************

load up table

    REQUIRE_EQUAL( "Number of records:  15", action_print_buffer)
    lowest_record = find_lowest_record

    elect( 16, lowest_record.score+1 )

    REQUIRE_EQUAL( "Number of records:  15", action_print_buffer)

    REQUIRE_ASSERT( TRUE, find_record(lowest_record) )
    REQUIRE_ASSERT( FALSE, find_record(16) )

*/
EOSIO_TEST_END

EOSIO_TEST_BEGIN(scorebook_full_table_records_added_highest)
/*
//*****************************************************************************
//
//   check if record is added when: score is highest
//
//*****************************************************************************

load up table

    REQUIRE_EQUAL( "Number of records:  15", action_print_buffer)

    highest_record = find_highest_record
    lowest_record = find_lowest_record

    elect( 16, highest_record.score+1 )

    REQUIRE_EQUAL( "Number of records:  15", action_print_buffer)

    REQUIRE_ASSERT( find_record(lowest_record) )  //Lowest recored dropped
    CHECK_ASSERT( find_record(16) )               //should find it

*/
EOSIO_TEST_END

EOSIO_TEST_BEGIN(scorebook_full_table_records_dropped_lower_lowest)
/*
//*****************************************************************************
//
//   check if elected record is dropped when: score is lower than lowest score
//
//*****************************************************************************

load up table

    REQUIRE_EQUAL( "Number of records:  15", action_print_buffer)

    lowest_record = find_lowest_record

    elect( 16, lowest_record.score - .1 )

    REQUIRE_EQUAL( "Number of records:  15", action_print_buffer)

    CHECK_ASSERT( find_record(lowest_record) )  //should find it
    REQUIRE_ASSERT( find_record(16) )           //shouldn't find it

*/
EOSIO_TEST_END

EOSIO_TEST_BEGIN(scorebook_full_table_records_dropped_tie)
/*
//*****************************************************************************
//
//   check if elected record is dropped when: score is tied
//
//*****************************************************************************

load up table

for each record
    score = find_current_score
    elect(15+i,score)
    REQUIRE_EQUAL( "Elected score tied. Record was not added to the index.",
                    action_print_buffer)
    ++i

*/
EOSIO_TEST_END


// boilerplate main, this will be generated in a future release
int main(int argc, char** argv) {
   silence_output(false);
   EOSIO_TEST(scorebook_partial_table_records_added);
   EOSIO_TEST(scorebook_partial_table_records_dropped_tied);
   EOSIO_TEST(scorebook_full_table_records_added_higher_lowest);
   EOSIO_TEST(scorebook_full_table_records_added_highest);
   EOSIO_TEST(scorebook_full_table_records_dropped_lower_lowest);
   EOSIO_TEST(scorebook_full_table_records_dropped_tie);
   return has_failed();
}
