//
// Created by mike on 1/17/24.
//

#ifndef JAVA_DRAGON_COMP_COMMON_H
#define JAVA_DRAGON_COMP_COMMON_H

#include <memory>
#include <type_traits>

namespace d_common {

	 /**
	  * https://stackoverflow.com/questions/56618230/how-to-require-a-c-template-parameter-to-have-some-methods-with-a-given-signat
	  * @tparam K
	  */
	 template<class K, typename = typename std::enable_if<
			 std::is_same<decltype(&K::operator()), size_t (K::*)() const>::value>
	 >
	 struct SharedPtrHashFun {
		  size_t operator()(const std::shared_ptr<K>& key) const {
			  return key->operator()();
		  }
	 };

	 template<class K>
	 struct SharedPtrEqualFun {
		  bool operator()(const std::shared_ptr<K>& k1, const std::shared_ptr<K>& k2) const {
			  return *k1.get() == *k2.get();
		  }
	 };
}

#endif //JAVA_DRAGON_COMP_COMMON_H
