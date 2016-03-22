/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Base\Allocator.h

							Describe:	内存池分配器，和 VC.net 2003 的 STL Alloc 兼容

							Author:		赵洪松(xueren)

							CreateTime: 2003.04.18
							UpdateTime:
*/

#ifndef _ZEPHYR_3_BASE_ALLOCATOR_H
#define _ZEPHYR_3_BASE_ALLOCATOR_H

//#include <xmemory>
#include <map>

#include <Base\List.h>

namespace Zephyr3{

	///////////////////////////////////////////////////////////////////////////////////////////
	// _SafeAllocator
	// 安全的内存分配器，记录所有的分配结果，并于析构时释放掉，没有内存释放接口
	// 主要用于Zephyr3内部数据结构

	inline LPVOID _Alloc(unsigned int size) {
		return malloc(size);
	}

	template<class T>
	inline T* _AllocObject(unsigned int size) {
		return malloc(size * sizeof(T));
	}

	inline LPVOID _Realloc(LPVOID pDat,unsigned int size) {
		return realloc(pDat,size);
	}

	template<class T>
	inline T* _ReallocObject(T* pDat,unsigned int oldSize,unsigned int size) {
		ZASSERT(size != 0);
		ZASSERT(oldSize != size);

		T* pTmp = _AllocObject<T>(size);
		if(pDat != NULL)
		{
			for(int i = 0; i < oldSize; ++i)
				pTmp[i] = pDat[i];
		}
		else
			return pTmp;
	}

	inline void _SafeFree(LPVOID& pDat) {
		free(pDat);

		pDat = NULL;
	}

	inline void _Free(LPVOID pDat) {
		free(pDat);
	}
/*
	template<class T>
		T* _Construct(T* 
*/
/*
	class _Malloc_Allocator{
	public:
		static LPVOID Alloc(unsigned int size) {
			return malloc(size);
		}

		static void Free(LPVOID& pDat) {
			free(pDat);

			pDat = NULL;
		}

		static LPVOID Realloc(LPVOID pDat,unsigned int size) {
			return realloc(pDat,size);
		}
	};
*/
	template<class T,class TYPE_TRAITS>
	class _Allocator{
	public:
		typedef typename TYPE_TRAITS::_PointerType	_PointerType;
		typedef typename TYPE_TRAITS::_ValueType	_ValueType;

		typedef typename TYPE_TRAITS	_TypeTraits;
	public:
		_PointerType Alloc() {
			return Alloc(_TypeTraits::_Constructor());
		}

		_PointerType Construct(LPVOID pDat) {
			return Construct(pDat,_TypeTraits::_Constructor());
		}

		void Destroy(_PointerType& pDat) {
			Destroy(pDat,_TypeTraits::_Destructor);
		}

		void Destruct(_PointerType& pDat) {
			Destruct(pDat,_TypeTraits::_Destructor);
		}
	private:
		// 执行构造函数
		_PointerType Alloc(Int2Type<true>) {
			_PointerType tmp = (_PointerType)_Alloc(sizeof(ValueType));

			ZASSERT_R(tmp != NULL);

			return new(tmp) T;
		}

		// 不执行构造函数
		_PointerType Alloc(Int2Type<false>) {
			return (_PointerType)_Alloc(sizeof(_ValueType));
		}

		// 执行构造函数
		_PointerType Construct(LPVOID pDat,Int2Type<true>) {
			ZASSERT(pDat != NULL);

			return new(pDat) T;
		}

		// 不执行构造函数
		_PointerType Construct(LPVOID pDat,Int2Type<false>) {
			return (_PointerType)pDat;
		}

		// 执行析构函数
		void Destroy(_PointerType& pDat,Int2Type<true>) {
			pDat->~T();

			_Free(pDat);
		}

		// 不执行析构函数
		void Destroy(_PointerType& pDat,Int2Type<false>) {
			_Free(pDat);
		}

		// 执行析构函数
		void Destruct(_PointerType& pDat,Int2Type<true>) {
			pDat->~T();
		}

		// 不执行析构函数
		void Destruct(_PointerType& pDat,Int2Type<false>) {
		}
	};
/*
	template<class ALLOCATOR,class T>
	class _SafeAllocator : public _ObjAllocator<ALLOCATOR,T> {
	public:
		typedef std::vector<LPVOID> Array;
	public:
		_SafeAllocator() {}
		~_SafeAllocator() { Release(); }

		// 内存分配
		// size 为字节大小
		LPVOID Alloc(unsigned int size) {
			LPVOID tmp = ALLOCATOR::Alloc(size);

			m_memory.push_back(tmp);

			return tmp;
		}

		// 对象内存分配
		// nums 为需要分配的对象数量
		PointerType AllocObj() {
			LPVOID tmp = _ObjAllocator::AllocObj();

			m_memory.push_back(tmp);

			return (PointerType)tmp;
		}
	private:
		// -----------------------------------------------
		// 禁止 = 

		_SafeAllocator(_SafeAllocator& src) {}
		_SafeAllocator& operator = (_SafeAllocator& src) { return *this; }
	private:
		// 内存释放
		void Release() {
			for(Array::size_type i = 0; i < m_memory.size(); i++)
			{
				if(m_memory[i] != NULL)
					free(m_memory[i]);
			}

			m_memory.clear();
		}
	private:
		Array		m_memory;
	};
*/

/*
	//////////////////////////////////////////////////////////////////////////////////////
	// 内存池，线程安全

	// 支持数组的内存分配，但效率上不如单体内存分配，如果确定要分配 int[100]，
	// 最好将 int[100]封装成struct，来单体分配，会更高效

	class ZEPHYR_3_API MemoryPool{
	public:
		struct Node{
			void*			prt;
			unsigned int	nums;
		};

		typedef Node* LPNode;

		typedef Link<Node, 128, 64>	List;

		struct MapData{
			LockImp			lock;
			List			list;
		};

		typedef std::map<_SIZE,MapData>	Map;
	public:
		// 分配空间
		void* Alloc(_SIZE size, unsigned int pool_size) {
			return Alloc(m_map[size], size, pool_size);
		}

		// 分配空间
		void* Alloc(MapData& dat, _SIZE size, unsigned int pool_size) {

			AutoLockEx lock(dat.lock);

			if(dat.list.GetUsed() > 0)
			{
				void* t = dat.list.GetHeadNode()->obj.prt;
				ZASSERT(dat.list.GetHeadNode()->obj.nums > 0);

				if(dat.list.GetHeadNode()->obj.nums > 1)
				{
					dat.list.GetHeadNode()->obj.nums--;

					return (void*)((BYTE*)t + dat.list.GetHeadNode()->obj.nums * size);
				}
				else
					dat.list.DelNext(NULL);

				return t;
			}

			LPNode pNode = dat.list.Add();
			ZASSERT(pNode != NULL);

			pNode->nums = pool_size - 1;

			pNode->prt = malloc(pool_size * size);
			ZASSERT_RET_V(pNode->prt != NULL, NULL);

			return (void*)((BYTE*)pNode->prt + dat.list.GetHeadNode()->obj.nums * size);
		}

		// 释放回内存池
		void Dealloc(_SIZE size, unsigned int pool_size, void* ptr) {
			Free(m_map[size], size, pool_size, ptr);
		}

		// 释放
		void Dealloc(MapData& dat, _SIZE size, unsigned int pool_size, void* ptr) {

			ZASSERT(ptr != NULL);

			AutoLockEx lock(dat.lock);

			LPNode pNode = dat.list.Add();
			ZASSERT(pNode != NULL);

			pNode->nums = 1;

			pNode->prt = ptr;
		}
	private:
		Map		m_map;
	};
*/

/*
	/////////////////////////////////////////////////////////////////////////////////////////
	// 内存分配器

	template<class T, unsigned int POOL_SIZE, unsigned int OBJ_SIZE = sizeof(T)>
	class Allocator : public std::_Allocator_base<T>{
	public:
		typedef std::_Allocator_base<T> _Mybase;
		typedef typename _Mybase::value_type value_type;

		typedef value_type _FARQ *pointer;
		typedef value_type _FARQ& reference;
		typedef const value_type _FARQ *const_pointer;
		typedef const value_type _FARQ& const_reference;

		typedef _SIZT size_type;
		typedef _PDFT difference_type;

		template<class OTHER>
		struct rebind{
			typedef Allocator<OTHER, POOL_SIZE, sizeof(OTHER)> other;
		};

	public:
		pointer address(reference val) const {
			return (&val);
		}

		const_pointer address(const_reference val) const {
			return (&val);
		}

		Allocator() {
		}

		Allocator(const allocator<T, POOL_SIZE, OBJ_SIZE>&) {
		}

		template<class OTHER>
		Allocator(const Allocator<OTHER, POOL_SIZE, sizeof(OTHER)>&) {
		}

		template<class OTHER>
		Allocator<T, POOL_SIZE, OBJ_SIZE>& operator=(const Allocator<OTHER, POOL_SIZE, sizeof(OTHER)>&) {
			return (*this);
		}

		void deallocate(pointer ptr, size_type) {
			operator delete(ptr);
		}

		pointer allocate(size_type count) {
			return (_Allocate(count, (pointer)0));
		}

		pointer allocate(size_type count, const void _FARQ *) {
			return (allocate(count));
		}

		void construct(pointer ptr, const T& val) {
			_Construct(ptr, val);
		}

		void destroy(pointer ptr) {
			_Destroy(ptr);
		}

		_SIZT max_size() const {
			_SIZT count = (_SIZT)(-1) / sizeof (_Ty);
			return (0 < count ? count : 1);
		}
	};
*/
};

#endif // _ZEPHYR_3_BASE_ALLOCATOR_H