#include <vector>
#include <iostream>

// I saw the logic of this at The Coding Train. Just gave it a try and that's some nice shit.

const int* radiusPowered = new int(2*2);
const int* sampleCountEachGeneration = new int(10000);

int* inCircle = new int(0);
int* outCircle = new int(0);

int* step = new int(0);
double* approximation = new double();

inline float GetRandomValue()
{
	return (float)rand() / (float)(RAND_MAX) * *radiusPowered;
}

struct Particle {
	float* x = new float(GetRandomValue());
	float* y = new float(GetRandomValue());
	float* distance = new float((pow(*x, 2) + pow(*y,2)));
	bool* isInside = new bool(*distance <= *radiusPowered);

	void Update() {
		*x = GetRandomValue();
		*y = GetRandomValue();
		*distance = sqrt(pow(*x, 2) + pow(*y, 2));
		*isInside = *distance <= *radiusPowered;
	}
};

int main() {
	srand(time(NULL));
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
		*approximation = ((*step-1) * *approximation + static_cast<double>(4) * (double)*inCircle / (double)*sampleCountEachGeneration) / (double)*step;
		std::cout << "Approximate Pi: " << *approximation << std::endl;
	}
}