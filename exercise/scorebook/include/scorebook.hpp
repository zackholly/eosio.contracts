#include <eosio/eosio.hpp>

using namespace eosio;

class [[eosio::contract("scorebook")]] scorebook : public eosio::contract {

public:
  
	scorebook(name receiver, name code,  datastream<const char*> ds): contract(receiver, code, ds){}

	[[eosio::action]]
	void elect(uint64_t id, double score){}

private:

	struct [[eosio::table]] record {
		uint64_t id;
		double score;
		uint64_t primary_key() const { return id; }
		double by_score() const { return score; }
	};

	typedef eosio::multi_index<"records"_n, record, indexed_by<"byscore"_n, const_mem_fun<record, double, &record::by_score>>> record_index;

};    
