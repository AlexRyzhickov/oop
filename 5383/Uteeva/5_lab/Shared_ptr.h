﻿#pragma once
#ifndef SHAREDPTR_H
#define SHAREDPTR_H
#include <algorithm>
#include <cstddef>
namespace stepik
	{
	template <typename T>
		class shared_ptr
		 {
		template <typename U>
			friend class shared_ptr;
		
			public:
			explicit shared_ptr(T *ptr = 0) :
					m_ptr(ptr), m_count(ptr ? new size_t(1) : nullptr)
					 {
					      // implement this
						}
				
					~shared_ptr()
					 {
					      // implement this
						free();
					}
				
					
					template <typename U>
					shared_ptr(const shared_ptr<U> & other) :
					m_ptr(other.m_ptr), m_count(other.m_count)
					 {
					      // implement this
						if (m_count)
						{
						(*m_count)++;
						}
					}
				
					shared_ptr(const shared_ptr & other) :
					m_ptr(other.m_ptr), m_count(other.m_count)
					 {
					     // implement this
						if (m_count)
						{
						(*m_count)++;
						}
					}
				
				template <typename U>
					shared_ptr& operator=(const shared_ptr<U> & other)
					 {
						shared_ptr tmp(other);
					    this->swap(tmp);
					}
				
					shared_ptr& operator=(const shared_ptr & other)
					 {
						shared_ptr tmp(other);
					    swap(tmp);
						return *this;
					}
				
					template <typename U>
					bool operator > (const shared_ptr<U> &other)
					 {
					if (get()->getId() > other.get()->getId())
						{
						return true;
						}
					else
						 {
						return false;
						}
					}
				
					template <typename U>
					bool operator < (const shared_ptr<U> &other)
					 {
					if (get()->getId() < other.get()->getId())
						{
						return true;
						}
					else
						 {
						return false;
						}
					}
				
					template <typename U>
					bool operator == (const shared_ptr<U> &other) const
					 {
				return (m_ptr == other.m_ptr);
					}
				
					explicit operator bool() const
					 {
					      // implement this
						return (m_ptr != nullptr);
					}
				
					T* get() const
					 {
					     // implement this
						return m_ptr;
					}
				
					long use_count() const
					 {
					      // implement this
						return (m_count ? *m_count : 0);
					}
				
					T& operator*() const
					{
					      // implement this
						return *m_ptr;
					}
				
					T* operator->() const
					 {
					      // implement this
						return m_ptr;
					}
				
					void swap(shared_ptr& x) noexcept
					 {
					      // implement this
						std::swap(this->m_ptr, x.m_ptr);
					std::swap(this->m_count, x.m_count);
					}
				
					void reset(T *ptr = nullptr)
					 {
					      // implement this
						shared_ptr tmp(ptr);
					this->swap(tmp);
					}
				
					private:
						    // data members
							T* m_ptr;
					size_t* m_count;
						
							void free()
							 {
							if (m_ptr)
								{
								(*m_count)--;
								if (*m_count == 0)
									 {
									delete m_ptr;
									delete m_count;
									}
								}
							}
						};
	} // namespace stepik
#endif // SHAREDPTR_H