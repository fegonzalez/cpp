/*DOC  http://www.cplusplus.com/reference/streambuf/streambuf/

// sync: synchronize stream buffer, thus write the buffer content into
//       the file.

  "std::streambuf::pubsync" : "public" sync

  Calls the protected virtual member sync.

  Member sync does nothing in streambuf, but derived classes shall
  synchronize the contents pointed by the internal pointers with their
  associated sequences, if different (this effectively writes any
  unwritten characters on output buffers).


      [ Example 

        std::streambuf * pbuf = ostr.rdbuf();

	pbuf->sputn (sentence,sizeof(sentence)-1);  // buffer not flushed yet

	pbuf->pubsync(); // Now: buffer flushed to the file: 

	// ver ejemplo completo abajo: sputn_example()
     ]


// the stream is automatically closed when the scope ends, so
// fs.close() is optional

// the stream is automatically flushed when it is closed, so
// fs.flush() is optional



/*DOC   https://stackoverflow.com/questions/8116541/what-exactly-is-streambuf-how-do-i-use-it

+ streambuf is for raw data (e.g. raw bytes, raw ints, etc.),

+ whereas stream is for cooked data (text, integers formatted as text,
  etc.). Put another way, stream represents the parsing (or
  serialization) layer.

+ When dealing with plain strings, you can technically use either, but
  the meaning is different: streambuf means you want the raw data to
  be the string itself, whereas stream abstracts away the encoding.

*/

/*
  // the stream is automatically closed when the scope ends, so
  // fs.close() is optional

  // the stream is automatically flushed when it is closed, so
  // fs.flush() is optional
*/

#include <iostream>
#include <fstream>      // std::ofstream

#include <cassert>



class LrgConfig
{
public:
   static const char         outFileName[];
   static const char         outFileNameOld[];
}; // LrgConfig


const char LrgConfig::outFileName[] = "RMAN.LOG";
const char LrgConfig::outFileNameOld[] = "RMAN.LOG_OLD";

//-----------------------------------

class  LrgStreamBuf : public std::streambuf
{
public:

  LrgStreamBuf(): std::streambuf(),
		  the_sync_times(0)
  {
    std::clog << "\n in...  " << __FILE__ << ":  " << __func__ << " : " << __LINE__ << std::endl;


    //Base class pointers (std::streambuf::setp)
    setp(r_buffer, r_buffer+c_bufferSize);


    // std::clog << "\n in...  " << __FILE__ << ":  " << __func__ << " : " << __LINE__ << std::endl;


    //Rename RMAN.LOG to RMAN.LOG_OLD, and open for writing
    checkOutFileInit();
    // std::clog << "\n in...  " << __FILE__ << ":  " << __func__ << " : " << __LINE__ << std::endl;


  }

  virtual ~LrgStreamBuf()
  {
    std::clog << "\n in...  " << __FILE__ << ":  " << __func__ << " : " << __LINE__ << std::endl;

    close_buffer();
  }

  //-----------------------------------

  void setType()
  {
    // std::clog << "\n in...  " << __FILE__ << ":  " << __func__ << " : " << __LINE__ << std::endl;


    sync();


    // std::clog << "\n in...  " << __FILE__ << ":  " << __func__ << " : " << __LINE__ << std::endl;

  }

  static const int get_buffer_size()  {return c_bufferSize;}


  //-----------------------------------


protected:
  

//-----------------------------------
// std::streambuf output methods to overwrite.
//
// sync
// xsputn
// overflow
//-----------------------------------

int sync(void)
{
	   // std::clog << "\n in...  (ENTRO)" << __FILE__ << ":  " << __func__ << " : " << __LINE__ << std::endl;


   if((pptr() - pbase()) > 0)
   {
     std::clog << "\n in...  (if... then...ESCRIBO)" << __FILE__ << ":  " << __func__ << " : " << __LINE__ << std::endl;

      print(pbase(), pptr() - pbase());
      pbump(pbase() - pptr());

     //  if(++the_sync_times > SYNC_TIMES_VALUE)
     //  {
     // std::clog << "\n (fffffffffffffFLUSH exec)" << __FILE__ << ":  " << __func__ << " : " << __LINE__ << std::endl;

     // 	r_slog.flush();
     // 	the_sync_times = 0;
     //  }
   }


   else
   {
     std::clog << "\n in...  (else ...NO ESCRIBO)" << __FILE__ << ":  " << __func__ << " : " << __LINE__ << std::endl;

   }


   // std::clog << "\n in... (SALGO) " << __FILE__ << ":  " << __func__ << " : " << __LINE__ << std::endl;

   return 0;
}


//-----------------------------------

// Se llama automáticamente desde "xsputn" cuando el texto es mayor
// que el tamaño del buffer
//
// Hay que hacer pbump para obligar a escribir el texto que no cabe.
// De otra forma, se ignora el texto sobrante.
int overflow(int c=EOF)
{
  std::clog << "\n oooooooooo; c:< " << static_cast<char>(c) << ">" 
	    << __FILE__ << ":  " << __func__ << " : " << __LINE__ 
	    << std::endl;

   *pptr() = c;
   pbump(1);
   sync();   //!\warning Required to update the buffer after pbump
             //          Otherwise runtime error: "free(): invalid size ..."

   // r_isOverflowed = true;
   return c;
}

//-----------------------------------

// Se llama automaticamente al volcar datos (operator<<)  al std::streambuf
// e.g. local_rlog.info() << "Msg " << std::endl;
std::streamsize xsputn(const char_type *buffer, std::streamsize n)
{
  assert(buffer);
  std::clog << "\n XXXXX buffer<" << buffer << ">   "
	    << "\n streamsize: " << n << "  ;  "
	    << __FILE__ << ":  " << __func__ << " : " 
	    << __LINE__ << std::endl;

   for(int i=0; i<n; ++i)
   {
      sputc(buffer[i]);
      if(buffer[i] == '\n')
      {
         for(int j=0; j<1; ++j)
         {
            sputc(' ');
         }
      }
   }
   return n;
}


//-----------------------------------

 private:

static std::ofstream       r_slog;

   //Buffer
static const int           c_bufferSize = 2; //64
char                       r_buffer[c_bufferSize];


size_t the_sync_times; // frequency to sync (write buffer to file)

static const size_t SYNC_TIMES_VALUE = 10;


   //Internal methods
  
//-----------------------------------

  static void checkOutFileInit()
  {
    std::clog << "\n in...  " << __FILE__ << ":  " << __func__ << " : " << __LINE__ << std::endl;

    std::rename(LrgConfig::outFileName,
		LrgConfig::outFileNameOld);
    // std::clog << "\n in...  " << __FILE__ << ":  " << __func__ << " : " << __LINE__ << std::endl;


    r_slog.open(LrgConfig::outFileName, std::ios::out); // AKI DA EL core


    // std::clog << "\n in...  " << __FILE__ << ":  " << __func__ << " : " << __LINE__ << std::endl;

  }

//-----------------------------------
//-----------------------------------


  static void close_buffer()
  {
    std::clog << "\n in...  " << __FILE__ << ":  " << __func__ << " : " << __LINE__ << std::endl;

    if (r_slog.is_open())
    {
      std::clog << "\n in... (CLOSING THE FILE)  " << __FILE__ << ":  " << __func__ << " : " << __LINE__ << std::endl;
      r_slog.close();
    }
    else
    {
    std::clog << "\n in...  " << __FILE__ << ":  " << __func__ << " : " << __LINE__ << std::endl;
    }
    

  }


//-----------------------------------

void print(const char *buffer, int num)
  {
    assert(buffer);
    std::clog << "\n PpPpPpPp buffer< " 
	      << buffer
	      << ">"
	      << __FILE__ << ":  " << __func__ << " : " << __LINE__ 
	      << std::endl;


    r_slog.write(buffer, num);
    
    //    r_slog.flush();
  }

//-----------------------------------

};//LrgStreamBuf


std::ofstream LrgStreamBuf::r_slog;



//-----------------------------------
// Envoltorio del buffer
//-----------------------------------


class LrgStream : public std::ostream
{
public:

  LrgStream(): std::ostream(new LrgStreamBuf())
  {
    std::clog << "\n in...  " << __FILE__ << ":  " << __func__ << " : " << __LINE__ << std::endl;


    // std::clog << "\n in...  " << __FILE__ << ":  " << __func__ << " : " << __LINE__ << std::endl;

  }


  ~LrgStream()
  {
    std::clog << "\n in...  " << __FILE__ << ":  " << __func__ << " : " << __LINE__ << std::endl;

    delete this->rdbuf();

 std::clog << "\n in...  " << __FILE__ << ":  " << __func__ << " : " << __LINE__ << std::endl;

  }

  LrgStream & info(void)      {return setLevel();}


  //-------------------
  /*
  //write buffer to file now!
  void sync()
  {
   std::clog << "\n SYNNCCCC  " << __FILE__ << ":  " << __func__ << " : " << __LINE__ << std::endl;

   // The first form (1) returns a pointer to the stream buffer object currently associated with the stream.

   assert(this->rdbuf());
   LrgStreamBuf * aux_buf = dynamic_cast<LrgStreamBuf *>(this->rdbuf());
   assert(aux_buf);
   aux_buf->pubsync();
   aux_buf=0;

    // if(this->rdbuf() and this->rdbuf()->pubsync())
    // {
    //   this->rdbuf()->pubsync();
    // }
    // else
    // {
    //   std::cerr << "\n\nERROR: null_ptr."
    // 		<< "File: "<< __FILE__
    // 		<< " ; Func:  " << __func__
    // 		<< " ; Line: " << __LINE__
    // 		<< std::endl;
    // }

  }
*/
  //-------------------

  // escribir stream (operator<<) al buffer
LrgStream & setLevel()
{
   std::clog << "\n in...  " << __FILE__ << ":  " << __func__ << " : " << __LINE__ << std::endl;


   //   dynamic_cast<LrgStreamBuf *>(this->rdbuf())->setType();
    LrgStreamBuf * aux_buf = dynamic_cast<LrgStreamBuf *>(this->rdbuf());
    assert(aux_buf);
    aux_buf->setType();
    aux_buf=0;

     
   // std::clog << "\n in...  " << __FILE__ << ":  " << __func__ << " : " << __LINE__ << std::endl;

   return *this;
}

  //-------------------


}; //LrgStream


//----------------------------------------------------------------------------

void normal_log()
{

std::ofstream normal_slog;
normal_slog.open("normal_slog", std::ios::out);

 if (normal_slog.fail())
 {
   std::cerr << "normal_slog.fail():  LrgStreamBuf::checkOutFileInit() " 
	     << "normal_slog.open  normal_slog.fail() "
	     << std::endl << std::flush;
   return;
 }
 else
 {
  std::clog << "\n normal_slog.open  SUCCESS. " 
	    << __FILE__ << ":  " << __func__ << " : " << __LINE__ 
	    << std::endl;

  std::clog << "\n Inner buffer (std::ofstream::filebuf) size = "
	    << normal_slog.rdbuf()->in_avail() << " ; "
	    << __FILE__ << ":  " << __func__ << " : " << __LINE__ 
	    << std::endl;
  

   //    std::string buffer = "m1";
   // std::streamsize num = sizeof(buffer.c_str());
   // normal_slog.write(buffer.c_str(), num);
   normal_slog.write("m1\n", sizeof("m1"));
   std::clog << "\n Inner buffer (std::ofstream::filebuf) size = "
	     << normal_slog.rdbuf()->in_avail() << " ; "
	     << __FILE__ << ":  " << __func__ << " : " << __LINE__ 
	     << std::endl;  
   std::cout << "\n (1) Esperando hasta pulsar ENTER ... " << std::flush;  
   std::cin.ignore();

   std::clog << "\n Inner buffer (std::ofstream::filebuf) size = "
	     << normal_slog.rdbuf()->in_avail() << " ; "
	     << __FILE__ << ":  " << __func__ << " : " << __LINE__ 
	     << std::endl;  

   normal_slog.close();
 }


}

//----------------------------------------------------------------------------

void static_local_Buffer()
{
  std::clog << "\n in...  " << __FILE__ << ":  " << __func__ << " : " << __LINE__ << std::endl;


  
  LrgStream local_rlog; //aki no es global

  //  LrgStreamBuf

  int msg_id =222;
  std::cout << "\nIntro msg id: " << std::flush;
  //std::cin >> msg_id;


  local_rlog.info() << "Msg " << msg_id << std::endl;
  std::cout << "\n (1) Esperando hasta pulsar ENTER ... " << std::flush;  
  std::cin.ignore();

  local_rlog.info() << "123456789abcdefg"<< std::endl;
  std::cout << "\n (2) Esperando hasta pulsar ENTER ... " << std::flush;  
  std::cin.ignore();



  // local_rlog.sync();
  // std::cout << "\n (3!!!) SYNC ejecutado (file == buffer). Press ENTER ... " << std::flush;  
  // std::cin.ignore();



  local_rlog.info() << ".-_xyz"<< std::endl;
  std::cout << "\n (4) Esperando hasta pulsar ENTER ... " << std::flush;  
  std::cin.ignore();

  /*  AKI ya se escribieron datos en fichero:

>>cat RMAN.LOG
Msg 222
123456789abcdefg
.-_xyz>

   */




  std::cout << "\n\n THE END " << std::flush;  
  local_rlog.info() <<  "\n\n THE END. "<< std::endl;

  return;

  /*
  std::clog << "\n in...  " << __FILE__ << ":  " << __func__ << " : " << __LINE__ << std::endl;

  //local_rlog.~LrgStream();

  std::clog << "\n in...  " << __FILE__ << ":  " << __func__ << " : " << __LINE__ << std::endl;

  std::cout << "\n (1) Esperando hasta pulsar ENTER ... " << std::flush;  
  std::cin.ignore();

    local_rlog.info() << "\n (LrgStreamBuf::get_buffer_size()/3) = " << (LrgStreamBuf::get_buffer_size()/3) << " - in...  " << __FILE__ << ":  " << __func__ << " : " << __LINE__ << std::endl;
  for (size_t loopi = 0; 
       loopi < (LrgStreamBuf::get_buffer_size()/3); 
       ++loopi)
  {
    local_rlog.info() << "\n First 3rd: loopi = " << loopi << " - in...  " << __FILE__ << ":  " << __func__ << " : " << __LINE__ << std::endl;

    std::clog << "F3F3F3F3F3  First 3rd: loopi = " << loopi << " - in...  " << __FILE__ << ":  " << __func__ << " : " << __LINE__ << std::endl;
    
  }
  std::cout << "\n First 3rd done.  Esperando hasta pulsar ENTER ... " << std::flush;  
  std::cin.ignore();


    local_rlog.info() << "\n (LrgStreamBuf::get_buffer_size()/3) = " << (LrgStreamBuf::get_buffer_size()/3) << " - in...  " << __FILE__ << ":  " << __func__ << " : " << __LINE__ << std::endl;
  for (size_t loopi = 0; 
       loopi < (LrgStreamBuf::get_buffer_size()/3); 
       ++loopi)
  {
    local_rlog.info() << "\n Second 3rd: loopi = " << loopi << " - in...  " << __FILE__ << ":  " << __func__ << " : " << __LINE__ << std::endl;
  }
  std::cout << "\nSecond 3rd done. Esperando hasta pulsar ENTER ... " << std::flush;  
  std::cin.ignore();



    local_rlog.info() << "\n (LrgStreamBuf::get_buffer_size()/3) = " << (LrgStreamBuf::get_buffer_size()/3) << " - in...  " << __FILE__ << ":  " << __func__ << " : " << __LINE__ << std::endl;
  for (size_t loopi = 0; 
       loopi < (LrgStreamBuf::get_buffer_size()/3  + 10);
       ++loopi)
  {
    local_rlog.info() << "\n Third 3rd: loopi = " << loopi << " - in...  " << __FILE__ << ":  " << __func__ << " : " << __LINE__ << std::endl;
  }
  std::cout << "\n Compleado. Esperando hasta pulsar ENTER ... " << std::flush;  
  std::cin.ignore();


  std::cout << "\n\n THE END " << std::flush;  
  */
}



//----------------------------------------------------------------------------

// volcar al fichero el contenido del buffer => sincronizar buffer y fichero
int sputn_example() {
  const char sentence[]= "Sample sentence";
  const char s2_sentence[]= "2nd sentence";

  std::ofstream ostr ("test.txt");
  if (ostr) {
    std::streambuf * pbuf = ostr.rdbuf();
    pbuf->sputn (sentence,sizeof(sentence)-1);
  std::cout << "\n (1) Esperando hasta pulsar ENTER ... " << std::flush;  
  std::cin.ignore();

    pbuf->pubsync();
  std::cout << "\n (2) SYNC ejecutado (file == buffer). Press ENTER ... " << std::flush;  
  std::cin.ignore();

    pbuf->sputn (s2_sentence,sizeof(s2_sentence)-1);
  std::cout << "\n (3) NO sync => (buffer no volcado a file). Press ENTER ... " << std::flush;  
  std::cin.ignore();


    pbuf->pubsync();
  std::cout << "\n (2) SYNC ejecutado (file == buffer). Press ENTER ... " << std::flush;  
  std::cin.ignore();


    ostr.close();
  }

  return 0;
}

//----------------------------------------------------------------------------

int main()
{ 

  normal_log();
  std::clog << "\n in...  " << __FILE__ << ":  " << __func__ << " : " << __LINE__ << std::endl;
  return 0;



 //  sputn_example();
  //  return 0; 



  std::clog << "\n in...  " << __FILE__ << ":  " << __func__ << " : " << __LINE__ << std::endl;



  static_local_Buffer();

  std::clog << "\n in...  " << __FILE__ << ":  " << __func__ << " : " << __LINE__ << std::endl;


 return 0;
}
