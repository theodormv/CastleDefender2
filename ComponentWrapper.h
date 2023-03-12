#pragma once

#include <iostream>

class Component;

class CompWrapper {
	using Comp_Ptr = Component*;

	


public:
	Comp_Ptr* data;

	CompWrapper() = default;
	CompWrapper(Comp_Ptr* comp);
	CompWrapper(const CompWrapper& other);
	//CompWrapper(Comp_Ptr& comp);
	CompWrapper(CompWrapper&& other) noexcept;

	Comp_Ptr& operator * ();
	Comp_Ptr operator -> ();

	Comp_Ptr* operator = (Comp_Ptr& other);
	Comp_Ptr* operator = (Comp_Ptr* other);
	Component*& getCore();
};