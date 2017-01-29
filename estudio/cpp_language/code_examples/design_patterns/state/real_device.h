#ifndef _REAL_DEVICE_H
#define _REAL_DEVICE_H



namespace avionic_control
{

  // 2 opciones:
  // a) individualmente en cada clase (DKU1)
  // b) en la base (RealDevice)
  //----------------------------------------------------------------------------

  // a) individualmente en cada clase (DKU1)
  class DKU1 : public RealDevice
  {
    DKU1():the_state_manager(*this)
    {
      the_state_manager.set_state_off();
    }
    
    void power_on()
    {
      the_state_manager.power_on();
    }
    
  private:

    RDStateManager the_state_manager;
        
  };
  
  //----------------------------------------------------------------------------

  // b) en la base (RealDevice)
  class RealDevice
  {
  RealDevice():the_state_manager(*this)
      { the_state_manager.set_state_off(); }

    init() { the_state_manager.set_state_off(); }

    void power_on()
    {
      the_state_manager.power_on();
    }
    
  protected:

    RDStateManager the_state_manager;
        
  };
  
  //----------------------------------------------------------------------------

} /*namespace avionic_control*/


#endif
