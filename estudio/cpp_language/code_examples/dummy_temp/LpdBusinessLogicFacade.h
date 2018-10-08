#if !defined(__LPD_BUSINESS_LOGIC_FACADE_H__)
#define __LPD_BUSINESS_LOGIC_FACADE_H__


#include <LpiInterfaces.h>
#include "LpdbRunwaySystem.h"
#include "LpdbAlternativeSchedule.h"
#include <LpschAbstractSchedulesGenerator.h>
#include <LpiSchedule.h>
#include <LpiScheduleActivation.h>
#include <LpiActiveSchedule.h>
#include "LpdbWarningErrors.h"
#include "LpdbDataBase.h"
#include <LpiFlightPlan.h>
#include <LpiDemand.h>

class LpdBusinessLogicFacade : public LpiILifeCycle,
                               public LpiIGetAdaptationRunway,
                               public LpiIGetAdaptationRunwaySystem,
                               public LpiIGetAdaptationAirportsInfo,
                               public LpiIForwardTimeline,
                               public LpiIGetSystemTime,
                               public LpiICalculateMaxCapacities,
                               public LpiICalculateEstimatedDCB,
                               public LpiICalculateRealDCB,
                               public LpiICalculateRunwayAllocation,
                               public LpiICalculateRunwayFinalAssignation,
                               public LpiIScheduleActivation,
                               public LpiICalculateRealDCBAndRunwayAllocation,
                               public LpiIPerformActiveScheduleCalculations,
                               public LpiIPerformFPInScheduleCalculations,
                               public LpiIGenerateSchedules,
                               public LpiIGenerateManualSchedule,
                               public LpiIScheduleDeletion,
                               public LpiISchedulesComparison,
                               public LpiISchedulesPublish,
                               public LpiIKeyPerformanceIndicatorsCalculations,
                               public LpiIUpdateDemand,
                               public LpiIWhatIfRunwayClosures,
                               public LpiIGetPriorityTable
{
public:

   LpdBusinessLogicFacade();
   ~LpdBusinessLogicFacade();

   // Eventos consumidos
   virtual void updateDemandTimeAndDate(const posix_time::ptime   &timeAndDate, std::string airport);
   virtual void updateDemand(const LpiFlightPlan &data);
   virtual void updateMeteoForecast (const LpiCreateMeteoList &meteolist);
   virtual void updateMeteoNowcast(const LpiCreateMeteoList & meteolist);
   virtual void updateScheduleActivation(const LpiScheduleActivation &scheduleActivation);

   virtual void updateCapacityReductions (const LpiCapacityReductions &reductions);
   virtual void updateOptimizationCriteria (const LpiOptimizationCriteria &criteria);


   // Published events (implemented in BaseComponent)

   virtual void getSystemTime (LpiTime & tick, LpiResult & result) ;


   virtual void getConfigurationCoreParameters (
                                        LpiConfigurationCoreParameters & parameters,
                                        LpiResult & result);

   virtual void getConfigurationHmiParameters (
                                        LpiConfigurationHmiParameters & parameters,
                                        LpiResult & result);


   virtual void getAdaptationMrtmInfo(LpiAdaptationMrtmInfo &mrtm_info,
		   	   	   	   	   	   	   	   LpiResult & result);

   virtual void getAdaptationAssignmentPreference(LpiAdaptationAssignmentPreference &ass_pref,
                                       LpiResult & result);

   virtual void getAdaptationRunway (LpiAdaptationRunwayList & runways,
                                     LpiResult & result);

   virtual void getAdaptationRunwaySystem (
                                     LpiAdaptationRunwaySystemList & runway_systems,
                                     LpiResult & result);

   virtual void getAdaptationAirportsInfo(
                                     LpiAdaptationAirportsInfo &airportsInfo,
                                     LpiResult & result);

   virtual void getAdaptationAlert_KPIs(LpiAdaptationAlert_KPIs &configurationAlert_KPIs,
                                           LpiResult &result);

   virtual void getPriorityTableDepartures(LpiPriorityTable & priorities, LpiResult & result);
   virtual void getPriorityTableArrivals(LpiPriorityTable & priorities, LpiResult & result);

   virtual void getWakeVortexCapacityReductions(
                                   LpiWakeVortexCapacityReductions & capacity,
                                   LpiResult & result);

   virtual void create(void);
   virtual void initialise(void);
   virtual void complete(void);

   virtual void forwardTimeline(void);

   LpiTime& currentTime(void) {return this->_currentTime;}


   //Capacities Calculations
   virtual void calculateMaxCapacities(void);
   virtual void calculateRunwayAndRSMaxCapacities();
   //virtual void calculateRunwaysMaxCapacities(void);
   //virtual void calculateRunwaysMaxCapacities(string);
   virtual void calculateRSMaxCapacities(void);
   virtual void calculateRSMaxCapacities(string);

   virtual void calculateAirportMaxCapacitiesAndMinDelayedFPs(void);
   //virtual void calculatePriorityOperation(string interval);
   //virtual void calculateAirportMaxCapacitiesForAllRS(const string & interval);
   //virtual void calculateMinDelayedFPs(const string &);

   //Demand Capacity Balance Calculations, interface with Component layer
   virtual void calculateEstimatedDCB(void);
   virtual void calculateEstimatedDCB(std::string interval);
   virtual void updateHMIDemand(const LpiCalculationReason::LpiEnum & reason, LpiCreateDemand demandL);
   virtual void updateHMIDemand(const LpiCalculationReason::LpiEnum & reason, std::string airport);
   virtual void publishUpdateDemandToHmi();

   //virtual void calculateDCBSuitability(void);
   //virtual void calculateEstimatedDelayedFPs(void);

   //Schedules Generation via Pathfinding algorithm

   //Generate schedules via 1 invocation to pathfinding algorithm
   virtual void generateSchedulesForAllIntervals(void);
   //Generate existent optimal schedule with a newly generated node for the new interval
   virtual void generateSchedulesForLastInterval(string new_interval);

   //Generate existent optimal schedule with only frozen part and newly created intervals
   virtual void generateSchedulesForClock(int minutesFrozenForClock);

   //Real Demand Calculations
   virtual void calculateRealDCB(void);
   virtual void calculateRealDCB(std::string interval);
 
   //KPIs calculations
   virtual void calculateSchedulesKPIs(bool isClockForwarding, bool isInitialization = false);

   //Optimal Schedule
   virtual void generateOptimalSchedule();

   //Flight Plan Runway Allocations
   virtual void calculateRunwayAllocation(void);
   virtual void calculateRunwayAllocation(std::string interval);

   //Runway Final Assignation
   virtual void calculateRunwayFinalAssignation(void);
   virtual void calculateRunwayFinalAssignation(std::string interval);

   //Schedule activation
   virtual void activateSchedule(int, LpiScheduleActivationType::LpiEnum activation_type =
                                      LpiScheduleActivationType::E_AUTO);

   //Optimization: Both calculations on same element and interval
   virtual void calculateRealDCBAndRunwayAllocation();
   virtual void calculateActiveRealDCBAndRunwayAllocation();
   virtual void calculateRealDCBAndRunwayAllocation(std::string interval);

   //FTOT, FLDT, forecast delay and punctuality delay
   virtual void performFPInScheduleCalculations();

   virtual void performActiveScheduleCalculations(bool isClockForwarding, bool isInitialization = false);

   virtual void generateManualSchedule (const LpiAlternativeSchedule & manualSchedule);
   virtual void deleteSchedule(int scheduleId);
   virtual void compareSchedules(const LpiSchedulesComparison & schedulesToCompare);

   virtual void publishOptimalAndActiveSchedules(const LpiCalculationReason::LpiEnum & reason);
   virtual void publishOptimalSchedule(const LpiCalculationReason::LpiEnum & reason);
   virtual void publishActiveSchedule(const LpiCalculationReason::LpiEnum & reason);

   virtual void deleteNotReceivedFPs(vector<string> & receivedFPKeys);
   virtual void calculateTurnRound(LpiFlightPlan & fp);
   virtual void calculatePriority(LpiFlightPlan & fp);

   virtual void generateWhatIfClosuresforActive(const LpiWhatIfClosure & closures);
   virtual void generateWhatIfClosuresforOptimal(const LpiWhatIfClosure & closures);
   virtual void setExpirationDateForWhatIfs(boost::posix_time::ptime expirationDate,
                                            int idWhatIfToExclude = -1);

protected:

   void showAdapAndConfigInfo();

   //Calculations for one rs in one determined interval, invoked from interface methods
   void calculateEstimatedNotAllowed(std::string interval, LpdbRunwaySystem & rs);
   void calculateEstimatedDCB(std::string interval, LpdbRunwaySystem & rs);

   //Updates arrivals, departures, and overall demand numbers
   void calculateTimedDemand ();                         //calculates whole timeline demand
   void calculateTimedDemand (std::string interval, std::string airport);     //calculates demand only in one interval
   void calculateTimedDemand (const LpiFlightPlan & fp, boost::optional<ptime>); //updates demand with one fp data

   //Check FPs for cancelation by age
   void reviewObsoleteFlightPlans (int minutes_threshold);
   void reviewObsoleteFlightPlansByAssignedTime (int minutes_threshold);
   void reviewTurnRound(string fpKey);


   /**@fn void LpdBusinessLogicFacade::reviewMeteoInfo(std::string new_interval)

      @brief Fall all the managed airports, check meteo info on clock
      event (add stored info to new interval)

      - Update meteo info in the DB after a CLOCK event (for all airports);
      - Send meteo info for the new interval to the HMI (for all airports)
   */
   void reviewMeteoInfo(std::string new_interval);
   
   ///@brief reviewMeteoInfo for the pair (airport, interval)
   void reviewMeteoInfo(std::string airport_id, std::string new_interval);



   //Max Capacities Calculations
   void calculateMaxCapacities(string interval);
   void calculateTMATWYsMaxCapacities(std::string airport_id);
   void calculateTMATWYsMaxCapacities(std::string airport_id,
				      std::string interval);

   //Monitoring functionality methods
   void activateOptimalSchedule();

   void calculateWhatIfMode1(const LpiOptimizationCriteria & criteria);

   //void generateMrtmTransitionCosts(LpiAdaptationMrtmTransitionCostTable & transitions);

   void generateRSForActiveScheduleLastInterval(string interval);

   //aux methods for algorithm generation
   string getLastFrozenNodeOfActiveSchedule(const vector<string> & frozen) const;
   string getLastFrozenNodeOfOptimalSchedule(const vector<string> & frozen) const;

   LpiADOVector<int> getEstimatedDelayed(string initialNode, string interval);

   //Auxiliary methods for What-if 3
   void performCalculationsInSchedule(LpdbAlternativeSchedule & schedule);
   void applyRunwayClosures(const LpiWhatIfClosure & closures, bool mustResetState = true);
   void applyRunwayClosures(const LpdbWhatIfClosure & closures, bool mustResetState = true);
   void applyRunwayClosures(const LpiRunwayClosure & closure);

   void activateRunwayClosures(int alternativeId);
   int updateWhatIfDataBase(const LpiWhatIfClosure & closures,
                            LpdbAlternativeSchedule & result,
                            LpiCalculationReason::LpiEnum & reason);

   void sendAlternativeSchedule(int alternativeId,
                                LpiCalculationReason::LpiEnum reason);

   void reviewObsoleteWhatIfs();

   vector<LpiRunwayClosure> getCurrentClosures();

   void reviewClockForwardingForActivation(const LpiActivationType::ActivationType & origin);

   //Auxiliar method for logging
   void printRSDataBaseState() const;

   ///@brief Send Meteo (nowcast) data to the HMI
   void updateMeteoNowcastHmi(const LpiCreateMeteoList & meteolist);

   ///@brief Send Meteo (forecast) data to the HMI
   void updateMeteoForecastHmi(const LpiCreateMeteoList & meteolist);

   ///@brief update DB with the new meteo NOWcast data received
   void updateMeteoNowcastDB(const LpiCreateMeteoList & meteolist);
   void updateMeteoNowcastDB(const LpiCreateMeteo & meteoData);

   ///@brief update DB with the new meteo FOREcast data received
   void updateMeteoForecastDB(const LpiCreateMeteoList & meteolist);
   void updateMeteoForecastDB(const LpiCreateMeteo & meteoData);
     

private:
   LpiTime     _currentTime;
   LpiUpdateDemandList demandUpdateList;

   boost::shared_ptr<LpschAbstractSchedulesGenerator> _schedules_generator;
};



#endif // __LPD_BUSINESS_LOGIC_FACADE_H__
