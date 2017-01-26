#ifndef BASE_UNITS_HEADER_
#define BASE_UNITS_HEADER_

#include "../base/INDAR.h"

#include "base.h"
#include <cmath>

//rmarin: check this designation
#undef min  //min definition, VXWORKS function, is cleared

BEGIN_NAMESPACE_INDAR


/* This package defines units of measurement, and functions to handle them
 * and for converting values among different units. The units can be
 * multiplied and divided by one another, and they can be raised to a power.
 * Also, they can be premultiplied by scalars (1000*m=km). The conversions
 * verify the compatibility of the units. See "unidtest.cpp" for examples.
 *
 * Temperature units can be treated as differences among temperatures
 * (0 degrees Celsius corresponding to 0 degress Kelvin) using the units
 * names "K", "degree_C", "degree_F" and "degree_R", or as the temperatures
 * per se (0 degrees Celsius corresponding to 273.15 degrees Kelvin),
 * using the temperatures names "temperature_K", "temperature_C",
 * "temperature_F", "temperature_R". */

namespace Units {

   template <signed int M,
             signed int L,
             signed int T,
             signed int theta>
     class Unit {
      public:
	Unit(unchecked_scalar magnitude_) // into SI units
	  : magnitude(magnitude_) { };
	unchecked_scalar magnitude;
     };

   class Unit_temperature {
    public:
      Unit_temperature(unchecked_scalar magnitude_, // into K
			 unchecked_scalar zero_) // into K
	: magnitude(magnitude_), zero(zero_) { };
      unchecked_scalar magnitude;
      unchecked_scalar zero;
   };


   template <signed int M,
             signed int L,
             signed int T,
             signed int theta>
     Unit<M, L, T, theta> const
     operator*(unchecked_scalar k, Unit<M, L, T, theta> u)
     { return Unit<M, L, T, theta>(k*u.magnitude); }


     template
       <signed int M_1, signed int L_1, signed int T_1, signed int theta_1,
        signed int M_2, signed int L_2, signed int T_2, signed int theta_2>
     struct UnitProduct {
       typedef Unit<M_1+M_2, L_1+L_2, T_1+T_2, theta_1+theta_2> Result;
     };
     template <signed int M_1,
             signed int L_1,
             signed int T_1,
             signed int theta_1,
             signed int M_2,
             signed int L_2,
             signed int T_2,
             signed int theta_2>
     typename
     UnitProduct<M_1, L_1, T_1, theta_1, M_2, L_2, T_2, theta_2>::Result const
     operator*(Unit<M_1, L_1, T_1, theta_1> u_1,
	       Unit<M_2, L_2, T_2, theta_2> u_2)
     {
	return Unit<M_1+M_2, L_1+L_2, T_1+T_2, theta_1+theta_2>
	  (u_1.magnitude*u_2.magnitude);
     }

     template
       <signed int p,
        signed int M, signed int L, signed int T, signed int theta>
     struct UnitPower {
       typedef Unit<p*M, p*L, p*T, p*theta> Result;
     };
     template <signed int p,
             signed int M,
             signed int L,
             signed int T,
             signed int theta>
     typename
     UnitPower<p, M, L, T, theta>::Result const
     pot(Unit<M, L, T, theta> u)
     { return Unit<p*M, p*L, p*T, p*theta>(pow(u.magnitude, p)); }


     template
       <signed int M_1, signed int L_1, signed int T_1, signed int theta_1,
        signed int M_2, signed int L_2, signed int T_2, signed int theta_2>
     struct UnitQuotient {
       typedef Unit<M_1-M_2, L_1-L_2, T_1-T_2, theta_1-theta_2> Result;
     };
     template <signed int M_1,
             signed int L_1,
             signed int T_1,
             signed int theta_1,
             signed int M_2,
             signed int L_2,
             signed int T_2,
             signed int theta_2>
     typename
     UnitQuotient<M_1, L_1, T_1, theta_1, M_2, L_2, T_2, theta_2>::Result const
     operator/(Unit<M_1, L_1, T_1, theta_1> u_1,
	       Unit<M_2, L_2, T_2, theta_2> u_2)
     {
	return Unit<M_1-M_2, L_1-L_2, T_1-T_2, theta_1-theta_2>
                     (u_1.magnitude/u_2.magnitude);
     }

   template <class Type,
             signed int M,
             signed int L,
             signed int T,
             signed int theta>
     Type convert(Type const &value,
			  Unit<M, L, T, theta> unit_origin,
			  Unit<M, L, T, theta> unit_destination)
     {
	return (unit_origin.magnitude/unit_destination.magnitude)*value;
     }

   template <signed int M,
             signed int L,
             signed int T,
             signed int theta>
     unchecked_scalar  convert(int const &value,
                               Unit<M, L, T, theta> unit_origin,
                               Unit<M, L, T, theta> unit_destination)
     {
	return convert(unchecked_scalar(value),
			 unit_origin, unit_destination);
     }

   template <class Type,
             signed int M,
             signed int L,
             signed int T,
             signed int theta>
     Type convert_from_si(Type const &value,
                     Unit<M, L, T, theta> unit_destination)
     { return convert(value, Unit<M, L, T, theta>(1.), unit_destination); }

   template <signed int M,
             signed int L,
             signed int T,
             signed int theta>
     unchecked_scalar convert_from_si(int const &value,
                                      Unit<M, L, T, theta> unit_destination)
     { return convert_from_si(unchecked_scalar(value), unit_destination); }

   template <class Type,
             signed int M,
             signed int L,
             signed int T,
             signed int theta>
     Type convert_to_si(Type const &value,
                     Unit<M, L, T, theta> unit_origin)
     { return convert(value, unit_origin, Unit<M, L, T, theta>(1.)); }

   template <signed int M,
             signed int L,
             signed int T,
             signed int theta>
     unchecked_scalar convert_to_si(int const &value,
                                    Unit<M, L, T, theta> unit_origin)
     { return convert_to_si(unchecked_scalar(value), unit_origin); }

   template <class Type>
     Type convert(Type const &value,
			  Unit_temperature unit_origin,
			  Unit_temperature unit_destination)
     {
	return
	  (unit_origin.magnitude*value+unit_origin.zero-unit_destination.zero)
	  /unit_destination.magnitude;
     }

   inline unchecked_scalar convert(int const &value,
                                   Unit_temperature unit_origin,
                                   Unit_temperature unit_destination)
     {
	return convert(unchecked_scalar(value),
			 unit_origin, unit_destination);
     }

   template <class Type>
     Type convert_from_si(Type const &value,
			  Unit_temperature unit_destination)
   { return convert(value, Unit_temperature(1., 0.), unit_destination); }

   template <class Type>
     Type convert_to_si(Type const &value,
                        Unit_temperature unit_origin)
   { return convert(value, unit_origin, Unit_temperature(1., 0.)); }

   /// debugging
   extern
   scalar convert_non_templated_debug(scalar value,
                                      scalar unit_origin_magnitude,
                                      scalar unit_destination_magnitude);
   extern
   scalar convert_from_si_non_templated_debug(
     scalar value,
     scalar unit_destination_magnitude);

   extern
   scalar convert_to_si_non_templated_debug(
     scalar value,
     scalar unit_origin_magnitude);

   typedef Unit<0, 0, 0, 0> Unit_nondim;
   typedef Unit<1, 0, 0, 0> Unit_mass;
   typedef Unit<0, 1, 0, 0> Unit_lenght;
   typedef Unit<0, 0, 1, 0> Unit_time;
   typedef Unit<0, 0, 0, 1> Unit_temperature_interval;

   typedef Unit<0, 0, 0, 0>   Unit_angle;
   typedef Unit<0, 2, 0, 0>   Unit_surface;
   typedef Unit<0, 3, 0, 0>   Unit_volume;
   typedef Unit<0, 0, -1, 0>  Unit_frequency;
   typedef Unit<0, 0, -1, 0>  Unit_angular_velocity;
   typedef Unit<0, 1, -1, 0>  Unit_velocity;
   typedef Unit<0, 1, -2, 0>  Unit_acceleration;
   typedef Unit<1, 1, -2, 0>  Unit_force;
   typedef Unit<1, 2, -2, 0>  Unit_moment;
   typedef Unit<1, -1, -2, 0> Unit_pressure;
   typedef Unit<1, 2, -3, 0>  Unit_power;
   typedef Unit<1, -3, 0, 0>  Unit_density;

   // multiplicative prefixes
   // bigger than kilo: with capital letter
   unchecked_scalar const Exa= 1e18;
   unchecked_scalar const Peta=1e15;
   unchecked_scalar const Tera=1e12;
   unchecked_scalar const Giga=1e9;
   unchecked_scalar const Mega=1e6;

   // deca, hecto and kilo: with lower-case letter
   unchecked_scalar const kilo=1000;
   unchecked_scalar const hecto=100;
   unchecked_scalar const deca=  10;

   // divisor prefixes
   // all with lower-case letter
   unchecked_scalar const deci=  .1;
   unchecked_scalar const centi=.01;
   unchecked_scalar const mili=.001; // FIXME: typo
   unchecked_scalar const milli=.001;
   unchecked_scalar const micro=1e-6;
   unchecked_scalar const nano= 1e-9;
   unchecked_scalar const pico= 1e-12;
   unchecked_scalar const femto=1e-15;

   unchecked_scalar const percent=centi;

   // units
   Unit_nondim const one(1); //non-dimensional unit

   Unit_mass const kg(1); // kilograms; basic
   Unit_mass const g(.001); // grams
   Unit_mass const lb(0.45359237); // pounds
   Unit_mass const slug(14.5939029); // slugs

   Unit_lenght const m(1); // meters; basic
   Unit_lenght const km(1000); // kilometers
   Unit_lenght const dm(.1); // decimeters
   Unit_lenght const cm(.01); // centimeters
   Unit_lenght const mm(.001); // milimeters
   Unit_lenght const ft(0.3048);  // feet
   Unit_lenght const in(0.0254); // inches
   Unit_lenght const n_mile(1852); // nautical miles
   Unit_lenght const parsec(30.857e15); // parsecs

   Unit_time const s(1); // seconds; basic
   Unit_time const min(60); // minutes
   Unit_time const h(60*60); // hours
   Unit_time const day(24*60*60); // days
   Unit_time const mean_gregorian_year(365.2425*24*60*60); // years

   Unit_temperature_interval const K(1); // degrees Kelvin; basic
   Unit_temperature_interval const degree_C(1); // degrees Celsius (interval)
   Unit_temperature_interval const degree_F(1./1.8);
                                               // degrees Fahrenheit (interval)
   Unit_temperature_interval const degree_R(1./1.8);
                                                  // degrees Rankine (interval)

   /* revolution is taken as basic in order to match the conversion of
    * revolutions per minute to radians per second */
   Unit_angle const revolution(1); // revolution; taken as basic
   Unit_angle const rad(1./(2*PI)); // radians
   Unit_angle const deg(1./(360.)); // sexagesimal degrees

   Unit_volume const l(.001); // litres
   Unit_volume const L(l); // synonym for "l"
   Unit_volume const gal_UK(0.004546087); // English liquid gallons
   Unit_volume const gal_US(0.003785412); // US-American liquid gallons
   Unit_volume const quart_US(convert(1./4., gal_US, pot<3>(m))); // quart

   Unit_frequency const Hz(1); // hertzes
   Unit_frequency const rpm(1./60.); // revolutions per minute

   Unit_velocity const kt(0.514444); // knots
   Unit_velocity const fpm(convert(1, ft/min, m/s)); // feet per minute

   Unit_force const N(1); // newtons
   Unit_force const kp(9.80665); // kiloponds
   Unit_force const kgf(convert(1, kp, N)); // kilograms force
   Unit_force const lbf(4.448221615); // pounds force

   Unit_acceleration const g_acceleration(1*kp/kg);

   Unit_pressure const Pa(1); // pascals
   Unit_pressure const bar(100000.0); // bars
   Unit_pressure const mbar(100.0); // mbars
   Unit_pressure const atm(101325.); // atmospheres
   Unit_pressure const mmHg(133.3224); // millimeters of mercury
   Unit_pressure const inHg(3386.38815789); // inches of mercury
   Unit_pressure const psi(convert(1, lbf/pot<2>(in), Pa));
			                  // pounds force per square inch
   Unit_pressure const psf(convert(1, lbf/pot<2>(ft), Pa));
			                  // pounds force per square foot

   Unit_power const W(1); // watts
   Unit_power const hp(745.699871582); // horsepower

   // units for temperature conversion
   Unit_temperature const temperature_K(1, 0); // degrees Kelvin
   Unit_temperature const temperature_C(1, 273.15); // degrees Celsius
   Unit_temperature const temperature_F(1./1.8, 273.15-32./1.8);
                                                           // degrees Fahrenheit
   Unit_temperature const temperature_R(1./1.8, 0); // degrees Rankine

  namespace Rad { // the world as it should be: angles in radians
    Unit_angle const rad(1.); // radians; taken as basic
    Unit_angle const revolution(2.*PI); // revolution; taken as basic
    Unit_angle const deg(2.*PI/360.); // sexagesimal degrees
    Unit_frequency const rpm(2.*PI/60.); // revolutions per minute
  }
}

END_NAMESPACE_INDAR

#endif
