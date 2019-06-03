#include <eosio/eosio.hpp>

using namespace eosio;

CONTRACT scorebook : public contract {
public:
    
	using contract::contract;
	
    ACTION elect( uint64_t id, double score );
	
private:
	
	struct [[eosio::table]] record {
	uint64_t id = 0;
	double score =0;
	uint64_t primary_key() const { return id; }
	double by_score() const { return score; }
	};
	
	typedef eosio::multi_index<"records"_n, record, indexed_by<"byscore"_n, const_mem_fun<record, double, &record::by_score>>> record_index;
	
};