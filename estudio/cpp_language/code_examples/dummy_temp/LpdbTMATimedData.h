/*
 * LpdbTMATimedData.h
 *
 */

#ifndef LPDBTMATIMEDDATA_H_
#define LPDBTMATIMEDDATA_H_

#include <iosfwd>


class LpdbTMATimedData
{
 public:
  LpdbTMATimedData() = default;
  LpdbTMATimedData(const LpdbTMATimedData& source) = default;
  LpdbTMATimedData & operator =(const LpdbTMATimedData& source) = default;
  virtual ~LpdbTMATimedData() {}

  inline unsigned int getCapacity() const;
  //  void setCapacity(unsigned int capacity);
  inline void calculateCapacity(unsigned int numberOfIntervals,
				unsigned int nominalCapacity);

 protected:

  ///@param r_capacity: capacity per interval = nominal capacity / num intervals
  unsigned int r_capacity = 0;  ///@warning  -1 in RMAN == NULL ?


  ///@warning RMAN's used manual capacity reductions, RTP doesn't
  //       LpiADOVector<double> r_manual_capacity_reduction; // not in RTP
  //       bool r_hasManualReduction;

};

std::ostream & operator<<(std::ostream & os, const LpdbTMATimedData & info);

#endif /* LPDBTMATIMEDDATA_H_ */
