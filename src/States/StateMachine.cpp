#include "StateMachine.h"

void StateMachine::switchState(State* state)
{
	_current->exit();
	_current = state;
	_current->enter();
}

StateMachine::StateMachine(PlayingState* playingState, GameOverState* gameOverState, sf::RenderWindow* renderWindow) :
	_playing(playingState),
	_gameOver(gameOverState),
	_renderWindow(renderWindow),
	_gameRestarted(false)
{
	_current = _playing;
	_current->enter();
}


void StateMachine::execute()
{
	if(_current == _playing)
	{
		if(_playing->isGameLost())
		{
			switchState(_gameOver);
		}
	} else if(_current == _gameOver)
	{
		if(_gameOver->restarted())
		{
			_gameRestarted = true;
		}
	}

	_current->execute();
	_renderWindow->draw(*_current);
}

bool StateMachine::gameRestarted() const
{
	return _gameRestarted;
}
