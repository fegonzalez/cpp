#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>

/*
Now, in the directory where you saved example.cpp, issue the following command:

c++ -I path/to/boost_1_64_0 example.cpp -o example

i.e. c++ -I $BOOST_ROOT example.cpp -o example


To test the result, type:

echo 1 2 3 | ./example

 */
int main()
{
    using namespace boost::lambda;
    typedef std::istream_iterator<int> in;

    std::for_each(in(std::cin), 
		  in(), 
		  std::cout << (_1 * 3) << " " );
}

