#include "../include/scorebook.hpp"

ACTION scorebook::elect( uint64_t id, double score ) {
	
	record_index records(get_self(), get_first_receiver().value);
	
	auto scores = records.get_index<"byscore"_n>(); 						/// load record index into a new table by score 
	auto iterator_secondary = scores.find(score);							

	auto number_of_records = std::distance(records.cbegin(),records.cend());/// current number of record
	
	check(iterator_secondary == scores.end(),"Elected score tied. Record was not added to the index."); /// check for tie
			
	if(number_of_records<15){												/// check record count		
		
		records.emplace(get_self(), [&]( auto& row ) { 						/// add record
			row.id = id;
			row.score = score;
		});	

	}
	else{
									
		iterator_secondary = scores.begin(); 
		if(score>iterator_secondary->score)  								/// check if current election is higher then the lowest
		{
			auto iterator_primary = records.find(iterator_secondary->id);	/// find the id of the lowest record
			records.erase(iterator_primary);								/// and remove it
				
			records.emplace(get_self(), [&]( auto& row ) { 					/// add the elected record
				row.id = id;
				row.score = score;
			});
		}	
	}
	
	number_of_records = std::distance(records.cbegin(),records.cend());  	/// update number of records
	print("Number of records: ",number_of_records);							/// print out number of records
}
