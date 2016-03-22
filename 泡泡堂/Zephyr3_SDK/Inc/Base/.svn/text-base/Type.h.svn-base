/*
							Zephyr Engine v3.0

								by ’‘∫ÈÀ…(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Base\Type.h

							Describe:	¿‡–Õ

							Author:		’‘∫ÈÀ…(xueren)

							CreateTime: 2004.05.14
							UpdateTime: 2004.04.14
*/

#ifndef _ZEPHYR_3_BASE_TYPE_H
#define _ZEPHYR_3_BASE_TYPE_H

namespace Zephyr3{

	template<int V>
	class Int2Type{
		enum { _Value = V };
	};

	template<typename TYPE,bool HAS_CONSTRUCTOR = true,bool HAS_DESTRUCTOR = true>
	class TypeTraits{
	public:
		typedef	TYPE						_ValueType;
		typedef TYPE*						_PointerType;
		typedef TYPE&						_ReferenceType;

		typedef const TYPE					_ConValueType;
		typedef const TYPE*					_ConPointerType;
		typedef const TYPE&					_ConReferenceType;

		typedef Int2Type<HAS_CONSTRUCTOR>	_Constructor;
		typedef Int2Type<HAS_DESTRUCTOR>	_Destructor;

		enum { _Size = sizeof(TYPE) };
	};
};

#endif // _ZEPHYR_3_BASE_TYPE_H