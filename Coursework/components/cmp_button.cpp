#include "cmp_button.h"
#include <system_renderer.h>
#include <system_resources.h>
#include "../game.h"
#include <SFML/Audio/Sound.hpp>
#include <sstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <SFML/Window/Keyboard.hpp>
#include "../Keys.h"

using namespace sf;
using namespace std;   //now need to getKeys to player physics to see if it works.

//bool KeyPressEvent(MyKeys k, sf::Event e)
//{
//	if (k.KeyCode == e.key.code)	//if the keycode of the MYKeys struct equals the keycode of the event
//	{
//		return true;	//then return true
//	}else 
//	{
//		return false;
//	}
//}

//std::map<std::string, MyKeys> ButtonComponent::GetKeys()
//{
//	return Keys;
//}

void ButtonComponent::SetParentKeys()
{
	//key.KeyCode = sf::Keyboard::D;	//initilaising struct values and _parent keys to remember which key belongs to which action
	//Keys["Right"] = key;

	//key.KeyCode = sf::Keyboard::A;
	//Keys["Left"] = key;

	//key.KeyCode = sf::Keyboard::S;
	//Keys["Down"] = key;

	//key.KeyCode = sf::Keyboard::Space;
	//Keys["Jump"] = key;

	string tag = _text.getString();
	_parentKeys[0] = "d";
	_parentKeys[1] = "a";
	_parentKeys[2] = "s";
	_parentKeys[3] = "space";

	if (tag == "d")					//sets up parent keys from intial control values
	{
		_parentKey = _parentKeys[0];
	}
	else if (tag == "a")
	{
		_parentKey = _parentKeys[1];
	}
	else if (tag == "s")
	{
		_parentKey = _parentKeys[2];
	}
	else if (tag == "space")
	{
		_parentKey = _parentKeys[3];
	}
	else {
		_parentKey == "UNUSED";
	}
}

void ButtonComponent::update(double dt) {
	string tag = _text.getString(); //gets the string name of the button
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		mousethis = true;	//mouse timing, ensuring only one click
	}
	else
	{
		mousethis = false;
	}

	////remappable controls
	//if (_buttonType == "remappable" && isClicked)
	//{
	//	//button has been clicked.
	//	
	//	while (Engine::GetWindow().pollEvent(eventT))
	//	{
	//		//if (KeyPressEvent(Keys["Right"], eventT))
	//		//{
	//		//	//walk right code.
	//		//}
	//		//else if (KeyPressEvent(Keys["Left"], eventT))
	//		//{
	//		//	//walk Left code.
	//		//}else if (KeyPressEvent(Keys["Down"], eventT))
	//		//{
	//		//	//walk Down code.
	//		//}else if (KeyPressEvent(Keys["Jump"], eventT))
	//		//{
	//		//	//jump code.
	//		//}
	//		if (eventT.type == sf::Event::TextEntered)	//if the text event is a text event
	//		{
	//			cout << "YOU ENTERED = " << eventT.text.unicode << "\n";
	//			_text.setString(eventT.text.unicode);	//set the value of the button to the character entered for visual confirmation
	//			isClicked = false;
	//			if (_parentKey == "d")					//if this button had a parent key of " "
	//			{
	//				auto as = eventT.text.unicode;		//get the uni code and cast to keycode
	//				key.KeyCode = (sf::Keyboard::Key)as;
	//				Keys::keys["Right"] = key.KeyCode;				//set the action up as this new keycode
	//			}else if (_parentKey == "a")
	//			{
	//				auto as = eventT.text.unicode;
	//				key.KeyCode = (sf::Keyboard::Key)as;
	//				Keys::keys["Left"] = key.KeyCode;
	//			}
	//			else if (_parentKey == "s")
	//			{
	//				auto as = eventT.text.unicode;
	//				key.KeyCode = (sf::Keyboard::Key)as;
	//				Keys::keys["Down"] = key.KeyCode;
	//			}
	//			else if (_parentKey == "space")
	//			{
	//				auto as = eventT.text.unicode;
	//				key.KeyCode = (sf::Keyboard::Key)as;
	//				Keys::keys["Jump"] = key.KeyCode;
	//			}
	//		}
	//	}
	//}

	//if string contains numbers for volume ui
	if (_buttonType == "SoundNumber")			//if the button has this buttontype, meaning it has a numerical value
	{
		int vol = sounds.GetSoundVolume();			//then set the text = to the numerical value
		_text.setString(to_string(vol));
	}
	else if (_buttonType == "MusicNumber")
	{
		int vol = sounds.GetMusicVolume();
		_text.setString(to_string(vol));
	}

	if (_buttonType != "NotPaused")			//if the game is not in the paused state, for small group of buttons otherwise
	{
		if (mousethis && !mouselast && _rect.contains(static_cast<sf::Vector2i>(sf::Mouse::getPosition(Engine::GetWindow()))))
		{
			sounds.PlayButtonSound();	//if the mouse intersects the button and has clicked once, then play sound effect

			if (tag == "Start Game" || tag == "Level-1" || tag == "Restart Level")
			{
				Engine::ChangeScene(&level1);	//various tags that do things based on their function
			}
			else if (tag == "Level Select")
			{
				Engine::ChangeScene(&levelSelect);
			}
			else if (tag == "Options" || tag == "Back to Options")
			{
				Engine::ChangeScene(&optionsScene);
			}
			else if (tag == "Back to Main Menu")
			{
				Engine::ChangeScene(&menu);
			}
			else if (tag == "Restart Game")
			{
				sceneTracker.ClearLevelComplete();
			}
			else if (tag == "Exit Game")
			{
				//exit game
				Engine::GetWindow().close();
			}
			else if (tag == "Volume")
			{
				Engine::ChangeScene(&volScene);
			}
			else if (tag == "+" && _buttonType == "Sound")
			{
				if (sounds.GetSoundVolume() < 100) {//limits on volume
					sounds.SetSoundVolume(sounds.GetSoundVolume() + 10);
				}
				else if (sounds.GetSoundVolume() > 100) //limits on volume
				{
					sounds.SetSoundVolume(100);
				}
			}	  //plus and minus for adjusting volume of music or sound
			else if (tag == "-" && _buttonType == "Sound")
			{
				if (sounds.GetSoundVolume() > 0) { //limits on volume
					sounds.SetSoundVolume(sounds.GetSoundVolume() - 10);
				}
				else if (sounds.GetSoundVolume() < 0) //limits on volume
				{
					sounds.SetSoundVolume(0);
				}
			}
			else if (tag == "+" && _buttonType == "Music")
			{
				if (sounds.GetMusicVolume() < 100) {//limits on volume
					sounds.SetMusicVolume(sounds.GetMusicVolume() + 10);
				}
				else if (sounds.GetMusicVolume() > 100) //limits on volume
				{
					sounds.SetMusicVolume(100);
				}
			}
			else if (tag == "-" && _buttonType == "Music")
			{
				if (sounds.GetMusicVolume() > 0) { //limits on volume
					sounds.SetMusicVolume(sounds.GetMusicVolume() - 10);
				}
				else if (sounds.GetMusicVolume() < 0) //limits on volume
				{
					sounds.SetMusicVolume(0);
				}
			}
			else if (tag == "Resolution")
			{
				Engine::ChangeScene(&resScene);
			}
			else if (tag == "Level-2" && sceneTracker.GetLevelComplete()[0] == true)
			{
				Engine::ChangeScene(&level2);
			}
			else if (tag == "Level-3" && sceneTracker.GetLevelComplete()[1] == true)
			{
				Engine::ChangeScene(&level3);
			}
			else if (tag == "Level-4" && sceneTracker.GetLevelComplete()[2] == true)
			{
				Engine::ChangeScene(&level4);
			}
			else if (tag == "Level-5" && sceneTracker.GetLevelComplete()[3] == true)
			{
				Engine::ChangeScene(&level5);
			}
			else if (tag == "Level-6" && sceneTracker.GetLevelComplete()[4] == true)
			{
				Engine::ChangeScene(&level6);
			}
			else if (tag == "Level-7" && sceneTracker.GetLevelComplete()[5] == true)
			{
				Engine::ChangeScene(&level7);
			}
			else if (tag == "Resume")
			{
				_buttonType = "NotPaused";	
				isClicked = true;			//is clicked is used to determine whether the button has in fact been clicked
			}								//if so then do something, here meaning get rid of pause menu from viewer
			else if (tag == "1920 x 1080")		//for adjusting resolution
			{
				sceneTracker.SetWidthHeight(1920, 1080);
				Engine::ChangeScene(&resScene);
			}
			else if (tag == "1280 x 720")
			{
				sceneTracker.SetWidthHeight(1280, 720); //0.67 of 1080p
				Engine::ChangeScene(&resScene);
			}
			else if (tag == "1024 x 576")
			{
				sceneTracker.SetWidthHeight(1024, 576); //0.53 of 1080p
				Engine::ChangeScene(&resScene);
			}
			else if (tag == "Controls")
			{
				Engine::ChangeScene(&controlScene);
			}
			else if (tag == "d" || _parentKey == "d")	//to determine whether a remappable key should be changed when clicked
			{
				isClicked = true;
			}
			else if (tag == "a" || _parentKey == "a")
			{
				isClicked = true;
			}
			else if (tag == "s" || _parentKey == "s")
			{
				isClicked = true;
			}
			else if (tag == "Space" || _parentKey == "space")
			{
				isClicked = true;
			}
		}
	}
	mouselast = mousethis; //updates the two bools, for one click mouse events
}


void ButtonComponent::render() { Renderer::queue(&_text); } //queues the text for rendering
 
ButtonComponent::ButtonComponent(Entity* const p, const std::string f, const int charSize, const sf::Color c, const sf::Vector2f pos, std::string tag, const std::string& str) : Component(p), _string(str) {
    _text.setString(_string);
    _font = Resources::get<sf::Font>(f); //intiialises values based on constructor input.
    _text.setFont(*_font);
	_charSize = charSize;
	_colour = c;
	_pos = pos;
	_text.setPosition(_pos);
	_text.setColor(c);
	_text.setCharacterSize(48 * sceneTracker.GetMultiplier());
	auto xLength = _string.size() * _charSize;			//sets up the rectangle of the button for mouse interaction
	_rect = IntRect(_pos.x, _pos.y, xLength, _charSize);//based on length and size of text
	_buttonType = tag;

}

void ButtonComponent::SetText(const std::string& str) { //allows changing of the visible text
    _string = str;
    _text.setString(_string);
}

std::string ButtonComponent::GetButtonType()	//gets the type of button for use in other classes
{
	return _buttonType;
}

void ButtonComponent::SetButtonType(std::string s) //allows the setting of the button to be different, for use when pausing
{
	_buttonType = s;
}

bool ButtonComponent::GetIsClicked() //determine whether the button has been clicked
{
	return isClicked;
}

void ButtonComponent::SetIsClicked(bool b) //change the isClicked bool, mostly for resetting one time events
{
	isClicked = b;
}