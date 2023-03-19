#pragma once

template <typename T>
class Singleton {
public:
	Singleton() = default;
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton) = delete;

	static T& get() {
		static T instance;
		return instance;
	}
};
