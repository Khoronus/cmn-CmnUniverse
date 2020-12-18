/**
* @file foundations_memory.hpp
* @brief Header of foundations memory classes.
*
* @section LICENSE
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR/AUTHORS BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
* THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* @original author Alessandro Moro
* @bug No known bugs.
* @version 0.1.0.0
*
*/


#ifndef CMNLIB_CMNLIBCORE_FOUNDATIONSMEMORY_HPP__
#define CMNLIB_CMNLIBCORE_FOUNDATIONSMEMORY_HPP__

#include <assert.h>

#include <limits>
#include <climits>
#include <iostream>
#include <cstdint>
#include <fstream>
#include <memory>
#include <cstdlib>

#include "cmnlibcore/inc/cmnlibcore/libdefine.hpp"

#if _DEBUG
#ifdef USE_MEMORYMANAGER
#define CMNLIB
#define CL_MEMORY_MANAGER
#endif
#endif

#include "misc.hpp"
#include "foundation_lib.hpp"
#include "error.hpp"
#include "singleton.hpp"

#ifndef CL_MEMORY_MANAGER

	// Use the default memory manager.
	#define CL_NEW new
	#define CL_DELETE delete

#else

	// Overrides of the global new and delete operators.  These enhance the
	// default memory manager by keeping track of information about allocations
	// and deallocations.

	class Memory : public CmnLib::core::Singleton<Memory>
	{
	public:

		//Override standard Singleton retrieval.
		//	@remarks
		//		Why do we do this? Well, it's because the Singleton
		//		implementation is in a .h file, which means it gets compiled
		//		into anybody who includes it. This is needed for the
		//		Singleton template to work, but we actually only want it
		//		compiled into the implementation of the class based on the
		//		Singleton, not all of them. If we don't change this, we get
		//		link errors when trying to use the Singleton-based class from
		//		an outside dll.
		//	@par
		//		This method just delegates to the template version anyway,
		//		but the implementation stays in this single compilation unit,
		//		preventing link errors.
		//
		static Memory& getSingleton(void);
		//Override standard Singleton retrieval.
		//	@remarks
		//		Why do we do this? Well, it's because the Singleton
		//		implementation is in a .h file, which means it gets compiled
		//		into anybody who includes it. This is needed for the
		//		Singleton template to work, but we actually only want it
		//		compiled into the implementation of the class based on the
		//		Singleton, not all of them. If we don't change this, we get
		//		link errors when trying to use the Singleton-based class from
		//		an outside dll.
		//	@par
		//		This method just delegates to the template version anyway,
		//		but the implementation stays in this single compilation unit,
		//		preventing link errors.
		//
		static Memory* getSingletonPtr(void);

		// The memory chunks have information prepended of the following data
		// type.  The blocks are inserted and removed from a doubly linked list.
		struct Block
		{
			size_t Size;
			const char* File;
			unsigned int Line;
			bool IsArray;
			Block* Prev;
			Block* Next;
		};

		// read-write members
		size_t& MaxAllowedBytes ()
		{
			return ms_uiMaxAllowedBytes;
		}
		bool& TrackSizes ()
		{
			return ms_bTrackSizes;
		}

		// read-only members
		size_t GetNumNewCalls ()
		{
			return ms_uiNumNewCalls;
		}
		size_t GetNumDeleteCalls ()
		{
			return ms_uiNumDeleteCalls;
		}
		size_t GetNumBlocks ()
		{
			return ms_uiNumBlocks;
		}
		size_t GetNumBytes ()
		{
			return ms_uiNumBytes;
		}
		size_t GetMaxAllocatedBytes ()
		{
			return ms_uiMaxAllocatedBytes;
		}
		size_t GetMaxBlockSize ()
		{
			return ms_uiMaxBlockSize;
		}
		size_t GetHistogram (int i)
		{
			if (0 <= i && i <= 31)
			{
				return ms_auiHistogram[i];
			}

			return 0;
		}

		// For iteration over the current list of memory blocks.
		const Block* Memory::GetHead ()
		{
			return ms_pkHead;
		}
		const Block* Memory::GetTail ()
		{
			return ms_pkTail;
		}




		// Generate a report about the current list memory blocks.
		//void GenerateReport (const char* acFilename);

		// Generate a report about the current list memory blocks.
		void GenerateReport (const char* acFilename)
		{
			std::ofstream kOStr(acFilename);
			assert(kOStr);
			if (!kOStr)
			{
				return;
			}

			// Total calls.
			kOStr << "Total number of 'new' calls = "
				<< (unsigned int)ms_uiNumNewCalls << std::endl;
			kOStr << "Total number of 'delete' calls = "
				<< (unsigned int)ms_uiNumDeleteCalls << std::endl;
			kOStr << "Maximum number of allocated bytes = "
				<< (unsigned int)ms_uiMaxAllocatedBytes << std::endl << std::endl;

			// Remaining counts.
			kOStr << "Remaining number of blocks = "
				<< (unsigned int)ms_uiNumBlocks << std::endl;
			kOStr << "Remaining number of bytes  = "
				<< (unsigned int)ms_uiNumBytes << std::endl << std::endl;

			// Count the blocks and bytes from known and unknown sources.
			size_t uiNumKnownBlocks = 0;
			size_t uiNumKnownBytes = 0;
			size_t uiNumUnknownBlocks = 0;
			size_t uiNumUnknownBytes = 0;
			Block* pkBlock = ms_pkHead;
			while (pkBlock)
			{
				if (pkBlock->File)
				{
					uiNumKnownBlocks++;
					uiNumKnownBytes += pkBlock->Size;
				}
				else
				{
					uiNumUnknownBlocks++;
					uiNumUnknownBytes += pkBlock->Size;
				}
				pkBlock = pkBlock->Next;
			}

		#ifdef WM4_ENABLE_CONSISTENCY_CHECK
			// consistency check
			assert(uiNumKnownBlocks + uiNumUnknownBlocks == ms_uiNumBlocks);
			assert(uiNumKnownBytes + uiNumUnknownBytes == ms_uiNumBytes);
		#endif

			kOStr << "Remaining number of known blocks = "
				<< (unsigned int)uiNumKnownBlocks << std::endl;
			kOStr << "Remaining number of known bytes  = "
				<< (unsigned int)uiNumKnownBytes << std::endl << std::endl;

			kOStr << "Remaining number of unknown blocks = "
				<< (unsigned int)uiNumUnknownBlocks << std::endl;
			kOStr << "Remaining number of unknown bytes  = "
				<< (unsigned int)uiNumUnknownBytes << std::endl << std::endl;

			// Report the information for each block.
			pkBlock = ms_pkHead;
			size_t uiIndex = 0;
			while (pkBlock)
			{
				kOStr << "block = " << (unsigned int)uiIndex << std::endl;
				kOStr << "size  = " << (unsigned int)pkBlock->Size << std::endl;
				if (pkBlock->File)
				{
					kOStr << "file  = " << pkBlock->File << std::endl;
					kOStr << "line  = " << pkBlock->Line << std::endl;
				}
				else
				{
					kOStr << "file  = unknown" << std::endl;
					kOStr << "line  = unknown" << std::endl;
				}
				kOStr << "array = " << pkBlock->IsArray << std::endl << std::endl;
				pkBlock = pkBlock->Next;
				uiIndex++;
			}
			kOStr.close();

		#ifdef WM4_ENABLE_CONSISTENCY_CHECK
			// consistency check
			assert(uiIndex == ms_uiNumBlocks);
		#endif
		}

	private:
		// Count the number of times the memory allocation/deallocation system
		// has been entered.
		size_t ms_uiNumNewCalls;
		size_t ms_uiNumDeleteCalls;

		// Set this value in your application if you want to know when NumBytes
		// exceeds a maximum allowed number of bytes.  An 'assert' will be
		// triggered in Allocate when this happens.  The default value is 0, in
		// which case no comparison is made between NumBytes and MaxAllowedBytes.
		size_t ms_uiMaxAllowedBytes;

		// The current number of allocated memory blocks.
		size_t ms_uiNumBlocks;

		// The current number of allocated bytes.
		size_t ms_uiNumBytes;

		// Doubly linked list of headers for the memory blocks.
		Block* ms_pkHead;
		Block* ms_pkTail;

		// Set this variable to 'true' if you want the ms_uiMaxBlockSize and
		// ms_auiHistogram[] elements to be computed.  The default is 'false'.
		bool ms_bTrackSizes;

		// The maximum number of bytes allocated by the application.
		size_t ms_uiMaxAllocatedBytes;

		// The size of the largest memory block allocated by the application.
		size_t ms_uiMaxBlockSize;

		// Keep track of the number of allocated blocks of various sizes.  The
		// element Histogram[0] stores the number of allocated blocks of size 1.
		// The element Histogram[31] stores the number of allocated blocks of
		// size larger than pow(2,30).  For 1 <= i <= 30, the element Histogram[i]
		// stores the number of allocated blocks of size N, where
		// pow(2,i-1) < N <= pow(2,i).
		size_t ms_auiHistogram[32];

	// internal use
	public:

		Memory()	{
			ms_uiNumNewCalls = 0;
			ms_uiNumDeleteCalls = 0;
			ms_uiMaxAllowedBytes = 0;
			ms_uiNumBlocks = 0;
			ms_uiNumBytes = 0;
			ms_pkHead = 0;
			ms_pkTail = 0;
			ms_bTrackSizes = false;
			ms_uiMaxAllocatedBytes = 0;
			ms_uiMaxBlockSize = 0;
			REP(i, 32)
				ms_auiHistogram[i] = 0;
		}

		//void* Allocate (size_t uiSize, char* acFile, unsigned int uiLine,
		//	bool bIsArray);
		//void Deallocate (char* pcAddr, bool bIsArray);
		//void InsertBlock (Block* pkBlock);
		//void RemoveBlock (Block* pkBlock);

		//----------------------------------------------------------------------------
		void* Allocate (size_t uiSize, const char* acFile, unsigned int uiLine,
			bool bIsArray)
		{
			ms_uiNumNewCalls++;

			// The 'assert' used to be enabled to trap attempts to allocate zero
			// bytes.  However, the DirectX function D3DXCheckNewDelete may pass in
			// a value of zero.
			// assert(uiSize > 0);

			// Allocate additional storage for the block header information.
			size_t uiExtendedSize = sizeof(Block) + uiSize;
			char* pcAddr = (char*)malloc(uiExtendedSize);

			// Save the allocation information.
			Block* pkBlock = (Block*)pcAddr;
			pkBlock->Size = uiSize;
			pkBlock->File = acFile;
			pkBlock->Line = uiLine;
			pkBlock->IsArray = bIsArray;
			InsertBlock(pkBlock);

			// Move the pointer to the start of what the user expects from 'new'.
			pcAddr += sizeof(Block);

			// Keep track of number of allocated blocks and bytes.
			ms_uiNumBlocks++;
			ms_uiNumBytes += uiSize;

			if (ms_uiMaxAllowedBytes > 0 && ms_uiNumBytes > ms_uiMaxAllowedBytes)
			{
				// The allocation has exceeded the maximum number of bytes.
				assert(false);
			}

			// Keep track of the maximum number of bytes allocated.
			if (ms_uiNumBytes > ms_uiMaxAllocatedBytes)
			{
				ms_uiMaxAllocatedBytes = ms_uiNumBytes;
			}

			// Keep track of the distribution of sizes for allocations.
			if (ms_bTrackSizes)
			{
				// Keep track of the largest block ever allocated.
				if (uiSize > ms_uiMaxBlockSize)
				{
					ms_uiMaxBlockSize = uiSize;
				}

				unsigned int uiTwoPowerI = 1;
				int i;
				for (i = 0; i <= 30; i++, uiTwoPowerI <<= 1)
				{
					if (uiSize <= uiTwoPowerI)
					{
						ms_auiHistogram[i]++;
						break;
					}
				}
				if (i == 31)
				{
					ms_auiHistogram[i]++;
				}
			}

			return (void*)pcAddr;
		}
		//----------------------------------------------------------------------------
		void Deallocate (char* pcAddr, bool bIsArray)
		{
			ms_uiNumDeleteCalls++;

			if (!pcAddr)
			{
				return;
			}

			// Move the pointer to the start of the actual allocated block.
			pcAddr -= sizeof(Block);

			// Get the allocation information and remove the block.  The removal
			// only modifies the Prev and Next pointers, so the block information is
			// accessible after the call.
			Block* pkBlock = (Block*)pcAddr;
			RemoveBlock(pkBlock);

		#ifdef WM4_ENABLE_NEW_DELETE_MISMATCH_ASSERT
			// Check for correct pairing of new/delete or new[]/delete[].
			assert(pkBlock->IsArray == bIsArray);
		#else
			// Avoid compiler warnings about an unused formal parameter.
			(void)bIsArray;
		#endif

			// Keep track of number of allocated blocks and bytes.  If the number of
			// blocks is zero at this time, a delete has been called twice on the
			// same pointer.  If the number of bytes is too small at this time, some
			// internal problem has occurred within this class and needs to be
			// diagnosed.
			assert(ms_uiNumBlocks > 0 && ms_uiNumBytes >= pkBlock->Size);
			ms_uiNumBlocks--;
			ms_uiNumBytes -= pkBlock->Size;

			// Deallocate the memory block.
			free(pcAddr);
		}
		//----------------------------------------------------------------------------
		void InsertBlock (Block* pkBlock)
		{
			// New blocks are inserted at the tail of the doubly linked list.
			if (ms_pkTail)
			{
				pkBlock->Prev = ms_pkTail;
				pkBlock->Next = 0;
				ms_pkTail->Next = pkBlock;
				ms_pkTail = pkBlock;
			}
			else
			{
				pkBlock->Prev = 0;
				pkBlock->Next = 0;
				ms_pkHead = pkBlock;
				ms_pkTail = pkBlock;
			}
		}
		//----------------------------------------------------------------------------
		void RemoveBlock (Block* pkBlock)
		{
			if (pkBlock->Prev)
			{
				pkBlock->Prev->Next = pkBlock->Next;
			}
			else
			{
				ms_pkHead = pkBlock->Next;
			}
		    
			if (pkBlock->Next)
			{
				pkBlock->Next->Prev = pkBlock->Prev;
			}
			else
			{
				ms_pkTail = pkBlock->Prev;
			}
		}
	};

	#define CL_NEW new(__FILE__,__LINE__)
	#define CL_DELETE delete

	//----------------------------------------------------------------------------
	void* operator new (size_t uiSize);
	//----------------------------------------------------------------------------
	void* operator new[](size_t uiSize);
	//----------------------------------------------------------------------------
	void* operator new (size_t uiSize, const char* acFile, unsigned int uiLine);
	//----------------------------------------------------------------------------
	void* operator new[](size_t uiSize, const char* acFile, unsigned int uiLine);
	//----------------------------------------------------------------------------
	void operator delete (void* pvAddr);
	//----------------------------------------------------------------------------
	void operator delete[](void* pvAddr);
	//----------------------------------------------------------------------------
	void operator delete (void* pvAddr, char*, unsigned int);
	//----------------------------------------------------------------------------
	void operator delete[](void* pvAddr, char*, unsigned int);
	//----------------------------------------------------------------------------





	// C standard memory allocation memory leak tracker
	// Based on the code of Rabinarayan Biswal 
	// http://www.codeproject.com/KB/cpp/leak_detector_c.aspx

	#undef		malloc
	#undef		calloc
	#undef 		free

	class MemoryLeakTrackerC : public CmnLib::core::Singleton<MemoryLeakTrackerC>
	{
	public:

		//Override standard Singleton retrieval.
		//	@remarks
		//		Why do we do this? Well, it's because the Singleton
		//		implementation is in a .h file, which means it gets compiled
		//		into anybody who includes it. This is needed for the
		//		Singleton template to work, but we actually only want it
		//		compiled into the implementation of the class based on the
		//		Singleton, not all of them. If we don't change this, we get
		//		link errors when trying to use the Singleton-based class from
		//		an outside dll.
		//	@par
		//		This method just delegates to the template version anyway,
		//		but the implementation stays in this single compilation unit,
		//		preventing link errors.
		//
		static MemoryLeakTrackerC& getSingleton(void);
		//Override standard Singleton retrieval.
		//	@remarks
		//		Why do we do this? Well, it's because the Singleton
		//		implementation is in a .h file, which means it gets compiled
		//		into anybody who includes it. This is needed for the
		//		Singleton template to work, but we actually only want it
		//		compiled into the implementation of the class based on the
		//		Singleton, not all of them. If we don't change this, we get
		//		link errors when trying to use the Singleton-based class from
		//		an outside dll.
		//	@par
		//		This method just delegates to the template version anyway,
		//		but the implementation stays in this single compilation unit,
		//		preventing link errors.
		//
		static MemoryLeakTrackerC* getSingletonPtr(void);

		MemoryLeakTrackerC()	{
			ptr_start = NULLPTR;
			ptr_next = NULLPTR;
		}

		static const int FILE_NAME_LENGTH = 512;

		struct _MEM_INFO
		{
			void			*address;
			unsigned int	size;
			char			file_name[FILE_NAME_LENGTH];
			unsigned int	line;
		};
		typedef struct _MEM_INFO MEM_INFO;

		struct _MEM_LEAK {
			MEM_INFO mem_info;
			struct _MEM_LEAK * next;
		};
		typedef struct _MEM_LEAK MEM_LEAK;


		MEM_LEAK * ptr_start;
		MEM_LEAK * ptr_next;

		/*
		 * adds allocated memory info. into the list
		 *
		 */
		void add(MEM_INFO alloc_info)
		{

			MEM_LEAK * mem_leak_info = NULLPTR;
			mem_leak_info = (MEM_LEAK *) malloc (sizeof(MEM_LEAK));
			mem_leak_info->mem_info.address = alloc_info.address;
			mem_leak_info->mem_info.size = alloc_info.size;
			strcpy(mem_leak_info->mem_info.file_name, alloc_info.file_name); 
			mem_leak_info->mem_info.line = alloc_info.line;
			mem_leak_info->next = NULLPTR;

			if (ptr_start == NULLPTR) {	
				ptr_start = mem_leak_info;
				ptr_next = ptr_start;
			} else {
				ptr_next->next = mem_leak_info;
				ptr_next = ptr_next->next;				
			}

		}

		/*
		 * erases memory info. from the list
		 *
		 */
		void erase(unsigned pos)
		{

			unsigned index = 0;
			MEM_LEAK * alloc_info, * temp;
			
			if(pos == 0) {
				MEM_LEAK * temp = ptr_start;
				ptr_start = ptr_start->next;
				free(temp);
			} else {
				for(index = 0, alloc_info = ptr_start; index < pos; 
					alloc_info = alloc_info->next, ++index)
				{
					if(pos == index + 1)
					{
						temp = alloc_info->next;
						alloc_info->next =  temp->next;
						free(temp);
						break;
					}
				}
			}
		}

		/*
		 * deletes all the elements from the list
		 */
		void clear()
		{
			MEM_LEAK * temp = ptr_start;
			MEM_LEAK * alloc_info = ptr_start;

			while(alloc_info != NULLPTR) 
			{
				alloc_info = alloc_info->next;
				free(temp);
				temp = alloc_info;
			}
		}

		/*
		 * replacement of malloc
		 */
		void * xmalloc (unsigned int size, const char * file, unsigned int line)
		{
			void * ptr = malloc (size);
			if (ptr != NULLPTR) 
			{
				add_mem_info(ptr, size, file, line);
			}
			return ptr;
		}

		/*
		 * replacement of calloc
		 */
		void * xcalloc (unsigned int elements, unsigned int size, const char * file, unsigned int line)
		{
			unsigned total_size;
			void * ptr = calloc(elements , size);
			if(ptr != NULLPTR)
			{
				total_size = elements * size;
				add_mem_info (ptr, total_size, file, line);
			}
			return ptr;
		}


		/*
		 * replacement of free
		 */
		void xfree(void * mem_ref)
		{
			remove_mem_info(mem_ref);
			free(mem_ref);
		}

		/*
		 * gets the allocated memory info and adds it to a list
		 *
		 */
		void add_mem_info (void * mem_ref, unsigned int size,  const char * file, unsigned int line)
		{
			MEM_INFO mem_alloc_info;

			/* fill up the structure with all info */
			memset( &mem_alloc_info, 0, sizeof ( mem_alloc_info ) );
			mem_alloc_info.address 	= mem_ref;
			mem_alloc_info.size = size;
			strncpy(mem_alloc_info.file_name, file, FILE_NAME_LENGTH);
			mem_alloc_info.line = line;
			
			/* add the above info to a list */
			add(mem_alloc_info);
		}

		/*
		 * if the allocated memory info is part of the list, removes it
		 *
		 */
		void remove_mem_info (void * mem_ref)
		{
			unsigned short index;
			MEM_LEAK  * leak_info = ptr_start;

			/* check if allocate memory is in our list */
			for(index = 0; leak_info != NULLPTR; ++index, leak_info = leak_info->next)
			{
				if ( leak_info->mem_info.address == mem_ref )
				{
					erase ( index );
					break;
				}
			}
		}

		/*
		 * writes all info of the unallocated memory into a file
		 */
		void report_mem_leak(const char *output_filename)
		{
			//unsigned short index;
			MEM_LEAK * leak_info;

			FILE * fp_write = fopen (output_filename, "wt");
			char info[1024];

			if(fp_write != NULLPTR)
			{
				sprintf(info, "%s\n", "Memory Leak Summary");
				fwrite(info, (strlen(info) + 1) , 1, fp_write);
				sprintf(info, "%s\n", "-----------------------------------");	
				fwrite(info, (strlen(info) + 1) , 1, fp_write);
				
				for(leak_info = ptr_start; leak_info != NULLPTR; leak_info = leak_info->next)
				{
					sprintf(info, "address : %d\n", leak_info->mem_info.address);
					fwrite(info, (strlen(info) + 1) , 1, fp_write);
					sprintf(info, "size    : %d bytes\n", leak_info->mem_info.size);			
					fwrite(info, (strlen(info) + 1) , 1, fp_write);
					sprintf(info, "file    : %s\n", leak_info->mem_info.file_name);
					fwrite(info, (strlen(info) + 1) , 1, fp_write);
					sprintf(info, "line    : %d\n", leak_info->mem_info.line);
					fwrite(info, (strlen(info) + 1) , 1, fp_write);
					sprintf(info, "%s\n", "-----------------------------------");	
					fwrite(info, (strlen(info) + 1) , 1, fp_write);
				}
			}	
			clear();
		}
	};


	#define  malloc(size) 	    	   	MemoryLeakTrackerC::getSingletonPtr()->xmalloc (size, __FILE__, __LINE__)
	#define  calloc(elements, size)  	MemoryLeakTrackerC::getSingletonPtr()->xcalloc (elements, size, __FILE__, __LINE__)
	#define  free(mem_ref) 		  	 	MemoryLeakTrackerC::getSingletonPtr()->xfree(mem_ref)


	//**************************************************//
	//	MAIN CLASS TO INTERACT WITH THE CREST PROJECT	//
	//**************************************************//

	//--------------------------------------------------------------------------
	template<> Memory* CmnLib::core::Singleton<Memory>::ms_Singleton = 0;
	//Memory* Memory::getSingletonPtr(void)
	//{
	//	return ms_Singleton;
	//}
	////--------------------------------------------------------------------------
	//Memory& Memory::getSingleton(void)
	//{  
	//	return *ms_Singleton;
	//}

	//--------------------------------------------------------------------------
	template<> MemoryLeakTrackerC* CmnLib::core::Singleton<MemoryLeakTrackerC>::ms_Singleton = 0;
	//MemoryLeakTrackerC* MemoryLeakTrackerC::getSingletonPtr(void)
	//{
	//	return ms_Singleton;
	//}
	////--------------------------------------------------------------------------
	//MemoryLeakTrackerC& MemoryLeakTrackerC::getSingleton(void)
	//{  
	//	return *ms_Singleton;
	//}

#endif	// endif #define CL_MEMORY_MANAGER




namespace CmnLib
{
namespace core
{
	// Define memory min block allocable
	#define CL_ALLOC_MINSIZE 4

	// Define max memory allocable
	#define CL_MAX_ALLOC_SIZE (((size_t)1 << (sizeof(size_t)*8-2)))

	typedef void* (CL_CDECL *ClAllocFunc)(size_t size, void* userdata);
	typedef int (CL_CDECL *ClFreeFunc)(void* pptr, void* userdata);

	//CL_EXPORTS void* fastMalloc(size_t);
	//CL_EXPORTS void fastFree(void* ptr);

	template<typename _Tp> static inline _Tp* allocate(size_t n)
	{
#ifndef CMNLIB
		return new _Tp[n];
#else
#ifndef CL_MEMORY_MANAGER
		return CL_NEW _Tp[n];
#else
		return new(__FILE__, __LINE__) _Tp[n];
#endif
#endif

	}

	template<typename _Tp> static inline void deallocate(_Tp* ptr, size_t)
	{
		delete[] ptr;
	}

	template<typename _Tp> static inline _Tp* alignPtr(_Tp* ptr, int n=(int)sizeof(_Tp))
	{
		return (_Tp*)(((size_t)ptr + n-1) & -n);
	}

	static inline size_t alignSize(size_t sz, int n)
	{
		return (sz + n-1) & -n;
	}

	/** Class to manage the basic memory functions such as allocation and free
	*/
	class MemoryFoundations
	{
	public:

		static void* clAlignPtr( const void* ptr, int align CL_DEFAULT(32) )
		{
			assert( (align & (align-1)) == 0 );
			return (void*)( ((size_t)ptr + align - 1) & ~(size_t)(align-1) );
		}

		static int clAlign( int size, int align )
		{
			assert( (align & (align-1)) == 0 && size < INT_MAX );
			return (size + align - 1) & -align;
		}

		/* <malloc> wrapper.
		   If there is no enough memory, the function
		   (as well as other OpenCV functions that call cvAlloc)
		   raises an error. */
		static void* clAlloc( size_t size )
		{
			return fastMalloc( size );
		}

		/* <free> wrapper.
		   Here and further all the memory releasing functions
		   (that all call cvFree) take double pointer in order to
		   to clear pointer to the data after releasing it.
		   Passing pointer to NULLPTR pointer is Ok: nothing happens in this case
		*/
		//CLAPI(void)   clFree_( void* ptr );
		//#define clFree(ptr) (clFree_(*(ptr)), *(ptr)=0)
		static void clFree( void* ptr )
		{
			fastFree( ptr );
		}


		static void clSetMemoryManager( ClAllocFunc, ClFreeFunc, void * )
		{
			CmnLib::core::CL_Error( -1, "Custom memory allocator is not supported" );
		}


		#define CL_USE_SYSTEM_MALLOC 1

		static void* OutOfMemoryError(size_t size)
		{
			CL_Error_(Error::CL_NoMem, ("Failed to allocate %lu bytes", (unsigned long)size));
			return 0;
		}

		#if CL_USE_SYSTEM_MALLOC

		static void deleteThreadAllocData() {}

		static void* fastMalloc( size_t size )
		{
			uchar* udata = (uchar*)malloc(size + 
				static_cast<size_t>(sizeof(void*)) + 
				static_cast<size_t>(CL_MALLOC_ALIGN));
			if(!udata)
				return OutOfMemoryError(size);
			uchar** adata = alignPtr((uchar**)udata + 1, CL_MALLOC_ALIGN);
			adata[-1] = udata;
			return adata;
		}
		    
		static void fastFree(void* ptr)
		{
			if(ptr)
			{
				uchar* udata = ((uchar**)ptr)[-1];
				CL_DbgAssert(udata < (uchar*)ptr &&
					   ((uchar*)ptr - udata) <= (ptrdiff_t)(
						   static_cast<size_t>(sizeof(void*)) + 
						   static_cast<size_t>(CL_MALLOC_ALIGN)));
				free(udata);
			}
		}

		#else

		#if 0
		#define SANITY_CHECK(block) \
			CL_Assert(((size_t)(block) & (MEM_BLOCK_SIZE-1)) == 0 && \
				(unsigned)(block)->binIdx <= (unsigned)MAX_BIN && \
				(block)->signature == MEM_BLOCK_SIGNATURE)
		#else
		#define SANITY_CHECK(block)
		#endif

		#define STAT(stmt)

		#ifdef WIN32
		struct CriticalSection
		{
			CriticalSection() { InitializeCriticalSection(&cs); }
			~CriticalSection() { DeleteCriticalSection(&cs); }
			void lock() { EnterCriticalSection(&cs); }
			void unlock() { LeaveCriticalSection(&cs); }
			bool trylock() { return TryEnterCriticalSection(&cs) != 0; }

			CRITICAL_SECTION cs;
		};

		void* SystemAlloc(size_t size)
		{
			void* ptr = malloc(size);
			return ptr ? ptr : OutOfMemoryError(size);
		}

		void SystemFree(void* ptr, size_t)
		{
			free(ptr);
		}
		#else
		struct CriticalSection
		{
			CriticalSection() { pthread_mutex_init(&mutex, 0); }
			~CriticalSection() { pthread_mutex_destroy(&mutex); }
			void lock() { pthread_mutex_lock(&mutex); }
			void unlock() { pthread_mutex_unlock(&mutex); }
			bool trylock() { return pthread_mutex_trylock(&mutex) == 0; }

			pthread_mutex_t mutex;
		};

		void* SystemAlloc(size_t size)
		{
			#ifndef MAP_ANONYMOUS
			#define MAP_ANONYMOUS MAP_ANON
			#endif
			void* ptr = 0;
			ptr = mmap(ptr, size, (PROT_READ | PROT_WRITE), MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
			return ptr != MAP_FAILED ? ptr : OutOfMemoryError(size);
		}

		void SystemFree(void* ptr, size_t size)
		{
			munmap(ptr, size);
		}
		#endif

		struct AutoLock
		{
			AutoLock(CriticalSection& _cs) : cs(&_cs) { cs->lock(); }
			~AutoLock() { cs->unlock(); }
			CriticalSection* cs;
		};

		const size_t MEM_BLOCK_SIGNATURE = 0x01234567;
		const int MEM_BLOCK_SHIFT = 14;
		const size_t MEM_BLOCK_SIZE = 1 << MEM_BLOCK_SHIFT;
		const size_t HDR_SIZE = 128;
		const size_t MAX_BLOCK_SIZE = MEM_BLOCK_SIZE - HDR_SIZE;
		const int MAX_BIN = 28;

		static const int binSizeTab[MAX_BIN+1] =
		{ 8, 16, 24, 32, 40, 48, 56, 64, 80, 96, 128, 160, 192, 256, 320, 384, 480, 544, 672, 768,
		896, 1056, 1328, 1600, 2688, 4048, 5408, 8128, 16256 };

		struct MallocTables
		{
			void initBinTab()
			{
				int i, j = 0, n;
				for( i = 0; i <= MAX_BIN; i++ )
				{
					n = binSizeTab[i]>>3;
					for( ; j <= n; j++ )
						binIdx[j] = (uchar)i;
				}
			}
			int bin(size_t size)
			{
				assert( size <= MAX_BLOCK_SIZE );
				return binIdx[(size + 7)>>3];
			}

			MallocTables()
			{
				initBinTab();
			}

			uchar binIdx[MAX_BLOCK_SIZE/8+1];
		};

		MallocTables mallocTables;

		struct Node
		{
			Node* next;
		};

		struct ThreadData;

		struct Block
		{
			Block(Block* _next)
			{
				signature = MEM_BLOCK_SIGNATURE;
				prev = 0;
				next = _next;
				privateFreeList = publicFreeList = 0;
				bumpPtr = endPtr = 0;
				objSize = 0;
				threadData = 0;
				data = (uchar*)this + HDR_SIZE;
			}

			~Block() {}

			void init(Block* _prev, Block* _next, int _objSize, ThreadData* _threadData)
			{
				prev = _prev;
				if(prev)
					prev->next = this;
				next = _next;
				if(next)
					next->prev = this;
				objSize = _objSize;
				binIdx = mallocTables.bin(objSize);
				threadData = _threadData;
				privateFreeList = publicFreeList = 0;
				bumpPtr = data;
				int nobjects = MAX_BLOCK_SIZE/objSize;
				endPtr = bumpPtr + nobjects*objSize;
				almostEmptyThreshold = (nobjects + 1)/2;
				allocated = 0;
			}

			bool isFilled() const { return allocated > almostEmptyThreshold; }

			size_t signature;
			Block* prev;
			Block* next;
			Node* privateFreeList;
			Node* publicFreeList;
			uchar* bumpPtr;
			uchar* endPtr;
			uchar* data;
			ThreadData* threadData;
			int objSize;
			int binIdx;
			int allocated;
			int almostEmptyThreshold;
			CriticalSection cs;
		};

		struct BigBlock
		{
			BigBlock(int bigBlockSize, BigBlock* _next)
			{
				first = alignPtr((Block*)(this+1), MEM_BLOCK_SIZE);
				next = _next;
				nblocks = (int)(((char*)this + bigBlockSize - (char*)first)/MEM_BLOCK_SIZE);
				Block* p = 0;
				for( int i = nblocks-1; i >= 0; i-- )
					p = ::new((uchar*)first + i*MEM_BLOCK_SIZE) Block(p);
			}

			~BigBlock()
			{
				for( int i = nblocks-1; i >= 0; i-- )
					((Block*)((uchar*)first+i*MEM_BLOCK_SIZE))->~Block();
			}

			BigBlock* next;
			Block* first;
			int nblocks;
		};

		struct BlockPool
		{
			BlockPool(int _bigBlockSize=1<<20) : pool(0), bigBlockSize(_bigBlockSize)
			{
			}

			~BlockPool()
			{
				AutoLock lock(cs);
				while( pool )
				{
					BigBlock* nextBlock = pool->next;
					pool->~BigBlock();
					SystemFree(pool, bigBlockSize);
					pool = nextBlock;
				}
			}

			Block* alloc()
			{
				AutoLock lock(cs);
				Block* block;
				if( !freeBlocks )
				{
					BigBlock* bblock = ::new(SystemAlloc(bigBlockSize)) BigBlock(bigBlockSize, pool);
					assert( bblock != 0 );
					freeBlocks = bblock->first;
					pool = bblock;
				}
				block = freeBlocks;
				freeBlocks = freeBlocks->next;
				if( freeBlocks )
					freeBlocks->prev = 0;
				STAT(stat.bruttoBytes += MEM_BLOCK_SIZE);
				return block;
			}

			void free(Block* block)
			{
				AutoLock lock(cs);
				block->prev = 0;
				block->next = freeBlocks;
				freeBlocks = block;
				STAT(stat.bruttoBytes -= MEM_BLOCK_SIZE);
			}

			CriticalSection cs;
			Block* freeBlocks;
			BigBlock* pool;
			int bigBlockSize;
			int blocksPerBigBlock;
		};

		BlockPool mallocPool;

		enum { START=0, FREE=1, GC=2 };

		struct ThreadData
		{
			ThreadData() { for(int i = 0; i <= MAX_BIN; i++) bins[i][START] = bins[i][FREE] = bins[i][GC] = 0; }
			~ThreadData()
			{
				// mark all the thread blocks as abandoned or even release them
				for( int i = 0; i <= MAX_BIN; i++ )
				{
					Block *bin = bins[i][START], *block = bin;
					bins[i][START] = bins[i][FREE] = bins[i][GC] = 0;
					if( block )
					{
						do
						{
							Block* next = block->next;
							int allocated = block->allocated;
							{
							AutoLock lock(block->cs);
							block->next = block->prev = 0;
							block->threadData = 0;
							Node *node = block->publicFreeList;
							for( ; node != 0; node = node->next )
								allocated--;
							}
							if( allocated == 0 )
								mallocPool.free(block);
							block = next;
						}
						while( block != bin );
					}
				}
			}

			void moveBlockToFreeList( Block* block )
			{
				int i = block->binIdx;
				Block*& freePtr = bins[i][FREE];
				CL_DbgAssert( block->next->prev == block && block->prev->next == block );
				if( block != freePtr )
				{
					Block*& gcPtr = bins[i][GC];
					if( gcPtr == block )
						gcPtr = block->next;
					if( block->next != block )
					{
						block->prev->next = block->next;
						block->next->prev = block->prev;
					}
					block->next = freePtr->next;
					block->prev = freePtr;
					freePtr = block->next->prev = block->prev->next = block;
				}
			}

			Block* bins[MAX_BIN+1][3];

		#ifdef WIN32
		#ifdef WINCE
		#	define TLS_OUT_OF_INDEXES ((DWORD)0xFFFFFFFF)
		#endif

			static DWORD tlsKey;
			static ThreadData* get()
			{
				ThreadData* data;
				if( tlsKey == TLS_OUT_OF_INDEXES )
					tlsKey = TlsAlloc();
				data = (ThreadData*)TlsGetValue(tlsKey);
				if( !data )
				{
					data = new ThreadData;
					TlsSetValue(tlsKey, data);
				}
				return data;
			}
		#else
			static void deleteData(void* data)
			{
				delete (ThreadData*)data;
			}

			static pthread_key_t tlsKey;
			static ThreadData* get()
			{
				ThreadData* data;
				if( !tlsKey )
					pthread_key_create(&tlsKey, deleteData);
				data = (ThreadData*)pthread_getspecific(tlsKey);
				if( !data )
				{
					data = new ThreadData;
					pthread_setspecific(tlsKey, data);
				}
				return data;
			}
		#endif
		};

		#ifdef WIN32
		DWORD ThreadData::tlsKey = TLS_OUT_OF_INDEXES;

		void deleteThreadAllocData()
		{
			if( ThreadData::tlsKey != TLS_OUT_OF_INDEXES )
				delete (ThreadData*)TlsGetValue( ThreadData::tlsKey );
		}

		#else
		pthread_key_t ThreadData::tlsKey = 0;
		#endif

		#if 0
		static void checkList(ThreadData* tls, int idx)
		{
			Block* block = tls->bins[idx][START];
			if( !block )
			{
				CL_DbgAssert( tls->bins[idx][FREE] == 0 && tls->bins[idx][GC] == 0 );
			}
			else
			{
				bool gcInside = false;
				bool freeInside = false;
				do
				{
					if( tls->bins[idx][FREE] == block )
						freeInside = true;
					if( tls->bins[idx][GC] == block )
						gcInside = true;
					block = block->next;
				}
				while( block != tls->bins[idx][START] );
				CL_DbgAssert( gcInside && freeInside );
			}
		}
		#else
		#define checkList(tls, idx)
		#endif

		void* fastMalloc( size_t size )
		{
			if( size > MAX_BLOCK_SIZE )
			{
				size_t size1 = size + sizeof(uchar*)*2 + MEM_BLOCK_SIZE;
				uchar* udata = (uchar*)SystemAlloc(size1);
				uchar** adata = alignPtr((uchar**)udata + 2, MEM_BLOCK_SIZE);
				adata[-1] = udata;
				adata[-2] = (uchar*)size1;
				return adata;
			}

			{
			ThreadData* tls = ThreadData::get();
			int idx = mallocTables.bin(size);
			Block*& startPtr = tls->bins[idx][START];
			Block*& gcPtr = tls->bins[idx][GC];
			Block*& freePtr = tls->bins[idx][FREE], *block = freePtr;
			checkList(tls, idx);
			size = binSizeTab[idx];
			STAT(
				stat.nettoBytes += size;
				stat.mallocCalls++;
				);
			uchar* data = 0;

			for(;;)
			{
				if( block )
				{
					// try to find non-full block
					for(;;)
					{
						CL_DbgAssert( block->next->prev == block && block->prev->next == block );
						if( block->bumpPtr )
						{
							data = block->bumpPtr;
							if( (block->bumpPtr += size) >= block->endPtr )
								block->bumpPtr = 0;
							break;
						}

						if( block->privateFreeList )
						{
							data = (uchar*)block->privateFreeList;
							block->privateFreeList = block->privateFreeList->next;
							break;
						}

						if( block == startPtr )
							break;
						block = block->next;
					}
		#if 0
					avg_k += _k;
					avg_nk++;
					if( avg_nk == 1000 )
					{
						printf("avg search iters per 1e3 allocs = %g\n", (double)avg_k/avg_nk );
						avg_k = avg_nk = 0;
					}
		#endif

					freePtr = block;
					if( !data )
					{
						block = gcPtr; 
						for( int k = 0; k < 2; k++ )
						{
							SANITY_CHECK(block);
							CL_DbgAssert( block->next->prev == block && block->prev->next == block );
							if( block->publicFreeList )
							{
								{
								AutoLock lock(block->cs);
								block->privateFreeList = block->publicFreeList;
								block->publicFreeList = 0;
								}
								Node* node = block->privateFreeList;
								for(;node != 0; node = node->next)
									--block->allocated;
								data = (uchar*)block->privateFreeList;
								block->privateFreeList = block->privateFreeList->next;
								gcPtr = block->next;
								if( block->allocated+1 <= block->almostEmptyThreshold )
									tls->moveBlockToFreeList(block);
								break;
							}
							block = block->next;
						}
						if( !data )
							gcPtr = block;
					}
				}

				if( data )
					break;
				block = mallocPool.alloc();
				block->init(startPtr ? startPtr->prev : block, startPtr ? startPtr : block, (int)size, tls);
				if( !startPtr )
					startPtr = gcPtr = freePtr = block;
				checkList(tls, block->binIdx);
				SANITY_CHECK(block);
			}

			++block->allocated;
			return data;
			}
		}

		void fastFree( void* ptr )
		{
			if( ((size_t)ptr & (MEM_BLOCK_SIZE-1)) == 0 )
			{
				if( ptr != 0 )
				{
					void* origPtr = ((void**)ptr)[-1];
					size_t sz = (size_t)((void**)ptr)[-2];
					SystemFree( origPtr, sz );
				}
				return;
			}

			{
			ThreadData* tls = ThreadData::get();
			Node* node = (Node*)ptr;
			Block* block = (Block*)((size_t)ptr & -(int)MEM_BLOCK_SIZE);
			assert( block->signature == MEM_BLOCK_SIGNATURE );

			if( block->threadData == tls )
			{
				STAT(
				stat.nettoBytes -= block->objSize;
				stat.freeCalls++;
				float ratio = (float)stat.nettoBytes/stat.bruttoBytes;
				if( stat.minUsageRatio > ratio )
					stat.minUsageRatio = ratio;
				);

				SANITY_CHECK(block);

				bool prevFilled = block->isFilled();
				--block->allocated;
				if( !block->isFilled() && (block->allocated == 0 || prevFilled) )
				{
					if( block->allocated == 0 )
					{
						int idx = block->binIdx;
						Block*& startPtr = tls->bins[idx][START];
						Block*& freePtr = tls->bins[idx][FREE];
						Block*& gcPtr = tls->bins[idx][GC];
		                
						if( block == block->next )
						{
							CL_DbgAssert( startPtr == block && freePtr == block && gcPtr == block );
							startPtr = freePtr = gcPtr = 0;
						}
						else
						{
							if( freePtr == block )
								freePtr = block->next;
							if( gcPtr == block )
								gcPtr = block->next;
							if( startPtr == block )
								startPtr = block->next;
							block->prev->next = block->next;
							block->next->prev = block->prev;
						}
						mallocPool.free(block);
						checkList(tls, idx);
						return;
					}

					tls->moveBlockToFreeList(block);
				}
				node->next = block->privateFreeList;
				block->privateFreeList = node;
			}
			else
			{
				AutoLock lock(block->cs);
				SANITY_CHECK(block);

				node->next = block->publicFreeList;
				block->publicFreeList = node;
				if( block->threadData == 0 )
				{
					// take ownership of the abandoned block.
					// note that it can happen at the same time as
					// ThreadData::deleteData() marks the blocks as abandoned,
					// so this part of the algorithm needs to be checked for data races
					int idx = block->binIdx;
					block->threadData = tls;
					Block*& startPtr = tls->bins[idx][START];

					if( startPtr )
					{
						block->next = startPtr;
						block->prev = startPtr->prev;
						block->next->prev = block->prev->next = block;
					}
					else
						startPtr = tls->bins[idx][FREE] = tls->bins[idx][GC] = block;
				}
			}
			}
		}

		#endif
	};


	/*!
	  The STL-compilant memory Allocator based on CmnLib::fastMalloc() and CmnLib::fastFree()
	*/
	template<typename _Tp> class CL_EXPORTS Allocator
	{
	public:
		typedef _Tp value_type;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		template<typename U> class rebind { typedef Allocator<U> other; };

		explicit Allocator() {}
		~Allocator() {}
		explicit Allocator(Allocator const&) {}
		template<typename U>
		explicit Allocator(Allocator<U> const&) {}

		// address
		pointer address(reference r) { return &r; }
		const_pointer address(const_reference r) { return &r; }

		pointer allocate(size_type count, const void* = 0)
		{
			return reinterpret_cast<pointer>(MemoryFoundations::fastMalloc(count * sizeof(_Tp)));
		}

		void deallocate(pointer p, size_type) { fastFree(p); }

		size_type max_size() const
		{
			return max(static_cast<_Tp>(-1) / sizeof(_Tp), 1);
		}

		void construct(pointer p, const _Tp& v) { new(static_cast<void*>(p)) _Tp(v); }
		void destroy(pointer p) { p->~_Tp(); }
	};



}	// namespace core
}	// namespace CmnLib



#endif	/* CMNLIB_CMNLIBCORE_FOUNDATIONSMEMORY_HPP__ */
