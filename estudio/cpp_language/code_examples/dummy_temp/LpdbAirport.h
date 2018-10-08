/*
 * LpdbAirport.h
 *
 * @warning LpdbAirport: process info from DAORTP_AirportsInfo.xml.
 *
 * DOC Reference: [1] "2018-08-03 RTP Diseño Funcional.docx"
 *
 */

#ifndef LPBAIRPORT_H_
#define LPBAIRPORT_H_

#include <LpiAdaptationAirportsInfo.h>
#include <LpdbMeteoTimedData.h>
#include <LctimTimeLine.h>
#include <LpdbDemand.h>
#include <LpiMeteoInfo.h>
#include <LpdbTMA.h>
#include <LpdbTWY.h>

#include <boost/optional.hpp>

#include <string>
#include <vector>

class LpdbAirport
{
 public:

  LpdbAirport(std::string id,
	      unsigned int totalMovAirportUpperThreshold,
	      unsigned int totalMovAirportLowerThreshold,
	      unsigned int vfrAirportUpperThreshold,
	      unsigned int vfrAirportLowerThreshold,
	      unsigned int N1,
	      unsigned int taxywaysMaxNominalCapacity,
	      unsigned int tmaMaxNominalCapacity);

  LpdbAirport()=default;
  LpdbAirport(const LpdbAirport & source)=default;
  LpdbAirport & operator= (const LpdbAirport & source) = default;
  virtual ~LpdbAirport() {}

  std::string getAirportId() const;
  unsigned int getTotalMovAirportUpperThreshold()const;
  unsigned int getTotalMovAirportLowerThreshold()const;
  unsigned int getVfrAirportUpperThreshold()const;
  unsigned int getVfrAirportLowerThreshold()const;


  void setAirportId(std::string id);


  //Forwards internal timeline in one interval
  void forwardTimeline();


  ////////////////////////////////////////
  /// Capacity data
  ////////////////////////////////////////
  inline unsigned int get_taxywaysNominalCapacity()const;
  inline unsigned int get_tmaNominalCapacity()const;
  inline LpdbTMA & getTMA() { return the_tma; }
  inline LpdbTWY & getTWY() { return the_twy; }

  void initCapacity(const LpiTimeParameters & timeData,
		    const boost::posix_time::ptime &now);
  void forwardCapacity();


  ////////////////////////////////////////
  /// Demand data
  ////////////////////////////////////////

  LpdbDemand & getDemand()
  { return r_demand; }
  

  ////////////////////////////////////////
  /// Meteo data
  ////////////////////////////////////////

  TimeLine<LpdbMeteoTimedData> & getMeteoForecast()
  {
    return r_meteoLine;
  }

 
  void setMeteoForecast(const TimeLine<LpdbMeteoTimedData> & data)
  {
    r_meteoLine = data;
  }


  //Forwards internal timeline in one interval
  unsigned int getNumberOfMeteoReportsReceived (); //const;
  std::vector<LpiMeteoInfo> getReceivedMeteoReports (); // const;
  LpiMeteoInfo getMeteoReport (const unsigned int index);
  void addMeteoReport (const LpiMeteoInfo &report);
  void deleteMeteoReport (unsigned int index);
  void deleteObsoleteMeteoReports();//remove ALL obsolete reports

  /**@warning getLastReceivedMeteoReport: UNUSED in RMAN
  boost::optional<LpiMeteoInfo> getLastReceivedMeteoReport () const;
  */


      /* Lo siguiente está copiado de LpdbRunway.h */

      /* //Check if has data associated to one given interval name */
      /* bool has_data(const string & interval_name); */

      /* //Get one element from internal timeline for modification */
      /* LpdbAirportTimedData & operator[] (const string & interval_name); */

      /* //stablish timeline */
      /* void init(const LpiTimeParameters & parameters, */
      /*           boost::posix_time::ptime begin_timestamp); */

      /* //Forwards internal timeline in one interval */
      /* void forwardTimeline(); */


      //Getters and setters

      //For logging purposes
      //      string getMaxCapacityScheduledAsString() const;


      /* vector<string> getAllIntervalIds() const; */
      /* optional<TimeInterval> getIntervalParameters(string interval); */


 protected:

  ///////////////////////////////////////////////////////////////
  ///data area
  ///////////////////////////////////////////////////////////////

  std::string theAirportName;

  // (airport/interval) thresholds & prohibitions (see [1].4.1)
  //
  // i) total movements (DAORTP_AirportsInfo.xml)
  unsigned int theTotalMovAirportUpperThreshold;
  unsigned int theTotalMovAirportLowerThreshold;
  // ii) VFR flight (DAORTP_AirportsInfo.xml)
  unsigned int theVfrAirportUpperThreshold;
  unsigned int theVfrAirportLowerThreshold;


  ////////////////////////////////////////
  /// Capacity data
  ///
  ///@brief [1].4.3.1 Capacidades de TMA y Taxyways. Se toma como punto de
  ///       partida las capacidades nominales de ambas y se dividen entre
  ///       el valor N1 para obtener el número de movimientos posibles por subintervalo:
  ///       TMA.Capacity (ti) = (TMA.Nominal_Capacity / N1)
  ///       TWY.Capacity (ti) = (TWY.Nominal_Capacity / N1)
  ///
  ///
  ///@param the_tmaNominalCapacity: TMA nominal capacity for the airport
  ///@warning Set at construction with the value from the adap file => const 
  //
  ///@param the_twyNominalCapacity: taxy ways nominal capacity for the airport
  ///@warning Set at construction with the value from the adap file => const 
  ///
  ///@warning ADO not required for nominal TMA & TWY: they will be eventually
  ///         compared to Airport_Capacity see [1].4.3.1, last paragraph),
  ///         that is the minimum of (ARR,DEP,OVE).
  ///
  ///
  ///@param the_tma: TMA per interval for the airport
  ///@param the_twy: TWY per interval for the airport
  ///
  ////////////////////////////////////////
  unsigned int the_twyNominalCapacity;
  unsigned int the_tmaNominalCapacity; 
  LpdbTMA      the_tma;
  LpdbTWY      the_twy;


  /*@param theAirportAdapData
    @brief Saves the daptationAirportsInfo loaded for the airport.
    @warning Faster access to the daptationAirportsInfo for the airport,

    std::string _airportName;
    AirportType _airportType;
    AirportMaxNominalCapacity _airportMaxNominal;
    unsigned int _taxywaysMaxNominalCapacity;
    unsigned int _tmaMaxNominalCapacity;
    RunwayMaxIlsCategory _airportMaxILsCategory;
    RunwaysAirportsList _runway;
    LvpActivacionConditonsList _lvpActivationConditions;
    CatILsList _catILs;
    ComplexityAirportsThresholds _complexityThresholds;
   */
  /// Airport theAirportAdapData; ///@todo iff required

  ////////////////////////////////////////
  /// Demand data
  ////////////////////////////////////////
  LpdbDemand                   r_demand;

  ////////////////////////////////////////
  /// Meteo data
  ////////////////////////////////////////

  /**@param r_meteoLine
   *
   * @brief Storing the meteo information actually required for the
   *        RTP's logic calculations (complexity and capacity)
   *        calculations.
   *
   * Stored info: TimeLine<LpdbMeteoTimedData>: one meteo data per
   *              interval, thus every new meteo report received will
   *              replace the current one stored.
   *
   * - Use case: new meteo nowcast received: storage the new data
   *             (substitution of the old one)
   *
   * - Use case: new meteo forecast received: storage the new data
   *             (substitution of the old one)
   *
   * - Use case: forward timeline: remove obsolete data & add data for
   *             the new (last) interval.
   *  
   * @info class LpdbMeteoTimelineConverter: 
   *             converter TimeLine<LpdbMeteoTimedData> => LpiMeteoTimeline
   */
  TimeLine<LpdbMeteoTimedData> r_meteoLine;

  
  /**@param r_meteoReports: last meteo reports received (nowcast or forecast)
   *
   * @brief Used to manage the logic of forwardTimeLine at LpdBusinessLogicFacade::reviewMeteoInfo:
   *        For every report stored, update DB's timeline for that period: period is active
   *                               , remove report: if obsolete
   *
   * @warning (use case: new meteo now/fore msg) Just adds all the new reports received,
   *          thus repeated data can exists for any (airport, interval) pair.
   *          Note/Hint.- the most recent info is stored at the end of the vector.
   *
   */
  vector<LpiMeteoInfo> r_meteoReports;


  ///////////////////////////////////////////////////////////////
  ///methods area
  ///////////////////////////////////////////////////////////////
  
  void forwardTimeLineMeteo();
  void forwardTimeLineDemand();

};

std::ostream& operator<<(std::ostream &os, const LpdbAirport &obj);

#endif /* LPBAIRPORT_H_ */
