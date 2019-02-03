#pragma once

class Capital : public Building
{
public:
	Capital( );
	virtual ~Capital( );
	// Make objects non-copyable
	// https://msdn.microsoft.com/en-us/library/dn457344.aspx 
	Capital( const Capital& ) = delete;
	Capital& operator=( const Capital& ) = delete;

private: 

};
