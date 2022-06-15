#include "c_application.h"
#include "ArrayElementBar.h"
#include <random>
#include "project.hpp"
#include <thread>
#include <mutex>
std::atomic_bool worker::sort_working(true);
std::atomic_bool is_updating(true);
std::mutex m;
std::unique_ptr<c_application>g_application(new c_application());
static ArrayElementBar* c_copy = new ArrayElementBar[g_application->ARRAY_SIZE];
c_application::c_application()
{
}
c_application::~c_application()
{
	if (this->c_array)
		delete[] c_array;
	this->c_array = nullptr;
	if (this->c_bars)
		delete[] c_bars;
	this->c_bars = nullptr;
	delete[] c_copy;
}

void c_application::initialize()
{
	srand(NULL);
	this->c_array = new int[this->ARRAY_SIZE];
	this->c_bars = new ArrayElementBar[this->ARRAY_SIZE];
	for (size_t i = 0u; i < this->ARRAY_SIZE; ++i) {
		this->c_array[i] = rand() % DW_DISPRESION;
		this->dwAligment = std::fmax(c_array[i], dwAligment);
		this->c_bars[i] = ArrayElementBar(this->c_array[i], sf::Vector2f(static_cast<float>(i) / static_cast<float>(this->ARRAY_SIZE) * static_cast<float>(project::SCREEN_WIDTH),project::SCREEN_HEIGHT));
		this->c_bars[i].set_size(sf::Vector2f(static_cast<float>(project::SCREEN_WIDTH)/ static_cast<float>(this->ARRAY_SIZE)/1.25f, 0));
	}
	std::thread worker(worker::WorkerThread);
	worker.detach();
}
void c_application::update(ArrayElementBar * bar, int i)
{
	bar->set_value(c_array[i]);
	bar->set_position(sf::Vector2f(static_cast<float>((float)i / (float)this->ARRAY_SIZE * (float)project::SCREEN_WIDTH), project::SCREEN_HEIGHT));
	const auto width = (float)project::SCREEN_WIDTH / (float)this->ARRAY_SIZE / 1.25f;
	const auto height = (float)bar->get_value() / (float)dwAligment * (float)project::SCREEN_HEIGHT;
	bar->set_size(sf::Vector2f(width, -height));
}
int * c_application::get_array()
{
	return this->c_array;
}
ArrayElementBar * c_application::get_bars()
{
	return this->c_bars;
}
void c_application::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= this->getTransform();
	sf::Color fillColor = sf::Color(255, 255, 255, 255);
	//sf::Color outlineColor = sf::Color(255, 0, 0, 255);
	if (!is_updating.load())
	{
		std::memcpy(c_copy, this->c_bars, sizeof(ArrayElementBar)*this->ARRAY_SIZE);
	}
	for (size_t i = 0u; i < this->ARRAY_SIZE; ++i) {
		sf::RectangleShape rectangle = sf::RectangleShape(c_copy[i].get_size());
		rectangle.setPosition(c_copy[i].get_position());
		//rectangle.setOutlineThickness(c_copy[i].get_size().x/4.f);
		rectangle.setFillColor(fillColor);
		//rectangle.setOutlineColor(outlineColor);
		target.draw(rectangle);
	}
}
void worker::WorkerThread()
{
	//std::thread sort_thread(bubble_sort, std::ref(g_application->c_array), g_application->ARRAY_SIZE);
	std::thread sort_thread(merge_sort, g_application->get_array(),0, g_application->ARRAY_SIZE-1);
	sort_thread.detach();
	while (sort_working.load())
	{
		is_updating = true;
		for (size_t i = 0u; i < g_application->ARRAY_SIZE; ++i) {
			g_application->update(&g_application->get_bars()[i], i);
		}
		is_updating = false;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000/60));
	}
	is_updating = true;
	for (size_t i = 0u; i < g_application->ARRAY_SIZE; ++i) {
		g_application->update(&g_application->get_bars()[i], i);
	}
	is_updating = false;
}




void worker::bubble_sort(int * arr, int n)
{
	sort_working = true;
	bool swapped = true;
	while (swapped)
	{
		swapped = false;
		for (size_t i = 0u; i < n-1; i++) {
			if (arr[i] > arr[i + 1]) {
				swapped = true;
				int tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
				std::this_thread::sleep_for(std::chrono::milliseconds(g_application->STEP_DELAY_MS));
			}	
		}
	}
	sort_working = false;
}
void merge(int* arr, int l, int h, int mid) {
	
	int i, j, k;
	int* helper = new int[l + h +1];
	i = k = l;
	j =  mid + 1;
	while (i <= mid && j <= h) {
		if (arr[i] < arr[j]) {
			helper[k] = arr[i];
			k++;
			i++;
		}
		else {
			helper[k] = arr[j];
			j++;
			k++;
		}
	}
	while (i <= mid) {
		helper[k] = arr[i];
		k++;
		i++;
	}
	while (j <= h) {
		helper[k] = arr[j];
		k++;
		j++;
	}
	for (i = l; i < k; i++) {
		arr[i] = helper[i];
		std::this_thread::sleep_for(std::chrono::milliseconds(1));//для наглядности
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(g_application->STEP_DELAY_MS));
	delete[] helper;
}
void i_merge_sort(int * arr, int l, int r)
{
	int mid = (l + r) / 2;
	if (l < r) {
		i_merge_sort(arr, l, mid);
		i_merge_sort(arr, mid + 1, r);
		merge(arr, l, r, mid);
	};
}
void worker::merge_sort(int * arr, int l, int r)
{
	sort_working = true;
	i_merge_sort(arr, l, r);
	sort_working = false;
}
