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

#ifndef CMNLIB_CMNLIBCORE_SINGLETON_HPP__
#define CMNLIB_CMNLIBCORE_SINGLETON_HPP__

namespace CmnLib
{
namespace core
{

	/****************************************************************************************\
	*                                  Singleton instance	                                 *
	\****************************************************************************************/

	/* Original version Copyright (C) Scott Bilas, 2000.
		* All rights reserved worldwide.
		*
		* This software is provided "as is" without express or implied
		* warranties. You may freely copy and compile this source into
		* applications you distribute provided that the copyright text
		* below is included in the resulting source code, for example:
		* "Portions Copyright (C) Scott Bilas, 2000"
		*/
	/** Template class for creating single-instance global classes.
	*/
	template <typename T> 
	class Singleton
	{
	protected:

		static T* ms_Singleton;

	public:
		Singleton( void )
		{
			assert( !ms_Singleton );
	#if defined( _MSC_VER ) && _MSC_VER < 1200	 
			int offset = (int)(T*)1 - (int)(Singleton <T>*)(T*)1;
			ms_Singleton = (T*)((int)this + offset);
	#else
		ms_Singleton = static_cast< T* >( this );
	#endif
		}
		~Singleton( void )
			{  assert( ms_Singleton );  ms_Singleton = 0;  }
		static T& getSingleton( void )
		{	assert( ms_Singleton );  return ( *ms_Singleton ); }
		static T* getSingletonPtr( void )
		{ return ms_Singleton; }
	};

}

}	// end namespace CmnLib


#endif /* CMNLIB_CMNLIBCORE_SINGLETON_HPP__ */
