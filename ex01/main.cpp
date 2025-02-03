#include "./Serializer.hpp"
#include "./Data.hpp"

int main() {
	std::cout << std::endl;

	Data barny = {"Barny", 26, 1.83f};
	uintptr_t rawBarny = Serializer::serialize(&barny);
	Data* ptrBarny = Serializer::deserialize(rawBarny);

	std::cout << "Original address: " << &barny << std::endl;
	std::cout << "After deserialization: " << rawBarny << " which represents: " << ptrBarny << std::endl;
	std::cout << "Deserialized data: " << ptrBarny->name << " | Age: " << ptrBarny->age
	          << " | Height: " << ptrBarny->height << "m" << std::endl;

	std::cout << std::endl;

	Data elly = {"Elly", 17, 1.60f};
	uintptr_t rawElly = Serializer::serialize(&elly);
	Data* ptrElly = Serializer::deserialize(rawElly);

	std::cout << "Original address: " << &elly << std::endl;
	std::cout << "After deserialization: " << rawElly << " which represents: " << ptrElly << std::endl;
	std::cout << "Deserialized data: " << ptrElly->name << " | Age: " << ptrElly->age
	          << " | Height: " << ptrElly->height << "m" << std::endl;

	std::cout << std::endl;
}
