/**
* @file foundations_memory.cpp
* @brief Body to the related classes.
*
* @section LICENSE
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED.IN NO EVENT SHALL THE AUTHOR / AUTHORS BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
* THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* @author  Alessandro Moro <alessandromoro.italy@gmail.com>
* @bug No known bugs.
* @version 1.0.1.0
*
*/


#include "../inc/cmnlibcore/foundations_memory.hpp"

#ifndef CL_MEMORY_MANAGER


#else


//----------------------------------------------------------------------------
void* operator new (size_t uiSize)
{
	return Memory::getSingletonPtr()->Allocate(uiSize, 0, 0, false);
}
//----------------------------------------------------------------------------
void* operator new[](size_t uiSize)
{
	return Memory::getSingletonPtr()->Allocate(uiSize, 0, 0, true);
}
//----------------------------------------------------------------------------
void* operator new (size_t uiSize, const char* acFile, unsigned int uiLine)
{
	return Memory::getSingletonPtr()->Allocate(uiSize, acFile, uiLine, false);
}
//----------------------------------------------------------------------------
void* operator new[](size_t uiSize, const char* acFile, unsigned int uiLine)
{
	return Memory::getSingletonPtr()->Allocate(uiSize, acFile, uiLine, true);
}
//----------------------------------------------------------------------------
void operator delete (void* pvAddr)
{
	Memory::getSingletonPtr()->Deallocate((char*)pvAddr, false);
}
//----------------------------------------------------------------------------
void operator delete[](void* pvAddr)
{
	Memory::getSingletonPtr()->Deallocate((char*)pvAddr, true);
}
//----------------------------------------------------------------------------
void operator delete (void* pvAddr, char*, unsigned int)
{
	Memory::getSingletonPtr()->Deallocate((char*)pvAddr, false);
}
//----------------------------------------------------------------------------
void operator delete[](void* pvAddr, char*, unsigned int)
{
	Memory::getSingletonPtr()->Deallocate((char*)pvAddr, true);
}
//----------------------------------------------------------------------------


//--------------------------------------------------------------------------
Memory* Memory::getSingletonPtr(void)
{
	return ms_Singleton;
}
//--------------------------------------------------------------------------
Memory& Memory::getSingleton(void)
{  
	return *ms_Singleton;
}
//--------------------------------------------------------------------------
MemoryLeakTrackerC* MemoryLeakTrackerC::getSingletonPtr(void)
{
	return ms_Singleton;
}
//--------------------------------------------------------------------------
MemoryLeakTrackerC& MemoryLeakTrackerC::getSingleton(void)
{  
	return *ms_Singleton;
}

#endif	// endif #define CL_MEMORY_MANAGER
