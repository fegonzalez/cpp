/*
 * LpdBusinessLogicFacade.h
 *
 * DOC Reference: [1] "RTP Diseño Funcional.docx"
 *
 */
#include <LplcTypeConstants.h>

#include "LpdBusinessLogicFacade.h"
#include <LpschDynamicDemandSchedulesGenerator.h>
#include "LpdComponent.h"
#include <LpiADOVector.h>
#include <LpdbDemand.h>
#include <LpdbDataBase.h>
#include <LpdbMeteoTimedData.h>
#include "LpdbRunwayIntervalKPIs.h"
#include "LpdbAirportIntervalKPIs.h"
#include <LpdbScheduleConverter.h>
#include <LpdbMeteoTimelineConverter.h>
#include <LpiRunwayMeteoInfo.h>
#include <LctimVirtualClock.h>
#include <LpdbRunwaySystemsMemento.h>

#include <LclogStream.h>

#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <iterator>
#include <cassert>
#include <algorithm>    // std::for_each


#include <boost/foreach.hpp>
#include <boost/optional.hpp>
#include <boost/math/distributions/normal.hpp>

//For random numbers generation (only for testing)
#include <boost/random/random_device.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>

#include <boost/algorithm/string/trim.hpp>

//For execution time measuring
#include <boost/chrono/thread_clock.hpp>

using std::vector;
using std::string;

LpdBusinessLogicFacade::LpdBusinessLogicFacade()
        : _schedules_generator(LpschDynamicDemandSchedulesGenerator::Get())
{
}

LpdBusinessLogicFacade::~LpdBusinessLogicFacade()
{
}

void LpdBusinessLogicFacade::getSystemTime(LpiTime &tick, LpiResult &result)
{
    LpdComponent::Get().getSystemTime(tick, result);
}

void LpdBusinessLogicFacade::getConfigurationCoreParameters(LpiConfigurationCoreParameters &parameters, LpiResult &result)
{
    LpdComponent::Get().getConfigurationCoreParameters(parameters, result);
}

void LpdBusinessLogicFacade::getConfigurationHmiParameters(LpiConfigurationHmiParameters &parameters, LpiResult &result)
{
    LpdComponent::Get().getConfigurationHmiParameters(parameters, result);
}

void LpdBusinessLogicFacade::getAdaptationMrtmInfo(LpiAdaptationMrtmInfo &mrtm_info, LpiResult & result)
{
    LpdComponent::Get().getAdaptationMrtmInfo(mrtm_info, result);
}

void LpdBusinessLogicFacade::getAdaptationAssignmentPreference(LpiAdaptationAssignmentPreference &ass_pref, LpiResult & result)
{
    LpdComponent::Get().getAdaptationAssignmentPreference(ass_pref, result);
}

void LpdBusinessLogicFacade::getAdaptationRunway(LpiAdaptationRunwayList & runways, LpiResult & result)
{
    LpdComponent::Get().getAdaptationRunway(runways, result);
}

void LpdBusinessLogicFacade::getAdaptationRunwaySystem(LpiAdaptationRunwaySystemList & runway_systems,
                                                       LpiResult & result)
{
    LpdComponent::Get().getAdaptationRunwaySystem(runway_systems, result);
}

void LpdBusinessLogicFacade::getAdaptationAlert_KPIs(LpiAdaptationAlert_KPIs &configurationAlert_KPIs,
                                                       LpiResult &result)
{
    LpdComponent::Get().getAdaptationAlert_KPIs(configurationAlert_KPIs, result);

}

void LpdBusinessLogicFacade::getAdaptationAirportsInfo(LpiAdaptationAirportsInfo &airportsInfo, LpiResult & result)
{
    LpdComponent::Get().getAdaptationAirportsInfo(airportsInfo, result);
}

void LpdBusinessLogicFacade::getPriorityTableDepartures(LpiPriorityTable & priorities, LpiResult & result)
{
    LpdComponent::Get().getPriorityTableDepartures(priorities, result);
}

void LpdBusinessLogicFacade::getPriorityTableArrivals(LpiPriorityTable & priorities, LpiResult & result)
{
    LpdComponent::Get().getPriorityTableArrivals(priorities, result);
}

void LpdBusinessLogicFacade::getWakeVortexCapacityReductions(
                                  LpiWakeVortexCapacityReductions &capacity,
                                  LpiResult & result)
{
   LpdComponent::Get().getWakeVortexCapacityReductions(capacity, result);
}

void LpdBusinessLogicFacade::create(void)
{
}

void LpdBusinessLogicFacade::initialise(void)
{

#ifdef TRACE_OUT
  LclogStream::instance(LclogConfig::E_RTP).info()
    << "TODO: RTP Server's Business Logic initialization." 
    << " : File: " << __FILE__
    << " ; fn: " << __func__
    << " ; line: " << __LINE__ 
    << std::endl;
#endif


#ifdef TRACE_OUT
  LclogStream::instance(LclogConfig::E_RTP).debug() 
    << "STEP-1: Get necessary data to initialize database tables..." 
    << std::endl;
#endif

    //Get necessary data to initialize database tables:
    //Timelines, Runways, Runway Systems
    LpiResult result;

    //Configuration

#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).debug() 
      << "STEP-1-a: CONFIG parameters..." << std::endl;
#endif

#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).debug() 
      << "Business Logic: getConfigurationCoreParameters "
      << "(DAORTP_Parameters.xml => daortp_coreparameters_xsd.h => "
      << "LpiConfigurationCoreParameters) ..."
      << std::endl;
#endif
    LpiConfigurationCoreParameters config_core_parameters;
    getConfigurationCoreParameters(config_core_parameters, result);
    assert(result.getResult() == LpiResult::LpiEnum::E_OK);


    //@warning getConfigurationHmiParameters NO se hace en RMAN
#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).debug() 
      << "Business Logic: getConfigurationHmiParameters..." << std::endl;
#endif
    LpiConfigurationHmiParameters config_hmi_parameters;
    getConfigurationHmiParameters(config_hmi_parameters, result);



    //Adaptation

#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).debug() 
      << "STEP-1-b: ADAP parameters..." << std::endl;
#endif


#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).debug() 
      << "Business Logic: getAdaptationMrtmInfo..."
      << rtp_constants::FILENAME_DAORTP_MRTM_INFO
      << "=> daortp_smmrtminfo_xsd.h => LpiAdaptationMrtmInfo) ..." << std::endl;
#endif
    LpiAdaptationMrtmInfo mrtm_info;            // RTP only
    getAdaptationMrtmInfo(mrtm_info, result);


#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).debug() 
      << "Business Logic: getAdaptationAirportsInfo(..." << std::endl;
#endif
    LpiAdaptationAirportsInfo airports_info;
    getAdaptationAirportsInfo(airports_info, result);


#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).debug() 
      << "Business Logic: getPriorityTableDepartures..." << std::endl;
#endif
    LpiPriorityTable priority_table_dep;
    getPriorityTableDepartures(priority_table_dep, result);
#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).debug() 
      << "Business Logic: getPriorityTableArrivals..." << std::endl;
#endif
    LpiPriorityTable priority_table_arr;
    getPriorityTableArrivals(priority_table_arr, result);


#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).debug() 
      << "Business Logic: getAdaptationAssignmentPreference..." << std::endl;
#endif
    LpiAdaptationAssignmentPreference ass_pref;  // RTP only
    getAdaptationAssignmentPreference(ass_pref, result);


#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).debug() 
      << "Business Logic: getAdaptationAlert_Kpi..." << std::endl;
#endif
    LpiAdaptationAlert_KPIs adap_alert_kpi;
    getAdaptationAlert_KPIs(adap_alert_kpi, result);


#ifdef TRACE_OUT
   LclogStream::instance(LclogConfig::E_RTP).debug() 
     << "Business Logic: getWakeVortexCapacityReductions..." << std::endl;
#endif
   LpiWakeVortexCapacityReductions wtc_capacity;
   getWakeVortexCapacityReductions(wtc_capacity, result);
#ifdef TRACE_OUT
   LclogStream::instance(LclogConfig::E_RTP).debug() 
     << "WTC demand capacity reductions read: " << std::endl;
//   LclogStream::instance(LclogConfig::E_RTP).debug() << wtc_capacity  // 1000 líneas log
//						     << std::endl;
#endif


   //----------------------

   /* Requirement ([1].4.1), last paragraph): assert (simultaneousOpsTime <= Minutes_Subinterval)
    *
    * simultaneousOpsTime ([1].3.1.2): Tiempo en minutos para determinar que una
    * operación es simultánea (debe de ser menor que el tiempo por subintervalo
    *
    */
    if ( mrtm_info.getSimultaneousOpsTime() > config_core_parameters.getTimeParameters().getMinutesSubinterval() )
    {
    	std::stringstream err_msg;
    	err_msg << "SimultaneousOpsTime " << '(' << rtp_constants::FILENAME_DAORTP_MRTM_INFO << ')'
    			<< " > " << "Minutes_Subinterval " << '(' << rtp_constants::FILENAME_DAORTP_MRTM_INFO << ')';
        LclogStream::instance(LclogConfig::E_RTP).error() << err_msg.str() << std::endl;
    	std::cerr << "\n\nERROR: " << err_msg.str() << std::endl;

    	exit(EXIT_FAILURE);
    }

   //----------------------

   /// init DB

#ifdef TRACE_OUT
  LclogStream::instance(LclogConfig::E_RTP).debug() 
    << "STEP-2: DB initialization ( LpdbDataBase::Get().init() ) ..."
    << std::endl;
#endif

  LpdbDataBase::Get().init(config_core_parameters,
			   mrtm_info,
			   airports_info,
			   priority_table_dep,
			   priority_table_arr,
			   ass_pref,
			   adap_alert_kpi,
			   wtc_capacity);

   //----------------------

   ///@test setting thresholds & prohibitions [1].4.1
#ifdef TRACE_OUT

   LclogStream::instance(LclogConfig::E_RTP).debug()
     << "### DB Test - Initial load (see [1].4.1):"
     << std::endl;

  LclogStream::instance(LclogConfig::E_RTP).debug() 
    << "DB: adaptation thresholds per MRTM - threshold/interval:"
	 << "\n" << LpdbDataBase::Get().getGlobalParameters().getAdapThresholdsPerInterval()
    << std::endl;

  LclogStream::instance(LclogConfig::E_RTP).debug()
    << "DB: adaptation thresholds per Airport: threshold/interval:"
	 << "\n" << LpdbDataBase::Get().getAirportTable()
    << std::endl;

  LclogStream::instance(LclogConfig::E_RTP).debug() 
    << "DB: Prohibitions table - prohibitions/interval (DAORTP_AssignmentPreference):"
    << "\n" << LpdbDataBase::Get().getProhibitionsTimeline()
    << std::endl;

  LclogStream::instance(LclogConfig::E_RTP).debug() 
    << "DB: Preferences table - prefs./interval (DAORTP_AssignmentPreference):"
    << "\n" << LpdbDataBase::Get().getPreferencesTimeline()
    << std::endl;

#endif
  
//#ifdef TRACE_OUT
//  LclogStream::instance(LclogConfig::E_RTP).debug()
//    << "DB: WakeVortexReductions"
//    << "\n" << LpdbDataBase::Get().getWakeVortexReductions() // 900 lineas de log
//    << std::endl;
//#endif

   //----------------------

  /// (additional) setting DB params 


   ///@todo transitionsTable

   LclogStream::instance(LclogConfig::E_RTP).warning()
     << "@TODO  STEP-4: DB initialization: transitionsTable ..."
     << std::endl;


   // RMAN code bellow:
   //
   //    LpiAdaptationRunwaySystemPreferenceList preferences;
   //    getAdaptationRunwaySystemPreference(preferences, result);


// #ifdef TRACE_OUT
//    LclogStream::instance(LclogConfig::E_RTP).debug()
//      << "@TODO  STEP-4: DB initialization: transitionsTable ..."
//      << std::endl;
// #endif
//    LpiAdaptationMrtmTransitionCostTable transitionsTable;
//    getAdaptationMrtmTransitionCosts(transitionsTable, result);
//
//    generateMrtmTransitionCosts(transitionsTable);
// #ifdef TRACE_OUT
//     LclogStream::instance(LclogConfig::E_RTP).debug() 
//       << "@todo RS change table generated: " << std::endl;
//     LclogStream::instance(LclogConfig::E_RTP).debug() 
//       << transitionsTable << std::endl;
//     LclogStream::instance(LclogConfig::E_RTP).debug() 
//       << "DataBase initialized." << std::endl;
// #endif


   //----------------------


   ///@todo generateDefaultSchedule   (RMAN code bellow)

   LclogStream::instance(LclogConfig::E_RTP).warning() 
     << "@todo STEP-65: DB initialization: Default schedule generated." 
     << std::endl;
   //
//    _schedules_generator->setCalculationParameters();
//    _schedules_generator->setPreferentialLevels(preferences);
//    _schedules_generator->setStabilityCostMatrix(transitionsTable);
//    _schedules_generator->generateDefaultSchedule();
// #ifdef TRACE_OUT
//    LclogStream::instance(LclogConfig::E_RTP).debug() 
//      << "STEP-5: DB initialization: Default schedule generated." << std::endl;
// #endif

}

void LpdBusinessLogicFacade::showAdapAndConfigInfo()
{
    std::stringstream sOutput;
    sOutput << "[ADAPTATION DATA]";
    sOutput << "\nRunways:   @todo Implement me     ";
//    vector<string> runways = LpdbDataBase::Get().getRunwayTable().getAllIds();
//    BOOST_FOREACH(string nameRwy, runways)
//    {
//        sOutput << nameRwy << " ";
//    }

//    LpiPriorityTable prioritiesDepartures;
//    getPriorityTableDepartures(prioritiesDepartures, result);
//    sOutput << "\nFP PRIORITIES_DEPARTURES:\n";
//    sOutput << prioritiesDepartures << "\n";
//
//    LpiPriorityTable prioritiesArrivals;
//    getPriorityTableArrivals(prioritiesArrivals, result);
//    sOutput << "\nFP PRIORITIES_ARRIVALS:\n";
//    sOutput << prioritiesArrivals << "\n";

//    LpiRunwaySystemProhibitions prohibitions;
//    getRunwaySystemProhibitions(prohibitions, result);
//
//    sOutput << "Prohibitions read:\n" << prohibitions << "\n";
//    sOutput << "Prohibitions timeline:\n";
//    sOutput << LpdbDataBase::Get().getProhibitionsTimeline() << std::endl;

//idem con getPreferencesTimeLine

//    LpiConfigurationParameters config_parameters;
//    getConfigurationParameters(config_parameters, result);
//    sOutput << "\n\n[CONFIGURATION DATA]";
//    sOutput << "\nTIME PARAMETERS:";
//    sOutput << config_parameters.getTimeParameters();

    LclogStream::instance(LclogConfig::E_RTP).info() << sOutput.str() << std::endl;

}

void LpdBusinessLogicFacade::complete(void)
{

#ifdef TRACE_OUT
  LclogStream::instance(LclogConfig::E_RTP).debug()
    << "TODO: RTP Server's Business Logic completion: Capacity calculations."
    << " : File: " << __FILE__
    << " ; fn: " << __func__
    << " ; line: " << __LINE__
    << std::endl;
#endif


  // calculate capacities for each airport, for each interval
  calculateMaxCapacities();


/** RMAN code

#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).info() << "OPTIMAL SCHEDULE CALCULATION" <<std::endl;
    LclogStream::instance(LclogConfig::E_RTP).info() << "Calculation cause: Initialization" <<std::endl;

    //showAdapAndConfigInfo();
#endif
    calculateEstimatedDCB();
    generateSchedulesForAllIntervals();
    calculateRealDCBAndRunwayAllocation();

#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).debug() << "FPS Schedule calculations..." <<std::endl;
#endif
    performFPInScheduleCalculations();
    bool isClockForwarding = false;
    bool isInitialization = true;
    calculateSchedulesKPIs(isClockForwarding, isInitialization);

#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).info() << "Calculate Optimal Schedule..." << std::endl;
#endif
    generateOptimalSchedule();
    activateOptimalSchedule();
    performActiveScheduleCalculations(isClockForwarding, isInitialization);
    publishOptimalAndActiveSchedules(LpiCalculationReason::E_INIT);
*/
}

//--------------------------------------------------------------

void LpdBusinessLogicFacade::forwardTimeline(void)
{
#ifdef TRACE_OUT
  LclogStream::instance(LclogConfig::E_RTP).info()
    << "OPTIMAL SCHEDULE CALCULATION" <<std::endl;
  LclogStream::instance(LclogConfig::E_RTP).info()
    << "Calculation cause: Rtp Clock event" 
    << " : File: " << __FILE__
    << " ; fn: " << __func__
    << " ; line: " << __LINE__
    << std::endl;
#endif


  // data base

  LpdbDataBase::Get().forwardTimeline(); // throw InvalidSubintervalException

#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).debug()
      << "Database timelines forwarded" 
      << " : File: " << __FILE__
      << " ; fn: " << __func__
      << " ; line: " << __LINE__
      << std::endl;
#endif

    LpiResult result;
    LpiAdaptationAirportsInfo parameters;
    LpdComponent::Get().getAdaptationAirportsInfo(parameters, result);
    std::string new_interval = LpdbDataBase::Get().getDemand(parameters.getAirport().at(0).getAirportName()).getTimeLine().getLastInterval();

    //DB::meteo
    reviewMeteoInfo(new_interval);

//demand
#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).debug() << "Calculate Demand Data for new interval..." << new_interval << std::endl;
#endif

    calculateTimedDemand(new_interval, parameters.getAirport().at(0).getAirportName());

#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).info() << "Demand Forecast:" << std::endl;
    LclogStream::instance(LclogConfig::E_RTP).info() << LpdbDataBase::Get().getDemand(parameters.getAirport().at(0).getAirportName()) << std::endl;
#endif

    for(unsigned int a = 0; a < parameters.getAirport().size(); a++)
    	LpdbDataBase::Get().getDemand(parameters.getAirport().at(0).getAirportName()).updateTotalDemandForecast();


#ifdef TRACE_OUT
  LclogStream::instance(LclogConfig::E_RTP).debug()
    << "Calculating capcacities for each airport in the new interval..."
    << new_interval
    << " : File: " << __FILE__
    << " ; fn: " << __func__
    << " ; line: " << __LINE__
    << std::endl;
#endif
    calculateMaxCapacities(new_interval);


    
#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).debug() << "Calculate Estimated DCB for new interval..." << new_interval << std::endl;
#endif

    calculateEstimatedDCB(new_interval);

#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).debug() << "Estimated DCB calculations: " << std::endl;
//    LclogStream::instance(LclogConfig::E_RTP).debug() << LpdbDataBase::Get().getEstimatedDCBAsString() << std::endl;
#endif

    double cancelation_threshold = LpdbDataBase::Get().getGlobalParameters().getFPExpirationTime();

#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).debug() << "Reviewing obsolete FPs..." << std::endl;
#endif

//   reviewObsoleteFlightPlans(cancelation_threshold);
    reviewObsoleteFlightPlansByAssignedTime(cancelation_threshold);

#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).info() << "DataBase FPs:" << std::endl;
    LclogStream::instance(LclogConfig::E_RTP).info() << LpdbDataBase::Get().getFPTable() << std::endl;

    //Optimal Schedule calculations
    LclogStream::instance(LclogConfig::E_RTP).debug() << "Invocation to schedules generation..." << std::endl;
#endif

    //_schedules_generator->forwardDefaultSchedule();

//    LpiConfigurationParameters configurationData;
//    LpiResult result;
//    getConfigurationParameters(configurationData, result);
//
//    int minutesFrozenForClock = configurationData.getTimeParameters().getMinutesFrozenForClock();
//    generateSchedulesForClock(minutesFrozenForClock);

    //generateSchedulesForLastInterval(new_interval);
#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).info() << "Real DCB calculations..." << std::endl;
#endif

    calculateRealDCBAndRunwayAllocation();

#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).info() << "FPS Schedule calculations..." <<std::endl;
#endif

    performFPInScheduleCalculations();

    bool isClockForwarding = true;

    calculateSchedulesKPIs(isClockForwarding);

    for(unsigned int a = 0; a < parameters.getAirport().size(); a++)
    	updateHMIDemand(LpiCalculationReason::E_CLOCK, parameters.getAirport().at(a).getAirportName());

#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).info() <<"Calculate Optimal Schedule..." << std::endl;
#endif

    generateOptimalSchedule();

    //Active Schedule calculations
    generateRSForActiveScheduleLastInterval(new_interval);

    performActiveScheduleCalculations(isClockForwarding);

    publishOptimalAndActiveSchedules(LpiCalculationReason::E_CLOCK);

#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).info() << "[RUNWAY FINAL ASSIGNATION]: " << std::endl;
#endif

    calculateRunwayFinalAssignation();

    LpdbDataBase::Get().setInputReceivedInLastInterval(false);

    setExpirationDateForWhatIfs(LctimVirtualClock::Get().getTime());
    reviewObsoleteWhatIfs();
}

//--------------------------------------------------------------

/**@fn void LpdBusinessLogicFacade::calculate_airport_TMATWYsMaxCapacities
   (std::string airport_id)

   @brief For 'airport_id', for each interval: calculate capacities
   of TMA and Taxiways.

   @param TMA: Terminal Maneuvering Area
*/
void LpdBusinessLogicFacade::calculateTMATWYsMaxCapacities(std::string airport_id)
{
#ifdef TRACE_OUT
  LclogStream::instance(LclogConfig::E_RTP).debug()
    << "TODO: RTP Server's Business Logic completion: Capacity calculations."
    << " ; TMA & TWY"
    << " ; airport_id:" << airport_id    
    << " : File: " << __FILE__
    << " ; fn: " << __func__
    << " ; line: " << __LINE__
    << std::endl;
#endif

 LpdbDataBase::Get().getAirportTable()[airport_id].getTMA().calculateCapacity();
 LpdbDataBase::Get().getAirportTable()[airport_id].getTWY().calculateCapacity();
}

//------------------------------------------------------------------------------

void LpdBusinessLogicFacade::calculateTMATWYsMaxCapacities
     (std::string airport_id, string interval)
{
#ifdef TRACE_OUT
  LclogStream::instance(LclogConfig::E_RTP).debug()
    << "TODO: RTP Server's Business Logic completion: Capacity calculations."
    << " ; TMA & TWY"
    << " ; airport_id:" << airport_id
    << " ; interval:" << interval
    << " : File: " << __FILE__
    << " ; fn: " << __func__
    << " ; line: " << __LINE__
    << std::endl;
#endif

 LpdbDataBase::Get().getAirportTable()[airport_id].getTMA().calculateCapacity(interval);
 LpdbDataBase::Get().getAirportTable()[airport_id].getTWY().calculateCapacity(interval);
}

//--------------------------------------------------------------

void LpdBusinessLogicFacade::calculateMaxCapacities(void)
{
#ifdef TRACE_OUT
  LclogStream::instance(LclogConfig::E_RTP).debug()
    << "TODO: RTP Server's Business Logic completion: Capacity calculations."
    << " : File: " << __FILE__
    << " ; fn: " << __func__
    << " ; line: " << __LINE__
    << std::endl;
#edif
  

  auto calculate = [this](const std::string airport_id) 
  {
    calculateTMATWYsMaxCapacities(airport_id);
    // calculateRunwaysMaxCapacities(airport_id); ///@todo RTP uses airport_id
    // calculateRSMaxCapacities(airport_id); ///@todo RTP uses airport_id
  };
  std::for_each(std::begin(LpdbDataBase::Get().getAirportTable().getAllIds()), 
		std::end(LpdbDataBase::Get().getAirportTable().getAllIds()),
		calculate);


  
//#ifdef TRACE_OUT
//    //Logging
//    LclogStream::instance(LclogConfig::E_RTP).info() << "Runways Calculations: " << std::endl;
//    LclogStream::instance(LclogConfig::E_RTP).info() << LpdbDataBase::Get().getRunwaysCapacitiesAsString() << std::endl;
//
//    LclogStream::instance(LclogConfig::E_RTP).info() << "Runways in Runway System Calculations: " << std::endl;
//    LclogStream::instance(LclogConfig::E_RTP).info() << LpdbDataBase::Get().getRunwaySystemRunwaysCapacitiesAsString() << std::endl;
//
//    LclogStream::instance(LclogConfig::E_RTP).info() << "Runway System Calculations: " << std::endl;
//    LclogStream::instance(LclogConfig::E_RTP).info() << LpdbDataBase::Get().getRunwaySystemsCapacitiesAsString() << std::endl;
//#endif
}

//------------------------------------------------------------------------------

void LpdBusinessLogicFacade::calculateMaxCapacities(string interval)
{
#ifdef TRACE_OUT
  LclogStream::instance(LclogConfig::E_RTP).debug()
    << "TODO: RTP Server's Business Logic completion: Capacity calculations."
    << " ; interval:" << interval
    << " : File: " << __FILE__
    << " ; fn: " << __func__
    << " ; line: " << __LINE__
    << std::endl;
#endif
  

  auto calculate = [this](const std::string airport_id) 
  {
    calculateTMATWYsMaxCapacities(airport_id, interval);
    // calculateRunwaysMaxCapacities(airport_id, interval); ///@todo
    // calculateRSMaxCapacities(airport_id, interval); ///@todo 
  };
  std::for_each(std::begin(LpdbDataBase::Get().getAirportTable().getAllIds()), 
		std::end(LpdbDataBase::Get().getAirportTable().getAllIds()),
		calculate);


// #ifdef TRACE_OUT
//     //Logging
//     LclogStream::instance(LclogConfig::E_RTP).debug() << "Runways Calculations: " << std::endl;
//     LclogStream::instance(LclogConfig::E_RTP).debug() << LpdbDataBase::Get().getRunwaysCapacitiesAsString() << std::endl;

//     LclogStream::instance(LclogConfig::E_RTP).debug() << "Runways in Runway System Calculations: " << std::endl;
//     LclogStream::instance(LclogConfig::E_RTP).debug() << LpdbDataBase::Get().getRunwaySystemRunwaysCapacitiesAsString() << std::endl;

//     LclogStream::instance(LclogConfig::E_RTP).debug() << "Runway System Calculations: " << std::endl;
//     LclogStream::instance(LclogConfig::E_RTP).debug() << LpdbDataBase::Get().getRunwaySystemsCapacitiesAsString() << std::endl;
// #endif
}

void LpdBusinessLogicFacade::calculateRunwayAndRSMaxCapacities()
{
    //calculateRunwaysMaxCapacities();
    calculateRSMaxCapacities();

#ifdef TRACE_OUT
    //Logging
    LclogStream::instance(LclogConfig::E_RTP).debug() << "Runways Calculations: " << std::endl;
    LclogStream::instance(LclogConfig::E_RTP).debug() << LpdbDataBase::Get().getRunwaysCapacitiesAsString() << std::endl;

    LclogStream::instance(LclogConfig::E_RTP).debug() << "Runways in Runway System Calculations: " << std::endl;
    LclogStream::instance(LclogConfig::E_RTP).debug() << LpdbDataBase::Get().getRunwaySystemRunwaysCapacitiesAsString() << std::endl;

    LclogStream::instance(LclogConfig::E_RTP).debug() << "Runway System Calculations: " << std::endl;
    LclogStream::instance(LclogConfig::E_RTP).debug() << LpdbDataBase::Get().getRunwaySystemsCapacitiesAsString() << std::endl;
#endif
}

//------------------------------------------------------------------------------

/*
void LpdBusinessLogicFacade::calculateRunwaysMaxCapacities(void)
{
#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).debug() << "Calculating Ruways maximum capacities..." << std::endl;
#endif

    LpdbDataBase::RunwayTable & rwyTable = LpdbDataBase::Get().getRunwayTable();
    vector<string> runway_ids = rwyTable.getAllIds();

    //Get thresholds for applying reductions
    LpiAdaptationMeteothresholdList thresholds;
    LpiResult thresholds_result;

    //getAdaptationMeteoThresholds(thresholds, thresholds_result);

    //Get minimal capacity reduction
    LpiAdaptationCapacityReduction reduction;
    LpiResult reductions_result;

    getAdaptationCapacityReduction(reduction, reductions_result);

    if ((reductions_result.getResult() == LpiResult::E_OK) && (reductions_result.getResult() == LpiResult::E_OK))
    {
        BOOST_FOREACH(string id, runway_ids)
        {
            if (rwyTable.exists(id))
            {
                rwyTable[id].calculateMaximumCapacity();
                rwyTable[id].calculateNoOperationCapacity();
                rwyTable[id].calculateManualReductionCapacity();
                rwyTable[id].calculateILSCapacity();

                if (reductions_result.getResult() == LpiResult::E_OK)
                {
                    LpiADOVector<double> crosswind_reduction = reduction.getCrossWindCapacityReduction(id);
                    LpiADOVector<double> tailwind_reduction = reduction.getTailWindCapacityReduction(id);
                    LpiADOVector<double> visibility_reduction = reduction.getHorizontalVisibilityReduction(id);

                    rwyTable[id].applyMeteoReductions(crosswind_reduction, tailwind_reduction, visibility_reduction,
                                                      thresholds);
                }
            }
        }
    }
}
*/

/*
void LpdBusinessLogicFacade::calculateRunwaysMaxCapacities(string interval)
{
#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).debug() << "Calculating Ruways maximum capacities..." << interval << std::endl;
#endif

    LpdbDataBase::RunwayTable & rwyTable = LpdbDataBase::Get().getRunwayTable();
    vector<string> runway_ids = rwyTable.getAllIds();

    //Get thresholds for applying reductions
    LpiAdaptationMeteothresholdList thresholds;
    LpiResult thresholds_result;

    getAdaptationMeteoThresholds(thresholds, thresholds_result);

    //Get minimal capacity reduction
    LpiAdaptationCapacityReduction reduction;
    LpiResult reductions_result;

    getAdaptationCapacityReduction(reduction, reductions_result);

    if ((reductions_result.getResult() == LpiResult::E_OK) && (reductions_result.getResult() == LpiResult::E_OK))
    {
        BOOST_FOREACH(string id, runway_ids)
        {
            if (rwyTable.exists(id))
            {
                rwyTable[id].calculateMaximumCapacity(interval);
                rwyTable[id].calculateNoOperationCapacity(interval);
                rwyTable[id].calculateManualReductionCapacity(interval);
                rwyTable[id].calculateILSCapacity(interval);

                if (reductions_result.getResult() == LpiResult::E_OK)
                {
                    LpiADOVector<double> crosswind_reduction = reduction.getCrossWindCapacityReduction(id);
                    LpiADOVector<double> tailwind_reduction = reduction.getTailWindCapacityReduction(id);
                    LpiADOVector<double> visibility_reduction = reduction.getHorizontalVisibilityReduction(id);

                    rwyTable[id].applyMeteoReductions(interval, crosswind_reduction, tailwind_reduction,
                                                      visibility_reduction, thresholds);
                }
            }
        }
    }
}
*/

void LpdBusinessLogicFacade::calculateRSMaxCapacities(void)
{
#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).debug() << "Calculating Runway System maximum capacities..." << std::endl;
#endif

    LpdbDataBase::RunwaySystemTable & rsTable = LpdbDataBase::Get().getRunwaySystemTable();
    vector<string> rs_ids = rsTable.getAllIds();

    BOOST_FOREACH(string id, rs_ids)
    {
        if (rsTable.exists(id))
        {
            rsTable[id].calculateMaximumCapacity();
        }
    }
}

void LpdBusinessLogicFacade::calculateRSMaxCapacities(string interval)
{
#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).debug() << "Calculating Runway System maximum capacities...interval " << interval << std::endl;
#endif

    LpdbDataBase::RunwaySystemTable & rsTable = LpdbDataBase::Get().getRunwaySystemTable();
    vector<string> rs_ids = rsTable.getAllIds();

    BOOST_FOREACH(string id, rs_ids)
    {
        if (rsTable.exists(id))
        {
            rsTable[id].calculateMaximumCapacity(interval);
        }
    }
}

void LpdBusinessLogicFacade::calculateAirportMaxCapacitiesAndMinDelayedFPs(void)
{
    TimeLine<LpdbDCBAirportTimedData> & airportTimeline = LpdbDataBase::Get().getDCBAirportTimeline();

    vector<string> intervals = airportTimeline.getAllIntervalIds();

    BOOST_FOREACH(string interval, intervals)
    {
        //calculatePriorityOperation(interval);
        //calculateAirportMaxCapacitiesForAllRS(interval);
        //calculateMinDelayedFPs(interval);
    }
}

/*
void LpdBusinessLogicFacade::calculatePriorityOperation(string interval)
{
    TimeLine<LpdbDCBAirportTimedData> & airportDCBTimeline = LpdbDataBase::Get().getDCBAirportTimeline();

    LpiADOVector<int> minDelayedFPsPreviousInterval(0, 0, 0);

    int priorityOperationPreviousInterval = E_ARR;

    if (interval != "t0")
    {
        string previousInterval = airportDCBTimeline.getPreviousIntervalId(interval);

        if (airportDCBTimeline.hasData(previousInterval))
        {
            minDelayedFPsPreviousInterval = airportDCBTimeline[previousInterval].getMinDelayedFPs();
            priorityOperationPreviousInterval = airportDCBTimeline[previousInterval].getPriorityOperation();
        }
    }

    LpdbDemand & demand = LpdbDataBase::Get().getDemand();

    LpiADOVector<int> demandForecast(0, 0, 0);

    if (demand.has_data(interval))
    {
        demandForecast = demand[interval].getDemandForecast();
    }

    LpiADOVector<int> predictedDemand = minDelayedFPsPreviousInterval + demandForecast;

    int priorityOperation = E_ARR; //Default priority

    if (predictedDemand != LpiADOVector<int>(0, 0, 0))
    {
        if (predictedDemand[E_DEP] > predictedDemand[E_ARR])
        {
            priorityOperation = E_DEP;
        }
        else if (predictedDemand[E_DEP] < predictedDemand[E_ARR])
        {
            priorityOperation = E_ARR;
        }
        else
        {
            if (demandForecast[E_DEP] > demandForecast[E_ARR])
            {
                priorityOperation = E_DEP;
            }
            else if (demandForecast[E_DEP] < demandForecast[E_ARR])
            {
                priorityOperation = E_ARR;
            }
            else
            {
                priorityOperation = priorityOperationPreviousInterval;
            }
        }
    }

    airportDCBTimeline[interval].setPriorityOperation(priorityOperation);
}
*/

/*
void LpdBusinessLogicFacade::calculateAirportMaxCapacitiesForAllRS(const string & interval)
{
    TimeLine<LpdbDCBAirportTimedData> & airportDCBTimeline = LpdbDataBase::Get().getDCBAirportTimeline();

    int priorityOperation = E_ARR;
    int complementaryPriorityOperation = E_DEP;

    if (airportDCBTimeline.hasData(interval))
    {
        priorityOperation = airportDCBTimeline[interval].getPriorityOperation();
        complementaryPriorityOperation = 1 - priorityOperation;
    }

    LpdbDataBase::RunwaySystemTable & rsTable = LpdbDataBase::Get().getRunwaySystemTable();
    vector<string> rs_ids = rsTable.getAllIds();

    LpiADOVector<int> maxAirportCapacity(0, 0, 0);

    BOOST_FOREACH(string id, rs_ids)
    {
        if (rsTable.exists(id))
        {
            LpdbRunwaySystem & rs = rsTable[id];
            if (rs.has_data(interval))
            {
                LpiADOVector<int> rsMaxCapacity = rs[interval].getMaxCapacity();

                if (rsMaxCapacity[priorityOperation] > maxAirportCapacity[priorityOperation])
                {
                    maxAirportCapacity = rsMaxCapacity;
                }
                else if (rsMaxCapacity[priorityOperation] == maxAirportCapacity[priorityOperation])
                {
                    if (rsMaxCapacity[complementaryPriorityOperation] > maxAirportCapacity[complementaryPriorityOperation])
                    {
                        maxAirportCapacity = rsMaxCapacity;
                    }
                }
            }
        }
    }

    TimeLine<LpdbDCBAirportTimedData> & airportTimeline = LpdbDataBase::Get().getDCBAirportTimeline();
    airportTimeline[interval].setMaxAirportCapacity(maxAirportCapacity);
}
*/

/*
void LpdBusinessLogicFacade::calculateMinDelayedFPs(const string & interval)
{
    //Phase III: Algorithm improvement: get min delayed FPs
    TimeLine<LpdbDCBAirportTimedData> & airportDCBTimeline = LpdbDataBase::Get().getDCBAirportTimeline();

    LpiADOVector<int> minDelayedFPsPreviousInterval(0, 0, 0);
    if (interval != "t0")
    {
        string previousInterval = airportDCBTimeline.getPreviousIntervalId(interval);

        if (airportDCBTimeline.hasData(previousInterval))
        {
            minDelayedFPsPreviousInterval = airportDCBTimeline[previousInterval].getMinDelayedFPs();
        }
    }

    LpiADOVector<int> maxAirportCapacity(0, 0, 0);
    if (airportDCBTimeline.hasData(interval))
    {
        maxAirportCapacity = airportDCBTimeline[interval].getMaxAirportCapacity();
    }

    LpdbDemand & demandTable = LpdbDataBase::Get().getDemand();
    LpiADOVector<int> demandForecast(0, 0, 0);
    if (demandTable.has_data(interval))
    {
        demandForecast = demandTable[interval].getDemandForecast();
    }

    LpiADOVector<int> minDelayedFPs = (demandForecast + minDelayedFPsPreviousInterval) - maxAirportCapacity;
    minDelayedFPs = max(minDelayedFPs, LpiADOVector<int>(0, 0, 0));
    minDelayedFPs[E_OVA] = minDelayedFPs[E_ARR] + minDelayedFPs[E_DEP];

    if (airportDCBTimeline.hasData(interval))
    {
        airportDCBTimeline[interval].setMinDelayedFPs(minDelayedFPs);
    }
}
*/

void LpdBusinessLogicFacade::updateHMIDemand(const LpiCalculationReason::LpiEnum & reason, LpiCreateDemand demandL)
{
    LpiDemand lpiDemand;
    LpdbDataBase::FPTable & fp_table = LpdbDataBase::Get().getFPTable();

    vector<string> fp_keys = fp_table.getAllIds();

	LpdbDemand & demand = LpdbDataBase::Get().getDemand(demandL.getNameAirport());
	vector<string> intervals = demand.getTimeLine().getAllIntervalIds();

	lpiDemand.setmessageTimeandDate(demand.getmessageTimeandDate());
	lpiDemand.setCalculationReason(reason);

	std::vector<Demand_list> demandList;
	std::vector<FPs_ADO> FpsLista;

	BOOST_FOREACH(string ti, intervals)
	{
		FPs_ADO fpAdo;

		Demand_list demandforecast;

		demandforecast.setIntervalName(ti);

		demandforecast.setdemandForecastScheduled(
				LpiADOConverter::Convert2Interface(demand.getTimeLine()[ti].getDemandForecast()));

		demandforecast.setDemandRatio(LpiADOConverter::Convert2Interface(demand[ti].getPonderatedDemand()));

		demandforecast.setStartTime(LctimTimeUtils::formatTime(demand.getTimeLine().getTimeInterval(ti).begin));
		demandforecast.setEndTime(LctimTimeUtils::formatTime(demand.getTimeLine().getTimeInterval(ti).end));

		demandList.push_back(demandforecast);

		int type = E_ARR;
		while (type <= E_DEP)
		{
			for (unsigned int j = 0; j < demand.getTimeLine()[ti].getDemandForecastFps()[type].size(); j++)
			{
				Fps_list fplist;
				fplist.reset();

				std::string name(demand.getTimeLine()[ti].getDemandForecastFps()[type][j]);

				for (unsigned int k = 0; k < fp_keys.size(); k++)
				{
				if (fp_table[fp_keys[k]].getUniqueKey() == name)
					{
						string callsign = fp_table[fp_keys[k]].getCallsign();
						boost::algorithm::trim(callsign);

						LpiFlightPlan fp = fp_table[fp_keys[k]];
						fplist.setdemandForecastFpsScheduled(fp.getCallsign());

						boost::optional<posix_time::ptime> intentional = fp.getIntentionalTime();
						if (intentional)
						{
							fplist.setItotIldt(*intentional);
						}
						fplist.setAircraftType(fp.getAircraftType());
						fplist.setOperationType(fp.getOperationType());

						if (type == E_DEP)
						{
							//Assign times
							LpiDepartureTimes dep_times = fp.getDepartureTimes();
							boost::optional<posix_time::ptime> fp_dep_time;

							fp_dep_time = dep_times.getCtot();
							if (fp_dep_time)
							{
								fplist.setCtotSibt(*fp_dep_time);
							}

							fp_dep_time = dep_times.getEtot();
							if (fp_dep_time)
							{
								fplist.setEtotEldt(*fp_dep_time);
							}

							fp_dep_time = dep_times.getStot();
							if (fp_dep_time)
							{
								fplist.setStotSldt(*fp_dep_time);
							}

							fp_dep_time = dep_times.getTtot();
							if (fp_dep_time)
							{
								fplist.setTtotTldt(*fp_dep_time);
							}

							fp_dep_time = dep_times.getUtot();
							if (fp_dep_time)
							{
								fplist.setUtotUldt(*fp_dep_time);
							}

							fplist.setSIDSTAR(fp.getSID());
							fpAdo.departure.push_back(fplist);
						}
						else
						{
							//Assign times
							LpiArrivalTimes arr_times = fp.getArrivalTimes();

							boost::optional<posix_time::ptime> fp_arr_time;

							fp_arr_time = arr_times.getSibt();
							if (fp_arr_time)
							{
								fplist.setCtotSibt(*fp_arr_time);
							}

							fp_arr_time = arr_times.getEldt();
							if (fp_arr_time)
							{
								fplist.setEtotEldt(*fp_arr_time);
							}

							fp_arr_time = arr_times.getSldt();
							if (fp_arr_time)
							{
								fplist.setStotSldt(*fp_arr_time);
							}

							fp_arr_time = arr_times.getTldt();
							if (fp_arr_time)
							{
								fplist.setTtotTldt(*fp_arr_time);
							}

							fp_arr_time = arr_times.getUldt();
							if (fp_arr_time)
							{
								fplist.setUtotUldt(*fp_arr_time);
							}

							fplist.setSIDSTAR(fp.getSTAR());
							fpAdo.arrivals.push_back(fplist);
						}

						fpAdo.overall.push_back(fplist);
						break;
					}
				}
			}
			type++;
		}
		FpsLista.push_back(fpAdo);
		fpAdo.arrivals.clear();
		fpAdo.departure.clear();
		fpAdo.overall.clear();
	}

	NumberDemand numberDemand;
	numberDemand.setDemand(demandList);

	numberDemand.settotalDemandForecast(LpiADOConverter::Convert2Interface(demand.getTotalDemandForecast()));

	numberDemand.setTotalDemandRatio(LpiADOConverter::Convert2Interface(demand.getTotalDemandRatio()));

	numberDemand.setTotalDemandVFR(LpiADOConverter::Convert2Interface(demand.getTotalDemandVFR()));

	lpiDemand.setDemand(numberDemand);

	lpiDemand.setFps(FpsLista);

	lpiDemand.setNameAirport(demandL.getNameAirport());
	lpiDemand.setDemandStartTimeAndDate(demandL.getDemandStartTimeAndDate());
	lpiDemand.setDemandEndTimeAndDate(demandL.getDemandEndTimeAndDate());

	LpiFlightPlanList fpList;
	for(unsigned int x = 0; x < demandL.getFlightPlanList().size(); x++)
	{
		LpiFlightPlan fp;
		fp = demandL.getFlightPlanList().at(x);
		fpList.push_back(fp);
	}
	lpiDemand.setFlightPlanList(fpList);

	LpiADO zeroADO;
	zeroADO.setarrivalsValue(0);
	zeroADO.setdeparturesValue(0);
	zeroADO.setoverallValue(0);

	demandUpdateList.push_back(lpiDemand);
}

void LpdBusinessLogicFacade::updateHMIDemand(const LpiCalculationReason::LpiEnum & reason, std::string airport)
{
    LpiDemand lpiDemand;
    LpdbDataBase::FPTable & fp_table = LpdbDataBase::Get().getFPTable();

    vector<string> fp_keys = fp_table.getAllIds();

    LpdbDemand & demand = LpdbDataBase::Get().getDemand(airport);
    vector<string> intervals = demand.getTimeLine().getAllIntervalIds();

    lpiDemand.setmessageTimeandDate(demand.getmessageTimeandDate());
    lpiDemand.setCalculationReason(reason);

    std::vector<Demand_list> demandList;
    std::vector<FPs_ADO> FpsLista;

    BOOST_FOREACH(string ti, intervals)
    {
        FPs_ADO fpAdo;

        Demand_list demandforecast;

        demandforecast.setIntervalName(ti);

        demandforecast.setdemandForecastScheduled(
                LpiADOConverter::Convert2Interface(demand.getTimeLine()[ti].getDemandForecast()));

        demandforecast.setDemandRatio(LpiADOConverter::Convert2Interface(demand[ti].getPonderatedDemand()));

        demandforecast.setStartTime(LctimTimeUtils::formatTime(demand.getTimeLine().getTimeInterval(ti).begin));
        demandforecast.setEndTime(LctimTimeUtils::formatTime(demand.getTimeLine().getTimeInterval(ti).end));

        demandList.push_back(demandforecast);

        int type = E_ARR;
        while (type <= E_DEP)
        {
            for (unsigned int j = 0; j < demand.getTimeLine()[ti].getDemandForecastFps()[type].size(); j++)
            {
                Fps_list fplist;
                fplist.reset();

                std::string name(demand.getTimeLine()[ti].getDemandForecastFps()[type][j]);

                for (unsigned int k = 0; k < fp_keys.size(); k++)
                {
                if (fp_table[fp_keys[k]].getUniqueKey() == name)
                    {
                        string callsign = fp_table[fp_keys[k]].getCallsign();
                        boost::algorithm::trim(callsign);

                        LpiFlightPlan fp = fp_table[fp_keys[k]];
                        fplist.setdemandForecastFpsScheduled(fp.getCallsign());

                        boost::optional<posix_time::ptime> intentional = fp.getIntentionalTime();
                        if (intentional)
                        {
                            fplist.setItotIldt(*intentional);
                        }
                        fplist.setAircraftType(fp.getAircraftType());
                        fplist.setOperationType(fp.getOperationType());

                        if (type == E_DEP)
                        {
                            //Assign times
                            LpiDepartureTimes dep_times = fp.getDepartureTimes();
                            boost::optional<posix_time::ptime> fp_dep_time;

                            fp_dep_time = dep_times.getCtot();
                            if (fp_dep_time)
                            {
                                fplist.setCtotSibt(*fp_dep_time);
                            }

                            fp_dep_time = dep_times.getEtot();
                            if (fp_dep_time)
                            {
                                fplist.setEtotEldt(*fp_dep_time);
                            }

                            fp_dep_time = dep_times.getStot();
                            if (fp_dep_time)
                            {
                                fplist.setStotSldt(*fp_dep_time);
                            }

                            fp_dep_time = dep_times.getTtot();
                            if (fp_dep_time)
                            {
                                fplist.setTtotTldt(*fp_dep_time);
                            }

                            fp_dep_time = dep_times.getUtot();
                            if (fp_dep_time)
                            {
                                fplist.setUtotUldt(*fp_dep_time);
                            }

                            fplist.setSIDSTAR(fp.getSID());
                            fpAdo.departure.push_back(fplist);
                        }
                        else
                        {
                            //Assign times
                            LpiArrivalTimes arr_times = fp.getArrivalTimes();

                            boost::optional<posix_time::ptime> fp_arr_time;

                            fp_arr_time = arr_times.getSibt();
                            if (fp_arr_time)
                            {
                                fplist.setCtotSibt(*fp_arr_time);
                            }

                            fp_arr_time = arr_times.getEldt();
                            if (fp_arr_time)
                            {
                                fplist.setEtotEldt(*fp_arr_time);
                            }

                            fp_arr_time = arr_times.getSldt();
                            if (fp_arr_time)
                            {
                                fplist.setStotSldt(*fp_arr_time);
                            }

                            fp_arr_time = arr_times.getTldt();
                            if (fp_arr_time)
                            {
                                fplist.setTtotTldt(*fp_arr_time);
                            }

                            fp_arr_time = arr_times.getUldt();
                            if (fp_arr_time)
                            {
                                fplist.setUtotUldt(*fp_arr_time);
                            }

                            fplist.setSIDSTAR(fp.getSTAR());
                            fpAdo.arrivals.push_back(fplist);
                        }

                        fpAdo.overall.push_back(fplist);
                        break;
                    }
                }
            }
            type++;
        }
        FpsLista.push_back(fpAdo);
        fpAdo.arrivals.clear();
        fpAdo.departure.clear();
        fpAdo.overall.clear();
    }

    NumberDemand numberDemand;
    numberDemand.setDemand(demandList);

    numberDemand.settotalDemandForecast(LpiADOConverter::Convert2Interface(demand.getTotalDemandForecast()));

    numberDemand.setTotalDemandRatio(LpiADOConverter::Convert2Interface(demand.getTotalDemandRatio()));

    numberDemand.setTotalDemandVFR(LpiADOConverter::Convert2Interface(demand.getTotalDemandVFR()));

    lpiDemand.setDemand(numberDemand);

    lpiDemand.setFps(FpsLista);


    LpiADO zeroADO;
    zeroADO.setarrivalsValue(0);
    zeroADO.setdeparturesValue(0);
    zeroADO.setoverallValue(0);



    demandUpdateList.push_back(lpiDemand);

}

void LpdBusinessLogicFacade::publishUpdateDemandToHmi()
{
	LpiUpdateDemandEvt demandevt;
	demandevt.setDemand(demandUpdateList);
	demandUpdateList.clear();
	LpdComponent::Get().publish(demandevt);
}

void LpdBusinessLogicFacade::calculateEstimatedDCB(void)
{
    calculateAirportMaxCapacitiesAndMinDelayedFPs();

    //Estimated Demand Capacity Margin: calculation for all Runway Systems
    LpdbDataBase::RunwaySystemTable & rsTable = LpdbDataBase::Get().getRunwaySystemTable();

    vector<string> runway_system_keys = rsTable.getAllIds();

    BOOST_FOREACH(string rs_key, runway_system_keys)
    {
        if (rsTable.exists(rs_key))
        {
            LpdbRunwaySystem & rs = rsTable[rs_key];
            rs.resetEstimatedDelayedFPs();

            //Apply calculations in all Runway System timeline
            vector<string> intervals = rs.getTimeLine().getAllIntervalIds();

            BOOST_FOREACH(string ti, intervals)
            {
                calculateEstimatedNotAllowed(ti, rs);
                calculateEstimatedDCB(ti, rs);
            }
        }
    }
}


void LpdBusinessLogicFacade::calculateEstimatedDCB(std::string interval)
{
    //Estimated Demand Capacity Margin
    LpdbDataBase::RunwaySystemTable & rsTable = LpdbDataBase::Get().getRunwaySystemTable();

    vector<string> runway_system_keys = rsTable.getAllIds();

    BOOST_FOREACH(string rs_key, runway_system_keys)
    {
        if (rsTable.exists(rs_key))
        {
            LpdbRunwaySystem & rs = rsTable[rs_key];

            calculateEstimatedNotAllowed(interval, rs);
            calculateEstimatedDCB(interval, rs);
        }
    }
}


void LpdBusinessLogicFacade::calculateEstimatedNotAllowed(std::string interval, LpdbRunwaySystem & rs)
{/*
    OperationType::Enum usages[3] = {OperationType::E_ARRIVALS, OperationType::E_DEPARTURES, OperationType::E_MIXED};

    LpdbDemand & demandTable = LpdbDataBase::Get().getDemand("");

   LpdbDataBase::FPTable & flightPlansTable = LpdbDataBase::Get().getFPTable();

    if (demandTable.has_data(interval))
    {
        LpiADOVector<vector<string> > demandForecast = demandTable[interval].getDemandForecastFps();

        LpiADOVector<int> notAllowed;

        for (int i = E_ARR; i <= E_DEP; ++i)
        {
         BOOST_FOREACH(string fpKey, demandForecast[i])
         {
            if (flightPlansTable.exists(fpKey))
            {
               LpiFlightPlan & fp = flightPlansTable[fpKey];

                vector<string> fp_not_allowed_runways = fp.getNotAllowedRunways();

                if (fp_not_allowed_runways.size() > 0)
                {
                    vector<string> runways_by_use = rs.getRunwaysByUse(usages[i]);

                    //With set_difference, we calculate runways of RS thar are not included in
                    //not allowed with set_difference in two ordered collections
                    //if all of RS' runways are contained in not allowed, difference will be 0
                    vector<string> difference;

                    std::sort(fp_not_allowed_runways.begin(), fp_not_allowed_runways.end());
                    std::sort(runways_by_use.begin(), runways_by_use.end());

                  std::set_difference(runways_by_use.begin(), runways_by_use.end(),
                                      fp_not_allowed_runways.begin(), fp_not_allowed_runways.end(),
                                      back_inserter(difference));

                    if (difference.size() == 0)
                    {
                        notAllowed[i] = notAllowed[i] + 1;
                        notAllowed[E_OVA] = notAllowed[E_OVA] + 1;
                    }
                }
            }
         }
       }//end-for

      rs[interval].setNotAllowedEstimatedFPs(notAllowed);
    }*/
}



void LpdBusinessLogicFacade::calculateEstimatedDCB(std::string interval, LpdbRunwaySystem & rs)
{/*
    LpiADOVector<int> airportCapacity = rs[interval].getMaxCapacity();

    //Phase III: Algorithm improvement: get min delayed FPs
    TimeLine<LpdbDCBAirportTimedData> & airportDCBTimeline = LpdbDataBase::Get().getDCBAirportTimeline();

    LpiADOVector<int> minDelayedFPsPreviousInterval(0, 0, 0);

    if (interval != "t0")
    {
        string previousInterval = airportDCBTimeline.getPreviousIntervalId(interval);

        if (airportDCBTimeline.hasData(previousInterval))
        {
            minDelayedFPsPreviousInterval = airportDCBTimeline[previousInterval].getMinDelayedFPs();
        }
    }

    LpdbDemand & demandTable = LpdbDataBase::Get().getDemand("");

    if (demandTable.has_data(interval))
    {
        //[7.1.1]. Estimated Demand Capacity Margin

        LpiADOVector<int> demandForecast = demandTable[interval].getDemandForecast();

        //Phase III: Algorithm improvement: calculate new estimated DC margin
        LpiADOVector<int> estimatedNotAllowedDelayed;
        if (rs.has_data(interval))
        {
            estimatedNotAllowedDelayed = rs[interval].getNotAllowedEstimatedFPs();
        }

        LpiADOVector<int> margin = (demandForecast + minDelayedFPsPreviousInterval + estimatedNotAllowedDelayed)
                - airportCapacity;

        rs[interval].setEstimatedDcMargin(margin);

        //[7.2]. Estimated Delayed FPs
        LpiADOVector<int> estimated_delayed;
        estimated_delayed[E_ARR] = (margin[E_ARR] > 0) ? margin[E_ARR] : 0;
        estimated_delayed[E_DEP] = (margin[E_DEP] > 0) ? margin[E_DEP] : 0;
        estimated_delayed[E_OVA] = (margin[E_OVA] > 0) ? margin[E_OVA] : 0;

        //Add to subinterval
        rs[interval].setEstimatedDelayedFps(estimated_delayed);

        //Add to total vector scheduled
        rs.addEstimatedDelayedFP(estimated_delayed);
    }*/
}


void LpdBusinessLogicFacade::updateDemandTimeAndDate(const posix_time::ptime &timeAndDate, std::string airport)
{
    LpdbDemand & demand = LpdbDataBase::Get().getDemand(airport);
    demand.setmessageTimeandDate(timeAndDate);
}


void LpdBusinessLogicFacade::updateDemand(const LpiFlightPlan & data)
{
    //Process FP only if concerns to our airport
    //string our_airport = LpdbDataBase::Get().getGlobalParameters().getAerodromeName();

    boost::optional<ptime> former_intentional;
    LpdbDataBase::FPTable & fpTable = LpdbDataBase::Get().getFPTable();
   std::string flightPlanKey = data.getUniqueKey();
    // Update Flight Plan DataBase Table
   // Update Flight Plan DataBase Table
   if (fpTable.exists(flightPlanKey) == false)
    {
      fpTable.addElement(flightPlanKey, data);
    }
    else
    {
        //FP exists, must update demand (eliminate from interval already stored
      former_intentional = fpTable[flightPlanKey].getIntentionalTime();
      fpTable.updateElement(flightPlanKey, data);
    }
    //Update Demand (timeline) values in DataBase
    calculateTimedDemand(data, former_intentional);
}


void LpdBusinessLogicFacade::calculateTimedDemand(const LpiFlightPlan & fp, boost::optional<ptime> former_intentional)
{
    // Get ITOT if it's departure FP or ILDT if it's arrival FP
    // Get interval in timeline associated to FP intentional time, decrement demand in former intentional
    // And increment in current interval

    // ADO Vector with appropiate values

	LpiResult result;
	LpiAdaptationAirportsInfo parameters;
	LpdComponent::Get().getAdaptationAirportsInfo(parameters, result);

    boost::optional<std::string> former_interval;

    boost::optional<posix_time::ptime> intentional = fp.getIntentionalTime();
std::string a = fp.getDepartureAerodrome();
trim(a);
    //Update Demand timed data only if FP has ITOT or ILDT
    for(unsigned int i = 0; i < parameters.getAirport().size(); i++)
	{
    	if(LpdbDataBase::Get().getAirportTable().getAllIds().at(i).compare(a) == 0){
    		if (intentional)
    		    {
    		    	std::string a = fp.getDepartureAerodrome();
    		    	trim(a);
    		        LpdbDemand & demand = LpdbDataBase::Get().getDemand(fp.getDepartureAerodrome());
    		        boost::optional<std::string> interval = demand.getTimeLine().getInterval(*intentional);
    		        //In case of updating, get previous demand value to decrement it
    		        if (former_intentional)
    		        {
    		            former_interval = demand.getTimeLine().getInterval(*former_intentional);

    		            if ((former_interval) && (demand.has_data(*former_interval)))
    		            {
    		                if (fp.getOperationType() == LpiOperationType::E_DEPARTURE)
    		                {
    		                    demand[*former_interval].decrementDemand(E_DEP, 1);
    		                    demand.decrementDemand(E_DEP, 1);
    		                }
    		                else if (fp.getOperationType() == LpiOperationType::E_ARRIVAL)
    		                {
    		                    demand[*former_interval].decrementDemand(E_ARR, 1);
    		                    demand.decrementDemand(E_ARR, 1);
    		                }

    		                demand[*former_interval].decrementDemand(E_OVA, 1);
    		                demand.decrementDemand(E_OVA, 1);

    		                demand[*former_interval].deleteFPFromForecast(fp);
    		            }
    		        }

    		        if (interval && demand.has_data(*interval))
    		        {
    		            if (fp.getOperationType() == LpiOperationType::E_DEPARTURE)
    		            {
    		                demand[*interval].incrementDemand(E_DEP, 1);
    		                demand.incrementDemand(E_DEP, 1);
    		            }
    		            else if (fp.getOperationType() == LpiOperationType::E_ARRIVAL)
    		            {
    		                demand[*interval].incrementDemand(E_ARR, 1);
    		                demand.incrementDemand(E_ARR, 1);
    		            }

    		            demand[*interval].incrementDemand(E_OVA, 1);
    		            demand.incrementDemand(E_OVA, 1);

    		            //Store FP in forecast ordered by Intentional time
    		            demand[*interval].storeFPInForecast(fp);
    		        }
    		    }
    	}
	}


}


void LpdBusinessLogicFacade::calculateTimedDemand(std::string interval, std::string airport)
{
    //Iterate Through all FPs and update data only if ITOT or ILDT is in given interval
    LpdbDataBase::FPTable & fp_table = LpdbDataBase::Get().getFPTable();
    LpdbDemand & demand = LpdbDataBase::Get().getDemand(airport);

    vector<string> fp_keys = fp_table.getAllIds();

    BOOST_FOREACH (string fp_key, fp_keys)
    {
        if (fp_table.exists(fp_key))
        {
            LpiFlightPlan fp = fp_table[fp_key];

            boost::optional<posix_time::ptime> former_intentional;
            boost::optional<posix_time::ptime> intentional = fp.getIntentionalTime();

            if (intentional)
            {
                boost::optional<std::string> fp_interval = demand.getTimeLine().getInterval(*intentional);

                //Update Demand timed data only if FP has ITOT or ILDT and any of them is in interval
                if (fp_interval == interval)
                {
                    //In this case we don't have to update, former intentional will not store a value
                    calculateTimedDemand(fp, former_intentional);
                }
            }
        }
    }
}


void LpdBusinessLogicFacade::reviewObsoleteFlightPlans(int minutes_threshold)
{
    //Iterate Through all FPs and delete data only if ITOT or ILDT is in given interval

    LpdbDataBase::FPTable & fp_table = LpdbDataBase::Get().getFPTable();
    vector<string> fp_keys = fp_table.getAllIds();

    boost::posix_time::ptime now_timestamp = LctimVirtualClock::Get().getTime();

    BOOST_FOREACH (string fp_key, fp_keys)
    {
        if (fp_table.exists(fp_key))
        {
            LpiFlightPlan fp = fp_table[fp_key];

            boost::optional<posix_time::ptime> intentional = fp.getIntentionalTime();

            if (intentional)
            {
                if ((now_timestamp - *intentional).total_seconds() >= minutes_threshold * 60)
                {
#ifdef TRACE_OUT
                    LclogStream::instance(LclogConfig::E_RTP).debug() << "Deleting obsolete FP " << fp_key
                    << ", intentional time= " << *intentional << std::endl;
#endif

                    fp_table.deleteElement(fp_key);
                }
            }
        }
    }
}


void LpdBusinessLogicFacade::reviewObsoleteFlightPlansByAssignedTime(int minutes_threshold)
{
    LpdbDataBase::FPTable & fp_table = LpdbDataBase::Get().getFPTable();
    vector<string> fp_keys = fp_table.getAllIds();

    boost::posix_time::ptime now_timestamp = LctimVirtualClock::Get().getTime();

    BOOST_FOREACH (string fp_key, fp_keys)
    {
        if (fp_table.exists(fp_key))
        {
            LpiFlightPlan fp = fp_table[fp_key];

            boost::optional<posix_time::ptime> timeToCheck = boost::none;

            //1 - Check deletion by assigned time
            LpdbAlternativeSchedule & active = LpdbDataBase::Get().getActiveSchedule();

            string timeTypeForLog;

         if (active.isPlannedFP(fp_key))
            {
            timeToCheck = active.getAssignedTime(fp_key);
                timeTypeForLog = "assigned";
#ifdef TRACE_OUT
            /*
            std::cout << "Checking time for scheduled FP in active: " << fp_key << "assignedTime = " << timeToCheck;
            if (timeToCheck)
            {
               std::cout << " *assignedTime = " << *timeToCheck << std::endl;
            }
            */
#endif
            }
            else
            {
                //2 - Check deletion by intentional time
                timeToCheck = fp.getIntentionalTime();
                timeTypeForLog = "intentional";
            }

            if (timeToCheck)
            {
#ifdef TURN_ROUND
                //reviewTurnRound(fp_key);
#endif
                if ((now_timestamp - *timeToCheck).total_seconds() >= minutes_threshold * 60)
                {
                    LclogStream::instance(LclogConfig::E_RTP).debug() << "Deleting obsolete FP " << fp_key
                                 << ", " << timeTypeForLog << " time= " << *timeToCheck << std::endl;

                    fp_table.deleteElement(fp_key);
                }
            }
        }
    }
}


void LpdBusinessLogicFacade::reviewTurnRound(string fpKey)
{
    LpdbDataBase::FPTable & fpTable = LpdbDataBase::Get().getFPTable();
    boost::posix_time::ptime timeLineBegin = LpdbDataBase::Get().getTimeLineBase();

    if (fpTable.exists(fpKey))
    {
        LpiFlightPlan & fp = fpTable[fpKey];

        if ((fp.getOperationType() == LpiOperationType::E_ARRIVAL) && (fp.getTurnRoundKey() != ""))
        {
            boost::optional<posix_time::ptime> fpIldt = fp.getArrivalTimes().getIldt();

            if (fpIldt && (*fpIldt < timeLineBegin))
            {
                string associatedDEPFP = fp.getTurnRoundKey();
                LpiFlightPlan & associatedFP = fpTable[fpKey];

                fp.setTurnRoundKey("");
                fp.setClosedTurnRound(false);

                associatedFP.setTurnRoundKey("");
                associatedFP.setClosedTurnRound(false);
            }
        }
    }
}

//-----------------------------------------------------------------------------

/**@fn void LpdBusinessLogicFacade::reviewMeteoInfo(std::string new_interval)

   @brief Fall all the managed airports, check meteo info on clock
   event (add stored info to new interval)

   - Update meteo info in the DB after a CLOCK event (for all airports);
   - Send meteo info for the new interval to the HMI (for all airports)
*/
void LpdBusinessLogicFacade::reviewMeteoInfo(std::string new_interval)
{

#ifdef TRACE_OUT
  LclogStream::instance(LclogConfig::E_RTP).debug()
    << "Business Logic: forward meteo information in database. Last interval: " << new_interval
    << ", for ALL the airports ..."
    << " : File: " << __FILE__
    << " ; fn: " << __func__
    << " ; line: " << __LINE__
    << std::endl;
#endif


  ///@test for_each airport
  std::vector<std::string> airport_keys = LpdbDataBase::Get().getAirportTable().
                                                              getAllIds();
  BOOST_FOREACH(const std::string & airport_id, airport_keys)
   {
	reviewMeteoInfo(airport_id, new_interval);
   }

}

//-----------------------------------------------------------------------------

///@brief reviewMeteoInfo for the pair (airport, interval)
void LpdBusinessLogicFacade::reviewMeteoInfo(std::string airport_id,
					     std::string new_interval)
{

	LclogStream::instance(LclogConfig::E_RTP).info()
    		<< "Business Logic: forward meteo information in database. "
			<< " for airport =  <" << airport_id << '>'
			<< " , and for last interval =  <" << new_interval << '>'
			<< " ; File: " << __FILE__
			<< " ; fn: " << __func__
			<< " ; line: " << __LINE__
			<< std::endl;


  if(LpdbDataBase::Get().getNumberOfMeteoReportsReceived(airport_id) <= 0 )
  {
#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).debug()
      << "No meteo reports found for airport <" << airport_id << '>'
      << " ; File: " << __FILE__
      << " ; fn: " << __func__
      << " ; line: " << __LINE__
      << std::endl;
#endif

    return;
  }


  // I. Update DB: for each airport, for all the received reports on the airport


  // I.a) remove obsolete reports


#ifdef TRACE_OUT
  LclogStream::instance(LclogConfig::E_RTP).debug()
    << "Forward meteo on airport <" << airport_id << '>'
	<< " BEFORE deleteObsoleteMeteoReports()"
	<< " ; number of reports = " << LpdbDataBase::Get().getNumberOfMeteoReportsReceived(airport_id)
    << " ; File: " << __FILE__
    << " ; fn: " << __func__
    << " ; line: " << __LINE__
    << std::endl;
#endif

  LpdbDataBase::Get().deleteObsoleteMeteoReports(airport_id);


#ifdef TRACE_OUT
  LclogStream::instance(LclogConfig::E_RTP).debug()
    << "Forward meteo on airport <" << airport_id << '>'
	<< " AFTER deleteObsoleteMeteoReports()"
	<< " ; number of reports = " << LpdbDataBase::Get().getNumberOfMeteoReportsReceived(airport_id)
    << " ; File: " << __FILE__
    << " ; fn: " << __func__
    << " ; line: " << __LINE__
    << std::endl;
#endif


  // I.b) update data for the new (forwarded) interval


#ifdef TRACE_OUT
  LclogStream::instance(LclogConfig::E_RTP).debug() << "Reviewing "
		  << LpdbDataBase::Get().getNumberOfMeteoReportsReceived(airport_id)
		  << " meteo blocks..."
		  << " ; File: " << __FILE__
		  << " ; fn: " << __func__
		  << " ; line: " << __LINE__
		  << std::endl;
#endif


  ///@bug: std::vector:.erase within a loop : after erase the range has changed
  /// for (unsigned int i = 0; i < meteo_blocks.size(); ++i)
  ///
  for (unsigned int i = 0; i < LpdbDataBase::Get().getNumberOfMeteoReportsReceived(airport_id); ++i)
  {
	  LpiMeteoInfo meteo = LpdbDataBase::Get().getMeteoReport(airport_id, i);
	  posix_time::ptime begin_time = meteo.getStartTimeAndDate();
	  posix_time::ptime end_time = meteo.getEndTimeAndDate();

#ifdef TRACE_OUT
	  LclogStream::instance(LclogConfig::E_RTP).debug()
					  << "Meteo block " << i << ", end_time= " << end_time
					  << " NOT OBSOLETE: searching affected intervals..."
					  << " ; File: " << __FILE__
					  << " ; fn: " << __func__
					  << " ; line: " << __LINE__
					  << std::endl;
#endif

	  TimeLine<LpdbMeteoTimedData> & meteoForecast = LpdbDataBase::Get().getMeteoForecast(airport_id);

	  vector<string> affected_intervals = meteoForecast.getIntervalsInRange(begin_time, end_time);

	  //Check if new interval (the current last interval) is affected by stored report
	  vector<string>::iterator it = std::find(affected_intervals.begin(), affected_intervals.end(), new_interval);
	  if (it != affected_intervals.end())
	  {

#ifdef TRACE_OUT
		  LclogStream::instance(LclogConfig::E_RTP).debug()
    		<< "Forward meteo: afected interval: " << new_interval
			<< " ; File: " << __FILE__
			<< " ; fn: " << __func__
			<< " ; line: " << __LINE__
			<< std::endl;
#endif

		  if (meteoForecast.hasData(new_interval))
		  {

//#ifdef TRACE_OUT
//			  LclogStream::instance(LclogConfig::E_RTP).debug()
//    		<< "Forward meteo: affected interval: " << new_interval << " ; current data: "
//			<< meteoForecast[new_interval]
//							 << " ; File: " << __FILE__
//							 << " ; fn: " << __func__
//							 << " ; line: " << __LINE__
//							 << std::endl;
//#endif

			  meteoForecast[new_interval].setHorizontalVisibility(meteo.getHorizontalVisibility());
			  meteoForecast[new_interval].setWetness(meteo.getWetness());
			  meteoForecast[new_interval].setLvpActivation(meteo.getLvpActivation());
			  meteoForecast[new_interval].setIlsCategory(meteo.getRequiredILSCategory());
			  meteoForecast[new_interval].setDeicingRequired(meteo.getDeicing());

			  meteoForecast[new_interval].setWindSpeed(meteo.getWindSpeed());
			  meteoForecast[new_interval].setWindDirection(meteo.getWindDirection());

			  LpdbDataBase::Get().setMeteoForecast(airport_id, meteoForecast);

			  //Populate crosswind and tailwind of each runway
			  std::map<string, LpiRunwayMeteoInfo> runways_meteo_info;

			  vector<RVRPerRunway> runways_data =
					  meteo.getRvrperRunway().getRVRPerRunway();

			  for (unsigned int j = 0; j < runways_data.size(); j++)
			  {
				  string rwy_name = runways_data[j].getName();
				  LpiRunwayMeteoInfo information(rwy_name,
						  runways_data[j].getCrossWind(),
						  runways_data[j].getTailWind());
				  runways_meteo_info[rwy_name] = information;
			  }

			  meteoForecast[new_interval].setRwyMeteoInfo(runways_meteo_info);


#ifdef TRACE_OUT
			  LclogStream::instance(LclogConfig::E_RTP).debug()
    		<< "Forward meteo: afected interval: " << new_interval << " ; new data: "
			<< meteoForecast[new_interval]
							 << " ; File: " << __FILE__
							 << " ; fn: " << __func__
							 << " ; line: " << __LINE__
							 << std::endl;
#endif
		  }
	  }//end-if-it


  }//end-for meteo_blocks.size()




    ///@test  II. Send meteo forecast update to HMI: one timeline per airport
#ifdef TRACE_OUT
  LclogStream::instance(LclogConfig::E_RTP).info()
    << "I. Send meteo forecast update to HMI: one timeline per airport:  "
    << " for airport =  <" << airport_id << '>'
    << " , and for last interval =  <" << new_interval << '>'
    << " ; File: " << __FILE__
    << " ; fn: " << __func__
    << " ; line: " << __LINE__
    << std::endl;
#endif
    LpiUpdateMeteo airport_meteo_report;
    airport_meteo_report.setCalculationReason(LpiCalculationReason::E_CLOCK);
    airport_meteo_report.setAirport(airport_id);
    boost::optional<boost::posix_time::ptime> initialTime =
    		LpdbDataBase::Get().getMeteoForecast(airport_id).getInitialTime();
    if (initialTime.is_initialized())
    {
    	airport_meteo_report.setMessageTimeandDate(initialTime.get());
    }
    else
    {
    	airport_meteo_report.setMessageTimeandDate(ptime());
    }
    airport_meteo_report.setMeteoInfo(LpdbDataBase::Get().getReceivedMeteoReports(airport_id));
    airport_meteo_report.setTimeline(LpdbMeteoTimelineConverter::Convert2Interface
    		(LpdbDataBase::Get().getMeteoForecast(airport_id)));


    LpiUpdateMeteoList meteo_report_list;
    meteo_report_list.push_back(airport_meteo_report);

    LpiMeteoForecastEvt meteoEvt;
    meteoEvt.setMeteoForecast(meteo_report_list);
    LpdComponent::Get().publish(meteoEvt);


}


//-----------------------------------------------------------------------------


void LpdBusinessLogicFacade::updateOptimizationCriteria(const LpiOptimizationCriteria &criteria)
{
    calculateWhatIfMode1(criteria);
}

///@todo now RMAN's code
void LpdBusinessLogicFacade::updateCapacityReductions(const LpiCapacityReductions &reductions)
{
//	   LriADOVector<double> vNull(0.0, 0.0, 0.0);
//	   std::vector < LriADOVector<double> > vmanual;
//	   std::vector<bool> vnonAvalilability;
//
//	   LrdbTMA & capacityReductionsTMA =  LrdbDataBase::Get().getTMA();
//	   capacityReductionsTMA.resetPercentages();
//
//	   vector<string> intervals= LrdbDataBase::Get().getTMA().getTimeLine().getAllIntervalIds();
//	   vector<LriADOVector<double> > & capacityreductionscheduledTMA = LrdbDataBase::Get().getTMA().getManualCapacityReductionScheduled();
//
//	   LrdbTWY  & capacityReductionsTWY =  LrdbDataBase::Get().getTWY();
//	   capacityReductionsTWY.resetPercentages();
//
//	   vector<string> intervalsTWY= LrdbDataBase::Get().getTWY().getTimeLine().getAllIntervalIds();
//	   vector<LriADOVector<double> > & capacityreductionscheduledTWY = LrdbDataBase::Get().getTWY().getManualCapacityReductionScheduled();
//
//	   LrdbDataBase::RunwayTable &  runwayTable = LrdbDataBase::Get().getRunwayTable();
//	   vector<string> ids_runways=runwayTable.getAllIds();
//
//
//	   BOOST_FOREACH(string ti,intervals)
//	   {
//	      capacityreductionscheduledTMA.push_back(vNull);
//	      capacityreductionscheduledTWY.push_back(vNull);
//	      vmanual.push_back(vNull);
//	      vnonAvalilability.push_back(0);
//	   }
//
//	   BOOST_FOREACH(string id, ids_runways)
//	   {
//	       LrdbRunway & runway=runwayTable[id];
//	       runway.setManualCapacityReductionScheduled(vmanual);
//	       runway.setNonAvailabilityScheduled(vnonAvalilability);
//	   }
//
//
//	   for(unsigned int i = 0; i < reductions.getcapacityReductionsTMA().getCapacityReductions().size(); i++)
//	   {
//	      boost::optional<posix_time::ptime> begin_time= reductions.getcapacityReductionsTMA().getCapacityReductions(i).getstartTimeAndDate();
//	      boost::optional<posix_time::ptime> end_time = reductions.getcapacityReductionsTMA().getCapacityReductions(i).getendTimeAndDate();
//
//	      if (begin_time && end_time)
//	      {
//	         vector<string> affected_intervals = LrdbDataBase::Get().getTMA().getTimeLine().getIntervalsInRange(*begin_time, *end_time);
//	         BOOST_FOREACH(string ti, affected_intervals)
//	         {
//	            if(capacityReductionsTMA.has_data(ti))
//	            {
//	               LriADOVector<double> vcapacityreductions(reductions.getcapacityReductionsTMA().getCapacityReductions(i).getvectorADO().getarrivalsValue(),
//	                                                        reductions.getcapacityReductionsTMA().getCapacityReductions(i).getvectorADO().getdeparturesValue(),
//	                                                        reductions.getcapacityReductionsTMA().getCapacityReductions(i).getvectorADO().getoverallValue());
//
//	               LriADOVector<double> maxTMACapacity = capacityReductionsTMA[ti].getCapacity();
//
//	               for (int j = E_ARR; j <= E_OVA; ++j)
//	               {
//	                  if (vcapacityreductions[j] >= 0.0)
//	                  {
//	                     double int_part = 0.0;
//	                     vcapacityreductions[j] = int_part;
//	                  }
//	                  else
//	                  {
//	                     vcapacityreductions[j] = maxTMACapacity[j];
//	                  }
//	               }
//
//	               capacityReductionsTMA[ti].hasManualReduction(true);
//	               capacityReductionsTMA[ti].setManualCapacityReduction(vcapacityreductions);
//
//	               std::string tmp_a(ti);
//	               boost::erase_all(tmp_a, "t");
//	               unsigned int t_number= boost::lexical_cast<unsigned int>(tmp_a);
//
//	               capacityreductionscheduledTMA[t_number] = vcapacityreductions;
//	            }
//	         }
//	      }
//	   }
//
//
//	   for(unsigned int i = 0; i < reductions.getcapacityReductionsTWY().getCapacityReductions().size(); i++)
//	   {
//	      boost::optional<posix_time::ptime> begin_time= reductions.getcapacityReductionsTWY().getCapacityReductions(i).getstartTimeAndDate();
//	      boost::optional<posix_time::ptime> end_time = reductions.getcapacityReductionsTWY().getCapacityReductions(i).getendTimeAndDate();
//
//	      if (begin_time && end_time)
//	      {
//	         vector<string> affected_intervalsTWY= LrdbDataBase::Get().getTWY().getTimeLine().getIntervalsInRange(*begin_time, *end_time);
//	         BOOST_FOREACH(string ti, affected_intervalsTWY)
//	         {
//	            if(capacityReductionsTWY.has_data(ti))
//	            {
//	               LriADOVector<double> vcapacityreductions(reductions.getcapacityReductionsTWY().getCapacityReductions(i).getvectorADO().getarrivalsValue(),
//	                                                        reductions.getcapacityReductionsTWY().getCapacityReductions(i).getvectorADO().getdeparturesValue(),
//	                                                        reductions.getcapacityReductionsTWY().getCapacityReductions(i).getvectorADO().getoverallValue());
//
//	               LriADOVector<double> maxTWYCapacity = capacityReductionsTWY[ti].getCapacity();
//
//	               for (int j = E_ARR; j <= E_OVA; ++j)
//	               {
//	                  if (vcapacityreductions[j] >= 0.0)
//	                  {
//	                     double int_part = 0.0;
//	                     vcapacityreductions[j] = int_part;
//	                  }
//	                  else
//	                  {
//	                     vcapacityreductions[j] = maxTWYCapacity[j];
//	                  }
//	               }
//
//	               capacityReductionsTWY[ti].hasManualReduction(true);
//	               capacityReductionsTWY[ti].setManualCapacityReduction(vcapacityreductions);
//
//	               std::string tmp_a(ti);
//	               boost::erase_all(tmp_a, "t");
//	               unsigned int t_number= boost::lexical_cast<unsigned int>(tmp_a);
//
//	               capacityreductionscheduledTWY[t_number] = vcapacityreductions;
//	            }
//	         }
//	      }
//	   }
//
//	   //Reset all availabilities prior to activation
//
//	   vector<string> runway_identifiers = runwayTable.getAllIds();
//
//	   BOOST_FOREACH(string runway_id, runway_identifiers)
//	   {
//	      if(runwayTable.exists(runway_id))
//	      {
//	            LrdbRunway & runway= runwayTable[runway_id];
//	            runway.resetOperationalStateInputs();
//	      }
//	   }
//
//	   vector<string>  ids_rwys;
//	   for(unsigned int i = 0; i< reductions.getcapacityReductionsRUNWY().size(); i++)
//	   {
//	     string runway_id = reductions.getcapacityReductionsRUNWY()[i].getrunway();
//	     boost::algorithm::trim(runway_id);
//
//	     if(runwayTable.exists(runway_id))
//	     {
//	        ids_rwys.push_back(runway_id);
//	        LrdbRunway & runway = runwayTable[runway_id];
//
//	        boost::optional<posix_time::ptime> begin_time= reductions.getcapacityReductionsRUNWY()[i].getstartTimeAndDate();
//	        boost::optional<posix_time::ptime> end_time = reductions.getcapacityReductionsRUNWY()[i].getendTimeAndDate();
//
//	        if (begin_time && end_time)
//	        {
//	           LriADOVector<double> vreductions(reductions.getcapacityReductionsRUNWY()[i].getvectorADO().getarrivalsValue(),
//	                                            reductions.getcapacityReductionsRUNWY()[i].getvectorADO().getdeparturesValue(),
//	                                            reductions.getcapacityReductionsRUNWY()[i].getvectorADO().getoverallValue());
//
//	           runway.applyManualReduction(*begin_time, *end_time, vreductions);
//	        }
//	     }
//	   }
//
//	    for(unsigned int i = 0; i < reductions.getnonAvailabilityRUNWY().size(); i++)
//	    {
//	       if(runwayTable.exists(reductions.getnonAvailabilityRUNWY()[i].getrunway()))
//	       {
//	         LrdbRunway & runway = runwayTable[reductions.getnonAvailabilityRUNWY()[i].getrunway()];
//	         boost::optional<posix_time::ptime> begin_time= reductions.getnonAvailabilityRUNWY()[i].getstartTimeAndDate();
//	         boost::optional<posix_time::ptime> end_time = reductions.getnonAvailabilityRUNWY()[i].getendTimeAndDate();
//
//	         LriClosureReason::LriEnum reason = reductions.getnonAvailabilityRUNWY()[i].getReason();
//
//	         if(begin_time && end_time)
//	         {
//	            bool isNonAvailable = 1;
//	            runway.applyNoOperationReduction(*begin_time, *end_time, reason, isNonAvailable);
//	         }
//	       }
//	    }
//
//	#ifdef TRACE_OUT
//	   LclogStream::instance(LclogConfig::E_RTP).debug() << LrdbDataBase::Get().getCapacityReductionsAsString(ids_rwys) << std::endl;
//	#endif

}

//------------------------------------------------------------------------------


void LpdBusinessLogicFacade::updateMeteoNowcast(const LpiCreateMeteoList & meteolist)
{

#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).debug()
      << "RTP-MeteoNowcast-CONSUMER: New meteo info: "
      << " : File: " << __FILE__
      << " ; fn: " << __func__
      << " ; line: " << __LINE__
      << std::endl;
#endif


    // section I: update DB with the new meteo data
    updateMeteoNowcastDB(meteolist);



///@test db_meteo_nowcast: Here the stored (airport, interval) data in the DB.
#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).debug()
      << " : File: " << __FILE__
      << " ; fn: " << __func__
      << " ; line: " << __LINE__
      << " ; Meteo DB (nowcast) updated: "
      << std::endl;
    for(unsigned int meteo_data_i = 0;
    		meteo_data_i < meteolist.size();
    		++meteo_data_i)
    {
    	LclogStream::instance(LclogConfig::E_RTP).debug()
	  << "Airport: <" << meteolist[meteo_data_i].getAirport() << ">\n"
	  << LpdbDataBase::Get().getMeteoForecast(meteolist[meteo_data_i].getAirport());   
    }
#endif

    

    // section II (depends on the timeline stored in the DB): send the
    // meteo data to the HMI
    updateMeteoNowcastHmi(meteolist);


    ///@todo section III: update the optimal schedule using the new meteo data
    /// void LpdBusinessLogicFacade::updateMeteoNowcastSchedule(const LpiCreateMeteoList & meteolist)

    /** @todo Upon RTP's CORE construction review the following code. (it is the RMAN's code)


 setExpirationDateForWhatIfs(LctimVirtualClock::Get().getTime());

   #ifdef TRACE_OUT
   LclogStream::instance(LclogConfig::E_RTP).info() << "OPTIMAL SCHEDULE CALCULATION" <<std::endl;
   LclogStream::instance(LclogConfig::E_RTP).info() << "Calculation cause: Meteo Nowcast input received" <<std::endl;
   #endif

   string our_airport = LpdbDataBase::Get().getGlobalParameters().getAerodromeName();

   if (meteolist.getairport() != our_airport)
   {
   #ifdef TRACE_OUT
   LclogStream::instance(LclogConfig::E_RTP).info() << "Business Logic: meteorological information doesn't concern our airport..." << std::endl;
   LclogStream::instance(LclogConfig::E_RTP).info() << "Meteo airport:" << meteolist.getairport() << std::endl;
   LclogStream::instance(LclogConfig::E_RTP).info() << "Our airport:" << our_airport << std::endl;
   #endif
   return;
   }


     calculateMaxCapacities();
     calculateEstimatedDCB();

     #ifdef TRACE_OUT
     LclogStream::instance(LclogConfig::E_RTP).debug() << "Estimated DCB calculations: " << std::endl;
     LclogStream::instance(LclogConfig::E_RTP).debug() << LpdbDataBase::Get().getEstimatedDCBAsString() << std::endl;

     LclogStream::instance(LclogConfig::E_RTP).debug() << "Invocation to schedules generation..." << std::endl;
     #endif

     generateSchedulesForAllIntervals();

     calculateRealDCBAndRunwayAllocation();

     #ifdef TRACE_OUT
     LclogStream::instance(LclogConfig::E_RTP).info() << "FPS Schedule calculations..." <<std::endl;
     #endif

     performFPInScheduleCalculations();

     #ifdef TRACE_OUT
     LclogStream::instance(LclogConfig::E_RTP).info() << "Calculate KPIs..." << std::endl;
     #endif

     bool isClockForwarding = false;
     calculateSchedulesKPIs(isClockForwarding);

     #ifdef TRACE_OUT
     LclogStream::instance(LclogConfig::E_RTP).info() << "Calculate Optimal Schedule..." << std::endl;
     #endif

     generateOptimalSchedule();

     performActiveScheduleCalculations(isClockForwarding);

     publishOptimalAndActiveSchedules(LpiCalculationReason::E_NEW_METEO_NOWCAST);

     #ifdef TRACE_OUT
     LclogStream::instance(LclogConfig::E_RTP).info() << "[RUNWAY FINAL ASSIGNATION]: " << std::endl;
     #endif

     calculateRunwayFinalAssignation();

     LpdbDataBase::Get().setInputReceivedInLastInterval(true); */


}

//------------------------------------------------------------------------------

void LpdBusinessLogicFacade::updateMeteoForecast(const LpiCreateMeteoList &meteolist)
{

#ifdef TRACE_OUT

    LclogStream::instance(LclogConfig::E_RTP).debug()
      << "RTP-MeteoForecast-CONSUMER: New meteo info: "
      << " : File: " << __FILE__
      << " ; fn: " << __func__
      << " ; line: " << __LINE__
      << std::endl;
#endif


    // section I: update DB with the new meteo data
    updateMeteoForecastDB(meteolist);
    

#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).debug()
      << " : File: " << __FILE__
      << " ; fn: " << __func__
      << " ; line: " << __LINE__
      << "Meteo DB (forecast) updated: "
      << std::endl;
    for(unsigned int meteo_data_i = 0;
	meteo_data_i < meteolist.size();
	++meteo_data_i)
      {
    	LclogStream::instance(LclogConfig::E_RTP).debug()
	  << LpdbDataBase::Get().getMeteoForecast(meteolist[meteo_data_i].
						  getAirport());
      }
#endif


    // section II (depends on the timeline stored in the DB): send the meteo data to the HMI
    updateMeteoForecastHmi(meteolist);


    ///@todo section III: update the optimal schedule using the new meteo data
    /// void LpdBusinessLogicFacade::updateMeteoForecastSchedule(const LpiCreateMeteoList & meteolist)


//    setExpirationDateForWhatIfs(LctimVirtualClock::Get().getTime());
//
//#ifdef TRACE_OUT
//    LclogStream::instance(LclogConfig::E_RTP).info() << "OPTIMAL SCHEDULE CALCULATION" <<std::endl;
//    LclogStream::instance(LclogConfig::E_RTP).info() << "Calculation cause: Meteo Forecast input received" <<std::endl;
//#endif


    //
    //    //Process meteo information only if concerns to our airport
    //    string our_airport = LpdbDataBase::Get().getGlobalParameters().getAerodromeName();
    //    if (meteolist.getairport() != our_airport)
    //    {
    //#ifdef TRACE_OUT
    //        LclogStream::instance(LclogConfig::E_RTP).info() << "Business Logic: meteorological information doesn't concern our airport..." << std::endl;
    //#endif
    //
    //        return;
    //    }

//
//    calculateMaxCapacities();
//    calculateEstimatedDCB();
//
//#ifdef TRACE_OUT
//    LclogStream::instance(LclogConfig::E_RTP).debug() << "Estimated DCB calculations: " << std::endl;
//    LclogStream::instance(LclogConfig::E_RTP).debug() << LpdbDataBase::Get().getEstimatedDCBAsString() << std::endl;
//
//    LclogStream::instance(LclogConfig::E_RTP).debug() << "Invocation to schedules generation..." << std::endl;
//#endif
//
//    generateSchedulesForAllIntervals();
//
//    calculateRealDCBAndRunwayAllocation();
//
//#ifdef TRACE_OUT
//    LclogStream::instance(LclogConfig::E_RTP).info() << "FPS Schedule calculations..." <<std::endl;
//#endif
//
//    performFPInScheduleCalculations();
//
//#ifdef TRACE_OUT
//    LclogStream::instance(LclogConfig::E_RTP).info() << "Calculate KPIs..." << std::endl;
//#endif
//
//    bool isClockForwarding = false;
//    calculateSchedulesKPIs(isClockForwarding);
//
//#ifdef TRACE_OUT
//    LclogStream::instance(LclogConfig::E_RTP).info() << "Calculate Optimal Schedule..." << std::endl;
//#endif
//
//    generateOptimalSchedule();
//
//    performActiveScheduleCalculations(isClockForwarding);
//
//    publishOptimalAndActiveSchedules(LpiCalculationReason::E_NEW_METEO_FORECAST);
//
//#ifdef TRACE_OUT
//    LclogStream::instance(LclogConfig::E_RTP).info() << "[RUNWAY FINAL ASSIGNATION]: " << std::endl;
//#endif
//
//    calculateRunwayFinalAssignation();
//
//    LpdbDataBase::Get().setInputReceivedInLastInterval(true);
}

//------------------------------------------------------------------------------

///@brief update DB with the new meteo NOWcast data received for N airports
void LpdBusinessLogicFacade::updateMeteoNowcastDB(const LpiCreateMeteoList & meteolist)
{

#ifdef TRACE_OUT
  LclogStream::instance(LclogConfig::E_RTP).debug()
    << "Business Logic: updating (nowcast) meteo information in database "
    << " for N airports ..."
    << " : File: " << __FILE__
    << " ; fn: " << __func__
    << " ; line: " << __LINE__
    << std::endl;
#endif

  ///@test for_each airport
  for(unsigned int meteo_data_i = 0;
      meteo_data_i < meteolist.size();
      ++meteo_data_i)
  {
    updateMeteoNowcastDB(meteolist[meteo_data_i]);
  }

}

//------------------------------------------------------------------------------

///@brief update DB with the new meteo NOWcast data received for 1 airport
void LpdBusinessLogicFacade::updateMeteoNowcastDB(const LpiCreateMeteo & meteoData)
{

#ifdef TRACE_OUT
  LclogStream::instance(LclogConfig::E_RTP).info()
    << "Business Logic: updating (nowcast) meteo information in database "
    << " for airport <" << meteoData.getAirport() << '>'
    << " : File: " << __FILE__
    << " ; fn: " << __func__
    << " ; line: " << __LINE__
    << std::endl;
#endif


  for (unsigned int i = 0; i < meteoData.getMeteoInfo().size(); i++)
  {
    
#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).info() 
      << "Adding received Meteorological Nowcast block to DB." << std::endl;
#endif
    
    LpdbDataBase::Get().addMeteoReport(meteoData.getAirport(), meteoData.getMeteoInfo()[i]);
  }

  
  /// ... for each meteo-bodyInformation
  vector<LpiMeteoInfo> meteo_blocks = meteoData.getMeteoInfo();
  for(unsigned int i = 0; i < meteo_blocks.size(); ++i)
  {
    LpiMeteoInfo meteo = meteo_blocks[i];

    TimeLine<LpdbMeteoTimedData>  & meteoForecast =
      LpdbDataBase::Get().getMeteoForecast(meteoData.getAirport());

    vector<string> affected_intervals = meteoForecast.getIntervalsInRange
      (meteo.getStartTimeAndDate(), meteo.getEndTimeAndDate());

    //for each interval affected by the meteo-bodyInformation
    BOOST_FOREACH(string ti, affected_intervals)
    {
      
#ifdef TRACE_OUT
      LclogStream::instance(LclogConfig::E_RTP).debug()
	<< "interval: <" << ti << '>' << std::endl;
#endif

      if (meteoForecast.hasData(ti))
      {
	meteoForecast[ti].setHasNowcastReport(true);
	meteoForecast[ti].setHorizontalVisibility(meteo.
						  getHorizontalVisibility());
	meteoForecast[ti].setWetness(meteo.getWetness());
	meteoForecast[ti].setLvpActivation(meteo.getLvpActivation());
	meteoForecast[ti].setIlsCategory(meteo.getRequiredILSCategory());

	///@todo FIXME: phenomenon / PE
	meteoForecast[ti].setDeicingRequired(meteo.getDeicing());

	///@warning unused in RTP
	meteoForecast[ti].setWindSpeed(meteo.getWindSpeed());
	meteoForecast[ti].setWindDirection(meteo.getWindDirection());

	LpdbDataBase::Get().setMeteoForecast(meteoData.getAirport(),
					     meteoForecast);

	//Populate crosswind and tailwind of each runway
	std::map<string, LpiRunwayMeteoInfo> runways_meteo_info;
	vector<RVRPerRunway> runways_data = meteo.getRvrperRunway().
	                                          getRVRPerRunway();

	for (unsigned int j = 0; j < runways_data.size(); ++j)
	{
	  std::string rwy_name = runways_data[j].getName();
	  LpiRunwayMeteoInfo information(rwy_name,
					 runways_data[j].getCrossWind(),
					 runways_data[j].getTailWind());
	  runways_meteo_info[rwy_name] = information;
	}
	meteoForecast[ti].setRwyMeteoInfo(runways_meteo_info);
      }
    }//end-BOOST_FOREACH
  }

  LpdbDataBase::Get().setInputReceivedInLastInterval(true);
}

//-----------------------------------------------------------------------------

///@brief update DB with the new meteo FOREcast data received
void LpdBusinessLogicFacade::updateMeteoForecastDB(const LpiCreateMeteoList & meteolist)
{

#ifdef TRACE_OUT
  LclogStream::instance(LclogConfig::E_RTP).debug()
    << "Business Logic: updating (forecast) meteo information in database "
    << " for N airports ..."
    << " : File: " << __FILE__
    << " ; fn: " << __func__
    << " ; line: " << __LINE__
    << std::endl;
#endif

  ///@test for_each airport
  for(unsigned int meteo_data_i = 0;
      meteo_data_i < meteolist.size();
      ++meteo_data_i)
  {
    updateMeteoForecastDB(meteolist[meteo_data_i]);
  }
  
}

//-----------------------------------------------------------------------------

///@brief update DB with the new meteo FOREcast data received for 1 airport
void LpdBusinessLogicFacade::updateMeteoForecastDB(const LpiCreateMeteo & meteoData)
{

#ifdef TRACE_OUT
  LclogStream::instance(LclogConfig::E_RTP).info()
    << "Business Logic: updating (forecast) meteo information in database "
    << " for airport <" << meteoData.getAirport() << '>'
    << " : File: " << __FILE__
    << " ; fn: " << __func__
    << " ; line: " << __LINE__
    << std::endl;
#endif


  for (unsigned int i = 0; i < meteoData.getMeteoInfo().size(); i++)
  {
#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).info()
      << "Adding received Meteorological Forecast block to DB." << std::endl;
#endif
    
    LpdbDataBase::Get().addMeteoReport(meteoData.getAirport(), meteoData.getMeteoInfo()[i]);
  }

 
  /// ... for each meteo-bodyInformation
  vector<LpiMeteoInfo> meteo_blocks = meteoData.getMeteoInfo();  
  for (unsigned int i = 0; i < meteo_blocks.size(); ++i)
  {
    LpiMeteoInfo meteo = meteo_blocks[i];

    TimeLine<LpdbMeteoTimedData> & meteoForecast =
      LpdbDataBase::Get().getMeteoForecast(meteoData.getAirport());
	
    vector<string> affected_intervals = meteoForecast.getIntervalsInRange
      (meteo.getStartTimeAndDate(), meteo.getEndTimeAndDate());

    //for each interval affected by the meteo-bodyInformation	
    BOOST_FOREACH(string ti, affected_intervals)
    {
      
#ifdef TRACE_OUT
      LclogStream::instance(LclogConfig::E_RTP).debug()
	<< "interval: <" << ti << '>' << std::endl;
#endif
      
      if (meteoForecast.hasData(ti)
	  ///@warning requirement: nowcast has preference over forecast
	  and (meteoForecast[ti].getHasNowcastReport() == false))
      {
	
	meteoForecast[ti].setHorizontalVisibility(meteo.
						  getHorizontalVisibility());
	meteoForecast[ti].setWetness(meteo.getWetness());
	meteoForecast[ti].setLvpActivation(meteo.getLvpActivation());
	meteoForecast[ti].setIlsCategory(meteo.getRequiredILSCategory());

	///@todo FIXME: phenomenon / PE
	meteoForecast[ti].setDeicingRequired(meteo.getDeicing());

	///@warning unused in RTP
	meteoForecast[ti].setWindSpeed(meteo.getWindSpeed());
	meteoForecast[ti].setWindDirection(meteo.getWindDirection());

	LpdbDataBase::Get().setMeteoForecast(meteoData.getAirport(),
					     meteoForecast);

	//Populate crosswind and tailwind of each runway
	std::map<string, LpiRunwayMeteoInfo> runways_meteo_info;
	vector<RVRPerRunway> runways_data = meteo.getRvrperRunway().
	                                          getRVRPerRunway();

	for (unsigned int j = 0; j < runways_data.size(); ++j)
	{
	  std::string rwy_name = runways_data[j].getName();
	  LpiRunwayMeteoInfo information(rwy_name,
					 runways_data[j].getCrossWind(),
					 runways_data[j].getTailWind());
	  runways_meteo_info[rwy_name] = information;
	}
	meteoForecast[ti].setRwyMeteoInfo(runways_meteo_info);
      }
      else
      {
#ifdef TRACE_OUT
	LclogStream::instance(LclogConfig::E_RTP).info()
	  << "Meteorological Forecast Report has been discarded for interval:"
	  << ti << " because it already has a Nowcast Report"
	  << std::endl;
#endif
	}
	    
    }//end-BOOST_FOREACH
	
  }//end-for
	
}
  
//-----------------------------------------------------------------------------

///@brief Send Meteo (nowcast) data to the HMI
void LpdBusinessLogicFacade::updateMeteoNowcastHmi
(const LpiCreateMeteoList & meteolist)
{

#ifdef TRACE_OUT
  LclogStream::instance(LclogConfig::E_RTP).debug()
    << "METEO-NOWCAST to HMI"
    << " : File: " << __FILE__
    << " ; fn: " << __func__
    << " ; line: " << __LINE__
    << std::endl;
#endif


  LpiCreateMeteoList meteoReport = meteolist;  // to update setTimeline

  /**@warning If we don't explicitly set calculationReason & timeline fields,
              then iMASBlue error "...deserialize..", and the data never gets
              to the HMI consumer.
  */
    std::for_each(std::begin(meteoReport), std::end(meteoReport),
		  [](LpiCreateMeteo &val)
    {
      val.setCalculationReason(LpiCalculationReason::E_NEW_METEO_NOWCAST);
      val.setTimeline(LpdbMeteoTimelineConverter::Convert2Interface
		      (LpdbDataBase::Get().getMeteoForecast(val.getAirport())));
    });

  //////////////////////////
#ifdef TRACE_OUT
  LclogStream::instance(LclogConfig::E_RTP).debug()
    << "RTP-MeteoNowcast-CONSUMER: New meteo info: "
    << " : File: " << __FILE__
    << " ; fn: " << __func__
    << " ; line: " << __LINE__
    << "\n LpiCreateMeteoList & meteoReport: size = "
    << meteoReport.size()
    << " ; list: ";

  std::for_each(std::begin(meteoReport),
		std::end(meteoReport),
		[](const LpiCreateMeteo &val)
		{
		  LclogStream::instance(LclogConfig::E_RTP).debug()
		    << val << std::endl;
		});
#endif
  //////////////////////////


  // Send MeteoNowcast to HMI
  LpiMeteoNowcastEvt meteoEvt;
  meteoEvt.setMeteoNowcast(meteoReport);
  LpdComponent::Get().publish(meteoEvt);

}

//------------------------------------------------------------------------------

///@brief Send Meteo (forecast) data to the HMI
void LpdBusinessLogicFacade::updateMeteoForecastHmi
(const LpiCreateMeteoList & meteolist)
{

#ifdef TRACE_OUT
  LclogStream::instance(LclogConfig::E_RTP).debug()
    << "METEO-FORECAST to HMI"
    << " : File: " << __FILE__
    << " ; fn: " << __func__
    << " ; line: " << __LINE__
    << std::endl;
#endif


  LpiCreateMeteoList meteoReport = meteolist; // to update setTimeline


    /**@warning If we don't explicitly set calculationReason & timeline fields,
       then iMASBlue error "...deserialize..", and the data never gets
       to the HMI consumer.
    */
    std::for_each(std::begin(meteoReport), std::end(meteoReport),
		  [](LpiCreateMeteo &val)
    {
      val.setCalculationReason(LpiCalculationReason::E_NEW_METEO_FORECAST);     
      val.setTimeline(LpdbMeteoTimelineConverter::Convert2Interface
		      (LpdbDataBase::Get().getMeteoForecast(val.getAirport())));
    });
    

  LpiMeteoForecastEvt meteoEvt;
  meteoEvt.setMeteoForecast(meteoReport);
  LpdComponent::Get().publish(meteoEvt);
}

//------------------------------------------------------------------------------

void LpdBusinessLogicFacade::updateScheduleActivation(const LpiScheduleActivation & scheduleActivation)
{
    activateSchedule(scheduleActivation.getScheduleId(), LpiScheduleActivationType::E_MANUAL);

    publishActiveSchedule(LpiCalculationReason::E_MANUAL_ACTIVATION);
}

void LpdBusinessLogicFacade::calculateSchedulesKPIs(bool isClockForwarding, bool isInitialization)
{
    LpdbDataBase::ScheduleTable & schTable = LpdbDataBase::Get().getScheduleTable();
    vector<int> schedule_ids = schTable.getAllIds();

//    LpiConfigurationAlertKPIs alertKPIs;
//    LpiResult result;
//    getConfigurationAlertKPIs(alertKPIs, result);

//    LpiConfigurationParameters config;
//    getConfigurationParameters(config, result);
//
//    int delayThreshold = config.getMaxForecastedDelayThreshold();
//
//    for (int i = 0; i < schTable.getNumberOfElements(); i++)
//    {
//        schTable[i].generateKPIs(alertKPIs, delayThreshold, isClockForwarding, isInitialization);
//    }
}

void LpdBusinessLogicFacade::generateOptimalSchedule()
{
    std::stringstream sOutput;

    LpdbDataBase::ScheduleTable & schTable = LpdbDataBase::Get().getScheduleTable();

    if (schTable.getNumberOfElements() > 0)
    {
        LpdbDataBase & db = LpdbDataBase::Get();

        LpdbSchedule new_optimal = schTable[0];

        db.setOptimalSchedule(new_optimal);
    }
}

void LpdBusinessLogicFacade::generateSchedulesForAllIntervals(void)
{/*
    //Execution time measuring
    //boost::chrono::thread_clock::time_point start_time = boost::chrono::thread_clock::now();

    //Schedules will be stored in DataBase

    LpdbDataBase::ScheduleTable & schTable = LpdbDataBase::Get().getScheduleTable();
    schTable.clear();

    bool empty_demand = LpdbDataBase::Get().getDemand("").isEmpty();

    if (empty_demand)
    {

        boost::optional<LpdbSchedule> default_schedule = _schedules_generator->getDefaultSchedule();

        if (default_schedule)
        {
            (*default_schedule).setOrigin(LpiActivationType::E_PREFERENTIAL);

            schTable.addElement(0, *default_schedule);

            //         boost::chrono::thread_clock::time_point end_time = boost::chrono::thread_clock::now(); //error: variable ‘fract_part’ set but not used [-Werror=unused-but-set-variable]

            return;
        }
    }

    LpdbDataBase::RunwaySystemTable & rsTable = LpdbDataBase::Get().getRunwaySystemTable();

    vector<string> runway_systems = rsTable.getAllIds();

    if (runway_systems.size() > 0)
    {
        string id = runway_systems[0];

        vector<string> intervals = rsTable[id].getTimeLine().getAllIntervalIds();
        vector<string> frozen = rsTable[id].getTimeLine().getFrozenIntervals();
        vector<string> notFrozen = rsTable[id].getTimeLine().getNotFrozenIntervals();

        string initial_node = "BEGIN";

        bool hasFrozenNodes = false;

        bool existsActiveSchedule = LpdbDataBase::Get().hasActiveSchedule();

        if (existsActiveSchedule)
        {
            LpdbAlternativeSchedule & active = LpdbDataBase::Get().getActiveSchedule();

            if (active.isManuallyActivated() && (frozen.size() > 0))
            {
                string lastFrozenInterval = frozen.back();

                TimeLine<LpdbSCHTimedData> schedule_timeline = active.getTimeLine();

                if (schedule_timeline.hasData(lastFrozenInterval))
                {
                    initial_node = schedule_timeline[lastFrozenInterval].getRsScheduled().getRunwaySystemId();
                    intervals = notFrozen;

                    hasFrozenNodes = true;
                }
            }
        }

        _schedules_generator->createGraph(runway_systems, intervals, initial_node);

#ifdef TRACE_OUT
        //Logging
        if (hasFrozenNodes)
        {
            LclogStream::instance(LclogConfig::E_RTP).debug() << "[FROZEN DATA]: " << std::endl;
            LclogStream::instance(LclogConfig::E_RTP).debug() << "Active schedule has been manually activated, and there is frozen period." << std::endl;

            LclogStream::instance(LclogConfig::E_RTP).debug() << "Initial node: " << initial_node << ", Frozen intervals: ";

            std::copy(frozen.begin(), frozen.end(),
                    std::ostream_iterator<std::string>(LclogStream::instance(LclogConfig::E_RTP).debug(), " "));
            LclogStream::instance(LclogConfig::E_RTP).debug() << std::endl;
        }
        else
        {
            LclogStream::instance(LclogConfig::E_RTP).debug() << "[FROZEN DATA]: " << std::endl;
            LclogStream::instance(LclogConfig::E_RTP).debug() << "Active schedule has not been manually activated, or there is no frozen period." << std::endl;
        }

        LclogStream::instance(LclogConfig::E_RTP).debug() << "[ALGORITHM TRANSITION MATRIX]: " << std::endl;
        LclogStream::instance(LclogConfig::E_RTP).debug() << _schedules_generator->getTransitionMatrixAsString() << std::endl;
#endif

        _schedules_generator->generateSchedules(initial_node, 1);

        LpdbSchedule solution;

        if (hasFrozenNodes)
        {
            vector<string> frozenOfActive = frozen;
            solution = _schedules_generator->getSolution(frozen, frozenOfActive, LpdbSchedule::E_ACTIVE);
            solution.setFrozenPeriods(frozen.size());
        }
        else
        {
            solution = _schedules_generator->getBestSolution();
        }

        solution.setOrigin(LpiActivationType::E_OPTIMAL);
        schTable.addElement(0, solution);
    }

    // boost::chrono::thread_clock::time_point end_time = boost::chrono::thread_clock::now();
    // std::cout << "Schedules generation (algorithm invocation): " << boost::chrono::duration_cast<boost::chrono::milliseconds>(end_time - start_time).count() << " ms\n";
*/
}

void LpdBusinessLogicFacade::generateSchedulesForLastInterval(string new_interval)
{/*
    //Execution time measuring
    //   boost::chrono::thread_clock::time_point start_time = boost::chrono::thread_clock::now();

    //Schedules will be stored in DataBase

    LpdbDataBase::ScheduleTable & schTable = LpdbDataBase::Get().getScheduleTable();
    schTable.clear();

    bool empty_demand = LpdbDataBase::Get().getDemand("").isEmpty();

    if (empty_demand)
    {

        boost::optional<LpdbSchedule> default_schedule = _schedules_generator->getDefaultSchedule();

        if (default_schedule)
        {
            (*default_schedule).setOrigin(LpiActivationType::E_PREFERENTIAL);

            schTable.addElement(0, *default_schedule);

            // boost::chrono::thread_clock::time_point end_time = boost::chrono::thread_clock::now();
            // std::cout << "Schedules generation (default schedule): " << boost::chrono::duration_cast<boost::chrono::milliseconds>(end_time - start_time).count() << " ms\n";

            return;
        }
    }

    LpdbDataBase::RunwaySystemTable & rsTable = LpdbDataBase::Get().getRunwaySystemTable();

    vector<string> runway_systems = rsTable.getAllIds();
    vector<string> intervals(1, new_interval);

    if (runway_systems.size() > 0)
    {

        bool exists_previous_optimal_schedule = LpdbDataBase::Get().hasOptimalSchedule();

        if (exists_previous_optimal_schedule)
        {
            LpdbSchedule previous_optimal = LpdbDataBase::Get().getOptimalSchedule();

            TimeLine<LpdbSCHTimedData> schedule_timeline = previous_optimal.getTimeLine();

            //Get last interval planned RS and estimated delayed fps
            string last_interval = schedule_timeline.getLastInterval();

            if (schedule_timeline.hasData(last_interval))
            {
                string previous_final_node = schedule_timeline[last_interval].getRsScheduled().getRunwaySystemId();

                if (rsTable.exists(previous_final_node))
                {
                    LpdbRunwaySystem & first_rs = rsTable[previous_final_node];
                    if (first_rs.has_data(last_interval))
                    {
                        LpiADOVector<int> estimated_delayed = first_rs[last_interval].getEstimatedDelayedFps();

                        _schedules_generator->createGraph(runway_systems, intervals, previous_final_node,
                                                          estimated_delayed);

#ifdef TRACE_OUT
                        LclogStream::instance(LclogConfig::E_RTP).debug() << "[ALGORITHM TRANSITION MATRIX]: " << std::endl;
                        LclogStream::instance(LclogConfig::E_RTP).debug() << _schedules_generator->getTransitionMatrixAsString() << std::endl;
#endif

                        _schedules_generator->generateSchedules(previous_final_node, 1);

                        previous_optimal.forward();
                        previous_optimal[new_interval] = _schedules_generator->getSolutionForInterval();

                        schTable.addElement(0, previous_optimal);
                    }
                }
            }
        }
    }*/
}

void LpdBusinessLogicFacade::generateSchedulesForClock(int minutesFrozenForClock)
{/*
    //Schedules will be stored in DataBase

    LpdbDataBase::ScheduleTable & schTable = LpdbDataBase::Get().getScheduleTable();
    schTable.clear();

    bool empty_demand = LpdbDataBase::Get().getDemand("").isEmpty();

    if (empty_demand)
    {
        boost::optional<LpdbSchedule> default_schedule = _schedules_generator->getDefaultSchedule();

        if (default_schedule)
        {
            (*default_schedule).setOrigin(LpiActivationType::E_PREFERENTIAL);

            schTable.addElement(0, *default_schedule);

            return;
        }
    }

    LpdbDataBase::RunwaySystemTable & rsTable = LpdbDataBase::Get().getRunwaySystemTable();

    vector<string> runwaySystems = rsTable.getAllIds();

    //Optimal and Active Schedule timelines already forwarded (in LpdbDataBase::forwardTimeline method)

    if (runwaySystems.size() > 0)
    {
        bool exists_previous_optimal_schedule = LpdbDataBase::Get().hasOptimalSchedule();

        if (exists_previous_optimal_schedule)
        {
            LpdbSchedule previous_optimal = LpdbDataBase::Get().getOptimalSchedule();

            TimeLine<LpdbSCHTimedData> schedule_timeline = previous_optimal.getTimeLine();

            //Get frozen intervals, and frozen by clock
            vector<string> frozen = schedule_timeline.getFrozenIntervals();
            vector<string> frozenForClock = schedule_timeline.getFrozenIntervals(minutesFrozenForClock);

            vector<string> intervalsToMaintain;
            vector<string> intervalsToGenerate;
            string initialNode;
            LpiADOVector<int> estimatedDelayedFPs;

            //bool hasFrozenNodes = (frozen.size() > 0) ? true : false;

            //Check if active has been manually activated
            bool isActiveManuallyActivated = false;

            bool existsActiveSchedule = LpdbDataBase::Get().hasActiveSchedule();

            if (existsActiveSchedule)
            {
                LpdbAlternativeSchedule & active = LpdbDataBase::Get().getActiveSchedule();
                isActiveManuallyActivated = active.isManuallyActivated();
            }

            if ((frozen.size() >= frozenForClock.size()) && isActiveManuallyActivated)
            {
                intervalsToMaintain = frozen;

                intervalsToGenerate = schedule_timeline.getNotFrozenIntervals();

                initialNode = getLastFrozenNodeOfActiveSchedule(frozen);

                if (intervalsToMaintain.size() > 0)
                {
                    estimatedDelayedFPs = getEstimatedDelayed(initialNode, intervalsToMaintain.back());
                }
            }
            else
            {
                intervalsToMaintain = frozenForClock;

                intervalsToGenerate = schedule_timeline.getNotFrozenIntervals(minutesFrozenForClock);

                initialNode = getLastFrozenNodeOfOptimalSchedule(frozenForClock);

                if (intervalsToMaintain.size() > 0)
                {
                    estimatedDelayedFPs = getEstimatedDelayed(initialNode, intervalsToMaintain.back());
                }
            }

            //Create graph and get solution
            _schedules_generator->createGraph(runwaySystems, intervalsToGenerate, initialNode, estimatedDelayedFPs);

            _schedules_generator->generateSchedules(initialNode, 1);

            LpdbSchedule solution;

            if (frozen.size() >= frozenForClock.size())
            {
                solution = _schedules_generator->getSolution(intervalsToMaintain, frozen, LpdbSchedule::E_ACTIVE);
            }
            else
            {
                solution = _schedules_generator->getSolution(intervalsToMaintain, frozen, LpdbSchedule::E_OPTIMAL);
            }

            if (isActiveManuallyActivated)
            {
                solution.setFrozenPeriods(frozen.size());
            }

            solution.setOrigin(LpiActivationType::E_OPTIMAL);
            schTable.addElement(0, solution);
        }
    }*/
}

void LpdBusinessLogicFacade::calculateRealDCB()
{
    LpdbDataBase::ScheduleTable & schTable = LpdbDataBase::Get().getScheduleTable();

    if (schTable.getNumberOfElements() > 0)
    {
        vector<string> intervals = schTable[0].getTimeLine().getAllIntervalIds();

        BOOST_FOREACH(string interval, intervals)
        {
            calculateRealDCB(interval);
        }
    }

#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).info() << "Schedules in DB after Real DCB calculations: " << std::endl;
    LclogStream::instance(LclogConfig::E_RTP).info() << schTable << std::endl;
#endif
}

void LpdBusinessLogicFacade::calculateRealDCB(string interval)
{
    int minClosedTurnRound = LpdbDataBase::Get().getGlobalParameters().getTminTurnRound();

    LpdbDataBase::ScheduleTable & schTable = LpdbDataBase::Get().getScheduleTable();

    vector<int> schedule_ids = schTable.getAllIds();

    if (schTable.getNumberOfElements() > 0)
    {
        BOOST_FOREACH(int id, schedule_ids)
        {
            double ratioARR;
            double ratioDEP;

            _schedules_generator->getPonderationsInInterval(interval, ratioARR, ratioDEP);

            LpdbSchedule & schedule = schTable[id];
            schedule.calculateRealDCB(interval, minClosedTurnRound, ratioARR, ratioDEP);
        }
    }
}

void LpdBusinessLogicFacade::calculateRunwayAllocation()
{
    LpdbDataBase::ScheduleTable & schTable = LpdbDataBase::Get().getScheduleTable();

    if (schTable.getNumberOfElements() > 0)
    {
        vector<string> intervals = schTable[0].getTimeLine().getAllIntervalIds();

        BOOST_FOREACH(string interval, intervals)
        {
            calculateRunwayAllocation(interval);
        }
    }

#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).info() << LpdbDataBase::Get().getRunwayAllocationsAsString() << std::endl;
#endif
}

void LpdBusinessLogicFacade::calculateRunwayAllocation(string interval)
{
    LpdbDataBase::ScheduleTable & schTable = LpdbDataBase::Get().getScheduleTable();

    vector<int> schedule_ids = schTable.getAllIds();

    if (schTable.getNumberOfElements() > 0)
    {
        BOOST_FOREACH(int id, schedule_ids)
        {
            LpdbSchedule & schedule = schTable[id];
            schedule.calculateRunwayAllocation(interval);
        }
    }
}

void LpdBusinessLogicFacade::calculateRealDCBAndRunwayAllocation()
{
    int minClosedTurnRound = LpdbDataBase::Get().getGlobalParameters().getTminTurnRound();

    LpdbDataBase::ScheduleTable & schTable = LpdbDataBase::Get().getScheduleTable();

    vector<int> schedule_ids = schTable.getAllIds();

    if (schTable.getNumberOfElements() > 0)
    {
        BOOST_FOREACH(int id, schedule_ids)
        {
            LpdbSchedule & schedule = schTable[id];
            vector<string> intervals = schedule.getTimeLine().getAllIntervalIds();

            BOOST_FOREACH(string interval, intervals)
            {
                double ratioARR;
                double ratioDEP;

                _schedules_generator->getPonderationsInInterval(interval, ratioARR, ratioDEP);

                schedule.calculateRealDCB(interval, minClosedTurnRound, ratioARR, ratioDEP);
                schedule.calculateRunwayAllocation(interval);
            }
        }
    }

#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).info() << "Real DCB calculations..." << std::endl;
    LclogStream::instance(LclogConfig::E_RTP).info() << "Schedules in DB after Real DCB calculations: " << std::endl;
    LclogStream::instance(LclogConfig::E_RTP).info() << schTable << std::endl;

    LclogStream::instance(LclogConfig::E_RTP).info() << "[RUNWAY ALLOCATION]: " << std::endl;
    LclogStream::instance(LclogConfig::E_RTP).info() << LpdbDataBase::Get().getRunwayAllocationsAsString() << std::endl;
#endif
}

void LpdBusinessLogicFacade::calculateActiveRealDCBAndRunwayAllocation()
{
    int minClosedTurnRound = LpdbDataBase::Get().getGlobalParameters().getTminTurnRound();

    if (LpdbDataBase::Get().hasActiveSchedule())
    {
        LpdbAlternativeSchedule & active = LpdbDataBase::Get().getActiveSchedule();

        vector<string> intervals = active.getTimeLine().getAllIntervalIds();

        BOOST_FOREACH(string interval, intervals)
        {
            double ratioARR;
            double ratioDEP;

            _schedules_generator->getPonderationsInInterval(interval, ratioARR, ratioDEP);

            active.calculateRealDCB(interval, minClosedTurnRound, ratioARR, ratioDEP);
            active.calculateRunwayAllocation(interval);
        }
    }
}

void LpdBusinessLogicFacade::calculateRealDCBAndRunwayAllocation(std::string interval)
{
    int minClosedTurnRound = LpdbDataBase::Get().getGlobalParameters().getTminTurnRound();

    LpdbDataBase::ScheduleTable & schTable = LpdbDataBase::Get().getScheduleTable();

    vector<int> schedule_ids = schTable.getAllIds();

    if (schTable.getNumberOfElements() > 0)
    {
        BOOST_FOREACH(int id, schedule_ids)
        {
            LpdbSchedule & schedule = schTable[id];
            double ratioARR;
            double ratioDEP;

            _schedules_generator->getPonderationsInInterval(interval, ratioARR, ratioDEP);

            //Calculate new interval and previous interval (only will be applied for mixed runways case)
            double previousRatioARR;
            double previousRatioDEP;

            string previous_interval = schedule.getTimeLine().getPreviousIntervalId(interval);
            _schedules_generator->getPonderationsInInterval(previous_interval, previousRatioARR, previousRatioDEP);

            schedule.calculateRealDCB(interval, minClosedTurnRound, ratioARR, ratioDEP, previous_interval,
                                      previousRatioARR, previousRatioDEP, true);

            schedule.calculateRunwayAllocation(interval);
        }
    }
}

void LpdBusinessLogicFacade::calculateRunwayFinalAssignation()
{
    if (LpdbDataBase::Get().hasActiveSchedule())
    {
        LpdbAlternativeSchedule & active = LpdbDataBase::Get().getActiveSchedule();

        vector<string> intervals = active.getTimeLine().getAllIntervalIds();

        BOOST_FOREACH(string interval, intervals)
        {
            calculateRunwayFinalAssignation(interval);
        }

#ifdef TRACE_OUT
        LclogStream::instance(LclogConfig::E_RTP).info() << LpdbDataBase::Get().getRunwayFinalAssignationAsString() << std::endl;
#endif
    }
}

void LpdBusinessLogicFacade::calculateRunwayFinalAssignation(std::string interval)
{
    if (LpdbDataBase::Get().hasActiveSchedule())
    {
        //We don't need a reference to opt schedule since we only modify FP's
        LpdbAlternativeSchedule active = LpdbDataBase::Get().getActiveSchedule();

        //We will modify each FP, assigning a departure/arrival runway
        LpdbDataBase::FPTable & flight_plans = LpdbDataBase::Get().getFPTable();

        if (active.has_data(interval))
        {
            LpdbRSScheduled rs = active[interval].getRsScheduled();
            std::map<std::string, LpdbRwyScheduled> runways = rs.getRunways();

            typedef std::map<std::string, LpdbRwyScheduled>::value_type rwy_data_type;

            BOOST_FOREACH (rwy_data_type & runway, runways)
            {
                string runway_id = runway.first;

                LpiADOVector<vector<string> > allocated_fps = runway.second.getAllocatedFpsFps();

                for (int i = E_ARR; i < E_OVA; i++)
                {
                    BOOST_FOREACH (string fpKey, allocated_fps[i])
                    {
                      if (flight_plans.exists(fpKey))
                      {
                        LpiFlightPlan & flight_plan = flight_plans[fpKey];

                        switch(i)
                        {
                            case E_ARR:
                                flight_plan.setArrivalRunway(runway_id);
                                break;

                            case E_DEP:
                                flight_plan.setDepartureRunway(runway_id);
                                break;
                        }
                      }
                   }
              }
          }
      }
   }
}


void LpdBusinessLogicFacade::activateSchedule(int schedule_id, LpiScheduleActivationType::LpiEnum activation_type)
{
//    LpiConfigurationAlertKPIs alertKPIs;
//    LpiResult result;
//    getConfigurationAlertKPIs(alertKPIs, result);

    //if schedule_id == -1, optimal schedule has been activated

    if (schedule_id == -1)
    {
        if (LpdbDataBase::Get().hasOptimalSchedule())
        {
            LpdbSchedule optimal = LpdbDataBase::Get().getOptimalSchedule();

            LpdbAlternativeSchedule active(optimal);

            //active.recalculateComparativeKPIs(alertKPIs);
            active.setActivationType(activation_type);

            LpdbDataBase::Get().setActiveSchedule(active);
            LpdbDataBase::Get().setActivationTime(LctimVirtualClock::Get().getTime());

#ifdef TRACE_OUT
            LclogStream::instance(LclogConfig::E_RTP).debug() << "[OPTIMAL SCHEDULE ACTIVATION]: "
            << LpdbDataBase::Get().getActivationTime()
            << std::endl;
#endif
        }
    }
    else
    {
        LpdbDataBase::AlternativeScheduleTable & alt_scheds = LpdbDataBase::Get().getAlternativeScheduleTable();

        if (alt_scheds.exists(schedule_id))
        {
            LpdbAlternativeSchedule active = alt_scheds[schedule_id];

            //active.recalculateComparativeKPIs(alertKPIs);
            active.setActivationType(activation_type);

            // In case of what-if 3, apply runway closures and calculate optimal in case of option 1
            LpiActivationType::ActivationType origin = active.getOrigin();
            if ((origin == LpiActivationType::E_WHAT_IF_3_ACTIVE) || (origin
                    == LpiActivationType::E_WHAT_IF_3_NEW_SOLUTION)
                || (origin == LpiActivationType::E_WHAT_IF_3_BEST_POINT)
                || (origin == LpiActivationType::E_WHAT_IF_3_BEST_POINT_FOR_ACTIVE))
            {
                //apply runway closures
                activateRunwayClosures(active.getId());

                calculateEstimatedDCB();

                if ((origin == LpiActivationType::E_WHAT_IF_3_ACTIVE) || (origin
                        == LpiActivationType::E_WHAT_IF_3_BEST_POINT_FOR_ACTIVE))
                {
                    //generate optimal schedule
                    generateSchedulesForAllIntervals();

                    LpdbDataBase::ScheduleTable & schTable = LpdbDataBase::Get().getScheduleTable();

                    LpdbSchedule optimalGenerated = schTable[0];
                    LpdbAlternativeSchedule result(optimalGenerated);

                    performCalculationsInSchedule(result);
                    LpdbDataBase::Get().setOptimalSchedule(result);

                    LclogStream::instance(LclogConfig::E_RTP).debug()
                            << "TEST_CLOCK: Publishing optimal schedule with no forwarding, type = " << origin
                            << std::endl;
                    publishOptimalSchedule(LpiCalculationReason::E_MANUAL_ACTIVATION);
                }
                else  //Activated is also the new optimal
                {
                    LpdbDataBase::Get().setOptimalSchedule(active);
                    LpdbSchedule & optimal = LpdbDataBase::Get().getOptimalSchedule();
                    optimal.setOrigin(LpiActivationType::E_OPTIMAL);

                    //send optimal after reviewing clock forwarding
                }

                //All what-if must become obsolete (excluding the activated one)
                setExpirationDateForWhatIfs(LctimVirtualClock::Get().getTime(), active.getId());

//            publishOptimalSchedule(LpiCalculationReason::E_MANUAL_ACTIVATION);
            }

            LpdbDataBase::Get().setActiveSchedule(active);
            LpdbDataBase::Get().setActivationTime(LctimVirtualClock::Get().getTime());

            reviewClockForwardingForActivation(origin);

#ifdef TRACE_OUT
            LclogStream::instance(LclogConfig::E_RTP).debug() << "[ALTERNATIVE SCHEDULE ACTIVATION, ID ="
            << schedule_id
            << " (" << active.getName() << ")]"
            << LpdbDataBase::Get().getActivationTime()
            << std::endl;
#endif
        }
        else
        {
            LclogStream::instance(LclogConfig::E_RTP).error() << "[ALTERNATIVE SCHEDULE DOES NOT EXIST IN DATABASE]"
                                                              << std::endl;
        }
    }
}

void LpdBusinessLogicFacade::activateOptimalSchedule()
{
    activateSchedule(-1, LpiScheduleActivationType::E_AUTO);
}

void LpdBusinessLogicFacade::performActiveScheduleCalculations(bool isClockForwarding, bool isInitialization)
{
    int minClosedTurnRound = LpdbDataBase::Get().getGlobalParameters().getTminTurnRound();

//    LpiConfigurationAlertKPIs alertKPIs;
//    LpiResult result;
//    getConfigurationAlertKPIs(alertKPIs, result);

//    LpiConfigurationParameters config;
//    getConfigurationParameters(config, result);
//
//    int delayThreshold = config.getMaxForecastedDelayThreshold();

    int minTurnRoundTime = LpdbDataBase::Get().getGlobalParameters().getTminTurnRound();

    if (LpdbDataBase::Get().hasActiveSchedule())
    {
        LpdbAlternativeSchedule & active = LpdbDataBase::Get().getActiveSchedule();

        if (!isInitialization)
        {
            active.clearStoredFPs();

            vector<string> intervals = active.getTimeLine().getAllIntervalIds();

            BOOST_FOREACH (string interval, intervals)
            {
                double ratioARR;
                double ratioDEP;

                _schedules_generator->getPonderationsInInterval(interval, ratioARR, ratioDEP);

                active.calculateRealDCB(interval, minClosedTurnRound, ratioARR, ratioDEP);

                active.calculateRunwayAllocation(interval);
                active.performFPCalculations(interval, minTurnRoundTime);
            }

#ifdef TURN_ROUND
            active.markTurnRoundFlights();
#endif
            //active.generateKPIs(alertKPIs, delayThreshold, isClockForwarding);

#ifdef TRACE_OUT
            //Trace and Logging
            LclogStream::instance(LclogConfig::E_RTP).info() << "Real DCB calculations..." << std::endl;
            LclogStream::instance(LclogConfig::E_RTP).info() << active << std::endl;

            LclogStream::instance(LclogConfig::E_RTP).info() << LpdbDataBase::Get().getAlternativeScheduleRwyAllocationsAsString(active.getId()) << std::endl;
            LclogStream::instance(LclogConfig::E_RTP).info() << LpdbDataBase::Get().getScheduledFlightPlansAsString(LpdbSchedule::E_ACTIVE);
#endif
        }
    }
}

void LpdBusinessLogicFacade::performFPInScheduleCalculations()
{
    int minTurnRoundTime = LpdbDataBase::Get().getGlobalParameters().getTminTurnRound();

    LpdbDataBase::ScheduleTable & schTable = LpdbDataBase::Get().getScheduleTable();

    vector<int> schedule_ids = schTable.getAllIds();

    if (schTable.getNumberOfElements() > 0)
    {
        BOOST_FOREACH(int id, schedule_ids)
        {
            LpdbSchedule & schedule = schTable[id];
            schedule.performFPCalculations(minTurnRoundTime);

#ifdef TRACE_OUT
            LclogStream::instance(LclogConfig::E_RTP).info() << LpdbDataBase::Get().getScheduledFlightPlansAsString(LpdbSchedule::E_OPTIMAL) << std::endl;
#endif
        }
    }
}

void LpdBusinessLogicFacade::calculateWhatIfMode1(const LpiOptimizationCriteria & criteria)
{
#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).debug() << "[WHAT IF 1 (OPTIMIZATION CRITERIA) RECEIVED]: " << std::endl;
    LclogStream::instance(LclogConfig::E_RTP).info() << criteria << std::endl;
#endif

    int minTurnRoundTime = LpdbDataBase::Get().getGlobalParameters().getTminTurnRound();

    LpdbAlternativeSchedule result = _schedules_generator->generateAlternativeSchedule(criteria);

    vector<string> intervals = result.getTimeLine().getAllIntervalIds();

    BOOST_FOREACH (string interval, intervals)
    {
        double ratioARR;
        double ratioDEP;

        _schedules_generator->getPonderationsInInterval(interval, ratioARR, ratioDEP);

        result.calculateRealDCB(interval, minTurnRoundTime, ratioARR, ratioDEP);
        result.calculateRunwayAllocation(interval);
        result.performFPCalculations(interval, minTurnRoundTime);

#ifdef TURN_ROUND
        result.markTurnRoundFlights();
#endif
    }

//    LpiConfigurationAlertKPIs alertKPIs;
//    LpiResult res;
//    getConfigurationAlertKPIs(alertKPIs, res);

//    LpiConfigurationParameters config;
//    getConfigurationParameters(config, res);
//
//    int delayThreshold = config.getMaxForecastedDelayThreshold();
//
//    bool isClockForwarding = false;
//
//    result.generateKPIs(alertKPIs, delayThreshold, isClockForwarding);
    result.setOrigin(LpiActivationType::E_WHAT_IF_1);

    //Update Ids and expiration information
    LpdbExpirationInfo expirationInformation;
    expirationInformation.setAutomaticDeletion(!criteria.getAvoidAutomaticDeletion());
    //expirationInformation.setExpirationHours(config.getAlternativeSchedulesExpirationHours());

    result.setExpirationInformation(expirationInformation);

    LpdbDataBase::AlternativeScheduleTable & alternatives = LpdbDataBase::Get().getAlternativeScheduleTable();

    int alternative_id;

    //LpiCalculationReason::LpiEnum reason;

    if ((criteria.getId() == -1) || (!alternatives.exists(criteria.getId())))
    {
#ifdef TRACE_OUT
        LclogStream::instance(LclogConfig::E_RTP).debug() << "Adding active schedule to alternatives table..." << std::endl;
#endif

        alternative_id = alternatives.addElement(result);

        //reason = LpiCalculationReason::E_WHAT_IF_NEW_CRITERIA;
    }
    else
    {
        alternative_id = criteria.getId();
        alternatives[alternative_id] = result;

        //reason = LpiCalculationReason::E_WHAT_IF_NEW_CRITERIA_UPDATE;
    }

#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).debug() << "Alternative updated with, id= " << alternative_id << ", name = " << criteria.getName() << std::endl;
#endif

    alternatives[alternative_id].setId(alternative_id);
    alternatives[alternative_id].setName(criteria.getName());

#ifdef TRACE_OUT
    //Trace and Logging
    LclogStream::instance(LclogConfig::E_RTP).info() << "Real DCB calculations..." << std::endl;
    LclogStream::instance(LclogConfig::E_RTP).info() << alternatives[alternative_id] << std::endl;

    LclogStream::instance(LclogConfig::E_RTP).info() << LpdbDataBase::Get().getAlternativeScheduleRwyAllocationsAsString(alternative_id) << std::endl;
    LclogStream::instance(LclogConfig::E_RTP).info() << LpdbDataBase::Get().getScheduledFlightPlansAsString(LpdbSchedule::E_ALTERNATIVE, alternative_id);
#endif

    LpdbAlternativeSchedule to_send = alternatives[alternative_id];

    //LpiAlternativeSchedule scheduleData = LpdbAlternativeSchedule::Convert2AlternativeInterface(to_send, alertKPIs);
    //scheduleData.setCalculationReason(reason);

    //LpiAlternativeScheduleEvt event;
    //event.setAlternativeSchedule(scheduleData);

    //LpdComponent::Get().publish(event);
}

void LpdBusinessLogicFacade::generateManualSchedule(const LpiAlternativeSchedule & manualSchedule)
{
#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).info() << "[WHAT IF 2 (MANUAL SCHEDULE) RECEIVED]: " << std::endl;
#endif

    int minTurnRoundTime = LpdbDataBase::Get().getGlobalParameters().getTminTurnRound();

    LpdbAlternativeSchedule result = _schedules_generator->generateManualSchedule(manualSchedule);

    vector<string> intervals = result.getTimeLine().getAllIntervalIds();

    BOOST_FOREACH (string interval, intervals)
    {
        double ratioARR;
        double ratioDEP;

        _schedules_generator->getPonderationsInInterval(interval, ratioARR, ratioDEP);

        result.calculateRealDCB(interval, minTurnRoundTime, ratioARR, ratioDEP);
        result.calculateRunwayAllocation(interval);
        result.performFPCalculations(interval, minTurnRoundTime);

#ifdef TURN_ROUND
        result.markTurnRoundFlights();
#endif
    }

//    LpiConfigurationAlertKPIs alertKPIs;
//    LpiResult res;
//    getConfigurationAlertKPIs(alertKPIs, res);

//    LpiConfigurationParameters config;
//    getConfigurationParameters(config, res);
//
//    int delayThreshold = config.getMaxForecastedDelayThreshold();
//
//    bool isClockForwarding = false;
//
//    result.generateKPIs(alertKPIs, delayThreshold, isClockForwarding);
    result.setOrigin(LpiActivationType::E_WHAT_IF_2);

    //Update Ids and expiration information
    LpdbExpirationInfo expirationInformation;
    expirationInformation.setAutomaticDeletion(!manualSchedule.getAvoidAutomaticDeletion());
    //expirationInformation.setExpirationHours(config.getAlternativeSchedulesExpirationHours());

    result.setExpirationInformation(expirationInformation);

    LpdbDataBase::AlternativeScheduleTable & alternatives = LpdbDataBase::Get().getAlternativeScheduleTable();

    int alternative_id;
    //LpiCalculationReason::LpiEnum reason;

    if ((manualSchedule.getId() == -1) || (!alternatives.exists(manualSchedule.getId())))
    {
#ifdef TRACE_OUT
        LclogStream::instance(LclogConfig::E_RTP).info() << "Adding active schedule to alternatives table..." << std::endl;
#endif

        alternative_id = alternatives.addElement(result);
        //reason = LpiCalculationReason::E_WHAT_IF_MANUAL_EDITION;
    }
    else
    {
        alternative_id = manualSchedule.getId();
        alternatives[alternative_id] = result;
        //reason = LpiCalculationReason::E_WHAT_IF_MANUAL_EDITION_UPDATE;
    }

#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).info() << "Alternative updated with, id= " << alternative_id << ", name = " << manualSchedule.getName() << std::endl;
#endif

    alternatives[alternative_id].setId(alternative_id);
    alternatives[alternative_id].setName(manualSchedule.getName());

#ifdef TRACE_OUT
    //Trace and Logging
    LclogStream::instance(LclogConfig::E_RTP).info() << "Real DCB calculations..." << std::endl;
    LclogStream::instance(LclogConfig::E_RTP).info() << alternatives[alternative_id] << std::endl;
    LclogStream::instance(LclogConfig::E_RTP).info() << LpdbDataBase::Get().getAlternativeScheduleRwyAllocationsAsString(alternative_id) << std::endl;
    LclogStream::instance(LclogConfig::E_RTP).info() << LpdbDataBase::Get().getScheduledFlightPlansAsString(LpdbSchedule::E_ALTERNATIVE, alternative_id);
#endif

    LpdbAlternativeSchedule to_send = alternatives[alternative_id];

    //LpiAlternativeSchedule scheduleData = LpdbAlternativeSchedule::Convert2AlternativeInterface(to_send, alertKPIs);
    //scheduleData.setCalculationReason(reason);

    //LpiAlternativeScheduleEvt event;
    //event.setAlternativeSchedule(scheduleData);

    //LpdComponent::Get().publish(event);
}

void LpdBusinessLogicFacade::deleteSchedule(int scheduleId)
{
#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).info() << "[ALTERNATIVE SCHEDULE DELETION RECEIVED]: Id: " << scheduleId << std::endl;
#endif

    LpdbDataBase::AlternativeScheduleTable & alternatives = LpdbDataBase::Get().getAlternativeScheduleTable();
    LpdbDataBase::WhatIfClosureTable & closures = LpdbDataBase::Get().getWhatIfClosureTable();

#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).info() << "Number of what-ifs in database before deletion: " << alternatives.getNumberOfElements() << std::endl;
#endif

    if (alternatives.exists(scheduleId))
    {
        int closureId = alternatives[scheduleId].getRunwayClosure();

        if (closures.exists(closureId))
        {
            closures.deleteElement(closureId);
        }

        alternatives.deleteElement(scheduleId);
    }

#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).info() << "Number of what-ifs in database after deletion: " << alternatives.getNumberOfElements() << std::endl;
#endif
}

void LpdBusinessLogicFacade::compareSchedules(const LpiSchedulesComparison & schedulesToCompare)
{
#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).info() << "[SCHEDULES COMPARISON RECEIVED]: ";
#endif

    int leftId = schedulesToCompare.getLeftOperandId();
    string leftName = schedulesToCompare.getLeftOperandName();

    int rightId = schedulesToCompare.getRightOperandId();
    string rightName = schedulesToCompare.getRightOperandName();

    LpdbDataBase::AlternativeScheduleTable & alternatives = LpdbDataBase::Get().getAlternativeScheduleTable();

    //Get schedules to compare from database
    LpdbSchedule leftOperand;
    bool leftOperandExists = false;

    if (leftId == -1)
    {
        if ((leftName == "ACTIVE") && (LpdbDataBase::Get().hasActiveSchedule()))
        {
            leftOperand = LpdbDataBase::Get().getActiveSchedule();
            leftOperandExists = true;
        }
        else if ((leftName == "OPTIMAL") && (LpdbDataBase::Get().hasOptimalSchedule()))
        {
            leftOperand = LpdbDataBase::Get().getOptimalSchedule();
            leftOperandExists = true;
        }
    }
    else
    {
        if (alternatives.exists(leftId))
        {
            leftOperand = alternatives[leftId];
            leftOperandExists = true;
        }
    }

    LpdbSchedule rightOperand;
    bool rightOperandExists = false;

    if (rightId == -1)
    {
        if ((rightName == "ACTIVE") && (LpdbDataBase::Get().hasActiveSchedule()))
        {
            rightOperand = LpdbDataBase::Get().getActiveSchedule();
            rightOperandExists = true;
        }
        else if ((rightName == "OPTIMAL") && (LpdbDataBase::Get().hasOptimalSchedule()))
        {
            rightOperand = LpdbDataBase::Get().getOptimalSchedule();
            rightOperandExists = true;
        }
    }
    else
    {
        if (alternatives.exists(rightId))
        {
            rightOperand = alternatives[rightId];
            rightOperandExists = true;
        }
    }

    if (leftOperandExists && rightOperandExists)
    {
//        LpiConfigurationAlertKPIs alertThresholds;
//        LpiResult result;
//        getConfigurationAlertKPIs(alertThresholds, result);

        //TimeLine<LpdbSCHTimedData> comparison = leftOperand.compareTo(rightOperand, alertThresholds);

        //Convert and send
        //LpiComparativeKpis convertedKPIs = LpdbScheduleConverter::ConvertKpis2Interface(comparison);

//#ifdef TRACE_OUT
//        LclogStream::instance(LclogConfig::E_RTP).info() << "Id= " << leftId << ", Name= " << leftName << std::endl;
//        LclogStream::instance(LclogConfig::E_RTP).info() << leftOperand.getIntervalAbsoluteKpisAsString() << std::endl;
//
//        LclogStream::instance(LclogConfig::E_RTP).info() << "With  Id= " << rightId << ", Name= " << rightName << std::endl;
//        LclogStream::instance(LclogConfig::E_RTP).info() << rightOperand.getIntervalAbsoluteKpisAsString() << std::endl;
//
//        LclogStream::instance(LclogConfig::E_RTP).info() << "[SCHEDULES COMPARISON RESULT: " << '\n'
//        << convertedKPIs.getRelativeKpisAsString() << "\n]" << std::endl;
//#endif

//        LpiSchedulesComparisonResponse response(schedulesToCompare);
//        response.setKpis(convertedKPIs);
//
//        LpiSchedulesComparisonResponseEvt responseEvt;
//        responseEvt.setSchedulesComparisonResponse(response);
//
//        LpdComponent::Get().publish(responseEvt);
    }
}

/*
void LpdBusinessLogicFacade::generateMrtmTransitionCosts(LpiAdaptationMrtmTransitionCostTable & transitions)
{
    LpdbDataBase::RunwaySystemTable & rsTable = LpdbDataBase::Get().getRunwaySystemTable();
    std::vector<std::string> all_rs_ids = rsTable.getAllIds();

    BOOST_FOREACH(string rs_origin_id, all_rs_ids)
    {
        BOOST_FOREACH(string rs_destination_id, all_rs_ids)
        {
            if (!transitions.existsTransition(rs_origin_id, rs_destination_id))
            {
                if (rsTable.exists(rs_origin_id) && rsTable.exists(rs_destination_id))
                {
                    LpdbRunwaySystem & rsOrigin = rsTable[rs_origin_id];
                    LpdbRunwaySystem & rsDestination = rsTable[rs_destination_id];

                    if (rs_origin_id == rs_destination_id)
                    {
                        double transition_cost = transitions.getMrtmTransitionMaintenanceCost();
                        transitions.addMrtmTransitionCost(rs_origin_id, rs_destination_id, transition_cost);
                    }
                    else
                    {
                        const map<string, LpdbRunwaySystemRunway> & rs_origin_rwys = rsOrigin.getRunways();
                        const map<string, LpdbRunwaySystemRunway> & rs_destination_rwys = rsDestination.getRunways();
                        int commonRunways = 0;
                        typedef const map<string, LpdbRunwaySystemRunway>::value_type rs_rwy_value_type;

                        BOOST_FOREACH (rs_rwy_value_type & data, rs_origin_rwys)
                        {
                            string originId = data.second.getId();

                            if (rs_destination_rwys.count(originId) > 0)
                            {
                                commonRunways++;
                            }
                        }

                        double transition_cost = transitions.getMrtmTransitionCost(commonRunways);
                        transitions.addMrtmTransitionCost(rs_origin_id, rs_destination_id, transition_cost);
                    }
                }
            }
        }
    }
}
*/

//Plans a RS in a newly created interval, result of a clock event
void LpdBusinessLogicFacade::generateRSForActiveScheduleLastInterval(string interval)
{
    if (LpdbDataBase::Get().hasActiveSchedule())
    {
        LpdbDataBase::RunwaySystemTable & rsTable = LpdbDataBase::Get().getRunwaySystemTable();

        LpdbAlternativeSchedule & active = LpdbDataBase::Get().getActiveSchedule();
        //TimeInterval ti = active.getTimeLine().getTimeInterval(interval); //error: unused variable
        std::string planned_rs;

        //Get last known planned RS (former last interval)
        std::string former_last_interval = active.getTimeLine().getPreviousIntervalId(interval);
        if (active.has_data(former_last_interval))
        {
            planned_rs = active[former_last_interval].getRsScheduled().getRunwaySystemId();
        }

        //Plan selected RS in active schedule's last interval
        if (active.has_data(interval) && !empty(planned_rs) && rsTable.exists(planned_rs))
        {
            LpdbRunwaySystem rs = rsTable[planned_rs];
            LpdbRSScheduled rs_scheduled(rs);
            active[interval].setRsScheduled(rs_scheduled);

#ifdef TRACE_OUT
            LclogStream::instance(LclogConfig::E_RTP).debug() << "Planned RS in new interval " << interval << ": " << rs_scheduled.getRunwaySystemId() << std::endl;
#endif
        }
    }
}

void LpdBusinessLogicFacade::publishOptimalAndActiveSchedules(const LpiCalculationReason::LpiEnum & reason)
{
//    LpiConfigurationAlertKPIs alertKPIs;
//    LpiResult result;
//    getConfigurationAlertKPIs(alertKPIs, result);

    LpdbDataBase & db = LpdbDataBase::Get();

    if (db.hasOptimalSchedule() && db.hasActiveSchedule())
    {
        //Optimal conversion
#ifdef TRACE_OUT
        LclogStream::instance(LclogConfig::E_RTP).debug() << "[OPTIMAL SCHEDULE]:" << std::endl;
#endif

        LpiSchedule optimalSchedule;

//        optimalSchedule = LpdbScheduleConverter::Convert2Interface(db.getOptimalSchedule(), LpdbSchedule::E_OPTIMAL,
//                                                                   alertKPIs);

        optimalSchedule.setCalculationReason(reason);

        LpiOptimalScheduleEvt optimalEvt;
        optimalEvt.setSchedule(optimalSchedule);

        //Active conversion
        LpiActiveScheduleEvt activeScheduleEvt;

        LpiActiveSchedule activeSchedule;

//        activeSchedule = LpdbAlternativeSchedule::Convert2ActiveInterface(db.getActiveSchedule(), alertKPIs,
//                                                                          db.getActivationTime());
        activeSchedule.setCalculationReason(reason);

        activeScheduleEvt.setActiveSchedule(activeSchedule);

        //Events publication
        LpdComponent::Get().publish(optimalEvt);
#ifdef TRACE_OUT
        LclogStream::instance(LclogConfig::E_RTP).debug() << "[OPTIMAL SCHEDULE PUBLISHED]" << std::endl;
#endif

        LpdComponent::Get().publish(activeScheduleEvt);
#ifdef TRACE_OUT
        LclogStream::instance(LclogConfig::E_RTP).info() << "[ACTIVE SCHEDULE PUBLISHED]" << std::endl;
#endif
    }

}

void LpdBusinessLogicFacade::publishOptimalSchedule(const LpiCalculationReason::LpiEnum & reason)
{
//    LpiConfigurationAlertKPIs alertKPIs;
//    LpiResult result;
//    getConfigurationAlertKPIs(alertKPIs, result);

    LpdbDataBase & db = LpdbDataBase::Get();

    if (db.hasOptimalSchedule())
    {
        LpiSchedule optimalSchedule;

//        optimalSchedule = LpdbScheduleConverter::Convert2Interface(db.getOptimalSchedule(), LpdbSchedule::E_OPTIMAL,
//                                                                   alertKPIs);

        optimalSchedule.setCalculationReason(reason);

        LpiOptimalScheduleEvt optimalEvt;
        optimalEvt.setSchedule(optimalSchedule);

        LpdComponent::Get().publish(optimalEvt);

#ifdef TRACE_OUT
        LclogStream::instance(LclogConfig::E_RTP).debug() << "[OPTIMAL SCHEDULE PUBLISHED]" << std::endl;
#endif
    }
    else
    {
        LclogStream::instance(LclogConfig::E_RTP).error() << "OPTIMAL SCHEDULE DOES NOT EXIST" << std::endl;
    }
}

void LpdBusinessLogicFacade::publishActiveSchedule(const LpiCalculationReason::LpiEnum & reason)
{
//    LpiConfigurationAlertKPIs alertKPIs;
//    LpiResult result;
//    getConfigurationAlertKPIs(alertKPIs, result);

    LpdbDataBase & db = LpdbDataBase::Get();

    if (db.hasActiveSchedule())
    {
        //LpdbAlternativeSchedule & active_schedule = db.getActiveSchedule();

        LpiActiveSchedule activeSchedule;
//        activeSchedule = LpdbAlternativeSchedule::Convert2ActiveInterface(active_schedule, alertKPIs,
//                                                                          db.getActivationTime());

        activeSchedule.setCalculationReason(reason);

        LpiActiveScheduleEvt activeScheduleEvt;
        activeScheduleEvt.setActiveSchedule(activeSchedule);

        LpdComponent::Get().publish(activeScheduleEvt);

#ifdef TRACE_OUT
        LclogStream::instance(LclogConfig::E_RTP).info() << "[SCHEDULE ACTIVATION PUBLISHED]" << std::endl;
#endif
    }
    else
    {
        LclogStream::instance(LclogConfig::E_RTP).error() << "ACTIVE SCHEDULE DOES NOT EXIST" << std::endl;
    }
}

string LpdBusinessLogicFacade::getLastFrozenNodeOfActiveSchedule(const vector<string> & frozen) const
{
    string result = "BEGIN";

    if (frozen.size() > 0)
    {
        bool existsActiveSchedule = LpdbDataBase::Get().hasActiveSchedule();

        if (existsActiveSchedule)
        {
            LpdbAlternativeSchedule & active = LpdbDataBase::Get().getActiveSchedule();

            if (active.isManuallyActivated() && (frozen.size() > 0))
            {
                string lastFrozenInterval = frozen.back();

                TimeLine<LpdbSCHTimedData> scheduleTimeline = active.getTimeLine();

                if (scheduleTimeline.hasData(lastFrozenInterval))
                {
                    result = scheduleTimeline[lastFrozenInterval].getRsScheduled().getRunwaySystemId();
                }
            }
        }
    }

    return result;
}

string LpdBusinessLogicFacade::getLastFrozenNodeOfOptimalSchedule(const vector<string> & frozen) const
{
    string result = "BEGIN";

    if (frozen.size() > 0)
    {
        bool existsOptimal = LpdbDataBase::Get().hasOptimalSchedule();

        if (existsOptimal)
        {
            LpdbSchedule optimal = LpdbDataBase::Get().getOptimalSchedule();

            string lastFrozenInterval = frozen.back();

            TimeLine<LpdbSCHTimedData> scheduleTimeline = optimal.getTimeLine();

            if (scheduleTimeline.hasData(lastFrozenInterval))
            {
                result = scheduleTimeline[lastFrozenInterval].getRsScheduled().getRunwaySystemId();
            }
        }
    }

    return result;
}

LpiADOVector<int> LpdBusinessLogicFacade::getEstimatedDelayed(string initialNode, string interval)
{
    LpiADOVector<int> result;

    LpdbDataBase::RunwaySystemTable & rsTable = LpdbDataBase::Get().getRunwaySystemTable();

    if (rsTable.exists(initialNode))
    {
        LpdbRunwaySystem & firstRS = rsTable[initialNode];

        if (firstRS.has_data(interval))
        {
            result = firstRS[interval].getEstimatedDelayedFps();
        }
    }

    return result;
}

void LpdBusinessLogicFacade::deleteNotReceivedFPs(vector<string> & receivedFPKeys)
{/*
    LpdbDataBase::FPTable & fpTable = LpdbDataBase::Get().getFPTable();
    LpdbDemand & demandForecast = LpdbDataBase::Get().getDemand("");

    vector<string> allFlightPlansInDB = fpTable.getAllIds();

    std::sort(allFlightPlansInDB.begin(), allFlightPlansInDB.end());
    std::sort(receivedFPKeys.begin(), receivedFPKeys.end());

    vector<string> fpsToDelete;
    std::set_difference(allFlightPlansInDB.begin(), allFlightPlansInDB.end(), receivedFPKeys.begin(),
                        receivedFPKeys.end(), back_inserter(fpsToDelete));

    if (fpsToDelete.size() > 0)
    {
        for (unsigned int i = 0; i < fpsToDelete.size(); ++i)
        {
            //Delete also from demand forecast
            std::string flightPlanKey = fpsToDelete[i];
            LpiFlightPlan & fp = fpTable[flightPlanKey];

            demandForecast.deleteFromForecast(fp);
        }

        fpTable.deleteElements(fpsToDelete);
    }*/
}

void LpdBusinessLogicFacade::generateWhatIfClosuresforActive(const LpiWhatIfClosure & closures)
{

#ifdef TRACE_OUT
    //Execution time measuring
    boost::chrono::thread_clock::time_point start_time = boost::chrono::thread_clock::now();

    LclogStream::instance(LclogConfig::E_RTP).debug() << "[WHAT IF 3 (RUNWAY CLOSURES FOR ACTIVE) RECEIVED]" << std::endl;

#endif

    if (LpdbDataBase::Get().hasActiveSchedule())
    {
        //Close runways
        LpdbRunwaySystemsMemento memento = LpdbDataBase::Get().createRunwaySystemsMemento();

        //Calculate new capacities
        applyRunwayClosures(closures);
        calculateRunwayAndRSMaxCapacities();
        calculateEstimatedDCB();

        //Generate schedule from active
        LpdbAlternativeSchedule & active = LpdbDataBase::Get().getActiveSchedule();

        //Important: this method uses DB runways state to fill schedule rwys capacity
        LpdbAlternativeSchedule result = _schedules_generator->generateAlternativeFromActive(active);

        //Perform calculations
        performCalculationsInSchedule(result);

        //Restore runways database state
        LpdbDataBase::Get().setRunwaySystemsMemento(memento);

        result.setOrigin(LpiActivationType::E_WHAT_IF_3_ACTIVE);

        LpiCalculationReason::LpiEnum reason;
        int alternativeId = updateWhatIfDataBase(closures, result, reason);

        sendAlternativeSchedule(alternativeId, reason);
    }

#ifdef TRACE_OUT

    boost::chrono::thread_clock::time_point end_time = boost::chrono::thread_clock::now();
    LclogStream::instance(LclogConfig::E_RTP).debug() << "What-if execution time: " << boost::chrono::duration_cast<boost::chrono::milliseconds>(end_time - start_time).count() << " ms\n";

#endif

}

void LpdBusinessLogicFacade::generateWhatIfClosuresforOptimal(const LpiWhatIfClosure & closures)
{

    //Execution time measuring
    boost::chrono::thread_clock::time_point start_time = boost::chrono::thread_clock::now();

#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).debug() << "[WHAT IF 3 (GENERATE NEW SOLUTION) RECEIVED]" << std::endl;

#endif

    //Close runways
    LpdbRunwaySystemsMemento memento = LpdbDataBase::Get().createRunwaySystemsMemento();

    //Calculate new capacities
    applyRunwayClosures(closures);
    calculateRunwayAndRSMaxCapacities();
    calculateEstimatedDCB();

    //generate optimal schedule
    generateSchedulesForAllIntervals();

    LpdbDataBase::ScheduleTable & schTable = LpdbDataBase::Get().getScheduleTable();

    LpdbSchedule optimalGenerated = schTable[0];

    LpdbAlternativeSchedule result(optimalGenerated);

    performCalculationsInSchedule(result);

    //Restore runways database state
    LpdbDataBase::Get().setRunwaySystemsMemento(memento);

    result.setOrigin(LpiActivationType::E_WHAT_IF_3_NEW_SOLUTION);

    LpiCalculationReason::LpiEnum reason;
    int alternativeId = updateWhatIfDataBase(closures, result, reason);

    sendAlternativeSchedule(alternativeId, reason);

#ifdef TRACE_OUT

    boost::chrono::thread_clock::time_point end_time = boost::chrono::thread_clock::now();
    LclogStream::instance(LclogConfig::E_RTP).debug() << "What-if execution time: " << boost::chrono::duration_cast<boost::chrono::milliseconds>(end_time - start_time).count() << " ms\n";

#endif

}

void LpdBusinessLogicFacade::performCalculationsInSchedule(LpdbAlternativeSchedule & schedule)
{
    int minTurnRoundTime = LpdbDataBase::Get().getGlobalParameters().getTminTurnRound();

    vector<string> intervals = schedule.getTimeLine().getAllIntervalIds();

    BOOST_FOREACH (string interval, intervals)
    {
        double ratioARR;
        double ratioDEP;

        _schedules_generator->getPonderationsInInterval(interval, ratioARR, ratioDEP);

        schedule.calculateRealDCB(interval, minTurnRoundTime, ratioARR, ratioDEP);
        schedule.calculateRunwayAllocation(interval);
        schedule.performFPCalculations(interval, minTurnRoundTime);

#ifdef TURN_ROUND
        schedule.markTurnRoundFlights();
#endif
    }

//    LpiConfigurationAlertKPIs alertKPIs;
//    LpiResult res;
//    getConfigurationAlertKPIs(alertKPIs, res);

//    LpiConfigurationParameters config;
//    getConfigurationParameters(config, res);
//
//    int delayThreshold = config.getMaxForecastedDelayThreshold();
//
//    bool isClockForwarding = false;
//
//    schedule.generateKPIs(alertKPIs, delayThreshold, isClockForwarding);
}

void LpdBusinessLogicFacade::applyRunwayClosures(const LpiWhatIfClosure & closures, bool mustResetState)
{
    LpdbDataBase::RunwayTable & runwayTable = LpdbDataBase::Get().getRunwayTable();

    if (mustResetState)
    {
        //Reset all availabilities prior to activation
        vector<string> runway_identifiers = runwayTable.getAllIds();

        BOOST_FOREACH(string runway_id, runway_identifiers)
        {
            if (runwayTable.exists(runway_id))
            {
                LpdbRunway & runway = runwayTable[runway_id];
                runway.resetNonAvailabilities();
            }
        }
    }

    typedef std::vector<LpiRunwayClosure>::iterator closures_iterator;

    std::vector<LpiRunwayClosure> runwayClosures = closures.getClosures();

    for (closures_iterator it = runwayClosures.begin(); it != runwayClosures.end(); it++)
    {
        std::string runwayId = (*it).getRunwayId();

//        if (runwayTable.exists(runwayId))
//        {
//            LpdbRunway & runway = runwayTable[runwayId];
//            runway.applyNoOperationReduction((*it).getStartTime(), (*it).getEndTime(), (*it).getReason(), true);
//        }
    }
}

void LpdBusinessLogicFacade::applyRunwayClosures(const LpdbWhatIfClosure & closures, bool mustResetState)
{
    LpdbDataBase::RunwayTable & runwayTable = LpdbDataBase::Get().getRunwayTable();

    if (mustResetState)
    {
        //Reset all availabilities prior to activation
        vector<string> runway_identifiers = runwayTable.getAllIds();

        BOOST_FOREACH(string runway_id, runway_identifiers)
        {
            if (runwayTable.exists(runway_id))
            {
                LpdbRunway & runway = runwayTable[runway_id];
                runway.resetNonAvailabilities();
            }
        }
    }

    typedef std::map<std::string, LpiRunwayClosure>::const_iterator runways_iterator;

    const std::map<std::string, LpiRunwayClosure> & runwayClosures = closures.getAllRunwayClosures();

    for (runways_iterator itr = runwayClosures.begin(); itr != runwayClosures.end(); itr++)
    {
        std::string runwayId = (*itr).first;

//        if (runwayTable.exists(runwayId))
//        {
//            LpdbRunway & runway = runwayTable[runwayId];
//            runway.applyNoOperationReduction((*itr).second.getStartTime(), (*itr).second.getEndTime(),
//                                             (*itr).second.getReason(), true);
//        }
    }
}

void LpdBusinessLogicFacade::applyRunwayClosures(const LpiRunwayClosure & closure)
{
//    LpdbDataBase::RunwayTable & runwayTable = LpdbDataBase::Get().getRunwayTable();
//
//    std::string runwayId = closure.getRunwayId();
//
//    if (runwayTable.exists(runwayId))
//    {
//        LpdbRunway & runway = runwayTable[runwayId];
//        runway.applyNoOperationReduction(closure.getStartTime(), closure.getEndTime(), closure.getReason(), true);
//    }
}

void LpdBusinessLogicFacade::activateRunwayClosures(int alternativeId)
{
    LpdbDataBase::AlternativeScheduleTable & alternativeSchedulesTable =
            LpdbDataBase::Get().getAlternativeScheduleTable();
    LpdbDataBase::WhatIfClosureTable & closuresTable = LpdbDataBase::Get().getWhatIfClosureTable();

    if (alternativeSchedulesTable.exists(alternativeId))
    {
        LpdbAlternativeSchedule & alternative = alternativeSchedulesTable[alternativeId];
        int closureId = alternative.getRunwayClosure();

        if ((closureId != -1) && closuresTable.exists(closureId))
        {
            LpdbWhatIfClosure & closures = closuresTable[closureId];

            bool mustOpenOtherRunways = closures.isBestPointClosureType() ? false : true;

            applyRunwayClosures(closures, mustOpenOtherRunways);

            calculateRunwayAndRSMaxCapacities();
        }
    }
}

int LpdBusinessLogicFacade::updateWhatIfDataBase(const LpiWhatIfClosure & closures, LpdbAlternativeSchedule & result,
                                                 LpiCalculationReason::LpiEnum & reason)
{
    LpiResult res;
//    LpiConfigurationParameters config;
//    getConfigurationParameters(config, res);

    LpdbWhatIfClosure closuresInformation;
    if (closures.isBestPointClosureType())
    {
        closuresInformation = LpdbWhatIfClosure(closures.getBestPointClosure().getClosure());
    }
    else
    {
        closuresInformation = LpdbWhatIfClosure(closures);
    }

    LpdbDataBase::WhatIfClosureTable & closuresTable = LpdbDataBase::Get().getWhatIfClosureTable();

    LpdbDataBase::AlternativeScheduleTable & alternatives = LpdbDataBase::Get().getAlternativeScheduleTable();

    int alternative_id;
    int runwayClosures_id;

    if ((closures.getId() == -1) || (!alternatives.exists(closures.getId())))
    {
#ifdef TRACE_OUT
        LclogStream::instance(LclogConfig::E_RTP).debug() << "Adding active schedule to alternatives table..." << std::endl;
#endif

        alternative_id = alternatives.addElement(result);
        runwayClosures_id = closuresTable.addElement(closuresInformation);

        reason = closures.getAssociatedCalculationReason();
    }
    else
    {
        alternative_id = closures.getId();
        runwayClosures_id = alternatives[alternative_id].getRunwayClosure();

        alternatives[alternative_id] = result;
        closuresTable[alternative_id] = closuresInformation;

        reason = closures.getAssociatedCalculationReasonForUpdate();
    }

#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).debug() << "Alternative updated with, id= " << alternative_id << ", name = " << closures.getName() << std::endl;
#endif

    alternatives[alternative_id].setId(alternative_id);
    alternatives[alternative_id].setName(closures.getName());

    //Update Ids and expiration information
    LpdbExpirationInfo expirationInformation;
    expirationInformation.setAutomaticDeletion(!closures.getAvoidAutomaticDeletion());
    //expirationInformation.setExpirationHours(config.getAlternativeSchedulesExpirationHours());

    alternatives[alternative_id].setExpirationInformation(expirationInformation);
    alternatives[alternative_id].setRunwayClosure(runwayClosures_id);
    closuresTable[runwayClosures_id].setAlternativeScheduleId(alternative_id);

#ifdef TRACE_OUT
    LclogStream::instance(LclogConfig::E_RTP).debug() << "Closures DataBase: " << std::endl;
    LclogStream::instance(LclogConfig::E_RTP).debug() << closuresTable << std::endl;

    //Trace and Logging
    LclogStream::instance(LclogConfig::E_RTP).info() << "Real DCB calculations..." << std::endl;
    LclogStream::instance(LclogConfig::E_RTP).info() << alternatives[alternative_id] << std::endl;

    LclogStream::instance(LclogConfig::E_RTP).info() << LpdbDataBase::Get().getAlternativeScheduleRwyAllocationsAsString(alternative_id) << std::endl;
    LclogStream::instance(LclogConfig::E_RTP).info() << LpdbDataBase::Get().getScheduledFlightPlansAsString(LpdbSchedule::E_ALTERNATIVE, alternative_id);
#endif

    return alternative_id;
}

void LpdBusinessLogicFacade::sendAlternativeSchedule(int alternativeId, LpiCalculationReason::LpiEnum reason)
{
//    LpiConfigurationAlertKPIs alertKPIs;
//    LpiResult res;
//    getConfigurationAlertKPIs(alertKPIs, res);

    //Send result
    LpdbDataBase::AlternativeScheduleTable & alternatives = LpdbDataBase::Get().getAlternativeScheduleTable();

    LpdbAlternativeSchedule to_send = alternatives[alternativeId];

//    LpiAlternativeSchedule scheduleData = LpdbAlternativeSchedule::Convert2AlternativeInterface(to_send, alertKPIs);
//    scheduleData.setCalculationReason(reason);
//
//    LpiAlternativeScheduleEvt event;
//    event.setAlternativeSchedule(scheduleData);

    //In case of runway closures closureId: calculate best point for closure,
    //Send also selected point
    int closureId = to_send.getRunwayClosure();
    if (closureId != -1)
    {
        LpdbDataBase::WhatIfClosureTable & closuresTable = LpdbDataBase::Get().getWhatIfClosureTable();

        if (closuresTable.exists(closureId))
        {
            //LpdbWhatIfClosure & closure = closuresTable[closureId];

//            if (closure.isBestPointClosureType() && (closure.getNumberOfElements() == 1))
//            {
//                //Calculated solution: It must contain only one closure (will be sent on first position on closures list)
//                LpiRunwayClosure runwayData = closure.getFirstClosure();
//
//                event.addClosure(runwayData);
//
//                //Get current closures in database
//                vector<LpiRunwayClosure> currentClosures = getCurrentClosures();
//                for (unsigned int i = 0; i < currentClosures.size(); ++i)
//                {
//                    event.addClosure(currentClosures[i]);
//                }
//            }
        }
    }

    //LpdComponent::Get().publish(event);
}

void LpdBusinessLogicFacade::reviewObsoleteWhatIfs()
{
    LpdbDataBase::AlternativeScheduleTable & alternativesTable = LpdbDataBase::Get().getAlternativeScheduleTable();

    vector<int> alternatives = alternativesTable.getAllIds();

    vector<int> deletedIds;

    BOOST_FOREACH(int alternativeId, alternatives)
    {
        LpdbAlternativeSchedule & alternative = alternativesTable[alternativeId];

        const LpdbExpirationInfo & expirationInformation = alternative.getExpirationInformation();

#ifdef TRACE_OUT
        LclogStream::instance(LclogConfig::E_RTP).debug() 
	  << "Alternative " << alternativeId << "\n" 
	  << expirationInformation << std::endl;
#endif

        if (expirationInformation.isExpired() && expirationInformation.getAutomaticDeletion())
        {
            boost::posix_time::ptime now = LctimVirtualClock::Get().getTime();
            boost::posix_time::ptime cancelationDate = expirationInformation.getCancellationTime();

            if (now >= cancelationDate)
            {
#ifdef TRACE_OUT
                LclogStream::instance(LclogConfig::E_RTP).debug() << "Deleting alternative " << alternativeId << std::endl;
#endif
                deleteSchedule(alternativeId);

                deletedIds.push_back(alternativeId);
            }
        }
    }

    //publish deletedIds
    if (deletedIds.size() > 0)
    {
        LpiAutomaticDeletionEvt event;
        event.setDeletedScheduleIds(deletedIds);

        LpdComponent::Get().publish(event);
    }
}

void LpdBusinessLogicFacade::setExpirationDateForWhatIfs(boost::posix_time::ptime expirationDate, int idWhatIfToExclude)
{
    LpdbDataBase::AlternativeScheduleTable & alternativesTable = LpdbDataBase::Get().getAlternativeScheduleTable();

    vector<int> alternatives = alternativesTable.getAllIds();

    BOOST_FOREACH(int alternativeId, alternatives)
    {
        if (idWhatIfToExclude != alternativeId)
        {
            LpdbAlternativeSchedule & alternative = alternativesTable[alternativeId];

            if (!alternative.isExpired())
            {
                alternative.setExpirationDate(expirationDate);
            }
        }
    }
}

//-------------------------------------------------------------------------------

///@warning removed RMAN function:  void LrdBusinessLogicFacade::generateWhatIfBestPointForClosure(const LriWhatIfClosure & closures)

//-------------------------------------------------------------------------------

void LpdBusinessLogicFacade::printRSDataBaseState() const
{
    LpdbDataBase::RunwayTable & runwaysState = LpdbDataBase::Get().getRunwayTable();
    LpdbDataBase::RunwaySystemTable & runwaySystemsState = LpdbDataBase::Get().getRunwaySystemTable();
    TimeLine<LpdbDCBAirportTimedData> & dcbAirportTimeline = LpdbDataBase::Get().getDCBAirportTimeline();

    LclogStream::instance(LclogConfig::E_RTP).debug() << "[RUNWAYS:\n" << runwaysState << "| RUNWAY SYSTEMS:\n"
                                                      << runwaySystemsState << "| DCB AIRPORT TIMELINE:\n"
                                                      << dcbAirportTimeline << ']' << std::endl;
}

void LpdBusinessLogicFacade::calculateTurnRound(LpiFlightPlan & fp)
{
    int minutesCloseRound = LpdbDataBase::Get().getGlobalParameters().getClosedTurnRound();
    boost::posix_time::ptime beginTimeLine = LpdbDataBase::Get().getTimeLineBase();

    LpdbDataBase::FPTable & fpTable = LpdbDataBase::Get().getFPTable();

    vector<string> storedFPKeys = fpTable.getAllIds();

    bool isStoredFPArrivalType = false;

    BOOST_FOREACH(string fpKey, storedFPKeys)
    {
        LpiFlightPlan & storedFP = fpTable[fpKey];

        if (fp.getRegistration() == storedFP.getRegistration())
        {
            LpiOperationType::LpiEnum fpOperation = fp.getOperationType();
            LpiOperationType::LpiEnum storedFPOperation = storedFP.getOperationType();

            if (fpOperation != storedFPOperation)
            {
                boost::optional<boost::posix_time::ptime> itot;
                boost::optional<boost::posix_time::ptime> ildt;

                switch(fpOperation)
                {
                    case LpiOperationType::E_ARRIVAL:
                        ildt = fp.getIntentionalTime();
                        break;
                    case LpiOperationType::E_DEPARTURE:
                        itot = fp.getIntentionalTime();
                        break;
                    case LpiOperationType::E_NONE:
                    default:
                        break;
                }

                switch(storedFPOperation)
                {
                    case LpiOperationType::E_ARRIVAL:
                        ildt = storedFP.getIntentionalTime();
                        isStoredFPArrivalType = true;
                        break;
                    case LpiOperationType::E_DEPARTURE:
                        itot = storedFP.getIntentionalTime();
                        break;
                    case LpiOperationType::E_NONE:
                    default:
                        break;
                }

            if (itot && ildt &&
               (itot >= beginTimeLine) &&
               (ildt >= beginTimeLine) &&
               (*itot > *ildt))
                {
                    fp.setTurnRoundKey(storedFP.getUniqueKey());
                    storedFP.setTurnRoundKey(fp.getUniqueKey());
#ifdef TRACE_OUT
                    std::cout << "TURN-ROUND detected:\nReceived FP: " << fp << "\nStoredFP: " << storedFP << std::endl;
#endif
                    int difference = static_cast<int>((*itot - *ildt).total_seconds() / 60);

                    if (difference < minutesCloseRound)
                    {
                        if (isStoredFPArrivalType)
                        {
                            storedFP.setClosedTurnRound(true);
                        }
                        else
                        {
                            fp.setClosedTurnRound(true);
                        }
                    }
                }
            }
        }
    }
}


void LpdBusinessLogicFacade::calculatePriority(LpiFlightPlan & fp)
{
    LpiPriorityTable priorities;
    LpiResult result;

    getPriorityTableDepartures(priorities, result);

    int priorityDepartures = priorities.calculatePriorityDepartures(fp);
    fp.setPriorityDepartures(priorityDepartures);

    getPriorityTableArrivals(priorities, result);

    int priorityArrivals = priorities.calculatePriorityArrivals(fp);
    fp.setPriorityArrivals(priorityArrivals);

#ifdef TURN_ROUND
    string associatedFP = fp.getTurnRoundKey();

    if (associatedFP != "")
    {
        LpdbDataBase::FPTable & fpTable = LpdbDataBase::Get().getFPTable();

        if (fpTable.exists(associatedFP))
        {
            LpiFlightPlan & turnRoundFPArrival = fpTable[associatedFP];

            LpiOperationType::LpiEnum fpTurnRoundType = turnRoundFPArrival.getOperationType();

            bool isClosedTurnRound = turnRoundFPArrival.isClosedTurnRound();

            if ((fpTurnRoundType == LpiOperationType::E_ARRIVAL) &&
                    isClosedTurnRound)
            {
                int priority = priorities.calculatePriority(turnRoundFPArrival);
                turnRoundFPArrival.setPriority(priority);
            }
        }
    }
#endif

}


vector<LpiRunwayClosure> LpdBusinessLogicFacade::getCurrentClosures()
{
    vector<LpiRunwayClosure> result;

    LpdbDataBase::RunwayTable & runwaysTable = LpdbDataBase::Get().getRunwayTable();
    vector<string> runwaysIds = runwaysTable.getAllIds();

    BOOST_FOREACH(string runwayId, runwaysIds)
    {
        LpdbRunway & runway = runwaysTable[runwayId];

        vector<string> intervals = runway.getAllIntervalIds();

        string firstConsecutiveInterval = "";
        string lastConsecutiveInterval = "";
        LpiClosureReason::LpiEnum lastReason = LpiClosureReason::E_NONE;

        bool firstNonAvailableFound = false; //true when current is non available without reason

        BOOST_FOREACH(string interval, intervals)
        {
            if (runway.has_data(interval) && runway[interval].isNonAvailability())
            {
                LpiClosureReason::LpiEnum reason = runway[interval].getClosureReason();

                if (reason == lastReason)
                {
                    if ((reason == LpiClosureReason::E_NONE) && !firstNonAvailableFound)
                    {
                        firstNonAvailableFound = true;
                        firstConsecutiveInterval = interval;
                    }

                    lastReason = reason;
                    lastConsecutiveInterval = interval;
                }
                else
                {
                    if (firstConsecutiveInterval != "")
                    {
                        optional<TimeInterval> firstInterval = runway.getIntervalParameters(firstConsecutiveInterval);
                        optional<TimeInterval> lastInterval = runway.getIntervalParameters(lastConsecutiveInterval);

                        if (firstInterval && lastInterval)
                        {
                            LpiRunwayClosure closure(runwayId, (*firstInterval).begin, (*lastInterval).end, lastReason);
                            result.push_back(closure);
                        }
                        else if (firstInterval)
                        {
                            LpiRunwayClosure closure(runwayId, (*firstInterval).begin, (*firstInterval).end,
                                                     lastReason);
                            result.push_back(closure);
                        }
                    }

                    firstConsecutiveInterval = interval;
                    lastConsecutiveInterval = "";
                    lastReason = reason;
                }
            }
            else
            {
                if (firstConsecutiveInterval != "")
                {
                    optional<TimeInterval> firstInterval = runway.getIntervalParameters(firstConsecutiveInterval);
                    optional<TimeInterval> lastInterval;

                    if (lastConsecutiveInterval != "")
                    {
                        lastInterval = runway.getIntervalParameters(lastConsecutiveInterval);
                    }

                    if (firstInterval && lastInterval)
                    {
                        LpiRunwayClosure closure(runwayId, (*firstInterval).begin, (*lastInterval).end, lastReason);
                        result.push_back(closure);
                    }
                    else if (firstInterval)
                    {
                        LpiRunwayClosure closure(runwayId, (*firstInterval).begin, (*firstInterval).end, lastReason);
                        result.push_back(closure);
                    }
                }

                firstConsecutiveInterval = "";
                lastConsecutiveInterval = "";
                lastReason = LpiClosureReason::E_NONE;
            }
        }

        //Check if there are non available at the end of the line
        if (firstConsecutiveInterval != "")
        {
            optional<TimeInterval> firstInterval = runway.getIntervalParameters(firstConsecutiveInterval);
            optional<TimeInterval> lastInterval;

            if (lastConsecutiveInterval != "")
            {
                lastInterval = runway.getIntervalParameters(lastConsecutiveInterval);
            }

            if (firstInterval && lastInterval)
            {
                LpiRunwayClosure closure(runwayId, (*firstInterval).begin, (*lastInterval).end, lastReason);
                result.push_back(closure);
            }
            else if (firstInterval)
            {
                LpiRunwayClosure closure(runwayId, (*firstInterval).begin, (*lastInterval).end, lastReason);
                result.push_back(closure);
            }
        }

    }

    return result;
}

void LpdBusinessLogicFacade::reviewClockForwardingForActivation(
        const LpiActivationType::ActivationType & activationType)
{
    LpdbDataBase & db = LpdbDataBase::Get();

    boost::posix_time::ptime currentBase = db.getTimeLineBase();

    if (db.hasActiveSchedule())
    {
        LpdbAlternativeSchedule & active = db.getActiveSchedule();

        boost::optional<boost::posix_time::ptime> begin = active.getTimeLine().getInitialTime();

        if (begin)
        {
#ifdef TRACE_OUT
            LclogStream::instance(LclogConfig::E_RTP).debug() << "TEST_CLOCK:  current base = " << currentBase
                                                              << ", initial time = " << *begin << std::endl;
#endif
            if (currentBase > *begin)
            {
#ifdef TRACE_OUT
                LclogStream::instance(LclogConfig::E_RTP).debug() << "TEST_CLOCK: must review clock for activation"<< std::endl;
#endif
                active.forward();

                std::string new_interval = active.getTimeLine().getLastInterval();
                generateRSForActiveScheduleLastInterval(new_interval);

                bool isClockForwarding = true;
                performActiveScheduleCalculations(isClockForwarding);

                if ((activationType == LpiActivationType::E_WHAT_IF_3_NEW_SOLUTION) || 
                    (activationType == LpiActivationType::E_WHAT_IF_3_BEST_POINT))
                {
                    LpdbAlternativeSchedule & currentActive = LpdbDataBase::Get().getActiveSchedule();
                    LpdbDataBase::Get().setOptimalSchedule(currentActive);
                    LpdbSchedule & optimal = LpdbDataBase::Get().getOptimalSchedule();
                    optimal.setOrigin(LpiActivationType::E_OPTIMAL);
#ifdef TRACE_OUT
                    LclogStream::instance(LclogConfig::E_RTP).debug() << "TEST_CLOCK: New active is also new optimal" << std::endl;
#endif
                }
            }

            if ((activationType == LpiActivationType::E_WHAT_IF_3_NEW_SOLUTION) || 
                (activationType == LpiActivationType::E_WHAT_IF_3_BEST_POINT))
            {
#ifdef TRACE_OUT
                LclogStream::instance(LclogConfig::E_RTP).debug() << "TEST_CLOCK: Publishing optimal schedule, type = "
                                                                  << activationType << std::endl;
#endif
                publishOptimalSchedule(LpiCalculationReason::E_MANUAL_ACTIVATION);
            }
        }
    }

}
