#include <sstream>

#include "SArgReader.h"

using std::istringstream;

SArgReader::SArgReader(int argc, char* argv[]) {
	// Grab the name of the program:
	m_name = argv[0];

	//Loop through any remaining arguments,
	// and push them onto the vector:
	for ( int i = 1; i < argc; i++ ) {
		string temp = argv[i];
		m_arguments.push_back( temp );
	}
}

bool SArgReader::peek(string& str) {
	if ( m_arguments.size() > 0 ) {
		str = m_arguments[0];
		return true;
	}
	return false;
}

bool SArgReader::peek(int& i) {
	if ( m_arguments.size() > 0 ) {
		int temp;
		if ( toInt(m_arguments[0], temp) ) {
			i = temp;
			return true;
		}
	}
	return false;
}

bool SArgReader::peek(double& d) {
	if ( m_arguments.size() > 0 ) {
		double temp;
		if ( toDouble(m_arguments[0], temp) ) {
			d = temp;
			return true;
		}
	}
	return false;
}

bool SArgReader::nextString(string & str) {
	if ( m_arguments.size() > 0 ) {
		str = m_arguments[0];
		m_arguments.erase(m_arguments.begin());
		return true;
	}
	return false;
}

bool SArgReader::nextInt(int& i) {
	if ( m_arguments.size() > 0 ) {
		int temp;
		if ( toInt(m_arguments[0], temp) ) {
			i = temp;
			m_arguments.erase(m_arguments.begin());
			return true;
		}
	}
	return false;
}

bool SArgReader::nextDouble(double& d) {
	if ( m_arguments.size() > 0 ) {
		double temp;
		if ( toDouble(m_arguments[0], temp) ) {
			d = temp;
			m_arguments.erase(m_arguments.begin());
			return true;
		}
	}
	return false;
}

bool SArgReader::flagExists() {
	if ( m_arguments.size() > 0 ) {
		if ( m_arguments[0][0] == '-' )
			return true;
	}

	return false;
}

/*  Check Flag Method
 * Checks if the provided flag is the next
 * string in the arguments list. If it is,
 * it will delete that argument from the list.
 * Return Values:
 * 	* True if argument is the next string.
 * 	* False if argument is not the next string.
 * This method will automatically add the dash
 * to the flag if the dash is not present.
 *
 * Example: if ( args.checkFlag("-debug") )
 * Example: if ( args.checkFlag("debug") )
 *
 * Requires the command line arguments to have
 * a dash. If they do not have a dash, this
 * will not be considered a flag.
 */
bool SArgReader::checkFlag(string str) {
	if ( m_arguments.size() > 0 ) {
		if ( str[0] != '-' ) {
			str.insert(0, "-");
		}
		if ( m_arguments[0] == str ) {
			m_arguments.erase(m_arguments.begin());
			return true;
		}
	}
	return false;
}

/***  STATIC MEMBER FUNCTIONS ***/
bool SArgReader::toInt(string str, int & r) {
	istringstream converter(str);

	int temp_result;
	if ( converter >> temp_result ) {
		r = temp_result;
		return true;
	}
	r = 0;
	return false;
}

bool SArgReader::toDouble(string str, double & r) {
	istringstream converter(str);

	double temp_result;
	if ( converter >> temp_result ) {
		r = temp_result;
		return true;
	}
	r = 0.0;
	return false;
}
