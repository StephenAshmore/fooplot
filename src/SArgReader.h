#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::cerr;
using std::endl;

class SArgReader {
	private:
		vector<string> m_arguments;
		string m_name;
	
	public:
		// Member Constructors/Destructors:
		SArgReader(int argc, char* argv[]);
		~SArgReader() { m_arguments.clear(); }
		
		// Member Methods:
		string getName() { return m_name; }
		// Peek Overloaded:
		bool peek(string&);
		bool peek(int& i);
		bool peek(double& d);
		
		bool nextString(string &);
		bool nextInt(int&);
		bool nextDouble(double&);
		
		void remove() { m_arguments.erase(m_arguments.begin()); }
		
		bool checkFlag(string str);
		bool empty() { return m_arguments.size() == 0; }
		int size() { return m_arguments.size(); }
		bool flagExists();
		
		// STATIC MEMBER METHODS:
		static bool toInt(string str, int & r);
		static bool toDouble(string str, double & r);
};