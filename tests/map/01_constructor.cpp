#include "test_utils.hpp"

using namespace NAMESPACE;


bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const char& lhs, const char& rhs) const
  {return lhs<rhs;}
};

template <typename Map>
void	print (Map &x) {
	std::cout << "My map containt :";
	for (typename Map::iterator it = x.begin(); it != x.end(); it++)
		std::cout << "[" << it->first << "]" << it->second << "\n";
	std::cout << "\n";
}

int main ()
{
  map<char,int> first;

  first['a']=10;
  first['b']=30;
  first['c']=50;
  first['d']=70;

	print(first);

  map<char,int> second (first.begin(),first.end());
  print(second);

//   map<char,int> third (second);

  map<char,int,classcomp> fourth;                 // class as Compare
  print(fourth);

  bool(*fn_pt)(char,char) = fncomp;
  map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare
  print(fifth);

  return 0;
}