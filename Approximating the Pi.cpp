#include <vector>
#include <iostream>

// I saw the logic of this at The Coding Train. Just gave it a try and that's some nice shit.

const int* radius = new int(2);
const int* radiusPowered = new int(pow(*radius, 2));
const int* sampleCountEachGeneration = new int(10000);

int* inCircle = new int(0);
int* outCircle = new int(0);

int* step = new int(0);
long double* approximation = new long double();

inline long double GetRandomValue()
{
	long double number = (long double)rand() / (long double)(RAND_MAX) * *radius;

	if (((float)rand() / RAND_MAX) > 0.5) number *= -1;
	return number;
}

struct Particle {
	long double* x = new long double(GetRandomValue());
	long double* y = new long double(GetRandomValue());
	long double* distance = new long double(sqrt((pow(*x, 2) + pow(*y, 2))));
	bool* isInside = new bool(*distance <= *radiusPowered);

	void Update() {
		*x = GetRandomValue();
		*y = GetRandomValue();
		*distance = pow(*x, 2) + pow(*y, 2);
		*isInside = *distance <= *radiusPowered;
	}
};

int main() {
	std::cout.precision(15);
	srand((unsigned) time(NULL));

	std::vector<Particle*>* particles = new std::vector<Particle*>();

	for (int i = 0; i < *sampleCountEachGeneration; ++i) {
		Particle* p = new Particle;
		particles->push_back(p);
	}

	while (true) {
		*inCircle = 0;
		*outCircle = 0;
		
		for (Particle* p : *particles) {
			if (*p->isInside) *inCircle += 1;
			else *outCircle += 1;

			p->Update();
		}

		*step += 1;
		*approximation = ((*step-1) * *approximation + static_cast<long double>(4) * (long double)*inCircle / (long double)*sampleCountEachGeneration) / (long double)*step;
		std::cout << "Approximate Pi: " << *approximation << std::endl;
	}
}