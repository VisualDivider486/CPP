#include "defines.h"
#include "movie.h"
#include <sgg/graphics.h>
#include <string>
#include <iostream>

using namespace std;

void Movie::draw()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	SETCOLOR(br.fill_color, 1.0f,1.0f, 1.0f);

	if (m_state == STATE_INIT)
	{
		graphics::setFont("Aller_Lt.ttf"); //sets font style
		graphics::drawText(CANVAS_WIDTH/2,CANVAS_HEIGHT/2,1.0f, "loading the app...",br);
		m_state = STATE_LOADING;
		return;
	}


	br.outline_opacity = 0.0f;
	br.texture = ASSET_PATH + string("ba.png");

	SETCOLOR(br.fill_color, 0.0f, 0.0f, 0.3f);

	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	for (auto poster : m_posters) // draws posters
	{
		poster->draw();
	}
}

void Movie::update()
{
	if (m_state == STATE_INIT)
	{
		return;
	}

	if (m_state == STATE_LOADING)
	{
		init();
		m_state = STATE_IDLE;
		return;
	}

	for (auto poster : m_posters)
	{
		poster->update();
	}

	graphics::MouseState ms; //pairnei to stigmiotypo toy pontikiou
	graphics::getMouseState(ms);

	float mx = graphics::windowToCanvasX(ms.cur_pos_x);
	float my = graphics::windowToCanvasY(ms.cur_pos_y);

	Poster* cur_poster = nullptr;
	for (auto poster : m_posters)
	{
		if (poster->contains(mx, my))
		{
			poster->setHighlight(true); //ginetai true otan einai mesa sto plaisio o cursor
			cur_poster = poster; //krataei to torino poster poy kano hover
		}
		else
		{
			poster->setHighlight(false);
		}
	}	

	//activate poster
	if (ms.button_left_pressed && cur_poster)
	{
		m_active_poster = cur_poster;
		m_active_poster->setActive(true);
		for (auto poster : m_posters) //kanei disable ta inactive posters 
		{
			if (poster != m_active_poster)
			{
				m_active_poster->setActive(false);
			}
		}
	}

	//mouse dragging:poster motion
	//if (ms.dragging && m_active_poster)
	//{
	//	m_state = STATE_MOVING;
	//	m_active_poster->setPosX(mx);
	//	m_active_poster->setPosY(my);
	//}

	//draging
	//if (ms.button_left_released && m_active_poster)
	//{
	//	m_state = STATE_IDLE;
	//	m_active_poster->setActive(false);
	//	m_active_poster = nullptr;
	//}
	//not necessary (yet?)
	//for (auto poster : m_posters)
	//{
	//	poster->update();
	//}
}

void Movie::init()
{
	for (int i = 2; i < 6; i++) {
		//for (int j = 0; j < 2; j++) {

			Poster* p = new Poster(); //dhmioyrgia instance poster
			m_posters.push_front(p);

			p->setPosX(CANVAS_WIDTH * (i-0.5f) / 6.0f);
			p->setPosY(CANVAS_HEIGHT * (0.5f) / 2.0f);
		//}
	}

	graphics::preloadBitmaps(ASSET_PATH); //preloads assets

}

Movie::~Movie()
{
	for (auto poster : m_posters)
	{
		delete poster;
	}
	m_posters.clear();
}

Movie* Movie::getInstance()
{
	if (!m_instance)
		m_instance = new Movie();
	return m_instance;
}

Movie* Movie::m_instance = nullptr; //arxikopoihsh