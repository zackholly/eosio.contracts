# Scorebook – Multi Index Exercise

This contract contains a table with two indexes, id (primary) and score (secondary). Additionally, this contract contains one action, elect. User can add elected records via the elect action. Records will be included in the record index under the following conditions:
	
* If there are fewer than 15 entries
* If the elected record has a higher score than an existing entry
	
If there is a tie, the elected record is dropped.

## Testing Plan

### Partial table test group
1. Check if record is added when:
	* less than 15 entries
2. Check if record is dropped when:
	* score is tied
				
### Full table test group
1. Check if record is added when:
	* score is higher than lowest score
	* score is highest
2. Check if record is dropped when:
	* score is lower than lowest score
	* score is tied