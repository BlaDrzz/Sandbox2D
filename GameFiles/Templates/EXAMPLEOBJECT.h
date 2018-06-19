#pragma once

class EXAMPLEOBJECT //: public ContactListener
{
public:
	EXAMPLEOBJECT( );
	virtual ~EXAMPLEOBJECT( );
	// Make objects non-copyable
	// https://msdn.microsoft.com/en-us/library/dn457344.aspx 
	EXAMPLEOBJECT( const EXAMPLEOBJECT& ) = delete;
	EXAMPLEOBJECT& operator=( const EXAMPLEOBJECT& ) = delete;

	//--------------------------------------------------------
	// ContactListener overloaded member function declarations
	//--------------------------------------------------------
	// virtual void BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);
	// virtual void EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);
	// virtual void ContactImpulse(PhysicsActor *actThisPtr, double impulse);

private: 

};
