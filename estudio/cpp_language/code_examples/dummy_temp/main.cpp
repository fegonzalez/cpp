#include "data.h"

#include "wxr_common_data.h"
#include "ews_common_data.h"

#include <iostream>


//------------------------------------------------------------------------------

void using_wxr()
{
  std::cout << "\n\nusing_wxr()" << std::endl;

    wxr_radar::L350_00_WXR_BITE_MTN tipo1;
  tipo1.dummy_var=1;
  
  std::cout << tipo1.dummy_var << std::endl;


  wxr_radar::TypeWXRControl tipo2;

  tipo2.the_wxr_control_2_b.dummy_var = 77;
  std::cout << tipo2.the_wxr_control_2_b.dummy_var << std::endl;
}

//------------------------------------------------------------------------------

void using_ews()
{
  std::cout << "\n\nusing_ews()" << std::endl;

  ews::TypeCGFEmissionData tipo1;
  tipo1.dummy_data=100;
  std::cout << tipo1.dummy_data << std::endl;

  ews::TypeCFDMode tipo2 = ews::SEMI;
  std::cout << tipo2 << std::endl;

  ews::TypeDispenserSelection tipo3 = ews::NORM;
  std::cout << tipo3 << std::endl;
}

//------------------------------------------------------------------------------

int main()
{
  Aspectocielo micolor = ROJO;
  if (micolor == ROJO)
    std::cout << "\n Rojo.";
  else
    std::cout << "\n nooooo Rojo.";
  std::cout << std::endl;


  micolor = VERDE;
if (micolor == ROJO)
    std::cout << "\n Rojo.";
  else
    std::cout << "\n nooooo cielo Rojo.";
  std::cout << std::endl;


  using_wxr();

  using_ews();
  
  return 0;
}
