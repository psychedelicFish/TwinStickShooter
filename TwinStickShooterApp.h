#pragma once

#include "Application.h"
#include "Renderer2D.h"

class TwinStickShooterApp : public aie::Application {
public:

	TwinStickShooterApp();
	virtual ~TwinStickShooterApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
};