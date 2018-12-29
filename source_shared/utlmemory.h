#ifndef UTLMEMORY_H
#define UTLMEMORY_H

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define UTLMEMORY_TRACK_ALLOC()
#define UTLMEMORY_TRACK_FREE()
#define MEM_ALLOC_CREDIT_CLASS()
#define COMPILE_TIME_ASSERT(a)
#ifndef _WIN32
#define _aligned_malloc(a, b) aligned_alloc(b, a)
#define _stricmp(a, b) strcasecmp(a, b)
#endif

#ifdef __APPLE__
#undef _aligned_malloc
#define _aligned_malloc(x,y) malloc(x)
#endif

template< class T, class I = int >
class CUtlMemory
{
  public:
	// constructor, destructor
	CUtlMemory(int nGrowSize = 0, int nInitSize = 0);
	CUtlMemory(T* pMemory, int numElements);
	CUtlMemory(const T* pMemory, int numElements);
	~CUtlMemory();

	// Set the size by which the memory grows
	void Init(int nGrowSize = 0, int nInitSize = 0);

	class Iterator_t
	{
	  public:
		Iterator_t(I i) : index(i) {}
		I index;

		bool operator==(const Iterator_t it) const { return index == it.index; }
		bool operator!=(const Iterator_t it) const { return index != it.index; }
	};
	Iterator_t First() const { return Iterator_t(IsIdxValid(0) ? 0 : InvalidIndex()); }
	Iterator_t Next(const Iterator_t &it) const { return Iterator_t(IsIdxValid(it.index + 1) ? it.index + 1 : InvalidIndex()); }
	I GetIndex(const Iterator_t &it) const { return it.index; }
	bool IsIdxAfter(I i, const Iterator_t &it) const { return i > it.index; }
	bool IsValidIterator(const Iterator_t &it) const { return IsIdxValid(it.index); }
	Iterator_t InvalidIterator() const { return Iterator_t(InvalidIndex()); }

	// element access
	T& operator[](I i);
	const T& operator[](I i) const;
	T& Element(I i);
	const T& Element(I i) const;

	bool IsIdxValid(I i) const;

	static const I INVALID_INDEX = (I)-1; // For use with COMPILE_TIME_ASSERT
	static I InvalidIndex() { return INVALID_INDEX; }

	T* Base();
	const T* Base() const;

	void SetExternalBuffer(T* pMemory, int numElements);
	void SetExternalBuffer(const T* pMemory, int numElements);
	void AssumeMemory(T *pMemory, int nSize);
	T* Detach();
	void *DetachMemory();

	void Swap(CUtlMemory< T, I > &mem);
	void ConvertToGrowableMemory(int nGrowSize);
	int NumAllocated() const;
	int Count() const;
	void Grow(int num = 1);
	void EnsureCapacity(int num);
	void Purge();
	void Purge(int numElements);
	bool IsExternallyAllocated() const;
	bool IsReadOnly() const;
	void SetGrowSize(int size);

	void ValidateGrowSize()
	{

	}

	enum
	{
		EXTERNAL_BUFFER_MARKER = -1,
		EXTERNAL_CONST_BUFFER_MARKER = -2,
	};

	T* memory;
	int allocationCount;
	int growSize;
};

//-----------------------------------------------------------------------------
// constructor, destructor
//-----------------------------------------------------------------------------

template< class T, class I >
CUtlMemory<T, I>::CUtlMemory(int nGrowSize, int nInitAllocationCount) : memory(0),
																		allocationCount(nInitAllocationCount), growSize(nGrowSize)
{
	ValidateGrowSize();
	assert(nGrowSize >= 0);
	if(allocationCount) {
		memory = (T*)new unsigned char[allocationCount * sizeof(T)];
		//memory = (T*)malloc(allocationCount * sizeof(T));
	}
}

template< class T, class I >
CUtlMemory<T, I>::CUtlMemory(T* pMemory, int numElements) : memory(pMemory),
															allocationCount(numElements)
{
	// Special marker indicating externally supplied modifyable memory
	growSize = EXTERNAL_BUFFER_MARKER;
}

template< class T, class I >
CUtlMemory<T, I>::CUtlMemory(const T* pMemory, int numElements) : memory((T*)pMemory),
																  allocationCount(numElements)
{
	// Special marker indicating externally supplied modifyable memory
	growSize = EXTERNAL_CONST_BUFFER_MARKER;
}

template< class T, class I >
CUtlMemory<T, I>::~CUtlMemory()
{
	Purge();
}

template< class T, class I >
void CUtlMemory<T, I>::Init(int nGrowSize /*= 0*/, int nInitSize /*= 0*/)
{
	Purge();

	growSize = nGrowSize;
	allocationCount = nInitSize;
	ValidateGrowSize();
	assert(nGrowSize >= 0);
	if(allocationCount) {
		UTLMEMORY_TRACK_ALLOC();
		MEM_ALLOC_CREDIT_CLASS();
		memory = (T*)malloc(allocationCount * sizeof(T));
	}
}

//-----------------------------------------------------------------------------
// Fast swap
//-----------------------------------------------------------------------------
template< class T, class I >
void CUtlMemory<T, I>::Swap(CUtlMemory<T, I> &mem)
{
	std::swap(growSize, mem.growSize);
	std::swap(memory, mem.memory);
	std::swap(allocationCount, mem.allocationCount);
}


//-----------------------------------------------------------------------------
// Switches the buffer from an external memory buffer to a reallocatable buffer
//-----------------------------------------------------------------------------
template< class T, class I >
void CUtlMemory<T, I>::ConvertToGrowableMemory(int nGrowSize)
{
	if(!IsExternallyAllocated())
		return;

	growSize = nGrowSize;
	if(allocationCount) {
		int nNumBytes = allocationCount * sizeof(T);
		T *pMemory = (T*)malloc(nNumBytes);
		memcpy(pMemory, memory, nNumBytes);
		memory = pMemory;
	} else {
		memory = NULL;
	}
}


//-----------------------------------------------------------------------------
// Attaches the buffer to external memory....
//-----------------------------------------------------------------------------
template< class T, class I >
void CUtlMemory<T, I>::SetExternalBuffer(T* pMemory, int numElements)
{
	// Blow away any existing allocated memory
	Purge();

	memory = pMemory;
	allocationCount = numElements;

	// Indicate that we don't own the memory
	growSize = EXTERNAL_BUFFER_MARKER;
}

template< class T, class I >
void CUtlMemory<T, I>::SetExternalBuffer(const T* pMemory, int numElements)
{
	// Blow away any existing allocated memory
	Purge();

	memory = const_cast<T*>(pMemory);
	allocationCount = numElements;

	// Indicate that we don't own the memory
	growSize = EXTERNAL_CONST_BUFFER_MARKER;
}

template< class T, class I >
void CUtlMemory<T, I>::AssumeMemory(T* pMemory, int numElements)
{
	// Blow away any existing allocated memory
	Purge();

	// Simply take the pointer but don't mark us as external
	memory = pMemory;
	allocationCount = numElements;
}

template< class T, class I >
void *CUtlMemory<T, I>::DetachMemory()
{
	if(IsExternallyAllocated())
		return NULL;

	void *pMemory = memory;
	memory = 0;
	allocationCount = 0;
	return pMemory;
}

template< class T, class I >
inline T* CUtlMemory<T, I>::Detach()
{
	return (T*)DetachMemory();
}


//-----------------------------------------------------------------------------
// element access
//-----------------------------------------------------------------------------
template< class T, class I >
inline T& CUtlMemory<T, I>::operator[](I i)
{
	assert(!IsReadOnly());
	assert(IsIdxValid(i));
	return memory[i];
}

template< class T, class I >
inline const T& CUtlMemory<T, I>::operator[](I i) const
{
	assert(IsIdxValid(i));
	return memory[i];
}

template< class T, class I >
inline T& CUtlMemory<T, I>::Element(I i)
{
	assert(!IsReadOnly());
	assert(IsIdxValid(i));
	return memory[i];
}

template< class T, class I >
inline const T& CUtlMemory<T, I>::Element(I i) const
{
	assert(IsIdxValid(i));
	return memory[i];
}


//-----------------------------------------------------------------------------
// is the memory externally allocated?
//-----------------------------------------------------------------------------
template< class T, class I >
bool CUtlMemory<T, I>::IsExternallyAllocated() const
{
	return (growSize < 0);
}


//-----------------------------------------------------------------------------
// is the memory read only?
//-----------------------------------------------------------------------------
template< class T, class I >
bool CUtlMemory<T, I>::IsReadOnly() const
{
	return (growSize == EXTERNAL_CONST_BUFFER_MARKER);
}


template< class T, class I >
void CUtlMemory<T, I>::SetGrowSize(int nSize)
{
	assert(!IsExternallyAllocated());
	assert(nSize >= 0);
	growSize = nSize;
	ValidateGrowSize();
}


//-----------------------------------------------------------------------------
// Gets the base address (can change when adding elements!)
//-----------------------------------------------------------------------------
template< class T, class I >
inline T* CUtlMemory<T, I>::Base()
{
	assert(!IsReadOnly());
	return memory;
}

template< class T, class I >
inline const T *CUtlMemory<T, I>::Base() const
{
	return memory;
}


//-----------------------------------------------------------------------------
// Size
//-----------------------------------------------------------------------------
template< class T, class I >
inline int CUtlMemory<T, I>::NumAllocated() const
{
	return allocationCount;
}

template< class T, class I >
inline int CUtlMemory<T, I>::Count() const
{
	return allocationCount;
}


//-----------------------------------------------------------------------------
// Is element index valid?
//-----------------------------------------------------------------------------
template< class T, class I >
inline bool CUtlMemory<T, I>::IsIdxValid(I i) const
{
	// GCC warns if I is an unsigned type and we do a ">= 0" against it (since the comparison is always 0).
	// We Get the warning even if we cast inside the expression. It only goes away if we assign to another variable.
	long x = i;
	return (x >= 0) && (x < allocationCount);
}

//-----------------------------------------------------------------------------
// Grows the memory
//-----------------------------------------------------------------------------
inline int UtlMemory_CalcNewAllocationCount(int nAllocationCount, int nGrowSize, int nNewSize, int nBytesItem)
{
	if(nGrowSize) {
		nAllocationCount = ((1 + ((nNewSize - 1) / nGrowSize)) * nGrowSize);
	} else {
		if(!nAllocationCount) {
			// Compute an allocation which is at least as big as a cache line...
			nAllocationCount = (31 + nBytesItem) / nBytesItem;
		}

		while(nAllocationCount < nNewSize) {
#ifndef _X360
			nAllocationCount *= 2;
#else
			int nNewAllocationCount = (nAllocationCount * 9) / 8; // 12.5 %
			if(nNewAllocationCount > nAllocationCount)
				nAllocationCount = nNewAllocationCount;
			else
				nAllocationCount *= 2;
#endif
		}
	}

	return nAllocationCount;
}

template< class T, class I >
void CUtlMemory<T, I>::Grow(int num)
{
	assert(num > 0);

	if(IsExternallyAllocated()) {
		// Can't grow a buffer whose memory was externally allocated 
		assert(0);
		return;
	}


	auto oldAllocationCount = allocationCount;
	// Make sure we have at least numallocated + num allocations.
	// Use the grow rules specified for this memory (in growSize)
	int nAllocationRequested = allocationCount + num;

	int nNewAllocationCount = UtlMemory_CalcNewAllocationCount(allocationCount, growSize, nAllocationRequested, sizeof(T));

	// if allocationRequested wraps index type I, recalculate
	if((int)(I)nNewAllocationCount < nAllocationRequested) {
		if((int)(I)nNewAllocationCount == 0 && (int)(I)(nNewAllocationCount - 1) >= nAllocationRequested) {
			--nNewAllocationCount; // deal w/ the common case of allocationCount == MAX_USHORT + 1
		} else {
			if((int)(I)nAllocationRequested != nAllocationRequested) {
				// we've been asked to grow memory to a size s.t. the index type can't address the requested amount of memory
				assert(0);
				return;
			}
			while((int)(I)nNewAllocationCount < nAllocationRequested) {
				nNewAllocationCount = (nNewAllocationCount + nAllocationRequested) / 2;
			}
		}
	}

	allocationCount = nNewAllocationCount;

	if(memory) {
		auto ptr = new unsigned char[allocationCount * sizeof(T)];

		memcpy(ptr, memory, oldAllocationCount * sizeof(T));
		memory = (T*)ptr;
	} else {
		memory = (T*)new unsigned char[allocationCount * sizeof(T)];
	}
}


//-----------------------------------------------------------------------------
// Makes sure we've got at least this much memory
//-----------------------------------------------------------------------------
template< class T, class I >
inline void CUtlMemory<T, I>::EnsureCapacity(int num)
{
	if(allocationCount >= num)
		return;

	if(IsExternallyAllocated()) {
		// Can't grow a buffer whose memory was externally allocated 
		assert(0);
		return;
	}
	allocationCount = num;

	if(memory) {
		memory = (T*)realloc(memory, allocationCount * sizeof(T));
	} else {
		memory = (T*)malloc(allocationCount * sizeof(T));
	}
}


//-----------------------------------------------------------------------------
// Memory deallocation
//-----------------------------------------------------------------------------
template< class T, class I >
void CUtlMemory<T, I>::Purge()
{
	if(!IsExternallyAllocated()) {
		if(memory) {
			free((void*)memory);
			memory = 0;
		}
		allocationCount = 0;
	}
}

template< class T, class I >
void CUtlMemory<T, I>::Purge(int numElements)
{
	assert(numElements >= 0);

	if(numElements > allocationCount) {
		// Ensure this isn't a grow request in disguise.
		assert(numElements <= allocationCount);
		return;
	}

	// If we have zero elements, simply do a purge:
	if(numElements == 0) {
		Purge();
		return;
	}

	if(IsExternallyAllocated()) {
		// Can't shrink a buffer whose memory was externally allocated, fail silently like purge 
		return;
	}

	// If the number of elements is the same as the allocation count, we are done.
	if(numElements == allocationCount) {
		return;
	}


	if(!memory) {
		// Allocation count is non zero, but memory is null.
		assert(memory);
		return;
	}
	allocationCount = numElements;
	memory = (T*)realloc(memory, allocationCount * sizeof(T));
}

//-----------------------------------------------------------------------------
// The CUtlMemory class:
// A growable memory class which doubles in size by default.
//-----------------------------------------------------------------------------
template< class T, int nAlignment >
class CUtlMemoryAligned : public CUtlMemory<T>
{
  public:
	// constructor, destructor
	CUtlMemoryAligned(int nGrowSize = 0, int nInitSize = 0);
	CUtlMemoryAligned(T* pMemory, int numElements);
	CUtlMemoryAligned(const T* pMemory, int numElements);
	~CUtlMemoryAligned();

	// Attaches the buffer to external memory....
	void SetExternalBuffer(T* pMemory, int numElements);
	void SetExternalBuffer(const T* pMemory, int numElements);

	// Grows the memory, so that at least allocated + num elements are allocated
	void Grow(int num = 1);

	// Makes sure we've got at least this much memory
	void EnsureCapacity(int num);

	// Memory deallocation
	void Purge();

	// Purge all but the given number of elements (NOT IMPLEMENTED IN CUtlMemoryAligned)
	void Purge(int numElements) { assert(0); }

  private:
	void *Align(const void *pAddr);
};


//-----------------------------------------------------------------------------
// Aligns a pointer
//-----------------------------------------------------------------------------
template< class T, int nAlignment >
void *CUtlMemoryAligned<T, nAlignment>::Align(const void *pAddr)
{
	size_t nAlignmentMask = nAlignment - 1;
	return (void*)(((size_t)pAddr + nAlignmentMask) & (~nAlignmentMask));
}


//-----------------------------------------------------------------------------
// constructor, destructor
//-----------------------------------------------------------------------------
template< class T, int nAlignment >
CUtlMemoryAligned<T, nAlignment>::CUtlMemoryAligned(int nGrowSize, int nInitAllocationCount)
{
	CUtlMemory<T>::memory = 0;
	CUtlMemory<T>::allocationCount = nInitAllocationCount;
	CUtlMemory<T>::growSize = nGrowSize;
	this->ValidateGrowSize();

	// Alignment must be a power of two
	COMPILE_TIME_ASSERT((nAlignment & (nAlignment - 1)) == 0);
	assert((nGrowSize >= 0) && (nGrowSize != CUtlMemory<T>::EXTERNAL_BUFFER_MARKER));
	if(CUtlMemory<T>::allocationCount) {
		UTLMEMORY_TRACK_ALLOC();
		MEM_ALLOC_CREDIT_CLASS();
		CUtlMemory<T>::memory = (T*)_aligned_malloc(nInitAllocationCount * sizeof(T), nAlignment);
	}
}

template< class T, int nAlignment >
CUtlMemoryAligned<T, nAlignment>::CUtlMemoryAligned(T* pMemory, int numElements)
{
	// Special marker indicating externally supplied memory
	CUtlMemory<T>::growSize = CUtlMemory<T>::EXTERNAL_BUFFER_MARKER;

	CUtlMemory<T>::memory = (T*)Align(pMemory);
	CUtlMemory<T>::allocationCount = ((int)(pMemory + numElements) - (int)CUtlMemory<T>::memory) / sizeof(T);
}

template< class T, int nAlignment >
CUtlMemoryAligned<T, nAlignment>::CUtlMemoryAligned(const T* pMemory, int numElements)
{
	// Special marker indicating externally supplied memory
	CUtlMemory<T>::growSize = CUtlMemory<T>::EXTERNAL_CONST_BUFFER_MARKER;

	CUtlMemory<T>::memory = (T*)Align(pMemory);
	CUtlMemory<T>::allocationCount = ((int)(pMemory + numElements) - (int)CUtlMemory<T>::memory) / sizeof(T);
}

template< class T, int nAlignment >
CUtlMemoryAligned<T, nAlignment>::~CUtlMemoryAligned()
{
	Purge();
}


//-----------------------------------------------------------------------------
// Attaches the buffer to external memory....
//-----------------------------------------------------------------------------
template< class T, int nAlignment >
void CUtlMemoryAligned<T, nAlignment>::SetExternalBuffer(T* pMemory, int numElements)
{
	// Blow away any existing allocated memory
	Purge();

	CUtlMemory<T>::memory = (T*)Align(pMemory);
	CUtlMemory<T>::allocationCount = ((int)(pMemory + numElements) - (int)CUtlMemory<T>::memory) / sizeof(T);

	// Indicate that we don't own the memory
	CUtlMemory<T>::growSize = CUtlMemory<T>::EXTERNAL_BUFFER_MARKER;
}

template< class T, int nAlignment >
void CUtlMemoryAligned<T, nAlignment>::SetExternalBuffer(const T* pMemory, int numElements)
{
	// Blow away any existing allocated memory
	Purge();

	CUtlMemory<T>::memory = (T*)Align(pMemory);
	CUtlMemory<T>::allocationCount = ((int)(pMemory + numElements) - (int)CUtlMemory<T>::memory) / sizeof(T);

	// Indicate that we don't own the memory
	CUtlMemory<T>::growSize = CUtlMemory<T>::EXTERNAL_CONST_BUFFER_MARKER;
}


//-----------------------------------------------------------------------------
// Grows the memory
//-----------------------------------------------------------------------------
template< class T, int nAlignment >
void CUtlMemoryAligned<T, nAlignment>::Grow(int num)
{
	assert(num > 0);

	if(this->IsExternallyAllocated()) {
		// Can't grow a buffer whose memory was externally allocated 
		assert(0);
		return;
	}

	UTLMEMORY_TRACK_FREE();

	// Make sure we have at least numallocated + num allocations.
	// Use the grow rules specified for this memory (in growSize)
	int nAllocationRequested = CUtlMemory<T>::allocationCount + num;

	CUtlMemory<T>::allocationCount = UtlMemory_CalcNewAllocationCount(CUtlMemory<T>::allocationCount, CUtlMemory<T>::growSize, nAllocationRequested, sizeof(T));

	UTLMEMORY_TRACK_ALLOC();

	if(CUtlMemory<T>::memory) {
		MEM_ALLOC_CREDIT_CLASS();
		CUtlMemory<T>::memory = (T*)MemAlloc_ReallocAligned(CUtlMemory<T>::memory, CUtlMemory<T>::allocationCount * sizeof(T), nAlignment);
		assert(CUtlMemory<T>::memory);
	} else {
		MEM_ALLOC_CREDIT_CLASS();
		CUtlMemory<T>::memory = (T*)MemAlloc_AllocAligned(CUtlMemory<T>::allocationCount * sizeof(T), nAlignment);
		assert(CUtlMemory<T>::memory);
	}
}


//-----------------------------------------------------------------------------
// Makes sure we've got at least this much memory
//-----------------------------------------------------------------------------
template< class T, int nAlignment >
inline void CUtlMemoryAligned<T, nAlignment>::EnsureCapacity(int num)
{
	if(CUtlMemory<T>::allocationCount >= num)
		return;

	if(this->IsExternallyAllocated()) {
		// Can't grow a buffer whose memory was externally allocated
		assert(0);
		return;
	}

	UTLMEMORY_TRACK_FREE();

	CUtlMemory<T>::allocationCount = num;

	UTLMEMORY_TRACK_ALLOC();

	if(CUtlMemory<T>::memory) {
		MEM_ALLOC_CREDIT_CLASS();
		CUtlMemory<T>::memory = (T*)MemAlloc_ReallocAligned(CUtlMemory<T>::memory, CUtlMemory<T>::allocationCount * sizeof(T), nAlignment);
	} else {
		MEM_ALLOC_CREDIT_CLASS();
		CUtlMemory<T>::memory = (T*)MemAlloc_AllocAligned(CUtlMemory<T>::allocationCount * sizeof(T), nAlignment);
	}
}


//-----------------------------------------------------------------------------
// Memory deallocation
//-----------------------------------------------------------------------------
template< class T, int nAlignment >
void CUtlMemoryAligned<T, nAlignment>::Purge()
{
	if(!this->IsExternallyAllocated()) {
		if(CUtlMemory<T>::memory) {
			UTLMEMORY_TRACK_FREE();
			MemAlloc_FreeAligned(CUtlMemory<T>::memory);
			CUtlMemory<T>::memory = 0;
		}
		CUtlMemory<T>::allocationCount = 0;
	}
}

#endif
