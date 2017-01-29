#ifndef _STATE_CLASS_H
#define _STATE_CLASS_H

/*
  Four states: Off, TurningOn, ON, eTurningOff.

*/


namespace avionic_control
{

  //----------------------------------------------------------------------------

  class RDStateBase
  {
  protected:

    void power_on()=0;
    void power_off()=0;
    void cut_milbus()=0;
    double calculate_energy_consumption()=0;

    void init()=0;
    void run()=0;  // main actions executed in the active state
  
  };/*StateBase*/

  //----------------------------------------------------------------------------

  class RDStateOff : public RDStateBase
  {
  public:

  RDStateOff(RDStateManager & manager): the_manager(manager) {}
  
    void power_on() { the_manager.set_state_turningon(); }
  
    void power_off() {} //not applicable

    void cut_milbus() {} //not applicable
  
    double calculate_energy_consumption() { return 0.0; }

  
    void init()   {} //nothing to do  } 

  void run()  {} //nothing to do

  };/*RDStateOff*/

  //----------------------------------------------------------------------------

  class RDStateTurningOn : public RDStateBase
  {
  public:

  RDStateTurningOn(RDStateManager & manager): the_manager(manager) {}
  
    void power_on() {} //not applicable
  
    void power_off() { the_manager.set_state_turningoff(); }

    void cut_milbus() {} //not applicable
  
    double calculate_energy_consumption() { return 0.0; }

    void init()
    {
      //!\todo 1) command the (SES) outputs to turn on the device
      the_manager.ses_output_on();
    
      //!\todo 2) init turning-on timer or whatever necessary actions
    } 

    void run()
    {
      //!\todo Execute the actual run-actions: i.e. udpate turning-on
      //       timer, or whatever necessary actions

      //until actual actions, just turn-on immediately
      the_manager.set_state_on();
    } 

  };/*StateTurningOn*/

  //----------------------------------------------------------------------------

  class RDStateOn : public RDStateBase
  {
  public:

  RDStateOn(RDStateManager & manager): the_manager(manager) {}
  
    void power_on() {} //not applicable
  
    void power_off() { the_manager.set_state_turningoff(); }

    void cut_milbus()
    {
      //!\todo execute cut-milbus actions
    }
  
    double calculate_energy_consumption()
    { return the_manager.the_device.calculate_energy_consumption(); }

  
    void init()   {} //!\todo init actions executed in the active state

    void run()  {}   //!\todo main actions executed in the active state

  };/*RDStateOn*/

  //----------------------------------------------------------------------------

  class RDStateTurningOff : public RDStateBase
  {
  public:

  RDStateTurningOff(RDStateManager & manager): the_manager(manager) {}
  
    void power_on() { the_manager.set_state_turningoff(); }
  
    void power_off() {} //not applicable

    void cut_milbus() {} //not applicable
  
    double calculate_energy_consumption()
    { return the_manager.the_device.calculate_energy_consumption(); }


    void init()
    {
      //!\todo 1) command the (SES) outputs to turn off the device
      the_manager.ses_output_off();
    
      //!\todo 2) init turning-off timer or whatever necessary actions
    } 

    void run()
    {
      //!\todo Execute the actual run-actions: i.e. udpate turning-off
      //       timer, or whatever necessary actions

      //until actual actions, just turn-off immediately
      the_manager.set_state_off();
    } 

  };/*StateTurningOff*/


  //----------------------------------------------------------------------------

} /*namespace avionic_control*/


#endif
