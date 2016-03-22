// Inc\ZTree.h
// Ê÷
// Write by zhs007			y2k3.7.4

#include <Zephyr.h>

#if _MSC_VER <= 1020
# define TYPENAME
#else
# define TYPENAME typename
#endif

////////////////////////////////////////////////////////////////////////////////////////////////
//	ZTree

const HRESULT	ZTREE_ENUMFINISH	=	0xf0000000;

template<class T, unsigned long SIZE, unsigned long ADD_SIZE>
class ZTree{
public:
	struct _node{
		_node	*next;
		_node	*child;
		T		obj;

		_node() {
			next = child = NULL;
		}
	};
private:
	_node			*m_Root;
	_node			*m_Free;

	unsigned long	m_Used;
	unsigned long	m_Size;
public:
	ZTree();
	~ZTree() { Release(); }

	void Release();

	void SetRoot(T &obj);

	void AddChild(TYPENAME ZTree<T,SIZE,ADD_SIZE>::_node *parent,T &obj);

	void AddBorther(TYPENAME ZTree<T,SIZE,ADD_SIZE>::_node *brother,T &obj);

	TYPENAME ZTree<T,SIZE,ADD_SIZE>::_node *AddChild(TYPENAME ZTree<T,SIZE,ADD_SIZE>::_node *parent);

	TYPENAME ZTree<T,SIZE,ADD_SIZE>::_node *AddBorther(TYPENAME ZTree<T,SIZE,ADD_SIZE>::_node *brother);

	HRESULT EnumChild(TYPENAME ZTree<T,SIZE,ADD_SIZE>::_node *parent,TYPENAME ZTree<T,SIZE,ADD_SIZE>::_node* &child);

	void ClearChildren(TYPENAME ZTree<T,SIZE,ADD_SIZE>::_node *parent);

	void Clear() { ClearChildren(m_Root); }

	unsigned long GetUsed() { return m_Used; }

	TYPENAME ZTree<T,SIZE,ADD_SIZE>::_node *GetRoot() { return m_Root; }
private:
	TYPENAME ZTree<T,SIZE,ADD_SIZE>::_node *Alloc(unsigned long size);

	TYPENAME ZTree<T,SIZE,ADD_SIZE>::_node *GetNode();

	void PutNode(TYPENAME ZTree<T,SIZE,ADD_SIZE>::_node *node);

	TYPENAME ZTree<T,SIZE,ADD_SIZE>::_node *GetLastChild(TYPENAME ZTree<T,SIZE,ADD_SIZE>::_node *parent);

	TYPENAME ZTree<T,SIZE,ADD_SIZE>::_node *GetLastBrother(TYPENAME ZTree<T,SIZE,ADD_SIZE>::_node *brother);
};

template<class T, unsigned long SIZE, unsigned long ADD_SIZE>
ZTree<T,SIZE,ADD_SIZE>::ZTree()
{
	m_Free = Alloc(SIZE);
	m_Size = SIZE;

	m_Root = GetNode();
	m_Used = 1;

	m_Root->next = NULL;
}

template<class T, unsigned long SIZE, unsigned long ADD_SIZE>
TYPENAME ZTree<T,SIZE,ADD_SIZE>::_node *ZTree<T,SIZE,ADD_SIZE>::Alloc(unsigned long size)
{
	ZASSERT(size != 0);

	_node *tmp = NULL;

	tmp = new _node[size];
	assert(tmp);

	_node *node = tmp;

	for(unsigned long i = 1; i < size; i++)
	{
		node->next = &(tmp[i]);

		node = node->next;
	}

	return tmp;
}

template<class T, unsigned long SIZE, unsigned long ADD_SIZE>
void ZTree<T,SIZE,ADD_SIZE>::Release()
{
	m_Root = NULL;
	m_Free = NULL;

	m_Size = 0;
	m_Used = 0;
}

template<class T, unsigned long SIZE, unsigned long ADD_SIZE>
TYPENAME ZTree<T,SIZE,ADD_SIZE>::_node *ZTree<T,SIZE,ADD_SIZE>::GetNode()
{
	_node *tmp = m_Free;

	if(m_Free->next == NULL)
	{
		m_Free = Alloc(ADD_SIZE);

		m_Size += ADD_SIZE;
	}
	else
		m_Free = m_Free->next;

	ZASSERT(tmp->child == NULL);

	m_Used++;

	return tmp;
}

template<class T, unsigned long SIZE, unsigned long ADD_SIZE>
void ZTree<T,SIZE,ADD_SIZE>::PutNode(TYPENAME ZTree<T,SIZE,ADD_SIZE>::_node *node)
{
	ZASSERT(m_Used > 0);

	node->next = m_Free;
	node->child = NULL;

	m_Free = node;

	m_Used--;
}

template<class T, unsigned long SIZE, unsigned long ADD_SIZE>
void ZTree<T,SIZE,ADD_SIZE>::SetRoot(T &obj)
{
	ZASSERT(m_Root != NULL);

	m_Root->obj = obj;
}

template<class T, unsigned long SIZE, unsigned long ADD_SIZE>
void ZTree<T,SIZE,ADD_SIZE>::AddChild(TYPENAME ZTree<T,SIZE,ADD_SIZE>::_node *parent,T &obj)
{
	ZASSERT(parent != NULL);

	if(parent->child != NULL)
	{
		_node *tmp = GetLastChild(parent);
		ZASSERT(tmp != NULL);

		tmp->next = GetNode();

		tmp->next->next = NULL;
		tmp->next->obj = obj;
	}
	else
	{
		parent->child = GetNode();

		parent->child->next = NULL;
		parent->child->obj = obj;
	}
}

template<class T, unsigned long SIZE, unsigned long ADD_SIZE>
HRESULT ZTree<T,SIZE,ADD_SIZE>::EnumChild(TYPENAME ZTree<T,SIZE,ADD_SIZE>::_node *parent,TYPENAME ZTree<T,SIZE,ADD_SIZE>::_node* &child)
{
	ZASSERT(parent != NULL);

	if(child == NULL)
	{
		if(parent->child == NULL)
			return ZTREE_ENUMFINISH;

		child = parent->child;
	}
	else
	{
		if(child->next == NULL)
		{
			child = NULL;

			return ZTREE_ENUMFINISH;
		}

		child = child->next;
	}

	if(child->next == NULL)
		return ZTREE_ENUMFINISH;

	return S_OK;
}

template<class T, unsigned long SIZE, unsigned long ADD_SIZE>
void ZTree<T,SIZE,ADD_SIZE>::AddBorther(TYPENAME ZTree<T,SIZE,ADD_SIZE>::_node *brother,T &obj)
{
	ZASSERT(brother != NULL);

	brother = GetLastBrother(brother);

	brother->next = GetNode();

	brother->next->next = NULL;
	brother->next->obj = obj;
}

template<class T, unsigned long SIZE, unsigned long ADD_SIZE>
TYPENAME ZTree<T,SIZE,ADD_SIZE>::_node *ZTree<T,SIZE,ADD_SIZE>::AddChild(TYPENAME ZTree<T,SIZE,ADD_SIZE>::_node *parent)
{
	ZASSERT(parent != NULL);

	if(parent->child != NULL)
	{
		_node *tmp = GetLastChild(parent);
		ZASSERT(tmp != NULL);

		tmp->next = GetNode();

		tmp->next->next = NULL;

		return tmp->next;
	}
	else
	{
		parent->child = GetNode();

		parent->child->next = NULL;

		return parent->child;
	}
}

template<class T, unsigned long SIZE, unsigned long ADD_SIZE>
TYPENAME ZTree<T,SIZE,ADD_SIZE>::_node *ZTree<T,SIZE,ADD_SIZE>::AddBorther(TYPENAME ZTree<T,SIZE,ADD_SIZE>::_node *brother)
{
	ZASSERT(brother != NULL);

	brother = GetLastBrother(brother);

	brother->next = GetNode();

	brother->next->next = NULL;

	return brother->next;
}

template<class T, unsigned long SIZE, unsigned long ADD_SIZE>
TYPENAME ZTree<T,SIZE,ADD_SIZE>::_node *ZTree<T,SIZE,ADD_SIZE>::GetLastChild(TYPENAME ZTree<T,SIZE,ADD_SIZE>::_node *parent)
{
	ZASSERT(parent != NULL);

	ZASSERT(parent->child != NULL);

	_node *tmp = NULL;
		
	do{
		if(EnumChild(parent,tmp) == ZTREE_ENUMFINISH)
			break;

	}while(tmp != NULL);

	return tmp;
}

template<class T, unsigned long SIZE, unsigned long ADD_SIZE>
TYPENAME ZTree<T,SIZE,ADD_SIZE>::_node *ZTree<T,SIZE,ADD_SIZE>::GetLastBrother(TYPENAME ZTree<T,SIZE,ADD_SIZE>::_node *brother)
{
	ZASSERT(brother != NULL);
		
	while(brother->next != NULL)
		brother = brother->next;

	return brother;
}

template<class T, unsigned long SIZE, unsigned long ADD_SIZE>
void ZTree<T,SIZE,ADD_SIZE>::ClearChildren(TYPENAME ZTree<T,SIZE,ADD_SIZE>::_node *parent)
{
	ZASSERT(parent != NULL);

	_node *tmp = parent->child;
	_node *next;

	if(tmp)
	{
		while(tmp != NULL)
		{
			next = tmp->next;

			if(tmp->child != NULL)
				ClearChildren(tmp);

			PutNode(tmp);

			tmp = next;
		}
	}

	parent->child = NULL;
}