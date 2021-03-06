#pragma once
#include <string>
#include "../CatalogManager/CharStream.h"

enum Type {
	Int,
	Float,
	Chars
};

class TypeInfo {
public:
	TypeInfo(Type type, size_t size) :_type(type), _size(size) {
	}
	TypeInfo(Type type) : _type(type), _size(4) {

	}

	TypeInfo(int type, int size) {
		switch (type) {
		case 82:
			_type = Chars;
			_size = size;
			break;
		case 83:
			_type = Int;
			_size = 4;
			break;
		case 84:
			_type = Float;
			_size = 4;
			break;
		default:
			_type = Int;
			std::cerr << "TypeInfo constructor: no such type" << std::endl;
			break;
		}
	}

	~TypeInfo() = default;

	std::string name() {
		switch (_type) {
		case Int:
			return "int";
			break;
		case Float:
			return "float";
			break;
		case Chars:
			return "char(" + std::to_string(_size) + ")";
			break;
		default:
			assert(1 == 2);
			return "no such type";
			//throw SomeError("no such type");
			break;
		}
	}
	static TypeInfo deserialize(CharInStream& cis) {
		Type type;
		size_t size;
		cis >> type;
		cis >> size;
		return TypeInfo(type, size);
	}

	void serialize(CharOutStream& couts)const {
		couts << _type;
		couts << _size;
	}

	int get_type_magic() const {
		switch (_type) {
		case Int:
			return 83;
			break;
		case Float:
			return 84;
			break;
		case Chars:
			return 82;
			break;
		default:
			assert(1 == 2);
			break;
		}
		return -1;
	}

	Type get_type() const{
		return _type;
	}

	size_t get_size() const {
		if (_type==Chars) {
			return _size+1;
		} else {
			return _size;
		}
		
	}

private:
	Type _type;
	size_t _size;

};



