#ifndef __Dominus_MemoryUtils_h__
#define __Dominus_MemoryUtils_h__

template<typename T, typename ...Args>
std::unique_ptr<T> make_unique( Args&& ...args ) {
    return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
}

#endif /* _MEMORY_UTILS_H_ */
