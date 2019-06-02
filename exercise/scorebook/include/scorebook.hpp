#include <eosio/eosio.hpp>

using namespace eosio;

class [[eosio::contract("scorebook")]] scorebook : public eosio::contract {

public:
  
	scorebook(name receiver, name code,  datastream<const char*> ds): contract(receiver, code, ds){}

	[[eosio::action]]
	void elect(uint64_t id, double score){
	
		static uint8_t record_count = 0;
		
		record_index records(get_self(), get_first_receiver().value);
		
		auto scores = records.get_index<"byscore"_n>();
		auto iterator_secondary = scores.find(score);
		check(iterator_secondary == scores.end(),"Elected score tied. Record was not added to the index."); 
			
		if(record_count<15){	/// check record count
				
			records.emplace(get_self(), [&]( auto& row ) { /// add record
				row.id = id;
				row.score = score;
			});	
				
				++record_count;
			print(record_count);
		}
		else{
									
			iterator_secondary = scores.begin();
			if(score>iterator_secondary->score)
			{
				auto iterator_primary = records.find(iterator_secondary->id);
				records.erase(*iterator_primary);
				
				records.emplace(get_self(), [&]( auto& row ) { /// add record
					row.id = id;
					row.score = score;
				});
			}	
		}
	}	

private:

	
	struct [[eosio::table]] record {
		uint64_t id = 0;
		double score =0;
		uint64_t primary_key() const { return id; }
		double by_score() const { return score; }
	};

	typedef eosio::multi_index<"records"_n, record, indexed_by<"byscore"_n, const_mem_fun<record, double, &record::by_score>>> record_index;

};    
