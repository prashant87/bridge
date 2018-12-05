
#ifndef __PORTABLE_INSTS_H_
#define __PORTABLE_INSTS_H_


//#include "portable_iarchive.hpp"
//#include "portable_oarchive.hpp"



// if you include this header multiple times and your compiler is picky
// about multiple template instantiations (eg. gcc is) then you need to
// define NO_EXPLICIT_TEMPLATE_INSTANTIATION before every include but one
// or you move the instantiation section into an implementation file
#ifndef NO_EXPLICIT_TEMPLATE_INSTANTIATION_O
#define NO_EXPLICIT_TEMPLATE_INSTANTIATION_O

#include <boost/archive/impl/basic_binary_oarchive.ipp>
#include <boost/archive/impl/basic_binary_oprimitive.ipp>

#if BOOST_VERSION < 104000
#include <boost/archive/impl/archive_pointer_oserializer.ipp>
#elif !defined BOOST_ARCHIVE_SERIALIZER_INCLUDED
#include <boost/archive/impl/archive_serializer_map.ipp>
#define BOOST_ARCHIVE_SERIALIZER_INCLUDED
#endif

namespace boost { namespace archive {

	// explicitly instantiate for this type of binary stream
	template class basic_binary_oarchive<eos::portable_oarchive>;

	template class basic_binary_oprimitive<
		eos::portable_oarchive
	#if BOOST_VERSION < 103400
		, std::ostream
	#else
		, std::ostream::char_type
		, std::ostream::traits_type
	#endif
	>;

#if BOOST_VERSION < 104000
	template class detail::archive_pointer_oserializer<eos::portable_oarchive>;
#else
	template class detail::archive_serializer_map<eos::portable_oarchive>;
	//template class detail::archive_serializer_map<eos::polymorphic_portable_oarchive>;
#endif

} } // namespace boost::archive

#endif





// if you include this header multiple times and your compiler is picky
// about multiple template instantiations (eg. gcc is) then you need to
// define NO_EXPLICIT_TEMPLATE_INSTANTIATION before every include but one
// or you move the instantiation section into an implementation file
#ifndef NO_EXPLICIT_TEMPLATE_INSTANTIATION_I
#define NO_EXPLICIT_TEMPLATE_INSTANTIATION_I

#include <boost/archive/impl/basic_binary_iarchive.ipp>
#include <boost/archive/impl/basic_binary_iprimitive.ipp>

#if BOOST_VERSION < 104000
#include <boost/archive/impl/archive_pointer_iserializer.ipp>
#elif !defined BOOST_ARCHIVE_SERIALIZER_INCLUDED
#include <boost/archive/impl/archive_serializer_map.ipp>
#define BOOST_ARCHIVE_SERIALIZER_INCLUDED
#endif

namespace boost { namespace archive {

	// explicitly instantiate for this type of binary stream
	template class basic_binary_iarchive<eos::portable_iarchive>;

	template class basic_binary_iprimitive<
		eos::portable_iarchive
	#if BOOST_VERSION < 103400
		, std::istream
	#else
		, std::istream::char_type
		, std::istream::traits_type
	#endif
	>;

#if BOOST_VERSION < 104000
	template class detail::archive_pointer_iserializer<eos::portable_iarchive>;
#else
	template class detail::archive_serializer_map<eos::portable_iarchive>;
	//template class detail::archive_serializer_map<eos::polymorphic_portable_iarchive>;
#endif

} } // namespace boost::archive

#endif















#endif






