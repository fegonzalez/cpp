#ifndef _WXR__COMMON_DATA_H
#define _WXR__COMMON_DATA_H


/*!\file wxr_common_data.h

\brief Common data structs used by the WXR radar module.

\param wxr_radar::TypeIRSConfig Ownship's IRS position.

\param wxr_radar::TTypeWXRControl Ownship's config. info from the MTC devices.

*/


namespace wxr_radar {



/******************************************************************************/
  /*!\typedef struct TypeProvisionalForCompilation_L350_00_WXR_BITE_MTN

    \struct L350_00_WXR_BITE_MTN wxr_common_data.h

    \warning typedef used for test compilation until the actual type is
    available in a complete simulator.

    \todo Use the actual Arinc L350_00_WXR_BITE_MTN type when available.

  */
/******************************************************************************/

  typedef struct TypeProvisionalForCompilation_L350_00_WXR_BITE_MTN
  {
    unsigned int dummy_var;
  
  } L350_00_WXR_BITE_MTN;



/******************************************************************************/
  /*!\struct TypeIRSConfig wxr_common_data.h

    \brief Información de la posición del helicóptero recibida desde los
    equipos IRS.
  */
/******************************************************************************/

  struct TypeIRSConfig
  {
    /*!\param altitude
      \brief ownship altitude
      units:   [m]
      default: 0.0
      range:   >= 0.0
      src: N/A ( TBD  Airbus's flis_flightloop.Fgalti ?
    */
    double altitude;

  
    /*!\param ground_speed
      \brief ownship's horizontal speed relative to the ground
      units:   [m/s]
      default: 0.0
      range:   >= 0.0
      src: N/A ( TBD  Airbus's  ?
    */
    double ground_speed;

  
    /*!\param heading
      \brief ownship's magnetic heading
      units:   [rad]
      default: 0.0
      range:   [-PI, PI]
      src: N/A ( TBD  Airbus's FMagnHdg ?
    */
    double heading;

  
    /*!\param phi_attitude
      \brief ownship's roll angle
      units:   [rad]
      default: 0.0
      range:   [-PI, PI]
      src: N/A ( TBD  Airbus's ?
    */
    double phi_attitude;

  
    /*!\param theta_attitude
      \brief ownship's pitch angle
      units:   [rad]
      default: 0.0
      range:   [-PI/2, PI/2]
      src: N/A ( TBD  Airbus's ?
    */
    double theta_attitude;

  
    /*!\param psi_attitude
      \brief ownship's yaw angle
      units:   [rad]
      default: 0.0
      range:   [-PI, PI]
      src: N/A ( TBD  Airbus's ?
    */
    double psi_attitude;
  };


/******************************************************************************/
  /*!\struct TypeWXRControl wxr_common_data.h 

    \brief Información de configuración del radar WXR del helicóptero
    recibida desde los equipos MTC

    \warning typedef used for test compilation until the actual type is
    available in a complete simulator.

    \doc arinc_irs_nh1_2968_WXR
  */
/******************************************************************************/


  typedef struct TypeProvisionalForCompilation_L270_01_WXR_CONTROL_1
  { unsigned int dummy_var; } L270_01_WXR_CONTROL_1;
  typedef struct TypeProvisionalForCompilation_L270_10_WXR_CONTROL_1
  { unsigned int dummy_var; } L270_10_WXR_CONTROL_1;
  typedef struct TypeProvisionalForCompilation_L271_01_WXR_CONTROL_2
  { unsigned int dummy_var; } L271_01_WXR_CONTROL_2;
  typedef struct TypeProvisionalForCompilation_L271_10_WXR_CONTROL_2
  { unsigned int dummy_var; } L271_10_WXR_CONTROL_2;
  typedef struct TypeProvisionalForCompilation_L272_01_WXR_CONTROL_3
  { unsigned int dummy_var; } L272_01_WXR_CONTROL_3;
  typedef struct TypeProvisionalForCompilation_L272_10_WXR_CONTROL_3
  { unsigned int dummy_var; } L272_10_WXR_CONTROL_3;


  struct TypeWXRControl
  {
    /*!\param the_wxr_control_1_a
      \brief radar config param 1 of 6 (as defined in "arinc_irs_nh1_2968_WXR")
      units:   N/A
      default: N/A
      range:   N/A
      src:     N/A (Arinc msg. from the MTC device)

      \info The description of the rest of the parameters are equivalent.
    */
    L270_01_WXR_CONTROL_1 the_wxr_control_1_a;
    L270_10_WXR_CONTROL_1 the_wxr_control_1_b;
    L271_01_WXR_CONTROL_2	the_wxr_control_2_a; 
    L271_10_WXR_CONTROL_2	the_wxr_control_2_b;
    L272_01_WXR_CONTROL_3	the_wxr_control_3_a;
    L272_10_WXR_CONTROL_3	the_wxr_control_3_b;
  };


} //end of namespace wxr_radar

#endif
