#include "BinaryTree.h"
#include <iostream>
uNode16::uNode16() : data(0), owner(nullptr), greater(nullptr), lesser(nullptr) {}

uNode16::uNode16(uint16 d) : data(d), owner(nullptr), greater(nullptr), lesser(nullptr) {}

uNode16::uNode16(const uNode16& other) : data(other.data), owner(other.owner), greater(nullptr), lesser(nullptr) { //recursivly copy the nodes
	if(other.greater != nullptr)
		greater = new uNode16(*greater);
	if(other.lesser != nullptr)
		lesser = new uNode16(*lesser);
}

uNode16::uNode16(uNode16&& other) noexcept : data(other.data), owner(other.owner), greater(other.greater), lesser(other.lesser) {
	other.greater = nullptr;
	other.lesser = nullptr;
	other.owner = nullptr;
}


uNode16::~uNode16() {
	if (lesser == nullptr && greater == nullptr) return;

	if (!lesser && greater) {
		if (data >= owner->data)
		{
			owner->greater = greater;
			return;
		}
		owner->lesser = greater;
		return;
	}
	
	if (lesser && !greater) {
		if (data >= owner->data)
		{
			owner->greater = lesser;
			return;
		}
		owner->lesser = lesser;
		return;
	}

	//reorder the tree


	uNode16* target; 
	//verdi mellom L & G
	// lengst venstre i større grena eller lengst høyre i mindre grena
	// velger å bruke venstre i større grena 

	target = greater;
	while (target->lesser) {
		target = target->lesser;
	}
	target->owner->lesser = target->greater;
	target->owner = owner;
	target->lesser = lesser;
	target->greater = greater;
}


void uNode16::setGreater(uNode16* g) { greater = g; }
void uNode16::setLesser(uNode16* l) { lesser = l; }

uNode16& uNode16::operator = (uint16 nd) { data = nd; return *this; }

uNode16& uNode16::operator = (const uNode16& on) {

	data = on.data;
	if (on.greater != nullptr)
		greater = new uNode16(*greater);
	if (on.lesser != nullptr)
		lesser = new uNode16(*lesser);

	return *this;
}

uNode16& uNode16::operator= (uNode16&& on) noexcept {
	data = on.data;
	greater = on.greater;
	lesser = on.lesser;
	return *this;
}

bool operator == (const uNode16& node, uint16 cd) { return node.data == cd; }
bool operator <  (const uNode16& node, uint16 cd) { return node.data < cd; }
bool operator >  (const uNode16& node, uint16 cd) { return node.data > cd; }
											 
bool operator == (uint16 cd, const uNode16& node) { return cd == node.data; }
bool operator <  (uint16 cd, const uNode16& node) { return cd < node.data; }
bool operator >  (uint16 cd, const uNode16& node) { return cd > node.data; }

bool operator != (const uNode16& node, uint16 cd) { return node.data != cd; }
bool operator <=  (const uNode16& node, uint16 cd) { return node.data <= cd; }
bool operator >=  (const uNode16& node, uint16 cd) { return node.data >= cd; }

bool operator != (uint16 cd, const uNode16& node) { return cd != node.data; }
bool operator <=  (uint16 cd, const uNode16& node) { return cd <= node.data; }
bool operator >=  (uint16 cd, const uNode16& node) { return cd >= node.data; }

bool uNode16::add(uint16 d) {
	if (d < data) {
		if (lesser){
			return lesser->add(d);
		}
		lesser = new uNode16(d);
		lesser->owner = this;
		return true;
	}
	
	if (d >= data) {
		if (greater) {
			return greater->add(d);
		}
		greater = new uNode16(d);
		greater->owner = this;
		return true;

	}

	return false;
}

void uNode16::print() {
	if (lesser) {
		std::cout << "(";
		lesser->print();
		std::cout << ")";
	}
	std::cout << data;
	if (greater) {
		std::cout << "(";
		greater->print();
		std::cout << ")";
	}

}

uNode16* uNode16::remove(uint16 d) {
	if (!(lesser || greater)) return this;
	if (d != data) {
		if (d < data){
			return (!lesser) ? nullptr : lesser->remove(d);
		}
		return (!greater) ? nullptr : greater->remove(d);
	}



	uNode16* replacement = greater;
	while (replacement->lesser) replacement = replacement->lesser;
	
	data = replacement->data;
	if (reinterpret_cast<int>(replacement->owner) == reinterpret_cast<int>(owner)) {
		replacement->owner->lesser = nullptr;
		std::cout << "activated \n";
	}
	

	return replacement;
}


uTree16::uTree16() : root(new uNode16()), memsize(sizeof(uTree16) + sizeof(uNode16)), nodes(1) { root->owner = nullptr; }

uTree16::uTree16(uint16 rd) : root(new uNode16(rd)), memsize(sizeof(uTree16) + sizeof(uNode16)), nodes(1) {}

uTree16::uTree16(const uTree16& other) : root(other.root), memsize(other.memsize), nodes(other.nodes) {}

uTree16::uTree16(uTree16&& other) noexcept : root(other.root), memsize(other.memsize), nodes(other.nodes) {
	other.root = nullptr;
}

void uTree16::add(uint16 d) {
	if (root->add(d)) {
		nodes++;
		memsize += sizeof(uNode16);
	}
}

void uTree16::print() {

	root->print();
	std::cout << std::endl;
}

void uTree16::remove(uint16 d) {
	uNode16* target = root->remove(d);
	if (target) delete target;
}

bool uTree16::contains(uint16 i) {
	return false;
}