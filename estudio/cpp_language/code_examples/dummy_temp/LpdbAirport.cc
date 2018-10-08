/*
 * LpdbAirport.cc
 *
 */

#include "LpdbAirport.h"
//#include <LpiAdaptationAirportsInfo.h>
#include <LclogStream.h>

#include <boost/optional.hpp>

#include <iostream>
#include <algorithm> // remove and remove_if


LpdbAirport::LpdbAirport(std::string id,
			 unsigned int totalMovAirportUpperThreshold,
			 unsigned int totalMovAirportLowerThreshold,
			 unsigned int vfrAirportUpperThreshold,
			 unsigned int vfrAirportLowerThreshold,
			 unsigned int N1,
			 unsigned int taxywaysMaxNominalCapacity,
			 unsigned int tmaMaxNominalCapacity)
  : theAirportName(id),
    theTotalMovAirportUpperThreshold(totalMovAirportUpperThreshold / N1),
    theTotalMovAirportLowerThreshold(totalMovAirportLowerThreshold / N1),
    theVfrAirportUpperThreshold(vfrAirportUpperThreshold / N1),
    theVfrAirportLowerThreshold(vfrAirportLowerThreshold / N1),
    the_twyNominalCapacity(taxywaysMaxNominalCapacity), // error:   / N1),
    the_tmaNominalCapacity(tmaMaxNominalCapacity)
{
}

std::string LpdbAirport::getAirportId() const { return theAirportName; }

unsigned int LpdbAirport::getTotalMovAirportUpperThreshold()const
{return theTotalMovAirportUpperThreshold; }

unsigned int LpdbAirport::getTotalMovAirportLowerThreshold()const
{return theTotalMovAirportLowerThreshold; }

unsigned int LpdbAirport::getVfrAirportUpperThreshold()const
{ return theVfrAirportUpperThreshold; }

unsigned int LpdbAirport::getVfrAirportLowerThreshold()const
{ return theVfrAirportLowerThreshold; }


void LpdbAirport::setAirportId(std::string id)
{
  theAirportName = id;
}


void LpdbAirport::forwardTimeline()
{
  forwardTimeLineMeteo();
  forwardTimeLineDemand();
  forwardCapacity();
}


////////////////////////////////////////
/// Capacity data
////////////////////////////////////////

unsigned int LpdbAirport::get_taxywaysNominalCapacity()const
{ return the_twyNominalCapacity; }

unsigned int LpdbAirport::get_tmaNominalCapacity()const
{ return the_tmaNominalCapacity; }

void LpdbAirport::initCapacity(const LpiTimeParameters & timeData,
		const boost::posix_time::ptime &now)
{
  the_tma.init(timeData, now, get_tmaNominalCapacity());
  the_twy.init(timeData, now, get_taxywaysNominalCapacity());


#ifdef TRACE_OUT
  LclogStream::instance(LclogConfig::E_RTP).debug()
    << "AFTER: init capacity on airport <" << getAirportId() << '>'
    << " ; TMA intervals = " << getTMA().getTimeLine().getNumberOfElements()
    << " ; last interval id = " << getTMA().getTimeLine().getLastInterval()
    << " ; TMA intervals = " << getTWY().getTimeLine().getNumberOfElements()
    << " ; last interval id = " << getTWY().getTimeLine().getLastInterval()
    << " ; File: " << __FILE__
    << " ; fn: " << __func__
    << " ; line: " << __LINE__
    << std::endl;
#endif

}

void LpdbAirport::forwardCapacity()
{
#ifdef TRACE_OUT
  LclogStream::instance(LclogConfig::E_RTP).debug()
    << "BEFORE: Forward capacity on airport <" << getAirportId() << '>'
    << " ; TMA intervals = " << getTMA().getTimeLine().getNumberOfElements()
    << " ; last interval id = " << getTMA().getTimeLine().getLastInterval()
    << " ; TMA intervals = " << getTWY().getTimeLine().getNumberOfElements()
    << " ; last interval id = " << getTWY().getTimeLine().getLastInterval()
    << " ; File: " << __FILE__
    << " ; fn: " << __func__
    << " ; line: " << __LINE__
    << std::endl;
#endif


  the_tma.forward();
  the_twy.forward();


#ifdef TRACE_OUT
  LclogStream::instance(LclogConfig::E_RTP).debug()
    << "AFTER: Forward capacity on airport <" << getAirportId() << '>'
    << " ; TMA intervals = " << getTMA().getTimeLine().getNumberOfElements()
    << " ; last interval id = " << getTMA().getTimeLine().getLastInterval()
    << " ; TMA intervals = " << getTWY().getTimeLine().getNumberOfElements()
    << " ; last interval id = " << getTWY().getTimeLine().getLastInterval()
    << " ; File: " << __FILE__
    << " ; fn: " << __func__
    << " ; line: " << __LINE__
    << std::endl;
#endif
}



////////////////////////////////////////
/// Meteo data
////////////////////////////////////////


unsigned int LpdbAirport::getNumberOfMeteoReportsReceived ()// const
{
   return r_meteoReports.size();
}


std::vector<LpiMeteoInfo> LpdbAirport::getReceivedMeteoReports () //const
{
   return r_meteoReports;
}

///@warning: assert index < getNumberOfMeteoReportsReceived() before call
LpiMeteoInfo LpdbAirport::getMeteoReport (const unsigned int index)
{
	assert(index < getNumberOfMeteoReportsReceived());
	return r_meteoReports[index];
}


void LpdbAirport::addMeteoReport (const LpiMeteoInfo &report)
{
   r_meteoReports.push_back(report);
}

void LpdbAirport::deleteMeteoReport (unsigned int index)
{
   if (index < r_meteoReports.size())
   {
      r_meteoReports.erase(r_meteoReports.begin() + index);
   }
}

void LpdbAirport::deleteObsoleteMeteoReports()
{
  auto condition = [this](const LpiMeteoInfo &meteo )
  {
    return  ( getMeteoForecast().getInitialTime().is_initialized() and
	      (meteo.getEndTimeAndDate() <= getMeteoForecast().getInitialTime().get()) );
  };

  r_meteoReports.erase( std::remove_if(r_meteoReports.begin(), r_meteoReports.end(), condition), r_meteoReports.end() );
}


/**@warning getLastReceivedMeteoReport: UNUSED in RMAN
boost::optional<LpiMeteoInfo> LpdbAirport::getLastReceivedMeteoReport () const
{
   boost::optional<LpiMeteoInfo> meteo_report;

   if (r_meteoReports.size() > 0)
   {
      int last_element = r_meteoReports.size() - 1;
      meteo_report = r_meteoReports[last_element];
   }

   return meteo_report;
}
*/


void LpdbAirport::forwardTimeLineMeteo()
{
#ifdef TRACE_OUT
  LclogStream::instance(LclogConfig::E_RTP).debug()
    << "BEFORE: Forward meteo on airport <" << getAirportId() << '>'
	<< " ; number of intervals = " << getMeteoForecast().getNumberOfElements()
	<< " ; last interval id = " << getMeteoForecast().getLastInterval()
    << " ; File: " << __FILE__
    << " ; fn: " << __func__
    << " ; line: " << __LINE__
    << std::endl;
#endif

  r_meteoLine.forward();
  
  //   Creates default element in newly created interval
  r_meteoLine.createElement(r_meteoLine.getLastInterval());


#ifdef TRACE_OUT
  LclogStream::instance(LclogConfig::E_RTP).debug()
    << "AFTER: Forward meteo on airport <" << getAirportId() << '>'
	<< " ; number of intervals = " << getMeteoForecast().getNumberOfElements()
	<< " ; last interval id = " << getMeteoForecast().getLastInterval()
    << " ; File: " << __FILE__
    << " ; fn: " << __func__
    << " ; line: " << __LINE__
    << std::endl;
#endif
}


////////////////////////////////////////
/// Demand data
////////////////////////////////////////


void LpdbAirport::forwardTimeLineDemand()
{
  r_demand.forward();

}

////////////////////////////////////////
std::ostream& operator<<(std::ostream & os, const LpdbAirport & obj)
{
   return os << "[ID: " << obj.getAirportId() 
	     << " | totalMovAirportUpperThreshold: "
	     << obj.getTotalMovAirportUpperThreshold()
	     << " | totalMovAirportLowerThreshold: "
	     << obj.getTotalMovAirportLowerThreshold()
	     << " | VfrAirportUpperThreshold: "
	     << obj.getVfrAirportUpperThreshold()
	     << " | VfrAirportLowerThreshold: "
	     << obj.getVfrAirportLowerThreshold()
             << ']';
}
