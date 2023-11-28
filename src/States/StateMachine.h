#pragma once

#include "State.h"
#include "States.h"
#include "SFML/Graphics.hpp"

class StateMachine
{
private:
	PlayingState* _playing;
	GameOverState* _gameOver;
	State* _current;
	sf::RenderWindow* _renderWindow;
	bool _gameRestarted;
	void switchState(State* state);
public:
	explicit StateMachine(PlayingState* playingState, GameOverState* gameOverState, sf::RenderWindow* renderWindow);
	void execute();
	bool gameRestarted() const;
};