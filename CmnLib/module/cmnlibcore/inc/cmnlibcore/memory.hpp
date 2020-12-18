/**

THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY 
APPLICABLE LAW. EXCEPT WHEN OTHERWISE STATED IN WRITING THE 
COPYRIGHT HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM 
ÅgAS ISÅh WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR 
IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM 
IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE 
COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.

*/

#ifndef CMNLIB_CMNLIBCORE_MEMORY_HPP__
#define CMNLIB_CMNLIBCORE_MEMORY_HPP__

#include "cmnlibcore/inc/cmnlibcore/libdefine.hpp"

#if _DEBUG
#ifdef USE_MEMORYMANAGER
#define CMNLIB
#define CL_MEMORY_MANAGER
#endif
#endif

#include <iostream>
#include <string>

#include "cmnlibcore_headers.hpp"

namespace CmnLib
{
namespace memory
{
  /****************************************************************************************\
  *                         Simple memory manager class                                    *
  \****************************************************************************************/

  /** Manage the basic memory allocation for the most common structures
  *	@author Dr. Moro Alessandro
  *	@brief Apply memory allocation for the vary basic structures
  *	@remarks
  *		It provides vector, matrix and 3D matrix allocation
  */
  template <typename T>
  class MemoryManager
  {
   public:
    /** Allocate the memory for a vector 
    *	@param data Pointer to the vecture structure. Must be a NULLPTR pointer
    *	@param lenght Memory to allocate
    */
//      static void AllocateVector(T* &data, int lenght, char* acFile = __FILE__, unsigned int uiLine = __LINE__)	{
      static void AllocateVector(T* &data, int lenght, const std::string& acFile = __FILE__, unsigned int uiLine = __LINE__)	{
        if (data == NULLPTR)
        {
          try
          {
#ifndef CMNLIB
			data = new T[lenght];
#else
#ifndef CL_MEMORY_MANAGER
            data = CL_NEW T[lenght];
#else
			const char* pchar = acFile.c_str();
            data = new(pchar, uiLine) T[lenght];
#endif
#endif
          }
          catch(std::bad_alloc xa)
          {
            //cout << "[e] Error memory allocation" << endl;
          }
        }
        //else
        //cout << "[e] Pointer already allocated" << endl;
      }

      /** Deallocate the memory for a vector
      *	@param data Pointer to the vecture structure.
      */
      static void DeallocateVector(T* &data)	{
        if (data != NULLPTR)
        {
          // Release memory
          delete[] data;
          data = NULLPTR;
        }
      }
      /** Allocate the memory for a matrix 
      *	@param data Pointer to the matrix structure. Must be a NULLPTR pointer
      *	@param height	Matrix height size
      *	@param width	Matrix width size
      */
      static void AllocateMatrix(T** &data, int height, int width, char* acFile = __FILE__, unsigned int uiLine = __LINE__)	{
        if (data == NULLPTR)
        {
          // Allocate rows memory
          try
          {
#ifndef CMNLIB
			data = new T*[height];
#else
#ifndef CL_MEMORY_MANAGER
            data = CL_NEW T*[height];
#else
            data = new(acFile, uiLine) T*[height];
#endif
#endif
          }
          catch(std::bad_alloc xa)
          {
            //cout << "[e] Error memory allocation" << endl;
          }
          for (int y = 0; y < height; y++)
          {
            try
            {
#ifndef CMNLIB
				data[y] = new T[width];
#else
#ifndef CL_MEMORY_MANAGER
              data = CL_NEW T[width];
#else
              data[y] = new(acFile, uiLine) T[width];
#endif
#endif
            }
            catch(std::bad_alloc xa)
            {
              //cout << "[e] Error memory allocation" << endl;
            }
          }
        }
      }
      /** Deallocate the memory for a matrix 
      *	@param data Pointer to the vecture structure.
      *	@param height	Matrix height size
      */
      static void DeallocateMatrix(T** &data, int height)	{
        if (data != NULLPTR)
        {
          // Release memory
          for (int y = 0; y < height; y++)
          {
            delete[] data[y];
          }
          delete[] data;
          data = NULLPTR;
        }
      }
      /** Allocate the memory for a 3D matrix 
      *	@param data Pointer to the matrix structure. Must be a NULLPTR pointer
      *	@param depth	Matrix depth size
      *	@param height	Matrix height size
      *	@param width	Matrix width size
      */
      static void Allocate3DMatrix(T*** &data, int depth, int height, int width, char* acFile = __FILE__, unsigned int uiLine = __LINE__)	
	  {
        if (data == NULLPTR)
        {
          // Allocate depth memory
          try
          {
#ifndef CMNLIB
			data = new T**[depth];
#else
#ifndef CL_MEMORY_MANAGER
            data = CL_NEW T**[depth];
#else
            data = new(acFile, uiLine) T**[depth];
#endif
#endif
          }
          catch(std::bad_alloc xa)
          {
            //cout << "[e] Error memory allocation" << endl;
          }
          for (int d = 0; d < depth; d++)
          {
            // Allocate rows memory
            try
            {
#ifndef CMNLIB
		      data[d] = new T*[height];
#else
#ifndef CL_MEMORY_MANAGER
              data = CL_NEW T*[height];
#else
              data[d] = new(acFile, uiLine) T*[height];
#endif
#endif
            }
            catch(std::bad_alloc xa)
            {
              //cout << "[e] Error memory allocation" << endl;
            }
            for (int y = 0; y < height; y++)
            {
              // Allocate cols memory
              try
              {
#ifndef CMNLIB
				data[d][y] = new T[width];
#else
#ifndef CL_MEMORY_MANAGER
                data = CL_NEW T[width];
#else
                data[d][y] = new(acFile, uiLine) T[width];
#endif
#endif
              }
              catch(std::bad_alloc xa)
              {
                //cout << "[e] Error memory allocation" << endl;
              }
            }
          }
        }
      }
      /** Deallocate the memory for a 3D matrix
      *	@param data Pointer to the matrix structure.
      *	@param depth	Matrix depth size
      *	@param height	Matrix height size
      */
      static void Deallocate3DMatrix(T*** &data, int depth, int height)	{
        if (data != NULLPTR)
        {
          // Release memory
          for (int d = 0; d < depth; d++)
          {
            for (int y = 0; y < height; y++)
            {
              delete[] data[d][y];
            }
            delete[] data[d];
          }
          delete[] data;
          data = NULLPTR;
        }
      }
    };// MemoryManager<T>

}	// namespace memory
}	// namespace CmnLib


//	std::string cpp_filename = "../../bin/data\\MemoryLeakCPP.txt";\
//	std::string c_filename = "../../bin/data\\MemoryLeakC.txt";

#define CMNLIB_TEST_MAIN(resource, cppfile, cfile) \
int main(int argc, char **argv) \
{ \
	CmnLib::ts::TestSystem test_system;\
	std::string cpp_filename = cppfile;\
	std::string c_filename = cfile;\
	test_system.set_memoryc_filename(c_filename);\
	test_system.set_memory_filename(cpp_filename);\
	test_system.test(resource);\
}

#endif /* CMNLIB_CMNLIBCORE_MEMORY_HPP__ */
