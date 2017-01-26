#include "units.h"

#include <iostream>

USING_NAMESPACE_INDRA

using namespace Units;
using std::cout;
using std::endl;

int main()
{
   cout << "1 lb -> kg: " << convert(1., lb, kg) << endl;
   cout << "2 lb -> kg: " << convert(2., lb, kg) << endl;
   cout << "4 kb -> lb: " << convert(4., kg, lb) << endl;
   cout << "1 kt -> m/s: " << convert(1, kt, m/s) << endl;
   cout << "1.5 ft² -> in²: " << convert(1.5, ft*ft, in*in) << endl;
   cout << "1.5 ft² -> in²: " << convert(1.5, pot<2>(ft), pot<2>(in)) << endl;
   cout << "10 fpm -> km/h: " << convert(10, fpm, km/h) << endl;
   cout << "1 psi -> Pa: " << convert(1, psi, Pa) << endl;
   cout << "1 rpm -> rad/s: " << convert(1, rpm, rad*pot<-1>(s)) << endl;
   cout << "1 (kilo*m) -> m: " << convert(1, kilo*m, m) << endl;

   cout << "1 lb -> SI: " << convert_to_si(1, lb) << endl;
   cout << "1 lb -> SI: " << convert_to_si(1., lb) << endl;
   cout << "1 SI -> lb: " << convert_from_si(1, lb) << endl;
   cout << "1 SI -> lb: " << convert_from_si(1., lb) << endl;
}

