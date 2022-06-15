#pragma once
#include <SFML/Graphics.hpp>
#include <atomic>
#include <memory>
class ArrayElementBar;
class c_application : public sf::Drawable, public sf::Transformable
{
public:
	const unsigned int ARRAY_SIZE = 1000;
	const unsigned int DW_DISPRESION = 100;
	const unsigned short STEP_DELAY_MS = 1;
private:
	float dwAligment = 0;
	int* c_array = nullptr;
	ArrayElementBar* c_bars = nullptr;
public:
	c_application();
	~c_application();
	void initialize();
	void update(ArrayElementBar* bar, int i);
	int* get_array();
	ArrayElementBar* get_bars();
public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
extern std::unique_ptr<c_application>g_application;
namespace worker {
	extern std::atomic_bool sort_working;
	void WorkerThread();
	void bubble_sort(int * arr, int n);
	void merge_sort(int* arr, int l, int r);
}