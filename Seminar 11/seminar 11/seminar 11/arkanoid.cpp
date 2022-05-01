#include <algorithm>
#include <ctime>
#include <vector>
#include <random>

#include <SFML/Graphics.hpp>

using namespace sf;

int main(int argc, char ** argv)
{
	RenderWindow application(VideoMode(520, 450), "ARKANOID");

	Texture texture_1, texture_2, texture_3, texture_4;

	texture_1.loadFromFile("images/block.png");
	texture_2.loadFromFile("images/background.jpg");
	texture_3.loadFromFile("images/ball.png");
	texture_4.loadFromFile("images/paddle.png");

	Sprite background(texture_2);
	Sprite ball(texture_3);
	Sprite paddle(texture_4);

	paddle.setPosition(1.0f, 440.0f);

	const std::size_t size = 10;

	std::vector < Sprite > blocks;

	for (std::size_t i = 1; i <= size; ++i)
	{
		for (std::size_t j = 1; j <= size; ++j)
		{
			blocks.push_back(Sprite());

			blocks.back().setTexture(texture_1);
			blocks.back().setPosition(i * 42.0f, j * 20.0f);
		}
	}

	float x = 300.0f;
	float y = 300.0f;

	float dx = 0.05f;
	float dy = 0.05f;

	std::default_random_engine dre;
	std::uniform_real_distribution < float > uid(0.05f, 0.07f);

	Event event;

	while (application.isOpen())
	{
		while (application.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				application.close();
			}
		}

		x += dx;

		blocks.erase(std::remove_if(blocks.begin(), blocks.end(), [x, y, &dx](const auto & sprite)
		{
			if (FloatRect(x + 3.0f, y + 3.0f, 6.0f, 6.0f).intersects(sprite.getGlobalBounds()))
			{
				dx = -dx;
				return true;
			}
			return false;
		}), blocks.end());
			
		y += dy;

		blocks.erase(std::remove_if(blocks.begin(), blocks.end(), [x, y, &dy](const auto & sprite)
		{
			if (FloatRect(x + 3.0f, y + 3.0f, 6.0f, 6.0f).intersects(sprite.getGlobalBounds()))
			{
				dy = -dy;
				return true;
			}
			return false;
		}), blocks.end());

		if (x < 0.0f || x > 520.0f - 12.0f)  dx = -dx;
		if (y < 0.0f || y > 450.0f - 12.0f)  dy = -dy;

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			if (paddle.getGlobalBounds().left + paddle.getGlobalBounds().width < 519.0f)
			{
				paddle.move(0.2f, 0.0f);
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			if (paddle.getGlobalBounds().left > 1.0f)
			{
				paddle.move(-0.2f, 0.0f);
			}
		}

		if (FloatRect(x, y, 12.0, 12.0).intersects(paddle.getGlobalBounds()))
		{
			dy = -uid(dre);
		}

		ball.setPosition(x, y);

		application.clear();

		application.draw(background);
		application.draw(ball);
		application.draw(paddle);

		for (const auto & sprite : blocks)
		{
			application.draw(sprite);
		}

		application.display();
	}

	system("pause");

	return EXIT_SUCCESS;
}
