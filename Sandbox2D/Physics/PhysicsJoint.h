#pragma once

/**
* \brief PhysicsJoint
*/
class PhysicsJoint
{
public:
	/**
	* \brief Constructor
	*/
	PhysicsJoint() {};

	/**
	* \brief Destructor
	*/
	virtual ~PhysicsJoint() {};

	/**
	* \brief Sets the userdata of this Joint
	* \n Use this to identify the Joint if only the pointer of the actor is known
	* \n Best practice is to use a enumeration type (not class enum type)
	* @param data: the int containing a value that the programmer(user) can define
	*/
	void setUserData(const int data) { _userData = data; }

	/**
	* \brief Returns the userdata of this Joint
	* @return The userdata of this Joint
	*/
	int getUserData() const { return _userData; }

protected:
	//! bool _deleted
	bool _deleted = false;

private:
	//! friend class Sandbox2D
	friend class Sandbox2D;

	//! int _userData
	int _userData = 0;
};