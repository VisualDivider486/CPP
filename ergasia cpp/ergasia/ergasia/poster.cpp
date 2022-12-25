#include "poster.h"
#include "sgg/graphics.h"
#include "defines.h"
#include <string>

using namespace std;

void Poster::draw() // FTIAKSE GLOBAL BRUSH!
{
	graphics::Brush br;

	float h = 1.0f * m_highlighted;

	SETCOLOR(br.fill_color, h, h, h);
	br.outline_opacity = 1.0f * m_active;
	graphics::drawRect(m_pos[0], m_pos[1], POSTER_SIZE*1.01f, POSTER_SIZE * 1.02f, br);

	SETCOLOR(br.fill_color, m_color[0], m_color[1], m_color[2]);
	br.texture = ASSET_PATH + string("download.png");
	br.outline_opacity = 0.0f;
	graphics::drawRect(m_pos[0], m_pos[1], POSTER_SIZE, POSTER_SIZE, br);
}

void Poster::update()
{
}

Poster::Poster() //constructor definition
{
	SETCOLOR(m_color, 1.0f, 1.0f, 1.0f); //xoris auto mavrizoun ta posters
}

bool Poster::contains(float x, float y)
{
	return distance(x, y, m_pos[0], m_pos[1]) < POSTER_SIZE*0.6f; //den ksero gt doulevei me to 0.6 kai oxi sketo
}
