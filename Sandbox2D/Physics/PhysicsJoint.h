#pragma once

class PhysicsJoint
{
public:
	PhysicsJoint() {};
	virtual ~PhysicsJoint() {};

	//! Sets the userdata of this Joint
	//! @param data is the int containing a value that the programmer(user) can define
	//! Use this to identify the Joint if only the pointer of the actor is known
	//! Best practice is to use a enumeration type (not class enum type)
	void setUserData(const int data) { _userData = data; }

	//! Returns the userdata of this Joint
	int getUserData() const { return _userData; }

protected:
	bool _deleted = false;

private:
	friend class Sandbox2D;
	int _userData = 0;
};