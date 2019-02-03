#pragma once

class Building
{
public:
	Building() = default;
	virtual ~Building() = default;
	// Make objects non-copyable
	// https://msdn.microsoft.com/en-us/library/dn457344.aspx 
	Building(const Building&) = delete;
	Building& operator=(const Building&) = delete;

private:

};
