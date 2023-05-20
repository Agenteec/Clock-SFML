#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>
void Render(sf::RenderWindow* window);
void main()
{
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1024,720),L"Часы");
	window->setFramerateLimit(0);
	Render(window);
}
void Render(sf::RenderWindow* window)
{	
	bool isTimer = 0;

	#pragma region Стрелки часов
	//Квадрат секунд
	sf::RectangleShape CentRect(sf::Vector2f(28, 28));
	CentRect.setFillColor(sf::Color::Black);
	CentRect.setOrigin(CentRect.getSize() / 2.f);
	CentRect.setPosition(sf::Vector2f(1024 / 2, 720 / 2));
	//Квадрат минут
	sf::RectangleShape CentRectM(sf::Vector2f(20, 20));
	CentRectM.setFillColor(sf::Color::Blue);
	CentRectM.setOrigin(CentRectM.getSize() / 2.f);
	CentRectM.setPosition(CentRect.getPosition());

	//Квадрат часов
	sf::RectangleShape CentRectH(sf::Vector2f(14, 14));
	CentRectH.setFillColor(sf::Color::Red);
	CentRectH.setOrigin(CentRectH.getSize() / 2.f);
	CentRectH.setPosition(CentRect.getPosition());


	//Секунды
	sf::RectangleShape CentLineS(sf::Vector2f(6, 150));
	CentLineS.setFillColor(sf::Color::Black);
	CentLineS.setOrigin(sf::Vector2f(3, 0));
	CentLineS.setPosition(CentRect.getPosition());

	//Миллисекунды
	sf::RectangleShape CentLineMs(sf::Vector2f(4, 150));
	CentLineMs.setFillColor(sf::Color::Red);
	CentLineMs.setOrigin(sf::Vector2f(2, 0));
	CentLineMs.setPosition(CentRect.getPosition());

	//Минуты
	sf::RectangleShape CentLineM(sf::Vector2f(8, 140));
	CentLineM.setFillColor(sf::Color::Blue);
	CentLineM.setOrigin(sf::Vector2f(4, 0));
	CentLineM.setPosition(CentRectM.getPosition());
	//Часы
	sf::RectangleShape CentLineH(sf::Vector2f(8, 80));
	CentLineH.setFillColor(sf::Color::Red);
	CentLineH.setOrigin(sf::Vector2f(4, 0));
	CentLineH.setPosition(CentRectH.getPosition());
	#pragma endregion
	sf::CircleShape CentCircle(200);
	CentCircle.setFillColor(sf::Color(66, 135, 245,128));
	CentCircle.setPosition(CentRect.getPosition()-sf::Vector2f(200,200));

	sf::CircleShape CentCircleG(210);
	CentCircleG.setFillColor(sf::Color(107, 112, 120, 128));
	CentCircleG.setPosition(CentRect.getPosition() - sf::Vector2f(210, 210));

	#pragma region Деления
	sf::VertexArray* ClockLines = new sf::VertexArray[60];
	for (size_t i = 0; i < 60; i++)
	{
		ClockLines[i] = sf::VertexArray(sf::Lines, 2);
		for (int j = 0; j < 2; j++)
		{
			ClockLines[i][j].color = (sf::Color::Black);

		}
		float Ang = ((i + 1) * 6) * 0.0175;
		ClockLines[i][0].position = sf::Vector2f(CentRect.getPosition().x - 200 * cos(Ang), CentRect.getPosition().y - 200 * sin(Ang));
		if ((i + 1) % 5 == 0)
		{
			ClockLines[i][1].position = sf::Vector2f(CentRect.getPosition().x - 170 * cos(Ang), CentRect.getPosition().y - 170 * sin(Ang));

		}
		else
			ClockLines[i][1].position = sf::Vector2f(CentRect.getPosition().x - 180 * cos(Ang), CentRect.getPosition().y - 180 * sin(Ang));

	}
#pragma endregion
	#pragma region Углы поворота стрелок
	float anglems = 180.f;
	float angle = 180.f;
	float anglem = 180.f;
	float angleh = 180.f;
	if (!isTimer)
	{
		#pragma region Текущие время
		std::time_t currentTime = std::time(nullptr);
		std::tm t;
		localtime_s(&t, &currentTime);
		#pragma endregion
		//anglems = t.tm_sec / 60;
		angle = (t.tm_sec+2) * 6 - 180.f;
		anglem =( (float)t.tm_min+(float)t.tm_sec/60.f) * 6 - 180.f;
		angleh = ((float)(t.tm_hour > 12 ? t.tm_hour - 12 : t.tm_hour )+ (float)t.tm_min / 60.f) * 30 - 180.f;
		//::cout << (t.tm_hour > 12 ? t.tm_hour - 12 : t.tm_hour);
	}
	#pragma endregion
	sf::Clock clock;
	while (window->isOpen())
	{
		sf::Event e;
		while (window->pollEvent(e))
		{
			if (e.type == sf::Event::Closed())window->close();

		}
		sf::Time deltatime = clock.restart();
		float dts = deltatime.asSeconds();

		//float dtms = deltatime.asMilliseconds();
		//anglems += 3.6f*dtms;
		angle += 6.f*dts;
		anglem += 6.f * dts / 60.f;
		angleh += 30.f * dts / 3600.f;
		//std::cout << angleh << std::endl;

		//if (anglems >= 360)anglems = 0;
		if (angle >= 360)angle = angle-360;
		if (anglem >= 360)anglem = anglem-360;
		if (angleh >= 360)angleh = angleh-360;
		//CentLineMs.setRotation(anglems);
		CentRect.setRotation(angle);
		CentLineS.setRotation(angle);
		CentLineM.setRotation(anglem);
		CentRectM.setRotation(anglem);
		CentLineH.setRotation(angleh);
		CentRectH.setRotation(angleh);

		window->clear(sf::Color::White);
		window->draw(CentCircleG);
		//window->draw(CentCircle);
		//window->draw(CentLineMs);
		window->draw(CentRect);
		window->draw(CentLineS);

		window->draw(CentRectM);
		window->draw(CentLineM);

		window->draw(CentRectH);
		window->draw(CentLineH);
		for (size_t i = 0; i < 60; i++)
		{
			window->draw(ClockLines[i]);
		}
		window->display();
	}
}