#ifndef OTHER_SOURCE_H
#define OTHER_SOURCE_H


/* \test c) Static data members

   data_member `classone::one_per_program_static_data_member "int
   one_per_program_non_static_global_var' defined twice in the
   program: main.cpp, other_source.cpp

   expected: compilation error multiple definitions of
   `classone::one_per_program_static_data_member'

   obtained: the expected 
*/

class classone
{
public:
  static int one_per_program_static_data_member;
};


#endif
