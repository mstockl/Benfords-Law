/* 
	Reads in a dataset from standard in, each entry on a new line, and lists
	the conformity to Benford's Law.
*/

#include <cmath>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
using namespace std;

int get_first_digit( long double i )
{
	i = abs(i);
	while ( i >= 10 ) 
		i /= 10;
	return i;
}

double benford_prediction( int i )
{
	return log10(1 + (1/double(i)));
}

void get_first_digit_count( int *digit_count, vector<string> &errors )
{
	string line;
	double value;

	stringstream ss;
	int line_num = 0;

	while ( getline(cin, line) )
	{
		++line_num;

		if ( line.empty() ) 
			continue;
		
		try
		{
			value = stold(line);
			++digit_count[get_first_digit(value) - 1];
		}
		catch( const exception& e )
		{
			ss.seekp(0);
			ss << e.what() << "[Line " << line_num 
			   << "]: Error converting line into number.";

			errors.push_back(ss.str());
		}
	}
}

void print_result( int *digit_count, const vector<string> &errors )
{
	double data_percent;
	double benfords_percent;
	unsigned long long total_data_points = 0;

	for ( int i = 0; i < 9; ++i )
		total_data_points += digit_count[i];

	cout << "┌─────────┬─────────────┬─────────────┬─────────────┐\n"
		 << "│ Digits  │ Benford %   │ Data %      │ Difference  │\n"
		 << "├─────────┼─────────────┼─────────────┼─────────────┤\n";

	for ( int i = 0; i < 9; ++i )
	{
		benfords_percent = 100*(benford_prediction(i+1));
		data_percent  = 100*(digit_count[i]/double(total_data_points));

		cout.precision(4);
		cout.flags(ios_base::fixed);
		cout << "│ " << setw(8)  << left  << i + 1 
		     << "│ " << setw(12) << right << benfords_percent
			 << "│ " << setw(12) << right << data_percent
			 << "│ " << setw(12) << right << showpos 
			         << data_percent - benfords_percent << noshowpos << "│\n";
		
		if ( i < 8 )
			cout << "├─────────┼─────────────┼─────────────┼─────────────┤\n";
		else
			cout << "└─────────┴─────────────┴─────────────┴─────────────┘\n";
	}

	if ( !errors.empty() )
	{
		cout << "\n\nERRORS:\n";
		for ( string s : errors )
			cout << s << "\n";
	}
}

int main( )
{
	vector<string> errors;
	int digit_count[9] = {0};
	
	get_first_digit_count(digit_count, errors);
	print_result(digit_count, errors);

	return EXIT_SUCCESS;
}