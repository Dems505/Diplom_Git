// Импортируем необходимые библиотеки
#include <SFML/Graphics.hpp>
#include <clipper.hpp>
#include <vector>
#include <iostream>

// Используем пространства имен 
using namespace ClipperLib;
using namespace std;

// Преобразуем список точек в формат понятный для библиотеки Clipper
Path toPath(const vector<IntPoint>& points) {
	Path path;
	for (const auto& point : points) {
		path << point; // Добавляем каждую точку в path
	}
	return path; // Возвращаем path
}

// Преобразование Path в sf::ConvexShape для рисования в SFML
sf::ConvexShape pathToShape(const Path& path) {
	sf::ConvexShape shape;
	shape.setPointCount(path.size()); // Устанавливаем количество точек
	for (int i = 0; i < path.size(); i++) {
		shape.setPoint(i, sf::Vector2f(path[i].X, path[i].Y)); // Задаем координаты каждой точки
	}
	return shape; // Возвращаем shape
}

// Функция для получения входных данных от пользователя
void getInput(vector<IntPoint>& polygon, vector<vector<IntPoint>>& holes) {
	// Получаем данные для основного полигона
	cout << "Enter number of vertices for the polygon: ";
	int numVertices;
	cin >> numVertices;
	polygon.resize(numVertices);
	for (int i = 0; i < numVertices; i++) {
		cout << "Enter coordinates for vertex " << i + 1 << ": ";
		cin >> polygon[i].X >> polygon[i].Y;
	}

	// Получаем данные для дыр
	cout << "Enter number of holes: ";
	int numHoles;
	cin >> numHoles;
	holes.resize(numHoles);
	for (int i = 0; i < numHoles; i++) {
		cout << "Enter number of vertices for hole " << i + 1 << ": ";
		int numVerticesHole;
		cin >> numVerticesHole;
		holes[i].resize(numVerticesHole);
		for (int j = 0; j < numVerticesHole; j++) {
			cout << "Enter coordinates for vertex " << j + 1 << " of hole " << i + 1 << ": ";
			cin >> holes[i][j].X >> holes[i][j].Y;
		}
	}
}


int main() {
	// Получаем входные данные
	vector<IntPoint> polygon;
	vector<vector<IntPoint>> holes;
	getInput(polygon, holes);

	// Создаем окно SFML
	sf::RenderWindow window(sf::VideoMode(800, 600), "Polygon with holes");

	// Преобразуем входные данные в нужные форматы
	sf::ConvexShape polygonShape = pathToShape(toPath(polygon));
	polygonShape.setFillColor(sf::Color::Green); // Задаем цвет полигона
	vector<sf::ConvexShape> holeShapes;
	for (const auto& hole : holes) {
		sf::ConvexShape shape = pathToShape(toPath(hole));
		shape.setFillColor(sf::Color::Red); // Задаем цвет дыр
		holeShapes.push_back(shape);
	}

	while (window.isOpen())
	{
		// Обрабатываем события
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) // Если окно закрыто, выходим из цикла
				window.close();
		}

		// Очищаем окно
		window.clear();

		// Рисуем полигон и дыры
		window.draw(polygonShape);
		for (const auto& holeShape : holeShapes) {
			window.draw(holeShape);
		}

		// Отображаем содержимое окна
		window.display();
	}

	return 0;
}
