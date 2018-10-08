/*
 * LpdbTMA.h
 *
 */

#include "LpdbTMA.h"
#include <LpiIncreasingReductionFunction.h>

#ifdef TRACE_OUT
#include <LclogStream.h>
#endif

#include <iostream>
#include <cmath>
#include <algorithm>    // std::for_each


bool LpdbTMA::has_data(const string& interval_name)
{
   return r_timeLine.hasData(interval_name);
}


LpdbTMATimedData& LpdbTMA::operator [](const string& interval_name)
{
   return r_timeLine[interval_name];
}


void LpdbTMA::init(const LpiTimeParameters & parameters,
		   boost::posix_time::ptime begin_timestamp,
		   const unsigned int tmaNominalCapacity)
{

#ifdef TRACE_OUT
  LclogStream::instance(LclogConfig::E_RTP).debug()
    << " : File: " << __FILE__
    << " ; fn: " << __func__
    << " ; line: " << __LINE__
    << std::endl;
#endif

  r_tmaNominal = tmaNominalCapacity; 

  r_timeLine.initialize(parameters.getMinutesSubinterval(),
			parameters.getHoursWindow(),
			parameters.getMinutesFrozen(),
			begin_timestamp);
   r_timeLine.fill();
}


void LpdbTMA::forward()
{

#ifdef TRACE_OUT
  LclogStream::instance(LclogConfig::E_RTP).debug()
    << " : File: " << __FILE__
    << " ; fn: " << __func__
    << " ; line: " << __LINE__
    << std::endl;
#endif

   r_timeLine.forward();

   //Creates default element in newly created interval
   r_timeLine.createElement(r_timeLine.getLastInterval());
}

TimeLine<LpdbTMATimedData> & LpdbTMA::getTimeLine()
{
   return r_timeLine;
}

std::string LpdbTMA::getIntervalsShortFormat () const
{
   return r_timeLine.getIntervalsShortFormat();
}


std::string LpdbTMA::getIntervalsAsString () const
{
   return r_timeLine.getAsString();
}


void LpdbTMA::calculateCapacity()
{

#ifdef TRACE_OUT
  LclogStream::instance(LclogConfig::E_RTP).debug()
    << " : File: " << __FILE__
    << " ; fn: " << __func__
    << " ; line: " << __LINE__
    << std::endl;
#endif

   // std::vector<string> intervals = r_timeLine.getAllIntervalIds();
   // BOOST_FOREACH (string interval_id, intervals)
   // {
   //   calculateCapacity(interval_id);
   // }

  std::for_each(std::begin(r_timeLine.getAllIntervalIds()),
		std::end(r_timeLine.getAllIntervalIds()),
		calculateCapacity);
}


void LpdbTMA::calculateCapacity(string interval)
{

#ifdef TRACE_OUT
  LclogStream::instance(LclogConfig::E_RTP).debug()
    << " ; interval: " << interval
    << " : File: " << __FILE__
    << " ; fn: " << __func__
    << " ; line: " << __LINE__
    << std::endl;
#endif

  if (has_data(interval))
  {
    LpdbTMATimedData & tma_data = r_timeLine[interval];
    tma_data.calculateCapacity(r_timeLine.getNumberOfIntervalsPerHour(), 
			       r_tmaNominal);
  }
}

//------------------------------------------------------------------------------

///compilation error: passing ‘const LpdbTMA’ as ‘this’ argument of
///‘TimeLine<LpdbTMATimedData>& LpdbTMA::getTimeLine()’ discards
///qualifiers
///
/// must be LpdbTMA & info
///
// std::ostream & operator<<(std::ostream & os, const LpdbTMA & info)
// {
//   return os << "nominal_tma: " << info.getNominalTMA()
// 	    << " | timeline: " << info.getTimeLine()
// 	    << ']';
// }
