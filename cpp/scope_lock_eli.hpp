/*******************************************************************************
	Edited by: Eli Vaserman.
	Date created: 06.02.2018.
	Name: scope_lock_eli.hpp
*******************************************************************************/

namespace ilrd
{

template <class T, void(T::*lock)(),void(T::*unlock)()>
class ScopeLock
{
public:
	ScopeLock(T *pm);
	~ScopeLock();

private:

	T *m_locker_ptr;

	//blocked by design
	ScopeLock(const ScopeLock& other);
	ScopeLock& operator = (const ScopeLock& other);
};

template <class T, void(T::*lock)(),void(T::*unlock)()>
inline ScopeLock<T, lock, unlock>::ScopeLock(T *pm):m_locker_ptr(pm)
{
	(m_locker_ptr->*lock)();
}

template <class T, void(T::*lock)(),void(T::*unlock)()>
inline ScopeLock<T, lock, unlock>::~ScopeLock()
{
	(m_locker_ptr->*unlock)();
}
} //namespace ilrd
