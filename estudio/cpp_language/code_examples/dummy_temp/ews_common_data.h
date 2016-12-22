#ifndef _EWS_COMMON_DATA_H
#define _EWS_COMMON_DATA_H


/*!\file ews_common_data.h

  \brief Common data structs used by the EWS module.

  \param ews::CGFEmissionData CGF-emitters information. TBD.

  \param ews::TTypeEWSControl Ownship's config. info from the MTC devices.

*/


namespace ews {



/******************************************************************************/
  /*!\struct TypeIRSConfig wxr_common_data.h

    \brief Datos de los emisores del CGF; CONTENIDO POR DEFINIR;
    Fuente: CGF; unit: N/A

  */
/******************************************************************************/

  struct TypeCGFEmissionData
  {
    unsigned int dummy_data;
  };


/******************************************************************************/
  /*!\enum TypeCFDMode {OFF, MAN, AUTO, SEMI}

    \brief Modos del CFD; Rango: {OFF, MAN, AUTO, SEMI}; units: N/A
  */
/******************************************************************************/

  enum TypeCFDMode {OFF, MAN, AUTO, SEMI};
 

/******************************************************************************/
  /*!\enum TypeDispenserSelection {NORM, LH, RH};

    \brief Modos de dispensación; Rango: {NORM, LH, RH}; units: N/A
   */
/******************************************************************************/

  enum TypeDispenserSelection {NORM, LH, RH};
    
  
} //end of namespace ews

#endif
