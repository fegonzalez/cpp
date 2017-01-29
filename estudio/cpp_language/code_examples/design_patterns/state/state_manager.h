#ifndef _STATE_MANAGER_H
#define _STATE_MANAGER_H

/*
  Four states: Off, TurningOn, ON, eTurningOff.

*/


namespace avionic_control
{

  //----------------------------------------------------------------------------

  class RDStateManager
  {

  public:

  RDStateManager(RealDevice & device):the_device(device)
  {
    set_state_off();
  }
      
    void power_on()  { current()->power_on(); }
    void power_off() { current()->power_off(); }
    void cut_milbus() { current()->cut_milbus() }
    double calculate_energy_consumption()
    { current()->calculate_energy_consumption() }

    void set_state_off() { the_current_state = &the_off; }
    void set_state_on() { the_current_state = &the_on; }
    void set_state_turnungoff() { the_current_state = &the_toff; }
    void set_state_turningon() { the_current_state = &the_ton; }

    
  private:
    RealDevice &the_device;
    RDStateOff the_off;
    RDStateTurningOn the_ton;
    RDStateOn the_on;
    RDStateTurningOff the_toff;

    RDStateBase * the_current_state;

    RDStateBase * current() { return the_current_state; }
  };
  
  //----------------------------------------------------------------------------

} /*namespace avionic_control*/


#endif
