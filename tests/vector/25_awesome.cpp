#include "test_utils.hpp"

using namespace NAMESPACE;

class Awesome {

	public:

		Awesome(void) : _n( new int(42) ) { std::cout << "Hello !" << std::endl; }
		Awesome( int n ) : _n( new int(n) ) { std::cout << "Hello !" << std::endl; (void)n;}
		virtual ~Awesome(void) { std::cout << "Goodbye !" << std::endl; }

		bool operator==( Awesome const & rhs ) const { return (this->_n == rhs._n); }
		bool operator!=( Awesome const & rhs ) const { return (this->_n != rhs._n); }
		bool operator>( Awesome const & rhs ) const { return (this->_n > rhs._n); }
		bool operator<( Awesome const & rhs ) const { return (this->_n < rhs._n); }
		bool operator>=( Awesome const & rhs ) const { return (this->_n >= rhs._n); }
		bool operator<=( Awesome const & rhs ) const { return (this->_n <= rhs._n); }
		int get( void ) const { return *this->_n; }

	private:

		int *_n;
};

std::ostream & operator<<( std::ostream & o, Awesome const & rhs ) { o << rhs.get(); return o; }

int main()
{
	vector<int> test;

	for (size_t i = 0; i < 51; i++)
		test.push_back(1);
	test.resize(72);
	test.resize(100);
	test.resize(4170);
	test.resize(171, 12);
	std::cout << test[72] << std::endl;
	std::cout << test[170] << std::endl;
	test.resize(62);
	test.insert(test.begin(), 200, 12);
	vector<int> test2(1, 1);
	vector<int> test3(12, 12);
	vector<int> test4(65, 65);
	test4.reserve(12);
	test4.reserve(66);
	test4.reserve(128);
	test4.reserve(1023);
	test4.reserve(10252);
	vector<int> test5(test);
	test4.swap(test3);
	test4.erase(test4.begin(), test4.begin() + 5);
	test4.clear();
	std::cout << test.max_size() << std::endl;
	std::cout << test2.max_size() << std::endl;
	std::cout << test3.max_size() << std::endl;
	std::cout << test4.max_size() << std::endl;
	std::cout << test5.max_size() << std::endl;
	vector<Awesome> test6(21, 12);
}