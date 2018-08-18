#include "../stdafx.h"
#include "PrecisionTimer.h"
#include "../GameFiles/EntryState.h"
#include "../GameFiles/GlobalState.h"
#include "Physics/ContactListener.h"

// Static Variable Initialization
Sandbox2D* Sandbox2D::_sandbox2DPtr = nullptr;

// Sandbox2D constructor/deconstructor
Sandbox2D::Sandbox2D() {}
Sandbox2D::~Sandbox2D() {}

/*********************
* PRIVATE FUNCTIONS  *
*********************/
Sandbox2D* Sandbox2D::GetSingleton()
{
	return _sandbox2DPtr == nullptr ? _sandbox2DPtr = new Sandbox2D() : _sandbox2DPtr;
}

int Sandbox2D::run()
{
	// Initialise the game
	init();

	// Start global state
	globalState = new GlobalState();
	globalState->globalStart();

	// Start entry state
	_states.push_back(new EntryState());
	_states.back()->stateStart();

	// Main game loop
	auto previous = _gameTickTimerPtr->GetGameTime() - _physicsTimeStep;
	auto lag = 0.00000; // Left over time
	
	// Main loop _flag
	auto quit = false;

	// Main game loop, runs as fast as it can
	while (!quit)
	{
		const auto current = _gameTickTimerPtr->GetGameTime();
		auto elapsed = current - previous;
		// prevent jumps in time when game is sleeping or running at less than 5 fps.
		if (elapsed > 0.25) elapsed = 0.25; 
		previous = current;
		lag += elapsed;

		// Ensures that physics time steps are being executed properly
		while (lag >= _physicsTimeStep)
		{
			inputManager->setOldInputStates();
			// Handle all events in queue
			SDL_Event event;
			while (SDL_PollEvent(&event))
			{
				// User requests quit
				if (event.type == SDL_QUIT) quit = true;
			}
			inputManager->setCurrInputStates();

			// Execute the Global state's stateTick
			globalState->globalTick(_physicsTimeStep);

			// Execute the active state's stateTick
			_states.back()->stateTick(_physicsTimeStep);

			// Do physics magic
			_box2DWorld->Step(float(_physicsTimeStep), velocityIterations, positionIterations);
			
			lag -= _physicsTimeStep;
		}

		// Execute the active state's statePaint
		_graphics->renderAll(_states.back());
	}
	return 0;
}

void Sandbox2D::init()
{
	// Initialise logging
	if (CreateLog()) LogInfo("Logging started!");

	// Initialise high precision timer
	_gameTickTimerPtr = new PrecisionTimer();
	_gameTickTimerPtr->Reset();

	// Initialise InputManager and InputEvents
	inputManager = new InputManager();

	// TODO: change to reading from ini file
	

	GameSettings gameSettings;
	try
	{
		IniFile* gameIni = new IniFile("Config/gamesettings.ini");
		gameIni->parse();

		gameSettings._windowSize = {
			std::stoi(gameIni->getValue("graphics", "width")),
			std::stoi(gameIni->getValue("graphics", "height"))
		};
		gameSettings._windowTitle = gameIni->getValue("game", "title");

		delete gameIni;
	} 
	catch(std::invalid_argument &e)
	{
		LogError(e.what());
		gameSettings._windowSize = { 1280, 720 };
		gameSettings._windowTitle = "Sandbox2D testing environment";
	}

	// Initialise Graphics
	_graphics = new Graphics(gameSettings);

	// Initialise Box2D
	_gravity = { 0, 9.81 };
	_box2DWorld = new b2World(Tob2Vec2(_gravity));
	_box2DWorld->SetContactListener(this);
	_box2DWorld->SetDestructionListener(this);

	// Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return;
	}

	LogInfo("Sandbox2D initialised successfully!");
}

void Sandbox2D::destroy()
{
	LogInfo("Destroying Sandbox2D!");

	// Delete any left over gamestates
	while (!_states.empty())
		this->popState();

	// Delete the global state
	globalState->globalEnd();
	delete globalState;

	// Delete Box2D related stuff
	delete _box2DWorld;
	_box2DWorld = nullptr;

	// Engine cleanup
	delete _gameTickTimerPtr;
	_gameTickTimerPtr = nullptr;

	delete inputManager;
	inputManager = nullptr;

	delete _graphics;
	_graphics = nullptr;

	// Quit SDL subsystems
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	LogInfo("SDL cleanup finished!");

	// Delete engine singleton
	if (_sandbox2DPtr != nullptr)
	{
		delete _sandbox2DPtr;
		_sandbox2DPtr = nullptr;
	}
	LogInfo("Sandbox2D destroyed successfully!");
}

/*********************
 * PUBLIC FUNCTIONS  *
 *********************/

void Sandbox2D::changeState(GameState* state)
{
	popState();
	pushState(state);
}

void Sandbox2D::pushState(GameState* state)
{
	// Add state to gamestates
	_states.push_back(state);

	// User fegined start
	_states.back()->stateStart();
}

void Sandbox2D::popState()
{
	// User defined cleanup
	_states.back()->stateEnd();

	// Delete the gamestate
	delete _states.back();
	_states.pop_back();
}

b2World* Sandbox2D::getb2World() const
{
	return _box2DWorld;
}

void Sandbox2D::setGravity(const Vector2 gravity)
{
	_gravity = gravity;
	_box2DWorld->SetGravity(Tob2Vec2(gravity));
}

Pixel Sandbox2D::getWindowSize() const
{
	return _graphics->getWindowSize();
}

void Sandbox2D::BeginContact(b2Contact* contactPtr)
{
	b2Fixture* fixContactListenerPtr = nullptr;
	b2Fixture* fixOtherPtr = nullptr;

	//is A a contactlistener?
	if (contactPtr->GetFixtureA()->GetBody()->GetUserData() != nullptr)
	{
		fixContactListenerPtr = contactPtr->GetFixtureA();
		fixOtherPtr = contactPtr->GetFixtureB();
		// check for removed actors, this method can be called by Box2D when a PhysicsActor is being destroyed
		if (fixContactListenerPtr->GetUserData() != nullptr && fixOtherPtr->GetUserData() != nullptr)
		{
			ContactListener* contactListenerPtr = reinterpret_cast<ContactListener*>(fixContactListenerPtr->GetBody()->GetUserData());
			contactListenerPtr->beginContact(
				reinterpret_cast<PhysicsObject*>(fixContactListenerPtr->GetUserData()),
				reinterpret_cast<PhysicsObject*>(fixOtherPtr->GetUserData())
			);
		}
	}
	//is B a contactlistener?
	if (contactPtr->GetFixtureB()->GetBody()->GetUserData() != nullptr)
	{
		fixContactListenerPtr = contactPtr->GetFixtureB();
		fixOtherPtr = contactPtr->GetFixtureA();
		// check for removed actors, this method can be called by Box2D when a PhysicsActor is being destroyed
		if (fixContactListenerPtr->GetUserData() != nullptr && fixOtherPtr->GetUserData() != nullptr)
		{
			ContactListener * contactListenerPtr = reinterpret_cast<ContactListener *>(fixContactListenerPtr->GetBody()->GetUserData());
			contactListenerPtr->beginContact(
				reinterpret_cast<PhysicsObject*>(fixContactListenerPtr->GetUserData()),
				reinterpret_cast<PhysicsObject*>(fixOtherPtr->GetUserData())
			);
		}
	}
}

void Sandbox2D::EndContact(b2Contact* contactPtr)
{
	b2Fixture* fixContactListenerPtr = nullptr;
	b2Fixture* fixOtherPtr = nullptr;

	//is A a contactlistener?
	if (contactPtr->GetFixtureA()->GetBody()->GetUserData() != nullptr)
	{
		fixContactListenerPtr = contactPtr->GetFixtureA();
		fixOtherPtr = contactPtr->GetFixtureB();
		// check for removed actors, this method can be called by Box2D when a PhysicsActor is being destroyed
		if (fixContactListenerPtr->GetUserData() != nullptr && fixOtherPtr->GetUserData() != nullptr)
		{
			ContactListener* contactListenerPtr = reinterpret_cast<ContactListener*>(fixContactListenerPtr->GetBody()->GetUserData());
			contactListenerPtr->endContact(
				reinterpret_cast<PhysicsObject*>(fixContactListenerPtr->GetUserData()),
				reinterpret_cast<PhysicsObject*>(fixOtherPtr->GetUserData())
			);
		}
	}
	//is B a contactlistener?
	if (contactPtr->GetFixtureB()->GetBody()->GetUserData() != nullptr)
	{
		fixContactListenerPtr = contactPtr->GetFixtureB();
		fixOtherPtr = contactPtr->GetFixtureA();
		// check for removed actors, this method can be called by Box2D when a PhysicsActor is being destroyed
		if (fixContactListenerPtr->GetUserData() != nullptr && fixOtherPtr->GetUserData() != nullptr)
		{
			ContactListener * contactListenerPtr = reinterpret_cast<ContactListener *>(fixContactListenerPtr->GetBody()->GetUserData());
			contactListenerPtr->endContact(
				reinterpret_cast<PhysicsObject*>(fixContactListenerPtr->GetUserData()),
				reinterpret_cast<PhysicsObject*>(fixOtherPtr->GetUserData())
			);
		}
	}
}

void Sandbox2D::PreSolve(b2Contact* contactPtr, const b2Manifold* oldManifoldPtr)
{
	b2Fixture * fixContactListenerPtr = nullptr;
	b2Fixture * fixOtherPtr = nullptr;

	//is A a contactlistener?
	if (contactPtr->GetFixtureA()->GetBody()->GetUserData() != nullptr)
	{
		fixContactListenerPtr = contactPtr->GetFixtureA();
		fixOtherPtr = contactPtr->GetFixtureB();
		// check for removed actors, this method can be called from within the PhysicsActor destructor
		// when one of two overlapping actors is deleted
		if (fixContactListenerPtr->GetUserData() != nullptr && fixOtherPtr->GetUserData() != nullptr)
		{
			bool bEnableContact = true;
			ContactListener* contactListenerPtr = reinterpret_cast<ContactListener*>(fixContactListenerPtr->GetBody()->GetUserData());
			contactListenerPtr->preSolve(
				reinterpret_cast<PhysicsObject*>(fixContactListenerPtr->GetUserData()),
				reinterpret_cast<PhysicsObject*>(fixOtherPtr->GetUserData()),
				bEnableContact
			);
			contactPtr->SetEnabled(bEnableContact);
		}
	}
	//is B a contactlistener?
	if (contactPtr->GetFixtureB()->GetBody()->GetUserData() != nullptr)
	{
		fixContactListenerPtr = contactPtr->GetFixtureB();
		fixOtherPtr = contactPtr->GetFixtureA();
		// check for removed actors, this method can be called from within the PhysicsActor destructor
		// when one of two overlapping actors is deleted
		if (fixContactListenerPtr->GetUserData() != nullptr && fixOtherPtr->GetUserData() != nullptr)
		{
			bool bEnableContact = true;
			ContactListener* contactListenerPtr = reinterpret_cast<ContactListener*>(fixContactListenerPtr->GetBody()->GetUserData());
			contactListenerPtr->preSolve(
				reinterpret_cast<PhysicsObject*>(fixContactListenerPtr->GetUserData()),
				reinterpret_cast<PhysicsObject*>(fixOtherPtr->GetUserData()),
				bEnableContact
			);
			contactPtr->SetEnabled(bEnableContact);
		}
	}
}

void Sandbox2D::SayGoodbye(b2Joint* jointPtr)
{
	const auto joint = reinterpret_cast<PhysicsJoint*>(jointPtr->GetUserData());
	if (joint != nullptr) joint->_deleted = true;
}

void Sandbox2D::SayGoodbye(b2Fixture* fixturePtr)
{
}
