#pragma once
#include "types.h"

class uNode16 {
	uint16 data;
	
	uNode16* greater;
	uNode16* lesser;
public:
	uNode16* owner;

	uNode16();
	uNode16(uint16 d);
	uNode16(const uNode16& other);
	uNode16(uNode16&& other) noexcept;
	~uNode16();


	void setGreater(uNode16* g);
	void setLesser(uNode16* l);


	uNode16& operator = (uint16 nd);
	
	uNode16& operator = (const uNode16& on);
	uNode16& operator = (uNode16&& on) noexcept;

	friend bool operator == (const uNode16& node,uint16 cd);							 
	friend bool operator <  (const uNode16& node,uint16 cd);							 
	friend bool operator >  (const uNode16& node,uint16 cd);

	friend bool operator == (uint16 cd,const uNode16& node);
	friend bool operator <  (uint16 cd,const uNode16& node);
	friend bool operator >  (uint16 cd,const uNode16& node);

	friend bool operator != (const uNode16& node, uint16 cd);
	friend bool operator <=  (const uNode16& node, uint16 cd);
	friend bool operator >= (const uNode16& node, uint16 cd);

	friend bool operator != (uint16 cd, const uNode16& node);
	friend bool operator <=  (uint16 cd, const uNode16& node);
	friend bool operator >= (uint16 cd, const uNode16& node);

	inline uNode16* getLesser() const { return lesser; }
	inline uNode16* getGreater() const { return greater; }

	bool add(uint16 d);
	void print();
	
	uNode16* remove(uint16 d);

	uint16 getSmallest() const;
};


class uTree16 {
	uNode16* root;
	uint64 memsize;
	uint32 nodes;


public:
	uTree16();

	uTree16(uint16 rd);
	uTree16(const uTree16& other);
	uTree16(uTree16&& other) noexcept;
	
	template<typename ... Targs>
	uTree16(uint16 first, Targs ... Margs) : root(first), memsize(sizeof(uTree16) + sizeof(uNode16)), nodes(1){
		add(Margs...);
	}


	inline void setRootData(uint16 rd) { *root = rd; }

	inline uint64 getMemSize() const { return memsize; }

	inline uint32 getSize() const { return nodes; }

	void add(uint16 d);

	template<typename ... Targs>
	void add(uint16 first, Targs ... Margs) {
		add(first);
		add(Margs...);
	}

	void print();

	void remove(uint16 d);

	bool contains(uint16 i);
};