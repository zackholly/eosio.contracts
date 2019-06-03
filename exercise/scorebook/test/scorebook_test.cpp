#include <eosio/eosio.hpp>
#include <eosio/tester.hpp>

#include "../src/scorebook.cpp"

using namespace eosio;
using namespace eosio::native;

EOSIO_TEST_BEGIN(scorebook_test)

EOSIO_TEST_END

// boilerplate main, this will be generated in a future release
int main(int argc, char** argv) {
   silence_output(true);
   EOSIO_TEST(scorebook_test);
   return has_failed();
}
