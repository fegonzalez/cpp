
/*!\test [K???] Using bit fields and pragma pack


  Ref. docs. :

  [1] c-howto, 6.9 Bit-fields

  [2] c++-howto

  [3]  GeeksforGeeks - Bit Fields in C - https://www.geeksforgeeks.org/bit-fields-c/


----

1. The C++ memory model:

FACT Byte size = IMPLEMENTATION-DEFINED   [2].1.7.1)

FACT mem address != mem location: a mem. location occupies one or more
        mem. addr.  [2].1.7.3)

FACT Word size is a characteristic given to computer architecture. It
        denotes the number of bits that a CPU can process at one time
        (eg. 32, 64)  [2].Y.1)


2. Bit-fields

WARNING Almost everything about fields is implementation-dependent. [1]


HINT Use: one-bit flags (bit masks) corresponding to the relevant bit positions,
    [ Example - 
	
        struct 
	{
	    unsigned int is_keyword : 1;
	    unsigned int is_extern : 1;
	    unsigned int is_static : 1;
	} flags;
    end-example ]



Conclusions after the test result:

C1 - memory storage of a bit-field struct (without pragma pack): 

      The minimum bytes required by the bit-fields (a), but following
      the word-size of the architecture (b):

    [ Example 
        
        struct TypeBitFieldMsg
	{
            char        the_char    :1;    // (a) 1 byte required (signed => 2's complement)
            uint8_t     the_byte    :4;    // (a) 1 byte required
            unsigned int         the_int     :9;    // (a) 2 bytes required
	};

	(a) At least 4 bytes required
	(b) word size = 64 bits = 8 bytes =  4 or 8 bytes words => 4 bytes used


C2 - memory storage of a regular struct:, without pragma pack:  

      The sizeof of each data type, but following the word-size of the
      architecture (b):

    [ Example 
        
        struct TypeRegularMsg
	{
            char        the_char;    // (a) 1 byte required
            uint8_t     the_byte;    // (a) 1 byte required
            unsigned int         the_int;    // (a) 4 bytes required
	};

	(a) At least 6 bytes required

	(b) word size = 64 bits = 8 bytes = 4 or 8 bytes words: 	     
	     required: 6 bytes
	     minimum word size required: 8 bytes (6 of data + 2 bytes of padding)


C3: value stored of the bit-field types

(1)  Value included in the range of values supported by the bit-field length
      [ Example - unsigned int the_int :9;  range [0, 2e9=512] -- end example ]
      [ Example - unsigned int the_int :17;  range [0, 2e17= 131072] -- end example ]

(2) In unsigned types, If the value of the fields goes beyond the
    bits allocated, the exceeded bits are ignored.
      [ Example - unsigned int the_int :9; the_int = 4099 => actual value stored is 3;
      -- end example ]

(3) In signed types, If the value of the fields goes beyond the bits
    allocated, and the MSB bit is a '1', then it is considered a
    negative number, and 2ś complement is executed to get the actual
    value; (eg int the_int :5 = 31 (b 11111) => actual value = -1).

*/



#include <iostream>



/*******************************************************************************
 PROBLEM code
*******************************************************************************/

struct TypeBitFieldMsg
{
  char          the_char     :1;
  uint8_t      the_byte     :4;
  unsigned int   the_int        :9;
  
  // minimum bytes required = 1+4+12 bits = 3 bytes
  // minimum word size required = 4 bytes (3 bytes of data + 1 bytes of padding)
  // sizeof (64bits architecture) =  = 4 bytes

};


struct TypeBitFieldMsg2
{
  char          the_char     :1;
  uint8_t      the_byte     :4;
  
  unsigned int             the_int        :28;

  // minimum bytes required = 1+4+28 = 5 bytes
  // minimum word size required = 8 bytes (5 bytes of data + 3 bytes of padding)
  // sizeof (64bits architecture) = 8 bytes

};


struct TypeBitFieldMsg3
{
  char          the_char     :1;
  uint8_t      the_byte     :4;

  unsigned int             the_int        :32; // 5 bytes

  // 5 bytes required
  // sizeof (64bits architecture) = 8 bytes

};
struct TypeBitFieldMsg4
{
  char          the_char     :1;
  uint8_t      the_byte     :4; // 1 byte of data

  ///@warning here goes up to 12 bytes because two 'int' are required
  // to store a variable greater than 32 bits: int1 (4bytes of data)
  // and int2 (1 data + 3 padding) note.- same result for one "int:33"
  // or several "int:x" where the sum of x be 33.
  //
  unsigned int             the_int        :33;  // first 'int': 4 bytes of data;
                                                // second 'int': 1 bytes of data + 3 bytes padding

  
  // 9 bytes required
  // sizeof (64bits architecture) = 12 bytes

};



struct TypeRegularMsg
{
  char          the_char;
  uint8_t      the_byte;
  unsigned int             the_int;
  
  // minimum bytes required = 1+1+4 bytes = 6 bytes
  // minimum word size required = 8 bytes (6 bytes of data + 2 bytes of padding)
  // sizeof (64bits architecture) = 8 bytes

};



void set_datos(TypeBitFieldMsg & datos)
{
  datos.the_char=0b01000001;   /// (65 => 1):  64 + 1 
  datos.the_byte=0b00110111;   /// (55  => 7): 48  + 7 (4 lsb bits)
  datos.the_int = 4099; //  (4096 => 3): 4096 (bit 15-12) + 3 (bit 11-0)
}


void set_datos(TypeRegularMsg & datos)
{
  datos.the_char=0b01000001; // 65
  datos.the_byte=0b00110111; // 55
  datos.the_int = 4099; // 4099
}


void print_datos(const TypeBitFieldMsg & datos)
{
  std::cout << "\nsizeof(TypeBitFieldMsg) = " << sizeof(datos);

  ///make  error: invalid application of ‘sizeof’ to a bit-field
  // std::cout << "\nsizeof(datos.the_char) = " << sizeof(datos.the_char);
  // std::cout << "\nsizeof(datos.the_byte) = " << sizeof(datos.the_byte);
  // std::cout << "\nsizeof(datos.the_int) = " << sizeof(datos.the_int);
  
  std::cout << "\n";
  std::cout << "{";
  std::cout << static_cast<int>(datos.the_char)  << "; ";
  std::cout << static_cast<int>(datos.the_byte)  << "; ";
  std::cout << datos.the_int;
  std::cout << "}";
}


void print_datos(const TypeRegularMsg & datos)
{
  std::cout << "\nsizeof(TypeRegularMsg)  = " << sizeof(datos);

  std::cout << "\nsizeof(datos.the_char) = " << sizeof(datos.the_char);
  std::cout << "\nsizeof(datos.the_byte) = " << sizeof(datos.the_byte);
  std::cout << "\nsizeof(datos.the_int) = " << sizeof(datos.the_int);

  std::cout << "\n";
  std::cout << "{";
  std::cout << static_cast<int>(datos.the_char)  << "; ";
  std::cout << static_cast<int>(datos.the_byte)  << "; ";
  std::cout << datos.the_int;
  std::cout << "}";
}


void print_datos(const char &print_char,
		 const uint8_t &print_byte,
		 const int &print_int)
{
  std::cout << "\n";
  std::cout << "{";
  std::cout << static_cast<int>(print_char) << "; ";
  std::cout << static_cast<int>(print_byte)  << "; ";
  std::cout << print_int;
  std::cout << "}";
}

/******************************************************************************/

/**@struct TypeMemLocation

   4 memory locations 

   sizeof(TypeMemLocation) (expected= 7) = 12
   
  */
struct TypeMemLocation 
{
  char a;    // field      => memory location 1
  int b:5,   // bit-field  => memory location 2
      c:11,  // bit-field
      :0,    //  zero-length bit-field declaration
      d:8;   // bit-field  => memory location 3
  struct {int ee:8;} e; // nested bit-field declaration   => memory location 4
};


void write_TypeMemLocation (const TypeMemLocation  & datos)
{
  std::cout << "\nsizeof(TypeMemLocation) (expected=7) = " << sizeof(TypeMemLocation);
  std::cout << "\nsizeof(TypeMemLocation.a) (1?) = " << sizeof(datos.a);
  // std::cout << "\nsizeof(TypeMemLocation.b) (1?) = " << sizeof(datos.b);
  // std::cout << "\nsizeof(TypeMemLocation.c) (1?) = " << sizeof(datos.c);
  // std::cout << "\nsizeof(TypeMemLocation.d) (1?) = " << sizeof(datos.d);
  std::cout << "\nsizeof(TypeMemLocation.e) (1?) = " << sizeof(datos.e);

  
  // std::cout << "\n";
  // std::cout << "{";
  // std::cout << static_cast<int>(datos.the_char)  << "; ";
  // std::cout << static_cast<int>(datos.the_byte)  << "; ";
  // std::cout << datos.the_int;
  // std::cout << "}";
}


/******************************************************************************/


int main()
{
  std::cout << "\nTest Using bit fields and pragma pack. " << std::endl;

  std::cout << "\nsizeof(char) (¿1?) = " << sizeof(char);
  std::cout << "\nsizeof(byte) (¿1?) = " << sizeof(uint8_t);
  // std::cout << "\nsizeof(short) (¿2?) = " << sizeof(short);
  std::cout << "\nsizeof(int) (¿2?) = " << sizeof(int);
  // std::cout << "\nsizeof(long) (¿2?) = " << sizeof(long);
  // std::cout << "\nsizeof(float) (¿2?) = " << sizeof(float);
  // std::cout << "\nsizeof(double) (¿2?) = " << sizeof(double);
  // std::cout << "\nsizeof(long double) (¿2?) = " << sizeof(long double);
  std::cout << "\nsizeof(TypeBitFieldMsg)  = " << sizeof(TypeBitFieldMsg);
  std::cout << "\nsizeof(TypeBitFieldMsg2)  = " << sizeof(TypeBitFieldMsg2);
  std::cout << "\nsizeof(TypeBitFieldMsg3)  = " << sizeof(TypeBitFieldMsg3);
  std::cout << "\nsizeof(TypeRegularMsg)  = " << sizeof(TypeRegularMsg);

  std::cout << "\n\n///@warning aki cambia a 12 bytes:";
  std::cout << "\nsizeof(TypeBitFieldMsg4)  = " << sizeof(TypeBitFieldMsg4);
  


  TypeBitFieldMsg msg_bitfield;
  set_datos(msg_bitfield);
  std::cout << "\n\nmsg_bitfield: ";
  print_datos(msg_bitfield);
      
  TypeRegularMsg msg_regular;
  set_datos(msg_regular);
  std::cout << "\n\nmsg_regular: ";
  print_datos(msg_regular);

  std::cout << "\n\nCopiar no pack (msg_bitfield) a variables";
  char local_char = msg_bitfield.the_char;
  uint8_t local_byte = msg_bitfield.the_byte;
  int local_int = msg_bitfield.the_int;
  std::cout << "\nsizeof(local_char) (¿1?) = " << sizeof(local_char);
  std::cout << "\nsizeof(local_byte) (¿1?) = " << sizeof(local_byte);
  std::cout << "\nsizeof(local_int) (¿2?) = " << sizeof(local_int);
  std::cout << "\n msg_bitfield como vars: ";
  print_datos(local_char, local_byte, local_int);
  

  // std::cout << "\nsizeof(TypeMemLocation) (expected= 7) = " << sizeof(TypeMemLocation);
  // TypeMemLocation mem_location_data;
  // write_TypeMemLocation(mem_location_data);
    
  
    
  std::cout << std::endl;
  return 0;
}


