#define _CRT_SECURE_NO_WARNINGS
#include <cstdlib>
#include <iostream>
void printEnv(const char* name) {
	const char* value = std::getenv(name);
	std::cout << name << " = "
		<< (value ? value : "<not set>")
		<< "\n";
}
int main() {
	printEnv("PATH");
	printEnv("USERPROFILE");
	printEnv("COURSE_MODE");
}
