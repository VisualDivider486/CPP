#pragma once
#include <list>
#include "poster.h"

using namespace std;

class Movie
{
public:

	enum game_state_t {STATE_INIT,STATE_LOADING, STATE_IDLE, STATE_TEMP, STATE_MOVING};

protected:

	static Movie* m_instance; //static-prepei na arxikopoihthei

	list<Poster*> m_posters;
	Poster* m_active_poster = nullptr;
	game_state_t m_state = STATE_INIT; //arxikh katastash

	Movie() {}

public:
	void draw();
	void update();
	void init();

	~Movie();

	static void releaseInstance() { if (m_instance) delete m_instance; m_instance = nullptr; }
	static Movie* getInstance();
};